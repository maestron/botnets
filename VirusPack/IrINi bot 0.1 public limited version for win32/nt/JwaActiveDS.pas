{******************************************************************************}
{                                                       	               }
{ Active Directory Services API interface Unit for Object Pascal               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: activeds.h, released June 2000. The original Pascal    }
{ code is: ActiveDS.pas, released December 2000. The initial developer of the  }
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
{ For more information about the LGPL: http://www.gn.org/copyleft/lesser.html }
{ 						    u		               }
{******************************************************************************}

unit JwaActiveDS;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "activeds.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef GUID REFIID'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  ActiveX {TODO}, JwaAdsTLB, JwaWinNT, JwaWinType, JwaWinUser;

type
  REFIID = GUID;
  {$NODEFINE REFIID}

type
  // imports of a type library sometimes are missing a few decls, these are just
  // a few of them to make this file compile at all. I really should do all of
  // them one day.

  PADSVALUE = ^_adsvalue;
  {$EXTERNALSYM PADSVALUE}
  PADS_ATTR_INFO = ^_ads_attr_info;
  {$EXTERNALSYM PADS_ATTR_INFO}

//  Contents:   Master include file for Ole Ds
//
//  Notes:      All Ole Ds client applications must include this file. This
//              provides access to the primary Ole Ds interfaces, the error
//              codes, and function prototypes for the Ole Ds helper apis.

//
// Interface definitions and well known GUIDS for Ole Ds
//

//#include "iads.h"  >> AdsTLB from activeds.dll

//
// Helper function prototypes for Ole Ds
//

//#include "adshlp.h"

function ADsGetObject(lpszPathName: LPCWSTR; const riid: REFIID; out ppObject: Pointer): HRESULT; stdcall;
{$EXTERNALSYM ADsGetObject}

function ADsBuildEnumerator(pADsContainer: IADsContainer; out ppEnumVariant: IEnumVARIANT): HRESULT; stdcall;
{$EXTERNALSYM ADsBuildEnumerator}

function ADsFreeEnumerator(var pEnumVariant: IEnumVARIANT): HRESULT;
{$EXTERNALSYM ADsFreeEnumerator}

function ADsEnumerateNext(pEnumVariant: IEnumVARIANT; cElements: ULONG;
  var pvar: OleVariant; var pcElementsFetched: ULONG): HRESULT; stdcall;
{$EXTERNALSYM ADsEnumerateNext}

function ADsBuildVarArrayStr(lppPathNames: LPWSTR; dwPathNames: DWORD;
  var pVar: OleVariant): HRESULT; stdcall;
{$EXTERNALSYM ADsBuildVarArrayStr}

function ADsBuildVarArrayInt(lpdwObjectTypes: LPDWORD; dwObjectTypes: DWORD;
  var pVar: OleVariant): HRESULT; stdcall;
{$EXTERNALSYM ADsBuildVarArrayInt}

function ADsOpenObject(lpszPathName, lpszUserName, lpszPassword: LPCWSTR;
  dwReserved: DWORD; const riid: REFIID; out ppObject: Pointer): HRESULT; stdcall;
{$EXTERNALSYM ADsOpenObject}

//
// Helper functions for extended error support
//

function ADsGetLastError(var lpError: DWORD; lpErrorBuf: LPWSTR;
  dwErrorBufLen: DWORD; lpNameBuf: LPWSTR; dwNameBufLen: DWORD): HRESULT; stdcall;
{$EXTERNALSYM ADsGetLastError}

procedure ADsSetLastError(dwErr: DWORD; pszError, pszProvider: LPCWSTR); stdcall;
{$EXTERNALSYM ADsSetLastError}

//procedure ADsFreeAllErrorRecords; stdcall;
//{$EXTERNALSYM ADsFreeAllErrorRecords}

function AllocADsMem(cb: DWORD): LPVOID; stdcall;
{$EXTERNALSYM AllocADsMem}

function FreeADsMem(pMem: LPVOID): BOOL; stdcall;
{$EXTERNALSYM FreeADsMem}

function ReallocADsMem(pOldMem: LPVOID; cbOld, cbNew: DWORD): LPVOID; stdcall;
{$EXTERNALSYM ReallocADsMem}

function AllocADsStr(pStr: LPCWSTR): LPWSTR; stdcall;
{$EXTERNALSYM AllocADsStr}

function FreeADsStr(pStr: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM FreeADsStr}

function ReallocADsStr(var ppStr: LPWSTR; pStr: LPWSTR): BOOL; stdcall;
{$EXTERNALSYM ReallocADsStr}

function ADsEncodeBinaryData(pbSrcData: PBYTE; dwSrcLen: DWORD;
  var ppszDestData: LPWSTR): HRESULT; stdcall;
{$EXTERNALSYM ADsEncodeBinaryData}

function ADsDecodeBinaryData(szSrcData: LPCWSTR; var ppbDestData: PBYTE;
  var pdwDestLen: ULONG): HRESULT; stdcall;
{$EXTERNALSYM ADsDecodeBinaryData}

function PropVariantToAdsType(var pVariant: OleVariant; dwNumVariant: DWORD;
  var ppAdsValues: PADSVALUE; pdwNumValues: PDWORD): HRESULT; stdcall;
{$EXTERNALSYM PropVariantToAdsType}

function AdsTypeToPropVariant(pAdsValues: PADSVALUE; dwNumValues: DWORD;
  var pVariant: OleVariant): HRESULT; stdcall;
{$EXTERNALSYM AdsTypeToPropVariant}

procedure AdsFreeAdsValues(pAdsValues: PADSVALUE; dwNumValues: DWORD); stdcall;
{$EXTERNALSYM AdsFreeAdsValues}

//
// Error codes for Ole Ds - generated from ..\..\errmsg
//

//#include "adserr.h"

// ---------------------- HRESULT value definitions -----------------
//
// HRESULT definitions
//

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//

const
  FACILITY_WINDOWS  = 8;
  {$EXTERNALSYM FACILITY_WINDOWS}
  FACILITY_STORAGE  = 3;
  {$EXTERNALSYM FACILITY_STORAGE}
  FACILITY_RPC      = 1;
  {$EXTERNALSYM FACILITY_RPC}
  FACILITY_SSPI     = 9;
  {$EXTERNALSYM FACILITY_SSPI}
  FACILITY_WIN32    = 7;
  {$EXTERNALSYM FACILITY_WIN32}
  FACILITY_CONTROL  = 10;
  {$EXTERNALSYM FACILITY_CONTROL}
  FACILITY_NULL     = 0;
  {$EXTERNALSYM FACILITY_NULL}
  FACILITY_ITF      = 4;
  {$EXTERNALSYM FACILITY_ITF}
  FACILITY_DISPATCH = 2;
  {$EXTERNALSYM FACILITY_DISPATCH}

//
// Define the severity codes
//


//
// MessageId: E_ADS_BAD_PATHNAME
//
// MessageText:
//
//  An invalid Active Directory pathname was passed
//

  E_ADS_BAD_PATHNAME               = HRESULT($80005000);
  {$EXTERNALSYM E_ADS_BAD_PATHNAME}

//
// MessageId: E_ADS_INVALID_DOMAIN_OBJECT
//
// MessageText:
//
//  An unknown Active Directory domain object was requested
//

  E_ADS_INVALID_DOMAIN_OBJECT      = HRESULT($80005001);
  {$EXTERNALSYM  E_ADS_INVALID_DOMAIN_OBJECT}

//
// MessageId: E_ADS_INVALID_USER_OBJECT
//
// MessageText:
//
//  An unknown Active Directory user object was requested
//

  E_ADS_INVALID_USER_OBJECT        = HRESULT($80005002);
  {$EXTERNALSYM E_ADS_INVALID_USER_OBJECT}

//
// MessageId: E_ADS_INVALID_COMPUTER_OBJECT
//
// MessageText:
//
//  An unknown Active Directory computer object was requested
//

  E_ADS_INVALID_COMPUTER_OBJECT    = HRESULT($80005003);
  {$EXTERNALSYM E_ADS_INVALID_COMPUTER_OBJECT}

//
// MessageId: E_ADS_UNKNOWN_OBJECT
//
// MessageText:
//
//  An unknown Active Directory object was requested
//

  E_ADS_UNKNOWN_OBJECT             = HRESULT($80005004);
  {$EXTERNALSYM E_ADS_UNKNOWN_OBJECT}

//
// MessageId: E_ADS_PROPERTY_NOT_SET
//
// MessageText:
//
//  The specified Active Directory property was not set
//

  E_ADS_PROPERTY_NOT_SET           = HRESULT($80005005);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_SET}

