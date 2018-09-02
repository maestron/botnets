{******************************************************************************}
{                                                       	               }
{ DHCP Callout DLL API interface unit for Object Pascal                        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dhcpssdk.h, released June 2000. The original Pascal    }
{ code is: DhcpSSdk.pas, released December 2000. The initial developer of the  }
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

unit JwaDhcpSSdk;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dhcpssdk.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef DHCP_IP_ADDRESS *LPDHCP_IP_ADDRESS;'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType;

//  This structure could change any day.  This will be accurate only for version 0 -- which
//  has to be checked for by any CalloutDLL that is hooking onto the DhcpHandleOptionsHook.

type
  DHCP_IP_ADDRESS = DWORD;
  {$EXTERNALSYM DHCP_IP_ADDRESS}
  LPDHCP_IP_ADDRESS = ^DHCP_IP_ADDRESS;
  {$NODEFINE LPDHCP_IP_ADDRESS}
  TDhcpIpAddress = DHCP_IP_ADDRESS;

  _DHCP_SERVER_OPTIONS = record
    MessageType: LPBYTE;
    SubnetMask: LPDHCP_IP_ADDRESS;
    RequestedAddress: LPDHCP_IP_ADDRESS;
    RequestLeaseTime: LPDWORD;
    OverlayFields: LPBYTE;
    RouterAddress: LPDHCP_IP_ADDRESS;
    Server: LPDHCP_IP_ADDRESS;
    ParameterRequestList: LPBYTE;
    ParameterRequestListLength: DWORD;
    MachineName: PCHAR;
    MachineNameLength: DWORD;
    ClientHardwareAddressType: BYTE;
    ClientHardwareAddressLength: BYTE;
    ClientHardwareAddress: LPBYTE;
    ClassIdentifier: PCHAR;
    ClassIdentifierLength: DWORD;
    VendorClass: LPBYTE;
    VendorClassLength: DWORD;
    DNSFlags: DWORD;
    DNSNameLength: DWORD;
    DNSName: LPBYTE;
    DSDomainNameRequested: LongBool;
    DSDomainName: PCHAR;
    DSDomainNameLen: DWORD;
    ScopeId: LPDWORD;
  end;
  {$EXTERNALSYM _DHCP_SERVER_OPTIONS}
  DHCP_SERVER_OPTIONS = _DHCP_SERVER_OPTIONS;
  {$EXTERNALSYM DHCP_SERVER_OPTIONS}
  LPDHCP_SERVER_OPTIONS = ^DHCP_SERVER_OPTIONS;
  {$EXTERNALSYM LPDHCP_SERVER_OPTIONS}
  TDhcpServerOptions = DHCP_SERVER_OPTIONS;
  PDhcpServerOptions = LPDHCP_SERVER_OPTIONS;

//
// The location in registry where the REG_MULTI_SZ list of callout DLLs
// that the DHCP Server will try to load.
//

const
  DHCP_CALLOUT_LIST_KEY    = WideString('System\CurrentControlSet\Services\DHCPServer\Parameters');
  {$EXTERNALSYM DHCP_CALLOUT_LIST_KEY}
  DHCP_CALLOUT_LIST_VALUE  = WideString('CalloutDlls');
  {$EXTERNALSYM DHCP_CALLOUT_LIST_VALUE}
  DHCP_CALLOUT_LIST_TYPE   = REG_MULTI_SZ;
  {$EXTERNALSYM DHCP_CALLOUT_LIST_TYPE}
  DHCP_CALLOUT_ENTRY_POINT = 'DhcpServerCalloutEntry';
  {$EXTERNALSYM DHCP_CALLOUT_ENTRY_POINT}

//
// Control CODES used by DHCP Server to notify server state change.
//

  DHCP_CONTROL_START    = $00000001;
  {$EXTERNALSYM DHCP_CONTROL_START}
  DHCP_CONTROL_STOP     = $00000002;
  {$EXTERNALSYM DHCP_CONTROL_STOP}
  DHCP_CONTROL_PAUSE    = $00000003;
  {$EXTERNALSYM DHCP_CONTROL_PAUSE}
  DHCP_CONTROL_CONTINUE = $00000004;
  {$EXTERNALSYM DHCP_CONTROL_CONTINUE}

