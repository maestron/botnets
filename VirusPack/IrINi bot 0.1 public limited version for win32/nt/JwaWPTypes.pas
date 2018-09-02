{******************************************************************************}
{                                                       	               }
{ Web Publishing Type Declarations API interface Unit for Object Pascal        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wptypes.h, released June 2000. The original Pascal     }
{ code is: WPTypes.pas, released December 2000. The initial developer of the   }
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

unit JwaWPTypes;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wptypes.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
//	Site info structures
//

type
  LPWPSITEINFOA = ^WPSITEINFOA;
  {$EXTERNALSYM LPWPSITEINFOA}
  tagWPSITEINFOA = record
    dwSize: DWORD;
    dwFlags: DWORD;
    lpszSiteName: LPSTR;
    lpszSiteURL: LPSTR;
  end;
  {$EXTERNALSYM tagWPSITEINFOA}
  WPSITEINFOA = tagWPSITEINFOA;
  {$EXTERNALSYM WPSITEINFOA}
  TWpSiteInfoA = WPSITEINFOA;
  PWpSiteInfoA = LPWPSITEINFOA;

  LPWPSITEINFOW = ^WPSITEINFOW;
  {$EXTERNALSYM LPWPSITEINFOW}
  tagWPSITEINFOW = record
    dwSize: DWORD;
    dwFlags: DWORD;
    lpszSiteName: LPWSTR;
    lpszSiteURL: LPWSTR;
  end;
  {$EXTERNALSYM tagWPSITEINFOW}
  WPSITEINFOW = tagWPSITEINFOW;
  {$EXTERNALSYM WPSITEINFOW}
  TWpSiteInfoW = WPSITEINFOW;
  PWpSiteInfoW = LPWPSITEINFOW;

//
//	Provider info structures
//

  LPWPPROVINFOA = ^WPPROVINFOA;
  {$EXTERNALSYM LPWPPROVINFOA}
  tagWPPROVINFOA = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwPriority: DWORD;
    lpszProviderName: LPSTR;
    lpszProviderCLSID: LPSTR;
    lpszDllPath: LPSTR;
  end;
  {$EXTERNALSYM tagWPPROVINFOA}
  WPPROVINFOA = tagWPPROVINFOA;
  {$EXTERNALSYM WPPROVINFOA}
  TWpProvInfoA = WPPROVINFOA;
  PWpProvInfoA = LPWPPROVINFOA;

  LPWPPROVINFOW = ^WPPROVINFOW;
  {$EXTERNALSYM LPWPPROVINFOW}
  tagWPPROVINFOW = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwPriority: DWORD;
    lpszProviderName: LPWSTR;
    lpszProviderCLSID: LPWSTR;
    lpszDllPath: LPWSTR;
  end;
  {$EXTERNALSYM tagWPPROVINFOW}
  WPPROVINFOW = tagWPPROVINFOW;
  {$EXTERNALSYM WPPROVINFOW}
  TWpProvInfoW = WPPROVINFOW;
  PWpProvInfoW = LPWPPROVINFOW;

{$IFDEF UNICODE}

  WPSITEINFO = WPSITEINFOW;
  {$EXTERNALSYM WPSITEINFO}
  LPWPSITEINFO = LPWPSITEINFOW;
  {$EXTERNALSYM LPWPSITEINFO}
  TWpSiteInfo = TWpSiteInfoW;
  PWpSiteInfo = PWpSiteInfoW;
  WPPROVINFO = WPPROVINFOW;
  {$EXTERNALSYM WPPROVINFO}
  LPWPPROVINFO = LPWPPROVINFOW;
  {$EXTERNALSYM LPWPPROVINFO}
  TWpProvInfo = TWpProvInfoW;
  PWpProvInfo = PWpProvInfoW;

{$ELSE}

  WPSITEINFO = WPSITEINFOA;
  {$EXTERNALSYM WPSITEINFO}
  LPWPSITEINFO = LPWPSITEINFOA;
  {$EXTERNALSYM LPWPSITEINFO}
  TWpSiteInfo = TWpSiteInfoA;
  PWpSiteInfo = PWpSiteInfoA;
  WPPROVINFO = WPPROVINFOA;
  {$EXTERNALSYM WPPROVINFO}
  LPWPPROVINFO = LPWPPROVINFOA;
  {$EXTERNALSYM LPWPPROVINFO}
  TWpProvInfo = TWpProvInfoA;
  PWpProvInfo = PWpProvInfoA;

{$ENDIF}

implementation

end.
