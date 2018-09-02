#ifndef NO_TFTPD
typedef struct TFTP 
{
	SOCKET sock;
	char filename[MAX_PATH];
	char requestname[MAX_PATH];
	int threadnum;
	int threads;
	unsigned short port;
	char chan[128];
	bool notice;
	bool silent;
	bool gotinfo;

} TFTP;

DWORD WINAPI tftpserver(LPVOID pParam);
#endif