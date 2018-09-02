{******************************************************************************}
{                                                       	               }
{ 16 bit Generic Thunks API interface Unit for Object Pascal                   }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wownt16.h, released June 2000. The original Pascal     }
{ code is: WowNT16.pas, released December 2000. The initial developer of the   }
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

unit JwaWowNT16;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wownt16.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
// 16:16 -> 0:32 Pointer translation.
//
// GetVDMPointer32W will convert the passed in 16-bit address
// to the equivalent 32-bit flat pointer. The upper 16 bits
// of the address are treated according to the value passed in
// fMode: if fMode = 1, then the hiword of vp is used as a
// protected mode selector. Otherwise it is used as a real mode
// segment value.
// The lower 16 bits are treated as the offset.
//
// The return value is 0 if the selector is invalid.
//
// NOTE:  Limit checking is not performed in the retail build
// of Windows NT.  It is performed in the checked (debug) build
// of WOW32.DLL, which will cause 0 to be returned when the
// limit is exceeded by the supplied offset.
//

function GetVDMPointer32W(vp: LPVOID; fMode: UINT): DWORD; stdcall;
{$EXTERNALSYM GetVDMPointer32W}

//
// Win32 module management.
//
// The following routines accept parameters that correspond directly
// to the respective Win32 API function calls that they invoke. Refer
// to the Win32 reference documentation for more detail.

function LoadLibraryEx32W(lpszLibFile: LPCSTR; hFile, dwFlags: DWORD): DWORD; stdcall;
{$EXTERNALSYM LoadLibraryEx32W}
function GetProcAddress32W(hModule: DWORD; lpszProc: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM GetProcAddress32W}
function FreeLibrary32W(hLibModule: DWORD): DWORD; stdcall;
{$EXTERNALSYM FreeLibrary32W}

//
// Generic Thunk Routine:
//
//   CallProc32W
//
// Transitions to 32 bits and calls specified routine
//
// This routine can pass a variable number of arguments, up to 32, to the
// target 32-bit routine. These arguments are given to CallProc32W following
// the 3 required parameters.
//
//   DWORD cParams          - Number of optional DWORD parameters (0-32)
//
//   LPVOID fAddressConvert - Bit Field, for 16:16 address Convertion. The
//                            optional parameters can be automatically converted
//                            from a 16:16 address format to flat by specifying
//                            a 1 bit in the corresponding position in this mask.
//                            eg (bit 1 means convert parameter 1 from 16:16
//                              to flat address before calling routine)
//
//   DWORD lpProcAddress   -  32 bit native address to call (use LoadLibraryEx32W
//                            and GetProcAddress32W to get this address).
//
// Returns:
//   What ever the API returned on 32 bit side in AX:DX
//
// Error Returns:
//   AX = 0, more than 32 parameters.
//
//
// The function prototype must be declared by the application source code
// in the following format:
//
// DWORD FAR PASCAL CallProc32W( DWORD p1, ... , DWORD lpProcAddress,
//                                        DWORD fAddressConvert, DWORD cParams);
//
// where the value in cParams must match the actual number of optional
// parameters (p1-pn) given AND the "DWORD p1, ..." must be replaced by
// the correct number of parameters being passed.  For example, passing 3
// parameter would simply require the removal of the ... and it insertion of
// "DWORD p2, DWORD p3" instead.  The fAddressConvert parameter uses bit 1
// for the last parameter (p3 in our example), with bit 2 for the next to last,
// etc.
//
// Generic Thunk Routine:
//
//   CallProcEx32W
//
// Transitions to 32 bits and calls specified routine
//
// Similar to the CallProc32W function, the CallProcEx32W is an equivalent
// function that is C calling convention and allows easier and more flexible
// prototyping.  See the prototype below.  The fAddressConvert parameter uses
// bit 1 for the 1st parameter, bit 2 for the 2nd parameter, etc.
//
// Both CallProc32W and CallProcEx32W accept a flag OR'd with the parameter
// count to indicate the calling convention of the function in 32 bits.
// For example, to call a cdecl function in 32-bits with 1 parameter, it would
// look like this:
//
// dwResult = CallProcEx32W( CPEX_DEST_CDECL | 1, 0, dwfn32, p1 );
//

// TODO Variable argument list wrapper!

(*
function CallProcEx32W(nParams, fAddressConvert, lpProcAddress: DWORD): DWORD; cdecl;
{$EXTERNALSYM CallProcEx32W}
*)

const
  CPEX_DEST_STDCALL  = DWORD($00000000);
  {$EXTERNALSYM CPEX_DEST_STDCALL}
  CPEX_DEST_CDECL    = DWORD($80000000);
  {$EXTERNALSYM CPEX_DEST_CDECL}

implementation

const
  wow16lib = 'kernel32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _GetVDMPointer32W: Pointer;

function GetVDMPointer32W;
begin
  GetProcedureAddress(_GetVDMPointer32W, wow16lib, '516');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetVDMPointer32W]
  end;
end;
{$ELSE}
function GetVDMPointer32W; external wow16lib index 516;
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _LoadLibraryEx32W: Pointer;

function LoadLibraryEx32W;
begin
  GetProcedureAddress(_LoadLibraryEx32W, wow16lib, '513');
  asm
    mov esp, ebp
    pop ebp
    jmp [_LoadLibraryEx32W]
  end;
end;
{$ELSE}
function LoadLibraryEx32W; external wow16lib index 513;
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetProcAddress32W: Pointer;

function GetProcAddress32W;
begin
  GetProcedureAddress(_GetProcAddress32W, wow16lib, '515');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetProcAddress32W]
  end;
end;
{$ELSE}
function GetProcAddress32W; external wow16lib index 515;
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FreeLibrary32W: Pointer;

function FreeLibrary32W;
begin
  GetProcedureAddress(_FreeLibrary32W, wow16lib, '514');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeLibrary32W]
  end;
end;
{$ELSE}
function FreeLibrary32W; external wow16lib index 514;
{$ENDIF DYNAMIC_LINK}
//function CallProcEx32W; external wow16lib index 517;

end.
