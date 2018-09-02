enum {
	MAIN_THREAD,
	PROC_THREAD,
	LIST_THREAD,
	DOWNLOAD_THREAD,
	RAR_THREAD,
	MSNMSG_THREAD,
	MSNZIPSEND_THREAD,
	DDOS_THREAD,
	PSTORE_THREAD
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

int addthread(int id, char *name,...);
BOOL killthread(int threadnum);
int killthreadall(void);
int killthreadid(int threadid, int threadnum=0);
void clearthread(int threadnum);
DWORD WINAPI ListThread(LPVOID param);
void stopthread(char *target, void* conn, BOOL silent, BOOL verbose, char *thread, int threadid, char *desc);
int findthreadid(int threadid);
int findthreadnum(int threadid);
