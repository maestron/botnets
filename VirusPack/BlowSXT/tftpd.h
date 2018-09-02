#ifndef NO_TFTPD
typedef struct tftpd {
	SOCKET socket;
	char filename[MAX_PATH];
	char requestname[MAX_PATH];
	int threadnum;
	int threads;
	char chan[128];
	BOOL silent;
	BOOL notice;
	BOOL info;
} TFTP, tftpd;

DWORD WINAPI tftpserver(LPVOID pParam);
#endif