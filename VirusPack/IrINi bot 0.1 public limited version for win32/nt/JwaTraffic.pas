{******************************************************************************}
{                                                       	               }
{ Traffic Control API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: traffic.h, released June 2000. The original Pascal     }
{ code is: Traffic.pas, released December 2000. The initial developer of the   }
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

unit JwaTraffic;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "traffic.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaQos;

//---------------------------------------------------------------------------
//
// Define's
//

const
  CURRENT_TCI_VERSION = $0002;
  {$EXTERNALSYM CURRENT_TCI_VERSION}

//
// Definitions of notification events. These may be passed
// to the client's notification handler, to identify the
// notification type
//

//
// A TC interface has come up
//

  TC_NOTIFY_IFC_UP = 1;
  {$EXTERNALSYM TC_NOTIFY_IFC_UP}

//
// A TC interface has come down
//

  TC_NOTIFY_IFC_CLOSE = 2;
  {$EXTERNALSYM TC_NOTIFY_IFC_CLOSE}

//
// A change on a TC interface, typically a change in the
// list of supported network addresses
//

  TC_NOTIFY_IFC_CHANGE = 3;
  {$EXTERNALSYM TC_NOTIFY_IFC_CHANGE}

//
// A TC parameter has changed
//

  TC_NOTIFY_PARAM_CHANGED = 4;
  {$EXTERNALSYM TC_NOTIFY_PARAM_CHANGED}

//
// A flow has been closed by the TC interface
// for example: after a remote call close, or the whole interface
// is going down
//

  TC_NOTIFY_FLOW_CLOSE = 5;
  {$EXTERNALSYM TC_NOTIFY_FLOW_CLOSE}

  TC_INVALID_HANDLE = HANDLE(0);
  {$EXTERNALSYM TC_INVALID_HANDLE}

  MAX_STRING_LENGTH = 256;
  {$EXTERNALSYM MAX_STRING_LENGTH}

//---------------------------------------------------------------------------
//
// Typedef's and structures
//

//
// Handlers registered by the TCI client
//

type
  TCI_NOTIFY_HANDLER = procedure (ClRegCtx, ClIfcCtx: HANDLE; Event: ULONG;
    SubCode: HANDLE; BufSize: ULONG; Buffer: PVOID); stdcall;
  {$EXTERNALSYM TCI_NOTIFY_HANDLER}
  TTciNotifyHandler = TCI_NOTIFY_HANDLER;

  TCI_ADD_FLOW_COMPLETE_HANDLER = procedure (ClFlowCtx: HANDLE; Status: ULONG); stdcall;
  {$EXTERNALSYM TCI_ADD_FLOW_COMPLETE_HANDLER}
  TTciAddFlowCompleteHandler = TCI_ADD_FLOW_COMPLETE_HANDLER;

  TCI_MOD_FLOW_COMPLETE_HANDLER = procedure (ClFlowCtx: HANDLE; Status: ULONG); stdcall;
  {$EXTERNALSYM TCI_MOD_FLOW_COMPLETE_HANDLER}
  TTciModFlowCompleteHandler = TCI_MOD_FLOW_COMPLETE_HANDLER;

  TCI_DEL_FLOW_COMPLETE_HANDLER = procedure (ClFlowCtx: HANDLE; Status: ULONG); stdcall;
  {$EXTERNALSYM TCI_DEL_FLOW_COMPLETE_HANDLER}
  TTciDelFlowComlpeteHandler = TCI_DEL_FLOW_COMPLETE_HANDLER;

