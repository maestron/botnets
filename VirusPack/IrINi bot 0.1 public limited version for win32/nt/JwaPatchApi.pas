{******************************************************************************}
{                                                       	               }
{ Creating and applying patches to filesAPI interface Unit for Object Pascal   }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: patchapi.h, released August 2001. The original Pascal  }
{ code is: PatchApi.pas, released December 2001. The initial developer of the  }
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

unit JwaPatchApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "patchapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
//  The following constants can be combined and used as the OptionFlags
//  parameter in the patch creation apis.
//

const
  PATCH_OPTION_USE_BEST = $00000000; // auto choose best (slower)
  {$EXTERNALSYM PATCH_OPTION_USE_BEST}

  PATCH_OPTION_USE_LZX_BEST  = $00000003; // auto choose best of LZX
  {$EXTERNALSYM PATCH_OPTION_USE_LZX_BEST}
  PATCH_OPTION_USE_LZX_A     = $00000001; // normal
  {$EXTERNALSYM PATCH_OPTION_USE_LZX_A}
  PATCH_OPTION_USE_LZX_B     = $00000002; // better on some x86 binaries
  {$EXTERNALSYM PATCH_OPTION_USE_LZX_B}
  PATCH_OPTION_USE_LZX_LARGE = $00000004; // better support for files >8MB
  {$EXTERNALSYM PATCH_OPTION_USE_LZX_LARGE}

  PATCH_OPTION_NO_BINDFIX        = $00010000; // PE bound imports
  {$EXTERNALSYM PATCH_OPTION_NO_BINDFIX}
  PATCH_OPTION_NO_LOCKFIX        = $00020000; // PE smashed locks
  {$EXTERNALSYM PATCH_OPTION_NO_LOCKFIX}
  PATCH_OPTION_NO_REBASE         = $00040000; // PE rebased image
  {$EXTERNALSYM PATCH_OPTION_NO_REBASE}
  PATCH_OPTION_FAIL_IF_SAME_FILE = $00080000; // don't create if same
  {$EXTERNALSYM PATCH_OPTION_FAIL_IF_SAME_FILE}
  PATCH_OPTION_FAIL_IF_BIGGER    = $00100000; // fail if patch is larger than simply compressing new file (slower)
  {$EXTERNALSYM PATCH_OPTION_FAIL_IF_BIGGER}
  PATCH_OPTION_NO_CHECKSUM       = $00200000; // PE checksum zero
  {$EXTERNALSYM PATCH_OPTION_NO_CHECKSUM}
  PATCH_OPTION_NO_RESTIMEFIX     = $00400000; // PE resource timestamps
  {$EXTERNALSYM PATCH_OPTION_NO_RESTIMEFIX}
  PATCH_OPTION_NO_TIMESTAMP      = $00800000; // don't store new file timestamp in patch
  {$EXTERNALSYM PATCH_OPTION_NO_TIMESTAMP}
  PATCH_OPTION_SIGNATURE_MD5     = $01000000; // use MD5 instead of CRC32
  {$EXTERNALSYM PATCH_OPTION_SIGNATURE_MD5}
  PATCH_OPTION_RESERVED1         = DWORD($80000000); // (used internally)
  {$EXTERNALSYM PATCH_OPTION_RESERVED1}

  PATCH_OPTION_VALID_FLAGS = DWORD($80FF0007);
  {$EXTERNALSYM PATCH_OPTION_VALID_FLAGS}

  PATCH_SYMBOL_NO_IMAGEHLP     = $00000001; // don't use imagehlp.dll
  {$EXTERNALSYM PATCH_SYMBOL_NO_IMAGEHLP}
  PATCH_SYMBOL_NO_FAILURES     = $00000002; // don't fail patch due to imagehlp failures
  {$EXTERNALSYM PATCH_SYMBOL_NO_FAILURES}
  PATCH_SYMBOL_UNDECORATED_TOO = $00000004; // after matching decorated symbols, try to match remaining by undecorated names
  {$EXTERNALSYM PATCH_SYMBOL_UNDECORATED_TOO}
  PATCH_SYMBOL_RESERVED1       = DWORD($80000000); // (used internally)
  {$EXTERNALSYM PATCH_SYMBOL_RESERVED1}

//
//  The following constants can be combined and used as the ApplyOptionFlags
//  parameter in the patch apply and test apis.
//

  APPLY_OPTION_FAIL_IF_EXACT = $00000001; // don't copy new file
  {$EXTERNALSYM APPLY_OPTION_FAIL_IF_EXACT}
  APPLY_OPTION_FAIL_IF_CLOSE = $00000002; // differ by rebase, bind
  {$EXTERNALSYM APPLY_OPTION_FAIL_IF_CLOSE}
  APPLY_OPTION_TEST_ONLY     = $00000004; // don't create new file
  {$EXTERNALSYM APPLY_OPTION_TEST_ONLY}
  APPLY_OPTION_VALID_FLAGS   = $00000007;
  {$EXTERNALSYM APPLY_OPTION_VALID_FLAGS}

