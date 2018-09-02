{******************************************************************************}
{                                                       	               }
{ Web Publishing SPI Helper API interface Unit for Object Pascal               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wpspihlp.h, released June 2000. The original Pascal    }
{ code is: WPSpiHlp.pas, released December 2000. The initial developer of the  }
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

unit JwaWPSpiHlp;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wpspihlp.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWPTypes, JwaWinType;

//
//	Flags
//

const
  WPF_FORCE_BIND  = $00000100; // WppBindToSite

//
//	Helper function declarations and typedefs
//

//function WppBindToSiteA(hwnd: HWND; sSiteName, sURL: LPCSTR; const riid: TGUID;
//  dwFlag, dwReserved: DWORD; out ppvUnk): HRESULT; stdcall;
//{$EXTERNALSYM WppBindToSiteA}

type
  PFN_WPPBINDTOSITEA = function (hwnd: HWND; sSiteName, sURL: LPCSTR;
    const riid: TGUID; dwFlag, dwReserved: DWORD; out ppvUnk): HRESULT; stdcall;
  {$EXTERNALSYM PFN_WPPBINDTOSITEA}

//function WppListSitesA(var pdwSitesBufLen: DWORD; pSitesBuffer: LPWPSITEINFOA;
//  pdwNumSites: LPDWORD): HRESULT; stdcall;
//{$EXTERNALSYM WppListSitesA}

type
  PFN_WPPLISTSITESA = function (var pdwSitesBufLen: DWORD;
    pSitesBuffer: LPWPSITEINFOA; pdwNumSites: LPDWORD): HRESULT; stdcall;
  {$EXTERNALSYM PFN_WPPLISTSITESA}

//function WppDeleteSiteA(sSiteName: LPCSTR): HRESULT; stdcall;
//{$EXTERNALSYM WppDeleteSiteA}

type
  PFN_WPPDELETESITEA = function (sSiteName: LPCSTR): HRESULT; stdcall;
  {$EXTERNALSYM PFN_WPPDELETESITEA}

//function WppBindToSiteW(hwnd: HWND; sSiteName, sURL: LPCWSTR; const riid: TGUID;
//  dwFlag, dwReserved: DWORD; out ppvUnk): HRESULT; stdcall;
//{$EXTERNALSYM WppBindToSiteW}

type
  PFN_WPPBINDTOSITEW = function (hwnd: HWND; sSiteName, sURL: LPCWSTR;
    const riid: TGUID; dwFlag, dwReserved: DWORD; out ppvUnk): HRESULT; stdcall;
  {$EXTERNALSYM PFN_WPPBINDTOSITEW}

//function WppListSitesW(var pdwSitesBufLen: DWORD; pSitesBuffer: LPWPSITEINFOW;
//  pdwNumSites: LPDWORD): HRESULT; stdcall;
//{$EXTERNALSYM WppListSitesW}

type
  PFN_WPPLISTSITESW = function (var pdwSitesBufLen: DWORD;
    pSitesBuffer: LPWPSITEINFOW; pdwNumSites: LPDWORD): HRESULT; stdcall;
  {$EXTERNALSYM PFN_WPPLISTSITESW}

//function WppDeleteSiteW(sSiteName: LPCWSTR): HRESULT; stdcall;
//{$EXTERNALSYM WppDeleteSiteW}

type
  PFN_WPPDELETESITEW = function (sSiteName: LPCWSTR): HRESULT; stdcall;
  {$EXTERNALSYM PFN_WPPDELETESITEW}

//
//	Entry Points
//

const
  EP_WPPBINDTOSITEW  = 'WppBindToSiteW';
  {$EXTERNALSYM EP_WPPBINDTOSITEW}
  EP_WPPLISTSITESW   = 'WppListSitesW';
  {$EXTERNALSYM EP_WPPLISTSITESW}
  EP_WPPDELETESITEW  = 'WppDeleteSiteW';
  {$EXTERNALSYM EP_WPPDELETESITEW}

  EP_WPPBINDTOSITEA  = 'WppBindToSiteA';
  {$EXTERNALSYM EP_WPPBINDTOSITEA}
  EP_WPPLISTSITESA   = 'WppListSitesA';
  {$EXTERNALSYM EP_WPPLISTSITESA}
  EP_WPPDELETESITEA  = 'WppDeleteSiteA';
  {$EXTERNALSYM EP_WPPDELETESITEA}

implementation

end.
