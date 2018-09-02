{******************************************************************************}
{                                                       	               }
{ Winsock2 AppleTalk API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: atalkwsh.h, released June 2000. The original Pascal    }
{ code is: ATalkWsh.pas, released December 2000. The initial developer of the  }
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

unit JwaAtalkWsh;

interface

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "atalkwsh.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

uses
  JwaWinSock2;

//
//  All protocol types should be specified in the Decimal base
//

const
  DECIMAL_BASE = 10;
  {$EXTERNALSYM DECIMAL_BASE}

//
//  Protocol number 0 is invalid in the Appletalk case
//

  ATPROTO_BASE    = (1000 * AF_APPLETALK);
  {$EXTERNALSYM ATPROTO_BASE}
  SOL_APPLETALK   = (ATPROTO_BASE);
  {$EXTERNALSYM SOL_APPLETALK}

  DDPPROTO_RTMP   = (ATPROTO_BASE + 1);
  {$EXTERNALSYM DDPPROTO_RTMP}
  DDPPROTO_NBP    = (ATPROTO_BASE + 2);
  {$EXTERNALSYM DDPPROTO_NBP}
  DDPPROTO_ATP    = (ATPROTO_BASE + 3);
  {$EXTERNALSYM DDPPROTO_ATP}
  DDPPROTO_AEP    = (ATPROTO_BASE + 4);
  {$EXTERNALSYM DDPPROTO_AEP}
  DDPPROTO_RTMPRQ = (ATPROTO_BASE + 5);
  {$EXTERNALSYM DDPPROTO_RTMPRQ}
  DDPPROTO_ZIP    = (ATPROTO_BASE + 6);
  {$EXTERNALSYM DDPPROTO_ZIP}
  DDPPROTO_ADSP   = (ATPROTO_BASE + 7);
  {$EXTERNALSYM DDPPROTO_ADSP}

  DDPPROTO_MAX    = (ATPROTO_BASE + 255);
  {$EXTERNALSYM DDPPROTO_MAX}

//
//  Define the higher layer appletalk protocol types
//

  ATPROTO_ADSP = (DDPPROTO_MAX + 1);
  {$EXTERNALSYM ATPROTO_ADSP}
  ATPROTO_ATP  = (DDPPROTO_MAX + 2);
  {$EXTERNALSYM ATPROTO_ATP}
  ATPROTO_ASP  = (DDPPROTO_MAX + 3);
  {$EXTERNALSYM ATPROTO_ASP}
  ATPROTO_PAP  = (DDPPROTO_MAX + 4);
  {$EXTERNALSYM ATPROTO_PAP}

  SO_REGISTER_NAME            = $A000;
  {$EXTERNALSYM SO_REGISTER_NAME}
  SO_DEREGISTER_NAME          = $A001;
  {$EXTERNALSYM SO_DEREGISTER_NAME}
  SO_REMOVE_NAME              = SO_DEREGISTER_NAME;
  {$EXTERNALSYM SO_REMOVE_NAME}
  SO_LOOKUP_NAME              = $A002;
  {$EXTERNALSYM SO_LOOKUP_NAME}
  SO_CONFIRM_NAME             = $A003;
  {$EXTERNALSYM SO_CONFIRM_NAME}
  SO_LOOKUP_MYZONE            = $A004;
  {$EXTERNALSYM SO_LOOKUP_MYZONE}
  SO_GETMYZONE                = SO_LOOKUP_MYZONE;
  {$EXTERNALSYM SO_GETMYZONE}
  SO_LOOKUP_ZONES             = $A005;
  {$EXTERNALSYM SO_LOOKUP_ZONES}
  SO_GETZONELIST              = SO_LOOKUP_ZONES;
  {$EXTERNALSYM SO_GETZONELIST}
  SO_LOOKUP_ZONES_ON_ADAPTER  = $A006;
  {$EXTERNALSYM SO_LOOKUP_ZONES_ON_ADAPTER}
  SO_GETLOCALZONES            = SO_LOOKUP_ZONES_ON_ADAPTER;
  {$EXTERNALSYM SO_GETLOCALZONES}
  SO_LOOKUP_NETDEF_ON_ADAPTER = $A007;
  {$EXTERNALSYM SO_LOOKUP_NETDEF_ON_ADAPTER}
  SO_GETNETINFO               = SO_LOOKUP_NETDEF_ON_ADAPTER;
  {$EXTERNALSYM SO_GETNETINFO}

