{******************************************************************************}
{                                                       	               }
{ Image Mastering API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: imapi.h, released Aug 2002. The original Pascal        }
{ code is: Imapi.pas, released November 2002. The initial developer of the     }
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

unit JwaImapi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "imapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, ActiveX{todo};

//
// interface IDiscRecorder
//

type
  MEDIA_TYPES = DWORD;
  {$EXTERNALSYM MEDIA_TYPES}
  TMediaTypes = MEDIA_TYPES;

const
  MEDIA_CDDA_CDROM = 1;
  {$EXTERNALSYM MEDIA_CDDA_CDROM}
  MEDIA_CD_ROM_XA  = MEDIA_CDDA_CDROM + 1;
  {$EXTERNALSYM MEDIA_CD_ROM_XA}
  MEDIA_CD_I       = MEDIA_CD_ROM_XA + 1;
  {$EXTERNALSYM MEDIA_CD_I}
  MEDIA_CD_EXTRA   = MEDIA_CD_I + 1;
  {$EXTERNALSYM MEDIA_CD_EXTRA}
  MEDIA_CD_OTHER   = MEDIA_CD_EXTRA + 1;
  {$EXTERNALSYM MEDIA_CD_OTHER}
  MEDIA_SPECIAL    = MEDIA_CD_OTHER + 1;
  {$EXTERNALSYM MEDIA_SPECIAL}

type
  MEDIA_FLAGS = DWORD;
  {$EXTERNALSYM MEDIA_FLAGS}
  TMediaFlags = MEDIA_FLAGS;

const
  MEDIA_BLANK                    = $1;
  {$EXTERNALSYM MEDIA_BLANK}
  MEDIA_RW                       = $2;
  {$EXTERNALSYM MEDIA_RW}
  MEDIA_WRITABLE                 = $4;
  {$EXTERNALSYM MEDIA_WRITABLE}
  MEDIA_FORMAT_UNUSABLE_BY_IMAPI = $8;
  {$EXTERNALSYM MEDIA_FORMAT_UNUSABLE_BY_IMAPI}

type
  RECORDER_TYPES = DWORD;
  {$EXTERNALSYM RECORDER_TYPES}
  TRecorderTypes = RECORDER_TYPES;

const
  RECORDER_CDR  = $1;
  {$EXTERNALSYM RECORDER_CDR}
  RECORDER_CDRW = $2;
  {$EXTERNALSYM RECORDER_CDRW}

  RECORDER_DOING_NOTHING = 0;
  {$EXTERNALSYM RECORDER_DOING_NOTHING}

  RECORDER_OPENED = $1;
  {$EXTERNALSYM RECORDER_OPENED}

  RECORDER_BURNING = $2;
  {$EXTERNALSYM RECORDER_BURNING}

  IID_IDiscRecorder: TGUID = '{85AC9776-CA88-4cf2-894E-09598C078A41}';
  {$EXTERNALSYM IID_IDiscRecorder}

type
  IDiscRecorder = interface (IUnknown)
  ['{85AC9776-CA88-4cf2-894E-09598C078A41}']
    function Init(pbyUniqueID: PByte; nulIDSize, nulDriveNumber: ULONG): HRESULT; stdcall;
    function GetRecorderGUID(pbyUniqueID: PByte; ulBufferSize: ULONG; out pulReturnSizeRequired: ULONG): HRESULT; stdcall;
    function GetRecorderType(out fTypeCode: Longint): HRESULT; stdcall;
    function GetDisplayNames(var pbstrVendorID, pbstrProductID, pbstrRevision: PWideChar): HRESULT; stdcall;
    function GetBasePnPID(out pbstrBasePnPID: PWideChar): HRESULT; stdcall;
    function GetPath(out pbstrPath: PWideChar): HRESULT; stdcall;
    function GetRecorderProperties(out ppPropStg: IPropertyStorage): HRESULT; stdcall;
    function SetRecorderProperties(pPropStg: IPropertyStorage): HRESULT; stdcall;
    function GetRecorderState(out pulDevStateFlags: ULONG): HRESULT; stdcall;
    function OpenExclusive: HRESULT; stdcall;
    function QueryMediaType(out fMediaType, fMediaFlags: Longint): HRESULT; stdcall;
    function QueryMediaInfo(out pbSessions, pbLastTrack: Byte; out ulStartAddress, ulNextWritable, ulFreeBlocks: ULONG): HRESULT; stdcall;
    function Eject: HRESULT; stdcall;
    function Erase(bFullErase: BOOL): HRESULT; stdcall;
    function Close: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDiscRecorder}

