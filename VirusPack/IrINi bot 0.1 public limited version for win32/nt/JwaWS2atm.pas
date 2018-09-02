{******************************************************************************}
{                                                       	               }
{ Winsock2 ATM API interface Unit for Object Pascal                            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ws2atm.h, released June 2000. The original Pascal      }
{ code is: WS2atm.pas, released December 2000. The initial developer of the    }
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

unit JwaWS2atm;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ws2atm.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinSock2;

//#include <pshpack4.h>

{$ALIGN ON}

const
  ATMPROTO_AALUSER = $00;  (* User-defined AAL *)
  {$EXTERNALSYM ATMPROTO_AALUSER}
  ATMPROTO_AAL1    = $01;  (* AAL 1 *)
  {$EXTERNALSYM ATMPROTO_AAL1}
  ATMPROTO_AAL2    = $02;  (* AAL 2 *)
  {$EXTERNALSYM ATMPROTO_AAL2}
  ATMPROTO_AAL34   = $03;  (* AAL 3/4 *)
  {$EXTERNALSYM ATMPROTO_AAL34}
  ATMPROTO_AAL5    = $05;  (* AAL 5 *)
  {$EXTERNALSYM ATMPROTO_AAL5}

  SAP_FIELD_ABSENT        = DWORD($FFFFFFFE);
  {$EXTERNALSYM SAP_FIELD_ABSENT}
  SAP_FIELD_ANY           = DWORD($FFFFFFFF);
  {$EXTERNALSYM SAP_FIELD_ANY}
  SAP_FIELD_ANY_AESA_SEL  = DWORD($FFFFFFFA);
  {$EXTERNALSYM SAP_FIELD_ANY_AESA_SEL}
  SAP_FIELD_ANY_AESA_REST = DWORD($FFFFFFFB);
  {$EXTERNALSYM SAP_FIELD_ANY_AESA_REST}

(*
 *  values used for AddressType in struct ATM_ADDRESS
 *)

  ATM_E164 = $01   (* E.164 addressing scheme *);
  {$EXTERNALSYM ATM_E164}
  ATM_NSAP = $02   (* NSAP-style ATM Endsystem Address scheme *);
  {$EXTERNALSYM ATM_NSAP}
  ATM_AESA = $02   (* NSAP-style ATM Endsystem Address scheme *);
  {$EXTERNALSYM ATM_AESA}

  ATM_ADDR_SIZE = 20;
  {$EXTERNALSYM ATM_ADDR_SIZE}

type
  ATM_ADDRESS = record
    AddressType: DWORD;                (* E.164 or NSAP-style ATM Endsystem Address *)
    NumofDigits: DWORD;                (* number of digits; *)
    Addr: array [0..ATM_ADDR_SIZE - 1] of UCHAR; (* IA5 digits for E164, BCD encoding for NSAP *)
                                      (* format as defined in the ATM Forum UNI 3.1 *)
  end;
  {$EXTERNALSYM ATM_ADDRESS}
  TAtmAddress = ATM_ADDRESS;
  PAtmAddress = ^ATM_ADDRESS;

(*
 *  values used for Layer2Protocol in B-LLI
 *)

const
  BLLI_L2_ISO_1745       = $01;  (* Basic mode ISO 1745                      *)
  {$EXTERNALSYM BLLI_L2_ISO_1745}
  BLLI_L2_Q921           = $02;  (* CCITT Rec. Q.921                         *)
  {$EXTERNALSYM BLLI_L2_Q921}
  BLLI_L2_X25L           = $06;  (* CCITT Rec. X.25, link layer              *)
  {$EXTERNALSYM BLLI_L2_X25L}
  BLLI_L2_X25M           = $07;  (* CCITT Rec. X.25, multilink               *)
  {$EXTERNALSYM BLLI_L2_X25M}
  BLLI_L2_ELAPB          = $08;  (* Extended LAPB; for half duplex operation *)
  {$EXTERNALSYM BLLI_L2_ELAPB}
  BLLI_L2_HDLC_ARM       = $09;  (* HDLC ARM (ISO 4335)                      *)
  {$EXTERNALSYM BLLI_L2_HDLC_ARM}
  BLLI_L2_HDLC_NRM       = $0A;  (* HDLC NRM (ISO 4335)                      *)
  {$EXTERNALSYM BLLI_L2_HDLC_NRM}
  BLLI_L2_HDLC_ABM       = $0B;  (* HDLC ABM (ISO 4335)                      *)
  {$EXTERNALSYM BLLI_L2_HDLC_ABM}
  BLLI_L2_LLC            = $0C;  (* LAN logical link control (ISO 8802/2)    *)
  {$EXTERNALSYM BLLI_L2_LLC}
  BLLI_L2_X75            = $0D;  (* CCITT Rec. X.75, single link procedure   *)
  {$EXTERNALSYM BLLI_L2_X75}
  BLLI_L2_Q922           = $0E;  (* CCITT Rec. Q.922                         *)
  {$EXTERNALSYM BLLI_L2_Q922}
  BLLI_L2_USER_SPECIFIED = $10;  (* User Specified                           *)
  {$EXTERNALSYM BLLI_L2_USER_SPECIFIED}
  BLLI_L2_ISO_7776       = $11;  (* ISO 7776 DTE-DTE operation               *)
  {$EXTERNALSYM BLLI_L2_ISO_7776}

