/*  ya.bot  */

bool thread_add(char *pszName, int nID, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter);
bool thread_find(int nID);
bool thread_kill(int nThread);
void thread_killall();
bool thread_killid(int nID);
void thread_list(SOCKET bsock, char *pszAction, char *pszDestination, bool bSilent, bool bVerbose);
bool thread_remove(int nID);

typedef struct SThread
{
	char m_szName[LOWBUF];
	int m_nID;
	HANDLE m_hThread;
} SThread;