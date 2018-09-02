{******************************************************************************}
{                                                       	               }
{ SSPI Context Management API interface Unit for Object Pascal                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: secext.h, released August 2001. The original Pascal    }
{ code is: SecExt.pas, released December 2000. The initial developer of the    }
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

unit JwaSecExt;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "secext.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaSSPI, JwaWinType;

//
// Extended Name APIs for ADS
//

const
  // Examples for the following formats assume a fictitous company
  // which hooks into the global X.500 and DNS name spaces as follows.
  //
  // Enterprise root domain in DNS is
  //
  //      widget.com
  //
  // Enterprise root domain in X.500 (RFC 1779 format) is
  //
  //      O=Widget, C=US
  //
  // There exists the child domain
  //
  //      engineering.widget.com
  //
  // equivalent to
  //
  //      OU=Engineering, O=Widget, C=US
  //
  // There exists a container within the Engineering domain
  //
  //      OU=Software, OU=Engineering, O=Widget, C=US
  //
  // There exists the user
  //
  //      CN=John Doe, OU=Software, OU=Engineering, O=Widget, C=US
  //
  // And this user's downlevel (pre-ADS) user name is
  //
  //      Engineering\JohnDoe

  // unknown name type
  NameUnknown = 0;
  {$EXTERNALSYM NameUnknown}

  // CN=John Doe, OU=Software, OU=Engineering, O=Widget, C=US
  NameFullyQualifiedDN = 1;
  {$EXTERNALSYM NameFullyQualifiedDN}

  // Engineering\JohnDoe
  NameSamCompatible = 2;
  {$EXTERNALSYM NameSamCompatible}

  // Probably "John Doe" but could be something else.  I.e. The
  // display name is not necessarily the defining RDN.
  NameDisplay = 3;
  {$EXTERNALSYM NameDisplay}

  // String-ized GUID as returned by IIDFromString().
  // eg: {4fa050f0-f561-11cf-bdd9-00aa003a77b6}
  NameUniqueId = 6;
  {$EXTERNALSYM NameUniqueId}

  // engineering.widget.com/software/John Doe
  NameCanonical = 7;
  {$EXTERNALSYM NameCanonical}

  // johndoe@engineering.com
  NameUserPrincipal = 8;
  {$EXTERNALSYM NameUserPrincipal}

  // Same as NameCanonical except that rightmost '/' is
  // replaced with '\n' - even in domain-only case.
  // eg: engineering.widget.com/software\nJohn Doe
  NameCanonicalEx = 9;
  {$EXTERNALSYM NameCanonicalEx}

  // www/srv.engineering.com/engineering.com
  NameServicePrincipal = 10;
  {$EXTERNALSYM NameServicePrincipal}

  // DNS domain name + SAM username
  // eg: engineering.widget.com\JohnDoe
  NameDnsDomain = 12;
  {$EXTERNALSYM NameDnsDomain}

type
  EXTENDED_NAME_FORMAT = DWORD;
  {$EXTERNALSYM EXTENDED_NAME_FORMAT}
  PEXTENDED_NAME_FORMAT = ^EXTENDED_NAME_FORMAT;
  {$EXTERNALSYM PEXTENDED_NAME_FORMAT}
  TExtendedNameFormat = EXTENDED_NAME_FORMAT;
  PExtendedNameFormat = PEXTENDED_NAME_FORMAT;

function GetUserNameExA(NameFormat: EXTENDED_NAME_FORMAT; lpNameBuffer: LPSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetUserNameExA}
function GetUserNameExW(NameFormat: EXTENDED_NAME_FORMAT; lpNameBuffer: LPWSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetUserNameExW}

{$IFDEF UNICODE}
function GetUserNameEx(NameFormat: EXTENDED_NAME_FORMAT; lpNameBuffer: LPWSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetUserNameEx}
{$ELSE}
function GetUserNameEx(NameFormat: EXTENDED_NAME_FORMAT; lpNameBuffer: LPSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetUserNameEx}
{$ENDIF}

function GetComputerObjectNameA(NameFormat: EXTENDED_NAME_FORMAT;
  lpNameBuffer: LPSTR; var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetComputerObjectNameA}
function GetComputerObjectNameW(NameFormat: EXTENDED_NAME_FORMAT;
  lpNameBuffer: LPWSTR; var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetComputerObjectNameW}

{$IFDEF UNICODE}
function GetComputerObjectName(NameFormat: EXTENDED_NAME_FORMAT;
  lpNameBuffer: LPWSTR; var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetComputerObjectName}
{$ELSE}
function GetComputerObjectName(NameFormat: EXTENDED_NAME_FORMAT;
  lpNameBuffer: LPSTR; var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM GetComputerObjectName}
{$ENDIF}

