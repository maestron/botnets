/*
#############################
# Simple Application Hider  #
# Hides From Ctrl-Alt-Del   #
# Coded: #x0 @ bluehell.org #
#############################
*/

#include <windows.h>

#define RSP_SIMPLE_SERVICE 1
#define RSP_UNREGISTER_SERVICE 0

typedef DWORD (*REGSERVPROC)(DWORD, DWORD);
HINSTANCE hLibrary;

void Initalize(void)
	{
	DWORD process;
	REGSERVPROC regproc;
	//Load kernel32.dll
	hLibrary = LoadLibrary("kernel32.dll");
	//Get current process identifier
	process = GetCurrentProcessId();
	//Get address of function
	regproc = (REGSERVPROC) GetProcAddress(hLibrary, "RegisterServiceProcess");
	}

void HideApp(void)
	{
	//Function to make program invisible to ctrl+alt+del
	(regproc) (process, RSP_SIMPLE_SERVICE);
    return;
	}

void ShowApp(void)
    {
	//Function to make program revisible to ctrl+alt+del
	(regproc) (process, RSP_UNREGISTER_SERVICE);
	return;
	}

void Cleanup(void)
    {
	//Unload Library
	FreeLibrary(hLibrary);
	return;
	}