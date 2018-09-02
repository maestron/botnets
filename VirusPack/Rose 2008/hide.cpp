/*
######################
#   process hider    #
# #x0 @ bluehell.org #
######################
*/

#include <windows.h>

HINSTANCE hLibrary;
void *regproc;

void CADInit(void);
void HideApp(void);
void ShowApp(void);
void CADClean(void);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CADInit(); //Load DLL and create a pointer to it
	HideApp(); //Hide the application
	//ShowApp(); //Show the application

	//TODO: Place program or calls here
	
	CADClean(); //Unload DLL
	return 0; //retrun 0 because not in message loop
}

void CADInit(void)
{
	//Load kernel32.dll
	hLibrary = LoadLibrary("kernel32.dll");
	//Get address of function
	regproc = GetProcAddress(hLibrary, "RegisterServiceProcess");
}

void HideApp(void)
{
	//Function to make program invisible to ctrl+alt+del
	__asm
	{
		push 1
		push 0
		call regproc
	}
	return;
}

void ShowApp(void)
{
	//Function to make program revisible to ctrl+alt+del
	__asm
	{
		push 0
		push 0
		call regproc
	}
	return;
}

void CADClean(void)
{
	//Unload Library
	FreeLibrary(hLibrary);
	return;
}