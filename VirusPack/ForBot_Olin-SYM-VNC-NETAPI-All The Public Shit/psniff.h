/*
#ifndef __SNIFFER_H__
#define __SNIFFER_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"


class CSnifferPick : public CCommandHandler {
public:
	void Init();

	bool HandleCommand(CMessage *pMsg);

	command	m_cmdSniffOn, m_cmdSniffOff;
};

class CSniffer : public CThread {
public:
	CSniffer();
	virtual	~CSniffer();
	void *Run();
};

#endif // __SNIFFER_H__
*/

