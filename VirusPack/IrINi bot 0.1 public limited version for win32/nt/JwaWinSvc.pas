{******************************************************************************}
{                                                       	               }
{ Services API interface Unit for Object Pascal                                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winsvc.h, released June 2000. The original Pascal      }
{ code is: WinSvc.pas, released December 2000. The initial developer of the    }
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

unit JwaWinSvc;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinSvc.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

//
// Service database names
//

const
  SERVICES_ACTIVE_DATABASEW = 'ServicesActive';
  {$EXTERNALSYM SERVICES_ACTIVE_DATABASEW}
  SERVICES_FAILED_DATABASEW = 'ServicesFailed';
  {$EXTERNALSYM SERVICES_FAILED_DATABASEW}

  SERVICES_ACTIVE_DATABASEA = 'ServicesActive';
  {$EXTERNALSYM SERVICES_ACTIVE_DATABASEA}
  SERVICES_FAILED_DATABASEA = 'ServicesFailed';
  {$EXTERNALSYM SERVICES_FAILED_DATABASEA}

//
// Character to designate that a name is a group
//

  SC_GROUP_IDENTIFIERW = '+';
  {$EXTERNALSYM SC_GROUP_IDENTIFIERW}
  SC_GROUP_IDENTIFIERA = '+';
  {$EXTERNALSYM SC_GROUP_IDENTIFIERA}

{$IFDEF UNICODE}

  SERVICES_ACTIVE_DATABASE = SERVICES_ACTIVE_DATABASEW;
  {$EXTERNALSYM SERVICES_ACTIVE_DATABASE}
  SERVICES_FAILED_DATABASE = SERVICES_FAILED_DATABASEW;
  {$EXTERNALSYM SERVICES_FAILED_DATABASE}

  SC_GROUP_IDENTIFIER = SC_GROUP_IDENTIFIERW;
  {$EXTERNALSYM SC_GROUP_IDENTIFIER}

{$ELSE}

  SERVICES_ACTIVE_DATABASE = SERVICES_ACTIVE_DATABASEA;
  {$EXTERNALSYM SERVICES_ACTIVE_DATABASE}
  SERVICES_FAILED_DATABASE = SERVICES_FAILED_DATABASEA;
  {$EXTERNALSYM SERVICES_FAILED_DATABASE}

  SC_GROUP_IDENTIFIER = SC_GROUP_IDENTIFIERA;
  {$EXTERNALSYM SC_GROUP_IDENTIFIER}

{$ENDIF}

//
// Value to indicate no change to an optional parameter
//

  SERVICE_NO_CHANGE = $ffffffff;
  {$EXTERNALSYM SERVICE_NO_CHANGE}

//
// Service State -- for Enum Requests (Bit Mask)
//

  SERVICE_ACTIVE    = $00000001;
  {$EXTERNALSYM SERVICE_ACTIVE}
  SERVICE_INACTIVE  = $00000002;
  {$EXTERNALSYM SERVICE_INACTIVE}
  SERVICE_STATE_ALL = SERVICE_ACTIVE or SERVICE_INACTIVE;
  {$EXTERNALSYM SERVICE_STATE_ALL}

//
// Controls
//

  SERVICE_CONTROL_STOP                  = $00000001;
  {$EXTERNALSYM SERVICE_CONTROL_STOP}
  SERVICE_CONTROL_PAUSE                 = $00000002;
  {$EXTERNALSYM SERVICE_CONTROL_PAUSE}
  SERVICE_CONTROL_CONTINUE              = $00000003;
  {$EXTERNALSYM SERVICE_CONTROL_CONTINUE}
  SERVICE_CONTROL_INTERROGATE           = $00000004;
  {$EXTERNALSYM SERVICE_CONTROL_INTERROGATE}
  SERVICE_CONTROL_SHUTDOWN              = $00000005;
  {$EXTERNALSYM SERVICE_CONTROL_SHUTDOWN}
  SERVICE_CONTROL_PARAMCHANGE           = $00000006;
  {$EXTERNALSYM SERVICE_CONTROL_PARAMCHANGE}
  SERVICE_CONTROL_NETBINDADD            = $00000007;
  {$EXTERNALSYM SERVICE_CONTROL_NETBINDADD}
  SERVICE_CONTROL_NETBINDREMOVE         = $00000008;
  {$EXTERNALSYM SERVICE_CONTROL_NETBINDREMOVE}
  SERVICE_CONTROL_NETBINDENABLE         = $00000009;
  {$EXTERNALSYM SERVICE_CONTROL_NETBINDENABLE}
  SERVICE_CONTROL_NETBINDDISABLE        = $0000000A;
  {$EXTERNALSYM SERVICE_CONTROL_NETBINDDISABLE}
  SERVICE_CONTROL_DEVICEEVENT           = $0000000B;
  {$EXTERNALSYM SERVICE_CONTROL_DEVICEEVENT}
  SERVICE_CONTROL_HARDWAREPROFILECHANGE = $0000000C;
  {$EXTERNALSYM SERVICE_CONTROL_HARDWAREPROFILECHANGE}
  SERVICE_CONTROL_POWEREVENT            = $0000000D;
  {$EXTERNALSYM SERVICE_CONTROL_POWEREVENT}
  SERVICE_CONTROL_SESSIONCHANGE         = $0000000E;
  {$EXTERNALSYM SERVICE_CONTROL_SESSIONCHANGE}

//
// Service State -- for CurrentState
//

  SERVICE_STOPPED          = $00000001;
  {$EXTERNALSYM SERVICE_STOPPED}
  SERVICE_START_PENDING    = $00000002;
  {$EXTERNALSYM SERVICE_START_PENDING}
  SERVICE_STOP_PENDING     = $00000003;
  {$EXTERNALSYM SERVICE_STOP_PENDING}
  SERVICE_RUNNING          = $00000004;
  {$EXTERNALSYM SERVICE_RUNNING}
  SERVICE_CONTINUE_PENDING = $00000005;
  {$EXTERNALSYM SERVICE_CONTINUE_PENDING}
  SERVICE_PAUSE_PENDING    = $00000006;
  {$EXTERNALSYM SERVICE_PAUSE_PENDING}
  SERVICE_PAUSED           = $00000007;
  {$EXTERNALSYM SERVICE_PAUSED}

//
// Controls Accepted  (Bit Mask)
//

  SERVICE_ACCEPT_STOP                  = $00000001;
  {$EXTERNALSYM SERVICE_ACCEPT_STOP}
  SERVICE_ACCEPT_PAUSE_CONTINUE        = $00000002;
  {$EXTERNALSYM SERVICE_ACCEPT_PAUSE_CONTINUE}
  SERVICE_ACCEPT_SHUTDOWN              = $00000004;
  {$EXTERNALSYM SERVICE_ACCEPT_SHUTDOWN}
  SERVICE_ACCEPT_PARAMCHANGE           = $00000008;
  {$EXTERNALSYM SERVICE_ACCEPT_PARAMCHANGE}
  SERVICE_ACCEPT_NETBINDCHANGE         = $00000010;
  {$EXTERNALSYM SERVICE_ACCEPT_NETBINDCHANGE}
  SERVICE_ACCEPT_HARDWAREPROFILECHANGE = $00000020;
  {$EXTERNALSYM SERVICE_ACCEPT_HARDWAREPROFILECHANGE}
  SERVICE_ACCEPT_POWEREVENT            = $00000040;
  {$EXTERNALSYM SERVICE_ACCEPT_POWEREVENT}
  SERVICE_ACCEPT_SESSIONCHANGE         = $00000080;
  {$EXTERNALSYM SERVICE_ACCEPT_SESSIONCHANGE}

//
// Service Control Manager object specific access types
//

  SC_MANAGER_CONNECT            = $0001;
  {$EXTERNALSYM SC_MANAGER_CONNECT}
  SC_MANAGER_CREATE_SERVICE     = $0002;
  {$EXTERNALSYM SC_MANAGER_CREATE_SERVICE}
  SC_MANAGER_ENUMERATE_SERVICE  = $0004;
  {$EXTERNALSYM SC_MANAGER_ENUMERATE_SERVICE}
  SC_MANAGER_LOCK               = $0008;
  {$EXTERNALSYM SC_MANAGER_LOCK}
  SC_MANAGER_QUERY_LOCK_STATUS  = $0010;
  {$EXTERNALSYM SC_MANAGER_QUERY_LOCK_STATUS}
  SC_MANAGER_MODIFY_BOOT_CONFIG = $0020;
  {$EXTERNALSYM SC_MANAGER_MODIFY_BOOT_CONFIG}

  SC_MANAGER_ALL_ACCESS         = STANDARD_RIGHTS_REQUIRED or
                                  SC_MANAGER_CONNECT or
                                  SC_MANAGER_CREATE_SERVICE or
                                  SC_MANAGER_ENUMERATE_SERVICE or
                                  SC_MANAGER_LOCK or
                                  SC_MANAGER_QUERY_LOCK_STATUS or
                                  SC_MANAGER_MODIFY_BOOT_CONFIG;
  {$EXTERNALSYM SC_MANAGER_ALL_ACCESS}

