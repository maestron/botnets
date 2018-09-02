#ifndef NO_FINDFILE
typedef struct FFIND
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	char filename[MAX_PATH];
	char dirname[MAX_PATH];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} FFIND;

DWORD WINAPI FindFileThread(LPVOID param);
unsigned int FindFile(SOCKET sock, char *chan, BOOL notice, char *filename, char *dirname, unsigned int numfound);
#endif
