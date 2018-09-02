{******************************************************************************}
{                                                       	               }
{ RPC NSI API interface Unit for Object Pascal                                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: rpcnsi.h, released June 2000. The original Pascal      }
{ code is: RpcNsi.pas, released December 2000. The initial developer of the    }
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

unit JwaRpcNsi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "RpcNsi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaRpc, JwaRpcDce, JwaWinType{todo only here for GetProcedureAddress};

type
  RPC_NS_HANDLE = Pointer;
  {$EXTERNALSYM RPC_NS_HANDLE}

const
  RPC_C_NS_SYNTAX_DEFAULT = 0;
  {$EXTERNALSYM RPC_C_NS_SYNTAX_DEFAULT}
  RPC_C_NS_SYNTAX_DCE = 3;
  {$EXTERNALSYM RPC_C_NS_SYNTAX_DCE}

  RPC_C_PROFILE_DEFAULT_ELT = 0;
  {$EXTERNALSYM RPC_C_PROFILE_DEFAULT_ELT}
  RPC_C_PROFILE_ALL_ELT = 1;
  {$EXTERNALSYM RPC_C_PROFILE_ALL_ELT}
  RPC_C_PROFILE_ALL_ELTS = RPC_C_PROFILE_ALL_ELT;
  {$EXTERNALSYM RPC_C_PROFILE_ALL_ELTS}
  RPC_C_PROFILE_MATCH_BY_IF = 2;
  {$EXTERNALSYM RPC_C_PROFILE_MATCH_BY_IF}
  RPC_C_PROFILE_MATCH_BY_MBR = 3;
  {$EXTERNALSYM RPC_C_PROFILE_MATCH_BY_MBR}
  RPC_C_PROFILE_MATCH_BY_BOTH = 4;
  {$EXTERNALSYM RPC_C_PROFILE_MATCH_BY_BOTH}

  RPC_C_NS_DEFAULT_EXP_AGE = -1;
  {$EXTERNALSYM RPC_C_NS_DEFAULT_EXP_AGE}

// Server APIs

function RpcNsBindingExportA(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; BindingVec: PRPC_BINDING_VECTOR;
  ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExportA}
function RpcNsBindingExportW(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; BindingVec: PRPC_BINDING_VECTOR;
  ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExportW}

{$IFDEF UNICODE}
function RpcNsBindingExport(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; BindingVec: PRPC_BINDING_VECTOR;
  ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExport}
{$ELSE}
function RpcNsBindingExport(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; BindingVec: PRPC_BINDING_VECTOR;
  ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExport}
{$ENDIF}

function RpcNsBindingUnexportA(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexportA}
function RpcNsBindingUnexportW(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexportW}

{$IFDEF UNICODE}
function RpcNsBindingUnexport(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexport}
{$ELSE}
function RpcNsBindingUnexport(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexport}
{$ENDIF}

// Server PnP APIs

function RpcNsBindingExportPnPA(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExportPnPA}
function RpcNsBindingExportPnPW(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExportPnPW}

{$IFDEF UNICODE}
function RpcNsBindingExportPnP(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExportPnP}
{$ELSE}
function RpcNsBindingExportPnP(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingExportPnP}
{$ENDIF}

function RpcNsBindingUnexportPnPA(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexportPnPA}
function RpcNsBindingUnexportPnPW(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexportPnPW}

{$IFDEF UNICODE}
function RpcNsBindingUnexportPnP(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexportPnP}
{$ELSE}
function RpcNsBindingUnexportPnP(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjectVector: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingUnexportPnP}
{$ENDIF}

// Client APIs

function RpcNsBindingLookupBeginA(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; BindingMaxCount: Longword;
  var LookupContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingLookupBeginA}
function RpcNsBindingLookupBeginW(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; BindingMaxCount: Longword;
  var LookupContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingLookupBeginW}

{$IFDEF UNICODE}
function RpcNsBindingLookupBegin(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; BindingMaxCount: Longword;
  var LookupContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingLookupBegin}
{$ELSE}
function RpcNsBindingLookupBegin(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; BindingMaxCount: Longword;
  var LookupContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingLookupBegin}
{$ENDIF}

function RpcNsBindingLookupNext(LookupContext: RPC_NS_HANDLE;
  var BindingVec: PRPC_BINDING_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingLookupNext}

function RpcNsBindingLookupDone(var LookupContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingLookupDone}

// Group APIs

function RpcNsGroupDeleteA(GroupNameSyntax: Longword; GroupName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupDeleteA}
function RpcNsGroupDeleteW(GroupNameSyntax: Longword; GroupName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupDeleteW}

{$IFDEF UNICODE}
function RpcNsGroupDelete(GroupNameSyntax: Longword; GroupName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupDelete}
{$ELSE}
function RpcNsGroupDelete(GroupNameSyntax: Longword; GroupName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupDelete}
{$ENDIF}

function RpcNsGroupMbrAddA(GroupNameSyntax: Longword; GroupName: PChar;
  MemberNameSyntax: Longword; MemberName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrAddA}
function RpcNsGroupMbrAddW(GroupNameSyntax: Longword; GroupName: PWideChar;
  MemberNameSyntax: Longword; MemberName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrAddW}

{$IFDEF UNICODE}
function RpcNsGroupMbrAdd(GroupNameSyntax: Longword; GroupName: PWideChar;
  MemberNameSyntax: Longword; MemberName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrAdd}
{$ELSE}
function RpcNsGroupMbrAdd(GroupNameSyntax: Longword; GroupName: PChar;
  MemberNameSyntax: Longword; MemberName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrAdd}
{$ENDIF}

function RpcNsGroupMbrRemoveA(GroupNameSyntax: Longword; GroupName: PChar;
  MemberNameSyntax: Longword; MemberName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrRemoveA}
function RpcNsGroupMbrRemoveW(GroupNameSyntax: Longword; GroupName: PWideChar;
  MemberNameSyntax: Longword; MemberName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrRemoveW}

{$IFDEF UNICODE}
function RpcNsGroupMbrRemove(GroupNameSyntax: Longword; GroupName: PWideChar;
  MemberNameSyntax: Longword; MemberName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrRemove}
{$ELSE}
function RpcNsGroupMbrRemove(GroupNameSyntax: Longword; GroupName: PChar;
  MemberNameSyntax: Longword; MemberName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrRemove}
{$ENDIF}

function RpcNsGroupMbrInqBeginA(GroupNameSyntax: Longword; GroupName: PChar;
  MemberNameSyntax: Longword; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqBeginA}
