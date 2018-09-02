{******************************************************************************}
{                                                       	               }
{ DHCP Client API interface unit for Object Pascal                             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dhcpcsdk.h, released June 2000. The original Pascal    }
{ code is: DhcpCSdk.pas, released December 2000. The initial developer of the  }
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

unit JwaDhcpCSdk;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dhcpcsdk.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
// DHCP Standard Options.
//

const
  OPTION_PAD                 = 0;
  {$EXTERNALSYM OPTION_PAD}
  OPTION_SUBNET_MASK         = 1;
  {$EXTERNALSYM OPTION_SUBNET_MASK}
  OPTION_TIME_OFFSET         = 2;
  {$EXTERNALSYM OPTION_TIME_OFFSET}
  OPTION_ROUTER_ADDRESS      = 3;
  {$EXTERNALSYM OPTION_ROUTER_ADDRESS}
  OPTION_TIME_SERVERS        = 4;
  {$EXTERNALSYM OPTION_TIME_SERVERS}
  OPTION_IEN116_NAME_SERVERS = 5;
  {$EXTERNALSYM OPTION_IEN116_NAME_SERVERS}
  OPTION_DOMAIN_NAME_SERVERS = 6;
  {$EXTERNALSYM OPTION_DOMAIN_NAME_SERVERS}
  OPTION_LOG_SERVERS         = 7;
  {$EXTERNALSYM OPTION_LOG_SERVERS}
  OPTION_COOKIE_SERVERS      = 8;
  {$EXTERNALSYM OPTION_COOKIE_SERVERS}
  OPTION_LPR_SERVERS         = 9;
  {$EXTERNALSYM OPTION_LPR_SERVERS}
  OPTION_IMPRESS_SERVERS     = 10;
  {$EXTERNALSYM OPTION_IMPRESS_SERVERS}
  OPTION_RLP_SERVERS         = 11;
  {$EXTERNALSYM OPTION_RLP_SERVERS}
  OPTION_HOST_NAME           = 12;
  {$EXTERNALSYM OPTION_HOST_NAME}
  OPTION_BOOT_FILE_SIZE      = 13;
  {$EXTERNALSYM OPTION_BOOT_FILE_SIZE}
  OPTION_MERIT_DUMP_FILE     = 14;
  {$EXTERNALSYM OPTION_MERIT_DUMP_FILE}
  OPTION_DOMAIN_NAME         = 15;
  {$EXTERNALSYM OPTION_DOMAIN_NAME}
  OPTION_SWAP_SERVER         = 16;
  {$EXTERNALSYM OPTION_SWAP_SERVER}
  OPTION_ROOT_DISK           = 17;
  {$EXTERNALSYM OPTION_ROOT_DISK}
  OPTION_EXTENSIONS_PATH     = 18;
  {$EXTERNALSYM OPTION_EXTENSIONS_PATH}

//
// IP layer parameters - per host
//

  OPTION_BE_A_ROUTER              = 19;
  {$EXTERNALSYM OPTION_BE_A_ROUTER}
  OPTION_NON_LOCAL_SOURCE_ROUTING = 20;
  {$EXTERNALSYM OPTION_NON_LOCAL_SOURCE_ROUTING}
  OPTION_POLICY_FILTER_FOR_NLSR   = 21;
  {$EXTERNALSYM OPTION_POLICY_FILTER_FOR_NLSR}
  OPTION_MAX_REASSEMBLY_SIZE      = 22;
  {$EXTERNALSYM OPTION_MAX_REASSEMBLY_SIZE}
  OPTION_DEFAULT_TTL              = 23;
  {$EXTERNALSYM OPTION_DEFAULT_TTL}
  OPTION_PMTU_AGING_TIMEOUT       = 24;
  {$EXTERNALSYM OPTION_PMTU_AGING_TIMEOUT}
  OPTION_PMTU_PLATEAU_TABLE       = 25;
  {$EXTERNALSYM OPTION_PMTU_PLATEAU_TABLE}

//
// Link layer parameters - per interface.
//

  OPTION_MTU                      = 26;
  {$EXTERNALSYM OPTION_MTU}
  OPTION_ALL_SUBNETS_MTU          = 27;
  {$EXTERNALSYM OPTION_ALL_SUBNETS_MTU}
  OPTION_BROADCAST_ADDRESS        = 28;
  {$EXTERNALSYM OPTION_BROADCAST_ADDRESS}
  OPTION_PERFORM_MASK_DISCOVERY   = 29;
  {$EXTERNALSYM OPTION_PERFORM_MASK_DISCOVERY}
  OPTION_BE_A_MASK_SUPPLIER       = 30;
  {$EXTERNALSYM OPTION_BE_A_MASK_SUPPLIER}
  OPTION_PERFORM_ROUTER_DISCOVERY = 31;
  {$EXTERNALSYM OPTION_PERFORM_ROUTER_DISCOVERY}
  OPTION_ROUTER_SOLICITATION_ADDR = 32;
  {$EXTERNALSYM OPTION_ROUTER_SOLICITATION_ADDR}
  OPTION_STATIC_ROUTES            = 33;
  {$EXTERNALSYM OPTION_STATIC_ROUTES}
  OPTION_TRAILERS                 = 34;
  {$EXTERNALSYM OPTION_TRAILERS}
  OPTION_ARP_CACHE_TIMEOUT        = 35;
  {$EXTERNALSYM OPTION_ARP_CACHE_TIMEOUT}
  OPTION_ETHERNET_ENCAPSULATION   = 36;
  {$EXTERNALSYM OPTION_ETHERNET_ENCAPSULATION}