//
//  In addition to standard Win32 error codes, the following error codes may
//  be returned via GetLastError() when one of the patch APIs fails.
//

  ERROR_PATCH_ENCODE_FAILURE         = DWORD($C00E3101); // create
  {$EXTERNALSYM ERROR_PATCH_ENCODE_FAILURE}
  ERROR_PATCH_INVALID_OPTIONS        = DWORD($C00E3102); // create
  {$EXTERNALSYM ERROR_PATCH_INVALID_OPTIONS}
  ERROR_PATCH_SAME_FILE              = DWORD($C00E3103); // create
  {$EXTERNALSYM ERROR_PATCH_SAME_FILE}
  ERROR_PATCH_RETAIN_RANGES_DIFFER   = DWORD($C00E3104); // create
  {$EXTERNALSYM ERROR_PATCH_RETAIN_RANGES_DIFFER}
  ERROR_PATCH_BIGGER_THAN_COMPRESSED = DWORD($C00E3105); // create
  {$EXTERNALSYM ERROR_PATCH_BIGGER_THAN_COMPRESSED}
  ERROR_PATCH_IMAGEHLP_FAILURE       = DWORD($C00E3106); // create
  {$EXTERNALSYM ERROR_PATCH_IMAGEHLP_FAILURE}

  ERROR_PATCH_DECODE_FAILURE = DWORD($C00E4101); // apply
  {$EXTERNALSYM ERROR_PATCH_DECODE_FAILURE}
  ERROR_PATCH_CORRUPT        = DWORD($C00E4102); // apply
  {$EXTERNALSYM ERROR_PATCH_CORRUPT}
  ERROR_PATCH_NEWER_FORMAT   = DWORD($C00E4103); // apply
  {$EXTERNALSYM ERROR_PATCH_NEWER_FORMAT}
  ERROR_PATCH_WRONG_FILE     = DWORD($C00E4104); // apply
  {$EXTERNALSYM ERROR_PATCH_WRONG_FILE}
  ERROR_PATCH_NOT_NECESSARY  = DWORD($C00E4105); // apply
  {$EXTERNALSYM ERROR_PATCH_NOT_NECESSARY}
  ERROR_PATCH_NOT_AVAILABLE  = DWORD($C00E4106); // apply
  {$EXTERNALSYM ERROR_PATCH_NOT_AVAILABLE}

