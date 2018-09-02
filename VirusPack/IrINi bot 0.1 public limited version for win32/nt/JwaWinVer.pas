{******************************************************************************}
{                                                       	               }
{ Windows Version API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winver.h, released June 2000. The original Pascal      }
{ code is: WinVer.pas, released December 2000. The initial developer of the    }
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

unit JwaWinVer;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "WinVer.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinUser, JwaWinType; 

const

//  RT_VERSION = MAKEINTRESOURCE(16);

// ----- Symbols -----

  VS_FILE_INFO    = RT_VERSION;
  {$EXTERNALSYM VS_FILE_INFO}
  VS_VERSION_INFO = 1;
  {$EXTERNALSYM VS_VERSION_INFO}
  VS_USER_DEFINED = 100;
  {$EXTERNALSYM VS_USER_DEFINED}

// ----- VS_VERSION.dwFileFlags -----

  VS_FFI_SIGNATURE     = $FEEF04BD;
  {$EXTERNALSYM VS_FFI_SIGNATURE}
  VS_FFI_STRUCVERSION  = $00010000;
  {$EXTERNALSYM VS_FFI_STRUCVERSION}
  VS_FFI_FILEFLAGSMASK = $0000003F;
  {$EXTERNALSYM VS_FFI_FILEFLAGSMASK}

// ----- VS_VERSION.dwFileFlags -----

  VS_FF_DEBUG        = $00000001;
  {$EXTERNALSYM VS_FF_DEBUG}
  VS_FF_PRERELEASE   = $00000002;
  {$EXTERNALSYM VS_FF_PRERELEASE}
  VS_FF_PATCHED      = $00000004;
  {$EXTERNALSYM VS_FF_PATCHED}
  VS_FF_PRIVATEBUILD = $00000008;
  {$EXTERNALSYM VS_FF_PRIVATEBUILD}
  VS_FF_INFOINFERRED = $00000010;
  {$EXTERNALSYM VS_FF_INFOINFERRED}
  VS_FF_SPECIALBUILD = $00000020;
  {$EXTERNALSYM VS_FF_SPECIALBUILD}

// ----- VS_VERSION.dwFileOS -----

  VOS_UNKNOWN = $00000000;
  {$EXTERNALSYM VOS_UNKNOWN}
  VOS_DOS     = $00010000;
  {$EXTERNALSYM VOS_DOS}
  VOS_OS216   = $00020000;
  {$EXTERNALSYM VOS_OS216}
  VOS_OS232   = $00030000;
  {$EXTERNALSYM VOS_OS232}
  VOS_NT      = $00040000;
  {$EXTERNALSYM VOS_NT}
  VOS_WINCE   = $00050000;
  {$EXTERNALSYM VOS_WINCE}

  VOS__BASE      = $00000000;
  {$EXTERNALSYM VOS__BASE}
  VOS__WINDOWS16 = $00000001;
  {$EXTERNALSYM VOS__WINDOWS16}
  VOS__PM16      = $00000002;
  {$EXTERNALSYM VOS__PM16}
  VOS__PM32      = $00000003;
  {$EXTERNALSYM VOS__PM32}
  VOS__WINDOWS32 = $00000004;
  {$EXTERNALSYM VOS__WINDOWS32}

  VOS_DOS_WINDOWS16 = $00010001;
  {$EXTERNALSYM VOS_DOS_WINDOWS16}
  VOS_DOS_WINDOWS32 = $00010004;
  {$EXTERNALSYM VOS_DOS_WINDOWS32}
  VOS_OS216_PM16    = $00020002;
  {$EXTERNALSYM VOS_OS216_PM16}
  VOS_OS232_PM32    = $00030003;
  {$EXTERNALSYM VOS_OS232_PM32}
  VOS_NT_WINDOWS32  = $00040004;
  {$EXTERNALSYM VOS_NT_WINDOWS32}

