{******************************************************************************}
{                                                       	               }
{ Winsock2 IPX/SPX Extensions API interface Unit for Object Pascal             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wsipx.h, released June 2000. The original Pascal       }
{ code is: WSIpxpas, released December 2000. The initial developer of the      }
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

unit JwaWSNwLink;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wsnwlink.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2;

//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992-1999.
//   Microsoft-specific extensions to the Windows NT IPX/SPX Windows
//   Sockets interface.  These extensions are provided for use as
//   necessary for compatibility with existing applications.  They are
//   otherwise not recommended for use, as they are only guaranteed to
//   work *   over the Microsoft IPX/SPX stack.  An application which
//   uses these *   extensions may not work over other IPX/SPX
//   implementations.  Include this header file after winsock.h and
//   wsipx.h.
//
//   To open an IPX socket where a particular packet type is sent in
//   the IPX header, specify NSPROTO_IPX + n as the protocol parameter
//   of the socket() API.  For example, to open an IPX socket that
//   sets the packet type to 34, use the following socket() call:
//
//       s = socket(AF_IPX, SOCK_DGRAM, NSPROTO_IPX + 34);
//
//   Below are socket option that may be set or retrieved by specifying
//   the appropriate manifest in the "optname" parameter of getsockopt()
//   or setsockopt().  Use NSPROTO_IPX as the "level" argument for the
//   call.
//

//
//   Set/get the IPX packet type.  The value specified in the
//   optval argument will be set as the packet type on every IPX
//   packet sent from this socket.  The optval parameter of
//   getsockopt()/setsockopt() points to an int.
//

const
  IPX_PTYPE = $4000;
  {$EXTERNALSYM IPX_PTYPE}

//
//   Set/get the receive filter packet type.  Only IPX packets with
//   a packet type equal to the value specified in the optval
//   argument will be returned; packets with a packet type that
//   does not match are discarded.  optval points to an int.
//

  IPX_FILTERPTYPE = $4001;
  {$EXTERNALSYM IPX_FILTERPTYPE}

//
//   Stop filtering on packet type set with IPX_FILTERPTYPE.
//

  IPX_STOPFILTERPTYPE = $4003;
  {$EXTERNALSYM IPX_STOPFILTERPTYPE}

//
//   Set/get the value of the datastream field in the SPX header on
//   every packet sent.  optval points to an int.
//

  IPX_DSTYPE = $4002;
  {$EXTERNALSYM IPX_DSTYPE}

//
//   Enable extended addressing.  On sends, adds the element
//   "unsigned char sa_ptype" to the SOCKADDR_IPX structure,
//   making the total length 15 bytes.  On receives, add both
//   the sa_ptype and "unsigned char sa_flags" to the SOCKADDR_IPX
//   structure, making the total length 16 bytes.  The current
//   bits defined in sa_flags are:
//
//   0x01 - the received frame was sent as a broadcast
//   0x02 - the received frame was sent from this machine
//
//   optval points to a BOOL.
//

  IPX_EXTENDED_ADDRESS = $4004;
  {$EXTERNALSYM IPX_EXTENDED_ADDRESS}

//
//   Send protocol header up on all receive packets.  optval points
//   to a BOOL.
//

  IPX_RECVHDR = $4005;
  {$EXTERNALSYM IPX_RECVHDR}

//
//   Get the maximum data size that can be sent.  Not valid with
//   setsockopt().  optval points to an int where the value is
//   returned.
//

  IPX_MAXSIZE = $4006;
  {$EXTERNALSYM IPX_MAXSIZE}

//
//   Query information about a specific adapter that IPX is bound
//   to.  In a system with n adapters they are numbered 0 through n-1.
//   Callers can issue the IPX_MAX_ADAPTER_NUM getsockopt() to find
//   out the number of adapters present, or call IPX_ADDRESS with
//   increasing values of adapternum until it fails.  Not valid
//   with setsockopt().  optval points to an instance of the
//   IPX_ADDRESS_DATA structure with the adapternum filled in.
//

  IPX_ADDRESS = $4007;
  {$EXTERNALSYM IPX_ADDRESS}

