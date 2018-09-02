{******************************************************************************}
{                                                       	               }
{ Winsock2 Quality Of Service API interface Unit for Object Pascal             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: qos.h, released June 2000. The original Pascal         }
{ code is: Qos.pas, released December 2000. The initial developer of the       }
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

unit JwaQos;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "qos.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

type
  ULONG = Cardinal;
  {$NODEFINE ULONG}

//
//  Definitions for valued-based Service Type for each direction of data flow.
//

type
  SERVICETYPE = ULONG;
  {$EXTERNALSYM SERVICETYPE}
  TServiceType = SERVICETYPE;
  PServiceType = ^TServiceType;

const
  SERVICETYPE_NOTRAFFIC           = $00000000;  // No data in this direction
  {$EXTERNALSYM SERVICETYPE_NOTRAFFIC}
  SERVICETYPE_BESTEFFORT          = $00000001;  // Best Effort
  {$EXTERNALSYM SERVICETYPE_BESTEFFORT}
  SERVICETYPE_CONTROLLEDLOAD      = $00000002;  // Controlled Load
  {$EXTERNALSYM SERVICETYPE_CONTROLLEDLOAD}
  SERVICETYPE_GUARANTEED          = $00000003;  // Guaranteed
  {$EXTERNALSYM SERVICETYPE_GUARANTEED}
  SERVICETYPE_NETWORK_UNAVAILABLE = $00000004;  // Used to notify change to user
  {$EXTERNALSYM SERVICETYPE_NETWORK_UNAVAILABLE}
  SERVICETYPE_GENERAL_INFORMATION = $00000005;  // corresponds to "General Parameters" defined by IntServ
  {$EXTERNALSYM SERVICETYPE_GENERAL_INFORMATION}
  SERVICETYPE_NOCHANGE            = $00000006;  // used to indicate that the flow spec contains no change from any previous one
  {$EXTERNALSYM SERVICETYPE_NOCHANGE}
  SERVICETYPE_NONCONFORMING       = $00000009;  // Non-Conforming Traffic
  {$EXTERNALSYM SERVICETYPE_NONCONFORMING}
  SERVICETYPE_NETWORK_CONTROL     = $0000000A;  // Network Control traffic
  {$EXTERNALSYM SERVICETYPE_NETWORK_CONTROL}
  SERVICETYPE_QUALITATIVE         = $0000000D;  // Qualitative applications
  {$EXTERNALSYM SERVICETYPE_QUALITATIVE}

// *********  The usage of these is currently not supported.  ***************

  SERVICE_BESTEFFORT     = DWORD($80010000);
  {$EXTERNALSYM SERVICE_BESTEFFORT}
  SERVICE_CONTROLLEDLOAD = DWORD($80020000);
  {$EXTERNALSYM SERVICE_CONTROLLEDLOAD}
  SERVICE_GUARANTEED     = DWORD($80040000);
  {$EXTERNALSYM SERVICE_GUARANTEED}
  SERVICE_QUALITATIVE    = DWORD($80200000);
  {$EXTERNALSYM SERVICE_QUALITATIVE}

// ***************************** ***** ************************************

//
// Flags to control the usage of RSVP on this flow.
//

//
// to turn off traffic control, 'OR' ( | ) this flag with the
// ServiceType field in the FLOWSPEC
//

  SERVICE_NO_TRAFFIC_CONTROL = DWORD($81000000);
  {$EXTERNALSYM SERVICE_NO_TRAFFIC_CONTROL}

//
// this flag can be used to prevent any rsvp signaling messages from being
// sent. Local traffic control will be invoked, but no RSVP Path messages
// will be sent.This flag can also be used in conjunction with a receiving
// flowspec to suppress the automatic generation of a Reserve message.
// The application would receive notification that a Path  message had arrived
// and would then need to alter the QOS by issuing WSAIoctl( SIO_SET_QOS ),
// to unset this flag and thereby causing Reserve messages to go out.
//

  SERVICE_NO_QOS_SIGNALING = $40000000;
  {$EXTERNALSYM SERVICE_NO_QOS_SIGNALING}

//
//  Flow Specifications for each direction of data flow.
//

type
  _flowspec = record
    TokenRate: ULONG;              // In Bytes/sec
    TokenBucketSize: ULONG;        // In Bytes
    PeakBandwidth: ULONG;          // In Bytes/sec
    Latency: ULONG;                // In microseconds
    DelayVariation: ULONG;         // In microseconds
    ServiceType: SERVICETYPE;
    MaxSduSize: ULONG;             // In Bytes
    MinimumPolicedSize: ULONG;     // In Bytes
  end;
  {$EXTERNALSYM _flowspec}
  FLOWSPEC = _flowspec;
  {$EXTERNALSYM FLOWSPEC}
  PFLOWSPEC = ^FLOWSPEC;
  {$EXTERNALSYM PFLOWSPEC}
  LPFLOWSPEC = ^FLOWSPEC;
  {$EXTERNALSYM LPFLOWSPEC}
  TFlowSpec = FLOWSPEC;

//
// this value can be used in the FLOWSPEC structure to instruct the Rsvp Service
// provider to derive the appropriate default value for the parameter.  Note
// that not all values in the FLOWSPEC structure can be defaults. In the
// ReceivingFlowspec, all parameters can be defaulted except the ServiceType.
// In the SendingFlowspec, the MaxSduSize and MinimumPolicedSize can be
// defaulted. Other defaults may be possible. Refer to the appropriate
// documentation.
//

