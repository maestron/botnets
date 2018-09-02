{******************************************************************************}
{                                                       	               }
{ Web Publishing API interface Unit for Object Pascal                          }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wpapi.h, released June 2000. The original Pascal       }
{ code is: WPApi.pas, released December 2000. The initial developer of the     }
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

unit JwaWPApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wpapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWPTypes, JwaWinType;

//
//	Flags
//

const
  WPF_NO_RECURSIVE_POST     = $00000001; // WpPost
  {$EXTERNALSYM WPF_NO_RECURSIVE_POST}
  WPF_NO_WIZARD             = $00000002; // WpPost
  {$EXTERNALSYM WPF_NO_WIZARD}
  WPF_MINIMAL_UI            = $00000004; // WpPost - OBSOLETE
  {$EXTERNALSYM WPF_MINIMAL_UI}
  WPF_FIRST_FILE_AS_DEFAULT = $00000008; // WpPost/PostFiles
  {$EXTERNALSYM WPF_FIRST_FILE_AS_DEFAULT}
  WPF_NO_DIRECT_LOOKUP      = $00000010; // WpBindToSite
  {$EXTERNALSYM WPF_NO_DIRECT_LOOKUP}
  WPF_NO_URL_LOOKUP         = $00000020; // WpBindToSite
  {$EXTERNALSYM WPF_NO_URL_LOOKUP}
  WPF_USE_PROVIDER_PASSED   = $00000040; // WpCreateSite
  {$EXTERNALSYM WPF_USE_PROVIDER_PASSED}
  WPF_NO_VERIFY_POST        = $00000080; // WpPost
  {$EXTERNALSYM WPF_NO_VERIFY_POST}
  WPF_NO_PROGRESS_DLGS      = $00000200; // WpPost
  {$EXTERNALSYM WPF_NO_PROGRESS_DLGS}
  WPF_SHOWPAGE_WELCOME      = $00010000; // WpPost/Wizard
  {$EXTERNALSYM WPF_SHOWPAGE_WELCOME}
  WPF_SHOWPAGE_SRCFILE      = $00020000; // WpPost/Wizard
  {$EXTERNALSYM WPF_SHOWPAGE_SRCFILE}
  WPF_SHOWPAGE_DESTSITE     = $00040000; // WpPost/Wizard
  {$EXTERNALSYM WPF_SHOWPAGE_DESTSITE}
  WPF_SHOWPAGE_PROVIDER     = $00080000; // WpPost/Wizard/AddWizardPages
  {$EXTERNALSYM WPF_SHOWPAGE_PROVIDER}
  WPF_ENABLE_LOCAL_BASE_DIR = $00100000; // WpPost/Wizard
  {$EXTERNALSYM WPF_ENABLE_LOCAL_BASE_DIR}

  WPF_NO_UI = WPF_NO_WIZARD or WPF_NO_PROGRESS_DLGS;
  {$EXTERNALSYM WPF_NO_UI}

  WPF_SHOWPAGE_ALL = WPF_SHOWPAGE_WELCOME or WPF_SHOWPAGE_SRCFILE or WPF_SHOWPAGE_DESTSITE or WPF_SHOWPAGE_PROVIDER;
  {$EXTERNALSYM WPF_SHOWPAGE_ALL}

//
//	Miscellaneous
//

  MAX_SITENAME_LEN = 128;
  {$EXTERNALSYM MAX_SITENAME_LEN}

//
//	Unicode APIs
//

function WpPostW(hwnd: HWND; dwNumLocalPaths: DWORD; pwsLocalPaths: LPWSTR;
  var pdwSiteNameBufLen: DWORD; wsSiteName: LPWSTR; var pdwDestURLBufLen: DWORD;
  wsDestURL: LPWSTR; dwFlag: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpPostW}
function WpListSitesW(var pdwSitesBufLen: DWORD; pSitesBuffer: LPWPSITEINFOW;
  var pdwNumSites: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpListSitesW}