//
// Other ControlCodes used by various Callout HOOKS.
//

  DHCP_DROP_DUPLICATE      = $00000001; // duplicate of pkt being processed
  {$EXTERNALSYM DHCP_DROP_DUPLICATE}
  DHCP_DROP_NOMEM          = $00000002; // not enough server mem in queues
  {$EXTERNALSYM DHCP_DROP_NOMEM}
  DHCP_DROP_INTERNAL_ERROR = $00000003; // ooops?
  {$EXTERNALSYM DHCP_DROP_INTERNAL_ERROR}
  DHCP_DROP_TIMEOUT        = $00000004; // too late, pkt is too old
  {$EXTERNALSYM DHCP_DROP_TIMEOUT}
  DHCP_DROP_UNAUTH         = $00000005; // server is not authorized to run
  {$EXTERNALSYM DHCP_DROP_UNAUTH}
  DHCP_DROP_PAUSED         = $00000006; // service is paused
  {$EXTERNALSYM DHCP_DROP_PAUSED}
  DHCP_DROP_NO_SUBNETS     = $00000007; // no subnets configured on server
  {$EXTERNALSYM DHCP_DROP_NO_SUBNETS}
  DHCP_DROP_INVALID        = $00000008; // invalid packet or client
  {$EXTERNALSYM DHCP_DROP_INVALID}
  DHCP_DROP_WRONG_SERVER   = $00000009; // client in different DS enterprise
  {$EXTERNALSYM DHCP_DROP_WRONG_SERVER}
  DHCP_DROP_NOADDRESS      = $0000000A; // no address available to offer
  {$EXTERNALSYM DHCP_DROP_NOADDRESS}
  DHCP_DROP_PROCESSED      = $0000000B; // packet has been processed
  {$EXTERNALSYM DHCP_DROP_PROCESSED}
  DHCP_DROP_GEN_FAILURE    = $00000100; // catch-all error
  {$EXTERNALSYM DHCP_DROP_GEN_FAILURE}
  DHCP_SEND_PACKET         = $10000000; // send the packet on wire
  {$EXTERNALSYM DHCP_SEND_PACKET}
  DHCP_PROB_CONFLICT       = $20000001; // address conflicted..
  {$EXTERNALSYM DHCP_PROB_CONFLICT}
  DHCP_PROB_DECLINE        = $20000002; // an addr got declined
  {$EXTERNALSYM DHCP_PROB_DECLINE}
  DHCP_PROB_RELEASE        = $20000003; // an addr got released
  {$EXTERNALSYM DHCP_PROB_RELEASE}
  DHCP_PROB_NACKED         = $20000004; // a client is being nacked.
  {$EXTERNALSYM DHCP_PROB_NACKED}
  DHCP_GIVE_ADDRESS_NEW    = $30000001; // give client a "new" address
  {$EXTERNALSYM DHCP_GIVE_ADDRESS_NEW}
  DHCP_GIVE_ADDRESS_OLD    = $30000002; // renew client's "old" address
  {$EXTERNALSYM DHCP_GIVE_ADDRESS_OLD}
  DHCP_CLIENT_BOOTP        = $30000003; // client is a BOOTP client
  {$EXTERNALSYM DHCP_CLIENT_BOOTP}
  DHCP_CLIENT_DHCP         = $30000004; // client is a DHCP client
  {$EXTERNALSYM DHCP_CLIENT_DHCP}

type
  LPDHCP_CONTROL = function (dwControlCode: DWORD; lpReserved: LPVOID): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_CONTROL}
  PDhcpControl = LPDHCP_CONTROL;