type
  PATCH_PROGRESS_CALLBACK = function (CallbackContext: PVOID; CurrentPosition, MaximumPosition: ULONG): BOOL; stdcall;
  {$EXTERNALSYM PATCH_PROGRESS_CALLBACK}
  TPatchProgressCallback = PATCH_PROGRESS_CALLBACK;


  PPATCH_PROGRESS_CALLBACK = ^PATCH_PROGRESS_CALLBACK;
  {$EXTERNALSYM PPATCH_PROGRESS_CALLBACK}
  PPatchProgressCallback = PPATCH_PROGRESS_CALLBACK;

  PATCH_SYMLOAD_CALLBACK = function (WhichFile: ULONG; SymbolFileName: LPCSTR; SymType, SymbolFileCheckSum,
    SymbolFileTimeDate, ImageFileCheckSum, ImageFileTimeDate: ULONG; CallbackContext: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PATCH_SYMLOAD_CALLBACK}
  TPatchSymLoadCallback = PATCH_SYMLOAD_CALLBACK;

  PPATCH_SYMLOAD_CALLBACK = ^PATCH_SYMLOAD_CALLBACK;
  {$EXTERNALSYM PPATCH_SYMLOAD_CALLBACK}
  PPatchSymLoadCallback = PPATCH_SYMLOAD_CALLBACK;

  PPATCH_IGNORE_RANGE = ^PATCH_IGNORE_RANGE;
  {$EXTERNALSYM PPATCH_IGNORE_RANGE}
  _PATCH_IGNORE_RANGE = record
    OffsetInOldFile: ULONG;
    LengthInBytes: ULONG;
  end;
  {$EXTERNALSYM _PATCH_IGNORE_RANGE}
  PATCH_IGNORE_RANGE = _PATCH_IGNORE_RANGE;
  {$EXTERNALSYM PATCH_IGNORE_RANGE}
  TPatchIgnoreRange = PATCH_IGNORE_RANGE;
  PPatchIgnoreRange = PPATCH_IGNORE_RANGE;

  PPATCH_RETAIN_RANGE = ^PATCH_RETAIN_RANGE;
  {$EXTERNALSYM PPATCH_RETAIN_RANGE}
  _PATCH_RETAIN_RANGE = record
    OffsetInOldFile: ULONG;
    LengthInBytes: ULONG;
    OffsetInNewFile: ULONG;
  end;
  {$EXTERNALSYM _PATCH_RETAIN_RANGE}
  PATCH_RETAIN_RANGE = _PATCH_RETAIN_RANGE;
  {$EXTERNALSYM PATCH_RETAIN_RANGE}
  TPatchRetainRange = PATCH_RETAIN_RANGE;
  PPatchRetainRange = PPATCH_RETAIN_RANGE;

  PPATCH_OLD_FILE_INFO_A = ^PATCH_OLD_FILE_INFO_A;
  {$EXTERNALSYM PPATCH_OLD_FILE_INFO_A}
  _PATCH_OLD_FILE_INFO_A = record
    SizeOfThisStruct: ULONG;
    OldFileName: LPCSTR;
    IgnoreRangeCount: ULONG; // maximum 255
    IgnoreRangeArray: PPATCH_IGNORE_RANGE;
    RetainRangeCount: ULONG; // maximum 255
    RetainRangeArray: PPATCH_RETAIN_RANGE;
  end;
  {$EXTERNALSYM _PATCH_OLD_FILE_INFO_A}
  PATCH_OLD_FILE_INFO_A = _PATCH_OLD_FILE_INFO_A;
  {$EXTERNALSYM PATCH_OLD_FILE_INFO_A}
  TPatchOldFileInfoA = PATCH_OLD_FILE_INFO_A;
  PPatchOldFileInfoA = PPATCH_OLD_FILE_INFO_A;

  PPATCH_OLD_FILE_INFO_W = ^PATCH_OLD_FILE_INFO_W;
  {$EXTERNALSYM PPATCH_OLD_FILE_INFO_W}
  _PATCH_OLD_FILE_INFO_W = record
    SizeOfThisStruct: ULONG;
    OldFileName: LPCWSTR;
    IgnoreRangeCount: ULONG; // maximum 255
    IgnoreRangeArray: PPATCH_IGNORE_RANGE;
    RetainRangeCount: ULONG; // maximum 255
    RetainRangeArray: PPATCH_RETAIN_RANGE;
  end;
  {$EXTERNALSYM _PATCH_OLD_FILE_INFO_W}
  PATCH_OLD_FILE_INFO_W = _PATCH_OLD_FILE_INFO_W;
  {$EXTERNALSYM PATCH_OLD_FILE_INFO_W}
  TPatchOldFileInfoW = PATCH_OLD_FILE_INFO_W;
  PPatchOldFileInfoW = PPATCH_OLD_FILE_INFO_W;

  PPATCH_OLD_FILE_INFO_H = ^PATCH_OLD_FILE_INFO_H;
  {$EXTERNALSYM PPATCH_OLD_FILE_INFO_H}
  _PATCH_OLD_FILE_INFO_H = record
    SizeOfThisStruct: ULONG;
    OldFileHandle: HANDLE;
    IgnoreRangeCount: ULONG; // maximum 255
    IgnoreRangeArray: PPATCH_IGNORE_RANGE;
    RetainRangeCount: ULONG; // maximum 255
    RetainRangeArray: PPATCH_RETAIN_RANGE;
  end;
  {$EXTERNALSYM _PATCH_OLD_FILE_INFO_H}
  PATCH_OLD_FILE_INFO_H = _PATCH_OLD_FILE_INFO_H;
  {$EXTERNALSYM PATCH_OLD_FILE_INFO_H}
  TPatchOldFileInfoH = PATCH_OLD_FILE_INFO_H;
  PPatchOldFileInfoH = PPATCH_OLD_FILE_INFO_H;

  PPATCH_OLD_FILE_INFO = ^PATCH_OLD_FILE_INFO;
  {$EXTERNALSYM PPATCH_OLD_FILE_INFO}
  _PATCH_OLD_FILE_INFO = record
    SizeOfThisStruct: ULONG;
    Union: record
    case Integer of
      0: (OldFileNameA: LPCSTR);
      1: (OldFileNameW: LPCWSTR);
      2: (OldFileHandle: HANDLE);
    end;
    IgnoreRangeCount: ULONG; // maximum 255
    IgnoreRangeArray: PPATCH_IGNORE_RANGE;
    RetainRangeCount: ULONG; // maximum 255
    RetainRangeArray: PPATCH_RETAIN_RANGE;
  end;
  {$EXTERNALSYM _PATCH_OLD_FILE_INFO}
  PATCH_OLD_FILE_INFO = _PATCH_OLD_FILE_INFO;
  {$EXTERNALSYM PATCH_OLD_FILE_INFO}
  TPatchOldFileInfo = PATCH_OLD_FILE_INFO;
  PPatchOldFileInfo = PPATCH_OLD_FILE_INFO;

  PPATCH_OPTION_DATA = ^PATCH_OPTION_DATA;
  {$EXTERNALSYM PPATCH_OPTION_DATA}
  _PATCH_OPTION_DATA = record
    SizeOfThisStruct: ULONG;
    SymbolOptionFlags: ULONG; // PATCH_SYMBOL_xxx flags
    NewFileSymbolPath: LPCSTR; // always ANSI, never Unicode
    OldFileSymbolPathArray: ^LPCSTR; // array[ OldFileCount ]
    ExtendedOptionFlags: ULONG;
    SymLoadCallback: PATCH_SYMLOAD_CALLBACK;
    SymLoadContext: PVOID;
  end;
  {$EXTERNALSYM _PATCH_OPTION_DATA}
  PATCH_OPTION_DATA = _PATCH_OPTION_DATA;
  {$EXTERNALSYM PATCH_OPTION_DATA}
  TPatchOptionData = PATCH_OPTION_DATA;
  PPatchOptionData = PPATCH_OPTION_DATA;

