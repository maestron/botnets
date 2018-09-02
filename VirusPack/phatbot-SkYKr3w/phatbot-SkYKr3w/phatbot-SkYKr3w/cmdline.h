

#ifndef __CMDLINE_H__
#define __CMDLINE_H__

#include "cmdopt.h"

class CCmdLine
{
public:
	CCmdLine();
	virtual ~CCmdLine();
	void Parse(const char *szCmdLine);
	config_t m_cConfig;
private:
	char *m_szCmdLine;
};

#endif // __CMDLINE_H__
