/*  ya.bot  */

#ifndef NO_DAEMONFTP
DWORD WINAPI daemon_ftphandler(LPVOID param);
DWORD WINAPI daemon_ftpmain(LPVOID param);
bool daemon_ftptransfer(char *pszIP, int nPort, char *pszFilePath);

typedef struct SDaemonFTP
{
	SOCKET m_csock;
	SOCKET m_bsock;
	char m_szResultChannel[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SDaemonFTP;
#endif
