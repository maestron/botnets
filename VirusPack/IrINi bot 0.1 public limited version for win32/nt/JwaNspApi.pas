{******************************************************************************}
{                                                       	               }
{ Winsock2 Namespace API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: nspapi.h, released June 2000. The original Pascal      }
{ code is: NspApi.pas, released December 2000. The initial developer of the    }
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

unit JwaNspAPI;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "nspapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinSock2;

//
// Service categories
//

const
  SERVICE_RESOURCE = ($00000001);
  {$EXTERNALSYM SERVICE_RESOURCE}
  SERVICE_SERVICE  = ($00000002);
  {$EXTERNALSYM SERVICE_SERVICE}
  SERVICE_LOCAL    = ($00000004);
  {$EXTERNALSYM SERVICE_LOCAL}

//
// Operation used when calling SetService()
//

  SERVICE_REGISTER    = ($00000001);
  {$EXTERNALSYM SERVICE_REGISTER}
  SERVICE_DEREGISTER  = ($00000002);
  {$EXTERNALSYM SERVICE_DEREGISTER}
  SERVICE_FLUSH       = ($00000003);
  {$EXTERNALSYM SERVICE_FLUSH}
  SERVICE_ADD_TYPE    = ($00000004);
  {$EXTERNALSYM SERVICE_ADD_TYPE}
  SERVICE_DELETE_TYPE = ($00000005);
  {$EXTERNALSYM SERVICE_DELETE_TYPE}

//
// Flags that affect the operations above
//

  SERVICE_FLAG_DEFER = ($00000001);
  {$EXTERNALSYM SERVICE_FLAG_DEFER}
  SERVICE_FLAG_HARD  = ($00000002);
  {$EXTERNALSYM SERVICE_FLAG_HARD}

//
// Used as input to GetService() for setting the dwProps parameter
//

  PROP_COMMENT      = ($00000001);
  {$EXTERNALSYM PROP_COMMENT}
  PROP_LOCALE       = ($00000002);
  {$EXTERNALSYM PROP_LOCALE}
  PROP_DISPLAY_HINT = ($00000004);
  {$EXTERNALSYM PROP_DISPLAY_HINT}
  PROP_VERSION      = ($00000008);
  {$EXTERNALSYM PROP_VERSION}
  PROP_START_TIME   = ($00000010);
  {$EXTERNALSYM PROP_START_TIME}
  PROP_MACHINE      = ($00000020);
  {$EXTERNALSYM PROP_MACHINE}
  PROP_ADDRESSES    = ($00000100);
  {$EXTERNALSYM PROP_ADDRESSES}
  PROP_SD           = ($00000200);
  {$EXTERNALSYM PROP_SD}
  PROP_ALL          = DWORD($80000000);
  {$EXTERNALSYM PROP_ALL}

//
// Flags that describe attributes of Service Addresses
//

  SERVICE_ADDRESS_FLAG_RPC_CN = ($00000001);
  {$EXTERNALSYM SERVICE_ADDRESS_FLAG_RPC_CN}
  SERVICE_ADDRESS_FLAG_RPC_DG = ($00000002);
  {$EXTERNALSYM SERVICE_ADDRESS_FLAG_RPC_DG}
  SERVICE_ADDRESS_FLAG_RPC_NB = ($00000004);
  {$EXTERNALSYM SERVICE_ADDRESS_FLAG_RPC_NB}

//
// Name Spaces
//

  NS_DEFAULT = (0);
  {$EXTERNALSYM NS_DEFAULT}

  NS_SAP         = (1);
  {$EXTERNALSYM NS_SAP}
  NS_NDS         = (2);
  {$EXTERNALSYM NS_NDS}
  NS_PEER_BROWSE = (3);
  {$EXTERNALSYM NS_PEER_BROWSE}

  NS_TCPIP_LOCAL = (10);
  {$EXTERNALSYM NS_TCPIP_LOCAL}
  NS_TCPIP_HOSTS = (11);
  {$EXTERNALSYM NS_TCPIP_HOSTS}
  NS_DNS         = (12);
  {$EXTERNALSYM NS_DNS}
  NS_NETBT       = (13);
  {$EXTERNALSYM NS_NETBT}
  NS_WINS        = (14);
  {$EXTERNALSYM NS_WINS}

  NS_NBP = (20);
  {$EXTERNALSYM NS_NBP}

  NS_MS   = (30);
  {$EXTERNALSYM NS_MS}
  NS_STDA = (31);
  {$EXTERNALSYM NS_STDA}
  NS_NTDS = (32);
  {$EXTERNALSYM NS_NTDS}

  NS_X500 = (40);
  {$EXTERNALSYM NS_X500}
  NS_NIS  = (41);
  {$EXTERNALSYM NS_NIS}

  NS_VNS = (50);
  {$EXTERNALSYM NS_VNS}

//
// Name space attributes.
//

  NSTYPE_HIERARCHICAL = ($00000001);
  {$EXTERNALSYM NSTYPE_HIERARCHICAL}
  NSTYPE_DYNAMIC      = ($00000002);
  {$EXTERNALSYM NSTYPE_DYNAMIC}
  NSTYPE_ENUMERABLE   = ($00000004);
  {$EXTERNALSYM NSTYPE_ENUMERABLE}
  NSTYPE_WORKGROUP    = ($00000008);
  {$EXTERNALSYM NSTYPE_WORKGROUP}

//
// Transport attributes.
//

  XP_CONNECTIONLESS       = ($00000001);
  {$EXTERNALSYM XP_CONNECTIONLESS}
  XP_GUARANTEED_DELIVERY  = ($00000002);
  {$EXTERNALSYM XP_GUARANTEED_DELIVERY}
  XP_GUARANTEED_ORDER     = ($00000004);
  {$EXTERNALSYM XP_GUARANTEED_ORDER}
  XP_MESSAGE_ORIENTED     = ($00000008);
  {$EXTERNALSYM XP_MESSAGE_ORIENTED}
  XP_PSEUDO_STREAM        = ($00000010);
  {$EXTERNALSYM XP_PSEUDO_STREAM}
  XP_GRACEFUL_CLOSE       = ($00000020);
  {$EXTERNALSYM XP_GRACEFUL_CLOSE}
  XP_EXPEDITED_DATA       = ($00000040);
  {$EXTERNALSYM XP_EXPEDITED_DATA}
  XP_CONNECT_DATA         = ($00000080);
  {$EXTERNALSYM XP_CONNECT_DATA}
  XP_DISCONNECT_DATA      = ($00000100);
  {$EXTERNALSYM XP_DISCONNECT_DATA}
  XP_SUPPORTS_BROADCAST   = ($00000200);
  {$EXTERNALSYM XP_SUPPORTS_BROADCAST}
  XP_SUPPORTS_MULTICAST   = ($00000400);
  {$EXTERNALSYM XP_SUPPORTS_MULTICAST}
  XP_BANDWIDTH_ALLOCATION = ($00000800);
  {$EXTERNALSYM XP_BANDWIDTH_ALLOCATION}
  XP_FRAGMENTATION        = ($00001000);
  {$EXTERNALSYM XP_FRAGMENTATION}
  XP_ENCRYPTS             = ($00002000);
  {$EXTERNALSYM XP_ENCRYPTS}