// ----- VS_VERSION.dwFileType -----

  VFT_UNKNOWN    = $00000000;
  {$EXTERNALSYM VFT_UNKNOWN}
  VFT_APP        = $00000001;
  {$EXTERNALSYM VFT_APP}
  VFT_DLL        = $00000002;
  {$EXTERNALSYM VFT_DLL}
  VFT_DRV        = $00000003;
  {$EXTERNALSYM VFT_DRV}
  VFT_FONT       = $00000004;
  {$EXTERNALSYM VFT_FONT}
  VFT_VXD        = $00000005;
  {$EXTERNALSYM VFT_VXD}
  VFT_STATIC_LIB = $00000007;
  {$EXTERNALSYM VFT_STATIC_LIB}

// ----- VS_VERSION.dwFileSubtype for VFT_WINDOWS_DRV -----

  VFT2_UNKNOWN         = $00000000;
  {$EXTERNALSYM VFT2_UNKNOWN}
  VFT2_DRV_PRINTER     = $00000001;
  {$EXTERNALSYM VFT2_DRV_PRINTER}
  VFT2_DRV_KEYBOARD    = $00000002;
  {$EXTERNALSYM VFT2_DRV_KEYBOARD}
  VFT2_DRV_LANGUAGE    = $00000003;
  {$EXTERNALSYM VFT2_DRV_LANGUAGE}
  VFT2_DRV_DISPLAY     = $00000004;
  {$EXTERNALSYM VFT2_DRV_DISPLAY}
  VFT2_DRV_MOUSE       = $00000005;
  {$EXTERNALSYM VFT2_DRV_MOUSE}
  VFT2_DRV_NETWORK     = $00000006;
  {$EXTERNALSYM VFT2_DRV_NETWORK}
  VFT2_DRV_SYSTEM      = $00000007;
  {$EXTERNALSYM VFT2_DRV_SYSTEM}
  VFT2_DRV_INSTALLABLE = $00000008;
  {$EXTERNALSYM VFT2_DRV_INSTALLABLE}
  VFT2_DRV_SOUND       = $00000009;
  {$EXTERNALSYM VFT2_DRV_SOUND}
  VFT2_DRV_COMM        = $0000000A;
  {$EXTERNALSYM VFT2_DRV_COMM}
  VFT2_DRV_INPUTMETHOD = $0000000B;
  {$EXTERNALSYM VFT2_DRV_INPUTMETHOD}
  VFT2_DRV_VERSIONED_PRINTER = $0000000C;
  {$EXTERNALSYM VFT2_DRV_VERSIONED_PRINTER}

// ----- VS_VERSION.dwFileSubtype for VFT_WINDOWS_FONT -----

  VFT2_FONT_RASTER   = $00000001;
  {$EXTERNALSYM VFT2_FONT_RASTER}
  VFT2_FONT_VECTOR   = $00000002;
  {$EXTERNALSYM VFT2_FONT_VECTOR}
  VFT2_FONT_TRUETYPE = $00000003;
  {$EXTERNALSYM VFT2_FONT_TRUETYPE}

// ----- VerFindFile() flags -----

  VFFF_ISSHAREDFILE = $0001;
  {$EXTERNALSYM VFFF_ISSHAREDFILE}

  VFF_CURNEDEST     = $0001;
  {$EXTERNALSYM VFF_CURNEDEST}
  VFF_FILEINUSE     = $0002;
  {$EXTERNALSYM VFF_FILEINUSE}
  VFF_BUFFTOOSMALL  = $0004;
  {$EXTERNALSYM VFF_BUFFTOOSMALL}

