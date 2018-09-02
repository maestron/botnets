#include "Thif.h"

char *Thif::CheckForCdKey(HKEY hk, char *path, char *name, char *GameName)
{
	char *ret = new char[256];
	memset(ret, '\0', 256);

	hkey = 0;
	dwSize = 128;
	RegOpenKeyEx(hk, path, 0, KEY_READ, &hkey);
	if(RegQueryValueEx(hkey, name, 0, 0, szDataBuf, &dwSize) == ERROR_SUCCESS)
	{
		sprintf(ret, "CdKey for %s: %s", GameName, szDataBuf);
	}
	else
	{
		ret = "0";
	}

	return ret;
}