const
  QOS_NOT_SPECIFIED = DWORD($FFFFFFFF);
  {$EXTERNALSYM QOS_NOT_SPECIFIED}

//
// define a value that can be used for the PeakBandwidth, which will map into
// positive infinity when the FLOWSPEC is converted into IntServ floating point
// format.  We can't use (-1) because that value was previously defined to mean
// "select the default".
//

  POSITIVE_INFINITY_RATE = DWORD($FFFFFFFE);
  {$EXTERNALSYM POSITIVE_INFINITY_RATE}

//
// the provider specific structure can have a number of objects in it.
// Each next structure in the
// ProviderSpecific will be the QOS_OBJECT_HDR struct that prefaces the actual
// data with a type and length for that object.  This QOS_OBJECT struct can
// repeat several times if there are several objects.  This list of objects
// terminates either when the buffer length has been reached ( WSABUF ) or
// an object of type QOS_END_OF_LIST is encountered.
//

type
  QOS_OBJECT_HDR = record
    ObjectType: ULONG;
    ObjectLength: ULONG;  // the length of object buffer INCLUDING this header
  end;
  {$EXTERNALSYM QOS_OBJECT_HDR}
  LPQOS_OBJECT_HDR = ^QOS_OBJECT_HDR;
  {$EXTERNALSYM LPQOS_OBJECT_HDR}
  TQOSObjectHdr = QOS_OBJECT_HDR;
  PQOSObjectHdr = LPQOS_OBJECT_HDR;

//
// general QOS objects start at this offset from the base and have a range
// of 1000
//

const
  QOS_GENERAL_ID_BASE = 2000;
  {$EXTERNALSYM QOS_GENERAL_ID_BASE}

  QOS_OBJECT_END_OF_LIST = ($00000001 + QOS_GENERAL_ID_BASE); // QOS_End_of_list structure passed
  {$EXTERNALSYM QOS_OBJECT_END_OF_LIST}

  QOS_OBJECT_SD_MODE = ($00000002 + QOS_GENERAL_ID_BASE); // QOS_ShapeDiscard structure passed
  {$EXTERNALSYM QOS_OBJECT_SD_MODE}

  QOS_OBJECT_SHAPING_RATE = ($00000003 + QOS_GENERAL_ID_BASE); // QOS_ShapingRate structure
  {$EXTERNALSYM QOS_OBJECT_SHAPING_RATE	}

  QOS_OBJECT_DESTADDR = ($00000004 + QOS_GENERAL_ID_BASE); // QOS_DestAddr structure (defined in qossp.h)
  {$EXTERNALSYM QOS_OBJECT_DESTADDR}

//
// This structure is used to define the behaviour that the traffic
// control packet shaper will apply to the flow.
//
// TC_NONCONF_BORROW - the flow will receive resources remaining
//  after all higher priority flows have been serviced. If a
//  TokenRate is specified, packets may be non-conforming and
//  will be demoted to less than best-effort priority.
//
// TC_NONCONF_SHAPE - TokenRate must be specified. Non-conforming
//  packets will be retianed in the packet shaper until they become
//  conforming.
//
// TC_NONCONF_DISCARD - TokenRate must be specified. Non-conforming
//  packets will be discarded.
//

type
  _QOS_SD_MODE = record
    ObjectHdr: QOS_OBJECT_HDR;
    ShapeDiscardMode: ULONG;
  end;
  {$EXTERNALSYM _QOS_SD_MODE}
  QOS_SD_MODE = _QOS_SD_MODE;
  {$EXTERNALSYM QOS_SD_MODE}
  LPQOS_SD_MODE = ^QOS_SD_MODE;
  {$EXTERNALSYM LPQOS_SD_MODE}
  TQOSSDMode = QOS_SD_MODE;
  PQOSSDMode = LPQOS_SD_MODE;

const
  TC_NONCONF_BORROW      = 0;
  {$EXTERNALSYM TC_NONCONF_BORROW}
  TC_NONCONF_SHAPE       = 1;
  {$EXTERNALSYM TC_NONCONF_SHAPE}
  TC_NONCONF_DISCARD     = 2;
  {$EXTERNALSYM TC_NONCONF_DISCARD}
  TC_NONCONF_BORROW_PLUS = 3;  // not supported currently
  {$EXTERNALSYM TC_NONCONF_BORROW_PLUS}

//
// This structure allows an app to specify a prorated "average token rate" using by
// the traffic shaper under SHAPE modehaper queue. It is expressed in bytes per sec.
//
// ShapingRate (bytes per sec.)
//

type
  _QOS_SHAPING_RATE = record
    ObjectHdr: QOS_OBJECT_HDR;
    ShapingRate: ULONG;
  end;
  {$EXTERNALSYM _QOS_SHAPING_RATE}
  QOS_SHAPING_RATE = _QOS_SHAPING_RATE;
  {$EXTERNALSYM QOS_SHAPING_RATE}
  LPQOS_SHAPING_RATE = ^QOS_SHAPING_RATE;
  {$EXTERNALSYM LPQOS_SHAPING_RATE}
  TQOSShapingRate = QOS_SHAPING_RATE;
  PQOSShapingRate = LPQOS_SHAPING_RATE;

implementation

end.
