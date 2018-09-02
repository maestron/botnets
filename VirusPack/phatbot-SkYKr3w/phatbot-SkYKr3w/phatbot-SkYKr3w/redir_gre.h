
#ifndef __REDIR_GRE_H__
#define __REDIR_GRE_H__

#include "cstring.h"
#include "redirect.h"
#include "utility.h"

class CRedirectGRE : public CRedirectBase
{
public:
	CRedirectGRE();
	virtual void StartRedirect();
};

#endif // __REDIR_GRE_H__
