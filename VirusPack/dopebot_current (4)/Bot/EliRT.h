#ifndef _ELIRT_
#define _ELIRT_ 0x100

#ifdef __cplusplus
extern "C" {
#endif
  DWORD  __stdcall RT_GetVersion(VOID *pReserved);
  LPVOID __stdcall xVirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD flAllocationType, DWORD flProtect);
  BOOL   __stdcall xVirtualFreeEx (HANDLE hProcess, LPVOID lpAddress, DWORD dwSize, DWORD dwFreeType);
  HANDLE __stdcall xCreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, DWORD dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
  HANDLE __stdcall xOpenThread(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwThreadId);
#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma comment(lib, "EliRT_COFF.lib")
#endif
#ifdef __TURBOC__
#pragma comment(lib, "EliRT_OMF_B.lib")
#endif
#ifdef __SC__
#pragma comment(lib, "EliRT_OMF.lib")
#endif
#ifdef __WATCOMC__
#pragma comment(lib, "EliRT_OMF.lib")
#endif
#ifdef __LCC__
#pragma comment(lib, "EliRT_COFF.lib")
#endif

#endif