#include "commands.h"
#include "message.h"
#include "irc.h"
#include "main.h"
#ifndef __PORTSCAN__
#define __PORTSCAN__
class CPortScan : public CCommandHandler
{
public:
	void Init();


	bool HandleCommand(CMessage *pMsg);
	command m_cmdPScan;
};
#endif