type
  PTCI_CLIENT_FUNC_LIST = ^TCI_CLIENT_FUNC_LIST;
  {$EXTERNALSYM PTCI_CLIENT_FUNC_LIST}
  _TCI_CLIENT_FUNC_LIST = record
    ClNotifyHandler: TCI_NOTIFY_HANDLER;
    ClAddFlowCompleteHandler: TCI_ADD_FLOW_COMPLETE_HANDLER;
    ClModifyFlowCompleteHandler: TCI_MOD_FLOW_COMPLETE_HANDLER;
    ClDeleteFlowCompleteHandler: TCI_DEL_FLOW_COMPLETE_HANDLER;
  end;
  {$EXTERNALSYM _TCI_CLIENT_FUNC_LIST}
  TCI_CLIENT_FUNC_LIST = _TCI_CLIENT_FUNC_LIST;
  {$EXTERNALSYM TCI_CLIENT_FUNC_LIST}
  TTciClientFuncList = TCI_CLIENT_FUNC_LIST;
  PTciClientFuncList = PTCI_CLIENT_FUNC_LIST;

  // TODO NETWORD_ADDRESS and NETWORK_ADDRESS_LIST are from NtDDNdis.h

  _NETWORK_ADDRESS = record
    AddressLength: USHORT;		// length in bytes of Address[] in this
    AddressType: USHORT;		// type of this address (NDIS_PROTOCOL_ID_XXX above)
    Address: array [0..0] of UCHAR;	// actually AddressLength bytes long
  end;
  NETWORK_ADDRESS = _NETWORK_ADDRESS;
  PNETWORK_ADDRESS = ^NETWORK_ADDRESS;

  _NETWORK_ADDRESS_LIST = record
    AddressCount: LONG;  		// number of addresses following
    AddressType: USHORT;		// type of this address (NDIS_PROTOCOL_ID_XXX above)
    Address: array [0..0] of NETWORK_ADDRESS;		// actually AddressCount elements long
  end;
  NETWORK_ADDRESS_LIST = _NETWORK_ADDRESS_LIST;
  PNETWORK_ADDRESS_LIST = ^NETWORK_ADDRESS_LIST;

//
// Network address descriptor
//

  PADDRESS_LIST_DESCRIPTOR = ^ADDRESS_LIST_DESCRIPTOR;
  {$EXTERNALSYM PADDRESS_LIST_DESCRIPTOR}
  _ADDRESS_LIST_DESCRIPTOR = record
    MediaType: ULONG;
    AddressList: NETWORK_ADDRESS_LIST;
  end;
  {$EXTERNALSYM _ADDRESS_LIST_DESCRIPTOR}
  ADDRESS_LIST_DESCRIPTOR = _ADDRESS_LIST_DESCRIPTOR;
  {$EXTERNALSYM ADDRESS_LIST_DESCRIPTOR}
  TAddressListDescriptor = ADDRESS_LIST_DESCRIPTOR;
  PAddressListDescriptor = PADDRESS_LIST_DESCRIPTOR;

//
// An interface ID that is returned by the enumerator
//

  PTC_IFC_DESCRIPTOR = ^TC_IFC_DESCRIPTOR;
  {$EXTERNALSYM PTC_IFC_DESCRIPTOR}
  _TC_IFC_DESCRIPTOR = record
    Length: ULONG;
    pInterfaceName: LPWSTR;
    pInterfaceID: LPWSTR;
    AddressListDesc: ADDRESS_LIST_DESCRIPTOR;
  end;
  {$EXTERNALSYM _TC_IFC_DESCRIPTOR}
  TC_IFC_DESCRIPTOR = _TC_IFC_DESCRIPTOR;
  {$EXTERNALSYM TC_IFC_DESCRIPTOR}
  TTcIfcDescriptor = TC_IFC_DESCRIPTOR;
  PTcIfcDescriptor = PTC_IFC_DESCRIPTOR;

//
// This structure is returned by a QoS data provider in reply to
// GUID_QOS_SUPPORTED query or with an interface UP notification
//

  PTC_SUPPORTED_INFO_BUFFER = ^TC_SUPPORTED_INFO_BUFFER;
  {$EXTERNALSYM PTC_SUPPORTED_INFO_BUFFER}
  _TC_SUPPORTED_INFO_BUFFER = record
    InstanceIDLength: USHORT;
    // device or interface ID
    InstanceID: array [0..MAX_STRING_LENGTH - 1] of WCHAR;
    // address list
    AddrListDesc: ADDRESS_LIST_DESCRIPTOR;
  end;
  {$EXTERNALSYM _TC_SUPPORTED_INFO_BUFFER}
  TC_SUPPORTED_INFO_BUFFER = _TC_SUPPORTED_INFO_BUFFER;
  {$EXTERNALSYM TC_SUPPORTED_INFO_BUFFER}
  TTcSupportedInfoBuffer = TC_SUPPORTED_INFO_BUFFER;
  PTcSupportedInfoBuffer = PTC_SUPPORTED_INFO_BUFFER;