//
// MessageId: E_ADS_PROPERTY_NOT_SUPPORTED
//
// MessageText:
//
//  The specified Active Directory property is not supported
//

  E_ADS_PROPERTY_NOT_SUPPORTED     = HRESULT($80005006);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_SUPPORTED}

//
// MessageId: E_ADS_PROPERTY_INVALID
//
// MessageText:
//
//  The specified Active Directory property is invalid
//

  E_ADS_PROPERTY_INVALID           = HRESULT($80005007);
  {$EXTERNALSYM E_ADS_PROPERTY_INVALID}

//
// MessageId: E_ADS_BAD_PARAMETER
//
// MessageText:
//
//  One or more input parameters are invalid
//

  E_ADS_BAD_PARAMETER              = HRESULT($80005008);
  {$EXTERNALSYM E_ADS_BAD_PARAMETER}

//
// MessageId: E_ADS_OBJECT_UNBOUND
//
// MessageText:
//
//  The specified Active Directory object is not bound to a remote resource
//

  E_ADS_OBJECT_UNBOUND             = HRESULT($80005009);
  {$EXTERNALSYM E_ADS_OBJECT_UNBOUND}

//
// MessageId: E_ADS_PROPERTY_NOT_MODIFIED
//
// MessageText:
//
//  The specified Active Directory object has not been modified
//

  E_ADS_PROPERTY_NOT_MODIFIED      = HRESULT($8000500A);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_MODIFIED}

//
// MessageId: E_ADS_PROPERTY_MODIFIED
//
// MessageText:
//
//  The specified Active Directory object has not been modified
//

  E_ADS_PROPERTY_MODIFIED          = HRESULT($8000500B);
  {$EXTERNALSYM E_ADS_PROPERTY_MODIFIED}

