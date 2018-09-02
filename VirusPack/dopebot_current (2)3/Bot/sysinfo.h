

#ifndef NO_SYSINFO
static inline unsigned __int64 cyclecount();
void get_computername(char *szBuffer);
void get_cpu(char *szBuffer);
void get_mem(char *szBuffer);
void get_os(char *szBuffer);
void get_sysinfo(char *szBuffer);
void get_uptime(char *szBuffer);
void get_username(char *szBuffer);
bool is_os9x();
bool is_osnt();
#endif