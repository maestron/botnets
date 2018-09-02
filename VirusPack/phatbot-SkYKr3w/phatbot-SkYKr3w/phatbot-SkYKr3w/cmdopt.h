
#ifndef __CMDOPT_H__
#define __CMDOPT_H__

#include "cstring.h"

typedef struct config_s
{	bool	bDebug;
	int		iDebugLevel;
	bool	bUpdate;
	bool	bService;
	bool	bMeltServer;
	char	szOldServer[MAX_PATH];
} config_t;

#endif // __CMDOPT_H__