//
//  PAP-specific options
//

  SO_PAP_SET_SERVER_STATUS = $A007;
  {$EXTERNALSYM SO_PAP_SET_SERVER_STATUS}
  SO_PAP_GET_SERVER_STATUS = $A008;
  {$EXTERNALSYM SO_PAP_GET_SERVER_STATUS}
  SO_PAP_PRIME_READ        = $A009;
  {$EXTERNALSYM SO_PAP_PRIME_READ}

  ATADDR_ANY       = 0; // Dynamic socket (=0)
  {$EXTERNALSYM ATADDR_ANY}
  ATADDR_BROADCAST = $FF; // Broadcast node id (=ff)
  {$EXTERNALSYM ATADDR_BROADCAST}

//
//	Define flags/error codes peculiar to Appletalk
//

  WSAEMSGPARTIAL = (WSABASEERR + 100);
  {$EXTERNALSYM WSAEMSGPARTIAL}


//	Maximum pap status size

  MAX_PAP_STATUS_SIZE   = 255;
  {$EXTERNALSYM MAX_PAP_STATUS_SIZE}
  MIN_PAP_READ_BUF_SIZE = 4096;
  {$EXTERNALSYM MIN_PAP_READ_BUF_SIZE}

//	These are the unused 4 bytes returned in the PAP status packet. If ever
//	they are to be interpreted, they will be available.

  PAP_UNUSED_STATUS_BYTES = 4;
  {$EXTERNALSYM PAP_UNUSED_STATUS_BYTES}

//
//  SOCKADDR_AT structure
//

type
  SOCKADDR_AT = record
    sat_family: USHORT;
    sat_net: USHORT;
    sat_node: UCHAR;
    sat_socket: UCHAR;
  end;
  {$EXTERNALSYM SOCKADDR_AT}
  PSOCKADDR_AT = ^SOCKADDR_AT;
  {$EXTERNALSYM PSOCKADDR_AT}
  TSockAddrAT = SOCKADDR_AT;
  PSockAddrAT = PSOCKADDR_AT;  

//
//	***WARNING***
//	This is defined to be the same as the ATALK ADDRESS defined in atalktdi.h
//	Change this if the other changes.
//

type
  WSH_ATALK_ADDRESS = record
    case Integer of
      0: (
        Network: USHORT;
        Node: UCHAR;
        Socket: UCHAR);
      1: (
        Address: ULONG);
  end;
  {$EXTERNALSYM WSH_ATALK_ADDRESS}
  PWSH_ATALK_ADDRESS = ^WSH_ATALK_ADDRESS;
  {$EXTERNALSYM PWSH_ATALK_ADDRESS}
  TWSHATalkAddress = WSH_ATALK_ADDRESS;
  PWSHATalkAddress = PWSH_ATALK_ADDRESS;  

//
//  Typedefs for the various options
//

//
//  ***WARNING***:
//  This should be exactly the same as NBP_NAME defined in atalktdi.h
//

const
  MAX_ENTITY = 32;
  {$EXTERNALSYM MAX_ENTITY}

