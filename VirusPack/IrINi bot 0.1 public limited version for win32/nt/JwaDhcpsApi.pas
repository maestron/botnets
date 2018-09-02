{******************************************************************************}
{                                                       	               }
{ DHCP Server Management API interface Unit for Object Pascal                  }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dhcpsapi.h, released Feb 2003. The original Pascal     }
{ code is: DhcpsApi.pas, released December 2003. The initial developer of the  }
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

unit JwaDhcpsApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dhcpsapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

type
  DHCP_IP_ADDRESS = DWORD;
  {$EXTERNALSYM DHCP_IP_ADDRESS}
  PDHCP_IP_ADDRESS = ^DHCP_IP_ADDRESS;
  {$EXTERNALSYM PDHCP_IP_ADDRESS}
  LPDHCP_IP_ADDRESS = ^DHCP_IP_ADDRESS;
  {$EXTERNALSYM LPDHCP_IP_ADDRESS}
  TDhcpIpAddress = DHCP_IP_ADDRESS;
  PDhcpIpAddress = ^DHCP_IP_ADDRESS;

  DHCP_IP_MASK = DWORD;
  {$EXTERNALSYM DHCP_IP_MASK}
  TDhcpIpMask = DHCP_IP_MASK;
  DHCP_RESUME_HANDLE = DWORD;
  {$EXTERNALSYM DHCP_RESUME_HANDLE}
  TDhcpResumeHandle = DHCP_RESUME_HANDLE;

  DHCP_OPTION_ID = DWORD;
  {$EXTERNALSYM DHCP_OPTION_ID}
  TDhcpOptionID = DHCP_OPTION_ID;

  _DATE_TIME = record
    dwLowDateTime: DWORD;
    dwHighDateTime: DWORD;
  end;
  {$EXTERNALSYM _DATE_TIME}
  DATE_TIME = _DATE_TIME;
  {$EXTERNALSYM DATE_TIME}
  LPDATE_TIME = ^DATE_TIME;
  {$EXTERNALSYM LPDATE_TIME}
  TDateTime = DATE_TIME;
  PDateTime = ^DATE_TIME;

  _DWORD_DWORD = record
    DWord1: DWORD;
    DWord2: DWORD;
  end;
  {$EXTERNALSYM _DWORD_DWORD}
  DWORD_DWORD = _DWORD_DWORD;
  {$EXTERNALSYM DWORD_DWORD}
  LPDWORD_DWORD = ^DWORD_DWORD;
  {$EXTERNALSYM LPDWORD_DWORD}
  TDwordDword = DWORD_DWORD;
  PDwordDword = ^DWORD_DWORD;

  _DHCP_BINARY_DATA = record
    DataLength: DWORD;
    Data: LPBYTE;
  end;
  {$EXTERNALSYM _DHCP_BINARY_DATA}
  DHCP_BINARY_DATA = _DHCP_BINARY_DATA;
  {$EXTERNALSYM DHCP_BINARY_DATA}
  LPDHCP_BINARY_DATA = ^DHCP_BINARY_DATA;
  {$EXTERNALSYM LPDHCP_BINARY_DATA}
  TDhcpBinaryData = DHCP_BINARY_DATA;
  PDhcpBinaryData = ^DHCP_BINARY_DATA;

  DHCP_CLIENT_UID = DHCP_BINARY_DATA;
  {$EXTERNALSYM DHCP_CLIENT_UID}
  TDhcpClientUid = DHCP_CLIENT_UID;

const
  DHCP_ENDPOINT_FLAG_CANT_MODIFY = $01;
  {$EXTERNALSYM DHCP_ENDPOINT_FLAG_CANT_MODIFY}

