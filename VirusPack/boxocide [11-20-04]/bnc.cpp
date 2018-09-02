#include "main.h"
#include "mainctrl.h"
#ifdef __COMPILE_BNC__
#include "bnc.h"
#include "mac.h"

CBNC::CBNC() { lbStart.clear(); }
CBNCClient::CBNCClient() { m_szType="CBNCClient"; lbsStart.clear(); }

bool CBNC::Init() {
	return true;
}

void CBNC::StartBNC(int iBNCPort)
{
	CSocket bncsock, ClientSock, Client;
	sockaddr_in cAddr;
	bnc *pBNC=FindBNCByPort(iBNCPort);
	CString sReply;

	if(!bncsock.Bind(iBNCPort)) {
		pBNC->pMsg->pReply->DoReplyF(pBNC->pMsg, "BNC: Error binding to port %d.", iBNCPort);
		return; }

	pBNC->bConnected=true; bncsock.SetAsync(true);
	pBNC->pMsg->pReply->DoReplyF(pBNC->pMsg, "BNC: Started on port %d.", iBNCPort);
	while(pBNC->bConnected)
	{
		if(bncsock.Accept(ClientSock, &cAddr))
		{
			CBNCClient *pTemp=new CBNCClient; pTemp->m_pBNC=this;
			pTemp->m_iPort=iBNCPort; pTemp->m_sClientSock=ClientSock;
			pTemp->Start(true);
		}
		else
			Sleep(1200);
	}
	lbStart.remove(FindBNCByPort(iBNCPort));

	delete[] pBNC;
}

bnc *CBNC::FindBNCByPort(int iBNCPort)
{	list<bnc*>::iterator ib; for(ib=lbStart.begin(); ib!=lbStart.end(); ++ib)
		if((*ib)->iBNCPort == iBNCPort)
			return (*ib);
	return NULL; }

bool CBNC::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare(m_cmdStartBNC.szName))
	{
		int iPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		if(iPort<1 || iPort>65535) return false;

		bnc *pBNC=new bnc; pBNC->iBNCPort=iPort;
		pBNC->pMsg=new CMessage; *pBNC->pMsg=*pMsg;
		lbStart.push_back(pBNC);

		StartBNC(iPort);
	}

	else if(!pMsg->sCmd.Compare(m_cmdStopBNC.szName))
	{
		int iPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		if(iPort<1 || iPort>65535) return false;

		list<bnc*>::iterator i; for(i=lbStart.begin(); i!=lbStart.end(); ++i)
		{	if((*i)->iBNCPort==atoi(pMsg->sChatString.Token(1, " ").CStr())) {
				(*i)->bConnected=false;

				pMsg->pReply->DoReplyF(pMsg, "BNC: Stopped port %s.", pMsg->sChatString.Token(1, " ").CStr());

				return true; } }
	}

	else if(!pMsg->sCmd.Compare(m_cmdStopAll.szName))
	{
		list<bnc*>::iterator i; for(i=lbStart.begin(); i!=lbStart.end(); ++i)
		{ (*i)->bConnected=false; }

		pMsg->pReply->DoReply(pMsg, "BNC: Stopped all ports.");
	}

	else if(!pMsg->sCmd.Compare(m_cmdListBNC.szName))
	{
		pMsg->pReply->DoReply(pMsg, "-[ bnc list ]-");
		list<bnc*>::iterator ic; int iCount=0;
		for(ic=lbStart.begin(); ic!=lbStart.end(); ++ic) {
			iCount++; pMsg->pReply->DoReplyF(pMsg, "%d. / \"Port %d.\"", iCount, (*ic)->iBNCPort); }
	}

	return false;
}


void *CBNCClient::Run()
{	HandleClient();
	return NULL; }

