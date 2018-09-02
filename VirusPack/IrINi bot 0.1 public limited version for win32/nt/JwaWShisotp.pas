{******************************************************************************}
{                                                       	               }
{ Winsock2 ISO TP4 API interface Unit for Object Pascal                        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wshisotp.h, released June 2000. The original Pascal    }
{ code is: WShisotp.pas, released December 2000. The initial developer of the  }
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

unit JwaWShisotp;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wshisotp.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2;

//
//   wshisotp.h
//   Copyright (c) 1994-1999, Microsoft Corp. All rights reserved.
//
//   Windows Sockets include file for ISO TP4.  This file contains all
//   standardized ISO TP4 information.  Include this header file after
//   winsock.h.
//
//   The information contained in this header file was originally
//   created by Alcatel TITN Inc.
//

//
// Protocol values for ISO transport protocols.
//

const
  ISOPROTO_TP0       = 25;     // connection orientated transport protocol
  {$EXTERNALSYM ISOPROTO_TP0}
  ISOPROTO_TP1       = 26;     // not implemented
  {$EXTERNALSYM ISOPROTO_TP1}
  ISOPROTO_TP2       = 27;     // not implemented
  {$EXTERNALSYM ISOPROTO_TP2}
  ISOPROTO_TP3       = 28;     // not implemented
  {$EXTERNALSYM ISOPROTO_TP3}
  ISOPROTO_TP4       = 29;     // connection orientated transport protocol
  {$EXTERNALSYM ISOPROTO_TP4}
  ISOPROTO_TP        = ISOPROTO_TP4;
  {$EXTERNALSYM ISOPROTO_TP}
  ISOPROTO_CLTP      = 30;     // connectionless transport
  {$EXTERNALSYM ISOPROTO_CLTP}
  ISOPROTO_CLNP      = 31;     // connectionless internetworking protocol
  {$EXTERNALSYM ISOPROTO_CLNP}
  ISOPROTO_X25       = 32;     // cons
  {$EXTERNALSYM ISOPROTO_X25}
  ISOPROTO_INACT_NL  = 33;     // inactive network layer
  {$EXTERNALSYM ISOPROTO_INACT_NL}
  ISOPROTO_ESIS      = 34;     // ES-IS protocol
  {$EXTERNALSYM ISOPROTO_ESIS}
  ISOPROTO_INTRAISIS = 35;     // IS-IS protocol
  {$EXTERNALSYM ISOPROTO_INTRAISIS}

  IPPROTO_RAW        = 255;    // raw clnp
  {$EXTERNALSYM IPPROTO_RAW}
  IPPROTO_MAX        = 256;
  {$EXTERNALSYM IPPROTO_MAX}

//
//   The maximum size of the tranport address (tp_addr field of a
//   sockaddr_tp structure) is 64.
//

const
  ISO_MAX_ADDR_LENGTH = 64;
  {$EXTERNALSYM ISO_MAX_ADDR_LENGTH}

//
//   There are two types of ISO addresses, hierarchical and
//   non-hierarchical.  For hierarchical addresses, the tp_addr
//   field contains both the transport selector and the network
//   address.  For non-hierarchical addresses, tp_addr contains only
//   the transport address, which must be translated by the ISO TP4
//   transport provider into the transport selector and network address.
//

const
  ISO_HIERARCHICAL     = 0;
  {$EXTERNALSYM ISO_HIERARCHICAL}
  ISO_NON_HIERARCHICAL = 1;
  {$EXTERNALSYM ISO_NON_HIERARCHICAL}

//
//   The format of the address structure (sockaddr) to pass to Windows
//   Sockets APIs.
//

type
  SOCKADDR_TP = record
   tp_family: u_short;    // Always AF_ISO
   tp_addr_type: u_short; // ISO_HIERARCHICAL or ISO_NON_HIERARCHICAL
   tp_taddr_len: u_short; // Length of transport address, <= 52
   tp_tsel_len: u_short;  // Length of transport selector, <= 32 0 if ISO_NON_HIERARCHICAL
   tp_addr: array [0..ISO_MAX_ADDR_LENGTH - 1] of u_char;
  end;
  {$EXTERNALSYM SOCKADDR_TP}
  PSOCKADDR_TP = ^SOCKADDR_TP;
  {$EXTERNALSYM PSOCKADDR_TP}
  LPSOCKADDR_TP = ^SOCKADDR_TP;
  {$EXTERNALSYM LPSOCKADDR_TP}
  TSockAddrTP = SOCKADDR_TP;
  PSockAddrTP = LPSOCKADDR_TP;  

//procedure ISO_SET_TP_ADDR(var sa_tp: TSockAddrTP; port: PChar; portlen: u_short; node: PChar; nodelen: u_short);
//{$EXTERNALSYM ISO_SET_TP_ADDR}

//
//   Expedited Data Usage Negotiation option.
//   Default when the option is not present is be EXP_DATA_USE
//   as per ISO 8073
//

const
  ISO_EXP_DATA_USE  = 00;    // Use of Expedited Data
  {$EXTERNALSYM ISO_EXP_DATA_USE}
  ISO_EXP_DATA_NUSE = 01;    // Non-use of Expedited Data
  {$EXTERNALSYM ISO_EXP_DATA_NUSE}

implementation

// TODO
//procedure ISO_SET_TP_ADDR(var sa_tp: TSockAddrTP; port: PChar; portlen: u_short; node: PChar; nodelen: u_short);
//begin
//  sa_tp.tp_family := AF_ISO;
//  sa_tp.tp_addr_type := ISO_HIERARCHICAL;
//  sa_tp.tp_tsel_len := portlen;
//  sa_tp.tp_taddr_len := portlen + nodelen;
//  System.Move(port, @sa_tp.tp_addr[0], portlen);
//  System.Move(node, @sa_tp.tp_addr[portlen], nodelen);
//end;

end.
