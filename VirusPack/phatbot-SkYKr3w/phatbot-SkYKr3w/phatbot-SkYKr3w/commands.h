

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "cstring.h"
#include "cmdbase.h"
#include "message.h"

using namespace std;

class CCommands : public CCommandHandler
{
public:
					 CCommands();

	void			 Init();

	void			 RegisterCommand(command *pCommand, const char *szName, const char *szDescription, bool bFallBack, CCommandHandler *pHandler);
	command			*FindCommandByName(const char *szName, bool bExact);
	command			*FindFallBack();

	bool			 HandleCommand(CMessage *pMsg);

	command			 m_cmdList;
protected:
	list<command*>	 m_lCommands;
};

#endif // __COMMANDS_H__