//
// Resolution flags for GetAddressByName().
//

  RES_SOFT_SEARCH   = ($00000001);
  {$EXTERNALSYM RES_SOFT_SEARCH}
  RES_FIND_MULTIPLE = ($00000002);
  {$EXTERNALSYM RES_FIND_MULTIPLE}
  RES_SERVICE       = ($00000004);
  {$EXTERNALSYM RES_SERVICE}

//
// Well known value names for Service Types
//

  SERVICE_TYPE_VALUE_SAPIDA = 'SapId';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPIDA}
  SERVICE_TYPE_VALUE_SAPIDW = WideString('SapId');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPIDW}

  SERVICE_TYPE_VALUE_CONNA = 'ConnectionOriented';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_CONNA}
  SERVICE_TYPE_VALUE_CONNW = WideString('ConnectionOriented');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_CONNW}

  SERVICE_TYPE_VALUE_TCPPORTA = 'TcpPort';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORTA}
  SERVICE_TYPE_VALUE_TCPPORTW = WideString('TcpPort');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORTW}

  SERVICE_TYPE_VALUE_UDPPORTA = 'UdpPort';
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORTA}
  SERVICE_TYPE_VALUE_UDPPORTW = WideString('UdpPort');
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORTW}

{$IFDEF UNICODE}

  SERVICE_TYPE_VALUE_SAPID   = SERVICE_TYPE_VALUE_SAPIDW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPID}
  SERVICE_TYPE_VALUE_CONN    = SERVICE_TYPE_VALUE_CONNW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_CONN}
  SERVICE_TYPE_VALUE_TCPPORT = SERVICE_TYPE_VALUE_TCPPORTW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORT}
  SERVICE_TYPE_VALUE_UDPPORT = SERVICE_TYPE_VALUE_UDPPORTW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORT}

{$ELSE}

  SERVICE_TYPE_VALUE_SAPID   = SERVICE_TYPE_VALUE_SAPIDA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_SAPID}
  SERVICE_TYPE_VALUE_CONN    = SERVICE_TYPE_VALUE_CONNA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_CONN}
  SERVICE_TYPE_VALUE_TCPPORT = SERVICE_TYPE_VALUE_TCPPORTA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_TCPPORT}
  SERVICE_TYPE_VALUE_UDPPORT = SERVICE_TYPE_VALUE_UDPPORTA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_UDPPORT}

{$ENDIF}


//
// status flags returned by SetService
//

  SET_SERVICE_PARTIAL_SUCCESS = ($00000001);
  {$EXTERNALSYM SET_SERVICE_PARTIAL_SUCCESS}

//
// Name Space Information
//

type
  _NS_INFOA = record
    dwNameSpace: DWORD;
    dwNameSpaceFlags: DWORD;
    lpNameSpace: LPSTR;
  end;
  {$EXTERNALSYM _NS_INFOA}
  NS_INFOA = _NS_INFOA;
  {$EXTERNALSYM NS_INFOA}
  PNS_INFOA = ^NS_INFOA;
  {$EXTERNALSYM PNS_INFOA}
  LPNS_INFOA = ^NS_INFOA;
  {$EXTERNALSYM LPNS_INFOA}
  TNsInfoA = NS_INFOA;
  PNsInfoA = LPNS_INFOA;

//
// Name Space Information
//

  _NS_INFOW = record
    dwNameSpace: DWORD;
    dwNameSpaceFlags: DWORD;
    lpNameSpace: LPWSTR;
  end;
  {$EXTERNALSYM _NS_INFOW}
  NS_INFOW = _NS_INFOW;
  {$EXTERNALSYM NS_INFOW}
  PNS_INFOW = ^NS_INFOW;
  {$EXTERNALSYM PNS_INFOW}
  LPNS_INFOW = ^NS_INFOW;
  {$EXTERNALSYM LPNS_INFOW}
  TNsInfoW = NS_INFOW;
  PNsInfoW = LPNS_INFOW;

{$IFDEF UNICODE}
  NS_INFO = NS_INFOW;
  {$EXTERNALSYM NS_INFO}
  PNS_INFO = PNS_INFOW;
  {$EXTERNALSYM PNS_INFO}
  LPNS_INFO = LPNS_INFOW;
  {$EXTERNALSYM LPNS_INFO}
  TNsInfo = TNsInfoW;
  PNsInfo = PNsInfoW;
{$ELSE}
  NS_INFO = NS_INFOA;
  {$EXTERNALSYM NS_INFO}
  PNS_INFO = PNS_INFOA;
  {$EXTERNALSYM PNS_INFO}
  LPNS_INFO = LPNS_INFOA;
  {$EXTERNALSYM LPNS_INFO}
  TNsInfo = TNsInfoA;
  PNsInfo = PNsInfoA;
{$ENDIF}

//
// Service Type Values. The structures are used to define named Service
// Type specific values. This structure is self relative and has no pointers.
//

  LPSERVICE_TYPE_VALUE = ^SERVICE_TYPE_VALUE;
  {$EXTERNALSYM LPSERVICE_TYPE_VALUE}
  PSERVICE_TYPE_VALUE = ^SERVICE_TYPE_VALUE;
  {$EXTERNALSYM PSERVICE_TYPE_VALUE}
  _SERVICE_TYPE_VALUE = record
    dwNameSpace: DWORD;
    dwValueType: DWORD;
    dwValueSize: DWORD;
    dwValueNameOffset: DWORD;
    dwValueOffset: DWORD;
  end;
  {$EXTERNALSYM _SERVICE_TYPE_VALUE}
  SERVICE_TYPE_VALUE = _SERVICE_TYPE_VALUE;
  {$EXTERNALSYM SERVICE_TYPE_VALUE}
  TServiceTypeValue = SERVICE_TYPE_VALUE;
  PServiceTypeValue = LPSERVICE_TYPE_VALUE;

