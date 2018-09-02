{******************************************************************************}
{                                                       	               }
{ Lan Manager Remote API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmremutl.h, released November 2001. The original Pascal}
{ code is: LmRemUtl.pas, released Februari 2002. The initial developer of the  }
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

unit JwaLmRemUtl;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmremutl.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// Type Definitions
//

type
{$IFNDEF DESC_CHAR_UNICODE}
  DESC_CHAR = CHAR;
  {$EXTERNALSYM DESC_CHAR}
{$ELSE}
  DESC_CHAR = WCHAR;
  {$EXTERNALSYM DESC_CHAR}
{$ENDIF}
  TDescChar = DESC_CHAR;

  LPDESC = ^DESC_CHAR;
  {$EXTERNALSYM LPDESC}
  PDesc = LPDESC;

//
// Function Prototypes
//

function NetRemoteTOD(UncServerName: LPCWSTR; var BufferPtr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetRemoteTOD}

function NetRemoteComputerSupports(UncServerName: LPCWSTR; OptionsWanted: DWORD; OptionsSupported: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetRemoteComputerSupports}

{$IFDEF VER140}
// mvb Delphi 6 and up only (because of the varargs)
function RxRemoteApi(ApiNumber: DWORD; UncServerName: LPCWSTR; ParmDescString, DataDesc16, DataDesc32, DataDescSmb,
  AuxDesc16, AuxDesc32, AuxDescSmb: LPDESC; Flags: DWORD{, ...}): NET_API_STATUS; cdecl; varargs;
{$EXTERNALSYM RxRemoteApi}
{$ENDIF}

//
//  Data Structures
//

type
  _TIME_OF_DAY_INFO = record
    tod_elapsedt: DWORD;
    tod_msecs: DWORD;
    tod_hours: DWORD;
    tod_mins: DWORD;
    tod_secs: DWORD;
    tod_hunds: DWORD;
    tod_timezone: LONG;
    tod_tinterval: DWORD;
    tod_day: DWORD;
    tod_month: DWORD;
    tod_year: DWORD;
    tod_weekday: DWORD;
  end;
  {$EXTERNALSYM _TIME_OF_DAY_INFO}
  TIME_OF_DAY_INFO = _TIME_OF_DAY_INFO;
  {$EXTERNALSYM TIME_OF_DAY_INFO}
  PTIME_OF_DAY_INFO = ^TIME_OF_DAY_INFO;
  {$EXTERNALSYM PTIME_OF_DAY_INFO}
  LPTIME_OF_DAY_INFO = ^TIME_OF_DAY_INFO;
  {$EXTERNALSYM LPTIME_OF_DAY_INFO}
  TTimeOfDayInfo = TIME_OF_DAY_INFO;
  PTimeOfDayInfo = PTIME_OF_DAY_INFO;  

//
// Special Values and Constants
//

//
// Mask bits for use with NetRemoteComputerSupports:
//

const
  SUPPORTS_REMOTE_ADMIN_PROTOCOL = $00000002;
  {$EXTERNALSYM SUPPORTS_REMOTE_ADMIN_PROTOCOL}
  SUPPORTS_RPC                   = $00000004;
  {$EXTERNALSYM SUPPORTS_RPC}
  SUPPORTS_SAM_PROTOCOL          = $00000008;
  {$EXTERNALSYM SUPPORTS_SAM_PROTOCOL}
  SUPPORTS_UNICODE               = $00000010;
  {$EXTERNALSYM SUPPORTS_UNICODE}
  SUPPORTS_LOCAL                 = $00000020;
  {$EXTERNALSYM SUPPORTS_LOCAL}
  SUPPORTS_ANY                   = DWORD($FFFFFFFF);
  {$EXTERNALSYM SUPPORTS_ANY}

//
// Flag bits for RxRemoteApi:
//

const
  NO_PERMISSION_REQUIRED = $00000001;      // set if use NULL session
  {$EXTERNALSYM NO_PERMISSION_REQUIRED}
  ALLOCATE_RESPONSE      = $00000002;      // set if RxRemoteApi allocates response buffer
  {$EXTERNALSYM ALLOCATE_RESPONSE}
  USE_SPECIFIC_TRANSPORT = DWORD($80000000);
  {$EXTERNALSYM USE_SPECIFIC_TRANSPORT}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetRemoteTOD: Pointer;

function NetRemoteTOD;
begin
  GetProcedureAddress(_NetRemoteTOD, netapi32, 'NetRemoteTOD');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetRemoteTOD]
  end;
end;
{$ELSE}
function NetRemoteTOD; external netapi32 name 'NetRemoteTOD';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetRemoteComputerSupports: Pointer;

function NetRemoteComputerSupports;
begin
  GetProcedureAddress(_NetRemoteComputerSupports, netapi32, 'NetRemoteComputerSupports');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetRemoteComputerSupports]
  end;
end;
{$ELSE}
function NetRemoteComputerSupports; external netapi32 name 'NetRemoteComputerSupports';
{$ENDIF DYNAMIC_LINK}

// todo cdecl function so no dynamic linking for the time being...

{$IFDEF VER140}
function RxRemoteApi; external netapi32 name 'RxRemoteApi';
{$ENDIF}


end.
