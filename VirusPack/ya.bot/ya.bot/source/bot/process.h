/*  ya.bot  */

bool process_killpid(DWORD dwPID);
DWORD process_list(SOCKET bsock,
		char *pszAction,
		char *pszDestination,
		bool bSilent,
		bool bVerbose);
DWORD process_start(char *pszFilePath, bool bVisible);