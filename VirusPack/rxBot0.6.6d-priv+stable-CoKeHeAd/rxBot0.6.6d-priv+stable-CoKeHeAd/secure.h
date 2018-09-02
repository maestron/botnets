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

typedef struct SECURE 
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	int threadnum;
	BOOL secure;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} SECURE;

typedef struct NetShares
{
	char *ShareName;
	char *SharePath;
		
} NetShares;

DWORD WINAPI SecureThread(LPVOID param);
BOOL SecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
BOOL UnSecureSystem(SOCKET sock, char *chan, BOOL notice, BOOL silent);
#ifndef NO_SECSYSTEM
DWORD WINAPI AutoSecureThread(LPVOID param);
#endif