//
// Service object specific access type
//

  SERVICE_QUERY_CONFIG         = $0001;
  {$EXTERNALSYM SERVICE_QUERY_CONFIG}
  SERVICE_CHANGE_CONFIG        = $0002;
  {$EXTERNALSYM SERVICE_CHANGE_CONFIG}
  SERVICE_QUERY_STATUS         = $0004;
  {$EXTERNALSYM SERVICE_QUERY_STATUS}
  SERVICE_ENUMERATE_DEPENDENTS = $0008;
  {$EXTERNALSYM SERVICE_ENUMERATE_DEPENDENTS}
  SERVICE_START                = $0010;
  {$EXTERNALSYM SERVICE_START}
  SERVICE_STOP                 = $0020;
  {$EXTERNALSYM SERVICE_STOP}
  SERVICE_PAUSE_CONTINUE       = $0040;
  {$EXTERNALSYM SERVICE_PAUSE_CONTINUE}
  SERVICE_INTERROGATE          = $0080;
  {$EXTERNALSYM SERVICE_INTERROGATE}
  SERVICE_USER_DEFINED_CONTROL = $0100;
  {$EXTERNALSYM SERVICE_USER_DEFINED_CONTROL}

  SERVICE_ALL_ACCESS           = STANDARD_RIGHTS_REQUIRED or
                                 SERVICE_QUERY_CONFIG or
                                 SERVICE_CHANGE_CONFIG or
                                 SERVICE_QUERY_STATUS or
                                 SERVICE_ENUMERATE_DEPENDENTS or
                                 SERVICE_START or
                                 SERVICE_STOP or
                                 SERVICE_PAUSE_CONTINUE or
                                 SERVICE_INTERROGATE or
                                 SERVICE_USER_DEFINED_CONTROL;
  {$EXTERNALSYM SERVICE_ALL_ACCESS}

//
// Service flags for QueryServiceStatusEx
//

  SERVICE_RUNS_IN_SYSTEM_PROCESS = $00000001;
  {$EXTERNALSYM SERVICE_RUNS_IN_SYSTEM_PROCESS}

//
// Info levels for ChangeServiceConfig2 and QueryServiceConfig2
//

  SERVICE_CONFIG_DESCRIPTION     = 1;
  {$EXTERNALSYM SERVICE_CONFIG_DESCRIPTION}
  SERVICE_CONFIG_FAILURE_ACTIONS = 2;
  {$EXTERNALSYM SERVICE_CONFIG_FAILURE_ACTIONS}

//
// Service description string
//

type
  LPSERVICE_DESCRIPTIONA = ^SERVICE_DESCRIPTIONA;
  {$EXTERNALSYM LPSERVICE_DESCRIPTIONA}
  _SERVICE_DESCRIPTIONA = record
    lpDescription: LPSTR;
  end;
  {$EXTERNALSYM _SERVICE_DESCRIPTIONA}
  SERVICE_DESCRIPTIONA = _SERVICE_DESCRIPTIONA;
  {$EXTERNALSYM SERVICE_DESCRIPTIONA}
  TServiceDescriptionA = SERVICE_DESCRIPTIONA;
  PServiceDescriptionA = LPSERVICE_DESCRIPTIONA;

//
// Service description string
//

  LPSERVICE_DESCRIPTIONW = ^SERVICE_DESCRIPTIONW;
  {$EXTERNALSYM LPSERVICE_DESCRIPTIONW}
  _SERVICE_DESCRIPTIONW = record
    lpDescription: LPWSTR;
  end;
  {$EXTERNALSYM _SERVICE_DESCRIPTIONW}
  SERVICE_DESCRIPTIONW = _SERVICE_DESCRIPTIONW;
  {$EXTERNALSYM SERVICE_DESCRIPTIONW}
  TServiceDescriptionW = SERVICE_DESCRIPTIONW;
  PServiceDescriptionW = LPSERVICE_DESCRIPTIONW;

{$IFDEF UNICODE}
  SERVICE_DESCRIPTION = SERVICE_DESCRIPTIONW;
  {$EXTERNALSYM SERVICE_DESCRIPTION}
  LPSERVICE_DESCRIPTION = LPSERVICE_DESCRIPTIONW;
  {$EXTERNALSYM LPSERVICE_DESCRIPTION}
  TServiceDescription = TServiceDescriptionW;
  PServiceDescription = PServiceDescriptionW;
{$ELSE}
  SERVICE_DESCRIPTION = SERVICE_DESCRIPTIONA;
  {$EXTERNALSYM SERVICE_DESCRIPTION}
  LPSERVICE_DESCRIPTION = LPSERVICE_DESCRIPTIONA;
  {$EXTERNALSYM LPSERVICE_DESCRIPTION}
  TServiceDescription = TServiceDescriptionA;
  PServiceDescription = PServiceDescriptionA;
{$ENDIF}

//
// Actions to take on service failure
//

  _SC_ACTION_TYPE = (SC_ACTION_NONE, SC_ACTION_RESTART, SC_ACTION_REBOOT,
    SC_ACTION_RUN_COMMAND);
  {$EXTERNALSYM _SC_ACTION_TYPE}
  SC_ACTION_TYPE = _SC_ACTION_TYPE;
  {$EXTERNALSYM SC_ACTION_TYPE}
  TScActionType = _SC_ACTION_TYPE;

  LPSC_ACTION = ^SC_ACTION;
  {$EXTERNALSYM LPSC_ACTION}
  _SC_ACTION = record
    Type_: SC_ACTION_TYPE;
    Delay: DWORD;
  end;
  {$EXTERNALSYM _SC_ACTION}
  SC_ACTION = _SC_ACTION;
  {$EXTERNALSYM SC_ACTION}
  TScAction = SC_ACTION;
  PScAction = LPSC_ACTION;

  LPSERVICE_FAILURE_ACTIONSA = ^SERVICE_FAILURE_ACTIONSA;
  {$EXTERNALSYM LPSERVICE_FAILURE_ACTIONSA}
  _SERVICE_FAILURE_ACTIONSA = record
    dwResetPeriod: DWORD;
    lpRebootMsg: LPSTR;
    lpCommand: LPSTR;
    cActions: DWORD;
    lpsaActions: LPSC_ACTION;
  end;
  {$EXTERNALSYM _SERVICE_FAILURE_ACTIONSA}
  SERVICE_FAILURE_ACTIONSA = _SERVICE_FAILURE_ACTIONSA;
  {$EXTERNALSYM SERVICE_FAILURE_ACTIONSA}
  TServiceFailureActionsA = SERVICE_FAILURE_ACTIONSA;
  PServiceFailureActionsA = LPSERVICE_FAILURE_ACTIONSA;

  LPSERVICE_FAILURE_ACTIONSW = ^SERVICE_FAILURE_ACTIONSW;
  {$EXTERNALSYM LPSERVICE_FAILURE_ACTIONSW}
  _SERVICE_FAILURE_ACTIONSW = record
    dwResetPeriod: DWORD;
    lpRebootMsg: LPWSTR;
    lpCommand: LPWSTR;
    cActions: DWORD;
    lpsaActions: LPSC_ACTION;
  end;
  {$EXTERNALSYM _SERVICE_FAILURE_ACTIONSW}
  SERVICE_FAILURE_ACTIONSW = _SERVICE_FAILURE_ACTIONSW;
  {$EXTERNALSYM SERVICE_FAILURE_ACTIONSW}
  TServiceFailureActionsW = SERVICE_FAILURE_ACTIONSW;
  PServiceFailureActionsW = LPSERVICE_FAILURE_ACTIONSW;

{$IFDEF UNICODE}
  SERVICE_FAILURE_ACTIONS = SERVICE_FAILURE_ACTIONSW;
  {$EXTERNALSYM SERVICE_FAILURE_ACTIONS}
  LPSERVICE_FAILURE_ACTIONS = LPSERVICE_FAILURE_ACTIONSW;
  {$EXTERNALSYM LPSERVICE_FAILURE_ACTIONS}
  TServiceFailureActions = TServiceFailureActionsW;
  PServiceFailureActions = PServiceFailureActionsW;
{$ELSE}
  SERVICE_FAILURE_ACTIONS = SERVICE_FAILURE_ACTIONSA;
  {$EXTERNALSYM SERVICE_FAILURE_ACTIONS}
  LPSERVICE_FAILURE_ACTIONS = LPSERVICE_FAILURE_ACTIONSA;
  {$EXTERNALSYM LPSERVICE_FAILURE_ACTIONS}
  TServiceFailureActions = TServiceFailureActionsA;
  PServiceFailureActions = PServiceFailureActionsA;
{$ENDIF}

//
// Handle Types
//

  SC_HANDLE = HANDLE;
  {$EXTERNALSYM SC_HANDLE}
  LPSC_HANDLE = ^SC_HANDLE;
  {$EXTERNALSYM LPSC_HANDLE}

  SERVICE_STATUS_HANDLE = HANDLE;
  {$EXTERNALSYM SERVICE_STATUS_HANDLE}

//
// Info levels for QueryServiceStatusEx
//

  _SC_STATUS_TYPE = (SC_STATUS_PROCESS_INFO);
  {$EXTERNALSYM _SC_STATUS_TYPE}
  SC_STATUS_TYPE = _SC_STATUS_TYPE;
  {$EXTERNALSYM SC_STATUS_TYPE}

//
// Info levels for EnumServicesStatusEx
//

  _SC_ENUM_TYPE = (SC_ENUM_PROCESS_INFO);
  {$EXTERNALSYM _SC_ENUM_TYPE}
  SC_ENUM_TYPE = _SC_ENUM_TYPE;
  {$EXTERNALSYM SC_ENUM_TYPE}