//
// TCP Paramters - per host
//

  OPTION_TTL                  = 37;
  {$EXTERNALSYM OPTION_TTL}
  OPTION_KEEP_ALIVE_INTERVAL  = 38;
  {$EXTERNALSYM OPTION_KEEP_ALIVE_INTERVAL}
  OPTION_KEEP_ALIVE_DATA_SIZE = 39;
  {$EXTERNALSYM OPTION_KEEP_ALIVE_DATA_SIZE}

//
// Application Layer Parameters
//

  OPTION_NETWORK_INFO_SERVICE_DOM = 40;
  {$EXTERNALSYM OPTION_NETWORK_INFO_SERVICE_DOM}
  OPTION_NETWORK_INFO_SERVERS     = 41;
  {$EXTERNALSYM OPTION_NETWORK_INFO_SERVERS}
  OPTION_NETWORK_TIME_SERVERS     = 42;
  {$EXTERNALSYM OPTION_NETWORK_TIME_SERVERS}

//
// Vender specific information option
//

  OPTION_VENDOR_SPEC_INFO = 43;
  {$EXTERNALSYM OPTION_VENDOR_SPEC_INFO}

//
// NetBIOS over TCP/IP Name server option
//

  OPTION_NETBIOS_NAME_SERVER     = 44;
  {$EXTERNALSYM OPTION_NETBIOS_NAME_SERVER}
  OPTION_NETBIOS_DATAGRAM_SERVER = 45;
  {$EXTERNALSYM OPTION_NETBIOS_DATAGRAM_SERVER}
  OPTION_NETBIOS_NODE_TYPE       = 46;
  {$EXTERNALSYM OPTION_NETBIOS_NODE_TYPE}
  OPTION_NETBIOS_SCOPE_OPTION    = 47;
  {$EXTERNALSYM OPTION_NETBIOS_SCOPE_OPTION}

//
// X Window System Options.
//

  OPTION_XWINDOW_FONT_SERVER     = 48;
  {$EXTERNALSYM OPTION_XWINDOW_FONT_SERVER}
  OPTION_XWINDOW_DISPLAY_MANAGER = 49;
  {$EXTERNALSYM OPTION_XWINDOW_DISPLAY_MANAGER}

//
// Other extensions
//

  OPTION_REQUESTED_ADDRESS      = 50;
  {$EXTERNALSYM OPTION_REQUESTED_ADDRESS}
  OPTION_LEASE_TIME             = 51;
  {$EXTERNALSYM OPTION_LEASE_TIME}
  OPTION_OK_TO_OVERLAY          = 52;
  {$EXTERNALSYM OPTION_OK_TO_OVERLAY}
  OPTION_MESSAGE_TYPE           = 53;
  {$EXTERNALSYM OPTION_MESSAGE_TYPE}
  OPTION_SERVER_IDENTIFIER      = 54;
  {$EXTERNALSYM OPTION_SERVER_IDENTIFIER}
  OPTION_PARAMETER_REQUEST_LIST = 55;
  {$EXTERNALSYM OPTION_PARAMETER_REQUEST_LIST}
  OPTION_MESSAGE                = 56;
  {$EXTERNALSYM OPTION_MESSAGE}
  OPTION_MESSAGE_LENGTH         = 57;
  {$EXTERNALSYM OPTION_MESSAGE_LENGTH}
  OPTION_RENEWAL_TIME           = 58; // T1
  {$EXTERNALSYM OPTION_RENEWAL_TIME}
  OPTION_REBIND_TIME            = 59; // T2
  {$EXTERNALSYM OPTION_REBIND_TIME}
  OPTION_CLIENT_CLASS_INFO      = 60;
  {$EXTERNALSYM OPTION_CLIENT_CLASS_INFO}
  OPTION_CLIENT_ID              = 61;
  {$EXTERNALSYM OPTION_CLIENT_ID}

  OPTION_TFTP_SERVER_NAME = 66;
  {$EXTERNALSYM OPTION_TFTP_SERVER_NAME}
  OPTION_BOOTFILE_NAME    = 67;
  {$EXTERNALSYM OPTION_BOOTFILE_NAME}

  OPTION_END = 255;
  {$EXTERNALSYM OPTION_END}

