{******************************************************************************}
{                                                       	               }
{ Lan Manager Shares API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmshare.h, released November 2001. The original Pascal }
{ code is: LmShare.pas, released Februari 2002. The initial developer of the   }
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

unit JwaLmShare;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmshare.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinNT, JwaWinType;

//
// Function Prototypes - Share
//

function NetShareAdd(servername: LMSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareAdd}

function NetShareEnum(servername: LMSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resume_handle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareEnum}

function NetShareEnumSticky(servername: LMSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resume_handle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareEnumSticky}

function NetShareGetInfo(servername, netname: LMSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareGetInfo}

function NetShareSetInfo(servername, netname: LMSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareSetInfo}

function NetShareDel(servername, netname: LMSTR; reserved: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareDel}

function NetShareDelSticky(servername, netname: LMSTR; reserved: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareDelSticky}

function NetShareCheck(servername, device: LMSTR; type_: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetShareCheck}

//
// Data Structures - Share
//

type
  LPSHARE_INFO_0 = ^SHARE_INFO_0;
  {$EXTERNALSYM LPSHARE_INFO_0}
  PSHARE_INFO_0 = ^SHARE_INFO_0;
  {$EXTERNALSYM PSHARE_INFO_0}
  _SHARE_INFO_0 = record
    shi0_netname: LMSTR;
  end;
  {$EXTERNALSYM _SHARE_INFO_0}
  SHARE_INFO_0 = _SHARE_INFO_0;
  {$EXTERNALSYM SHARE_INFO_0}
  TShareInfo0 = SHARE_INFO_0;
  PShareInfo0 = PSHARE_INFO_0;

  LPSHARE_INFO_1 = ^SHARE_INFO_1;
  {$EXTERNALSYM LPSHARE_INFO_1}
  PSHARE_INFO_1 = ^SHARE_INFO_1;
  {$EXTERNALSYM PSHARE_INFO_1}
  _SHARE_INFO_1 = record
    shi1_netname: LMSTR;
    shi1_type: DWORD;
    shi1_remark: LMSTR;
  end;
  {$EXTERNALSYM _SHARE_INFO_1}
  SHARE_INFO_1 = _SHARE_INFO_1;
  {$EXTERNALSYM SHARE_INFO_1}
  TShareInfo1 = SHARE_INFO_1;
  PShareInfo1 = PSHARE_INFO_1;

  LPSHARE_INFO_2 = ^SHARE_INFO_2;
  {$EXTERNALSYM LPSHARE_INFO_2}
  PSHARE_INFO_2 = ^SHARE_INFO_2;
  {$EXTERNALSYM PSHARE_INFO_2}
  _SHARE_INFO_2 = record
    shi2_netname: LMSTR;
    shi2_type: DWORD;
    shi2_remark: LMSTR;
    shi2_permissions: DWORD;
    shi2_max_uses: DWORD;
    shi2_current_uses: DWORD;
    shi2_path: LMSTR;
    shi2_passwd: LMSTR;
  end;
  {$EXTERNALSYM _SHARE_INFO_2}
  SHARE_INFO_2 = _SHARE_INFO_2;
  {$EXTERNALSYM SHARE_INFO_2}
  TShareInfo2 = SHARE_INFO_2;
  PShareInfo2 = PSHARE_INFO_2;

  LPSHARE_INFO_501 = ^SHARE_INFO_501;
  {$EXTERNALSYM LPSHARE_INFO_501}
  PSHARE_INFO_501 = ^SHARE_INFO_501;
  {$EXTERNALSYM PSHARE_INFO_501}
  _SHARE_INFO_501 = record
    shi501_netname: LMSTR;
    shi501_type: DWORD;
    shi501_remark: LMSTR;
    shi501_flags: DWORD;
  end;
  {$EXTERNALSYM _SHARE_INFO_501}
  SHARE_INFO_501 = _SHARE_INFO_501;
  {$EXTERNALSYM SHARE_INFO_501}
  TShareInfo501 = SHARE_INFO_501;
  PShareInfo501 = PSHARE_INFO_501;

  LPSHARE_INFO_502 = ^SHARE_INFO_502;
  {$EXTERNALSYM LPSHARE_INFO_502}
  PSHARE_INFO_502 = ^SHARE_INFO_502;
  {$EXTERNALSYM PSHARE_INFO_502}
  _SHARE_INFO_502 = record
    shi502_netname: LMSTR;
    shi502_type: DWORD;
    shi502_remark: LMSTR;
    shi502_permissions: DWORD;
    shi502_max_uses: DWORD;
    shi502_current_uses: DWORD;
    shi502_path: LMSTR;
    shi502_passwd: LMSTR;
    shi502_reserved: DWORD;
    shi502_security_descriptor: PSECURITY_DESCRIPTOR;
  end;
  {$EXTERNALSYM _SHARE_INFO_502}
  SHARE_INFO_502 = _SHARE_INFO_502;
  {$EXTERNALSYM SHARE_INFO_502}
  TShareInfo502 = SHARE_INFO_502;
  PShareInfo502 = PSHARE_INFO_502;

  LPSHARE_INFO_1004 = ^SHARE_INFO_1004;
  {$EXTERNALSYM LPSHARE_INFO_1004}
  PSHARE_INFO_1004 = ^SHARE_INFO_1004;
  {$EXTERNALSYM PSHARE_INFO_1004}
  _SHARE_INFO_1004 = record
    shi1004_remark: LMSTR;
  end;
  {$EXTERNALSYM _SHARE_INFO_1004}
  SHARE_INFO_1004 = _SHARE_INFO_1004;
  {$EXTERNALSYM SHARE_INFO_1004}
  TShareInfo1004 = SHARE_INFO_1004;
  PShareInfo1004 = PSHARE_INFO_1004;

  LPSHARE_INFO_1005 = ^SHARE_INFO_1005;
  {$EXTERNALSYM LPSHARE_INFO_1005}
  PSHARE_INFO_1005 = ^SHARE_INFO_1005;
  {$EXTERNALSYM PSHARE_INFO_1005}
  _SHARE_INFO_1005 = record
    shi1005_flags: DWORD;
  end;
  {$EXTERNALSYM _SHARE_INFO_1005}
  SHARE_INFO_1005 = _SHARE_INFO_1005;
  {$EXTERNALSYM SHARE_INFO_1005}
  TShareInfo1005 = SHARE_INFO_1005;
  PShareInfo1005 = PSHARE_INFO_1005;

  LPSHARE_INFO_1006 = ^SHARE_INFO_1006;
  {$EXTERNALSYM LPSHARE_INFO_1006}
  PSHARE_INFO_1006 = ^SHARE_INFO_1006;
  {$EXTERNALSYM PSHARE_INFO_1006}
  _SHARE_INFO_1006 = record
    shi1006_max_uses: DWORD;
  end;
  {$EXTERNALSYM _SHARE_INFO_1006}
  SHARE_INFO_1006 = _SHARE_INFO_1006;
  {$EXTERNALSYM SHARE_INFO_1006}
  TShareInfo1006 = SHARE_INFO_1006;
  PShareInfo1006 = PSHARE_INFO_1006;

  LPSHARE_INFO_1501 = ^SHARE_INFO_1501;
  {$EXTERNALSYM LPSHARE_INFO_1501}
  PSHARE_INFO_1501 = ^SHARE_INFO_1501;
  {$EXTERNALSYM PSHARE_INFO_1501}
  _SHARE_INFO_1501 = record
    shi1501_reserved: DWORD;
    shi1501_security_descriptor: PSECURITY_DESCRIPTOR;
  end;
  {$EXTERNALSYM _SHARE_INFO_1501}
  SHARE_INFO_1501 = _SHARE_INFO_1501;
  {$EXTERNALSYM SHARE_INFO_1501}
  TShareInfo1501 = SHARE_INFO_1501;
  PShareInfo1501 = PSHARE_INFO_1501;