function WpDoesSiteExistW(wsSiteName: LPCWSTR; var pfSiteExists: BOOL): DWORD; stdcall;
{$EXTERNALSYM WpDoesSiteExistW}
function WpDeleteSiteW(wsSiteName: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM WpDeleteSiteW}
function WpBindToSiteW(hwnd: HWND; wsSiteName, wsSitePostingURL: LPCWSTR;
  dwFlag, dwReserved: DWORD; out ppvUnk: IUnknown): DWORD; stdcall;
{$EXTERNALSYM WpBindToSiteW}
function WpCreateSiteW(wsSiteName, wsSiteLocalBaseDir, wsSitePostingURL,
  wsProviderCLSID: LPCWSTR; dwFlags: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpCreateSiteW}
function WpEnumProvidersW(var pdwProvidersBufLen: DWORD; pProvidersBuffer: LPWPPROVINFOW;
  var pdwNumProviders: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpEnumProvidersW}
function WpGetErrorStringW(uErrCode: UINT; wsOutputBuf: LPWSTR; var pdwBufLen: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpGetErrorStringW}

//
//	ANSI APIs
//

function WpPostA(hwnd: HWND; dwNumLocalPaths: DWORD; pwsLocalPaths: LPSTR;
  var pdwSiteNameBufLen: DWORD; wsSiteName: LPSTR; var pdwDestURLBufLen: DWORD;
  wsDestURL: LPSTR; dwFlag: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpPostA}
function WpListSitesA(var pdwSitesBufLen: DWORD; pSitesBuffer: LPWPSITEINFOA;
  var pdwNumSites: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpListSitesA}
function WpDoesSiteExistA(wsSiteName: LPCSTR; var pfSiteExists: BOOL): DWORD; stdcall;
{$EXTERNALSYM WpDoesSiteExistA}
function WpDeleteSiteA(wsSiteName: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM WpDeleteSiteA}
function WpBindToSiteA(hwnd: HWND; wsSiteName, wsSitePostingURL: LPCSTR;
  dwFlag, dwReserved: DWORD; out ppvUnk: IUnknown): DWORD; stdcall;
{$EXTERNALSYM WpBindToSiteA}
function WpCreateSiteA(wsSiteName, wsSiteLocalBaseDir, wsSitePostingURL,
  wsProviderCLSID: LPCSTR; dwFlags: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpCreateSiteA}
function WpEnumProvidersA(var pdwProvidersBufLen: DWORD; pProvidersBuffer: LPWPPROVINFOA;
  var pdwNumProviders: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpEnumProvidersA}
function WpGetErrorStringA(uErrCode: UINT; wsOutputBuf: LPSTR; var pdwBufLen: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpGetErrorStringA}

{$IFDEF UNICODE}

function WpPost(hwnd: HWND; dwNumLocalPaths: DWORD; pwsLocalPaths: LPWSTR;
  var pdwSiteNameBufLen: DWORD; wsSiteName: LPWSTR; var pdwDestURLBufLen: DWORD;
  wsDestURL: LPWSTR; dwFlag: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpPost}
function WpListSites(var pdwSitesBufLen: DWORD; pSitesBuffer: LPWPSITEINFOW;
  var pdwNumSites: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpListSites}
function WpDoesSiteExist(wsSiteName: LPCWSTR; var pfSiteExists: BOOL): DWORD; stdcall;
{$EXTERNALSYM WpDoesSiteExist}
function WpDeleteSite(wsSiteName: LPCWSTR): DWORD; stdcall;
{$EXTERNALSYM WpDeleteSite}
function WpBindToSite(hwnd: HWND; wsSiteName, wsSitePostingURL: LPCWSTR;
  dwFlag, dwReserved: DWORD; out ppvUnk: IUnknown): DWORD; stdcall;
{$EXTERNALSYM WpBindToSite}
function WpCreateSite(wsSiteName, wsSiteLocalBaseDir, wsSitePostingURL, wsProviderCLSID: LPCWSTR; dwFlags: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpCreateSite}
function WpEnumProviders(var pdwProvidersBufLen: DWORD; pProvidersBuffer: LPWPPROVINFOW;
  var pdwNumProviders: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpEnumProviders}
