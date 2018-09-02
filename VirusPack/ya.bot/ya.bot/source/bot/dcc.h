/*  ya.bot  */

#ifndef NO_DCC
DWORD WINAPI dcc_get(LPVOID param);
DWORD WINAPI dcc_send(LPVOID param);

typedef struct SDCCGet
{
	DWORD m_dwIP;
	int m_nPort;
	char m_szFileName[MAX_PATH];
	DWORD m_dwFileLength;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SDCCGet;

typedef struct SDCCSend
{
	char m_szNick[LOWBUF];
	char m_szFilePath[MAX_PATH];
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SDCCSend;
#endif