type
  _DHCP_BIND_ELEMENT = record
    Flags: ULONG;
    fBoundToDHCPServer: BOOL;
    AdapterPrimaryAddress: DHCP_IP_ADDRESS;
    AdapterSubnetAddress: DHCP_IP_ADDRESS;
    IfDescription: LPWSTR;
    IfIdSize: ULONG;
    IfId: LPBYTE;
  end;
  {$EXTERNALSYM _DHCP_BIND_ELEMENT}
  DHCP_BIND_ELEMENT = _DHCP_BIND_ELEMENT;
  {$EXTERNALSYM DHCP_BIND_ELEMENT}
  LPDHCP_BIND_ELEMENT = ^DHCP_BIND_ELEMENT;
  {$EXTERNALSYM LPDHCP_BIND_ELEMENT}
  TDhcpBindElement = DHCP_BIND_ELEMENT;
  PDhcpBindElement = ^DHCP_BIND_ELEMENT;

  _DHCP_BIND_ELEMENT_ARRAY = record
    NumElements: DWORD;
    Elements: LPDHCP_BIND_ELEMENT; //array
  end;
  {$EXTERNALSYM _DHCP_BIND_ELEMENT_ARRAY}
  DHCP_BIND_ELEMENT_ARRAY = _DHCP_BIND_ELEMENT_ARRAY;
  {$EXTERNALSYM DHCP_BIND_ELEMENT_ARRAY}
  LPDHCP_BIND_ELEMENT_ARRAY = ^DHCP_BIND_ELEMENT_ARRAY;
  {$EXTERNALSYM LPDHCP_BIND_ELEMENT_ARRAY}
  TDhcpBindElementArray = DHCP_BIND_ELEMENT_ARRAY;
  PDhcpBindElementArray = ^DHCP_BIND_ELEMENT_ARRAY;

  _DHCP_CLIENT_SEARCH_TYPE = (
    DhcpClientIpAddress,
    DhcpClientHardwareAddress,
    DhcpClientName);
  {$EXTERNALSYM _DHCP_CLIENT_SEARCH_TYPE}
  DHCP_SEARCH_INFO_TYPE = _DHCP_CLIENT_SEARCH_TYPE;
  {$EXTERNALSYM DHCP_SEARCH_INFO_TYPE}
  LPDHCP_SEARCH_INFO_TYPE = ^DHCP_SEARCH_INFO_TYPE;
  {$EXTERNALSYM LPDHCP_SEARCH_INFO_TYPE}
  TDhcpSearchInfoType = DHCP_SEARCH_INFO_TYPE;
  PDhcpSearchInfoType = ^DHCP_SEARCH_INFO_TYPE;

  _DHCP_CLIENT_SEARCH_UNION = record
    case Integer of
      0: (ClientIpAddress: DHCP_IP_ADDRESS);
      1: (ClientHardwareAddress: DHCP_CLIENT_UID);
      2: (ClientName: LPWSTR);
  end;
  {$EXTERNALSYM _DHCP_CLIENT_SEARCH_UNION}

  _DHCP_CLIENT_SEARCH_INFO = record
    SearchType: DHCP_SEARCH_INFO_TYPE;
    SearchInfo: _DHCP_CLIENT_SEARCH_UNION;
  end;
  {$EXTERNALSYM _DHCP_CLIENT_SEARCH_INFO}
  DHCP_SEARCH_INFO = _DHCP_CLIENT_SEARCH_INFO;
  {$EXTERNALSYM DHCP_SEARCH_INFO}
  LPDHCP_SEARCH_INFO = ^DHCP_SEARCH_INFO;
  {$EXTERNALSYM LPDHCP_SEARCH_INFO}
  TDhcpSearchInfo = DHCP_SEARCH_INFO;
  PDhcpSearchInfo = ^DHCP_SEARCH_INFO;

  _DHCP_OPTION_SCOPE_TYPE = (
    DhcpDefaultOptions,
    DhcpGlobalOptions,
    DhcpSubnetOptions,
    DhcpReservedOptions,
    DhcpMScopeOptions);
  {$EXTERNALSYM _DHCP_OPTION_SCOPE_TYPE}
  DHCP_OPTION_SCOPE_TYPE = _DHCP_OPTION_SCOPE_TYPE;
  {$EXTERNALSYM DHCP_OPTION_SCOPE_TYPE}
  LPDHCP_OPTION_SCOPE_TYPE = ^DHCP_OPTION_SCOPE_TYPE;
  {$EXTERNALSYM LPDHCP_OPTION_SCOPE_TYPE}
  TDhcpOptionScopeType = DHCP_OPTION_SCOPE_TYPE;
  PDhcpOptionScopeType = ^DHCP_OPTION_SCOPE_TYPE;

  _DHCP_RESERVED_SCOPE = record
    ReservedIpAddress: DHCP_IP_ADDRESS;
    ReservedIpSubnetAddress: DHCP_IP_ADDRESS;
  end;
  {$EXTERNALSYM _DHCP_RESERVED_SCOPE}
  DHCP_RESERVED_SCOPE = _DHCP_RESERVED_SCOPE;
  {$EXTERNALSYM DHCP_RESERVED_SCOPE}
  LPDHCP_RESERVED_SCOPE = ^DHCP_RESERVED_SCOPE;
  {$EXTERNALSYM LPDHCP_RESERVED_SCOPE}
  TDhcpReservedScope = DHCP_RESERVED_SCOPE;
  PDhcpReservedScope = ^DHCP_RESERVED_SCOPE;

  _DHCP_OPTION_SCOPE_UNION = record
    case Integer of
      0: (DefaultScopeInfo: PVOID); // must be NULL
      1: (GlobalScopeInfo: PVOID);  // must be NULL
      2: (SubnetScopeInfo: DHCP_IP_ADDRESS);
      3: (ReservedScopeInfo: DHCP_RESERVED_SCOPE);
      4: (MScopeInfo: LPWSTR);
  end;
  {$EXTERNALSYM _DHCP_OPTION_SCOPE_UNION}

  _DHCP_OPTION_SCOPE_INFO = record
    ScopeType: DHCP_OPTION_SCOPE_TYPE;
    ScopeInfo: _DHCP_OPTION_SCOPE_UNION;
  end;
  {$EXTERNALSYM _DHCP_OPTION_SCOPE_INFO}
  DHCP_OPTION_SCOPE_INFO = _DHCP_OPTION_SCOPE_INFO;
  {$EXTERNALSYM DHCP_OPTION_SCOPE_INFO}
  LPDHCP_OPTION_SCOPE_INFO = ^DHCP_OPTION_SCOPE_INFO;
  {$EXTERNALSYM LPDHCP_OPTION_SCOPE_INFO}
  TDhcpOptionScopeInfo = DHCP_OPTION_SCOPE_INFO;
  PDhcpOptionScopeInfo = ^DHCP_OPTION_SCOPE_INFO;

  _DHCP_HOST_INFO = record
    IpAddress: DHCP_IP_ADDRESS;      // minimum information always available
    NetBiosName: LPWSTR;             // optional information
    HostName: LPWSTR;                // optional information
  end;
  {$EXTERNALSYM _DHCP_HOST_INFO}
  DHCP_HOST_INFO = _DHCP_HOST_INFO;
  {$EXTERNALSYM DHCP_HOST_INFO}
  LPDHCP_HOST_INFO = ^DHCP_HOST_INFO;
  {$EXTERNALSYM LPDHCP_HOST_INFO}
  TDhcpHostInfo = DHCP_HOST_INFO;
  PDhcpHostInfo = ^DHCP_HOST_INFO;

  _DHCP_CLIENT_INFO = record
    ClientIpAddress: DHCP_IP_ADDRESS;    // currently assigned IP address.
    SubnetMask: DHCP_IP_MASK;
    ClientHardwareAddress: DHCP_CLIENT_UID;
    ClientName: LPWSTR;                  // optional.
    ClientComment: LPWSTR;
    ClientLeaseExpires: DATE_TIME;       // UTC time in FILE_TIME format.
    OwnerHost: DHCP_HOST_INFO;           // host that distributed this IP address.
  end;
  {$EXTERNALSYM _DHCP_CLIENT_INFO}
  DHCP_CLIENT_INFO = _DHCP_CLIENT_INFO;
  {$EXTERNALSYM DHCP_CLIENT_INFO}
  LPDHCP_CLIENT_INFO = ^DHCP_CLIENT_INFO;
  {$EXTERNALSYM LPDHCP_CLIENT_INFO}
  TDhcpClientInfo = DHCP_CLIENT_INFO;
  PDhcpClientInfo = ^DHCP_CLIENT_INFO;

  _DHCP_CLIENT_INFO_ARRAY = record
    NumElements: DWORD;
    Clients: ^LPDHCP_CLIENT_INFO; // array of pointers\
  end;
  {$EXTERNALSYM _DHCP_CLIENT_INFO_ARRAY}
  DHCP_CLIENT_INFO_ARRAY = _DHCP_CLIENT_INFO_ARRAY;
  {$EXTERNALSYM DHCP_CLIENT_INFO_ARRAY}
  LPDHCP_CLIENT_INFO_ARRAY = ^DHCP_CLIENT_INFO_ARRAY;
  {$EXTERNALSYM LPDHCP_CLIENT_INFO_ARRAY}
  TDhcpClientInfoArray = DHCP_CLIENT_INFO_ARRAY;
  PDhcpClientInfoArray = ^DHCP_CLIENT_INFO_ARRAY;

  _DHCP_IP_ARRAY = record
    NumElements: DWORD;
    Elements: LPDHCP_IP_ADDRESS; //array
  end;
  {$EXTERNALSYM _DHCP_IP_ARRAY}
  DHCP_IP_ARRAY = _DHCP_IP_ARRAY;
  {$EXTERNALSYM DHCP_IP_ARRAY}
  LPDHCP_IP_ARRAY = ^DHCP_IP_ARRAY;
  {$EXTERNALSYM LPDHCP_IP_ARRAY}
  TDhcpIpArray = DHCP_IP_ARRAY;
  PDhcpIpArray = ^DHCP_IP_ARRAY;

