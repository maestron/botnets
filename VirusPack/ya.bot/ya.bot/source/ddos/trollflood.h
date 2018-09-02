/*  ya.bot  */

#ifndef NO_TROLLFLOOD
DWORD WINAPI trollflood_main(LPVOID param);

typedef struct STrollFlood
{
	char m_szHost[LOWBUF];
	int m_nPort;
	int m_nSockets;
	int m_nDelay;
	DWORD m_dwTime;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} STrollFlood;
#endif