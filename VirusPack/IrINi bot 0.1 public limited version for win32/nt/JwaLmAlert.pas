{******************************************************************************}
{                                                       	               }
{ Lan Manager Alterter API interface Unit for Object Pascal                    }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmalert.h, released November 2001. The original Pascal }
{ code is: LmAlert.pas, released Februari 2002. The initial developer of the   }
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

unit JwaLmAlert;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmalert.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// Function Prototypes
//

function NetAlertRaise(AlertEventName: LPCWSTR; Buffer: LPVOID; BufferSize: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAlertRaise}

function NetAlertRaiseEx(AlertEventName: LPCWSTR; VariableInfo: LPVOID; VariableInfoSize: DWORD; ServiceName: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAlertRaiseEx}


//
//  Data Structures
//

type
  _STD_ALERT = record
    alrt_timestamp: DWORD;
    alrt_eventname: array [0..EVLEN] of WCHAR;
    alrt_servicename: array [0..SNLEN] of WCHAR;
  end;
  {$EXTERNALSYM _STD_ALERT}
  STD_ALERT = _STD_ALERT;
  {$EXTERNALSYM STD_ALERT}
  PSTD_ALERT = ^STD_ALERT;
  {$EXTERNALSYM PSTD_ALERT}
  LPSTD_ALERT = ^STD_ALERT;
  {$EXTERNALSYM LPSTD_ALERT}
  TStdAlert = STD_ALERT;
  PStdAlert = PSTD_ALERT;

  _ADMIN_OTHER_INFO = record
    alrtad_errcode: DWORD;
    alrtad_numstrings: DWORD;
  end;
  {$EXTERNALSYM _ADMIN_OTHER_INFO}
  ADMIN_OTHER_INFO = _ADMIN_OTHER_INFO;
  {$EXTERNALSYM ADMIN_OTHER_INFO}
  PADMIN_OTHER_INFO = ^ADMIN_OTHER_INFO;
  {$EXTERNALSYM PADMIN_OTHER_INFO}
  LPADMIN_OTHER_INFO = ^ADMIN_OTHER_INFO;
  {$EXTERNALSYM LPADMIN_OTHER_INFO}
  TAdminOtherInfo = ADMIN_OTHER_INFO;
  PAdminOtherInfo = PADMIN_OTHER_INFO;

  _ERRLOG_OTHER_INFO = record
    alrter_errcode: DWORD;
    alrter_offset: DWORD;
  end;
  {$EXTERNALSYM _ERRLOG_OTHER_INFO}
  ERRLOG_OTHER_INFO = _ERRLOG_OTHER_INFO;
  {$EXTERNALSYM ERRLOG_OTHER_INFO}
  PERRLOG_OTHER_INFO = ^ERRLOG_OTHER_INFO;
  {$EXTERNALSYM PERRLOG_OTHER_INFO}
  LPERRLOG_OTHER_INFO = ^ERRLOG_OTHER_INFO;
  {$EXTERNALSYM LPERRLOG_OTHER_INFO}
  TErrlogOtherInfo = ERRLOG_OTHER_INFO;
  PErrlogOtherInfo = PERRLOG_OTHER_INFO;

  _PRINT_OTHER_INFO = record
    alrtpr_jobid: DWORD;
    alrtpr_status: DWORD;
    alrtpr_submitted: DWORD;
    alrtpr_size: DWORD;
  end;
  {$EXTERNALSYM _PRINT_OTHER_INFO}
  PRINT_OTHER_INFO = _PRINT_OTHER_INFO;
  {$EXTERNALSYM PRINT_OTHER_INFO}
  PPRINT_OTHER_INFO = ^PRINT_OTHER_INFO;
  {$EXTERNALSYM PPRINT_OTHER_INFO}
  LPPRINT_OTHER_INFO = ^PRINT_OTHER_INFO;
  {$EXTERNALSYM LPPRINT_OTHER_INFO}
  TPrintOtherInfo = PRINT_OTHER_INFO;
  PPrintOtherInfo = PPRINT_OTHER_INFO;

  _USER_OTHER_INFO = record
    alrtus_errcode: DWORD;
    alrtus_numstrings: DWORD;
  end;
  {$EXTERNALSYM _USER_OTHER_INFO}
  USER_OTHER_INFO = _USER_OTHER_INFO;
  {$EXTERNALSYM USER_OTHER_INFO}
  PUSER_OTHER_INFO = ^USER_OTHER_INFO;
  {$EXTERNALSYM PUSER_OTHER_INFO}
  LPUSER_OTHER_INFO = ^USER_OTHER_INFO;
  {$EXTERNALSYM LPUSER_OTHER_INFO}
  TUserOtherInfo = USER_OTHER_INFO;
  PUserOtherInfo = PUSER_OTHER_INFO;

//
// Special Values and Constants
//