void CBNCClient::HandleClient()
{
	bnc	*pBNC=m_pBNC->FindBNCByPort(m_iPort);
	char szLine[8192];
	bool bRecvd=false;
	unsigned int iFailedCount=0;
	unsigned long lStartTime=GetTickCount();

	memset(szLine, 0, sizeof(szLine));
	m_sClientSock.SetAsync(true);

	SendClient(":Shell NOTICE :You are accessing a private shell, authorize or disconnect at once.\r\n");
	while(pBNC->bConnected) {
		if((GetTickCount()-lStartTime)>=25000 || iFailedCount > 3)
		{	m_sClientSock.Disconnect(); return; }

		bRecvd=m_sClientSock.RecvLineIRC(szLine, sizeof(szLine));
		if(bRecvd)
		{
			CString sLine(szLine);
			if(!sLine.Token(0, " ").CompareNoCase("nick"))
			{
				if(!sLine.Token(1, " ").Compare("")) continue;
				m_sNickname=sLine.Token(1, " ");
			}
			else if(!sLine.Token(0, " ").CompareNoCase("user"))
			{
				if(!sLine.Token(1, " ").Compare("")) continue;
				m_sUser=sLine;
			}
			else if(!sLine.Token(0, " ").CompareNoCase("quit") || !sLine.CompareNoCase("quit"))
			{
				m_sClientSock.Disconnect(); return;
			}
			else if(!sLine.Token(0, " ").CompareNoCase("login"))
			{	user *pUser=g_pMainCtrl->m_pMac->FindUser(sLine.Token(1, " "));
				if(!pUser || !g_pMainCtrl->m_pMac->CheckPassword(sLine.Token(2, " "), pUser))
				{	iFailedCount++; continue; }
				m_sUsername=sLine.Token(1, " ");
				break;
			}
		}
		else Sleep(1200);
	}
	Sleep(350);
	SendClient(":PhatBNC NOTICE :Welcome to PhatBNC!\r\n:PhatBNC Notice :Type /bnchelp for help.\r\n");
	while(pBNC->bConnected)
	{
		// Servers
		list<bnc_server*>::iterator is; for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
		{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername)) {
				bRecvd=(*is)->ServerSock.RecvLineIRC(szLine, sizeof(szLine));
				if(bRecvd) {
					CString sLine(szLine);
					if(!sLine.Token(0, " ").Compare("PING"))
						SendServer((*is), "PONG %s\r\n", sLine.Token(1, " ").CStr());
					else if(sLine.Compare("") && (*is)->bClientConnected) {
						CString sChatString(""), sDest, sSrc;

						CString sIdentd(sLine.Token(1, "!").Token(0, "@"));
						CString sHost(sLine.Token(1, "@").Token(0, " "));
						char *szText=strstr(sLine.Str(), " :");
						if(szText) sChatString.Assign(szText+2);
						if(sLine.Token(0, " ").Find("!")) sSrc.Assign(sLine.Token(0, ":").Token(0, " ").Token(0, "!"));
						else sSrc.Assign(sLine.Token(0, ":").Token(0, " "));
						if(sSrc.Compare(m_sNickname)) sSrc.Format("%s~%s", (*is)->sNetwork.CStr(), sSrc.CStr());
						if(sLine.Token(2, " ")[0]==':') sDest.Assign(sLine.Token(2, " ").Mid(1));
						else sDest.Assign(sLine.Token(2, " "));
						if(sDest.Compare(m_sNickname)) sDest.Format("#%s~%s", (*is)->sNetwork.CStr(), sDest.CStr());

						if(!sLine.Token(1, " ").Compare("324"))			// CHANNELMODEIS
							SendClient(":%s 324 %s #%s~%s %s %s\r\n", sSrc.CStr(), m_sNickname.CStr(), (*is)->sNetwork.CStr(), sLine.Token(3, " ").CStr(), sLine.Token(4, " ").CStr(), sLine.Token(5, " ").CStr());
						else if(!sLine.Token(1, " ").Compare("329"))	// CREATIONTIME
							SendClient(":%s 329 %s #%s~%s %s",sSrc.CStr(), m_sNickname.CStr(), (*is)->sNetwork.CStr(), sLine.Token(3, " ").CStr(), sLine.Token(4, " ").CStr());
						else if(!sLine.Token(1, " ").Compare("353")) {	// NAMES
							CString sNames("");
							for(int i=0; sChatString.Token(i, " ").Compare(""); i++) {
								CString sTemp; sTemp.Format(" %s~%s", (*is)->sNetwork.CStr(), sChatString.Token(i, " ").CStr());
								sNames.Append(sTemp); }
							if(sNames.Compare("")) sNames.Assign(sNames.Mid(1));
							SendClient(":%s 353 %s = #%s~%s :%s\r\n", sSrc.CStr(), m_sNickname.CStr(), (*is)->sNetwork.CStr(), sLine.Token(4, " ").CStr(), sNames.CStr()); }
						else if(!sLine.Token(1, " ").Compare("366"))	// ENDOFNAMES
							SendClient(":%s 366 %s #%s~%s :%s\r\n", sSrc.CStr(), m_sNickname.CStr(), (*is)->sNetwork.CStr(), sLine.Token(3, " ").CStr(), sChatString.CStr());
						else if(!sLine.Token(1, " ").Compare("JOIN") || !sLine.Token(1, " ").Compare("PART"))
							SendClient(":%s!%s@%s %s %s\r\n", sSrc.CStr(), sIdentd.CStr(), sHost.CStr(), sLine.Token(1, " ").CStr(), sDest.CStr());
						else if(!sLine.Token(1, " ").Compare("PRIVMSG") || !sLine.Token(1, " ").Compare("NOTICE"))
							SendClient(":%s!%s@%s %s %s :%s\r\n", sSrc.CStr(), sIdentd.CStr(), sHost.CStr(), sLine.Token(1, " ").CStr(), sDest.CStr(), sChatString.CStr());
						else if(!sLine.Token(1, " ").Compare("MODE"))
							SendClient(":%s!%s@%s MODE %s %s %s\r\n", sSrc.CStr(), sIdentd.CStr(), sHost.CStr(), sDest.CStr(), sLine.Token(3, " ").CStr(), sLine.Mid(sLine.Token(0, " ").GetLength()+sLine.Token(1, " ").GetLength()+sLine.Token(2, " ").GetLength()+sLine.Token(3, " ").GetLength()+4).CStr());
						else
							SendClient("%s\r\n", sLine.CStr());
					}
				}
			}
		}
		// Client
		bRecvd=m_sClientSock.RecvLineIRC(szLine, sizeof(szLine));
		if(bRecvd)
		{
			CString sLine(szLine);
			if(!sLine.CompareNoCase("bnchelp"))
			{
				SendClient("PhatBNC NOTICE : - bnchelp      - lists help for PhatBNC;                   /bnchelp\r\n");
				SendClient("PhatBNC NOTICE : - addserver    - adds a server to list;                    /addserver <network> <server>:<port> <password>\r\n");
				SendClient("PhatBNC NOTICE : - bconnect     - connects to a server;                     /bconnect [#]\r\n");
				SendClient("PhatBNC NOTICE : - bdisconnect  - disconnects from all/specified server;    /bdisconnect [#]\r\n");
				SendClient("PhatBNC NOTICE : - bquit        - disconnects bnc from all/selected server; /bquit [#]\r\n");
				SendClient("PhatBNC NOTICE : - delserver    - deletes a server from list;               /delserver [#]\r\n");
				SendClient("PhatBNC NOTICE : - listconnects - lists all connected servers;              /listconnects\r\n");
				SendClient("PhatBNC NOTICE : - listservers  - lists all servers;                        /listservers\r\n");
				SendClient("PhatBNC NOTICE : - setawaynick  - sets away nick;                           /setawaynick <nick>\r\n");
			}
			else if(!sLine.Token(0, " ").CompareNoCase("addserver"))
			{
				if(!sLine.Token(1, " ").Compare("") || !sLine.Token(2, " ").Compare("")) continue;
				int iPort=atoi(sLine.Token(2, " ").Mid(sLine.Token(2, " ").Token(0, ":").GetLength()+1).CStr());
				if(iPort<1 || iPort>65535) continue;

				if(FindServerByNetwork(sLine.Token(1, " "))!=NULL) {
					SendClient(":PhatBNC NOTICE :Network %s is already added.\r\n", sLine.Token(1, " ").CStr()); continue; }

				bnc_server *pBNCServer=new bnc_server; pBNCServer->bClientConnected=false;
				pBNCServer->iPort=iPort; pBNCServer->sServer=sLine.Token(2, " ").Token(0, ":");
				pBNCServer->sNetwork=sLine.Token(1, " "); pBNCServer->sUsername=m_sUsername;
				pBNCServer->sPassword=sLine.Token(3, " "); pBNCServer->iBNCPort=m_iPort;
				lbsStart.push_back(pBNCServer);

				SendClient(":PhatBNC NOTICE :Added server %s to list.\r\n", sLine.Token(2, " ").Token(0, ":").CStr());
			}
			else if(!sLine.Token(0, " ").CompareNoCase("bconnect"))
			{
				if(!sLine.Compare("")) continue;
				bnc_server *pServer=FindServer(atoi(sLine.Token(1, " ").CStr()), false);
				if(pServer!=NULL) {
					if(pServer->ServerSock.IsConnected() && pServer->bClientConnected) SendClient(":PhatBNC NOTICE :Alread connected to %s~%s!\r\n", pServer->sNetwork.CStr(), pServer->sServer.CStr());
					else if(pServer->ServerSock.IsConnected()) {
						pServer->bClientConnected=true;
						SendClient("Connected back to %s~%s\r\n", pServer->sNetwork.CStr(), pServer->sServer.CStr());
						SendServer(pServer, "NICK %s\r\n", m_sNickname.CStr()); }
					else if(pServer->ServerSock.Connect(pServer->sServer.CStr(), pServer->iPort, false, false)) {
						pServer->ServerSock.SetAsync(true);
						if(pServer->sPassword.Compare("")) SendServer(pServer, "PASS %s\r\n", pServer->sPassword.CStr());
						SendServer(pServer, "NICK %s\r\n%s\r\n", m_sNickname.CStr(), m_sUser.CStr());
						SendClient(":PhatBNC NOTICE :Connected to server %s~%s.\r\n", pServer->sNetwork.CStr(), pServer->sServer.CStr());
						pServer->bClientConnected=true; }
					else SendClient(":PhatBNC NOTICE :Error connecting to %s~%s!\r\n", pServer->sNetwork.CStr(), pServer->sServer.CStr()); }
				else
					SendClient(":PhatBNC NOTICE :Server %s not found.\r\n", sLine.Token(1, " ").CStr());
			}
			else if(!sLine.Token(0, " ").CompareNoCase("bdisconnect") || !sLine.CompareNoCase("bdisconnect"))
			{
				if(!sLine.Token(1, " ").Compare("")) {
					list<bnc_server*>::iterator is;
					for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
					{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
						{	(*is)->bClientConnected=false; 
							SendServer((*is), "NICK %s\r\n", m_sAwayNick.CStr()); } } }
				else {
					bnc_server *pServer=FindServer(atoi(sLine.Token(1, " ").CStr()), false);
					if(pServer!=NULL)
					{	SendServer((*is), "NICK %s\r\n", m_sAwayNick.CStr());
						pServer->bClientConnected=false; }
					else SendClient(":PhatBNC NOTICE :Server %s not found.\r\n", sLine.Token(1, " ").CStr()); }
			}
			else if(!sLine.Token(0, " ").CompareNoCase("bquit") || !sLine.CompareNoCase("bquit"))
			{
				if(!sLine.Token(1, " ").Compare("")) {
					list<bnc_server*>::iterator is;
					for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
					{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
						{	SendServer((*is), "QUIT :\r\n"); (*is)->ServerSock.Disconnect(); } } }
				else {
					bnc_server *pServer=FindServer(atoi(sLine.Token(1, " ").CStr()), false);
					if(pServer!=NULL) { SendServer((*is), "QUIT :\r\n"); pServer->ServerSock.Disconnect(); }
					else SendClient(":PhatBNC NOTICE :Server %s not found.\r\n", sLine.Token(1, " ").CStr()); }
			}
			else if(!sLine.Token(0, " ").CompareNoCase("delserver"))
			{
				if(!sLine.Token(1, " ").Compare("")) continue;
				bnc_server *pServer=FindServer(atoi(sLine.Token(1, " ").CStr()), false);
				if(pServer!=NULL) {
					pServer->ServerSock.Disconnect(); lbsStart.remove(pServer);
					SendClient(":PhatBNC NOTICE :Server %s deleted.\r\n", pServer->sServer.CStr()); }
			}
			else if(!sLine.Token(0, " ").CompareNoCase("listconnects"))
			{
				SendClient(":PhatBNC NOTICE :-[ connects list ]-\r\n");
				list<bnc_server*>::iterator is; int iCount=0;
				for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
				{	if(!(*is)->ServerSock.IsConnected()) continue;
					if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
					{	iCount++; SendClient(":PhatBNC NOTICE :#%d. / \"%s~%s:%d\"\r\n", \
							iCount, (*is)->sNetwork.CStr(), (*is)->sServer.CStr(), (*is)->iPort); } }
			}
			else if(!sLine.Token(0, " ").CompareNoCase("listservers"))
			{
				SendClient(":PhatBNC NOTICE :-[ server list ]-\r\n");
				list<bnc_server*>::iterator is; int iCount=0;
				for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
				{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
					{	iCount++; SendClient(":PhatBNC NOTICE :#%d. / \"%s~%s:%d\"\r\n", \
							iCount, (*is)->sNetwork.CStr(), (*is)->sServer.CStr(), (*is)->iPort); } }
			}
			else if(!sLine.Token(0, " ").CompareNoCase("setawaynick"))
			{
				if(!sLine.Token(1, " ").Compare("")) continue;
				m_sAwayNick=sLine.Token(1, " ");
				SendClient(":PhatBNC NOTICE :AwayNick changed to %s.\r\n", sLine.Token(1, " ").CStr());
			}
			else if(!sLine.Token(0, " ").CompareNoCase("quit") || !sLine.CompareNoCase("quit"))
			{
				bool bDisconnect=true;
				list<bnc_server*>::iterator is;
				for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
				{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
					{	if((*is)->ServerSock.IsConnected()) bDisconnect=false; (*is)->bClientConnected=false;
						SendServer((*is), "NICK %s\r\n", m_sAwayNick.CStr()); } }
				if(bDisconnect) break;
			}
			else if(sLine.Token(0, " ").Compare("")) {
				bnc_server *pServer=NULL;
				CString sSend;
				sSend.Format("%s\r\n", szLine);
				if(!sLine.Token(0, " ").CompareNoCase("quote") || !sLine.Token(0, " ").CompareNoCase("raw"))
					sLine.Assign(sLine.Mid(sLine.Token(0, " ").GetLength()+1));
				if(!sLine.Token(0, " ").CompareNoCase("nick")) m_sNickname=sLine.Token(1, " ").Mid(1);
				else if(!sLine.Token(0, " ").CompareNoCase("user")) m_sUser=sLine.Token(1, " ").Mid(1);
				if(!sLine.Token(1, " ").Find("~")) {
					// Check if more than one server is connected
					pServer=FindServer(2, false);
					if(pServer!=NULL) continue;
					pServer=FindServer(1, false);
					if(pServer==NULL) { SendClient(":PhatBNC NOTICE :Not connected to a server.\r\n"); continue; }
				} else {
					CString sNetwork(sLine.Token(1, " ").Token(0, "~"));
					if(!sNetwork.Compare("")) continue;
					if(sNetwork[0]=='#') sNetwork.Assign(sNetwork.Mid(1));
					pServer=FindServerByNetwork(sNetwork);
					if(pServer==NULL) { SendClient(":PhatBNC NOTICE :Network %s not found.\r\n", sNetwork.CStr()); continue; }
					sSend.Format("%s %s\r\n", sLine.Token(0, " ").CStr(), sLine.Mid(sLine.Find(' ')+sLine.Token(1, " ").Token(0, "~").GetLength()+1).CStr());
				}
				SendServer(pServer, sSend.CStr());
			}
		}
		Sleep(200);
	}
	ClearServers();
}