//
// Subnet State.
//
// Currently a Subnet scope can be Enabled or Disabled.
//
// If the state is Enabled State,
//  The server distributes address to the client, extends leases and
//  accepts releases.
//
// If the state is Disabled State,
//  The server does not distribute address to any new client, and does
//  extent (and sends NACK) old leases, but the servers accepts lease
//  releases.
//
// The idea behind this subnet state is, when the admin wants to stop
//  serving a subnet, he moves the state from Enbaled to Disabled so
//  that the clients from the subnets smoothly move to another servers
//  serving that subnet. When all or most of the clients move to
//  another server, the admin can delete the subnet without any force
//  if no client left in that subnet, otherwise the admin should use
//  full force to delete the subnet.
//

type
  _DHCP_SUBNET_STATE = (
    DhcpSubnetEnabled = 0,
    DhcpSubnetDisabled,
    DhcpSubnetEnabledSwitched,
    DhcpSubnetDisabledSwitched,
    DhcpSubnetInvalidState);
  {$EXTERNALSYM _DHCP_SUBNET_STATE}
  DHCP_SUBNET_STATE = _DHCP_SUBNET_STATE;
  {$EXTERNALSYM DHCP_SUBNET_STATE}
  LPDHCP_SUBNET_STATE = ^DHCP_SUBNET_STATE;
  {$EXTERNALSYM LPDHCP_SUBNET_STATE}
  TDhcpSubnetState = DHCP_SUBNET_STATE;
  PDhcpSubnetState = ^DHCP_SUBNET_STATE;

