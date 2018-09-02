/*  ya.bot  */

__int64 info_cpucycle();
DWORD info_cpuspeed();
#ifndef NO_INFO
void info_getnet(SOCKET bsock, char *pszServer, char *pszBuffer, DWORD dwSize);
void info_getsys(char *pszBuffer, DWORD dwSize);
#endif
bool info_goodbot(SOCKET bsock);
int info_os();
