/*  ya.bot  */

#ifndef NO_DAEMONSOCKS4
DWORD WINAPI daemon_socks4handler(LPVOID param);
DWORD WINAPI daemon_socks4main(LPVOID param);

typedef struct SDaemonSOCKS4
{
	int m_nPort;
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SDaemonSOCKS4;

typedef struct SDaemonSOCKS4Info
{
	BYTE m_byVn;
	BYTE m_byCd;
	WORD m_wDstPort;
	DWORD m_dwDstIp;
	BYTE m_byUserId[BIGBUF];
} SDaemonSOCKS4Info;
#endif