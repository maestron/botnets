{******************************************************************************}
{                                                       	               }
{ BlueTooth API interface Unit for Object Pascal                               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Contributors: John Penman       			                       }
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

// todo externalsym

unit JwaBtHDef;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "bthdef.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaBthSdpDef;

const
  GUID_BTHPORT_DEVICE_INTERFACE: TGUID =     '{0850302A-B344-4FDA-9BE9-90576B8D46F0}';
  GUID_BLUETOOTH_RADIO_IN_RANGE: TGUID =     '{EA3B5B82-26EE-450E-B0D8-D26FE30A3869}';
  GUID_BLUETOOTH_RADIO_OUT_OF_RANGE: TGUID = '{E28867C9-C2AA-4CED-B969-4570866037C4}';
  GUID_BLUETOOTH_PIN_REQUEST: TGUID =        '{BD198B7C-24AB-4B9A-8C0D-A8EA8349AA16}';
  GUID_BLUETOOTH_L2CAP_EVENT: TGUID =        '{7EAE4030-B709-4AA8-AC55-E953829C9DAA}';
  GUID_BLUETOOTH_HCI_EVENT: TGUID =          '{FC240062-1541-49BE-B463-84C4DCD7BF7F}';

//
// Bluetooth base UUID for service discovery
//

 BLUETOOTH_BASE_UUID = '{00000000-0000-1000-8000-00805F9B34FB}';

