{******************************************************************************}
{                                                       	               }
{ Lan Manager Replicator API interface Unit for Object Pascal                  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmrepl.h, released November 2001. The original Pascal  }
{ code is: LmRepl.pas, released Februari 2002. The initial developer of the    }
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

unit JwaLmRepl;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmrepl.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// Replicator Configuration APIs
//

const
  REPL_ROLE_EXPORT = 1;
  {$EXTERNALSYM REPL_ROLE_EXPORT}
  REPL_ROLE_IMPORT = 2;
  {$EXTERNALSYM REPL_ROLE_IMPORT}
  REPL_ROLE_BOTH   = 3;
  {$EXTERNALSYM REPL_ROLE_BOTH}

  REPL_INTERVAL_INFOLEVEL  = (PARMNUM_BASE_INFOLEVEL + 0);
  {$EXTERNALSYM REPL_INTERVAL_INFOLEVEL}
  REPL_PULSE_INFOLEVEL     = (PARMNUM_BASE_INFOLEVEL + 1);
  {$EXTERNALSYM REPL_PULSE_INFOLEVEL}
  REPL_GUARDTIME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + 2);
  {$EXTERNALSYM REPL_GUARDTIME_INFOLEVEL}
  REPL_RANDOM_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + 3);
  {$EXTERNALSYM REPL_RANDOM_INFOLEVEL}

type
  _REPL_INFO_0 = record
    rp0_role: DWORD;
    rp0_exportpath: LPWSTR;
    rp0_exportlist: LPWSTR;
    rp0_importpath: LPWSTR;
    rp0_importlist: LPWSTR;
    rp0_logonusername: LPWSTR;
    rp0_interval: DWORD;
    rp0_pulse: DWORD;
    rp0_guardtime: DWORD;
    rp0_random: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_0}
  REPL_INFO_0 = _REPL_INFO_0;
  {$EXTERNALSYM REPL_INFO_0}
  LPREPL_INFO_0 = ^REPL_INFO_0;
  {$EXTERNALSYM LPREPL_INFO_0}
  PREPL_INFO_0 = ^REPL_INFO_0;
  {$EXTERNALSYM PREPL_INFO_0}
  TReplInfo0 = REPL_INFO_0;
  PReplInfo0 = PREPL_INFO_0;

  _REPL_INFO_1000 = record
    rp1000_interval: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1000}
  REPL_INFO_1000 = _REPL_INFO_1000;
  {$EXTERNALSYM REPL_INFO_1000}
  LPREPL_INFO_1000 = ^REPL_INFO_1000;
  {$EXTERNALSYM LPREPL_INFO_1000}
  PREPL_INFO_1000 = ^REPL_INFO_1000;
  {$EXTERNALSYM PREPL_INFO_1000}
  TReplInfo1000 = REPL_INFO_1000;
  PReplInfo1000 = PREPL_INFO_1000;

  _REPL_INFO_1001 = record
    rp1001_pulse: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1001}
  REPL_INFO_1001 = _REPL_INFO_1001;
  {$EXTERNALSYM REPL_INFO_1001}
  LPREPL_INFO_1001 = ^REPL_INFO_1001;
  {$EXTERNALSYM LPREPL_INFO_1001}
  PREPL_INFO_1001 = ^REPL_INFO_1001;
  {$EXTERNALSYM PREPL_INFO_1001}
  TReplInfo1001 = REPL_INFO_1001;
  PReplInfo1001 = PREPL_INFO_1001;

  _REPL_INFO_1002 = record
    rp1002_guardtime: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1002}
  REPL_INFO_1002 = _REPL_INFO_1002;
  {$EXTERNALSYM REPL_INFO_1002}
  LPREPL_INFO_1002 = ^REPL_INFO_1002;
  {$EXTERNALSYM LPREPL_INFO_1002}
  PREPL_INFO_1002 = ^REPL_INFO_1002;
  {$EXTERNALSYM PREPL_INFO_1002}
  TReplInfo1002 = REPL_INFO_1002;
  PReplInfo1002 = PREPL_INFO_1002;

  _REPL_INFO_1003 = record
    rp1003_random: DWORD;
  end;
  {$EXTERNALSYM _REPL_INFO_1003}
  REPL_INFO_1003 = _REPL_INFO_1003;
  {$EXTERNALSYM REPL_INFO_1003}
  LPREPL_INFO_1003 = ^REPL_INFO_1003;
  {$EXTERNALSYM LPREPL_INFO_1003}
  PREPL_INFO_1003 = ^REPL_INFO_1003;
  {$EXTERNALSYM PREPL_INFO_1003}
  TReplInfo1003 = REPL_INFO_1003;
  PReplInfo1003 = PREPL_INFO_1003;