type
  WSH_NBP_NAME = record
    ObjectNameLen: CHAR;
    ObjectName: array [0..MAX_ENTITY - 1] of CHAR;
    TypeNameLen: CHAR;
    TypeName: array [0..MAX_ENTITY - 1] of CHAR;
    ZoneNameLen: CHAR;
    ZoneName: array [0..MAX_ENTITY - 1] of CHAR;
  end;
  {$EXTERNALSYM WSH_NBP_NAME}
  PWSH_NBP_NAME = ^WSH_NBP_NAME;
  {$EXTERNALSYM PWSH_NBP_NAME}
  TWSHNBPName = WSH_NBP_NAME;
  PWSHNBPName = PWSH_NBP_NAME;

  WSH_NBP_TUPLE = record
    Address: WSH_ATALK_ADDRESS;
    Enumerator: USHORT;
    NbpName: WSH_NBP_NAME;
  end;
  {$EXTERNALSYM WSH_NBP_TUPLE}
  PWSH_NBP_TUPLE = ^WSH_NBP_TUPLE;
  {$EXTERNALSYM PWSH_NBP_TUPLE}
  TWSHNBPTuple = WSH_NBP_TUPLE;
  PWSHNBPTuple = PWSH_NBP_TUPLE;  

  WSH_REGISTER_NAME = WSH_NBP_NAME;
  {$EXTERNALSYM WSH_REGISTER_NAME}
  TWSHRegisterName = WSH_REGISTER_NAME;
  PWSH_REGISTER_NAME = ^WSH_NBP_NAME;
  {$EXTERNALSYM PWSH_REGISTER_NAME}
  PWSHRegisterName = PWSH_REGISTER_NAME;
  WSH_DEREGISTER_NAME = WSH_NBP_NAME;
  {$EXTERNALSYM WSH_DEREGISTER_NAME}
  TWSHDeregisterName = WSH_DEREGISTER_NAME;
  PWSH_DEREGISTER_NAME = ^WSH_NBP_NAME;
  {$EXTERNALSYM PWSH_DEREGISTER_NAME}
  PWSHDeregisterName = PWSH_DEREGISTER_NAME;
  WSH_REMOVE_NAME = WSH_NBP_NAME;
  {$EXTERNALSYM WSH_REMOVE_NAME}
  TWSHRemoveName = WSH_REMOVE_NAME;
  PWSH_REMOVE_NAME = ^WSH_NBP_NAME;
  {$EXTERNALSYM PWSH_REMOVE_NAME}
  PWSHRemoveName = PWSH_REMOVE_NAME;

  _WSH_LOOKUP_ZONES = record
    NoZones: ULONG;
    //
    //  CHAR    Zones[] - null separated zones
    //
  end;
  {$EXTERNALSYM _WSH_LOOKUP_ZONES}
  WSH_LOOKUP_ZONES = _WSH_LOOKUP_ZONES;
  {$EXTERNALSYM WSH_LOOKUP_ZONES}
  PWSH_LOOKUP_ZONES = ^WSH_LOOKUP_ZONES;
  {$EXTERNALSYM PWSH_LOOKUP_ZONES}
  TWSHLookupZones = WSH_LOOKUP_ZONES;
  PWSHLookupZones = PWSH_LOOKUP_ZONES;

  _WSH_LOOKUP_NETDEF_ON_ADAPTER = record
    NetworkRangeLowerEnd: USHORT;
    NetworkRangeUpperEnd: USHORT;
    // This will be followed by a null terminated ansi default zone.
    // PUCHAR DefaultZone[]
  end;
  {$EXTERNALSYM _WSH_LOOKUP_NETDEF_ON_ADAPTER}
  WSH_LOOKUP_NETDEF_ON_ADAPTER = _WSH_LOOKUP_NETDEF_ON_ADAPTER;
  {$EXTERNALSYM WSH_LOOKUP_NETDEF_ON_ADAPTER}
  PWSH_LOOKUP_NETDEF_ON_ADAPTER = ^WSH_LOOKUP_NETDEF_ON_ADAPTER;
  {$EXTERNALSYM PWSH_LOOKUP_NETDEF_ON_ADAPTER}
  TWSHLookupNetDefOnAdapter = WSH_LOOKUP_NETDEF_ON_ADAPTER;
  PWSHLookupNetDefOnAdapter = PWSH_LOOKUP_NETDEF_ON_ADAPTER;

  _WSH_LOOKUP_NAME = record
    LookupTuple: WSH_NBP_TUPLE;
    NoTuples: ULONG;
    //
    //  Array of NoTuple WSH_NBP_TUPLEs
    //
  end;
  {$EXTERNALSYM _WSH_LOOKUP_NAME}
  WSH_LOOKUP_NAME = _WSH_LOOKUP_NAME;
  {$EXTERNALSYM WSH_LOOKUP_NAME}
  PWSH_LOOKUP_NAME = ^WSH_LOOKUP_NAME;
  {$EXTERNALSYM PWSH_LOOKUP_NAME}
  TWSHLookupName = WSH_LOOKUP_NAME;
  PWSHLookupName = PWSH_LOOKUP_NAME;

  _WSH_PAP_GET_SERVER_STATUS = record
    ServerAddr: SOCKADDR_AT;
    Reserved: array [0..PAP_UNUSED_STATUS_BYTES - 1] of UCHAR;
    ServerStatus: array [0..MAX_PAP_STATUS_SIZE] of UCHAR;
  end;
  {$EXTERNALSYM _WSH_PAP_GET_SERVER_STATUS}
  WSH_PAP_GET_SERVER_STATUS = _WSH_PAP_GET_SERVER_STATUS;
  {$EXTERNALSYM WSH_PAP_GET_SERVER_STATUS}
  PWSH_PAP_GET_SERVER_STATUS = ^WSH_PAP_GET_SERVER_STATUS;
  {$EXTERNALSYM PWSH_PAP_GET_SERVER_STATUS}
  TWSHPapGetServerStatus = WSH_PAP_GET_SERVER_STATUS;
  PWSHPapGetServerStatus = PWSH_PAP_GET_SERVER_STATUS;

implementation

end.
