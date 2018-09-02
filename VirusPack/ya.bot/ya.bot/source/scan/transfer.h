/*  ya.bot  */

#ifndef NO_EXPSCAN
bool transfer_directtransfer(char *pszIP,
		int nPort,
		char *pszExploitName,
		SOCKET bsock,
		char *pszResultChannel,
		bool bSilent,
		bool bVerbose);
bool transfer_shelltransfer(SOCKET bsock, char *pszIP, int nPort);
#endif