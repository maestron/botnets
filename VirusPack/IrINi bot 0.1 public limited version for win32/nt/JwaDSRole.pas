{******************************************************************************}
{                                                       	               }
{ Directory Services API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dsrole.h, released June 2000. The original Pascal      }
{ code is: DsRole.pas, released December 2000. The initial developer of the    }
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

unit JwaDSRole;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dsrole.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
// Domain information
//

type
  _DSROLE_MACHINE_ROLE = (
    DsRole_RoleStandaloneWorkstation,
    DsRole_RoleMemberWorkstation,
    DsRole_RoleStandaloneServer,
    DsRole_RoleMemberServer,
    DsRole_RoleBackupDomainController,
    DsRole_RolePrimaryDomainController);
  {$EXTERNALSYM _DSROLE_MACHINE_ROLE}
  DSROLE_MACHINE_ROLE = _DSROLE_MACHINE_ROLE;
  {$EXTERNALSYM DSROLE_MACHINE_ROLE}
  TDsRoleMachineRole = DSROLE_MACHINE_ROLE;

//
// Previous server state
//

  _DSROLE_SERVER_STATE = (
    DsRoleServerUnknown,
    DsRoleServerPrimary,
    DsRoleServerBackup);
  {$EXTERNALSYM DSROLE_SERVER_STATE}
  DSROLE_SERVER_STATE = _DSROLE_SERVER_STATE;
  {$EXTERNALSYM DSROLE_SERVER_STATE}
  PDSROLE_SERVER_STATE = ^DSROLE_SERVER_STATE;
  {$EXTERNALSYM PDSROLE_SERVER_STATE}
  TDsRoleServerState = DSROLE_SERVER_STATE;

  _DSROLE_PRIMARY_DOMAIN_INFO_LEVEL = (
    DsRoleFiller0,
    DsRolePrimaryDomainInfoBasic,
    DsRoleUpgradeStatus,
    DsRoleOperationState);
  {$EXTERNALSYM _DSROLE_PRIMARY_DOMAIN_INFO_LEVEL}
  DSROLE_PRIMARY_DOMAIN_INFO_LEVEL = _DSROLE_PRIMARY_DOMAIN_INFO_LEVEL;
  {$EXTERNALSYM DSROLE_PRIMARY_DOMAIN_INFO_LEVEL}
  TDsRolePrimaryDomainInfoLevel = DSROLE_PRIMARY_DOMAIN_INFO_LEVEL;

//
// Flags to be used with the PRIMARY_DOMAIN_INFO_LEVEL structures below
//

const
  DSROLE_PRIMARY_DS_RUNNING          = $00000001;
  {$EXTERNALSYM DSROLE_PRIMARY_DS_RUNNING}
  DSROLE_PRIMARY_DS_MIXED_MODE       = $00000002;
  {$EXTERNALSYM DSROLE_PRIMARY_DS_MIXED_MODE}
  DSROLE_UPGRADE_IN_PROGRESS         = $00000004;
  {$EXTERNALSYM DSROLE_UPGRADE_IN_PROGRESS}
  DSROLE_PRIMARY_DOMAIN_GUID_PRESENT = $01000000;
  {$EXTERNALSYM DSROLE_PRIMARY_DOMAIN_GUID_PRESENT}

//
// Structure that correspond to the DSROLE_PRIMARY_DOMAIN_INFO_LEVEL
//

