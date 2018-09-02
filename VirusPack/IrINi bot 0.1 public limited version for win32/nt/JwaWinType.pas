{******************************************************************************}
{                                                       	               }
{ Windows Base Types API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: basetsd.h, released August 2001. The original Pascal   }
{ code is: WinType.pas, released December 2000. The initial developer of the   }
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

unit JwaWinType;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "BaseTsd.h"'}
{$HPPEMIT '#include "BaseTyps.h"'}
{$HPPEMIT '#include "NtDef.h"'}
{$HPPEMIT '#include "WinDef.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef LPVOID *LPLPVOID'}
{$HPPEMIT 'typedef GUID TGUID'}
{$HPPEMIT 'typedef GUID *LPGUID'}
{$HPPEMIT 'typedef GUID CLSID'}
{$HPPEMIT 'typedef HMODULE *PHMODULE'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  Windows, SysUtils; // TODO

type
  EJwaError = class (Exception)
  end;

  EJwaLoadLibraryError = class (EJwaError)
  end;

  EJwaGetProcAddressError = class (EJwaError)
  end;

procedure GetProcedureAddress(var P: Pointer; const ModuleName, ProcName: string);

type
  LPLPSTR = ^LPSTR;
  {$NODEFINE LPLPSTR}
  LPLPCSTR = ^LPCSTR;
  {$NODEFINE LPLPCSTR}
  LPLPCWSTR = ^LPCWSTR;
  {$NODEFINE LPLPCWSTR}
  LPLPWSTR = ^LPWSTR;
  {$NODEFINE LPLPWSTR}

  PPChar = ^PChar;
  PPWideChar = ^PWideChar;
  PPointer = ^Pointer;

  GUID = TGUID;
  {$NODEFINE GUID}
  LPGUID = ^GUID;
  {$NODEFINE LPGUID}
  CLSID = TGUID;
  {$NODEFINE CLSID}

// ntdef.h

type

//typedef double DOUBLE;

  PQuad = ^TQuad;
  _QUAD = record                // QUAD is for those times we want
    DoNotUseThisField: Double;  // an 8 byte aligned 8 byte long structure
  end;                          // which is NOT really a floating point
  {$EXTERNALSYM _QUAD}          // number.  Use DOUBLE if you want an FP number.
  QUAD = _QUAD;
  {$EXTERNALSYM QUAD}
  TQuad = _QUAD;

//
// Unsigned Basics
//

  UCHAR = {$IFDEF USE_DELPHI_TYPES}Windows.UCHAR{$ELSE}Char{$ENDIF};
  {$EXTERNALSYM UCHAR}
  USHORT = Word;
  {$EXTERNALSYM USHORT}
  ULONG = {$IFDEF USE_DELPHI_TYPES}Windows.ULONG{$ELSE}Longword{$ENDIF};
  {$EXTERNALSYM ULONG}
  UQUAD = QUAD;
  {$EXTERNALSYM UQUAD}

//
// __int64 is only supported by 2.0 and later midl.
// __midl is set by the 2.0 midl and not by 1.0 midl.
//

type
  LONGLONG = {$IFDEF USE_DELPHI_TYPES}Windows.LONGLONG{$ELSE}Int64{$ENDIF};
  {$EXTERNALSYM LONGLONG}
  ULONGLONG = Int64;
  {$EXTERNALSYM ULONGLONG}

const
  MAXLONGLONG = $7fffffffffffffff;
  {$EXTERNALSYM MAXLONGLONG}

type
  PLONGLONG = ^LONGLONG;
  {$EXTERNALSYM PLONGLONG}
  PULONGLONG = ^ULONGLONG;
  {$EXTERNALSYM PULONGLONG}

  BOOL = {$IFDEF USE_DELPHI_TYPES}Windows.BOOL{$ELSE}LongBool{$ENDIF};
  {$EXTERNALSYM BOOL}

  DWORD = {$IFDEF USE_DELPHI_TYPES}Windows.DWORD{$ELSE}Longword{$ENDIF};
  {$EXTERNALSYM DWORD}

const
  ANYSIZE_ARRAY = 1;
  {$EXTERNALSYM ANYSIZE_ARRAY}

  MAX_NATURAL_ALIGNMENT = SizeOf(ULONG);
  {$EXTERNALSYM MAX_NATURAL_ALIGNMENT}

//
// Void
//

type
  PVOID = Pointer;
  {$EXTERNALSYM PVOID}
  PPVOID = ^PVOID;
  {$EXTERNALSYM PPVOID}
  PVOID64 = Pointer;
  {$EXTERNALSYM PVOID64}

//
// Basics
//

  SHORT = {$IFDEF USE_DELPHI_TYPES}Windows.SHORT{$ELSE}Smallint{$ENDIF};
  {$EXTERNALSYM SHORT}
  LONG = Longint;
  {$EXTERNALSYM LONG}

//
// UNICODE (Wide Character) types
//

  WCHAR = {$IFDEF USE_DELPHI_TYPES}Windows.WCHAR{$ELSE}WideChar{$ENDIF};
  {$EXTERNALSYM WCHAR}

  PWCHAR = {$IFDEF USE_DELPHI_TYPES}Windows.PWChar{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM PWCHAR}
  LPWCH = ^WCHAR;
  {$EXTERNALSYM LPWCH}
  PWCH = ^WCHAR;
  {$EXTERNALSYM PWCH}
  LPCWCH = ^WCHAR;
  {$EXTERNALSYM LPCWCH}
  PCWCH = ^WCHAR;
  {$EXTERNALSYM PCWCH}
  NWPSTR = ^WCHAR;
  {$EXTERNALSYM NWPSTR}
  LPWSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPWSTR{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM LPWSTR}
  LPCWSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCWSTR{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM LPCWSTR}
  PWSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPWSTR{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM PWSTR}
  LPUWSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPWSTR{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM LPUWSTR}
  PUWSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPWSTR{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM PUWSTR}
  LCPUWSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPWSTR{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM LCPUWSTR}
  PCUWSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPWSTR{$ELSE}^WCHAR{$ENDIF};
  {$EXTERNALSYM PCUWSTR}

//
// ANSI (Multi-byte Character) types
//

  LPCH = ^CHAR;
  {$EXTERNALSYM LPCH}
  PCH = ^CHAR;
  {$EXTERNALSYM PCH}

  LPCCH = ^CHAR;
  {$EXTERNALSYM LPCCH}
  PCCH = ^CHAR;
  {$EXTERNALSYM PCCH}
  NPSTR = ^CHAR;
  {$EXTERNALSYM NPSTR}
  LPSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPSTR{$ELSE}^CHAR{$ENDIF};
  {$EXTERNALSYM LPSTR}
  PSTR = {$IFDEF USE_DELPHI_TYPES}PChar{$ELSE}^CHAR{$ENDIF};
  {$EXTERNALSYM PSTR}
  LPCSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCSTR{$ELSE}^CHAR{$ENDIF};
  {$EXTERNALSYM LPCSTR}
  PCSTR = {$IFDEF USE_DELPHI_TYPES}PChar{$ELSE}^CHAR{$ENDIF};
  {$EXTERNALSYM PCSTR}

//
// Neutral ANSI/UNICODE types and macros
//

{$IFDEF UNICODE}

  TCHAR = WCHAR;
  {$EXTERNALSYM TCHAR}
  PTCHAR = ^TCHAR;
  {$EXTERNALSYM PTCHAR}
  TUCHAR = WCHAR;
  {$EXTERNALSYM TUCHAR}
  PTUCHAR = ^TUCHAR;
  {$EXTERNALSYM PTUCHAR}

  LPTCH = LPWSTR;
  {$EXTERNALSYM LPTCH}
  PTCH = LPWSTR;
  {$EXTERNALSYM PTCH}
  PTSTR = LPWSTR;
  {$EXTERNALSYM PTSTR}
  LPTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPTSTR{$ELSE}LPWSTR{$ENDIF};
  {$EXTERNALSYM LPTSTR}
  PCTSTR = LPCWSTR;
  {$EXTERNALSYM PCTSTR}
  LPCTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCTSTR{$ELSE}LPCWSTR{$ENDIF};
  {$EXTERNALSYM LPCTSTR}

  PCUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCTSTR{$ELSE}LPCWSTR{$ENDIF};
  {$EXTERNALSYM PCUTSTR}
  LPCUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCTSTR{$ELSE}LPCWSTR{$ENDIF};
  {$EXTERNALSYM LPCUTSTR}
  PUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCSTR{$ELSE}LPCWSTR{$ENDIF};
  {$EXTERNALSYM PUTSTR}
  LPUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCSTR{$ELSE}LPCWSTR{$ENDIF};
  {$EXTERNALSYM LPUTSTR}

  __TEXT = WideString;
  {$EXTERNALSYM __TEXT}

{$ELSE}

  TCHAR = CHAR;
  {$EXTERNALSYM TCHAR}
  PTCHAR = ^TCHAR;
  {$EXTERNALSYM PTCHAR}
  TUCHAR = CHAR;
  {$EXTERNALSYM TUCHAR}
  PTUCHAR = ^TUCHAR;
  {$EXTERNALSYM PTUCHAR}

  LPTCH = LPSTR;
  {$EXTERNALSYM LPTCH}
  PTCH = LPSTR;
  {$EXTERNALSYM PTCH}
  PTSTR = LPSTR;
  {$EXTERNALSYM PTSTR}
  LPTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPTSTR{$ELSE}LPSTR{$ENDIF};
  {$EXTERNALSYM LPTSTR}
  PCTSTR = LPCSTR;
  {$EXTERNALSYM PCTSTR}
  LPCTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCTSTR{$ELSE}LPCSTR{$ENDIF};
  {$EXTERNALSYM LPCTSTR}

  PCUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCSTR{$ELSE}LPCSTR{$ENDIF};
  {$EXTERNALSYM PCUTSTR}
  LPCUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCSTR{$ELSE}LPCSTR{$ENDIF};
  {$EXTERNALSYM LPCUTSTR}
  PUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCSTR{$ELSE}LPCSTR{$ENDIF};
  {$EXTERNALSYM PUTSTR}
  LPUTSTR = {$IFDEF USE_DELPHI_TYPES}Windows.LPCSTR{$ELSE}LPCSTR{$ENDIF};
  {$EXTERNALSYM LPUTSTR}

  __TEXT = AnsiString;
  {$EXTERNALSYM __TEXT}

{$ENDIF}

  TEXT = __TEXT;
  {$EXTERNALSYM TEXT}

//
// Pointer to Basics
//

  PSHORT = ^SHORT;
  {$EXTERNALSYM PSHORT}
  PLONG = ^LONG;
  {$EXTERNALSYM PLONG}

//
// Pointer to Unsigned Basics
//

  PUCHAR = {$IFDEF USE_DELPHI_TYPES}Windows.PUCHAR{$ELSE}^UCHAR{$ENDIF};
  {$EXTERNALSYM PUCHAR}
  PUSHORT = ^USHORT;
  {$EXTERNALSYM PUSHORT}
  PULONG = {$IFDEF USE_DELPHI_TYPES}Windows.PULONG{$ELSE}^ULONG{$ENDIF};
  {$EXTERNALSYM PULONG}
  PUQUAD = ^UQUAD;
  {$EXTERNALSYM PUQUAD}

//
// Signed characters
//

  SCHAR = Shortint;
  {$EXTERNALSYM SCHAR}
  PSCHAR = ^SCHAR;
  {$EXTERNALSYM PSCHAR}

//
// Handle to an Object
//

  HANDLE = {$IFDEF USE_DELPHI_TYPES}Windows.THandle{$ELSE}Longword{$ENDIF};
  {$EXTERNALSYM HANDLE}
  PHANDLE = {$IFDEF USE_DELPHI_TYPES}Windows.PHandle{$ELSE}^HANDLE{$ENDIF};
  {$EXTERNALSYM PHANDLE}
  THandle = {$IFDEF USE_DELPHI_TYPES}Windows.THandle{$ELSE}HANDLE{$ENDIF};

//
// Flag (bit) fields
//

  FCHAR = UCHAR;
  {$EXTERNALSYM FCHAR}
  FSHORT = USHORT;
  {$EXTERNALSYM FSHORT}
  FLONG = ULONG;
  {$EXTERNALSYM FLONG}

// Component Object Model defines, and macros

  HRESULT = System.HRESULT; // LONG;
  {$EXTERNALSYM HRESULT}

//
// Low order two bits of a handle are ignored by the system and available
// for use by application code as tag bits.  The remaining bits are opaque
// and used to store a serial number and table index.
//

const
  OBJ_HANDLE_TAGBITS = $00000003;
  {$EXTERNALSYM OBJ_HANDLE_TAGBITS}

//
// Cardinal Data Types [0 - 2**N-2)
//

type
  CCHAR = Char;
  {$EXTERNALSYM CCHAR}
  CSHORT = Shortint;
  {$EXTERNALSYM CSHORT}
  CLONG = ULONG;
  {$EXTERNALSYM CLONG}

  PCCHAR = ^CCHAR;
  {$EXTERNALSYM PCCHAR}
  PCSHORT = ^CSHORT;
  {$EXTERNALSYM PCSHORT}
  PCLONG = ^CLONG;
  {$EXTERNALSYM PCLONG}

//
// NLS basics (Locale and Language Ids)
//

  LCID = {$IFDEF USE_DELPHI_TYPES}Windows.LCID{$ELSE}ULONG{$ENDIF};
  {$EXTERNALSYM LCID}
  PLCID = {$IFDEF USE_DELPHI_TYPES}^LCID{$ELSE}PULONG{$ENDIF};
  {$EXTERNALSYM PLCID}
  LANGID = {$IFDEF USE_DELPHI_TYPES}Windows.LANGID{$ELSE}USHORT{$ENDIF};
  {$EXTERNALSYM LANGID}
  PLANGID = ^LANGID; // TODO Not in original header (used in MSI)

//
// Logical Data Type - These are 32-bit logical values.
//

  LOGICAL = ULONG;
  {$EXTERNALSYM LOGICAL}
  PLOGICAL = ^ULONG;
  {$EXTERNALSYM PLOGICAL}

//
// NTSTATUS
//

  NTSTATUS = LONG;
  {$EXTERNALSYM NTSTATUS}
  PNTSTATUS = ^NTSTATUS;
  {$EXTERNALSYM PNTSTATUS}
  TNTStatus = NTSTATUS;

//
//  Status values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-------------------------+-------------------------------+
//  |Sev|C|       Facility          |               Code            |
//  +---+-+-------------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

//
// Generic test for success on any status value (non-negative numbers
// indicate success).
//

function NT_SUCCESS(Status: NTSTATUS): BOOL;
{$EXTERNALSYM NT_SUCCESS}

//
// Generic test for information on any status value.
//

function NT_INFORMATION(Status: NTSTATUS): BOOL;
{$EXTERNALSYM NT_INFORMATION}

//
// Generic test for warning on any status value.
//

function NT_WARNING(Status: NTSTATUS): BOOL;
{$EXTERNALSYM NT_WARNING}

//
// Generic test for error on any status value.
//

function NT_ERROR(Status: NTSTATUS): BOOL;
{$EXTERNALSYM NT_ERROR}

const
  APPLICATION_ERROR_MASK       = $20000000;
  {$EXTERNALSYM APPLICATION_ERROR_MASK}
  ERROR_SEVERITY_SUCCESS       = $00000000;
  {$EXTERNALSYM ERROR_SEVERITY_SUCCESS}
  ERROR_SEVERITY_INFORMATIONAL = $40000000;
  {$EXTERNALSYM ERROR_SEVERITY_INFORMATIONAL}
  ERROR_SEVERITY_WARNING       = DWORD($80000000);
  {$EXTERNALSYM ERROR_SEVERITY_WARNING}
  ERROR_SEVERITY_ERROR         = DWORD($C0000000);
  {$EXTERNALSYM ERROR_SEVERITY_ERROR}

//
// Large (64-bit) integer types and operations
//

type
  LPLARGE_INTEGER = ^LARGE_INTEGER;
  {$EXTERNALSYM LPLARGE_INTEGER}

{$IFDEF USE_DELPHI_TYPES}
  _LARGE_INTEGER = Windows._LARGE_INTEGER;
  LARGE_INTEGER = Windows.LARGE_INTEGER;
  TLargeInteger = Windows.TLargeInteger;
{$ELSE}
  _LARGE_INTEGER = record
    case Integer of
    0: (
      LowPart: DWORD;
      HighPart: LONG);
    1: (
      QuadPart: LONGLONG);
  end;
  {$EXTERNALSYM _LARGE_INTEGER}
  LARGE_INTEGER = _LARGE_INTEGER;
  {$EXTERNALSYM LARGE_INTEGER}
  TLargeInteger = LARGE_INTEGER;
{$ENDIF}

  PLARGE_INTEGER = ^LARGE_INTEGER;
  {$EXTERNALSYM PLARGE_INTEGER}
  PLargeInteger = LPLARGE_INTEGER;

  LPULARGE_INTEGER = ^ULARGE_INTEGER;
  {$EXTERNALSYM LPULARGE_INTEGER}

{$IFDEF USE_DELPHI_TYPES}
  ULARGE_INTEGER = Windows.ULARGE_INTEGER;
  TULargeInteger = Windows.TULargeInteger;
  PULargeInteger = Windows.PULargeInteger;
{$ELSE}
  ULARGE_INTEGER = record
    case Integer of
      0: (
        LowPart: DWORD;
        HighPart: DWORD);
      1: (
        QuadPart: LONGLONG);
  end;
  {$EXTERNALSYM ULARGE_INTEGER}
  TULargeInteger = ULARGE_INTEGER;
  PULargeInteger = LPULARGE_INTEGER;
{$ENDIF}

  PULARGE_INTEGER = ^ULARGE_INTEGER;
  {$EXTERNALSYM PULARGE_INTEGER}

  TIME = LARGE_INTEGER;
  {$EXTERNALSYM TIME}
  _TIME = _LARGE_INTEGER;
  {$EXTERNALSYM _TIME}
  PTIME = PLARGE_INTEGER;
  {$EXTERNALSYM PTIME}

//
// _M_IX86 included so that EM CONTEXT structure compiles with
// x86 programs. *** TBD should this be for all architectures?
//

//
// 16 byte aligned type for 128 bit floats
//

//
// For we define a 128 bit structure and use __declspec(align(16)) pragma to
// align to 128 bits.
//

type
  PFloat128 = ^TFloat128;
  _FLOAT128 = record
    LowPart: Int64;
    HighPart: Int64;
  end;
  {$EXTERNALSYM _FLOAT128}
  FLOAT128 = _FLOAT128;
  {$EXTERNALSYM FLOAT128}
  TFloat128 = FLOAT128;

// Update Sequence Number

  USN = LONGLONG;
  {$EXTERNALSYM USN}

//
// Locally Unique Identifier
//

type
  PLuid = ^LUID;
  _LUID = record
    LowPart: DWORD;
    HighPart: LONG;
  end;
  {$EXTERNALSYM _LUID}
  LUID = _LUID;
  {$EXTERNALSYM LUID}  
  TLuid = LUID;

  DWORDLONG = ULONGLONG;
  {$EXTERNALSYM DWORDLONG}
  PDWORDLONG = ^DWORDLONG;
  {$EXTERNALSYM PDWORDLONG}

//
// Physical address.
//

  PHYSICAL_ADDRESS = LARGE_INTEGER;
  {$EXTERNALSYM PHYSICAL_ADDRESS}
  PPHYSICAL_ADDRESS = ^LARGE_INTEGER;
  {$EXTERNALSYM PPHYSICAL_ADDRESS}

//
// Define operations to logically shift an int64 by 0..31 bits and to multiply
// 32-bits by 32-bits to form a 64-bit product.
//

//
// The x86 C compiler understands inline assembler. Therefore, inline functions
// that employ inline assembler are used for shifts of 0..31.  The multiplies
// rely on the compiler recognizing the cast of the multiplicand to int64 to
// generate the optimal code inline.
//

function Int32x32To64(a, b: LONG): LONGLONG;
{$EXTERNALSYM Int32x32To64}
function UInt32x32To64(a, b: DWORD): ULONGLONG;
{$EXTERNALSYM UInt32x32To64}

function Int64ShllMod32(Value: ULONGLONG; ShiftCount: DWORD): ULONGLONG;

{$EXTERNALSYM Int64ShllMod32}
function Int64ShraMod32(Value: LONGLONG; ShiftCount: DWORD): LONGLONG;
{$EXTERNALSYM Int64ShraMod32}
function Int64ShrlMod32(Value: ULONGLONG; ShiftCount: DWORD): ULONGLONG;
{$EXTERNALSYM Int64ShrlMod32}

//
// Event type
//

type
  _EVENT_TYPE = (NotificationEvent, SynchronizationEvent);
  {$EXTERNALSYM _EVENT_TYPE}
  EVENT_TYPE = _EVENT_TYPE;
  {$EXTERNALSYM EVENT_TYPE}
  TEventType = _EVENT_TYPE;

//
// Timer type
//

  _TIMER_TYPE = (NotificationTimer, SynchronizationTimer);
  {$EXTERNALSYM _TIMER_TYPE}
  TIMER_TYPE = _TIMER_TYPE;
  {$EXTERNALSYM TIMER_TYPE}

//
// Wait type
//

  _WAIT_TYPE = (WaitAll, WaitAny);
  {$EXTERNALSYM _WAIT_TYPE}
  WAIT_TYPE = _WAIT_TYPE;
  {$EXTERNALSYM WAIT_TYPE}

//
// Pointer to an Asciiz string
//

  PSZ = ^CHAR;
  {$EXTERNALSYM PSZ}
  PCSZ = ^CHAR;
  {$EXTERNALSYM PCSZ}

//
// Counted String
//

  PString = ^TString;
  _STRING = record
    Length: USHORT;
    MaximumLength: USHORT;
    Buffer: PCHAR;
  end;
  {$EXTERNALSYM _STRING}
  TString = _STRING;

  ANSI_STRING = _STRING;
  {$EXTERNALSYM ANSI_STRING}
  PANSI_STRING = PSTRING;
  {$EXTERNALSYM PANSI_STRING}

  OEM_STRING = _STRING;
  {$EXTERNALSYM OEM_STRING}
  POEM_STRING = PSTRING;
  {$EXTERNALSYM POEM_STRING}

//
// CONSTCounted String
//

  PCString = ^CSTRING;
  _CSTRING = record
    Length: USHORT;
    MaximumLength: USHORT;
    Buffer: PCHAR;
  end;
  {$EXTERNALSYM _CSTRING}
  CSTRING = _CSTRING;
  {$EXTERNALSYM CSTRING}
  TCString = CSTRING;

const
  ANSI_NULL = CHAR(0);
  {$EXTERNALSYM ANSI_NULL}
  UNICODE_NULL = WCHAR(0);
  {$EXTERNALSYM UNICODE_NULL}
  UNICODE_STRING_MAX_BYTES = WORD(65534);
  {$EXTERNALSYM UNICODE_STRING_MAX_BYTES}
  UNICODE_STRING_MAX_CHARS = 32767;
  {$EXTERNALSYM UNICODE_STRING_MAX_CHARS}

type
  CANSI_STRING = _STRING;
  {$EXTERNALSYM CANSI_STRING}
  PCANSI_STRING = PSTRING;
  {$EXTERNALSYM PCANSI_STRING}

//
// Unicode strings are counted 16-bit character strings. If they are
// NULL terminated, Length does not include trailing NULL.
//

type
  PUNICODE_STRING = ^UNICODE_STRING;
  {$EXTERNALSYM PUNICODE_STRING}
  _UNICODE_STRING = record
    Length: USHORT;
    MaximumLength: USHORT;
    Buffer: PWSTR;
  end;
  {$EXTERNALSYM _UNICODE_STRING}
  UNICODE_STRING = _UNICODE_STRING;
  {$EXTERNALSYM UNICODE_STRING}
  PCUNICODE_STRING = ^UNICODE_STRING;
  {$EXTERNALSYM PCUNICODE_STRING}
  TUnicodeString = UNICODE_STRING;
  PUnicodeString = PUNICODE_STRING;

//
// Boolean
//

type
//typedef UCHAR BOOLEAN;
  PBOOLEAN = ^ByteBool;
  {$EXTERNALSYM PBOOLEAN}

//
//  Doubly linked list structure.  Can be used as either a list head, or
//  as link words.
//

type
  PLIST_ENTRY = ^LIST_ENTRY;
  {$EXTERNALSYM PLIST_ENTRY}

{$IFDEF USE_DELPHI_TYPES}
  _LIST_ENTRY = Windows._LIST_ENTRY;
  LIST_ENTRY = Windows.LIST_ENTRY;
  TListEntry = Windows.TListEntry;
  PListEntry = Windows.PListEntry;
{$ELSE}
  _LIST_ENTRY = record
    Flink: PLIST_ENTRY;
    Blink: PLIST_ENTRY;
  end;
  {$EXTERNALSYM _LIST_ENTRY}
  LIST_ENTRY = _LIST_ENTRY;
  {$EXTERNALSYM LIST_ENTRY}
  TListEntry = LIST_ENTRY;
  PListEntry = PLIST_ENTRY;
{$ENDIF}

  PRLIST_ENTRY = ^LIST_ENTRY;
  {$EXTERNALSYM PLIST_ENTRY}

//
//  Singly linked list structure. Can be used as either a list head, or
//  as link words.
//

  PSINGLE_LIST_ENTRY = ^SINGLE_LIST_ENTRY;
  {$EXTERNALSYM PSINGLE_LIST_ENTRY}
  _SINGLE_LIST_ENTRY = record
    Next: PSINGLE_LIST_ENTRY;
  end;
  {$EXTERNALSYM _SINGLE_LIST_ENTRY}
  SINGLE_LIST_ENTRY = _SINGLE_LIST_ENTRY;
  {$EXTERNALSYM SINGLE_LIST_ENTRY}
  TSingleListEntry = SINGLE_LIST_ENTRY;
  PSingleListEntry = PSINGLE_LIST_ENTRY;

//
// These are needed for portable debugger support.
//

  PLIST_ENTRY32 = ^LIST_ENTRY32;
  {$EXTERNALSYM PLIST_ENTRY32}  
  {$EXTERNALSYM PLIST_ENTRY32}
  LIST_ENTRY32 = record
    Flink: DWORD;
    Blink: DWORD;
  end;
  {$EXTERNALSYM LIST_ENTRY32}
  TListEntry32 = LIST_ENTRY32;
  PListEntry32 = PLIST_ENTRY32;

  PLIST_ENTRY64 = ^LIST_ENTRY64;
  {$EXTERNALSYM PLIST_ENTRY64}
  LIST_ENTRY64 = record
    Flink: ULONGLONG;
    Blink: ULONGLONG;
  end;
  {$EXTERNALSYM LIST_ENTRY64}
  TListEntry64 = LIST_ENTRY64;
  PListEntry64 = PLIST_ENTRY64;

procedure ListEntry32To64(l32: PLIST_ENTRY32; l64: PLIST_ENTRY64);
{$EXTERNALSYM ListEntry32To64}

procedure ListEntry64To32(l64: PLIST_ENTRY64; l32: PLIST_ENTRY32);
{$EXTERNALSYM ListEntry64To32}

//
// These macros are used to walk lists on a target system
//

{
#define CONTAINING_RECORD32(address, type, field) ( \
                                                  (ULONG_PTR)(address) - \
                                                  (ULONG_PTR)(&((type *)0)->field))

#define CONTAINING_RECORD64(address, type, field) ( \
                                                  (ULONGLONG)(address) - \
                                                  (ULONGLONG)(&((type *)0)->field))
}

