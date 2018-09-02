char *Uptime(int startup=0);

#ifndef NO_SYSINFO
inline unsigned __int64 GetCycleCount(void);
unsigned __int64 GetCPUSpeed(void);
unsigned __int64 cpuspeed2(void);
char *sysinfo(char *sinfo, SOCKET sock);
#endif

#ifndef NO_NETINFO
char *netinfo(char *ninfo, char *host, SOCKET sock);
#endif
