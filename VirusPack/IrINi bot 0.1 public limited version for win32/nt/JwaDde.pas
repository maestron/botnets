{******************************************************************************}
{                                                       	               }
{ Dynamic Data Exchange API interface Unit for Object Pascal                   }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dde.h, released June 2000. The original Pascal         }
{ code is: Dde.pas, released December 2000. The initial developer of the       }
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

unit JwaDde;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "Dde.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

// DDE window messages

const
  WM_DDE_FIRST = $03E0;
  {$EXTERNALSYM WM_DDE_FIRST}
  WM_DDE_INITIATE = (WM_DDE_FIRST);
  {$EXTERNALSYM WM_DDE_INITIATE}
  WM_DDE_TERMINATE = (WM_DDE_FIRST + 1);
  {$EXTERNALSYM WM_DDE_TERMINATE}
  WM_DDE_ADVISE = (WM_DDE_FIRST + 2);
  {$EXTERNALSYM WM_DDE_ADVISE}
  WM_DDE_UNADVISE = (WM_DDE_FIRST + 3);
  {$EXTERNALSYM WM_DDE_UNADVISE}
  WM_DDE_ACK = (WM_DDE_FIRST + 4);
  {$EXTERNALSYM WM_DDE_ACK}
  WM_DDE_DATA = (WM_DDE_FIRST + 5);
  {$EXTERNALSYM WM_DDE_DATA}
  WM_DDE_REQUEST = (WM_DDE_FIRST + 6);
  {$EXTERNALSYM WM_DDE_REQUEST}
  WM_DDE_POKE = (WM_DDE_FIRST + 7);
  {$EXTERNALSYM WM_DDE_POKE}
  WM_DDE_EXECUTE = (WM_DDE_FIRST + 8);
  {$EXTERNALSYM WM_DDE_EXECUTE}
  WM_DDE_LAST = (WM_DDE_FIRST + 8);
  {$EXTERNALSYM WM_DDE_LAST}

{*----------------------------------------------------------------------------
|       DDEACK structure
|
|	Structure of wStatus (LOWORD(lParam)) in WM_DDE_ACK message
|       sent in response to a WM_DDE_DATA, WM_DDE_REQUEST, WM_DDE_POKE,
|       WM_DDE_ADVISE, or WM_DDE_UNADVISE message.
|
----------------------------------------------------------------------------*}

type
  DDEACK = record
    Flags: Word;
    // bAppReturnCode:8,
    // reserved:6,
    // fBusy:1,
    // fAck:1;
  end;
  {$EXTERNALSYM DDEACK}
  TDdeAck = DDEACK;
  PDdeAck = ^DDEACK;

{*----------------------------------------------------------------------------
|       DDEADVISE structure
|
|	WM_DDE_ADVISE parameter structure for hOptions (LOWORD(lParam))
|
----------------------------------------------------------------------------*}

type
  DDEADVICE = record
    Flags: Word;
    // reserved:14,
    // fDeferUpd:1,
    // fAckReq:1;
    cfFormat: Smallint;
  end;
  {$EXTERNALSYM DDEADVICE}
  TDdeAdvice = DDEADVICE;
  PDdeAdvice = ^DDEADVICE;

{*----------------------------------------------------------------------------
|       DDEDATA structure
|
|       WM_DDE_DATA parameter structure for hData (LOWORD(lParam)).
|       The actual size of this structure depends on the size of
|       the Value array.
|
----------------------------------------------------------------------------*}

type
  DDEDATA = record
    usFlags: Word;
    // unused:12,
    // fResponse:1,
    // fRelease:1,
    // reserved:1,
    // fAckReq:1;
    cfFormat: Smallint;
    Value: array [0..0] of Byte;
  end;
  {$EXTERNALSYM DDEDATA}
  TDdeData = DDEDATA;
  PDdeData = ^DDEDATA;

{*----------------------------------------------------------------------------
|	DDEPOKE structure
|
|	WM_DDE_POKE parameter structure for hData (LOWORD(lParam)).
|       The actual size of this structure depends on the size of
|       the Value array.
|
----------------------------------------------------------------------------*}

type
  DDEPOKE = record
    usFlags: Word;
    //unused:13,  // Earlier versions of DDE.H incorrectly 12 unused bits.
    //fRelease:1,
    //fReserved:2;
    cfFormat: Smallint;
    Value: array [0..0] of Byte;  // This member was named rgb[1] in previous
                                  // versions of DDE.H
  end;
  {$EXTERNALSYM DDEPOKE}
  TDdePoke = DDEPOKE;
  PDdePoke = ^DDEPOKE;

