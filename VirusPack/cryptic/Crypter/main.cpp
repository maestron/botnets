#pragma comment(linker, "/OPT:NOREF") // this tells the linker to keep the machine code of unreferenced source code
#pragma optimize("", off) // disable all optimizations in order for our stub to run smootly, though im not sure if it really helps, i just saw some guy doing it this way lolz :)

#include <windows.h> // familiar?
#include <stdio.h> // i wonder what this might be, hmm...

// gets the first sections header offset
#define SECHDROFFSET(a) ((LPVOID) ( (LPBYTE) a			 + \
						((PIMAGE_DOS_HEADER)a)->e_lfanew + \
						sizeof(IMAGE_NT_HEADERS)))

// those are the offsets to the 
#define OEP_o 21 // original entry point
#define SEG_o 11 // virtual address of section
#define BSZ_o 1  // block size, must be a multiple of 8
#define  SZ_o 6  // section size, must be a multiple of the chosen block size
				 // values in the stub

// a simple block xor
// every byte in the given block is XOR'ed with its index
void _xor_block(unsigned char *pblock, unsigned int blocksize)
{
	unsigned int i;

	for(i = 0; i < blocksize; i++)
		pblock[i] ^= i;

	return;
}

// just a wrapper around the above function
int _xor_chunk(unsigned char* pchunk, unsigned long chunksize, unsigned int blocksize)
{
	if(chunksize % blocksize || blocksize % 8)
		return -1;

	unsigned long index = 0;

	while(index < chunksize)
	{
		_xor_block(pchunk + index, blocksize);
		index += blocksize;
	}

	return 0;
}

// this is our stub and the new entry point for the encrypted PE
__declspec(naked) void __stdcall _stub(void)
{
	__asm
	{
		push 0xFEFEFEFE //blocksize
		push 0xFDFDFDFD //chunksize
		push 0xFCFCFCFC //pchunk

		call _xor_chunk //decrypt

		mov eax, 0x7FFFFFFF //oep
		jmp eax //go go
	}
}

// a placeholder, used for stub size calculation
__declspec(naked) int _end(void)
{
	__asm ret 8
}

// so basicly the ASM code of the above 3 (w/o _end) functions will be added to the end of the ".text" section
// after updating the proper values in the stub, ofc
// then the PE header is updated along with the section header
// and with the entry point at _stub's code its all done! wow that was easy oO

