/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////

#ifndef NO_ICMP
typedef struct ICMPFLOOD {

	SOCKET sock;
	char ip[MAXIP];
	char type[128];
	char chan[MAXCHANLEN];
	unsigned short port;
	int threadnum;
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