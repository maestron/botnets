
typedef struct irc_server {
	char	host[MAX_HOSTNAME];			// The server host
	char	pass[16];					// The server password
	int		port;						// The server port
	BOOL	usessl;						// Is this server/port ssl?
	char	chan[MAX_NICKLEN];			// The channel
	char	chanpass[16];				// The channel pass
	char	modeonconn[12];				// The modes to set on connect
	char	modeonjoin[12];				// The modes to set on op
	char	exploitchan[MAX_NICKLEN];	// The exploit channel
	//char	keylogchan[MAX_NICKLEN];	// The keylog channel
	char	sniffchan[MAX_NICKLEN];		// The sniffer channel
	char	warningchan[MAX_NICKLEN];	// The warning channel
} SERVER;

DWORD WINAPI BotThread(LPVOID param);
