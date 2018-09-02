typedef struct PARAMS
{
	BOOL silent;
	BOOL halfsilent;
	BOOL verbose;
	BOOL stop;
	BOOL force;
	BOOL replace_underscores;//for .file copy/move
	char replace_char;
	BOOL createwait;//for .file createproc
	BOOL overwrite;//for .file copy
	BOOL attrib_system;//for .file attrib
	BOOL attrib_hidden;//for .file attrib
	BOOL attrib_readonly;//for .file attrib
	BOOL attrib_normal;//for .file attrib
	
	BOOL netstat_noresolve;
	BOOL netstat_all;

} SWITCHES;

int IRC_TempCommand(char *params,irc_reply_data* hostd,void* conn,BOOL silent,BOOL topic=FALSE);
int IRC_CommandParse(char *a[MAX_TOKENS],int t,char *params,irc_reply_data* hostd,void* conn,SWITCHES switches,BOOL topic=FALSE);

