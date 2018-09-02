typedef struct ipsites {
	char *site;
	char *match;
	char *useless;
	BOOL tried;
} IPSITES;

DWORD host2ip(char *hostname);

#ifndef NO_FLUSHARP
BOOL FlushARPCache(void);
#endif

#ifndef NO_FLUSHDNS
BOOL FlushDNSCache(void);
#endif

#ifndef NO_GET_IP_HTTP
char *GetExternalIp(void);
DWORD WINAPI GetExIP(LPVOID param);
#endif
BOOL PrivateIP(const char *ip);