//
// interface IEnumDiscRecorders
//

const
  IID_IEnumDiscRecorders: TGUID = '{9B1921E1-54AC-11d3-9144-00104BA11C5E}';
  {$EXTERNALSYM IID_IEnumDiscRecorders}

type
  IEnumDiscRecorders = interface (IUnknown)
  ['{9B1921E1-54AC-11d3-9144-00104BA11C5E}']
    function Next(cRecorders: ULONG; out ppRecorder: IDiscRecorder; out pcFetched: ULONG): HRESULT; stdcall;
    function Skip(cRecorders: ULONG): HRESULT; stdcall;
    function Reset: HRESULT; stdcall;
    function Clone(out ppEnum: IEnumDiscRecorders): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IEnumDiscRecorders}

//
// interface IEnumDiscMasterFormats
//

const
  IID_IEnumDiscMasterFormats: TGUID = '{DDF445E1-54BA-11d3-9144-00104BA11C5E}';
  {$EXTERNALSYM IID_IEnumDiscMasterFormats}

type
  IEnumDiscMasterFormats = interface (IUnknown)
  ['{DDF445E1-54BA-11d3-9144-00104BA11C5E}']
    function Next(cFormats: ULONG; out lpiidFormatID: TGUID; out pcFetched: ULONG): HRESULT; stdcall;
    function Skip(cFormats: ULONG): HRESULT; stdcall;
    function Reset: HRESULT; stdcall;
    function Clone(out ppEnum: IEnumDiscMasterFormats): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IEnumDiscMasterFormats}

//
// interface IRedbookDiscMaster
//

const
  IID_IRedbookDiscMaster: TGUID = '{E3BC42CD-4E5C-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM IID_IRedbookDiscMaster}

type
  IRedbookDiscMaster = interface (IUnknown)
  ['{E3BC42CD-4E5C-11D3-9144-00104BA11C5E}']
    function GetTotalAudioTracks(out pnTracks: Longint): HRESULT; stdcall;
    function GetTotalAudioBlocks(out pnBlocks: Longint): HRESULT; stdcall;
    function GetUsedAudioBlocks(out pnBlocks: Longint): HRESULT; stdcall;
    function GetAvailableAudioTrackBlocks(out pnBlocks: Longint): HRESULT; stdcall;
    function GetAudioBlockSize(out pnBlockBytes: Longint): HRESULT; stdcall;
    function CreateAudioTrack(nBlocks: Longint): HRESULT; stdcall;
    function AddAudioTrackBlocks(pby: PByte; cb: Longint): HRESULT; stdcall;
    function CloseAudioTrack: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IRedbookDiscMaster}

//
// interface IJolietDiscMaster
//

const
  IID_IJolietDiscMaster: TGUID = '{E3BC42CE-4E5C-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM IID_IJolietDiscMaster}

type
  IJolietDiscMaster = interface (IUnknown)
  ['{E3BC42CE-4E5C-11D3-9144-00104BA11C5E}']
    function GetTotalDataBlocks(out pnBlocks: Longint): HRESULT; stdcall;
    function GetUsedDataBlocks(out pnBlocks: Longint): HRESULT; stdcall;
    function GetDataBlockSize(out pnBlockBytes: Longint): HRESULT; stdcall;
    function AddData(pStorage: IStorage; lFileOverwrite: Longint): HRESULT; stdcall;
    function GetJolietProperties(out ppPropStg: IPropertyStorage): HRESULT; stdcall;
    function SetJolietProperties(pPropStg: IPropertyStorage): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IJolietDiscMaster}