{
Routine Description:

    This routine is called whenever the DHCP Server service is
    started, stopped, paused or continued as defined by the values of
    the dwControlCode parameter.  The lpReserved parameter is reserved
    for future use and it should not be interpreted in any way.   This
    routine should not block.

Arguments:

    dwControlCode - one of the DHCP_CONTROL_* values
    lpReserved - reserved for future use.

}


type
  LPDHCP_NEWPKT = function (var Packet: LPBYTE; var PacketSize: DWORD; IpAddress: DWORD;
    Reserved: LPVOID; var PktContext: LPVOID; ProcessIt: LPBOOL): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_NEWPKT}
  PDhcpNewPkt = LPDHCP_NEWPKT;

{
Routine Description:

    This routine is called soon after the DHCP Server receives a
    packet that it attempts to process.  This routine is in the
    critical path of server execution and should return very fast, as
    otherwise server performance will be impacted.  The Callout DLL
    can modify the buffer or return a new buffer via the Packet,
    PacketSize arguments.  Also, if the callout DLL has internal
    structures to keep track of the packet and its progress, it can
    then return a context to this packet in the PktContext parameter.
    This context will be passed to almost all other hooks to indicate
    the packet being referred to.  Also, if the Callout DLL is
    planning on processing the packet or for some other reason the
    DHCP server is not expected to process this packet, then it can
    set the ProcessIt flag to FALSE to indicate that the packet is to
    be dropped.

Arguments:

    Packet - This parameter points to a character buffer that holds
    the actual packet received by the DHCP Server.

    PacketSize - This parameter points to a variable that holds the
    size of the above buffer.

    IpAddress - This parameter points to an IPV4 host order IP address
    of the socket that this packet was received on.

    Reserved -Reserved for future use.

    PktContect - This is an opaque pointer used by the DHCP Server for
    future references to this packet.  It is expected that the callout
    DLL will provide this pointer if it is interested in keeping track
    of the packet.  (See the descriptions for the hooks below for
    other usage of this Context).

    ProcessIt - This is a BOOL flag that the CalloutDll can set to
    TRUE or reset to indicate if the DHCP Server should continue
    processing this packet or not, respectively.
}

type
  LPDHCP_DROP_SEND = function (var Packet: LPBYTE; var PacketSize: DWORD;
    ControlCode, IpAddress: DWORD; Reserved, PktContext: LPVOID): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_DROP_SEND}
  PDhcpDropSend = LPDHCP_DROP_SEND;

{
Routine Description:

    This hook is called if a packet is (DropPktHook) dropped for some
    reason or if the packet is completely processed.   (If a packet is
    dropped, the hook is called twice as it is called once again to
    note that the packet has been completely processed).  The callout
    DLL should  be prepared to handle this hook multiple times for a
    packet. This routine should not block. The ControlCode parameter
    defines the reasons for the packet being dropped:

    * DHCP_DROP_DUPLICATE - This packet is a duplicate of another
      received by the server.
    * DHCP_DROP_NOMEM - Not enough memory to process the packet.
    * DHCP_DROP_INTERNAL_ERROR - Unexpected nternal error occurred.
    * DHCP_DROP_TIMEOUT - The packet is too old to process.
    * DHCP_DROP_UNAUTH - The server is not authorized.
    * DHCP_DROP_PAUSED - The server is paused.
    * DHCP_DROP_NO_SUBNETS - There are no subnets configured.
    * DHCP_DROP_INVALID - The packet is invalid or it came on an
      invalid socket ..
    * DHCP_DROP_WRONG_SERVER - The packet was sent to the wrong DHCP Server.
    * DHCP_DROP_NOADDRESS - There is no address to offer.
    * DHCP_DROP_PROCESSED - The packet has been processed.
    * DHCP_DROP_GEN_FAILURE - An unknown error occurred.

    This routine is also called right before a response is sent down
    the wire (SendPktHook) and in this case the ControlCode has a
    value of DHCP_SEND_PACKET.

Arguments:

    Packet - This parameter points to a character buffer that holds
    the packet being processed by the DHCP Server.

    PacketSize - This parameter points to a variable that holds the
    size of the above buffer.

    ControlCode - See description for various control codes.

    IpAddress - This parameter points to an IPV4 host order IP address
    of the socket that this packet was received on.

    Reserved - Reserved for future use.

    PktContext - This parameter is the packet context that the Callout
    DLL NewPkt Hook returned for this packet.  This can be used to
    track a packet.
}

