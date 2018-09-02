#ifndef NO_TFTPD
typedef struct TFTP
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

} TFTP;

DWORD WINAPI tftpserver(LPVOID pParam);
#endif