//
// MessageId: E_ADS_CANT_CONVERT_DATATYPE
//
// MessageText:
//
//  The Active Directory datatype cannot be converted to/from a native DS datatype
//

  E_ADS_CANT_CONVERT_DATATYPE      = HRESULT($8000500C);
  {$EXTERNALSYM E_ADS_CANT_CONVERT_DATATYPE}

//
// MessageId: E_ADS_PROPERTY_NOT_FOUND
//
// MessageText:
//
//  The Active Directory property cannot be found in the cache.
//

  E_ADS_PROPERTY_NOT_FOUND         = HRESULT($8000500D);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_FOUND}

//
// MessageId: E_ADS_OBJECT_EXISTS
//
// MessageText:
//
//  The Active Directory object exists.
//

  E_ADS_OBJECT_EXISTS              = HRESULT($8000500E);
  {$EXTERNALSYM E_ADS_OBJECT_EXISTS}

//
// MessageId: E_ADS_SCHEMA_VIOLATION
//
// MessageText:
//
//  The attempted action violates the DS schema rules.
//

  E_ADS_SCHEMA_VIOLATION           = HRESULT($8000500F);
  {$EXTERNALSYM E_ADS_SCHEMA_VIOLATION}

//
// MessageId: E_ADS_COLUMN_NOT_SET
//
// MessageText:
//
//  The specified column in the Active Directory was not set.
//

  E_ADS_COLUMN_NOT_SET             = HRESULT($80005010);
  {$EXTERNALSYM E_ADS_COLUMN_NOT_SET}

//
// MessageId: S_ADS_ERRORSOCCURRED
//
// MessageText:
//
//  One or more errors occurred
//

  S_ADS_ERRORSOCCURRED             = HRESULT($00005011);
  {$EXTERNALSYM S_ADS_ERRORSOCCURRED}

//
// MessageId: S_ADS_NOMORE_ROWS
//
// MessageText:
//
//  No more rows to be obatained by the search result.
//

  S_ADS_NOMORE_ROWS                = HRESULT($00005012);
  {$EXTERNALSYM S_ADS_NOMORE_ROWS}

//
// MessageId: S_ADS_NOMORE_COLUMNS
//
// MessageText:
//
//  No more columns to be obatained for the current row.
//

  S_ADS_NOMORE_COLUMNS             = HRESULT($00005013);
  {$EXTERNALSYM S_ADS_NOMORE_COLUMNS}

//
// MessageId: E_ADS_INVALID_FILTER
//
// MessageText:
//
//  The search filter specified is invalid
//

  E_ADS_INVALID_FILTER             = HRESULT($80005014);
  {$EXTERNALSYM E_ADS_INVALID_FILTER}

//
// Globally accessible GUIDS
//

//#include "adsiid.h" -> adstlb from activeds.dll

//
// Status codes for ads objects
//

//#include "adssts.h"

const
  ADS_PRINTER_PAUSED            = $00000001;
  {$EXTERNALSYM ADS_PRINTER_PAUSED}
  ADS_PRINTER_PENDING_DELETION  = $00000002;
  {$EXTERNALSYM ADS_PRINTER_PENDING_DELETION}
  ADS_PRINTER_ERROR             = $00000003;
  {$EXTERNALSYM ADS_PRINTER_ERROR}
  ADS_PRINTER_PAPER_JAM         = $00000004;
  {$EXTERNALSYM ADS_PRINTER_PAPER_JAM}
  ADS_PRINTER_PAPER_OUT         = $00000005;
  {$EXTERNALSYM ADS_PRINTER_PAPER_OUT}
  ADS_PRINTER_MANUAL_FEED       = $00000006;
  {$EXTERNALSYM ADS_PRINTER_MANUAL_FEED}
  ADS_PRINTER_PAPER_PROBLEM     = $00000007;
  {$EXTERNALSYM ADS_PRINTER_PAPER_PROBLEM}
  ADS_PRINTER_OFFLINE           = $00000008;
  {$EXTERNALSYM ADS_PRINTER_OFFLINE}
  ADS_PRINTER_IO_ACTIVE         = $00000100;
  {$EXTERNALSYM ADS_PRINTER_IO_ACTIVE}
  ADS_PRINTER_BUSY              = $00000200;
  {$EXTERNALSYM ADS_PRINTER_BUSY}
  ADS_PRINTER_PRINTING          = $00000400;
  {$EXTERNALSYM ADS_PRINTER_PRINTING}
  ADS_PRINTER_OUTPUT_BIN_FULL   = $00000800;
  {$EXTERNALSYM ADS_PRINTER_OUTPUT_BIN_FULL}
  ADS_PRINTER_NOT_AVAILABLE     = $00001000;
  {$EXTERNALSYM ADS_PRINTER_NOT_AVAILABLE}
  ADS_PRINTER_WAITING           = $00002000;
  {$EXTERNALSYM ADS_PRINTER_WAITING}
  ADS_PRINTER_PROCESSING        = $00004000;
  {$EXTERNALSYM ADS_PRINTER_PROCESSING}
  ADS_PRINTER_INITIALIZING      = $00008000;
  {$EXTERNALSYM ADS_PRINTER_INITIALIZING}
  ADS_PRINTER_WARMING_UP        = $00010000;
  {$EXTERNALSYM ADS_PRINTER_WARMING_UP}
  ADS_PRINTER_TONER_LOW         = $00020000;
  {$EXTERNALSYM ADS_PRINTER_TONER_LOW}
  ADS_PRINTER_NO_TONER          = $00040000;
  {$EXTERNALSYM ADS_PRINTER_NO_TONER}
  ADS_PRINTER_PAGE_PUNT         = $00080000;
  {$EXTERNALSYM ADS_PRINTER_PAGE_PUNT}
  ADS_PRINTER_USER_INTERVENTION = $00100000;
  {$EXTERNALSYM ADS_PRINTER_USER_INTERVENTION}
  ADS_PRINTER_OUT_OF_MEMORY     = $00200000;
  {$EXTERNALSYM ADS_PRINTER_OUT_OF_MEMORY}
  ADS_PRINTER_DOOR_OPEN         = $00400000;
  {$EXTERNALSYM ADS_PRINTER_DOOR_OPEN}
  ADS_PRINTER_SERVER_UNKNOWN    = $00800000;
  {$EXTERNALSYM ADS_PRINTER_SERVER_UNKNOWN}
  ADS_PRINTER_POWER_SAVE        = $01000000;
  {$EXTERNALSYM ADS_PRINTER_POWER_SAVE}

