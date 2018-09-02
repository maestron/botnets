{******************************************************************************}
{                                                       	               }
{ Active Directory Helper Functions API interface Unit for Object Pascal       }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: adshlp.h, released June 2000. The original Pascal      }
{ code is: AdsHlp.pas, released December 2000. The initial developer of the    }
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

unit JwaAdsHlp;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "adshlp.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX {TODO}, JwaAdsTLB, JwaWinType, JwaWinNT;

function ADsGetObject(lpszPathName: LPCWSTR; const riid: TGUID; out ppObject: Pointer): HRESULT; stdcall;
{$EXTERNALSYM ADsGetObject}

function ADsBuildEnumerator(pADsContainer: IADsContainer; out ppEnumVariant: IEnumVARIANT): HRESULT; stdcall;
{$EXTERNALSYM ADsBuildEnumerator}

function ADsFreeEnumerator(pEnumVariant: IEnumVARIANT): HRESULT; stdcall;
{$EXTERNALSYM ADsFreeEnumerator}

function ADsEnumerateNext(pEnumVariant: IEnumVARIANT; cElements: ULONG;
  var pvar: OleVariant; var pcElementsFetched: ULONG): HRESULT; stdcall;
{$EXTERNALSYM ADsEnumerateNext}

function ADsBuildVarArrayStr(lppPathNames: LPWSTR; dwPathNames: DWORD;
  var pVar: OleVariant): HRESULT; stdcall;
{$EXTERNALSYM ADsBuildVarArrayStr}

function ADsBuildVarArrayInt(lpdwObjectTypes: LPDWORD; dwObjectTypes: DWORD;
  var pVar: OleVariant): HRESULT; stdcall;
{$EXTERNALSYM ADsBuildVarArrayInt}

function ADsOpenObject(lpszPathName, lpszUserName, lpszPassword: LPCWSTR;
  dwReserved: DWORD; const riid: TGUID; out ppObject: Pointer): HRESULT; stdcall;
{$EXTERNALSYM ADsOpenObject}

//
// Helper functions for extended error support
//

function ADsGetLastError(var lpError: DWORD; lpErrorBuf: LPWSTR;
  dwErrorBufLen: DWORD; lpNameBuf: LPWSTR; dwNameBufLen: DWORD): HRESULT; stdcall;
{$EXTERNALSYM ADsGetLastError}

procedure ADsSetLastError(dwErr: DWORD; pszError, pszProvider: LPCWSTR); stdcall;
{$EXTERNALSYM ADsSetLastError}

//procedure ADsFreeAllErrorRecords; stdcall;
//{$EXTERNALSYM ADsFreeAllErrorRecords}

function AllocADsMem(cb: DWORD): LPVOID; stdcall;
{$EXTERNALSYM AllocADsMem}

function FreeADsMem(pMem: LPVOID): BOOL; stdcall;
{$EXTERNALSYM FreeADsMem}

function ReallocADsMem(pOldMem: LPVOID; cbOld, cbNew: DWORD): LPVOID; stdcall;
{$EXTERNALSYM ReallocADsMem}

function AllocADsStr(pStr: LPCWSTR): LPWSTR; stdcall;
{$EXTERNALSYM AllocADsStr}

function FreeADsStr(pStr: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM FreeADsStr}

function ReallocADsStr(var ppStr: LPWSTR; pStr: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM ReallocADsStr}

function ADsEncodeBinaryData(pbSrcData: PBYTE; dwSrcLen: DWORD;
  var ppszDestData: LPWSTR): HRESULT; stdcall;
{$EXTERNALSYM ADsEncodeBinaryData}

function ADsDecodeBinaryData(szSrcData: LPCWSTR; var ppbDestData: PBYTE;
  var pdwDestLen: ULONG): HRESULT; stdcall;
{$EXTERNALSYM ADsDecodeBinaryData}

type
  // imports of a type library sometimes are missing a few decls, these are just
  // a few of them to make this file compile at all. I really should do all of
  // them one day.

  PADSVALUE = ^_adsvalue;
  {$EXTERNALSYM PADSVALUE}
  PADS_ATTR_INFO = ^_ads_attr_info;
  {$EXTERNALSYM PADS_ATTR_INFO}

function PropVariantToAdsType(var pVariant: OleVariant; dwNumVariant: DWORD;
  var ppAdsValues: PADSVALUE; pdwNumValues: PDWORD): HRESULT; stdcall;
{$EXTERNALSYM PropVariantToAdsType}

