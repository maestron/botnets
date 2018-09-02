{******************************************************************************}
{                                                       	               }
{ Interface Unit for Object Pascal                                             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2003 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ Portions created by Marcel van Brakel are Copyright (C) 2003                 }
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

unit JwaWsrm;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wsrm.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

(*
**	wsrm.h - winsock extension for Reliable Multicast (RMCast) Transport
**
**	This file contains PGM specific information for use by WinSock2 compatible
**  applications that need Reliable Multicast Transport.
**
**  Copyright (c) Microsoft Corporation. All rights reserved.
**
**	Created: Mar 12, 2000
**
*)

const
  IPPROTO_RM     = 113;
  {$EXTERNALSYM IPPROTO_RM}
  MAX_MCAST_TTL  = 255;
  {$EXTERNALSYM MAX_MCAST_TTL}

//
// options for setsockopt, getsockopt
//
  RM_OPTIONSBASE      = 1000;
  {$EXTERNALSYM RM_OPTIONSBASE}

// Set/Query rate (Kb/Sec) + window size (Kb and/or MSec) -- described by RM_SEND_WINDOW below
  RM_RATE_WINDOW_SIZE            = (RM_OPTIONSBASE + 1);
  {$EXTERNALSYM RM_RATE_WINDOW_SIZE}

// Set the size of the next message -- (ULONG)
  RM_SET_MESSAGE_BOUNDARY        = (RM_OPTIONSBASE + 2);
  {$EXTERNALSYM RM_SET_MESSAGE_BOUNDARY}

// flush the entire data (window) right now -- not implemented
  RM_FLUSHCACHE                  = (RM_OPTIONSBASE + 3);
  {$EXTERNALSYM RM_FLUSHCACHE}

// Set or Query the window advance method on the sender -- methods enumerated in eWINDOW_ADVANCE_METHOD
  RM_SENDER_WINDOW_ADVANCE_METHOD = (RM_OPTIONSBASE + 4);
  {$EXTERNALSYM RM_SENDER_WINDOW_ADVANCE_METHOD}

// get sender statistics
  RM_SENDER_STATISTICS           = (RM_OPTIONSBASE + 5);
  {$EXTERNALSYM RM_SENDER_STATISTICS}

// allow a late-joiner to NAK any packet upto the lowest sequence Id
  RM_LATEJOIN                    = (RM_OPTIONSBASE + 6);
  {$EXTERNALSYM RM_LATEJOIN}

// set IP multicast outgoing interface
  RM_SET_SEND_IF                 = (RM_OPTIONSBASE + 7);
  {$EXTERNALSYM RM_SET_SEND_IF}

// add IP multicast incoming interface
  RM_ADD_RECEIVE_IF              = (RM_OPTIONSBASE + 8);
  {$EXTERNALSYM RM_ADD_RECEIVE_IF}

// delete IP multicast incoming interface
  RM_DEL_RECEIVE_IF              = (RM_OPTIONSBASE + 9);
  {$EXTERNALSYM RM_DEL_RECEIVE_IF}

// Set/Query the Window's Advance rate (has to be less that MAX_WINDOW_INCREMENT_PERCENTAGE)
  RM_SEND_WINDOW_ADV_RATE        = (RM_OPTIONSBASE + 10);
  {$EXTERNALSYM RM_SEND_WINDOW_ADV_RATE}

// Instruct to use parity-based forward error correction schemes
  RM_USE_FEC                     = (RM_OPTIONSBASE + 11);
  {$EXTERNALSYM RM_USE_FEC}

// Set the Ttl of the MCast packets -- (ULONG)
  RM_SET_MCAST_TTL               = (RM_OPTIONSBASE + 12);
  {$EXTERNALSYM RM_SET_MCAST_TTL}

// get receiver statistics
  RM_RECEIVER_STATISTICS         = (RM_OPTIONSBASE + 13);
  {$EXTERNALSYM RM_RECEIVER_STATISTICS}

// get receiver statistics
  RM_HIGH_SPEED_INTRANET_OPT     = (RM_OPTIONSBASE + 14);
  {$EXTERNALSYM RM_HIGH_SPEED_INTRANET_OPT}

//==============================================================
//
// Definitions
//

const
  SENDER_DEFAULT_RATE_KBITS_PER_SEC       = 56;             // 56 Kbits/Sec
  {$EXTERNALSYM SENDER_DEFAULT_RATE_KBITS_PER_SEC}
  SENDER_DEFAULT_WINDOW_SIZE_BYTES        = 10 *1000*1000;  // 10 Megs
  {$EXTERNALSYM SENDER_DEFAULT_WINDOW_SIZE_BYTES}

  SENDER_DEFAULT_WINDOW_ADV_PERCENTAGE    = 15;             // 15%
  {$EXTERNALSYM SENDER_DEFAULT_WINDOW_ADV_PERCENTAGE}
  MAX_WINDOW_INCREMENT_PERCENTAGE         = 25;             // 25%
  {$EXTERNALSYM MAX_WINDOW_INCREMENT_PERCENTAGE}

  SENDER_DEFAULT_LATE_JOINER_PERCENTAGE   = 0;              // 0%
  {$EXTERNALSYM SENDER_DEFAULT_LATE_JOINER_PERCENTAGE}
  SENDER_MAX_LATE_JOINER_PERCENTAGE       = 75;             // 75%
  {$EXTERNALSYM SENDER_MAX_LATE_JOINER_PERCENTAGE}

  BITS_PER_BYTE                           = 8;
  {$EXTERNALSYM BITS_PER_BYTE}
  LOG2_BITS_PER_BYTE                      = 3;
  {$EXTERNALSYM LOG2_BITS_PER_BYTE}