//
// Special Values and Constants - Share
//

//
// Values for parm_err parameter.
//

const
  SHARE_NETNAME_PARMNUM      = 1;
  {$EXTERNALSYM SHARE_NETNAME_PARMNUM}
  SHARE_TYPE_PARMNUM         = 3;
  {$EXTERNALSYM SHARE_TYPE_PARMNUM}
  SHARE_REMARK_PARMNUM       = 4;
  {$EXTERNALSYM SHARE_REMARK_PARMNUM}
  SHARE_PERMISSIONS_PARMNUM  = 5;
  {$EXTERNALSYM SHARE_PERMISSIONS_PARMNUM}
  SHARE_MAX_USES_PARMNUM     = 6;
  {$EXTERNALSYM SHARE_MAX_USES_PARMNUM}
  SHARE_CURRENT_USES_PARMNUM = 7;
  {$EXTERNALSYM SHARE_CURRENT_USES_PARMNUM}
  SHARE_PATH_PARMNUM         = 8;
  {$EXTERNALSYM SHARE_PATH_PARMNUM}
  SHARE_PASSWD_PARMNUM       = 9;
  {$EXTERNALSYM SHARE_PASSWD_PARMNUM}
  SHARE_FILE_SD_PARMNUM      = 501;
  {$EXTERNALSYM SHARE_FILE_SD_PARMNUM}

