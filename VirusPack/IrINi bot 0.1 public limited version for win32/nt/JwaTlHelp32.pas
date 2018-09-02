{******************************************************************************}
{                                                       	               }
{ ToolHelp API interface Unit for Object Pascal                                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: tlhelp32.h, released June 2000. The original Pascal    }
{ code is: TlHelp32.pas, released December 2000. The initial developer of the  }
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

unit JwaTlHelp32;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "tlhelp32.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

const
  MAX_MODULE_NAME32 = 255;
  {$EXTERNALSYM MAX_MODULE_NAME32}

// Snapshot function

function CreateToolhelp32Snapshot(dwFlags, th32ProcessID: DWORD): HANDLE; stdcall;
{$EXTERNALSYM CreateToolhelp32Snapshot}

//
// The th32ProcessID argument is only used if TH32CS_SNAPHEAPLIST or
// TH32CS_SNAPMODULE is specified. th32ProcessID == 0 means the current
// process.
//
// NOTE that all of the snapshots are global except for the heap and module
//      lists which are process specific. To enumerate the heap or module
//      state for all WIN32 processes call with TH32CS_SNAPALL and the
//      current process. Then for each process in the TH32CS_SNAPPROCESS
//      list that isn't the current process, do a call with just
//      TH32CS_SNAPHEAPLIST and/or TH32CS_SNAPMODULE.
//
// dwFlags
//

const
  TH32CS_SNAPHEAPLIST = $00000001;
  {$EXTERNALSYM TH32CS_SNAPHEAPLIST}
  TH32CS_SNAPPROCESS  = $00000002;
  {$EXTERNALSYM TH32CS_SNAPPROCESS}
  TH32CS_SNAPTHREAD   = $00000004;
  {$EXTERNALSYM TH32CS_SNAPTHREAD}
  TH32CS_SNAPMODULE   = $00000008;
  {$EXTERNALSYM TH32CS_SNAPMODULE}
  TH32CS_SNAPMODULE32 = $00000010;
  {$EXTERNALSYM TH32CS_SNAPMODULE32}
  TH32CS_SNAPALL      = TH32CS_SNAPHEAPLIST or TH32CS_SNAPPROCESS or
                        TH32CS_SNAPTHREAD or TH32CS_SNAPMODULE;
  {$EXTERNALSYM TH32CS_SNAPALL}
  TH32CS_INHERIT      = $80000000;
  {$EXTERNALSYM TH32CS_INHERIT}

//
// Use CloseHandle to destroy the snapshot
//

// Heap walking

type
  PHEAPLIST32 = ^HEAPLIST32;
  {$EXTERNALSYM PHEAPLIST32}
  tagHEAPLIST32 = record
    dwSize: SIZE_T;
    th32ProcessID: DWORD;   // owning process
    th32HeapID: ULONG_PTR;  // heap (in owning process's context!)
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM tagHEAPLIST32}
  HEAPLIST32 = tagHEAPLIST32;
  {$EXTERNALSYM HEAPLIST32}
  LPHEAPLIST32 = ^HEAPLIST32;
  {$EXTERNALSYM LPHEAPLIST32}
  THeapList32 = HEAPLIST32;

//
// dwFlags
//

const
  HF32_DEFAULT    = 1;  // process's default heap
  {$EXTERNALSYM HF32_DEFAULT}
  HF32_SHARED     = 2;  // is shared heap
  {$EXTERNALSYM HF32_SHARED}

function Heap32ListFirst(hSnapshot: HANDLE; var lphl: HEAPLIST32): BOOL; stdcall;
{$EXTERNALSYM Heap32ListFirst}
function Heap32ListNext(hSnapshot: HANDLE; var lphl: HEAPLIST32): BOOL; stdcall;
{$EXTERNALSYM Heap32ListNext}