//
// UUID for the root of the browse group list
//

  SDP_PROTOCOL_UUID: TGUID        = '{00000001-0000-1000-8000-00805F9B34FB}';
  UDP_PROTOCOL_UUID: TGUID        = '{00000002-0000-1000-8000-00805F9B34FB}';
  RFCOMM_PROTOCOL_UUID: TGUID     = '{00000003-0000-1000-8000-00805F9B34FB}';
  TCP_PROTOCOL_UUID: TGUID        = '{00000004-0000-1000-8000-00805F9B34FB}';
  TCSBIN_PROTOCOL_UUID: TGUID     = '{00000005-0000-1000-8000-00805F9B34FB}';
  TCSAT_PROTOCOL_UUID: TGUID      = '{00000006-0000-1000-8000-00805F9B34FB}';
  OBEX_PROTOCOL_UUID: TGUID       = '{00000008-0000-1000-8000-00805F9B34FB}';
  IP_PROTOCOL_UUID: TGUID         = '{00000009-0000-1000-8000-00805F9B34FB}';
  FTP_PROTOCOL_UUID: TGUID        = '{0000000A-0000-1000-8000-00805F9B34FB}';
  HTTP_PROTOCOL_UUID: TGUID       = '{0000000C-0000-1000-8000-00805F9B34FB}';
  WSP_PROTOCOL_UUID: TGUID        = '{0000000E-0000-1000-8000-00805F9B34FB}';
  BNEP_PROTOCOL_UUID: TGUID       = '{0000000F-0000-1000-8000-00805F9B34FB}';
  UPNP_PROTOCOL_UUID: TGUID       = '{00000010-0000-1000-8000-00805F9B34FB}';
  HID_PROTOCOL_UUID: TGUID        = '{00000011-0000-1000-8000-00805F9B34FB}';
  HCCC_PROTOCOL_UUID: TGUID       = '{00000012-0000-1000-8000-00805F9B34FB}';
  HCDC_PROTOCOL_UUID: TGUID       = '{00000014-0000-1000-8000-00805F9B34FB}';
  HN_PROTOCOL_UUID: TGUID         = '{00000016-0000-1000-8000-00805F9B34FB}';
  AVCTP_PROTOCOL_UUID: TGUID      = '{00000017-0000-1000-8000-00805F9B34FB}';
  AVDTP_PROTOCOL_UUID: TGUID      = '{00000019-0000-1000-8000-00805F9B34FB}';
  CMPT_PROTOCOL_UUID: TGUID       = '{0000001B-0000-1000-8000-00805F9B34FB}';
  UDI_C_PLANE_PROTOCOL_UUID: TGUID= '{0000001D-0000-1000-8000-00805F9B34FB}';
  L2CAP_PROTOCOL_UUID: TGUID      = '{00000100-0000-1000-8000-00805F9B34FB}';

  SDP_PROTOCOL_UUID16 = $0001;
  UDP_PROTOCOL_UUID16 = $0002;
  RFCOMM_PROTOCOL_UUID16 = $0003;
  TCP_PROTOCOL_UUID16 = $0004;
  TCSBIN_PROTOCOL_UUID16 = $0005;
  TCSAT_PROTOCOL_UUID16 = $0006;
  OBEX_PROTOCOL_UUID16 = $0008;
  IP_PROTOCOL_UUID16 = $0009;
  FTP_PROTOCOL_UUID16 = $000A;
  HTTP_PROTOCOL_UUID16 = $000C;
  WSP_PROTOCOL_UUID16 = $000E;
  BNEP_PROTOCOL_UUID16 = $000;
  UPNP_PROTOCOL_UUID16 = $0010;
  HID_PROTOCOL_UUID16 = $0011;
  HCCC_PROTOCOL_UUID16 = $0012;
  HCDC_PROTOCOL_UUID16 = $0014;
  HCN_PROTOCOL_UUID16 = $0016;
  AVCTP_PROTOCOL_UUID16 = $0017;
  AVDTP_PROTOCOL_UUID16 = $0019;
  CMPT_PROTOCOL_UUID16 = $001B;
  UDI_C_PLANE_PROTOCOL_UUID16 = $001D;
  L2CAP_PROTOCOL_UUID16 = $0100;

  ServiceDiscoveryServerServiceClassID_UUID: TGUID = '{00001000-0000-1000-8000-00805F9B34FB}';
  BrowseGroupDescriptorServiceClassID_UUID: TGUID = '{00001001-0000-1000-8000-00805F9B34FB}';
  PublicBrowseGroupServiceClass_UUID: TGUID = '{00001002-0000-1000-8000-00805F9B34FB}';
  SerialPortServiceClass_UUID: TGUID = '{00001101-0000-1000-8000-00805F9B34FB}';
  LANAccessUsingPPPServiceClass_UUID: TGUID = '{00001102-0000-1000-8000-00805F9B34FB}';
  DialupNetworkingServiceClass_UUID: TGUID = '{00001103-0000-1000-8000-00805F9B34FB}';
  IrMCSyncServiceClass_UUID: TGUID = '{00001104-0000-1000-8000-00805F9B34FB}';
  OBEXObjectPushServiceClass_UUID: TGUID = '{00001105-0000-1000-8000-00805F9B34FB}';
  OBEXFileTransferServiceClass_UUID: TGUID = '{00001106-0000-1000-8000-00805F9B34FB}';
  IrMCSyncCommandServiceClass_UUID: TGUID = '{00001107-0000-1000-8000-00805F9B34FB}';
  HeadsetServiceClass_UUID: TGUID = '{00001108-0000-1000-8000-00805F9B34FB}';
  CordlessTelephonyServiceClass_UUID: TGUID = '{00001109-0000-1000-8000-00805F9B34FB}';
  AudioSourceServiceClass_UUID: TGUID = '{0000110A-0000-1000-8000-00805F9B34FB}';
  AudioSinkServiceClass_UUID: TGUID = '{0000110B-0000-1000-8000-00805F9B34FB}';
  AVRemoteControlTargetServiceClass_UUID: TGUID = '{0000110C-0000-1000-8000-00805F9B34FB}';
  AdvancedAudioDistributionServiceClass_UUID: TGUID = '{0000110D-0000-1000-8000-00805F9B34FB}';
  AVRemoteControlServiceClass_UUID: TGUID = '{0000110E-0000-1000-8000-00805F9B34FB}';
  VideoConferencingServiceClass_UUID: TGUID = '{0000110F-0000-1000-8000-00805F9B34FB}';
  IntercomServiceClass_UUID: TGUID = '{00001110-0000-1000-8000-00805F9B34FB}';
  FaxServiceClass_UUID: TGUID = '{00001111-0000-1000-8000-00805F9B34FB}';
  HeadsetAudioGatewayServiceClass_UUID: TGUID = '{00001112-0000-1000-8000-00805F9B34FB}';
  WAPServiceClass_UUID: TGUID = '{00001113-0000-1000-8000-00805F9B34FB}';
  WAPClientServiceClass_UUID: TGUID = '{00001114-0000-1000-8000-00805F9B34FB}';
  PANUServiceClass_UUID: TGUID = '{00001115-0000-1000-8000-00805F9B34FB}';
  NAPServiceClass_UUID: TGUID = '{00001116-0000-1000-8000-00805F9B34FB}';
  GNServiceClass_UUID: TGUID = '{00001117-0000-1000-8000-00805F9B34FB}';
  DirectPrintingServiceClass_UUID: TGUID = '{00001118-0000-1000-8000-00805F9B34FB}';
  ReferencePrintingServiceClass_UUID: TGUID = '{00001119-0000-1000-8000-00805F9B34FB}';
  ImagingServiceClass_UUID: TGUID = '{0000111A-0000-1000-8000-00805F9B34FB}';
  ImagingResponderServiceClass_UUID: TGUID = '{0000111B-0000-1000-8000-00805F9B34FB}';
  ImagingAutomaticArchiveServiceClass_UUID: TGUID = '{0000111C-0000-1000-8000-00805F9B34FB}';
  ImagingReferenceObjectsServiceClass_UUID: TGUID = '{0000111D-0000-1000-8000-00805F9B34FB}';
  HandsfreeServiceClass_UUID: TGUID = '{0000111E-0000-1000-8000-00805F9B34FB}';
  HandsfreeAudioGatewayServiceClass_UUID: TGUID = '{0000111F-0000-1000-8000-00805F9B34FB}';
  DirectPrintingReferenceObjectsServiceClass_UUID: TGUID = '{00001120-0000-1000-8000-00805F9B34FB}';
  ReflectedUIServiceClass_UUID: TGUID = '{00001121-0000-1000-8000-00805F9B34FB}';
  BasicPringingServiceClass_UUID: TGUID = '{00001122-0000-1000-8000-00805F9B34FB}';
  PrintingStatusServiceClass_UUID: TGUID = '{00001123-0000-1000-8000-00805F9B34FB}';
  HumanInterfaceDeviceServiceClass_UUID: TGUID = '{00001124-0000-1000-8000-00805F9B34FB}';
  HardcopyCableReplacementServiceClass_UUID: TGUID = '{00001125-0000-1000-8000-00805F9B34FB}';
  HCRPrintServiceClass_UUID: TGUID = '{00001126-0000-1000-8000-00805F9B34FB}';
  HCRScanServiceClass_UUID: TGUID = '{00001127-0000-1000-8000-00805F9B34FB}';
  CommonISDNAccessServiceClass_UUID: TGUID = '{00001128-0000-1000-8000-00805F9B34FB}';
  VideoConferencingGWServiceClass_UUID: TGUID = '{00001129-0000-1000-8000-00805F9B34FB}';
  UDIMTServiceClass_UUID: TGUID = '{0000112A-0000-1000-8000-00805F9B34FB}';
  UDITAServiceClass_UUID: TGUID = '{0000112B-0000-1000-8000-00805F9B34FB}';
  AudioVideoServiceClass_UUID: TGUID = '{0000112C-0000-1000-8000-00805F9B34FB}';
  PnPInformationServiceClass_UUID: TGUID = '{00001200-0000-1000-8000-00805F9B34FB}';
  GenericNetworkingServiceClass_UUID: TGUID = '{00001201-0000-1000-8000-00805F9B34FB}';
  GenericFileTransferServiceClass_UUID: TGUID = '{00001202-0000-1000-8000-00805F9B34FB}';
  GenericAudioServiceClass_UUID: TGUID = '{00001203-0000-1000-8000-00805F9B34FB}';
  GenericTelephonyServiceClass_UUID: TGUID = '{00001204-0000-1000-8000-00805F9B34FB}';

  ServiceDiscoveryServerServiceClassID_UUID16 = $1000;
  BrowseGroupDescriptorServiceClassID_UUID16 = $1001;
  PublicBrowseGroupServiceClassID_UUID16 = $1002;
  SerialPortServiceClassID_UUID16 = $1101;
  LANAccessUsingPPPServiceClassID_UUID16 = $1102;
  DialupNetworkingServiceClassID_UUID16 = $1103;
  IrMCSyncServiceClassID_UUID16 = $1104;
  OBEXObjectPushServiceClassID_UUID16 = $1105;
  OBEXFileTransferServiceClassID_UUID16 = $1106;
  IrMcSyncCommandServiceClassID_UUID16 = $1107;
  HeadsetServiceClassID_UUID16 = $1108;
  CordlessServiceClassID_UUID16 = $1109;
  AudioSourceServiceClassID_UUID16 = $110A;
  AudioSinkSourceServiceClassID_UUID16 = $110B;
  AVRemoteControlTargetServiceClassID_UUID16 = $110C;
  AdvancedAudioDistributionServiceClassID_UUID16 = $110D;
  AVRemoteControlServiceClassID_UUID16 = $110E;
  VideoConferencingServiceClassID_UUID16 = $110;
  IntercomServiceClassID_UUID16 = $1110;
  FaxServiceClassID_UUID16 = $1111;
  HeadsetAudioGatewayServiceClassID_UUID16 = $1112;
  WAPServiceClassID_UUID16 = $1113;
  WAPClientServiceClassID_UUID16 = $1114;
  PANUServiceClassID_UUID16 = $1115;
  NAPServiceClassID_UUID16 = $1116;
  GNServiceClassID_UUID16 = $1117;
  DirectPrintingServiceClassID_UUID16 = $1118;
  ReferencePrintingServiceClassID_UUID16 = $1119;
  ImagingServiceClassID_UUID16 = $111A;
  ImagingResponderServiceClassID_UUID16 = $111B;
  ImagingAutomaticArchiveServiceClassID_UUID16 = $111C;
  ImagingReferenceObjectsServiceClassID_UUID16 = $111D;
  HandsfreeServiceClassID_UUID16 = $111E;
  HandsfreeAudioGatewayServiceClassID_UUID16 = $111F;
  DirectPrintingReferenceObjectsServiceClassID_UUID16 = $1120;
  ReflectsUIServiceClassID_UUID16 = $1121;
  BasicPrintingServiceClassID_UUID16 = $1122;
  PrintingStatusServiceClassID_UUID16 = $1123;
  HumanInterfaceDeviceServiceClassID_UUID16 = $1124;
  HardcopyCableReplacementServiceClassID_UUID16 = $1125;
  HCRPrintServiceClassID_UUID16 = $1126;
  HCRScanServiceClassID_UUID16 = $1127;
  CommonISDNAccessServiceClass_UUID16 = $1128;
  VideoConferencingGWServiceClass_UUID16 = $1129;
  UDIMTServiceClass_UUID16 = $112A;
  UDITAServiceClass_UUID16 = $112B;
  AudioVideoServiceClass_UUID16 = $112C;

  PnPInformationServiceClassID_UUID16 = $1200;
  GenericNetworkingServiceClassID_UUID16 = $1201;
  GenericFileTransferServiceClassID_UUID16 = $1202;
  GenericAudioServiceClassID_UUID16 = $1203;
  GenericTelephonyServiceClassID_UUID16 = $1204;