function NetReplGetInfo(servername: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplGetInfo}

function NetReplSetInfo(servername: LPCWSTR; level: DWORD; buf: LPBYTE ; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplSetInfo}

//
// Replicator Export Directory APIs
//

const
  REPL_INTEGRITY_FILE = 1;
  {$EXTERNALSYM REPL_INTEGRITY_FILE}
  REPL_INTEGRITY_TREE = 2;
  {$EXTERNALSYM REPL_INTEGRITY_TREE}

  REPL_EXTENT_FILE = 1;
  {$EXTERNALSYM REPL_EXTENT_FILE}
  REPL_EXTENT_TREE = 2;
  {$EXTERNALSYM REPL_EXTENT_TREE}

  REPL_EXPORT_INTEGRITY_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + 0);
  {$EXTERNALSYM REPL_EXPORT_INTEGRITY_INFOLEVEL}
  REPL_EXPORT_EXTENT_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + 1);
  {$EXTERNALSYM REPL_EXPORT_EXTENT_INFOLEVEL}

type
  _REPL_EDIR_INFO_0 = record
    rped0_dirname: LPWSTR;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_0}
  REPL_EDIR_INFO_0 = _REPL_EDIR_INFO_0;
  {$EXTERNALSYM REPL_EDIR_INFO_0}
  LPREPL_EDIR_INFO_0 = ^REPL_EDIR_INFO_0;
  {$EXTERNALSYM LPREPL_EDIR_INFO_0}
  PREPL_EDIR_INFO_0 = ^REPL_EDIR_INFO_0;
  {$EXTERNALSYM PREPL_EDIR_INFO_0}
  TReplEdirInfo0 = REPL_EDIR_INFO_0;
  PReplEdirInfo0 = PREPL_EDIR_INFO_0;

  _REPL_EDIR_INFO_1 = record
    rped1_dirname: LPWSTR;
    rped1_integrity: DWORD;
    rped1_extent: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_1}
  REPL_EDIR_INFO_1 = _REPL_EDIR_INFO_1;
  {$EXTERNALSYM REPL_EDIR_INFO_1}
  LPREPL_EDIR_INFO_1 = ^REPL_EDIR_INFO_1;
  {$EXTERNALSYM LPREPL_EDIR_INFO_1}
  PREPL_EDIR_INFO_1 = ^REPL_EDIR_INFO_1;
  {$EXTERNALSYM PREPL_EDIR_INFO_1}
  TReplEdirInfo1 = REPL_EDIR_INFO_1;
  PReplEdirInfo1 = PREPL_EDIR_INFO_1;

  _REPL_EDIR_INFO_2 = record
    rped2_dirname: LPWSTR;
    rped2_integrity: DWORD;
    rped2_extent: DWORD;
    rped2_lockcount: DWORD;
    rped2_locktime: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_2}
  REPL_EDIR_INFO_2 = _REPL_EDIR_INFO_2;
  {$EXTERNALSYM REPL_EDIR_INFO_2}
  LPREPL_EDIR_INFO_2 = ^REPL_EDIR_INFO_2;
  {$EXTERNALSYM LPREPL_EDIR_INFO_2}
  PREPL_EDIR_INFO_2 = ^REPL_EDIR_INFO_2;
  {$EXTERNALSYM PREPL_EDIR_INFO_2}
  TReplEdirInfo2 = REPL_EDIR_INFO_2;
  PReplEdirInfo2 = PREPL_EDIR_INFO_2;

  _REPL_EDIR_INFO_1000 = record
    rped1000_integrity: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_1000}
  REPL_EDIR_INFO_1000 = _REPL_EDIR_INFO_1000;
  {$EXTERNALSYM REPL_EDIR_INFO_1000}
  LPREPL_EDIR_INFO_1000 = ^REPL_EDIR_INFO_1000;
  {$EXTERNALSYM LPREPL_EDIR_INFO_1000}
  PREPL_EDIR_INFO_1000 = ^REPL_EDIR_INFO_1000;
  {$EXTERNALSYM PREPL_EDIR_INFO_1000}
  TReplEdirInfo1000 = REPL_EDIR_INFO_1000;
  PReplEdirInfo1000 = PREPL_EDIR_INFO_1000;

  _REPL_EDIR_INFO_1001 = record
    rped1001_extent: DWORD;
  end;
  {$EXTERNALSYM _REPL_EDIR_INFO_1001}
  REPL_EDIR_INFO_1001 = _REPL_EDIR_INFO_1001;
  {$EXTERNALSYM REPL_EDIR_INFO_1001}
  LPREPL_EDIR_INFO_1001 = ^REPL_EDIR_INFO_1001;
  {$EXTERNALSYM LPREPL_EDIR_INFO_1001}
  PREPL_EDIR_INFO_1001 = ^REPL_EDIR_INFO_1001;
  {$EXTERNALSYM PREPL_EDIR_INFO_1001}
  TReplEdirInfo1001 = REPL_EDIR_INFO_1001;
  PReplEdirInfo1001 = PREPL_EDIR_INFO_1001;

