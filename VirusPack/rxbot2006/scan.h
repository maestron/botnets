#ifndef NO_SCAN
// scan structure
typedef struct SCAN 
{
	SOCKET sock;
	char chan[128];
	int port;
	int maxport;
	int delay;
	int threadnum;
	IN_ADDR addy;
	DWORD host;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	BOOL cgotinfo;

} SCAN;

DWORD WINAPI ScanConnectThread(LPVOID param);
DWORD WINAPI ScanThread(LPVOID param);
DWORD WINAPI PortScanThread(LPVOID param);
#endif
