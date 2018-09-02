{******************************************************************************}
{                                                       	               }
{ Background Intelligent Transfer API interface Unit for Object Pascal         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: bitscfg.h, released August 2001. The original Pascal   }
{ code is: Bits.pas, released October 2001. The initial developer of the       }
{ Pascal code is Wayne Sherman (body1233@yahoo.com).                           }
{                                                                              }
{ Portions created by Wayne Sherman are Copyright (C) 1999-2001                }
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

unit JwaBitscfg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "bitscfg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType;

const
  IID_IBITSExtensionSetup: TGUID = '{29cfbbf7-09e4-4b97-b0bc-f2287e3d8eb3}';
  {$EXTERNALSYM IID_IBITSExtensionSetup}

type
  REFIID = TGUID; // also in ActiveDS and another unit

  IBITSExtensionSetup = interface (IDispatch)
  ['{29cfbbf7-09e4-4b97-b0bc-f2287e3d8eb3}']
    function EnableBITSUploads: HRESULT; stdcall;
    function DisableBITSUploads: HRESULT; stdcall;
    function GetCleanupTaskName(out pTaskName: WideString): HRESULT; stdcall;
    function GetCleanupTask(riid: REFIID; out ppUnk: IUnknown): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IBITSExtensionSetup}

  IBITSExtensionSetupFactory = interface (IDispatch)
  ['{d5d2d542-5503-4e64-8b48-72ef91a32ee1}']
    function GetObject(Path: WideString; out ppExtensionSetup: IBITSExtensionSetup): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IBITSExtensionSetupFactory}


//---------------------------------------------------------------------------

const
  LIBID_BITSExtensionSetup: GUID = '{efbbab68-7286-4783-94bf-9461d8b7e7e9}';
  {$EXTERNALSYM LIBID_BITSExtensionSetup}
  CLSID_BITSExtensionSetupFactory: GUID = '{efbbab68-7286-4783-94bf-9461d8b7e7e9}';
  {$EXTERNALSYM CLSID_BITSExtensionSetupFactory}

implementation

end.