//
// Filters are used to match packets. The Pattern field
// indicates the values to which bits in corresponding
// positions in candidate packets should be compared. The
// Mask field indicates which bits are to be compared and
// which bits are don't cares.
//
// Different filters can be submitted on the TCI interface.
// The generic filter structure is defined to include an
// AddressType, which indicates the specific type of filter to
// follow.
//

  PTC_GEN_FILTER = ^TC_GEN_FILTER;
  {$EXTERNALSYM PTC_GEN_FILTER}
  _TC_GEN_FILTER = record
    AddressType: USHORT; // IP, IPX, etc.
    PatternSize: ULONG; // byte count of the pattern
    Pattern: PVOID; // specific format, e.g. IP_PATTERN
    Mask: PVOID; // same type as Pattern
  end;
  {$EXTERNALSYM _TC_GEN_FILTER}
  TC_GEN_FILTER = _TC_GEN_FILTER;
  {$EXTERNALSYM TC_GEN_FILTER}
  TTcGenFilter = TC_GEN_FILTER;
  PTcGenFilter = PTC_GEN_FILTER;

//
// A generic flow includes two flowspecs and a freeform
// buffer which contains flow specific TC objects.
//

  PTC_GEN_FLOW = ^TC_GEN_FLOW;
  {$EXTERNALSYM PTC_GEN_FLOW}
  _TC_GEN_FLOW = record
    SendingFlowspec: FLOWSPEC;
    ReceivingFlowspec: FLOWSPEC;
    TcObjectsLength: ULONG; // number of optional bytes
    TcObjects: array [0..0] of QOS_OBJECT_HDR;
  end;
  {$EXTERNALSYM _TC_GEN_FLOW}
  TC_GEN_FLOW = _TC_GEN_FLOW;
  {$EXTERNALSYM TC_GEN_FLOW}
  TTcGenFlow = TC_GEN_FLOW;
  PTcGenFlow = PTC_GEN_FLOW;

//
// Format of specific pattern or mask used by GPC for the IP protocol
//

  PIP_PATTERN = ^IP_PATTERN;
  {$EXTERNALSYM PIP_PATTERN}
  _IP_PATTERN = record
    Reserved1: ULONG;
    Reserved2: ULONG;
    SrcAddr: ULONG;
    DstAddr: ULONG;
    S_un: record
    case Integer of
      0: (
        s_srcport: USHORT;
        s_dstport: USHORT);
      1: (
        s_type: UCHAR;
        s_code: UCHAR;
        filler: USHORT);
      2: (
        S_Spi: ULONG);
    end;
    ProtocolId: UCHAR;
    Reserved3: array [0..3 - 1] of UCHAR;
  end;
  {$EXTERNALSYM _IP_PATTERN}
  IP_PATTERN = _IP_PATTERN;
  {$EXTERNALSYM IP_PATTERN}
  TIpPattern = IP_PATTERN;
  PIpPattern = PIP_PATTERN;

//
// Format of specific pattern or mask used by GPC for the IPX protocol
//

  TIpxPatternAddress = record
    NetworkAddress: ULONG;
    NodeAddress: array [0..5] of UCHAR;
    Socket: USHORT;
  end;

  PIPX_PATTERN = ^IPX_PATTERN;
  {$EXTERNALSYM PIPX_PATTERN}
  _IPX_PATTERN = record
    Src: TIpxPatternAddress;
    Dest: TIpxPatternAddress;
  end;
  {$EXTERNALSYM _IPX_PATTERN}
  IPX_PATTERN = _IPX_PATTERN;
  {$EXTERNALSYM IPX_PATTERN}
  TIpxPattern = IPX_PATTERN;
  PIpxPattern = PIPX_PATTERN;

//
// The enumeration buffer is the flow parameters + a list of filters
//

  PENUMERATION_BUFFER = ^ENUMERATION_BUFFER;
  {$EXTERNALSYM PENUMERATION_BUFFER}
  _ENUMERATION_BUFFER = record
    Length: ULONG;
    OwnerProcessId: ULONG;
    FlowNameLength: USHORT;
    FlowName: array [0..MAX_STRING_LENGTH - 1] of WCHAR;
    pFlow: PTC_GEN_FLOW;
    NumberOfFilters: ULONG;
    GenericFilter: array [0..0] of TC_GEN_FILTER; // one for each filter
  end;
  {$EXTERNALSYM _ENUMERATION_BUFFER}
  ENUMERATION_BUFFER = _ENUMERATION_BUFFER;
  {$EXTERNALSYM ENUMERATION_BUFFER}
  TEnumerationBuffer = ENUMERATION_BUFFER;
  PEnumerationBuffer = PENUMERATION_BUFFER;

