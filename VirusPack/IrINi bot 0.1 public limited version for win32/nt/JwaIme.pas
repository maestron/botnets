{******************************************************************************}
{                                                       	               }
{ IME Component API interface Unit for Object Pascal                           }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ime.h, released June 2000. The original Pascal         }
{ code is: Ime.pas, released December 2000. The initial developer of the       }
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

unit JwaIme;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "Ime.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

const
  IME_MAXPROCESS = 32;
  {$EXTERNALSYM IME_MAXPROCESS}

function SendIMEMessageExA(hWnd: HWND; lParam: LPARAM): LRESULT; stdcall;
{$EXTERNALSYM SendIMEMessageExA}
function SendIMEMessageExW(hWnd: HWND; lParam: LPARAM): LRESULT; stdcall;
{$EXTERNALSYM SendIMEMessageExW}
{$IFDEF UNICODE}
function SendIMEMessageEx(hWnd: HWND; lParam: LPARAM): LRESULT; stdcall;
{$EXTERNALSYM SendIMEMessageEx}
{$ELSE}
function SendIMEMessageEx(hWnd: HWND; lParam: LPARAM): LRESULT; stdcall;
{$EXTERNALSYM SendIMEMessageEx}
{$ENDIF}

//
// IMESTRUCT structure for SendIMEMessageEx
//

type
  tagIMESTRUCT = record
    fnc: UINT;       // function code
    wParam: WPARAM;  // word parameter
    wCount: UINT;    // word counter
    dchSource: UINT; // offset to Source from top of memory object
    dchDest: UINT;   // offset to Desrination from top of memory object
    lParam1: LPARAM;
    lParam2: LPARAM;
    lParam3: LPARAM;
  end;
  {$EXTERNALSYM tagIMESTRUCT}
  IMESTRUCT = tagIMESTRUCT;
  {$EXTERNALSYM IMESTRUCT}
  LPIMESTRUCT = ^IMESTRUCT;
  {$EXTERNALSYM LPIMESTRUCT}
  PIMESTRUCT = ^IMESTRUCT;
  {$EXTERNALSYM PIMESTRUCT}
  NPIMESTRUCT = ^IMESTRUCT;
  {$EXTERNALSYM NPIMESTRUCT}
  TImeStruct = IMESTRUCT;

const
  CP_HWND   = 0;
  {$EXTERNALSYM CP_HWND}
  CP_OPEN   = 1;
  {$EXTERNALSYM CP_OPEN}
  CP_DIRECT = 2;
  {$EXTERNALSYM CP_DIRECT}
  CP_LEVEL  = 3;
  {$EXTERNALSYM CP_LEVEL}

//
//      Virtual Keys
//

  VK_DBE_ALPHANUMERIC           = $0f0;
  {$EXTERNALSYM VK_DBE_ALPHANUMERIC}
  VK_DBE_KATAKANA               = $0f1;
  {$EXTERNALSYM VK_DBE_KATAKANA}
  VK_DBE_HIRAGANA               = $0f2;
  {$EXTERNALSYM VK_DBE_HIRAGANA}
  VK_DBE_SBCSCHAR               = $0f3;
  {$EXTERNALSYM VK_DBE_SBCSCHAR}
  VK_DBE_DBCSCHAR               = $0f4;
  {$EXTERNALSYM VK_DBE_DBCSCHAR}
  VK_DBE_ROMAN                  = $0f5;
  {$EXTERNALSYM VK_DBE_ROMAN}
  VK_DBE_NOROMAN                = $0f6;
  {$EXTERNALSYM VK_DBE_NOROMAN}
  VK_DBE_ENTERWORDREGISTERMODE  = $0f7;
  {$EXTERNALSYM VK_DBE_ENTERWORDREGISTERMODE}
  VK_DBE_ENTERIMECONFIGMODE     = $0f8;
  {$EXTERNALSYM VK_DBE_ENTERIMECONFIGMODE}
  VK_DBE_FLUSHSTRING            = $0f9;
  {$EXTERNALSYM VK_DBE_FLUSHSTRING}
  VK_DBE_CODEINPUT              = $0fa;
  {$EXTERNALSYM VK_DBE_CODEINPUT}
  VK_DBE_NOCODEINPUT            = $0fb;
  {$EXTERNALSYM VK_DBE_NOCODEINPUT}
  VK_DBE_DETERMINESTRING        = $0fc;
  {$EXTERNALSYM VK_DBE_DETERMINESTRING}
  VK_DBE_ENTERDLGCONVERSIONMODE = $0fd;
  {$EXTERNALSYM VK_DBE_ENTERDLGCONVERSIONMODE}

