{******************************************************************************}
{                                                       	               }
{ Lan Manager Scheduler API interface Unit for Object Pascal                   }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmat.h, released November 2001. The original Pascal    }
{ code is: LmAt.pas, released Februari 2002. The initial developer of the      }
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

unit JwaLmAt;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmat.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
//  The following bits are used with Flags field in structures below.
//

//
//  Do we exec programs for this job periodically (/EVERY switch)
//  or one time (/NEXT switch).
//

const
  JOB_RUN_PERIODICALLY           = $01;    //  set if EVERY
  {$EXTERNALSYM JOB_RUN_PERIODICALLY}

//
//  Was there an error last time we tried to exec a program on behalf of
//  this job.
//  This flag is meaningfull on output only!
//

  JOB_EXEC_ERROR                 = $02;    //  set if error
  {$EXTERNALSYM JOB_EXEC_ERROR}

//
//  Will this job run today or tomorrow.
//  This flag is meaningfull on output only!
//

  JOB_RUNS_TODAY                 = $04;    //  set if today
  {$EXTERNALSYM JOB_RUNS_TODAY}

//
//  Add current day of the month to DaysOfMonth input.
//  This flag is meaningfull on input only!
//

  JOB_ADD_CURRENT_DATE            = $08;    // set if to add current date
  {$EXTERNALSYM JOB_ADD_CURRENT_DATE}

//
//  Will this job be run interactively or not.  Windows NT 3.1 do not
//  know about this bit, i.e. they submit interactive jobs only.
//

  JOB_NONINTERACTIVE              = $10;    // set for noninteractive
  {$EXTERNALSYM JOB_NONINTERACTIVE}

  JOB_INPUT_FLAGS = JOB_RUN_PERIODICALLY or JOB_ADD_CURRENT_DATE or JOB_NONINTERACTIVE;
  {$EXTERNALSYM JOB_INPUT_FLAGS}

  JOB_OUTPUT_FLAGS = JOB_RUN_PERIODICALLY or JOB_EXEC_ERROR or JOB_RUNS_TODAY or JOB_NONINTERACTIVE;
  {$EXTERNALSYM JOB_OUTPUT_FLAGS}

type
  _AT_INFO = record
    JobTime: DWORD_PTR;
    DaysOfMonth: DWORD;
    DaysOfWeek: UCHAR;
    Flags: UCHAR;
    Command: LPWSTR;
  end;
  {$EXTERNALSYM _AT_INFO}
  AT_INFO = _AT_INFO;
  {$EXTERNALSYM AT_INFO}
  PAT_INFO = ^AT_INFO;
  {$EXTERNALSYM PAT_INFO}
  LPAT_INFO = ^AT_INFO;
  {$EXTERNALSYM LPAT_INFO}
  TAtInfo = AT_INFO;
  PAtInfo = PAT_INFO;

  _AT_ENUM = record
    JobId: DWORD;
    JobTime: DWORD_PTR;
    DaysOfMonth: DWORD;
    DaysOfWeek: UCHAR;
    Flags: UCHAR;
    Command: LPWSTR;
  end;
  {$EXTERNALSYM _AT_ENUM}
  AT_ENUM = _AT_ENUM;
  {$EXTERNALSYM AT_ENUM}
  PAT_ENUM = ^AT_ENUM;
  {$EXTERNALSYM PAT_ENUM}
  LPAT_ENUM = ^AT_ENUM;
  {$EXTERNALSYM LPAT_ENUM}
  TAtEnum = AT_ENUM;
  PAtEnum = PAT_ENUM;  

function NetScheduleJobAdd(Servername: LPCWSTR; Buffer: LPBYTE; JobId: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetScheduleJobAdd}

function NetScheduleJobDel(Servername: LPCWSTR; MinJobId, MaxJobId: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetScheduleJobDel}

function NetScheduleJobEnum(Servername: LPCWSTR; var PointerToBuffer: LPBYTE; PrefferedMaximumLength: DWORD; EntriesRead, TotalEntries, ResumeHandle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetScheduleJobEnum}

function NetScheduleJobGetInfo(Servername: LPCWSTR; JobId: DWORD; var PointerToBuffer: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetScheduleJobGetInfo}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobAdd: Pointer;

function NetScheduleJobAdd;
begin
  GetProcedureAddress(_NetScheduleJobAdd, netapi32, 'NetScheduleJobAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobAdd]
  end;
end;
{$ELSE}
function NetScheduleJobAdd; external netapi32 name 'NetScheduleJobAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobDel: Pointer;

function NetScheduleJobDel;
begin
  GetProcedureAddress(_NetScheduleJobDel, netapi32, 'NetScheduleJobDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobDel]
  end;
end;
{$ELSE}
function NetScheduleJobDel; external netapi32 name 'NetScheduleJobDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobEnum: Pointer;

function NetScheduleJobEnum;
begin
  GetProcedureAddress(_NetScheduleJobEnum, netapi32, 'NetScheduleJobEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobEnum]
  end;
end;
{$ELSE}
function NetScheduleJobEnum; external netapi32 name 'NetScheduleJobEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetScheduleJobGetInfo: Pointer;

function NetScheduleJobGetInfo;
begin
  GetProcedureAddress(_NetScheduleJobGetInfo, netapi32, 'NetScheduleJobGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetScheduleJobGetInfo]
  end;
end;
{$ELSE}
function NetScheduleJobGetInfo; external netapi32 name 'NetScheduleJobGetInfo';
{$ENDIF DYNAMIC_LINK}

end.