function AdsTypeToPropVariant(pAdsValues: PADSVALUE; dwNumValues: DWORD;
  var pVariant: OleVariant): HRESULT; stdcall;
{$EXTERNALSYM AdsTypeToPropVariant}

procedure AdsFreeAdsValues(pAdsValues: PADSVALUE; dwNumValues: DWORD); stdcall;
{$EXTERNALSYM AdsFreeAdsValues}

//
// Helper routines to convert IADsSecurityDescriptor to a binary
// security descriptor and also to convert a binary SD to 
// IADsSecurityDescriptor.
//

// TODO VARIANT!

function BinarySDToSecurityDescriptor(pSecurityDescriptor: PSECURITY_DESCRIPTOR;
  var pVarsec: VARIANT; pszServerName, userName, passWord: LPCWSTR; dwFlags: DWORD): HRESULT; stdcall;
{$EXTERNALSYM BinarySDToSecurityDescriptor}

function SecurityDescriptorToBinarySD(vVarSecDes: VARIANT;
  var ppSecurityDescriptor: PSECURITY_DESCRIPTOR; pdwSDLength: PDWORD;
  pszServerName, userName, passWord: LPCWSTR; dwFlags: DWORD): HRESULT; stdcall;
{$EXTERNALSYM SecurityDescriptorToBinarySD}

implementation

const
  adslib = 'activeds.dll';


{$IFDEF DYNAMIC_LINK}
var
  _ADsGetObject: Pointer;

function ADsGetObject;
begin
  GetProcedureAddress(_ADsGetObject, adslib, 'ADsGetObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsGetObject]
  end;
end;
{$ELSE}
function ADsGetObject; external adslib name 'ADsGetObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsBuildEnumerator: Pointer;

function ADsBuildEnumerator;
begin
  GetProcedureAddress(_ADsBuildEnumerator, adslib, 'ADsBuildEnumerator');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsBuildEnumerator]
  end;
end;
{$ELSE}
function ADsBuildEnumerator; external adslib name 'ADsBuildEnumerator';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsFreeEnumerator: Pointer;

function ADsFreeEnumerator;
begin
  GetProcedureAddress(_ADsFreeEnumerator, adslib, 'ADsFreeEnumerator');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsFreeEnumerator]
  end;
end;
{$ELSE}
function ADsFreeEnumerator; external adslib name 'ADsFreeEnumerator';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsEnumerateNext: Pointer;