//
// max length of device friendly name.
//

  BTH_MAX_NAME_SIZE = 248;

  BTH_MAX_PIN_SIZE = 16;
  BTH_LINK_KEY_LENGTH = (16);

  BTH_MFG_ERICSSON = (0);
  BTH_MFG_NOKIA = (1);
  BTH_MFG_INTEL = (2);
  BTH_MFG_IBM = (3);
  BTH_MFG_TOSHIBA = (4);
  BTH_MFG_3COM = (5);
  BTH_MFG_MICROSOFT = (6);
  BTH_MFG_LUCENT = (7);
  BTH_MFG_MOTOROLA = (8);
  BTH_MFG_INFINEON = (9);
  BTH_MFG_CSR = (10);
  BTH_MFG_SILICONWAVE = (11);
  BTH_MFG_DIGIANSWER = (12);
  BTH_MFG_TI = (13);
  BTH_MFG_PARTHUS = (14);
  BTH_MFG_BROADCOM = (15);
  BTH_MFG_MITEL = (16);
  BTH_MFG_WIDCOMM = (17);
  BTH_MFG_ZEEVO = (18);
  BTH_MFG_ATMEL = (19);
  BTH_MFG_MITSIBUSHI = (20);
  BTH_MFG_RTX_TELECOM = (21);
  BTH_MFG_KC_TECHNOLOGY = (22);
  BTH_MFG_NEWLOGIC = (23);
  BTH_MFG_TRANSILICA = (24);
  BTH_MFG_ROHDE_SCHWARZ = (25);
  BTH_MFG_TTPCOM = (26);
  BTH_MFG_SIGNIA = (27);
  BTH_MFG_CONEXANT = (28);
  BTH_MFG_QUALCOMM = (29);
  BTH_MFG_INVENTEL = (30);
  BTH_MFG_AVM_BERLIN = (31);
  BTH_MFG_BANDSPEED = (32);
  BTH_MFG_MANSELLA = (33);
  BTH_MFG_NEC = (34);
  BTH_MFG_WAVEPLUS_TECHNOLOGY_CO = (35);
  BTH_MFG_ALCATEL = (36);
  BTH_MFG_PHILIPS_SEMICONDUCTOR = (37);
  BTH_MFG_C_TECHNOLOGIES = (38);
  BTH_MFG_OPEN_INTERFACE = (39);
  BTH_MFG_RF_MICRO_DEVICES = (40);
  BTH_MFG_HITACHI = (41);
  BTH_MFG_SYMBOL_TECHNOLOGIES = (42);
  BTH_MFG_TENOVIS = (43);
  BTH_MFG_MACRONIX_INTERNATIONAL = (44);
  BTH_MFG_INTERNAL_USE = (65535);

type
  BTH_ADDR = Int64;
  PBTH_ADDR = ^BTH_ADDR;
  BTH_COD = ULONG;
  PBTH_COD = ^BTH_COD;
  BTH_LAP = ULONG;
  PBTH_LAP = ^BTH_LAP;

const
  BTH_ADDR_NULL = Int64($0000000000000000);

  NAP_MASK = Int64($FFFF00000000);
  SAP_MASK = Int64($0000FFFFFFFF);

  NAP_BIT_OFFSET = (8 * 4);
  SAP_BIT_OFFSET = (0);

function GET_NAP(_bth_addr: BTH_ADDR): Word;
function GET_SAP(_bth_addr: BTH_ADDR): ULONG;
function SET_NAP(_nap: Word): Int64; //todo impl
function SET_SAP(_sap: ULONG): Int64; // todo impl
function SET_NAP_SAP(_nap, _sap: Word): Int64; // todo impl

const
  COD_FORMAT_BIT_OFFSET = (0);
  COD_MINOR_BIT_OFFSET = (2);
  COD_MAJOR_BIT_OFFSET = (8 * 1);
  COD_SERVICE_BIT_OFFSET = (8 * 1 + 5);

  COD_FORMAT_MASK = ($000003);
  COD_MINOR_MASK = ($0000FC);
  COD_MAJOR_MASK = ($001F00);
  COD_SERVICE_MASK = ($FFE000);

