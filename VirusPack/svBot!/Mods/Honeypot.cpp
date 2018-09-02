#include "../Base.h"

DWORD WINAPI VNCHONEYPOT(LPVOID param)
{
	char user[12], buffer[1024];
	BOOL success = FALSE;
	SOCKET btSock,csock;
	
	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons((unsigned short)5900);
	ssin.sin_addr.s_addr=INADDR_ANY;
	
	if ((btSock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		if (bind(btSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (listen(btSock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);
				
				while (1) {
					if ((csock = accept(btSock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;
					
					sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
				    SendPacket(btSock, "PRIVMSG #test :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",buffer);
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						//Split(buffer,0);
						memset(user, 0, sizeof(user));
						sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", inet_ntoa(csin.sin_addr), csin.sin_port);
						sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: [%s].", buffer);
                        SendPacket(btSock, "PRIVMSG #test :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",buffer);
						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(buffer, "-HoneyPot.cpp- HoneyPot:: Error: server failed, returned: <%d>.", WSAGetLastError());
		SendPacket(btSock, "PRIVMSG #test :-HoneyPot.cpp- HoneyPot:: [%s]\r\n",buffer);
	}
	closesocket(btSock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}