function ADsEnumerateNext;
begin
  GetProcedureAddress(_ADsEnumerateNext, adslib, 'ADsEnumerateNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsEnumerateNext]
  end;
end;
{$ELSE}
function ADsEnumerateNext; external adslib name 'ADsEnumerateNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsBuildVarArrayStr: Pointer;

function ADsBuildVarArrayStr;
begin
  GetProcedureAddress(_ADsBuildVarArrayStr, adslib, 'ADsBuildVarArrayStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsBuildVarArrayStr]
  end;
end;
{$ELSE}
function ADsBuildVarArrayStr; external adslib name 'ADsBuildVarArrayStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsBuildVarArrayInt: Pointer;

function ADsBuildVarArrayInt;
begin
  GetProcedureAddress(_ADsBuildVarArrayInt, adslib, 'ADsBuildVarArrayInt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsBuildVarArrayInt]
  end;
end;
{$ELSE}
function ADsBuildVarArrayInt; external adslib name 'ADsBuildVarArrayInt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsOpenObject: Pointer;

function ADsOpenObject;
begin
  GetProcedureAddress(_ADsOpenObject, adslib, 'ADsOpenObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsOpenObject]
  end;
end;
{$ELSE}
function ADsOpenObject; external adslib name 'ADsOpenObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsGetLastError: Pointer;

function ADsGetLastError;
begin
  GetProcedureAddress(_ADsGetLastError, adslib, 'ADsGetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsGetLastError]
  end;
end;
{$ELSE}
function ADsGetLastError; external adslib name 'ADsGetLastError';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsSetLastError: Pointer;

procedure ADsSetLastError;
begin
  GetProcedureAddress(_ADsSetLastError, adslib, 'ADsSetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsSetLastError]
  end;
end;
{$ELSE}
procedure ADsSetLastError; external adslib name 'ADsSetLastError';
{$ENDIF DYNAMIC_LINK}
//procedure ADsFreeAllErrorRecords

{$IFDEF DYNAMIC_LINK}
var
  _AllocADsMem: Pointer;

function AllocADsMem;
begin
  GetProcedureAddress(_AllocADsMem, adslib, 'AllocADsMem');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AllocADsMem]
  end;
end;
{$ELSE}
function AllocADsMem; external adslib name 'AllocADsMem';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FreeADsMem: Pointer;

function FreeADsMem;
begin
  GetProcedureAddress(_FreeADsMem, adslib, 'FreeADsMem');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeADsMem]
  end;
end;
{$ELSE}
function FreeADsMem; external adslib name 'FreeADsMem';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReallocADsMem: Pointer;

function ReallocADsMem;
begin
  GetProcedureAddress(_ReallocADsMem, adslib, 'ReallocADsMem');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReallocADsMem]
  end;
end;
{$ELSE}
function ReallocADsMem; external adslib name 'ReallocADsMem';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AllocADsStr: Pointer;

function AllocADsStr;
begin
  GetProcedureAddress(_AllocADsStr, adslib, 'AllocADsStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AllocADsStr]
  end;
end;
{$ELSE}
function AllocADsStr; external adslib name 'AllocADsStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FreeADsStr: Pointer;

function FreeADsStr;
begin
  GetProcedureAddress(_FreeADsStr, adslib, 'FreeADsStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeADsStr]
  end;
end;
{$ELSE}
function FreeADsStr; external adslib name 'FreeADsStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReallocADsStr: Pointer;

function ReallocADsStr;
begin
  GetProcedureAddress(_ReallocADsStr, adslib, 'ReallocADsStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReallocADsStr]
  end;
end;
{$ELSE}
function ReallocADsStr; external adslib name 'ReallocADsStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsEncodeBinaryData: Pointer;

function ADsEncodeBinaryData;
begin
  GetProcedureAddress(_ADsEncodeBinaryData, adslib, 'ADsEncodeBinaryData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsEncodeBinaryData]
  end;
end;
{$ELSE}
function ADsEncodeBinaryData; external adslib name 'ADsEncodeBinaryData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsDecodeBinaryData: Pointer;

function ADsDecodeBinaryData;
begin
  GetProcedureAddress(_ADsDecodeBinaryData, adslib, 'ADsDecodeBinaryData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsDecodeBinaryData]
  end;
end;
{$ELSE}
function ADsDecodeBinaryData; external adslib name 'ADsDecodeBinaryData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PropVariantToAdsType: Pointer;

function PropVariantToAdsType;
begin
  GetProcedureAddress(_PropVariantToAdsType, adslib, 'PropVariantToAdsType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PropVariantToAdsType]
  end;
end;
{$ELSE}
function PropVariantToAdsType; external adslib name 'PropVariantToAdsType';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AdsTypeToPropVariant: Pointer;

function AdsTypeToPropVariant;
begin
  GetProcedureAddress(_AdsTypeToPropVariant, adslib, 'AdsTypeToPropVariant');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AdsTypeToPropVariant]
  end;
end;
{$ELSE}
function AdsTypeToPropVariant; external adslib name 'AdsTypeToPropVariant';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AdsFreeAdsValues: Pointer;

procedure AdsFreeAdsValues;
begin
  GetProcedureAddress(_AdsFreeAdsValues, adslib, 'AdsFreeAdsValues');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AdsFreeAdsValues]
  end;
end;
{$ELSE}
procedure AdsFreeAdsValues; external adslib name 'AdsFreeAdsValues';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _BinarySDToSecurityDescriptor: Pointer;

function BinarySDToSecurityDescriptor;
begin
  GetProcedureAddress(_BinarySDToSecurityDescriptor, adslib, 'BinarySDToSecurityDescriptor');
  asm
    mov esp, ebp
    pop ebp
    jmp [_BinarySDToSecurityDescriptor]
  end;
end;
{$ELSE}
function BinarySDToSecurityDescriptor; external adslib name 'BinarySDToSecurityDescriptor';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SecurityDescriptorToBinarySD: Pointer;

function SecurityDescriptorToBinarySD;
begin
  GetProcedureAddress(_SecurityDescriptorToBinarySD, adslib, 'SecurityDescriptorToBinarySD');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SecurityDescriptorToBinarySD]
  end;
end;
{$ELSE}
function SecurityDescriptorToBinarySD; external adslib name 'SecurityDescriptorToBinarySD';
{$ENDIF DYNAMIC_LINK}

end.
