#include "startup.h"

char* KEY_STARTUP = new char[MAX_PATH];

bool WinStartup::AddApp(HINSTANCE hInst, LPCTSTR lpszName, HKEY hRootKey, int w)
{
	if(w == 1)
	{
		KEY_STARTUP = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	}
	if(w == 2)
	{
		KEY_STARTUP = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices";
	}

	char* szPath = (char*)malloc(100+1);
	GetCurrentAppPath(hInst, szPath, sizeof(szPath));

	return AddApp(lpszName, szPath, hRootKey, w);
}


bool WinStartup::AddApp(LPCTSTR lpszName, LPCTSTR lpszPath, HKEY hRootKey, int w)
{
    if(w == 1)
	{
		KEY_STARTUP = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	}
	if(w == 2)
	{
		KEY_STARTUP = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices";
	}
	
	HKEY hKey = 0;
	HRESULT hr = RegOpenKey(hRootKey, KEY_STARTUP, &hKey);

	if (hr == ERROR_SUCCESS)
	{
		hr = RegSetValueEx(hKey, lpszName, 0, REG_SZ, (const BYTE*)lpszPath, strlen(lpszPath));

		RegCloseKey(hKey);
	}

	return (hr == ERROR_SUCCESS);
}

bool WinStartup::DelApp(LPCTSTR lpszName, HKEY hRootKey, int w)
{
	if(w == 1)
	{
		KEY_STARTUP = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	}
	if(w == 2)
	{
		KEY_STARTUP = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunServices";
	}
	
	HKEY hKey = 0;
	HRESULT hr = RegOpenKey(hRootKey, KEY_STARTUP, &hKey);

	if (hr == ERROR_SUCCESS)
	{
		hr = RegDeleteValue(hKey, lpszName);

		RegCloseKey(hKey);
	}

	return (hr == ERROR_SUCCESS);
}

LPCTSTR WinStartup::GetCurrentAppPath(HINSTANCE hInst, LPTSTR lpszPath, int nSize)
{
	GetModuleFileName(hInst, lpszPath, nSize);

	return lpszPath;
}

void WinStartup::GLocation(int argc, char** argv)
{
	for(int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
}