function RpcNsGroupMbrInqBeginW(GroupNameSyntax: Longword; GroupName: PWideChar;
  MemberNameSyntax: Longword; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqBeginW}

{$IFDEF UNICODE}
function RpcNsGroupMbrInqBegin(GroupNameSyntax: Longword; GroupName: PWideChar;
  MemberNameSyntax: Longword; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqBegin}
{$ELSE}
function RpcNsGroupMbrInqBegin(GroupNameSyntax: Longword; GroupName: PChar;
  MemberNameSyntax: Longword; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqBegin}
{$ENDIF}

function RpcNsGroupMbrInqNextA(InquiryContext: RPC_NS_HANDLE; MemberName: PPChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqNextA}
function RpcNsGroupMbrInqNextW(InquiryContext: RPC_NS_HANDLE; MemberName: PPWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqNextW}

{$IFDEF UNICODE}
function RpcNsGroupMbrInqNext(InquiryContext: RPC_NS_HANDLE; MemberName: PPWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqNext}
{$ELSE}
function RpcNsGroupMbrInqNext(InquiryContext: RPC_NS_HANDLE; MemberName: PPChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqNext}
{$ENDIF}

function RpcNsGroupMbrInqDone(var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsGroupMbrInqDone}

// Profile APIs

function RpcNsProfileDeleteA(ProfileNameSyntax: Longword; ProfileName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileDeleteA}
function RpcNsProfileDeleteW(ProfileNameSyntax: Longword; ProfileName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileDeleteW}

{$IFDEF UNICODE}
function RpcNsProfileDelete(ProfileNameSyntax: Longword; ProfileName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileDelete}
{$ELSE}
function RpcNsProfileDelete(ProfileNameSyntax: Longword; ProfileName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileDelete}
{$ENDIF}

function RpcNsProfileEltAddA(ProfileNameSyntax: Longword; ProfileName: PChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PChar;
  Priority: Longword; Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltAddA}
function RpcNsProfileEltAddW(ProfileNameSyntax: Longword; ProfileName: PWideChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PWideChar;
  Priority: Longword; Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltAddW}

{$IFDEF UNICODE}
function RpcNsProfileEltAdd(ProfileNameSyntax: Longword; ProfileName: PWideChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PWideChar;
  Priority: Longword; Annotation: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltAdd}
{$ELSE}
function RpcNsProfileEltAdd(ProfileNameSyntax: Longword; ProfileName: PChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PChar;
  Priority: Longword; Annotation: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltAdd}
{$ENDIF}

function RpcNsProfileEltRemoveA(ProfileNameSyntax: Longword; ProfileName: PChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltRemoveA}
function RpcNsProfileEltRemoveW(ProfileNameSyntax: Longword; ProfileName: PWideChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltRemoveW}

{$IFDEF UNICODE}
function RpcNsProfileEltRemove(ProfileNameSyntax: Longword; ProfileName: PWideChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltRemove}
{$ELSE}
function RpcNsProfileEltRemove(ProfileNameSyntax: Longword; ProfileName: PChar;
  IfId: PRPC_IF_ID; MemberNameSyntax: Longword; MemberName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltRemove}
{$ENDIF}

function RpcNsProfileEltInqBeginA(ProfileNameSyntax: Longword; ProfileName: PChar;
  InquiryType: Longword; IfId: PRPC_IF_ID; VersOption, MemberNameSyntax: Longword;
  MemberName: PChar; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqBeginA}
function RpcNsProfileEltInqBeginW(ProfileNameSyntax: Longword; ProfileName: PWideChar;
  InquiryType: Longword; IfId: PRPC_IF_ID; VersOption, MemberNameSyntax: Longword;
  MemberName: PWideChar; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqBeginW}

{$IFDEF UNICODE}
function RpcNsProfileEltInqBegin(ProfileNameSyntax: Longword; ProfileName: PWideChar;
  InquiryType: Longword; IfId: PRPC_IF_ID; VersOption, MemberNameSyntax: Longword;
  MemberName: PWideChar; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqBegin}
{$ELSE}
function RpcNsProfileEltInqBegin(ProfileNameSyntax: Longword; ProfileName: PChar;
  InquiryType: Longword; IfId: PRPC_IF_ID; VersOption, MemberNameSyntax: Longword;
  MemberName: PChar; var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqBegin}
{$ENDIF}

function RpcNsProfileEltInqNextA(InquiryContext: RPC_NS_HANDLE; var IfId: RPC_IF_ID;
  MemberName: PPChar; var Priority: Longword; Annotation: PPChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqNextA}
function RpcNsProfileEltInqNextW(InquiryContext: RPC_NS_HANDLE; var IfId: RPC_IF_ID;
  MemberName: PPWideChar; var Priority: Longword; Annotation: PPWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqNextW}

{$IFDEF UNICODE}
function RpcNsProfileEltInqNext(InquiryContext: RPC_NS_HANDLE; var IfId: RPC_IF_ID;
  MemberName: PPWideChar; var Priority: Longword; Annotation: PPWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqNext}
{$ELSE}
function RpcNsProfileEltInqNext(InquiryContext: RPC_NS_HANDLE; var IfId: RPC_IF_ID;
  MemberName: PPChar; var Priority: Longword; Annotation: PPChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqNext}
{$ENDIF}

function RpcNsProfileEltInqDone(var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsProfileEltInqDone}

// Entry object APIs

function RpcNsEntryObjectInqBeginA(EntryNameSyntax: Longword; EntryName: PChar;
  var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryObjectInqBeginA}
function RpcNsEntryObjectInqBeginW(EntryNameSyntax: Longword; EntryName: PWideChar;
  var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryObjectInqBeginW}

{$IFDEF UNICODE}
function RpcNsEntryObjectInqBegin(EntryNameSyntax: Longword; EntryName: PWideChar;
  var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryObjectInqBegin}
{$ELSE}
function RpcNsEntryObjectInqBegin(EntryNameSyntax: Longword; EntryName: PChar;
  var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryObjectInqBegin}
{$ENDIF}

function RpcNsEntryObjectInqNext(InquiryContext: RPC_NS_HANDLE; ObjUuid: PUUID): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryObjectInqNext}

function RpcNsEntryObjectInqDone(var InquiryContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryObjectInqDone}

// Management and MISC APIs

function RpcNsEntryExpandNameA(EntryNameSyntax: Longword; EntryName: PChar;
  var ExpandedName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryExpandNameA}
function RpcNsEntryExpandNameW(EntryNameSyntax: Longword; EntryName: PWideChar;
  var ExpandedName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryExpandNameW}

