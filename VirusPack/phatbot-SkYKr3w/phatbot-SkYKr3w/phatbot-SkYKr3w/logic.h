
#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "commands.h"
#include "message.h"
#include "irc.h"

class CLogic : public CCommandHandler
{
public:
	void Init();

	bool HandleCommand(CMessage *pMsg);

	command	m_cmdIfUptime;
};

#endif // __LOGIC_H__