//
// Single-field infolevels for NetShareSetInfo.
//

  SHARE_REMARK_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + SHARE_REMARK_PARMNUM);
  {$EXTERNALSYM SHARE_REMARK_INFOLEVEL}
  SHARE_MAX_USES_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + SHARE_MAX_USES_PARMNUM);
  {$EXTERNALSYM SHARE_MAX_USES_INFOLEVEL}
  SHARE_FILE_SD_INFOLEVEL  = (PARMNUM_BASE_INFOLEVEL + SHARE_FILE_SD_PARMNUM);
  {$EXTERNALSYM SHARE_FILE_SD_INFOLEVEL}

  SHI1_NUM_ELEMENTS = 4;
  {$EXTERNALSYM SHI1_NUM_ELEMENTS}
  SHI2_NUM_ELEMENTS = 10;
  {$EXTERNALSYM SHI2_NUM_ELEMENTS}

//
// Share types (shi1_type and shi2_type fields).
//

  STYPE_DISKTREE = 0;
  {$EXTERNALSYM STYPE_DISKTREE}
  STYPE_PRINTQ   = 1;
  {$EXTERNALSYM STYPE_PRINTQ}
  STYPE_DEVICE   = 2;
  {$EXTERNALSYM STYPE_DEVICE}
  STYPE_IPC      = 3;
  {$EXTERNALSYM STYPE_IPC}

  STYPE_TEMPORARY = $40000000;
  {$EXTERNALSYM STYPE_TEMPORARY}
  STYPE_SPECIAL   = DWORD($80000000);
  {$EXTERNALSYM STYPE_SPECIAL}

  SHI_USES_UNLIMITED = DWORD(-1);
  {$EXTERNALSYM SHI_USES_UNLIMITED}