// ----- VerInstallFile() flags -----

  VIFF_FORCEINSTALL  = $0001;
  {$EXTERNALSYM VIFF_FORCEINSTALL}
  VIFF_DONTDELETEOLD = $0002;
  {$EXTERNALSYM VIFF_DONTDELETEOLD}

  VIF_TEMPFILE = $00000001;
  {$EXTERNALSYM VIF_TEMPFILE}
  VIF_MISMATCH = $00000002;
  {$EXTERNALSYM VIF_MISMATCH}
  VIF_SRCOLD   = $00000004;
  {$EXTERNALSYM VIF_SRCOLD}

  VIF_DIFFLANG   = $00000008;
  {$EXTERNALSYM VIF_DIFFLANG}
  VIF_DIFFCODEPG = $00000010;
  {$EXTERNALSYM VIF_DIFFCODEPG}
  VIF_DIFFTYPE   = $00000020;
  {$EXTERNALSYM VIF_DIFFTYPE}

  VIF_WRITEPROT        = $00000040;
  {$EXTERNALSYM VIF_WRITEPROT}
  VIF_FILEINUSE        = $00000080;
  {$EXTERNALSYM VIF_FILEINUSE}
  VIF_OUTOFSPACE       = $00000100;
  {$EXTERNALSYM VIF_OUTOFSPACE}
  VIF_ACCESSVIOLATION  = $00000200;
  {$EXTERNALSYM VIF_ACCESSVIOLATION}
  VIF_SHARINGVIOLATION = $00000400;
  {$EXTERNALSYM VIF_SHARINGVIOLATION}
  VIF_CANNOTCREATE     = $00000800;
  {$EXTERNALSYM VIF_CANNOTCREATE}
  VIF_CANNOTDELETE     = $00001000;
  {$EXTERNALSYM VIF_CANNOTDELETE}
  VIF_CANNOTRENAME     = $00002000;
  {$EXTERNALSYM VIF_CANNOTRENAME}
  VIF_CANNOTDELETECUR  = $00004000;
  {$EXTERNALSYM VIF_CANNOTDELETECUR}
  VIF_OUTOFMEMORY      = $00008000;
  {$EXTERNALSYM VIF_OUTOFMEMORY}

  VIF_CANNOTREADSRC = $00010000;
  {$EXTERNALSYM VIF_CANNOTREADSRC}
  VIF_CANNOTREADDST = $00020000;
  {$EXTERNALSYM VIF_CANNOTREADDST}

  VIF_BUFFTOOSMALL      = $00040000;
  {$EXTERNALSYM VIF_BUFFTOOSMALL}
  VIF_CANNOTLOADLZ32    = $00080000;
  {$EXTERNALSYM VIF_CANNOTLOADLZ32}
  VIF_CANNOTLOADCABINET = $00100000;
  {$EXTERNALSYM VIF_CANNOTLOADCABINET}

// ----- Types and structures -----

type
{$IFDEF USEDELPHI5}
  PVSFixedFileInfo = Windows.PVSFixedFileInfo;
  tagVS_FIXEDFILEINFO = Windows.tagVS_FIXEDFILEINFO;
  VS_FIXEDFILEINFO = Windows.VS_FIXEDFILEINFO;
  TVSFixedFileInfo = Windows.TVSFixedFileInfo;
{$ELSE}
  PVSFixedFileInfo = ^VS_FIXEDFILEINFO;
  tagVS_FIXEDFILEINFO = record
    dwSignature: DWORD;        // e.g. 0xfeef04bd
    dwStrucVersion: DWORD;     // e.g. 0x00000042 = "0.42"
    dwFileVersionMS: DWORD;    // e.g. 0x00030075 = "3.75"
    dwFileVersionLS: DWORD;    // e.g. 0x00000031 = "0.31"
    dwProductVersionMS: DWORD; // e.g. 0x00030010 = "3.10"
    dwProductVersionLS: DWORD; // e.g. 0x00000031 = "0.31"
    dwFileFlagsMask: DWORD;    // = 0x3F for version "0.42"
    dwFileFlags: DWORD;        // e.g. VFF_DEBUG | VFF_PRERELEASE
    dwFileOS: DWORD;           // e.g. VOS_DOS_WINDOWS16
    dwFileType: DWORD;         // e.g. VFT_DRIVER
    dwFileSubtype: DWORD;      // e.g. VFT2_DRV_KEYBOARD
    dwFileDateMS: DWORD;       // e.g. 0
    dwFileDateLS: DWORD;       // e.g. 0
  end;
  {$EXTERNALSYM tagVS_FIXEDFILEINFO}
  VS_FIXEDFILEINFO = tagVS_FIXEDFILEINFO;
  {$EXTERNALSYM VS_FIXEDFILEINFO}
  TVSFixedFileInfo = VS_FIXEDFILEINFO;
{$ENDIF}

// ----- Function prototypes -----