//
//     switch for wParam of IME_SETCONVERSIONWINDOW
//

  MCW_DEFAULT  = $00;
  {$EXTERNALSYM MCW_DEFAULT}
  MCW_RECT     = $01;
  {$EXTERNALSYM MCW_RECT}
  MCW_WINDOW   = $02;
  {$EXTERNALSYM MCW_WINDOW}
  MCW_SCREEN   = $04;
  {$EXTERNALSYM MCW_SCREEN}
  MCW_VERTICAL = $08;
  {$EXTERNALSYM MCW_VERTICAL}
  MCW_HIDDEN   = $10;
  {$EXTERNALSYM MCW_HIDDEN}

//
//    switch for wParam of IME_SETCONVERSIONMODE
//       and IME_GETCONVERSIONMODE
//

  IME_MODE_ALPHANUMERIC = $0001;
  {$EXTERNALSYM IME_MODE_ALPHANUMERIC}

{$IFDEF KOREA}    // BeomOh - 9/29/92
  IME_MODE_SBCSCHAR = $0002;
  {$EXTERNALSYM IME_MODE_SBCSCHAR}
{$ELSE}
  IME_MODE_SBCSCHAR = $0008;
  {$EXTERNALSYM IME_MODE_SBCSCHAR}
{$ENDIF}

  IME_MODE_KATAKANA     = $0002;
  {$EXTERNALSYM IME_MODE_KATAKANA}
  IME_MODE_HIRAGANA     = $0004;
  {$EXTERNALSYM IME_MODE_HIRAGANA}
  IME_MODE_HANJACONVERT = $0004;
  {$EXTERNALSYM IME_MODE_HANJACONVERT}
  IME_MODE_DBCSCHAR     = $0010;
  {$EXTERNALSYM IME_MODE_DBCSCHAR}
  IME_MODE_ROMAN        = $0020;
  {$EXTERNALSYM IME_MODE_ROMAN}
  IME_MODE_NOROMAN      = $0040;
  {$EXTERNALSYM IME_MODE_NOROMAN}
  IME_MODE_CODEINPUT    = $0080;
  {$EXTERNALSYM IME_MODE_CODEINPUT}
  IME_MODE_NOCODEINPUT  = $0100;
  {$EXTERNALSYM IME_MODE_NOCODEINPUT}

//
//

//
//     IME APIs
//

  IME_GETIMECAPS          = $03;
  {$EXTERNALSYM IME_GETIMECAPS}
  IME_SETOPEN             = $04;
  {$EXTERNALSYM IME_SETOPEN}
  IME_GETOPEN             = $05;
  {$EXTERNALSYM IME_GETOPEN}
  IME_GETVERSION          = $07;
  {$EXTERNALSYM IME_GETVERSION}
  IME_SETCONVERSIONWINDOW = $08;
  {$EXTERNALSYM IME_SETCONVERSIONWINDOW}
  IME_MOVEIMEWINDOW       = IME_SETCONVERSIONWINDOW; // KOREA only
  {$EXTERNALSYM IME_MOVEIMEWINDOW}
  IME_SETCONVERSIONMODE   = $10;
  {$EXTERNALSYM IME_SETCONVERSIONMODE}

  IME_GETCONVERSIONMODE     = $11;
  {$EXTERNALSYM IME_GETCONVERSIONMODE}
  IME_SET_MODE              = $12; // KOREA only
  {$EXTERNALSYM IME_SET_MODE}
  IME_SENDVKEY              = $13;
  {$EXTERNALSYM IME_SENDVKEY}
  IME_ENTERWORDREGISTERMODE = $18;
  {$EXTERNALSYM IME_ENTERWORDREGISTERMODE}
  IME_SETCONVERSIONFONTEX   = $19;
  {$EXTERNALSYM IME_SETCONVERSIONFONTEX}

//
// IME_CODECONVERT subfunctions
//

  IME_BANJAtoJUNJA = $13; // KOREA only
  {$EXTERNALSYM IME_BANJAtoJUNJA}
  IME_JUNJAtoBANJA = $14; // KOREA only
  {$EXTERNALSYM IME_JUNJAtoBANJA}
  IME_JOHABtoKS    = $15; // KOREA only
  {$EXTERNALSYM IME_JOHABtoKS}
  IME_KStoJOHAB    = $16; // KOREA only
  {$EXTERNALSYM IME_KStoJOHAB}

