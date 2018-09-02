#ifndef __IRCGATE_H__
#define __IRCGATE_H__

#include "cstring.h"
#include "p2p.h"

class CIRCGate : public CThread, public CP2PTarget
{
public:
	CIRCGate();
	virtual ~CIRCGate();
	virtual void *Run();
	
	bool RecvLine(int sSocket, char *szBuffer, int iBufSize);
	void IRCLoop();
	
	void Recv(char *szData, int iDataLen, message *pMsg);

	bool m_bRunning;
	CString m_sClientIp;
	CString m_sClientNick;
protected:
	int m_sListenSock;
	int m_sServerSock;
};

#endif // __IRCGATE_H__