type
  PHEAPENTRY32 = ^HEAPENTRY32;
  {$EXTERNALSYM PHEAPENTRY32}
  tagHEAPENTRY32 = record
    dwSize: SIZE_T;
    hHandle: HANDLE;       // Handle of this heap block
    dwAddress: ULONG_PTR;  // Linear address of start of block
    dwBlockSize: SIZE_T;   // Size of block in bytes
    dwFlags: DWORD;
    dwLockCount: DWORD;
    dwResvd: DWORD;
    th32ProcessID: DWORD;  // owning process
    th32HeapID: ULONG_PTR; // heap block is in
  end;
  {$EXTERNALSYM tagHEAPENTRY32}
  HEAPENTRY32 = tagHEAPENTRY32;
  {$EXTERNALSYM HEAPENTRY32}
  LPHEAPENTRY32 = ^HEAPENTRY32;
  {$EXTERNALSYM LPHEAPENTRY32}
  THeapEntry32 = HEAPENTRY32;

//
// dwFlags
//

const
  LF32_FIXED    = $00000001;
  {$EXTERNALSYM LF32_FIXED}
  LF32_FREE     = $00000002;
  {$EXTERNALSYM LF32_FREE}
  LF32_MOVEABLE = $00000004;
  {$EXTERNALSYM LF32_MOVEABLE}

function Heap32First(var lphe: HEAPENTRY32; th32ProcessID: DWORD;
  th32HeapID: ULONG_PTR): BOOL; stdcall;
{$EXTERNALSYM Heap32First}
function Heap32Next(var lphe: HEAPENTRY32): BOOL; stdcall;
{$EXTERNALSYM Heap32Next}

function Toolhelp32ReadProcessMemory(th32ProcessID: DWORD; lpBaseAddress: LPCVOID;
  lpBuffer: LPVOID; cbRead: DWORD; lpNumberOfBytesRead: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM Toolhelp32ReadProcessMemory}

// Process walking

type
  PPROCESSENTRY32W = ^PROCESSENTRY32W;
  {$EXTERNALSYM PPROCESSENTRY32W}
  tagPROCESSENTRY32W = record
    dwSize: DWORD;
    cntUsage: DWORD;
    th32ProcessID: DWORD;          // this process
    th32DefaultHeapID: ULONG_PTR;
    th32ModuleID:DWORD;            // associated exe
    cntThreads: DWORD;
    th32ParentProcessID: DWORD;    // this process's parent process
    pcPriClassBase: LONG;          // Base priority of process's threads
    dwFlags: DWORD;
    szExeFile: array [0..MAX_PATH - 1] of WCHAR;   // Path
  end;
  {$EXTERNALSYM tagPROCESSENTRY32W}
  PROCESSENTRY32W = tagPROCESSENTRY32W;
  {$EXTERNALSYM PROCESSENTRY32W}
  LPPROCESSENTRY32W = ^PROCESSENTRY32W;
  {$EXTERNALSYM LPPROCESSENTRY32W}
  TProcessEntry32W = PROCESSENTRY32W;

function Process32FirstW(hSnapshot: HANDLE; var lppe: PROCESSENTRY32W): BOOL; stdcall;
{$EXTERNALSYM Process32FirstW}
function Process32NextW(hSnapshot: HANDLE; var lppe: PROCESSENTRY32W): BOOL; stdcall;
{$EXTERNALSYM Process32NextW}

{$IFNDEF UNICODE}

type
  PPROCESSENTRY32 = ^PROCESSENTRY32;
  {$EXTERNALSYM PPROCESSENTRY32}
  tagPROCESSENTRY32 = record
    dwSize: DWORD;
    cntUsage: DWORD;
    th32ProcessID: DWORD;          // this process
    th32DefaultHeapID: ULONG_PTR;
    th32ModuleID: DWORD;           // associated exe
    cntThreads: DWORD;
    th32ParentProcessID: DWORD;    // this process's parent process
    pcPriClassBase: LONG;          // Base priority of process's threads
    dwFlags: DWORD;
    szExeFile: array [0..MAX_PATH - 1] of CHAR;    // Path
  end;
  {$EXTERNALSYM tagPROCESSENTRY32}
  PROCESSENTRY32 = tagPROCESSENTRY32;
  {$EXTERNALSYM PROCESSENTRY32}
  LPPROCESSENTRY32 = ^PROCESSENTRY32;
  {$EXTERNALSYM LPPROCESSENTRY32}
  TProcessEntry32 = PROCESSENTRY32;

