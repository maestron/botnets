#ifndef NO_SCAN
// scan structure
typedef struct scans {
	IN_ADDR addy;
	char chan[128];
	int port;
	int delay;
	SOCKET sock;
	int threadnum;
	DWORD host;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;
	BOOL cgotinfo;
} scans;

DWORD WINAPI ip_connect(LPVOID param);
DWORD WINAPI ip_scan(LPVOID param);
#endif