//
// Subnet related data structures.
//

  _DHCP_SUBNET_INFO = record
    SubnetAddress: DHCP_IP_ADDRESS;
    SubnetMask: DHCP_IP_MASK;
    SubnetName: LPWSTR;
    SubnetComment: LPWSTR;
    PrimaryHost: DHCP_HOST_INFO;
    SubnetState: DHCP_SUBNET_STATE;
  end;
  {$EXTERNALSYM _DHCP_SUBNET_INFO}
  DHCP_SUBNET_INFO = _DHCP_SUBNET_INFO;
  {$EXTERNALSYM DHCP_SUBNET_INFO}
  LPDHCP_SUBNET_INFO = ^DHCP_SUBNET_INFO;
  {$EXTERNALSYM LPDHCP_SUBNET_INFO}
  TDhcpSubnetInfo = DHCP_SUBNET_INFO;
  PDhcpSubnetInfo = ^DHCP_SUBNET_INFO;

//
// DHCP Options related data structures.
//

  _DHCP_OPTION_DATA_TYPE = (
    DhcpByteOption,
    DhcpWordOption,
    DhcpDWordOption,
    DhcpDWordDWordOption,
    DhcpIpAddressOption,
    DhcpStringDataOption,
    DhcpBinaryDataOption,
    DhcpEncapsulatedDataOption);
  {$EXTERNALSYM _DHCP_OPTION_DATA_TYPE}
  DHCP_OPTION_DATA_TYPE = _DHCP_OPTION_DATA_TYPE;
  {$EXTERNALSYM DHCP_OPTION_DATA_TYPE}
  LPDHCP_OPTION_DATA_TYPE = ^DHCP_OPTION_DATA_TYPE;
  {$EXTERNALSYM LPDHCP_OPTION_DATA_TYPE}
  TDhcpOptionDataType = DHCP_OPTION_DATA_TYPE;
  PDhcpOptionDataType = ^DHCP_OPTION_DATA_TYPE;

  _DHCP_OPTION_ELEMENT_UNION = record
    case Integer of
      0: (ByteOption: BYTE);
      1: (WordOption: WORD);
      2: (DWordOption: DWORD);
      3: (DWordDWordOption: DWORD_DWORD);
      4: (IpAddressOption: DHCP_IP_ADDRESS);
      5: (StringDataOption: LPWSTR);
      6: (BinaryDataOption: DHCP_BINARY_DATA);
      7: (EncapsulatedDataOption: DHCP_BINARY_DATA);
      // for vendor specific information option.
  end;
  {$EXTERNALSYM _DHCP_OPTION_ELEMENT_UNION}

  _DHCP_OPTION_DATA_ELEMENT = record
    OptionType: DHCP_OPTION_DATA_TYPE;
    Element: _DHCP_OPTION_ELEMENT_UNION;
  end;
  {$EXTERNALSYM _DHCP_OPTION_DATA_ELEMENT}
  DHCP_OPTION_DATA_ELEMENT = _DHCP_OPTION_DATA_ELEMENT;
  {$EXTERNALSYM DHCP_OPTION_DATA_ELEMENT}
  LPDHCP_OPTION_DATA_ELEMENT = ^DHCP_OPTION_DATA_ELEMENT;
  {$EXTERNALSYM LPDHCP_OPTION_DATA_ELEMENT}
  TDhcpOptionDataElement = DHCP_OPTION_DATA_ELEMENT;
  PDhcpOptionDataElement = ^DHCP_OPTION_DATA_ELEMENT;

  _DHCP_OPTION_DATA = record
    NumElements: DWORD; // number of option elements in the pointed array
    Elements: LPDHCP_OPTION_DATA_ELEMENT; //array
  end;
  {$EXTERNALSYM _DHCP_OPTION_DATA}
  DHCP_OPTION_DATA = _DHCP_OPTION_DATA;
  {$EXTERNALSYM DHCP_OPTION_DATA}
  LPDHCP_OPTION_DATA = ^DHCP_OPTION_DATA;
  {$EXTERNALSYM LPDHCP_OPTION_DATA}
  TDhcpOptionData = DHCP_OPTION_DATA;
  PDhcpOptionData = ^DHCP_OPTION_DATA;

  _DHCP_OPTION_VALUE = record
    OptionID: DHCP_OPTION_ID;
    Value: DHCP_OPTION_DATA;
  end;
  {$EXTERNALSYM _DHCP_OPTION_VALUE}
  DHCP_OPTION_VALUE = _DHCP_OPTION_VALUE;
  {$EXTERNALSYM DHCP_OPTION_VALUE}
  LPDHCP_OPTION_VALUE = ^DHCP_OPTION_VALUE;
  {$EXTERNALSYM LPDHCP_OPTION_VALUE}
  TDhcpOptionValue = DHCP_OPTION_VALUE;
  PDhcpOptionValue = ^DHCP_OPTION_VALUE;  

