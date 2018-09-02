{******************************************************************************}
{                                                       	               }
{ Performance Monitoring Installer API interface Unit for Object Pascal        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: loadperf.h, released June 2000. The original Pascal    }
{ code is: LoadPerf.pas, released December 2000. The initial developer of the  }
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

unit JwaLoadPerf;

interface

uses
  JwaWinType;

// flags for dwFlags Argument

const
  LOADPERF_FLAGS_DELETE_MOF_ON_EXIT  = ULONG_PTR(1);
  {$EXTERNALSYM LOADPERF_FLAGS_DELETE_MOF_ON_EXIT}
  LOADPERF_FLAGS_LOAD_REGISTRY_ONLY  = ULONG_PTR(2);
  {$EXTERNALSYM LOADPERF_FLAGS_LOAD_REGISTRY_ONLY}
  LOADPERF_FLAGS_CREATE_MOF_ONLY     = ULONG_PTR(4);
  {$EXTERNALSYM LOADPERF_FLAGS_CREATE_MOF_ONLY}
  LOADPERF_FLAGS_DISPLAY_USER_MSGS   = ULONG_PTR(8);
  {$EXTERNALSYM LOADPERF_FLAGS_DISPLAY_USER_MSGS}

(* removed PSDK XP SP1
// note: LOADPERF_FLAGS_LOAD_REGISTRY_ONLY is not a valid flag for
// LoadMofFromInstalledServiceA/W as the service must already be installed

function LoadMofFromInstalledServiceA(szServiceName, szMofFilename: LPCSTR;
  dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM LoadMofFromInstalledServiceA}
function LoadMofFromInstalledServiceW(szServiceName, szMofFilename: LPCWSTR;
  dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM LoadMofFromInstalledServiceW}

{$IFDEF UNICODE}
function LoadMofFromInstalledService(szServiceName, szMofFilename: LPCWSTR;
  dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM LoadMofFromInstalledService}
{$ELSE}
function LoadMofFromInstalledService(szServiceName, szMofFilename: LPCSTR;
  dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM LoadMofFromInstalledService}
{$ENDIF}
*)

function InstallPerfDllA(szComputerName, lpIniFile: LPCSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM InstallPerfDllA}
function InstallPerfDllW(szComputerName, lpIniFile: LPCWSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM InstallPerfDllW}

{$IFDEF UNICODE}
function InstallPerfDll(szComputerName, lpIniFile: LPCWSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM InstallPerfDll}
{$ELSE}
function InstallPerfDll(szComputerName, lpIniFile: LPCSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM InstallPerfDll}
{$ENDIF}

function LoadPerfCounterTextStringsA(lpCommandLine: LPSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM LoadPerfCounterTextStringsA}
function LoadPerfCounterTextStringsW(lpCommandLine: LPWSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM LoadPerfCounterTextStringsW}

{$IFDEF UNICODE}
function LoadPerfCounterTextStrings(lpCommandLine: LPWSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM LoadPerfCounterTextStrings}
{$ELSE}
function LoadPerfCounterTextStrings(lpCommandLine: LPSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM LoadPerfCounterTextStrings}
{$ENDIF}

function UnloadPerfCounterTextStringsA(lpCommandLine: LPSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM UnloadPerfCounterTextStringsA}
function UnloadPerfCounterTextStringsW(lpCommandLine: LPWSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM UnloadPerfCounterTextStringsW}

{$IFDEF UNICODE}
function UnloadPerfCounterTextStrings(lpCommandLine: LPWSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM UnloadPerfCounterTextStrings}
{$ELSE}
function UnloadPerfCounterTextStrings(lpCommandLine: LPSTR; bQuietModeArg: BOOL): DWORD; stdcall;
{$EXTERNALSYM UnloadPerfCounterTextStrings}
{$ENDIF}

function UpdatePerfNameFilesA(szNewCtrFilePath, szNewHlpFilePath: LPCSTR;
  szLanguageID: LPSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM UpdatePerfNameFilesA}
function UpdatePerfNameFilesW(szNewCtrFilePath, szNewHlpFilePath: LPCWSTR;
  szLanguageID: LPWSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM UpdatePerfNameFilesW}

{$IFDEF UNICODE}
function UpdatePerfNameFiles(szNewCtrFilePath, szNewHlpFilePath: LPCWSTR;
  szLanguageID: LPWSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM UpdatePerfNameFiles}
{$ELSE}
function UpdatePerfNameFiles(szNewCtrFilePath, szNewHlpFilePath: LPCSTR;
  szLanguageID: LPSTR; dwFlags: ULONG_PTR): DWORD; stdcall;
{$EXTERNALSYM UpdatePerfNameFiles}
{$ENDIF}