//
// job status values
//

  ADS_JOB_PAUSED   = $00000001;
  {$EXTERNALSYM ADS_JOB_PAUSED}
  ADS_JOB_ERROR    = $00000002;
  {$EXTERNALSYM ADS_JOB_ERROR}
  ADS_JOB_DELETING = $00000004;
  {$EXTERNALSYM ADS_JOB_DELETING}
  ADS_JOB_SPOOLING = $00000008;
  {$EXTERNALSYM ADS_JOB_SPOOLING}
  ADS_JOB_PRINTING = $00000010;
  {$EXTERNALSYM ADS_JOB_PRINTING}
  ADS_JOB_OFFLINE  = $00000020;
  {$EXTERNALSYM ADS_JOB_OFFLINE}
  ADS_JOB_PAPEROUT = $00000040;
  {$EXTERNALSYM ADS_JOB_PAPEROUT}
  ADS_JOB_PRINTED  = $00000080;
  {$EXTERNALSYM ADS_JOB_PRINTED}
  ADS_JOB_DELETED  = $00000100;
  {$EXTERNALSYM ADS_JOB_DELETED}

//
// service status values
//

  ADS_SERVICE_STOPPED          = $00000001;
  {$EXTERNALSYM ADS_SERVICE_STOPPED}
  ADS_SERVICE_START_PENDING	   = $00000002;
  {$EXTERNALSYM ADS_SERVICE_START_PENDING	}
  ADS_SERVICE_STOP_PENDING     = $00000003;
  {$EXTERNALSYM ADS_SERVICE_STOP_PENDING}
  ADS_SERVICE_RUNNING	         = $00000004;
  {$EXTERNALSYM ADS_SERVICE_RUNNING	}
  ADS_SERVICE_CONTINUE_PENDING = $00000005;
  {$EXTERNALSYM ADS_SERVICE_CONTINUE_PENDING}
  ADS_SERVICE_PAUSE_PENDING	   = $00000006;
  {$EXTERNALSYM ADS_SERVICE_PAUSE_PENDING	}
  ADS_SERVICE_PAUSED           = $00000007;
  {$EXTERNALSYM ADS_SERVICE_PAUSED}
  ADS_SERVICE_ERROR            = $00000008;
  {$EXTERNALSYM ADS_SERVICE_ERROR}

//---------------------------------------------------------------------

//
// Service Type Valid Values
//

  ADS_SERVICE_OWN_PROCESS        = $00000010;
  {$EXTERNALSYM ADS_SERVICE_OWN_PROCESS}
  ADS_SERVICE_SHARE_PROCESS      = $00000020;
  {$EXTERNALSYM ADS_SERVICE_SHARE_PROCESS}
  ADS_SERVICE_KERNEL_DRIVER      = $00000001;
  {$EXTERNALSYM ADS_SERVICE_KERNEL_DRIVER}
  ADS_SERVICE_FILE_SYSTEM_DRIVER = $00000002;
  {$EXTERNALSYM ADS_SERVICE_FILE_SYSTEM_DRIVER}

//
// Start Type Valid Values
//

  ADS_SERVICE_BOOT_START   = SERVICE_BOOT_START;
  {$EXTERNALSYM ADS_SERVICE_BOOT_START}
  ADS_SERVICE_SYSTEM_START = SERVICE_SYSTEM_START;
  {$EXTERNALSYM ADS_SERVICE_SYSTEM_START}
  ADS_SERVICE_AUTO_START   = SERVICE_AUTO_START;
  {$EXTERNALSYM ADS_SERVICE_AUTO_START}
  ADS_SERVICE_DEMAND_START = SERVICE_DEMAND_START;
  {$EXTERNALSYM ADS_SERVICE_DEMAND_START}
  ADS_SERVICE_DISABLED     = SERVICE_DISABLED;
  {$EXTERNALSYM ADS_SERVICE_DISABLED}

