{******************************************************************************}
{                                                       	               }
{ Winsock2 IRDA API interface Unit for Object Pascal                           }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ad_irda.h, released June 2000. The original Pascal     }
{ code is: AD_Irda.pas, released December 2000. The initial developer of the   }
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

unit JwaAF_Irda;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "af_irda.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2;

//
// Winsock1.1, IrDA1.1, WindowsNT5.0, Windows98 and WindowsCE1.0.
// Define one of _WIN32_WINNT, _WIN32_WINDOWS, _WIN32_WCE.
//  Copyright (C) Microsoft Corporation, 1994-1999.
//

const
  WINDOWS_AF_IRDA = 26;
  {$EXTERNALSYM WINDOWS_AF_IRDA}
  WINDOWS_PF_IRDA = WINDOWS_AF_IRDA;
  {$EXTERNALSYM WINDOWS_PF_IRDA}

  WCE_AF_IRDA = 22;
  {$EXTERNALSYM WCE_AF_IRDA}
  WCE_PF_IRDA = WCE_AF_IRDA;
  {$EXTERNALSYM WCE_PF_IRDA}

  //AF_IRDA = WINDOWS_AF_IRDA;
  //{$EXTERNALSYM AF_IRDA}

  IRDA_PROTO_SOCK_STREAM  = 1;
  {$EXTERNALSYM IRDA_PROTO_SOCK_STREAM}

  PF_IRDA = WINDOWS_AF_IRDA;
  {$EXTERNALSYM PF_IRDA}

  // WINNT, WIN98, WINCE

  SOL_IRLMP		 = $00FF;
  {$EXTERNALSYM SOL_IRLMP}

  IRLMP_ENUMDEVICES = $00000010;
  {$EXTERNALSYM IRLMP_ENUMDEVICES}
  IRLMP_IAS_SET     = $00000011;
  {$EXTERNALSYM IRLMP_IAS_SET}
  IRLMP_IAS_QUERY   = $00000012;
  {$EXTERNALSYM IRLMP_IAS_QUERY}

  // WINNT, WINCE

  IRLMP_SEND_PDU_LEN   = $00000013;
  {$EXTERNALSYM IRLMP_SEND_PDU_LEN}
  IRLMP_EXCLUSIVE_MODE = $00000014;
  {$EXTERNALSYM IRLMP_EXCLUSIVE_MODE}
  IRLMP_IRLPT_MODE     = $00000015;
  {$EXTERNALSYM IRLMP_IRLPT_MODE}
  IRLMP_9WIRE_MODE     = $00000016;
  {$EXTERNALSYM IRLMP_9WIRE_MODE}

  // WIN98

  IRLMP_TINYTP_MODE    = $00000017;
  {$EXTERNALSYM IRLMP_TINYTP_MODE}
  IRLMP_PARAMETERS     = $00000018;
  {$EXTERNALSYM IRLMP_PARAMETERS}
  IRLMP_DISCOVERY_MODE = $00000019;
  {$EXTERNALSYM IRLMP_DISCOVERY_MODE}

  // WINCE

  IRLMP_SHARP_MODE = $00000020;
  {$EXTERNALSYM IRLMP_SHARP_MODE}

  SIO_LAZY_DISCOVERY = $4004747F; // _IOR('t', 127, u_long)
  {$EXTERNALSYM SIO_LAZY_DISCOVERY}

  IAS_ATTRIB_NO_CLASS  = $00000010;
  {$EXTERNALSYM IAS_ATTRIB_NO_CLASS}
  IAS_ATTRIB_NO_ATTRIB = $00000000;
  {$EXTERNALSYM IAS_ATTRIB_NO_ATTRIB}
  IAS_ATTRIB_INT       = $00000001;
  {$EXTERNALSYM IAS_ATTRIB_INT}
  IAS_ATTRIB_OCTETSEQ  = $00000002;
  {$EXTERNALSYM IAS_ATTRIB_OCTETSEQ}
  IAS_ATTRIB_STR       = $00000003;
  {$EXTERNALSYM IAS_ATTRIB_STR}

  IAS_MAX_USER_STRING  = 256;
  {$EXTERNALSYM IAS_MAX_USER_STRING}
  IAS_MAX_OCTET_STRING = 1024;
  {$EXTERNALSYM IAS_MAX_OCTET_STRING}
  IAS_MAX_CLASSNAME    = 64;
  {$EXTERNALSYM IAS_MAX_CLASSNAME}
  IAS_MAX_ATTRIBNAME   = 256;
  {$EXTERNALSYM IAS_MAX_ATTRIBNAME}

