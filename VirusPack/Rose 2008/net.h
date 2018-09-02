//secure function
#ifndef NO_SECSYSTEM
//net.cpp
static char *AsWideString(const char *cszANSIstring);
char *AsAnsiString(const WCHAR *cszWIDEstring);
NET_API_STATUS ShareAdd(char *ServerName, char *ShareName, char *SharePath);
NET_API_STATUS ShareDel(char *ServerName, char *ShareName);
#endif