function Process32First(hSnapshot: HANDLE; var lppe: PROCESSENTRY32): BOOL; stdcall;
{$EXTERNALSYM Process32First}
function Process32Next(hSnapshot: HANDLE; var lppe: PROCESSENTRY32): BOOL; stdcall;
{$EXTERNALSYM Process32Next}

{$ELSE}

type
  PROCESSENTRY32 = PROCESSENTRY32W;
  {$EXTERNALSYM PROCESSENTRY32}
  PPROCESSENTRY32 = PPROCESSENTRY32W;
  {$EXTERNALSYM PPROCESSENTRY32}
  LPPROCESSENTRY32 = LPPROCESSENTRY32W;
  {$EXTERNALSYM LPPROCESSENTRY32}
  TProcessEntry32 = TProcessEntry32W;

function Process32First(hSnapshot: HANDLE; var lppe: PROCESSENTRY32): BOOL; stdcall;
{$EXTERNALSYM Process32First}
function Process32Next(hSnapshot: HANDLE; var lppe: PROCESSENTRY32): BOOL; stdcall;
{$EXTERNALSYM Process32Next}

{$ENDIF}

// Thread walking

type
  PTHREADENTRY32 = ^THREADENTRY32;
  {$EXTERNALSYM PTHREADENTRY32}
  tagTHREADENTRY32 = record
    dwSize: DWORD;
    cntUsage: DWORD;
    th32ThreadID: DWORD;       // this thread
    th32OwnerProcessID: DWORD; // Process this thread is associated with
    tpBasePri: LONG;
    tpDeltaPri: LONG;
    dwFlags: DWORD;
  end;
  {$EXTERNALSYM tagTHREADENTRY32}
  THREADENTRY32 = tagTHREADENTRY32;
  {$EXTERNALSYM THREADENTRY32}
  LPTHREADENTRY32 = ^THREADENTRY32;
  {$EXTERNALSYM LPTHREADENTRY32}
  TThreadEntry32 = THREADENTRY32;

function Thread32First(hSnapshot: HANDLE; var lpte: THREADENTRY32): BOOL; stdcall;
{$EXTERNALSYM Thread32First}
function Thread32Next(hSnapshot: HANDLE; var lpte: THREADENTRY32): BOOL; stdcall;
{$EXTERNALSYM Thread32Next}

// Module walking

type
  PMODULEENTRY32W = ^MODULEENTRY32W;
  {$EXTERNALSYM PMODULEENTRY32W}
  tagMODULEENTRY32W = record
    dwSize: DWORD;
    th32ModuleID: DWORD;       // This module
    th32ProcessID: DWORD;      // owning process
    GlblcntUsage: DWORD;       // Global usage count on the module
    ProccntUsage: DWORD;       // Module usage count in th32ProcessID's context
    modBaseAddr: LPBYTE;       // Base address of module in th32ProcessID's context
    modBaseSize: DWORD;        // Size in bytes of module starting at modBaseAddr
    hModule: HMODULE;          // The hModule of this module in th32ProcessID's context
    szModule: array [0..MAX_MODULE_NAME32] of WCHAR;
    szExePath: array [0..MAX_PATH - 1] of WCHAR;
  end;
  {$EXTERNALSYM tagMODULEENTRY32W}
  MODULEENTRY32W = tagMODULEENTRY32W;
  {$EXTERNALSYM MODULEENTRY32W}
  LPMODULEENTRY32W = ^MODULEENTRY32W;
  {$EXTERNALSYM LPMODULEENTRY32W}
  TModuleEntry32W = MODULEENTRY32W;

function Module32FirstW(hSnapshot: HANDLE; var lpme: MODULEENTRY32W): BOOL; stdcall;
{$EXTERNALSYM Module32FirstW}
function Module32NextW(hSnapshot: HANDLE; var lpme: MODULEENTRY32W): BOOL; stdcall;
{$EXTERNALSYM Module32NextW}

{$IFNDEF UNICODE}

