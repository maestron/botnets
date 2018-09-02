typedef struct IRC 
{
	SOCKET sock;
	char host[MAXHOSTNAME];
	char channel[MAXCHANLEN];
	char chanpass[MAXCHANLEN];
	char nick[MAXNICKLEN];
	unsigned short port;
	int clone;
	int threadnum;
	BOOL gotinfo;

} IRC;

int IRC_Startup(void);
