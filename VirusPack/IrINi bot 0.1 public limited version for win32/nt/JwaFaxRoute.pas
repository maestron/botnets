{******************************************************************************}
{                                                       	               }
{  Fax Routing Extension API interface unit for Object Pascal                  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: faxroute.h, released November 2001. The original Pascal}
{ code is: FaxRoute.pas, released April 2002. The initial developer of the     }
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

unit JwaFaxRoute;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "faxroute.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
// microsoft routing guids
//

const
  MS_FAXROUTE_PRINTING_GUID = TEXT('{aec1b37c-9af2-11d0-abf7-00c04fd91a4e}');
  {$EXTERNALSYM MS_FAXROUTE_PRINTING_GUID}
  MS_FAXROUTE_FOLDER_GUID   = TEXT('{92041a90-9af2-11d0-abf7-00c04fd91a4e}');
  {$EXTERNALSYM MS_FAXROUTE_FOLDER_GUID}
  MS_FAXROUTE_EMAIL_GUID    = TEXT('{6bbf7bfe-9af2-11d0-abf7-00c04fd91a4e}');
  {$EXTERNALSYM MS_FAXROUTE_EMAIL_GUID}

//
// callback routines
//

type
  PFAXROUTEADDFILE = function (JobId: DWORD; FileName: LPCWSTR; Guid: LPGUID): LONG; stdcall;
  {$EXTERNALSYM PFAXROUTEADDFILE}
  PFAXROUTEDELETEFILE = function (JobId: DWORD; FileName: LPCWSTR): LONG; stdcall;
  {$EXTERNALSYM PFAXROUTEDELETEFILE}
  PFAXROUTEGETFILE = function (JobId, Index: DWORD; FileNameBuffer: LPWSTR; RequiredSize: LPDWORD): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEGETFILE}
  PFAXROUTEENUMFILE = function (JobId: DWORD; GuidOwner, GuidCaller: LPGUID; FileName: LPCWSTR; Context: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEENUMFILE}
  PFAXROUTEENUMFILES = function (JobId: DWORD; Guid: LPGUID; FileEnumerator: PFAXROUTEENUMFILE; Context: PVOID): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEENUMFILES}
  PFAXROUTEMODIFYROUTINGDATA = function (JobId: DWORD; RoutingGuid: LPCWSTR; RoutingData: LPBYTE; RoutingDataSize: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEMODIFYROUTINGDATA}

  PFAX_ROUTE_CALLBACKROUTINES = ^FAX_ROUTE_CALLBACKROUTINES;
  {$EXTERNALSYM PFAX_ROUTE_CALLBACKROUTINES}
  _FAX_ROUTE_CALLBACKROUTINES = record
    SizeOfStruct: DWORD; // size of the struct set by the fax service
    FaxRouteAddFile: PFAXROUTEADDFILE;
    FaxRouteDeleteFile: PFAXROUTEDELETEFILE;
    FaxRouteGetFile: PFAXROUTEGETFILE;
    FaxRouteEnumFiles: PFAXROUTEENUMFILES;
    FaxRouteModifyRoutingData: PFAXROUTEMODIFYROUTINGDATA;
  end;
  {$EXTERNALSYM _FAX_ROUTE_CALLBACKROUTINES}
  FAX_ROUTE_CALLBACKROUTINES = _FAX_ROUTE_CALLBACKROUTINES;
  {$EXTERNALSYM FAX_ROUTE_CALLBACKROUTINES}
  TFaxRouteCallbackRoutines = FAX_ROUTE_CALLBACKROUTINES;
  PFaxRouteCallbackRoutines = PFAX_ROUTE_CALLBACKROUTINES;

//
// routing data structure
//

  PFAX_ROUTE = ^FAX_ROUTE;
  {$EXTERNALSYM PFAX_ROUTE}
  _FAX_ROUTE = record
    SizeOfStruct: DWORD; // size of the struct set by the fax service
    JobId: DWORD; // Fax job identifier
    ElapsedTime: DWORDLONG; // Elapsed time for whole fax job in Coordinated Universal Time (UTC)
    ReceiveTime: DWORDLONG; // Starting time for fax job in Coordinated Universal Time (UTC)
    PageCount: DWORD; // Number of pages received
    Csid: LPCWSTR; // Called station identifier
    Tsid: LPCWSTR; // Transmitting station identifier
    CallerId: LPCWSTR; // Caller id
    RoutingInfo: LPCWSTR; // Routing info such as DID, T.30-subaddress, etc.
    ReceiverName: LPCWSTR; // Receiver's name
    ReceiverNumber: LPCWSTR; // Receiver's fax number
    DeviceName: LPCWSTR; // Device name for the line that received the fax
    DeviceId: DWORD; // Permenant line identifier for the receiving device
    RoutingInfoData: LPBYTE; // Routing infor data to override configured info
    RoutingInfoDataSize: DWORD; // Size of routing info data
  end;
  {$EXTERNALSYM _FAX_ROUTE}
  FAX_ROUTE = _FAX_ROUTE;
  {$EXTERNALSYM FAX_ROUTE}
  TFaxRoute = FAX_ROUTE;
  PFaxRoute = PFAX_ROUTE;

  FAXROUTE_ENABLE = DWORD;
  {$EXTERNALSYM FAXROUTE_ENABLE}
  TFaxRouteEnabl = FAXROUTE_ENABLE;

const
  QUERY_STATUS = DWORD(-1);
  {$EXTERNALSYM QUERY_STATUS}
  STATUS_DISABLE = 0;
  {$EXTERNALSYM STATUS_DISABLE}
  STATUS_ENABLE = 1;
  {$EXTERNALSYM STATUS_ENABLE}

//
// prototypes
//

type
  PFAXROUTEINITIALIZE = function (HeapHandle: HANDLE; FaxRouteCallbackRoutines: PFAX_ROUTE_CALLBACKROUTINES): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEINITIALIZE}
  PFAXROUTEMETHOD = function (FaxRoute: PFAX_ROUTE; P: PVOID; D: LPDWORD): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEMETHOD}
  PFAXROUTEDEVICEENABLE = function (RoutingGuid: LPCWSTR; DeviceId: DWORD; Enabled: LONG): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEDEVICEENABLE}
  PFAXROUTEDEVICECHANGENOTIFICATION = function (DeviceId: DWORD; NewDevice: BOOL): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEDEVICECHANGENOTIFICATION}
  PFAXROUTEGETROUTINGINFO = function (RoutingGuid: LPCWSTR; DeviceId: DWORD; RoutingInfo: LPBYTE; RoutingInfoSize: LPDWORD): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTEGETROUTINGINFO}
  PFAXROUTESETROUTINGINFO = function (RoutingGuid: LPCWSTR; DeviceId: DWORD; RoutingInfo: LPBYTE; RoutingInfoSize: DWORD): BOOL; stdcall;
  {$EXTERNALSYM PFAXROUTESETROUTINGINFO}

implementation

end.