//
// Service Status Structures
//

  LPSERVICE_STATUS = ^SERVICE_STATUS;
  {$EXTERNALSYM LPSERVICE_STATUS}
  _SERVICE_STATUS = record
    dwServiceType: DWORD;
    dwCurrentState: DWORD;
    dwControlsAccepted: DWORD;
    dwWin32ExitCode: DWORD;
    dwServiceSpecificExitCode: DWORD;
    dwCheckPoint: DWORD;
    dwWaitHint: DWORD;
  end;
  {$EXTERNALSYM _SERVICE_STATUS}
  SERVICE_STATUS = _SERVICE_STATUS;
  {$EXTERNALSYM SERVICE_STATUS}
  TServiceStatus = SERVICE_STATUS;
  PServiceStatus = LPSERVICE_STATUS;

  LPSERVICE_STATUS_PROCESS = ^SERVICE_STATUS_PROCESS;
  {$EXTERNALSYM LPSERVICE_STATUS_PROCESS}
  _SERVICE_STATUS_PROCESS = record
    dwServiceType: DWORD;
    dwCurrentState: DWORD;
    dwControlsAccepted: DWORD;
    dwWin32ExitCode: DWORD;
    dwServiceSpecificExitCode: DWORD;
    dwCheckPoint: DWORD;
    dwWaitHint: DWORD;
    dwProcessId: DWORD;
    dwServiceFlags: DWORD;
  end;
  {$EXTERNALSYM _SERVICE_STATUS_PROCESS}
  SERVICE_STATUS_PROCESS = _SERVICE_STATUS_PROCESS;
  {$EXTERNALSYM SERVICE_STATUS_PROCESS}
  TServiceStatusProcess = SERVICE_STATUS_PROCESS;
  PServiceStatusProcess = LPSERVICE_STATUS_PROCESS;

//
// Service Status Enumeration Structure
//

  LPENUM_SERVICE_STATUSA = ^ENUM_SERVICE_STATUSA;
  {$EXTERNALSYM LPENUM_SERVICE_STATUSA}
  _ENUM_SERVICE_STATUSA = record
    lpServiceName: LPSTR;
    lpDisplayName: LPSTR;
    ServiceStatus: SERVICE_STATUS;
  end;
  {$EXTERNALSYM _ENUM_SERVICE_STATUSA}
  ENUM_SERVICE_STATUSA = _ENUM_SERVICE_STATUSA;
  {$EXTERNALSYM ENUM_SERVICE_STATUSA}
  TEnumServiceStatusA = ENUM_SERVICE_STATUSA;
  PEnumServiceStatusA = LPENUM_SERVICE_STATUSA;

  LPENUM_SERVICE_STATUSW = ^ENUM_SERVICE_STATUSW;
  {$EXTERNALSYM LPENUM_SERVICE_STATUSW}
  _ENUM_SERVICE_STATUSW = record
    lpServiceName: LPWSTR;
    lpDisplayName: LPWSTR;
    ServiceStatus: SERVICE_STATUS;
  end;
  {$EXTERNALSYM _ENUM_SERVICE_STATUSW}
  ENUM_SERVICE_STATUSW = _ENUM_SERVICE_STATUSW;
  {$EXTERNALSYM ENUM_SERVICE_STATUSW}
  TEnumServiceStatusW = ENUM_SERVICE_STATUSW;
  PEnumServiceStatusW = LPENUM_SERVICE_STATUSW;

{$IFDEF UNICODE}
  ENUM_SERVICE_STATUS = ENUM_SERVICE_STATUSW;
  {$EXTERNALSYM ENUM_SERVICE_STATUS}
  LPENUM_SERVICE_STATUS = LPENUM_SERVICE_STATUSW;
  {$EXTERNALSYM LPENUM_SERVICE_STATUS}
  TEnumServiceStatus = TEnumServiceStatusW;
  PEnumServiceStatus = PEnumServiceStatusW;
{$ELSE}
  ENUM_SERVICE_STATUS = ENUM_SERVICE_STATUSA;
  {$EXTERNALSYM ENUM_SERVICE_STATUS}
  LPENUM_SERVICE_STATUS = LPENUM_SERVICE_STATUSA;
  {$EXTERNALSYM LPENUM_SERVICE_STATUS}
  TEnumServiceStatus = TEnumServiceStatusA;
  PEnumServiceStatus = PEnumServiceStatusA;
{$ENDIF}

  LPENUM_SERVICE_STATUS_PROCESSA = ^ENUM_SERVICE_STATUS_PROCESSA;
  {$EXTERNALSYM LPENUM_SERVICE_STATUS_PROCESSA}
  _ENUM_SERVICE_STATUS_PROCESSA = record
    lpServiceName: LPSTR;
    lpDisplayName: LPSTR;
    ServiceStatusProcess: SERVICE_STATUS_PROCESS;
  end;
  {$EXTERNALSYM _ENUM_SERVICE_STATUS_PROCESSA}
  ENUM_SERVICE_STATUS_PROCESSA = _ENUM_SERVICE_STATUS_PROCESSA;
  {$EXTERNALSYM ENUM_SERVICE_STATUS_PROCESSA}
  TEnumServiceStatusProcessA = ENUM_SERVICE_STATUS_PROCESSA;
  PEnumServiceStatusProcessA = LPENUM_SERVICE_STATUS_PROCESSA;

  LPENUM_SERVICE_STATUS_PROCESSW = ^ENUM_SERVICE_STATUS_PROCESSW;
  {$EXTERNALSYM LPENUM_SERVICE_STATUS_PROCESSW}
  _ENUM_SERVICE_STATUS_PROCESSW = record
    lpServiceName: LPWSTR;
    lpDisplayName: LPWSTR;
    ServiceStatusProcess: SERVICE_STATUS_PROCESS;
  end;
  {$EXTERNALSYM _ENUM_SERVICE_STATUS_PROCESSW}
  ENUM_SERVICE_STATUS_PROCESSW = _ENUM_SERVICE_STATUS_PROCESSW;
  {$EXTERNALSYM ENUM_SERVICE_STATUS_PROCESSW}
  TEnumServiceStatusProcessW = ENUM_SERVICE_STATUS_PROCESSW;
  PEnumServiceStatusProcessW = LPENUM_SERVICE_STATUS_PROCESSW;

{$IFDEF UNICODE}
  ENUM_SERVICE_STATUS_PROCESS = ENUM_SERVICE_STATUS_PROCESSW;
  {$EXTERNALSYM ENUM_SERVICE_STATUS_PROCESS}
  LPENUM_SERVICE_STATUS_PROCESS = LPENUM_SERVICE_STATUS_PROCESSW;
  {$EXTERNALSYM LPENUM_SERVICE_STATUS_PROCESS}
  TEnumServiceStatusProcess = TEnumServiceStatusProcessW;
  PEnumServiceStatusProcess = PEnumServiceStatusProcessW;
{$ELSE}
  ENUM_SERVICE_STATUS_PROCESS = ENUM_SERVICE_STATUS_PROCESSA;
  {$EXTERNALSYM ENUM_SERVICE_STATUS_PROCESS}
  LPENUM_SERVICE_STATUS_PROCESS = LPENUM_SERVICE_STATUS_PROCESSA;
  {$EXTERNALSYM LPENUM_SERVICE_STATUS_PROCESS}
  TEnumServiceStatusProcess = TEnumServiceStatusProcessA;
  PEnumServiceStatusProcess = PEnumServiceStatusProcessA;
{$ENDIF}

//
// Structures for the Lock API functions
//

  SC_LOCK = LPVOID;
  {$EXTERNALSYM SC_LOCK}

  LPQUERY_SERVICE_LOCK_STATUSA = ^QUERY_SERVICE_LOCK_STATUSA;
  {$EXTERNALSYM LPQUERY_SERVICE_LOCK_STATUSA}
  _QUERY_SERVICE_LOCK_STATUSA = record
    fIsLocked: DWORD;
    lpLockOwner: LPSTR;
    dwLockDuration: DWORD;
  end;
  {$EXTERNALSYM _QUERY_SERVICE_LOCK_STATUSA}
  QUERY_SERVICE_LOCK_STATUSA = _QUERY_SERVICE_LOCK_STATUSA;
  {$EXTERNALSYM QUERY_SERVICE_LOCK_STATUSA}
  TQueryServiceLockStatusA = QUERY_SERVICE_LOCK_STATUSA;
  PQueryServiceLockStatusA = LPQUERY_SERVICE_LOCK_STATUSA;

  LPQUERY_SERVICE_LOCK_STATUSW = ^QUERY_SERVICE_LOCK_STATUSW;
  {$EXTERNALSYM LPQUERY_SERVICE_LOCK_STATUSW}
  _QUERY_SERVICE_LOCK_STATUSW = record
    fIsLocked: DWORD;
    lpLockOwner: LPWSTR;
    dwLockDuration: DWORD;
  end;
  {$EXTERNALSYM _QUERY_SERVICE_LOCK_STATUSW}
  QUERY_SERVICE_LOCK_STATUSW = _QUERY_SERVICE_LOCK_STATUSW;
  {$EXTERNALSYM QUERY_SERVICE_LOCK_STATUSW}
  TQueryServiceLockStatusW = QUERY_SERVICE_LOCK_STATUSW;
  PQueryServiceLockStatusW = LPQUERY_SERVICE_LOCK_STATUSW;

{$IFDEF UNICODE}
  QUERY_SERVICE_LOCK_STATUS = QUERY_SERVICE_LOCK_STATUSW;
  {$EXTERNALSYM QUERY_SERVICE_LOCK_STATUS}
  LPQUERY_SERVICE_LOCK_STATUS = LPQUERY_SERVICE_LOCK_STATUSW;
  {$EXTERNALSYM LPQUERY_SERVICE_LOCK_STATUS}
  TQueryServiceLockStatus = TQueryServiceLockStatusW;
  PQueryServiceLockStatus = PQueryServiceLockStatusW;
{$ELSE}
  QUERY_SERVICE_LOCK_STATUS = QUERY_SERVICE_LOCK_STATUSA;
  {$EXTERNALSYM QUERY_SERVICE_LOCK_STATUS}
  LPQUERY_SERVICE_LOCK_STATUS = LPQUERY_SERVICE_LOCK_STATUSA;
  {$EXTERNALSYM LPQUERY_SERVICE_LOCK_STATUS}
  TQueryServiceLockStatus = TQueryServiceLockStatusA;
  PQueryServiceLockStatus = PQueryServiceLockStatusA;
{$ENDIF}