//
// An absolute version of above. This structure does contain pointers.
//

  LPSERVICE_TYPE_VALUE_ABSA = ^SERVICE_TYPE_VALUE_ABSA;
  {$EXTERNALSYM LPSERVICE_TYPE_VALUE_ABSA}
  PSERVICE_TYPE_VALUE_ABSA = ^SERVICE_TYPE_VALUE_ABSA;
  {$EXTERNALSYM PSERVICE_TYPE_VALUE_ABSA}
  _SERVICE_TYPE_VALUE_ABSA = record
    dwNameSpace: DWORD;
    dwValueType: DWORD;
    dwValueSize: DWORD;
    lpValueName: LPSTR;
    lpValue: LPVOID;
  end;
  {$EXTERNALSYM _SERVICE_TYPE_VALUE_ABSA}
  SERVICE_TYPE_VALUE_ABSA = _SERVICE_TYPE_VALUE_ABSA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_ABSA}
  TServiceTypeValueAbsA = SERVICE_TYPE_VALUE_ABSA;
  PServiceTypeValueAbsA = LPSERVICE_TYPE_VALUE_ABSA;

//
// An absolute version of above. This structure does contain pointers.
//

  LPSERVICE_TYPE_VALUE_ABSW = ^SERVICE_TYPE_VALUE_ABSW;
  {$EXTERNALSYM LPSERVICE_TYPE_VALUE_ABSW}
  PSERVICE_TYPE_VALUE_ABSW = ^SERVICE_TYPE_VALUE_ABSW;
  {$EXTERNALSYM PSERVICE_TYPE_VALUE_ABSW}
  _SERVICE_TYPE_VALUE_ABSW = record
    dwNameSpace: DWORD;
    dwValueType: DWORD;
    dwValueSize: DWORD;
    lpValueName: LPWSTR;
    lpValue: LPVOID;
  end;
  {$EXTERNALSYM _SERVICE_TYPE_VALUE_ABSW}
  SERVICE_TYPE_VALUE_ABSW = _SERVICE_TYPE_VALUE_ABSW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_ABSW}
  TServiceTypeValueAbsW = SERVICE_TYPE_VALUE_ABSW;
  PServiceTypeValueAbsW = LPSERVICE_TYPE_VALUE_ABSW;

{$IFDEF UNICODE}
  SERVICE_TYPE_VALUE_ABS = SERVICE_TYPE_VALUE_ABSW;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_ABS}
  PSERVICE_TYPE_VALUE_ABS = PSERVICE_TYPE_VALUE_ABSW;
  {$EXTERNALSYM PSERVICE_TYPE_VALUE_ABS}
  LPSERVICE_TYPE_VALUE_ABS = LPSERVICE_TYPE_VALUE_ABSW;
  {$EXTERNALSYM LPSERVICE_TYPE_VALUE_ABS}
  TServiceTypeValueAbs = TServiceTypeValueAbsW;
  PServiceTypeValueAbs = PServiceTypeValueAbsW;
{$ELSE}
  SERVICE_TYPE_VALUE_ABS = SERVICE_TYPE_VALUE_ABSA;
  {$EXTERNALSYM SERVICE_TYPE_VALUE_ABS}
  PSERVICE_TYPE_VALUE_ABS = PSERVICE_TYPE_VALUE_ABSA;
  {$EXTERNALSYM PSERVICE_TYPE_VALUE_ABS}
  LPSERVICE_TYPE_VALUE_ABS = LPSERVICE_TYPE_VALUE_ABSA;
  {$EXTERNALSYM LPSERVICE_TYPE_VALUE_ABS}
  TServiceTypeValueAbs = TServiceTypeValueAbsA;
  PServiceTypeValueAbs = PServiceTypeValueAbsA;
{$ENDIF}

//
// Service Type Information. Contains the name of the Service Type and
// and an array of SERVICE_NS_TYPE_VALUE structures. This structure is self
// relative and has no pointers in it.
//

  LPSERVICE_TYPE_INFO = ^SERVICE_TYPE_INFO;
  {$EXTERNALSYM LPSERVICE_TYPE_INFO}
  PSERVICE_TYPE_INFO = ^SERVICE_TYPE_INFO;
  {$EXTERNALSYM PSERVICE_TYPE_INFO}
  _SERVICE_TYPE_INFO = record
    dwTypeNameOffset: DWORD;
    dwValueCount: DWORD;
    Values: array [0..0] of SERVICE_TYPE_VALUE;
  end;
  {$EXTERNALSYM _SERVICE_TYPE_INFO}
  SERVICE_TYPE_INFO = _SERVICE_TYPE_INFO;
  {$EXTERNALSYM SERVICE_TYPE_INFO}
  TServiceTypeInfo = SERVICE_TYPE_INFO;
  PServiceTypeInfo = LPSERVICE_TYPE_INFO;

  LPSERVICE_TYPE_INFO_ABSA = ^SERVICE_TYPE_INFO_ABSA;
  {$EXTERNALSYM LPSERVICE_TYPE_INFO_ABSA}
  PSERVICE_TYPE_INFO_ABSA = ^SERVICE_TYPE_INFO_ABSA;
  {$EXTERNALSYM PSERVICE_TYPE_INFO_ABSA}
  _SERVICE_TYPE_INFO_ABSA = record
    lpTypeName: LPSTR;
    dwValueCount: DWORD;
    Values: array [0..0] of SERVICE_TYPE_VALUE_ABSA;
  end;
  {$EXTERNALSYM _SERVICE_TYPE_INFO_ABSA}
  SERVICE_TYPE_INFO_ABSA = _SERVICE_TYPE_INFO_ABSA;
  {$EXTERNALSYM SERVICE_TYPE_INFO_ABSA}
  TServiceTypeInfoAbsA = SERVICE_TYPE_INFO_ABSA;
  PServiceTypeInfoAbsA = PSERVICE_TYPE_INFO_ABSA;

  LPSERVICE_TYPE_INFO_ABSW = ^SERVICE_TYPE_INFO_ABSW;
  {$EXTERNALSYM LPSERVICE_TYPE_INFO_ABSW}
  PSERVICE_TYPE_INFO_ABSW = ^SERVICE_TYPE_INFO_ABSW;
  {$EXTERNALSYM PSERVICE_TYPE_INFO_ABSW}
  _SERVICE_TYPE_INFO_ABSW = record
    lpTypeName: LPWSTR;
    dwValueCount: DWORD;
    Values: array [0..0] of SERVICE_TYPE_VALUE_ABSW;
  end;
  {$EXTERNALSYM _SERVICE_TYPE_INFO_ABSW}
  SERVICE_TYPE_INFO_ABSW = _SERVICE_TYPE_INFO_ABSW;
  {$EXTERNALSYM SERVICE_TYPE_INFO_ABSW}
  TServiceTypeInfoAbsW = SERVICE_TYPE_INFO_ABSW;
  PServiceTypeInfoAbsW = LPSERVICE_TYPE_INFO_ABSW;

