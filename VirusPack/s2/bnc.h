#ifndef __BNC_H__
#define __BNC_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "irc.h"

using namespace std;

typedef struct bnc_s
{
	unsigned short  iPort;
	unsigned int	iServerNum;
} bnc;

typedef struct bnc_server_s
{
	CString			sServer;
	unsigned short  iPort;
	unsigned int	iServerNum;
} bnc_server;

typedef struct bnc_user_s
{
	CString			sUsername;		// Username
	CString			sPassword;		// Password
	CString			sHost;			// Host
	CString			sIdentd;		// Identd
	unsigned int	iServerNum;
} bnc_user;

typedef struct bnc_login_s
{
	CString			sUsername;		// Username
	CString			sIRCUsername;	// Username in IRC
	CString			sHost;			// Host
	CString			sIdentd;		// Identd
	unsigned int	iServerNum;
} bnc_login;

class CBNC : public CCommandHandler
{
public:
	CBNC();
	void Init();

	bool	HandleCommand(CMessage *pMsg);

	int		StartBNC(unsigned long iServerNum, int iPort);

	unsigned long	iServerNum;
	command	m_cmdStart, m_cmdStop, m_cmdStopAll, m_cmdList;
protected:
	int		DeleteLoginById(unsigned long iServerNum, char *szUsername);
	int		DeleteLoginById(unsigned long iServerNum, bool bAll);

	int		DeleteUserById(unsigned long iServerNum, char *szUsername);
	int		DeleteUserById(unsigned long iServerNum, bool bAll);

	int		DeleteServerById(unsigned long iServerNum, char *szUsername);
	int		DeleteServerById(unsigned long iServerNum, bool bAll);
private:
	list<bnc*> lbStart;
	list<bnc_server*> lsStart;
	list<bnc_login*> llStart;
	list<bnc_user*> luStart;
};

#endif // __BNC_H__