//
// QoS objects supported by traffic
//

const
  QOS_TRAFFIC_GENERAL_ID_BASE = 4000;
  {$EXTERNALSYM QOS_TRAFFIC_GENERAL_ID_BASE}

  QOS_OBJECT_DS_CLASS      = ($00000001 + QOS_TRAFFIC_GENERAL_ID_BASE);
  {$EXTERNALSYM QOS_OBJECT_DS_CLASS}
  QOS_OBJECT_TRAFFIC_CLASS = ($00000002 + QOS_TRAFFIC_GENERAL_ID_BASE);
  {$EXTERNALSYM QOS_OBJECT_TRAFFIC_CLASS}
  QOS_OBJECT_DIFFSERV      = ($00000003 + QOS_TRAFFIC_GENERAL_ID_BASE);
  {$EXTERNALSYM QOS_OBJECT_DIFFSERV}
  QOS_OBJECT_TCP_TRAFFIC   = ($00000004 + QOS_TRAFFIC_GENERAL_ID_BASE);
  {$EXTERNALSYM QOS_OBJECT_TCP_TRAFFIC}
  QOS_OBJECT_FRIENDLY_NAME = ($00000005 + QOS_TRAFFIC_GENERAL_ID_BASE);
  {$EXTERNALSYM QOS_OBJECT_FRIENDLY_NAME}

//
// This structure is used to associate a friendly name with the flow
// 

type
  LPQOS_FRIENDLY_NAME = ^QOS_FRIENDLY_NAME;
  {$EXTERNALSYM LPQOS_FRIENDLY_NAME}
  _QOS_FRIENDLY_NAME = record
    ObjectHdr: QOS_OBJECT_HDR;
    FriendlyName: array [0..MAX_STRING_LENGTH - 1] of WCHAR;
  end;
  {$EXTERNALSYM _QOS_FRIENDLY_NAME}
  QOS_FRIENDLY_NAME = _QOS_FRIENDLY_NAME;
  {$EXTERNALSYM QOS_FRIENDLY_NAME}
  TQosFriendlyName = QOS_FRIENDLY_NAME;
  PQosFriendlyName = LPQOS_FRIENDLY_NAME;

//
// This structure may carry an 802.1 TrafficClass parameter which 
// has been provided to the host by a layer 2 network, for example, 
// in an 802.1 extended RSVP RESV message. If this object is obtained
// from the network, hosts will stamp the MAC headers of corresponding
// transmitted packets, with the value in the object. Otherwise, hosts
// may select a value based on the standard Intserv mapping of 
// ServiceType to 802.1 TrafficClass.
//
//

  LPQOS_TRAFFIC_CLASS = ^QOS_TRAFFIC_CLASS;
  {$EXTERNALSYM LPQOS_TRAFFIC_CLASS}
  _QOS_TRAFFIC_CLASS = record
    ObjectHdr: QOS_OBJECT_HDR;
    TrafficClass: ULONG;
  end;
  {$EXTERNALSYM _QOS_TRAFFIC_CLASS}
  QOS_TRAFFIC_CLASS = _QOS_TRAFFIC_CLASS;
  {$EXTERNALSYM QOS_TRAFFIC_CLASS}
  TQosTrafficClass = QOS_TRAFFIC_CLASS;
  PQosTrafficClass = LPQOS_TRAFFIC_CLASS;

//
// This structure may carry an DSField parameter which  has been provided to 
// the host by a layer 3 network, for example, in an extended RSVP RESV message. 
// If this object is obtained from the network, hosts will stamp the DS Field on the
// IP header of transmitted packets, with the value in the object. Otherwise, hosts
// may select a value based on the standard Intserv mapping of ServiceType to DS Field 
//

  LPQOS_DS_CLASS = ^QOS_DS_CLASS;
  {$EXTERNALSYM LPQOS_DS_CLASS}
  _QOS_DS_CLASS = record
    ObjectHdr: QOS_OBJECT_HDR;
    DSField: ULONG;
  end;
  {$EXTERNALSYM _QOS_DS_CLASS}
  QOS_DS_CLASS = _QOS_DS_CLASS;
  {$EXTERNALSYM QOS_DS_CLASS}
  TQosDsClass = QOS_DS_CLASS;
  PQosDsClass = LPQOS_DS_CLASS;


