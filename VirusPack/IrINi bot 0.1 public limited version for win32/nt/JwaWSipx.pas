{******************************************************************************}
{                                                       	               }
{ Winsock2 IPX API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wsipx.h, released June 2000. The original Pascal       }
{ code is: WSIpx.pas, released December 2000. The initial developer of the     }
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

unit JwaWSipx;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wsipx.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//
//   Microsoft Windows
//   Copyright (C) Microsoft Corporation, 1992-1999.
//
//   Windows Sockets include file for IPX/SPX.  This file contains all
//   standardized IPX/SPX information.  Include this header file after
//   winsock.h.
//
//   To open an IPX socket, call socket() with an address family of
//   AF_IPX, a socket type of SOCK_DGRAM, and protocol NSPROTO_IPX.
//   Note that the protocol value must be specified, it cannot be 0.
//   All IPX packets are sent with the packet type field of the IPX
//   header set to 0.
//
//   To open an SPX or SPXII socket, call socket() with an address
//   family of AF_IPX, socket type of SOCK_SEQPACKET or SOCK_STREAM,
//   and protocol of NSPROTO_SPX or NSPROTO_SPXII.  If SOCK_SEQPACKET
//   is specified, then the end of message bit is respected, and
//   recv() calls are not completed until a packet is received with
//   the end of message bit set.  If SOCK_STREAM is specified, then
//   the end of message bit is not respected, and recv() completes
//   as soon as any data is received, regardless of the setting of the
//   end of message bit.  Send coalescing is never performed, and sends
//   smaller than a single packet are always sent with the end of
//   message bit set.  Sends larger than a single packet are packetized
//   with the end of message bit set on only the last packet of the
//   send.
//

//
//   This is the structure of the SOCKADDR structure for IPX and SPX.
//

type
  SOCKADDR_IPX = record
    sa_family: Smallint;
    sa_netnum: array [0..3] of Char;
    sa_nodenum: array [0..5] of Char;
    sa_socket: Word;
  end;
  {$EXTERNALSYM SOCKADDR_IPX}
  PSOCKADDR_IPX = ^SOCKADDR_IPX;
  {$EXTERNALSYM PSOCKADDR_IPX}
  LPSOCKADDR_IPX = ^SOCKADDR_IPX;
  {$EXTERNALSYM LPSOCKADDR_IPX}
  TSockAddrIPX = SOCKADDR_IPX;
  PSockAddrIPX = LPSOCKADDR_IPX;

//
//   Protocol families used in the "protocol" parameter of the socket() API.
//

const
  NSPROTO_IPX   = 1000;
  {$EXTERNALSYM NSPROTO_IPX}
  NSPROTO_SPX   = 1256;
  {$EXTERNALSYM NSPROTO_SPX}
  NSPROTO_SPXII = 1257;
  {$EXTERNALSYM NSPROTO_SPXII}

implementation

end.