//
//  Note that PATCH_OPTION_DATA contains LPCSTR paths, and no LPCWSTR (Unicode)
//  path argument is available, even when used with one of the Unicode APIs
//  such as CreatePatchFileW.  This is because the underlying system services
//  for symbol file handling (IMAGEHLP.DLL) only support ANSI file/path names.
//

//
//  A note about PATCH_RETAIN_RANGE specifiers with multiple old files:
//
//  Each old version file must have the same RetainRangeCount, and the same
//  retain range LengthInBytes and OffsetInNewFile values in the same order.
//  Only the OffsetInOldFile values can differ between old files for retain
//  ranges.
//

//
//  The following prototypes are interface for creating patches from files.
//

function CreatePatchFileA(OldFileName: LPCSTR; NewFileName: LPCSTR; PatchFileName: LPCSTR; OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileA}

function CreatePatchFileW(OldFileName: LPCWSTR; NewFileName: LPCWSTR; PatchFileName: LPCWSTR; OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileW}

function CreatePatchFileByHandles(OldFileHandle: HANDLE; NewFileHandle: HANDLE; PatchFileHandle: HANDLE; OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileByHandles}

function CreatePatchFileExA(OldFileCount: ULONG; OldFileInfoArray: PPATCH_OLD_FILE_INFO_A; NewFileName: LPCSTR; PatchFileName: LPCSTR;
  OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileExA}

function CreatePatchFileExW(OldFileCount: ULONG; OldFileInfoArray: PPATCH_OLD_FILE_INFO_W; NewFileName: LPCWSTR; PatchFileName: LPCWSTR;
  OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileExW}

function CreatePatchFileByHandlesEx(OldFileCount: ULONG; OldFileInfoArray: PPATCH_OLD_FILE_INFO_H; NewFileHandle: HANDLE;
  PatchFileHandle: HANDLE; OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileByHandlesEx}

function ExtractPatchHeaderToFileA(PatchFileName: LPCSTR; PatchHeaderFileName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM ExtractPatchHeaderToFileA}

function ExtractPatchHeaderToFileW(PatchFileName: LPCWSTR; PatchHeaderFileName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM ExtractPatchHeaderToFileW}

function ExtractPatchHeaderToFileByHandles(PatchFileHandle: HANDLE; PatchHeaderFileHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM ExtractPatchHeaderToFileByHandles}

//
//  The following prototypes are interface for creating new file from old file
//  and patch file.  Note that it is possible for the TestApply API to succeed
//  but the actual Apply to fail since the TestApply only verifies that the
//  old file has the correct CRC without actually applying the patch.  The
//  TestApply API only requires the patch header portion of the patch file,
//  but its CRC must be fixed up.
//

function TestApplyPatchToFileA(PatchFileName: LPCSTR; OldFileName: LPCSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM TestApplyPatchToFileA}

function TestApplyPatchToFileW(PatchFileName: LPCWSTR; OldFileName: LPCWSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM TestApplyPatchToFileW}

function TestApplyPatchToFileByHandles(PatchFileHandle: HANDLE; OldFileHandle: HANDLE; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM TestApplyPatchToFileByHandles}

function ApplyPatchToFileA(PatchFileName: LPCSTR; OldFileName: LPCSTR; NewFileName: LPCSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileA}

