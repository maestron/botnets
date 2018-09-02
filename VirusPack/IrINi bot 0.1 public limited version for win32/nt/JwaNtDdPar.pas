{******************************************************************************}
{                                                                              }
{ Parallel Port Driver Interface Unit for Object Pascal                        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2003 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ntddpar.h , released June 2000. The original Pascal    }
{ code is: JwaNtDdPar, released December 2003. The initial developer of the    }
{ Pascal code is Pasha Sivtsov (ps4me@mail.ru).                                }
{                                                                              }
{ Contributor(s): Pasha Sivtsov (ps4me@mail.ru)                                }
{                                                                              }
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

unit JwaNtDdPar;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ntddk.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinIoctl;

const
  // Parallel port device GUIDs
  GUID_DEVINTERFACE_PARALLEL: TGUID = (
    D1:$97F76EF0; D2:$F883; D3:$11D0; D4:($AF,$1F,$00,$00,$F8,$00,$84,$5C));
  {$EXTERNALSYM GUID_DEVINTERFACE_PARALLEL}
  GUID_DEVINTERFACE_PARCLASS: TGUID = (
    D1:$811FC6A5; D2:$F728; D3:$11D0; D4:($A5,$37,$00,$00,$F8,$75,$3E,$D1));
  {$EXTERNALSYM GUID_DEVINTERFACE_PARCLASS}

  GUID_PARALLEL_DEVICE: TGUID = (
    D1:$97F76EF0; D2:$F883; D3:$11D0; D4:($AF,$1F,$00,$00,$F8,$00,$84,$5C));
  {$EXTERNALSYM GUID_PARALLEL_DEVICE}
  GUID_PARCLASS_DEVICE: TGUID = (
    D1:$811FC6A5; D2:$F728; D3:$11D0; D4:($A5,$37,$00,$00,$F8,$75,$3E,$D1));
  {$EXTERNALSYM GUID_PARCLASS_DEVICE}

  IOCTL_IEEE1284_GET_MODE = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (5 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_IEEE1284_GET_MODE}
  IOCTL_IEEE1284_NEGOTIATE = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (6 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_IEEE1284_NEGOTIATE}
  IOCTL_PAR_GET_DEFAULT_MODES = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (10 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_GET_DEFAULT_MODES}
  IOCTL_PAR_GET_DEVICE_CAPS = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (9 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_GET_DEVICE_CAPS}
  IOCTL_PAR_IS_PORT_FREE = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (21 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_IS_PORT_FREE}
  IOCTL_PAR_QUERY_DEVICE_ID = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (3 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_QUERY_DEVICE_ID}
  IOCTL_PAR_QUERY_DEVICE_ID_SIZE = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (4 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_QUERY_DEVICE_ID_SIZE}
  IOCTL_PAR_QUERY_INFORMATION = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (1 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_QUERY_INFORMATION}
  IOCTL_PAR_QUERY_LOCATION = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (22 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_QUERY_LOCATION}
  IOCTL_PAR_QUERY_RAW_DEVICE_ID = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (12 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_QUERY_RAW_DEVICE_ID}
  IOCTL_PAR_SET_INFORMATION = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (2 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_SET_INFORMATION}
  IOCTL_PAR_SET_READ_ADDRESS = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (8 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_SET_READ_ADDRESS}
  IOCTL_PAR_SET_WRITE_ADDRESS = (
    (FILE_DEVICE_PARALLEL_PORT shl 16) or (FILE_ANY_ACCESS shl 14) or
    (7 shl 2) or METHOD_BUFFERED);
  {$EXTERNALSYM IOCTL_PAR_SET_WRITE_ADDRESS}

type
  PPAR_DEVICE_ID_SIZE_INFORMATION = ^PAR_DEVICE_ID_SIZE_INFORMATION;
  {$EXTERNALSYM PPAR_DEVICE_ID_SIZE_INFORMATION}
  _PAR_DEVICE_ID_SIZE_INFORMATION = record
    DeviceIdSize: ULONG;
  end;
  {$EXTERNALSYM _PAR_DEVICE_ID_SIZE_INFORMATION}
  PAR_DEVICE_ID_SIZE_INFORMATION = _PAR_DEVICE_ID_SIZE_INFORMATION;
  {$EXTERNALSYM PAR_DEVICE_ID_SIZE_INFORMATION}
  TParDeviceIdSizeInformation = PAR_DEVICE_ID_SIZE_INFORMATION;
  PParDeviceIdSizeInformation = PPAR_DEVICE_ID_SIZE_INFORMATION;