function NetReplExportDirAdd(servername: LPCWSTR; level: DWORD; buf: LPBYTE ; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirAdd}

function NetReplExportDirDel(servername: LPCWSTR; dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirDel}

function NetReplExportDirEnum(servername: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resumehandle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirEnum}

function NetReplExportDirGetInfo(servername, dirname: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirGetInfo}

function NetReplExportDirSetInfo(servername, dirname: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirSetInfo}

function NetReplExportDirLock(servername: LPCWSTR; dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirLock}

function NetReplExportDirUnlock(servername: LPCWSTR; dirname: LPCWSTR; unlockforce: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplExportDirUnlock}

const
  REPL_UNLOCK_NOFORCE = 0;
  {$EXTERNALSYM REPL_UNLOCK_NOFORCE}
  REPL_UNLOCK_FORCE   = 1;
  {$EXTERNALSYM REPL_UNLOCK_FORCE}

//
// Replicator Import Directory APIs
//

type
  _REPL_IDIR_INFO_0 = record
    rpid0_dirname: LPWSTR;
  end;
  {$EXTERNALSYM _REPL_IDIR_INFO_0}
  REPL_IDIR_INFO_0 = _REPL_IDIR_INFO_0;
  {$EXTERNALSYM REPL_IDIR_INFO_0}
  LPREPL_IDIR_INFO_0 = ^REPL_IDIR_INFO_0;
  {$EXTERNALSYM LPREPL_IDIR_INFO_0}
  PREPL_IDIR_INFO_0 = ^REPL_IDIR_INFO_0;
  {$EXTERNALSYM PREPL_IDIR_INFO_0}
  TReplIdirInfo0 = REPL_IDIR_INFO_0;
  PReplIdirInfo0 = PREPL_IDIR_INFO_0;

  _REPL_IDIR_INFO_1 = record
    rpid1_dirname: LPWSTR;
    rpid1_state: DWORD;
    rpid1_mastername: LPWSTR;
    rpid1_last_update_time: DWORD;
    rpid1_lockcount: DWORD;
    rpid1_locktime: DWORD;
  end;
  {$EXTERNALSYM _REPL_IDIR_INFO_1}
  REPL_IDIR_INFO_1 = _REPL_IDIR_INFO_1;
  {$EXTERNALSYM REPL_IDIR_INFO_1}
  LPREPL_IDIR_INFO_1 = ^REPL_IDIR_INFO_1;
  {$EXTERNALSYM LPREPL_IDIR_INFO_1}
  PREPL_IDIR_INFO_1 = ^REPL_IDIR_INFO_1;
  {$EXTERNALSYM PREPL_IDIR_INFO_1}
  TReplIdirInfo1 = REPL_IDIR_INFO_1;
  PReplIdirInfo1 = PREPL_IDIR_INFO_1;

function NetReplImportDirAdd(servername: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirAdd}

function NetReplImportDirDel(servername: LPCWSTR; dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirDel}

function NetReplImportDirEnum(servername: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resumehandle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirEnum}

function NetReplImportDirGetInfo(servername, dirname: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirGetInfo}

function NetReplImportDirLock(servername: LPCWSTR; dirname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirLock}

function NetReplImportDirUnlock(servername: LPCWSTR; dirname: LPCWSTR; unlockforce: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetReplImportDirUnlock}

const
  REPL_STATE_OK               = 0;
  {$EXTERNALSYM REPL_STATE_OK}
  REPL_STATE_NO_MASTER        = 1;
  {$EXTERNALSYM REPL_STATE_NO_MASTER}
  REPL_STATE_NO_SYNC          = 2;
  {$EXTERNALSYM REPL_STATE_NO_SYNC}
  REPL_STATE_NEVER_REPLICATED = 3;
  {$EXTERNALSYM REPL_STATE_NEVER_REPLICATED}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetReplGetInfo: Pointer;

