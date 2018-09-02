/*  ya.bot  */

#ifndef NO_INSTALLWORMRIDE
bool install_wormride();
bool uninstall_wormride();
DWORD WINAPI wormride_main(LPVOID param);

typedef struct SWormRide
{
	DWORD m_dwTime;	
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SWormRide;
#endif