const
  PARALLEL_INIT          = $01;
  {$EXTERNALSYM PARALLEL_INIT}
  PARALLEL_AUTOFEED      = $02;
  {$EXTERNALSYM PARALLEL_AUTOFEED}
  PARALLEL_PAPER_EMPTY   = $04;
  {$EXTERNALSYM PARALLEL_PAPER_EMPTY}
  PARALLEL_OFF_LINE      = $08;
  {$EXTERNALSYM PARALLEL_OFF_LINE}
  PARALLEL_POWER_OFF     = $10;
  {$EXTERNALSYM PARALLEL_POWER_OFF}
  PARALLEL_NOT_CONNECTED = $20;
  {$EXTERNALSYM PARALLEL_NOT_CONNECTED}
  PARALLEL_BUSY          = $40;
  {$EXTERNALSYM PARALLEL_BUSY}
  PARALLEL_SELECTED      = $80;
  {$EXTERNALSYM PARALLEL_SELECTED}

type
  PPAR_QUERY_INFORMATION = ^PAR_QUERY_INFORMATION;
  {$EXTERNALSYM PPAR_QUERY_INFORMATION}
  _PAR_QUERY_INFORMATION = record
    Status: UCHAR;
  end;
  {$EXTERNALSYM _PAR_QUERY_INFORMATION}
  PAR_QUERY_INFORMATION = _PAR_QUERY_INFORMATION;
  {$EXTERNALSYM PAR_QUERY_INFORMATION}
  TParQueryInformation = PAR_QUERY_INFORMATION;
  PParQueryInformation = PPAR_QUERY_INFORMATION;

  PPAR_SET_INFORMATION = ^PAR_SET_INFORMATION;
  {$EXTERNALSYM PPAR_SET_INFORMATION}
  _PAR_SET_INFORMATION = record
    Init: UCHAR;
  end;
  {$EXTERNALSYM _PAR_SET_INFORMATION}
  PAR_SET_INFORMATION = _PAR_SET_INFORMATION;
  {$EXTERNALSYM PAR_SET_INFORMATION}
  TParSetInformation = PAR_SET_INFORMATION;
  PParSetInformation = PPAR_SET_INFORMATION;

  PPARCLASS_NEGOTIATION_MASK = ^PARCLASS_NEGOTIATION_MASK;
  {$EXTERNALSYM PPARCLASS_NEGOTIATION_MASK}
  _PARCLASS_NEGOTIATION_MASK = record
    usReadMask: USHORT;
    usWriteMask: USHORT;
  end;
  {$EXTERNALSYM _PARCLASS_NEGOTIATION_MASK}
  PARCLASS_NEGOTIATION_MASK = _PARCLASS_NEGOTIATION_MASK;
  {$EXTERNALSYM PARCLASS_NEGOTIATION_MASK}
  TParClassNegotiationMask = PARCLASS_NEGOTIATION_MASK;
  PParClassNegotiationMask = PPARCLASS_NEGOTIATION_MASK;

const
  NONE               = $0000;
  {$EXTERNALSYM NONE}
  CENTRONICS         = $0001;
  {$EXTERNALSYM CENTRONICS}
  IEEE_COMPATIBILITY = $0002;
  {$EXTERNALSYM IEEE_COMPATIBILITY}
  NIBBLE             = $0004;
  {$EXTERNALSYM NIBBLE}
  CHANNEL_NIBBLE     = $0008;
  {$EXTERNALSYM CHANNEL_NIBBLE}
  BYTE_BIDIR         = $0010;
  {$EXTERNALSYM BYTE_BIDIR}
  EPP_HW             = $0020;
  {$EXTERNALSYM EPP_HW}
  EPP_SW             = $0040;
  {$EXTERNALSYM EPP_SW}
  EPP_ANY            = $0060;
  {$EXTERNALSYM EPP_ANY}
  BOUNDED_ECP        = $0080;
  {$EXTERNALSYM BOUNDED_ECP}
  ECP_HW_NOIRQ       = $0100;
  {$EXTERNALSYM ECP_HW_NOIRQ}
  ECP_HW_IRQ         = $0200;
  {$EXTERNALSYM ECP_HW_IRQ}
  ECP_SW             = $0400;
  {$EXTERNALSYM ECP_SW}
  ECP_ANY            = $0780;
  {$EXTERNALSYM ECP_ANY}

implementation

end.
