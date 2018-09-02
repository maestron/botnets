#define SOCKS4_CONNECT 1
#define SOCKS4_BIND 2
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91
#define SOCKS4_REJECT_IDENTD 92
#define SOCKS4_REJECT_USERID 93

struct socks4_hdr
/* socks4 header */
{
	unsigned char vn;
	unsigned char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];
};

struct socks4s
/* struct for various socks4 functions */
{
	int tnum;
	unsigned short port;
	bool gotinfo;
	bool cgotinfo;
	SOCKET sock;
};

void socks4_tloop(SOCKET tsock, SOCKET csock);

DWORD WINAPI socks4_start(void *param);

DWORD WINAPI socks4_child(void *param);