//
// Flags values for the 501 and 1005 levels
//

  SHI1005_FLAGS_DFS      = $01; // Share is in the DFS
  {$EXTERNALSYM SHI1005_FLAGS_DFS}
  SHI1005_FLAGS_DFS_ROOT = $02; // Share is root of DFS
  {$EXTERNALSYM SHI1005_FLAGS_DFS_ROOT}

  CSC_MASK               = $30; // Used to mask off the following states
  {$EXTERNALSYM CSC_MASK}

  CSC_CACHE_MANUAL_REINT = $00; // No automatic file by file reintegration
  {$EXTERNALSYM CSC_CACHE_MANUAL_REINT}
  CSC_CACHE_AUTO_REINT   = $10; // File by file reintegration is OK
  {$EXTERNALSYM CSC_CACHE_AUTO_REINT}
  CSC_CACHE_VDO          = $20; // no need to flow opens
  {$EXTERNALSYM CSC_CACHE_VDO}
  CSC_CACHE_NONE         = $30; // no CSC for this share
  {$EXTERNALSYM CSC_CACHE_NONE}

  SHI1005_FLAGS_RESTRICT_EXCLUSIVE_OPENS = $0100;          // Used to disallow read-deny read behavior
  {$EXTERNALSYM SHI1005_FLAGS_RESTRICT_EXCLUSIVE_OPENS}
  SHI1005_FLAGS_FORCE_SHARED_DELETE      = $0200;          // Used to allows force shared delete
  {$EXTERNALSYM SHI1005_FLAGS_FORCE_SHARED_DELETE}
  SHI1005_FLAGS_ALLOW_NAMESPACE_CACHING  = $0400;          // The clients may cache the namespace
  {$EXTERNALSYM SHI1005_FLAGS_ALLOW_NAMESPACE_CACHING}

//
// The subset of 1005 infolevel flags that can be set via the API
//

  SHI1005_VALID_FLAGS_SET = (CSC_MASK or SHI1005_FLAGS_RESTRICT_EXCLUSIVE_OPENS or SHI1005_FLAGS_FORCE_SHARED_DELETE or SHI1005_FLAGS_ALLOW_NAMESPACE_CACHING);
  {$EXTERNALSYM SHI1005_VALID_FLAGS_SET}

//
// SESSION API
//

//
// Function Prototypes Session
//

function NetSessionEnum(servername, UncClientName, username: LMSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resume_handle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetSessionEnum}

function NetSessionDel(servername, UncClientName, username: LMSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetSessionDel}

function NetSessionGetInfo(servername, UncClientName, username: LMSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetSessionGetInfo}

//
// Data Structures - Session
//