function ApplyPatchToFileW(PatchFileName: LPCWSTR; OldFileName: LPCWSTR; NewFileName: LPCWSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileW}

function ApplyPatchToFileByHandles(PatchFileHandle: HANDLE; OldFileHandle: HANDLE; NewFileHandle: HANDLE; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileByHandles}

function ApplyPatchToFileExA(PatchFileName: LPCSTR; OldFileName: LPCSTR; NewFileName: LPCSTR; ApplyOptionFlags: ULONG;
  ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileExA}

function ApplyPatchToFileExW(PatchFileName: LPCWSTR; OldFileName: LPCWSTR; NewFileName: LPCWSTR; ApplyOptionFlags: ULONG;
  ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileExW}

function ApplyPatchToFileByHandlesEx(PatchFileHandle: HANDLE; OldFileHandle: HANDLE; NewFileHandle: HANDLE;
  ApplyOptionFlags: ULONG; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileByHandlesEx}

//
//  The following prototypes provide a unique patch "signature" for a given
//  file.  Consider the case where you have a new foo.dll and the machines
//  to be updated with the new foo.dll may have one of three different old
//  foo.dll files.  Rather than creating a single large patch file that can
//  update any of the three older foo.dll files, three separate smaller patch
//  files can be created and "named" according to the patch signature of the
//  old file.  Then the patch applyer application can determine at runtime
//  which of the three foo.dll patch files is necessary given the specific
//  foo.dll to be updated.  If patch files are being downloaded over a slow
//  network connection (Internet over a modem), this signature scheme provides
//  a mechanism for choosing the correct single patch file to download at
//  application time thus decreasing total bytes necessary to download.
//

function GetFilePatchSignatureA(FileName: LPCSTR; OptionFlags: ULONG; OptionData: PVOID; IgnoreRangeCount: ULONG; IgnoreRangeArray: PPATCH_IGNORE_RANGE;
  RetainRangeCount: ULONG; RetainRangeArray: PPATCH_RETAIN_RANGE; SignatureBufferSize: ULONG; SignatureBuffer: PVOID): BOOL; stdcall;
{$EXTERNALSYM GetFilePatchSignatureA}

function GetFilePatchSignatureW(FileName: LPCWSTR; OptionFlags: ULONG; OptionData: PVOID; IgnoreRangeCount: ULONG; IgnoreRangeArray: PPATCH_IGNORE_RANGE;
  RetainRangeCount: ULONG; RetainRangeArray: PPATCH_RETAIN_RANGE; SignatureBufferSizeInBytes: ULONG; SignatureBuffer: PVOID): BOOL; stdcall;
{$EXTERNALSYM GetFilePatchSignatureW}

function GetFilePatchSignatureByHandle(FileHandle: HANDLE; OptionFlags: ULONG; OptionData: PVOID; IgnoreRangeCount: ULONG; IgnoreRangeArray: PPATCH_IGNORE_RANGE;
  RetainRangeCount: ULONG; RetainRangeArray: PPATCH_RETAIN_RANGE; SignatureBufferSize: ULONG; SignatureBuffer: PVOID): BOOL; stdcall;
{$EXTERNALSYM GetFilePatchSignatureByHandle}

//
//  Depending on whether UNICODE is defined, map the generic API names to the
//  appropriate Unicode or Ansi APIs.
//

{$IFDEF UNICODE}

function CreatePatchFile(OldFileName: LPCWSTR; NewFileName: LPCWSTR; PatchFileName: LPCWSTR; OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFile}
function CreatePatchFileEx(OldFileCount: ULONG; OldFileInfoArray: PPATCH_OLD_FILE_INFO_W; NewFileName: LPCWSTR; PatchFileName: LPCWSTR;
  OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileEx}
function ExtractPatchHeaderToFile(PatchFileName: LPCWSTR; PatchHeaderFileName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM ExtractPatchHeaderToFile}
function TestApplyPatchToFile(PatchFileName: LPCWSTR; OldFileName: LPCWSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM TestApplyPatchToFile}
function ApplyPatchToFile(PatchFileName: LPCWSTR; OldFileName: LPCWSTR; NewFileName: LPCWSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFile}
function ApplyPatchToFileEx(PatchFileName: LPCWSTR; OldFileName: LPCWSTR; NewFileName: LPCWSTR; ApplyOptionFlags: ULONG; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileEx}
function GetFilePatchSignature(FileName: LPCWSTR; OptionFlags: ULONG; OptionData: PVOID; IgnoreRangeCount: ULONG; IgnoreRangeArray: PPATCH_IGNORE_RANGE;
  RetainRangeCount: ULONG; RetainRangeArray: PPATCH_RETAIN_RANGE; SignatureBufferSizeInBytes: ULONG; SignatureBuffer: PVOID): BOOL; stdcall;
{$EXTERNALSYM GetFilePatchSignature}

