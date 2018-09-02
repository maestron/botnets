#include "../h/includes.h"

BOOL AntiSandBox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser", "nepenthes", "andy"};
	DWORD size = 128;
	char szUser[128];
	int i;

	GetUserName(szUser, &size);
	CharLower(szUser);

	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(szUser, users[i]) != 0)
			 return TRUE;
	}

	return FALSE;
}