function VerFindFileA(uFlags: DWORD; szFileName, szWinDir, szAppDir,
  szCurDir: LPSTR; var lpuCurDirLen: UINT; szDestDir: LPSTR;
  var lpuDestDirLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerFindFileA}
function VerFindFileW(uFlags: DWORD; szFileName, szWinDir, szAppDir,
  szCurDir: LPWSTR; var lpuCurDirLen: UINT; szDestDir: LPWSTR;
  var lpuDestDirLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerFindFileW}

{$IFDEF UNICODE}
function VerFindFile(uFlags: DWORD; szFileName, szWinDir, szAppDir,
  szCurDir: LPWSTR; var lpuCurDirLen: UINT; szDestDir: LPWSTR;
  var lpuDestDirLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerFindFile}
{$ELSE}
function VerFindFile(uFlags: DWORD; szFileName, szWinDir, szAppDir,
  szCurDir: LPSTR; var lpuCurDirLen: UINT; szDestDir: LPSTR;
  var lpuDestDirLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerFindFile}
{$ENDIF}

function VerInstallFileA(uFlags: DWORD; szSrcFileName, szDestFileName, szSrcDir,
  szDestDir, szCurDir, szTmpFile: LPSTR; var lpuTmpFileLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerInstallFileA}
function VerInstallFileW(uFlags: DWORD; szSrcFileName, szDestFileName, szSrcDir,
  szDestDir, szCurDir, szTmpFile: LPWSTR; var lpuTmpFileLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerInstallFileW}

{$IFDEF UNICODE}
function VerInstallFile(uFlags: DWORD; szSrcFileName, szDestFileName, szSrcDir,
  szDestDir, szCurDir, szTmpFile: LPWSTR; var lpuTmpFileLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerInstallFile}
{$ELSE}
function VerInstallFile(uFlags: DWORD; szSrcFileName, szDestFileName, szSrcDir,
  szDestDir, szCurDir, szTmpFile: LPSTR; var lpuTmpFileLen: UINT): DWORD; stdcall;
{$EXTERNALSYM VerInstallFile}
{$ENDIF}

// Returns size of version info in bytes

function GetFileVersionInfoSizeA(lptstrFilename: LPCSTR; var lpdwHandle: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetFileVersionInfoSizeA}
function GetFileVersionInfoSizeW(lptstrFilename: LPCWSTR; var lpdwHandle: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetFileVersionInfoSizeW}

{$IFDEF UNICODE}
function GetFileVersionInfoSize(lptstrFilename: LPCWSTR; var lpdwHandle: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetFileVersionInfoSize}
{$ELSE}
function GetFileVersionInfoSize(lptstrFilename: LPCSTR; var lpdwHandle: DWORD): DWORD; stdcall;
{$EXTERNALSYM GetFileVersionInfoSize}
{$ENDIF}

// Read version info into buffer

function GetFileVersionInfoA(lptstrFilename: LPCSTR; dwHandle, dwLen: DWORD;
  lpData: LPVOID): BOOL; stdcall;
{$EXTERNALSYM GetFileVersionInfoA}
function GetFileVersionInfoW(lptstrFilename: LPCWSTR; dwHandle, dwLen: DWORD;
  lpData: LPVOID): BOOL; stdcall;
{$EXTERNALSYM GetFileVersionInfoW}

{$IFDEF UNICODE}
function GetFileVersionInfo(lptstrFilename: LPCWSTR; dwHandle, dwLen: DWORD;
  lpData: LPVOID): BOOL; stdcall;
{$EXTERNALSYM GetFileVersionInfo}
{$ELSE}
function GetFileVersionInfo(lptstrFilename: LPCSTR; dwHandle, dwLen: DWORD;
  lpData: LPVOID): BOOL; stdcall;
{$EXTERNALSYM GetFileVersionInfo}
{$ENDIF}

function VerLanguageNameA(wLang: DWORD; szLang: LPSTR; nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM VerLanguageNameA}
function VerLanguageNameW(wLang: DWORD; szLang: LPWSTR; nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM VerLanguageNameW}