{ todo
#define GET_COD_FORMAT(_cod)    ( (_cod) & COD_FORMAT_MASK   >> COD_FORMAT_BIT_OFFSET)
#define GET_COD_MINOR(_cod)     (((_cod) & COD_MINOR_MASK)   >> COD_MINOR_BIT_OFFSET)
#define GET_COD_MAJOR(_cod)     (((_cod) & COD_MAJOR_MASK)   >> COD_MAJOR_BIT_OFFSET)
#define GET_COD_SERVICE(_cod)   (((_cod) & COD_SERVICE_MASK) >> COD_SERVICE_BIT_OFFSET)

#define SET_COD_MINOR(_cod, _minor) (_cod) = ((_cod) & ~COD_MINOR_MASK) | ((_minor) << COD_MINOR_BIT_OFFSET)
#define SET_COD_MAJOR(_cod, _major) (_cod) = ((_cod) & ~COD_MAJOR_MASK) | ((_major) << COD_MAJOR_BIT_OFFSET)
#define SET_COD_SERVICE(_cod, _service) (_cod) = ((_cod) & ~COD_SERVICE_MASK) | ((_service) << COD_SERVICE_BIT_OFFSET)
}

const
  COD_VERSION = $0;

  COD_SERVICE_LIMITED = $0001;
  COD_SERVICE_POSITIONING = $0008;
  COD_SERVICE_NETWORKING = $0010;
  COD_SERVICE_RENDERING = $0020;
  COD_SERVICE_CAPTURING = $0040;
  COD_SERVICE_OBJECT_XFER = $0080;
  COD_SERVICE_AUDIO = $0100;
  COD_SERVICE_TELEPHONY = $0200;
  COD_SERVICE_INFORMATION = $0400;

  COD_SERVICE_VALID_MASK = (COD_SERVICE_LIMITED or COD_SERVICE_POSITIONING or
                            COD_SERVICE_NETWORKING or COD_SERVICE_RENDERING or
                            COD_SERVICE_CAPTURING or COD_SERVICE_OBJECT_XFER or
                            COD_SERVICE_AUDIO or COD_SERVICE_TELEPHONY or
                            COD_SERVICE_INFORMATION);


  COD_SERVICE_MAX_COUNT = (9);

//
// Major class codes
//

const
  COD_MAJOR_MISCELLANEOUS = $00;
  COD_MAJOR_COMPUTER = $01;
  COD_MAJOR_PHONE = $02;
  COD_MAJOR_LAN_ACCESS = $03;
  COD_MAJOR_AUDIO = $04;
  COD_MAJOR_PERIPHERAL = $05;
  COD_MAJOR_IMAGING = $06;
  COD_MAJOR_UNCLASSIFIED = $1;

//
// Minor class codes specific to each major class
//

const
  COD_COMPUTER_MINOR_UNCLASSIFIED = $00;
  COD_COMPUTER_MINOR_DESKTOP = $01;
  COD_COMPUTER_MINOR_SERVER = $02;
  COD_COMPUTER_MINOR_LAPTOP = $03;
  COD_COMPUTER_MINOR_HANDHELD = $04;
  COD_COMPUTER_MINOR_PALM = $05;
  COD_COMPUTER_MINOR_WEARABLE = $06;

  COD_PHONE_MINOR_UNCLASSIFIED = ($00);
  COD_PHONE_MINOR_CELLULAR = $01;
  COD_PHONE_MINOR_CORDLESS = $02;
  COD_PHONE_MINOR_SMART = $03;
  COD_PHONE_MINOR_WIRED_MODEM = $04;

  COD_AUDIO_MINOR_UNCLASSIFIED = $00;
  COD_AUDIO_MINOR_HEADSET = $01;
  COD_AUDIO_MINOR_HANDS_FREE = $02;
  COD_AUDIO_MINOR_HEADSET_HANDS_FREE = $03;
  COD_AUDIO_MINOR_MICROPHONE = $0;
  COD_AUDIO_MINOR_LOUDSPEAKER = $05;
  COD_AUDIO_MINOR_HEADPHONES = $06;
  COD_AUDIO_MINOR_PORTABLE_AUDIO = $07;
  COD_AUDIO_MINOR_CAR_AUDIO = $08;
  COD_AUDIO_MINOR_SET_TOP_BOX = $09;
  COD_AUDIO_MINOR_HIFI_AUDIO = $0A;
  COD_AUDIO_MINOR_VCR = $0B;
  COD_AUDIO_MINOR_VIDEO_CAMERA = $0C;
  COD_AUDIO_MINOR_CAMCORDER = $0D;
  COD_AUDIO_MINOR_VIDEO_MONITOR = $0E;
  COD_AUDIO_MINOR_VIDEO_DISPLAY_LOUDSPEAKER = $0F;
  COD_AUDIO_MINOR_VIDEO_DISPLAY_CONFERENCING = $10;
  //COD_AUDIO_MINOR_RESERVED = $11:
  COD_AUDIO_MINOR_GAMING_TOY = $12;

  COD_PERIPHERAL_MINOR_KEYBOARD_MASK = $10;
  COD_PERIPHERAL_MINOR_POINTER_MASK = $20;

  COD_PERIPHERAL_MINOR_NO_CATEGORY = $00;
  COD_PERIPHERAL_MINOR_JOYSTICK = $01;
  COD_PERIPHERAL_MINOR_GAMEPAD = $02;
  COD_PERIPHERAL_MINOR_REMOTE_CONTROL = $03;
  COD_PERIPHERAL_MINOR_SENSING = $04;

  COD_IMAGING_MINOR_DISPLAY_MASK = $04;
  COD_IMAGING_MINOR_CAMERA_MASK = $08;
  COD_IMAGING_MINOR_SCANNER_MASK = $10;
  COD_IMAGING_MINOR_PRINTER_MASK = $20;

//
// Cannot use GET_COD_MINOR for this b/c it is embedded in a different manner
// than the rest of the major classes
//

const
  COD_LAN_ACCESS_BIT_OFFSET = (5);

  COD_LAN_MINOR_MASK = $00001C;
  COD_LAN_ACCESS_MASK = $0000E0;

function GET_COD_LAN_MINOR(_cod: DWORD): DWORD;
function GET_COD_LAN_ACCESS(_cod: DWORD): DWORD;

//
// LAN access percent usage subcodes
//