//
// Query Service Configuration Structure
//

  LPQUERY_SERVICE_CONFIGA = ^QUERY_SERVICE_CONFIGA;
  {$EXTERNALSYM LPQUERY_SERVICE_CONFIGA}
  _QUERY_SERVICE_CONFIGA = record
    dwServiceType: DWORD;
    dwStartType: DWORD;
    dwErrorControl: DWORD;
    lpBinaryPathName: LPSTR;
    lpLoadOrderGroup: LPSTR;
    dwTagId: DWORD;
    lpDependencies: LPSTR;
    lpServiceStartName: LPSTR;
    lpDisplayName: LPSTR;
  end;
  {$EXTERNALSYM _QUERY_SERVICE_CONFIGA}
  QUERY_SERVICE_CONFIGA = _QUERY_SERVICE_CONFIGA;
  {$EXTERNALSYM QUERY_SERVICE_CONFIGA}
  TQueryServiceConfigA = QUERY_SERVICE_CONFIGA;
  PQueryServiceConfigA = LPQUERY_SERVICE_CONFIGA;

  LPQUERY_SERVICE_CONFIGW = ^QUERY_SERVICE_CONFIGW;
  {$EXTERNALSYM LPQUERY_SERVICE_CONFIGW}
  _QUERY_SERVICE_CONFIGW = record
    dwServiceType: DWORD;
    dwStartType: DWORD;
    dwErrorControl: DWORD;
    lpBinaryPathName: LPWSTR;
    lpLoadOrderGroup: LPWSTR;
    dwTagId: DWORD;
    lpDependencies: LPWSTR;
    lpServiceStartName: LPWSTR;
    lpDisplayName: LPWSTR;
  end;
  {$EXTERNALSYM _QUERY_SERVICE_CONFIGW}
  QUERY_SERVICE_CONFIGW = _QUERY_SERVICE_CONFIGW;
  {$EXTERNALSYM QUERY_SERVICE_CONFIGW}
  TQueryServiceConfigW = QUERY_SERVICE_CONFIGW;
  PQueryServiceConfigW = LPQUERY_SERVICE_CONFIGW;

{$IFDEF UNICODE}
  QUERY_SERVICE_CONFIG = QUERY_SERVICE_CONFIGW;
  {$EXTERNALSYM QUERY_SERVICE_CONFIG}
  LPQUERY_SERVICE_CONFIG = LPQUERY_SERVICE_CONFIGW;
  {$EXTERNALSYM LPQUERY_SERVICE_CONFIG}
  TQueryServiceConfig = TQueryServiceConfigW;
  PQueryServiceConfig = PQueryServiceConfigW;
{$ELSE}
  QUERY_SERVICE_CONFIG = QUERY_SERVICE_CONFIGA;
  {$EXTERNALSYM QUERY_SERVICE_CONFIG}
  LPQUERY_SERVICE_CONFIG = LPQUERY_SERVICE_CONFIGA;
  {$EXTERNALSYM LPQUERY_SERVICE_CONFIG}
  TQueryServiceConfig = TQueryServiceConfigA;
  PQueryServiceConfig = PQueryServiceConfigA;
{$ENDIF}

//
// Function Prototype for the Service Main Function
//

type
  LPSERVICE_MAIN_FUNCTIONW = procedure (dwNumServicesArgs: DWORD;
    lpServiceArgVectors: LPWSTR); stdcall;
  {$EXTERNALSYM LPSERVICE_MAIN_FUNCTIONW}
  LPSERVICE_MAIN_FUNCTIONA = procedure (dwNumServicesArgs: DWORD;
    lpServiceArgVectors: LPSTR); stdcall;
  {$EXTERNALSYM LPSERVICE_MAIN_FUNCTIONA}

  TServiceMainFunctionA = LPSERVICE_MAIN_FUNCTIONA;
  TServiceMainFunctionW = LPSERVICE_MAIN_FUNCTIONW;

{$IFDEF UNICODE}
  LPSERVICE_MAIN_FUNCTION = LPSERVICE_MAIN_FUNCTIONW;
  {$EXTERNALSYM LPSERVICE_MAIN_FUNCTION}
  TServiceMainFunction = LPSERVICE_MAIN_FUNCTIONW;
{$ELSE}
  LPSERVICE_MAIN_FUNCTION = LPSERVICE_MAIN_FUNCTIONA;
  {$EXTERNALSYM LPSERVICE_MAIN_FUNCTION}
  TServiceMainFunction = LPSERVICE_MAIN_FUNCTIONA;  
{$ENDIF}

//
// Service Start Table
//

  LPSERVICE_TABLE_ENTRYA = ^SERVICE_TABLE_ENTRYA;
  {$EXTERNALSYM LPSERVICE_TABLE_ENTRYA}
  _SERVICE_TABLE_ENTRYA = record
    lpServiceName: LPSTR;
    lpServiceProc: LPSERVICE_MAIN_FUNCTIONA;
  end;
  {$EXTERNALSYM _SERVICE_TABLE_ENTRYA}
  SERVICE_TABLE_ENTRYA = _SERVICE_TABLE_ENTRYA;
  {$EXTERNALSYM SERVICE_TABLE_ENTRYA}
  TServiceTableEntryA = SERVICE_TABLE_ENTRYA;
  PServiceTableEntryA = LPSERVICE_TABLE_ENTRYA;

  LPSERVICE_TABLE_ENTRYW = ^SERVICE_TABLE_ENTRYW;
  {$EXTERNALSYM LPSERVICE_TABLE_ENTRYW}
  _SERVICE_TABLE_ENTRYW = record
    lpServiceName: LPWSTR;
    lpServiceProc: LPSERVICE_MAIN_FUNCTIONW;
  end;
  {$EXTERNALSYM _SERVICE_TABLE_ENTRYW}
  SERVICE_TABLE_ENTRYW = _SERVICE_TABLE_ENTRYW;
  {$EXTERNALSYM SERVICE_TABLE_ENTRYW}
  TServiceTableEntryW = SERVICE_TABLE_ENTRYW;
  PServiceTableEntryW = LPSERVICE_TABLE_ENTRYW;

{$IFDEF UNICODE}
  SERVICE_TABLE_ENTRY = SERVICE_TABLE_ENTRYW;
  LPSERVICE_TABLE_ENTRY = LPSERVICE_TABLE_ENTRYW;
  TServiceTableEntry = TServiceTableEntryW;
  PServiceTableEntry = PServiceTableEntryW;
{$ELSE}
  SERVICE_TABLE_ENTRY = SERVICE_TABLE_ENTRYA;
  LPSERVICE_TABLE_ENTRY = LPSERVICE_TABLE_ENTRYA;
  TServiceTableEntry = TServiceTableEntryA;
  PServiceTableEntry = PServiceTableEntryA;
{$ENDIF}

//
// Prototype for the Service Control Handler Function
//

  LPHANDLER_FUNCTION = procedure (dwControl: DWORD); stdcall;
  {$EXTERNALSYM LPHANDLER_FUNCTION}
  THandlerFunction = LPHANDLER_FUNCTION;

  LPHANDLER_FUNCTION_EX = function (dwControl, dwEventType: DWORD;
    lpEventData, lpContext: LPVOID): DWORD; stdcall;
  {$EXTERNALSYM LPHANDLER_FUNCTION_EX}
  THandlerFunctionEx = LPHANDLER_FUNCTION_EX;

///////////////////////////////////////////////////////////////////////////
// API Function Prototypes
///////////////////////////////////////////////////////////////////////////

function ChangeServiceConfigA(hService: SC_HANDLE; dwServiceType, dwStartType,
  dwErrorControl: DWORD; lpBinaryPathName, lpLoadOrderGroup: LPCSTR;
  lpdwTagId: LPDWORD; lpDependencies, lpServiceStartName, lpPassword,
  lpDisplayName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfigA}
function ChangeServiceConfigW(hService: SC_HANDLE; dwServiceType, dwStartType,
  dwErrorControl: DWORD; lpBinaryPathName, lpLoadOrderGroup: LPCWSTR;
  lpdwTagId: LPDWORD; lpDependencies, lpServiceStartName, lpPassword,
  lpDisplayName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfigW}

{$IFDEF UNICODE}
function ChangeServiceConfig(hService: SC_HANDLE; dwServiceType, dwStartType,
  dwErrorControl: DWORD; lpBinaryPathName, lpLoadOrderGroup: LPCWSTR;
  lpdwTagId: LPDWORD; lpDependencies, lpServiceStartName, lpPassword,
  lpDisplayName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfig}
{$ELSE}
function ChangeServiceConfig(hService: SC_HANDLE; dwServiceType, dwStartType,
  dwErrorControl: DWORD; lpBinaryPathName, lpLoadOrderGroup: LPCSTR;
  lpdwTagId: LPDWORD; lpDependencies, lpServiceStartName, lpPassword,
  lpDisplayName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfig}
{$ENDIF}

function ChangeServiceConfig2A(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpInfo: LPVOID): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfig2A}
function ChangeServiceConfig2W(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpInfo: LPVOID): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfig2W}

{$IFDEF UNICODE}
function ChangeServiceConfig2(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpInfo: LPVOID): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfig2}
{$ELSE}
function ChangeServiceConfig2(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpInfo: LPVOID): BOOL; stdcall;
{$EXTERNALSYM ChangeServiceConfig2}
{$ENDIF}

function CloseServiceHandle(hSCObject: SC_HANDLE): BOOL; stdcall;
{$EXTERNALSYM CloseServiceHandle}

function ControlService(hService: SC_HANDLE; dwControl: DWORD;
  var lpServiceStatus: SERVICE_STATUS): BOOL; stdcall;
{$EXTERNALSYM ControlService}