//
// Error Control Values
//

  ADS_SERVICE_ERROR_IGNORE   = 0;
  {$EXTERNALSYM ADS_SERVICE_ERROR_IGNORE}
  ADS_SERVICE_ERROR_NORMAL   = 1;
  {$EXTERNALSYM ADS_SERVICE_ERROR_NORMAL}
  ADS_SERVICE_ERROR_SEVERE   = 2;
  {$EXTERNALSYM ADS_SERVICE_ERROR_SEVERE}
  ADS_SERVICE_ERROR_CRITICAL = 3;
  {$EXTERNALSYM ADS_SERVICE_ERROR_CRITICAL}

//
// Schema class names and other schema related definitions
//

//#include "adsnms.h"

const
  NAMESPACE_CLASS_NAME        = 'Namespace';
  {$EXTERNALSYM NAMESPACE_CLASS_NAME}
  COUNTRY_CLASS_NAME          = 'Country';
  {$EXTERNALSYM COUNTRY_CLASS_NAME}
  LOCALITY_CLASS_NAME         = 'Locality';
  {$EXTERNALSYM LOCALITY_CLASS_NAME}
  ORGANIZATION_CLASS_NAME     = 'Organization';
  {$EXTERNALSYM ORGANIZATION_CLASS_NAME}
  ORGANIZATIONUNIT_CLASS_NAME = 'Organizational Unit';
  {$EXTERNALSYM ORGANIZATIONUNIT_CLASS_NAME}
  DOMAIN_CLASS_NAME           = 'Domain';
  {$EXTERNALSYM DOMAIN_CLASS_NAME}
  COMPUTER_CLASS_NAME         = 'Computer';
  {$EXTERNALSYM COMPUTER_CLASS_NAME}
  USER_CLASS_NAME             = 'User';
  {$EXTERNALSYM USER_CLASS_NAME}
  GROUP_CLASS_NAME            = 'Group';
  {$EXTERNALSYM GROUP_CLASS_NAME}
  GLOBALGROUP_CLASS_NAME      = 'GlobalGroup';
  {$EXTERNALSYM GLOBALGROUP_CLASS_NAME}
  LOCALGROUP_CLASS_NAME       = 'LocalGroup';
  {$EXTERNALSYM LOCALGROUP_CLASS_NAME}
  SERVICE_CLASS_NAME          = 'Service';
  {$EXTERNALSYM SERVICE_CLASS_NAME}
  FILESERVICE_CLASS_NAME      = 'FileService';
  {$EXTERNALSYM FILESERVICE_CLASS_NAME}
  SESSION_CLASS_NAME          = 'Session';
  {$EXTERNALSYM SESSION_CLASS_NAME}
  RESOURCE_CLASS_NAME         = 'Resource';
  {$EXTERNALSYM RESOURCE_CLASS_NAME}
  FILESHARE_CLASS_NAME        = 'FileShare';
  {$EXTERNALSYM FILESHARE_CLASS_NAME}
  PRINTER_CLASS_NAME          = 'PrintQueue';
  {$EXTERNALSYM PRINTER_CLASS_NAME}
  PRINTJOB_CLASS_NAME         = 'PrintJob';
  {$EXTERNALSYM PRINTJOB_CLASS_NAME}
  SCHEMA_CLASS_NAME           = 'Schema';
  {$EXTERNALSYM SCHEMA_CLASS_NAME}
  CLASS_CLASS_NAME            = 'Class';
  {$EXTERNALSYM CLASS_CLASS_NAME}
  PROPERTY_CLASS_NAME         = 'Property';
  {$EXTERNALSYM PROPERTY_CLASS_NAME}
  SYNTAX_CLASS_NAME           = 'Syntax';
  {$EXTERNALSYM SYNTAX_CLASS_NAME}
  ROOTDSE_CLASS_NAME          = 'RootDSE';
  {$EXTERNALSYM ROOTDSE_CLASS_NAME}

  NO_SCHEMA                    = '';
  {$EXTERNALSYM NO_SCHEMA}
  DOMAIN_SCHEMA_NAME           = 'Domain';
  {$EXTERNALSYM DOMAIN_SCHEMA_NAME}
  COMPUTER_SCHEMA_NAME         = 'Computer';
  {$EXTERNALSYM COMPUTER_SCHEMA_NAME}
  USER_SCHEMA_NAME             = 'User';
  {$EXTERNALSYM USER_SCHEMA_NAME}
  GROUP_SCHEMA_NAME            = 'Group';
  {$EXTERNALSYM GROUP_SCHEMA_NAME}
  GLOBALGROUP_SCHEMA_NAME      = 'GlobalGroup';
  {$EXTERNALSYM GLOBALGROUP_SCHEMA_NAME}
  LOCALGROUP_SCHEMA_NAME       = 'LocalGroup';
  {$EXTERNALSYM LOCALGROUP_SCHEMA_NAME}
  SERVICE_SCHEMA_NAME          = 'Service';
  {$EXTERNALSYM SERVICE_SCHEMA_NAME}
  PRINTER_SCHEMA_NAME          = 'PrintQueue';
  {$EXTERNALSYM PRINTER_SCHEMA_NAME}
  PRINTJOB_SCHEMA_NAME         = 'PrintJob';
  {$EXTERNALSYM PRINTJOB_SCHEMA_NAME}
  FILESERVICE_SCHEMA_NAME      = 'FileService';
  {$EXTERNALSYM FILESERVICE_SCHEMA_NAME}
  SESSION_SCHEMA_NAME          = 'Session';
  {$EXTERNALSYM SESSION_SCHEMA_NAME}
  RESOURCE_SCHEMA_NAME         = 'Resource';
  {$EXTERNALSYM RESOURCE_SCHEMA_NAME}
  FILESHARE_SCHEMA_NAME        = 'FileShare';
  {$EXTERNALSYM FILESHARE_SCHEMA_NAME}
  FPNW_FILESERVICE_SCHEMA_NAME = 'FPNWFileService';
  {$EXTERNALSYM FPNW_FILESERVICE_SCHEMA_NAME}
  FPNW_SESSION_SCHEMA_NAME     = 'FPNWSession';
  {$EXTERNALSYM FPNW_SESSION_SCHEMA_NAME}
  FPNW_RESOURCE_SCHEMA_NAME    = 'FPNWResource';
  {$EXTERNALSYM FPNW_RESOURCE_SCHEMA_NAME}
  FPNW_FILESHARE_SCHEMA_NAME   = 'FPNWFileShare';
  {$EXTERNALSYM FPNW_FILESHARE_SCHEMA_NAME}

