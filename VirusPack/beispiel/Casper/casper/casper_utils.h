#ifndef _CASPER_UTILS_H_
#define _CASPER_UTILS_H_

#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>


// Functions
DWORD		GetPIDByName (TCHAR *szProcName);
int inline	StrCmpI(LPSTR lpStr1,LPSTR lpStr2);


#endif // _CASPER_UTILS_H_