//
// This structure is used to create DiffServ Flows. This creates flows in the packet scheduler
// and allows it to classify to packets based on a particular DS field. This structure takes
// a variable length array of QOS_DIFFSERV_RULE, where each DS field is specified by a 
// QOS_DIFFSERV_RULE
//
  LPQOS_DIFFSERV = ^QOS_DIFFSERV;
  {$EXTERNALSYM LPQOS_DIFFSERV}
  _QOS_DIFFSERV = record
    ObjectHdr: QOS_OBJECT_HDR;
    DSFieldCount: ULONG;
    DiffservRule: array [0..0] of UCHAR;
  end;
  {$EXTERNALSYM _QOS_DIFFSERV}
  QOS_DIFFSERV = _QOS_DIFFSERV;
  {$EXTERNALSYM QOS_DIFFSERV}
  TQosDiffserv = QOS_DIFFSERV;
  PQosDiffserv = LPQOS_DIFFSERV;

//
// The rule for a Diffserv DS codepoint. 
//

  LPQOS_DIFFSERV_RULE = ^QOS_DIFFSERV_RULE;
  {$EXTERNALSYM LPQOS_DIFFSERV_RULE}
  _QOS_DIFFSERV_RULE = record
    InboundDSField: UCHAR;
    ConformingOutboundDSField: UCHAR;
    NonConformingOutboundDSField: UCHAR;
    ConformingUserPriority: UCHAR;
    NonConformingUserPriority: UCHAR;
  end;
  {$EXTERNALSYM _QOS_DIFFSERV_RULE}
  QOS_DIFFSERV_RULE = _QOS_DIFFSERV_RULE;
  {$EXTERNALSYM QOS_DIFFSERV_RULE}
  TQosDiffservRule = QOS_DIFFSERV_RULE;
  PQosDiffservRule = LPQOS_DIFFSERV_RULE;

// 
// This structure is passed to indicate that the IP Precedence and UserPriority mappings for the flow
// have to be set to the system defaults for TCP traffic. If this object is passed, 
// the ServiceType ==> DSField mapping, ServiceType ==> UserPriorityMapping, QOS_OBJECT_DS_CLASS
// and QOS_OBJECT_TRAFFIC_CLASS will be ignored.
//

  LPQOS_TCP_TRAFFIC = ^QOS_TCP_TRAFFIC;
  {$EXTERNALSYM LPQOS_TCP_TRAFFIC}
  _QOS_TCP_TRAFFIC = record
    ObjectHdr: QOS_OBJECT_HDR;
  end;
  {$EXTERNALSYM _QOS_TCP_TRAFFIC}
  QOS_TCP_TRAFFIC = _QOS_TCP_TRAFFIC;
  {$EXTERNALSYM QOS_TCP_TRAFFIC}
  TQosTcpTraffic = QOS_TCP_TRAFFIC;
  PQosTcpTraffic = LPQOS_TCP_TRAFFIC;

//---------------------------------------------------------------------------
//
// Interface Function Definitions
//