type
  PString32 = ^STRING32;
  _STRING32 = record
    Length: USHORT;
    MaximumLength: USHORT;
    Buffer: ULONG;
  end;
  {$EXTERNALSYM _STRING32}
  STRING32 = _STRING32;
  {$EXTERNALSYM STRING32}
  TString32 = STRING32;

  UNICODE_STRING32 = STRING32;
  {$EXTERNALSYM UNICODE_STRING32}
  PUNICODE_STRING32 = ^UNICODE_STRING32;
  {$EXTERNALSYM PUNICODE_STRING32}

  ANSI_STRING32 = STRING32;
  {$EXTERNALSYM ANSI_STRING32}
  PANSI_STRING32 = ^ANSI_STRING32;
  {$EXTERNALSYM PANSI_STRING32}

  PString64 = ^STRING64;
  _STRING64 = record
    Length: USHORT;
    MaximumLength: USHORT;
    Buffer: ULONGLONG;
  end;
  {$EXTERNALSYM _STRING64}
  STRING64 = _STRING64;
  {$EXTERNALSYM STRING64}
  TString64 = STRING64;

  UNICODE_STRING64 = STRING64;
  {$EXTERNALSYM UNICODE_STRING64}
  PUNICODE_STRING64 = ^UNICODE_STRING64;
  {$EXTERNALSYM PUNICODE_STRING64}

  ANSI_STRING64 = STRING64;
  {$EXTERNALSYM ANSI_STRING64}
  PANSI_STRING64 = ^ANSI_STRING64;
  {$EXTERNALSYM PANSI_STRING64}