{$ELSE}

function CreatePatchFile(OldFileName: LPCSTR; NewFileName: LPCSTR; PatchFileName: LPCSTR; OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFile}
function CreatePatchFileEx(OldFileCount: ULONG; OldFileInfoArray: PPATCH_OLD_FILE_INFO_A; NewFileName: LPCSTR; PatchFileName: LPCSTR;
  OptionFlags: ULONG; OptionData: PPATCH_OPTION_DATA; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM CreatePatchFileEx}
function ExtractPatchHeaderToFile(PatchFileName: LPCSTR; PatchHeaderFileName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM ExtractPatchHeaderToFile}
function TestApplyPatchToFile(PatchFileName: LPCSTR; OldFileName: LPCSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM TestApplyPatchToFile}
function ApplyPatchToFile(PatchFileName: LPCSTR; OldFileName: LPCSTR; NewFileName: LPCSTR; ApplyOptionFlags: ULONG): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFile}
function ApplyPatchToFileEx(PatchFileName: LPCSTR; OldFileName: LPCSTR; NewFileName: LPCSTR; ApplyOptionFlags: ULONG; ProgressCallback: PATCH_PROGRESS_CALLBACK; CallbackContext: PVOID): BOOL; stdcall;
{$EXTERNALSYM ApplyPatchToFileEx}
function GetFilePatchSignature(FileName: LPCSTR; OptionFlags: ULONG; OptionData: PVOID; IgnoreRangeCount: ULONG; IgnoreRangeArray: PPATCH_IGNORE_RANGE;
  RetainRangeCount: ULONG; RetainRangeArray: PPATCH_RETAIN_RANGE; SignatureBufferSize: ULONG; SignatureBuffer: PVOID): BOOL; stdcall;
{$EXTERNALSYM GetFilePatchSignature}

{$ENDIF}

implementation

const
  patchapi = 'patchapi.dll'; // todo verify

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileA: Pointer;