{$IFDEF UNICODE}
function RpcNsEntryExpandName(EntryNameSyntax: Longword; EntryName: PWideChar;
  var ExpandedName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryExpandName}
{$ELSE}
function RpcNsEntryExpandName(EntryNameSyntax: Longword; EntryName: PChar;
  var ExpandedName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsEntryExpandName}
{$ENDIF}

function RpcNsMgmtBindingUnexportA(EntryNameSyntax: Longword; EntryName: PChar;
  IfId: PRPC_IF_ID; VersOption: Longword; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtBindingUnexportA}
function RpcNsMgmtBindingUnexportW(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfId: PRPC_IF_ID; VersOption: Longword; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtBindingUnexportW}

{$IFDEF UNICODE}
function RpcNsMgmtBindingUnexport(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfId: PRPC_IF_ID; VersOption: Longword; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtBindingUnexport}
{$ELSE}
function RpcNsMgmtBindingUnexport(EntryNameSyntax: Longword; EntryName: PChar;
  IfId: PRPC_IF_ID; VersOption: Longword; ObjectUuidVec: PUUID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtBindingUnexport}
{$ENDIF}

function RpcNsMgmtEntryCreateA(EntryNameSyntax: Longword; EntryName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryCreateA}
function RpcNsMgmtEntryCreateW(EntryNameSyntax: Longword; EntryName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryCreateW}

{$IFDEF UNICODE}
function RpcNsMgmtEntryCreate(EntryNameSyntax: Longword; EntryName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryCreate}
{$ELSE}
function RpcNsMgmtEntryCreate(EntryNameSyntax: Longword; EntryName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryCreate}
{$ENDIF}

function RpcNsMgmtEntryDeleteA(EntryNameSyntax: Longword; EntryName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryDeleteA}
function RpcNsMgmtEntryDeleteW(EntryNameSyntax: Longword; EntryName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryDeleteW}

{$IFDEF UNICODE}
function RpcNsMgmtEntryDelete(EntryNameSyntax: Longword; EntryName: PWideChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryDelete}
{$ELSE}
function RpcNsMgmtEntryDelete(EntryNameSyntax: Longword; EntryName: PChar): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryDelete}
{$ENDIF}

function RpcNsMgmtEntryInqIfIdsA(EntryNameSyntax: Longword; EntryName: PChar;
  var IfIdVec: PRPC_IF_ID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryInqIfIdsA}
function RpcNsMgmtEntryInqIfIdsW(EntryNameSyntax: Longword; EntryName: PWideChar;
  var IfIdVec: PRPC_IF_ID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryInqIfIdsW}

{$IFDEF UNICODE}
function RpcNsMgmtEntryInqIfIds(EntryNameSyntax: Longword; EntryName: PWideChar;
  var IfIdVec: PRPC_IF_ID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryInqIfIds}
{$ELSE}
function RpcNsMgmtEntryInqIfIds(EntryNameSyntax: Longword; EntryName: PChar;
  var IfIdVec: PRPC_IF_ID_VECTOR): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtEntryInqIfIds}
{$ENDIF}

function RpcNsMgmtHandleSetExpAge(NsHandle: RPC_NS_HANDLE;
  ExpirationAge: Longword): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtHandleSetExpAge}

function RpcNsMgmtInqExpAge(var ExpirationAge: Longword): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtInqExpAge}

function RpcNsMgmtSetExpAge(ExpirationAge: Longword): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsMgmtSetExpAge}

// Client API's implemented in wrappers.

function RpcNsBindingImportBeginA(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; var ImportContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingImportBeginA}
function RpcNsBindingImportBeginW(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; var ImportContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingImportBeginW}

{$IFDEF UNICODE}
function RpcNsBindingImportBegin(EntryNameSyntax: Longword; EntryName: PWideChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; var ImportContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingImportBegin}
{$ELSE}
function RpcNsBindingImportBegin(EntryNameSyntax: Longword; EntryName: PChar;
  IfSpec: RPC_IF_HANDLE; ObjUuid: PUUID; var ImportContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingImportBegin}
{$ENDIF}

function RpcNsBindingImportNext(ImportContext: RPC_NS_HANDLE;
  var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingImportNext}

function RpcNsBindingImportDone(var ImportContext: RPC_NS_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingImportDone}

function RpcNsBindingSelect(BindingVec: PRPC_BINDING_VECTOR; var Binding: RPC_BINDING_HANDLE): RPC_STATUS; stdcall;
{$EXTERNALSYM RpcNsBindingSelect}

implementation

const
  rpcns4 = 'rpcns4.dll';


