

#ifndef NO_SYSINFO
#include "bt1.h"

//Count CPU Cycles
static inline unsigned __int64 cyclecount()
{
	unsigned int i, j;
	__asm
	{
			rdtsc
			mov i, edx;
			mov j, eax;
	}
		return ((unsigned __int64)i << 32) + (unsigned __int64)j;
}

//Get ComputerName
void get_computername(char *szBuffer)
{
	char szCompName[MEDBUF];
	DWORD dwSize = MEDBUF;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting computer name, getcomputername()...\n");
#endif

	if (!GetComputerName(szCompName, &dwSize)) sprintf(szCompName, "???");
		sprintf(szBuffer, "computername: %s", szCompName);
		return;
}


//Get CPU Speed
void get_cpu(char *szBuffer)
{
	const unsigned __int64 ui64StartCycle = cyclecount();
	unsigned __int64 speed;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting cpu speed, getcpu()...\n");
#endif

		Sleep(1000);
		speed = ((cyclecount() - ui64StartCycle) / 1000000);
		sprintf(szBuffer, "cpu: %dMHZ", speed);
		return;
}

//Get MemStats
void get_mem(char *szBuffer)
{
	MEMORYSTATUS memstat;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting  memoy status, getmem()...\n");
#endif

		GlobalMemoryStatus(&memstat); 
		sprintf(szBuffer, "ram: %dMB total, %dMB free", memstat.dwTotalPhys / 1048576, memstat.dwAvailPhys / 1048576);
		return;
}

//Get OS
void get_os(char *szBuffer)
{
	OSVERSIONINFO vInfo;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting os version, getos()...\n");
#endif

		vInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&vInfo);
	if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 0) 
	{
		if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) sprintf(szBuffer, "Windows 95");
		if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) sprintf(szBuffer, "Windows NT");
	}
	else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 10) sprintf(szBuffer, "os: Windows 98 %s (%d.%d, Build: %d)", vInfo.szCSDVersion, vInfo.dwMajorVersion, vInfo.dwMinorVersion, vInfo.dwBuildNumber);
	else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 90) sprintf(szBuffer, "os: Windows ME %s (%d.%d, Build: %d)", vInfo.szCSDVersion, vInfo.dwMajorVersion, vInfo.dwMinorVersion, vInfo.dwBuildNumber);
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 0) sprintf(szBuffer, "os: Windows 2000 %s (%d.%d, Build: %d)", vInfo.szCSDVersion, vInfo.dwMajorVersion, vInfo.dwMinorVersion, vInfo.dwBuildNumber);
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 1) sprintf(szBuffer, "os: Windows XP %s (%d.%d, Build: %d)", vInfo.szCSDVersion, vInfo.dwMajorVersion, vInfo.dwMinorVersion, vInfo.dwBuildNumber);
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 2) sprintf(szBuffer, "os: Windows 2003 %s (%d.%d, Build: %d)", vInfo.szCSDVersion, vInfo.dwMajorVersion, vInfo.dwMinorVersion, vInfo.dwBuildNumber);
	else sprintf(szBuffer, "???");
		return;
}

//Get System Info
void get_sysinfo(char *szBuffer)
{
	char szInfoBuff[MEDBUF];

#ifndef NO_DEBUG
		printf("[DEBUG] Getting system info, getsysinfo()...\n");
#endif

//Get CPU Speed
		get_cpu(szInfoBuff);
		strcat(szBuffer, szInfoBuff);
		strcat(szBuffer, ". ");
//Get MemStats
		get_mem(szInfoBuff);
		strcat(szBuffer, szInfoBuff);
		strcat(szBuffer, ". ");
//Get OS
		get_os(szInfoBuff);
		strcat(szBuffer, szInfoBuff);
		strcat(szBuffer, ". ");
//Get Uptime
		get_uptime(szInfoBuff);
		strcat(szBuffer, szInfoBuff);
		strcat(szBuffer, ". ");
//Get UserName
		get_username(szInfoBuff);
		strcat(szBuffer, szInfoBuff);
		strcat(szBuffer, ". ");
//Get ComputerName
		get_computername(szInfoBuff);
		strcat(szBuffer, szInfoBuff);
		return;
}

//Get Uptime
void get_uptime(char *szBuffer)
{
	int i;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting uptime, getuptime()...\n");
#endif

		i = GetTickCount() / 1000;
		sprintf(szBuffer, "uptime: %dd %dh %dm", i / 86400, (i % 86400) / 3600, ((i % 86400) % 3600) / 60);
		return;
}

//Get UserName
void get_username(char *szBuffer)
{
	char szUserName[MEDBUF];
	DWORD dwSize = MEDBUF;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting user name, getusername()...\n");
#endif

	if (!GetUserName(szUserName, &dwSize)) sprintf(szUserName, "???");
		sprintf(szBuffer, "username: %s", szUserName);
		return;
}
	
//Is OS 9x
bool is_os9x()
{
	OSVERSIONINFO vInfo;

#ifndef NO_DEBUG
		printf("[DEBUG] Checking if os is 9x, isos9x()...\n");
#endif

		vInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&vInfo);
	if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 0) 
	{
		if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return TRUE;
		if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) return FALSE;
	}
	else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 10) return TRUE;
	else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 90) return TRUE;
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 0) return FALSE;
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 1) return FALSE;
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 2) return FALSE;
		return FALSE;
}

//Is OS NT
bool is_osnt()
{
	OSVERSIONINFO vInfo;

#ifndef NO_DEBUG
		printf("[DEBUG] Checking if os is NT, isosnt()...\n");
#endif

		vInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&vInfo);
	if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 0) 
	{
		if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) return FALSE;
		if (vInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) return FALSE;
	}
	else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 10) return FALSE;
	else if (vInfo.dwMajorVersion == 4 && vInfo.dwMinorVersion == 90) return FALSE;
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 0) return TRUE;
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 1) return TRUE;
	else if (vInfo.dwMajorVersion == 5 && vInfo.dwMinorVersion == 2) return TRUE;
		return FALSE;
}
#endif