function DhcpGetVersion(ServerIpAddress: LPWSTR; MajorVersion, MinorVersion: LPDWORD): DWORD; stdcall;
{$EXTERNALSYM DhcpGetVersion}
function DhcpSetServerBindingInfo(ServerIpAddress: PWideChar; Flags: ULONG; BindElementInfo: LPDHCP_BIND_ELEMENT_ARRAY): DWORD; stdcall;
{$EXTERNALSYM DhcpSetServerBindingInfo}
function DhcpGetServerBindingInfo(ServerIpAddress: PWideChar; Flags: ULONG; out BindElementsInfo: LPDHCP_BIND_ELEMENT_ARRAY): DWORD; stdcall;
{$EXTERNALSYM DhcpGetServerBindingInfo}
function DhcpCreateClientInfo(ServerIpAddress: PWideChar; ClientInfo: LPDHCP_CLIENT_INFO): DWORD; stdcall;
{$EXTERNALSYM DhcpCreateClientInfo}
function DhcpSetClientInfo(ServerIpAddress: PWideChar; ClientInfo: LPDHCP_CLIENT_INFO): DWORD; stdcall;
{$EXTERNALSYM DhcpSetClientInfo}
function DhcpGetClientInfo(ServerIpAddress: PWideChar; SearchInfo: LPDHCP_SEARCH_INFO; ClientInfo: LPDHCP_CLIENT_INFO): DWORD; stdcall;
{$EXTERNALSYM DhcpGetClientInfo}
function DhcpDeleteClientInfo(ServerIpAddress: PWideChar; ClientInfo: LPDHCP_SEARCH_INFO): DWORD; stdcall;
{$EXTERNALSYM DhcpDeleteClientInfo}
function DhcpEnumSubnetClients(ServerIpAddress: PWideChar; SubnetAddress: DHCP_IP_ADDRESS; var ResumeHandle: DHCP_RESUME_HANDLE; PreferredMaximum: DWORD; out ClientInfo: LPDHCP_CLIENT_INFO_ARRAY; out ClientsRead, ClientsTotal: DWORD): DWORD; stdcall;
{$EXTERNALSYM DhcpEnumSubnetClients}
function DhcpEnumSubnets(ServerIpAddress: PWideChar; var ResumeHandle: DHCP_RESUME_HANDLE; PreferredMaximum: DWORD; EnumInfo: LPDHCP_IP_ARRAY; out ElementsRead, ElementsTotal: DWORD): DWORD; stdcall;
{$EXTERNALSYM DhcpEnumSubnets}
function DhcpGetSubnetInfo(ServerIpAddress: PWideChar; SubnetAddress: DHCP_IP_ADDRESS; out SubnetInfo: LPDHCP_SUBNET_INFO): DWORD; stdcall;
{$EXTERNALSYM DhcpGetSubnetInfo}
function DhcpGetOptionValue(ServerIpAddress: PWideChar; OptionID: DHCP_OPTION_ID; const ScopeInfo: DHCP_OPTION_SCOPE_INFO; out OptionValue: LPDHCP_OPTION_VALUE): DWORD; stdcall;
{$EXTERNALSYM DhcpGetOptionValue}
procedure DhcpRpcFreeMemory(BufferPointer: PVOID); stdcall;
{$EXTERNALSYM DhcpRpcFreeMemory}

implementation

const
  dhcplib = 'dhcpsapi.dll';

// todo dynamic linking support

function DhcpGetVersion; external dhcplib name 'DhcpGetVersion';
function DhcpSetServerBindingInfo; external dhcplib name 'DhcpSetServerBindingInfo';
function DhcpGetServerBindingInfo; external dhcplib name 'DhcpGetServerBindingInfo';
function DhcpCreateClientInfo; external dhcplib name 'DhcpCreateClientInfo';
function DhcpSetClientInfo; external dhcplib name 'DhcpSetClientInfo';
function DhcpGetClientInfo; external dhcplib name 'DhcpGetClientInfo';
function DhcpDeleteClientInfo; external dhcplib name 'DhcpDeleteClientInfo';
function DhcpEnumSubnetClients; external dhcplib name 'DhcpEnumSubnetClients';
function DhcpEnumSubnets; external dhcplib name 'DhcpEnumSubnets';
function DhcpGetSubnetInfo; external dhcplib name 'DhcpGetSubnetInfo';
function DhcpGetOptionValue; external dhcplib name 'DhcpGetOptionValue';
procedure DhcpRpcFreeMemory; external dhcplib name 'DhcpRpcFreeMemory';

end.