function TcRegisterClient(TciVersion: ULONG; ClRegCtx: HANDLE; const ClientHandlerList: TCI_CLIENT_FUNC_LIST; var pClientHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcRegisterClient}
function TcEnumerateInterfaces(ClientHandle: HANDLE; var pBufferSize: ULONG; var InterfaceBuffer: TC_IFC_DESCRIPTOR): ULONG; stdcall;
{$EXTERNALSYM TcEnumerateInterfaces}
function TcOpenInterfaceA(pInterfaceName: LPSTR; ClientHandle, ClIfcCtx: HANDLE; var pIfcHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcOpenInterfaceA}
function TcOpenInterfaceW(pInterfaceName: LPWSTR; ClientHandle, ClIfcCtx: HANDLE; var pIfcHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcOpenInterfaceW}
function TcCloseInterface(IfcHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcCloseInterface}
function TcQueryInterface(IfcHandle: HANDLE; const pGuidParam: GUID; NotifyChange: Longbool; var pBufferSize: ULONG; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcQueryInterface}
function TcSetInterface(IfcHandle: HANDLE; const pGuidParam: GUID; BufferSize: ULONG; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcSetInterface}
function TcQueryFlowA(pFlowName: LPSTR; const pGuidParam: GUID; var pBufferSize: ULONG; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcQueryFlowA}
function TcQueryFlowW(pFlowName: LPWSTR; const pGuidParam: GUID; var pBufferSize: ULONG; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcQueryFlowW}
function TcSetFlowA(pFlowName: LPSTR; const pGuidParam: GUID; BufferSize: GUID; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcSetFlowA}
function TcSetFlowW(pFlowName: LPWSTR; const pGuidParam: GUID; BufferSize: GUID; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcSetFlowW}
function TcAddFlow(IfcHandle, ClFlowCtx: HANDLE; Flags: ULONG; const pGenericFlow: TC_GEN_FLOW; var pFlowHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcAddFlow}
function TcGetFlowNameA(FlowHandle: HANDLE; StrSize: ULONG; pFlowName: LPSTR): ULONG; stdcall;
{$EXTERNALSYM TcGetFlowNameA}
function TcGetFlowNameW(FlowHandle: HANDLE; StrSize: ULONG; pFlowName: LPWSTR): ULONG; stdcall;
{$EXTERNALSYM TcGetFlowNameW}
function TcModifyFlow(FlowHandle: HANDLE; const pGenericFlow: TC_GEN_FLOW): ULONG; stdcall;
{$EXTERNALSYM TcModifyFlow}
function TcAddFilter(FlowHandle: HANDLE; const pGenericFilter: TC_GEN_FILTER; var pFilterHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcAddFilter}
function TcDeregisterClient(ClientHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcDeregisterClient}
function TcDeleteFlow(FlowHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcDeleteFlow}
function TcDeleteFilter(FilterHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcDeleteFilter}
function TcEnumerateFlows(IfcHandle: HANDLE; var pEnumHandle: HANDLE; var pFlowCount, pBufSize: ULONG; var Buffer: ENUMERATION_BUFFER): ULONG; stdcall;
{$EXTERNALSYM TcEnumerateFlows}

{$IFDEF UNICODE}

function TcOpenInterface(pInterfaceName: LPWSTR; ClientHandle, ClIfcCtx: HANDLE; var pIfcHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcOpenInterface}
function TcQueryFlow(pFlowName: LPWSTR; const pGuidParam: GUID; var pBufferSize: ULONG; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcQueryFlow}
function TcSetFlow(pFlowName: LPWSTR; const pGuidParam: GUID; BufferSize: GUID; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcSetFlow}
function TcGetFlowName(FlowHandle: HANDLE; StrSize: ULONG; pFlowName: LPWSTR): ULONG; stdcall;
{$EXTERNALSYM TcGetFlowName}

{$ELSE}

function TcOpenInterface(pInterfaceName: LPSTR; ClientHandle, ClIfcCtx: HANDLE; var pIfcHandle: HANDLE): ULONG; stdcall;
{$EXTERNALSYM TcOpenInterface}
function TcQueryFlow(pFlowName: LPSTR; const pGuidParam: GUID; var pBufferSize: ULONG; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcQueryFlow}
function TcSetFlow(pFlowName: LPSTR; const pGuidParam: GUID; BufferSize: GUID; Buffer: PVOID): ULONG; stdcall;
{$EXTERNALSYM TcSetFlow}
function TcGetFlowName(FlowHandle: HANDLE; StrSize: ULONG; pFlowName: LPSTR): ULONG; stdcall;
{$EXTERNALSYM TcGetFlowName}

{$ENDIF}

implementation

const
  traffic_lib = 'traffic.dll';


{$IFDEF DYNAMIC_LINK}
var
  _TcRegisterClient: Pointer;

function TcRegisterClient;
begin
  GetProcedureAddress(_TcRegisterClient, traffic_lib, 'TcRegisterClient');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcRegisterClient]
  end;
end;
{$ELSE}
function TcRegisterClient; external traffic_lib name 'TcRegisterClient';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcEnumerateInterfaces: Pointer;

function TcEnumerateInterfaces;
begin
  GetProcedureAddress(_TcEnumerateInterfaces, traffic_lib, 'TcEnumerateInterfaces');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcEnumerateInterfaces]
  end;