type
  LPDHCP_PROB = function (Packet: LPBYTE; PacketSize, ControlCode, IpAddress,
    AltAddress: DWORD; Reserved, PktContext: LPVOID): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_PROB}
  PDhcpProb = LPDHCP_PROB;

{
Routine Description:

    This routine is called whenever special events occur that cause
    the packet to be dropped etc.  The possible ControlCodes and their
    meanings are as follows:

    * DHCP_PROB_CONFLICT - The address attempted to be offered
      (AltAddress) is in use in the network already.
    * DHCP_PROB_DECLINE - The packet was a DECLINE message for the
      address specified in AltAddress.
    * DHCP_PROB_RELEASE - The packet was a RELEASE message for the
      address specified in AltAddress.
    * DHCP_PROB_NACKED - The packet was a REQUEST message for address
      specified in AltAddress and it was NACKed by the server.

    This routine should not block.

Arguments:

    Packet - This parameter is the buffer of the packet being
    processed.

    PacketSize - This is the size of the above buffer.

    ControlCode - Specifies the event. See description below for
    control codes and meanings.

    IpAddress - IpV4 address of socket this packet was received on.

    AltAddress - Request IpV4 Address or Ip address that is in
    conflict.

    Reserved - Reserve for future use.

    PktContext - This is the context returned by the NewPkt hook for
    this packet.
}

type
  LPDHCP_GIVE_ADDRESS = function (Packet: LPBYTE; PacketSize, ControlCode, IpAddress,
    AltAddress, AddrType, LeaseTime: DWORD; Reserved, PktContext: LPVOID): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_GIVE_ADDRESS}
  PDhcpGiveAddress = LPDHCP_GIVE_ADDRESS;

{
Routine Description:

    This routine is called when the server is about to send an ACK to
    a REQUEST message.  The ControlCode specifies if the address is a
    totally new address or if it an renewal of an old address (with
    values DHCP_GIVE_ADDRESS_NEW and DHCP_GIVE_ADDRESS_OLD
    respectively). The address being offered is passed as the
    AltAddress parameter and the AddrType parameter can be one of
    DHCP_CLIENT_BOOTP or DHCP_CLIENT_DHCP indicating whether the
    client is using BOOTP or DHCP respectively. This call should not
    block.

Arguments:

    Packet - This parameter is the buffer of the packet being
    processed.

    PacketSize - This is the size of the above buffer.

    ControlCode -  See description above for control codes and
    meanings.

    IpAddress - IpV4 address of socket this packet was received on.

    AltAddress - IpV4 address being ACKed to the client.

    AddrType - Is this a DHCP or BOOTP address?

    LeaseTime - Lease duration being passed.

    Reserved - Reserve for future use.

    PktContext - This is the context returned by the NewPkt hook for
    this packet.
}

type
  LPDHCP_HANDLE_OPTIONS = function (Packet: LPBYTE; PacketSize: DWORD;
    Reserved, PktContext: LPVOID; ServerOptions: DHCP_SERVER_OPTIONS): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_HANDLE_OPTIONS}
  TDhcpHandleOptions = LPDHCP_HANDLE_OPTIONS;

{
Routine Description:

    This routine can be utilized by the CalloutDLL to avoid parsing
    the whole packet.  The packet is parsed by the server and some
    commonly used options are returned in the parsed pointers
    structure (see header for definition of DHCP_SERVER_OPTIONS).  The
    hook is expected to make a copy of the structure pointed to by
    ServerOptions if it needs it beyond this function call.  This
    routine may be called several times for a single packet.  This
    routine should not block.

Arguments:

    Packet - This parameter is the buffer of the packet being
    processed.

    PacketSize - This is the size of the above buffer.

    Reserved - Reserve for future use.

    PktContext - This is the context returned by the NewPkt hook for
    this packet.

    ServerOptions - This parameter is the structure that contains a
    bunch of pointers that represent corresponding options.
}