//
// IME_AUTOMATA subfunctions
//

  IMEA_INIT = $01; // KOREA only
  {$EXTERNALSYM IMEA_INIT}
  IMEA_NEXT = $02; // KOREA only
  {$EXTERNALSYM IMEA_NEXT}
  IMEA_PREV = $03; // KOREA only
  {$EXTERNALSYM IMEA_PREV}

//
// IME_HANJAMODE subfunctions
//

  IME_REQUEST_CONVERT = $01; // KOREA only
  {$EXTERNALSYM IME_REQUEST_CONVERT}
  IME_ENABLE_CONVERT  = $02; // KOREA only
  {$EXTERNALSYM IME_ENABLE_CONVERT}

//
// IME_MOVEIMEWINDOW subfunctions
//

  INTERIM_WINDOW = $00; // KOREA only
  {$EXTERNALSYM INTERIM_WINDOW}
  MODE_WINDOW    = $01; // KOREA only
  {$EXTERNALSYM MODE_WINDOW}
  HANJA_WINDOW   = $02; // KOREA only
  {$EXTERNALSYM HANJA_WINDOW}

//
//    error code
//

  IME_RS_ERROR       = $01; // genetal error
  {$EXTERNALSYM IME_RS_ERROR}
  IME_RS_NOIME       = $02; // IME is not installed
  {$EXTERNALSYM IME_RS_NOIME}
  IME_RS_TOOLONG     = $05; // given string is too long
  {$EXTERNALSYM IME_RS_TOOLONG}
  IME_RS_ILLEGAL     = $06; // illegal charactor(s) is string
  {$EXTERNALSYM IME_RS_ILLEGAL}
  IME_RS_NOTFOUND    = $07; // no (more) candidate
  {$EXTERNALSYM IME_RS_NOTFOUND}
  IME_RS_NOROOM      = $0a; // no disk/memory space
  {$EXTERNALSYM IME_RS_NOROOM}
  IME_RS_DISKERROR   = $0e; // disk I/O error
  {$EXTERNALSYM IME_RS_DISKERROR}
  IME_RS_INVALID     = $11; // Win3.1/NT
  {$EXTERNALSYM IME_RS_INVALID}
  IME_RS_NEST        = $12; // called nested
  {$EXTERNALSYM IME_RS_NEST}
  IME_RS_SYSTEMMODAL = $13; // called when system mode
  {$EXTERNALSYM IME_RS_SYSTEMMODAL}

//
//   report messge from IME to WinApps
//

  WM_IME_REPORT = $0280;
  {$EXTERNALSYM WM_IME_REPORT}

//
//   report message parameter for WM_IME_REPORT
//

  IR_STRINGSTART   = $100;
  {$EXTERNALSYM IR_STRINGSTART}
  IR_STRINGEND     = $101;
  {$EXTERNALSYM IR_STRINGEND}
  IR_OPENCONVERT   = $120;
  {$EXTERNALSYM IR_OPENCONVERT}
  IR_CHANGECONVERT = $121;
  {$EXTERNALSYM IR_CHANGECONVERT}
  IR_CLOSECONVERT  = $122;
  {$EXTERNALSYM IR_CLOSECONVERT}
  IR_FULLCONVERT   = $123;
  {$EXTERNALSYM IR_FULLCONVERT}
  IR_IMESELECT     = $130;
  {$EXTERNALSYM IR_IMESELECT}
  IR_STRING        = $140;
  {$EXTERNALSYM IR_STRING}
  IR_DBCSCHAR      = $160;
  {$EXTERNALSYM IR_DBCSCHAR}
  IR_UNDETERMINE   = $170;
  {$EXTERNALSYM IR_UNDETERMINE}
  IR_STRINGEX      = $180; // New for 3.1
  {$EXTERNALSYM IR_STRINGEX}
  IR_MODEINFO      = $190;
  {$EXTERNALSYM IR_MODEINFO}

