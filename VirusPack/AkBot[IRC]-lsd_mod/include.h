#ifdef WIN32
#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
#pragma comment(linker,"/RELEASE")			// Release code
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.
//#pragma pack(1)								// Force packing on byte boundaries.
#endif // WIN32

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

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <winsock2.h>
#include <windows.h>
#include <shellapi.h>
#include <wininet.h>
#include <process.h>
#include <tlhelp32.h>
#pragma comment(lib, "user32")


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <winsock2.h>
#include <windows.h>
#include <shellapi.h>
#include <wininet.h>
#include <tlhelp32.h>
#include <winsvc.h>
#include "akbot.h"
#include "asn.h"
#include "download.h"
#include "ftpd.h"
#include "ip.h"
#include "irc.h"
#include "netapi.h"
#include "process.h"
#include "scanner.h"
#include "thread.h"
#include "ehttp.h"