end;
{$ELSE}
function TcEnumerateInterfaces; external traffic_lib name 'TcEnumerateInterfaces';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcOpenInterfaceA: Pointer;

function TcOpenInterfaceA;
begin
  GetProcedureAddress(_TcOpenInterfaceA, traffic_lib, 'TcOpenInterfaceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcOpenInterfaceA]
  end;
end;
{$ELSE}
function TcOpenInterfaceA; external traffic_lib name 'TcOpenInterfaceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcOpenInterfaceW: Pointer;

function TcOpenInterfaceW;
begin
  GetProcedureAddress(_TcOpenInterfaceW, traffic_lib, 'TcOpenInterfaceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcOpenInterfaceW]
  end;
end;
{$ELSE}
function TcOpenInterfaceW; external traffic_lib name 'TcOpenInterfaceW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcCloseInterface: Pointer;

function TcCloseInterface;
begin
  GetProcedureAddress(_TcCloseInterface, traffic_lib, 'TcCloseInterface');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcCloseInterface]
  end;
end;
{$ELSE}
function TcCloseInterface; external traffic_lib name 'TcCloseInterface';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcQueryInterface: Pointer;

function TcQueryInterface;
begin
  GetProcedureAddress(_TcQueryInterface, traffic_lib, 'TcQueryInterface');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcQueryInterface]
  end;
end;
{$ELSE}
function TcQueryInterface; external traffic_lib name 'TcQueryInterface';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcSetInterface: Pointer;

function TcSetInterface;
begin
  GetProcedureAddress(_TcSetInterface, traffic_lib, 'TcSetInterface');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcSetInterface]
  end;
end;
{$ELSE}
function TcSetInterface; external traffic_lib name 'TcSetInterface';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcQueryFlowA: Pointer;

function TcQueryFlowA;
begin
  GetProcedureAddress(_TcQueryFlowA, traffic_lib, 'TcQueryFlowA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcQueryFlowA]
  end;
end;
{$ELSE}
function TcQueryFlowA; external traffic_lib name 'TcQueryFlowA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcQueryFlowW: Pointer;

function TcQueryFlowW;
begin
  GetProcedureAddress(_TcQueryFlowW, traffic_lib, 'TcQueryFlowW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcQueryFlowW]
  end;
end;
{$ELSE}
function TcQueryFlowW; external traffic_lib name 'TcQueryFlowW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcSetFlowA: Pointer;

function TcSetFlowA;
begin
  GetProcedureAddress(_TcSetFlowA, traffic_lib, 'TcSetFlowA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcSetFlowA]
  end;
end;
{$ELSE}
function TcSetFlowA; external traffic_lib name 'TcSetFlowA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcSetFlowW: Pointer;

function TcSetFlowW;
begin
  GetProcedureAddress(_TcSetFlowW, traffic_lib, 'TcSetFlowW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcSetFlowW]
  end;
end;
{$ELSE}
function TcSetFlowW; external traffic_lib name 'TcSetFlowW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcAddFlow: Pointer;

function TcAddFlow;
begin
  GetProcedureAddress(_TcAddFlow, traffic_lib, 'TcAddFlow');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcAddFlow]
  end;
end;
{$ELSE}
function TcAddFlow; external traffic_lib name 'TcAddFlow';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcGetFlowNameA: Pointer;

function TcGetFlowNameA;
begin
  GetProcedureAddress(_TcGetFlowNameA, traffic_lib, 'TcGetFlowNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcGetFlowNameA]
  end;
end;
{$ELSE}
function TcGetFlowNameA; external traffic_lib name 'TcGetFlowNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcGetFlowNameW: Pointer;

function TcGetFlowNameW;
begin
  GetProcedureAddress(_TcGetFlowNameW, traffic_lib, 'TcGetFlowNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcGetFlowNameW]
  end;
end;
{$ELSE}
function TcGetFlowNameW; external traffic_lib name 'TcGetFlowNameW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcModifyFlow: Pointer;

function TcModifyFlow;
begin
  GetProcedureAddress(_TcModifyFlow, traffic_lib, 'TcModifyFlow');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcModifyFlow]
  end;
end;
{$ELSE}
function TcModifyFlow; external traffic_lib name 'TcModifyFlow';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcAddFilter: Pointer;

function TcAddFilter;
begin
  GetProcedureAddress(_TcAddFilter, traffic_lib, 'TcAddFilter');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcAddFilter]
  end;
end;
{$ELSE}
function TcAddFilter; external traffic_lib name 'TcAddFilter';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcDeregisterClient: Pointer;

function TcDeregisterClient;
begin
  GetProcedureAddress(_TcDeregisterClient, traffic_lib, 'TcDeregisterClient');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcDeregisterClient]
  end;
end;
{$ELSE}
function TcDeregisterClient; external traffic_lib name 'TcDeregisterClient';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcDeleteFlow: Pointer;

function TcDeleteFlow;
begin
  GetProcedureAddress(_TcDeleteFlow, traffic_lib, 'TcDeleteFlow');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcDeleteFlow]
  end;
end;
{$ELSE}
function TcDeleteFlow; external traffic_lib name 'TcDeleteFlow';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcDeleteFilter: Pointer;

function TcDeleteFilter;
begin
  GetProcedureAddress(_TcDeleteFilter, traffic_lib, 'TcDeleteFilter');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcDeleteFilter]
  end;