function WpGetErrorString(uErrCode: UINT; wsOutputBuf: LPWSTR; var pdwBufLen: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpGetErrorString}

{$ELSE}

function WpPost(hwnd: HWND; dwNumLocalPaths: DWORD; pwsLocalPaths: LPSTR;
  var pdwSiteNameBufLen: DWORD; wsSiteName: LPSTR; var pdwDestURLBufLen: DWORD;
  wsDestURL: LPSTR; dwFlag: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpPost}
function WpListSites(var pdwSitesBufLen: DWORD; pSitesBuffer: LPWPSITEINFOA;
  var pdwNumSites: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpListSites}
function WpDoesSiteExist(wsSiteName: LPCSTR; var pfSiteExists: BOOL): DWORD; stdcall;
{$EXTERNALSYM WpDoesSiteExist}
function WpDeleteSite(wsSiteName: LPCSTR): DWORD; stdcall;
{$EXTERNALSYM WpDeleteSite}
function WpBindToSite(hwnd: HWND; wsSiteName, wsSitePostingURL: LPCSTR;
  dwFlag, dwReserved: DWORD; out ppvUnk: IUnknown): DWORD; stdcall;
{$EXTERNALSYM WpBindToSite}
function WpCreateSite(wsSiteName, wsSiteLocalBaseDir, wsSitePostingURL, wsProviderCLSID: LPCSTR; dwFlags: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpCreateSite}
function WpEnumProviders(var pdwProvidersBufLen: DWORD; pProvidersBuffer: LPWPPROVINFOA;
  var pdwNumProviders: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpEnumProviders}
function WpGetErrorString(uErrCode: UINT; wsOutputBuf: LPSTR; var pdwBufLen: DWORD): DWORD; stdcall;
{$EXTERNALSYM WpGetErrorString}

{$ENDIF}

implementation

const
  wpapi_lib = 'wpapi.dll';


{$IFDEF DYNAMIC_LINK}
var
  _WpPostA: Pointer;

