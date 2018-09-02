#include "../Base.h"

bool KillSBox( )
{
	char *users[] = {"sandbox", "honey", "vmware", "nepenthes", "user", "USER"};
	DWORD size = 128;
	char btUser[128];
	int i;
	GetUserName(btUser, &size);
	CharLower(btUser);
	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(btUser, users[i]) != 0)
			 return TRUE;
	}
	return FALSE;
}