{$IFDEF UNICODE}
  SERVICE_TYPE_INFO_ABS = SERVICE_TYPE_INFO_ABSW;
  {$EXTERNALSYM SERVICE_TYPE_INFO_ABS}
  PSERVICE_TYPE_INFO_ABS = PSERVICE_TYPE_INFO_ABSW;
  {$EXTERNALSYM PSERVICE_TYPE_INFO_ABS}
  LPSERVICE_TYPE_INFO_ABS = LPSERVICE_TYPE_INFO_ABSW;
  {$EXTERNALSYM LPSERVICE_TYPE_INFO_ABS}
  TServiceTypeInfoAbs = TServiceTypeInfoAbsW;
  PServiceTypeInfoAbs = PServiceTypeInfoAbsW;
{$ELSE}
  SERVICE_TYPE_INFO_ABS = SERVICE_TYPE_INFO_ABSA;
  {$EXTERNALSYM SERVICE_TYPE_INFO_ABS}
  PSERVICE_TYPE_INFO_ABS = PSERVICE_TYPE_INFO_ABSA;
  {$EXTERNALSYM PSERVICE_TYPE_INFO_ABS}
  LPSERVICE_TYPE_INFO_ABS = LPSERVICE_TYPE_INFO_ABSA;
  {$EXTERNALSYM LPSERVICE_TYPE_INFO_ABS}
  TServiceTypeInfoAbs = TServiceTypeInfoAbsA;
  PServiceTypeInfoAbs = PServiceTypeInfoAbsA;
{$ENDIF}

//
// A Single Address definition.
//

  LPSERVICE_ADDRESS = ^SERVICE_ADDRESS;
  {$EXTERNALSYM LPSERVICE_ADDRESS}
  PSERVICE_ADDRESS = ^SERVICE_ADDRESS;
  {$EXTERNALSYM PSERVICE_ADDRESS}
  _SERVICE_ADDRESS = record
    dwAddressType: DWORD;
    dwAddressFlags: DWORD;
    dwAddressLength: DWORD;
    dwPrincipalLength: DWORD;
    lpAddress: LPBYTE;
    lpPrincipal: LPBYTE;
  end;
  {$EXTERNALSYM _SERVICE_ADDRESS}
  SERVICE_ADDRESS = _SERVICE_ADDRESS;
  {$EXTERNALSYM SERVICE_ADDRESS}
  TServiceAddress = SERVICE_ADDRESS;
  PServiceAddress = LPSERVICE_ADDRESS;

//
// Addresses used by the service. Contains array of SERVICE_ADDRESS.
//

  LPSERVICE_ADDRESSES = ^SERVICE_ADDRESSES;
  {$EXTERNALSYM LPSERVICE_ADDRESSES}
  PSERVICE_ADDRESSES = ^SERVICE_ADDRESSES;
  {$EXTERNALSYM PSERVICE_ADDRESSES}
  _SERVICE_ADDRESSES = record
    dwAddressCount: DWORD;
    Addresses: array [0..0] of SERVICE_ADDRESS;
  end;
  {$EXTERNALSYM _SERVICE_ADDRESSES}
  SERVICE_ADDRESSES = _SERVICE_ADDRESSES;
  {$EXTERNALSYM SERVICE_ADDRESSES}
  TServiceAddresses = SERVICE_ADDRESSES;
  PServiceAddresses = PSERVICE_ADDRESSES;

//
// Service Information.
//

  LPSERVICE_INFOA = ^SERVICE_INFOA;
  {$EXTERNALSYM LPSERVICE_INFOA}
  PSERVICE_INFOA = ^SERVICE_INFOA;
  {$EXTERNALSYM PSERVICE_INFOA}
  _SERVICE_INFOA = record
    lpServiceType: PGUID;
    lpServiceName: LPSTR;
    lpComment: LPSTR;
    lpLocale: LPSTR;
    dwDisplayHint: DWORD;
    dwVersion: DWORD;
    dwTime: DWORD;
    lpMachineName: LPSTR;
    lpServiceAddress: LPSERVICE_ADDRESSES;
    ServiceSpecificInfo: BLOB;
  end;
  {$EXTERNALSYM _SERVICE_INFOA}
  SERVICE_INFOA = _SERVICE_INFOA;
  {$EXTERNALSYM SERVICE_INFOA}
  TServiceInfoA = SERVICE_INFOA;
  PServiceInfoA = PSERVICE_INFOA;

//
// Service Information.
//

  LPSERVICE_INFOW = ^SERVICE_INFOW;
  {$EXTERNALSYM LPSERVICE_INFOW}
  PSERVICE_INFOW = ^SERVICE_INFOW;
  {$EXTERNALSYM PSERVICE_INFOW}
  _SERVICE_INFOW = record
    lpServiceType: PGUID;
    lpServiceName: LPWSTR;
    lpComment: LPWSTR;
    lpLocale: LPWSTR;
    dwDisplayHint: DWORD;
    dwVersion: DWORD;
    dwTime: DWORD;
    lpMachineName: LPWSTR;
    lpServiceAddress: LPSERVICE_ADDRESSES;
    ServiceSpecificInfo: BLOB;
  end;
  {$EXTERNALSYM _SERVICE_INFOW}
  SERVICE_INFOW = _SERVICE_INFOW;
  {$EXTERNALSYM SERVICE_INFOW}
  TServiceInfoW = SERVICE_INFOW;
  PServiceInfoW = PSERVICE_INFOW;

