#ifndef NO_TERM
typedef struct TERMFLOOD {

	SOCKET sock;
	char ip[128];
	char chan[128];
	int threadnum;
	unsigned int port;
	int type;
	bool notice;
	bool silent;
	bool gotinfo;

} TCPFLOOD;

DWORD WINAPI TermFloodThread(LPVOID param);
#endif