{******************************************************************************}
{                                                       	               }
{ Cryptograhic UI API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: cryptuiapi.h, released August 2001. The original       }
{ Pascal code is: CryptUIApi.pas, released December 2001. The initial          }
{ developer of the Pascal code is Marcel van Brakel (brakelm@chello.nl).       }
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

unit JwaCryptUIApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "cryptuiapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinCrypt, JwaWinType;

// #include <pshpack8.h>

//+-------------------------------------------------------------------------
//  Dialog viewer of a certificate, CTL or CRL context.
//
//  dwContextType and associated pvContext's
//      CERT_STORE_CERTIFICATE_CONTEXT  PCCERT_CONTEXT
//      CERT_STORE_CRL_CONTEXT          PCCRL_CONTEXT
//      CERT_STORE_CTL_CONTEXT          PCCTL_CONTEXT
//
//  dwFlags currently isn't used and should be set to 0.
//--------------------------------------------------------------------------

function CryptUIDlgViewContext(dwContextType: DWORD; pvContext: LPVOID; hwnd: HWND; pwszTitle: LPCWSTR;
  dwFlags: DWORD; pvReserved: LPVOID): BOOL; stdcall;
{$EXTERNALSYM CryptUIDlgViewContext}

//+-------------------------------------------------------------------------
//  Dialog to select a certificate from the specified store.
//
//  Returns the selected certificate context. If no certificate was
//  selected, NULL is returned.
//
//  pwszTitle is either NULL or the title to be used for the dialog.
//  If NULL, the default title is used.  The default title is
//  "Select Certificate".
//
//  pwszDisplayString is either NULL or the text statement in the selection
//  dialog.  If NULL, the default phrase
//  "Select a certificate you wish to use" is used in the dialog.
//
//  dwDontUseColumn can be set to exclude columns from the selection
//  dialog. See the CRYPTDLG_SELECTCERT_*_COLUMN definitions below.
//
//  dwFlags currently isn't used and should be set to 0.
//--------------------------------------------------------------------------

function CryptUIDlgSelectCertificateFromStore(hCertStore: HCERTSTORE; hwnd: HWND; pwszTitle, pwszDisplayString: LPCWSTR;
  dwDontUseColumn, dwFlags: DWORD; pvReserved: LPVOID): PCCERT_CONTEXT; stdcall;
{$EXTERNALSYM CryptUIDlgSelectCertificateFromStore}

// flags for dwDontUseColumn

const
  CRYPTUI_SELECT_ISSUEDTO_COLUMN       = $000000001;
  {$EXTERNALSYM CRYPTUI_SELECT_ISSUEDTO_COLUMN}
  CRYPTUI_SELECT_ISSUEDBY_COLUMN       = $000000002;
  {$EXTERNALSYM CRYPTUI_SELECT_ISSUEDBY_COLUMN}
  CRYPTUI_SELECT_INTENDEDUSE_COLUMN    = $000000004;
  {$EXTERNALSYM CRYPTUI_SELECT_INTENDEDUSE_COLUMN}
  CRYPTUI_SELECT_FRIENDLYNAME_COLUMN   = $000000008;
  {$EXTERNALSYM CRYPTUI_SELECT_FRIENDLYNAME_COLUMN}
  CRYPTUI_SELECT_LOCATION_COLUMN       = $000000010;
  {$EXTERNALSYM CRYPTUI_SELECT_LOCATION_COLUMN}
  CRYPTUI_SELECT_EXPIRATION_COLUMN     = $000000020;
  {$EXTERNALSYM CRYPTUI_SELECT_EXPIRATION_COLUMN}

implementation

const
  cryptuiapi = 'cryptui.dll';


{$IFDEF DYNAMIC_LINK}
var
  _CryptUIDlgViewContext: Pointer;

function CryptUIDlgViewContext;
begin
  GetProcedureAddress(_CryptUIDlgViewContext, cryptuiapi, 'CryptUIDlgViewContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUIDlgViewContext]
  end;
end;
{$ELSE}
function CryptUIDlgViewContext; external cryptuiapi name 'CryptUIDlgViewContext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _CryptUIDlgSelCertFromStore: Pointer;

function CryptUIDlgSelectCertificateFromStore;
begin
  GetProcedureAddress(_CryptUIDlgSelCertFromStore, cryptuiapi, 'CryptUIDlgSelectCertificateFromStore');
  asm
    mov esp, ebp
    pop ebp
    jmp [_CryptUIDlgSelCertFromStore]
  end;
end;
{$ELSE}
function CryptUIDlgSelectCertificateFromStore; external cryptuiapi name 'CryptUIDlgSelectCertificateFromStore';
{$ENDIF DYNAMIC_LINK}

end.