function CreateServiceA(hSCManager: SC_HANDLE; lpServiceName, lpDisplayName: LPCSTR;
  dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl: DWORD;
  lpBinaryPathName, lpLoadOrderGroup: LPCSTR; lpdwTagId: LPDWORD;
  lpDependencies, lpServiceStartName, lpPassword: LPCSTR): SC_HANDLE; stdcall;
{$EXTERNALSYM CreateServiceA}
function CreateServiceW(hSCManager: SC_HANDLE; lpServiceName, lpDisplayName: LPCWSTR;
  dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl: DWORD;
  lpBinaryPathName, lpLoadOrderGroup: LPCWSTR; lpdwTagId: LPDWORD;
  lpDependencies, lpServiceStartName, lpPassword: LPCWSTR): SC_HANDLE; stdcall;
{$EXTERNALSYM CreateServiceW}

{$IFDEF UNICODE}
function CreateService(hSCManager: SC_HANDLE; lpServiceName, lpDisplayName: LPCWSTR;
  dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl: DWORD;
  lpBinaryPathName, lpLoadOrderGroup: LPCWSTR; lpdwTagId: LPDWORD;
  lpDependencies, lpServiceStartName, lpPassword: LPCWSTR): SC_HANDLE; stdcall;
{$EXTERNALSYM CreateService}
{$ELSE}
function CreateService(hSCManager: SC_HANDLE; lpServiceName, lpDisplayName: LPCSTR;
  dwDesiredAccess, dwServiceType, dwStartType, dwErrorControl: DWORD;
  lpBinaryPathName, lpLoadOrderGroup: LPCSTR; lpdwTagId: LPDWORD;
  lpDependencies, lpServiceStartName, lpPassword: LPCSTR): SC_HANDLE; stdcall;
{$EXTERNALSYM CreateService}
{$ENDIF}

function DeleteService(hService: SC_HANDLE): BOOL; stdcall;
{$EXTERNALSYM DeleteService}

function EnumDependentServicesA(hService: SC_HANDLE; dwServiceState: DWORD;
  lpServices: LPENUM_SERVICE_STATUSA; cbBufSize: DWORD; var pcbBytesNeeded,
  lpServicesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumDependentServicesA}
function EnumDependentServicesW(hService: SC_HANDLE; dwServiceState: DWORD;
  lpServices: LPENUM_SERVICE_STATUSW; cbBufSize: DWORD; var pcbBytesNeeded,
  lpServicesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumDependentServicesW}

{$IFDEF UNICODE}
function EnumDependentServices(hService: SC_HANDLE; dwServiceState: DWORD;
  lpServices: LPENUM_SERVICE_STATUSW; cbBufSize: DWORD; var pcbBytesNeeded,
  lpServicesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumDependentServices}
{$ELSE}
function EnumDependentServices(hService: SC_HANDLE; dwServiceState: DWORD;
  lpServices: LPENUM_SERVICE_STATUSA; cbBufSize: DWORD; var pcbBytesNeeded,
  lpServicesReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumDependentServices}
{$ENDIF}

function EnumServicesStatusA(hSCManager: SC_HANDLE; dwServiceType: DWORD;
  dwServiceState: DWORD; lpServices: LPENUM_SERVICE_STATUSA; cbBufSize: DWORD;
  var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatusA}
function EnumServicesStatusW(hSCManager: SC_HANDLE; dwServiceType: DWORD;
  dwServiceState: DWORD; lpServices: LPENUM_SERVICE_STATUSW; cbBufSize: DWORD;
  var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatusW}

{$IFDEF UNICODE}
function EnumServicesStatus(hSCManager: SC_HANDLE; dwServiceType: DWORD;
  dwServiceState: DWORD; lpServices: LPENUM_SERVICE_STATUSW; cbBufSize: DWORD;
  var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatus}
{$ELSE}
function EnumServicesStatus(hSCManager: SC_HANDLE; dwServiceType: DWORD;
  dwServiceState: DWORD; lpServices: LPENUM_SERVICE_STATUSA; cbBufSize: DWORD;
  var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatus}
{$ENDIF}

function EnumServicesStatusExA(hSCManager: SC_HANDLE; InfoLevel: SC_ENUM_TYPE;
  dwServiceType: DWORD; dwServiceState: DWORD; lpServices: LPBYTE;
  cbBufSize: DWORD; var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD;
  pszGroupName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatusExA}
function EnumServicesStatusExW(hSCManager: SC_HANDLE; InfoLevel: SC_ENUM_TYPE;
  dwServiceType: DWORD; dwServiceState: DWORD; lpServices: LPBYTE;
  cbBufSize: DWORD; var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD;
  pszGroupName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatusExW}

{$IFDEF UNICODE}
function EnumServicesStatusEx(hSCManager: SC_HANDLE; InfoLevel: SC_ENUM_TYPE;
  dwServiceType: DWORD; dwServiceState: DWORD; lpServices: LPBYTE;
  cbBufSize: DWORD; var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD;
  pszGroupName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatusEx}
{$ELSE}
function EnumServicesStatusEx(hSCManager: SC_HANDLE; InfoLevel: SC_ENUM_TYPE;
  dwServiceType: DWORD; dwServiceState: DWORD; lpServices: LPBYTE;
  cbBufSize: DWORD; var pcbBytesNeeded, lpServicesReturned, lpResumeHandle: DWORD;
  pszGroupName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM EnumServicesStatusEx}
{$ENDIF}

function GetServiceKeyNameA(hSCManager: SC_HANDLE; lpDisplayName: LPCSTR;
  lpServiceName: LPSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceKeyNameA}
function GetServiceKeyNameW(hSCManager: SC_HANDLE; lpDisplayName: LPCWSTR;
  lpServiceName: LPWSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceKeyNameW}

{$IFDEF UNICODE}
function GetServiceKeyName(hSCManager: SC_HANDLE; lpDisplayName: LPCWSTR;
  lpServiceName: LPWSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceKeyName}
{$ELSE}
function GetServiceKeyName(hSCManager: SC_HANDLE; lpDisplayName: LPCSTR;
  lpServiceName: LPSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceKeyName}
{$ENDIF}

function GetServiceDisplayNameA(hSCManager: SC_HANDLE; lpServiceName: LPCSTR;
  lpDisplayName: LPSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceDisplayNameA}
function GetServiceDisplayNameW(hSCManager: SC_HANDLE; lpServiceName: LPCWSTR;
  lpDisplayName: LPWSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceDisplayNameW}

{$IFDEF UNICODE}
function GetServiceDisplayName(hSCManager: SC_HANDLE; lpServiceName: LPCWSTR;
  lpDisplayName: LPWSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceDisplayName}
{$ELSE}
function GetServiceDisplayName(hSCManager: SC_HANDLE; lpServiceName: LPCSTR;
  lpDisplayName: LPSTR; var lpcchBuffer: DWORD): BOOL; stdcall;
{$EXTERNALSYM GetServiceDisplayName}
{$ENDIF}

function LockServiceDatabase(hSCManager: SC_HANDLE): SC_LOCK; stdcall;
{$EXTERNALSYM LockServiceDatabase}

function NotifyBootConfigStatus(BootAcceptable: BOOL): BOOL; stdcall;
{$EXTERNALSYM NotifyBootConfigStatus}

function OpenSCManagerA(lpMachineName: LPCSTR; lpDatabaseName: LPCSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenSCManagerA}
function OpenSCManagerW(lpMachineName: LPCWSTR; lpDatabaseName: LPCWSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenSCManagerW}

{$IFDEF UNICODE}
function OpenSCManager(lpMachineName: LPCWSTR; lpDatabaseName: LPCWSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenSCManager}
{$ELSE}
function OpenSCManager(lpMachineName: LPCSTR; lpDatabaseName: LPCSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenSCManager}
{$ENDIF}

function OpenServiceA(hSCManager: SC_HANDLE; lpServiceName: LPCSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenServiceA}
function OpenServiceW(hSCManager: SC_HANDLE; lpServiceName: LPCWSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenServiceW}

{$IFDEF UNICODE}
function OpenService(hSCManager: SC_HANDLE; lpServiceName: LPCWSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenService}
{$ELSE}
function OpenService(hSCManager: SC_HANDLE; lpServiceName: LPCSTR;
  dwDesiredAccess: DWORD): SC_HANDLE; stdcall;
{$EXTERNALSYM OpenService}
{$ENDIF}

function QueryServiceConfigA(hService: SC_HANDLE;
  lpServiceConfig: LPQUERY_SERVICE_CONFIGA; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfigA}
function QueryServiceConfigW(hService: SC_HANDLE;
  lpServiceConfig: LPQUERY_SERVICE_CONFIGW; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfigW}

{$IFDEF UNICODE}
function QueryServiceConfig(hService: SC_HANDLE;
  lpServiceConfig: LPQUERY_SERVICE_CONFIGW; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfig}
{$ELSE}
function QueryServiceConfig(hService: SC_HANDLE;
  lpServiceConfig: LPQUERY_SERVICE_CONFIGA; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfig}
{$ENDIF}

function QueryServiceConfig2A(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpBuffer: LPBYTE; cbBufSize: DWORD; var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfig2A}
function QueryServiceConfig2W(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpBuffer: LPBYTE; cbBufSize: DWORD; var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfig2W}

{$IFDEF UNICODE}
function QueryServiceConfig2(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpBuffer: LPBYTE; cbBufSize: DWORD; var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfig2}
{$ELSE}
function QueryServiceConfig2(hService: SC_HANDLE; dwInfoLevel: DWORD;
  lpBuffer: LPBYTE; cbBufSize: DWORD; var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceConfig2}
{$ENDIF}

function QueryServiceLockStatusA(hSCManager: SC_HANDLE;
  lpLockStatus: LPQUERY_SERVICE_LOCK_STATUSA; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceLockStatusA}