function CreatePatchFileA;
begin
  GetProcedureAddress(_CreatePatchFileA, patchapi, 'CreatePatchFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileA]
  end;
end;
{$ELSE}
function CreatePatchFileA; external patchapi name 'CreatePatchFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileW: Pointer;

function CreatePatchFileW;
begin
  GetProcedureAddress(_CreatePatchFileW, patchapi, 'CreatePatchFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileW]
  end;
end;
{$ELSE}
function CreatePatchFileW; external patchapi name 'CreatePatchFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileByHandles: Pointer;

function CreatePatchFileByHandles;
begin
  GetProcedureAddress(_CreatePatchFileByHandles, patchapi, 'CreatePatchFileByHandles');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileByHandles]
  end;
end;
{$ELSE}
function CreatePatchFileByHandles; external patchapi name 'CreatePatchFileByHandles';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileExA: Pointer;

function CreatePatchFileExA;
begin
  GetProcedureAddress(_CreatePatchFileExA, patchapi, 'CreatePatchFileExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileExA]
  end;
end;
{$ELSE}
function CreatePatchFileExA; external patchapi name 'CreatePatchFileExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileExW: Pointer;

function CreatePatchFileExW;
begin
  GetProcedureAddress(_CreatePatchFileExW, patchapi, 'CreatePatchFileExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileExW]
  end;
end;
{$ELSE}
function CreatePatchFileExW; external patchapi name 'CreatePatchFileExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileByHandlesEx: Pointer;

function CreatePatchFileByHandlesEx;
begin
  GetProcedureAddress(_CreatePatchFileByHandlesEx, patchapi, 'CreatePatchFileByHandlesEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileByHandlesEx]
  end;
end;
{$ELSE}
function CreatePatchFileByHandlesEx; external patchapi name 'CreatePatchFileByHandlesEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExtractPatchHeaderToFileA: Pointer;

function ExtractPatchHeaderToFileA;
begin
  GetProcedureAddress(_ExtractPatchHeaderToFileA, patchapi, 'ExtractPatchHeaderToFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExtractPatchHeaderToFileA]
  end;
end;
{$ELSE}
function ExtractPatchHeaderToFileA; external patchapi name 'ExtractPatchHeaderToFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExtractPatchHeaderToFileW: Pointer;

function ExtractPatchHeaderToFileW;
begin
  GetProcedureAddress(_ExtractPatchHeaderToFileW, patchapi, 'ExtractPatchHeaderToFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExtractPatchHeaderToFileW]
  end;
end;
{$ELSE}
function ExtractPatchHeaderToFileW; external patchapi name 'ExtractPatchHeaderToFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExtrPatchHdrToFileByHandles: Pointer;

function ExtractPatchHeaderToFileByHandles;
begin
  GetProcedureAddress(_ExtrPatchHdrToFileByHandles, patchapi, 'ExtractPatchHeaderToFileByHandles');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExtrPatchHdrToFileByHandles]
  end;
end;
{$ELSE}
function ExtractPatchHeaderToFileByHandles; external patchapi name 'ExtractPatchHeaderToFileByHandles';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TestApplyPatchToFileA: Pointer;

function TestApplyPatchToFileA;
begin
  GetProcedureAddress(_TestApplyPatchToFileA, patchapi, 'TestApplyPatchToFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TestApplyPatchToFileA]
  end;
end;
{$ELSE}
function TestApplyPatchToFileA; external patchapi name 'TestApplyPatchToFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TestApplyPatchToFileW: Pointer;

function TestApplyPatchToFileW;
begin
  GetProcedureAddress(_TestApplyPatchToFileW, patchapi, 'TestApplyPatchToFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TestApplyPatchToFileW]
  end;
end;
{$ELSE}
function TestApplyPatchToFileW; external patchapi name 'TestApplyPatchToFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TestApplyPatchToFileByHandles: Pointer;

function TestApplyPatchToFileByHandles;
begin
  GetProcedureAddress(_TestApplyPatchToFileByHandles, patchapi, 'TestApplyPatchToFileByHandles');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TestApplyPatchToFileByHandles]
  end;
end;
{$ELSE}
function TestApplyPatchToFileByHandles; external patchapi name 'TestApplyPatchToFileByHandles';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileA: Pointer;

function ApplyPatchToFileA;
begin
  GetProcedureAddress(_ApplyPatchToFileA, patchapi, 'ApplyPatchToFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileA]
  end;
end;
{$ELSE}
function ApplyPatchToFileA; external patchapi name 'ApplyPatchToFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileW: Pointer;

function ApplyPatchToFileW;
begin
  GetProcedureAddress(_ApplyPatchToFileW, patchapi, 'ApplyPatchToFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileW]
  end;
end;
{$ELSE}
function ApplyPatchToFileW; external patchapi name 'ApplyPatchToFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileByHandles: Pointer;

function ApplyPatchToFileByHandles;
begin
  GetProcedureAddress(_ApplyPatchToFileByHandles, patchapi, 'ApplyPatchToFileByHandles');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileByHandles]
  end;
end;
{$ELSE}
function ApplyPatchToFileByHandles; external patchapi name 'ApplyPatchToFileByHandles';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileExA: Pointer;

function ApplyPatchToFileExA;
begin
  GetProcedureAddress(_ApplyPatchToFileExA, patchapi, 'ApplyPatchToFileExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileExA]
  end;
end;
{$ELSE}
function ApplyPatchToFileExA; external patchapi name 'ApplyPatchToFileExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileExW: Pointer;

function ApplyPatchToFileExW;
begin
  GetProcedureAddress(_ApplyPatchToFileExW, patchapi, 'ApplyPatchToFileExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileExW]
  end;
end;
{$ELSE}
function ApplyPatchToFileExW; external patchapi name 'ApplyPatchToFileExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileByHandlesEx: Pointer;

function ApplyPatchToFileByHandlesEx;
begin
  GetProcedureAddress(_ApplyPatchToFileByHandlesEx, patchapi, 'ApplyPatchToFileByHandlesEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileByHandlesEx]
  end;
end;
{$ELSE}
function ApplyPatchToFileByHandlesEx; external patchapi name 'ApplyPatchToFileByHandlesEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFilePatchSignatureA: Pointer;

function GetFilePatchSignatureA;
begin
  GetProcedureAddress(_GetFilePatchSignatureA, patchapi, 'GetFilePatchSignatureA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFilePatchSignatureA]
  end;
end;
{$ELSE}
function GetFilePatchSignatureA; external patchapi name 'GetFilePatchSignatureA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFilePatchSignatureW: Pointer;

function GetFilePatchSignatureW;
begin
  GetProcedureAddress(_GetFilePatchSignatureW, patchapi, 'GetFilePatchSignatureW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFilePatchSignatureW]
  end;
end;
{$ELSE}
function GetFilePatchSignatureW; external patchapi name 'GetFilePatchSignatureW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFilePatchSignatureByHandle: Pointer;

function GetFilePatchSignatureByHandle;
begin
  GetProcedureAddress(_GetFilePatchSignatureByHandle, patchapi, 'GetFilePatchSignatureByHandle');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFilePatchSignatureByHandle]
  end;
end;
{$ELSE}
function GetFilePatchSignatureByHandle; external patchapi name 'GetFilePatchSignatureByHandle';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}


{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFile: Pointer;

function CreatePatchFile;
begin
  GetProcedureAddress(_CreatePatchFile, patchapi, 'CreatePatchFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFile]
  end;
end;
{$ELSE}
function CreatePatchFile; external patchapi name 'CreatePatchFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileEx: Pointer;

function CreatePatchFileEx;
begin
  GetProcedureAddress(_CreatePatchFileEx, patchapi, 'CreatePatchFileExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileEx]
  end;
end;
{$ELSE}
function CreatePatchFileEx; external patchapi name 'CreatePatchFileExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExtractPatchHeaderToFile: Pointer;

function ExtractPatchHeaderToFile;
begin
  GetProcedureAddress(_ExtractPatchHeaderToFile, patchapi, 'ExtractPatchHeaderToFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExtractPatchHeaderToFile]
  end;
end;
{$ELSE}
function ExtractPatchHeaderToFile; external patchapi name 'ExtractPatchHeaderToFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TestApplyPatchToFile: Pointer;

function TestApplyPatchToFile;
begin
  GetProcedureAddress(_TestApplyPatchToFile, patchapi, 'TestApplyPatchToFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TestApplyPatchToFile]
  end;
end;
{$ELSE}
function TestApplyPatchToFile; external patchapi name 'TestApplyPatchToFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFile: Pointer;

function ApplyPatchToFile;
begin
  GetProcedureAddress(_ApplyPatchToFile, patchapi, 'ApplyPatchToFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFile]
  end;
end;
{$ELSE}
function ApplyPatchToFile; external patchapi name 'ApplyPatchToFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileEx: Pointer;

function ApplyPatchToFileEx;
begin
  GetProcedureAddress(_ApplyPatchToFileEx, patchapi, 'ApplyPatchToFileExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileEx]
  end;
end;
{$ELSE}
function ApplyPatchToFileEx; external patchapi name 'ApplyPatchToFileExW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFilePatchSignature: Pointer;

function GetFilePatchSignature;
begin
  GetProcedureAddress(_GetFilePatchSignature, patchapi, 'GetFilePatchSignatureW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFilePatchSignature]
  end;
end;
{$ELSE}
function GetFilePatchSignature; external patchapi name 'GetFilePatchSignatureW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}


{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFile: Pointer;

function CreatePatchFile;
begin
  GetProcedureAddress(_CreatePatchFile, patchapi, 'CreatePatchFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFile]
  end;
end;
{$ELSE}
function CreatePatchFile; external patchapi name 'CreatePatchFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CreatePatchFileEx: Pointer;

function CreatePatchFileEx;
begin
  GetProcedureAddress(_CreatePatchFileEx, patchapi, 'CreatePatchFileExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CreatePatchFileEx]
  end;
end;
{$ELSE}
function CreatePatchFileEx; external patchapi name 'CreatePatchFileExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ExtractPatchHeaderToFile: Pointer;

function ExtractPatchHeaderToFile;
begin
  GetProcedureAddress(_ExtractPatchHeaderToFile, patchapi, 'ExtractPatchHeaderToFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ExtractPatchHeaderToFile]
  end;
end;
{$ELSE}
function ExtractPatchHeaderToFile; external patchapi name 'ExtractPatchHeaderToFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TestApplyPatchToFile: Pointer;

function TestApplyPatchToFile;
begin
  GetProcedureAddress(_TestApplyPatchToFile, patchapi, 'TestApplyPatchToFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TestApplyPatchToFile]
  end;
end;
{$ELSE}
function TestApplyPatchToFile; external patchapi name 'TestApplyPatchToFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFile: Pointer;

function ApplyPatchToFile;
begin
  GetProcedureAddress(_ApplyPatchToFile, patchapi, 'ApplyPatchToFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFile]
  end;
end;
{$ELSE}
function ApplyPatchToFile; external patchapi name 'ApplyPatchToFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ApplyPatchToFileEx: Pointer;

function ApplyPatchToFileEx;
begin
  GetProcedureAddress(_ApplyPatchToFileEx, patchapi, 'ApplyPatchToFileExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ApplyPatchToFileEx]
  end;
end;
{$ELSE}
function ApplyPatchToFileEx; external patchapi name 'ApplyPatchToFileExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFilePatchSignature: Pointer;

function GetFilePatchSignature;
begin
  GetProcedureAddress(_GetFilePatchSignature, patchapi, 'GetFilePatchSignatureA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFilePatchSignature]
  end;
end;
{$ELSE}
function GetFilePatchSignature; external patchapi name 'GetFilePatchSignatureA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}


end.
