/*  ya.bot  */

#ifndef NO_DAEMONHTTP
DWORD WINAPI daemon_httphandler(LPVOID param);
DWORD WINAPI daemon_httpmain(LPVOID param);

typedef struct SDaemonHTTP
{
	SOCKET m_csock;
	SOCKET m_bsock;
	char m_szResultChannel[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SDaemonHTTP;
#endif