function TranslateNameA(lpAccountName: LPCSTR; AccountNameFormat,
  DesiredNameFormat: EXTENDED_NAME_FORMAT; lpTranslatedName: LPSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM TranslateNameA}
function TranslateNameW(lpAccountName: LPCWSTR; AccountNameFormat,
  DesiredNameFormat: EXTENDED_NAME_FORMAT; lpTranslatedName: LPWSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM TranslateNameW}

{$IFDEF UNICODE}
function TranslateName(lpAccountName: LPCWSTR; AccountNameFormat,
  DesiredNameFormat: EXTENDED_NAME_FORMAT; lpTranslatedName: LPWSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM TranslateName}
{$ELSE}
function TranslateName(lpAccountName: LPCSTR; AccountNameFormat,
  DesiredNameFormat: EXTENDED_NAME_FORMAT; lpTranslatedName: LPSTR;
  var nSize: ULONG): ByteBool; stdcall;
{$EXTERNALSYM TranslateName}
{$ENDIF}

implementation

const
  secur32 = 'secur32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _GetUserNameExA: Pointer;

function GetUserNameExA;
begin
  GetProcedureAddress(_GetUserNameExA, secur32, 'GetUserNameExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserNameExA]
  end;
end;
{$ELSE}
function GetUserNameExA; external secur32 name 'GetUserNameExA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetUserNameExW: Pointer;

function GetUserNameExW;
begin
  GetProcedureAddress(_GetUserNameExW, secur32, 'GetUserNameExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserNameExW]
  end;
end;
{$ELSE}
function GetUserNameExW; external secur32 name 'GetUserNameExW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetUserNameEx: Pointer;

function GetUserNameEx;
begin
  GetProcedureAddress(_GetUserNameEx, secur32, 'GetUserNameExW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserNameEx]
  end;
end;
{$ELSE}
function GetUserNameEx; external secur32 name 'GetUserNameExW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetUserNameEx: Pointer;

function GetUserNameEx;
begin
  GetProcedureAddress(_GetUserNameEx, secur32, 'GetUserNameExA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetUserNameEx]
  end;
end;
{$ELSE}
function GetUserNameEx; external secur32 name 'GetUserNameExA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetComputerObjectNameA: Pointer;

function GetComputerObjectNameA;
begin
  GetProcedureAddress(_GetComputerObjectNameA, secur32, 'GetComputerObjectNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetComputerObjectNameA]
  end;
end;
{$ELSE}
function GetComputerObjectNameA; external secur32 name 'GetComputerObjectNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetComputerObjectNameW: Pointer;

function GetComputerObjectNameW;
begin
  GetProcedureAddress(_GetComputerObjectNameW, secur32, 'GetComputerObjectNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetComputerObjectNameW]
  end;
end;
{$ELSE}
function GetComputerObjectNameW; external secur32 name 'GetComputerObjectNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetComputerObjectName: Pointer;

function GetComputerObjectName;
begin
  GetProcedureAddress(_GetComputerObjectName, secur32, 'GetComputerObjectNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetComputerObjectName]
  end;
end;
{$ELSE}
function GetComputerObjectName; external secur32 name 'GetComputerObjectNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetComputerObjectName: Pointer;

function GetComputerObjectName;
begin
  GetProcedureAddress(_GetComputerObjectName, secur32, 'GetComputerObjectNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetComputerObjectName]
  end;
end;
{$ELSE}
function GetComputerObjectName; external secur32 name 'GetComputerObjectNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _TranslateNameA: Pointer;

function TranslateNameA;
begin
  GetProcedureAddress(_TranslateNameA, secur32, 'TranslateNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TranslateNameA]
  end;
end;
{$ELSE}
function TranslateNameA; external secur32 name 'TranslateNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TranslateNameW: Pointer;

function TranslateNameW;
begin
  GetProcedureAddress(_TranslateNameW, secur32, 'TranslateNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TranslateNameW]
  end;
end;
{$ELSE}
function TranslateNameW; external secur32 name 'TranslateNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _TranslateName: Pointer;

function TranslateName;
begin
  GetProcedureAddress(_TranslateName, secur32, 'TranslateNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TranslateName]
  end;
end;
{$ELSE}
function TranslateName; external secur32 name 'TranslateNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _TranslateName: Pointer;

function TranslateName;
begin
  GetProcedureAddress(_TranslateName, secur32, 'TranslateNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TranslateName]
  end;
end;
{$ELSE}
function TranslateName; external secur32 name 'TranslateNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
