// KeybHookDll.cpp : Definiert den Einsprungpunkt für die DLL-Anwendung.
//

#include "stdafx.h"
#include "KeybHookDll.h"

//-----------------------------------------------------------------

LRESULT CALLBACK GetMsgProc( int iCode, WPARAM wParam, LPARAM lParam ) 
{ 
    //this is our callback function which will be called from the system when
	//a message arrives to a window

	//declare variables
	PMSG pMsg; 

    //decide whether to give control back to the system or handle the message
	if( iCode < 0 ) 
	{	
		//give control to system or other hooks
		return CallNextHookEx( NULL, iCode, wParam, lParam ); 
	}

    //set pointer to our structure to edit data in it
	pMsg = (PMSG)lParam; 

    //does the message contains data we would like to edit?
	if( pMsg->message == WM_CHAR  && wParam == PM_REMOVE )
	{ 
		//find the pressed key and change the value for it
		switch(pMsg->wParam)
		{
		case 'a':
			pMsg->wParam = '4';
			break;

		case 'A':
			pMsg->wParam = '4';
			break;

		case 't':
			pMsg->wParam = '7';
			break;

		case 'T':
			pMsg->wParam = '7';
			break;

		case 'l':
			pMsg->wParam = '1';
			break;
		
		case 'L':
			pMsg->wParam = '1';
			break;

		case 'o':
			pMsg->wParam = '0';
			break;

		case 'O':
			pMsg->wParam = '0';
			break;

		case 'e':
			pMsg->wParam = '3';
			break;

		case 'E':
			pMsg->wParam = '3';
			break;

		case '@':
			pMsg->wParam = 'A';
			break;

		case ' ':
			pMsg->wParam = '_';
			break;

		case '_':
			pMsg->wParam = '-';
			break;

		case '-':
			pMsg->wParam = '_';
			break;

		case 'c':
			pMsg->wParam = '©';
			break;

		case 'C':
			pMsg->wParam = '©';
			break;

		case 'r':
			pMsg->wParam = '®';
			break;

		case 'R':
			pMsg->wParam = '®';
			break;

		case 's':
			pMsg->wParam = '$';
			break;

		case 'S':
			pMsg->wParam = '$';
			break;

		case '?':
			pMsg->wParam = '!';
			break;

		case '!':
			pMsg->wParam = '?';
			break;

		default:
			break;
		}
    } 

    //return and give control to system or other hooks
	return CallNextHookEx( NULL, iCode, wParam, lParam ); 
} 

//-----------------------------------------------------------------

__declspec (dllexport) void CALLBACK InstallHook (void)
{ 
	//this function installs our hook on all threads
	hHook = SetWindowsHookEx( WH_GETMESSAGE, GetMsgProc, hInstDll, 0 );
	return;
} 

//-----------------------------------------------------------------

__declspec (dllexport) void CALLBACK UninstallHook (void)
{ 
	//this function unhooks all threads
	UnhookWindowsHookEx(hHook);
	return;
} 

//-----------------------------------------------------------------

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	//this is the dll entry point, just do nothing :)
	//you could add auto hook on loading here
	//but beware of installing the hook to often
	//solution:
	//create a mutex to check if hook is already installed

	hInstDll = (HINSTANCE)hModule;  
	
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
		break;
    }
    
	//everything fine, dll loaded successfully
	return TRUE;
}
