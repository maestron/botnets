{******************************************************************************}
{                                                       	               }
{ BlueTooth API interface Unit for Object Pascal                               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Contributors: John Penman       			                       }
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

unit JWaBthSdpDef;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "bthsdpdef.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

type
  SDP_LARGE_INTEGER_16 = record
    LowPart: Int64;
    HighPart: Int64;
  end;
  {$EXTERNALSYM SDP_LARGE_INTEGER_16}
  PSDP_LARGE_INTEGER_16 = ^SDP_LARGE_INTEGER_16;
  {$EXTERNALSYM PSDP_LARGE_INTEGER_16}
  LPSDP_LARGE_INTEGER_16 = PSDP_LARGE_INTEGER_16;
  {$EXTERNALSYM LPSDP_LARGE_INTEGER_16}
  TSdpLargeInteger = SDP_LARGE_INTEGER_16;
  PSdpLargeInteger = PSDP_LARGE_INTEGER_16;

  SDP_ULARGE_INTEGER_16 = record
    LowPart: Int64;
    HighPart: Int64;
  end;
  {$EXTERNALSYM SDP_ULARGE_INTEGER_16}
  PSDP_ULARGE_INTEGER_16 = ^SDP_ULARGE_INTEGER_16;
  {$EXTERNALSYM PSDP_ULARGE_INTEGER_16}
  LPSDP_ULARGE_INTEGER_16 = PSDP_ULARGE_INTEGER_16;
  {$EXTERNALSYM LPSDP_ULARGE_INTEGER_16}
  TSdpULargeInteger16 = SDP_ULARGE_INTEGER_16;
  PSdpULargeInteger16 = PSDP_ULARGE_INTEGER_16;

  NodeContainerType = (NodeContainerTypeSequence, NodeContainerTypeAlternative);
  TNodeContainerType = NodeContainerType;

  SDP_ERROR = Word;
  {$EXTERNALSYM SDP_ERROR}
  PSDP_ERROR = ^SDP_ERROR;
  {$EXTERNALSYM PSDP_ERROR}
  TSdpError = SDP_ERROR;
  PSdpError = PSDP_ERROR;

type
  SDP_TYPE = DWORD;
  {$EXTERNALSYM SDP_TYPE}
  TSdpType = SDP_TYPE;

const
  SDP_TYPE_NIL = $00;
  {$EXTERNALSYM SDP_TYPE_NIL}
  SDP_TYPE_UINT = $01;
  {$EXTERNALSYM SDP_TYPE_UINT}
  SDP_TYPE_INT = $02;
  {$EXTERNALSYM SDP_TYPE_INT}
  SDP_TYPE_UUID = $03;
  {$EXTERNALSYM SDP_TYPE_UUID}
  SDP_TYPE_STRING = $04;
  {$EXTERNALSYM SDP_TYPE_STRING}
  SDP_TYPE_BOOLEAN = $05;
  {$EXTERNALSYM SDP_TYPE_BOOLEAN}
  SDP_TYPE_SEQUENCE = $06;
  {$EXTERNALSYM SDP_TYPE_SEQUENCE}
  SDP_TYPE_ALTERNATIVE = $07;
  {$EXTERNALSYM SDP_TYPE_ALTERNATIVE}
  SDP_TYPE_URL = $08;
  {$EXTERNALSYM SDP_TYPE_URL}
  // 9 - 31 are reserved
  SDP_TYPE_CONTAINER = $20;
  {$EXTERNALSYM SDP_TYPE_CONTAINER}

// allow for a little easier type checking / sizing for integers and UUIDs
// ((SDP_ST_XXX & 0xF0) >> 4) == SDP_TYPE_XXX
// size of the data (in bytes) is encoded as ((SDP_ST_XXX & 0xF0) >> 8)

type
  SDP_SPECIFICTYPE = DWORD;
  {$EXTERNALSYM SDP_SPECIFICTYPE}
  TSdpSpecificType = SDP_SPECIFICTYPE;

const
  SDP_ST_NONE = $0000;
  {$EXTERNALSYM SDP_ST_NONE}

  SDP_ST_UINT8 = $0010;
  {$EXTERNALSYM SDP_ST_UINT8}
  SDP_ST_UINT16 = $0110;
  {$EXTERNALSYM SDP_ST_UINT16}
  SDP_ST_UINT32 = $0210;
  {$EXTERNALSYM SDP_ST_UINT32}
  SDP_ST_UINT64 = $0310;
  {$EXTERNALSYM SDP_ST_UINT64}
  SDP_ST_UINT128 = $0410;
  {$EXTERNALSYM SDP_ST_UINT128}

  SDP_ST_INT8 = $0020;
  {$EXTERNALSYM SDP_ST_INT8}
  SDP_ST_INT16 = $0120;
  {$EXTERNALSYM SDP_ST_INT16}
  SDP_ST_INT32 = $0220;
  {$EXTERNALSYM SDP_ST_INT32}
  SDP_ST_INT64 = $0320;
  {$EXTERNALSYM SDP_ST_INT64}
  SDP_ST_INT128 = $0420;
  {$EXTERNALSYM SDP_ST_INT128}

  SDP_ST_UUID16 = $0130;
  {$EXTERNALSYM SDP_ST_UUID16}
  SDP_ST_UUID32 = $0220;
  {$EXTERNALSYM SDP_ST_UUID32}
  SDP_ST_UUID128 = $0430;
  {$EXTERNALSYM SDP_ST_UUID128}

type
  _SdpAttributeRange = record
    minAttribute: Word;
    maxAttribute: Word;
  end;
  {$EXTERNALSYM _SdpAttributeRange}
  SdpAttributeRange = _SdpAttributeRange;
  {$EXTERNALSYM SdpAttributeRange}
  TSdpAttributeRange = SdpAttributeRange;

  SdpQueryUuidUnion = record
    case Integer of
      0: (uuid128: TGUID);
      1: (uuid32: ULONG);
      2: (uuid16: Word);
  end;
  TSdpQueryUuidUnion = SdpQueryUuidUnion;

  _SdpQueryUuid = record
    u: SdpQueryUuidUnion;
    uuidType: Word;
  end;
  {$EXTERNALSYM _SdpQueryUuid}
  SdpQueryUuid = _SdpQueryUuid;
  {$EXTERNALSYM SdpQueryUuid}
  TSdpQueryUuid = SdpQueryUuid;

implementation

end.
