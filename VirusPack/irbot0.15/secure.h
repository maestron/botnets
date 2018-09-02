

typedef struct SECURE
{
	SOCKET sock;
	char chan[128];
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
DWORD WINAPI AutoSecure(LPVOID param);
#endif