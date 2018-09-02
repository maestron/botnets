
#ifndef __REDIR_SOCKS_H__
#define __REDIR_SOCKS_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"

class CRedirectSOCKS;
class CRedirectSOCKS_Thread;

class CRedirectSOCKS_Thread : public CRedirectBase
{
public:
	CRedirectSOCKS_Thread();
	virtual void StartRedirect();

	CRedirectSOCKS				*m_pRedirSOCKS;

	CSocket						 m_sClientSocket;
};

class CRedirectSOCKS : public CRedirectBase
{
public:
	CRedirectSOCKS();
	virtual void StartRedirect();

	CSocket						 m_sListenSocket;
};

#endif // __REDIR_SOCKS_H__