//
// Valid values for the Attributes field
//

const
  OBJ_INHERIT          = $00000002;
  {$EXTERNALSYM OBJ_INHERIT}
  OBJ_PERMANENT        = $00000010;
  {$EXTERNALSYM OBJ_PERMANENT}
  OBJ_EXCLUSIVE        = $00000020;
  {$EXTERNALSYM OBJ_EXCLUSIVE}
  OBJ_CASE_INSENSITIVE = $00000040;
  {$EXTERNALSYM OBJ_CASE_INSENSITIVE}
  OBJ_OPENIF           = $00000080;
  {$EXTERNALSYM OBJ_OPENIF}
  OBJ_OPENLINK         = $00000100;
  {$EXTERNALSYM OBJ_OPENLINK}
  OBJ_KERNEL_HANDLE    = $00000200;
  {$EXTERNALSYM OBJ_KERNEL_HANDLE}
  OBJ_VALID_ATTRIBUTES = $000003F2;
  {$EXTERNALSYM OBJ_VALID_ATTRIBUTES}

//
// Object Attributes structure
//

type
  POBJECT_ATTRIBUTES = ^OBJECT_ATTRIBUTES;
  {$EXTERNALSYM POBJECT_ATTRIBUTES}
  _OBJECT_ATTRIBUTES = record
    Length: ULONG;
    RootDirectory: HANDLE;
    ObjectName: PUNICODE_STRING;
    Attributes: ULONG;
    SecurityDescriptor: PVOID;       // Points to type SECURITY_DESCRIPTOR
    SecurityQualityOfService: PVOID; // Points to type SECURITY_QUALITY_OF_SERVICE
  end;
  {$EXTERNALSYM _OBJECT_ATTRIBUTES}
  OBJECT_ATTRIBUTES = _OBJECT_ATTRIBUTES;
  {$EXTERNALSYM OBJECT_ATTRIBUTES}
  TObjectAttributes = OBJECT_ATTRIBUTES;
  PObjectAttributes = POBJECT_ATTRIBUTES;