{$IFDEF UNICODE}
function VerLanguageName(wLang: DWORD; szLang: LPWSTR; nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM VerLanguageName}
{$ELSE}
function VerLanguageName(wLang: DWORD; szLang: LPSTR; nSize: DWORD): DWORD; stdcall;
{$EXTERNALSYM VerLanguageName}
{$ENDIF}

function VerQueryValueA(pBlock: LPVOID; lpSubBlock: LPSTR; var lplpBuffer: LPVOID;
  var puLen: UINT): BOOL; stdcall;
{$EXTERNALSYM VerQueryValueA}
function VerQueryValueW(pBlock: LPVOID; lpSubBlock: LPWSTR; var lplpBuffer: LPVOID;
  var puLen: UINT): BOOL; stdcall;
{$EXTERNALSYM VerQueryValueW}

{$IFDEF UNICODE}
function VerQueryValue(pBlock: LPVOID; lpSubBlock: LPWSTR; var lplpBuffer: LPVOID;
  var puLen: UINT): BOOL; stdcall;
{$EXTERNALSYM VerQueryValue}
{$ELSE}
function VerQueryValue(pBlock: LPVOID; lpSubBlock: LPSTR; var lplpBuffer: LPVOID;
  var puLen: UINT): BOOL; stdcall;
{$EXTERNALSYM VerQueryValue}
{$ENDIF}

implementation

const
  Version = 'version.dll';


{$IFDEF DYNAMIC_LINK}
var
  _VerFindFileA: Pointer;