const
  LM_HB_Extension =             128;    // Any hint byte
  {$EXTERNALSYM LM_HB_Extension}

  LM_HB1_PnP =                  1;      // First hint byte
  {$EXTERNALSYM LM_HB1_PnP}
  LM_HB1_PDA_Palmtop =          2;
  {$EXTERNALSYM LM_HB1_PDA_Palmtop}
  LM_HB1_Computer =             4;
  {$EXTERNALSYM LM_HB1_Computer}
  LM_HB1_Printer =              8;
  {$EXTERNALSYM LM_HB1_Printer}
  LM_HB1_Modem =                16;
  {$EXTERNALSYM LM_HB1_Modem}
  LM_HB1_Fax =                  32;
  {$EXTERNALSYM LM_HB1_Fax}
  LM_HB1_LANAccess =            64;
  {$EXTERNALSYM LM_HB1_LANAccess}

  LM_HB2_Telephony =            1;      // Second hint byte
  {$EXTERNALSYM LM_HB2_Telephony}
  LM_HB2_FileServer =           2;
  {$EXTERNALSYM LM_HB2_FileServer}

  LmCharSetASCII      = 0;
  {$EXTERNALSYM LmCharSetASCII}
  LmCharSetISO_8859_1 = 1;
  {$EXTERNALSYM LmCharSetISO_8859_1}
  LmCharSetISO_8859_2 = 2;
  {$EXTERNALSYM LmCharSetISO_8859_2}
  LmCharSetISO_8859_3 = 3;
  {$EXTERNALSYM LmCharSetISO_8859_3}
  LmCharSetISO_8859_4 = 4;
  {$EXTERNALSYM LmCharSetISO_8859_4}
  LmCharSetISO_8859_5 = 5;
  {$EXTERNALSYM LmCharSetISO_8859_5}
  LmCharSetISO_8859_6 = 6;
  {$EXTERNALSYM LmCharSetISO_8859_6}
  LmCharSetISO_8859_7 = 7;
  {$EXTERNALSYM LmCharSetISO_8859_7}
  LmCharSetISO_8859_8 = 8;
  {$EXTERNALSYM LmCharSetISO_8859_8}
  LmCharSetISO_8859_9 = 9;
  {$EXTERNALSYM LmCharSetISO_8859_9}
  LmCharSetUNICODE    = $ff;
  {$EXTERNALSYM LmCharSetUNICODE}

type
  LM_BAUD_RATE = u_long;
  {$EXTERNALSYM LM_BAUD_RATE}
  TLMBaudRate = LM_BAUD_RATE;
  PLMBaudRate = ^LM_BAUD_RATE;

const
  LM_BAUD_1200   = 1200;
  {$EXTERNALSYM LM_BAUD_1200}
  LM_BAUD_2400   = 2400;
  {$EXTERNALSYM LM_BAUD_2400}
  LM_BAUD_9600   = 9600;
  {$EXTERNALSYM LM_BAUD_9600}
  LM_BAUD_19200  = 19200;
  {$EXTERNALSYM LM_BAUD_19200}
  LM_BAUD_38400  = 38400;
  {$EXTERNALSYM LM_BAUD_38400}
  LM_BAUD_57600  = 57600;
  {$EXTERNALSYM LM_BAUD_57600}
  LM_BAUD_115200 = 115200;
  {$EXTERNALSYM LM_BAUD_115200}
  LM_BAUD_576K   = 576000;
  {$EXTERNALSYM LM_BAUD_576K}
  LM_BAUD_1152K  = 1152000;
  {$EXTERNALSYM LM_BAUD_1152K}
  LM_BAUD_4M     = 4000000;
  {$EXTERNALSYM LM_BAUD_4M}