procedure InitializeObjectAttributes(p: POBJECT_ATTRIBUTES; n: PUNICODE_STRING;
  a: ULONG; r: HANDLE; s: PVOID{PSECURITY_DESCRIPTOR});
{$EXTERNALSYM InitializeObjectAttributes}

//
// Constants
//

const

//#define FALSE   0
//#define TRUE    1

  NULL   = 0;
  {$EXTERNALSYM NULL}
  NULL64 = 0;
  {$EXTERNALSYM NULL64}

//#include <guiddef.h>

type
  PObjectId = ^OBJECTID;
  _OBJECTID = record  // size is 20
    Lineage: GUID;
    Uniquifier: ULONG;
  end;
  {$EXTERNALSYM _OBJECTID}
  OBJECTID = _OBJECTID;
  {$EXTERNALSYM OBJECTID}
  TObjectId = OBJECTID;

const
  MINCHAR   = $80;
  {$EXTERNALSYM MINCHAR}
  MAXCHAR   = $7f;
  {$EXTERNALSYM MAXCHAR}
  MINSHORT  = $8000;
  {$EXTERNALSYM MINSHORT}
  MAXSHORT  = $7fff;
  {$EXTERNALSYM MAXSHORT}
  MINLONG   = DWORD($80000000);
  {$EXTERNALSYM MINLONG}
  MAXLONG   = $7fffffff;
  {$EXTERNALSYM MAXLONG}
  MAXUCHAR  = $ff;
  {$EXTERNALSYM MAXUCHAR}
  MAXUSHORT = $ffff;
  {$EXTERNALSYM MAXUSHORT}
  MAXULONG  = DWORD($ffffffff);
  {$EXTERNALSYM MAXULONG}