// mvb LongBool's in the following record changed to Boolean's (JCP)

type
  _IPX_ADDRESS_DATA = record
    adapternum: Integer;             // input: 0-based adapter number
    netnum: array [0..3] of UCHAR;   // output: IPX network number
    nodenum: array [0..5] of UCHAR;  // output: IPX node address
    wan: Boolean;                    // output: TRUE = adapter is on a wan link
    status: Boolean;                 // output: TRUE = wan link is up (or adapter is not wan)
    maxpkt: Integer;                 // output: max packet size, not including IPX header
    linkspeed: ULONG;                // output: link speed in 100 bytes/sec (i.e. 96 == 9600 bps)
  end;
  {$EXTERNALSYM _IPX_ADDRESS_DATA}
  IPX_ADDRESS_DATA = _IPX_ADDRESS_DATA;
  {$EXTERNALSYM IPX_ADDRESS_DATA}
  PIPX_ADDRESS_DATA = ^IPX_ADDRESS_DATA;
  {$EXTERNALSYM PIPX_ADDRESS_DATA}
  TIpxAddressData = IPX_ADDRESS_DATA;
  PIpxAddressData = PIPX_ADDRESS_DATA;  

//
//   Query information about a specific IPX network number.  If the
//   network is in IPX's cache it will return the information directly,
//   otherwise it will issue RIP requests to find it.  Not valid with
//   setsockopt().  optval points to an instance of the IPX_NETNUM_DATA
//   structure with the netnum filled in.
//

const
  IPX_GETNETINFO = $4008;
  {$EXTERNALSYM IPX_GETNETINFO}

type
  _IPX_NETNUM_DATA = record
    netnum: array [0..3] of UCHAR;  // input: IPX network number
    hopcount: USHORT;               // output: hop count to this network, in machine order
    netdelay: USHORT;               // output: tick count to this network, in machine order
    cardnum: Integer;               // output: 0-based adapter number used to route to this net;
                                    //         can be used as adapternum input to IPX_ADDRESS
    router: array [0..5] of UCHAR;  // output: MAC address of the next hop router, zeroed if
                                    //         the network is directly attached
  end;
  {$EXTERNALSYM _IPX_NETNUM_DATA}
  IPX_NETNUM_DATA = _IPX_NETNUM_DATA;
  {$EXTERNALSYM IPX_NETNUM_DATA}
  PIPX_NETNUM_DATA = ^IPX_NETNUM_DATA;
  {$EXTERNALSYM PIPX_NETNUM_DATA}
  TIpxNetNumData = IPX_NETNUM_DATA;
  PIpxNetNumData = PIPX_NETNUM_DATA;

//
//   Like IPX_GETNETINFO except it *does not* issue RIP requests. If the
//   network is in IPX's cache it will return the information, otherwise
//   it will fail (see also IPX_RERIPNETNUMBER which *always* forces a
//   re-RIP). Not valid with setsockopt().  optval points to an instance of
//   the IPX_NETNUM_DATA structure with the netnum filled in.
//

const
  IPX_GETNETINFO_NORIP = $4009;
  {$EXTERNALSYM IPX_GETNETINFO_NORIP}

//
//   Get information on a connected SPX socket.  optval points
//   to an instance of the IPX_SPXCONNSTATUS_DATA structure.
//
//   All numbers are in Novell (high-low) order.
//

  IPX_SPXGETCONNECTIONSTATUS = $400B;
  {$EXTERNALSYM IPX_SPXGETCONNECTIONSTATUS}