function SetServiceAsTrustedA(szReserved, szServiceName: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM SetServiceAsTrustedA}
function SetServiceAsTrustedW(szReserved, szServiceName: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM SetServiceAsTrustedW}

{$IFDEF UNICODE}
function SetServiceAsTrusted(szReserved, szServiceName: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM SetServiceAsTrusted}
{$ELSE}
function SetServiceAsTrusted(szReserved, szServiceName: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM SetServiceAsTrusted}
{$ENDIF}

function BackupPerfRegistryToFileW(szFileName: LPCWSTR; szCommentString: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM BackupPerfRegistryToFileW}

function RestorePerfRegistryFromFileW(szFileName: LPCWSTR; szLangId: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM RestorePerfRegistryFromFileW}

implementation

const
  loadperflib = 'loadperf.dll';

{$IFDEF DYNAMIC_LINK}
var
  _InstallPerfDllA: Pointer;

function InstallPerfDllA;
begin
  GetProcedureAddress(_InstallPerfDllA, loadperflib, 'InstallPerfDllA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InstallPerfDllA]
  end;
end;
{$ELSE}
function InstallPerfDllA; external loadperflib name 'InstallPerfDllA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _InstallPerfDllW: Pointer;

function InstallPerfDllW;
begin
  GetProcedureAddress(_InstallPerfDllW, loadperflib, 'InstallPerfDllW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InstallPerfDllW]
  end;
end;
{$ELSE}
function InstallPerfDllW; external loadperflib name 'InstallPerfDllW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _InstallPerfDll: Pointer;

function InstallPerfDll;
begin
  GetProcedureAddress(_InstallPerfDll, loadperflib, 'InstallPerfDllW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InstallPerfDll]
  end;
end;
{$ELSE}
function InstallPerfDll; external loadperflib name 'InstallPerfDllW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _InstallPerfDll: Pointer;

function InstallPerfDll;
begin
  GetProcedureAddress(_InstallPerfDll, loadperflib, 'InstallPerfDllA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_InstallPerfDll]
  end;
end;
{$ELSE}
function InstallPerfDll; external loadperflib name 'InstallPerfDllA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _LoadPerfCounterTextStringsA: Pointer;

function LoadPerfCounterTextStringsA;
begin
  GetProcedureAddress(_LoadPerfCounterTextStringsA, loadperflib, 'LoadPerfCounterTextStringsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadPerfCounterTextStringsA]
  end;
end;
{$ELSE}
function LoadPerfCounterTextStringsA; external loadperflib name 'LoadPerfCounterTextStringsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LoadPerfCounterTextStringsW: Pointer;

function LoadPerfCounterTextStringsW;
begin
  GetProcedureAddress(_LoadPerfCounterTextStringsW, loadperflib, 'LoadPerfCounterTextStringsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadPerfCounterTextStringsW]
  end;
end;
{$ELSE}
function LoadPerfCounterTextStringsW; external loadperflib name 'LoadPerfCounterTextStringsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _LoadPerfCounterTextStrings: Pointer;

function LoadPerfCounterTextStrings;
begin
  GetProcedureAddress(_LoadPerfCounterTextStrings, loadperflib, 'LoadPerfCounterTextStringsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadPerfCounterTextStrings]
  end;
end;
{$ELSE}
function LoadPerfCounterTextStrings; external loadperflib name 'LoadPerfCounterTextStringsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _LoadPerfCounterTextStrings: Pointer;

function LoadPerfCounterTextStrings;
begin
  GetProcedureAddress(_LoadPerfCounterTextStrings, loadperflib, 'LoadPerfCounterTextStringsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadPerfCounterTextStrings]
  end;
end;
{$ELSE}
function LoadPerfCounterTextStrings; external loadperflib name 'LoadPerfCounterTextStringsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _UnloadPerfCounterTextStringsA: Pointer;

function UnloadPerfCounterTextStringsA;
begin
  GetProcedureAddress(_UnloadPerfCounterTextStringsA, loadperflib, 'UnloadPerfCounterTextStringsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnloadPerfCounterTextStringsA]
  end;
end;
{$ELSE}
function UnloadPerfCounterTextStringsA; external loadperflib name 'UnloadPerfCounterTextStringsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnloadPerfCounterTextStringsW: Pointer;

function UnloadPerfCounterTextStringsW;
begin
  GetProcedureAddress(_UnloadPerfCounterTextStringsW, loadperflib, 'UnloadPerfCounterTextStringsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnloadPerfCounterTextStringsW]
  end;
end;
{$ELSE}
function UnloadPerfCounterTextStringsW; external loadperflib name 'UnloadPerfCounterTextStringsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _UnloadPerfCounterTextStrings: Pointer;

function UnloadPerfCounterTextStrings;
begin
  GetProcedureAddress(_UnloadPerfCounterTextStrings, loadperflib, 'UnloadPerfCounterTextStringsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnloadPerfCounterTextStrings]
  end;
end;
{$ELSE}
function UnloadPerfCounterTextStrings; external loadperflib name 'UnloadPerfCounterTextStringsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _UnloadPerfCounterTextStrings: Pointer;

function UnloadPerfCounterTextStrings;
begin
  GetProcedureAddress(_UnloadPerfCounterTextStrings, loadperflib, 'UnloadPerfCounterTextStringsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnloadPerfCounterTextStrings]
  end;
end;
{$ELSE}
function UnloadPerfCounterTextStrings; external loadperflib name 'UnloadPerfCounterTextStringsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _UpdatePerfNameFilesA: Pointer;

function UpdatePerfNameFilesA;
begin
  GetProcedureAddress(_UpdatePerfNameFilesA, loadperflib, 'UpdatePerfNameFilesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UpdatePerfNameFilesA]
  end;
end;
{$ELSE}
function UpdatePerfNameFilesA; external loadperflib name 'UpdatePerfNameFilesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UpdatePerfNameFilesW: Pointer;

function UpdatePerfNameFilesW;
begin
  GetProcedureAddress(_UpdatePerfNameFilesW, loadperflib, 'UpdatePerfNameFilesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UpdatePerfNameFilesW]
  end;
end;
{$ELSE}
function UpdatePerfNameFilesW; external loadperflib name 'UpdatePerfNameFilesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _UpdatePerfNameFiles: Pointer;

function UpdatePerfNameFiles;
begin
  GetProcedureAddress(_UpdatePerfNameFiles, loadperflib, 'UpdatePerfNameFilesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UpdatePerfNameFiles]
  end;
end;
{$ELSE}
function UpdatePerfNameFiles; external loadperflib name 'UpdatePerfNameFilesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _UpdatePerfNameFiles: Pointer;

function UpdatePerfNameFiles;
begin
  GetProcedureAddress(_UpdatePerfNameFiles, loadperflib, 'UpdatePerfNameFilesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UpdatePerfNameFiles]
  end;
end;
{$ELSE}
function UpdatePerfNameFiles; external loadperflib name 'UpdatePerfNameFilesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceAsTrustedA: Pointer;

function SetServiceAsTrustedA;
begin
  GetProcedureAddress(_SetServiceAsTrustedA, loadperflib, 'SetServiceAsTrustedA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceAsTrustedA]
  end;
end;
{$ELSE}
function SetServiceAsTrustedA; external loadperflib name 'SetServiceAsTrustedA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceAsTrustedW: Pointer;

function SetServiceAsTrustedW;
begin
  GetProcedureAddress(_SetServiceAsTrustedW, loadperflib, 'SetServiceAsTrustedW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceAsTrustedW]
  end;
end;
{$ELSE}
function SetServiceAsTrustedW; external loadperflib name 'SetServiceAsTrustedW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceAsTrusted: Pointer;

function SetServiceAsTrusted;
begin
  GetProcedureAddress(_SetServiceAsTrusted, loadperflib, 'SetServiceAsTrustedW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceAsTrusted]
  end;
end;
{$ELSE}
function SetServiceAsTrusted; external loadperflib name 'SetServiceAsTrustedW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceAsTrusted: Pointer;

function SetServiceAsTrusted;
begin
  GetProcedureAddress(_SetServiceAsTrusted, loadperflib, 'SetServiceAsTrustedA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceAsTrusted]
  end;
end;
{$ELSE}
function SetServiceAsTrusted; external loadperflib name 'SetServiceAsTrustedA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _BackupPerfRegistryToFileW: Pointer;

function BackupPerfRegistryToFileW;
begin
  GetProcedureAddress(_BackupPerfRegistryToFileW, loadperflib, 'BackupPerfRegistryToFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BackupPerfRegistryToFileW]
  end;
end;
{$ELSE}
function BackupPerfRegistryToFileW; external loadperflib name 'BackupPerfRegistryToFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RestorePerfRegistryFromFileW: Pointer;

function RestorePerfRegistryFromFileW;
begin
  GetProcedureAddress(_RestorePerfRegistryFromFileW, loadperflib, 'RestorePerfRegistryFromFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RestorePerfRegistryFromFileW]
  end;
end;
{$ELSE}
function RestorePerfRegistryFromFileW; external loadperflib name 'RestorePerfRegistryFromFileW';
{$ENDIF DYNAMIC_LINK}

end.
