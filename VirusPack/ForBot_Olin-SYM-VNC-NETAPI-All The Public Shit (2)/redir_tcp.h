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

#ifndef __REDIR_TCP_H__
#define __REDIR_TCP_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"

class CRedirectTCP;
class CRedirectTCP_XmitThread;
class CRedirectTCP_RecvThread;

class CRedirectTCP_RecvThread : public CRedirectBase
{
public:
	CRedirectTCP_RecvThread();
	virtual void StartRedirect();

	CRedirectTCP			*m_pRedirTCP;

	int						 m_sClientSocket;
	int						 m_sServerSocket;
};

class CRedirectTCP_XmitThread : public CRedirectBase
{
public:
	CRedirectTCP_XmitThread();
	virtual void StartRedirect();

	CRedirectTCP_RecvThread	*m_pRedirTCP_Recv;
};

class CRedirectTCP : public CRedirectBase
{
public:
	CRedirectTCP();
	virtual void StartRedirect();

	int						 m_sListenSocket;
};

#endif // __REDIR_TCP_H__