{$IFDEF UNICODE}
  SERVICE_INFO = SERVICE_INFOW;
  {$EXTERNALSYM SERVICE_INFO}
  PSERVICE_INFO = PSERVICE_INFOW;
  {$EXTERNALSYM PSERVICE_INFO}
  LPSERVICE_INFO = LPSERVICE_INFOW;
  {$EXTERNALSYM LPSERVICE_INFO}
  TServiceInfo = TServiceInfoW;
  PServiceInfo = PServiceInfoW;
{$ELSE}
  SERVICE_INFO = SERVICE_INFOA;
  {$EXTERNALSYM SERVICE_INFO}
  PSERVICE_INFO = PSERVICE_INFOA;
  {$EXTERNALSYM PSERVICE_INFO}
  LPSERVICE_INFO = LPSERVICE_INFOA;
  {$EXTERNALSYM LPSERVICE_INFO}
  TServiceInfo = TServiceInfoA;
  PServiceInfo = PServiceInfoA;
{$ENDIF}

//
// Name Space & Service Information
//

  LPNS_SERVICE_INFOA = ^NS_SERVICE_INFOA;
  {$EXTERNALSYM LPNS_SERVICE_INFOA}
  PNS_SERVICE_INFOA = ^NS_SERVICE_INFOA;
  {$EXTERNALSYM PNS_SERVICE_INFOA}
  _NS_SERVICE_INFOA = record
    dwNameSpace: DWORD;
    ServiceInfo: SERVICE_INFOA;
  end;
  {$EXTERNALSYM _NS_SERVICE_INFOA}
  NS_SERVICE_INFOA = _NS_SERVICE_INFOA;
  {$EXTERNALSYM NS_SERVICE_INFOA}
  TNsServiceInfoA = NS_SERVICE_INFOA;
  PNsServiceInfoA = LPNS_SERVICE_INFOA;

//
// Name Space & Service Information
//

  LPNS_SERVICE_INFOW = ^NS_SERVICE_INFOW;
  {$EXTERNALSYM LPNS_SERVICE_INFOW}
  PNS_SERVICE_INFOW = ^NS_SERVICE_INFOW;
  {$EXTERNALSYM PNS_SERVICE_INFOW}
  _NS_SERVICE_INFOW = record
    dwNameSpace: DWORD;
    ServiceInfo: SERVICE_INFOW;
  end;
  {$EXTERNALSYM _NS_SERVICE_INFOW}
  NS_SERVICE_INFOW = _NS_SERVICE_INFOW;
  {$EXTERNALSYM NS_SERVICE_INFOW}
  TNsServiceInfoW = NS_SERVICE_INFOW;
  PNsServiceInfoW = LPNS_SERVICE_INFOW;

{$IFDEF UNICODE}
  NS_SERVICE_INFO = NS_SERVICE_INFOW;
  {$EXTERNALSYM NS_SERVICE_INFO}
  PNS_SERVICE_INFO = PNS_SERVICE_INFOW;
  {$EXTERNALSYM PNS_SERVICE_INFO}
  LPNS_SERVICE_INFO = LPNS_SERVICE_INFOW;
  {$EXTERNALSYM LPNS_SERVICE_INFO}
  TNsServiceInfo = TNsServiceInfoW;
  PNsServiceInfo = PNsServiceInfoW;
{$ELSE}
  NS_SERVICE_INFO = NS_SERVICE_INFOA;
  {$EXTERNALSYM NS_SERVICE_INFO}
  PNS_SERVICE_INFO = PNS_SERVICE_INFOA;
  {$EXTERNALSYM PNS_SERVICE_INFO}
  LPNS_SERVICE_INFO = LPNS_SERVICE_INFOA;
  {$EXTERNALSYM LPNS_SERVICE_INFO}
  TNsServiceInfo = TNsServiceInfoA;
  PNsServiceInfo = PNsServiceInfoA;
{$ENDIF}

//
// SockAddr Information
//

  LPSOCKET_ADDRESS = ^SOCKET_ADDRESS;
  {$EXTERNALSYM LPSOCKET_ADDRESS}
  PSOCKET_ADDRESS = ^SOCKET_ADDRESS;
  {$EXTERNALSYM PSOCKET_ADDRESS}
  _SOCKET_ADDRESS = record
    lpSockaddr: LPSOCKADDR;
    iSockaddrLength: Integer;
  end;
  {$EXTERNALSYM _SOCKET_ADDRESS}
  SOCKET_ADDRESS = _SOCKET_ADDRESS;
  {$EXTERNALSYM SOCKET_ADDRESS}
  TSocketAddress = SOCKET_ADDRESS;
  PSocketAddress = PSOCKET_ADDRESS;

//
// CSAddr Information
//

  LPCSADDR_INFO = ^CSADDR_INFO;
  {$EXTERNALSYM LPCSADDR_INFO}
  PCSADDR_INFO = ^CSADDR_INFO;
  {$EXTERNALSYM PCSADDR_INFO}
  _CSADDR_INFO = record
    LocalAddr: SOCKET_ADDRESS;
    RemoteAddr: SOCKET_ADDRESS;
    iSocketType: Integer;
    iProtocol: Integer;
  end;
  {$EXTERNALSYM _CSADDR_INFO}
  CSADDR_INFO = _CSADDR_INFO;
  {$EXTERNALSYM CSADDR_INFO}
  TCsAddrInfo = CSADDR_INFO;
  PCsAddrInfo = LPCSADDR_INFO;

//
// Protocol Information
//

  LPPROTOCOL_INFOA = ^PROTOCOL_INFOA;
  {$EXTERNALSYM LPPROTOCOL_INFOA}
  PPROTOCOL_INFOA = ^PROTOCOL_INFOA;
  {$EXTERNALSYM PPROTOCOL_INFOA}
  _PROTOCOL_INFOA = record
    dwServiceFlags: DWORD;
    iAddressFamily: Integer;
    iMaxSockAddr: Integer;
    iMinSockAddr: Integer;
    iSocketType: Integer;
    iProtocol: Integer;
    dwMessageSize: DWORD;
    lpProtocol: LPSTR;
  end;
  {$EXTERNALSYM _PROTOCOL_INFOA}
  PROTOCOL_INFOA = _PROTOCOL_INFOA;
  {$EXTERNALSYM PROTOCOL_INFOA}
  TProtocolInfoA = PROTOCOL_INFOA;
  PProtocolInfoA = LPPROTOCOL_INFOA;