// GO GO POWER RANGERS!!!
int main(void)
{
	// im not going to lecture you about those, if you are not familiar with these structures, you should go read about PE format...
	PIMAGE_DOS_HEADER	  pDosH;
	PIMAGE_NT_HEADERS     pNtH;
	PIMAGE_SECTION_HEADER pSecH;

	// variables
	HANDLE hFile;

	DWORD  dwFileSize, dwSectionSize, dwStubSize, 
		   dwVSize, dwOldProt, dwSpot, dwGap, bytes;
	
	LPBYTE FileBuffer, SectionBuffer;
	CHAR FileName[MAX_PATH];

	// get the filename to encrypt
	printf("File to encrypt: ");
	scanf("%s", &FileName);

	// open it and get the size
	hFile = CreateFile(FileName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	dwFileSize = GetFileSize(hFile, 0);

	// load in memory
	FileBuffer = (LPBYTE) malloc(dwFileSize);
	ReadFile(hFile, FileBuffer, dwFileSize, &bytes, 0);


	pDosH = (PIMAGE_DOS_HEADER) FileBuffer;

	// check if it is valid PE, i would say that this is merely a proper check, for a proper one you would need to calculate all the RVA's and see if they are valid
	if(pDosH->e_magic != IMAGE_DOS_SIGNATURE)
		return -1;

	pNtH = (PIMAGE_NT_HEADERS) (FileBuffer + pDosH->e_lfanew);

	if(pNtH->Signature != IMAGE_NT_SIGNATURE)
		return -2;


	pSecH = (PIMAGE_SECTION_HEADER) SECHDROFFSET(FileBuffer);

	while(memcmp(pSecH->Name, ".text", 5)) // get the ".text" section header
		pSecH++;
	
	dwVSize			 = pSecH->Misc.VirtualSize; // the virtual size of the section, later this will be used as chunksize in our stub, after proper alignment
	dwSectionSize	 = pSecH->SizeOfRawData; // speaks for itself
	dwStubSize		 = (DWORD) _end - (DWORD) _xor_block; // the stubsize, in bytes
	

	SectionBuffer = (LPBYTE) malloc(dwSectionSize); // allocate memory enough to hold our raw section data 
	memcpy(SectionBuffer, FileBuffer + pSecH->PointerToRawData, dwSectionSize); // ... copy the data

	_xor_chunk(SectionBuffer, dwSectionSize, 256); // aaand encrypt it! you can use different block sizes here - 8, 16, 32, 64, 128, 256, 512...
	memset(SectionBuffer + pSecH->Misc.VirtualSize, 0, (dwSectionSize - pSecH->Misc.VirtualSize)); // fill with zeros after the end of actual data


	dwSpot = pSecH->Misc.VirtualSize; // this will be the offset (relative to the beginning of the section) where we will place our stub

	while(dwSpot % 16) // align it to 16 byte boundary
		dwSpot++;

	dwSpot += 256; // this is in order to prevent the stub from corruption by overwriting its own code, since we will place it after the end of the section data
	dwGap   = dwSpot - pSecH->Misc.VirtualSize; // the gap between our stub and the end of the data

	
	DWORD oep = pNtH->OptionalHeader.AddressOfEntryPoint + pNtH->OptionalHeader.ImageBase; // the original entry point, this is a linear address
	DWORD seg = pSecH->VirtualAddress + pNtH->OptionalHeader.ImageBase; // the section address, you guessed right, this too is a linear one
	DWORD bsz = 256; // you know what this is

	while(dwVSize % bsz) // we need to align it to block size
		dwVSize++;

	VirtualProtect(_xor_block, dwStubSize, PAGE_EXECUTE_READWRITE, &dwOldProt); // to be able to update the stub...

	// and update it, blah, blah, blah...
	memcpy((void *)((unsigned long) _stub + OEP_o), &oep, 4);
	memcpy((void *)((unsigned long) _stub + SEG_o), &seg, 4);
	memcpy((void *)((unsigned long) _stub + BSZ_o), &bsz, 4);
	memcpy((void *)((unsigned long) _stub +  SZ_o), &dwVSize, 4);

	memcpy(SectionBuffer + dwSpot, _xor_block, dwStubSize); // place the damn thing already!


	pSecH->Characteristics						 = 0xE0000060; // R/W/E, executable code, initialized data. although my experience shows that you are just fine with R/W...
	pSecH->Misc.VirtualSize						+= dwStubSize + dwGap; // update the virtual size of the section
	pNtH->OptionalHeader.AddressOfEntryPoint	 = pSecH->VirtualAddress + dwSpot + ( (DWORD)_stub - (DWORD)_xor_block ) ;


	// and finally update the file
	SetFilePointer(hFile, pSecH->PointerToRawData, 0, FILE_BEGIN);				//new section data
	WriteFile(hFile, SectionBuffer, dwSectionSize, &bytes, 0);

	SetFilePointer(hFile, pDosH->e_lfanew, 0, FILE_BEGIN);						//new PE header
	WriteFile(hFile, pNtH, sizeof(IMAGE_NT_HEADERS), &bytes, 0);

	SetFilePointer(hFile, ((DWORD) pSecH - (DWORD) FileBuffer), 0, FILE_BEGIN);	//new section header
	WriteFile(hFile, pSecH, sizeof(IMAGE_SECTION_HEADER), &bytes, 0);

	// some good habits :)
	CloseHandle(hFile);

	free(FileBuffer);
	free(SectionBuffer);

	return 0;
}

// bye, bye, EOF