function NetReplGetInfo;
begin
  GetProcedureAddress(_NetReplGetInfo, netapi32, 'NetReplGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplGetInfo]
  end;
end;
{$ELSE}
function NetReplGetInfo; external netapi32 name 'NetReplGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplSetInfo: Pointer;

function NetReplSetInfo;
begin
  GetProcedureAddress(_NetReplSetInfo, netapi32, 'NetReplSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplSetInfo]
  end;
end;
{$ELSE}
function NetReplSetInfo; external netapi32 name 'NetReplSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirAdd: Pointer;

function NetReplExportDirAdd;
begin
  GetProcedureAddress(_NetReplExportDirAdd, netapi32, 'NetReplExportDirAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirAdd]
  end;
end;
{$ELSE}
function NetReplExportDirAdd; external netapi32 name 'NetReplExportDirAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirDel: Pointer;

function NetReplExportDirDel;
begin
  GetProcedureAddress(_NetReplExportDirDel, netapi32, 'NetReplExportDirDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirDel]
  end;
end;
{$ELSE}
function NetReplExportDirDel; external netapi32 name 'NetReplExportDirDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirEnum: Pointer;

function NetReplExportDirEnum;
begin
  GetProcedureAddress(_NetReplExportDirEnum, netapi32, 'NetReplExportDirEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirEnum]
  end;
end;
{$ELSE}
function NetReplExportDirEnum; external netapi32 name 'NetReplExportDirEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirGetInfo: Pointer;

function NetReplExportDirGetInfo;
begin
  GetProcedureAddress(_NetReplExportDirGetInfo, netapi32, 'NetReplExportDirGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirGetInfo]
  end;
end;
{$ELSE}
function NetReplExportDirGetInfo; external netapi32 name 'NetReplExportDirGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirSetInfo: Pointer;

function NetReplExportDirSetInfo;
begin
  GetProcedureAddress(_NetReplExportDirSetInfo, netapi32, 'NetReplExportDirSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirSetInfo]
  end;
end;
{$ELSE}
function NetReplExportDirSetInfo; external netapi32 name 'NetReplExportDirSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirLock: Pointer;

function NetReplExportDirLock;
begin
  GetProcedureAddress(_NetReplExportDirLock, netapi32, 'NetReplExportDirLock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirLock]
  end;
end;
{$ELSE}
function NetReplExportDirLock; external netapi32 name 'NetReplExportDirLock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplExportDirUnlock: Pointer;

function NetReplExportDirUnlock;
begin
  GetProcedureAddress(_NetReplExportDirUnlock, netapi32, 'NetReplExportDirUnlock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplExportDirUnlock]
  end;
end;
{$ELSE}
function NetReplExportDirUnlock; external netapi32 name 'NetReplExportDirUnlock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirAdd: Pointer;

function NetReplImportDirAdd;
begin
  GetProcedureAddress(_NetReplImportDirAdd, netapi32, 'NetReplImportDirAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirAdd]
  end;
end;
{$ELSE}
function NetReplImportDirAdd; external netapi32 name 'NetReplImportDirAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirDel: Pointer;

function NetReplImportDirDel;
begin
  GetProcedureAddress(_NetReplImportDirDel, netapi32, 'NetReplImportDirDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirDel]
  end;
end;
{$ELSE}
function NetReplImportDirDel; external netapi32 name 'NetReplImportDirDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirEnum: Pointer;

function NetReplImportDirEnum;
begin
  GetProcedureAddress(_NetReplImportDirEnum, netapi32, 'NetReplImportDirEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirEnum]
  end;
end;
{$ELSE}
function NetReplImportDirEnum; external netapi32 name 'NetReplImportDirEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirGetInfo: Pointer;

function NetReplImportDirGetInfo;
begin
  GetProcedureAddress(_NetReplImportDirGetInfo, netapi32, 'NetReplImportDirGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirGetInfo]
  end;
end;
{$ELSE}
function NetReplImportDirGetInfo; external netapi32 name 'NetReplImportDirGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirLock: Pointer;

function NetReplImportDirLock;
begin
  GetProcedureAddress(_NetReplImportDirLock, netapi32, 'NetReplImportDirLock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirLock]
  end;
end;
{$ELSE}
function NetReplImportDirLock; external netapi32 name 'NetReplImportDirLock';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetReplImportDirUnlock: Pointer;

function NetReplImportDirUnlock;
begin
  GetProcedureAddress(_NetReplImportDirUnlock, netapi32, 'NetReplImportDirUnlock');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetReplImportDirUnlock]
  end;
end;
{$ELSE}
function NetReplImportDirUnlock; external netapi32 name 'NetReplImportDirUnlock';
{$ENDIF DYNAMIC_LINK}

end.