type
  LM_IRPARMS = record
    nTXDataBytes: u_long;   // Max tx data bytes per packet
    nRXDataBytes: u_long;   // Max rx data bytes per packet
    nBaudRate: LM_BAUD_RATE;      // Negotiated baud rate
    thresholdTime: u_long;  // Threshold (ms)
    discTime: u_long;       // Disconnect (ms)
    nMSLinkTurn: u_short;    // Link turn around (ms)
    nTXPackets: u_char;     // Number packets in transmit window
    nRXPackets: u_char;     // Number packets in receive window
  end;
  {$EXTERNALSYM LM_IRPARMS}
  PLM_IRPARMS = ^LM_IRPARMS;
  TLmIrParms = LM_IRPARMS;
  PLmIrParms = PLM_IRPARMS;

  _SOCKADDR_IRDA = record
    irdaAddressFamily: u_short;
    irdaDeviceID: array [0..3] of u_char;
    irdaServiceName: array [0..24] of Char;
  end;
  {$EXTERNALSYM _SOCKADDR_IRDA}
  SOCKADDR_IRDA = _SOCKADDR_IRDA;
  {$EXTERNALSYM SOCKADDR_IRDA}
  PSOCKADDR_IRDA = ^SOCKADDR_IRDA;
  {$EXTERNALSYM PSOCKADDR_IRDA}
  LPSOCKADDR_IRDA = ^SOCKADDR_IRDA;
  {$EXTERNALSYM LPSOCKADDR_IRDA}
  TSockAddrIrda = SOCKADDR_IRDA;
  PSockAddrIrda = LPSOCKADDR_IRDA;

  _WINDOWS_IRDA_DEVICE_INFO = record
    irdaDeviceID: array [0..3] of u_char;
    irdaDeviceName: array [0..21] of Char;
    irdaDeviceHints1: u_char;
    irdaDeviceHints2: u_char;
    irdaCharSet: u_char;
  end;
  {$EXTERNALSYM _WINDOWS_IRDA_DEVICE_INFO}
  WINDOWS_IRDA_DEVICE_INFO = _WINDOWS_IRDA_DEVICE_INFO;
  {$EXTERNALSYM WINDOWS_IRDA_DEVICE_INFO}
  PWINDOWS_IRDA_DEVICE_INFO = ^WINDOWS_IRDA_DEVICE_INFO;
  {$EXTERNALSYM PWINDOWS_IRDA_DEVICE_INFO}
  LPWINDOWS_IRDA_DEVICE_INFO = ^WINDOWS_IRDA_DEVICE_INFO;
  {$EXTERNALSYM LPWINDOWS_IRDA_DEVICE_INFO}
  TWindowsIrdaDeviceInfo = WINDOWS_IRDA_DEVICE_INFO;
  PWindowsIrdaDeviceInfo = LPWINDOWS_IRDA_DEVICE_INFO;  

  _WCE_IRDA_DEVICE_INFO = record
    irdaDeviceID: array [0..3] of u_char;
    irdaDeviceName: array [0..21] of Char;
    Reserved: array [0..1] of u_char;
  end;
  {$EXTERNALSYM _WCE_IRDA_DEVICE_INFO}
  WCE_IRDA_DEVICE_INFO = _WCE_IRDA_DEVICE_INFO;
  {$EXTERNALSYM WCE_IRDA_DEVICE_INFO}
  PWCE_IRDA_DEVICE_INFO = ^WCE_IRDA_DEVICE_INFO;
  {$EXTERNALSYM PWCE_IRDA_DEVICE_INFO}
  TWceIrdaDeviceInfo = WCE_IRDA_DEVICE_INFO;
  PWceIrdaDeviceInfo = PWCE_IRDA_DEVICE_INFO;

  IRDA_DEVICE_INFO = WINDOWS_IRDA_DEVICE_INFO;
  {$EXTERNALSYM IRDA_DEVICE_INFO}
  PIRDA_DEVICE_INFO = ^WINDOWS_IRDA_DEVICE_INFO;
  {$EXTERNALSYM PIRDA_DEVICE_INFO}
  LPIRDA_DEVICE_INFO = ^WINDOWS_IRDA_DEVICE_INFO;
  {$EXTERNALSYM LPIRDA_DEVICE_INFO}
  TIrdaDeviceInfo = IRDA_DEVICE_INFO;
  PIrdaDeviceInfo = LPIRDA_DEVICE_INFO;

  _WINDOWS_DEVICELIST = record
    numDevice: ULONG;
    Device: array [0..0] of WINDOWS_IRDA_DEVICE_INFO;
  end;
  {$EXTERNALSYM _WINDOWS_DEVICELIST}
  WINDOWS_DEVICELIST = _WINDOWS_DEVICELIST;
  {$EXTERNALSYM WINDOWS_DEVICELIST}
  PWINDOWS_DEVICELIST = ^WINDOWS_DEVICELIST;
  {$EXTERNALSYM PWINDOWS_DEVICELIST}
  LPWINDOWS_DEVICELIST = ^WINDOWS_DEVICELIST;
  {$EXTERNALSYM LPWINDOWS_DEVICELIST}
  TWindowsDeviceList = WINDOWS_DEVICELIST;
  PWindowsDeviceList = LPWINDOWS_DEVICELIST;

  _WCE_DEVICELIST = record
    numDevice: ULONG;
    Device: array [0..0] of WCE_IRDA_DEVICE_INFO;
  end;
  {$EXTERNALSYM _WCE_DEVICELIST}
  WCE_DEVICELIST = _WCE_DEVICELIST;
  {$EXTERNALSYM WCE_DEVICELIST}
  PWCE_DEVICELIST = ^WCE_DEVICELIST;
  {$EXTERNALSYM PWCE_DEVICELIST}
  TWceDeviceList = WCE_DEVICELIST;
  PWceDeviceList = PWCE_DEVICELIST;

  DEVICELIST = WINDOWS_DEVICELIST;
  {$EXTERNALSYM DEVICELIST}
  PDEVICELIST = ^WINDOWS_DEVICELIST;
  {$EXTERNALSYM PDEVICELIST}
  LPDEVICELIST = ^WINDOWS_DEVICELIST;
  {$EXTERNALSYM LPDEVICELIST}
  TDeviceList = DEVICELIST;

  _WINDOWS_IAS_SET = record
    irdaClassName: array [0..IAS_MAX_CLASSNAME - 1] of Char;
    irdaAttribName: array [0..IAS_MAX_ATTRIBNAME - 1] of Char;
    irdaAttribType: u_long;
    case Integer of
      0: (
        irdaAttribInt: Longint);
      1: (
        Len: u_short;
        OctetSeq: array [0..IAS_MAX_OCTET_STRING - 1] of u_char);
      2: (
        Len_: u_char;
        CharSet: u_char;
        UsrStr: array [0..IAS_MAX_USER_STRING - 1] of u_char);
  end;
  {$EXTERNALSYM _WINDOWS_IAS_SET}
  WINDOWS_IAS_SET = _WINDOWS_IAS_SET;
  {$EXTERNALSYM WINDOWS_IAS_SET}
  PWINDOWS_IAS_SET = ^WINDOWS_IAS_SET;
  {$EXTERNALSYM PWINDOWS_IAS_SET}
  LPWINDOWS_IAS_SET = ^WINDOWS_IAS_SET;
  {$EXTERNALSYM LPWINDOWS_IAS_SET}
  TWindowsIasSet = WINDOWS_IAS_SET;
  PWindowsIasSet = LPWINDOWS_IAS_SET;

  _WINDOWS_IAS_QUERY = record
    irdaDeviceID: array [0..3] of u_char;
    irdaClassName: array [0..IAS_MAX_CLASSNAME - 1] of Char;
    irdaAttribName: array [0..IAS_MAX_ATTRIBNAME - 1] of Char;
    irdaAttribType: u_long;
    case Integer of
      0: (
        irdaAttribInt: Longint);
      1: (
        Len: u_long;
        OctetSeq: array [0..IAS_MAX_OCTET_STRING - 1] of u_char);
      2: (
        Len_: u_long;
        CharSet: u_long;
        UsrStr: array [0..IAS_MAX_USER_STRING - 1] of u_char);
  end;
  {$EXTERNALSYM _WINDOWS_IAS_QUERY}
  WINDOWS_IAS_QUERY = _WINDOWS_IAS_QUERY;
  {$EXTERNALSYM WINDOWS_IAS_QUERY}
  PWINDOWS_IAS_QUERY = ^WINDOWS_IAS_QUERY;
  {$EXTERNALSYM PWINDOWS_IAS_QUERY}
  LPWINDOWS_IAS_QUERY = ^WINDOWS_IAS_QUERY;
  {$EXTERNALSYM LPWINDOWS_IAS_QUERY}
  TWindowsIasQuery = WINDOWS_IAS_QUERY;
  PWindowsIasQuery = LPWINDOWS_IAS_QUERY;

  _WCE_IAS_SET = record
    irdaClassName: array [0..60] of Char;
    irdaAttribName: array [0..60] of Char;
    irdaAttribType: u_short;
    case Integer of
      0: (
        irdaAttribInt: Integer);
      1: (
        Len: Integer;
        OctetSeq: array [0..0] of u_char;
        Reserved: array [0..2] of u_char);
      2: (
        Len_: Integer;
        CharSet: u_char;
        UsrStr: array [0..0] of u_char;
        Reserved_: array [0..1] of u_char);
  end;
  {$EXTERNALSYM _WCE_IAS_SET}
  WCE_IAS_SET = _WCE_IAS_SET;
  {$EXTERNALSYM WCE_IAS_SET}
  PWCE_IAS_SET = ^WCE_IAS_SET;
  {$EXTERNALSYM PWCE_IAS_SET}
  TWceIasSet = WCE_IAS_SET;
  PWceIasSet = PWCE_IAS_SET;

  _WCE_IAS_QUERY = record
    irdaDeviceID: array [0..3] of u_char;
    irdaClassName: array [0..60] of Char;
    irdaAttribName: array [0..60] of Char;
    irdaAttribType: u_short;
    case Integer of
      0: (irdaAttribInt: Integer);
      1: (
        Len: Integer;
        OctetSeq: array [0..0] of u_char;
        Reserved: array [0..2] of u_char);
      2: (
        Len_: Integer;
        CharSet: u_char;
        UsrStr: array [0..0] of u_char;
        Reserved_
        : array [0..1] of u_char);
  end;
  {$EXTERNALSYM _WCE_IAS_QUERY}
  WCE_IAS_QUERY = _WCE_IAS_QUERY;
  {$EXTERNALSYM WCE_IAS_QUERY}
  PWCE_IAS_QUERY = ^WCE_IAS_QUERY;
  {$EXTERNALSYM PWCE_IAS_QUERY}
  TWceIasQuery = WCE_IAS_QUERY;
  PWceIasQuery = PWCE_IAS_QUERY;

  IAS_SET = WINDOWS_IAS_SET;
  {$EXTERNALSYM IAS_SET}
  PIAS_SET = ^WINDOWS_IAS_SET;
  {$EXTERNALSYM PIAS_SET}
  LPIASSET = ^WINDOWS_IAS_SET;
  TIasSet = IAS_SET;
  PIasSet = PIAS_SET;
  {$EXTERNALSYM LPIASSET}
  IAS_QUERY = WINDOWS_IAS_QUERY;
  {$EXTERNALSYM IAS_QUERY}
  PIAS_QUERY = ^WINDOWS_IAS_QUERY;
  {$EXTERNALSYM PIAS_QUERY}
  LPIASQUERY = ^WINDOWS_IAS_QUERY;
  {$EXTERNALSYM LPIASQUERY}
  TIasQuery = IAS_QUERY;
  PIasQuery = PIAS_QUERY;  

implementation

end.
