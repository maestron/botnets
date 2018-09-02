#include "includes.h"
#include "functions.h"
#include "extern.h"

// globals
char log1[LOGSIZE][LOGLINE];

BOOL searchlog(char *filter)
{
	for (int i = 0; i < LOGSIZE; i++) 
		if (log1[i][0] != '\0') {
			if (lstrstr(log1[i], filter))
				return TRUE;
		}
	
	return FALSE;
}