//
// Protocol Information
//

  LPPROTOCOL_INFOW = ^PROTOCOL_INFOW;
  {$EXTERNALSYM LPPROTOCOL_INFOW}
  PPROTOCOL_INFOW = ^PROTOCOL_INFOW;
  {$EXTERNALSYM PPROTOCOL_INFOW}
  _PROTOCOL_INFOW = record
    dwServiceFlags: DWORD;
    iAddressFamily: Integer;
    iMaxSockAddr: Integer;
    iMinSockAddr: Integer;
    iSocketType: Integer;
    iProtocol: Integer;
    dwMessageSize: DWORD;
    lpProtocol: LPWSTR;
  end;
  {$EXTERNALSYM _PROTOCOL_INFOW}
  PROTOCOL_INFOW = _PROTOCOL_INFOW;
  {$EXTERNALSYM PROTOCOL_INFOW}
  TProtocolInfoW = PROTOCOL_INFOW;
  PProtocolInfoW = LPPROTOCOL_INFOW;

{$IFDEF UNICODE}
  PROTOCOL_INFO = PROTOCOL_INFOW;
  {$EXTERNALSYM PROTOCOL_INFO}
  PPROTOCOL_INFO = PPROTOCOL_INFOW;
  {$EXTERNALSYM PPROTOCOL_INFO}
  LPPROTOCOL_INFO = LPPROTOCOL_INFOW;
  {$EXTERNALSYM LPPROTOCOL_INFO}
  TProtocolInfo = TProtocolInfoW;
  PProtocolInfo = PProtocolInfoW;
{$ELSE}
  PROTOCOL_INFO = PROTOCOL_INFOA;
  {$EXTERNALSYM PROTOCOL_INFO}
  PPROTOCOL_INFO = PPROTOCOL_INFOA;
  {$EXTERNALSYM PPROTOCOL_INFO}
  LPPROTOCOL_INFO = LPPROTOCOL_INFOA;
  {$EXTERNALSYM LPPROTOCOL_INFO}
  TProtocolInfo = TProtocolInfoA;
  PProtocolInfo = PProtocolInfoA;
{$ENDIF}

//
// NETRESOURCE2 Structure
//

  LPNETRESOURCE2A = ^NETRESOURCE2A;
  {$EXTERNALSYM LPNETRESOURCE2A}
  PNETRESOURCE2A = ^NETRESOURCE2A;
  {$EXTERNALSYM PNETRESOURCE2A}
  _NETRESOURCE2A = record
    dwScope: DWORD;
    dwType: DWORD;
    dwUsage: DWORD;
    dwDisplayType: DWORD;
    lpLocalName: LPSTR;
    lpRemoteName: LPSTR;
    lpComment: LPSTR;
    ns_info: NS_INFO;
    ServiceType: TGUID;
    dwProtocols: DWORD;
    lpiProtocols: PINT;
  end;
  {$EXTERNALSYM _NETRESOURCE2A}
  NETRESOURCE2A = _NETRESOURCE2A;
  {$EXTERNALSYM NETRESOURCE2A}
  TNetResource2A = NETRESOURCE2A;

//
// NETRESOURCE2 Structure
//

  LPNETRESOURCE2W = ^NETRESOURCE2W;
  {$EXTERNALSYM LPNETRESOURCE2W}
  PNETRESOURCE2W = ^NETRESOURCE2W;
  {$EXTERNALSYM PNETRESOURCE2W}
  _NETRESOURCE2W = record
    dwScope: DWORD;
    dwType: DWORD;
    dwUsage: DWORD;
    dwDisplayType: DWORD;
    lpLocalName: LPWSTR;
    lpRemoteName: LPWSTR;
    lpComment: LPWSTR;
    ns_info: NS_INFO;
    ServiceType: TGUID;
    dwProtocols: DWORD;
    lpiProtocols: PINT;
  end;
  {$EXTERNALSYM _NETRESOURCE2W}
  NETRESOURCE2W = _NETRESOURCE2W;
  {$EXTERNALSYM NETRESOURCE2W}
  TNetResource2W = NETRESOURCE2W;

{$IFDEF UNICODE}
  NETRESOURCE2 = NETRESOURCE2W;
  {$EXTERNALSYM NETRESOURCE2}
  PNETRESOURCE2 = PNETRESOURCE2W;
  {$EXTERNALSYM PNETRESOURCE2}
  LPNETRESOURCE2 = LPNETRESOURCE2W;
  {$EXTERNALSYM LPNETRESOURCE2}
  TNetResource2 = TNetResource2W;
{$ELSE}
  NETRESOURCE2 = NETRESOURCE2A;
  {$EXTERNALSYM NETRESOURCE2}
  PNETRESOURCE2 = PNETRESOURCE2A;
  {$EXTERNALSYM PNETRESOURCE2}
  LPNETRESOURCE2 = LPNETRESOURCE2A;
  {$EXTERNALSYM LPNETRESOURCE2}
  TNetResource2 = TNetResource2A;
{$ENDIF}

  LPFN_NSPAPI = function: DWORD; stdcall;
  {$EXTERNALSYM LPFN_NSPAPI}
  TFnNspApi = LPFN_NSPAPI; 

//
// Structures for using the service routines asynchronously.
//

type
  LPSERVICE_CALLBACK_PROC = procedure (lParam: LPARAM; hAsyncTaskHandle: HANDLE); stdcall;
  {$EXTERNALSYM LPSERVICE_CALLBACK_PROC}
  TServiceCallbackProc = LPSERVICE_CALLBACK_PROC;

type
  LPSERVICE_ASYNC_INFO = ^SERVICE_ASYNC_INFO;
  {$EXTERNALSYM LPSERVICE_ASYNC_INFO}
  PSERVICE_ASYNC_INFO = ^SERVICE_ASYNC_INFO;
  {$EXTERNALSYM PSERVICE_ASYNC_INFO}
  _SERVICE_ASYNC_INFO = record
    lpServiceCallbackProc: LPSERVICE_CALLBACK_PROC;
    lParam: LPARAM;
    hAsyncTaskHandle: HANDLE;
  end;
  {$EXTERNALSYM _SERVICE_ASYNC_INFO}
  SERVICE_ASYNC_INFO = _SERVICE_ASYNC_INFO;
  {$EXTERNALSYM SERVICE_ASYNC_INFO}
  TServiceAsyncInfo = SERVICE_ASYNC_INFO;
  PServiceAsyncInfo = LPSERVICE_ASYNC_INFO;