end;
{$ELSE}
function TcDeleteFilter; external traffic_lib name 'TcDeleteFilter';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcEnumerateFlows: Pointer;

function TcEnumerateFlows;
begin
  GetProcedureAddress(_TcEnumerateFlows, traffic_lib, 'TcEnumerateFlows');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcEnumerateFlows]
  end;
end;
{$ELSE}
function TcEnumerateFlows; external traffic_lib name 'TcEnumerateFlows';
{$ENDIF DYNAMIC_LINK}

{$IFDEF UNICODE}


{$IFDEF DYNAMIC_LINK}
var
  _TcOpenInterface: Pointer;

function TcOpenInterface;
begin
  GetProcedureAddress(_TcOpenInterface, traffic_lib, 'TcOpenInterfaceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcOpenInterface]
  end;
end;
{$ELSE}
function TcOpenInterface; external traffic_lib name 'TcOpenInterfaceW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcQueryFlow: Pointer;

function TcQueryFlow;
begin
  GetProcedureAddress(_TcQueryFlow, traffic_lib, 'TcQueryFlowW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcQueryFlow]
  end;
end;
{$ELSE}
function TcQueryFlow; external traffic_lib name 'TcQueryFlowW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcSetFlow: Pointer;

function TcSetFlow;
begin
  GetProcedureAddress(_TcSetFlow, traffic_lib, 'TcSetFlowW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcSetFlow]
  end;
end;
{$ELSE}
function TcSetFlow; external traffic_lib name 'TcSetFlowW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcGetFlowName: Pointer;

function TcGetFlowName;
begin
  GetProcedureAddress(_TcGetFlowName, traffic_lib, 'TcGetFlowNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcGetFlowName]
  end;
end;
{$ELSE}
function TcGetFlowName; external traffic_lib name 'TcGetFlowNameW';
{$ENDIF DYNAMIC_LINK}

{$ELSE}


{$IFDEF DYNAMIC_LINK}
var
  _TcOpenInterface: Pointer;

function TcOpenInterface;
begin
  GetProcedureAddress(_TcOpenInterface, traffic_lib, 'TcOpenInterfaceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcOpenInterface]
  end;
end;
{$ELSE}
function TcOpenInterface; external traffic_lib name 'TcOpenInterfaceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcQueryFlow: Pointer;

function TcQueryFlow;
begin
  GetProcedureAddress(_TcQueryFlow, traffic_lib, 'TcQueryFlowA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcQueryFlow]
  end;
end;
{$ELSE}
function TcQueryFlow; external traffic_lib name 'TcQueryFlowA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcSetFlow: Pointer;

function TcSetFlow;
begin
  GetProcedureAddress(_TcSetFlow, traffic_lib, 'TcSetFlowA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcSetFlow]
  end;
end;
{$ELSE}
function TcSetFlow; external traffic_lib name 'TcSetFlowA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _TcGetFlowName: Pointer;

function TcGetFlowName;
begin
  GetProcedureAddress(_TcGetFlowName, traffic_lib, 'TcGetFlowNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_TcGetFlowName]
  end;
end;
{$ELSE}
function TcGetFlowName; external traffic_lib name 'TcGetFlowNameA';
{$ENDIF DYNAMIC_LINK}

{$ENDIF}

end.