//
// Definitions in the OLE DB provider for ADSI
//

//#include "adsdb.h"

//
// printer status values
//

// Most of the constants have been moved into an enum in adstype.h and
// are available publicly in iads.h. This file has been left here so that
// old references to adsdb.h do not break compiles.

const
  DBPROPFLAGS_ADSISEARCH        = $0000C000;
  {$EXTERNALSYM DBPROPFLAGS_ADSISEARCH}

//#include "adsprop.h"

//  Windows NT Active Directory Service Property Pages
//
//  Contents:   Functions and definitions used in the creation of AD property
//              sheets.

const
  WM_ADSPROP_NOTIFY_PAGEINIT   = (WM_USER + 1101); // where LPARAM is the PADSPROPINITPARAMS pointer.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_PAGEINIT}
  WM_ADSPROP_NOTIFY_PAGEHWND   = (WM_USER + 1102); // where WPARAM => page's HWND
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_PAGEHWND}
  WM_ADSPROP_NOTIFY_CHANGE     = (WM_USER + 1103); // used to send a change notification to a parent sheet
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_CHANGE}
  WM_ADSPROP_NOTIFY_APPLY      = (WM_USER + 1104); // pages send this to the notification object.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_APPLY}
  WM_ADSPROP_NOTIFY_SETFOCUS   = (WM_USER + 1105); // used internally by the notification object.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_SETFOCUS}
  WM_ADSPROP_NOTIFY_FOREGROUND = (WM_USER + 1106); // used internally by the notification object.
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_FOREGROUND}
  WM_ADSPROP_NOTIFY_EXIT       = (WM_USER + 1107); // sent on page release
  {$EXTERNALSYM WM_ADSPROP_NOTIFY_EXIT}

//+----------------------------------------------------------------------------
//
//  Structure:  ADSPROPINITPARAMS
//
//  Usage:      Used to pass page initialization information to new pages from
//              the notify object.
//
//-----------------------------------------------------------------------------

type
  PADSPROPINITPARAMS = ^ADSPROPINITPARAMS;
  {$EXTERNALSYM PADSPROPINITPARAMS}
  _ADSPROPINITPARAMS = record
    dwSize: DWORD;            // Set this to the size of the struct.
    dwFlags: DWORD;           // Reserved for future use.
    hr: HRESULT;              // If this is non-zero, then the others
    pDsObj: IDirectoryObject; // should be ignored.
    pwzCN: LPWSTR;
    pWritableAttrs: PADS_ATTR_INFO;
  end;
  {$EXTERNALSYM _ADSPROPINITPARAMS}
  ADSPROPINITPARAMS = _ADSPROPINITPARAMS;
  {$EXTERNALSYM ADSPROPINITPARAMS}
  TAdsPropInitParams = ADSPROPINITPARAMS;

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropCreateNotifyObj
//
//  Synopsis:   Checks to see if the notification window/object exists for this
//              sheet instance and if not creates it.
//
//  Arguments:  [pAppThdDataObj] - the unmarshalled data object pointer.
//              [pwzADsObjName]  - object path name.
//              [phNotifyObj]    - to return the notificion window handle.
//
//  Returns:    HRESULTs.
//
//-----------------------------------------------------------------------------

function ADsPropCreateNotifyObj(pAppThdDataObj: Pointer; {LPDATAOBJECT}
  pwzADsObjName: PWSTR; var phNotifyObj: HWND): HRESULT; stdcall;
{$EXTERNALSYM ADsPropCreateNotifyObj}

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropGetInitInfo
//
//  Synopsis:   Pages call this at their init time to retreive DS object info.
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [pInitParams] - struct filled in with DS object info. This
//                              struct must be allocated by the caller before
//                              the call.
//
//  Returns:    FALSE if the notify window has gone away for some reason or
//              if the parameters are invalid.
//
//  Notes:      This call results in the sending of the
//              WM_ADSPROP_NOTIFY_PAGEINIT message to the notify window.
//              pInitParams->pWritableAttrs can be NULL if there are no
//              writable attributes.
//
//-----------------------------------------------------------------------------

