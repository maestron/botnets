{******************************************************************************}
{                                                       	               }
{ Lan Manager Use API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmuse.h, released November 2001. The original Pascal   }
{ code is: LmUse.pas, released Februari 2002. The initial developer of the     }
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

unit JwaLmUse;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmuse.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// Function Prototypes
//

function NetUseAdd(UncServerName: LMSTR; Level: DWORD; Buf: LPBYTE; ParmError: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseAdd}

function NetUseDel(UncServerName: LMSTR; UseName: LMSTR; ForceCond: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseDel}

function NetUseEnum(UncServerName: LMSTR; Level: DWORD; var BufPtr: LPBYTE; PreferedMaximumSize: DWORD; EntriesRead: LPDWORD; TotalEntries: LPDWORD; ResumeHandle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseEnum}

function NetUseGetInfo(UncServerName: LMSTR; UseName: LMSTR; Level: DWORD; var BufPtr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUseGetInfo}

//
//  Data Structures
//

type
  _USE_INFO_0 = record
    ui0_local: LMSTR;
    ui0_remote: LMSTR;
  end;
  {$EXTERNALSYM _USE_INFO_0}
  USE_INFO_0 = _USE_INFO_0;
  {$EXTERNALSYM USE_INFO_0}
  PUSE_INFO_0 = ^USE_INFO_0;
  {$EXTERNALSYM PUSE_INFO_0}
  LPUSE_INFO_0 = ^USE_INFO_0;
  {$EXTERNALSYM LPUSE_INFO_0}
  TUseInfo0 = USE_INFO_0;
  PUseInfo0 = PUSE_INFO_0;

  _USE_INFO_1 = record
    ui1_local: LMSTR;
    ui1_remote: LMSTR;
    ui1_password: LMSTR;
    ui1_status: DWORD;
    ui1_asg_type: DWORD;
    ui1_refcount: DWORD;
    ui1_usecount: DWORD;
  end;
  {$EXTERNALSYM _USE_INFO_1}
  USE_INFO_1 = _USE_INFO_1;
  {$EXTERNALSYM USE_INFO_1}
  PUSE_INFO_1 = ^USE_INFO_1;
  {$EXTERNALSYM PUSE_INFO_1}
  LPUSE_INFO_1 = ^USE_INFO_1;
  {$EXTERNALSYM LPUSE_INFO_1}
  TUseInfo1 = USE_INFO_1;
  PUseInfo1 = PUSE_INFO_1;

  _USE_INFO_2 = record
    ui2_local: LMSTR;
    ui2_remote: LMSTR;
    ui2_password: LMSTR;
    ui2_status: DWORD;
    ui2_asg_type: DWORD;
    ui2_refcount: DWORD;
    ui2_usecount: DWORD;
    ui2_username: LMSTR;
    ui2_domainname: LMSTR;
  end;
  {$EXTERNALSYM _USE_INFO_2}
  USE_INFO_2 = _USE_INFO_2;
  {$EXTERNALSYM USE_INFO_2}
  PUSE_INFO_2 = ^USE_INFO_2;
  {$EXTERNALSYM PUSE_INFO_2}
  LPUSE_INFO_2 = ^USE_INFO_2;
  {$EXTERNALSYM LPUSE_INFO_2}
  TUseInfo2 = USE_INFO_2;
  PUseInfo2 = PUSE_INFO_2;

  _USE_INFO_3 = record
    ui3_ui2: USE_INFO_2;
    ui3_flags: ULONG;
  end;
  {$EXTERNALSYM _USE_INFO_3}
  USE_INFO_3 = _USE_INFO_3;
  {$EXTERNALSYM USE_INFO_3}
  PUSE_INFO_3 = ^USE_INFO_3;
  {$EXTERNALSYM PUSE_INFO_3}
  LPUSE_INFO_3 = ^USE_INFO_3;
  {$EXTERNALSYM LPUSE_INFO_3}
  TUseInfo3 = USE_INFO_3;
  PUseInfo3 = PUSE_INFO_3;

