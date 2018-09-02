
#ifndef __REDIR_TCP_H__
#define __REDIR_TCP_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"

class CRedirectTCP;
class CRedirectTCP_XmitThread;
class CRedirectTCP_RecvThread;

class CRedirectTCP_RecvThread : public CRedirectBase
{
public:
	CRedirectTCP_RecvThread();
	virtual void StartRedirect();

	CRedirectTCP			*m_pRedirTCP;

	CSocket					 m_sClientSocket;
	CSocket					 m_sServerSocket;
};

class CRedirectTCP_XmitThread : public CRedirectBase
{
public:
	CRedirectTCP_XmitThread();
	virtual void StartRedirect();

	CRedirectTCP_RecvThread	*m_pRedirTCP_Recv;
};

class CRedirectTCP : public CRedirectBase
{
public:
	CRedirectTCP();
	virtual void StartRedirect();

	CSocket					 m_sListenSocket;
};

#endif // __REDIR_TCP_H__