function ADsPropGetInitInfo(hNotifyObj: HWND; pInitParams: PADSPROPINITPARAMS): BOOL; stdcall;
{$EXTERNALSYM ADsPropGetInitInfo}

//+----------------------------------------------------------------------------
//
//  Function:   ADsPropSetHwnd
//
//  Synopsis:   Pages call this at their dialog init time to send their hwnd.
//
//  Arguments:  [hNotifyObj]  - the notificion window handle.
//              [hPage]       - the page's window handle.
//
//  Returns:    FALSE if the notify window has gone away for some reason.
//
//  Notes:      Sends the WM_ADSPROP_NOTIFY_PAGEHWND message to the notify
//              window.
//
//-----------------------------------------------------------------------------

function ADsPropSetHwnd(hNotifyObj: HWND; hPage: HWND): BOOL; stdcall;
{$EXTERNALSYM ADsPropSetHwnd}

//+----------------------------------------------------------------------------
//
//  function:   ADsPropCheckIfWritable
//
//  Synopsis:   See if the attribute is writable by checking if it is in
//              the allowedAttributesEffective array.
//
//  Arguments:  [pwzAttr]        - the attribute name.
//              [pWritableAttrs] - the array of writable attributes.
//
//  Returns:    FALSE if the attribute name is not found in the writable-attrs
//              array or if the array pointer is NULL.
//
//-----------------------------------------------------------------------------

function ADsPropCheckIfWritable(pwzAttr: PWSTR; pWritableAttrs: PADS_ATTR_INFO): BOOL; stdcall;
{$EXTERNALSYM ADsPropCheckIfWritable}

implementation

const
  adslib = 'activeds.dll';
  dsprop = 'dsprop.dll';

// adshlp.h


{$IFDEF DYNAMIC_LINK}
var
  _ADsGetObject: Pointer;

function ADsGetObject;
begin
  GetProcedureAddress(_ADsGetObject, adslib, 'ADsGetObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsGetObject]
  end;
end;
{$ELSE}
function ADsGetObject; external adslib name 'ADsGetObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsBuildEnumerator: Pointer;

function ADsBuildEnumerator;
begin
  GetProcedureAddress(_ADsBuildEnumerator, adslib, 'ADsBuildEnumerator');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsBuildEnumerator]
  end;
end;
{$ELSE}
function ADsBuildEnumerator; external adslib name 'ADsBuildEnumerator';
{$ENDIF DYNAMIC_LINK}

function _ADsFreeEnumerator(pEnumVariant: IEnumVARIANT): HRESULT; stdcall; external adslib name 'ADsFreeEnumerator';

function ADsFreeEnumerator(var pEnumVariant: IEnumVARIANT): HRESULT;
begin
  Result := _ADsFreeEnumerator(pEnumVariant);
  // ADsFreeEnumerator doesn't set pEnumVariant to nil causing Delphi to call
  // Release() again when pEnumVariant leaves scope. Result would be an access
  // violation, explicitly setting the interface to nil prevents this.
  if Result = 0{S_OK} then Pointer(pEnumVariant) := nil;
end;


{$IFDEF DYNAMIC_LINK}
var
  _ADsEnumerateNext: Pointer;

function ADsEnumerateNext;
begin
  GetProcedureAddress(_ADsEnumerateNext, adslib, 'ADsEnumerateNext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsEnumerateNext]
  end;
end;
{$ELSE}
function ADsEnumerateNext; external adslib name 'ADsEnumerateNext';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsBuildVarArrayStr: Pointer;

function ADsBuildVarArrayStr;
begin
  GetProcedureAddress(_ADsBuildVarArrayStr, adslib, 'ADsBuildVarArrayStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsBuildVarArrayStr]
  end;
end;
{$ELSE}
function ADsBuildVarArrayStr; external adslib name 'ADsBuildVarArrayStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsBuildVarArrayInt: Pointer;

function ADsBuildVarArrayInt;
begin
  GetProcedureAddress(_ADsBuildVarArrayInt, adslib, 'ADsBuildVarArrayInt');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsBuildVarArrayInt]
  end;
end;
{$ELSE}
function ADsBuildVarArrayInt; external adslib name 'ADsBuildVarArrayInt';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsOpenObject: Pointer;

function ADsOpenObject;
begin
  GetProcedureAddress(_ADsOpenObject, adslib, 'ADsOpenObject');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsOpenObject]
  end;
end;
{$ELSE}
function ADsOpenObject; external adslib name 'ADsOpenObject';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsGetLastError: Pointer;

function ADsGetLastError;
begin
  GetProcedureAddress(_ADsGetLastError, adslib, 'ADsGetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsGetLastError]
  end;
end;
{$ELSE}
function ADsGetLastError; external adslib name 'ADsGetLastError';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsSetLastError: Pointer;

procedure ADsSetLastError;
begin
  GetProcedureAddress(_ADsSetLastError, adslib, 'ADsSetLastError');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsSetLastError]
  end;
end;
{$ELSE}
procedure ADsSetLastError; external adslib name 'ADsSetLastError';
{$ENDIF DYNAMIC_LINK}
//procedure ADsFreeAllErrorRecords

{$IFDEF DYNAMIC_LINK}
var
  _AllocADsMem: Pointer;

