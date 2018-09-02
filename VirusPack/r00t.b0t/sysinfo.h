enum {OS_UNKNOWN, OS_WIN95, OS_WIN98, OS_WINME, OS_WINNT, OS_WIN2K, OS_WINXP, OS_WIN2K3, OS_WINVISTA};

char *Uptime(int startup=0);
int OSVersionCheck(void);

#ifndef NO_SYSINFO
inline unsigned __int64 GetCycleCount(void);
unsigned __int64 GetCPUSpeed(void);
char *sysinfo(char *sinfo, SOCKET sock);
#endif

#ifndef NO_NETINFO
char *netinfo(char *ninfo, char *host, SOCKET sock);
#endif