//
// Public NSP API prototypes.
//

function EnumProtocolsA(lpiProtocols: PINT; lpProtocolBuffer: LPVOID; lpdwBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM EnumProtocolsA}
function EnumProtocolsW(lpiProtocols: PINT; lpProtocolBuffer: LPVOID; lpdwBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM EnumProtocolsW}

{$IFDEF UNICODE}
function EnumProtocols(lpiProtocols: PINT; lpProtocolBuffer: LPVOID; lpdwBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM EnumProtocols}
{$ELSE}
function EnumProtocols(lpiProtocols: PINT; lpProtocolBuffer: LPVOID; lpdwBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM EnumProtocols}
{$ENDIF}

function GetAddressByNameA(dwNameSpace: DWORD; const lpServiceType: TGUID;
  lpServiceName: LPSTR; lpiProtocols: PINT; dwResolution: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO; lpCsaddrBuffer: LPVOID;
  var lpdwBufferLength: DWORD; lpAliasBuffer: LPSTR; lpdwAliasBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM GetAddressByNameA}
function GetAddressByNameW(dwNameSpace: DWORD; const lpServiceType: TGUID;
  lpServiceName: LPWSTR; lpiProtocols: PINT; dwResolution: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO; lpCsaddrBuffer: LPVOID;
  var lpdwBufferLength: DWORD; lpAliasBuffer: LPWSTR; lpdwAliasBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM GetAddressByNameW}

{$IFDEF UNICODE}
function GetAddressByName(dwNameSpace: DWORD; const lpServiceType: TGUID;
  lpServiceName: LPWSTR; lpiProtocols: PINT; dwResolution: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO; lpCsaddrBuffer: LPVOID;
  var lpdwBufferLength: DWORD; lpAliasBuffer: LPWSTR; lpdwAliasBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM GetAddressByName}
{$ELSE}
function GetAddressByName(dwNameSpace: DWORD; const lpServiceType: TGUID;
  lpServiceName: LPSTR; lpiProtocols: PINT; dwResolution: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO; lpCsaddrBuffer: LPVOID;
  var lpdwBufferLength: DWORD; lpAliasBuffer: LPSTR; lpdwAliasBufferLength: LPDWORD): Integer; stdcall;
{$EXTERNALSYM GetAddressByName}
{$ENDIF}

function GetTypeByNameA(lpServiceName: LPSTR; var lpServiceType: TGUID): Integer; stdcall;
{$EXTERNALSYM GetTypeByNameA}
function GetTypeByNameW(lpServiceName: LPWSTR; var lpServiceType: TGUID): Integer; stdcall;
{$EXTERNALSYM GetTypeByNameW}

{$IFDEF UNICODE}
function GetTypeByName(lpServiceName: LPWSTR; var lpServiceType: TGUID): Integer; stdcall;
{$EXTERNALSYM GetTypeByName}
{$ELSE}
function GetTypeByName(lpServiceName: LPSTR; var lpServiceType: TGUID): Integer; stdcall;
{$EXTERNALSYM GetTypeByName}
{$ENDIF}

function GetNameByTypeA(const lpServiceType: TGUID; lpServiceName: LPSTR; dwNameLength: DWORD): Integer; stdcall;
{$EXTERNALSYM GetNameByTypeA}
function GetNameByTypeW(const lpServiceType: TGUID; lpServiceName: LPWSTR; dwNameLength: DWORD): Integer; stdcall;
{$EXTERNALSYM GetNameByTypeW}

{$IFDEF UNICODE}
function GetNameByType(const lpServiceType: TGUID; lpServiceName: LPWSTR; dwNameLength: DWORD): Integer; stdcall;
{$EXTERNALSYM GetNameByType}
{$ELSE}
function GetNameByType(const lpServiceType: TGUID; lpServiceName: LPSTR; dwNameLength: DWORD): Integer; stdcall;
{$EXTERNALSYM GetNameByType}
{$ENDIF}

function SetServiceA(dwNameSpace, dwOperation, dwFlags: DWORD;
  const lpServiceInfo: SERVICE_INFOA; lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO;
  var lpdwStatusFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM SetServiceA}
function SetServiceW(dwNameSpace, dwOperation, dwFlags: DWORD;
  const lpServiceInfo: SERVICE_INFOW; lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO;
  var lpdwStatusFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM SetServiceW}

{$IFDEF UNICODE}
function SetService(dwNameSpace, dwOperation, dwFlags: DWORD;
  const lpServiceInfo: SERVICE_INFOW; lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO;
  var lpdwStatusFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM SetService}
{$ELSE}
function SetService(dwNameSpace, dwOperation, dwFlags: DWORD;
  const lpServiceInfo: SERVICE_INFOA; lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO;
  var lpdwStatusFlags: DWORD): Integer; stdcall;
{$EXTERNALSYM SetService}
{$ENDIF}

function GetServiceA(dwNameSpace: DWORD; const lpGuid: TGUID; lpServiceName: LPSTR;
  dwProperties: DWORD; lpBuffer: LPVOID; var lpdwBufferSize: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO): Integer; stdcall;
{$EXTERNALSYM GetServiceA}
function GetServiceW(dwNameSpace: DWORD; const lpGuid: TGUID; lpServiceName: LPWSTR;
  dwProperties: DWORD; lpBuffer: LPVOID; var lpdwBufferSize: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO): Integer; stdcall;
{$EXTERNALSYM GetServiceW}

{$IFDEF UNICODE}
function GetService(dwNameSpace: DWORD; const lpGuid: TGUID; lpServiceName: LPWSTR;
  dwProperties: DWORD; lpBuffer: LPVOID; var lpdwBufferSize: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO): Integer; stdcall;
{$EXTERNALSYM GetService}
{$ELSE}
function GetService(dwNameSpace: DWORD; const lpGuid: TGUID; lpServiceName: LPSTR;
  dwProperties: DWORD; lpBuffer: LPVOID; var lpdwBufferSize: DWORD;
  lpServiceAsyncInfo: LPSERVICE_ASYNC_INFO): Integer; stdcall;
{$EXTERNALSYM GetService}
{$ENDIF}

implementation

const
  nsplib = 'wsock32.dll';


