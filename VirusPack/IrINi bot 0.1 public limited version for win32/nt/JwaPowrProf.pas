{******************************************************************************}
{                                                       	               }
{ Power Policy Applicator interface Unit for Object Pascal                     }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: powrprof.h, released June 2000. The original Pascal    }
{ code is: PowrProf.pas, released August 2001. The initial developer of the    }
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

unit JwaPowrProf;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "powrprof.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

// Registry storage structures for the GLOBAL_POWER_POLICY data. There are two
// structures, GLOBAL_MACHINE_POWER_POLICY and GLOBAL_USER_POWER_POLICY. the
// GLOBAL_MACHINE_POWER_POLICY stores per machine data for which there is no UI.
// GLOBAL_USER_POWER_POLICY stores the per user data.

type
  PGLOBAL_MACHINE_POWER_POLICY = ^GLOBAL_MACHINE_POWER_POLICY;
  {$EXTERNALSYM PGLOBAL_MACHINE_POWER_POLICY}
  _GLOBAL_MACHINE_POWER_POLICY = record
    Revision: ULONG;
    LidOpenWakeAc: SYSTEM_POWER_STATE;
    LidOpenWakeDc: SYSTEM_POWER_STATE;
    BroadcastCapacityResolution: ULONG;
  end;
  {$EXTERNALSYM _GLOBAL_MACHINE_POWER_POLICY}
  GLOBAL_MACHINE_POWER_POLICY = _GLOBAL_MACHINE_POWER_POLICY;
  {$EXTERNALSYM GLOBAL_MACHINE_POWER_POLICY}
  TGlobalMachinePowerPolicy = GLOBAL_MACHINE_POWER_POLICY;
  PGlobalMachinePowerPolicy = PGLOBAL_MACHINE_POWER_POLICY;

  PGLOBAL_USER_POWER_POLICY = ^GLOBAL_USER_POWER_POLICY;
  {$EXTERNALSYM PGLOBAL_USER_POWER_POLICY}
  _GLOBAL_USER_POWER_POLICY = record
    Revision: ULONG;
    PowerButtonAc: POWER_ACTION_POLICY;
    PowerButtonDc: POWER_ACTION_POLICY;
    SleepButtonAc: POWER_ACTION_POLICY;
    SleepButtonDc: POWER_ACTION_POLICY;
    LidCloseAc: POWER_ACTION_POLICY;
    LidCloseDc: POWER_ACTION_POLICY;
    DischargePolicy: array [0..NUM_DISCHARGE_POLICIES - 1] of SYSTEM_POWER_LEVEL;
    GlobalFlags: ULONG;
  end;
  {$EXTERNALSYM _GLOBAL_USER_POWER_POLICY}
  GLOBAL_USER_POWER_POLICY = _GLOBAL_USER_POWER_POLICY;
  {$EXTERNALSYM GLOBAL_USER_POWER_POLICY}
  TGlobalUserPowerPolicy = GLOBAL_USER_POWER_POLICY;
  PGlobalUserPowerPolicy = PGLOBAL_USER_POWER_POLICY;

// Structure to manage global power policies at the user level. This structure
// contains data which is common across all power policy profiles.

  PGLOBAL_POWER_POLICY = ^GLOBAL_POWER_POLICY;
  {$EXTERNALSYM PGLOBAL_POWER_POLICY}
  _GLOBAL_POWER_POLICY = record
    user: GLOBAL_USER_POWER_POLICY;
    mach: GLOBAL_MACHINE_POWER_POLICY;
  end;
  {$EXTERNALSYM _GLOBAL_POWER_POLICY}
  GLOBAL_POWER_POLICY = _GLOBAL_POWER_POLICY;
  {$EXTERNALSYM GLOBAL_POWER_POLICY}
  TGlobalPowerPolicy = GLOBAL_POWER_POLICY;
  PGlobalPowerPolicy = PGLOBAL_POWER_POLICY;