type
  LPSESSION_INFO_0 = ^SESSION_INFO_0;
  {$EXTERNALSYM LPSESSION_INFO_0}
  PSESSION_INFO_0 = ^SESSION_INFO_0;
  {$EXTERNALSYM PSESSION_INFO_0}
  _SESSION_INFO_0 = record
    sesi0_cname: LMSTR; // client name (no backslashes)
  end;
  {$EXTERNALSYM _SESSION_INFO_0}
  SESSION_INFO_0 = _SESSION_INFO_0;
  {$EXTERNALSYM SESSION_INFO_0}
  TSessionInfo0 = SESSION_INFO_0;
  PSessionInfo0 = PSESSION_INFO_0;

  LPSESSION_INFO_1 = ^SESSION_INFO_1;
  {$EXTERNALSYM LPSESSION_INFO_1}
  PSESSION_INFO_1 = ^SESSION_INFO_1;
  {$EXTERNALSYM PSESSION_INFO_1}
  _SESSION_INFO_1 = record
    sesi1_cname: LMSTR; // client name (no backslashes)
    sesi1_username: LMSTR;
    sesi1_num_opens: DWORD;
    sesi1_time: DWORD;
    sesi1_idle_time: DWORD;
    sesi1_user_flags: DWORD;
  end;
  {$EXTERNALSYM _SESSION_INFO_1}
  SESSION_INFO_1 = _SESSION_INFO_1;
  {$EXTERNALSYM SESSION_INFO_1}
  TSessionInfo1 = SESSION_INFO_1;
  PSessionInfo1 = PSESSION_INFO_1;

  LPSESSION_INFO_2 = ^SESSION_INFO_2;
  {$EXTERNALSYM LPSESSION_INFO_2}
  PSESSION_INFO_2 = ^SESSION_INFO_2;
  {$EXTERNALSYM PSESSION_INFO_2}
  _SESSION_INFO_2 = record
    sesi2_cname: LMSTR; // client name (no backslashes)
    sesi2_username: LMSTR;
    sesi2_num_opens: DWORD;
    sesi2_time: DWORD;
    sesi2_idle_time: DWORD;
    sesi2_user_flags: DWORD;
    sesi2_cltype_name: LMSTR;
  end;
  {$EXTERNALSYM _SESSION_INFO_2}
  SESSION_INFO_2 = _SESSION_INFO_2;
  {$EXTERNALSYM SESSION_INFO_2}
  TSessionInfo2 = SESSION_INFO_2;
  PSessionInfo2 = PSESSION_INFO_2;

  LPSESSION_INFO_10 = ^SESSION_INFO_10;
  {$EXTERNALSYM LPSESSION_INFO_10}
  PSESSION_INFO_10 = ^SESSION_INFO_10;
  {$EXTERNALSYM PSESSION_INFO_10}
  _SESSION_INFO_10 = record
    sesi10_cname: LMSTR; // client name (no backslashes)
    sesi10_username: LMSTR;
    sesi10_time: DWORD;
    sesi10_idle_time: DWORD;
  end;
  {$EXTERNALSYM _SESSION_INFO_10}
  SESSION_INFO_10 = _SESSION_INFO_10;
  {$EXTERNALSYM SESSION_INFO_10}
  TSessionInfo10 = SESSION_INFO_10;
  PSessionInfo10 = PSESSION_INFO_10;

  LPSESSION_INFO_502 = ^SESSION_INFO_502;
  {$EXTERNALSYM LPSESSION_INFO_502}
  PSESSION_INFO_502 = ^SESSION_INFO_502;
  {$EXTERNALSYM PSESSION_INFO_502}
  _SESSION_INFO_502 = record
    sesi502_cname: LMSTR; // client name (no backslashes)
    sesi502_username: LMSTR;
    sesi502_num_opens: DWORD;
    sesi502_time: DWORD;
    sesi502_idle_time: DWORD;
    sesi502_user_flags: DWORD;
    sesi502_cltype_name: LMSTR;
    sesi502_transport: LMSTR;
  end;
  {$EXTERNALSYM _SESSION_INFO_502}
  SESSION_INFO_502 = _SESSION_INFO_502;
  {$EXTERNALSYM SESSION_INFO_502}
  TSessionInfo502 = SESSION_INFO_502;
  PSessionInfo502 = PSESSION_INFO_502;

//
// Special Values and Constants - Session
//


//
// Bits defined in sesi1_user_flags.
//

const
  SESS_GUEST        = $00000001; // session is logged on as a guest
  {$EXTERNALSYM SESS_GUEST}
  SESS_NOENCRYPTION = $00000002; // session is not using encryption
  {$EXTERNALSYM SESS_NOENCRYPTION}

  SESI1_NUM_ELEMENTS = 8;
  {$EXTERNALSYM SESI1_NUM_ELEMENTS}
  SESI2_NUM_ELEMENTS = 9;
  {$EXTERNALSYM SESI2_NUM_ELEMENTS}

//
// CONNECTION API
//

//
// Function Prototypes - CONNECTION
//

function NetConnectionEnum(servername, qualifier: LMSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resume_handle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetConnectionEnum}

//
// Data Structures - CONNECTION
//

