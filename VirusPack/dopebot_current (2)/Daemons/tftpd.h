/*	dopebot - a modular IRC bot for Win32
	Copyright (C) 2004 dope

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef NO_TFTPD
DWORD WINAPI tftpd(LPVOID parameter);
DWORD WINAPI tftpd_handler(LPVOID parameter);
bool tftpd_request(SOCKET bsock, char *szIP);

typedef struct tftp
{
	int iPort;
	char szFileName[32];
	SOCKET bsock;
	struct sockaddr_in sin;
	char szAction[32];
	char szChannel[32];
} tftp;

typedef struct TFTP_PACKET
{
	unsigned short int opcode;
	unsigned short int blockid;
	char data[512];
} TFTP_PACKET;

typedef struct TFTP_RECEIVE
{
	unsigned short int opcode;
	unsigned short int blockid;
} TFTP_RECEIVE;
#endif