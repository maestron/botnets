{******************************************************************************}
{                                                       	               }
{ Winsock2 Vines IP API interface Unit for Object Pascal                       }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wsvns.h, released June 2000. The original Pascal       }
{ code is: WSvns.pas, released December 2000. The initial developer of the     }
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

unit JwaWSvns;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wsvns.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2;

//
// Windows Sockets include file for VINES IP.  This file contains all
// standardized VINES IP information.  Include this header file after winsock.h.
//
// To open an VINES IP socket, call socket() with an address family of AF_BAN, a
// socket type of SOCK_DGRAM, SOCK_STREAM, or SOCK_SEQPACKET, and protocol of 0.
//

//
// Socket address, VINES IP style.  Address fields and port field are defined
// as a sequence of bytes.  This is done because they are byte ordered
// BIG ENDIAN, ala most significant byte first.
//

type
  SOCKADDR_VNS = record
    sin_family: u_short;                 // = AF_BAN
    net_address: array [0..3] of u_char; // network address
    subnet_addr: array [0..1] of u_char; // subnet address
    port: array [0..1] of u_char;        // msb=port[0], lsb=port[1]
    hops: u_char;                        // # hops for broadcasts
    filler: array [0..4] of u_char;        // filler, zeros
  end;
  {$EXTERNALSYM SOCKADDR_VNS}
  PSOCKADDR_VNS = ^SOCKADDR_VNS;
  {$EXTERNALSYM PSOCKADDR_VNS}
  LPSOCKADDR_VNS = ^SOCKADDR_VNS;
  {$EXTERNALSYM LPSOCKADDR_VNS}
  TSockAddrVNS = SOCKADDR_VNS;
  PSockAddrVNS = LPSOCKADDR_VNS;

const
  VNSPROTO_IPC          = 1;
  {$EXTERNALSYM VNSPROTO_IPC}
  VNSPROTO_RELIABLE_IPC = 2;
  {$EXTERNALSYM VNSPROTO_RELIABLE_IPC}
  VNSPROTO_SPP          = 3;
  {$EXTERNALSYM VNSPROTO_SPP}

implementation

end.
