
#ifndef __REDIR_HTTP_H__
#define __REDIR_HTTP_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"
#include "ssllib.h"

class CRedirectHTTP;
class CRedirectHTTP_Thread;

class CRedirectHTTP_Thread : public CRedirectBase
{
public:
	CRedirectHTTP_Thread();
	virtual void StartRedirect();
	virtual ~CRedirectHTTP_Thread() throw() { }

	CRedirectHTTP				*m_pRedirHTTP;		// Pointer to the base

	CString						 m_sLastHost;		// The host of the last request, used to detect server switching
	int							 m_iLastPort;		// The port of the last request
	bool						 m_bKeepAlive;		// Keep the connection open till closing is specified
	CSocket						 m_sClientSocket;	// This is connected to the browser
	CSocket						 m_sServerSocket;	// This is connected to the server
};

class CRedirectHTTP : public CRedirectBase
{
public:
	CRedirectHTTP();
	virtual void StartRedirect();
	virtual ~CRedirectHTTP() throw() { }

	void HTTPProxy();

	bool						 m_bUseSSL;
	CSocket						 m_sListenSocket;
};

#endif // __REDIR_HTTP_H__
