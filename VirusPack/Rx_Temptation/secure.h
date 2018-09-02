typedef struct SECURE 
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	bool secure;
	bool notice;
	bool silent;
	bool gotinfo;

} SECURE;

typedef struct NetShares
{
	char *ShareName;
	char *SharePath;
		
} NetShares;

DWORD WINAPI SecureThread(LPVOID param);
bool SecureSystem(SOCKET sock, char *chan, bool notice, bool silent);
bool UnSecureSystem(SOCKET sock, char *chan, bool notice, bool silent);
#ifndef NO_SECSYSTEM
DWORD WINAPI AutoSecure(LPVOID param);
#endif