//#define WM_CONVERTREQUESTEX     0x0109

  WM_WNT_CONVERTREQUESTEX = $0109; // WM_CONVERTREQUESTEX: 109 for NT, 108 for OT
  {$EXTERNALSYM WM_WNT_CONVERTREQUESTEX}
  WM_CONVERTREQUEST       = $010A;
  {$EXTERNALSYM WM_CONVERTREQUEST}
  WM_CONVERTRESULT        = $010B;
  {$EXTERNALSYM WM_CONVERTRESULT}
  WM_INTERIM              = $010C;
  {$EXTERNALSYM WM_INTERIM}

  WM_IMEKEYDOWN = $290;
  {$EXTERNALSYM WM_IMEKEYDOWN}
  WM_IMEKEYUP   = $291;
  {$EXTERNALSYM WM_IMEKEYUP}


//
// UNDETERMINESTRING structure for IR_UNDETERMINE
//

type
  tagUNDETERMINESTRUCT = record
    dwSize: DWORD;
    uDefIMESize: UINT;
    uDefIMEPos: UINT;
    uUndetTextLen: UINT;
    uUndetTextPos: UINT;
    uUndetAttrPos: UINT;
    uCursorPos: UINT;
    uDeltaStart: UINT;
    uDetermineTextLen: UINT;
    uDetermineTextPos: UINT;
    uDetermineDelimPos: UINT;
    uYomiTextLen: UINT;
    uYomiTextPos: UINT;
    uYomiDelimPos: UINT;
  end;
  {$EXTERNALSYM tagUNDETERMINESTRUCT}
  UNDETERMINESTRUCT = tagUNDETERMINESTRUCT;
  {$EXTERNALSYM UNDETERMINESTRUCT}
  LPUNDETERMINESTRUCT = ^UNDETERMINESTRUCT;
  {$EXTERNALSYM LPUNDETERMINESTRUCT}
  PUNDETERMINESTRUCT = ^UNDETERMINESTRUCT;
  {$EXTERNALSYM PUNDETERMINESTRUCT}
  NPUNDETERMINESTRUCT = ^UNDETERMINESTRUCT;
  {$EXTERNALSYM NPUNDETERMINESTRUCT}
  TUndetermineStruct = UNDETERMINESTRUCT;

  tagSTRINGEXSTRUCT = record
    dwSize: DWORD;
    uDeterminePos: UINT;
    uDetermineDelimPos: UINT;
    uYomiPos: UINT;
    uYomiDelimPos: UINT;
  end;
  {$EXTERNALSYM tagSTRINGEXSTRUCT}
  STRINGEXSTRUCT = tagSTRINGEXSTRUCT;
  {$EXTERNALSYM STRINGEXSTRUCT}
  LPSTRINGEXSTRUCT = ^STRINGEXSTRUCT;
  {$EXTERNALSYM LPSTRINGEXSTRUCT}
  PSTRINGEXSTRUCT = ^STRINGEXSTRUCT;
  {$EXTERNALSYM PSTRINGEXSTRUCT}
  NPSTRINGEXSTRUCT = ^STRINGEXSTRUCT;
  {$EXTERNALSYM NPSTRINGEXSTRUCT}
  TStringexStruct = STRINGEXSTRUCT;

implementation

const
  imelib = 'user32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _SendIMEMessageExA: Pointer;

function SendIMEMessageExA;
begin
  GetProcedureAddress(_SendIMEMessageExA, imelib, 'SendIMEMessageExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SendIMEMessageExA]
  end;
end;
{$ELSE}
function SendIMEMessageExA; external imelib name 'SendIMEMessageExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SendIMEMessageExW: Pointer;

function SendIMEMessageExW;
begin
  GetProcedureAddress(_SendIMEMessageExW, imelib, 'SendIMEMessageExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SendIMEMessageExW]
  end;
end;
{$ELSE}
function SendIMEMessageExW; external imelib name 'SendIMEMessageExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _SendIMEMessageEx: Pointer;

function SendIMEMessageEx;
begin
  GetProcedureAddress(_SendIMEMessageEx, imelib, 'SendIMEMessageExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SendIMEMessageEx]
  end;
end;
{$ELSE}
function SendIMEMessageEx; external imelib name 'SendIMEMessageExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _SendIMEMessageEx: Pointer;

function SendIMEMessageEx;
begin
  GetProcedureAddress(_SendIMEMessageEx, imelib, 'SendIMEMessageExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SendIMEMessageEx]
  end;
end;
{$ELSE}
function SendIMEMessageEx; external imelib name 'SendIMEMessageExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