// Registry storage structures for the POWER_POLICY data. There are three
// structures, MACHINE_POWER_POLICY, MACHINE_PROCESSOR_POWER_POLICY and USER_POWER_POLICY. the
// MACHINE_POWER_POLICY stores per machine data for which there is no UI.
// USER_POWER_POLICY stores the per user data.

  PMACHINE_POWER_POLICY = ^MACHINE_POWER_POLICY;
  {$EXTERNALSYM PMACHINE_POWER_POLICY}
  _MACHINE_POWER_POLICY = record
    Revision: ULONG; // 1
    // meaning of power action "sleep"
    MinSleepAc: SYSTEM_POWER_STATE;
    MinSleepDc: SYSTEM_POWER_STATE;
    ReducedLatencySleepAc: SYSTEM_POWER_STATE;
    ReducedLatencySleepDc: SYSTEM_POWER_STATE;
    // parameters for dozing
    DozeTimeoutAc: ULONG;
    DozeTimeoutDc: ULONG;
    DozeS4TimeoutAc: ULONG;
    DozeS4TimeoutDc: ULONG;
    // processor policies
    MinThrottleAc: UCHAR;
    MinThrottleDc: UCHAR;
    pad1: array [0..1] of UCHAR;
    OverThrottledAc: POWER_ACTION_POLICY;
    OverThrottledDc: POWER_ACTION_POLICY;
  end;
  {$EXTERNALSYM _MACHINE_POWER_POLICY}
  MACHINE_POWER_POLICY = _MACHINE_POWER_POLICY;
  {$EXTERNALSYM MACHINE_POWER_POLICY}
  TMachinePowerPolicy = MACHINE_POWER_POLICY;
  PMachinePowerPolicy = PMACHINE_POWER_POLICY;

  PMACHINE_PROCESSOR_POWER_POLICY = ^MACHINE_PROCESSOR_POWER_POLICY;
  {$EXTERNALSYM PMACHINE_PROCESSOR_POWER_POLICY}
  _MACHINE_PROCESSOR_POWER_POLICY = record
    Revision: ULONG; // 1
    ProcessorPolicyAc: PROCESSOR_POWER_POLICY;
    ProcessorPolicyDc: PROCESSOR_POWER_POLICY;
  end;
  {$EXTERNALSYM _MACHINE_PROCESSOR_POWER_POLICY}
  MACHINE_PROCESSOR_POWER_POLICY = _MACHINE_PROCESSOR_POWER_POLICY;
  {$EXTERNALSYM MACHINE_PROCESSOR_POWER_POLICY}
  TMachineProcessorPowerPolicy = MACHINE_PROCESSOR_POWER_POLICY;
  PMachineProcessorPowerPolicy = PMACHINE_PROCESSOR_POWER_POLICY;

  PUSER_POWER_POLICY = ^USER_POWER_POLICY;
  {$EXTERNALSYM PUSER_POWER_POLICY}
  _USER_POWER_POLICY = record
    Revision: ULONG; // 1
    // "system idle" detection
    IdleAc: POWER_ACTION_POLICY;
    IdleDc: POWER_ACTION_POLICY;
    IdleTimeoutAc: ULONG;
    IdleTimeoutDc: ULONG;
    IdleSensitivityAc: UCHAR;
    IdleSensitivityDc: UCHAR;
    // Throttling Policy
    ThrottlePolicyAc: UCHAR;
    ThrottlePolicyDc: UCHAR;
    // meaning of power action "sleep"
    MaxSleepAc: SYSTEM_POWER_STATE;
    MaxSleepDc: SYSTEM_POWER_STATE;
    // For future use
    Reserved: array [0..1] of ULONG;
    // video policies
    VideoTimeoutAc: ULONG;
    VideoTimeoutDc: ULONG;
    // hard disk policies
    SpindownTimeoutAc: ULONG;
    SpindownTimeoutDc: ULONG;
    // processor policies
    OptimizeForPowerAc: BOOLEAN;
    OptimizeForPowerDc: BOOLEAN;
    FanThrottleToleranceAc: UCHAR;
    FanThrottleToleranceDc: UCHAR;
    ForcedThrottleAc: UCHAR;
    ForcedThrottleDc: UCHAR;
  end;
  {$EXTERNALSYM _USER_POWER_POLICY}
  USER_POWER_POLICY = _USER_POWER_POLICY;
  {$EXTERNALSYM USER_POWER_POLICY}
  TUserPowerPolicy = USER_POWER_POLICY;
  PUserPowerPolicy = PUSER_POWER_POLICY;

// Structure to manage power policies at the user level. This structure
// contains data which is unique across power policy profiles.

  PPOWER_POLICY = ^POWER_POLICY;
  {$EXTERNALSYM PPOWER_POLICY}
  _POWER_POLICY = record
    user: USER_POWER_POLICY;
    mach: MACHINE_POWER_POLICY;
  end;
  {$EXTERNALSYM _POWER_POLICY}
  POWER_POLICY = _POWER_POLICY;
  {$EXTERNALSYM POWER_POLICY}
  TPowerPolicy = POWER_POLICY;
  PPowerPolicy = PPOWER_POLICY;

