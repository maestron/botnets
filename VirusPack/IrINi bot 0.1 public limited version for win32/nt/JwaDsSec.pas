{******************************************************************************}
{                                                       	               }
{ AD Security Property Pages API interface Unit for Object Pascal              }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dssec.h, released Feb 2003. The original Pascal        }
{ code is: DsSec.pas, released December 2003. The initial developer of the     }
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

unit JwaDsSec;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dssec.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinNT, JwaPrSht;

//+---------------------------------------------------------------------------
//
//  Function:   PFNREADOBJECTSECURITY
//
//  Synopsis:   Reads the security descriptor of a DS object
//
//  Arguments:  [IN  LPCWSTR]               --  ADS path of DS Object
//              [IN  SECURITY_INFORMATION]  --  Which SD parts to read
//              [OUT PSECURITY_DESCRIPTOR*] --  Return SD here. Caller frees with LocalFree
//              [IN  LPARAM]                --  Context param
//
//  Return:     HRESULT
//
//----------------------------------------------------------------------------
//
//  Function:   PFNWRITEOBJECTSECURITY
//
//  Synopsis:   Writes a security descriptor to a DS object
//
//  Arguments:  [IN  LPCWSTR]               --  ADS path of DS Object
//              [IN  SECURITY_INFORMATION]  --  Which SD parts to write
//              [OUT PSECURITY_DESCRIPTOR]  --  Security descriptor to write
//              [IN  LPARAM]                --  Context param
//
//  Return:     HRESULT
//
//----------------------------------------------------------------------------

type
  PFNREADOBJECTSECURITY = function (p1: LPCWSTR; p2: SECURITY_INFORMATION; p3: PPSECURITY_DESCRIPTOR; p4: LPARAM): HRESULT; stdcall;
  {$EXTERNALSYM PFNREADOBJECTSECURITY}
  PFNWRITEOBJECTSECURITY = function (p1: LPCWSTR; p2: SECURITY_INFORMATION; p3: PSECURITY_DESCRIPTOR; p4: LPARAM): HRESULT; stdcall;
  {$EXTERNALSYM PFNWRITEOBJECTSECURITY}

const
  DSSI_READ_ONLY           = $00000001;
  {$EXTERNALSYM DSSI_READ_ONLY}
  DSSI_NO_ACCESS_CHECK     = $00000002;
  {$EXTERNALSYM DSSI_NO_ACCESS_CHECK}
  DSSI_NO_EDIT_SACL        = $00000004;
  {$EXTERNALSYM DSSI_NO_EDIT_SACL}
  DSSI_NO_EDIT_OWNER       = $00000008;
  {$EXTERNALSYM DSSI_NO_EDIT_OWNER}
  DSSI_IS_ROOT             = $00000010;
  {$EXTERNALSYM DSSI_IS_ROOT}
  DSSI_NO_FILTER           = $00000020;
  {$EXTERNALSYM DSSI_NO_FILTER}
  DSSI_NO_READONLY_MESSAGE = $00000040;
  {$EXTERNALSYM DSSI_NO_READONLY_MESSAGE}

//+---------------------------------------------------------------------------
//
//  Function:   DSCreateSecurityPage
//
//  Synopsis:   Creates a Security property page for a DS object
//
//  Arguments:  [IN  pwszObjectPath]    --  Full ADS path of DS object
//              [IN  pwszObjectClass]   --  Class of the object (optional)
//              [IN  dwFlags]           --  Combination of DSSI_* flags
//              [OUT phPage]            --  HPROPSHEETPAGE returned here
//              [IN  pfnReadSD]         --  Optional function for reading SD
//              [IN  pfnWriteSD]        --  Optional function for writing SD
//              [IN  LPARAM]            --  Passed to pfnReadSD/pfnWriteSD
//
//  Return:     HRESULT
//
//----------------------------------------------------------------------------

function DSCreateSecurityPage(
  pwszObjectPath: LPCWSTR;
  pwszObjectClass: LPCWSTR;
  dwFlags: DWORD;
  out phPage: HPROPSHEETPAGE;
  pfnReadSD: PFNREADOBJECTSECURITY;
  pfnWriteSD: PFNWRITEOBJECTSECURITY;
  lpContext:LPARAM): HRESULT; stdcall;
{$EXTERNALSYM DSCreateSecurityPage}

type
  PFNDSCREATESECPAGE = function(
    pwszObjectPath: LPCWSTR;
    pwszObjectClass: LPCWSTR;
    dwFlags: DWORD;
    out phPage: HPROPSHEETPAGE;
    pfnReadSD: PFNREADOBJECTSECURITY;
    pfnWriteSD: PFNWRITEOBJECTSECURITY;
    lpContext:LPARAM): HRESULT; stdcall;
  {$EXTERNALSYM PFNDSCREATESECPAGE}

implementation

function DSCreateSecurityPage; external 'dssec.dll' name 'DSCreateSecurityPage';

end.