const
  COD_LAN_MINOR_UNCLASSIFIED = $00;

  COD_LAN_ACCESS_0_USED = $00;
  COD_LAN_ACCESS_17_USED = $01;
  COD_LAN_ACCESS_33_USED = $02;
  COD_LAN_ACCESS_50_USED = $03;
  COD_LAN_ACCESS_67_USED = $04;
  COD_LAN_ACCESS_83_USED = $05;
  COD_LAN_ACCESS_99_USED = $06;
  COD_LAN_ACCESS_FULL = $07;

//
// Used as an initializer of LAP_DATA
//

(*todo
#define LAP_GIAC_INIT                   { 0x33, 0x8B, 0x9E }
#define LAP_LIAC_INIT                   { 0x00, 0x8B, 0x9E }
*)

//
// General Inquiry Access Code.
//

const
  LAP_GIAC_VALUE = $009E8B33;

//
// Limited Inquiry Access Code.
//

const
  LAP_LIAC_VALUE = $009E8B00;

  BTH_ADDR_IAC_FIRST = $9E8B00;
  BTH_ADDR_IAC_LAST = $9E8B3;
  BTH_ADDR_LIAC = $9E8B00;
  BTH_ADDR_GIAC = $9E8B33;

type
  BTHSTATUS = UCHAR;
  PBTHSTATUS = ^BTHSTATUS;

function BTH_ERROR(_btStatus: BTHSTATUS): BOOL;
function BTH_SUCCESS(_btStatus: BTHSTATUS): BOOL;

const
  BTH_ERROR_SUCCESS = $00;
  BTH_ERROR_UNKNOWN_HCI_COMMAND = $01;
  BTH_ERROR_NO_CONNECTION = $02;
  BTH_ERROR_HARDWARE_FAILURE = $03;
  BTH_ERROR_PAGE_TIMEOUT = $04;
  BTH_ERROR_AUTHENTICATION_FAILURE = $05;
  BTH_ERROR_KEY_MISSING = $06;
  BTH_ERROR_MEMORY_FULL = $07;
  BTH_ERROR_CONNECTION_TIMEOUT = $08;
  BTH_ERROR_MAX_NUMBER_OF_CONNECTIONS = $09;
  BTH_ERROR_MAX_NUMBER_OF_SCO_CONNECTIONS = $0a;
  BTH_ERROR_ACL_CONNECTION_ALREADY_EXISTS = $0b;
  BTH_ERROR_COMMAND_DISALLOWED = $0c;
  BTH_ERROR_HOST_REJECTED_LIMITED_RESOURCES = $0d;
  BTH_ERROR_HOST_REJECTED_SECURITY_REASONS = $0e;
  BTH_ERROR_HOST_REJECTED_PERSONAL_DEVICE = $0;
  BTH_ERROR_HOST_TIMEOUT = $10;
  BTH_ERROR_UNSUPPORTED_FEATURE_OR_PARAMETER = $11;
  BTH_ERROR_INVALID_HCI_PARAMETER = $12;
  BTH_ERROR_REMOTE_USER_ENDED_CONNECTION = $13;
  BTH_ERROR_REMOTE_LOW_RESOURCES = $14;
  BTH_ERROR_REMOTE_POWERING_OFF = $15;
  BTH_ERROR_LOCAL_HOST_TERMINATED_CONNECTION = $16;
  BTH_ERROR_REPEATED_ATTEMPTS = $17;
  BTH_ERROR_PAIRING_NOT_ALLOWED = $18;
  BTH_ERROR_UKNOWN_LMP_PDU = $19;
  BTH_ERROR_UNSUPPORTED_REMOTE_FEATURE = $1a;
  BTH_ERROR_SCO_OFFSET_REJECTED = $1b;
  BTH_ERROR_SCO_INTERVAL_REJECTED = $1c;
  BTH_ERROR_SCO_AIRMODE_REJECTED = $1d;
  BTH_ERROR_INVALID_LMP_PARAMETERS = $1e;
  BTH_ERROR_UNSPECIFIED_ERROR = $1;
  BTH_ERROR_UNSUPPORTED_LMP_PARM_VALUE = $20;
  BTH_ERROR_ROLE_CHANGE_NOT_ALLOWED = $21;
  BTH_ERROR_LMP_RESPONSE_TIMEOUT = $22;
  BTH_ERROR_LMP_TRANSACTION_COLLISION = $23;
  BTH_ERROR_LMP_PDU_NOT_ALLOWED = $24;
  BTH_ERROR_ENCRYPTION_MODE_NOT_ACCEPTABLE = $25;
  BTH_ERROR_UNIT_KEY_NOT_USED = $26;
  BTH_ERROR_QOS_IS_NOT_SUPPORTED = $27;
  BTH_ERROR_INSTANT_PASSED = $28;
  BTH_ERROR_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED = $29;

  BTH_ERROR_UNSPECIFIED = $FF;

//
// Min, max, and default L2cap MTU.
//

const
  L2CAP_MIN_MTU = (48);
  L2CAP_MAX_MTU = ($FFFF);
  L2CAP_DEFAULT_MTU = (672);

//
// Max l2cap signal size (48) - size of signal header (4)
//

const
  MAX_L2CAP_PING_DATA_LENGTH = (44);
  MAX_L2CAP_INFO_DATA_LENGTH = (44);

//
// the following two structures provides information about
// disocvered remote radios.
//

const
  BDIF_ADDRESS = ($00000001);
  BDIF_COD = ($00000002);
  BDIF_NAME = ($00000004);
  BDIF_PAIRED = ($00000008);
  BDIF_PERSONAL = ($00000010);
  BDIF_CONNECTED = ($00000020);

const
  BDIF_VALID_FLAGS = (BDIF_CONNECTED or BDIF_ADDRESS or BDIF_COD or BDIF_NAME or BDIF_PAIRED or BDIF_PERSONAL);

type
  _BTH_DEVICE_INFO = record

    //
    // Combination BDIF_Xxx flags
    //
    flags: ULONG;

    //
    // Address of remote device.
    //
    address: BTH_ADDR;

    //
    // Class Of Device.
    //
    classOfDevice: BTH_COD;

    //
    // name of the device
    //
    name: array [0..BTH_MAX_NAME_SIZE - 1] of CHAR;
  end;
  BTH_DEVICE_INFO = _BTH_DEVICE_INFO;
  PBTH_DEVICE_INFO = ^BTH_DEVICE_INFO;
  TBthDeviceInfo = BTH_DEVICE_INFO;
  PBthDeviceInfo = PBTH_DEVICE_INFO;