// Constants for GlobalFlags

const
  EnableSysTrayBatteryMeter = $01;
  {$EXTERNALSYM EnableSysTrayBatteryMeter}
  EnableMultiBatteryDisplay = $02;
  {$EXTERNALSYM EnableMultiBatteryDisplay}
  EnablePasswordLogon       = $04;
  {$EXTERNALSYM EnablePasswordLogon}
  EnableWakeOnRing          = $08;
  {$EXTERNALSYM EnableWakeOnRing}
  EnableVideoDimDisplay     = $10;
  {$EXTERNALSYM EnableVideoDimDisplay}

// This constant is passed as a uiID to WritePwrScheme.

  NEWSCHEME = UINT(-1);
  {$EXTERNALSYM NEWSCHEME}

// Prototype for EnumPwrSchemes callback proceedures.

// TODO REPLACE BOOLEAN WITH ...

type
  PWRSCHEMESENUMPROC = function (uiIndex: UINT; dwName: DWORD; sName: LPTSTR; dwDesc: DWORD; sDesc: LPTSTR; pp: PPOWER_POLICY; lParam: LPARAM): BOOLEAN; stdcall;
  {$EXTERNALSYM PWRSCHEMESENUMPROC}
  PFNNTINITIATEPWRACTION = function (pPowerAction: POWER_ACTION; SystemPowerState: SYSTEM_POWER_STATE; u: ULONG; b: BOOLEAN): BOOLEAN; stdcall;
  {$EXTERNALSYM PFNNTINITIATEPWRACTION}

// Public function prototypes

function GetPwrDiskSpindownRange(var RangeMax, RangeMin: UINT): BOOLEAN; stdcall;
{$EXTERNALSYM GetPwrDiskSpindownRange}
function EnumPwrSchemes(lpfnPwrSchemesEnumProc: PWRSCHEMESENUMPROC; lParam: LPARAM): BOOLEAN; stdcall;
{$EXTERNALSYM EnumPwrSchemes}
function ReadGlobalPwrPolicy(var pGlobalPowerPolicy: GLOBAL_POWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM ReadGlobalPwrPolicy}
function ReadPwrScheme(uiID: UINT; var pPowerPolicy: POWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM ReadPwrScheme}
function WritePwrScheme(puiID: PUINT; lpszName, lpszDescription: LPTSTR; const pPowerPolicy: POWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM WritePwrScheme}
function WriteGlobalPwrPolicy(const pGlobalPowerPolicy: GLOBAL_POWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM WriteGlobalPwrPolicy}
function DeletePwrScheme(uiIndex: UINT): BOOLEAN; stdcall;
{$EXTERNALSYM DeletePwrScheme}
function GetActivePwrScheme(var puiID: UINT): BOOLEAN; stdcall;
{$EXTERNALSYM GetActivePwrScheme}
function SetActivePwrScheme(uiID: UINT; pGlobalPowerPolicy: PGLOBAL_POWER_POLICY; pPowerPolicy: PPOWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM SetActivePwrScheme}
function GetPwrCapabilities(var lpSystemPowerCapabilities: SYSTEM_POWER_CAPABILITIES): BOOLEAN; stdcall;
{$EXTERNALSYM GetPwrCapabilities}
function IsPwrSuspendAllowed: BOOLEAN; stdcall;
{$EXTERNALSYM IsPwrSuspendAllowed}
function IsPwrHibernateAllowed: BOOLEAN; stdcall;
{$EXTERNALSYM IsPwrHibernateAllowed}
function IsPwrShutdownAllowed: BOOLEAN; stdcall;
{$EXTERNALSYM IsPwrShutdownAllowed}
function IsAdminOverrideActive(pAdministratorPowerPolicy: PADMINISTRATOR_POWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM IsAdminOverrideActive}
function SetSuspendState(Hibernate, ForceCritical, DisableWakeEvent: BOOLEAN): BOOLEAN; stdcall;
{$EXTERNALSYM SetSuspendState}
function GetCurrentPowerPolicies(pGlobalPowerPolicy: PGLOBAL_POWER_POLICY; pPowerPolicy: PPOWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM GetCurrentPowerPolicies}
function CanUserWritePwrScheme: BOOLEAN; stdcall;
{$EXTERNALSYM CanUserWritePwrScheme}
function ReadProcessorPwrScheme(uiID: UINT; var pMachineProcessorPowerPolicy: MACHINE_PROCESSOR_POWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM ReadProcessorPwrScheme}
function WriteProcessorPwrScheme(uiID: UINT; const pMachineProcessorPowerPolicy: MACHINE_PROCESSOR_POWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM WriteProcessorPwrScheme}
function ValidatePowerPolicies(GlobalPolicy: PGLOBAL_POWER_POLICY; Policy: PPOWER_POLICY): BOOLEAN; stdcall;
{$EXTERNALSYM ValidatePowerPolicies}