{*----------------------------------------------------------------------------
The following typedef's were used in previous versions of the Windows SDK.
They are still valid.  The above typedef's define exactly the same structures
as those below.  The above typedef names are recommended, however, as they
are more meaningful.

Note that the DDEPOKE structure typedef'ed in earlier versions of DDE.H did
not correctly define the bit positions.
----------------------------------------------------------------------------*}

type
  DDELN = record
    usFlags: Word;
    // unused:13,
    // fRelease:1,
    // fDeferUpd:1,
    // fAckReq:1;
    cfFormat: Smallint;
  end;
  {$EXTERNALSYM DDELN}
  TDdeLn = DDELN;
  PDdeLn = ^DDELN;

  DDEUP = record
    usFlags: Word;
    // unused:12,
    // fAck:1,
    // fRelease:1,
    // fReserved:1,
    // fAckReq:1;
    cfFormat: Smallint;
    rgb: array [0..0] of Byte;
  end;
  {$EXTERNALSYM DDEUP}
  TDdeUp = DDEUP;
  PDdeUp = ^DDEUP;

//
// DDE SECURITY
//

function DdeSetQualityOfService(hwndClient: HWND; const pqosNew: SECURITY_QUALITY_OF_SERVICE;
  pqosPrev: PSECURITY_QUALITY_OF_SERVICE): BOOL; stdcall;
{$EXTERNALSYM DdeSetQualityOfService}

function ImpersonateDdeClientWindow(hWndClient, hWndServer: HWND): BOOL; stdcall;
{$EXTERNALSYM ImpersonateDdeClientWindow}

//
// DDE message packing APIs
//

function PackDDElParam(msg: UINT; uiLo, uiHi: UINT_PTR): LPARAM; stdcall;
{$EXTERNALSYM PackDDElParam}
function UnpackDDElParam(msg: UINT; lParam: LPARAM; puiLo, puiHi: PUINT_PTR): BOOL; stdcall;
{$EXTERNALSYM UnpackDDElParam}
function FreeDDElParam(msg: UINT; lParam: LPARAM): BOOL; stdcall;
{$EXTERNALSYM FreeDDElParam}
function ReuseDDElParam(lParam: LPARAM; msgIn, msgOut: UINT; uiLo, uiHi: UINT_PTR): LPARAM; stdcall;
{$EXTERNALSYM ReuseDDElParam}

implementation

const
  user32 = 'user32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _DdeSetQualityOfService: Pointer;

function DdeSetQualityOfService;
begin
  GetProcedureAddress(_DdeSetQualityOfService, user32, 'DdeSetQualityOfService');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DdeSetQualityOfService]
  end;
end;
{$ELSE}
function DdeSetQualityOfService; external user32 name 'DdeSetQualityOfService';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ImpersonateDdeClientWindow: Pointer;

function ImpersonateDdeClientWindow;
begin
  GetProcedureAddress(_ImpersonateDdeClientWindow, user32, 'ImpersonateDdeClientWindow');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ImpersonateDdeClientWindow]
  end;
end;
{$ELSE}
function ImpersonateDdeClientWindow; external user32 name 'ImpersonateDdeClientWindow';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PackDDElParam: Pointer;

function PackDDElParam;
begin
  GetProcedureAddress(_PackDDElParam, user32, 'PackDDElParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PackDDElParam]
  end;
end;
{$ELSE}
function PackDDElParam; external user32 name 'PackDDElParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _UnpackDDElParam: Pointer;

function UnpackDDElParam;
begin
  GetProcedureAddress(_UnpackDDElParam, user32, 'UnpackDDElParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_UnpackDDElParam]
  end;
end;
{$ELSE}
function UnpackDDElParam; external user32 name 'UnpackDDElParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FreeDDElParam: Pointer;

function FreeDDElParam;
begin
  GetProcedureAddress(_FreeDDElParam, user32, 'FreeDDElParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeDDElParam]
  end;
end;
{$ELSE}
function FreeDDElParam; external user32 name 'FreeDDElParam';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReuseDDElParam: Pointer;

function ReuseDDElParam;
begin
  GetProcedureAddress(_ReuseDDElParam, user32, 'ReuseDDElParam');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReuseDDElParam]
  end;
end;
{$ELSE}
function ReuseDDElParam; external user32 name 'ReuseDDElParam';
{$ENDIF DYNAMIC_LINK}

end.
