#include "commands.h"
#include "message.h"
#include "irc.h"
#include "main.h"

#ifndef __DCC__
#define __DCC__

class CDccCommand : public CCommandHandler
{

typedef struct DCC 
{
	SOCKET sock;
	SOCKET csock;
	CString filename;
	int threadnum;

} DCC;

public:
	void Init();

	bool HandleCommand(CMessage *pMsg);
	command m_cmdDccSend;
};

#endif