bnc_server *CBNCClient::FindServer(int iPos, bool bConnected)
{	int iCount=0;
	list<bnc_server*>::iterator is; for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
	{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
			if(bConnected) if(!(*is)->ServerSock.IsConnected()) continue;
			iCount++; if(iCount==iPos) return (*is); }
	return NULL; }

bnc_server *CBNCClient::FindServerByNetwork(CString sNetwork)
{	if(!sNetwork.CStr()) return NULL;
	list<bnc_server*>::iterator is; for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
	{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
			if(!(*is)->sNetwork.Compare(sNetwork)) return (*is); }
	return NULL; }

void CBNCClient::ClearServers()
{	list<bnc_server*>::iterator is; for(is=lbsStart.begin(); is!=lbsStart.end(); ++is)
	{	if((*is)->iBNCPort==m_iPort) if(!(*is)->sUsername.Compare(m_sUsername))
			(*is)->ServerSock.Disconnect(); lbsStart.remove((*is)); }
}

bool CBNCClient::SendClient(const char *szMsg, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szMsg);
	vsnprintf(formatbuf, sizeof(formatbuf), szMsg, va_alist); va_end(va_alist);
	if(!m_sClientSock.Write(formatbuf, strlen(formatbuf)))
	{	m_sClientSock.Disconnect(); return false; }
	else return true;
}

bool CBNCClient::SendServer(bnc_server *pServer, const char *szMsg, ...)
{	va_list va_alist; char formatbuf[8192]; va_start(va_alist, szMsg);
	vsnprintf(formatbuf, sizeof(formatbuf), szMsg, va_alist); va_end(va_alist);
	if(!pServer->ServerSock.Write(formatbuf, strlen(formatbuf)))
	{	pServer->ServerSock.Disconnect(); return false; }
	else return true;
}

REGOBJ(CBNC, g_pBNC, false, 0);
REGCMD(m_cmdStartBNC,		"bnc.start",		false, g_pBNC);
REGCMD(m_cmdStopBNC,		"bnc.stop",			false, g_pBNC);
REGCMD(m_cmdStopAll,		"bnc.stopall",		false, g_pBNC);
REGCMD(m_cmdListBNC,		"bnc.listall",		false, g_pBNC);

#endif // __COMPILE_BNC__
