#include "CMutex.h"
#define WIN32_LEAN_AND_MEAN	

CMutex::CMutex()
{

}
void CMutex::DoConsole()
{
	CHAR szAppName[MAX_PATH];
	string strAppName;
	GetModuleFileName(NULL, szAppName, MAX_PATH);
	strAppName = szAppName;

	strAppName = strAppName.substr(strAppName.rfind('\\')+1, strAppName.length() - 
		strAppName.rfind('\\')-1);
	hMutex = CreateMutex(NULL, FALSE, strAppName.c_str());
	if(GetLastError() == ERROR_ALREADY_EXISTS) ExitProcess(0);
}

CMutex::~CMutex()
{
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
}