{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExportA: Pointer;

function RpcNsBindingExportA;
begin
  GetProcedureAddress(_RpcNsBindingExportA, rpcns4, 'RpcNsBindingExportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExportA]
  end;
end;
{$ELSE}
function RpcNsBindingExportA; external rpcns4 name 'RpcNsBindingExportA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExportW: Pointer;

function RpcNsBindingExportW;
begin
  GetProcedureAddress(_RpcNsBindingExportW, rpcns4, 'RpcNsBindingExportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExportW]
  end;
end;
{$ELSE}
function RpcNsBindingExportW; external rpcns4 name 'RpcNsBindingExportW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExport: Pointer;

function RpcNsBindingExport;
begin
  GetProcedureAddress(_RpcNsBindingExport, rpcns4, 'RpcNsBindingExportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExport]
  end;
end;
{$ELSE}
function RpcNsBindingExport; external rpcns4 name 'RpcNsBindingExportW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExport: Pointer;

function RpcNsBindingExport;
begin
  GetProcedureAddress(_RpcNsBindingExport, rpcns4, 'RpcNsBindingExportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExport]
  end;
end;
{$ELSE}
function RpcNsBindingExport; external rpcns4 name 'RpcNsBindingExportA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexportA: Pointer;

function RpcNsBindingUnexportA;
begin
  GetProcedureAddress(_RpcNsBindingUnexportA, rpcns4, 'RpcNsBindingUnexportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexportA]
  end;
end;
{$ELSE}
function RpcNsBindingUnexportA; external rpcns4 name 'RpcNsBindingUnexportA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexportW: Pointer;

function RpcNsBindingUnexportW;
begin
  GetProcedureAddress(_RpcNsBindingUnexportW, rpcns4, 'RpcNsBindingUnexportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexportW]
  end;
end;
{$ELSE}
function RpcNsBindingUnexportW; external rpcns4 name 'RpcNsBindingUnexportW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexport: Pointer;

function RpcNsBindingUnexport;
begin
  GetProcedureAddress(_RpcNsBindingUnexport, rpcns4, 'RpcNsBindingUnexportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexport]
  end;
end;
{$ELSE}
function RpcNsBindingUnexport; external rpcns4 name 'RpcNsBindingUnexportW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexport: Pointer;

function RpcNsBindingUnexport;
begin
  GetProcedureAddress(_RpcNsBindingUnexport, rpcns4, 'RpcNsBindingUnexportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexport]
  end;
end;
{$ELSE}
function RpcNsBindingUnexport; external rpcns4 name 'RpcNsBindingUnexportA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExportPnPA: Pointer;

function RpcNsBindingExportPnPA;
begin
  GetProcedureAddress(_RpcNsBindingExportPnPA, rpcns4, 'RpcNsBindingExportPnPA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExportPnPA]
  end;
end;
{$ELSE}
function RpcNsBindingExportPnPA; external rpcns4 name 'RpcNsBindingExportPnPA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExportPnPW: Pointer;

function RpcNsBindingExportPnPW;
begin
  GetProcedureAddress(_RpcNsBindingExportPnPW, rpcns4, 'RpcNsBindingExportPnPW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExportPnPW]
  end;
end;
{$ELSE}
function RpcNsBindingExportPnPW; external rpcns4 name 'RpcNsBindingExportPnPW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExportPnP: Pointer;

function RpcNsBindingExportPnP;
begin
  GetProcedureAddress(_RpcNsBindingExportPnP, rpcns4, 'RpcNsBindingExportPnPW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExportPnP]
  end;
end;
{$ELSE}
function RpcNsBindingExportPnP; external rpcns4 name 'RpcNsBindingExportPnPW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingExportPnP: Pointer;

function RpcNsBindingExportPnP;
begin
  GetProcedureAddress(_RpcNsBindingExportPnP, rpcns4, 'RpcNsBindingExportPnPA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingExportPnP]
  end;
end;
{$ELSE}
function RpcNsBindingExportPnP; external rpcns4 name 'RpcNsBindingExportPnPA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexportPnPA: Pointer;

function RpcNsBindingUnexportPnPA;
begin
  GetProcedureAddress(_RpcNsBindingUnexportPnPA, rpcns4, 'RpcNsBindingUnexportPnPA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexportPnPA]
  end;
end;
{$ELSE}
function RpcNsBindingUnexportPnPA; external rpcns4 name 'RpcNsBindingUnexportPnPA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexportPnPW: Pointer;

function RpcNsBindingUnexportPnPW;
begin
  GetProcedureAddress(_RpcNsBindingUnexportPnPW, rpcns4, 'RpcNsBindingUnexportPnPW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexportPnPW]
  end;
end;
{$ELSE}
function RpcNsBindingUnexportPnPW; external rpcns4 name 'RpcNsBindingUnexportPnPW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexportPnP: Pointer;

function RpcNsBindingUnexportPnP;
begin
  GetProcedureAddress(_RpcNsBindingUnexportPnP, rpcns4, 'RpcNsBindingUnexportPnPW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexportPnP]
  end;
end;
{$ELSE}
function RpcNsBindingUnexportPnP; external rpcns4 name 'RpcNsBindingUnexportPnPW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingUnexportPnP: Pointer;

function RpcNsBindingUnexportPnP;
begin
  GetProcedureAddress(_RpcNsBindingUnexportPnP, rpcns4, 'RpcNsBindingUnexportPnPA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingUnexportPnP]
  end;
end;
{$ELSE}
function RpcNsBindingUnexportPnP; external rpcns4 name 'RpcNsBindingUnexportPnPA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingLookupBeginA: Pointer;

function RpcNsBindingLookupBeginA;
begin
  GetProcedureAddress(_RpcNsBindingLookupBeginA, rpcns4, 'RpcNsBindingLookupBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingLookupBeginA]
  end;
end;
{$ELSE}
function RpcNsBindingLookupBeginA; external rpcns4 name 'RpcNsBindingLookupBeginA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingLookupBeginW: Pointer;

function RpcNsBindingLookupBeginW;
begin
  GetProcedureAddress(_RpcNsBindingLookupBeginW, rpcns4, 'RpcNsBindingLookupBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingLookupBeginW]
  end;
end;
{$ELSE}
function RpcNsBindingLookupBeginW; external rpcns4 name 'RpcNsBindingLookupBeginW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingLookupBegin: Pointer;

function RpcNsBindingLookupBegin;
begin
  GetProcedureAddress(_RpcNsBindingLookupBegin, rpcns4, 'RpcNsBindingLookupBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingLookupBegin]
  end;
end;
{$ELSE}
function RpcNsBindingLookupBegin; external rpcns4 name 'RpcNsBindingLookupBeginW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingLookupBegin: Pointer;

function RpcNsBindingLookupBegin;
begin
  GetProcedureAddress(_RpcNsBindingLookupBegin, rpcns4, 'RpcNsBindingLookupBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingLookupBegin]
  end;
end;
{$ELSE}
function RpcNsBindingLookupBegin; external rpcns4 name 'RpcNsBindingLookupBeginA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingLookupNext: Pointer;

function RpcNsBindingLookupNext;
begin
  GetProcedureAddress(_RpcNsBindingLookupNext, rpcns4, 'RpcNsBindingLookupNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingLookupNext]
  end;
end;
{$ELSE}
function RpcNsBindingLookupNext; external rpcns4 name 'RpcNsBindingLookupNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingLookupDone: Pointer;

function RpcNsBindingLookupDone;
begin
  GetProcedureAddress(_RpcNsBindingLookupDone, rpcns4, 'RpcNsBindingLookupDone');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingLookupDone]
  end;
end;
{$ELSE}
function RpcNsBindingLookupDone; external rpcns4 name 'RpcNsBindingLookupDone';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupDeleteA: Pointer;

function RpcNsGroupDeleteA;
begin
  GetProcedureAddress(_RpcNsGroupDeleteA, rpcns4, 'RpcNsGroupDeleteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupDeleteA]
  end;
end;
{$ELSE}
function RpcNsGroupDeleteA; external rpcns4 name 'RpcNsGroupDeleteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupDeleteW: Pointer;

function RpcNsGroupDeleteW;
begin
  GetProcedureAddress(_RpcNsGroupDeleteW, rpcns4, 'RpcNsGroupDeleteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupDeleteW]
  end;
end;
{$ELSE}
function RpcNsGroupDeleteW; external rpcns4 name 'RpcNsGroupDeleteW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupDelete: Pointer;

function RpcNsGroupDelete;
begin
  GetProcedureAddress(_RpcNsGroupDelete, rpcns4, 'RpcNsGroupDeleteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupDelete]
  end;
end;
{$ELSE}
function RpcNsGroupDelete; external rpcns4 name 'RpcNsGroupDeleteW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupDelete: Pointer;

function RpcNsGroupDelete;
begin
  GetProcedureAddress(_RpcNsGroupDelete, rpcns4, 'RpcNsGroupDeleteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupDelete]
  end;
end;
{$ELSE}
function RpcNsGroupDelete; external rpcns4 name 'RpcNsGroupDeleteA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrAddA: Pointer;

function RpcNsGroupMbrAddA;
begin
  GetProcedureAddress(_RpcNsGroupMbrAddA, rpcns4, 'RpcNsGroupMbrAddA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrAddA]
  end;
end;
{$ELSE}
function RpcNsGroupMbrAddA; external rpcns4 name 'RpcNsGroupMbrAddA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrAddW: Pointer;

function RpcNsGroupMbrAddW;
begin
  GetProcedureAddress(_RpcNsGroupMbrAddW, rpcns4, 'RpcNsGroupMbrAddW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrAddW]
  end;
end;
{$ELSE}
function RpcNsGroupMbrAddW; external rpcns4 name 'RpcNsGroupMbrAddW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrAdd: Pointer;

function RpcNsGroupMbrAdd;
begin
  GetProcedureAddress(_RpcNsGroupMbrAdd, rpcns4, 'RpcNsGroupMbrAddW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrAdd]
  end;
end;
{$ELSE}
function RpcNsGroupMbrAdd; external rpcns4 name 'RpcNsGroupMbrAddW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrAdd: Pointer;

function RpcNsGroupMbrAdd;
begin
  GetProcedureAddress(_RpcNsGroupMbrAdd, rpcns4, 'RpcNsGroupMbrAddA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrAdd]
  end;
end;
{$ELSE}
function RpcNsGroupMbrAdd; external rpcns4 name 'RpcNsGroupMbrAddA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrRemoveA: Pointer;

function RpcNsGroupMbrRemoveA;
begin
  GetProcedureAddress(_RpcNsGroupMbrRemoveA, rpcns4, 'RpcNsGroupMbrRemoveA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrRemoveA]
  end;
end;
{$ELSE}
function RpcNsGroupMbrRemoveA; external rpcns4 name 'RpcNsGroupMbrRemoveA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrRemoveW: Pointer;

function RpcNsGroupMbrRemoveW;
begin
  GetProcedureAddress(_RpcNsGroupMbrRemoveW, rpcns4, 'RpcNsGroupMbrRemoveW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrRemoveW]
  end;
end;
{$ELSE}
function RpcNsGroupMbrRemoveW; external rpcns4 name 'RpcNsGroupMbrRemoveW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrRemove: Pointer;

function RpcNsGroupMbrRemove;
begin
  GetProcedureAddress(_RpcNsGroupMbrRemove, rpcns4, 'RpcNsGroupMbrRemoveW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrRemove]
  end;
end;
{$ELSE}
function RpcNsGroupMbrRemove; external rpcns4 name 'RpcNsGroupMbrRemoveW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrRemove: Pointer;

function RpcNsGroupMbrRemove;
begin
  GetProcedureAddress(_RpcNsGroupMbrRemove, rpcns4, 'RpcNsGroupMbrRemoveA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrRemove]
  end;
end;
{$ELSE}
function RpcNsGroupMbrRemove; external rpcns4 name 'RpcNsGroupMbrRemoveA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqBeginA: Pointer;

function RpcNsGroupMbrInqBeginA;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqBeginA, rpcns4, 'RpcNsGroupMbrInqBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqBeginA]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqBeginA; external rpcns4 name 'RpcNsGroupMbrInqBeginA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqBeginW: Pointer;

function RpcNsGroupMbrInqBeginW;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqBeginW, rpcns4, 'RpcNsGroupMbrInqBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqBeginW]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqBeginW; external rpcns4 name 'RpcNsGroupMbrInqBeginW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqBegin: Pointer;

function RpcNsGroupMbrInqBegin;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqBegin, rpcns4, 'RpcNsGroupMbrInqBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqBegin]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqBegin; external rpcns4 name 'RpcNsGroupMbrInqBeginW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqBegin: Pointer;

function RpcNsGroupMbrInqBegin;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqBegin, rpcns4, 'RpcNsGroupMbrInqBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqBegin]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqBegin; external rpcns4 name 'RpcNsGroupMbrInqBeginA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqNextA: Pointer;

function RpcNsGroupMbrInqNextA;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqNextA, rpcns4, 'RpcNsGroupMbrInqNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqNextA]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqNextA; external rpcns4 name 'RpcNsGroupMbrInqNextA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqNextW: Pointer;

function RpcNsGroupMbrInqNextW;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqNextW, rpcns4, 'RpcNsGroupMbrInqNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqNextW]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqNextW; external rpcns4 name 'RpcNsGroupMbrInqNextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqNext: Pointer;

function RpcNsGroupMbrInqNext;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqNext, rpcns4, 'RpcNsGroupMbrInqNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqNext]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqNext; external rpcns4 name 'RpcNsGroupMbrInqNextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqNext: Pointer;

function RpcNsGroupMbrInqNext;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqNext, rpcns4, 'RpcNsGroupMbrInqNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqNext]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqNext; external rpcns4 name 'RpcNsGroupMbrInqNextA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsGroupMbrInqDone: Pointer;

function RpcNsGroupMbrInqDone;
begin
  GetProcedureAddress(_RpcNsGroupMbrInqDone, rpcns4, 'RpcNsGroupMbrInqDone');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsGroupMbrInqDone]
  end;
end;
{$ELSE}
function RpcNsGroupMbrInqDone; external rpcns4 name 'RpcNsGroupMbrInqDone';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileDeleteA: Pointer;

function RpcNsProfileDeleteA;
begin
  GetProcedureAddress(_RpcNsProfileDeleteA, rpcns4, 'RpcNsProfileDeleteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileDeleteA]
  end;
end;
{$ELSE}
function RpcNsProfileDeleteA; external rpcns4 name 'RpcNsProfileDeleteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileDeleteW: Pointer;

function RpcNsProfileDeleteW;
begin
  GetProcedureAddress(_RpcNsProfileDeleteW, rpcns4, 'RpcNsProfileDeleteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileDeleteW]
  end;
end;
{$ELSE}
function RpcNsProfileDeleteW; external rpcns4 name 'RpcNsProfileDeleteW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileDelete: Pointer;

function RpcNsProfileDelete;
begin
  GetProcedureAddress(_RpcNsProfileDelete, rpcns4, 'RpcNsProfileDeleteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileDelete]
  end;
end;
{$ELSE}
function RpcNsProfileDelete; external rpcns4 name 'RpcNsProfileDeleteW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileDelete: Pointer;

function RpcNsProfileDelete;
begin
  GetProcedureAddress(_RpcNsProfileDelete, rpcns4, 'RpcNsProfileDeleteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileDelete]
  end;
end;
{$ELSE}
function RpcNsProfileDelete; external rpcns4 name 'RpcNsProfileDeleteA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltAddA: Pointer;

function RpcNsProfileEltAddA;
begin
  GetProcedureAddress(_RpcNsProfileEltAddA, rpcns4, 'RpcNsProfileEltAddA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltAddA]
  end;
end;
{$ELSE}
function RpcNsProfileEltAddA; external rpcns4 name 'RpcNsProfileEltAddA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltAddW: Pointer;

function RpcNsProfileEltAddW;
begin
  GetProcedureAddress(_RpcNsProfileEltAddW, rpcns4, 'RpcNsProfileEltAddW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltAddW]
  end;
end;
{$ELSE}
function RpcNsProfileEltAddW; external rpcns4 name 'RpcNsProfileEltAddW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltAdd: Pointer;

function RpcNsProfileEltAdd;
begin
  GetProcedureAddress(_RpcNsProfileEltAdd, rpcns4, 'RpcNsProfileEltAddW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltAdd]
  end;
end;
{$ELSE}
function RpcNsProfileEltAdd; external rpcns4 name 'RpcNsProfileEltAddW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltAdd: Pointer;

function RpcNsProfileEltAdd;
begin
  GetProcedureAddress(_RpcNsProfileEltAdd, rpcns4, 'RpcNsProfileEltAddA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltAdd]
  end;
end;
{$ELSE}
function RpcNsProfileEltAdd; external rpcns4 name 'RpcNsProfileEltAddA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltRemoveA: Pointer;

function RpcNsProfileEltRemoveA;
begin
  GetProcedureAddress(_RpcNsProfileEltRemoveA, rpcns4, 'RpcNsProfileEltRemoveA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltRemoveA]
  end;
end;
{$ELSE}
function RpcNsProfileEltRemoveA; external rpcns4 name 'RpcNsProfileEltRemoveA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltRemoveW: Pointer;

function RpcNsProfileEltRemoveW;
begin
  GetProcedureAddress(_RpcNsProfileEltRemoveW, rpcns4, 'RpcNsProfileEltRemoveW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltRemoveW]
  end;
end;
{$ELSE}
function RpcNsProfileEltRemoveW; external rpcns4 name 'RpcNsProfileEltRemoveW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltRemove: Pointer;

function RpcNsProfileEltRemove;
begin
  GetProcedureAddress(_RpcNsProfileEltRemove, rpcns4, 'RpcNsProfileEltRemoveW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltRemove]
  end;
end;
{$ELSE}
function RpcNsProfileEltRemove; external rpcns4 name 'RpcNsProfileEltRemoveW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltRemove: Pointer;

function RpcNsProfileEltRemove;
begin
  GetProcedureAddress(_RpcNsProfileEltRemove, rpcns4, 'RpcNsProfileEltRemoveA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltRemove]
  end;
end;
{$ELSE}
function RpcNsProfileEltRemove; external rpcns4 name 'RpcNsProfileEltRemoveA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqBeginA: Pointer;

function RpcNsProfileEltInqBeginA;
begin
  GetProcedureAddress(_RpcNsProfileEltInqBeginA, rpcns4, 'RpcNsProfileEltInqBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqBeginA]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqBeginA; external rpcns4 name 'RpcNsProfileEltInqBeginA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqBeginW: Pointer;

function RpcNsProfileEltInqBeginW;
begin
  GetProcedureAddress(_RpcNsProfileEltInqBeginW, rpcns4, 'RpcNsProfileEltInqBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqBeginW]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqBeginW; external rpcns4 name 'RpcNsProfileEltInqBeginW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqBegin: Pointer;

function RpcNsProfileEltInqBegin;
begin
  GetProcedureAddress(_RpcNsProfileEltInqBegin, rpcns4, 'RpcNsProfileEltInqBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqBegin]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqBegin; external rpcns4 name 'RpcNsProfileEltInqBeginW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqBegin: Pointer;

function RpcNsProfileEltInqBegin;
begin
  GetProcedureAddress(_RpcNsProfileEltInqBegin, rpcns4, 'RpcNsProfileEltInqBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqBegin]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqBegin; external rpcns4 name 'RpcNsProfileEltInqBeginA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqNextA: Pointer;

function RpcNsProfileEltInqNextA;
begin
  GetProcedureAddress(_RpcNsProfileEltInqNextA, rpcns4, 'RpcNsProfileEltInqNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqNextA]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqNextA; external rpcns4 name 'RpcNsProfileEltInqNextA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqNextW: Pointer;

function RpcNsProfileEltInqNextW;
begin
  GetProcedureAddress(_RpcNsProfileEltInqNextW, rpcns4, 'RpcNsProfileEltInqNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqNextW]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqNextW; external rpcns4 name 'RpcNsProfileEltInqNextW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqNext: Pointer;

function RpcNsProfileEltInqNext;
begin
  GetProcedureAddress(_RpcNsProfileEltInqNext, rpcns4, 'RpcNsProfileEltInqNextW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqNext]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqNext; external rpcns4 name 'RpcNsProfileEltInqNextW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqNext: Pointer;

function RpcNsProfileEltInqNext;
begin
  GetProcedureAddress(_RpcNsProfileEltInqNext, rpcns4, 'RpcNsProfileEltInqNextA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqNext]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqNext; external rpcns4 name 'RpcNsProfileEltInqNextA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsProfileEltInqDone: Pointer;

function RpcNsProfileEltInqDone;
begin
  GetProcedureAddress(_RpcNsProfileEltInqDone, rpcns4, 'RpcNsProfileEltInqDone');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsProfileEltInqDone]
  end;
end;
{$ELSE}
function RpcNsProfileEltInqDone; external rpcns4 name 'RpcNsProfileEltInqDone';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryObjectInqBeginA: Pointer;

function RpcNsEntryObjectInqBeginA;
begin
  GetProcedureAddress(_RpcNsEntryObjectInqBeginA, rpcns4, 'RpcNsEntryObjectInqBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryObjectInqBeginA]
  end;
end;
{$ELSE}
function RpcNsEntryObjectInqBeginA; external rpcns4 name 'RpcNsEntryObjectInqBeginA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryObjectInqBeginW: Pointer;

function RpcNsEntryObjectInqBeginW;
begin
  GetProcedureAddress(_RpcNsEntryObjectInqBeginW, rpcns4, 'RpcNsEntryObjectInqBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryObjectInqBeginW]
  end;
end;
{$ELSE}
function RpcNsEntryObjectInqBeginW; external rpcns4 name 'RpcNsEntryObjectInqBeginW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryObjectInqBegin: Pointer;

function RpcNsEntryObjectInqBegin;
begin
  GetProcedureAddress(_RpcNsEntryObjectInqBegin, rpcns4, 'RpcNsEntryObjectInqBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryObjectInqBegin]
  end;
end;
{$ELSE}
function RpcNsEntryObjectInqBegin; external rpcns4 name 'RpcNsEntryObjectInqBeginW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryObjectInqBegin: Pointer;

function RpcNsEntryObjectInqBegin;
begin
  GetProcedureAddress(_RpcNsEntryObjectInqBegin, rpcns4, 'RpcNsEntryObjectInqBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryObjectInqBegin]
  end;
end;
{$ELSE}
function RpcNsEntryObjectInqBegin; external rpcns4 name 'RpcNsEntryObjectInqBeginA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryObjectInqNext: Pointer;

function RpcNsEntryObjectInqNext;
begin
  GetProcedureAddress(_RpcNsEntryObjectInqNext, rpcns4, 'RpcNsEntryObjectInqNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryObjectInqNext]
  end;
end;
{$ELSE}
function RpcNsEntryObjectInqNext; external rpcns4 name 'RpcNsEntryObjectInqNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryObjectInqDone: Pointer;

function RpcNsEntryObjectInqDone;
begin
  GetProcedureAddress(_RpcNsEntryObjectInqDone, rpcns4, 'RpcNsEntryObjectInqDone');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryObjectInqDone]
  end;
end;
{$ELSE}
function RpcNsEntryObjectInqDone; external rpcns4 name 'RpcNsEntryObjectInqDone';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryExpandNameA: Pointer;

function RpcNsEntryExpandNameA;
begin
  GetProcedureAddress(_RpcNsEntryExpandNameA, rpcns4, 'RpcNsEntryExpandNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryExpandNameA]
  end;
end;
{$ELSE}
function RpcNsEntryExpandNameA; external rpcns4 name 'RpcNsEntryExpandNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryExpandNameW: Pointer;

function RpcNsEntryExpandNameW;
begin
  GetProcedureAddress(_RpcNsEntryExpandNameW, rpcns4, 'RpcNsEntryExpandNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryExpandNameW]
  end;
end;
{$ELSE}
function RpcNsEntryExpandNameW; external rpcns4 name 'RpcNsEntryExpandNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryExpandName: Pointer;

function RpcNsEntryExpandName;
begin
  GetProcedureAddress(_RpcNsEntryExpandName, rpcns4, 'RpcNsEntryExpandNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryExpandName]
  end;
end;
{$ELSE}
function RpcNsEntryExpandName; external rpcns4 name 'RpcNsEntryExpandNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsEntryExpandName: Pointer;

function RpcNsEntryExpandName;
begin
  GetProcedureAddress(_RpcNsEntryExpandName, rpcns4, 'RpcNsEntryExpandNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsEntryExpandName]
  end;
end;
{$ELSE}
function RpcNsEntryExpandName; external rpcns4 name 'RpcNsEntryExpandNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtBindingUnexportA: Pointer;

function RpcNsMgmtBindingUnexportA;
begin
  GetProcedureAddress(_RpcNsMgmtBindingUnexportA, rpcns4, 'RpcNsMgmtBindingUnexportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtBindingUnexportA]
  end;
end;
{$ELSE}
function RpcNsMgmtBindingUnexportA; external rpcns4 name 'RpcNsMgmtBindingUnexportA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtBindingUnexportW: Pointer;

function RpcNsMgmtBindingUnexportW;
begin
  GetProcedureAddress(_RpcNsMgmtBindingUnexportW, rpcns4, 'RpcNsMgmtBindingUnexportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtBindingUnexportW]
  end;
end;
{$ELSE}
function RpcNsMgmtBindingUnexportW; external rpcns4 name 'RpcNsMgmtBindingUnexportW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtBindingUnexport: Pointer;

function RpcNsMgmtBindingUnexport;
begin
  GetProcedureAddress(_RpcNsMgmtBindingUnexport, rpcns4, 'RpcNsMgmtBindingUnexportW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtBindingUnexport]
  end;
end;
{$ELSE}
function RpcNsMgmtBindingUnexport; external rpcns4 name 'RpcNsMgmtBindingUnexportW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtBindingUnexport: Pointer;

function RpcNsMgmtBindingUnexport;
begin
  GetProcedureAddress(_RpcNsMgmtBindingUnexport, rpcns4, 'RpcNsMgmtBindingUnexportA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtBindingUnexport]
  end;
end;
{$ELSE}
function RpcNsMgmtBindingUnexport; external rpcns4 name 'RpcNsMgmtBindingUnexportA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryCreateA: Pointer;

function RpcNsMgmtEntryCreateA;
begin
  GetProcedureAddress(_RpcNsMgmtEntryCreateA, rpcns4, 'RpcNsMgmtEntryCreateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryCreateA]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryCreateA; external rpcns4 name 'RpcNsMgmtEntryCreateA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryCreateW: Pointer;

function RpcNsMgmtEntryCreateW;
begin
  GetProcedureAddress(_RpcNsMgmtEntryCreateW, rpcns4, 'RpcNsMgmtEntryCreateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryCreateW]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryCreateW; external rpcns4 name 'RpcNsMgmtEntryCreateW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryCreate: Pointer;

function RpcNsMgmtEntryCreate;
begin
  GetProcedureAddress(_RpcNsMgmtEntryCreate, rpcns4, 'RpcNsMgmtEntryCreateW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryCreate]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryCreate; external rpcns4 name 'RpcNsMgmtEntryCreateW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryCreate: Pointer;

function RpcNsMgmtEntryCreate;
begin
  GetProcedureAddress(_RpcNsMgmtEntryCreate, rpcns4, 'RpcNsMgmtEntryCreateA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryCreate]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryCreate; external rpcns4 name 'RpcNsMgmtEntryCreateA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryDeleteA: Pointer;

function RpcNsMgmtEntryDeleteA;
begin
  GetProcedureAddress(_RpcNsMgmtEntryDeleteA, rpcns4, 'RpcNsMgmtEntryDeleteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryDeleteA]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryDeleteA; external rpcns4 name 'RpcNsMgmtEntryDeleteA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryDeleteW: Pointer;

function RpcNsMgmtEntryDeleteW;
begin
  GetProcedureAddress(_RpcNsMgmtEntryDeleteW, rpcns4, 'RpcNsMgmtEntryDeleteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryDeleteW]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryDeleteW; external rpcns4 name 'RpcNsMgmtEntryDeleteW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryDelete: Pointer;

function RpcNsMgmtEntryDelete;
begin
  GetProcedureAddress(_RpcNsMgmtEntryDelete, rpcns4, 'RpcNsMgmtEntryDeleteW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryDelete]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryDelete; external rpcns4 name 'RpcNsMgmtEntryDeleteW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryDelete: Pointer;

function RpcNsMgmtEntryDelete;
begin
  GetProcedureAddress(_RpcNsMgmtEntryDelete, rpcns4, 'RpcNsMgmtEntryDeleteA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryDelete]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryDelete; external rpcns4 name 'RpcNsMgmtEntryDeleteA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryInqIfIdsA: Pointer;

function RpcNsMgmtEntryInqIfIdsA;
begin
  GetProcedureAddress(_RpcNsMgmtEntryInqIfIdsA, rpcns4, 'RpcNsMgmtEntryInqIfIdsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryInqIfIdsA]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryInqIfIdsA; external rpcns4 name 'RpcNsMgmtEntryInqIfIdsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryInqIfIdsW: Pointer;

function RpcNsMgmtEntryInqIfIdsW;
begin
  GetProcedureAddress(_RpcNsMgmtEntryInqIfIdsW, rpcns4, 'RpcNsMgmtEntryInqIfIdsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryInqIfIdsW]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryInqIfIdsW; external rpcns4 name 'RpcNsMgmtEntryInqIfIdsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryInqIfIds: Pointer;

function RpcNsMgmtEntryInqIfIds;
begin
  GetProcedureAddress(_RpcNsMgmtEntryInqIfIds, rpcns4, 'RpcNsMgmtEntryInqIfIdsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryInqIfIds]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryInqIfIds; external rpcns4 name 'RpcNsMgmtEntryInqIfIdsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtEntryInqIfIds: Pointer;

function RpcNsMgmtEntryInqIfIds;
begin
  GetProcedureAddress(_RpcNsMgmtEntryInqIfIds, rpcns4, 'RpcNsMgmtEntryInqIfIdsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtEntryInqIfIds]
  end;
end;
{$ELSE}
function RpcNsMgmtEntryInqIfIds; external rpcns4 name 'RpcNsMgmtEntryInqIfIdsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtHandleSetExpAge: Pointer;

function RpcNsMgmtHandleSetExpAge;
begin
  GetProcedureAddress(_RpcNsMgmtHandleSetExpAge, rpcns4, 'RpcNsMgmtHandleSetExpAge');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtHandleSetExpAge]
  end;
end;
{$ELSE}
function RpcNsMgmtHandleSetExpAge; external rpcns4 name 'RpcNsMgmtHandleSetExpAge';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtInqExpAge: Pointer;

function RpcNsMgmtInqExpAge;
begin
  GetProcedureAddress(_RpcNsMgmtInqExpAge, rpcns4, 'RpcNsMgmtInqExpAge');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtInqExpAge]
  end;
end;
{$ELSE}
function RpcNsMgmtInqExpAge; external rpcns4 name 'RpcNsMgmtInqExpAge';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsMgmtSetExpAge: Pointer;

function RpcNsMgmtSetExpAge;
begin
  GetProcedureAddress(_RpcNsMgmtSetExpAge, rpcns4, 'RpcNsMgmtSetExpAge');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsMgmtSetExpAge]
  end;
end;
{$ELSE}
function RpcNsMgmtSetExpAge; external rpcns4 name 'RpcNsMgmtSetExpAge';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingImportBeginA: Pointer;

function RpcNsBindingImportBeginA;
begin
  GetProcedureAddress(_RpcNsBindingImportBeginA, rpcns4, 'RpcNsBindingImportBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingImportBeginA]
  end;
end;
{$ELSE}
function RpcNsBindingImportBeginA; external rpcns4 name 'RpcNsBindingImportBeginA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingImportBeginW: Pointer;

function RpcNsBindingImportBeginW;
begin
  GetProcedureAddress(_RpcNsBindingImportBeginW, rpcns4, 'RpcNsBindingImportBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingImportBeginW]
  end;
end;
{$ELSE}
function RpcNsBindingImportBeginW; external rpcns4 name 'RpcNsBindingImportBeginW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingImportBegin: Pointer;

function RpcNsBindingImportBegin;
begin
  GetProcedureAddress(_RpcNsBindingImportBegin, rpcns4, 'RpcNsBindingImportBeginW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingImportBegin]
  end;
end;
{$ELSE}
function RpcNsBindingImportBegin; external rpcns4 name 'RpcNsBindingImportBeginW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingImportBegin: Pointer;

function RpcNsBindingImportBegin;
begin
  GetProcedureAddress(_RpcNsBindingImportBegin, rpcns4, 'RpcNsBindingImportBeginA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingImportBegin]
  end;
end;
{$ELSE}
function RpcNsBindingImportBegin; external rpcns4 name 'RpcNsBindingImportBeginA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingImportNext: Pointer;

function RpcNsBindingImportNext;
begin
  GetProcedureAddress(_RpcNsBindingImportNext, rpcns4, 'RpcNsBindingImportNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingImportNext]
  end;
end;
{$ELSE}
function RpcNsBindingImportNext; external rpcns4 name 'RpcNsBindingImportNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingImportDone: Pointer;

function RpcNsBindingImportDone;
begin
  GetProcedureAddress(_RpcNsBindingImportDone, rpcns4, 'RpcNsBindingImportDone');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingImportDone]
  end;
end;
{$ELSE}
function RpcNsBindingImportDone; external rpcns4 name 'RpcNsBindingImportDone';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RpcNsBindingSelect: Pointer;

function RpcNsBindingSelect;
begin
  GetProcedureAddress(_RpcNsBindingSelect, rpcns4, 'RpcNsBindingSelect');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RpcNsBindingSelect]
  end;
end;
{$ELSE}
function RpcNsBindingSelect; external rpcns4 name 'RpcNsBindingSelect';
{$ENDIF DYNAMIC_LINK}

end.