type
  LPDHCP_DELETE_CLIENT = function (IpAddress: DWORD; HwAddress: LPBYTE;
    HwAddressLength: ULONG; Reserved, ClientType: DWORD): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_DELETE_CLIENT}
  PDhcpDeleteClient = LPDHCP_DELETE_CLIENT;

{
Routine Description:

    This routine is called before a client lease is deleted off the
    active leases database.  The ClientType field is currently not
    provided and this should not be used.  This routine should not
    block.

Arguments:

    IpAddress - IpV4 address of the client lease being deleted.

    HwAddress - Buffer holding the Hardware address of the client (MAC).

    HwAddressLength - This specifies the length of the above buffer.

    Reserved - Reserved for future use.

    ClientType - Reserved for future use.
}

type
  _DHCP_CALLOUT_TABLE = record
    DhcpControlHook: LPDHCP_CONTROL;
    DhcpNewPktHook: LPDHCP_NEWPKT;
    DhcpPktDropHook: LPDHCP_DROP_SEND;
    DhcpPktSendHook: LPDHCP_DROP_SEND;
    DhcpAddressDelHook: LPDHCP_PROB;
    DhcpAddressOfferHook: LPDHCP_GIVE_ADDRESS;
    DhcpHandleOptionsHook: LPDHCP_HANDLE_OPTIONS;
    DhcpDeleteClientHook: LPDHCP_DELETE_CLIENT;
    DhcpExtensionHook: LPVOID;
    DhcpReservedHook: LPVOID;
  end;
  {$EXTERNALSYM _DHCP_CALLOUT_TABLE}
  DHCP_CALLOUT_TABLE = _DHCP_CALLOUT_TABLE;
  {$EXTERNALSYM DHCP_CALLOUT_TABLE}
  LPDHCP_CALLOUT_TABLE = ^DHCP_CALLOUT_TABLE;
  {$EXTERNALSYM LPDHCP_CALLOUT_TABLE}
  TDhcpCalloutTable = DHCP_CALLOUT_TABLE;
  PDhcpCalloutTable = LPDHCP_CALLOUT_TABLE;

type
  LPDHCP_ENTRY_POINT_FUNC = function (ChainDlls: LPWSTR; CalloutVersion: DWORD;
    var CalloutTbl: DHCP_CALLOUT_TABLE): DWORD; stdcall;
  {$EXTERNALSYM LPDHCP_ENTRY_POINT_FUNC}
  PDhcpEntryPointFunc = LPDHCP_ENTRY_POINT_FUNC;

{
Routine Description:

    This is the routine that is called by the DHCP Server when it
    successfully loads a DLL.    If the routine succeeds, then the
    DHCP Server does not attempt to load any of the DLLs specified in
    the ChainDlls list of DLLs.   If this function fails for some
    reason, then the DHCP Server proceeds to the next DLL in the
    ChainDlls structure.

    Note that for version negotiation, the server may call this
    routine several times until a compatible version is found.

    It is expected that the entrypoint routine would walk through the
    names of the dlls and attempt to load each of them and when it
    succeeds in retrieving the entry point, it attempts to get the
    cumulative set of hooks by repeating the above procedure (as done
    by the DHCP Server).

Arguments:

    ChainDlls - This is a set of DLL names in REG_MULTI_SZ format (as
    returned by Registry function calls).  This does not contain the
    name of the current DLL itself, but only the names of all DLLs
    that follow the current DLL.

    CalloutVersion - This is the version that the Callout DLL is
    expected to support.  The current version number is 0.

    CalloutTbl - This is the cumulative set of Hooks that is needed by
    the current DLLs as well as all the DLLs in ChainDlls.   It is the
    responsibility of the current DLL to retrive the cumulative set of
    Hooks and merge that with its own set of hooks and return that in
    this table structure.  The table structure is defined above.
}

implementation

end.
