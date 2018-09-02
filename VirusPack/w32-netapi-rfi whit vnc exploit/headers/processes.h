#ifndef NO_PROCESS
typedef struct process_info_s {
	char			sProcessName[256];
	unsigned long	lProcessPid;
	char			mUsage[128];
} process_info;

DWORD WINAPI ProcessThread(LPVOID param);
bool ListProcesses(std::list<process_info> *lProcesses, char *filter);
bool KillProcess(const char *szProcName, char * procKilled);
BOOL KillPid(unsigned long lPid);
DWORD WINAPI CreateProcThread(LPVOID param);
PCHAR ProcessPidToName(DWORD ProcessId,PCHAR ProcessName);
#endif