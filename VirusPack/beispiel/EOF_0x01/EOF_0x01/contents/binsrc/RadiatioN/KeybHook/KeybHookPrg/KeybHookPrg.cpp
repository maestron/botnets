// KeybHookPrg.cpp : Definiert den Einsprungpunkt für die Anwendung.
//

#include "stdafx.h"

//Example code for tutorial "Introduction in Windows Message Hooking"

//typedef for hookfunctions in dll
typedef void (*InstallHookProc)(void); 
typedef void (*UninstallHookProc)(void); 

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	//variable definitions
	HMODULE hm;
	char szWinDir[MAX_PATH]="";
	HRSRC hRes;
	HGLOBAL hResGlob;
	DWORD *dwResPointer, dwResSize;
	int iFile=0;

	//use typedef's
	InstallHookProc InstallHook;
	UninstallHookProc UninstallHook;

	//get windows directory and add our dll name
	GetWindowsDirectory(szWinDir, MAX_PATH);
	strcat(szWinDir, "\\KeybHookDll.dll");
		
	//used for development
	//http://www.cpp-tutor.de/mfc/mfc/kap7/tut/tut2.htm
	//http://www.codeproject.com/win32/binaryresources.asp

	//Find resource in exe
	hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_BINARY1), "BINARY");

	//load resource in memory
	hResGlob = LoadResource(NULL, hRes);

	//Get Pointer to resource in memory
	dwResPointer = (DWORD*)LockResource(hResGlob);
	
	//how big is the resource?
	dwResSize = SizeofResource(NULL, hRes);

	//write resource to disk
	iFile = open(szWinDir, _O_BINARY | _O_CREAT | _O_TRUNC | _O_WRONLY, 777);
	if(iFile!=-1)
	{
		write(iFile, dwResPointer, dwResSize);
		close(iFile);
	}

	//load the library to hook
	hm = LoadLibrary(szWinDir); 

	//get function addresses in memory
	InstallHook = (InstallHookProc)GetProcAddress(hm, "?InstallHook@@YGXXZ");
	UninstallHook = (UninstallHookProc)GetProcAddress(hm, "?UninstallHook@@YGXXZ");

	//activate hook now
	InstallHook();
	
	//if you want you can disable the hook call
	//UninstallHook();

	//never ending loop
	//on break and ending the app the hook will be uninstalled
	//cause dll will be unloaded by the system
	while(1)
	{
		Sleep(3000);
	}

	//everything fine, return success
	return 0;
}



