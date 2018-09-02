{******************************************************************************}
{                                                       	               }
{ Winsock2 Netbios API interface Unit for Object Pascal                        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wsnetbs.h, released June 2000. The original Pascal     }
{ code is: WSnetbs.pas, released December 2000. The initial developer of the   }
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

unit JwaWSnetbs;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wsnetbs.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2;

//
//   wsnetbs.h
//   Copyright (c) 1994-1999, Microsoft Corp. All rights reserved.
//
//   Windows Sockets include file for NETBIOS.  This file contains all
//   standardized NETBIOS information.  Include this header file after
//   winsock.h.
//

//
//   This is the structure of the SOCKADDR structure for NETBIOS.
//

const
  NETBIOS_NAME_LENGTH = 16;
  {$EXTERNALSYM NETBIOS_NAME_LENGTH}

type
  SOCKADDR_NB = record
    snb_family: Smallint;
    snb_type: Word;
    snb_name: array [0..NETBIOS_NAME_LENGTH - 1] of Char;
  end;
  {$EXTERNALSYM SOCKADDR_NB}
  PSOCKADDR_NB = ^SOCKADDR_NB;
  {$EXTERNALSYM PSOCKADDR_NB}
  LPSOCKADDR_NB = ^SOCKADDR_NB;
  {$EXTERNALSYM LPSOCKADDR_NB}
  TSockAddrNB = SOCKADDR_NB;
  PSockAddrNB = LPSOCKADDR_NB;

//
// Bit values for the snb_type field of SOCKADDR_NB.
//

const
  NETBIOS_UNIQUE_NAME       = $0000;
  {$EXTERNALSYM NETBIOS_UNIQUE_NAME}
  NETBIOS_GROUP_NAME        = $0001;
  {$EXTERNALSYM NETBIOS_GROUP_NAME}
  NETBIOS_TYPE_QUICK_UNIQUE = $0002;
  {$EXTERNALSYM NETBIOS_TYPE_QUICK_UNIQUE}
  NETBIOS_TYPE_QUICK_GROUP  = $0003;
  {$EXTERNALSYM NETBIOS_TYPE_QUICK_GROUP}

//
// A macro convenient for setting up NETBIOS SOCKADDRs.
//

procedure SET_NETBIOS_SOCKADDR(var SNB: TSockAddrNB; _Type: u_short; const Name: string; Port: Byte);
{$EXTERNALSYM SET_NETBIOS_SOCKADDR}

//
//   To open a NetBIOS socket, call the socket() function as follows:
//
//       s = socket( AF_NETBIOS, {SOCK_SEQPACKET|SOCK_DGRAM}, -Lana );
//
//   where Lana is the NetBIOS Lana number of interest.  For example, to
//   open a socket for Lana 2, specify -2 as the "protocol" parameter
//   to the socket() function.
//

implementation

procedure SET_NETBIOS_SOCKADDR(var SNB: TSockAddrNB; _Type: u_short; const Name: string; Port: Byte);
var
  I: Integer;
begin
  SNB.snb_family := AF_NETBIOS;
  SNB.snb_type := _Type;
  for I := 0 to NETBIOS_NAME_LENGTH - 1 do SNB.snb_name[I] := ' ';
  I := 0;
  while I < NETBIOS_NAME_LENGTH - 1 do
  begin
    if SNB.snb_name[I] = #0 then Break;
    SNB.snb_name[I] := SNB.snb_name[I + 1];
    Inc(I);
  end;
  SNB.snb_name[NETBIOS_NAME_LENGTH - 1] := Char(Port);
end;

end.
