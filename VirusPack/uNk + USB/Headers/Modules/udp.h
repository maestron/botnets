
#ifndef NO_UDP
 // ping/udp structure.
typedef struct UDPFLOOD
{
	SOCKET sock;
	char chan[128];
	char host[128];
	int num;
	int size;
	int delay;
	int port;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	void *conn;
	char target[128];
} UDPFLOOD;

DWORD WINAPI udp(LPVOID param);
#endif

