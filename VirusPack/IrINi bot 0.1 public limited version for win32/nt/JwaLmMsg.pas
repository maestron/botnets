{******************************************************************************}
{                                                       	               }
{ Lan Manager Messages API interface Unit for Object Pascal                    }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmmsg.h, released November 2001. The original Pascal   } 
{ code is: LmMsg.pas, released Februari 2002. The initial developer of the     }
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

unit JwaLmMsg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmmsg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// Function Prototypes
//

function NetMessageNameAdd(servername, msgname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetMessageNameAdd}

function NetMessageNameEnum(servername: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries: LPDWORD; resume_handle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetMessageNameEnum}

function NetMessageNameGetInfo(servername, msgname: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetMessageNameGetInfo}

function NetMessageNameDel(servername, msgname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetMessageNameDel}

function NetMessageBufferSend(servername, msgname, fromname: LPCWSTR; buf: LPBYTE; buflen: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetMessageBufferSend}

//
//  Data Structures
//

type
  _MSG_INFO_0 = record
    msgi0_name: LPWSTR;
  end;
  {$EXTERNALSYM _MSG_INFO_0}
  MSG_INFO_0 = _MSG_INFO_0;
  {$EXTERNALSYM MSG_INFO_0}
  PMSG_INFO_0 = ^MSG_INFO_0;
  {$EXTERNALSYM PMSG_INFO_0}
  LPMSG_INFO_0 = ^MSG_INFO_0;
  {$EXTERNALSYM LPMSG_INFO_0}
  TMsgInfo0 = MSG_INFO_0;
  PMsgInfo0 = PMSG_INFO_0;

  _MSG_INFO_1 = record
    msgi1_name: LPWSTR;
    msgi1_forward_flag: DWORD;
    msgi1_forward: LPWSTR;
  end;
  {$EXTERNALSYM _MSG_INFO_1}
  MSG_INFO_1 = _MSG_INFO_1;
  {$EXTERNALSYM MSG_INFO_1}
  PMSG_INFO_1 = ^MSG_INFO_1;
  {$EXTERNALSYM PMSG_INFO_1}
  LPMSG_INFO_1 = ^MSG_INFO_1;
  {$EXTERNALSYM LPMSG_INFO_1}
  TMsgInfo1 = MSG_INFO_1;
  PMsgInfo1 = PMSG_INFO_1;

//
// Special Values and Constants
//

//
// Values for msgi1_forward_flag.
//

const
  MSGNAME_NOT_FORWARDED  = 0;      // Name not forwarded
  {$EXTERNALSYM MSGNAME_NOT_FORWARDED}
  MSGNAME_FORWARDED_TO   = $04;    // Name forward to remote station
  {$EXTERNALSYM MSGNAME_FORWARDED_TO}
  MSGNAME_FORWARDED_FROM = $10;    // Name forwarded from remote station
  {$EXTERNALSYM MSGNAME_FORWARDED_FROM}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameAdd: Pointer;

function NetMessageNameAdd;
begin
  GetProcedureAddress(_NetMessageNameAdd, netapi32, 'NetMessageNameAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameAdd]
  end;
end;
{$ELSE}
function NetMessageNameAdd; external netapi32 name 'NetMessageNameAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameEnum: Pointer;

function NetMessageNameEnum;
begin
  GetProcedureAddress(_NetMessageNameEnum, netapi32, 'NetMessageNameEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameEnum]
  end;
end;
{$ELSE}
function NetMessageNameEnum; external netapi32 name 'NetMessageNameEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameGetInfo: Pointer;

function NetMessageNameGetInfo;
begin
  GetProcedureAddress(_NetMessageNameGetInfo, netapi32, 'NetMessageNameGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameGetInfo]
  end;
end;
{$ELSE}
function NetMessageNameGetInfo; external netapi32 name 'NetMessageNameGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageNameDel: Pointer;

function NetMessageNameDel;
begin
  GetProcedureAddress(_NetMessageNameDel, netapi32, 'NetMessageNameDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageNameDel]
  end;
end;
{$ELSE}
function NetMessageNameDel; external netapi32 name 'NetMessageNameDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetMessageBufferSend: Pointer;

function NetMessageBufferSend;
begin
  GetProcedureAddress(_NetMessageBufferSend, netapi32, 'NetMessageBufferSend');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetMessageBufferSend]
  end;
end;
{$ELSE}
function NetMessageBufferSend; external netapi32 name 'NetMessageBufferSend';
{$ENDIF DYNAMIC_LINK}

end.