//
// Useful Helper Macros
//

//
// Determine if an argument is present by testing the value of the pointer
// to the argument value.
//

function ARGUMENT_PRESENT(ArgumentPointer: Pointer): BOOL;
{$EXTERNALSYM ARGUMENT_PRESENT}

//
// Exception handler routine definition.
//

// struct _CONTEXT;
// struct _EXCEPTION_RECORD;

//type
//  PEXCEPTION_ROUTINE = function (ExceptionRecord: LP_EXCEPTION_RECORD;
//    EstablisherFrame: PVOID; ContextRecord: LPCONTEXT;
//    DispatcherContext: PVOID): EXCEPTION_DISPOSITION; stdcall;
//  {$EXTERNALSYM PEXCEPTION_ROUTINE}

//
// Interrupt Request Level (IRQL)
//

type
  KIRQL = UCHAR;
  {$EXTERNALSYM KIRQL}
  PKIRQL = ^KIRQL;
  {$EXTERNALSYM PKIRQL}

//
// Product types
//

  _NT_PRODUCT_TYPE = (Filler0, NtProductWinNt, NtProductLanManNt, NtProductServer);
  {$EXTERNALSYM _NT_PRODUCT_TYPE}
  NT_PRODUCT_TYPE = _NT_PRODUCT_TYPE;
  {$EXTERNALSYM NT_PRODUCT_TYPE}
  PNT_PRODUCT_TYPE = ^NT_PRODUCT_TYPE;
  TNtProductType = _NT_PRODUCT_TYPE;

//
// the bit mask, SharedUserData->SuiteMask, is a ULONG
// so there can be a maximum of 32 entries
// in this enum.
//

type
  _SUITE_TYPE = (
    SmallBusiness,
    Enterprise,
    BackOffice,
    CommunicationServer,
    TerminalServer,
    SmallBusinessRestricted,
    EmbeddedNT,
    DataCenter,
    SingleUserTS,
    MaxSuiteType);
  {$EXTERNALSYM _SUITE_TYPE}
  SUITE_TYPE = _SUITE_TYPE;
  {$EXTERNALSYM SUITE_TYPE}
  TSuiteType = SUITE_TYPE;

const
  VER_SERVER_NT                      = DWORD($80000000);
  {$EXTERNALSYM VER_SERVER_NT}
  VER_WORKSTATION_NT                 = $40000000;
  {$EXTERNALSYM VER_WORKSTATION_NT}
  VER_SUITE_SMALLBUSINESS            = $00000001;
  {$EXTERNALSYM VER_SUITE_SMALLBUSINESS}
  VER_SUITE_ENTERPRISE               = $00000002;
  {$EXTERNALSYM VER_SUITE_ENTERPRISE}
  VER_SUITE_BACKOFFICE               = $00000004;
  {$EXTERNALSYM VER_SUITE_BACKOFFICE}
  VER_SUITE_COMMUNICATIONS           = $00000008;
  {$EXTERNALSYM VER_SUITE_COMMUNICATIONS}
  VER_SUITE_TERMINAL                 = $00000010;
  {$EXTERNALSYM VER_SUITE_TERMINAL}
  VER_SUITE_SMALLBUSINESS_RESTRICTED = $00000020;
  {$EXTERNALSYM VER_SUITE_SMALLBUSINESS_RESTRICTED}
  VER_SUITE_EMBEDDEDNT               = $00000040;
  {$EXTERNALSYM VER_SUITE_EMBEDDEDNT}
  VER_SUITE_DATACENTER               = $00000080;
  {$EXTERNALSYM VER_SUITE_DATACENTER}
  VER_SUITE_SINGLEUSERTS             = $00000100;
  {$EXTERNALSYM VER_SUITE_SINGLEUSERTS}
  VER_SUITE_PERSONAL                 = $00000200;
  {$EXTERNALSYM VER_SUITE_PERSONAL}
  VER_SUITE_BLADE                    = $00000400;
  {$EXTERNALSYM VER_SUITE_BLADE}

// ntdef.h

type
  error_status_t = Longword;
  {$EXTERNALSYM error_status_t}
  wchar_t = Word;
  {$EXTERNALSYM wchar_t}

//
// The following types are guaranteed to be signed and 32 bits wide.
//

type
  INT_PTR = Integer;
  {$EXTERNALSYM INT_PTR}
  PINT_PTR = ^INT_PTR;
  {$EXTERNALSYM PINT_PTR}
  UINT_PTR = Longword;
  {$EXTERNALSYM UINT_PTR}
  PUINT_PTR = ^UINT_PTR;
  {$EXTERNALSYM PUINT_PTR}
  LONG_PTR = Longint;
  {$EXTERNALSYM LONG_PTR}
  PLONG_PTR = ^LONG_PTR;
  {$EXTERNALSYM PLONG_PTR}
  ULONG_PTR = Longword;
  {$EXTERNALSYM ULONG_PTR}
  PULONG_PTR = ^ULONG_PTR;
  {$EXTERNALSYM PULONG_PTR}

  LONG32 = Integer;
  {$EXTERNALSYM LONG32}
  PLONG32 = ^LONG32;
  {$EXTERNALSYM PLONG32}
  INT32 = Integer;
  {$EXTERNALSYM INT32}
  PINT32 = ^INT32;
  {$EXTERNALSYM PINT32}

//
// The following types are guaranteed to be unsigned and 32 bits wide.
//

  ULONG32 = Longword;
  {$EXTERNALSYM ULONG32}
  PULONG32 = ^ULONG32;
  {$EXTERNALSYM PULONG32}
  DWORD32 = Longword;
  {$EXTERNALSYM DWORD32}
  PDWORD32 = ^DWORD32;
  {$EXTERNALSYM PDWORD32}
  UINT32 = Longword;
  {$EXTERNALSYM UINT32}
  PUINT32 = ^UINT32;
  {$EXTERNALSYM PUINT32}

const
  MAX_PATH = 260;
  {$EXTERNALSYM MAX_PATH}

type

//unsigned char       BYTE;
//unsigned short      WORD;

  FLOAT = Single;
  {$EXTERNALSYM FLOAT}
  PFLOAT = ^FLOAT;
  {$EXTERNALSYM PFLOAT}
  PBOOL = {$IFDEF USE_DELPHI_TYPES}Windows.PBOOL{$ELSE}^BOOL{$ENDIF};
  {$EXTERNALSYM PBOOL}
  LPBOOL = {$IFDEF USE_DELPHI_TYPES}Windows.PBOOL{$ELSE}^BOOL{$ENDIF};
  {$EXTERNALSYM LPBOOL}
  PBYTE = {$IFDEF USE_DELPHI_TYPES}Windows.PBYTE{$ELSE}^BYTE{$ENDIF};
  {$EXTERNALSYM PBYTE}
  LPBYTE = {$IFDEF USE_DELPHI_TYPES}Windows.PBYTE{$ELSE}^BYTE{$ENDIF};
  {$EXTERNALSYM LPBYTE}
  PINT = {$IFDEF USE_DELPHI_TYPES}Windows.PINT{$ELSE}^INT{$ENDIF};
  {$EXTERNALSYM PINT}
  PUINT = {$IFDEF USE_DELPHI_TYPES}Windows.PUINT{$ELSE}^UINT{$ENDIF};
  {$EXTERNALSYM PUINT}
  LPUINT = {$IFDEF USE_DELPHI_TYPES}Windows.PUINT{$ELSE}^UINT{$ENDIF};
  {$EXTERNALSYM LPUINT}
  LPINT = {$IFDEF USE_DELPHI_TYPES}Windows.PINT{$ELSE}^INT{$ENDIF};
  {$EXTERNALSYM LPINT}
  PWORD = {$IFDEF USE_DELPHI_TYPES}Windows.PWORD{$ELSE}^WORD{$ENDIF};
  {$EXTERNALSYM PWORD}
  LPWORD = {$IFDEF USE_DELPHI_TYPES}Windows.PWORD{$ELSE}^WORD{$ENDIF};
  {$EXTERNALSYM LPWORD}
  LPLONG = ^LONG;
  {$EXTERNALSYM LPLONG}
  PDWORD = {$IFDEF USE_DELPHI_TYPES}Windows.PDWORD{$ELSE}^DWORD{$ENDIF};
  {$EXTERNALSYM PDWORD}
  LPDWORD = {$IFDEF USE_DELPHI_TYPES}Windows.LPDWORD{$ELSE}^DWORD{$ENDIF};
  {$EXTERNALSYM LPDWORD}
  LPVOID = Pointer;
  {$EXTERNALSYM LPVOID}
  LPCVOID = Pointer;
  {$EXTERNALSYM LPCVOID}
  LPLPVOID = ^LPVOID;
  {$NODEFINE LPVOID}

  INT = Integer;
  {$EXTERNALSYM INT}
  UINT = {$IFDEF USE_DELPHI_TYPES}Windows.UINT{$ELSE}Longword{$ENDIF};
  {$EXTERNALSYM UINT}

