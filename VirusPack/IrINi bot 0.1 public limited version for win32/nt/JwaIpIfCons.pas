{******************************************************************************}
{                                                       	               }
{ Internet Protocol Helper API interface Unit for Object Pascal                }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: ipifcons.h, released August 2001. The original Pascal  }
{ code is: IpIfCons.pas, released September 2000. The initial developer of the }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Contributor(s): John C. Penman (jcp@craiglockhart.com)                       }
{                 Vladimir Vassiliev (voldemarv@hotpop.com)                    }
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

unit JwaIpIfCons;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "ipifcons.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Media types                                                              //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

const
  MIN_IF_TYPE = 1;
  {$EXTERNALSYM MIN_IF_TYPE}

  IF_TYPE_OTHER                   = 1; // None of the below
  {$EXTERNALSYM IF_TYPE_OTHER}
  IF_TYPE_REGULAR_1822            = 2;
  {$EXTERNALSYM IF_TYPE_REGULAR_1822}
  IF_TYPE_HDH_1822                = 3;
  {$EXTERNALSYM IF_TYPE_HDH_1822}
  IF_TYPE_DDN_X25                 = 4;
  {$EXTERNALSYM IF_TYPE_DDN_X25}
  IF_TYPE_RFC877_X25              = 5;
  {$EXTERNALSYM IF_TYPE_RFC877_X25}
  IF_TYPE_ETHERNET_CSMACD         = 6;
  {$EXTERNALSYM IF_TYPE_ETHERNET_CSMACD}
  IF_TYPE_IS088023_CSMACD         = 7;
  {$EXTERNALSYM IF_TYPE_IS088023_CSMACD}
  IF_TYPE_ISO88024_TOKENBUS       = 8;
  {$EXTERNALSYM IF_TYPE_ISO88024_TOKENBUS}
  IF_TYPE_ISO88025_TOKENRING      = 9;
  {$EXTERNALSYM IF_TYPE_ISO88025_TOKENRING}
  IF_TYPE_ISO88026_MAN            = 10;
  {$EXTERNALSYM IF_TYPE_ISO88026_MAN}
  IF_TYPE_STARLAN                 = 11;
  {$EXTERNALSYM IF_TYPE_STARLAN}
  IF_TYPE_PROTEON_10MBIT          = 12;
  {$EXTERNALSYM IF_TYPE_PROTEON_10MBIT}
  IF_TYPE_PROTEON_80MBIT          = 13;
  {$EXTERNALSYM IF_TYPE_PROTEON_80MBIT}
  IF_TYPE_HYPERCHANNEL            = 14;
  {$EXTERNALSYM IF_TYPE_HYPERCHANNEL}
  IF_TYPE_FDDI                    = 15;
  {$EXTERNALSYM IF_TYPE_FDDI}
  IF_TYPE_LAP_B                   = 16;
  {$EXTERNALSYM IF_TYPE_LAP_B}
  IF_TYPE_SDLC                    = 17;
  {$EXTERNALSYM IF_TYPE_SDLC}
  IF_TYPE_DS1                     = 18; // DS1-MIB
  {$EXTERNALSYM IF_TYPE_DS1}
  IF_TYPE_E1                      = 19; // Obsolete; see DS1-MIB
  {$EXTERNALSYM IF_TYPE_E1}
  IF_TYPE_BASIC_ISDN              = 20;
  {$EXTERNALSYM IF_TYPE_BASIC_ISDN}
  IF_TYPE_PRIMARY_ISDN            = 21;
  {$EXTERNALSYM IF_TYPE_PRIMARY_ISDN}
  IF_TYPE_PROP_POINT2POINT_SERIAL = 22; // proprietary serial
  {$EXTERNALSYM IF_TYPE_PROP_POINT2POINT_SERIAL}
  IF_TYPE_PPP                     = 23;
  {$EXTERNALSYM IF_TYPE_PPP}
  IF_TYPE_SOFTWARE_LOOPBACK       = 24;
  {$EXTERNALSYM IF_TYPE_SOFTWARE_LOOPBACK}
  IF_TYPE_EON                     = 25; // CLNP over IP
  {$EXTERNALSYM IF_TYPE_EON}
  IF_TYPE_ETHERNET_3MBIT          = 26;
  {$EXTERNALSYM IF_TYPE_ETHERNET_3MBIT}
  IF_TYPE_NSIP                    = 27; // XNS over IP
  {$EXTERNALSYM IF_TYPE_NSIP}
  IF_TYPE_SLIP                    = 28; // Generic Slip
  {$EXTERNALSYM IF_TYPE_SLIP}
  IF_TYPE_ULTRA                   = 29; // ULTRA Technologies
  {$EXTERNALSYM IF_TYPE_ULTRA}
  IF_TYPE_DS3                     = 30; // DS3-MIB
  {$EXTERNALSYM IF_TYPE_DS3}
  IF_TYPE_SIP                     = 31; // SMDS, coffee
  {$EXTERNALSYM IF_TYPE_SIP}
  IF_TYPE_FRAMERELAY              = 32; // DTE only
  {$EXTERNALSYM IF_TYPE_FRAMERELAY}
  IF_TYPE_RS232                   = 33;
  {$EXTERNALSYM IF_TYPE_RS232}
  IF_TYPE_PARA                    = 34; // Parallel port
  {$EXTERNALSYM IF_TYPE_PARA}
  IF_TYPE_ARCNET                  = 35;
  {$EXTERNALSYM IF_TYPE_ARCNET}
  IF_TYPE_ARCNET_PLUS             = 36;
  {$EXTERNALSYM IF_TYPE_ARCNET_PLUS}
  IF_TYPE_ATM                     = 37; // ATM cells
  {$EXTERNALSYM IF_TYPE_ATM}
  IF_TYPE_MIO_X25                 = 38;
  {$EXTERNALSYM IF_TYPE_MIO_X25}
  IF_TYPE_SONET                   = 39; // SONET or SDH
  {$EXTERNALSYM IF_TYPE_SONET}
  IF_TYPE_X25_PLE                 = 40;
  {$EXTERNALSYM IF_TYPE_X25_PLE}
  IF_TYPE_ISO88022_LLC            = 41;
  {$EXTERNALSYM IF_TYPE_ISO88022_LLC}
  IF_TYPE_LOCALTALK               = 42;
  {$EXTERNALSYM IF_TYPE_LOCALTALK}
  IF_TYPE_SMDS_DXI                = 43;
  {$EXTERNALSYM IF_TYPE_SMDS_DXI}
  IF_TYPE_FRAMERELAY_SERVICE      = 44; // FRNETSERV-MIB
  {$EXTERNALSYM IF_TYPE_FRAMERELAY_SERVICE}
  IF_TYPE_V35                     = 45;
  {$EXTERNALSYM IF_TYPE_V35}
  IF_TYPE_HSSI                    = 46;
  {$EXTERNALSYM IF_TYPE_HSSI}
  IF_TYPE_HIPPI                   = 47;
  {$EXTERNALSYM IF_TYPE_HIPPI}
  IF_TYPE_MODEM                   = 48; // Generic Modem
  {$EXTERNALSYM IF_TYPE_MODEM}
  IF_TYPE_AAL5                    = 49; // AAL5 over ATM
  {$EXTERNALSYM IF_TYPE_AAL5}
  IF_TYPE_SONET_PATH              = 50;
  {$EXTERNALSYM IF_TYPE_SONET_PATH}
  IF_TYPE_SONET_VT                = 51;
  {$EXTERNALSYM IF_TYPE_SONET_VT}
  IF_TYPE_SMDS_ICIP               = 52; // SMDS InterCarrier Interface
  {$EXTERNALSYM IF_TYPE_SMDS_ICIP}
  IF_TYPE_PROP_VIRTUAL            = 53; // Proprietary virtual/internal
  {$EXTERNALSYM IF_TYPE_PROP_VIRTUAL}
  IF_TYPE_PROP_MULTIPLEXOR        = 54; // Proprietary multiplexing
  {$EXTERNALSYM IF_TYPE_PROP_MULTIPLEXOR}
  IF_TYPE_IEEE80212               = 55; // 100BaseVG
  {$EXTERNALSYM IF_TYPE_IEEE80212}
  IF_TYPE_FIBRECHANNEL            = 56;
  {$EXTERNALSYM IF_TYPE_FIBRECHANNEL}
  IF_TYPE_HIPPIINTERFACE          = 57;
  {$EXTERNALSYM IF_TYPE_HIPPIINTERFACE}
  IF_TYPE_FRAMERELAY_INTERCONNECT = 58; // Obsolete, use 32 or 44
  {$EXTERNALSYM IF_TYPE_FRAMERELAY_INTERCONNECT}
  IF_TYPE_AFLANE_8023             = 59; // ATM Emulated LAN for 802.3
  {$EXTERNALSYM IF_TYPE_AFLANE_8023}
  IF_TYPE_AFLANE_8025             = 60; // ATM Emulated LAN for 802.5
  {$EXTERNALSYM IF_TYPE_AFLANE_8025}
  IF_TYPE_CCTEMUL                 = 61; // ATM Emulated circuit
  {$EXTERNALSYM IF_TYPE_CCTEMUL}
  IF_TYPE_FASTETHER               = 62; // Fast Ethernet (100BaseT)
  {$EXTERNALSYM IF_TYPE_FASTETHER}
  IF_TYPE_ISDN                    = 63; // ISDN and X.25
  {$EXTERNALSYM IF_TYPE_ISDN}
  IF_TYPE_V11                     = 64; // CCITT V.11/X.21
  {$EXTERNALSYM IF_TYPE_V11}
  IF_TYPE_V36                     = 65; // CCITT V.36
  {$EXTERNALSYM IF_TYPE_V36}
  IF_TYPE_G703_64K                = 66; // CCITT G703 at 64Kbps
  {$EXTERNALSYM IF_TYPE_G703_64K}
  IF_TYPE_G703_2MB                = 67; // Obsolete; see DS1-MIB
  {$EXTERNALSYM IF_TYPE_G703_2MB}
  IF_TYPE_QLLC                    = 68; // SNA QLLC
  {$EXTERNALSYM IF_TYPE_QLLC}
  IF_TYPE_FASTETHER_FX            = 69; // Fast Ethernet (100BaseFX)
  {$EXTERNALSYM IF_TYPE_FASTETHER_FX}
  IF_TYPE_CHANNEL                 = 70;
  {$EXTERNALSYM IF_TYPE_CHANNEL}
  IF_TYPE_IEEE80211               = 71; // Radio spread spectrum
  {$EXTERNALSYM IF_TYPE_IEEE80211}
  IF_TYPE_IBM370PARCHAN           = 72; // IBM System 360/370 OEMI Channel
  {$EXTERNALSYM IF_TYPE_IBM370PARCHAN}
  IF_TYPE_ESCON                   = 73; // IBM Enterprise Systems Connection
  {$EXTERNALSYM IF_TYPE_ESCON}
  IF_TYPE_DLSW                    = 74; // Data Link Switching
  {$EXTERNALSYM IF_TYPE_DLSW}
  IF_TYPE_ISDN_S                  = 75; // ISDN S/T interface
  {$EXTERNALSYM IF_TYPE_ISDN_S}
  IF_TYPE_ISDN_U                  = 76; // ISDN U interface
  {$EXTERNALSYM IF_TYPE_ISDN_U}
  IF_TYPE_LAP_D                   = 77; // Link Access Protocol D
  {$EXTERNALSYM IF_TYPE_LAP_D}
  IF_TYPE_IPSWITCH                = 78; // IP Switching Objects
  {$EXTERNALSYM IF_TYPE_IPSWITCH}
  IF_TYPE_RSRB                    = 79; // Remote Source Route Bridging
  {$EXTERNALSYM IF_TYPE_RSRB}
  IF_TYPE_ATM_LOGICAL             = 80; // ATM Logical Port
  {$EXTERNALSYM IF_TYPE_ATM_LOGICAL}
  IF_TYPE_DS0                     = 81; // Digital Signal Level 0
  {$EXTERNALSYM IF_TYPE_DS0}
  IF_TYPE_DS0_BUNDLE              = 82; // Group of ds0s on the same ds1
  {$EXTERNALSYM IF_TYPE_DS0_BUNDLE}
  IF_TYPE_BSC                     = 83; // Bisynchronous Protocol
  {$EXTERNALSYM IF_TYPE_BSC}
  IF_TYPE_ASYNC                   = 84; // Asynchronous Protocol
  {$EXTERNALSYM IF_TYPE_ASYNC}
  IF_TYPE_CNR                     = 85; // Combat Net Radio
  {$EXTERNALSYM IF_TYPE_CNR}
  IF_TYPE_ISO88025R_DTR           = 86; // ISO 802.5r DTR
  {$EXTERNALSYM IF_TYPE_ISO88025R_DTR}
  IF_TYPE_EPLRS                   = 87; // Ext Pos Loc Report Sys
  {$EXTERNALSYM IF_TYPE_EPLRS}
  IF_TYPE_ARAP                    = 88; // Appletalk Remote Access Protocol
  {$EXTERNALSYM IF_TYPE_ARAP}
  IF_TYPE_PROP_CNLS               = 89; // Proprietary Connectionless Proto
  {$EXTERNALSYM IF_TYPE_PROP_CNLS}
  IF_TYPE_HOSTPAD                 = 90; // CCITT-ITU X.29 PAD Protocol
  {$EXTERNALSYM IF_TYPE_HOSTPAD}
  IF_TYPE_TERMPAD                 = 91; // CCITT-ITU X.3 PAD Facility
  {$EXTERNALSYM IF_TYPE_TERMPAD}
  IF_TYPE_FRAMERELAY_MPI          = 92; // Multiproto Interconnect over FR
  {$EXTERNALSYM IF_TYPE_FRAMERELAY_MPI}
  IF_TYPE_X213                    = 93; // CCITT-ITU X213
  {$EXTERNALSYM IF_TYPE_X213}
  IF_TYPE_ADSL                    = 94; // Asymmetric Digital Subscrbr Loop
  {$EXTERNALSYM IF_TYPE_ADSL}
  IF_TYPE_RADSL                   = 95; // Rate-Adapt Digital Subscrbr Loop
  {$EXTERNALSYM IF_TYPE_RADSL}
  IF_TYPE_SDSL                    = 96; // Symmetric Digital Subscriber Loop
  {$EXTERNALSYM IF_TYPE_SDSL}
  IF_TYPE_VDSL                    = 97; // Very H-Speed Digital Subscrb Loop
  {$EXTERNALSYM IF_TYPE_VDSL}
  IF_TYPE_ISO88025_CRFPRINT       = 98; // ISO 802.5 CRFP
  {$EXTERNALSYM IF_TYPE_ISO88025_CRFPRINT}
  IF_TYPE_MYRINET                 = 99; // Myricom Myrinet
  {$EXTERNALSYM IF_TYPE_MYRINET}
  IF_TYPE_VOICE_EM                = 100; // Voice recEive and transMit
  {$EXTERNALSYM IF_TYPE_VOICE_EM}
  IF_TYPE_VOICE_FXO               = 101; // Voice Foreign Exchange Office
  {$EXTERNALSYM IF_TYPE_VOICE_FXO}
  IF_TYPE_VOICE_FXS               = 102; // Voice Foreign Exchange Station
  {$EXTERNALSYM IF_TYPE_VOICE_FXS}
  IF_TYPE_VOICE_ENCAP             = 103; // Voice encapsulation
  {$EXTERNALSYM IF_TYPE_VOICE_ENCAP}
  IF_TYPE_VOICE_OVERIP            = 104; // Voice over IP encapsulation
  {$EXTERNALSYM IF_TYPE_VOICE_OVERIP}
  IF_TYPE_ATM_DXI                 = 105; // ATM DXI
  {$EXTERNALSYM IF_TYPE_ATM_DXI}
  IF_TYPE_ATM_FUNI                = 106; // ATM FUNI
  {$EXTERNALSYM IF_TYPE_ATM_FUNI}
  IF_TYPE_ATM_IMA                 = 107; // ATM IMA
  {$EXTERNALSYM IF_TYPE_ATM_IMA}
  IF_TYPE_PPPMULTILINKBUNDLE      = 108; // PPP Multilink Bundle
  {$EXTERNALSYM IF_TYPE_PPPMULTILINKBUNDLE}
  IF_TYPE_IPOVER_CDLC             = 109; // IBM ipOverCdlc
  {$EXTERNALSYM IF_TYPE_IPOVER_CDLC}
  IF_TYPE_IPOVER_CLAW             = 110; // IBM Common Link Access to Workstn
  {$EXTERNALSYM IF_TYPE_IPOVER_CLAW}
  IF_TYPE_STACKTOSTACK            = 111; // IBM stackToStack
  {$EXTERNALSYM IF_TYPE_STACKTOSTACK}
  IF_TYPE_VIRTUALIPADDRESS        = 112; // IBM VIPA
  {$EXTERNALSYM IF_TYPE_VIRTUALIPADDRESS}
  IF_TYPE_MPC                     = 113; // IBM multi-proto channel support
  {$EXTERNALSYM IF_TYPE_MPC}
  IF_TYPE_IPOVER_ATM              = 114; // IBM ipOverAtm
  {$EXTERNALSYM IF_TYPE_IPOVER_ATM}
  IF_TYPE_ISO88025_FIBER          = 115; // ISO 802.5j Fiber Token Ring
  {$EXTERNALSYM IF_TYPE_ISO88025_FIBER}
  IF_TYPE_TDLC                    = 116; // IBM twinaxial data link control
  {$EXTERNALSYM IF_TYPE_TDLC}
  IF_TYPE_GIGABITETHERNET         = 117;
  {$EXTERNALSYM IF_TYPE_GIGABITETHERNET}
  IF_TYPE_HDLC                    = 118;
  {$EXTERNALSYM IF_TYPE_HDLC}
  IF_TYPE_LAP_F                   = 119;
  {$EXTERNALSYM IF_TYPE_LAP_F}
  IF_TYPE_V37                     = 120;
  {$EXTERNALSYM IF_TYPE_V37}
  IF_TYPE_X25_MLP                 = 121; // Multi-Link Protocol
  {$EXTERNALSYM IF_TYPE_X25_MLP}
  IF_TYPE_X25_HUNTGROUP           = 122; // X.25 Hunt Group
  {$EXTERNALSYM IF_TYPE_X25_HUNTGROUP}
  IF_TYPE_TRANSPHDLC              = 123;
  {$EXTERNALSYM IF_TYPE_TRANSPHDLC}
  IF_TYPE_INTERLEAVE              = 124; // Interleave channel
  {$EXTERNALSYM IF_TYPE_INTERLEAVE}
  IF_TYPE_FAST                    = 125; // Fast channel
  {$EXTERNALSYM IF_TYPE_FAST}
  IF_TYPE_IP                      = 126; // IP (for APPN HPR in IP networks)
  {$EXTERNALSYM IF_TYPE_IP}
  IF_TYPE_DOCSCABLE_MACLAYER      = 127; // CATV Mac Layer
  {$EXTERNALSYM IF_TYPE_DOCSCABLE_MACLAYER}
  IF_TYPE_DOCSCABLE_DOWNSTREAM    = 128; // CATV Downstream interface
  {$EXTERNALSYM IF_TYPE_DOCSCABLE_DOWNSTREAM}
  IF_TYPE_DOCSCABLE_UPSTREAM      = 129; // CATV Upstream interface
  {$EXTERNALSYM IF_TYPE_DOCSCABLE_UPSTREAM}
  IF_TYPE_A12MPPSWITCH            = 130; // Avalon Parallel Processor
  {$EXTERNALSYM IF_TYPE_A12MPPSWITCH}
  IF_TYPE_TUNNEL                  = 131; // Encapsulation interface
  {$EXTERNALSYM IF_TYPE_TUNNEL}
  IF_TYPE_COFFEE                  = 132; // Coffee pot
  {$EXTERNALSYM IF_TYPE_COFFEE}
  IF_TYPE_CES                     = 133; // Circuit Emulation Service
  {$EXTERNALSYM IF_TYPE_CES}
  IF_TYPE_ATM_SUBINTERFACE        = 134; // ATM Sub Interface
  {$EXTERNALSYM IF_TYPE_ATM_SUBINTERFACE}
  IF_TYPE_L2_VLAN                 = 135; // Layer 2 Virtual LAN using 802.1Q
  {$EXTERNALSYM IF_TYPE_L2_VLAN}
  IF_TYPE_L3_IPVLAN               = 136; // Layer 3 Virtual LAN using IP
  {$EXTERNALSYM IF_TYPE_L3_IPVLAN}
  IF_TYPE_L3_IPXVLAN              = 137; // Layer 3 Virtual LAN using IPX
  {$EXTERNALSYM IF_TYPE_L3_IPXVLAN}
  IF_TYPE_DIGITALPOWERLINE        = 138; // IP over Power Lines
  {$EXTERNALSYM IF_TYPE_DIGITALPOWERLINE}
  IF_TYPE_MEDIAMAILOVERIP         = 139; // Multimedia Mail over IP
  {$EXTERNALSYM IF_TYPE_MEDIAMAILOVERIP}
  IF_TYPE_DTM                     = 140; // Dynamic syncronous Transfer Mode
  {$EXTERNALSYM IF_TYPE_DTM}
  IF_TYPE_DCN                     = 141; // Data Communications Network
  {$EXTERNALSYM IF_TYPE_DCN}
  IF_TYPE_IPFORWARD               = 142; // IP Forwarding Interface
  {$EXTERNALSYM IF_TYPE_IPFORWARD}
  IF_TYPE_MSDSL                   = 143; // Multi-rate Symmetric DSL
  {$EXTERNALSYM IF_TYPE_MSDSL}
  IF_TYPE_IEEE1394                = 144; // IEEE1394 High Perf Serial Bus
  {$EXTERNALSYM IF_TYPE_IEEE1394}
  IF_TYPE_RECEIVE_ONLY            = 145; // TV adapter type
  {$EXTERNALSYM IF_TYPE_RECEIVE_ONLY}

  MAX_IF_TYPE = 145;
  {$EXTERNALSYM MAX_IF_TYPE}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Access types                                                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

  IF_ACCESS_LOOPBACK          = 1;
  {$EXTERNALSYM IF_ACCESS_LOOPBACK}
  IF_ACCESS_BROADCAST         = 2;
  {$EXTERNALSYM IF_ACCESS_BROADCAST}
  IF_ACCESS_POINTTOPOINT      = 3;
  {$EXTERNALSYM IF_ACCESS_POINTTOPOINT}
  IF_ACCESS_POINTTOMULTIPOINT = 4;
  {$EXTERNALSYM IF_ACCESS_POINTTOMULTIPOINT}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Interface Capabilities (bit flags)                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

  IF_CHECK_NONE                  = $00;
  {$EXTERNALSYM IF_CHECK_NONE}
  IF_CHECK_MCAST                 = $01;
  {$EXTERNALSYM IF_CHECK_MCAST}
  IF_CHECK_SEND                  = $02;
  {$EXTERNALSYM IF_CHECK_SEND}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Connection Types                                                         //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

  IF_CONNECTION_DEDICATED = 1;
  {$EXTERNALSYM IF_CONNECTION_DEDICATED}
  IF_CONNECTION_PASSIVE   = 2;
  {$EXTERNALSYM IF_CONNECTION_PASSIVE}
  IF_CONNECTION_DEMAND    = 3;
  {$EXTERNALSYM IF_CONNECTION_DEMAND}

  IF_ADMIN_STATUS_UP      = 1;
  {$EXTERNALSYM IF_ADMIN_STATUS_UP}
  IF_ADMIN_STATUS_DOWN    = 2;
  {$EXTERNALSYM IF_ADMIN_STATUS_DOWN}
  IF_ADMIN_STATUS_TESTING = 3;
  {$EXTERNALSYM IF_ADMIN_STATUS_TESTING}

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// The following are the the operational states for WAN and LAN interfaces. //
// The order of the states seems weird, but is done for a purpose. All      //
// states >= CONNECTED can transmit data right away. States >= DISCONNECTED //
// can tx data but some set up might be needed. States < DISCONNECTED can   //
// not transmit data.                                                       //
// A card is marked UNREACHABLE if DIM calls InterfaceUnreachable for       //
// reasons other than failure to connect.                                   //
//                                                                          //
// NON_OPERATIONAL -- Valid for LAN Interfaces. Means the card is not       //
//                      working or not plugged in or has no address.        //
// UNREACHABLE     -- Valid for WAN Interfaces. Means the remote site is    //
//                      not reachable at this time.                         //
// DISCONNECTED    -- Valid for WAN Interfaces. Means the remote site is    //
//                      not connected at this time.                         //
// CONNECTING      -- Valid for WAN Interfaces. Means a connection attempt  //
//                      has been initiated to the remote site.              //
// CONNECTED       -- Valid for WAN Interfaces. Means the remote site is    //
//                      connected.                                          //
// OPERATIONAL     -- Valid for LAN Interfaces. Means the card is plugged   //
//                      in and working.                                     //
//                                                                          //
// It is the users duty to convert these values to MIB-II values if they    //
// are to be used by a subagent                                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

  IF_OPER_STATUS_NON_OPERATIONAL = 0;
  {$EXTERNALSYM IF_OPER_STATUS_NON_OPERATIONAL}
  IF_OPER_STATUS_UNREACHABLE     = 1;
  {$EXTERNALSYM IF_OPER_STATUS_UNREACHABLE}
  IF_OPER_STATUS_DISCONNECTED    = 2;
  {$EXTERNALSYM IF_OPER_STATUS_DISCONNECTED}
  IF_OPER_STATUS_CONNECTING      = 3;
  {$EXTERNALSYM IF_OPER_STATUS_CONNECTING}
  IF_OPER_STATUS_CONNECTED       = 4;
  {$EXTERNALSYM IF_OPER_STATUS_CONNECTED}
  IF_OPER_STATUS_OPERATIONAL     = 5;
  {$EXTERNALSYM IF_OPER_STATUS_OPERATIONAL}

  MIB_IF_TYPE_OTHER     = 1;
  {$EXTERNALSYM MIB_IF_TYPE_OTHER}
  MIB_IF_TYPE_ETHERNET  = 6;
  {$EXTERNALSYM MIB_IF_TYPE_ETHERNET}
  MIB_IF_TYPE_TOKENRING = 9;
  {$EXTERNALSYM MIB_IF_TYPE_TOKENRING}
  MIB_IF_TYPE_FDDI      = 15;
  {$EXTERNALSYM MIB_IF_TYPE_FDDI}
  MIB_IF_TYPE_PPP       = 23;
  {$EXTERNALSYM MIB_IF_TYPE_PPP}
  MIB_IF_TYPE_LOOPBACK  = 24;
  {$EXTERNALSYM MIB_IF_TYPE_LOOPBACK}
  MIB_IF_TYPE_SLIP      = 28;
  {$EXTERNALSYM MIB_IF_TYPE_SLIP}

  MIB_IF_ADMIN_STATUS_UP      = 1;
  {$EXTERNALSYM MIB_IF_ADMIN_STATUS_UP}
  MIB_IF_ADMIN_STATUS_DOWN    = 2;
  {$EXTERNALSYM MIB_IF_ADMIN_STATUS_DOWN}
  MIB_IF_ADMIN_STATUS_TESTING = 3;
  {$EXTERNALSYM MIB_IF_ADMIN_STATUS_TESTING}

  MIB_IF_OPER_STATUS_NON_OPERATIONAL = 0;
  {$EXTERNALSYM MIB_IF_OPER_STATUS_NON_OPERATIONAL}
  MIB_IF_OPER_STATUS_UNREACHABLE     = 1;
  {$EXTERNALSYM MIB_IF_OPER_STATUS_UNREACHABLE}
  MIB_IF_OPER_STATUS_DISCONNECTED    = 2;
  {$EXTERNALSYM MIB_IF_OPER_STATUS_DISCONNECTED}
  MIB_IF_OPER_STATUS_CONNECTING      = 3;
  {$EXTERNALSYM MIB_IF_OPER_STATUS_CONNECTING}
  MIB_IF_OPER_STATUS_CONNECTED       = 4;
  {$EXTERNALSYM MIB_IF_OPER_STATUS_CONNECTED}
  MIB_IF_OPER_STATUS_OPERATIONAL     = 5;
  {$EXTERNALSYM MIB_IF_OPER_STATUS_OPERATIONAL}

implementation

end.
