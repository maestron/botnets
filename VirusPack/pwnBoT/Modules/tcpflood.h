#ifndef NO_TCP
typedef struct TCPFLOOD {

	SOCKET sock;
	char ip[MAXIP];
	char type[128];
	char chan[MAXCHANLEN];
	int threadnum;
	unsigned short port;
	int time;
	BOOL spoof;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} TCPFLOOD;

DWORD WINAPI TcpFloodThread(LPVOID param);
#endif