// Types use for passing & returning polymorphic values

  WPARAM = {$IFDEF USE_DELPHI_TYPES}Windows.WPARAM{$ELSE}UINT_PTR{$ENDIF};
  {$EXTERNALSYM WPARAM}
  LPARAM = {$IFDEF USE_DELPHI_TYPES}Windows.LPARAM{$ELSE}LONG_PTR{$ENDIF};
  {$EXTERNALSYM LPARAM}
  LRESULT = {$IFDEF USE_DELPHI_TYPES}Windows.LRESULT{$ELSE}LONG_PTR{$ENDIF};
  {$EXTERNALSYM LRESULT}

function MAKEWORD(a, b: BYTE): WORD;
{$EXTERNALSYM MAKEWORD}
function MAKELONG(a, b: WORD): DWORD;
{$EXTERNALSYM MAKELONG}

function LOWORD(L: DWORD): WORD;
{$EXTERNALSYM LOWORD}
function HIWORD(L: DWORD): WORD;
{$EXTERNALSYM HIWORD}
function LOBYTE(W: WORD): BYTE;
{$EXTERNALSYM LOBYTE}
function HIBYTE(W: WORD): BYTE;
{$EXTERNALSYM HIBYTE}

type
  HWND = {$IFDEF USE_DELPHI_TYPES}Windows.HWND{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HWND}
  LPHWND = ^HWND;
  {$EXTERNALSYM LPHWND}
  HHOOK = {$IFDEF USE_DELPHI_TYPES}Windows.HHOOK{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HHOOK}
  LPHHOOK = ^HHOOK;
  {$EXTERNALSYM LPHHOOK}
  HEVENT = HANDLE;
  {$EXTERNALSYM HEVENT}

  ATOM = {$IFDEF USE_DELPHI_TYPES}Windows.ATOM{$ELSE}WORD{$ENDIF};
  {$EXTERNALSYM ATOM}

  SPHANDLE = ^HANDLE;
  {$EXTERNALSYM SPHANDLE}
  LPHANDLE = ^HANDLE;
  {$EXTERNALSYM LPHANDLE}
  HGLOBAL = {$IFDEF USE_DELPHI_TYPES}Windows.HGLOBAL{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HGLOBAL}
  HLOCAL = {$IFDEF USE_DELPHI_TYPES}Windows.HLOCAL{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HLOCAL}
  GLOBALHANDLE = HANDLE;
  {$EXTERNALSYM GLOBALHANDLE}
  //LOCALHANDLE = HANDLE; // todo clashes with WinBase.LocalHandle function
  //{$EXTERNALSYM LOCALHANDLE}
  FARPROC = {$IFDEF USE_DELPHI_TYPES}Windows.FARPROC{$ELSE}function: Integer{$ENDIF};
  {$EXTERNALSYM FARPROC}
  NEARPROC = function: Integer; stdcall;
  {$EXTERNALSYM NEARPROC}
  PROC = function: Integer; stdcall;
  {$EXTERNALSYM PROC}

  HGDIOBJ = {$IFDEF USE_DELPHI_TYPES}Windows.HGDIOBJ{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HGDIOBJ}

  HKEY = {$IFDEF USE_DELPHI_TYPES}Windows.HKEY{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HKEY}
  PHKEY = {$IFDEF USE_DELPHI_TYPES}Windows.PHKEY{$ELSE}^HKEY{$ENDIF};
  {$EXTERNALSYM PHKEY}

  HACCEL = {$IFDEF USE_DELPHI_TYPES}Windows.HACCEL{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HACCEL}

  HBITMAP = {$IFDEF USE_DELPHI_TYPES}Windows.HBITMAP{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HBITMAP}
  HBRUSH = {$IFDEF USE_DELPHI_TYPES}Windows.HBRUSH{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HBRUSH}

  HCOLORSPACE = {$IFDEF USE_DELPHI_TYPES}Windows.HCOLORSPACE{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HCOLORSPACE}

  HDC = {$IFDEF USE_DELPHI_TYPES}Windows.HDC{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HDC}
  HGLRC = {$IFDEF USE_DELPHI_TYPES}Windows.HGLRC{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HGLRC}
  HDESK = {$IFDEF USE_DELPHI_TYPES}Windows.HDESK{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HDESK}
  HENHMETAFILE = {$IFDEF USE_DELPHI_TYPES}Windows.HENHMETAFILE{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HENHMETAFILE}
  HFONT = {$IFDEF USE_DELPHI_TYPES}Windows.HFONT{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HFONT}
  HICON = {$IFDEF USE_DELPHI_TYPES}Windows.HICON{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HICON}
  HMENU = {$IFDEF USE_DELPHI_TYPES}Windows.HMENU{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HMENU}
  HMETAFILE = {$IFDEF USE_DELPHI_TYPES}Windows.HMETAFILE{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HMETAFILE}
  HINSTANCE = {$IFDEF USE_DELPHI_TYPES}Windows.HINST{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HINSTANCE}
  HMODULE = {$IFDEF USE_DELPHI_TYPES}Windows.HMODULE{$ELSE}HINSTANCE{$ENDIF};
  {$EXTERNALSYM HMODULE}
  HPALETTE = {$IFDEF USE_DELPHI_TYPES}Windows.HPALETTE{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HPALETTE}
  HPEN = {$IFDEF USE_DELPHI_TYPES}Windows.HPEN{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HPEN}
  HRGN = {$IFDEF USE_DELPHI_TYPES}Windows.HRGN{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HRGN}
  HRSRC = {$IFDEF USE_DELPHI_TYPES}Windows.HRSRC{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HRSRC}
  HSTR = {$IFDEF USE_DELPHI_TYPES}Windows.HSTR{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HSTR}
  HTASK = {$IFDEF USE_DELPHI_TYPES}Windows.HTASK{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HTASK}
  HWINSTA = {$IFDEF USE_DELPHI_TYPES}Windows.HWINSTA{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HWINSTA}
  HKL = {$IFDEF USE_DELPHI_TYPES}Windows.HKL{$ELSE}HANDLE{$ENDIF};
  {$EXTERNALSYM HKL}
  PHKL = {$IFDEF USE_DELPHI_TYPES}^HKL{$ELSE}^HANDLE{$ENDIF};
  {$EXTERNALSYM PHKL}

  HMONITOR = HANDLE;
  {$EXTERNALSYM HMONITOR}
  HWINEVENTHOOK = HANDLE;
  {$EXTERNALSYM HWINEVENTHOOK}
  HUMPD = HANDLE;
  {$EXTERNALSYM HUMPD}  

  HFILE = {$IFDEF USE_DELPHI_TYPES}Windows.HFILE{$ELSE}Integer{$ENDIF};
  {$EXTERNALSYM HFILE}
  HCURSOR = {$IFDEF USE_DELPHI_TYPES}Windows.HCURSOR{$ELSE}HICON{$ENDIF};
  {$EXTERNALSYM HCURSOR}

  COLORREF = {$IFDEF USE_DELPHI_TYPES}Windows.COLORREF{$ELSE}DWORD{$ENDIF};
  {$EXTERNALSYM COLORREF}
  LPCOLORREF = ^COLORREF;
  {$EXTERNALSYM LPCOLORREF}

  PHMODULE = ^HMODULE;
  {$NODEFINE PHMODULE}