(*
 *  values used for Layer3Protocol in B-LLI
 *)

  BLLI_L3_X25            = $06;  (* CCITT Rec. X.25, packet layer            *)
  {$EXTERNALSYM BLLI_L3_X25}
  BLLI_L3_ISO_8208       = $07;  (* ISO/IEC 8208 (X.25 packet layer for DTE  *)
  {$EXTERNALSYM BLLI_L3_ISO_8208}
  BLLI_L3_X223           = $08;  (* X.223/ISO 8878                           *)
  {$EXTERNALSYM BLLI_L3_X223}
  BLLI_L3_SIO_8473       = $09;  (* ISO/IEC 8473 (OSI connectionless)        *)
  {$EXTERNALSYM BLLI_L3_SIO_8473}
  BLLI_L3_T70            = $0A;  (* CCITT Rec. T.70 min. network layer       *)
  {$EXTERNALSYM BLLI_L3_T70}
  BLLI_L3_ISO_TR9577     = $0B;  (* ISO/IEC TR 9577 Network Layer Protocol ID*)
  {$EXTERNALSYM BLLI_L3_ISO_TR9577}
  BLLI_L3_USER_SPECIFIED = $10;  (* User Specified                           *)
  {$EXTERNALSYM BLLI_L3_USER_SPECIFIED}

(*
 *  values used for Layer3IPI in B-LLI
 *)

  BLLI_L3_IPI_SNAP = $80;  (* IEEE 802.1 SNAP identifier               *)
  {$EXTERNALSYM BLLI_L3_IPI_SNAP}
  BLLI_L3_IPI_IP   = $CC;  (* Internet Protocol (IP) identifier        *)
  {$EXTERNALSYM BLLI_L3_IPI_IP}

type
  ATM_BLLI =  record
    Layer2Protocol: DWORD;                 (* User information layer 2 protocol           *)
    Layer2UserSpecifiedProtocol: DWORD;    (* User specified layer 2 protocol information *)
    Layer3Protocol: DWORD;                 (* User information layer 3 protocol           *)
    Layer3UserSpecifiedProtocol: DWORD;    (* User specified layer 3 protocol information *)
    Layer3IPI: DWORD;                      (* ISO/IEC TR 9577 Initial Protocol Identifier *)
    SnapID: array [0..4] of UCHAR;         (* SNAP ID consisting of OUI and PID           *)
  end;
  {$EXTERNALSYM ATM_BLLI}
  TAtmBLLI = ATM_BLLI;
  PAtmBLLI = ^ATM_BLLI;

(*
 *  values used for the HighLayerInfoType field in ATM_BHLI
 *)

const
  BHLI_ISO                 = $00;  (* ISO                                 *)
  {$EXTERNALSYM BHLI_ISO}
  BHLI_UserSpecific        = $01;  (* User Specific                       *)
  {$EXTERNALSYM BHLI_UserSpecific}
  BHLI_HighLayerProfile    = $02;  (* High layer profile (only in UNI3.0) *)
  {$EXTERNALSYM BHLI_HighLayerProfile}
  BHLI_VendorSpecificAppId = $03;  (* Vendor-Specific Application ID      *)
  {$EXTERNALSYM BHLI_VendorSpecificAppId}

type
  ATM_BHLI = record
    HighLayerInfoType: DWORD;             (* High Layer Information Type      *)
    HighLayerInfoLength: DWORD;           (* number of bytes in HighLayerInfo *)
    HighLayerInfo: array [0..7] of UCHAR; (* the value dependent on the       *)
                                          (*   HighLayerInfoType field        *)
  end;
  {$EXTERNALSYM ATM_BHLI}
  TAtmBHLI = ATM_BHLI;
  PAtmBHLI = ^ATM_BHLI;

  SOCKADDR_ATM = record
    satm_family: u_short;              (* address family should be AF_ATM  *)
    satm_number: ATM_ADDRESS;          (* ATM address                      *)
    satm_blli: ATM_BLLI;               (* B-LLI                            *)
    satm_bhli: ATM_BHLI;               (* B-HLI                            *)
  end;
  {$EXTERNALSYM SOCKADDR_ATM}
  PSOCKADDR_ATM = ^SOCKADDR_ATM;
  LPSOCKADDR_ATM = ^SOCKADDR_ATM;
  TSockAddrAtm = SOCKADDR_ATM;
  PSockAddrAtm = LPSOCKADDR_ATM;

  Q2931_IE_TYPE = (
    IE_AALParameters,
    IE_TrafficDescriptor,
    IE_BroadbandBearerCapability,
    IE_BHLI,
    IE_BLLI,
    IE_CalledPartyNumber,
    IE_CalledPartySubaddress,
    IE_CallingPartyNumber,
    IE_CallingPartySubaddress,
    IE_Cause,
    IE_QOSClass,
    IE_TransitNetworkSelection);
  {$EXTERNALSYM Q2931_IE_TYPE}
  TQ2931IEType = Q2931_IE_TYPE;
  PQ2931IEType = ^Q2931_IE_TYPE;  

  Q2931_IE = record
    IEType: Q2931_IE_TYPE;
    IELength: ULONG;
    IE: array [0..0] of UCHAR;
  end;
  {$EXTERNALSYM Q2931_IE}
  TQ2931IE = Q2931_IE;
  PQ2931IE = ^Q2931_IE;

(*
 *  manifest constants for the AALType field in struct AAL_PARAMETERS_IE
 *)

const
  AALTYPE_5     = 5;   (* AAL 5 *)
  {$EXTERNALSYM AALTYPE_5}
  AALTYPE_USER  = 16;  (* user-defined AAL *)
  {$EXTERNALSYM AALTYPE_USER}

type
 AAL_TYPE = DWORD;
 {$EXTERNALSYM AAL_TYPE}
 TAALType = AAL_TYPE;
 PAALType = ^AAL_TYPE;

(*
 *  values used for the Mode field in struct AAL5_PARAMETERS
 *)

const
  AAL5_MODE_MESSAGE   = $01;
  {$EXTERNALSYM AAL5_MODE_MESSAGE}
  AAL5_MODE_STREAMING = $02;
  {$EXTERNALSYM AAL5_MODE_STREAMING}

(*
 *  values used for the SSCSType field in struct AAL5_PARAMETERS
 *)

  AAL5_SSCS_NULL              = $00;
  {$EXTERNALSYM AAL5_SSCS_NULL}
  AAL5_SSCS_SSCOP_ASSURED     = $01;
  {$EXTERNALSYM AAL5_SSCS_SSCOP_ASSURED}
  AAL5_SSCS_SSCOP_NON_ASSURED = $02;
  {$EXTERNALSYM AAL5_SSCS_SSCOP_NON_ASSURED}
  AAL5_SSCS_FRAME_RELAY       = $04;
  {$EXTERNALSYM AAL5_SSCS_FRAME_RELAY}

type
  AAL5_PARAMETERS = record
    ForwardMaxCPCSSDUSize: ULONG;
    BackwardMaxCPCSSDUSize: ULONG;
    Mode: UCHAR;                        (* only available in UNI 3.0 *)
    SSCSType: UCHAR;
  end;
  {$EXTERNALSYM AAL5_PARAMETERS}
  TAAL5Parameters = AAL5_PARAMETERS;
  PAAL5Parameters = ^AAL5_PARAMETERS;

  AALUSER_PARAMETERS = record
    UserDefined: ULONG;
  end;
  {$EXTERNALSYM AALUSER_PARAMETERS}
  TAALUserParameters = AALUSER_PARAMETERS;
  PAALUserParameters = ^AALUSER_PARAMETERS;

  AAL_PARAMETERS_IE = record
    AALType: AAL_TYPE;
    case Integer of
      0: (AAL5Parameters: AAL5_PARAMETERS);
      1: (AALUserParameters: AALUSER_PARAMETERS);
  end;
  {$EXTERNALSYM AAL_PARAMETERS_IE}
  TAALParametersIE = AAL_PARAMETERS_IE;
  PAALParametersIE = ^AAL_PARAMETERS_IE;

  ATM_TD = record
    PeakCellRate_CLP0: ULONG;
    PeakCellRate_CLP01: ULONG;
    SustainableCellRate_CLP0: ULONG;
    SustainableCellRate_CLP01: ULONG;
    MaxBurstSize_CLP0: ULONG;
    MaxBurstSize_CLP01: ULONG;
    Tagging: BOOL;
  end;
  {$EXTERNALSYM ATM_TD}
  TAtmTD = ATM_TD;
  PAtmTD = ^ATM_TD;

  ATM_TRAFFIC_DESCRIPTOR_IE = record
    Forward_: ATM_TD;
    Backward: ATM_TD;
    BestEffort: BOOL;
  end;
  {$EXTERNALSYM ATM_TRAFFIC_DESCRIPTOR_IE}
  TAtmTrafficDescriptorIE = ATM_TD;
  PAtmTrafficDescriptorIE = ^ATM_TD;  

(*
 *  values used for the BearerClass field in struct ATM_BROADBAND_BEARER_CAPABILITY_IE
 *)

const
  BCOB_A = $01;   (* Bearer class A                      *)
  {$EXTERNALSYM BCOB_A}
  BCOB_C = $03;   (* Bearer class C                      *)
  {$EXTERNALSYM BCOB_C}
  BCOB_X = $10;   (* Bearer class X                      *)
  {$EXTERNALSYM BCOB_X}

(*
 *  values used for the TrafficType field in struct ATM_BROADBAND_BEARER_CAPABILITY_IE
 *)

  TT_NOIND = $00;   (* No indication of traffic type       *)
  {$EXTERNALSYM TT_NOIND}
  TT_CBR   = $04;   (* Constant bit rate                   *)
  {$EXTERNALSYM TT_CBR}
  TT_VBR   = $08;   (* Variable bit rate                   *)
  {$EXTERNALSYM TT_VBR}

(*
 *  values used for the TimingRequirements field in struct ATM_BROADBAND_BEARER_CAPABILITY_IE
 *)

  TR_NOIND         = $00;   (* No timing requirement indication    *)
  {$EXTERNALSYM TR_NOIND}
  TR_END_TO_END    = $01;   (* End-to-end timing required          *)
  {$EXTERNALSYM TR_END_TO_END}
  TR_NO_END_TO_END = $02;   (* End-to-end timing not required      *)
  {$EXTERNALSYM TR_NO_END_TO_END}

(*
 *  values used for the ClippingSusceptability field in struct ATM_BROADBAND_BEARER_CAPABILITY_IE
 *)

  CLIP_NOT = $00;   (* Not susceptible to clipping         *)
  {$EXTERNALSYM CLIP_NOT}
  CLIP_SUS = $20;   (* Susceptible to clipping             *)
  {$EXTERNALSYM CLIP_SUS}

(*
 *  values used for the UserPlaneConnectionConfig field in
 *  struct ATM_BROADBAND_BEARER_CAPABILITY_IE
 *)

  UP_P2P  = $00;   (* Point-to-point connection           *)
  {$EXTERNALSYM UP_P2P}
  UP_P2MP = $01;   (* Point-to-multipoint connection      *)
  {$EXTERNALSYM UP_P2MP}

type
  ATM_BROADBAND_BEARER_CAPABILITY_IE = record
    BearerClass: UCHAR;
    TrafficType: UCHAR;
    TimingRequirements: UCHAR;
    ClippingSusceptability: UCHAR;
    UserPlaneConnectionConfig: UCHAR;
  end;
  {$EXTERNALSYM ATM_BROADBAND_BEARER_CAPABILITY_IE}
  TAtmBroadbandBearerCapabilityIE = ATM_BROADBAND_BEARER_CAPABILITY_IE;
  PAtmBroadbandBearerCapabilityIE = ^ATM_BROADBAND_BEARER_CAPABILITY_IE;

  ATM_BHLI_IE = ATM_BHLI;
  {$EXTERNALSYM ATM_BHLI_IE}
  TAtmBHLIIE = ATM_BHLI_IE;
  PAtmBHLIIE = ^ATM_BHLI_IE;

(*
 *  values used for the Layer2Mode field in struct ATM_BLLI_IE
 *)

const
  BLLI_L2_MODE_NORMAL = $40;
  {$EXTERNALSYM BLLI_L2_MODE_NORMAL}
  BLLI_L2_MODE_EXT    = $80;
  {$EXTERNALSYM BLLI_L2_MODE_EXT}

(*
 *  values used for the Layer3Mode field in struct ATM_BLLI_IE
 *)

  BLLI_L3_MODE_NORMAL = $40;
  {$EXTERNALSYM BLLI_L3_MODE_NORMAL}
  BLLI_L3_MODE_EXT    = $80;
  {$EXTERNALSYM BLLI_L3_MODE_EXT}

(*
 *  values used for the Layer3DefaultPacketSize field in struct ATM_BLLI_IE
 *)

  BLLI_L3_PACKET_16   = $04;
  {$EXTERNALSYM BLLI_L3_PACKET_16}
  BLLI_L3_PACKET_32   = $05;
  {$EXTERNALSYM BLLI_L3_PACKET_32}
  BLLI_L3_PACKET_64   = $06;
  {$EXTERNALSYM BLLI_L3_PACKET_64}
  BLLI_L3_PACKET_128  = $07;
  {$EXTERNALSYM BLLI_L3_PACKET_128}
  BLLI_L3_PACKET_256  = $08;
  {$EXTERNALSYM BLLI_L3_PACKET_256}
  BLLI_L3_PACKET_512  = $09;
  {$EXTERNALSYM BLLI_L3_PACKET_512}
  BLLI_L3_PACKET_1024 = $0A;
  {$EXTERNALSYM BLLI_L3_PACKET_1024}
  BLLI_L3_PACKET_2048 = $0B;
  {$EXTERNALSYM BLLI_L3_PACKET_2048}
  BLLI_L3_PACKET_4096 = $0C;
  {$EXTERNALSYM BLLI_L3_PACKET_4096}

type
  ATM_BLLI_IE = record
    Layer2Protocol: DWORD;                 (* User information layer 2 protocol           *)
    Layer2Mode: UCHAR;
    Layer2WindowSize: UCHAR;
    Layer2UserSpecifiedProtocol: DWORD;    (* User specified layer 2 protocol information *)
    Layer3Protocol: DWORD;                 (* User information layer 3 protocol           *)
    Layer3Mode: UCHAR;
    Layer3DefaultPacketSize: UCHAR;
    Layer3PacketWindowSize: UCHAR;
    Layer3UserSpecifiedProtocol: DWORD;    (* User specified layer 3 protocol information *)
    Layer3IPI: DWORD;                      (* ISO/IEC TR 9577 Initial Protocol Identifier *)
    SnapID: array [0..4] of UCHAR;         (* SNAP ID consisting of OUI and PID           *)
  end;
  {$EXTERNALSYM ATM_BLLI_IE}
  TAtmBLLIIE = ATM_BLLI_IE;
  PAtmBLLIIE = ^ATM_BLLI_IE;

  ATM_CALLED_PARTY_NUMBER_IE = ATM_ADDRESS;
  {$EXTERNALSYM ATM_CALLED_PARTY_NUMBER_IE}
  TAtmCalledPartyNumberIE = ATM_CALLED_PARTY_NUMBER_IE;
  PAtmCalledPartyNumberIE = ^ATM_CALLED_PARTY_NUMBER_IE;  
  ATM_CALLED_PARTY_SUBADDRESS_IE = ATM_ADDRESS;
  {$EXTERNALSYM ATM_CALLED_PARTY_SUBADDRESS_IE}
  TAtmCalledPartySubAddressIE = ATM_CALLED_PARTY_SUBADDRESS_IE;
  PAtmCalledPartySubAddressIE = ^ATM_CALLED_PARTY_SUBADDRESS_IE;

(*
 *  values used for the Presentation_Indication field in
 *  struct ATM_CALLING_PARTY_NUMBER_IE
 *)

const
  PI_ALLOWED              = $00;
  {$EXTERNALSYM PI_ALLOWED}
  PI_RESTRICTED           = $40;
  {$EXTERNALSYM PI_RESTRICTED}
  PI_NUMBER_NOT_AVAILABLE = $80;
  {$EXTERNALSYM PI_NUMBER_NOT_AVAILABLE}

(*
 *  values used for the Screening_Indicator field in
 *  struct ATM_CALLING_PARTY_NUMBER_IE
 *)

  SI_USER_NOT_SCREENED = $00;
  {$EXTERNALSYM SI_USER_NOT_SCREENED}
  SI_USER_PASSED       = $01;
  {$EXTERNALSYM SI_USER_PASSED}
  SI_USER_FAILED       = $02;
  {$EXTERNALSYM SI_USER_FAILED}
  SI_NETWORK           = $03;
  {$EXTERNALSYM SI_NETWORK}

type
  ATM_CALLING_PARTY_NUMBER_IE = record
    ATM_Number: ATM_ADDRESS;
    Presentation_Indication: UCHAR;
    Screening_Indicator: UCHAR;
  end;
  {$EXTERNALSYM ATM_CALLING_PARTY_NUMBER_IE}
  TAtmCallingPartyNumberIE = ATM_CALLING_PARTY_NUMBER_IE;
  PAtmCallingPartyNumberIE = ^ATM_CALLING_PARTY_NUMBER_IE;

  ATM_CALLING_PARTY_SUBADDRESS_IE = ATM_ADDRESS;
  {$EXTERNALSYM ATM_CALLING_PARTY_SUBADDRESS_IE}
  TAtmCallingPartySubAddressIE = ATM_CALLING_PARTY_SUBADDRESS_IE;
  PAtmCallingPartySubAddressIE = ^ATM_CALLING_PARTY_SUBADDRESS_IE;  

(*
 *  values used for the Location field in struct ATM_CAUSE_IE
 *)

const
  CAUSE_LOC_USER                  = $00;
  {$EXTERNALSYM CAUSE_LOC_USER}
  CAUSE_LOC_PRIVATE_LOCAL         = $01;
  {$EXTERNALSYM CAUSE_LOC_PRIVATE_LOCAL}
  CAUSE_LOC_PUBLIC_LOCAL          = $02;
  {$EXTERNALSYM CAUSE_LOC_PUBLIC_LOCAL}
  CAUSE_LOC_TRANSIT_NETWORK       = $03;
  {$EXTERNALSYM CAUSE_LOC_TRANSIT_NETWORK}
  CAUSE_LOC_PUBLIC_REMOTE         = $04;
  {$EXTERNALSYM CAUSE_LOC_PUBLIC_REMOTE}
  CAUSE_LOC_PRIVATE_REMOTE        = $05;
  {$EXTERNALSYM CAUSE_LOC_PRIVATE_REMOTE}
  CAUSE_LOC_INTERNATIONAL_NETWORK = $07;
  {$EXTERNALSYM CAUSE_LOC_INTERNATIONAL_NETWORK}
  CAUSE_LOC_BEYOND_INTERWORKING   = $0A;
  {$EXTERNALSYM CAUSE_LOC_BEYOND_INTERWORKING}

(*
 *  values used for the Cause field in struct ATM_CAUSE_IE
 *)

  CAUSE_UNALLOCATED_NUMBER                = $01;
  {$EXTERNALSYM CAUSE_UNALLOCATED_NUMBER}
  CAUSE_NO_ROUTE_TO_TRANSIT_NETWORK       = $02;
  {$EXTERNALSYM CAUSE_NO_ROUTE_TO_TRANSIT_NETWORK}
  CAUSE_NO_ROUTE_TO_DESTINATION           = $03;
  {$EXTERNALSYM CAUSE_NO_ROUTE_TO_DESTINATION}
  CAUSE_VPI_VCI_UNACCEPTABLE              = $0A;
  {$EXTERNALSYM CAUSE_VPI_VCI_UNACCEPTABLE}
  CAUSE_NORMAL_CALL_CLEARING              = $10;
  {$EXTERNALSYM CAUSE_NORMAL_CALL_CLEARING}
  CAUSE_USER_BUSY                         = $11;
  {$EXTERNALSYM CAUSE_USER_BUSY}
  CAUSE_NO_USER_RESPONDING                = $12;
  {$EXTERNALSYM CAUSE_NO_USER_RESPONDING}
  CAUSE_CALL_REJECTED                     = $15;
  {$EXTERNALSYM CAUSE_CALL_REJECTED}
  CAUSE_NUMBER_CHANGED                    = $16;
  {$EXTERNALSYM CAUSE_NUMBER_CHANGED}
  CAUSE_USER_REJECTS_CLIR                 = $17;
  {$EXTERNALSYM CAUSE_USER_REJECTS_CLIR}
  CAUSE_DESTINATION_OUT_OF_ORDER          = $1B;
  {$EXTERNALSYM CAUSE_DESTINATION_OUT_OF_ORDER}
  CAUSE_INVALID_NUMBER_FORMAT             = $1C;
  {$EXTERNALSYM CAUSE_INVALID_NUMBER_FORMAT}
  CAUSE_STATUS_ENQUIRY_RESPONSE           = $1E;
  {$EXTERNALSYM CAUSE_STATUS_ENQUIRY_RESPONSE}
  CAUSE_NORMAL_UNSPECIFIED                = $1F;
  {$EXTERNALSYM CAUSE_NORMAL_UNSPECIFIED}
  CAUSE_VPI_VCI_UNAVAILABLE               = $23;
  {$EXTERNALSYM CAUSE_VPI_VCI_UNAVAILABLE}
  CAUSE_NETWORK_OUT_OF_ORDER              = $26;
  {$EXTERNALSYM CAUSE_NETWORK_OUT_OF_ORDER}
  CAUSE_TEMPORARY_FAILURE                 = $29;
  {$EXTERNALSYM CAUSE_TEMPORARY_FAILURE}
  CAUSE_ACCESS_INFORMAION_DISCARDED       = $2B;
  {$EXTERNALSYM CAUSE_ACCESS_INFORMAION_DISCARDED}
  CAUSE_NO_VPI_VCI_AVAILABLE              = $2D;
  {$EXTERNALSYM CAUSE_NO_VPI_VCI_AVAILABLE}
  CAUSE_RESOURCE_UNAVAILABLE              = $2F;
  {$EXTERNALSYM CAUSE_RESOURCE_UNAVAILABLE}
  CAUSE_QOS_UNAVAILABLE                   = $31;
  {$EXTERNALSYM CAUSE_QOS_UNAVAILABLE}
  CAUSE_USER_CELL_RATE_UNAVAILABLE        = $33;
  {$EXTERNALSYM CAUSE_USER_CELL_RATE_UNAVAILABLE}
  CAUSE_BEARER_CAPABILITY_UNAUTHORIZED    = $39;
  {$EXTERNALSYM CAUSE_BEARER_CAPABILITY_UNAUTHORIZED}
  CAUSE_BEARER_CAPABILITY_UNAVAILABLE     = $3A;
  {$EXTERNALSYM CAUSE_BEARER_CAPABILITY_UNAVAILABLE}
  CAUSE_OPTION_UNAVAILABLE                = $3F;
  {$EXTERNALSYM CAUSE_OPTION_UNAVAILABLE}
  CAUSE_BEARER_CAPABILITY_UNIMPLEMENTED   = $41;
  {$EXTERNALSYM CAUSE_BEARER_CAPABILITY_UNIMPLEMENTED}
  CAUSE_UNSUPPORTED_TRAFFIC_PARAMETERS    = $49;
  {$EXTERNALSYM CAUSE_UNSUPPORTED_TRAFFIC_PARAMETERS}
  CAUSE_INVALID_CALL_REFERENCE            = $51;
  {$EXTERNALSYM CAUSE_INVALID_CALL_REFERENCE}
  CAUSE_CHANNEL_NONEXISTENT               = $52;
  {$EXTERNALSYM CAUSE_CHANNEL_NONEXISTENT}
  CAUSE_INCOMPATIBLE_DESTINATION          = $58;
  {$EXTERNALSYM CAUSE_INCOMPATIBLE_DESTINATION}
  CAUSE_INVALID_ENDPOINT_REFERENCE        = $59;
  {$EXTERNALSYM CAUSE_INVALID_ENDPOINT_REFERENCE}
  CAUSE_INVALID_TRANSIT_NETWORK_SELECTION = $5B;
  {$EXTERNALSYM CAUSE_INVALID_TRANSIT_NETWORK_SELECTION}
  CAUSE_TOO_MANY_PENDING_ADD_PARTY        = $5C;
  {$EXTERNALSYM CAUSE_TOO_MANY_PENDING_ADD_PARTY}
  CAUSE_AAL_PARAMETERS_UNSUPPORTED        = $5D;
  {$EXTERNALSYM CAUSE_AAL_PARAMETERS_UNSUPPORTED}
  CAUSE_MANDATORY_IE_MISSING              = $60;
  {$EXTERNALSYM CAUSE_MANDATORY_IE_MISSING}
  CAUSE_UNIMPLEMENTED_MESSAGE_TYPE        = $61;
  {$EXTERNALSYM CAUSE_UNIMPLEMENTED_MESSAGE_TYPE}
  CAUSE_UNIMPLEMENTED_IE                  = $63;
  {$EXTERNALSYM CAUSE_UNIMPLEMENTED_IE}
  CAUSE_INVALID_IE_CONTENTS               = $64;
  {$EXTERNALSYM CAUSE_INVALID_IE_CONTENTS}
  CAUSE_INVALID_STATE_FOR_MESSAGE         = $65;
  {$EXTERNALSYM CAUSE_INVALID_STATE_FOR_MESSAGE}
  CAUSE_RECOVERY_ON_TIMEOUT               = $66;
  {$EXTERNALSYM CAUSE_RECOVERY_ON_TIMEOUT}
  CAUSE_INCORRECT_MESSAGE_LENGTH          = $68;
  {$EXTERNALSYM CAUSE_INCORRECT_MESSAGE_LENGTH}
  CAUSE_PROTOCOL_ERROR                    = $6F;
  {$EXTERNALSYM CAUSE_PROTOCOL_ERROR}

(*
 *  values used for the Condition portion of the Diagnostics field
 *  in struct ATM_CAUSE_IE, for certain Cause values
 *)

  CAUSE_COND_UNKNOWN   = $00;
  {$EXTERNALSYM CAUSE_COND_UNKNOWN}
  CAUSE_COND_PERMANENT = $01;
  {$EXTERNALSYM CAUSE_COND_PERMANENT}
  CAUSE_COND_TRANSIENT = $02;
  {$EXTERNALSYM CAUSE_COND_TRANSIENT}

(*
 *  values used for the Rejection Reason portion of the Diagnostics field
 *  in struct ATM_CAUSE_IE, for certain Cause values
 *)

  CAUSE_REASON_USER            = $00;
  {$EXTERNALSYM CAUSE_REASON_USER}
  CAUSE_REASON_IE_MISSING      = $04;
  {$EXTERNALSYM CAUSE_REASON_IE_MISSING}
  CAUSE_REASON_IE_INSUFFICIENT = $08;
  {$EXTERNALSYM CAUSE_REASON_IE_INSUFFICIENT}

(*
 *  values used for the P-U flag of the Diagnostics field
 *  in struct ATM_CAUSE_IE, for certain Cause values
 *)

  CAUSE_PU_PROVIDER = $00;
  {$EXTERNALSYM CAUSE_PU_PROVIDER}
  CAUSE_PU_USER     = $08;
  {$EXTERNALSYM CAUSE_PU_USER}

(*
 *  values used for the N-A flag of the Diagnostics field
 *  in struct ATM_CAUSE_IE, for certain Cause values
 *)

  CAUSE_NA_NORMAL   = $00;
  {$EXTERNALSYM CAUSE_NA_NORMAL}
  CAUSE_NA_ABNORMAL = $04;
  {$EXTERNALSYM CAUSE_NA_ABNORMAL}

type
  ATM_CAUSE_IE = record
    Location: UCHAR;
    Cause: UCHAR;
    DiagnosticsLength: UCHAR;
    Diagnostics: array [0..3] of UCHAR;
  end;
  {$EXTERNALSYM ATM_CAUSE_IE}
  TAtmCauseIE = ATM_CAUSE_IE;
  PAtmCauseIE = ^ATM_CAUSE_IE;

(*
 *  values used for the QOSClassForward and QOSClassBackward
 *  field in struct ATM_QOS_CLASS_IE
 *)

const
  QOS_CLASS0 = $00;
  {$EXTERNALSYM QOS_CLASS0}
  QOS_CLASS1 = $01;
  {$EXTERNALSYM QOS_CLASS1}
  QOS_CLASS2 = $02;
  {$EXTERNALSYM QOS_CLASS2}
  QOS_CLASS3 = $03;
  {$EXTERNALSYM QOS_CLASS3}
  QOS_CLASS4 = $04;
  {$EXTERNALSYM QOS_CLASS4}

type
  ATM_QOS_CLASS_IE = record
    QOSClassForward: UCHAR;
    QOSClassBackward: UCHAR;
  end;
  {$EXTERNALSYM ATM_QOS_CLASS_IE}
  TAtmQosClassIE = ATM_QOS_CLASS_IE;
  PAtmQosClassIE = ^ATM_QOS_CLASS_IE;

(*
 *  values used for the TypeOfNetworkId field in struct ATM_TRANSIT_NETWORK_SELECTION_IE
 *)

const
  TNS_TYPE_NATIONAL = $40;
  {$EXTERNALSYM TNS_TYPE_NATIONAL}

(*
 *  values used for the NetworkIdPlan field in struct ATM_TRANSIT_NETWORK_SELECTION_IE
 *)

  TNS_PLAN_CARRIER_ID_CODE = $01;
  {$EXTERNALSYM TNS_PLAN_CARRIER_ID_CODE}

type
  ATM_TRANSIT_NETWORK_SELECTION_IE = record
    TypeOfNetworkId: UCHAR;
    NetworkIdPlan: UCHAR;
    NetworkIdLength: UCHAR;
    NetworkId: array [0..0] of UCHAR;
  end;
  {$EXTERNALSYM ATM_TRANSIT_NETWORK_SELECTION_IE}
  TAtmTransitNetworkSelectionIE = ATM_TRANSIT_NETWORK_SELECTION_IE;
  PAtmTransitNetworkSelectionIE = ^ATM_TRANSIT_NETWORK_SELECTION_IE;

(*
 *  ATM specific Ioctl codes
 *)

const
  SIO_GET_NUMBER_OF_ATM_DEVICES = $50160001;
  {$EXTERNALSYM SIO_GET_NUMBER_OF_ATM_DEVICES}
  SIO_GET_ATM_ADDRESS           = DWORD($d0160002);
  {$EXTERNALSYM SIO_GET_ATM_ADDRESS}
  SIO_ASSOCIATE_PVC             = DWORD($90160003);
  {$EXTERNALSYM SIO_ASSOCIATE_PVC}
  SIO_GET_ATM_CONNECTION_ID     = $50160004;
  {$EXTERNALSYM SIO_GET_ATM_CONNECTION_ID}

(* ATM Connection Identifier *)

type
  ATM_CONNECTION_ID = record
    DeviceNumber: DWORD;
    VPI: DWORD;
    VCI: DWORD;
  end;
  {$EXTERNALSYM ATM_CONNECTION_ID}
  TAtmConnectionID = ATM_CONNECTION_ID;
  PAtmConnectionID = ^ATM_CONNECTION_ID;

(*
 * Input buffer format for SIO_ASSOCIATE_PVC
 *)

  ATM_PVC_PARAMS = record
   PvcConnectionId: ATM_CONNECTION_ID;
   PvcQos: QOS;
  end;
  {$EXTERNALSYM ATM_PVC_PARAMS}
  TAtmPvcParams = ATM_PVC_PARAMS;
  PAtmPvcParams = ^ATM_PVC_PARAMS;

implementation

end.