function WpPostA;
begin
  GetProcedureAddress(_WpPostA, wpapi_lib, 'WpPostA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpPostA]
  end;
end;
{$ELSE}
function WpPostA; external wpapi_lib name 'WpPostA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpListSitesA: Pointer;

function WpListSitesA;
begin
  GetProcedureAddress(_WpListSitesA, wpapi_lib, 'WpListSitesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpListSitesA]
  end;
end;
{$ELSE}
function WpListSitesA; external wpapi_lib name 'WpListSitesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDoesSiteExistA: Pointer;

function WpDoesSiteExistA;
begin
  GetProcedureAddress(_WpDoesSiteExistA, wpapi_lib, 'WpDoesSiteExistA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDoesSiteExistA]
  end;
end;
{$ELSE}
function WpDoesSiteExistA; external wpapi_lib name 'WpDoesSiteExistA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDeleteSiteA: Pointer;

function WpDeleteSiteA;
begin
  GetProcedureAddress(_WpDeleteSiteA, wpapi_lib, 'WpDeleteSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDeleteSiteA]
  end;
end;
{$ELSE}
function WpDeleteSiteA; external wpapi_lib name 'WpDeleteSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpBindToSiteA: Pointer;

function WpBindToSiteA;
begin
  GetProcedureAddress(_WpBindToSiteA, wpapi_lib, 'WpBindToSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpBindToSiteA]
  end;
end;
{$ELSE}
function WpBindToSiteA; external wpapi_lib name 'WpBindToSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpCreateSiteA: Pointer;

function WpCreateSiteA;
begin
  GetProcedureAddress(_WpCreateSiteA, wpapi_lib, 'WpCreateSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpCreateSiteA]
  end;
end;
{$ELSE}
function WpCreateSiteA; external wpapi_lib name 'WpCreateSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpEnumProvidersA: Pointer;

function WpEnumProvidersA;
begin
  GetProcedureAddress(_WpEnumProvidersA, wpapi_lib, 'WpEnumProvidersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpEnumProvidersA]
  end;
end;
{$ELSE}
function WpEnumProvidersA; external wpapi_lib name 'WpEnumProvidersA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpGetErrorStringA: Pointer;

function WpGetErrorStringA;
begin
  GetProcedureAddress(_WpGetErrorStringA, wpapi_lib, 'WpGetErrorStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpGetErrorStringA]
  end;
end;
{$ELSE}
function WpGetErrorStringA; external wpapi_lib name 'WpGetErrorStringA';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _WpPostW: Pointer;

function WpPostW;
begin
  GetProcedureAddress(_WpPostW, wpapi_lib, 'WpPostW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpPostW]
  end;
end;
{$ELSE}
function WpPostW; external wpapi_lib name 'WpPostW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpListSitesW: Pointer;

function WpListSitesW;
begin
  GetProcedureAddress(_WpListSitesW, wpapi_lib, 'WpListSitesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpListSitesW]
  end;
end;
{$ELSE}
function WpListSitesW; external wpapi_lib name 'WpListSitesW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDoesSiteExistW: Pointer;

function WpDoesSiteExistW;
begin
  GetProcedureAddress(_WpDoesSiteExistW, wpapi_lib, 'WpDoesSiteExistW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDoesSiteExistW]
  end;
end;
{$ELSE}
function WpDoesSiteExistW; external wpapi_lib name 'WpDoesSiteExistW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDeleteSiteW: Pointer;

function WpDeleteSiteW;
begin
  GetProcedureAddress(_WpDeleteSiteW, wpapi_lib, 'WpDeleteSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDeleteSiteW]
  end;
end;
{$ELSE}
function WpDeleteSiteW; external wpapi_lib name 'WpDeleteSiteW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpBindToSiteW: Pointer;

function WpBindToSiteW;
begin
  GetProcedureAddress(_WpBindToSiteW, wpapi_lib, 'WpBindToSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpBindToSiteW]
  end;
end;
{$ELSE}
function WpBindToSiteW; external wpapi_lib name 'WpBindToSiteW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpCreateSiteW: Pointer;

function WpCreateSiteW;
begin
  GetProcedureAddress(_WpCreateSiteW, wpapi_lib, 'WpCreateSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpCreateSiteW]
  end;
end;
{$ELSE}
function WpCreateSiteW; external wpapi_lib name 'WpCreateSiteW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpEnumProvidersW: Pointer;

function WpEnumProvidersW;
begin
  GetProcedureAddress(_WpEnumProvidersW, wpapi_lib, 'WpEnumProvidersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpEnumProvidersW]
  end;
end;
{$ELSE}
function WpEnumProvidersW; external wpapi_lib name 'WpEnumProvidersW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpGetErrorStringW: Pointer;

function WpGetErrorStringW;
begin
  GetProcedureAddress(_WpGetErrorStringW, wpapi_lib, 'WpGetErrorStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpGetErrorStringW]
  end;
end;
{$ELSE}
function WpGetErrorStringW; external wpapi_lib name 'WpGetErrorStringW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}


{$IFDEF DYNAMIC_LINK}
var
  _WpPost: Pointer;

function WpPost;
begin
  GetProcedureAddress(_WpPost, wpapi_lib, 'WpPostW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpPost]
  end;
end;
{$ELSE}
function WpPost; external wpapi_lib name 'WpPostW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpListSites: Pointer;

function WpListSites;
begin
  GetProcedureAddress(_WpListSites, wpapi_lib, 'WpListSitesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpListSites]
  end;
end;
{$ELSE}
function WpListSites; external wpapi_lib name 'WpListSitesW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDoesSiteExist: Pointer;

function WpDoesSiteExist;
begin
  GetProcedureAddress(_WpDoesSiteExist, wpapi_lib, 'WpDoesSiteExistW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDoesSiteExist]
  end;
end;
{$ELSE}
function WpDoesSiteExist; external wpapi_lib name 'WpDoesSiteExistW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDeleteSite: Pointer;

function WpDeleteSite;
begin
  GetProcedureAddress(_WpDeleteSite, wpapi_lib, 'WpDeleteSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDeleteSite]
  end;
end;
{$ELSE}
function WpDeleteSite; external wpapi_lib name 'WpDeleteSiteW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpBindToSite: Pointer;

function WpBindToSite;
begin
  GetProcedureAddress(_WpBindToSite, wpapi_lib, 'WpBindToSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpBindToSite]
  end;
end;
{$ELSE}
function WpBindToSite; external wpapi_lib name 'WpBindToSiteW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpCreateSite: Pointer;

function WpCreateSite;
begin
  GetProcedureAddress(_WpCreateSite, wpapi_lib, 'WpCreateSiteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpCreateSite]
  end;
end;
{$ELSE}
function WpCreateSite; external wpapi_lib name 'WpCreateSiteW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpEnumProviders: Pointer;

function WpEnumProviders;
begin
  GetProcedureAddress(_WpEnumProviders, wpapi_lib, 'WpEnumProvidersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpEnumProviders]
  end;
end;
{$ELSE}
function WpEnumProviders; external wpapi_lib name 'WpEnumProvidersW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpGetErrorString: Pointer;

function WpGetErrorString;
begin
  GetProcedureAddress(_WpGetErrorString, wpapi_lib, 'WpGetErrorStringW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpGetErrorString]
  end;
end;
{$ELSE}
function WpGetErrorString; external wpapi_lib name 'WpGetErrorStringW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}


{$IFDEF DYNAMIC_LINK}
var
  _WpPost: Pointer;

function WpPost;
begin
  GetProcedureAddress(_WpPost, wpapi_lib, 'WpPostA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpPost]
  end;
end;
{$ELSE}
function WpPost; external wpapi_lib name 'WpPostA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpListSites: Pointer;

function WpListSites;
begin
  GetProcedureAddress(_WpListSites, wpapi_lib, 'WpListSitesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpListSites]
  end;
end;
{$ELSE}
function WpListSites; external wpapi_lib name 'WpListSitesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDoesSiteExist: Pointer;

function WpDoesSiteExist;
begin
  GetProcedureAddress(_WpDoesSiteExist, wpapi_lib, 'WpDoesSiteExistA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDoesSiteExist]
  end;
end;
{$ELSE}
function WpDoesSiteExist; external wpapi_lib name 'WpDoesSiteExistA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpDeleteSite: Pointer;

function WpDeleteSite;
begin
  GetProcedureAddress(_WpDeleteSite, wpapi_lib, 'WpDeleteSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpDeleteSite]
  end;
end;
{$ELSE}
function WpDeleteSite; external wpapi_lib name 'WpDeleteSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpBindToSite: Pointer;

function WpBindToSite;
begin
  GetProcedureAddress(_WpBindToSite, wpapi_lib, 'WpBindToSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpBindToSite]
  end;
end;
{$ELSE}
function WpBindToSite; external wpapi_lib name 'WpBindToSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpCreateSite: Pointer;

function WpCreateSite;
begin
  GetProcedureAddress(_WpCreateSite, wpapi_lib, 'WpCreateSiteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpCreateSite]
  end;
end;
{$ELSE}
function WpCreateSite; external wpapi_lib name 'WpCreateSiteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpEnumProviders: Pointer;

function WpEnumProviders;
begin
  GetProcedureAddress(_WpEnumProviders, wpapi_lib, 'WpEnumProvidersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpEnumProviders]
  end;
end;
{$ELSE}
function WpEnumProviders; external wpapi_lib name 'WpEnumProvidersA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _WpGetErrorString: Pointer;

function WpGetErrorString;
begin
  GetProcedureAddress(_WpGetErrorString, wpapi_lib, 'WpGetErrorStringA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_WpGetErrorString]
  end;
end;
{$ELSE}
function WpGetErrorString; external wpapi_lib name 'WpGetErrorStringA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

end.
