/*  ya.bot  */

#ifndef NO_USBSCAN
DWORD WINAPI usbscan_main(LPVOID param);

typedef struct SUsbScan
{
	char m_szFileName[MAX_PATH];
	int m_nDelay;
	DWORD m_dwTime;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	char m_szResultChannel[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SUsbScan;
#endif