type
  _DHCPAPI_PARAMS = record
    Flags: ULONG;      // for future use
    OptionId: ULONG;   // what option is this?
    IsVendor: BOOL;    // is this vendor specific?
    Data: LPBYTE;      // the actual data
    nBytesData: DWORD; // how many bytes of data are there in Data?
  end;
  {$EXTERNALSYM _DHCPAPI_PARAMS}
  DHCPAPI_PARAMS = _DHCPAPI_PARAMS;
  {$EXTERNALSYM DHCPAPI_PARAMS}
  LPDHCPAPI_PARAMS = ^DHCPAPI_PARAMS;
  {$EXTERNALSYM LPDHCPAPI_PARAMS}
  PDHCPAPI_PARAMS = ^DHCPAPI_PARAMS;
  {$EXTERNALSYM PDHCPAPI_PARAMS}
  TDhcpApiParams = DHCPAPI_PARAMS;
  PDhcpApiParams = PDHCPAPI_PARAMS;

  DHCPCAPI_PARAMS = DHCPAPI_PARAMS;
  {$EXTERNALSYM DHCPCAPI_PARAMS}
  PDHCPCAPI_PARAMS = ^DHCPCAPI_PARAMS;
  {$EXTERNALSYM PDHCPCAPI_PARAMS}
  LPDHCPCAPI_PARAMS = ^DHCPCAPI_PARAMS;
  {$EXTERNALSYM LPDHCPCAPI_PARAMS}
  TDhcpCApiParams = DHCPCAPI_PARAMS;
  PDhcpCApiParams = PDHCPCAPI_PARAMS;

  _DHCPCAPI_PARAMS_ARRAY = record
    nParams: ULONG;            // size of array
    Params: PDHCPCAPI_PARAMS;  // actual array
  end;
  {$EXTERNALSYM _DHCPCAPI_PARAMS_ARRAY}
  DHCPCAPI_PARAMS_ARRAY = _DHCPCAPI_PARAMS_ARRAY;
  {$EXTERNALSYM DHCPCAPI_PARAMS_ARRAY}
  LPDHCPCAPI_PARAMS_ARRAY = ^DHCPCAPI_PARAMS_ARRAY;
  {$EXTERNALSYM LPDHCPCAPI_PARAMS_ARRAY}
  PDHCPCAPI_PARAMS_ARRAY = ^DHCPCAPI_PARAMS_ARRAY;
  {$EXTERNALSYM PDHCPCAPI_PARAMS_ARRAY}
  TDhcpcApiParamsArray = DHCPCAPI_PARAMS_ARRAY;
  PDhcpcApiParamsArray = PDHCPCAPI_PARAMS_ARRAY;

  _DHCPCAPI_CLASSID = record
    Flags: ULONG;      // must be zero currently.
    Data: LPBYTE;      // classid binary data.
    nBytesData: ULONG; // how many bytes of data are there?
  end;
  {$EXTERNALSYM _DHCPCAPI_CLASSID}
  DHCPCAPI_CLASSID = _DHCPCAPI_CLASSID;
  {$EXTERNALSYM DHCPCAPI_CLASSID}
  LPDHCPCAPI_CLASSID = ^DHCPCAPI_CLASSID;
  {$EXTERNALSYM LPDHCPCAPI_CLASSID}
  PDHCPCAPI_CLASSID = ^DHCPCAPI_CLASSID;
  {$EXTERNALSYM PDHCPCAPI_CLASSID}
  TDhcpcApiClassId = DHCPCAPI_CLASSID;
  PDhcpcApiClassId = PDHCPCAPI_CLASSID;

const
  DHCPCAPI_REQUEST_PERSISTENT   = $01; // request this options "permanently"
  {$EXTERNALSYM DHCPCAPI_REQUEST_PERSISTENT}
  DHCPCAPI_REQUEST_SYNCHRONOUS  = $02; // request and block on it
  {$EXTERNALSYM DHCPCAPI_REQUEST_SYNCHRONOUS}
  DHCPCAPI_REQUEST_ASYNCHRONOUS = $04; // request and return, set event on completion
  {$EXTERNALSYM DHCPCAPI_REQUEST_ASYNCHRONOUS}
  DHCPCAPI_REQUEST_CANCEL       = $08; // cancel request
  {$EXTERNALSYM DHCPCAPI_REQUEST_CANCEL}
  DHCPCAPI_REQUEST_MASK         = $0F; // allowed flags..
  {$EXTERNALSYM DHCPCAPI_REQUEST_MASK}

function DhcpCApiInitialize(var Version: DWORD): DWORD; stdcall;
{$EXTERNALSYM DhcpCApiInitialize}

