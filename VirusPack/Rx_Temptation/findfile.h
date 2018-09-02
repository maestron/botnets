#ifndef NO_FINDFILE
typedef struct FFIND
{
	SOCKET sock;
	char chan[128];
	char filename[MAX_PATH];
	char dirname[MAX_PATH];
	int threadnum;
	bool notice;
	bool silent;
	bool gotinfo;

} FFIND;

DWORD WINAPI FindFileThread(LPVOID param);
unsigned int FindFile(SOCKET sock, char *chan, bool notice, char *filename, char *dirname, unsigned int numfound);
#endif