//
// Buffer associated with GUID_BLUETOOTH_RADIO_IN_RANGE
//

type
  _BTH_RADIO_IN_RANGE = record
    //
    // Information about the remote radio
    //
    deviceInfo: BTH_DEVICE_INFO;
    //
    // The previous flags value for the BTH_DEVICE_INFO.  The receiver of this
    // notification can compare the deviceInfo.flags and previousDeviceFlags
    // to determine what has changed about this remote radio.
    //
    // For instance, if BDIF_NAME is set in deviceInfo.flags and not in
    // previousDeviceFlags, the remote radio's has just been retrieved.
    //
    previousDeviceFlags: ULONG;
  end;
  BTH_RADIO_IN_RANGE = _BTH_RADIO_IN_RANGE;
  PBTH_RADIO_IN_RANGE = ^BTH_RADIO_IN_RANGE;
  TBthRadioInRange = BTH_RADIO_IN_RANGE;
  PBthRadioInRange = PBTH_RADIO_IN_RANGE;

//
// Buffer associated with GUID_BLUETOOTH_L2CAP_EVENT
//

  _BTH_L2CAP_EVENT_INFO = record
    //
    // Remote radio address which the L2CAP event is associated with
    //
    bthAddress: BTH_ADDR;

    //
    // The PSM that is either being connected to or disconnected from
    //
    psm: Word;

    //
    // If != 0, then the channel has just been established.  If == 0, then the
    // channel has been destroyed.  Notifications for a destroyed channel will
    // only be sent for channels successfully established.
    //
    connected: UCHAR;

    //
    // If != 0, then the local host iniated the l2cap connection.  If == 0, then
    // the remote host initated the connection.  This field is only valid if
    // connect is != 0.
    //
    initiated: UCHAR;
  end;
  BTH_L2CAP_EVENT_INFO = _BTH_L2CAP_EVENT_INFO;
  PBTH_L2CAP_EVENT_INFO = ^BTH_L2CAP_EVENT_INFO;
  TBthL2CapEventInfo = BTH_L2CAP_EVENT_INFO;
  PBthL2CapEventInfo = PBTH_L2CAP_EVENT_INFO;

const
  HCI_CONNNECTION_TYPE_ACL = (1);
  HCI_CONNNECTION_TYPE_SCO = (2);

//
// Buffer associated with GUID_BLUETOOTH_HCI_EVENT
//

type
  _BTH_HCI_EVENT_INFO = record
    //
    // Remote radio address which the HCI event is associated with
    //
    bthAddress: BTH_ADDR;

    //
    // HCI_CONNNECTION_TYPE_XXX value
    //
    connectionType: UCHAR;

    //
    // If != 0, then the underlying connection to the remote radio has just
    // been estrablished.  If == 0, then the underlying conneciton has just been
    // destroyed.
    //
    connected: UCHAR;
  end;
  BTH_HCI_EVENT_INFO = _BTH_HCI_EVENT_INFO;
  PBTH_HCI_EVENT_INFO = ^BTH_HCI_EVENT_INFO;
  TBthHciEventInfo = BTH_HCI_EVENT_INFO;
  PBthHciEventInfo = PBTH_HCI_EVENT_INFO;

const
  MAX_UUIDS_IN_QUERY = (12);

  BTH_VID_DEFAULT_VALUE = ($FFFF);

  SDP_ERROR_INVALID_SDP_VERSION = ($0001);
  SDP_ERROR_INVALID_RECORD_HANDLE = ($0002);
  SDP_ERROR_INVALID_REQUEST_SYNTAX = ($0003);
  SDP_ERROR_INVALID_PDU_SIZE = ($0004);
  SDP_ERROR_INVALID_CONTINUATION_STATE = ($0005);
  SDP_ERROR_INSUFFICIENT_RESOURCES = ($0006);

//
// Defined by windows to handle server errors that are not described by the
// above errors.  Start at 0x0100 so we don't go anywhere near the spec
// defined values.
//

//
// Success, nothing went wrong
//

const
  SDP_ERROR_SUCCESS = SDP_ERROR($0000);

//
// The SDP PDU or parameters other than the SDP stream response was not correct
//

  SDP_ERROR_SERVER_INVALID_RESPONSE = SDP_ERROR ($0100);

///
/// The SDP response stream did not parse correctly.
///

  SDP_ERROR_SERVER_RESPONSE_DID_NOT_PARSE = SDP_ERROR ($0200);

///
/// The SDP response stream was successfully parsed, but did not match the
/// required format for the query.
///

  SDP_ERROR_SERVER_BAD_FORMAT = SDP_ERROR ($0300);

///
/// SDP was unable to send a continued query back to the server
///

  SDP_ERROR_COULD_NOT_SEND_CONTINUE = SDP_ERROR ($0400);

///
/// Server sent a response that was too large to fit in the caller's buffer.
///

  SDP_ERROR_RESPONSE_TOO_LARGE = SDP_ERROR ($0500);

  SDP_ATTRIB_RECORD_HANDLE = ($0000);
  SDP_ATTRIB_CLASS_ID_LIST = ($0001);
  SDP_ATTRIB_RECORD_STATE = ($0002);
  SDP_ATTRIB_SERVICE_ID = ($0003);
  SDP_ATTRIB_PROTOCOL_DESCRIPTOR_LIST = ($0004);
  SDP_ATTRIB_BROWSE_GROUP_LIST = ($0005);
  SDP_ATTRIB_LANG_BASE_ATTRIB_ID_LIST = ($0006);
  SDP_ATTRIB_INFO_TIME_TO_LIVE = ($0007);
  SDP_ATTRIB_AVAILABILITY = ($0008);
  SDP_ATTRIB_PROFILE_DESCRIPTOR_LIST = ($0009);
  SDP_ATTRIB_DOCUMENTATION_URL = ($000A);
  SDP_ATTRIB_CLIENT_EXECUTABLE_URL = ($000B);
  SDP_ATTRIB_ICON_URL = ($000C);
  SDP_ATTRIB_ADDITIONAL_PROTOCOL_DESCRIPTOR_LIST = ($000D);

//
// Attribute IDs in the range of 0x000D - 0x01FF are reserved for future use
//

