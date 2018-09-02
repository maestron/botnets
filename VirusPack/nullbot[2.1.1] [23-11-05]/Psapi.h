/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1994-1999  Microsoft Corporation

Module Name:

    psapi.h

Abstract:

    Include file for APIs provided by PSAPI.DLL

Author:

    Richard Shupak   [richards]  06-Jan-1994

Revision History:

--*/

#ifndef _PSAPI_H_
#define _PSAPI_H_

#if _MSC_VER > 1000
#pragma once
#endif

#ifdef __cplusplus
extern "C" {
#endif

BOOL
WINAPI
EnumProcesses(
    DWORD * lpidProcess,
    DWORD   cb,
    DWORD * cbNeeded
    );

BOOL
WINAPI
EnumProcessModules(
    HANDLE hProcess,
    HMODULE *lphModule,
    DWORD cb,
    LPDWORD lpcbNeeded
    );

DWORD
WINAPI
GetModuleBaseNameA(
    HANDLE hProcess,
    HMODULE hModule,
    LPSTR lpBaseName,
    DWORD nSize
    );

DWORD
WINAPI
GetModuleBaseNameW(
    HANDLE hProcess,
    HMODULE hModule,
    LPWSTR lpBaseName,
    DWORD nSize
    );

#ifdef UNICODE
#define GetModuleBaseName  GetModuleBaseNameW
#else
#define GetModuleBaseName  GetModuleBaseNameA
#endif // !UNICODE


DWORD
WINAPI
GetModuleFileNameExA(
    HANDLE hProcess,
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize
    );

DWORD
WINAPI
GetModuleFileNameExW(
    HANDLE hProcess,
    HMODULE hModule,
    LPWSTR lpFilename,
    DWORD nSize
    );

#ifdef UNICODE
#define GetModuleFileNameEx  GetModuleFileNameExW
#else
#define GetModuleFileNameEx  GetModuleFileNameExA
#endif // !UNICODE


typedef struct _MODULEINFO {
    LPVOID lpBaseOfDll;
    DWORD SizeOfImage;
    LPVOID EntryPoint;
} MODULEINFO, *LPMODULEINFO;


BOOL
WINAPI
GetModuleInformation(
    HANDLE hProcess,
    HMODULE hModule,
    LPMODULEINFO lpmodinfo,
    DWORD cb
    );


BOOL
WINAPI
EmptyWorkingSet(
    HANDLE hProcess
    );


BOOL
WINAPI
QueryWorkingSet(
    HANDLE hProcess,
    PVOID pv,
    DWORD cb
    );

BOOL
WINAPI
InitializeProcessForWsWatch(
    HANDLE hProcess
    );


typedef struct _PSAPI_WS_WATCH_INFORMATION {
    LPVOID FaultingPc;
    LPVOID FaultingVa;
} PSAPI_WS_WATCH_INFORMATION, *PPSAPI_WS_WATCH_INFORMATION;

BOOL
WINAPI
GetWsChanges(
    HANDLE hProcess,
    PPSAPI_WS_WATCH_INFORMATION lpWatchInfo,
    DWORD cb
    );

DWORD
WINAPI
GetMappedFileNameW(
    HANDLE hProcess,
    LPVOID lpv,
    LPWSTR lpFilename,
    DWORD nSize
    );

DWORD
WINAPI
GetMappedFileNameA(
    HANDLE hProcess,
    LPVOID lpv,
    LPSTR lpFilename,
    DWORD nSize
    );

#ifdef UNICODE
#define GetMappedFileName  GetMappedFileNameW
#else
#define GetMappedFileName  GetMappedFileNameA
#endif // !UNICODE

BOOL
WINAPI
EnumDeviceDrivers(
    LPVOID *lpImageBase,
    DWORD cb,
    LPDWORD lpcbNeeded
    );


DWORD
WINAPI
GetDeviceDriverBaseNameA(
    LPVOID ImageBase,
    LPSTR lpBaseName,
    DWORD nSize
    );

DWORD
WINAPI
GetDeviceDriverBaseNameW(
    LPVOID ImageBase,
    LPWSTR lpBaseName,
    DWORD nSize
    );

#ifdef UNICODE
#define GetDeviceDriverBaseName  GetDeviceDriverBaseNameW
#else
#define GetDeviceDriverBaseName  GetDeviceDriverBaseNameA
#endif // !UNICODE


DWORD
WINAPI
GetDeviceDriverFileNameA(
    LPVOID ImageBase,
    LPSTR lpFilename,
    DWORD nSize
    );

DWORD
WINAPI
GetDeviceDriverFileNameW(
    LPVOID ImageBase,
    LPWSTR lpFilename,
    DWORD nSize
    );

#ifdef UNICODE
#define GetDeviceDriverFileName  GetDeviceDriverFileNameW
#else
#define GetDeviceDriverFileName  GetDeviceDriverFileNameA
#endif // !UNICODE

// Structure for GetProcessMemoryInfo()

typedef struct _PROCESS_MEMORY_COUNTERS {
    DWORD cb;
    DWORD PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
} PROCESS_MEMORY_COUNTERS;
typedef PROCESS_MEMORY_COUNTERS *PPROCESS_MEMORY_COUNTERS;

#if (_WIN32_WINNT >= 0x0501)

typedef struct _PROCESS_MEMORY_COUNTERS_EX {
    DWORD cb;
    DWORD PageFaultCount;
    SIZE_T PeakWorkingSetSize;
    SIZE_T WorkingSetSize;
    SIZE_T QuotaPeakPagedPoolUsage;
    SIZE_T QuotaPagedPoolUsage;
    SIZE_T QuotaPeakNonPagedPoolUsage;
    SIZE_T QuotaNonPagedPoolUsage;
    SIZE_T PagefileUsage;
    SIZE_T PeakPagefileUsage;
    SIZE_T PrivateUsage;
} PROCESS_MEMORY_COUNTERS_EX;
typedef PROCESS_MEMORY_COUNTERS_EX *PPROCESS_MEMORY_COUNTERS_EX;

#endif

BOOL
WINAPI
GetProcessMemoryInfo(
    HANDLE Process,
    PPROCESS_MEMORY_COUNTERS ppsmemCounters,
    DWORD cb
    );

typedef struct _PERFORMANCE_INFORMATION {
    DWORD cb;
    SIZE_T CommitTotal;
    SIZE_T CommitLimit;
    SIZE_T CommitPeak;
    SIZE_T PhysicalTotal;
    SIZE_T PhysicalAvailable;
    SIZE_T SystemCache;
    SIZE_T KernelTotal;
    SIZE_T KernelPaged;
    SIZE_T KernelNonpaged;
    SIZE_T PageSize;
    DWORD HandleCount;
    DWORD ProcessCount;
    DWORD ThreadCount;
} PERFORMANCE_INFORMATION, *PPERFORMANCE_INFORMATION, PERFORMACE_INFORMATION, *PPERFORMACE_INFORMATION;

BOOL
WINAPI
GetPerformanceInfo (
    PPERFORMACE_INFORMATION pPerformanceInformation,
    DWORD cb
    );

typedef struct _ENUM_PAGE_FILE_INFORMATION {
    DWORD cb;
    DWORD Reserved;
    SIZE_T TotalSize;
    SIZE_T TotalInUse;
    SIZE_T PeakUsage;
} ENUM_PAGE_FILE_INFORMATION, *PENUM_PAGE_FILE_INFORMATION;

typedef BOOL (*PENUM_PAGE_FILE_CALLBACKW) (LPVOID pContext, PENUM_PAGE_FILE_INFORMATION pPageFileInfo, LPCWSTR lpFilename);

typedef BOOL (*PENUM_PAGE_FILE_CALLBACKA) (LPVOID pContext, PENUM_PAGE_FILE_INFORMATION pPageFileInfo, LPCSTR lpFilename);

BOOL
WINAPI
EnumPageFilesW (
    PENUM_PAGE_FILE_CALLBACKW pCallBackRoutine,
    LPVOID pContext
    );

BOOL
WINAPI
EnumPageFilesA (
    PENUM_PAGE_FILE_CALLBACKA pCallBackRoutine,
    LPVOID pContext
    );

#ifdef UNICODE
#define PENUM_PAGE_FILE_CALLBACK PENUM_PAGE_FILE_CALLBACKW
#define EnumPageFiles EnumPageFilesW
#else
#define PENUM_PAGE_FILE_CALLBACK PENUM_PAGE_FILE_CALLBACKA
#define EnumPageFiles EnumPageFilesA
#endif // !UNICODE

DWORD
WINAPI
GetProcessImageFileNameA(
    HANDLE hProcess,
    LPSTR lpImageFileName,
    DWORD nSize
    );

DWORD
WINAPI
GetProcessImageFileNameW(
    HANDLE hProcess,
    LPWSTR lpImageFileName,
    DWORD nSize
    );

#ifdef UNICODE
#define GetProcessImageFileName  GetProcessImageFileNameW
#else
#define GetProcessImageFileName  GetProcessImageFileNameA
#endif // !UNICODE

#ifdef __cplusplus
}
#endif

#endif
