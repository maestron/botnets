{******************************************************************************}
{                                                       	               }
{ Winsock2 Protocol Definitions API interface Unit for Object Pascal           }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: protocol.h, released June 2000. The original Pascal    }
{ code is: Protocol.pas, released December 2000. The initial developer of the  }
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

unit JwaProtocol;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "protocol.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
{$IFDEF STANDALONE}
  JwaWinTypes;
{$ELSE}
  Windows;
{$ENDIF}

type
  ETHERNET_ADDRESS = array [0..5] of BYTE;
  {$EXTERNALSYM ETHERNET_ADDRESS}

  ETHERNET_FRAME = record
   Destination: ETHERNET_ADDRESS;
    Source: ETHERNET_ADDRESS;
    FrameType: WORD; // in host-order
  end;
  {$EXTERNALSYM ETHERNET_FRAME}
  TEthernetFrame = ETHERNET_FRAME;
  PEthernetFrame = ^TEthernetFrame;

const
  ETHERNET_FRAME_TYPE_IP = $0800;
  {$EXTERNALSYM ETHERNET_FRAME_TYPE_IP}

type
  IP_HEADER = record
    x: BYTE;
    tos: BYTE;
    length: WORD;
    identifier: WORD;
    fragment: WORD;
    ttl: BYTE;
    protocol: BYTE;
    cksum: WORD;
    src: DWORD;
    dest: DWORD;
  end;
  {$EXTERNALSYM IP_HEADER}
  LPIP_HEADER = ^IP_HEADER;
  {$EXTERNALSYM LPIP_HEADER}
  TIPHeader = IP_HEADER;
  PIPHeader = LPIP_HEADER;

const
  IP_MF = $2000;
  {$EXTERNALSYM IP_MF}
  IP_FRAGMENT_OFFSET_MASK = $1FFF;
  {$EXTERNALSYM IP_FRAGMENT_OFFSET_MASK}

  IP_HEADER_MINIMUM_LEN = 20;
  {$EXTERNALSYM IP_HEADER_MINIMUM_LEN}

type
  UDP_HEADER = record
    src_port: WORD;
    dest_port: WORD;
    length: WORD; // including this header
    checksum: WORD;
  end;
  {$EXTERNALSYM UDP_HEADER}
  TUDPHeader = UDP_HEADER;
  PUDPHeader = ^TUDPHeader;

const
  UDP_HEADER_LEN = 8;
  {$EXTERNALSYM UDP_HEADER_LEN}

implementation

end.