function CallNtPowerInformation(InformationLeveL: POWER_INFORMATION_LEVEL; lpInputBuffer: PVOID; nInputBufferSize: ULONG; lpOutputBuffer: PVOID; nOutputBufferSize: ULONG): NTSTATUS; stdcall;
{$EXTERNALSYM CallNtPowerInformation}

implementation

uses
  SysUtils;

const
  powrprof_lib = 'powrprof.dll';

{$IFDEF DYNAMIC_LINK}
var
  _GetPwrDiskSpindownRange: Pointer;

function GetPwrDiskSpindownRange;
begin
  GetProcedureAddress(_GetPwrDiskSpindownRange, powrprof_lib, 'GetPwrDiskSpindownRange');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetPwrDiskSpindownRange]
  end;
end;
{$ELSE}
function GetPwrDiskSpindownRange; external powrprof_lib name 'GetPwrDiskSpindownRange';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumPwrSchemes: Pointer;

function EnumPwrSchemes;
begin
  GetProcedureAddress(_EnumPwrSchemes, powrprof_lib, 'EnumPwrSchemes');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumPwrSchemes]
  end;
end;
{$ELSE}
function EnumPwrSchemes; external powrprof_lib name 'EnumPwrSchemes';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReadGlobalPwrPolicy: Pointer;

