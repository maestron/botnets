{******************************************************************************}
{                                                       	               }
{ Process Status API interface Unit for Object Pascal                          }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: psapi.h, released June 2000. The original Pascal       }
{ code is: PsApi.pas, released December 2000. The initial developer of the     }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Obtained through: Joint Endeavour of Delphi Innovators (Project JEDI)        }
{								               }
{ You may retrieve the latest version of this file at the Project JEDI home    }
{ page, located at http://delphi-jedi.org or my personal homepage located at   }
{ http://members.chello.nl/m.vanbrakel2                                        }
{								               }
{ The contents of this file are used with permission, subject to the Mozilla   }
{ Public License Version 1.1 (the "License"); you may not use this file except }
{ in compliance with the License. You may obtain a copy of the License at      }
{ http://www.mozilla.org/MPL/MPL-1.1.html                                      }
{                                                                              }
{ Software distributed under the License is distributed on an "AS IS" basis,   }
{ WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for }
{ the specific language governing rights and limitations under the License.    }
{                                                                              }
{ Alternatively, the contents of this file may be used under the terms of the  }
{ GNU Lesser General Public License (the  "LGPL License"), in which case the   }
{ provisions of the LGPL License are applicable instead of those above.        }
{ If you wish to allow use of your version of this file only under the terms   }
{ of the LGPL License and not to allow others to use your version of this file }
{ under the MPL, indicate your decision by deleting  the provisions above and  }
{ replace  them with the notice and other provisions required by the LGPL      }
{ License.  If you do not delete the provisions above, a recipient may use     }
{ your version of this file under either the MPL or the LGPL License.          }
{ 								               }
{ For more information about the LGPL: http://www.gnu.org/copyleft/lesser.html }
{ 								               }
{******************************************************************************}

unit JwaPsApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include <psapi.h>'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

function EnumProcesses(lpidProcess: LPDWORD; cb: DWORD; var cbNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumProcesses}

function EnumProcessModules(hProcess: HANDLE; lphModule: PHMODULE; cb: DWORD;
  var lpcbNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumProcessModules}

function GetModuleBaseNameA(hProcess: HANDLE; hModule: HMODULE; lpBaseName: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleBaseNameA}
function GetModuleBaseNameW(hProcess: HANDLE; hModule: HMODULE; lpBaseName: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleBaseNameW}

{$IFDEF UNICODE}
function GetModuleBaseName(hProcess: HANDLE; hModule: HMODULE; lpBaseName: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleBaseName}
{$ELSE}
function GetModuleBaseName(hProcess: HANDLE; hModule: HMODULE; lpBaseName: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleBaseName}
{$ENDIF}

function GetModuleFileNameExA(hProcess: HANDLE; hModule: HMODULE; lpFilename: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleFileNameExA}
function GetModuleFileNameExW(hProcess: HANDLE; hModule: HMODULE; lpFilename: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleFileNameExW}

{$IFDEF UNICODE}
function GetModuleFileNameEx(hProcess: HANDLE; hModule: HMODULE; lpFilename: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleFileNameEx}
{$ELSE}
function GetModuleFileNameEx(hProcess: HANDLE; hModule: HMODULE; lpFilename: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetModuleFileNameEx}
{$ENDIF}

type
  LPMODULEINFO = ^MODULEINFO;
  {$EXTERNALSYM LPMODULEINFO}
  _MODULEINFO = packed record
    lpBaseOfDll: LPVOID;
    SizeOfImage: DWORD;
    EntryPoint: LPVOID;
  end;
  {$EXTERNALSYM _MODULEINFO}
  MODULEINFO = _MODULEINFO;
  {$EXTERNALSYM MODULEINFO}
  TModuleInfo = MODULEINFO;
  PModuleInfo = LPMODULEINFO;

function GetModuleInformation(hProcess: HANDLE; hModule: HMODULE;
  var lpmodinfo: MODULEINFO; cb: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetModuleInformation}

function EmptyWorkingSet(hProcess: HANDLE): BOOL; stdcall;
{$EXTERNALSYM EmptyWorkingSet}

function QueryWorkingSet(hProcess: HANDLE; pv: PVOID; cb: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryWorkingSet}

function InitializeProcessForWsWatch(hProcess: HANDLE): BOOL; stdcall;
{$EXTERNALSYM InitializeProcessForWsWatch}

type
  PPSAPI_WS_WATCH_INFORMATION = ^PSAPI_WS_WATCH_INFORMATION;
  {$EXTERNALSYM PPSAPI_WS_WATCH_INFORMATION}
  _PSAPI_WS_WATCH_INFORMATION = packed record
    FaultingPc: LPVOID;
    FaultingVa: LPVOID;
  end;
  {$EXTERNALSYM _PSAPI_WS_WATCH_INFORMATION}
  PSAPI_WS_WATCH_INFORMATION = _PSAPI_WS_WATCH_INFORMATION;
  {$EXTERNALSYM PSAPI_WS_WATCH_INFORMATION}
  TPsApiWsWatchInformation = PSAPI_WS_WATCH_INFORMATION;
  PPsApiWsWatchInformation = PPSAPI_WS_WATCH_INFORMATION;

function GetWsChanges(hProcess: HANDLE; var lpWatchInfo: PSAPI_WS_WATCH_INFORMATION;
  cb: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetWsChanges}

function GetMappedFileNameW(hProcess: HANDLE; lpv: LPVOID; lpFilename: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetMappedFileNameW}
function GetMappedFileNameA(hProcess: HANDLE; lpv: LPVOID; lpFilename: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetMappedFileNameA}

{$IFDEF UNICODE}
function GetMappedFileName(hProcess: HANDLE; lpv: LPVOID; lpFilename: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetMappedFileName}
{$ELSE}
function GetMappedFileName(hProcess: HANDLE; lpv: LPVOID; lpFilename: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetMappedFileName}
{$ENDIF}

function EnumDeviceDrivers(lpImageBase: LPLPVOID; cb: DWORD; var lpcbNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumDeviceDrivers}

function GetDeviceDriverBaseNameA(ImageBase: LPVOID; lpBaseName: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverBaseNameA}
function GetDeviceDriverBaseNameW(ImageBase: LPVOID; lpBaseName: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverBaseNameW}

{$IFDEF UNICODE}
function GetDeviceDriverBaseName(ImageBase: LPVOID; lpBaseName: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverBaseName}
{$ELSE}
function GetDeviceDriverBaseName(ImageBase: LPVOID; lpBaseName: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverBaseName}
{$ENDIF}

function GetDeviceDriverFileNameA(ImageBase: LPVOID; lpFilename: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverFileNameA}
function GetDeviceDriverFileNameW(ImageBase: LPVOID; lpFilename: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverFileNameW}

{$IFDEF UNICODE}
function GetDeviceDriverFileName(ImageBase: LPVOID; lpFilename: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverFileName}
{$ELSE}
function GetDeviceDriverFileName(ImageBase: LPVOID; lpFilename: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetDeviceDriverFileName}
{$ENDIF}

// Structure for GetProcessMemoryInfo()

type
  PPROCESS_MEMORY_COUNTERS = ^PROCESS_MEMORY_COUNTERS;
  {$EXTERNALSYM PPROCESS_MEMORY_COUNTERS}
  _PROCESS_MEMORY_COUNTERS = packed record
    cb: DWORD;
    PageFaultCount: DWORD;
    PeakWorkingSetSize: SIZE_T;
    WorkingSetSize: SIZE_T;
    QuotaPeakPagedPoolUsage: SIZE_T;
    QuotaPagedPoolUsage: SIZE_T;
    QuotaPeakNonPagedPoolUsage: SIZE_T;
    QuotaNonPagedPoolUsage: SIZE_T;
    PagefileUsage: SIZE_T;
    PeakPagefileUsage: SIZE_T;
  end;
  {$EXTERNALSYM _PROCESS_MEMORY_COUNTERS}
  PROCESS_MEMORY_COUNTERS = _PROCESS_MEMORY_COUNTERS;
  {$EXTERNALSYM PROCESS_MEMORY_COUNTERS}
  TProcessMemoryCounters = PROCESS_MEMORY_COUNTERS;
  PProcessMemoryCounters = PPROCESS_MEMORY_COUNTERS;

  _PROCESS_MEMORY_COUNTERS_EX = record
    cb: DWORD;
    PageFaultCount: DWORD;
    PeakWorkingSetSize: SIZE_T;
    WorkingSetSize: SIZE_T;
    QuotaPeakPagedPoolUsage: SIZE_T;
    QuotaPagedPoolUsage: SIZE_T;
    QuotaPeakNonPagedPoolUsage: SIZE_T;
    QuotaNonPagedPoolUsage: SIZE_T;
    PagefileUsage: SIZE_T;
    PeakPagefileUsage: SIZE_T;
    PrivateUsage: SIZE_T;
  end;
  {$EXTERNALSYM _PROCESS_MEMORY_COUNTERS_EX}
  PROCESS_MEMORY_COUNTERS_EX = _PROCESS_MEMORY_COUNTERS_EX;
  {$EXTERNALSYM PROCESS_MEMORY_COUNTERS_EX}
  PPROCESS_MEMORY_COUNTERS_EX = ^PROCESS_MEMORY_COUNTERS_EX;
  {$EXTERNALSYM PPROCESS_MEMORY_COUNTERS_EX}
  TProcessMemoryCountersEx = PROCESS_MEMORY_COUNTERS_EX;

function GetProcessMemoryInfo(Process: HANDLE;
  var ppsmemCounters: PROCESS_MEMORY_COUNTERS; cb: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetProcessMemoryInfo}

type
  _PERFORMANCE_INFORMATION = record
    cb: DWORD;
    CommitTotal: SIZE_T;
    CommitLimit: SIZE_T;
    CommitPeak: SIZE_T;
    PhysicalTotal: SIZE_T;
    PhysicalAvailable: SIZE_T;
    SystemCache: SIZE_T;
    KernelTotal: SIZE_T;
    KernelPaged: SIZE_T;
    KernelNonpaged: SIZE_T;
    PageSize: SIZE_T;
    HandleCount: DWORD;
    ProcessCount: DWORD;
    ThreadCount: DWORD;
  end;
  {$EXTERNALSYM _PERFORMANCE_INFORMATION}
  PERFORMANCE_INFORMATION = _PERFORMANCE_INFORMATION;
  {$EXTERNALSYM PERFORMANCE_INFORMATION}
  PPERFORMANCE_INFORMATION = ^PERFORMANCE_INFORMATION;
  {$EXTERNALSYM PPERFORMANCE_INFORMATION}
  TPerformanceInformation = PERFORMANCE_INFORMATION;
  PPerformanceInformation = PPERFORMANCE_INFORMATION;

{ MVB:

  Please note that this function, unlike what the Platform SDK documents, is _not_ available for Windows 2000!!!
  It is available starting with Windows XP and Windows.NET Server.
  If needed, you can relatively easily clone the functionality of this function by using the performance monitor
  API (either through the HKEY_PERFORMANCE_DATA registry interface or using the Performance Data Helper API)
}

function GetPerformanceInfo(pPerformanceInformation: PPERFORMANCE_INFORMATION;
  cb: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetPerformanceInfo}

type
  _ENUM_PAGE_FILE_INFORMATION = record
    cb: DWORD;
    Reserved: DWORD;
    TotalSize: SIZE_T;
    TotalInUse: SIZE_T;
    PeakUsage: SIZE_T;
  end;
  {$EXTERNALSYM _ENUM_PAGE_FILE_INFORMATION}
  ENUM_PAGE_FILE_INFORMATION = _ENUM_PAGE_FILE_INFORMATION;
  {$EXTERNALSYM ENUM_PAGE_FILE_INFORMATION}
  PENUM_PAGE_FILE_INFORMATION = ^ENUM_PAGE_FILE_INFORMATION;
  TEnumPageFileInformation = ENUM_PAGE_FILE_INFORMATION;
  PEnumPageFileInformation = PENUM_PAGE_FILE_INFORMATION;

type
  PENUM_PAGE_FILE_CALLBACKW = function (pContext: LPVOID;
    pPageFileInfo: PENUM_PAGE_FILE_INFORMATION; lpFilename: LPCWSTR): BOOL; stdcall;
  {$EXTERNALSYM PENUM_PAGE_FILE_CALLBACKW}
  PENUM_PAGE_FILE_CALLBACKA = function (pContext: LPVOID;
    pPageFileInfo: PENUM_PAGE_FILE_INFORMATION; lpFilename: LPCSTR): BOOL; stdcall;
  {$EXTERNALSYM PENUM_PAGE_FILE_CALLBACKA}

function EnumPageFilesW(pCallBackRoutine: PENUM_PAGE_FILE_CALLBACKW; pContext: LPVOID): BOOL; stdcall;
{$EXTERNALSYM EnumPageFilesW}
function EnumPageFilesA(pCallBackRoutine: PENUM_PAGE_FILE_CALLBACKA; pContext: LPVOID): BOOL; stdcall;
{$EXTERNALSYM EnumPageFilesA}

{$IFDEF UNICODE}
type
  PENUM_PAGE_FILE_CALLBACK = PENUM_PAGE_FILE_CALLBACKW;
  {$EXTERNALSYM PENUM_PAGE_FILE_CALLBACK}
function EnumPageFiles(pCallBackRoutine: PENUM_PAGE_FILE_CALLBACKW; pContext: LPVOID): BOOL; stdcall;
{$EXTERNALSYM EnumPageFiles}
{$ELSE}
type
  PENUM_PAGE_FILE_CALLBACK = PENUM_PAGE_FILE_CALLBACKA;
  {$EXTERNALSYM PENUM_PAGE_FILE_CALLBACK}
function EnumPageFiles(pCallBackRoutine: PENUM_PAGE_FILE_CALLBACKA; pContext: LPVOID): BOOL; stdcall;
{$EXTERNALSYM EnumPageFiles}
{$ENDIF}

function GetProcessImageFileNameA(hProcess: HANDLE; lpImageFileName: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetProcessImageFileNameA}
function GetProcessImageFileNameW(hProcess: HANDLE; lpImageFileName: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetProcessImageFileNameW}

{$IFDEF UNICODE}
function GetProcessImageFileName(hProcess: HANDLE; lpImageFileName: LPWSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetProcessImageFileName}
{$ELSE}
function GetProcessImageFileName(hProcess: HANDLE; lpImageFileName: LPSTR;
  nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetProcessImageFileName}
{$ENDIF}

implementation

const
  PsapiLib = 'psapi.dll';


{$IFDEF DYNAMIC_LINK}
var
  _EnumProcesses: Pointer;

function EnumProcesses;
begin
  GetProcedureAddress(_EnumProcesses, PsapiLib, 'EnumProcesses');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumProcesses]
  end;
end;
{$ELSE}
function EnumProcesses; external PsapiLib name 'EnumProcesses';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumProcessModules: Pointer;

function EnumProcessModules;
begin
  GetProcedureAddress(_EnumProcessModules, PsapiLib, 'EnumProcessModules');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumProcessModules]
  end;
end;
{$ELSE}
function EnumProcessModules; external PsapiLib name 'EnumProcessModules';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleBaseNameA: Pointer;

function GetModuleBaseNameA;
begin
  GetProcedureAddress(_GetModuleBaseNameA, PsapiLib, 'GetModuleBaseNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleBaseNameA]
  end;
end;
{$ELSE}
function GetModuleBaseNameA; external PsapiLib name 'GetModuleBaseNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleBaseNameW: Pointer;

function GetModuleBaseNameW;
begin
  GetProcedureAddress(_GetModuleBaseNameW, PsapiLib, 'GetModuleBaseNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleBaseNameW]
  end;
end;
{$ELSE}
function GetModuleBaseNameW; external PsapiLib name 'GetModuleBaseNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleBaseName: Pointer;

function GetModuleBaseName;
begin
  GetProcedureAddress(_GetModuleBaseName, PsapiLib, 'GetModuleBaseNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleBaseName]
  end;
end;
{$ELSE}
function GetModuleBaseName; external PsapiLib name 'GetModuleBaseNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleBaseName: Pointer;

function GetModuleBaseName;
begin
  GetProcedureAddress(_GetModuleBaseName, PsapiLib, 'GetModuleBaseNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleBaseName]
  end;
end;
{$ELSE}
function GetModuleBaseName; external PsapiLib name 'GetModuleBaseNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleFileNameExA: Pointer;

function GetModuleFileNameExA;
begin
  GetProcedureAddress(_GetModuleFileNameExA, PsapiLib, 'GetModuleFileNameExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleFileNameExA]
  end;
end;
{$ELSE}
function GetModuleFileNameExA; external PsapiLib name 'GetModuleFileNameExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleFileNameExW: Pointer;

function GetModuleFileNameExW;
begin
  GetProcedureAddress(_GetModuleFileNameExW, PsapiLib, 'GetModuleFileNameExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleFileNameExW]
  end;
end;
{$ELSE}
function GetModuleFileNameExW; external PsapiLib name 'GetModuleFileNameExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleFileNameEx: Pointer;

function GetModuleFileNameEx;
begin
  GetProcedureAddress(_GetModuleFileNameEx, PsapiLib, 'GetModuleFileNameExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleFileNameEx]
  end;
end;
{$ELSE}
function GetModuleFileNameEx; external PsapiLib name 'GetModuleFileNameExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleFileNameEx: Pointer;

function GetModuleFileNameEx;
begin
  GetProcedureAddress(_GetModuleFileNameEx, PsapiLib, 'GetModuleFileNameExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleFileNameEx]
  end;
end;
{$ELSE}
function GetModuleFileNameEx; external PsapiLib name 'GetModuleFileNameExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetModuleInformation: Pointer;

function GetModuleInformation;
begin
  GetProcedureAddress(_GetModuleInformation, PsapiLib, 'GetModuleInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetModuleInformation]
  end;
end;
{$ELSE}
function GetModuleInformation; external PsapiLib name 'GetModuleInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EmptyWorkingSet: Pointer;

function EmptyWorkingSet;
begin
  GetProcedureAddress(_EmptyWorkingSet, PsapiLib, 'EmptyWorkingSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EmptyWorkingSet]
  end;
end;
{$ELSE}
function EmptyWorkingSet; external PsapiLib name 'EmptyWorkingSet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _QueryWorkingSet: Pointer;

function QueryWorkingSet;
begin
  GetProcedureAddress(_QueryWorkingSet, PsapiLib, 'QueryWorkingSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryWorkingSet]
  end;
end;
{$ELSE}
function QueryWorkingSet; external PsapiLib name 'QueryWorkingSet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _InitializeProcessForWsWatch: Pointer;

function InitializeProcessForWsWatch;
begin
  GetProcedureAddress(_InitializeProcessForWsWatch, PsapiLib, 'InitializeProcessForWsWatch');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InitializeProcessForWsWatch]
  end;
end;
{$ELSE}
function InitializeProcessForWsWatch; external PsapiLib name 'InitializeProcessForWsWatch';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetWsChanges: Pointer;

function GetWsChanges;
begin
  GetProcedureAddress(_GetWsChanges, PsapiLib, 'GetWsChanges');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetWsChanges]
  end;
end;
{$ELSE}
function GetWsChanges; external PsapiLib name 'GetWsChanges';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetMappedFileNameW: Pointer;

function GetMappedFileNameW;
begin
  GetProcedureAddress(_GetMappedFileNameW, PsapiLib, 'GetMappedFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMappedFileNameW]
  end;
end;
{$ELSE}
function GetMappedFileNameW; external PsapiLib name 'GetMappedFileNameW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetMappedFileNameA: Pointer;

function GetMappedFileNameA;
begin
  GetProcedureAddress(_GetMappedFileNameA, PsapiLib, 'GetMappedFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMappedFileNameA]
  end;
end;
{$ELSE}
function GetMappedFileNameA; external PsapiLib name 'GetMappedFileNameA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetMappedFileName: Pointer;

function GetMappedFileName;
begin
  GetProcedureAddress(_GetMappedFileName, PsapiLib, 'GetMappedFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMappedFileName]
  end;
end;
{$ELSE}
function GetMappedFileName; external PsapiLib name 'GetMappedFileNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetMappedFileName: Pointer;

function GetMappedFileName;
begin
  GetProcedureAddress(_GetMappedFileName, PsapiLib, 'GetMappedFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetMappedFileName]
  end;
end;
{$ELSE}
function GetMappedFileName; external PsapiLib name 'GetMappedFileNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _EnumDeviceDrivers: Pointer;

function EnumDeviceDrivers;
begin
  GetProcedureAddress(_EnumDeviceDrivers, PsapiLib, 'EnumDeviceDrivers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumDeviceDrivers]
  end;
end;
{$ELSE}
function EnumDeviceDrivers; external PsapiLib name 'EnumDeviceDrivers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverBaseNameA: Pointer;

function GetDeviceDriverBaseNameA;
begin
  GetProcedureAddress(_GetDeviceDriverBaseNameA, PsapiLib, 'GetDeviceDriverBaseNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverBaseNameA]
  end;
end;
{$ELSE}
function GetDeviceDriverBaseNameA; external PsapiLib name 'GetDeviceDriverBaseNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverBaseNameW: Pointer;

function GetDeviceDriverBaseNameW;
begin
  GetProcedureAddress(_GetDeviceDriverBaseNameW, PsapiLib, 'GetDeviceDriverBaseNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverBaseNameW]
  end;
end;
{$ELSE}
function GetDeviceDriverBaseNameW; external PsapiLib name 'GetDeviceDriverBaseNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverBaseName: Pointer;

function GetDeviceDriverBaseName;
begin
  GetProcedureAddress(_GetDeviceDriverBaseName, PsapiLib, 'GetDeviceDriverBaseNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverBaseName]
  end;
end;
{$ELSE}
function GetDeviceDriverBaseName; external PsapiLib name 'GetDeviceDriverBaseNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverBaseName: Pointer;

function GetDeviceDriverBaseName;
begin
  GetProcedureAddress(_GetDeviceDriverBaseName, PsapiLib, 'GetDeviceDriverBaseNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverBaseName]
  end;
end;
{$ELSE}
function GetDeviceDriverBaseName; external PsapiLib name 'GetDeviceDriverBaseNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverFileNameA: Pointer;

function GetDeviceDriverFileNameA;
begin
  GetProcedureAddress(_GetDeviceDriverFileNameA, PsapiLib, 'GetDeviceDriverFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverFileNameA]
  end;
end;
{$ELSE}
function GetDeviceDriverFileNameA; external PsapiLib name 'GetDeviceDriverFileNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverFileNameW: Pointer;

function GetDeviceDriverFileNameW;
begin
  GetProcedureAddress(_GetDeviceDriverFileNameW, PsapiLib, 'GetDeviceDriverFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverFileNameW]
  end;
end;
{$ELSE}
function GetDeviceDriverFileNameW; external PsapiLib name 'GetDeviceDriverFileNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverFileName: Pointer;

function GetDeviceDriverFileName;
begin
  GetProcedureAddress(_GetDeviceDriverFileName, PsapiLib, 'GetDeviceDriverFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverFileName]
  end;
end;
{$ELSE}
function GetDeviceDriverFileName; external PsapiLib name 'GetDeviceDriverFileNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetDeviceDriverFileName: Pointer;

function GetDeviceDriverFileName;
begin
  GetProcedureAddress(_GetDeviceDriverFileName, PsapiLib, 'GetDeviceDriverFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetDeviceDriverFileName]
  end;
end;
{$ELSE}
function GetDeviceDriverFileName; external PsapiLib name 'GetDeviceDriverFileNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetProcessMemoryInfo: Pointer;

function GetProcessMemoryInfo;
begin
  GetProcedureAddress(_GetProcessMemoryInfo, PsapiLib, 'GetProcessMemoryInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProcessMemoryInfo]
  end;
end;
{$ELSE}
function GetProcessMemoryInfo; external PsapiLib name 'GetProcessMemoryInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetPerformanceInfo: Pointer;

function GetPerformanceInfo;
begin
  GetProcedureAddress(_GetPerformanceInfo, PsapiLib, 'GetPerformanceInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetPerformanceInfo]
  end;
end;
{$ELSE}
function GetPerformanceInfo; external PsapiLib name 'GetPerformanceInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumPageFilesW: Pointer;

function EnumPageFilesW;
begin
  GetProcedureAddress(_EnumPageFilesW, PsapiLib, 'EnumPageFilesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumPageFilesW]
  end;
end;
{$ELSE}
function EnumPageFilesW; external PsapiLib name 'EnumPageFilesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumPageFilesA: Pointer;

function EnumPageFilesA;
begin
  GetProcedureAddress(_EnumPageFilesA, PsapiLib, 'EnumPageFilesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumPageFilesA]
  end;
end;
{$ELSE}
function EnumPageFilesA; external PsapiLib name 'EnumPageFilesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumPageFiles: Pointer;

function EnumPageFiles;
begin
  GetProcedureAddress(_EnumPageFiles, PsapiLib, 'EnumPageFilesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumPageFiles]
  end;
end;
{$ELSE}
function EnumPageFiles; external PsapiLib name 'EnumPageFilesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumPageFiles: Pointer;

function EnumPageFiles;
begin
  GetProcedureAddress(_EnumPageFiles, PsapiLib, 'EnumPageFilesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumPageFiles]
  end;
end;
{$ELSE}
function EnumPageFiles; external PsapiLib name 'EnumPageFilesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetProcessImageFileNameA: Pointer;

function GetProcessImageFileNameA;
begin
  GetProcedureAddress(_GetProcessImageFileNameA, PsapiLib, 'GetProcessImageFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProcessImageFileNameA]
  end;
end;
{$ELSE}
function GetProcessImageFileNameA; external PsapiLib name 'GetProcessImageFileNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetProcessImageFileNameW: Pointer;

function GetProcessImageFileNameW;
begin
  GetProcedureAddress(_GetProcessImageFileNameW, PsapiLib, 'GetProcessImageFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProcessImageFileNameW]
  end;
end;
{$ELSE}
function GetProcessImageFileNameW; external PsapiLib name 'GetProcessImageFileNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetProcessImageFileName: Pointer;

function GetProcessImageFileName;
begin
  GetProcedureAddress(_GetProcessImageFileName, PsapiLib, 'GetProcessImageFileNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProcessImageFileName]
  end;
end;
{$ELSE}
function GetProcessImageFileName; external PsapiLib name 'GetProcessImageFileNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetProcessImageFileName: Pointer;

function GetProcessImageFileName;
begin
  GetProcedureAddress(_GetProcessImageFileName, PsapiLib, 'GetProcessImageFileNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProcessImageFileName]
  end;
end;
{$ELSE}
function GetProcessImageFileName; external PsapiLib name 'GetProcessImageFileNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