function QueryServiceLockStatusW(hSCManager: SC_HANDLE;
  lpLockStatus: LPQUERY_SERVICE_LOCK_STATUSW; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceLockStatusW}

{$IFDEF UNICODE}
function QueryServiceLockStatus(hSCManager: SC_HANDLE;
  lpLockStatus: LPQUERY_SERVICE_LOCK_STATUSW; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceLockStatus}
{$ELSE}
function QueryServiceLockStatus(hSCManager: SC_HANDLE;
  lpLockStatus: LPQUERY_SERVICE_LOCK_STATUSA; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceLockStatus}
{$ENDIF}

function QueryServiceObjectSecurity(hService: SC_HANDLE;
  dwSecurityInformation: SECURITY_INFORMATION;
  var lpSecurityDescriptor: SECURITY_DESCRIPTOR; cbBufSize: DWORD;
  var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceObjectSecurity}

function QueryServiceStatus(hService: SC_HANDLE;
  var lpServiceStatus: SERVICE_STATUS): BOOL; stdcall;
{$EXTERNALSYM QueryServiceStatus}

function QueryServiceStatusEx(hService: SC_HANDLE; InfoLevel: SC_STATUS_TYPE;
  lpBuffer: LPBYTE; cbBufSize: DWORD; var pcbBytesNeeded: DWORD): BOOL; stdcall;
{$EXTERNALSYM QueryServiceStatusEx}

function RegisterServiceCtrlHandlerA(lpServiceName: LPCSTR;
  lpHandlerProc: LPHANDLER_FUNCTION): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandlerA}
function RegisterServiceCtrlHandlerW(lpServiceName: LPCWSTR;
  lpHandlerProc: LPHANDLER_FUNCTION): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandlerW}

{$IFDEF UNICODE}
function RegisterServiceCtrlHandler(lpServiceName: LPCWSTR;
  lpHandlerProc: LPHANDLER_FUNCTION): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandler}
{$ELSE}
function RegisterServiceCtrlHandler(lpServiceName: LPCSTR;
  lpHandlerProc: LPHANDLER_FUNCTION): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandler}
{$ENDIF}

function RegisterServiceCtrlHandlerExA(lpServiceName: LPCSTR;
  lpHandlerProc: LPHANDLER_FUNCTION_EX; lpContext: LPVOID): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandlerExA}
function RegisterServiceCtrlHandlerExW(lpServiceName: LPCWSTR;
  lpHandlerProc: LPHANDLER_FUNCTION_EX; lpContext: LPVOID): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandlerExW}

{$IFDEF UNICODE}
function RegisterServiceCtrlHandlerEx(lpServiceName: LPCWSTR;
  lpHandlerProc: LPHANDLER_FUNCTION_EX; lpContext: LPVOID): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandlerEx}
{$ELSE}
function RegisterServiceCtrlHandlerEx(lpServiceName: LPCSTR;
  lpHandlerProc: LPHANDLER_FUNCTION_EX; lpContext: LPVOID): SERVICE_STATUS_HANDLE; stdcall;
{$EXTERNALSYM RegisterServiceCtrlHandlerEx}
{$ENDIF}

// 9/4/2002 Changed last parameter from const to pointer - reported by James Ots.

function SetServiceObjectSecurity(hService: SC_HANDLE;
  dwSecurityInformation: SECURITY_INFORMATION;
  lpSecurityDescriptor: PSECURITY_DESCRIPTOR): BOOL; stdcall;
{$EXTERNALSYM SetServiceObjectSecurity}

function SetServiceStatus(hServiceStatus: SERVICE_STATUS_HANDLE;
  const lpServiceStatus: SERVICE_STATUS): BOOL; stdcall;
{$EXTERNALSYM SetServiceStatus}

function StartServiceCtrlDispatcherA(lpServiceStartTable: LPSERVICE_TABLE_ENTRYA): BOOL; stdcall;
{$EXTERNALSYM StartServiceCtrlDispatcherA}
function StartServiceCtrlDispatcherW(lpServiceStartTable: LPSERVICE_TABLE_ENTRYW): BOOL; stdcall;
{$EXTERNALSYM StartServiceCtrlDispatcherW}

{$IFDEF UNICODE}
function StartServiceCtrlDispatcher(lpServiceStartTable: LPSERVICE_TABLE_ENTRYW): BOOL; stdcall;
{$EXTERNALSYM StartServiceCtrlDispatcher}
{$ELSE}
function StartServiceCtrlDispatcher(lpServiceStartTable: LPSERVICE_TABLE_ENTRYA): BOOL; stdcall;
{$EXTERNALSYM StartServiceCtrlDispatcher}
{$ENDIF}

function StartServiceA(hService: SC_HANDLE; dwNumServiceArgs: DWORD;
  lpServiceArgVectors: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM StartServiceA}
function StartServiceW(hService: SC_HANDLE; dwNumServiceArgs: DWORD;
  lpServiceArgVectors: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM StartServiceW}

{$IFDEF UNICODE}
function StartService(hService: SC_HANDLE; dwNumServiceArgs: DWORD;
  lpServiceArgVectors: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM StartService}
{$ELSE}
function StartService(hService: SC_HANDLE; dwNumServiceArgs: DWORD;
  lpServiceArgVectors: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM StartService}
{$ENDIF}

function UnlockServiceDatabase(ScLock: SC_LOCK): BOOL; stdcall;
{$EXTERNALSYM UnlockServiceDatabase}

implementation

const
  advapi32 = 'advapi32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfigA: Pointer;