//
// Name of mailslot to send alert notifications
//

const
  ALERTER_MAILSLOT = WideString('\\.\MAILSLOT\Alerter');
  {$EXTERNALSYM ALERTER_MAILSLOT}

//
// The following macro gives a pointer to the other_info data.
// It takes an alert structure and returns a pointer to structure
// beyond the standard portion.
//

function ALERT_OTHER_INFO(x: Pointer): Pointer;
{$EXTERNALSYM ALERT_OTHER_INFO}

//
// The following macro gives a pointer to the variable-length data.
// It takes a pointer to one of the other-info structs and returns a
// pointer to the variable data portion.
//

function ALERT_VAR_DATA(const p): Pointer;
{$EXTERNALSYM ALERT_VAR_DATA}

//
//      Names of standard Microsoft-defined alert events.
//

const
  ALERT_PRINT_EVENT    = WideString('PRINTING');
  {$EXTERNALSYM ALERT_PRINT_EVENT}
  ALERT_MESSAGE_EVENT  = WideString('MESSAGE');
  {$EXTERNALSYM ALERT_MESSAGE_EVENT}
  ALERT_ERRORLOG_EVENT = WideString('ERRORLOG');
  {$EXTERNALSYM ALERT_ERRORLOG_EVENT}
  ALERT_ADMIN_EVENT    = WideString('ADMIN');
  {$EXTERNALSYM ALERT_ADMIN_EVENT}
  ALERT_USER_EVENT     = WideString('USER');
  {$EXTERNALSYM ALERT_USER_EVENT}

//
//      Bitmap masks for prjob_status field of PRINTJOB.
//

// 2-7 bits also used in device status

  PRJOB_QSTATUS     = $3; // Bits 0,1
  {$EXTERNALSYM PRJOB_QSTATUS}
  PRJOB_DEVSTATUS   = $1fc; // 2-8 bits
  {$EXTERNALSYM PRJOB_DEVSTATUS}
  PRJOB_COMPLETE    = $4; // Bit 2
  {$EXTERNALSYM PRJOB_COMPLETE}
  PRJOB_INTERV      = $8; // Bit 3
  {$EXTERNALSYM PRJOB_INTERV}
  PRJOB_ERROR       = $10; // Bit 4
  {$EXTERNALSYM PRJOB_ERROR}
  PRJOB_DESTOFFLINE = $20; // Bit 5
  {$EXTERNALSYM PRJOB_DESTOFFLINE}
  PRJOB_DESTPAUSED  = $40; // Bit 6
  {$EXTERNALSYM PRJOB_DESTPAUSED}
  PRJOB_NOTIFY      = $80; // BIT 7
  {$EXTERNALSYM PRJOB_NOTIFY}
  PRJOB_DESTNOPAPER = $100; // BIT 8
  {$EXTERNALSYM PRJOB_DESTNOPAPER}
  PRJOB_DELETED     = $8000; // BIT 15
  {$EXTERNALSYM PRJOB_DELETED}

//
//      Values of PRJOB_QSTATUS bits in prjob_status field of PRINTJOB.
//

  PRJOB_QS_QUEUED   = 0;
  {$EXTERNALSYM PRJOB_QS_QUEUED}
  PRJOB_QS_PAUSED   = 1;
  {$EXTERNALSYM PRJOB_QS_PAUSED}
  PRJOB_QS_SPOOLING = 2;
  {$EXTERNALSYM PRJOB_QS_SPOOLING}
  PRJOB_QS_PRINTING = 3;
  {$EXTERNALSYM PRJOB_QS_PRINTING}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetAlertRaise: Pointer;

function NetAlertRaise;
begin
  GetProcedureAddress(_NetAlertRaise, netapi32, 'NetAlertRaise');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAlertRaise]
  end;
end;
{$ELSE}
function NetAlertRaise; external netapi32 name 'NetAlertRaise';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAlertRaiseEx: Pointer;

function NetAlertRaiseEx;
begin
  GetProcedureAddress(_NetAlertRaiseEx, netapi32, 'NetAlertRaiseEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAlertRaiseEx]
  end;
end;
{$ELSE}
function NetAlertRaiseEx; external netapi32 name 'NetAlertRaiseEx';
{$ENDIF DYNAMIC_LINK}

//#define ALERT_OTHER_INFO(x)    ((LPBYTE)(x) + sizeof(STD_ALERT))

function ALERT_OTHER_INFO(x: Pointer): Pointer;
begin
  Result := Pointer(Integer(x) + SizeOf(STD_ALERT));
end;

//#define ALERT_VAR_DATA(p)      ((LPBYTE)(p) + sizeof(*p))

function ALERT_VAR_DATA(const p): Pointer;
begin
  Result := Pointer(Integer(p) + SizeOf(p)); // todo check!
end;


end.