type
  PMODULEENTRY32 = ^MODULEENTRY32;
  {$EXTERNALSYM PMODULEENTRY32}
  tagMODULEENTRY32 = record
    dwSize: DWORD;
    th32ModuleID: DWORD;       // This module
    th32ProcessID: DWORD;      // owning process
    GlblcntUsage: DWORD;       // Global usage count on the module
    ProccntUsage: DWORD;       // Module usage count in th32ProcessID's context
    modBaseAddr: LPBYTE;       // Base address of module in th32ProcessID's context
    modBaseSize: DWORD;        // Size in bytes of module starting at modBaseAddr
    hModule: HMODULE;          // The hModule of this module in th32ProcessID's context
    szModule: array [0..MAX_MODULE_NAME32] of CHAR;
    szExePath: array [0..MAX_PATH - 1] of CHAR;
  end;
  {$EXTERNALSYM tagMODULEENTRY32}
  MODULEENTRY32 = tagMODULEENTRY32;
  {$EXTERNALSYM MODULEENTRY32}
  LPMODULEENTRY32 = ^MODULEENTRY32;
  {$EXTERNALSYM LPMODULEENTRY32}
  TModuleEntry32 = MODULEENTRY32;

//
// NOTE CAREFULLY that the modBaseAddr and hModule fields are valid ONLY
// in th32ProcessID's process context.
//

function Module32First(hSnapshot: HANDLE; var lpme: MODULEENTRY32): BOOL; stdcall;
{$EXTERNALSYM Module32First}
function Module32Next(hSnapshot: HANDLE; var lpme: MODULEENTRY32): BOOL; stdcall;
{$EXTERNALSYM Module32Next}

{$ELSE}

type
  MODULEENTRY32 = MODULEENTRY32W;
  {$EXTERNALSYM MODULEENTRY32}
  PMODULEENTRY32 = PMODULEENTRY32W;
  {$EXTERNALSYM PMODULEENTRY32}
  LPMODULEENTRY32 = LPMODULEENTRY32W;
  {$EXTERNALSYM LPMODULEENTRY32}
  TModuleEntry32 = TModuleEntry32W;

function Module32First(hSnapshot: HANDLE; var lpme: MODULEENTRY32): BOOL; stdcall;
{$EXTERNALSYM Module32First}
function Module32Next(hSnapshot: HANDLE; var lpme: MODULEENTRY32): BOOL; stdcall;
{$EXTERNALSYM Module32Next}

{$ENDIF}

implementation

const
  kernel32 = 'kernel32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _CreateToolhelp32Snapshot: Pointer;

function CreateToolhelp32Snapshot;
begin
  GetProcedureAddress(_CreateToolhelp32Snapshot, kernel32, 'CreateToolhelp32Snapshot');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateToolhelp32Snapshot]
  end;
end;
{$ELSE}
function CreateToolhelp32Snapshot; external kernel32 name 'CreateToolhelp32Snapshot';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Heap32ListFirst: Pointer;

function Heap32ListFirst;
begin
  GetProcedureAddress(_Heap32ListFirst, kernel32, 'Heap32ListFirst');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Heap32ListFirst]
  end;
end;
{$ELSE}
function Heap32ListFirst; external kernel32 name 'Heap32ListFirst';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Heap32ListNext: Pointer;

function Heap32ListNext;
begin
  GetProcedureAddress(_Heap32ListNext, kernel32, 'Heap32ListNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Heap32ListNext]
  end;
end;
{$ELSE}
function Heap32ListNext; external kernel32 name 'Heap32ListNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Heap32First: Pointer;

function Heap32First;
begin
  GetProcedureAddress(_Heap32First, kernel32, 'Heap32First');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Heap32First]
  end;
end;
{$ELSE}
function Heap32First; external kernel32 name 'Heap32First';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Heap32Next: Pointer;

function Heap32Next;
begin
  GetProcedureAddress(_Heap32Next, kernel32, 'Heap32Next');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Heap32Next]
  end;
end;
{$ELSE}
function Heap32Next; external kernel32 name 'Heap32Next';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Toolhelp32ReadProcessMemory: Pointer;