function ReadGlobalPwrPolicy;
begin
  GetProcedureAddress(_ReadGlobalPwrPolicy, powrprof_lib, 'ReadGlobalPwrPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReadGlobalPwrPolicy]
  end;
end;
{$ELSE}
function ReadGlobalPwrPolicy; external powrprof_lib name 'ReadGlobalPwrPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReadPwrScheme: Pointer;

function ReadPwrScheme;
begin
  GetProcedureAddress(_ReadPwrScheme, powrprof_lib, 'ReadPwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReadPwrScheme]
  end;
end;
{$ELSE}
function ReadPwrScheme; external powrprof_lib name 'ReadPwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WritePwrScheme: Pointer;

function WritePwrScheme;
begin
  GetProcedureAddress(_WritePwrScheme, powrprof_lib, 'WritePwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WritePwrScheme]
  end;
end;
{$ELSE}
function WritePwrScheme; external powrprof_lib name 'WritePwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WriteGlobalPwrPolicy: Pointer;

function WriteGlobalPwrPolicy;
begin
  GetProcedureAddress(_WriteGlobalPwrPolicy, powrprof_lib, 'WriteGlobalPwrPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WriteGlobalPwrPolicy]
  end;
end;
{$ELSE}
function WriteGlobalPwrPolicy; external powrprof_lib name 'WriteGlobalPwrPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DeletePwrScheme: Pointer;

function DeletePwrScheme;
begin
  GetProcedureAddress(_DeletePwrScheme, powrprof_lib, 'DeletePwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeletePwrScheme]
  end;
end;
{$ELSE}
function DeletePwrScheme; external powrprof_lib name 'DeletePwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetActivePwrScheme: Pointer;

function GetActivePwrScheme;
begin
  GetProcedureAddress(_GetActivePwrScheme, powrprof_lib, 'GetActivePwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetActivePwrScheme]
  end;
end;
{$ELSE}
function GetActivePwrScheme; external powrprof_lib name 'GetActivePwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetActivePwrScheme: Pointer;

function SetActivePwrScheme;
begin
  GetProcedureAddress(_SetActivePwrScheme, powrprof_lib, 'SetActivePwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetActivePwrScheme]
  end;
end;
{$ELSE}
function SetActivePwrScheme; external powrprof_lib name 'SetActivePwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetPwrCapabilities: Pointer;

function GetPwrCapabilities;
begin
  GetProcedureAddress(_GetPwrCapabilities, powrprof_lib, 'GetPwrCapabilities');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetPwrCapabilities]
  end;
end;
{$ELSE}
function GetPwrCapabilities; external powrprof_lib name 'GetPwrCapabilities';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsPwrSuspendAllowed: Pointer;

function IsPwrSuspendAllowed;
begin
  GetProcedureAddress(_IsPwrSuspendAllowed, powrprof_lib, 'IsPwrSuspendAllowed');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsPwrSuspendAllowed]
  end;
end;
{$ELSE}
function IsPwrSuspendAllowed; external powrprof_lib name 'IsPwrSuspendAllowed';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsPwrHibernateAllowed: Pointer;

function IsPwrHibernateAllowed;
begin
  GetProcedureAddress(_IsPwrHibernateAllowed, powrprof_lib, 'IsPwrHibernateAllowed');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsPwrHibernateAllowed]
  end;
end;
{$ELSE}
function IsPwrHibernateAllowed; external powrprof_lib name 'IsPwrHibernateAllowed';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsPwrShutdownAllowed: Pointer;

function IsPwrShutdownAllowed;
begin
  GetProcedureAddress(_IsPwrShutdownAllowed, powrprof_lib, 'IsPwrShutdownAllowed');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsPwrShutdownAllowed]
  end;
end;
{$ELSE}
function IsPwrShutdownAllowed; external powrprof_lib name 'IsPwrShutdownAllowed';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _IsAdminOverrideActive: Pointer;

function IsAdminOverrideActive;
begin
  GetProcedureAddress(_IsAdminOverrideActive, powrprof_lib, 'IsAdminOverrideActive');
  asm
    mov esp, ebp
    pop ebp
    jmp [_IsAdminOverrideActive]
  end;
end;
{$ELSE}
function IsAdminOverrideActive; external powrprof_lib name 'IsAdminOverrideActive';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetSuspendState: Pointer;

function SetSuspendState;
begin
  GetProcedureAddress(_SetSuspendState, powrprof_lib, 'SetSuspendState');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetSuspendState]
  end;
end;
{$ELSE}
function SetSuspendState; external powrprof_lib name 'SetSuspendState';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetCurrentPowerPolicies: Pointer;

function GetCurrentPowerPolicies;
begin
  GetProcedureAddress(_GetCurrentPowerPolicies, powrprof_lib, 'GetCurrentPowerPolicies');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetCurrentPowerPolicies]
  end;
end;
{$ELSE}
function GetCurrentPowerPolicies; external powrprof_lib name 'GetCurrentPowerPolicies';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CanUserWritePwrScheme: Pointer;

function CanUserWritePwrScheme;
begin
  GetProcedureAddress(_CanUserWritePwrScheme, powrprof_lib, 'CanUserWritePwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CanUserWritePwrScheme]
  end;
end;
{$ELSE}
function CanUserWritePwrScheme; external powrprof_lib name 'CanUserWritePwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReadProcessorPwrScheme: Pointer;

function ReadProcessorPwrScheme;
begin
  GetProcedureAddress(_ReadProcessorPwrScheme, powrprof_lib, 'ReadProcessorPwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReadProcessorPwrScheme]
  end;
end;
{$ELSE}
function ReadProcessorPwrScheme; external powrprof_lib name 'ReadProcessorPwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WriteProcessorPwrScheme: Pointer;

function WriteProcessorPwrScheme;
begin
  GetProcedureAddress(_WriteProcessorPwrScheme, powrprof_lib, 'WriteProcessorPwrScheme');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WriteProcessorPwrScheme]
  end;
end;
{$ELSE}
function WriteProcessorPwrScheme; external powrprof_lib name 'WriteProcessorPwrScheme';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ValidatePowerPolicies: Pointer;

function ValidatePowerPolicies;
begin
  GetProcedureAddress(_ValidatePowerPolicies, powrprof_lib, 'ValidatePowerPolicies');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ValidatePowerPolicies]
  end;
end;
{$ELSE}
function ValidatePowerPolicies; external powrprof_lib name 'ValidatePowerPolicies';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CallNtPowerInformation: Pointer;

function CallNtPowerInformation;
begin
  GetProcedureAddress(_CallNtPowerInformation, powrprof_lib, 'CallNtPowerInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CallNtPowerInformation]
  end;
end;
{$ELSE}
function CallNtPowerInformation; external powrprof_lib name 'CallNtPowerInformation';
{$ENDIF DYNAMIC_LINK}

end.