{$IFDEF DYNAMIC_LINK}
var
  _EnumProtocolsA: Pointer;

function EnumProtocolsA;
begin
  GetProcedureAddress(_EnumProtocolsA, nsplib, 'EnumProtocolsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumProtocolsA]
  end;
end;
{$ELSE}
function EnumProtocolsA; external nsplib name 'EnumProtocolsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _EnumProtocolsW: Pointer;

function EnumProtocolsW;
begin
  GetProcedureAddress(_EnumProtocolsW, nsplib, 'EnumProtocolsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumProtocolsW]
  end;
end;
{$ELSE}
function EnumProtocolsW; external nsplib name 'EnumProtocolsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumProtocols: Pointer;

function EnumProtocols;
begin
  GetProcedureAddress(_EnumProtocols, nsplib, 'EnumProtocolsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumProtocols]
  end;
end;
{$ELSE}
function EnumProtocols; external nsplib name 'EnumProtocolsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _EnumProtocols: Pointer;

function EnumProtocols;
begin
  GetProcedureAddress(_EnumProtocols, nsplib, 'EnumProtocolsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_EnumProtocols]
  end;
end;
{$ELSE}
function EnumProtocols; external nsplib name 'EnumProtocolsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetAddressByNameA: Pointer;

function GetAddressByNameA;
begin
  GetProcedureAddress(_GetAddressByNameA, nsplib, 'GetAddressByNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAddressByNameA]
  end;
end;
{$ELSE}
function GetAddressByNameA; external nsplib name 'GetAddressByNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetAddressByNameW: Pointer;

function GetAddressByNameW;
begin
  GetProcedureAddress(_GetAddressByNameW, nsplib, 'GetAddressByNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAddressByNameW]
  end;
end;
{$ELSE}
function GetAddressByNameW; external nsplib name 'GetAddressByNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAddressByName: Pointer;

function GetAddressByName;
begin
  GetProcedureAddress(_GetAddressByName, nsplib, 'GetAddressByNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAddressByName]
  end;
end;
{$ELSE}
function GetAddressByName; external nsplib name 'GetAddressByNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetAddressByName: Pointer;

function GetAddressByName;
begin
  GetProcedureAddress(_GetAddressByName, nsplib, 'GetAddressByNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetAddressByName]
  end;
end;
{$ELSE}
function GetAddressByName; external nsplib name 'GetAddressByNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetTypeByNameA: Pointer;

function GetTypeByNameA;
begin
  GetProcedureAddress(_GetTypeByNameA, nsplib, 'GetTypeByNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTypeByNameA]
  end;
end;
{$ELSE}
function GetTypeByNameA; external nsplib name 'GetTypeByNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetTypeByNameW: Pointer;

function GetTypeByNameW;
begin
  GetProcedureAddress(_GetTypeByNameW, nsplib, 'GetTypeByNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTypeByNameW]
  end;
end;
{$ELSE}
function GetTypeByNameW; external nsplib name 'GetTypeByNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTypeByName: Pointer;

function GetTypeByName;
begin
  GetProcedureAddress(_GetTypeByName, nsplib, 'GetTypeByNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTypeByName]
  end;
end;
{$ELSE}
function GetTypeByName; external nsplib name 'GetTypeByNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetTypeByName: Pointer;

function GetTypeByName;
begin
  GetProcedureAddress(_GetTypeByName, nsplib, 'GetTypeByNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetTypeByName]
  end;
end;
{$ELSE}
function GetTypeByName; external nsplib name 'GetTypeByNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetNameByTypeA: Pointer;

function GetNameByTypeA;
begin
  GetProcedureAddress(_GetNameByTypeA, nsplib, 'GetNameByTypeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNameByTypeA]
  end;
end;
{$ELSE}
function GetNameByTypeA; external nsplib name 'GetNameByTypeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetNameByTypeW: Pointer;

function GetNameByTypeW;
begin
  GetProcedureAddress(_GetNameByTypeW, nsplib, 'GetNameByTypeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNameByTypeW]
  end;
end;
{$ELSE}
function GetNameByTypeW; external nsplib name 'GetNameByTypeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetNameByType: Pointer;

function GetNameByType;
begin
  GetProcedureAddress(_GetNameByType, nsplib, 'GetNameByTypeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNameByType]
  end;
end;
{$ELSE}
function GetNameByType; external nsplib name 'GetNameByTypeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetNameByType: Pointer;

function GetNameByType;
begin
  GetProcedureAddress(_GetNameByType, nsplib, 'GetNameByTypeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetNameByType]
  end;
end;
{$ELSE}
function GetNameByType; external nsplib name 'GetNameByTypeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceA: Pointer;

function SetServiceA;
begin
  GetProcedureAddress(_SetServiceA, nsplib, 'SetServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceA]
  end;
end;
{$ELSE}
function SetServiceA; external nsplib name 'SetServiceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _SetServiceW: Pointer;

function SetServiceW;
begin
  GetProcedureAddress(_SetServiceW, nsplib, 'SetServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetServiceW]
  end;
end;
{$ELSE}
function SetServiceW; external nsplib name 'SetServiceW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _SetService: Pointer;

function SetService;
begin
  GetProcedureAddress(_SetService, nsplib, 'SetServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetService]
  end;
end;
{$ELSE}
function SetService; external nsplib name 'SetServiceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _SetService: Pointer;

function SetService;
begin
  GetProcedureAddress(_SetService, nsplib, 'SetServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_SetService]
  end;
end;
{$ELSE}
function SetService; external nsplib name 'SetServiceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceA: Pointer;

function GetServiceA;
begin
  GetProcedureAddress(_GetServiceA, nsplib, 'GetServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceA]
  end;
end;
{$ELSE}
function GetServiceA; external nsplib name 'GetServiceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _GetServiceW: Pointer;

function GetServiceW;
begin
  GetProcedureAddress(_GetServiceW, nsplib, 'GetServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetServiceW]
  end;
end;
{$ELSE}
function GetServiceW; external nsplib name 'GetServiceW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _GetService: Pointer;

function GetService;
begin
  GetProcedureAddress(_GetService, nsplib, 'GetServiceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetService]
  end;
end;
{$ELSE}
function GetService; external nsplib name 'GetServiceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _GetService: Pointer;

function GetService;
begin
  GetProcedureAddress(_GetService, nsplib, 'GetServiceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_GetService]
  end;
end;
{$ELSE}
function GetService; external nsplib name 'GetServiceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

end.