type
  LPCONNECTION_INFO_0 = ^CONNECTION_INFO_0;
  {$EXTERNALSYM LPCONNECTION_INFO_0}
  PCONNECTION_INFO_0 = ^CONNECTION_INFO_0;
  {$EXTERNALSYM PCONNECTION_INFO_0}
  _CONNECTION_INFO_0 = record
    coni0_id: DWORD;
  end;
  {$EXTERNALSYM _CONNECTION_INFO_0}
  CONNECTION_INFO_0 = _CONNECTION_INFO_0;
  {$EXTERNALSYM CONNECTION_INFO_0}
  TConnectionInfo0 = CONNECTION_INFO_0;
  PConnectionInfo0 = PCONNECTION_INFO_0;

  LPCONNECTION_INFO_1 = ^CONNECTION_INFO_1;
  {$EXTERNALSYM LPCONNECTION_INFO_1}
  PCONNECTION_INFO_1 = ^CONNECTION_INFO_1;
  {$EXTERNALSYM PCONNECTION_INFO_1}
  _CONNECTION_INFO_1 = record
    coni1_id: DWORD;
    coni1_type: DWORD;
    coni1_num_opens: DWORD;
    coni1_num_users: DWORD;
    coni1_time: DWORD;
    coni1_username: LMSTR;
    coni1_netname: LMSTR;
  end;
  {$EXTERNALSYM _CONNECTION_INFO_1}
  CONNECTION_INFO_1 = _CONNECTION_INFO_1;
  {$EXTERNALSYM CONNECTION_INFO_1}
  TConnectionInfo1 = CONNECTION_INFO_1;
  PConnectionInfo1 = PCONNECTION_INFO_1;

//
// FILE API
//

//
// Function Prototypes - FILE
//

function NetFileClose(servername: LMSTR; fileid: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetFileClose}

function NetFileEnum(servername, basepath, username: LMSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resume_handle: PDWORD_PTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetFileEnum}

function NetFileGetInfo(servername: LMSTR; fileid, level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetFileGetInfo}

//
// Data Structures - File
//

//  File APIs are available at information levels 2 & 3 only. Levels 0 &
//  1 are not supported.
//

type
  LPFILE_INFO_2 = ^FILE_INFO_2;
  {$EXTERNALSYM LPFILE_INFO_2}
  PFILE_INFO_2 = ^FILE_INFO_2;
  {$EXTERNALSYM PFILE_INFO_2}
  _FILE_INFO_2 = record
    fi2_id: DWORD;
  end;
  {$EXTERNALSYM _FILE_INFO_2}
  FILE_INFO_2 = _FILE_INFO_2;
  {$EXTERNALSYM FILE_INFO_2}
  TFileInfo2 = FILE_INFO_2;
  PFileInfo2 = PFILE_INFO_2;

  LPFILE_INFO_3 = ^FILE_INFO_3;
  {$EXTERNALSYM LPFILE_INFO_3}
  PFILE_INFO_3 = ^FILE_INFO_3;
  {$EXTERNALSYM PFILE_INFO_3}
  _FILE_INFO_3 = record
    fi3_id: DWORD;
    fi3_permissions: DWORD;
    fi3_num_locks: DWORD;
    fi3_pathname: LMSTR;
    fi3_username: LMSTR;
  end;
  {$EXTERNALSYM _FILE_INFO_3}
  FILE_INFO_3 = _FILE_INFO_3;
  {$EXTERNALSYM FILE_INFO_3}
  TFileInfo3 = FILE_INFO_3;
  PFileInfo3 = PFILE_INFO_3;

//
// Special Values and Constants - File
//

//
// bit values for permissions
//

const
  PERM_FILE_READ   = $1; // user has read access
  {$EXTERNALSYM PERM_FILE_READ}
  PERM_FILE_WRITE  = $2; // user has write access
  {$EXTERNALSYM PERM_FILE_WRITE}
  PERM_FILE_CREATE = $4; // user has create access
  {$EXTERNALSYM PERM_FILE_CREATE}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetShareAdd: Pointer;