type
  eWINDOW_ADVANCE_METHOD = (E_WINDOW_ADVANCE_BY_TIME = 1, E_WINDOW_USE_AS_DATA_CACHE);
  {$EXTERNALSYM eWINDOW_ADVANCE_METHOD}

//==============================================================
//
// Structures
//

type
  _RM_SEND_WINDOW = record
    RateKbitsPerSec: ULONG;            // Send rate
    WindowSizeInMSecs: ULONG;
    WindowSizeInBytes: ULONG;
  end;
  {$EXTERNALSYM _RM_SEND_WINDOW}
  RM_SEND_WINDOW = _RM_SEND_WINDOW;
  {$EXTERNALSYM RM_SEND_WINDOW}
  TRmSendWindow = RM_SEND_WINDOW;

  _RM_SENDER_STATS = record
    DataBytesSent: ULONGLONG;          // # client data bytes sent out so far
    TotalBytesSent: ULONGLONG;         // SPM, OData and RData bytes
    NaksReceived: ULONGLONG;           // # NAKs received so far
    NaksReceivedTooLate: ULONGLONG;    // # NAKs recvd after window advanced
    NumOutstandingNaks: ULONGLONG;     // # NAKs yet to be responded to
    NumNaksAfterRData: ULONGLONG;      // # NAKs yet to be responded to
    RepairPacketsSent: ULONGLONG;      // # Repairs (RDATA) sent so far
    BufferSpaceAvailable: ULONGLONG;   // # partial messages dropped
    TrailingEdgeSeqId: ULONGLONG;      // smallest (oldest) Sequence Id in the window
    LeadingEdgeSeqId: ULONGLONG;       // largest (newest) Sequence Id in the window
    RateKBitsPerSecOverall: ULONGLONG; // Internally calculated send-rate from the beginning
    RateKBitsPerSecLast: ULONGLONG;    // Send-rate calculated every INTERNAL_RATE_CALCULATION_FREQUENCY
    TotalODataPacketsSent: ULONGLONG;  // # ODATA packets sent so far
  end;
  {$EXTERNALSYM _RM_SENDER_STATS}
  RM_SENDER_STATS = _RM_SENDER_STATS;
  {$EXTERNALSYM RM_SENDER_STATS}
  TRmSenderStats = RM_SENDER_STATS;

  _RM_RECEIVER_STATS = record
    NumODataPacketsReceived: ULONGLONG;// # OData sequences received
    NumRDataPacketsReceived: ULONGLONG;// # RData sequences received
    NumDuplicateDataPackets: ULONGLONG;// # RData sequences received

    DataBytesReceived: ULONGLONG;      // # client data bytes received out so far
    TotalBytesReceived: ULONGLONG;     // SPM, OData and RData bytes
    RateKBitsPerSecOverall: ULONGLONG; // Internally calculated Receive-rate from the beginning
    RateKBitsPerSecLast: ULONGLONG;    // Receive-rate calculated every INTERNAL_RATE_CALCULATION_FREQUENCY

    TrailingEdgeSeqId: ULONGLONG;      // smallest (oldest) Sequence Id in the window
    LeadingEdgeSeqId: ULONGLONG;       // largest (newest) Sequence Id in the window
    AverageSequencesInWindow: ULONGLONG;
    MinSequencesInWindow: ULONGLONG;
    MaxSequencesInWindow: ULONGLONG;

    FirstNakSequenceNumber: ULONGLONG; // # First Outstanding Nak
    NumPendingNaks: ULONGLONG;         // # Sequences waiting for Ncfs
    NumOutstandingNaks: ULONGLONG;     // # Sequences for which Ncfs have been received, but no data
    NumDataPacketsBuffered: ULONGLONG; // # Data packets currently buffered by transport
    TotalSelectiveNaksSent: ULONGLONG; // # Selective NAKs sent so far
    TotalParityNaksSent: ULONGLONG;    // # Parity NAKs sent so far
  end;
  {$EXTERNALSYM _RM_RECEIVER_STATS}
  RM_RECEIVER_STATS = _RM_RECEIVER_STATS;
  {$EXTERNALSYM RM_RECEIVER_STATS}
  TRmReceiverStats = RM_RECEIVER_STATS;

  _RM_FEC_INFO = record
    FECBlockSize: USHORT;
    FECProActivePackets: USHORT;
    FECGroupSize: UCHAR;
    fFECOnDemandParityEnabled: BOOLEAN;
  end;
  {$EXTERNALSYM _RM_FEC_INFO}
  RM_FEC_INFO = _RM_FEC_INFO;
  {$EXTERNALSYM RM_FEC_INFO}
  TRmFecInfo = RM_FEC_INFO;

implementation

end.