procedure DhcpCApiCleanup; stdcall;
{$EXTERNALSYM DhcpCApiCleanup}

function DhcpRequestParams(Flags: DWORD; Reserved: LPVOID; AdapterName: LPWSTR;
  ClassId: PDHCPCAPI_CLASSID; SendParams, RecdParams: DHCPCAPI_PARAMS_ARRAY;
  Buffer: LPBYTE; pSize: LPDWORD; RequestIdStr: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DhcpRequestParams}

function DhcpUndoRequestParams(Flags: DWORD; Reserved: LPVOID; AdapterName: LPWSTR;
  RequestIdStr: LPWSTR): DWORD; stdcall;
{$EXTERNALSYM DhcpUndoRequestParams}

const
  DHCPCAPI_REGISTER_HANDLE_EVENT = $01; // handle returned is to an event
  {$EXTERNALSYM DHCPCAPI_REGISTER_HANDLE_EVENT}

function DhcpRegisterParamChange(Flags: DWORD; Reserved: LPVOID; AdapterName: LPWSTR;
  ClassId: PDHCPCAPI_CLASSID; Params: DHCPCAPI_PARAMS_ARRAY; Handle: LPVOID): DWORD; stdcall;
{$EXTERNALSYM DhcpRegisterParamChange}

const
  DHCPCAPI_DEREGISTER_HANDLE_EVENT = $01; // de-register handle that is an event
  {$EXTERNALSYM DHCPCAPI_DEREGISTER_HANDLE_EVENT}

function DhcpDeRegisterParamChange(Flags: DWORD; Reserved, Event: LPVOID): DWORD; stdcall;
{$EXTERNALSYM DhcpDeRegisterParamChange}

function DhcpRemoveDNSRegistrations: DWORD; stdcall;
{$EXTERNALSYM DhcpRemoveDNSRegistrations}

implementation

const
  dhcpapi = 'dhcpcsvc.dll';


{$IFDEF DYNAMIC_LINK}
var
  _DhcpCApiInitialize: Pointer;

function DhcpCApiInitialize;
begin
  GetProcedureAddress(_DhcpCApiInitialize, dhcpapi, 'DhcpCApiInitialize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DhcpCApiInitialize]
  end;
end;
{$ELSE}
function DhcpCApiInitialize; external dhcpapi name 'DhcpCApiInitialize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DhcpCApiCleanup: Pointer;

procedure DhcpCApiCleanup;
begin
  GetProcedureAddress(_DhcpCApiCleanup, dhcpapi, 'DhcpCApiCleanup');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DhcpCApiCleanup]
  end;
end;
{$ELSE}
procedure DhcpCApiCleanup; external dhcpapi name 'DhcpCApiCleanup';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DhcpRequestParams: Pointer;

function DhcpRequestParams;
begin
  GetProcedureAddress(_DhcpRequestParams, dhcpapi, 'DhcpRequestParams');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DhcpRequestParams]
  end;
end;
{$ELSE}
function DhcpRequestParams; external dhcpapi name 'DhcpRequestParams';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DhcpUndoRequestParams: Pointer;

function DhcpUndoRequestParams;
begin
  GetProcedureAddress(_DhcpUndoRequestParams, dhcpapi, 'DhcpUndoRequestParams');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DhcpUndoRequestParams]
  end;
end;
{$ELSE}
function DhcpUndoRequestParams; external dhcpapi name 'DhcpUndoRequestParams';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DhcpRegisterParamChange: Pointer;

function DhcpRegisterParamChange;
begin
  GetProcedureAddress(_DhcpRegisterParamChange, dhcpapi, 'DhcpRegisterParamChange');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DhcpRegisterParamChange]
  end;
end;
{$ELSE}
function DhcpRegisterParamChange; external dhcpapi name 'DhcpRegisterParamChange';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DhcpDeRegisterParamChange: Pointer;

function DhcpDeRegisterParamChange;
begin
  GetProcedureAddress(_DhcpDeRegisterParamChange, dhcpapi, 'DhcpDeRegisterParamChange');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DhcpDeRegisterParamChange]
  end;
end;
{$ELSE}
function DhcpDeRegisterParamChange; external dhcpapi name 'DhcpDeRegisterParamChange';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _DhcpRemoveDNSRegistrations: Pointer;

function DhcpRemoveDNSRegistrations;
begin
  GetProcedureAddress(_DhcpRemoveDNSRegistrations, dhcpapi, 'DhcpRemoveDNSRegistrations');
  asm
    mov esp, ebp
    pop ebp
    jmp [_DhcpRemoveDNSRegistrations]
  end;
end;
{$ELSE}
function DhcpRemoveDNSRegistrations; external dhcpapi name 'DhcpRemoveDNSRegistrations';
{$ENDIF DYNAMIC_LINK}

end.
