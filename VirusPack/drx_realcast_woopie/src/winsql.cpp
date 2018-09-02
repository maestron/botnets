#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"

#ifndef NO_THCSQL
#ifndef NO_WINS

BOOL winsql(EXINFO exinfo)

{
	
	exinfo.port = 1434;
	BOOL bThcsql = Thcsql(exinfo);
	exinfo.port = 43;
	BOOL bWINS = Thcsql(exinfo);

	return bThcsql || bWINS ? TRUE : FALSE;
}
#endif
#endif