const
  HFILE_ERROR = HFILE(-1);
  {$EXTERNALSYM HFILE_ERROR}

type
  LPRECT = ^RECT;
  {$EXTERNALSYM LPRECT}
  tagRECT = record
    left: LONG;
    top: LONG;
    right: LONG;
    bottom: LONG;
  end;
  {$EXTERNALSYM tagRECT}
  RECT = {$IFDEF USE_DELPHI_TYPES}Windows.TRect{$ELSE}tagRECT{$ENDIF};
  {$EXTERNALSYM RECT}
  NPRECT = ^RECT;
  {$EXTERNALSYM NPRECT}
  LPCRECT = ^RECT;
  {$EXTERNALSYM LPCRECT}
  TRect = {$IFDEF USE_DELPHI_TYPES}Windows.TRect{$ELSE}RECT{$ENDIF};
  PRect = {$IFDEF USE_DELPHI_TYPES}Windows.PRect{$ELSE}LPRECT{$ENDIF};

  LPRECTL = ^RECTL;
  {$EXTERNALSYM LPRECTL}
  _RECTL = record
    left: LONG;
    top: LONG;
    right: LONG;
    bottom: LONG;
  end;
  {$EXTERNALSYM _RECTL}
  RECTL = _RECTL;
  {$EXTERNALSYM RECTL}
  LPCRECTL = ^_RECTL;
  {$EXTERNALSYM LPCRECTL}
  TRectl = RECTL;
  PRectl = LPRECTL;

  LPPOINT = ^POINT;
  {$EXTERNALSYM LPPOINT}
  tagPOINT = record
    x: LONG;
    y: LONG;
  end;
  {$EXTERNALSYM tagPOINT}
  NPPOINT = ^tagPoint;
  {$EXTERNALSYM NPPOINT}
  POINT = tagPOINT;
  {$EXTERNALSYM tagPOINT}
  TPoint = {$IFDEF USE_DELPHI_TYPES}Windows.TPoint{$ELSE}POINT{$ENDIF};
  PPoint = {$IFDEF USE_DELPHI_TYPES}Windows.PPoint{$ELSE}LPPOINT{$ENDIF};

  PPointl = ^POINTL;
  _POINTL = record
    x: LONG;
    y: LONG;
  end;
  {$EXTERNALSYM _POINTL}
  POINTL = _POINTL;
  {$EXTERNALSYM POINTL}
  TPointl = POINTL;

  LPSIZE = ^TSize;
  {$EXTERNALSYM LPSIZE}

{$IFDEF USE_DELPHI_TYPES}
  TSize = Windows.TSize;
  PSize = Windows.PSize;
{$ELSE}
  tagSIZE = record
    cx: LONG;
    cy: LONG;
  end;
  {$EXTERNALSYM tagSIZE}
  TSize = tagSIZE;
  PSize = LPSIZE;
{$ENDIF}

  SIZE = TSize;
  {$EXTERNALSYM SIZE}
  SIZEL = TSize;
  {$EXTERNALSYM SIZEL}
  PSIZEL = PSize;
  {$EXTERNALSYM PSIZEL}
  LPSIZEL = PSize;
  {$EXTERNALSYM LPSIZEL}

  LPPOINTS = ^POINTS;
  {$EXTERNALSYM LPPOINTS}
  tagPOINTS = record
    x: SHORT;
    y: SHORT;
  end;
  {$EXTERNALSYM tagPOINTS}
  POINTS = tagPOINTS;
  {$EXTERNALSYM POINTS}
  TPoints = POINTS;
  PPoints = LPPOINTS;

//
//  File System time stamps are represented with the following structure:
//

  {$IFNDEF _FILETIME_}
  {$DEFINE _FILETIME_}
  _FILETIME = record
    dwLowDateTime: DWORD;
    dwHighDateTime: DWORD;
  end;
  {$EXTERNALSYM _FILETIME}
  FILETIME = _FILETIME;
  {$EXTERNALSYM FILETIME}
  PFILETIME = ^FILETIME;
  {$EXTERNALSYM PFILETIME}
  LPFILETIME = PFILETIME;
  {$EXTERNALSYM LPFILETIME}
  TFileTime = FILETIME;
  {$ENDIF}

// mode selections for the device mode function

const
  DM_UPDATE = 1;
  {$EXTERNALSYM DM_UPDATE}
  DM_COPY   = 2;
  {$EXTERNALSYM DM_COPY}
  DM_PROMPT = 4;
  {$EXTERNALSYM DM_PROMPT}
  DM_MODIFY = 8;
  {$EXTERNALSYM DM_MODIFY}

  DM_IN_BUFFER   = DM_MODIFY;
  {$EXTERNALSYM DM_IN_BUFFER}
  DM_IN_PROMPT   = DM_PROMPT;
  {$EXTERNALSYM DM_IN_PROMPT}
  DM_OUT_BUFFER  = DM_COPY;
  {$EXTERNALSYM DM_OUT_BUFFER}
  DM_OUT_DEFAULT = DM_UPDATE;
  {$EXTERNALSYM DM_OUT_DEFAULT}

// device capabilities indices

  DC_FIELDS           = 1;
  {$EXTERNALSYM DC_FIELDS}
  DC_PAPERS           = 2;
  {$EXTERNALSYM DC_PAPERS}
  DC_PAPERSIZE        = 3;
  {$EXTERNALSYM DC_PAPERSIZE}
  DC_MINEXTENT        = 4;
  {$EXTERNALSYM DC_MINEXTENT}
  DC_MAXEXTENT        = 5;
  {$EXTERNALSYM DC_MAXEXTENT}
  DC_BINS             = 6;
  {$EXTERNALSYM DC_BINS}
  DC_DUPLEX           = 7;
  {$EXTERNALSYM DC_DUPLEX}
  DC_SIZE             = 8;
  {$EXTERNALSYM DC_SIZE}
  DC_EXTRA            = 9;
  {$EXTERNALSYM DC_EXTRA}
  DC_VERSION          = 10;
  {$EXTERNALSYM DC_VERSION}
  DC_DRIVER           = 11;
  {$EXTERNALSYM DC_DRIVER}
  DC_BINNAMES         = 12;
  {$EXTERNALSYM DC_BINNAMES}
  DC_ENUMRESOLUTIONS  = 13;
  {$EXTERNALSYM DC_ENUMRESOLUTIONS}
  DC_FILEDEPENDENCIES = 14;
  {$EXTERNALSYM DC_FILEDEPENDENCIES}
  DC_TRUETYPE         = 15;
  {$EXTERNALSYM DC_TRUETYPE}
  DC_PAPERNAMES       = 16;
  {$EXTERNALSYM DC_PAPERNAMES}
  DC_ORIENTATION      = 17;
  {$EXTERNALSYM DC_ORIENTATION}
  DC_COPIES           = 18;
  {$EXTERNALSYM DC_COPIES}

//
// HALF_PTR is half the size of a pointer it intended for use with
// within strcuture which contain a pointer and two small fields.
// UHALF_PTR is the unsigned variation.
//

const
  ADDRESS_TAG_BIT = DWORD($80000000);
  {$EXTERNALSYM ADDRESS_TAG_BIT}

type
  UHALF_PTR = Byte;
  {$EXTERNALSYM UHALF_PTR}
  PUHALF_PTR = ^UHALF_PTR;
  {$EXTERNALSYM PUHALF_PTR}
  HALF_PTR = Shortint;
  {$EXTERNALSYM HALF_PTR}
  PHALF_PTR = ^HALF_PTR;
  {$EXTERNALSYM PHALF_PTR}

  SHANDLE_PTR = Longint;
  {$EXTERNALSYM SHANDLE_PTR}
  HANDLE_PTR = Longint;
  {$EXTERNALSYM HANDLE_PTR}

