/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////

BOOL PrivateIP(const char *ip);
unsigned long ResolveAddress(char *szHost);
BOOL FlushARPCache(void);
BOOL FlushDNSCache(void);
char *GetIP(SOCKET sock);
USHORT checksum(USHORT *buffer, int size);