function AllocADsMem;
begin
  GetProcedureAddress(_AllocADsMem, adslib, 'AllocADsMem');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AllocADsMem]
  end;
end;
{$ELSE}
function AllocADsMem; external adslib name 'AllocADsMem';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FreeADsMem: Pointer;

function FreeADsMem;
begin
  GetProcedureAddress(_FreeADsMem, adslib, 'FreeADsMem');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeADsMem]
  end;
end;
{$ELSE}
function FreeADsMem; external adslib name 'FreeADsMem';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReallocADsMem: Pointer;

function ReallocADsMem;
begin
  GetProcedureAddress(_ReallocADsMem, adslib, 'ReallocADsMem');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReallocADsMem]
  end;
end;
{$ELSE}
function ReallocADsMem; external adslib name 'ReallocADsMem';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AllocADsStr: Pointer;

function AllocADsStr;
begin
  GetProcedureAddress(_AllocADsStr, adslib, 'AllocADsStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AllocADsStr]
  end;
end;
{$ELSE}
function AllocADsStr; external adslib name 'AllocADsStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _FreeADsStr: Pointer;

function FreeADsStr;
begin
  GetProcedureAddress(_FreeADsStr, adslib, 'FreeADsStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_FreeADsStr]
  end;
end;
{$ELSE}
function FreeADsStr; external adslib name 'FreeADsStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ReallocADsStr: Pointer;

function ReallocADsStr;
begin
  GetProcedureAddress(_ReallocADsStr, adslib, 'ReallocADsStr');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ReallocADsStr]
  end;
end;
{$ELSE}
function ReallocADsStr; external adslib name 'ReallocADsStr';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsEncodeBinaryData: Pointer;

function ADsEncodeBinaryData;
begin
  GetProcedureAddress(_ADsEncodeBinaryData, adslib, 'ADsEncodeBinaryData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsEncodeBinaryData]
  end;
end;
{$ELSE}
function ADsEncodeBinaryData; external adslib name 'ADsEncodeBinaryData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsDecodeBinaryData: Pointer;

function ADsDecodeBinaryData;
begin
  GetProcedureAddress(_ADsDecodeBinaryData, adslib, 'ADsDecodeBinaryData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsDecodeBinaryData]
  end;
end;
{$ELSE}
function ADsDecodeBinaryData; external adslib name 'ADsDecodeBinaryData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PropVariantToAdsType: Pointer;

function PropVariantToAdsType;
begin
  GetProcedureAddress(_PropVariantToAdsType, adslib, 'PropVariantToAdsType');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PropVariantToAdsType]
  end;
end;
{$ELSE}
function PropVariantToAdsType; external adslib name 'PropVariantToAdsType';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AdsTypeToPropVariant: Pointer;

function AdsTypeToPropVariant;
begin
  GetProcedureAddress(_AdsTypeToPropVariant, adslib, 'AdsTypeToPropVariant');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AdsTypeToPropVariant]
  end;
end;
{$ELSE}
function AdsTypeToPropVariant; external adslib name 'AdsTypeToPropVariant';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _AdsFreeAdsValues: Pointer;

procedure AdsFreeAdsValues;
begin
  GetProcedureAddress(_AdsFreeAdsValues, adslib, 'AdsFreeAdsValues');
  asm
    mov esp, ebp
    pop ebp
    jmp [_AdsFreeAdsValues]
  end;
end;
{$ELSE}
procedure AdsFreeAdsValues; external adslib name 'AdsFreeAdsValues';
{$ENDIF DYNAMIC_LINK}

// adsprop.h


{$IFDEF DYNAMIC_LINK}
var
  _ADsPropCreateNotifyObj: Pointer;

function ADsPropCreateNotifyObj;
begin
  GetProcedureAddress(_ADsPropCreateNotifyObj, dsprop, 'ADsPropCreateNotifyObj');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropCreateNotifyObj]
  end;
end;
{$ELSE}
function ADsPropCreateNotifyObj; external dsprop name 'ADsPropCreateNotifyObj';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropGetInitInfo: Pointer;

function ADsPropGetInitInfo;
begin
  GetProcedureAddress(_ADsPropGetInitInfo, dsprop, 'ADsPropGetInitInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropGetInitInfo]
  end;
end;
{$ELSE}
function ADsPropGetInitInfo; external dsprop name 'ADsPropGetInitInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropSetHwnd: Pointer;

function ADsPropSetHwnd;
begin
  GetProcedureAddress(_ADsPropSetHwnd, dsprop, 'ADsPropSetHwnd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropSetHwnd]
  end;
end;
{$ELSE}
function ADsPropSetHwnd; external dsprop name 'ADsPropSetHwnd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _ADsPropCheckIfWritable: Pointer;

function ADsPropCheckIfWritable;
begin
  GetProcedureAddress(_ADsPropCheckIfWritable, dsprop, 'ADsPropCheckIfWritable');
  asm
    mov esp, ebp
    pop ebp
    jmp [_ADsPropCheckIfWritable]
  end;
end;
{$ELSE}
function ADsPropCheckIfWritable; external dsprop name 'ADsPropCheckIfWritable';
{$ENDIF DYNAMIC_LINK}

end.