//
// Special Values and Constants
//

//
// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetUseAdd.
//

const
  USE_LOCAL_PARMNUM      = 1;
  {$EXTERNALSYM USE_LOCAL_PARMNUM}
  USE_REMOTE_PARMNUM     = 2;
  {$EXTERNALSYM USE_REMOTE_PARMNUM}
  USE_PASSWORD_PARMNUM   = 3;
  {$EXTERNALSYM USE_PASSWORD_PARMNUM}
  USE_ASGTYPE_PARMNUM    = 4;
  {$EXTERNALSYM USE_ASGTYPE_PARMNUM}
  USE_USERNAME_PARMNUM   = 5;
  {$EXTERNALSYM USE_USERNAME_PARMNUM}
  USE_DOMAINNAME_PARMNUM = 6;
  {$EXTERNALSYM USE_DOMAINNAME_PARMNUM}

//
// Values appearing in the ui1_status field of use_info_1 structure.
// Note that USE_SESSLOST and USE_DISCONN are synonyms.
//

  USE_OK       = 0;
  {$EXTERNALSYM USE_OK}
  USE_PAUSED   = 1;
  {$EXTERNALSYM USE_PAUSED}
  USE_SESSLOST = 2;
  {$EXTERNALSYM USE_SESSLOST}
  USE_DISCONN  = 2;
  {$EXTERNALSYM USE_DISCONN}
  USE_NETERR   = 3;
  {$EXTERNALSYM USE_NETERR}
  USE_CONN     = 4;
  {$EXTERNALSYM USE_CONN}
  USE_RECONN   = 5;
  {$EXTERNALSYM USE_RECONN}

//
// Values of the ui1_asg_type field of use_info_1 structure
//

  USE_WILDCARD = DWORD(-1);
  {$EXTERNALSYM USE_WILDCARD}
  USE_DISKDEV  = 0;
  {$EXTERNALSYM USE_DISKDEV}
  USE_SPOOLDEV = 1;
  {$EXTERNALSYM USE_SPOOLDEV}
  USE_CHARDEV  = 2;
  {$EXTERNALSYM USE_CHARDEV}
  USE_IPC      = 3;
  {$EXTERNALSYM USE_IPC}

//
// Flags defined in the use_info_3 structure
//

  CREATE_NO_CONNECT = $1; // creation flags
  {$EXTERNALSYM CREATE_NO_CONNECT}
  CREATE_BYPASS_CSC = $2; // force connection to server, bypassing CSC
  {$EXTERNALSYM CREATE_BYPASS_CSC}
                          //  all ops on this connection go to the server,
                          //  never to the cache
  USE_DEFAULT_CREDENTIALS = $4; // No explicit credentials passed to NetUseAdd
  {$EXTERNALSYM USE_DEFAULT_CREDENTIALS}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetUseAdd: Pointer;

function NetUseAdd;
begin
  GetProcedureAddress(_NetUseAdd, netapi32, 'NetUseAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseAdd]
  end;
end;
{$ELSE}
function NetUseAdd; external netapi32 name 'NetUseAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUseDel: Pointer;

function NetUseDel;
begin
  GetProcedureAddress(_NetUseDel, netapi32, 'NetUseDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseDel]
  end;
end;
{$ELSE}
function NetUseDel; external netapi32 name 'NetUseDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUseEnum: Pointer;

function NetUseEnum;
begin
  GetProcedureAddress(_NetUseEnum, netapi32, 'NetUseEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseEnum]
  end;
end;
{$ELSE}
function NetUseEnum; external netapi32 name 'NetUseEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUseGetInfo: Pointer;

function NetUseGetInfo;
begin
  GetProcedureAddress(_NetUseGetInfo, netapi32, 'NetUseGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUseGetInfo]
  end;
end;
{$ELSE}
function NetUseGetInfo; external netapi32 name 'NetUseGetInfo';
{$ENDIF DYNAMIC_LINK}

end.