function NetShareAdd;
begin
  GetProcedureAddress(_NetShareAdd, netapi32, 'NetShareAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareAdd]
  end;
end;
{$ELSE}
function NetShareAdd; external netapi32 name 'NetShareAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareEnum: Pointer;

function NetShareEnum;
begin
  GetProcedureAddress(_NetShareEnum, netapi32, 'NetShareEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareEnum]
  end;
end;
{$ELSE}
function NetShareEnum; external netapi32 name 'NetShareEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareEnumSticky: Pointer;

function NetShareEnumSticky;
begin
  GetProcedureAddress(_NetShareEnumSticky, netapi32, 'NetShareEnumSticky');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareEnumSticky]
  end;
end;
{$ELSE}
function NetShareEnumSticky; external netapi32 name 'NetShareEnumSticky';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareGetInfo: Pointer;

function NetShareGetInfo;
begin
  GetProcedureAddress(_NetShareGetInfo, netapi32, 'NetShareGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareGetInfo]
  end;
end;
{$ELSE}
function NetShareGetInfo; external netapi32 name 'NetShareGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareSetInfo: Pointer;

function NetShareSetInfo;
begin
  GetProcedureAddress(_NetShareSetInfo, netapi32, 'NetShareSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareSetInfo]
  end;
end;
{$ELSE}
function NetShareSetInfo; external netapi32 name 'NetShareSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareDel: Pointer;

function NetShareDel;
begin
  GetProcedureAddress(_NetShareDel, netapi32, 'NetShareDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareDel]
  end;
end;
{$ELSE}
function NetShareDel; external netapi32 name 'NetShareDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareDelSticky: Pointer;

function NetShareDelSticky;
begin
  GetProcedureAddress(_NetShareDelSticky, netapi32, 'NetShareDelSticky');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareDelSticky]
  end;
end;
{$ELSE}
function NetShareDelSticky; external netapi32 name 'NetShareDelSticky';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetShareCheck: Pointer;

function NetShareCheck;
begin
  GetProcedureAddress(_NetShareCheck, netapi32, 'NetShareCheck');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetShareCheck]
  end;
end;
{$ELSE}
function NetShareCheck; external netapi32 name 'NetShareCheck';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _NetSessionEnum: Pointer;

function NetSessionEnum;
begin
  GetProcedureAddress(_NetSessionEnum, netapi32, 'NetSessionEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetSessionEnum]
  end;
end;
{$ELSE}
function NetSessionEnum; external netapi32 name 'NetSessionEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetSessionDel: Pointer;

function NetSessionDel;
begin
  GetProcedureAddress(_NetSessionDel, netapi32, 'NetSessionDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetSessionDel]
  end;
end;
{$ELSE}
function NetSessionDel; external netapi32 name 'NetSessionDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetSessionGetInfo: Pointer;

function NetSessionGetInfo;
begin
  GetProcedureAddress(_NetSessionGetInfo, netapi32, 'NetSessionGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetSessionGetInfo]
  end;
end;
{$ELSE}
function NetSessionGetInfo; external netapi32 name 'NetSessionGetInfo';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _NetConnectionEnum: Pointer;

function NetConnectionEnum;
begin
  GetProcedureAddress(_NetConnectionEnum, netapi32, 'NetConnectionEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetConnectionEnum]
  end;
end;
{$ELSE}
function NetConnectionEnum; external netapi32 name 'NetConnectionEnum';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _NetFileClose: Pointer;

function NetFileClose;
begin
  GetProcedureAddress(_NetFileClose, netapi32, 'NetFileClose');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetFileClose]
  end;
end;
{$ELSE}
function NetFileClose; external netapi32 name 'NetFileClose';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetFileEnum: Pointer;

function NetFileEnum;
begin
  GetProcedureAddress(_NetFileEnum, netapi32, 'NetFileEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetFileEnum]
  end;
end;
{$ELSE}
function NetFileEnum; external netapi32 name 'NetFileEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetFileGetInfo: Pointer;

function NetFileGetInfo;
begin
  GetProcedureAddress(_NetFileGetInfo, netapi32, 'NetFileGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetFileGetInfo]
  end;
end;
{$ELSE}
function NetFileGetInfo; external netapi32 name 'NetFileGetInfo';
{$ENDIF DYNAMIC_LINK}

end.
