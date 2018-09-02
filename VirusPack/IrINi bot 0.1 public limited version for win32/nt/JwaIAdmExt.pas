{******************************************************************************}
{                                                       	               }
{ IISAdmin Extensions API interface Unit for Object Pascal                     }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: iadmext.h, released November 2002. The original Pascal }
{ code is: IAdmExt.pas, released March 2002. The initial developer of the      }
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

unit JwaIAdmExt;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "iadmext.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaIisCnfg, JwaWinType;

//
// The Main Interface. All extensions must support this interface.
//
// {51DFE970-F6F2-11d0-B9BD-00A0C922E750}

const
  IID_IADMEXT: TGUID = (D1:$51dfe970; D2:$f6f2; D3:$11d0; D4:($b9, $bd, $0, $a0, $c9, $22, $e7, $50));
  {$EXTERNALSYM IID_IADMEXT}

//
// InProcess COM Registration. All extensions must write a subkey name by the
// CLSID for the above interface under this key in the Registry.
//

  IISADMIN_EXTENSIONS_REG_KEYA = 'SOFTWARE\Microsoft\InetStp\Extensions';
  {$EXTERNALSYM IISADMIN_EXTENSIONS_REG_KEYA}
  IISADMIN_EXTENSIONS_REG_KEYW = WideString('SOFTWARE\Microsoft\InetStp\Extensions');
  {$EXTERNALSYM IISADMIN_EXTENSIONS_REG_KEYW}
  IISADMIN_EXTENSIONS_REG_KEY  = TEXT('SOFTWARE\Microsoft\InetStp\Extensions');
  {$EXTERNALSYM IISADMIN_EXTENSIONS_REG_KEY}

//
// COM Registration. CLSIDS for the DCOM interface provided by these extensions will
// be written to this key and ID by IISADMIN as a multisz property.
//
// This is intended for use by other applications which need to find out what classid's are
// registered.
//

  IISADMIN_EXTENSIONS_CLSID_MD_KEYA = 'LM/IISADMIN/EXTENSIONS/DCOMCLSIDS';
  {$EXTERNALSYM IISADMIN_EXTENSIONS_CLSID_MD_KEYA}
  IISADMIN_EXTENSIONS_CLSID_MD_KEYW = WideString('LM/IISADMIN/EXTENSIONS/DCOMCLSIDS');
  {$EXTERNALSYM IISADMIN_EXTENSIONS_CLSID_MD_KEYW}
  IISADMIN_EXTENSIONS_CLSID_MD_KEY  = TEXT('LM/IISADMIN/EXTENSIONS/DCOMCLSIDS');
  {$EXTERNALSYM IISADMIN_EXTENSIONS_CLSID_MD_KEY}
  IISADMIN_EXTENSIONS_CLSID_MD_ID   = MD_IISADMIN_EXTENSIONS;
  {$EXTERNALSYM IISADMIN_EXTENSIONS_CLSID_MD_ID}

type
  IADMEXT = interface (IUnknown)
  ['{51DFE970-F6F2-11d0-B9BD-00A0C922E750}']
    //
    // All methods below will be called under a thread which has called
    // CoInitializeEx(NULL, COINIT_MULTITHREADED).
    //
    // The IMSAdminBase Object will be available during all of these calls.
    //

    //
    // Initialize will be called by IISADMIN when it initializes.
    //
    function Initialize: HRESULT; stdcall;

    //
    // EnumDcomCLSIDs will be called by IISADMIN when it initializes,
    // and the returned CLSIDs will be written to the metabase at
    // the path IISADMIN_EXTENSIONS_CLSID_MD_KEY.
    //
    function EnumDcomCLSIDs(var pclsidDcom: CLSID; dwEnumIndex: DWORD): HRESULT; stdcall;

    //
    // Terminate will be called by IISADMIN when it terminates.
    //
    function Terminate: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IADMEXT}

implementation

end.