//
// SIZE_T used for counts or ranges which need to span the range of
// of a pointer.  SSIZE_T is the signed variation.
//

  SIZE_T = ULONG_PTR;
  {$EXTERNALSYM SIZE_T}
  PSIZE_T = ^SIZE_T;
  {$EXTERNALSYM PSIZE_T}
  SSIZE_T = LONG_PTR;
  {$EXTERNALSYM SSIZE_T}
  PSSIZE_T = ^SSIZE_T;
  {$EXTERNALSYM PSSIZE_T}

//
// Add Windows flavor DWORD_PTR types
//

  DWORD_PTR = ULONG_PTR;
  {$EXTERNALSYM DWORD_PTR}
  PDWORD_PTR = ^DWORD_PTR;
  {$EXTERNALSYM PDWORD_PTR}

//
// The following types are guaranteed to be signed and 64 bits wide.
//

  LONG64 = Int64;
  {$EXTERNALSYM LONG64}
  PLONG64 = ^LONG64;
  {$EXTERNALSYM PLONG64}

  PINT64 = ^Int64;
  {$EXTERNALSYM PINT64}

//
// The following types are guaranteed to be unsigned and 64 bits wide.
//

  ULONG64 = Int64;
  {$EXTERNALSYM ULONG64}
  PULONG64 = ^ULONG64;
  {$EXTERNALSYM PULONG64}
  DWORD64 = Int64;
  {$EXTERNALSYM DWORD64}
  PDWORD64 = ^DWORD64;
  {$EXTERNALSYM PDWORD64}
  UINT64 = Int64;
  {$EXTERNALSYM UINT64}
  PUINT64 = ^UINT64;
  {$EXTERNALSYM PUINT64}

const
  MAXUINT_PTR   = not UINT_PTR(0);
  {$EXTERNALSYM MAXUINT_PTR}
  MAXINT_PTR    = INT_PTR((MAXUINT_PTR shr 1));
  {$EXTERNALSYM MAXINT_PTR}
  MININT_PTR    = not MAXINT_PTR;
  {$EXTERNALSYM MININT_PTR}

  MAXULONG_PTR  = not ULONG_PTR(0);
  {$EXTERNALSYM MAXULONG_PTR}
  MAXLONG_PTR   = LONG_PTR(MAXULONG_PTR shr 1);
  {$EXTERNALSYM MAXLONG_PTR}
  MINLONG_PTR   = not MAXLONG_PTR;
  {$EXTERNALSYM MINLONG_PTR}

  MAXUHALF_PTR  = UHALF_PTR( not 0);
  {$EXTERNALSYM MAXUHALF_PTR}
  MAXHALF_PTR   = HALF_PTR(MAXUHALF_PTR shr 1);
  {$EXTERNALSYM MAXHALF_PTR}
  MINHALF_PTR   = not MAXHALF_PTR;
  {$EXTERNALSYM MINHALF_PTR}

// basetsd

type
  INT8 = Shortint;
  {$EXTERNALSYM INT8}
  PINT8 = ^INT8;
  {$EXTERNALSYM PINT8}
  INT16 = Smallint;
  {$EXTERNALSYM INT16}
  PINT16 = ^INT16;
  {$EXTERNALSYM PINT16}
  UINT8 = Byte;
  {$EXTERNALSYM UINT8}
  PUINT8 = ^UINT8;
  {$EXTERNALSYM PUINT8}
  UINT16 = Word;
  {$EXTERNALSYM UINT16}
  PUINT16 = ^UINT16;
  {$EXTERNALSYM PUINT16}

//
// Thread affinity.
//

  KAFFINITY = ULONG_PTR;
  {$EXTERNALSYM KAFFINITY}
  PKAFFINITY = ^KAFFINITY;
  {$EXTERNALSYM PKAFFINITY}

implementation

uses
  JwaWinNT;

function Int32x32To64(a, b: LONG): LONGLONG;
begin
  Result := a * b;
end;

function UInt32x32To64(a, b: DWORD): ULONGLONG;
begin
  Result := a * b;
end;

function Int64ShllMod32(Value: ULONGLONG; ShiftCount: DWORD): ULONGLONG;
asm
        MOV     ECX, ShiftCount
        MOV     EAX, DWORD PTR [Value]
        MOV     EDX, DWORD PTR [Value + 4]
        SHLD    EDX, EAX, CL
        SHL     EAX, CL
end;

function Int64ShraMod32(Value: LONGLONG; ShiftCount: DWORD): LONGLONG;
asm
        MOV     ECX, ShiftCount
        MOV     EAX, DWORD PTR [Value]
        MOV     EDX, DWORD PTR [Value + 4]
        SHRD    EAX, EDX, CL
        SAR     EDX, CL
end;

function Int64ShrlMod32(Value: ULONGLONG; ShiftCount: DWORD): ULONGLONG;
asm
        MOV     ECX, ShiftCount
        MOV     EAX, DWORD PTR [Value]
        MOV     EDX, DWORD PTR [Value + 4]
        SHRD    EAX, EDX, CL
        SHR     EDX, CL
end;

procedure ListEntry32To64(l32: PLIST_ENTRY32; l64: PLIST_ENTRY64);
begin
  l64^.Flink := l32^.Flink;
  l64^.Blink := l32^.Blink;
end;

procedure ListEntry64To32(l64: PLIST_ENTRY64; l32: PLIST_ENTRY32);
begin
  l32^.Flink := ULONG(l64^.Flink);
  l32^.Blink := ULONG(l64^.Blink);
end;

function NT_SUCCESS(Status: NTSTATUS): BOOL;
begin
  Result := Status >= 0;
end;

function NT_INFORMATION(Status: NTSTATUS): BOOL;
begin
  Result := (ULONG(Status) shr 30) = 1;
end;

function NT_WARNING(Status: NTSTATUS): BOOL;
begin
  Result := (ULONG(Status) shr 30) = 2;
end;

function NT_ERROR(Status: NTSTATUS): BOOL;
begin
  Result := (ULONG(Status) shr 30) = 3;
end;

procedure InitializeObjectAttributes(p: POBJECT_ATTRIBUTES; n: PUNICODE_STRING;
  a: ULONG; r: HANDLE; s: PVOID{PSECURITY_DESCRIPTOR});
begin
  p^.Length := sizeof(OBJECT_ATTRIBUTES);
  p^.RootDirectory := r;
  p^.Attributes := a;
  p^.ObjectName := n;
  p^.SecurityDescriptor := s;
  p^.SecurityQualityOfService := nil;
end;

function ARGUMENT_PRESENT(ArgumentPointer: Pointer): BOOL;
begin
  Result := ArgumentPointer <> nil;
end;

function MAKEWORD(a, b: BYTE): WORD;
begin
  Result := (b shl 8) or a;
end;

function MAKELONG(a, b: WORD): DWORD;
begin
  Result := (b shl 16) or a;
end;

function LOWORD(L: DWORD): WORD;
begin
  Result := L and $0000FFFF;
end;

function HIWORD(L: DWORD): WORD;
begin
  Result := L shr 16;
end;

function LOBYTE(W: WORD): BYTE;
begin
  Result := W and $FF;
end;

function HIBYTE(W: WORD): BYTE;
begin
  Result := W shr 8;
end;

function GetModuleHandle(lpModuleName: LPCSTR): HMODULE; stdcall; external kernel32 name 'GetModuleHandleA';
function LoadLibrary(lpLibFileName: LPCSTR): HMODULE; stdcall; external kernel32 name 'LoadLibraryA';
function GetProcAddress(hModule: HMODULE; lpProcName: LPCSTR): FARPROC; stdcall; external kernel32 name 'GetProcAddress';

procedure GetProcedureAddress(var P: Pointer; const ModuleName, ProcName: string);
var
  ModuleHandle: HMODULE;
begin
  if not Assigned(P) then
  begin
    ModuleHandle := GetModuleHandle(PChar(ModuleName));
    if ModuleHandle = 0 then
    begin
      ModuleHandle := LoadLibrary(PChar(ModuleName));
      if ModuleHandle = 0 then raise EJwaLoadLibraryError.Create('Library not found: ' + ModuleName);
    end;
    P := GetProcAddress(ModuleHandle, PChar(ProcName));
    if not Assigned(P) then raise EJwaGetProcAddressError.Create('Function not found: ' + ModuleName + '.' + ProcName);
  end;
end;


end.
