{******************************************************************************}
{                                                       	               }
{ Directory Services Query API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dsquery.h, released November 2002. The original Pascal }
{ code is: DSQuery.pas, released March 2002. The initial developer of the      }
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

unit JwaDSQuery;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dsquery.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaCmnQuery, JwaWinType;

const
  CLSID_DsQuery: TGUID = (D1:$8a23e65e; D2:$31c2; D3:$11d0; D4:($89, $1c, $0, $a0, $24, $ab, $2d, $bb));
  {$EXTERNALSYM CLSID_DsQuery}

//
// standard forms shipped in dsquery.dll
//

  CLSID_DsFindObjects: TGUID = (D1:$83ee3fe1; D2:$57d9; D3:$11d0; D4:($b9, $32, $0, $a0, $24, $ab, $2d, $bb));
  {$EXTERNALSYM CLSID_DsFindObjects}
  CLSID_DsFindPeople: TGUID = (D1:$83ee3fe2; D2:$57d9; D3:$11d0; D4:($b9, $32, $0, $a0, $24, $ab, $2d, $bb));
  {$EXTERNALSYM CLSID_DsFindPeople}
  CLSID_DsFindPrinter: TGUID = (D1:$b577f070; D2:$7ee2; D3:$11d0; D4:($91, $3f, $0, $aa, $0, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_DsFindPrinter}
  CLSID_DsFindComputer: TGUID = (D1:$16006700; D2:$87ad; D3:$11d0; D4:($91, $40, $0, $aa, $0, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_DsFindComputer}
  CLSID_DsFindVolume: TGUID = (D1:$c1b3cbf1; D2:$886a; D3:$11d0; D4:($91, $40, $0, $aa, $0, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_DsFindVolume}
  CLSID_DsFindContainer: TGUID = (D1:$c1b3cbf2; D2:$886a; D3:$11d0; D4:($91, $40, $0, $aa, $0, $c1, $6e, $65));
  {$EXTERNALSYM CLSID_DsFindContainer}
  CLSID_DsFindAdvanced: TGUID = (D1:$83ee3fe3; D2:$57d9; D3:$11d0; D4:($b9, $32, $0, $a0, $24, $ab, $2d, $bb));
  {$EXTERNALSYM CLSID_DsFindAdvanced}

//
// admin forms
//

  CLSID_DsFindDomainController: TGUID = (D1:$538c7b7e; D2:$d25e; D3:$11d0; D4:($97, $42, $0, $a0, $c9, $6, $af, $45));
  {$EXTERNALSYM CLSID_DsFindDomainController}
  CLSID_DsFindFrsMembers: TGUID = (D1:$94ce4b18; D2:$b3d3; D3:$11d1; D4:($b9, $b4, $0, $c0, $4f, $d8, $d5, $b0));
  {$EXTERNALSYM CLSID_DsFindFrsMembers}

{$IFNDEF GUID_DEFS_ONLY}

//
// DSQUERYINITPARAMS
// -----------------
//  This structured is used when creating a new query view.
//

const
  DSQPF_NOSAVE                 = $00000001; // = 1 => remove save verb
  {$EXTERNALSYM DSQPF_NOSAVE}
  DSQPF_SAVELOCATION           = $00000002; // = 1 => pSaveLocation contains directory to save queries into
  {$EXTERNALSYM DSQPF_SAVELOCATION}
  DSQPF_SHOWHIDDENOBJECTS      = $00000004; // = 1 => show objects marked as "hidden" in results
  {$EXTERNALSYM DSQPF_SHOWHIDDENOBJECTS}
  DSQPF_ENABLEADMINFEATURES    = $00000008; // = 1 => show admin verbs, property pages etc
  {$EXTERNALSYM DSQPF_ENABLEADMINFEATURES}
  DSQPF_ENABLEADVANCEDFEATURES = $00000010; // = 1 => set the advanced flag for the property pages
  {$EXTERNALSYM DSQPF_ENABLEADVANCEDFEATURES}
  DSQPF_HASCREDENTIALS         = $00000020; // = 1 => pServer, pUserName & pPassword are valid
  {$EXTERNALSYM DSQPF_HASCREDENTIALS}
  DSQPF_NOCHOOSECOLUMNS        = $00000040; // = 1 => remove choose columns from view
  {$EXTERNALSYM DSQPF_NOCHOOSECOLUMNS}

type
  LPDSQUERYINITPARAMS = ^DSQUERYINITPARAMS;
  {$EXTERNALSYM LPDSQUERYINITPARAMS}
  DSQUERYINITPARAMS = record
    cbStruct: DWORD;
    dwFlags: DWORD;
    pDefaultScope: LPWSTR; // -> Active Directory path to use as scope / == NULL for none
    pDefaultSaveLocation: LPWSTR; // -> Directory to save queries into / == NULL default location
    pUserName: LPWSTR; // -> user name to authenticate with
    pPassword: LPWSTR; // -> password for authentication
    pServer: LPWSTR; // -> server to use for obtaining trusts etc
  end;
  {$EXTERNALSYM DSQUERYINITPARAMS}
  TDsQueryInitParams = DSQUERYINITPARAMS;
  PDsQueryInitParams = LPDSQUERYINITPARAMS;

//
// DSQUERYPARAMS
// -------------
//  The DS query handle takes a packed structure which contains the
//  columns and query to be issued.
//

const
  CFSTR_DSQUERYPARAMS = TEXT('DsQueryParameters');
  {$EXTERNALSYM CFSTR_DSQUERYPARAMS}

  DSCOLUMNPROP_ADSPATH     = LONG(-1);
  {$EXTERNALSYM DSCOLUMNPROP_ADSPATH}
  DSCOLUMNPROP_OBJECTCLASS = LONG(-2);
  {$EXTERNALSYM DSCOLUMNPROP_OBJECTCLASS}

type
  LPDSCOLUMN = ^DSCOLUMN;
  {$EXTERNALSYM LPDSCOLUMN}
  DSCOLUMN = record
    dwFlags: DWORD; // flags for this column
    fmt: INT; // list view form information
    cx: INT; // default column width
    idsName: INT; // resource ID for the column dispaly name
    offsetProperty: LONG; // offset to BSTR defining column ADs property name
    dwReserved: DWORD; // reserved field
  end;
  {$EXTERNALSYM DSCOLUMN}
  TDsColumn = DSCOLUMN;
  PDsColumn = LPDSCOLUMN;

  LPDSQUERYPARAMS = ^DSQUERYPARAMS;
  {$EXTERNALSYM LPDSQUERYPARAMS}
  DSQUERYPARAMS = record
    cbStruct: DWORD;
    dwFlags: DWORD;
    hInstance: HINSTANCE; // instance handle used for string extraction
    offsetQuery: LONG; // offset to LDAP filter string
    iColumns: LONG; // column count
    dwReserved: DWORD; // reserved field for this query
    aColumns: array [0..0] of DSCOLUMN; // array of column descriptions
  end;
  {$EXTERNALSYM DSQUERYPARAMS}
  TDsQueryParams = DSQUERYPARAMS;
  PDsQueryParams = LPDSQUERYPARAMS;

//
// CF_DSQUERYSCOPE
// ---------------
//  A clipboard format the puts a string version of the scope into a
//  storage medium via GlobalAlloc.
//

const
  CFSTR_DSQUERYSCOPE = TEXT('DsQueryScope');
  {$EXTERNALSYM CFSTR_DSQUERYSCOPE}

//
// DSQPM_GETCLASSLIST
// ------------------
//  This page message is sent to the form pages to retrieve the list of classes
//  that the pages are going to query from.  This is used by the feild selector
//  and the property well to build its list of display classes.
//

type
  LPDSQUERYCLASSLIST = ^DSQUERYCLASSLIST;
  {$EXTERNALSYM LPDSQUERYCLASSLIST}
  DSQUERYCLASSLIST = record
    cbStruct: DWORD;
    cClasses: LONG; // number of classes in array
    offsetClass: array [0..0] of DWORD; // offset to the class names (UNICODE)
  end;
  {$EXTERNALSYM DSQUERYCLASSLIST}
  TDsQueryClassList = DSQUERYCLASSLIST;
  PDsQueryClassList = LPDSQUERYCLASSLIST;

const
  DSQPM_GETCLASSLIST = (CQPM_HANDLERSPECIFIC+0); // wParam == flags, lParam = LPLPDSQUERYCLASSLIST
  {$EXTERNALSYM DSQPM_GETCLASSLIST}

//
// DSQPM_HELPTOPICS
// ----------------
//  This page message is sent to the form pages to allow them to handle the
//  "Help Topics" verb.
//

  DSQPM_HELPTOPICS = (CQPM_HANDLERSPECIFIC+1); // wParam = 0, lParam = hWnd parent
  {$EXTERNALSYM DSQPM_HELPTOPICS}

{$ENDIF}

implementation

end.
