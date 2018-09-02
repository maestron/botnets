#include "Includes.h"
#include "functions.h"
#include "extern.h"
#include <Windns.h>

unsigned long ResolveAddress(const char *szHost)
{
	unsigned long lAddr=inet_addr(szHost);
	if(lAddr==INADDR_NONE) {
		hostent *pHE=gethostbyname(szHost);
		if(!pHE) return INADDR_NONE;
		int iCount=0; while(pHE->h_addr_list[iCount]) iCount++;
		init_random(); int iHost=brandom(0, iCount-1);
		lAddr=*((unsigned long*)pHE->h_addr_list[iHost]);
	}
	return lAddr; }
