

#ifndef __CMDBASE_H__
#define __CMDBASE_H__

#include "message.h"

class CCommandHandler
{
public:
	virtual bool HandleCommand(CMessage *pMsg)=0;
};

typedef struct command_s
{
    CString			 sName;
    CString			 sDescription;
	CCommandHandler	*pHandler;
	bool			 bFallBack;
} command;

#endif // __CMDBASE_H__