type
  PDSROLE_PRIMARY_DOMAIN_INFO_BASIC = ^DSROLE_PRIMARY_DOMAIN_INFO_BASIC;
  {$EXTERNALSYM PDSROLE_PRIMARY_DOMAIN_INFO_BASIC}
  _DSROLE_PRIMARY_DOMAIN_INFO_BASIC = record
    MachineRole: DSROLE_MACHINE_ROLE;
    Flags: ULONG;
    DomainNameFlat: LPWSTR;
    DomainNameDns: LPWSTR;
    DomainForestName: LPWSTR;
    DomainGuid: GUID;
  end;
  {$EXTERNALSYM _DSROLE_PRIMARY_DOMAIN_INFO_BASIC}
  DSROLE_PRIMARY_DOMAIN_INFO_BASIC = _DSROLE_PRIMARY_DOMAIN_INFO_BASIC;
  {$EXTERNALSYM DSROLE_PRIMARY_DOMAIN_INFO_BASIC}
  TDsRolePrimaryDomainInfoBasic = DSROLE_PRIMARY_DOMAIN_INFO_BASIC;
  PDsRolePrimaryDomainInfoBasic = PDSROLE_PRIMARY_DOMAIN_INFO_BASIC;

  PDSROLE_UPGRADE_STATUS_INFO = ^DSROLE_UPGRADE_STATUS_INFO;
  {$EXTERNALSYM PDSROLE_UPGRADE_STATUS_INFO}
  _DSROLE_UPGRADE_STATUS_INFO = record
    OperationState: ULONG;
    PreviousServerState: DSROLE_SERVER_STATE;
  end;
  {$EXTERNALSYM _DSROLE_UPGRADE_STATUS_INFO}
  DSROLE_UPGRADE_STATUS_INFO = _DSROLE_UPGRADE_STATUS_INFO;
  {$EXTERNALSYM DSROLE_UPGRADE_STATUS_INFO}
  TDsRoleUpgradeStatusInfo = DSROLE_UPGRADE_STATUS_INFO;
  PDsRoleUpgradeStatusInfo = PDSROLE_UPGRADE_STATUS_INFO;

  _DSROLE_OPERATION_STATE = (
    DsRoleOperationIdle,
    DsRoleOperationActive,
    DsRoleOperationNeedReboot);
  {$EXTERNALSYM _DSROLE_OPERATION_STATE}
  DSROLE_OPERATION_STATE = _DSROLE_OPERATION_STATE;
  {$EXTERNALSYM DSROLE_OPERATION_STATE}
  TDsRoleOperationState = DSROLE_OPERATION_STATE;

  PDSROLE_OPERATION_STATE_INFO = ^DSROLE_OPERATION_STATE_INFO;
  {$EXTERNALSYM PDSROLE_OPERATION_STATE_INFO}
  _DSROLE_OPERATION_STATE_INFO = record
    OperationState: DSROLE_OPERATION_STATE;
  end;
  {$EXTERNALSYM _DSROLE_OPERATION_STATE_INFO}
  DSROLE_OPERATION_STATE_INFO = _DSROLE_OPERATION_STATE_INFO;
  {$EXTERNALSYM DSROLE_OPERATION_STATE_INFO}
  TDsRoleOperationStateInfo = DSROLE_OPERATION_STATE_INFO;
  PDsRoleOperationStateInfo = PDSROLE_OPERATION_STATE_INFO;

function DsRoleGetPrimaryDomainInformation(lpServer: LPCWSTR;
  InfoLevel: DSROLE_PRIMARY_DOMAIN_INFO_LEVEL; var Buffer: PVOID): DWORD; stdcall;
{$EXTERNALSYM DsRoleGetPrimaryDomainInformation}

procedure DsRoleFreeMemory(Buffer: PVOID); stdcall;
{$EXTERNALSYM DsRoleFreeMemory}

implementation

const
  netapi32 = 'netapi32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _DsRoleGetPrimaryDomainInfo: Pointer;

function DsRoleGetPrimaryDomainInformation;
begin
  GetProcedureAddress(_DsRoleGetPrimaryDomainInfo, netapi32, 'DsRoleGetPrimaryDomainInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRoleGetPrimaryDomainInfo]
  end;
end;
{$ELSE}
function DsRoleGetPrimaryDomainInformation; external netapi32 name 'DsRoleGetPrimaryDomainInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DsRoleFreeMemory: Pointer;

procedure DsRoleFreeMemory;
begin
  GetProcedureAddress(_DsRoleFreeMemory, netapi32, 'DsRoleFreeMemory');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DsRoleFreeMemory]
  end;
end;
{$ELSE}
procedure DsRoleFreeMemory; external netapi32 name 'DsRoleFreeMemory';
{$ENDIF DYNAMIC_LINK}

end.
