#include "Include.h"
#include "Hell.h"

BOOL mirccmd(char *cmd)
{
	HWND mwnd = FindWindow("mIRC",NULL);
	if (mwnd) {
		HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
		LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
		sprintf(mData, cmd);
		SendMessage(mwnd,WM_USER + 200,1,0);
		SendMessage(mwnd,WM_USER + 201,1,0);
		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
		
		return TRUE;
	} else
		return FALSE;
}