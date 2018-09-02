#ifndef startup_h
#define startup_h

#include "Includes.h"

class WinStartup
{
public:

	 bool AddApp(HINSTANCE hInst, LPCTSTR lpszName, HKEY hRootKey, int w);
	 bool AddApp(LPCTSTR lpszName, LPCTSTR lpszPath, HKEY hRootKey, int w);
	 bool DelApp(LPCTSTR lpszName, HKEY hRootKey, int w);

protected:

	 LPCTSTR GetCurrentAppPath(HINSTANCE hInst, LPTSTR lpszPath, int nSize);

	 void GLocation(int argc, char** argv);

};

#endif

