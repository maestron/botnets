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

#ifndef NO_NETINFO
#include "bot.h"

//Get Connection Info (IP & Host)
void get_connection_info(SOCKET bsock, char *szBuffer)
{
	char szHost[LOWBUF];
	SOCKADDR sa;
	int sas;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting connection ip and host, getconnectioninfo()...\n");
#endif

	if (gethostname(szHost, sizeof(szHost)) == SOCKET_ERROR) return;
		sas = sizeof(sa);
		memset(&sa, 0, sizeof(sa));
		getsockname(bsock, &sa, &sas);
		sprintf(szBuffer, "local IP address: %d.%d.%d.%d. connected from: %s", (BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5], szHost);
}

//Get ConnectionType
void get_connection_type(char *szBuffer)
{
	char szName[LOWBUF];
	DWORD dwCon;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting connection type, getconnectiontype()...\n");
#endif

		InternetGetConnectedStateEx(&dwCon, szName, sizeof(szName), 0);
    if (dwCon & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) sprintf(szBuffer, "connection type: dial-up (%s)", szName);
//	else if (dwCon & INTERNET_CONNECTION_LAN == INTERNET_CONNECTION_LAN) sprintf(szBuffer, "connection type: LAN (%s)", szName);
//	else if (dwCon & INTERNET_CONNECTION_PROXY == INTERNET_CONNECTION_PROXY) sprintf(szBuffer, "connection type: proxy (%s)", szName);
//	else sprintf(szBuffer, "connection type: unknown (%s)", szName);
	else sprintf(szBuffer, "connection type: LAN (%s)", szName);
	return;
}

//Get Net Info
void get_netinfo(SOCKET bsock, char *szBuffer)
{
	char szNetBuff[MEDBUF];

#ifndef NO_DEBUG
		printf("[DEBUG] Getting connection info, getnetinfo()...\n");
#endif

//Get Connection Type
		get_connection_type(szNetBuff);
		strcat(szBuffer, szNetBuff);
		strcat(szBuffer, ". ");
//Get Connection Info
		get_connection_info(bsock, szNetBuff);
		strcat(szBuffer, szNetBuff);
		return;
}
#endif