const
  SDP_ATTRIB_PROFILE_SPECIFIC = ($0200);

  LANG_BASE_LANGUAGE_INDEX = ($0000);
  LANG_BASE_ENCODING_INDEX = ($0001);
  LANG_BASE_OFFSET_INDEX = ($0002);
  LANG_DEFAULT_ID = ($0100);

  STRING_NAME_OFFSET = ($0000);
  STRING_DESCRIPTION_OFFSET = ($0001);
  STRING_PROVIDER_NAME_OFFSET = ($0002);

  SDP_ATTRIB_SDP_VERSION_NUMBER_LIST = ($0200);
  SDP_ATTRIB_SDP_DATABASE_STATE = ($0201);

  SDP_ATTRIB_BROWSE_GROUP_ID = ($0200);

  SDP_ATTRIB_CORDLESS_EXTERNAL_NETWORK = ($0301);

  SDP_ATTRIB_FAX_CLASS_1_SUPPORT = ($0302);
  SDP_ATTRIB_FAX_CLASS_2_0_SUPPORT = ($0303);
  SDP_ATTRIB_FAX_CLASS_2_SUPPORT = ($0304);
  SDP_ATTRIB_FAX_AUDIO_FEEDBACK_SUPPORT = ($0305);

  SDP_ATTRIB_HEADSET_REMOTE_AUDIO_VOLUME_CONTROL = ($0302);

  SDP_ATTRIB_LAN_LPSUBNET = ($0200);

  SDP_ATTRIB_OBJECT_PUSH_SUPPORTED_FORMATS_LIST = ($0303);

  SDP_ATTRIB_SYNCH_SUPPORTED_DATA_STORES_LIST = ($0301);

//  this is in the assigned numbers doc, but it does not show up in any profile

const
  SDP_ATTRIB_SERVICE_VERSION = ($0300);

  SDP_ATTRIB_PAN_NETWORK_ADDRESS = ($0306);
  SDP_ATTRIB_PAN_WAP_GATEWAY = ($0307);
  SDP_ATTRIB_PAN_HOME_PAGE_URL = ($0308);
  SDP_ATTRIB_PAN_WAP_STACK_TYPE = ($0309);
  SDP_ATTRIB_PAN_SECURITY_DESCRIPTION = ($030A);
  SDP_ATTRIB_PAN_NET_ACCESS_TYPE = ($030B);
  SDP_ATTRIB_PAN_MAX_NET_ACCESS_RATE = ($030C);

  SDP_ATTRIB_IMAGING_SUPPORTED_CAPABILITIES = ($0310);
  SDP_ATTRIB_IMAGING_SUPPORTED_FEATURES = ($0311);
  SDP_ATTRIB_IMAGING_SUPPORTED_FUNCTIONS = ($0312);
  SDP_ATTRIB_IMAGING_TOTAL_DATA_CAPACITY = ($0313);

  SDP_ATTRIB_DI_SPECIFICATION_ID = ($0200);
  SDP_ATTRIB_DI_VENDOR_ID = ($0201);
  SDP_ATTRIB_DI_PRODUCT_ID = ($0202);
  SDP_ATTRIB_DI_VERSION = ($0203);
  SDP_ATTRIB_DI_PRIMARY_RECORD = ($0204);
  SDP_ATTRIB_DI_VENDOR_ID_SOURCE = ($0205);

  SDP_ATTRIB_HID_DEVICE_RELEASE_NUMBER = ($0200);
  SDP_ATTRIB_HID_PARSER_VERSION = ($0201);
  SDP_ATTRIB_HID_DEVICE_SUBCLASS = ($0202);
  SDP_ATTRIB_HID_COUNTRY_CODE = ($0203);
  SDP_ATTRIB_HID_VIRTUAL_CABLE = ($0204);
  SDP_ATTRIB_HID_RECONNECT_INITIATE = ($0205);
  SDP_ATTRIB_HID_DESCRIPTOR_LIST = ($0206);
  SDP_ATTRIB_HID_LANG_ID_BASE_LIST = ($0207);
  SDP_ATTRIB_HID_SDP_DISABLE = ($0208);
  SDP_ATTRIB_HID_BATTERY_POWER = ($0209);
  SDP_ATTRIB_HID_REMOTE_WAKE = ($020A);
  SDP_ATTRIB_HID_REPORT_LIST = ($020B);
  SDP_ATTRIB_HID_SUPERVISION_TIMEOUT = ($020C);
  SDP_ATTRIB_HID_NORMALLY_CONNECTABLE = ($020D);
  SDP_ATTRIB_HID_BOOT_DEVICE = ($020E);

//
// Profile specific values
//

  CORDLESS_EXTERNAL_NETWORK_PSTN = ($01);
  CORDLESS_EXTERNAL_NETWORK_ISDN = ($02);
  CORDLESS_EXTERNAL_NETWORK_GSM = ($03);
  CORDLESS_EXTERNAL_NETWORK_CDMA = ($04);
  CORDLESS_EXTERNAL_NETWORK_ANALOG_CELLULAR = ($05);
  CORDLESS_EXTERNAL_NETWORK_PACKET_SWITCHED = ($06);
  CORDLESS_EXTERNAL_NETWORK_OTHER = ($07);

  OBJECT_PUSH_FORMAT_VCARD_2_1 = ($01);
  OBJECT_PUSH_FORMAT_VCARD_3_0 = ($02);
  OBJECT_PUSH_FORMAT_VCAL_1_0 = ($03);
  OBJECT_PUSH_FORMAT_ICAL_2_0 = ($04);
  OBJECT_PUSH_FORMAT_VNOTE = ($05);
  OBJECT_PUSH_FORMAT_VMESSAGE = ($06);
  OBJECT_PUSH_FORMAT_ANY = ($FF);

  SYNCH_DATA_STORE_PHONEBOOK = ($01);
  SYNCH_DATA_STORE_CALENDAR = ($03);
  SYNCH_DATA_STORE_NOTES = ($05);
  SYNCH_DATA_STORE_MESSAGES = ($06);

  DI_VENDOR_ID_SOURCE_BLUETOOTH_SIG = ($0001);
  DI_VENDOR_ID_SOURCE_USB_IF = ($0002);

  PSM_SDP = ($0001);
  PSM_RFCOMM = ($0003);
  PSM_TCS_BIN = ($0005);
  PSM_TCS_BIN_CORDLESS = ($0007);
  PSM_BNEP = ($000);
  PSM_HID_CONTROL = ($0011);
  PSM_HID_INTERRUPT = ($0013);
  PSM_AVCTP = ($0017);
  PSM_AVDTP = ($0019);
  PSM_UDI_C_PLANE = ($001D);

//
// Strings
//