function VerFindFileA;
begin
  GetProcedureAddress(_VerFindFileA, Version, 'VerFindFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerFindFileA]
  end;
end;
{$ELSE}
function VerFindFileA; external Version name 'VerFindFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _VerFindFileW: Pointer;

function VerFindFileW;
begin
  GetProcedureAddress(_VerFindFileW, Version, 'VerFindFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerFindFileW]
  end;
end;
{$ELSE}
function VerFindFileW; external Version name 'VerFindFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _VerFindFile: Pointer;

function VerFindFile;
begin
  GetProcedureAddress(_VerFindFile, Version, 'VerFindFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerFindFile]
  end;
end;
{$ELSE}
function VerFindFile; external Version name 'VerFindFileW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _VerFindFile: Pointer;

function VerFindFile;
begin
  GetProcedureAddress(_VerFindFile, Version, 'VerFindFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerFindFile]
  end;
end;
{$ELSE}
function VerFindFile; external Version name 'VerFindFileA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _VerInstallFileA: Pointer;

function VerInstallFileA;
begin
  GetProcedureAddress(_VerInstallFileA, Version, 'VerInstallFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerInstallFileA]
  end;
end;
{$ELSE}
function VerInstallFileA; external Version name 'VerInstallFileA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _VerInstallFileW: Pointer;

function VerInstallFileW;
begin
  GetProcedureAddress(_VerInstallFileW, Version, 'VerInstallFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerInstallFileW]
  end;
end;
{$ELSE}
function VerInstallFileW; external Version name 'VerInstallFileW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _VerInstallFile: Pointer;

function VerInstallFile;
begin
  GetProcedureAddress(_VerInstallFile, Version, 'VerInstallFileW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerInstallFile]
  end;
end;
{$ELSE}
function VerInstallFile; external Version name 'VerInstallFileW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _VerInstallFile: Pointer;

function VerInstallFile;
begin
  GetProcedureAddress(_VerInstallFile, Version, 'VerInstallFileA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerInstallFile]
  end;
end;
{$ELSE}
function VerInstallFile; external Version name 'VerInstallFileA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfoSizeA: Pointer;

function GetFileVersionInfoSizeA;
begin
  GetProcedureAddress(_GetFileVersionInfoSizeA, Version, 'GetFileVersionInfoSizeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfoSizeA]
  end;
end;
{$ELSE}
function GetFileVersionInfoSizeA; external Version name 'GetFileVersionInfoSizeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfoSizeW: Pointer;

function GetFileVersionInfoSizeW;
begin
  GetProcedureAddress(_GetFileVersionInfoSizeW, Version, 'GetFileVersionInfoSizeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfoSizeW]
  end;
end;
{$ELSE}
function GetFileVersionInfoSizeW; external Version name 'GetFileVersionInfoSizeW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfoSize: Pointer;

function GetFileVersionInfoSize;
begin
  GetProcedureAddress(_GetFileVersionInfoSize, Version, 'GetFileVersionInfoSizeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfoSize]
  end;
end;
{$ELSE}
function GetFileVersionInfoSize; external Version name 'GetFileVersionInfoSizeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfoSize: Pointer;

function GetFileVersionInfoSize;
begin
  GetProcedureAddress(_GetFileVersionInfoSize, Version, 'GetFileVersionInfoSizeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfoSize]
  end;
end;
{$ELSE}
function GetFileVersionInfoSize; external Version name 'GetFileVersionInfoSizeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfoA: Pointer;

function GetFileVersionInfoA;
begin
  GetProcedureAddress(_GetFileVersionInfoA, Version, 'GetFileVersionInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfoA]
  end;
end;
{$ELSE}
function GetFileVersionInfoA; external Version name 'GetFileVersionInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfoW: Pointer;

function GetFileVersionInfoW;
begin
  GetProcedureAddress(_GetFileVersionInfoW, Version, 'GetFileVersionInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfoW]
  end;
end;
{$ELSE}
function GetFileVersionInfoW; external Version name 'GetFileVersionInfoW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfo: Pointer;

function GetFileVersionInfo;
begin
  GetProcedureAddress(_GetFileVersionInfo, Version, 'GetFileVersionInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfo]
  end;
end;
{$ELSE}
function GetFileVersionInfo; external Version name 'GetFileVersionInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetFileVersionInfo: Pointer;

function GetFileVersionInfo;
begin
  GetProcedureAddress(_GetFileVersionInfo, Version, 'GetFileVersionInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetFileVersionInfo]
  end;
end;
{$ELSE}
function GetFileVersionInfo; external Version name 'GetFileVersionInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _VerLanguageNameA: Pointer;

function VerLanguageNameA;
begin
  GetProcedureAddress(_VerLanguageNameA, Version, 'VerLanguageNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerLanguageNameA]
  end;
end;
{$ELSE}
function VerLanguageNameA; external Version name 'VerLanguageNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _VerLanguageNameW: Pointer;

function VerLanguageNameW;
begin
  GetProcedureAddress(_VerLanguageNameW, Version, 'VerLanguageNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerLanguageNameW]
  end;
end;
{$ELSE}
function VerLanguageNameW; external Version name 'VerLanguageNameW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _VerLanguageName: Pointer;

function VerLanguageName;
begin
  GetProcedureAddress(_VerLanguageName, Version, 'VerLanguageNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerLanguageName]
  end;
end;
{$ELSE}
function VerLanguageName; external Version name 'VerLanguageNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _VerLanguageName: Pointer;

function VerLanguageName;
begin
  GetProcedureAddress(_VerLanguageName, Version, 'VerLanguageNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerLanguageName]
  end;
end;
{$ELSE}
function VerLanguageName; external Version name 'VerLanguageNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}


{$IFDEF DYNAMIC_LINK}
var
  _VerQueryValueA: Pointer;

function VerQueryValueA;
begin
  GetProcedureAddress(_VerQueryValueA, Version, 'VerQueryValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerQueryValueA]
  end;
end;
{$ELSE}
function VerQueryValueA; external Version name 'VerQueryValueA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _VerQueryValueW: Pointer;

function VerQueryValueW;
begin
  GetProcedureAddress(_VerQueryValueW, Version, 'VerQueryValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerQueryValueW]
  end;
end;
{$ELSE}
function VerQueryValueW; external Version name 'VerQueryValueW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _VerQueryValue: Pointer;

function VerQueryValue;
begin
  GetProcedureAddress(_VerQueryValue, Version, 'VerQueryValueW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerQueryValue]
  end;
end;
{$ELSE}
function VerQueryValue; external Version name 'VerQueryValueW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _VerQueryValue: Pointer;

function VerQueryValue;
begin
  GetProcedureAddress(_VerQueryValue, Version, 'VerQueryValueA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerQueryValue]
  end;
end;
{$ELSE}
function VerQueryValue; external Version name 'VerQueryValueA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
