#ifndef __SNAP__
#define __SNAP__


#include "commands.h"
#include "message.h"
#include "cthread.h"

class CSnap : public CCommandHandler {
public:
	void Init();
	bool HandleCommand(CMessage *pMsg);

	command m_cmdServSnap,m_cmdServHttp,m_cmdServStop;
};
#endif