const
  STR_ADDR_FMTA = '(%02x:%02x:%02x:%02x:%02x:%02x)';
  STR_ADDR_FMTW = '(%02x:%02x:%02x:%02x:%02x:%02x)';

  STR_ADDR_SHORT_FMTA = '%04x%08x';
  STR_ADDR_SHORT_FMTW = '%04x%08x';

{$IFDEF UNICODE}
  STR_ADDR_FMT = STR_ADDR_FMTW;
  STR_ADDR_SHORT_FMT = STR_ADDR_SHORT_FMTW;
{$ELSE}
  STR_ADDR_FMT = STR_ADDR_FMTA;
  STR_ADDR_SHORT_FMT = STR_ADDR_SHORT_FMTA;
{$ENDIF}

function GET_BITS(Field, Offset, Mask: Integer): Integer;
function GET_BIT(Field, Offset: Integer): Integer;

function LMP_3_SLOT_PACKETS(X: Integer): Integer;
function LMP_5_SLOT_PACKETS(X: Integer): Integer;
function LMP_ENCRYPTION(X: Integer): Integer;
function LMP_SLOT_OFFSET(X: Integer): Integer;
function LMP_TIMING_ACCURACY(X: Integer): Integer;
function LMP_SWITCH(X: Integer): Integer;
function LMP_HOLD_MODE(X: Integer): Integer;
function LMP_SNIFF_MODE(X: Integer): Integer;
function LMP_PARK_MODE(X: Integer): Integer;
function LMP_RSSI(X: Integer): Integer;
function LMP_CHANNEL_QUALITY_DRIVEN_MODE(X: Integer): Integer;
function LMP_SCO_LINK(X: Integer): Integer;
function LMP_HV2_PACKETS(X: Integer): Integer;
function LMP_HV3_PACKETS(X: Integer): Integer;
function LMP_MU_LAW_LOG(X: Integer): Integer;
function LMP_A_LAW_LOG(X: Integer): Integer;
function LMP_CVSD(X: Integer): Integer;
function LMP_PAGING_SCHEME(X: Integer): Integer;
function LMP_POWER_CONTROL(X: Integer): Integer;
function LMP_TRANSPARENT_SCO_DATA(X: Integer): Integer;
function LMP_FLOW_CONTROL_LAG(X: Integer): Integer;

implementation

function GET_NAP(_bth_addr: BTH_ADDR): Word;
begin
  Result := ((_bth_addr and NAP_MASK) shr NAP_BIT_OFFSET);
end;

function GET_SAP(_bth_addr: BTH_ADDR): ULONG;
begin
  Result := ((_bth_addr and SAP_MASK) shr SAP_BIT_OFFSET);
end;

function SET_NAP(_nap: Word): Int64;
begin
  Result := (_nap shl NAP_BIT_OFFSET);
end;

function SET_SAP(_sap: ULONG): Int64;
begin
  Result := (_sap shl SAP_BIT_OFFSET);
end;

function SET_NAP_SAP(_nap, _sap: Word): Int64;
begin
  Result := (SET_NAP(_nap) or SET_SAP(_sap));
end;

function GET_COD_LAN_MINOR(_cod: DWORD): DWORD;
begin
  Result := ((_cod and COD_LAN_MINOR_MASK) shr COD_MINOR_BIT_OFFSET);
end;

function GET_COD_LAN_ACCESS(_cod: DWORD): DWORD;
begin
  Result := ((_cod and COD_LAN_ACCESS_MASK) shr COD_LAN_ACCESS_BIT_OFFSET);
end;

function BTH_ERROR(_btStatus: BTHSTATUS): BOOL;
begin
  Result := _btStatus <> BTH_ERROR_SUCCESS;
end;

function BTH_SUCCESS(_btStatus: BTHSTATUS): BOOL;
begin
  Result := _btStatus = BTH_ERROR_SUCCESS;
end;

function GET_BITS(Field, Offset, Mask: Integer): Integer;
begin
  Result := (Field shr Offset) and Mask;
end;

function GET_BIT(field,offset: Integer): Integer;
begin
  Result := GET_BITS(Field, Offset, $1);
end;

function LMP_3_SLOT_PACKETS(X: Integer): Integer;               begin Result := GET_BIT(x, 0); end;
function LMP_5_SLOT_PACKETS(X: Integer): Integer;               begin Result := GET_BIT(x, 1); end;
function LMP_ENCRYPTION(X: Integer): Integer;                   begin Result := GET_BIT(x, 2); end;
function LMP_SLOT_OFFSET(X: Integer): Integer;                  begin Result := GET_BIT(x, 3); end;
function LMP_TIMING_ACCURACY(X: Integer): Integer;              begin Result := GET_BIT(x, 4); end;
function LMP_SWITCH(X: Integer): Integer;                       begin Result := GET_BIT(x, 5); end;
function LMP_HOLD_MODE(X: Integer): Integer;                    begin Result := GET_BIT(x, 6); end;
function LMP_SNIFF_MODE(X: Integer): Integer;                   begin Result := GET_BIT(x, 7); end;
function LMP_PARK_MODE(X: Integer): Integer;                    begin Result := GET_BIT(x, 8); end;
function LMP_RSSI(X: Integer): Integer;                         begin Result := GET_BIT(x, 9); end;
function LMP_CHANNEL_QUALITY_DRIVEN_MODE(X: Integer): Integer;  begin Result := GET_BIT(x,10); end;
function LMP_SCO_LINK(X: Integer): Integer;                     begin Result := GET_BIT(x,11); end;
function LMP_HV2_PACKETS(X: Integer): Integer;                  begin Result := GET_BIT(x,12); end;
function LMP_HV3_PACKETS(X: Integer): Integer;                  begin Result := GET_BIT(x,13); end;
function LMP_MU_LAW_LOG(X: Integer): Integer;                   begin Result := GET_BIT(x,14); end;
function LMP_A_LAW_LOG(X: Integer): Integer;                    begin Result := GET_BIT(x,15); end;
function LMP_CVSD(X: Integer): Integer;                         begin Result := GET_BIT(x,16); end;
function LMP_PAGING_SCHEME(X: Integer): Integer;                begin Result := GET_BIT(x,17); end;
function LMP_POWER_CONTROL(X: Integer): Integer;                begin Result := GET_BIT(x,18); end;
function LMP_TRANSPARENT_SCO_DATA(X: Integer): Integer;         begin Result := GET_BIT(x,19); end;
function LMP_FLOW_CONTROL_LAG(X: Integer): Integer;             begin Result := GET_BITS(x, 20, $3); end;

end.