function ChangeServiceConfigA;
begin
  GetProcedureAddress(_ChangeServiceConfigA, advapi32, 'ChangeServiceConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfigA]
  end;
end;
{$ELSE}
function ChangeServiceConfigA; external advapi32 name 'ChangeServiceConfigA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfigW: Pointer;

function ChangeServiceConfigW;
begin
  GetProcedureAddress(_ChangeServiceConfigW, advapi32, 'ChangeServiceConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfigW]
  end;
end;
{$ELSE}
function ChangeServiceConfigW; external advapi32 name 'ChangeServiceConfigW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfig: Pointer;

function ChangeServiceConfig;
begin
  GetProcedureAddress(_ChangeServiceConfig, advapi32, 'ChangeServiceConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfig]
  end;
end;
{$ELSE}
function ChangeServiceConfig; external advapi32 name 'ChangeServiceConfigW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfig: Pointer;

function ChangeServiceConfig;
begin
  GetProcedureAddress(_ChangeServiceConfig, advapi32, 'ChangeServiceConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfig]
  end;
end;
{$ELSE}
function ChangeServiceConfig; external advapi32 name 'ChangeServiceConfigA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfig2A: Pointer;

function ChangeServiceConfig2A;
begin
  GetProcedureAddress(_ChangeServiceConfig2A, advapi32, 'ChangeServiceConfig2A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfig2A]
  end;
end;
{$ELSE}
function ChangeServiceConfig2A; external advapi32 name 'ChangeServiceConfig2A';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfig2W: Pointer;

function ChangeServiceConfig2W;
begin
  GetProcedureAddress(_ChangeServiceConfig2W, advapi32, 'ChangeServiceConfig2W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfig2W]
  end;
end;
{$ELSE}
function ChangeServiceConfig2W; external advapi32 name 'ChangeServiceConfig2W';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfig2: Pointer;

function ChangeServiceConfig2;
begin
  GetProcedureAddress(_ChangeServiceConfig2, advapi32, 'ChangeServiceConfig2W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfig2]
  end;
end;
{$ELSE}
function ChangeServiceConfig2; external advapi32 name 'ChangeServiceConfig2W';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _ChangeServiceConfig2: Pointer;

function ChangeServiceConfig2;
begin
  GetProcedureAddress(_ChangeServiceConfig2, advapi32, 'ChangeServiceConfig2A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ChangeServiceConfig2]
  end;
end;
{$ELSE}
function ChangeServiceConfig2; external advapi32 name 'ChangeServiceConfig2A';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _CloseServiceHandle: Pointer;

function CloseServiceHandle;
begin
  GetProcedureAddress(_CloseServiceHandle, advapi32, 'CloseServiceHandle');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CloseServiceHandle]
  end;
end;
{$ELSE}
function CloseServiceHandle; external advapi32 name 'CloseServiceHandle';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ControlService: Pointer;

function ControlService;
begin
  GetProcedureAddress(_ControlService, advapi32, 'ControlService');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ControlService]
  end;
end;
{$ELSE}
function ControlService; external advapi32 name 'ControlService';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _CreateServiceA: Pointer;

function CreateServiceA;
begin
  GetProcedureAddress(_CreateServiceA, advapi32, 'CreateServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateServiceA]
  end;
end;
{$ELSE}
function CreateServiceA; external advapi32 name 'CreateServiceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreateServiceW: Pointer;

function CreateServiceW;
begin
  GetProcedureAddress(_CreateServiceW, advapi32, 'CreateServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateServiceW]
  end;
end;
{$ELSE}
function CreateServiceW; external advapi32 name 'CreateServiceW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _CreateService: Pointer;

function CreateService;
begin
  GetProcedureAddress(_CreateService, advapi32, 'CreateServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateService]
  end;
end;
{$ELSE}
function CreateService; external advapi32 name 'CreateServiceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _CreateService: Pointer;

function CreateService;
begin
  GetProcedureAddress(_CreateService, advapi32, 'CreateServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreateService]
  end;
end;
{$ELSE}
function CreateService; external advapi32 name 'CreateServiceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _DeleteService: Pointer;

function DeleteService;
begin
  GetProcedureAddress(_DeleteService, advapi32, 'DeleteService');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DeleteService]
  end;
end;
{$ELSE}
function DeleteService; external advapi32 name 'DeleteService';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _EnumDependentServicesA: Pointer;

function EnumDependentServicesA;
begin
  GetProcedureAddress(_EnumDependentServicesA, advapi32, 'EnumDependentServicesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumDependentServicesA]
  end;
end;
{$ELSE}
function EnumDependentServicesA; external advapi32 name 'EnumDependentServicesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumDependentServicesW: Pointer;

function EnumDependentServicesW;
begin
  GetProcedureAddress(_EnumDependentServicesW, advapi32, 'EnumDependentServicesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumDependentServicesW]
  end;
end;
{$ELSE}
function EnumDependentServicesW; external advapi32 name 'EnumDependentServicesW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumDependentServices: Pointer;

function EnumDependentServices;
begin
  GetProcedureAddress(_EnumDependentServices, advapi32, 'EnumDependentServicesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumDependentServices]
  end;
end;
{$ELSE}
function EnumDependentServices; external advapi32 name 'EnumDependentServicesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumDependentServices: Pointer;

function EnumDependentServices;
begin
  GetProcedureAddress(_EnumDependentServices, advapi32, 'EnumDependentServicesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumDependentServices]
  end;
end;
{$ELSE}
function EnumDependentServices; external advapi32 name 'EnumDependentServicesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatusA: Pointer;

function EnumServicesStatusA;
begin
  GetProcedureAddress(_EnumServicesStatusA, advapi32, 'EnumServicesStatusA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatusA]
  end;
end;
{$ELSE}
function EnumServicesStatusA; external advapi32 name 'EnumServicesStatusA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatusW: Pointer;

function EnumServicesStatusW;
begin
  GetProcedureAddress(_EnumServicesStatusW, advapi32, 'EnumServicesStatusW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatusW]
  end;
end;
{$ELSE}
function EnumServicesStatusW; external advapi32 name 'EnumServicesStatusW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatus: Pointer;

function EnumServicesStatus;
begin
  GetProcedureAddress(_EnumServicesStatus, advapi32, 'EnumServicesStatusW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatus]
  end;
end;
{$ELSE}
function EnumServicesStatus; external advapi32 name 'EnumServicesStatusW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatus: Pointer;

function EnumServicesStatus;
begin
  GetProcedureAddress(_EnumServicesStatus, advapi32, 'EnumServicesStatusA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatus]
  end;
end;
{$ELSE}
function EnumServicesStatus; external advapi32 name 'EnumServicesStatusA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatusExA: Pointer;

function EnumServicesStatusExA;
begin
  GetProcedureAddress(_EnumServicesStatusExA, advapi32, 'EnumServicesStatusExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatusExA]
  end;
end;
{$ELSE}
function EnumServicesStatusExA; external advapi32 name 'EnumServicesStatusExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatusExW: Pointer;

function EnumServicesStatusExW;
begin
  GetProcedureAddress(_EnumServicesStatusExW, advapi32, 'EnumServicesStatusExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatusExW]
  end;
end;
{$ELSE}
function EnumServicesStatusExW; external advapi32 name 'EnumServicesStatusExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatusEx: Pointer;

function EnumServicesStatusEx;
begin
  GetProcedureAddress(_EnumServicesStatusEx, advapi32, 'EnumServicesStatusExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatusEx]
  end;
end;
{$ELSE}
function EnumServicesStatusEx; external advapi32 name 'EnumServicesStatusExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumServicesStatusEx: Pointer;

function EnumServicesStatusEx;
begin
  GetProcedureAddress(_EnumServicesStatusEx, advapi32, 'EnumServicesStatusExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumServicesStatusEx]
  end;
end;
{$ELSE}
function EnumServicesStatusEx; external advapi32 name 'EnumServicesStatusExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _GetServiceKeyNameA: Pointer;

function GetServiceKeyNameA;
begin
  GetProcedureAddress(_GetServiceKeyNameA, advapi32, 'GetServiceKeyNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceKeyNameA]
  end;
end;
{$ELSE}
function GetServiceKeyNameA; external advapi32 name 'GetServiceKeyNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceKeyNameW: Pointer;

function GetServiceKeyNameW;
begin
  GetProcedureAddress(_GetServiceKeyNameW, advapi32, 'GetServiceKeyNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceKeyNameW]
  end;
end;
{$ELSE}
function GetServiceKeyNameW; external advapi32 name 'GetServiceKeyNameW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceKeyName: Pointer;

function GetServiceKeyName;
begin
  GetProcedureAddress(_GetServiceKeyName, advapi32, 'GetServiceKeyNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceKeyName]
  end;
end;
{$ELSE}
function GetServiceKeyName; external advapi32 name 'GetServiceKeyNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceKeyName: Pointer;

function GetServiceKeyName;
begin
  GetProcedureAddress(_GetServiceKeyName, advapi32, 'GetServiceKeyNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceKeyName]
  end;
end;
{$ELSE}
function GetServiceKeyName; external advapi32 name 'GetServiceKeyNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _GetServiceDisplayNameA: Pointer;

function GetServiceDisplayNameA;
begin
  GetProcedureAddress(_GetServiceDisplayNameA, advapi32, 'GetServiceDisplayNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceDisplayNameA]
  end;
end;
{$ELSE}
function GetServiceDisplayNameA; external advapi32 name 'GetServiceDisplayNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceDisplayNameW: Pointer;

function GetServiceDisplayNameW;
begin
  GetProcedureAddress(_GetServiceDisplayNameW, advapi32, 'GetServiceDisplayNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceDisplayNameW]
  end;
end;
{$ELSE}
function GetServiceDisplayNameW; external advapi32 name 'GetServiceDisplayNameW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceDisplayName: Pointer;

function GetServiceDisplayName;
begin
  GetProcedureAddress(_GetServiceDisplayName, advapi32, 'GetServiceDisplayNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceDisplayName]
  end;
end;
{$ELSE}
function GetServiceDisplayName; external advapi32 name 'GetServiceDisplayNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceDisplayName: Pointer;

function GetServiceDisplayName;
begin
  GetProcedureAddress(_GetServiceDisplayName, advapi32, 'GetServiceDisplayNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceDisplayName]
  end;
end;
{$ELSE}
function GetServiceDisplayName; external advapi32 name 'GetServiceDisplayNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _LockServiceDatabase: Pointer;

function LockServiceDatabase;
begin
  GetProcedureAddress(_LockServiceDatabase, advapi32, 'LockServiceDatabase');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LockServiceDatabase]
  end;
end;
{$ELSE}
function LockServiceDatabase; external advapi32 name 'LockServiceDatabase';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _NotifyBootConfigStatus: Pointer;

function NotifyBootConfigStatus;
begin
  GetProcedureAddress(_NotifyBootConfigStatus, advapi32, 'NotifyBootConfigStatus');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NotifyBootConfigStatus]
  end;
end;
{$ELSE}
function NotifyBootConfigStatus; external advapi32 name 'NotifyBootConfigStatus';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _OpenSCManagerA: Pointer;

function OpenSCManagerA;
begin
  GetProcedureAddress(_OpenSCManagerA, advapi32, 'OpenSCManagerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenSCManagerA]
  end;
end;
{$ELSE}
function OpenSCManagerA; external advapi32 name 'OpenSCManagerA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _OpenSCManagerW: Pointer;

function OpenSCManagerW;
begin
  GetProcedureAddress(_OpenSCManagerW, advapi32, 'OpenSCManagerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenSCManagerW]
  end;
end;
{$ELSE}
function OpenSCManagerW; external advapi32 name 'OpenSCManagerW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _OpenSCManager: Pointer;

function OpenSCManager;
begin
  GetProcedureAddress(_OpenSCManager, advapi32, 'OpenSCManagerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenSCManager]
  end;
end;
{$ELSE}
function OpenSCManager; external advapi32 name 'OpenSCManagerW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _OpenSCManager: Pointer;

function OpenSCManager;
begin
  GetProcedureAddress(_OpenSCManager, advapi32, 'OpenSCManagerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenSCManager]
  end;
end;
{$ELSE}
function OpenSCManager; external advapi32 name 'OpenSCManagerA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _OpenServiceA: Pointer;

function OpenServiceA;
begin
  GetProcedureAddress(_OpenServiceA, advapi32, 'OpenServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenServiceA]
  end;
end;
{$ELSE}
function OpenServiceA; external advapi32 name 'OpenServiceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _OpenServiceW: Pointer;

function OpenServiceW;
begin
  GetProcedureAddress(_OpenServiceW, advapi32, 'OpenServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenServiceW]
  end;
end;
{$ELSE}
function OpenServiceW; external advapi32 name 'OpenServiceW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _OpenService: Pointer;

function OpenService;
begin
  GetProcedureAddress(_OpenService, advapi32, 'OpenServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenService]
  end;
end;
{$ELSE}
function OpenService; external advapi32 name 'OpenServiceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _OpenService: Pointer;

function OpenService;
begin
  GetProcedureAddress(_OpenService, advapi32, 'OpenServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_OpenService]
  end;
end;
{$ELSE}
function OpenService; external advapi32 name 'OpenServiceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfigA: Pointer;

function QueryServiceConfigA;
begin
  GetProcedureAddress(_QueryServiceConfigA, advapi32, 'QueryServiceConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfigA]
  end;
end;
{$ELSE}
function QueryServiceConfigA; external advapi32 name 'QueryServiceConfigA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfigW: Pointer;

function QueryServiceConfigW;
begin
  GetProcedureAddress(_QueryServiceConfigW, advapi32, 'QueryServiceConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfigW]
  end;
end;
{$ELSE}
function QueryServiceConfigW; external advapi32 name 'QueryServiceConfigW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfig: Pointer;

function QueryServiceConfig;
begin
  GetProcedureAddress(_QueryServiceConfig, advapi32, 'QueryServiceConfigW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfig]
  end;
end;
{$ELSE}
function QueryServiceConfig; external advapi32 name 'QueryServiceConfigW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfig: Pointer;

function QueryServiceConfig;
begin
  GetProcedureAddress(_QueryServiceConfig, advapi32, 'QueryServiceConfigA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfig]
  end;
end;
{$ELSE}
function QueryServiceConfig; external advapi32 name 'QueryServiceConfigA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfig2A: Pointer;

function QueryServiceConfig2A;
begin
  GetProcedureAddress(_QueryServiceConfig2A, advapi32, 'QueryServiceConfig2A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfig2A]
  end;
end;
{$ELSE}
function QueryServiceConfig2A; external advapi32 name 'QueryServiceConfig2A';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfig2W: Pointer;

function QueryServiceConfig2W;
begin
  GetProcedureAddress(_QueryServiceConfig2W, advapi32, 'QueryServiceConfig2W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfig2W]
  end;
end;
{$ELSE}
function QueryServiceConfig2W; external advapi32 name 'QueryServiceConfig2W';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfig2: Pointer;

function QueryServiceConfig2;
begin
  GetProcedureAddress(_QueryServiceConfig2, advapi32, 'QueryServiceConfig2W');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfig2]
  end;
end;
{$ELSE}
function QueryServiceConfig2; external advapi32 name 'QueryServiceConfig2W';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceConfig2: Pointer;

function QueryServiceConfig2;
begin
  GetProcedureAddress(_QueryServiceConfig2, advapi32, 'QueryServiceConfig2A');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceConfig2]
  end;
end;
{$ELSE}
function QueryServiceConfig2; external advapi32 name 'QueryServiceConfig2A';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceLockStatusA: Pointer;

function QueryServiceLockStatusA;
begin
  GetProcedureAddress(_QueryServiceLockStatusA, advapi32, 'QueryServiceLockStatusA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceLockStatusA]
  end;
end;
{$ELSE}
function QueryServiceLockStatusA; external advapi32 name 'QueryServiceLockStatusA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceLockStatusW: Pointer;

function QueryServiceLockStatusW;
begin
  GetProcedureAddress(_QueryServiceLockStatusW, advapi32, 'QueryServiceLockStatusW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceLockStatusW]
  end;
end;
{$ELSE}
function QueryServiceLockStatusW; external advapi32 name 'QueryServiceLockStatusW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceLockStatus: Pointer;

function QueryServiceLockStatus;
begin
  GetProcedureAddress(_QueryServiceLockStatus, advapi32, 'QueryServiceLockStatusW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceLockStatus]
  end;
end;
{$ELSE}
function QueryServiceLockStatus; external advapi32 name 'QueryServiceLockStatusW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceLockStatus: Pointer;

function QueryServiceLockStatus;
begin
  GetProcedureAddress(_QueryServiceLockStatus, advapi32, 'QueryServiceLockStatusA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceLockStatus]
  end;
end;
{$ELSE}
function QueryServiceLockStatus; external advapi32 name 'QueryServiceLockStatusA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceObjectSecurity: Pointer;

function QueryServiceObjectSecurity;
begin
  GetProcedureAddress(_QueryServiceObjectSecurity, advapi32, 'QueryServiceObjectSecurity');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceObjectSecurity]
  end;
end;
{$ELSE}
function QueryServiceObjectSecurity; external advapi32 name 'QueryServiceObjectSecurity';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceStatus: Pointer;

function QueryServiceStatus;
begin
  GetProcedureAddress(_QueryServiceStatus, advapi32, 'QueryServiceStatus');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceStatus]
  end;
end;
{$ELSE}
function QueryServiceStatus; external advapi32 name 'QueryServiceStatus';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _QueryServiceStatusEx: Pointer;

function QueryServiceStatusEx;
begin
  GetProcedureAddress(_QueryServiceStatusEx, advapi32, 'QueryServiceStatusEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_QueryServiceStatusEx]
  end;
end;
{$ELSE}
function QueryServiceStatusEx; external advapi32 name 'QueryServiceStatusEx';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandlerA: Pointer;

function RegisterServiceCtrlHandlerA;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandlerA, advapi32, 'RegisterServiceCtrlHandlerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandlerA]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandlerA; external advapi32 name 'RegisterServiceCtrlHandlerA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandlerW: Pointer;

function RegisterServiceCtrlHandlerW;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandlerW, advapi32, 'RegisterServiceCtrlHandlerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandlerW]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandlerW; external advapi32 name 'RegisterServiceCtrlHandlerW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandler: Pointer;

function RegisterServiceCtrlHandler;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandler, advapi32, 'RegisterServiceCtrlHandlerW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandler]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandler; external advapi32 name 'RegisterServiceCtrlHandlerW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandler: Pointer;

function RegisterServiceCtrlHandler;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandler, advapi32, 'RegisterServiceCtrlHandlerA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandler]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandler; external advapi32 name 'RegisterServiceCtrlHandlerA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandlerExA: Pointer;

function RegisterServiceCtrlHandlerExA;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandlerExA, advapi32, 'RegisterServiceCtrlHandlerExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandlerExA]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandlerExA; external advapi32 name 'RegisterServiceCtrlHandlerExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandlerExW: Pointer;

function RegisterServiceCtrlHandlerExW;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandlerExW, advapi32, 'RegisterServiceCtrlHandlerExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandlerExW]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandlerExW; external advapi32 name 'RegisterServiceCtrlHandlerExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandlerEx: Pointer;

function RegisterServiceCtrlHandlerEx;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandlerEx, advapi32, 'RegisterServiceCtrlHandlerExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandlerEx]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandlerEx; external advapi32 name 'RegisterServiceCtrlHandlerExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RegisterServiceCtrlHandlerEx: Pointer;

function RegisterServiceCtrlHandlerEx;
begin
  GetProcedureAddress(_RegisterServiceCtrlHandlerEx, advapi32, 'RegisterServiceCtrlHandlerExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RegisterServiceCtrlHandlerEx]
  end;
end;
{$ELSE}
function RegisterServiceCtrlHandlerEx; external advapi32 name 'RegisterServiceCtrlHandlerExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _SetServiceObjectSecurity: Pointer;

function SetServiceObjectSecurity;
begin
  GetProcedureAddress(_SetServiceObjectSecurity, advapi32, 'SetServiceObjectSecurity');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceObjectSecurity]
  end;
end;
{$ELSE}
function SetServiceObjectSecurity; external advapi32 name 'SetServiceObjectSecurity';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceStatus: Pointer;

function SetServiceStatus;
begin
  GetProcedureAddress(_SetServiceStatus, advapi32, 'SetServiceStatus');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceStatus]
  end;
end;
{$ELSE}
function SetServiceStatus; external advapi32 name 'SetServiceStatus';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _StartServiceCtrlDispatcherA: Pointer;

function StartServiceCtrlDispatcherA;
begin
  GetProcedureAddress(_StartServiceCtrlDispatcherA, advapi32, 'StartServiceCtrlDispatcherA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartServiceCtrlDispatcherA]
  end;
end;
{$ELSE}
function StartServiceCtrlDispatcherA; external advapi32 name 'StartServiceCtrlDispatcherA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _StartServiceCtrlDispatcherW: Pointer;

function StartServiceCtrlDispatcherW;
begin
  GetProcedureAddress(_StartServiceCtrlDispatcherW, advapi32, 'StartServiceCtrlDispatcherW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartServiceCtrlDispatcherW]
  end;
end;
{$ELSE}
function StartServiceCtrlDispatcherW; external advapi32 name 'StartServiceCtrlDispatcherW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _StartServiceCtrlDispatcher: Pointer;

function StartServiceCtrlDispatcher;
begin
  GetProcedureAddress(_StartServiceCtrlDispatcher, advapi32, 'StartServiceCtrlDispatcherW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartServiceCtrlDispatcher]
  end;
end;
{$ELSE}
function StartServiceCtrlDispatcher; external advapi32 name 'StartServiceCtrlDispatcherW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _StartServiceCtrlDispatcher: Pointer;

function StartServiceCtrlDispatcher;
begin
  GetProcedureAddress(_StartServiceCtrlDispatcher, advapi32, 'StartServiceCtrlDispatcherA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartServiceCtrlDispatcher]
  end;
end;
{$ELSE}
function StartServiceCtrlDispatcher; external advapi32 name 'StartServiceCtrlDispatcherA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _StartServiceA: Pointer;

function StartServiceA;
begin
  GetProcedureAddress(_StartServiceA, advapi32, 'StartServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartServiceA]
  end;
end;
{$ELSE}
function StartServiceA; external advapi32 name 'StartServiceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _StartServiceW: Pointer;

function StartServiceW;
begin
  GetProcedureAddress(_StartServiceW, advapi32, 'StartServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartServiceW]
  end;
end;
{$ELSE}
function StartServiceW; external advapi32 name 'StartServiceW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _StartService: Pointer;

function StartService;
begin
  GetProcedureAddress(_StartService, advapi32, 'StartServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartService]
  end;
end;
{$ELSE}
function StartService; external advapi32 name 'StartServiceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _StartService: Pointer;

function StartService;
begin
  GetProcedureAddress(_StartService, advapi32, 'StartServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_StartService]
  end;
end;
{$ELSE}
function StartService; external advapi32 name 'StartServiceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _UnlockServiceDatabase: Pointer;

function UnlockServiceDatabase;
begin
  GetProcedureAddress(_UnlockServiceDatabase, advapi32, 'UnlockServiceDatabase');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnlockServiceDatabase]
  end;
end;
{$ELSE}
function UnlockServiceDatabase; external advapi32 name 'UnlockServiceDatabase';
{$ENDIF DYNAMIC_LINK}

end.
