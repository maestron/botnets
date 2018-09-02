#ifndef __BNC_H__
#define __BNC_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"
#include "sockets.h"

using namespace std;

typedef struct bnc_s {
	CMessage		*pMsg;
	bool			 bConnected;
	int				 iBNCPort;
} bnc;

typedef struct bnc_server_s {
	CSocket			 ServerSock;
	CString			 sUsername;
	CString			 sNetwork;
	CString			 sServer;
	CString			 sPassword;
	bool			 bClientConnected;
	int				 iPort;
	int				 iBNCPort;
} bnc_server;


class CBNC : public CCommandHandler {
public:
	CBNC();

	bool Init();

	bool	HandleCommand(CMessage *pMsg);

	void	StartBNC(int iBNCPort);

	CommandInfo	m_cmdStartBNC, m_cmdStopBNC, m_cmdStopAll, m_cmdListBNC;

	bnc		*FindBNCByPort(int iBNCPort);
private:
	list<bnc*> lbStart;
};

class CBNCClient : public CThread {
public:
	CBNCClient();
	virtual ~CBNCClient() { }
	virtual void *Run();

	CString	m_sUsername;
	CString	m_sUser;
	CString	m_sNickname;
	CString	m_sAwayNick;

	CSocket	m_sClientSock;

	int		m_iPort;

	CBNC	*m_pBNC;
protected:
	void HandleClient();

	void ClearServers();

	bool SendClient(const char *szMsg, ...);
	bool SendServer(bnc_server *pServer, const char *szMsg, ...);

	bnc_server	*FindServer(int iPos, bool bConnected);
	bnc_server  *FindServerByNetwork(CString sNetwork);
private:
	list<bnc_server*> lbsStart;
};

#endif // __BNC_H__