//
// interface IDiscMasterProgressEvents
//

const
  IID_IDiscMasterProgressEvents: TGUID = '{EC9E51C1-4E5D-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM IID_IDiscMasterProgressEvents}

type
  IDiscMasterProgressEvents = interface (IUnknown)
  ['{EC9E51C1-4E5D-11D3-9144-00104BA11C5E}']
    function QueryCancel(out pbCancel: BOOL): HRESULT; stdcall;
    function NotifyPnPActivity: HRESULT; stdcall;
    function NotifyAddProgress(nCompletedSteps, nTotalSteps: Longint): HRESULT; stdcall;
    function NotifyBlockProgress(nCompleted, nTotal: Longint): HRESULT; stdcall;
    function NotifyTrackProgress(nCurrentTrack, nTotalTracks: Longint): HRESULT; stdcall;
    function NotifyPreparingBurn(nEstimatedSeconds: Longint): HRESULT; stdcall;
    function NotifyClosingDisc(nEstimatedSeconds: Longint): HRESULT; stdcall;
    function NotifyBurnComplete(status: HRESULT): HRESULT; stdcall;
    function NotifyEraseComplete(status: HRESULT): HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDiscMasterProgressEvents}

//
// interface IDiscMaster
//

const
  IID_IDiscMaster: TGUID = '{520CCA62-51A5-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM IID_IDiscMaster}

type
  IDiscMaster = interface (IUnknown)
  ['{520CCA62-51A5-11D3-9144-00104BA11C5E}']
    function Open: HRESULT; stdcall;
    function EnumDiscMasterFormats(out ppEnum: IEnumDiscMasterFormats): HRESULT; stdcall;
    function GetActiveDiscMasterFormat(out lpiid: TGUID): HRESULT; stdcall;
    function SetActiveDiscMasterFormat(const riid: TGUID; out ppUnk: IUnknown): HRESULT; stdcall;
    function EnumDiscRecorders(out ppEnum: IEnumDiscRecorders): HRESULT; stdcall;
    function GetActiveDiscRecorder(out ppRecorder: IDiscRecorder): HRESULT; stdcall;
    function SetActiveDiscRecorder(pRecorder: IDiscRecorder): HRESULT; stdcall;
    function ClearFormatContent: HRESULT; stdcall;
    function ProgressAdvise(pEvents: IDiscMasterProgressEvents; out pvCookie: UINT): HRESULT; stdcall;
    function ProgressUnadvise(vCookie: UINT): HRESULT; stdcall;
    function RecordDisc(bSimulate, bEjectAfterBurn: BOOL): HRESULT; stdcall;
    function Close: HRESULT; stdcall;
  end;
  {$EXTERNALSYM IDiscMaster}

//
// library IMAPILib
//

const
  //EXTERN_C const IID LIBID_IMAPILib;

  CLSID_MSDiscRecorderObj: TGUID = '{520CCA61-51A5-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM CLSID_MSDiscRecorderObj}
  MSDiscRecorderObj: TGUID = '{520CCA61-51A5-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM MSDiscRecorderObj}

  CLSID_MSDiscMasterObj: TGUID = '{520CCA63-51A5-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM CLSID_MSDiscMasterObj}
  MSDiscMasterObj: TGUID = '{520CCA63-51A5-11D3-9144-00104BA11C5E}';
  {$EXTERNALSYM MSDiscMasterObj}

  CLSID_MSEnumDiscRecordersObj: TGUID = '{8A03567A-63CB-4BA8-BAF6-52119816D1EF}';
  {$EXTERNALSYM CLSID_MSEnumDiscRecordersObj}
  MSEnumDiscRecordersObj: TGUID = '{8A03567A-63CB-4BA8-BAF6-52119816D1EF}';
  {$EXTERNALSYM MSEnumDiscRecordersObj}

implementation

end.