type
  _IPX_SPXCONNSTATUS_DATA = record
    ConnectionState: UCHAR;
    WatchDogActive: UCHAR;
    LocalConnectionId: USHORT;
    RemoteConnectionId: USHORT;
    LocalSequenceNumber: USHORT;
    LocalAckNumber: USHORT;
    LocalAllocNumber: USHORT;
    RemoteAckNumber: USHORT;
    RemoteAllocNumber: USHORT;
    LocalSocket: USHORT;
    ImmediateAddress: array [0..5] of UCHAR;
    RemoteNetwork: array [0..3] of UCHAR;
    RemoteNode: array [0..5] of UCHAR;
    RemoteSocket: USHORT;
    RetransmissionCount: USHORT;
    EstimatedRoundTripDelay: USHORT; // In milliseconds
    RetransmittedPackets: USHORT;
    SuppressedPacket: USHORT;
  end;
  {$EXTERNALSYM _IPX_SPXCONNSTATUS_DATA}
  IPX_SPXCONNSTATUS_DATA = _IPX_SPXCONNSTATUS_DATA;
  {$EXTERNALSYM IPX_SPXCONNSTATUS_DATA}
  PIPX_SPXCONNSTATUS_DATA = ^IPX_SPXCONNSTATUS_DATA;
  {$EXTERNALSYM PIPX_SPXCONNSTATUS_DATA}
  TIpxSpcConnStatusData = IPX_SPXCONNSTATUS_DATA;
  PIpxSpcConnStatusData = PIPX_SPXCONNSTATUS_DATA;  

//
//   Get notification when the status of an adapter that IPX is
//   bound to changes.  Typically this will happen when a wan line
//   goes up or down.  Not valid with setsockopt().  optval points
//   to a buffer which contains an IPX_ADDRESS_DATA structure
//   followed immediately by a HANDLE to an unsignaled event.
//
//   When the getsockopt() query is submitted, it will complete
//   successfully.  However, the IPX_ADDRESS_DATA pointed to by
//   optval will not be updated at that point.  Instead the
//   request is queued internally inside the transport.
//
//   When the status of an adapter changes, IPX will locate a
//   queued getsockopt() query and fill in all the fields in the
//   IPX_ADDRESS_DATA structure.  It will then signal the event
//   pointed to by the HANDLE in the optval buffer.  This handle
//   should be obtained before calling getsockopt() by calling
//   CreateEvent().  If multiple getsockopts() are submitted at
//   once, different events must be used.
//
//   The event is used because the call needs to be asynchronous
//   but currently getsockopt() does not support this.
//
//   WARNING: In the current implementation, the transport will
//   only signal one queued query for each status change.  Therefore
//   only one service which uses this query should be running at
//   once.
//

const
  IPX_ADDRESS_NOTIFY = $400C;
  {$EXTERNALSYM IPX_ADDRESS_NOTIFY}

//
//   Get the maximum number of adapters present.  If this call returns
//   n then the adapters are numbered 0 through n-1.  Not valid
//   with setsockopt().  optval points to an int where the value
//   is returned.
//

  IPX_MAX_ADAPTER_NUM = $400D;
  {$EXTERNALSYM IPX_MAX_ADAPTER_NUM}

//
//   Like IPX_GETNETINFO except it forces IPX to re-RIP even if the
//   network is in its cache (but not if it is directly attached to).
//   Not valid with setsockopt().  optval points to an instance of
//   the IPX_NETNUM_DATA structure with the netnum filled in.
//

  IPX_RERIPNETNUMBER = $400E;
  {$EXTERNALSYM IPX_RERIPNETNUMBER}

//
//   A hint that broadcast packets may be received.  The default is
//   TRUE.  Applications that do not need to receive broadcast packets
//   should set this sockopt to FALSE which may cause better system
//   performance (note that it does not necessarily cause broadcasts
//   to be filtered for the application).  Not valid with getsockopt().
//   optval points to a BOOL.
//

  IPX_RECEIVE_BROADCAST = $400F;
  {$EXTERNALSYM IPX_RECEIVE_BROADCAST}

//
//   On SPX connections, don't delay before sending ack.  Applications
//   that do not tend to have back-and-forth traffic over SPX should
//   set this; it will increase the number of acks sent but will remove
//   delays in sending acks.  optval points to a BOOL.
//

  IPX_IMMEDIATESPXACK = $4010;
  {$EXTERNALSYM IPX_IMMEDIATESPXACK}

implementation

end.