function Toolhelp32ReadProcessMemory;
begin
  GetProcedureAddress(_Toolhelp32ReadProcessMemory, kernel32, 'Toolhelp32ReadProcessMemory');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Toolhelp32ReadProcessMemory]
  end;
end;
{$ELSE}
function Toolhelp32ReadProcessMemory; external kernel32 name 'Toolhelp32ReadProcessMemory';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _Process32FirstW: Pointer;

function Process32FirstW;
begin
  GetProcedureAddress(_Process32FirstW, kernel32, 'Process32FirstW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Process32FirstW]
  end;
end;
{$ELSE}
function Process32FirstW; external kernel32 name 'Process32FirstW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Process32NextW: Pointer;

function Process32NextW;
begin
  GetProcedureAddress(_Process32NextW, kernel32, 'Process32NextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Process32NextW]
  end;
end;
{$ELSE}
function Process32NextW; external kernel32 name 'Process32NextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _Process32First: Pointer;

function Process32First;
begin
  GetProcedureAddress(_Process32First, kernel32, 'Process32FirstW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Process32First]
  end;
end;
{$ELSE}
function Process32First; external kernel32 name 'Process32FirstW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Process32Next: Pointer;

function Process32Next;
begin
  GetProcedureAddress(_Process32Next, kernel32, 'Process32NextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Process32Next]
  end;
end;
{$ELSE}
function Process32Next; external kernel32 name 'Process32NextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _Process32First: Pointer;

function Process32First;
begin
  GetProcedureAddress(_Process32First, kernel32, 'Process32First');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Process32First]
  end;
end;
{$ELSE}
function Process32First; external kernel32 name 'Process32First';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Process32Next: Pointer;

function Process32Next;
begin
  GetProcedureAddress(_Process32Next, kernel32, 'Process32Next');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Process32Next]
  end;
end;
{$ELSE}
function Process32Next; external kernel32 name 'Process32Next';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _Thread32First: Pointer;

function Thread32First;
begin
  GetProcedureAddress(_Thread32First, kernel32, 'Thread32First');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Thread32First]
  end;
end;
{$ELSE}
function Thread32First; external kernel32 name 'Thread32First';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Thread32Next: Pointer;

function Thread32Next;
begin
  GetProcedureAddress(_Thread32Next, kernel32, 'Thread32Next');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Thread32Next]
  end;
end;
{$ELSE}
function Thread32Next; external kernel32 name 'Thread32Next';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Module32FirstW: Pointer;

function Module32FirstW;
begin
  GetProcedureAddress(_Module32FirstW, kernel32, 'Module32FirstW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Module32FirstW]
  end;
end;
{$ELSE}
function Module32FirstW; external kernel32 name 'Module32FirstW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Module32NextW: Pointer;

function Module32NextW;
begin
  GetProcedureAddress(_Module32NextW, kernel32, 'Module32NextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Module32NextW]
  end;
end;
{$ELSE}
function Module32NextW; external kernel32 name 'Module32NextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _Module32First: Pointer;

function Module32First;
begin
  GetProcedureAddress(_Module32First, kernel32, 'Module32FirstW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Module32First]
  end;
end;
{$ELSE}
function Module32First; external kernel32 name 'Module32FirstW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Module32Next: Pointer;

function Module32Next;
begin
  GetProcedureAddress(_Module32Next, kernel32, 'Module32NextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Module32Next]
  end;
end;
{$ELSE}
function Module32Next; external kernel32 name 'Module32NextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _Module32First: Pointer;

function Module32First;
begin
  GetProcedureAddress(_Module32First, kernel32, 'Module32First');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Module32First]
  end;
end;
{$ELSE}
function Module32First; external kernel32 name 'Module32First';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _Module32Next: Pointer;

function Module32Next;
begin
  GetProcedureAddress(_Module32Next, kernel32, 'Module32Next');
  asm
    mov esp, ebp
    pop ebp
    jmp [_Module32Next]
  end;
end;
{$ELSE}
function Module32Next; external kernel32 name 'Module32Next';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
