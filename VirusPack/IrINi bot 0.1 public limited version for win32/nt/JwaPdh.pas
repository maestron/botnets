{******************************************************************************}
{                                                       	               }
{ Performance Data Helper API interface Unit for Object Pascal                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: pdh.h, released June 2000. The original Pascal         }
{ code is: Pdh.pas, released December 2000. The initial developer of the       }
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

unit JwaPdh;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "pdh.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinBase, JwaWinType, JwaWinPerf;

type
  PDH_STATUS = DWORD;
  {$EXTERNALSYM PDH_STATUS}

const

// version info

  PDH_CVERSION_WIN40 = DWORD($0400);
  {$EXTERNALSYM PDH_CVERSION_WIN40}
  PDH_CVERSION_WIN50 = DWORD($0500);
  {$EXTERNALSYM PDH_CVERSION_WIN50}

// v1.1 revision of PDH -- basic log functions
// v1.2 of the PDH -- adds variable instance counters
// v1.3 of the PDH -- adds log service control & stubs for NT5/PDH v2 fn's
// v2.0 of the PDH -- is the NT v 5.0 B2 version

  PDH_VERSION        = DWORD((PDH_CVERSION_WIN50) + $0003);
  {$EXTERNALSYM PDH_VERSION}

// define severity masks

function IsSuccessSeverity(ErrorCode: Longint): Boolean;
{$EXTERNALSYM IsSuccessSeverity}
function IsInformationalSeverity(ErrorCode: Longint): Boolean;
{$EXTERNALSYM IsInformationalSeverity}
function IsWarningSeverity(ErrorCode: Longint): Boolean;
{$EXTERNALSYM IsWarningSeverity}
function IsErrorSeverity(ErrorCode: Longint): Boolean;
{$EXTERNALSYM IsErrorSeverity}

const
  MAX_COUNTER_PATH = 256;         // Maximum counter path length
  {$EXTERNALSYM MAX_COUNTER_PATH}

  PDH_MAX_COUNTER_NAME    = 1024;  // Maximum counter name length.
  {$EXTERNALSYM PDH_MAX_COUNTER_NAME}
  PDH_MAX_INSTANCE_NAME   = 1024;  // Maximum counter instance name length.
  {$EXTERNALSYM PDH_MAX_INSTANCE_NAME}
  PDH_MAX_COUNTER_PATH    = 2048;  // Maximum full counter path length.
  {$EXTERNALSYM PDH_MAX_COUNTER_PATH}
  PDH_MAX_DATASOURCE_PATH = 1024;  // MAximum full counter log name length.
  {$EXTERNALSYM PDH_MAX_DATASOURCE_PATH}

// data type definitions

type
  PDH_HCOUNTER = HANDLE;
  {$EXTERNALSYM PDH_HCOUNTER}
  PDH_HQUERY = HANDLE;
  {$EXTERNALSYM PDH_HQUERY}
  PDH_HLOG = HANDLE;
  {$EXTERNALSYM PDH_HLOG}

  HCOUNTER = PDH_HCOUNTER;
  {$EXTERNALSYM HCOUNTER}
  HQUERY = PDH_HQUERY;
  {$EXTERNALSYM HQUERY}
  HLOG = PDH_HLOG;
  {$EXTERNALSYM HLOG}

const
  INVALID_HANDLE_VALUE = HANDLE(LONG_PTR(-1));
  {$EXTERNALSYM INVALID_HANDLE_VALUE}

  H_REALTIME_DATASOURCE = NULL;
  {$EXTERNALSYM H_REALTIME_DATASOURCE}
  H_WBEM_DATASOURCE     = INVALID_HANDLE_VALUE;
  {$EXTERNALSYM H_WBEM_DATASOURCE}

type
  PPDH_RAW_COUNTER = ^PDH_RAW_COUNTER;
  {$EXTERNALSYM PPDH_RAW_COUNTER}
  _PDH_RAW_COUNTER = record
    CStatus: DWORD;
    TimeStamp: FILETIME;
    FirstValue: LONGLONG;
    SecondValue: LONGLONG;
    MultiCount: DWORD;
  end;
  {$EXTERNALSYM _PDH_RAW_COUNTER}
  PDH_RAW_COUNTER = _PDH_RAW_COUNTER;
  {$EXTERNALSYM PDH_RAW_COUNTER}
  TPdhRawCounter = PDH_RAW_COUNTER;
  PPdhRawCounter = PPDH_RAW_COUNTER;

  PPDH_RAW_COUNTER_ITEM_A = ^PDH_RAW_COUNTER_ITEM_A;
  {$EXTERNALSYM PPDH_RAW_COUNTER_ITEM_A}
  _PDH_RAW_COUNTER_ITEM_A = record
    szName: LPSTR;
    RawValue: PDH_RAW_COUNTER;
  end;
  {$EXTERNALSYM _PDH_RAW_COUNTER_ITEM_A}
  PDH_RAW_COUNTER_ITEM_A = _PDH_RAW_COUNTER_ITEM_A;
  {$EXTERNALSYM PDH_RAW_COUNTER_ITEM_A}
  TPdhRawCounterItemA = PDH_RAW_COUNTER_ITEM_A;
  PPdhRawCounterItemA = PPDH_RAW_COUNTER_ITEM_A;

  PPDH_RAW_COUNTER_ITEM_W = ^PDH_RAW_COUNTER_ITEM_W;
  {$EXTERNALSYM PPDH_RAW_COUNTER_ITEM_W}
  _PDH_RAW_COUNTER_ITEM_W = record
    szName: LPWSTR;
    RawValue: PDH_RAW_COUNTER;
  end;
  {$EXTERNALSYM _PDH_RAW_COUNTER_ITEM_W}
  PDH_RAW_COUNTER_ITEM_W = _PDH_RAW_COUNTER_ITEM_W;
  {$EXTERNALSYM PDH_RAW_COUNTER_ITEM_W}
  TPdhRawCounterItemW = PDH_RAW_COUNTER_ITEM_W;
  PPdhRawCounterItemW = PPDH_RAW_COUNTER_ITEM_W;

{$IFDEF UNICODE}
  PPdhRawCounterItem = PPdhRawCounterItemW;
  PDH_RAW_COUNTER_ITEM = _PDH_RAW_COUNTER_ITEM_W;
  {$EXTERNALSYM PDH_RAW_COUNTER_ITEM}
  PPDH_RAW_COUNTER_ITEM = PPDH_RAW_COUNTER_ITEM_W;
  {$EXTERNALSYM PPDH_RAW_COUNTER_ITEM}
  TPdhRawCounterItem = _PDH_RAW_COUNTER_ITEM_W;
{$ELSE}
  PPdhRawCounterItem = PPdhRawCounterItemA;
  PDH_RAW_COUNTER_ITEM = _PDH_RAW_COUNTER_ITEM_A;
  {$EXTERNALSYM PDH_RAW_COUNTER_ITEM}
  PPDH_RAW_COUNTER_ITEM = PPDH_RAW_COUNTER_ITEM_A;
  {$EXTERNALSYM PPDH_RAW_COUNTER_ITEM}
  TPdhRawCounterItem = _PDH_RAW_COUNTER_ITEM_A;
{$ENDIF}

  PPDH_FMT_COUNTERVALUE = ^PDH_FMT_COUNTERVALUE;
  {$EXTERNALSYM PPDH_FMT_COUNTERVALUE}
  _PDH_FMT_COUNTERVALUE = record
    CStatus: DWORD;
    case Longint of
      1: (longValue: LONG);
      2: (doubleValue: Double);
      3: (largeValue: LONGLONG);
      4: (AnsiStringValue: LPSTR);
      5: (WideStringValue: LPCWSTR);
  end;
  {$EXTERNALSYM _PDH_FMT_COUNTERVALUE}
  PDH_FMT_COUNTERVALUE = _PDH_FMT_COUNTERVALUE;
  {$EXTERNALSYM PDH_FMT_COUNTERVALUE}
  TPdhFmtCounterValue = PDH_FMT_COUNTERVALUE;
  PPdhFmtCounterValue = PPDH_FMT_COUNTERVALUE;

  PPDH_FMT_COUNTERVALUE_ITEM_A = ^PDH_FMT_COUNTERVALUE_ITEM_A;
  {$EXTERNALSYM PPDH_FMT_COUNTERVALUE_ITEM_A}
  _PDH_FMT_COUNTERVALUE_ITEM_A = record
    szName: LPSTR;
    FmtValue: PDH_FMT_COUNTERVALUE;
  end;
  {$EXTERNALSYM _PDH_FMT_COUNTERVALUE_ITEM_A}
  PDH_FMT_COUNTERVALUE_ITEM_A = _PDH_FMT_COUNTERVALUE_ITEM_A;
  {$EXTERNALSYM PDH_FMT_COUNTERVALUE_ITEM_A}
  TPdhFmtCounterValueItemA = PDH_FMT_COUNTERVALUE_ITEM_A;
  PPdhFmtCounterValueItemA = PPDH_FMT_COUNTERVALUE_ITEM_A;

  PPDH_FMT_COUNTERVALUE_ITEM_W = ^PDH_FMT_COUNTERVALUE_ITEM_W;
  {$EXTERNALSYM PPDH_FMT_COUNTERVALUE_ITEM_W}
  _PDH_FMT_COUNTERVALUE_ITEM_W = record
    szName: LPWSTR;
    FmtValue: PDH_FMT_COUNTERVALUE;
  end;
  {$EXTERNALSYM _PDH_FMT_COUNTERVALUE_ITEM_W}
  PDH_FMT_COUNTERVALUE_ITEM_W = _PDH_FMT_COUNTERVALUE_ITEM_W;
  {$EXTERNALSYM PDH_FMT_COUNTERVALUE_ITEM_W}
  TPdhFmtCounterValueItemW = PDH_FMT_COUNTERVALUE_ITEM_W;
  PPdhFmtCounterValueItemW = PPDH_FMT_COUNTERVALUE_ITEM_W;

{$IFDEF UNICODE}
  PPdhFmtCounterValueItem = PPdhFmtCounterValueItemW;
  PDH_FMT_COUNTERVALUE_ITEM = _PDH_FMT_COUNTERVALUE_ITEM_W;
  {$EXTERNALSYM PDH_FMT_COUNTERVALUE_ITEM}
  PPDH_FMT_COUNTERVALUE_ITEM = PPDH_FMT_COUNTERVALUE_ITEM_W;
  {$EXTERNALSYM PPDH_FMT_COUNTERVALUE_ITEM}
  TPdhFmtCounterValueItem = _PDH_FMT_COUNTERVALUE_ITEM_W;
{$ELSE}
  PPdhFmtCounterValueItem = PPdhFmtCounterValueItemA;
  PDH_FMT_COUNTERVALUE_ITEM = _PDH_FMT_COUNTERVALUE_ITEM_A;
  {$EXTERNALSYM PDH_FMT_COUNTERVALUE_ITEM}
  PPDH_FMT_COUNTERVALUE_ITEM = PPDH_FMT_COUNTERVALUE_ITEM_A;
  {$EXTERNALSYM PPDH_FMT_COUNTERVALUE_ITEM}
  TPdhFmtCounterValueItem = _PDH_FMT_COUNTERVALUE_ITEM_A;
{$ENDIF}

  PPDH_STATISTICS = ^PDH_STATISTICS;
  {$EXTERNALSYM PPDH_STATISTICS}
  _PDH_STATISTICS = record
    dwFormat: DWORD;
    Count: DWORD;
    min: PDH_FMT_COUNTERVALUE;
    max: PDH_FMT_COUNTERVALUE;
    mean: PDH_FMT_COUNTERVALUE;
  end;
  {$EXTERNALSYM _PDH_STATISTICS}
  PDH_STATISTICS = _PDH_STATISTICS;
  {$EXTERNALSYM PDH_STATISTICS}
  TPdhStatistics = PDH_STATISTICS;
  PPdhStatistics = PPDH_STATISTICS;

  PPDH_COUNTER_PATH_ELEMENTS_A = ^PDH_COUNTER_PATH_ELEMENTS_A;
  {$EXTERNALSYM PPDH_COUNTER_PATH_ELEMENTS_A}
  _PDH_COUNTER_PATH_ELEMENTS_A = record
    szMachineName: LPSTR;
    szObjectName: LPSTR;
    szInstanceName: LPSTR;
    szParentInstance: LPSTR;
    dwInstanceIndex: DWORD;
    szCounterName: LPSTR;
  end;
  {$EXTERNALSYM _PDH_COUNTER_PATH_ELEMENTS_A}
  PDH_COUNTER_PATH_ELEMENTS_A = _PDH_COUNTER_PATH_ELEMENTS_A;
  {$EXTERNALSYM PDH_COUNTER_PATH_ELEMENTS_A}
  TPdhCounterPathElementsA = PDH_COUNTER_PATH_ELEMENTS_A;
  PPdhCounterPathElementsA = PPDH_COUNTER_PATH_ELEMENTS_A;

  PPDH_COUNTER_PATH_ELEMENTS_W = ^PDH_COUNTER_PATH_ELEMENTS_W;
  {$EXTERNALSYM PPDH_COUNTER_PATH_ELEMENTS_W}
  _PDH_COUNTER_PATH_ELEMENTS_W = record
    szMachineName: LPWSTR;
    szObjectName: LPWSTR;
    szInstanceName: LPWSTR;
    szParentInstance: LPWSTR;
    dwInstanceIndex: DWORD;
    szCounterName: LPWSTR;
  end;
  {$EXTERNALSYM _PDH_COUNTER_PATH_ELEMENTS_W}
  PDH_COUNTER_PATH_ELEMENTS_W = _PDH_COUNTER_PATH_ELEMENTS_W;
  {$EXTERNALSYM PDH_COUNTER_PATH_ELEMENTS_W}
  TPdhCounterPathElementsW = PDH_COUNTER_PATH_ELEMENTS_W;
  PPdhCounterPathElementsW = PPDH_COUNTER_PATH_ELEMENTS_W;

{$IFDEF UNICODE}
  PPdhCounterPathElements = PPdhCounterPathElementsW;
  PDH_COUNTER_PATH_ELEMENTS = _PDH_COUNTER_PATH_ELEMENTS_W;
  {$EXTERNALSYM PDH_COUNTER_PATH_ELEMENTS}
  PPDH_COUNTER_PATH_ELEMENTS = PPDH_COUNTER_PATH_ELEMENTS_W;
  {$EXTERNALSYM PPDH_COUNTER_PATH_ELEMENTS}
  TPdhCounterPathElements = _PDH_COUNTER_PATH_ELEMENTS_W;
{$ELSE}
  PPdhCounterPathElements = PPdhCounterPathElementsA;
  PDH_COUNTER_PATH_ELEMENTS = _PDH_COUNTER_PATH_ELEMENTS_A;
  {$EXTERNALSYM PDH_COUNTER_PATH_ELEMENTS}
  PPDH_COUNTER_PATH_ELEMENTS = PPDH_COUNTER_PATH_ELEMENTS_A;
  {$EXTERNALSYM PPDH_COUNTER_PATH_ELEMENTS}
  TPdhCounterPathElements = _PDH_COUNTER_PATH_ELEMENTS_A;
{$ENDIF}

  PPDH_DATA_ITEM_PATH_ELEMENTS_A = ^PDH_DATA_ITEM_PATH_ELEMENTS_A;
  {$EXTERNALSYM PPDH_DATA_ITEM_PATH_ELEMENTS_A}
  _PDH_DATA_ITEM_PATH_ELEMENTS_A = record
    szMachineName: LPSTR;
    ObjectGUID: GUID;
    dwItemId: DWORD;
    szInstanceName: LPSTR;
  end;
  {$EXTERNALSYM _PDH_DATA_ITEM_PATH_ELEMENTS_A}
  PDH_DATA_ITEM_PATH_ELEMENTS_A = _PDH_DATA_ITEM_PATH_ELEMENTS_A;
  {$EXTERNALSYM PDH_DATA_ITEM_PATH_ELEMENTS_A}
  TPdhDataItemPathElementsA = PDH_DATA_ITEM_PATH_ELEMENTS_A;
  PPdhDataItemPathElementsA = PPDH_DATA_ITEM_PATH_ELEMENTS_A;

  PPDH_DATA_ITEM_PATH_ELEMENTS_W = ^PDH_DATA_ITEM_PATH_ELEMENTS_W;
  {$EXTERNALSYM PPDH_DATA_ITEM_PATH_ELEMENTS_W}
  _PDH_DATA_ITEM_PATH_ELEMENTS_W = record
    szMachineName: LPWSTR;
    ObjectGUID: GUID;
    dwItemId: DWORD;
    szInstanceName: LPWSTR;
  end;
  {$EXTERNALSYM _PDH_DATA_ITEM_PATH_ELEMENTS_W}
  PDH_DATA_ITEM_PATH_ELEMENTS_W = _PDH_DATA_ITEM_PATH_ELEMENTS_W;
  {$EXTERNALSYM PDH_DATA_ITEM_PATH_ELEMENTS_W}
  TPdhDataItemPathElementsW = PDH_DATA_ITEM_PATH_ELEMENTS_W;
  PPdhDataItemPathElementsW = PPDH_DATA_ITEM_PATH_ELEMENTS_W;

{$IFDEF UNICODE}
  PPdhDataItemPathElements = PPdhDataItemPathElementsW;
  PDH_DATA_ITEM_PATH_ELEMENTS = _PDH_DATA_ITEM_PATH_ELEMENTS_W;
  {$EXTERNALSYM PDH_DATA_ITEM_PATH_ELEMENTS}
  PPDH_DATA_ITEM_PATH_ELEMENTS = PPDH_DATA_ITEM_PATH_ELEMENTS_W;
  {$EXTERNALSYM PPDH_DATA_ITEM_PATH_ELEMENTS}
  TPdhDataItemPathElements = _PDH_DATA_ITEM_PATH_ELEMENTS_W;
{$ELSE}
  PPdhDataItemPathElements = PPdhDataItemPathElementsA;
  PDH_DATA_ITEM_PATH_ELEMENTS = _PDH_DATA_ITEM_PATH_ELEMENTS_A;
  {$EXTERNALSYM PDH_DATA_ITEM_PATH_ELEMENTS}
  PPDH_DATA_ITEM_PATH_ELEMENTS = PPDH_DATA_ITEM_PATH_ELEMENTS_A;
  {$EXTERNALSYM PPDH_DATA_ITEM_PATH_ELEMENTS}
  TPdhDataItemPathElements = _PDH_DATA_ITEM_PATH_ELEMENTS_A;
{$ENDIF}

  PPDH_COUNTER_INFO_A = ^PDH_COUNTER_INFO_A;
  {$EXTERNALSYM PPDH_COUNTER_INFO_A}
  _PDH_COUNTER_INFO_A = record
    dwLength: DWORD;
    dwType: DWORD;
    CVersion: DWORD;
    CStatus: DWORD;
    lScale: LONG;
    lDefaultScale: LONG;
    dwUserData: DWORD_PTR;
    dwQueryUserData: DWORD_PTR;
    szFullPath: LPSTR;
    Union: record
      case Longint of
        1: (DataItemPath: PDH_DATA_ITEM_PATH_ELEMENTS_A);
        2: (CounterPath: PDH_COUNTER_PATH_ELEMENTS_A);
        3: (szMachineName: LPSTR;
            szObjectName: LPSTR;
            szInstanceName: LPSTR;
            szParentInstance: LPSTR;
            dwInstanceIndex: DWORD;
            szCounterName: LPSTR);
    end;
    szExplainText: LPSTR;
    DataBuffer: array [0..0] of DWORD;
  end;
  {$EXTERNALSYM _PDH_COUNTER_INFO_A}
  PDH_COUNTER_INFO_A = _PDH_COUNTER_INFO_A;
  {$EXTERNALSYM PDH_COUNTER_INFO_A}
  TPdhCounterInfoA = PDH_COUNTER_INFO_A;
  PPdhCounterInfoA = PPDH_COUNTER_INFO_A;

  PPDH_COUNTER_INFO_W = ^PDH_COUNTER_INFO_W;
  {$EXTERNALSYM PPDH_COUNTER_INFO_W}
  _PDH_COUNTER_INFO_W = record
    dwLength: DWORD;
    dwType: DWORD;
    CVersion: DWORD;
    CStatus: DWORD;
    lScale: LONG;
    lDefaultScale: LONG;
    dwUserData: DWORD_PTR;
    dwQueryUserData: DWORD_PTR;
    szFullPath: LPWSTR;
    Union: record
      case Longint of
        1: (DataItemPath: PDH_DATA_ITEM_PATH_ELEMENTS_W);
        2: (CounterPath: PDH_COUNTER_PATH_ELEMENTS_W);
        3: (szMachineName: LPWSTR;
            szObjectName: LPWSTR;
            szInstanceName: LPWSTR;
            szParentInstance: LPWSTR;
            dwInstanceIndex: DWORD;
            szCounterName: LPWSTR);
    end;
    szExplainText: LPWSTR;
    DataBuffer: array [0..0] of DWORD;
  end;
  {$EXTERNALSYM _PDH_COUNTER_INFO_W}
  PDH_COUNTER_INFO_W = _PDH_COUNTER_INFO_W;
  {$EXTERNALSYM PDH_COUNTER_INFO_W}
  TPdhCounterInfoW = PDH_COUNTER_INFO_W;
  PPdhCounterInfoW = PPDH_COUNTER_INFO_W;

{$IFDEF UNICODE}
  PPdhCounterInfo = PPdhCounterInfoW;
  PDH_COUNTER_INFO = _PDH_COUNTER_INFO_W;
  {$EXTERNALSYM PDH_COUNTER_INFO}
  PPDH_COUNTER_INFO = PPDH_COUNTER_INFO_W;
  {$EXTERNALSYM PPDH_COUNTER_INFO}
  TPdhCounterInfo = _PDH_COUNTER_INFO_W;
{$ELSE}
  PPdhCounterInfo = PPdhCounterInfoA;
  PDH_COUNTER_INFO = _PDH_COUNTER_INFO_A;
  {$EXTERNALSYM PDH_COUNTER_INFO}
  PPDH_COUNTER_INFO = PPDH_COUNTER_INFO_A;
  {$EXTERNALSYM PPDH_COUNTER_INFO}
  TPdhCounterInfo = _PDH_COUNTER_INFO_A;
{$ENDIF}

  PPDH_TIME_INFO = ^PDH_TIME_INFO;
  {$EXTERNALSYM PPDH_TIME_INFO}
  _PDH_TIME_INFO = record
    StartTime: LONGLONG;
    EndTime: LONGLONG;
    SampleCount: DWORD;
  end;
  {$EXTERNALSYM _PDH_TIME_INFO}
  PDH_TIME_INFO = _PDH_TIME_INFO;
  {$EXTERNALSYM PDH_TIME_INFO}
  TPdhTimeInfo = PDH_TIME_INFO;
  PPdhTimeInfo = PPDH_TIME_INFO;

  PPDH_RAW_LOG_RECORD = ^PDH_RAW_LOG_RECORD;
  {$EXTERNALSYM PPDH_RAW_LOG_RECORD}
  _PDH_RAW_LOG_RECORD = record
    dwStructureSize: DWORD;
    dwRecordType: DWORD;
    dwItems: DWORD;
    RawBytes: array [0..0] of UCHAR;
  end;
  {$EXTERNALSYM _PDH_RAW_LOG_RECORD}
  PDH_RAW_LOG_RECORD = _PDH_RAW_LOG_RECORD;
  {$EXTERNALSYM PDH_RAW_LOG_RECORD}
  TPdhRawLogRecord = PDH_RAW_LOG_RECORD;
  PPdhRawLogRecord = PPDH_RAW_LOG_RECORD;

  PPDH_LOG_SERVICE_QUERY_INFO_A = ^PDH_LOG_SERVICE_QUERY_INFO_A;
  {$EXTERNALSYM PPDH_LOG_SERVICE_QUERY_INFO_A}
  _PDH_LOG_SERVICE_QUERY_INFO_A = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwLogQuota: DWORD;
    szLogFileCaption: LPSTR;
    szDefaultDir: LPSTR;
    szBaseFileName: LPSTR;
    dwFileType: DWORD;
    dwReserved: DWORD;
    Union: record
      case Longint of
      1: (PdlAutoNameInterval: DWORD;
          PdlAutoNameUnits: DWORD;
          PdlCommandFilename: LPSTR;
          PdlCounterList: LPSTR;
          PdlAutoNameFormat: DWORD;
          PdlSampleInterval: DWORD;
          PdlLogStartTime: FILETIME;
          PdlLogEndTime: FILETIME);
      2: (TlNumberOfBuffers: DWORD;
          TlMinimumBuffers: DWORD;
          TlMaximumBuffers: DWORD;
          TlFreeBuffers: DWORD;
          TlBufferSize: DWORD;
          TlEventsLost: DWORD;
          TlLoggerThreadId: DWORD;
          TlBuffersWritten: DWORD;
          TlLogHandle: DWORD;
          TlLogFileName: LPSTR);
    end;
  end;
  {$EXTERNALSYM _PDH_LOG_SERVICE_QUERY_INFO_A}
  PDH_LOG_SERVICE_QUERY_INFO_A = _PDH_LOG_SERVICE_QUERY_INFO_A;
  {$EXTERNALSYM _PDH_LOG_SERVICE_QUERY_INFO_A}
  TPdhLogServiceQueryInfoA = PDH_LOG_SERVICE_QUERY_INFO_A;
  PPdhLogServiceQueryInfoA = PPDH_LOG_SERVICE_QUERY_INFO_A;

  PPDH_LOG_SERVICE_QUERY_INFO_W = ^PDH_LOG_SERVICE_QUERY_INFO_W;
  {$EXTERNALSYM PPDH_LOG_SERVICE_QUERY_INFO_W}
  _PDH_LOG_SERVICE_QUERY_INFO_W = record
    dwSize: DWORD;
    dwFlags: DWORD;
    dwLogQuota: DWORD;
    szLogFileCaption: LPWSTR;
    szDefaultDir: LPWSTR;
    szBaseFileName: LPWSTR;
    dwFileType: DWORD;
    dwReserved: DWORD;
    Union: record
      case Longint of
      1: (PdlAutoNameInterval: DWORD;
          PdlAutoNameUnits: DWORD;
          PdlCommandFilename: LPWSTR;
          PdlCounterList: LPWSTR;
          PdlAutoNameFormat: DWORD;
          PdlSampleInterval: DWORD;
          PdlLogStartTime: FILETIME;
          PdlLogEndTime: FILETIME);
      2: (TlNumberOfBuffers: DWORD;
          TlMinimumBuffers: DWORD;
          TlMaximumBuffers: DWORD;
          TlFreeBuffers: DWORD;
          TlBufferSize: DWORD;
          TlEventsLost: DWORD;
          TlLoggerThreadId: DWORD;
          TlBuffersWritten: DWORD;
          TlLogHandle: DWORD;
          TlLogFileName: LPWSTR);
    end;
  end;
  {$EXTERNALSYM _PDH_LOG_SERVICE_QUERY_INFO_W}
  PDH_LOG_SERVICE_QUERY_INFO_W = _PDH_LOG_SERVICE_QUERY_INFO_W;
  {$EXTERNALSYM PDH_LOG_SERVICE_QUERY_INFO_W}
  TPdhLogServiceQueryInfoW = PDH_LOG_SERVICE_QUERY_INFO_W;
  PPdhLogServiceQueryInfoW = PPDH_LOG_SERVICE_QUERY_INFO_W;

{$IFDEF UNICODE}
  PPdhLogServiceQueryInfo = PPdhLogServiceQueryInfoW;
  PDH_LOG_SERVICE_QUERY_INFO = _PDH_LOG_SERVICE_QUERY_INFO_W;
  {$EXTERNALSYM PDH_LOG_SERVICE_QUERY_INFO}
  PPDH_LOG_SERVICE_QUERY_INFO = PPDH_LOG_SERVICE_QUERY_INFO_W;
  {$EXTERNALSYM PPDH_LOG_SERVICE_QUERY_INFO}
  TPdhLogServiceQueryInfo = _PDH_LOG_SERVICE_QUERY_INFO_W;
{$ELSE}
  PPdhLogServiceQueryInfo = PPdhLogServiceQueryInfoA;
  PDH_LOG_SERVICE_QUERY_INFO = _PDH_LOG_SERVICE_QUERY_INFO_A;
  {$EXTERNALSYM PDH_LOG_SERVICE_QUERY_INFO}
  PPDH_LOG_SERVICE_QUERY_INFO = PPDH_LOG_SERVICE_QUERY_INFO_A;
  {$EXTERNALSYM PPDH_LOG_SERVICE_QUERY_INFO}
  TPdhLogServiceQueryInfo = _PDH_LOG_SERVICE_QUERY_INFO_A;
{$ENDIF}

//
//  Time value constants
//

const
  MAX_TIME_VALUE = LONGLONG($7FFFFFFFFFFFFFFF);
  {$EXTERNALSYM MAX_TIME_VALUE}
  MIN_TIME_VALUE = LONGLONG(0);
  {$EXTERNALSYM MIN_TIME_VALUE}

// function definitions

function PdhGetDllVersion(var lpdwVersion: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDllVersion}

//
//  Query Functions
//

function PdhOpenQueryA(szDataSource: LPCSTR; dwUserData: DWORD_PTR;
  var phQuery: PDH_HQUERY): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenQueryA}
function PdhOpenQueryW(szDataSource: LPCWSTR; dwUserData: DWORD_PTR;
  var phQuery: PDH_HQUERY): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenQueryW}

{$IFDEF UNICODE}
function PdhOpenQuery(szDataSource: LPCWSTR; dwUserData: DWORD_PTR;
  var phQuery: PDH_HQUERY): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenQuery}
{$ELSE}
function PdhOpenQuery(szDataSource: LPCSTR; dwUserData: DWORD_PTR;
  var phQuery: PDH_HQUERY): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenQuery}
{$ENDIF}

function PdhAddCounterA(hQuery: PDH_HQUERY; szFullCounterPath: LPCSTR;
  dwUserData: DWORD_PTR; var phCounter: PDH_HCOUNTER): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhAddCounterA}
function PdhAddCounterW(hQuery: PDH_HQUERY; szFullCounterPath: LPCWSTR;
  dwUserData: DWORD_PTR; var phCounter: PDH_HCOUNTER): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhAddCounterW}

{$IFDEF UNICODE}
function PdhAddCounter(hQuery: PDH_HQUERY; szFullCounterPath: LPCWSTR;
  dwUserData: DWORD_PTR; var phCounter: PDH_HCOUNTER): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhAddCounter}
{$ELSE}
function PdhAddCounter(hQuery: PDH_HQUERY; szFullCounterPath: LPCSTR;
  dwUserData: DWORD_PTR; var phCounter: PDH_HCOUNTER): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhAddCounter}
{$ENDIF}

function PdhRemoveCounter(hCounter: PDH_HCOUNTER): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhRemoveCounter}

function PdhCollectQueryData(hQuery: PDH_HQUERY): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCollectQueryData}

function PdhCloseQuery(hQuery: PDH_HQUERY): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCloseQuery}

//
//  Counter Functions
//

function PdhGetFormattedCounterValue(hCounter: PDH_HCOUNTER; dwFormat: DWORD;
  lpdwType: LPDWORD; var pValue: PDH_FMT_COUNTERVALUE): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetFormattedCounterValue}

function PdhGetFormattedCounterArrayA(hCounter: PDH_HCOUNTER; dwFormat: DWORD;
  var lpdwBufferSize, lpdwItemCount: DWORD;
  var ItemBuffer: PDH_FMT_COUNTERVALUE_ITEM_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetFormattedCounterArrayA}
function PdhGetFormattedCounterArrayW(hCounter: PDH_HCOUNTER; dwFormat: DWORD;
  var lpdwBufferSize, lpdwItemCount: DWORD;
  var ItemBuffer: PDH_FMT_COUNTERVALUE_ITEM_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetFormattedCounterArrayW}

{$IFDEF UNICODE}
function PdhGetFormattedCounterArray(hCounter: PDH_HCOUNTER; dwFormat: DWORD;
  var lpdwBufferSize, lpdwItemCount: DWORD;
  var ItemBuffer: PDH_FMT_COUNTERVALUE_ITEM_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetFormattedCounterArray}
{$ELSE}
function PdhGetFormattedCounterArray(hCounter: PDH_HCOUNTER; dwFormat: DWORD;
  var lpdwBufferSize, lpdwItemCount: DWORD;
  var ItemBuffer: PDH_FMT_COUNTERVALUE_ITEM_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetFormattedCounterArray}
{$ENDIF}

// dwFormat flag values

const
  PDH_FMT_RAW      = DWORD($00000010);
  {$EXTERNALSYM PDH_FMT_RAW}
  PDH_FMT_ANSI     = DWORD($00000020);
  {$EXTERNALSYM PDH_FMT_ANSI}
  PDH_FMT_UNICODE  = DWORD($00000040);
  {$EXTERNALSYM PDH_FMT_UNICODE}
  PDH_FMT_LONG     = DWORD($00000100);
  {$EXTERNALSYM PDH_FMT_LONG}
  PDH_FMT_DOUBLE   = DWORD($00000200);
  {$EXTERNALSYM PDH_FMT_DOUBLE}
  PDH_FMT_LARGE    = DWORD($00000400);
  {$EXTERNALSYM PDH_FMT_LARGE}
  PDH_FMT_NOSCALE  = DWORD($00001000);
  {$EXTERNALSYM PDH_FMT_NOSCALE}
  PDH_FMT_1000     = DWORD($00002000);
  {$EXTERNALSYM PDH_FMT_1000}
  PDH_FMT_NODATA   = DWORD($00004000);
  {$EXTERNALSYM PDH_FMT_NODATA}
  PDH_FMT_NOCAP100 = DWORD($00008000);
  {$EXTERNALSYM PDH_FMT_NODATA}

  PERF_DETAIL_COSTLY   = DWORD($00010000);
  {$EXTERNALSYM PERF_DETAIL_COSTLY}
  PERF_DETAIL_STANDARD = DWORD($0000FFFF);
  {$EXTERNALSYM PERF_DETAIL_STANDARD}

function PdhGetRawCounterValue(hCounter: PDH_HCOUNTER; lpdwType: LPDWORD;
  var pValue: PDH_RAW_COUNTER): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetRawCounterValue}

function PdhGetRawCounterArrayA(hCounter: PDH_HCOUNTER; var lpdwBufferSize,
  lpdwItemCount: DWORD; var ItemBuffer: PDH_RAW_COUNTER_ITEM_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetRawCounterArrayA}
function PdhGetRawCounterArrayW(hCounter: PDH_HCOUNTER; var lpdwBufferSize,
  lpdwItemCount: DWORD; var ItemBuffer: PDH_RAW_COUNTER_ITEM_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetRawCounterArrayW}

{$IFDEF UNICODE}
function PdhGetRawCounterArray(hCounter: PDH_HCOUNTER; var lpdwBufferSize,
  lpdwItemCount: DWORD; var ItemBuffer: PDH_RAW_COUNTER_ITEM_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetRawCounterArray}
{$ELSE}
function PdhGetRawCounterArray(hCounter: PDH_HCOUNTER; var lpdwBufferSize,
  lpdwItemCount: DWORD; var ItemBuffer: PDH_RAW_COUNTER_ITEM_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetRawCounterArray}
{$ENDIF}

function PdhCalculateCounterFromRawValue(hCounter: PDH_HCOUNTER; dwFormat: DWORD;
  rawValue1, rawValue2: PPDH_RAW_COUNTER; var fmtValue: PDH_FMT_COUNTERVALUE): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCalculateCounterFromRawValue}

function PdhComputeCounterStatistics(hCounter: PDH_HCOUNTER; dwFormat, dwFirstEntry,
  dwNumEntries: DWORD; lpRawValueArray: PPDH_RAW_COUNTER; var data: PDH_STATISTICS): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhComputeCounterStatistics}

function PdhGetCounterInfoA(hCounter: PDH_HCOUNTER; bRetrieveExplainText: Boolean;
  var pdwBufferSize: DWORD; lpBuffer: PPDH_COUNTER_INFO_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetCounterInfoA}
function PdhGetCounterInfoW(hCounter: PDH_HCOUNTER; bRetrieveExplainText: Boolean;
  var pdwBufferSize: DWORD; lpBuffer: PPDH_COUNTER_INFO_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetCounterInfoW}

{$IFDEF UNICODE}
function PdhGetCounterInfo(hCounter: PDH_HCOUNTER; bRetrieveExplainText: Boolean;
  var pdwBufferSize: DWORD; lpBuffer: PPDH_COUNTER_INFO_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetCounterInfo}
{$ELSE}
function PdhGetCounterInfo(hCounter: PDH_HCOUNTER; bRetrieveExplainText: Boolean;
  var pdwBufferSize: DWORD; lpBuffer: PPDH_COUNTER_INFO_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetCounterInfo}
{$ENDIF}

const
  PDH_MAX_SCALE = Longint(7);
  {$EXTERNALSYM PDH_MAX_SCALE}
  PDH_MIN_SCALE = Longint(-7);
  {$EXTERNALSYM PDH_MIN_SCALE}

function PdhSetCounterScaleFactor(hCounter: PDH_HCOUNTER; lFactor: LONG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSetCounterScaleFactor}

//
//   Browsing and enumeration functions
//

function PdhConnectMachineA(szMachineName: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhConnectMachineA}
function PdhConnectMachineW(szMachineName: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhConnectMachineW}

{$IFDEF UNICODE}
function PdhConnectMachine(szMachineName: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhConnectMachine}
{$ELSE}
function PdhConnectMachine(szMachineName: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhConnectMachine}
{$ENDIF}

function PdhEnumMachinesA(szDataSource: LPCSTR; mszMachineList: LPSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachinesA}
function PdhEnumMachinesW(szDataSource: LPCWSTR; mszMachineList: LPWSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachinesW}

{$IFDEF UNICODE}
function PdhEnumMachines(szDataSource: LPCWSTR; mszMachineList: LPWSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachines}
{$ELSE}
function PdhEnumMachines(szDataSource: LPCSTR; mszMachineList: LPSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachines}
{$ENDIF}

function PdhEnumObjectsA(szDataSource, szMachineName: LPCSTR; mszObjectList: LPSTR;
  var pcchBufferSize: DWORD; dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectsA}
function PdhEnumObjectsW(szDataSource, szMachineName: LPCWSTR; mszObjectList: LPWSTR;
  var pcchBufferSize: DWORD; dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectsW}

{$IFDEF UNICODE}
function PdhEnumObjects(szDataSource, szMachineName: LPCWSTR; mszObjectList: LPWSTR;
  var pcchBufferSize: DWORD; dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjects}
{$ELSE}
function PdhEnumObjects(szDataSource, szMachineName: LPCSTR; mszObjectList: LPSTR;
  var pcchBufferSize: DWORD; dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjects}
{$ENDIF}

function PdhEnumObjectItemsA(szDataSource, szMachineName, szObjectName: LPCSTR;
  mszCounterList: LPSTR; var pcchCounterListLength: DWORD; mszInstanceList: LPSTR;
  var pcchInstanceListLength: DWORD; dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItemsA}
function PdhEnumObjectItemsW(szDataSource, szMachineName, szObjectName: LPCWSTR;
  mszCounterList: LPWSTR; var pcchCounterListLength: DWORD; mszInstanceList: LPWSTR;
  var pcchInstanceListLength: DWORD; dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItemsW}

{$IFDEF UNICODE}
function PdhEnumObjectItems(szDataSource, szMachineName, szObjectName: LPCWSTR;
  mszCounterList: LPWSTR; var pcchCounterListLength: DWORD; mszInstanceList: LPWSTR;
  var pcchInstanceListLength: DWORD; dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItems}
{$ELSE}
function PdhEnumObjectItems(szDataSource, szMachineName, szObjectName: LPCSTR;
  mszCounterList: LPSTR; var pcchCounterListLength: DWORD; mszInstanceList: LPSTR;
  var pcchInstanceListLength: DWORD; dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItems}
{$ENDIF}

const
  PDH_OBJECT_HAS_INSTANCES  = $00000001;
  {$EXTERNALSYM PDH_OBJECT_HAS_INSTANCES}

function PdhMakeCounterPathA(pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_A;
  szFullPathBuffer: LPSTR; var pcchBufferSize: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhMakeCounterPathA}
function PdhMakeCounterPathW(pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_W;
  szFullPathBuffer: LPWSTR; var pcchBufferSize: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhMakeCounterPathW}

{$IFDEF UNICODE}
function PdhMakeCounterPath(pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_W;
  szFullPathBuffer: LPWSTR; var pcchBufferSize: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhMakeCounterPath}
{$ELSE}
function PdhMakeCounterPath(pCounterPathElements: PPDH_COUNTER_PATH_ELEMENTS_A;
  szFullPathBuffer: LPSTR; var pcchBufferSize: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhMakeCounterPath}
{$ENDIF}

// todo shouldn't pCounterPathElements be a pointer to ...?

function PdhParseCounterPathA(szFullPathBuffer: LPCSTR;
  pCounterPathElements: PDH_COUNTER_PATH_ELEMENTS_A; var pdwBufferSize: DWORD;
  dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseCounterPathA}
function PdhParseCounterPathW(szFullPathBuffer: LPCWSTR;
  pCounterPathElements: PDH_COUNTER_PATH_ELEMENTS_W; var pdwBufferSize: DWORD;
  dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseCounterPathW}

{$IFDEF UNICODE}
function PdhParseCounterPath(szFullPathBuffer: LPCWSTR;
  pCounterPathElements: PDH_COUNTER_PATH_ELEMENTS_W; var pdwBufferSize: DWORD;
  dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseCounterPath}
{$ELSE}
function PdhParseCounterPath(szFullPathBuffer: LPCSTR;
  pCounterPathElements: PDH_COUNTER_PATH_ELEMENTS_A; var pdwBufferSize: DWORD;
  dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseCounterPath}
{$ENDIF}

const
  PDH_PATH_WBEM_RESULT       = DWORD($00000001);
  {$EXTERNALSYM PDH_PATH_WBEM_RESULT}
  PDH_PATH_WBEM_INPUT        = DWORD($00000002);
  {$EXTERNALSYM PDH_PATH_WBEM_INPUT}

function PDH_PATH_LANG_FLAGS(LangId, Flags: DWORD): DWORD;
{$EXTERNALSYM PDH_PATH_LANG_FLAGS}

function PdhParseInstanceNameA(szInstanceString: LPSTR; szInstanceName: LPCSTR;
  var pcchInstanceNameLength: DWORD; szParentName: LPSTR;
  var pcchParentNameLength: DWORD; lpIndex: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseInstanceNameA}
function PdhParseInstanceNameW(szInstanceString: LPWSTR; szInstanceName: LPCWSTR;
  var pcchInstanceNameLength: DWORD; szParentName: LPWSTR;
  var pcchParentNameLength: DWORD; lpIndex: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseInstanceNameW}

{$IFDEF UNICODE}
function PdhParseInstanceName(szInstanceString: LPWSTR; szInstanceName: LPCWSTR;
  var pcchInstanceNameLength: DWORD; szParentName: LPWSTR;
  var pcchParentNameLength: DWORD; lpIndex: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseInstanceName}
{$ELSE}
function PdhParseInstanceName(szInstanceString: LPSTR; szInstanceName: LPCSTR;
  var pcchInstanceNameLength: DWORD; szParentName: LPSTR;
  var pcchParentNameLength: DWORD; lpIndex: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhParseInstanceName}
{$ENDIF}

function PdhValidatePathA(szFullPathBuffer: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhValidatePathA}
function PdhValidatePathW(szFullPathBuffer: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhValidatePathW}

{$IFDEF UNICODE}
function PdhValidatePath(szFullPathBuffer: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhValidatePath}
{$ELSE}
function PdhValidatePath(szFullPathBuffer: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhValidatePath}
{$ENDIF}

function PdhGetDefaultPerfObjectA(szDataSource, szMachineName: LPCSTR;
  szDefaultObjectName: LPSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObjectA}
function PdhGetDefaultPerfObjectW(szDataSource, szMachineName: LPCWSTR;
  szDefaultObjectName: LPWSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObjectW}

{$IFDEF UNICODE}
function PdhGetDefaultPerfObject(szDataSource, szMachineName: LPCWSTR;
  szDefaultObjectName: LPWSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObject}
{$ELSE}
function PdhGetDefaultPerfObject(szDataSource, szMachineName: LPCSTR;
  szDefaultObjectName: LPSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObject}
{$ENDIF}

function PdhGetDefaultPerfCounterA(szDataSource, szMachineName, szObjectName: LPCSTR;
  szDefaultCounterName: LPSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounterA}
function PdhGetDefaultPerfCounterW(szDataSource, szMachineName, szObjectName: LPCWSTR;
  szDefaultCounterName: LPWSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounterW}

{$IFDEF UNICODE}
function PdhGetDefaultPerfCounter(szDataSource, szMachineName, szObjectName: LPCWSTR;
  szDefaultCounterName: LPWSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounter}
{$ELSE}
function PdhGetDefaultPerfCounter(szDataSource, szMachineName, szObjectName: LPCSTR;
  szDefaultCounterName: LPSTR; var pcchBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounter}
{$ENDIF}

type
  CounterPathCallBack = function (dwArg: DWORD_PTR): PDH_STATUS; stdcall;
  {$EXTERNALSYM CounterPathCallBack}

const
  PDH_CF_INCLUDEINSTANCEINDEX    = 1 shl 0;
  PDH_CF_SINGLECOUNTERPERADD     = 1 shl 1;
  PDH_CF_SINGLECOUNTERPERDIALOG  = 1 shl 2;
  PDH_CF_LOCALCOUNTERSONLY       = 1 shl 3;
  PDH_CF_WILDCARDINSTANCES       = 1 shl 4;
  PDH_CF_HIDEDETAILBOX           = 1 shl 5;
  PDH_CF_INITIALIZEPATH          = 1 shl 6;
  PDH_CF_DISABLEMACHINESELECTION = 1 shl 7;
  PDH_CF_INCLUDECOSTLYOBJECTS    = 1 shl 8;
  PDH_CF_SHOWOBJECTBROWSER       = 1 shl 9;
  PDH_CF_RESERVED                = DWORD($FFFFFD00);

type
  _BrowseDlgConfig_HW = record
    // Configuration flags
    dwConfigFlags: DWORD;
    hWndOwner: HWND;
    hDataSource: PDH_HLOG;
    szReturnPathBuffer: LPWSTR;
    cchReturnPathLength: DWORD;
    pCallBack: CounterPathCallBack;
    dwCallBackArg: DWORD_PTR;
    CallBackStatus: PDH_STATUS;
    dwDefaultDetailLevel: DWORD;
    szDialogBoxCaption: LPWSTR;
  end;
  {$EXTERNALSYM _BrowseDlgConfig_HW}
  PDH_BROWSE_DLG_CONFIG_HW = _BrowseDlgConfig_HW;
  {$EXTERNALSYM PDH_BROWSE_DLG_CONFIG_HW}
  PPDH_BROWSE_DLG_CONFIG_HW = ^PDH_BROWSE_DLG_CONFIG_HW;
  {$EXTERNALSYM PPDH_BROWSE_DLG_CONFIG_HW}
  TPdhBrowseDlgConfigHW = PDH_BROWSE_DLG_CONFIG_HW;
  PPdhBrowseDlgConfigHW = PPDH_BROWSE_DLG_CONFIG_HW;

  _BrowseDlgConfig_HA = record
    // Configuration flags
    dwConfigFlags: DWORD;
    hWndOwner: HWND;
    hDataSource: PDH_HLOG;
    szReturnPathBuffer: LPSTR;
    cchReturnPathLength: DWORD;
    pCallBack: CounterPathCallBack;
    dwCallBackArg: DWORD_PTR;
    CallBackStatus: PDH_STATUS;
    dwDefaultDetailLevel: DWORD;
    szDialogBoxCaption: LPSTR;
  end;
  {$EXTERNALSYM _BrowseDlgConfig_HA}
  PDH_BROWSE_DLG_CONFIG_HA = _BrowseDlgConfig_HA;
  {$EXTERNALSYM PDH_BROWSE_DLG_CONFIG_HA}
  PPDH_BROWSE_DLG_CONFIG_HA = ^PDH_BROWSE_DLG_CONFIG_HA;
  {$EXTERNALSYM PPDH_BROWSE_DLG_CONFIG_HA}
  TPdhBrowseDlGconfigHA = PDH_BROWSE_DLG_CONFIG_HA;
  PPdhBrowseDlGconfigHA = PPDH_BROWSE_DLG_CONFIG_HA;

  PPDH_BROWSE_DLG_CONFIG_A = ^_BrowseDlgConfig_A;
  {$EXTERNALSYM PPDH_BROWSE_DLG_CONFIG_A}
  _BrowseDlgConfig_A = record
    dwConfigFlags: DWORD;
    hWndOwner: HWND;
    szDataSource: LPSTR;
    szReturnPathBuffer: LPSTR;
    cchReturnPathLength: DWORD;
    pCallBack: CounterPathCallBack;
    dwCallBackArg: DWORD_PTR;
    CallBackStatus: PDH_STATUS;
    dwDefaultDetailLevel: DWORD;
    szDialogBoxCaption: LPSTR;
  end;
  {$EXTERNALSYM _BrowseDlgConfig_A}
  PDH_BROWSE_DLG_CONFIG_A = _BrowseDlgConfig_A;
  {$EXTERNALSYM PDH_BROWSE_DLG_CONFIG_A}
  TPdhBrowseDlgConfigA = PDH_BROWSE_DLG_CONFIG_A;
  PPdhBrowseDlgConfigA = PPDH_BROWSE_DLG_CONFIG_A;

  PPDH_BROWSE_DLG_CONFIG_W = ^_BrowseDlgConfig_W;
  {$EXTERNALSYM PPDH_BROWSE_DLG_CONFIG_W}
  _BrowseDlgConfig_W = record
    dwConfigFlags: DWORD;
    hWndOwner: HWND;
    szDataSource: LPWSTR;
    szReturnPathBuffer: LPWSTR;
    cchReturnPathLength: DWORD;
    pCallBack: CounterPathCallBack;
    dwCallBackArg: DWORD_PTR;
    CallBackStatus: PDH_STATUS;
    dwDefaultDetailLevel: DWORD;
    szDialogBoxCaption: LPWSTR;
  end;
  {$EXTERNALSYM _BrowseDlgConfig_W}
  PDH_BROWSE_DLG_CONFIG_W = _BrowseDlgConfig_W;
  {$EXTERNALSYM PDH_BROWSE_DLG_CONFIG_W}
  TPdhBrowseDlgConfigW = PDH_BROWSE_DLG_CONFIG_W;
  PPdhBrowseDlgConfigW = PPDH_BROWSE_DLG_CONFIG_W;

{$IFDEF UNICODE}
  PPdhBrowseDlgConfig = PPdhBrowseDlgConfigW;
  PDH_BROWSE_DLG_CONFIG = PDH_BROWSE_DLG_CONFIG_W;
  {$EXTERNALSYM PDH_BROWSE_DLG_CONFIG}
  PPDH_BROWSE_DLG_CONFIG = PPDH_BROWSE_DLG_CONFIG_W;
  {$EXTERNALSYM PPDH_BROWSE_DLG_CONFIG}
  TPdhBrowseDlgConfig = TPdhBrowseDlgConfigW;
{$ELSE}
  PPdhBrowseDlgConfig = PPdhBrowseDlgConfigA;
  PDH_BROWSE_DLG_CONFIG = PDH_BROWSE_DLG_CONFIG_A;
  {$EXTERNALSYM PDH_BROWSE_DLG_CONFIG}
  PPDH_BROWSE_DLG_CONFIG = PPDH_BROWSE_DLG_CONFIG_A;
  {$EXTERNALSYM PPDH_BROWSE_DLG_CONFIG}
  TPdhBrowseDlgConfig = TPdhBrowseDlgConfigA;
{$ENDIF}

function PdhBrowseCountersA(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCountersA}
function PdhBrowseCountersW(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCountersW}

{$IFDEF UNICODE}
function PdhBrowseCounters(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_W): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCounters}
{$ELSE}
function PdhBrowseCounters(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_A): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCounters}
{$ENDIF}

function PdhExpandCounterPathA(szWildCardPath: LPCSTR; mszExpandedPathList: LPSTR;
  var pcchPathListLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandCounterPathA}
function PdhExpandCounterPathW(szWildCardPath: LPCWSTR; mszExpandedPathList: LPWSTR;
  var pcchPathListLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandCounterPathW}

{$IFDEF UNICODE}
function PdhExpandCounterPath(szWildCardPath: LPCWSTR; mszExpandedPathList: LPWSTR;
  var pcchPathListLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandCounterPath}
{$ELSE}
function PdhExpandCounterPath(szWildCardPath: LPCSTR; mszExpandedPathList: LPSTR;
  var pcchPathListLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandCounterPath}
{$ENDIF}

//
//  v2.0 functions
//

function PdhLookupPerfNameByIndexA(szMachineName: LPCSTR; dwNameIndex: DWORD;
  szNameBuffer: LPSTR; var pcchNameBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfNameByIndexA}
function PdhLookupPerfNameByIndexW(szMachineName: LPCWSTR; dwNameIndex: DWORD;
  szNameBuffer: LPWSTR; var pcchNameBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfNameByIndexW}

{$IFDEF UNICODE}
function PdhLookupPerfNameByIndex(szMachineName: LPCWSTR; dwNameIndex: DWORD;
  szNameBuffer: LPWSTR; var pcchNameBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfNameByIndex}
{$ELSE}
function PdhLookupPerfNameByIndex(szMachineName: LPCSTR; dwNameIndex: DWORD;
  szNameBuffer: LPSTR; var pcchNameBufferSize: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfNameByIndex}
{$ENDIF}

function PdhLookupPerfIndexByNameA(szMachineName, szNameBuffer: LPCSTR;
  var pdwIndex: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfIndexByNameA}
function PdhLookupPerfIndexByNameW(szMachineName, szNameBuffer: LPCWSTR;
  var pdwIndex: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfIndexByNameW}

{$IFDEF UNICODE}
function PdhLookupPerfIndexByName(szMachineName, szNameBuffer: LPCWSTR;
  var pdwIndex: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfIndexByName}
{$ELSE}
function PdhLookupPerfIndexByName(szMachineName, szNameBuffer: LPCSTR;
  var pdwIndex: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhLookupPerfIndexByName}
{$ENDIF}

const
  PDH_NOEXPANDCOUNTERS   = 1;
  {$EXTERNALSYM PDH_NOEXPANDCOUNTERS}
  PDH_NOEXPANDINSTANCES  = 2;
  {$EXTERNALSYM PDH_NOEXPANDINSTANCES}
  PDH_REFRESHCOUNTERS    = 4;
  {$EXTERNALSYM PDH_REFRESHCOUNTERS}

function PdhExpandWildCardPathA(szDataSource, szWildCardPath: LPCSTR;
  mszExpandedPathList: LPSTR; var pcchPathListLength: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPathA}
function PdhExpandWildCardPathW(szDataSource, szWildCardPath: LPCWSTR;
  mszExpandedPathList: LPWSTR; var pcchPathListLength: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPathW}

{$IFDEF UNICODE}
function PdhExpandWildCardPath(szDataSource, szWildCardPath: LPCWSTR;
  mszExpandedPathList: LPWSTR; var pcchPathListLength: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPath}
{$ELSE}
function PdhExpandWildCardPath(szDataSource, szWildCardPath: LPCSTR;
  mszExpandedPathList: LPSTR; var pcchPathListLength: DWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPath}
{$ENDIF}

//
//   Logging Functions
//

const
  PDH_LOG_READ_ACCESS        = DWORD($00010000);
  {$EXTERNALSYM PDH_LOG_READ_ACCESS}
  PDH_LOG_WRITE_ACCESS       = DWORD($00020000);
  {$EXTERNALSYM PDH_LOG_WRITE_ACCESS}
  PDH_LOG_UPDATE_ACCESS      = DWORD($00040000);
  {$EXTERNALSYM PDH_LOG_UPDATE_ACCESS}
  PDH_LOG_ACCESS_MASK        = DWORD($000F0000);
  {$EXTERNALSYM PDH_LOG_ACCESS_MASK}

  PDH_LOG_CREATE_NEW         = DWORD($00000001);
  {$EXTERNALSYM PDH_LOG_CREATE_NEW}
  PDH_LOG_CREATE_ALWAYS      = DWORD($00000002);
  {$EXTERNALSYM PDH_LOG_CREATE_ALWAYS}
  PDH_LOG_OPEN_ALWAYS        = DWORD($00000003);
  {$EXTERNALSYM PDH_LOG_OPEN_ALWAYS}
  PDH_LOG_OPEN_EXISTING      = DWORD($00000004);
  {$EXTERNALSYM PDH_LOG_OPEN_EXISTING}
  PDH_LOG_CREATE_MASK        = DWORD($0000000F);
  {$EXTERNALSYM PDH_LOG_CREATE_MASK}

  PDH_LOG_OPT_USER_STRING    = DWORD($01000000);
  {$EXTERNALSYM PDH_LOG_OPT_USER_STRING}
  PDH_LOG_OPT_CIRCULAR       = DWORD($02000000);
  {$EXTERNALSYM PDH_LOG_OPT_CIRCULAR}
  PDH_LOG_OPT_MAX_IS_BYTES   = DWORD($04000000);
  {$EXTERNALSYM PDH_LOG_OPT_MAX_IS_BYTES}
  PDH_LOG_OPT_APPEND         = DWORD($08000000);
  {$EXTERNALSYM PDH_LOG_OPT_APPEND}
  PDH_LOG_OPT_MASK           = DWORD($0F000000);
  {$EXTERNALSYM PDH_LOG_OPT_MASK}

  PDH_LOG_TYPE_UNDEFINED     = 0;
  {$EXTERNALSYM PDH_LOG_TYPE_UNDEFINED}
  PDH_LOG_TYPE_CSV           = 1;
  {$EXTERNALSYM PDH_LOG_TYPE_CSV}
  PDH_LOG_TYPE_TSV           = 2;
  {$EXTERNALSYM PDH_LOG_TYPE_TSV}
  //PDH_LOG_TYPE_BINARY        = 3;  // this is the retired binary format
  //{$EXTERNALSYM PDH_LOG_TYPE_BINARY}
  PDH_LOG_TYPE_TRACE_KERNEL  = 4;
  {$EXTERNALSYM PDH_LOG_TYPE_TRACE_KERNEL}
  PDH_LOG_TYPE_TRACE_GENERIC = 5;
  {$EXTERNALSYM PDH_LOG_TYPE_TRACE_GENERIC}
  PDH_LOG_TYPE_PERFMON       = 6;
  {$EXTERNALSYM PDH_LOG_TYPE_PERFMON}
  PDH_LOG_TYPE_SQL           = 7;
  {$EXTERNALSYM PDH_LOG_TYPE_SQL}
  PDH_LOG_TYPE_BINARY        = 8;
  {$EXTERNALSYM PDH_LOG_TYPE_BINARY}

function PdhOpenLogA(szLogFileName: LPCSTR; dwAccessFlags: DWORD;
  lpdwLogType: LPDWORD; hQuery: PDH_HQUERY; dwMaxRecords: DWORD;
  szUserCaption: LPCSTR; var phLog: PDH_HLOG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenLogA}
function PdhOpenLogW(szLogFileName: LPCWSTR; dwAccessFlags: DWORD;
  lpdwLogType: LPDWORD; hQuery: PDH_HQUERY; dwMaxRecords: DWORD;
  szUserCaption: LPCWSTR; var phLog: PDH_HLOG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenLogW}

{$IFDEF UNICODE}
function PdhOpenLog(szLogFileName: LPCWSTR; dwAccessFlags: DWORD;
  lpdwLogType: LPDWORD; hQuery: PDH_HQUERY; dwMaxRecords: DWORD;
  szUserCaption: LPCWSTR; var phLog: PDH_HLOG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenLog}
{$ELSE}
function PdhOpenLog(szLogFileName: LPCSTR; dwAccessFlags: DWORD;
  lpdwLogType: LPDWORD; hQuery: PDH_HQUERY; dwMaxRecords: DWORD;
  szUserCaption: LPCSTR; var phLog: PDH_HLOG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenLog}
{$ENDIF}

function PdhUpdateLogA(hLog: PDH_HLOG; szUserString: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhUpdateLogA}
function PdhUpdateLogW(hLog: PDH_HLOG; szUserString: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhUpdateLogW}

{$IFDEF UNICODE}
function PdhUpdateLog(hLog: PDH_HLOG; szUserString: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhUpdateLog}
{$ELSE}
function PdhUpdateLog(hLog: PDH_HLOG; szUserString: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhUpdateLog}
{$ENDIF}

function PdhUpdateLogFileCatalog(hLog: PDH_HLOG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhUpdateLogFileCatalog}

function PdhGetLogFileSize(hLog: PDH_HLOG; var llSize: LONGLONG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetLogFileSize}

function PdhCloseLog(hLog: PDH_HLOG; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCloseLog}

const
  PDH_FLAGS_CLOSE_QUERY = DWORD($00000001);
  {$EXTERNALSYM PDH_FLAGS_CLOSE_QUERY}

//
//  Data source selection dialog
//

const
  PDH_FLAGS_FILE_BROWSER_ONLY = DWORD($00000001);
  {$EXTERNALSYM PDH_FLAGS_FILE_BROWSER_ONLY}

function PdhSelectDataSourceA(hWndOwner: HWND; dwFlags: DWORD;
  szDataSource: LPSTR; var pcchBufferLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSelectDataSourceA}
function PdhSelectDataSourceW(hWndOwner: HWND; dwFlags: DWORD;
  szDataSource: LPWSTR; var pcchBufferLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSelectDataSourceW}

{$IFDEF UNICODE}
function PdhSelectDataSource(hWndOwner: HWND; dwFlags: DWORD;
  szDataSource: LPWSTR; var pcchBufferLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSelectDataSource}
{$ELSE}
function PdhSelectDataSource(hWndOwner: HWND; dwFlags: DWORD;
  szDataSource: LPSTR; var pcchBufferLength: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSelectDataSource}
{$ENDIF}

function PdhIsRealTimeQuery(hQuery: PDH_HQUERY): BOOL; stdcall;
{$EXTERNALSYM PdhIsRealTimeQuery}

function PdhSetQueryTimeRange(hQuery: PDH_HQUERY; var pInfo: PDH_TIME_INFO): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSetQueryTimeRange}

function PdhGetDataSourceTimeRangeA(szDataSource: LPCSTR; var pdwNumEntries: DWORD;
  var pInfo: PDH_TIME_INFO; pdwBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDataSourceTimeRangeA}
function PdhGetDataSourceTimeRangeW(szDataSource: LPCWSTR; var pdwNumEntries: DWORD;
  var pInfo: PDH_TIME_INFO; pdwBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDataSourceTimeRangeW}

{$IFDEF UNICODE}
function PdhGetDataSourceTimeRange(szDataSource: LPCWSTR; var pdwNumEntries: DWORD;
  var pInfo: PDH_TIME_INFO; pdwBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDataSourceTimeRange}
{$ELSE}
function PdhGetDataSourceTimeRange(szDataSource: LPCSTR; var pdwNumEntries: DWORD;
  var pInfo: PDH_TIME_INFO; pdwBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDataSourceTimeRange}
{$ENDIF}

function PdhCollectQueryDataEx(hQuery: PDH_HQUERY; dwIntervalTime: DWORD;
  hNewDataEvent: HANDLE): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCollectQueryDataEx}

function PdhFormatFromRawValue(dwCounterType, dwFormat: DWORD;
  var pTimeBase: LONGLONG; pRawValue1, pRawValue2: PPDH_RAW_COUNTER;
  var pFmtValue: PDH_FMT_COUNTERVALUE): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhFormatFromRawValue}

function PdhGetCounterTimeBase(hCounter: PDH_HCOUNTER; var pTimeBase: LONGLONG): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetCounterTimeBase}

function PdhReadRawLogRecord(hLog: PDH_HLOG; ftRecord: FILETIME;
  var pRawLogRecord: PDH_RAW_LOG_RECORD; pdwBufferLength: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhReadRawLogRecord}

const
  DATA_SOURCE_REGISTRY    = DWORD($00000001);
  {$EXTERNALSYM DATA_SOURCE_REGISTRY}
  DATA_SOURCE_LOGFILE     = DWORD($00000002);
  {$EXTERNALSYM DATA_SOURCE_LOGFILE}
  DATA_SOURCE_WBEM        = DWORD($00000004);
  {$EXTERNALSYM DATA_SOURCE_WBEM}

function PdhSetDefaultRealTimeDataSource(dwDataSourceId: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSetDefaultRealTimeDataSource}

// Extended API for WMI event trace logfile format
//

function PdhBindInputDataSourceW(var phDataSource: PDH_HLOG; LogFileNameList: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBindInputDataSourceW}
function PdhBindInputDataSourceA(var phDataSource: PDH_HLOG; LogFileNameList: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBindInputDataSourceA}

{$IFDEF UNICODE}
function PdhBindInputDataSource(var phDataSource: PDH_HLOG; LogFileNameList: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBindInputDataSource}
{$ELSE}
function PdhBindInputDataSource(var phDataSource: PDH_HLOG; LogFileNameList: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBindInputDataSource}
{$ENDIF}

function PdhOpenQueryH(hDataSource: PDH_HLOG; dwUserData: DWORD_PTR; var phQuery: PDH_HQUERY): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhOpenQueryH}

function PdhEnumMachinesHW(hDataSource: PDH_HLOG; mszMachineList: LPWSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachinesHW}
function PdhEnumMachinesHA(hDataSource: PDH_HLOG; mszMachineList: LPSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachinesHA}

{$IFDEF UNICODE}
function PdhEnumMachinesH(hDataSource: PDH_HLOG; mszMachineList: LPWSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachinesH}
{$ELSE}
function PdhEnumMachinesH(hDataSource: PDH_HLOG; mszMachineList: LPSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumMachinesH}
{$ENDIF}

function PdhEnumObjectsHW(hDataSource: PDH_HLOG; szMachineName: LPCWSTR; mszObjectList: LPWSTR; pcchBufferSize: LPDWORD;
  dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectsHW}
function PdhEnumObjectsHA(hDataSource: PDH_HLOG; szMachineName: LPCSTR; mszObjectList: LPSTR; pcchBufferSize: LPDWORD;
  dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectsHA}

{$IFDEF UNICODE}
function PdhEnumObjectsH(hDataSource: PDH_HLOG; szMachineName: LPCWSTR; mszObjectList: LPWSTR; pcchBufferSize: LPDWORD;
  dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectsH}
{$ELSE}
function PdhEnumObjectsH(hDataSource: PDH_HLOG; szMachineName: LPCSTR; mszObjectList: LPSTR; pcchBufferSize: LPDWORD;
  dwDetailLevel: DWORD; bRefresh: BOOL): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectsH}
{$ENDIF}

function PdhEnumObjectItemsHW(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCWSTR; mszCounterList: LPWSTR;
  pcchCounterListLength: LPDWORD; mszInstanceList: LPWSTR; pcchInstanceListLength: LPDWORD;
  dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItemsHW}
function PdhEnumObjectItemsHA(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCSTR; mszCounterList: LPSTR;
  pcchCounterListLength: LPDWORD; mszInstanceList: LPSTR; pcchInstanceListLength: LPDWORD;
  dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItemsHA}

{$IFDEF UNICODE}
function PdhEnumObjectItemsH(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCWSTR; mszCounterList: LPWSTR;
  pcchCounterListLength: LPDWORD; mszInstanceList: LPWSTR; pcchInstanceListLength: LPDWORD;
  dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItemsH}
{$ELSE}
function PdhEnumObjectItemsH(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCSTR; mszCounterList: LPSTR;
  pcchCounterListLength: LPDWORD; mszInstanceList: LPSTR; pcchInstanceListLength: LPDWORD;
  dwDetailLevel, dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumObjectItemsH}
{$ENDIF}

function PdhExpandWildCardPathHW(hDataSource: PDH_HLOG; szWildCardPath: LPCWSTR; mszExpandedPathList: LPWSTR;
  pcchPathListLength: LPDWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPathHW}
function PdhExpandWildCardPathHA(hDataSource: PDH_HLOG; szWildCardPath: LPCSTR; mszExpandedPathList: LPSTR;
  pcchPathListLength: LPDWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPathHA}

{$IFDEF UNICODE}
function PdhExpandWildCardPathH(hDataSource: PDH_HLOG; szWildCardPath: LPCWSTR; mszExpandedPathList: LPWSTR;
  pcchPathListLength: LPDWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPathH}
{$ELSE}
function PdhExpandWildCardPathH(hDataSource: PDH_HLOG; szWildCardPath: LPCSTR; mszExpandedPathList: LPSTR;
  pcchPathListLength: LPDWORD; dwFlags: DWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhExpandWildCardPathH}
{$ENDIF}

function PdhGetDataSourceTimeRangeH(hDataSource: PDH_HLOG; pdwNumEntries: LPDWORD; pInfo: PPDH_TIME_INFO;
  pdwBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDataSourceTimeRangeH}

function PdhGetDefaultPerfObjectHW(hDataSource: PDH_HLOG; szMachineName: LPCWSTR; szDefaultObjectName: LPWSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObjectHW}
function PdhGetDefaultPerfObjectHA(hDataSource: PDH_HLOG; szMachineName: LPCSTR; szDefaultObjectName: LPSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObjectHA}

{$IFDEF UNICODE}
function PdhGetDefaultPerfObjectH(hDataSource: PDH_HLOG; szMachineName: LPCWSTR; szDefaultObjectName: LPWSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObjectH}
{$ELSE}
function PdhGetDefaultPerfObjectH(hDataSource: PDH_HLOG; szMachineName: LPCSTR; szDefaultObjectName: LPSTR;
  pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfObjectH}
{$ENDIF}

function PdhGetDefaultPerfCounterHW(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCWSTR;
  szDefaultCounterName: LPWSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounterHW}
function PdhGetDefaultPerfCounterHA(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCSTR;
  szDefaultCounterName: LPSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounterHA}

{$IFDEF UNICODE}
function PdhGetDefaultPerfCounterH(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCWSTR;
  szDefaultCounterName: LPWSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounterH}
{$ELSE}
function PdhGetDefaultPerfCounterH(hDataSource: PDH_HLOG; szMachineName, szObjectName: LPCSTR;
  szDefaultCounterName: LPSTR; pcchBufferSize: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetDefaultPerfCounterH}
{$ENDIF}

function PdhBrowseCountersHW(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_HW): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCountersHW}
function PdhBrowseCountersHA(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_HA): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCountersHA}

{$IFDEF UNICODE}
function PdhBrowseCountersH(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_HW): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCountersH}
{$ELSE}
function PdhBrowseCountersH(const pBrowseDlgData: PDH_BROWSE_DLG_CONFIG_HA): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhBrowseCountersH}
{$ENDIF}

//Check that a DSN points to a database that contains the correct Perfmon tables.

function PdhVerifySQLDBW(szDataSource: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhVerifySQLDBW}
function PdhVerifySQLDBA(szDataSource: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhVerifySQLDBA}

{$IFDEF UNICODE}
function PdhVerifySQLDB(szDataSource: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhVerifySQLDB}
{$ELSE}
function PdhVerifySQLDB(szDataSource: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhVerifySQLDB}
{$ENDIF}

//Create the correct perfmon tables in the database pointed to by a DSN.

function PdhCreateSQLTablesW(szDataSource: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCreateSQLTablesW}
function PdhCreateSQLTablesA(szDataSource: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCreateSQLTablesA}

{$IFDEF UNICODE}
function PdhCreateSQLTables(szDataSource: LPCWSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCreateSQLTables}
{$ELSE}
function PdhCreateSQLTables(szDataSource: LPCSTR): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhCreateSQLTables}
{$ENDIF}

//Return the list of Log set names in the database pointed to by the DSN.

function PdhEnumLogSetNamesW(szDataSource: LPCWSTR; mszDataSetNameList: LPWSTR; pcchBufferLength: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumLogSetNamesW}
function PdhEnumLogSetNamesA(szDataSource: LPCSTR; mszDataSetNameList: LPSTR; pcchBufferLength: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumLogSetNamesA}

{$IFDEF UNICODE}
function PdhEnumLogSetNames(szDataSource: LPCWSTR; mszDataSetNameList: LPWSTR; pcchBufferLength: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumLogSetNames}
{$ELSE}
function PdhEnumLogSetNames(szDataSource: LPCSTR; mszDataSetNameList: LPSTR; pcchBufferLength: LPDWORD): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhEnumLogSetNames}
{$ENDIF}

//Retrieve the GUID for an open Log Set

function PdhGetLogSetGUID(hLog: PDH_HLOG; pGuid: LPGUID; pRunId: LPINT): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhGetLogSetGUID}

//Set the RunID for an open Log Set

function PdhSetLogSetRunID(hLog: PDH_HLOG; RunId: Integer): PDH_STATUS; stdcall;
{$EXTERNALSYM PdhSetLogSetRunID}

implementation

const
  PdhLib = 'pdh.dll';

function IsSuccessSeverity(ErrorCode: Longint): Boolean;
begin
  Result := (ErrorCode and $C0000000) = $00000000;
end;

function IsInformationalSeverity(ErrorCode: Longint): Boolean;
begin
  Result := (ErrorCode and $C0000000) = $40000000;
end;

function IsWarningSeverity(ErrorCode: Longint): Boolean;
begin
  Result := (ErrorCode and $C0000000) = $80000000;
end;

function IsErrorSeverity(ErrorCode: Longint): Boolean;
begin
  Result := (ErrorCode and $C0000000) = $C0000000;
end;


{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDllVersion: Pointer;

function PdhGetDllVersion;
begin
  GetProcedureAddress(_PdhGetDllVersion, PdhLib, 'PdhGetDllVersion');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDllVersion]
  end;
end;
{$ELSE}
function PdhGetDllVersion; external PdhLib name 'PdhGetDllVersion';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenQueryA: Pointer;

function PdhOpenQueryA;
begin
  GetProcedureAddress(_PdhOpenQueryA, PdhLib, 'PdhOpenQueryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenQueryA]
  end;
end;
{$ELSE}
function PdhOpenQueryA; external PdhLib name 'PdhOpenQueryA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenQueryW: Pointer;

function PdhOpenQueryW;
begin
  GetProcedureAddress(_PdhOpenQueryW, PdhLib, 'PdhOpenQueryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenQueryW]
  end;
end;
{$ELSE}
function PdhOpenQueryW; external PdhLib name 'PdhOpenQueryW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenQuery: Pointer;

function PdhOpenQuery;
begin
  GetProcedureAddress(_PdhOpenQuery, PdhLib, 'PdhOpenQueryW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenQuery]
  end;
end;
{$ELSE}
function PdhOpenQuery; external PdhLib name 'PdhOpenQueryW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenQuery: Pointer;

function PdhOpenQuery;
begin
  GetProcedureAddress(_PdhOpenQuery, PdhLib, 'PdhOpenQueryA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenQuery]
  end;
end;
{$ELSE}
function PdhOpenQuery; external PdhLib name 'PdhOpenQueryA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhAddCounterA: Pointer;

function PdhAddCounterA;
begin
  GetProcedureAddress(_PdhAddCounterA, PdhLib, 'PdhAddCounterA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhAddCounterA]
  end;
end;
{$ELSE}
function PdhAddCounterA; external PdhLib name 'PdhAddCounterA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhAddCounterW: Pointer;

function PdhAddCounterW;
begin
  GetProcedureAddress(_PdhAddCounterW, PdhLib, 'PdhAddCounterW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhAddCounterW]
  end;
end;
{$ELSE}
function PdhAddCounterW; external PdhLib name 'PdhAddCounterW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhAddCounter: Pointer;

function PdhAddCounter;
begin
  GetProcedureAddress(_PdhAddCounter, PdhLib, 'PdhAddCounterW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhAddCounter]
  end;
end;
{$ELSE}
function PdhAddCounter; external PdhLib name 'PdhAddCounterW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhAddCounter: Pointer;

function PdhAddCounter;
begin
  GetProcedureAddress(_PdhAddCounter, PdhLib, 'PdhAddCounterA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhAddCounter]
  end;
end;
{$ELSE}
function PdhAddCounter; external PdhLib name 'PdhAddCounterA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhRemoveCounter: Pointer;

function PdhRemoveCounter;
begin
  GetProcedureAddress(_PdhRemoveCounter, PdhLib, 'PdhRemoveCounter');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhRemoveCounter]
  end;
end;
{$ELSE}
function PdhRemoveCounter; external PdhLib name 'PdhRemoveCounter';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCollectQueryData: Pointer;

function PdhCollectQueryData;
begin
  GetProcedureAddress(_PdhCollectQueryData, PdhLib, 'PdhCollectQueryData');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCollectQueryData]
  end;
end;
{$ELSE}
function PdhCollectQueryData; external PdhLib name 'PdhCollectQueryData';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCloseQuery: Pointer;

function PdhCloseQuery;
begin
  GetProcedureAddress(_PdhCloseQuery, PdhLib, 'PdhCloseQuery');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCloseQuery]
  end;
end;
{$ELSE}
function PdhCloseQuery; external PdhLib name 'PdhCloseQuery';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetFormattedCounterValue: Pointer;

function PdhGetFormattedCounterValue;
begin
  GetProcedureAddress(_PdhGetFormattedCounterValue, PdhLib, 'PdhGetFormattedCounterValue');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetFormattedCounterValue]
  end;
end;
{$ELSE}
function PdhGetFormattedCounterValue; external PdhLib name 'PdhGetFormattedCounterValue';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetFormattedCounterArrayA: Pointer;

function PdhGetFormattedCounterArrayA;
begin
  GetProcedureAddress(_PdhGetFormattedCounterArrayA, PdhLib, 'PdhGetFormattedCounterArrayA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetFormattedCounterArrayA]
  end;
end;
{$ELSE}
function PdhGetFormattedCounterArrayA; external PdhLib name 'PdhGetFormattedCounterArrayA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetFormattedCounterArrayW: Pointer;

function PdhGetFormattedCounterArrayW;
begin
  GetProcedureAddress(_PdhGetFormattedCounterArrayW, PdhLib, 'PdhGetFormattedCounterArrayW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetFormattedCounterArrayW]
  end;
end;
{$ELSE}
function PdhGetFormattedCounterArrayW; external PdhLib name 'PdhGetFormattedCounterArrayW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetFormattedCounterArray: Pointer;

function PdhGetFormattedCounterArray;
begin
  GetProcedureAddress(_PdhGetFormattedCounterArray, PdhLib, 'PdhGetFormattedCounterArrayW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetFormattedCounterArray]
  end;
end;
{$ELSE}
function PdhGetFormattedCounterArray; external PdhLib name 'PdhGetFormattedCounterArrayW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetFormattedCounterArray: Pointer;

function PdhGetFormattedCounterArray;
begin
  GetProcedureAddress(_PdhGetFormattedCounterArray, PdhLib, 'PdhGetFormattedCounterArrayA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetFormattedCounterArray]
  end;
end;
{$ELSE}
function PdhGetFormattedCounterArray; external PdhLib name 'PdhGetFormattedCounterArrayA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetRawCounterValue: Pointer;

function PdhGetRawCounterValue;
begin
  GetProcedureAddress(_PdhGetRawCounterValue, PdhLib, 'PdhGetRawCounterValue');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetRawCounterValue]
  end;
end;
{$ELSE}
function PdhGetRawCounterValue; external PdhLib name 'PdhGetRawCounterValue';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetRawCounterArrayA: Pointer;

function PdhGetRawCounterArrayA;
begin
  GetProcedureAddress(_PdhGetRawCounterArrayA, PdhLib, 'PdhGetRawCounterArrayA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetRawCounterArrayA]
  end;
end;
{$ELSE}
function PdhGetRawCounterArrayA; external PdhLib name 'PdhGetRawCounterArrayA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetRawCounterArrayW: Pointer;

function PdhGetRawCounterArrayW;
begin
  GetProcedureAddress(_PdhGetRawCounterArrayW, PdhLib, 'PdhGetRawCounterArrayW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetRawCounterArrayW]
  end;
end;
{$ELSE}
function PdhGetRawCounterArrayW; external PdhLib name 'PdhGetRawCounterArrayW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetRawCounterArray: Pointer;

function PdhGetRawCounterArray;
begin
  GetProcedureAddress(_PdhGetRawCounterArray, PdhLib, 'PdhGetRawCounterArrayW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetRawCounterArray]
  end;
end;
{$ELSE}
function PdhGetRawCounterArray; external PdhLib name 'PdhGetRawCounterArrayW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetRawCounterArray: Pointer;

function PdhGetRawCounterArray;
begin
  GetProcedureAddress(_PdhGetRawCounterArray, PdhLib, 'PdhGetRawCounterArrayA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetRawCounterArray]
  end;
end;
{$ELSE}
function PdhGetRawCounterArray; external PdhLib name 'PdhGetRawCounterArrayA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCalculateCounterFromRawValue: Pointer;

function PdhCalculateCounterFromRawValue;
begin
  GetProcedureAddress(_PdhCalculateCounterFromRawValue, PdhLib, 'PdhCalculateCounterFromRawValue');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCalculateCounterFromRawValue]
  end;
end;
{$ELSE}
function PdhCalculateCounterFromRawValue; external PdhLib name 'PdhCalculateCounterFromRawValue';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhComputeCounterStatistics: Pointer;

function PdhComputeCounterStatistics;
begin
  GetProcedureAddress(_PdhComputeCounterStatistics, PdhLib, 'PdhComputeCounterStatistics');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhComputeCounterStatistics]
  end;
end;
{$ELSE}
function PdhComputeCounterStatistics; external PdhLib name 'PdhComputeCounterStatistics';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetCounterInfoA: Pointer;

function PdhGetCounterInfoA;
begin
  GetProcedureAddress(_PdhGetCounterInfoA, PdhLib, 'PdhGetCounterInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetCounterInfoA]
  end;
end;
{$ELSE}
function PdhGetCounterInfoA; external PdhLib name 'PdhGetCounterInfoA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetCounterInfoW: Pointer;

function PdhGetCounterInfoW;
begin
  GetProcedureAddress(_PdhGetCounterInfoW, PdhLib, 'PdhGetCounterInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetCounterInfoW]
  end;
end;
{$ELSE}
function PdhGetCounterInfoW; external PdhLib name 'PdhGetCounterInfoW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetCounterInfo: Pointer;

function PdhGetCounterInfo;
begin
  GetProcedureAddress(_PdhGetCounterInfo, PdhLib, 'PdhGetCounterInfoW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetCounterInfo]
  end;
end;
{$ELSE}
function PdhGetCounterInfo; external PdhLib name 'PdhGetCounterInfoW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetCounterInfo: Pointer;

function PdhGetCounterInfo;
begin
  GetProcedureAddress(_PdhGetCounterInfo, PdhLib, 'PdhGetCounterInfoA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetCounterInfo]
  end;
end;
{$ELSE}
function PdhGetCounterInfo; external PdhLib name 'PdhGetCounterInfoA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSetCounterScaleFactor: Pointer;

function PdhSetCounterScaleFactor;
begin
  GetProcedureAddress(_PdhSetCounterScaleFactor, PdhLib, 'PdhSetCounterScaleFactor');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSetCounterScaleFactor]
  end;
end;
{$ELSE}
function PdhSetCounterScaleFactor; external PdhLib name 'PdhSetCounterScaleFactor';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhConnectMachineA: Pointer;

function PdhConnectMachineA;
begin
  GetProcedureAddress(_PdhConnectMachineA, PdhLib, 'PdhConnectMachineA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhConnectMachineA]
  end;
end;
{$ELSE}
function PdhConnectMachineA; external PdhLib name 'PdhConnectMachineA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhConnectMachineW: Pointer;

function PdhConnectMachineW;
begin
  GetProcedureAddress(_PdhConnectMachineW, PdhLib, 'PdhConnectMachineW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhConnectMachineW]
  end;
end;
{$ELSE}
function PdhConnectMachineW; external PdhLib name 'PdhConnectMachineW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhConnectMachine: Pointer;

function PdhConnectMachine;
begin
  GetProcedureAddress(_PdhConnectMachine, PdhLib, 'PdhConnectMachineW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhConnectMachine]
  end;
end;
{$ELSE}
function PdhConnectMachine; external PdhLib name 'PdhConnectMachineW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhConnectMachine: Pointer;

function PdhConnectMachine;
begin
  GetProcedureAddress(_PdhConnectMachine, PdhLib, 'PdhConnectMachineA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhConnectMachine]
  end;
end;
{$ELSE}
function PdhConnectMachine; external PdhLib name 'PdhConnectMachineA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachinesA: Pointer;

function PdhEnumMachinesA;
begin
  GetProcedureAddress(_PdhEnumMachinesA, PdhLib, 'PdhEnumMachinesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachinesA]
  end;
end;
{$ELSE}
function PdhEnumMachinesA; external PdhLib name 'PdhEnumMachinesA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachinesW: Pointer;

function PdhEnumMachinesW;
begin
  GetProcedureAddress(_PdhEnumMachinesW, PdhLib, 'PdhEnumMachinesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachinesW]
  end;
end;
{$ELSE}
function PdhEnumMachinesW; external PdhLib name 'PdhEnumMachinesW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachines: Pointer;

function PdhEnumMachines;
begin
  GetProcedureAddress(_PdhEnumMachines, PdhLib, 'PdhEnumMachinesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachines]
  end;
end;
{$ELSE}
function PdhEnumMachines; external PdhLib name 'PdhEnumMachinesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachines: Pointer;

function PdhEnumMachines;
begin
  GetProcedureAddress(_PdhEnumMachines, PdhLib, 'PdhEnumMachinesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachines]
  end;
end;
{$ELSE}
function PdhEnumMachines; external PdhLib name 'PdhEnumMachinesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectsA: Pointer;

function PdhEnumObjectsA;
begin
  GetProcedureAddress(_PdhEnumObjectsA, PdhLib, 'PdhEnumObjectsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectsA]
  end;
end;
{$ELSE}
function PdhEnumObjectsA; external PdhLib name 'PdhEnumObjectsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectsW: Pointer;

function PdhEnumObjectsW;
begin
  GetProcedureAddress(_PdhEnumObjectsW, PdhLib, 'PdhEnumObjectsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectsW]
  end;
end;
{$ELSE}
function PdhEnumObjectsW; external PdhLib name 'PdhEnumObjectsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjects: Pointer;

function PdhEnumObjects;
begin
  GetProcedureAddress(_PdhEnumObjects, PdhLib, 'PdhEnumObjectsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjects]
  end;
end;
{$ELSE}
function PdhEnumObjects; external PdhLib name 'PdhEnumObjectsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjects: Pointer;

function PdhEnumObjects;
begin
  GetProcedureAddress(_PdhEnumObjects, PdhLib, 'PdhEnumObjectsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjects]
  end;
end;
{$ELSE}
function PdhEnumObjects; external PdhLib name 'PdhEnumObjectsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItemsA: Pointer;

function PdhEnumObjectItemsA;
begin
  GetProcedureAddress(_PdhEnumObjectItemsA, PdhLib, 'PdhEnumObjectItemsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItemsA]
  end;
end;
{$ELSE}
function PdhEnumObjectItemsA; external PdhLib name 'PdhEnumObjectItemsA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItemsW: Pointer;

function PdhEnumObjectItemsW;
begin
  GetProcedureAddress(_PdhEnumObjectItemsW, PdhLib, 'PdhEnumObjectItemsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItemsW]
  end;
end;
{$ELSE}
function PdhEnumObjectItemsW; external PdhLib name 'PdhEnumObjectItemsW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItems: Pointer;

function PdhEnumObjectItems;
begin
  GetProcedureAddress(_PdhEnumObjectItems, PdhLib, 'PdhEnumObjectItemsW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItems]
  end;
end;
{$ELSE}
function PdhEnumObjectItems; external PdhLib name 'PdhEnumObjectItemsW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItems: Pointer;

function PdhEnumObjectItems;
begin
  GetProcedureAddress(_PdhEnumObjectItems, PdhLib, 'PdhEnumObjectItemsA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItems]
  end;
end;
{$ELSE}
function PdhEnumObjectItems; external PdhLib name 'PdhEnumObjectItemsA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhMakeCounterPathA: Pointer;

function PdhMakeCounterPathA;
begin
  GetProcedureAddress(_PdhMakeCounterPathA, PdhLib, 'PdhMakeCounterPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhMakeCounterPathA]
  end;
end;
{$ELSE}
function PdhMakeCounterPathA; external PdhLib name 'PdhMakeCounterPathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhMakeCounterPathW: Pointer;

function PdhMakeCounterPathW;
begin
  GetProcedureAddress(_PdhMakeCounterPathW, PdhLib, 'PdhMakeCounterPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhMakeCounterPathW]
  end;
end;
{$ELSE}
function PdhMakeCounterPathW; external PdhLib name 'PdhMakeCounterPathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhMakeCounterPath: Pointer;

function PdhMakeCounterPath;
begin
  GetProcedureAddress(_PdhMakeCounterPath, PdhLib, 'PdhMakeCounterPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhMakeCounterPath]
  end;
end;
{$ELSE}
function PdhMakeCounterPath; external PdhLib name 'PdhMakeCounterPathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhMakeCounterPath: Pointer;

function PdhMakeCounterPath;
begin
  GetProcedureAddress(_PdhMakeCounterPath, PdhLib, 'PdhMakeCounterPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhMakeCounterPath]
  end;
end;
{$ELSE}
function PdhMakeCounterPath; external PdhLib name 'PdhMakeCounterPathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhParseCounterPathA: Pointer;

function PdhParseCounterPathA;
begin
  GetProcedureAddress(_PdhParseCounterPathA, PdhLib, 'PdhParseCounterPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseCounterPathA]
  end;
end;
{$ELSE}
function PdhParseCounterPathA; external PdhLib name 'PdhParseCounterPathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhParseCounterPathW: Pointer;

function PdhParseCounterPathW;
begin
  GetProcedureAddress(_PdhParseCounterPathW, PdhLib, 'PdhParseCounterPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseCounterPathW]
  end;
end;
{$ELSE}
function PdhParseCounterPathW; external PdhLib name 'PdhParseCounterPathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhParseCounterPath: Pointer;

function PdhParseCounterPath;
begin
  GetProcedureAddress(_PdhParseCounterPath, PdhLib, 'PdhParseCounterPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseCounterPath]
  end;
end;
{$ELSE}
function PdhParseCounterPath; external PdhLib name 'PdhParseCounterPathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhParseCounterPath: Pointer;

function PdhParseCounterPath;
begin
  GetProcedureAddress(_PdhParseCounterPath, PdhLib, 'PdhParseCounterPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseCounterPath]
  end;
end;
{$ELSE}
function PdhParseCounterPath; external PdhLib name 'PdhParseCounterPathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

function PDH_PATH_LANG_FLAGS(LangId, Flags: DWORD): DWORD;
begin
  Result := DWORD(((LangId and $0000FFFF) shl 16) or (Flags and $0000FFFF));
end;


{$IFDEF DYNAMIC_LINK}
var
  _PdhParseInstanceNameA: Pointer;

function PdhParseInstanceNameA;
begin
  GetProcedureAddress(_PdhParseInstanceNameA, PdhLib, 'PdhParseInstanceNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseInstanceNameA]
  end;
end;
{$ELSE}
function PdhParseInstanceNameA; external PdhLib name 'PdhParseInstanceNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhParseInstanceNameW: Pointer;

function PdhParseInstanceNameW;
begin
  GetProcedureAddress(_PdhParseInstanceNameW, PdhLib, 'PdhParseInstanceNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseInstanceNameW]
  end;
end;
{$ELSE}
function PdhParseInstanceNameW; external PdhLib name 'PdhParseInstanceNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhParseInstanceName: Pointer;

function PdhParseInstanceName;
begin
  GetProcedureAddress(_PdhParseInstanceName, PdhLib, 'PdhParseInstanceNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseInstanceName]
  end;
end;
{$ELSE}
function PdhParseInstanceName; external PdhLib name 'PdhParseInstanceNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhParseInstanceName: Pointer;

function PdhParseInstanceName;
begin
  GetProcedureAddress(_PdhParseInstanceName, PdhLib, 'PdhParseInstanceNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhParseInstanceName]
  end;
end;
{$ELSE}
function PdhParseInstanceName; external PdhLib name 'PdhParseInstanceNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhValidatePathA: Pointer;

function PdhValidatePathA;
begin
  GetProcedureAddress(_PdhValidatePathA, PdhLib, 'PdhValidatePathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhValidatePathA]
  end;
end;
{$ELSE}
function PdhValidatePathA; external PdhLib name 'PdhValidatePathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhValidatePathW: Pointer;

function PdhValidatePathW;
begin
  GetProcedureAddress(_PdhValidatePathW, PdhLib, 'PdhValidatePathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhValidatePathW]
  end;
end;
{$ELSE}
function PdhValidatePathW; external PdhLib name 'PdhValidatePathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhValidatePath: Pointer;

function PdhValidatePath;
begin
  GetProcedureAddress(_PdhValidatePath, PdhLib, 'PdhValidatePathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhValidatePath]
  end;
end;
{$ELSE}
function PdhValidatePath; external PdhLib name 'PdhValidatePathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhValidatePath: Pointer;

function PdhValidatePath;
begin
  GetProcedureAddress(_PdhValidatePath, PdhLib, 'PdhValidatePathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhValidatePath]
  end;
end;
{$ELSE}
function PdhValidatePath; external PdhLib name 'PdhValidatePathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObjectA: Pointer;

function PdhGetDefaultPerfObjectA;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObjectA, PdhLib, 'PdhGetDefaultPerfObjectA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObjectA]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObjectA; external PdhLib name 'PdhGetDefaultPerfObjectA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObjectW: Pointer;

function PdhGetDefaultPerfObjectW;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObjectW, PdhLib, 'PdhGetDefaultPerfObjectW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObjectW]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObjectW; external PdhLib name 'PdhGetDefaultPerfObjectW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObject: Pointer;

function PdhGetDefaultPerfObject;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObject, PdhLib, 'PdhGetDefaultPerfObjectW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObject]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObject; external PdhLib name 'PdhGetDefaultPerfObjectW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObject: Pointer;

function PdhGetDefaultPerfObject;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObject, PdhLib, 'PdhGetDefaultPerfObjectA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObject]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObject; external PdhLib name 'PdhGetDefaultPerfObjectA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounterA: Pointer;

function PdhGetDefaultPerfCounterA;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounterA, PdhLib, 'PdhGetDefaultPerfCounterA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounterA]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounterA; external PdhLib name 'PdhGetDefaultPerfCounterA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounterW: Pointer;

function PdhGetDefaultPerfCounterW;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounterW, PdhLib, 'PdhGetDefaultPerfCounterW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounterW]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounterW; external PdhLib name 'PdhGetDefaultPerfCounterW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounter: Pointer;

function PdhGetDefaultPerfCounter;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounter, PdhLib, 'PdhGetDefaultPerfCounterW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounter]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounter; external PdhLib name 'PdhGetDefaultPerfCounterW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounter: Pointer;

function PdhGetDefaultPerfCounter;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounter, PdhLib, 'PdhGetDefaultPerfCounterA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounter]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounter; external PdhLib name 'PdhGetDefaultPerfCounterA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCountersA: Pointer;

function PdhBrowseCountersA;
begin
  GetProcedureAddress(_PdhBrowseCountersA, PdhLib, 'PdhBrowseCountersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCountersA]
  end;
end;
{$ELSE}
function PdhBrowseCountersA; external PdhLib name 'PdhBrowseCountersA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCountersW: Pointer;

function PdhBrowseCountersW;
begin
  GetProcedureAddress(_PdhBrowseCountersW, PdhLib, 'PdhBrowseCountersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCountersW]
  end;
end;
{$ELSE}
function PdhBrowseCountersW; external PdhLib name 'PdhBrowseCountersW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCounters: Pointer;

function PdhBrowseCounters;
begin
  GetProcedureAddress(_PdhBrowseCounters, PdhLib, 'PdhBrowseCountersW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCounters]
  end;
end;
{$ELSE}
function PdhBrowseCounters; external PdhLib name 'PdhBrowseCountersW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCounters: Pointer;

function PdhBrowseCounters;
begin
  GetProcedureAddress(_PdhBrowseCounters, PdhLib, 'PdhBrowseCountersA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCounters]
  end;
end;
{$ELSE}
function PdhBrowseCounters; external PdhLib name 'PdhBrowseCountersA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandCounterPathA: Pointer;

function PdhExpandCounterPathA;
begin
  GetProcedureAddress(_PdhExpandCounterPathA, PdhLib, 'PdhExpandCounterPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandCounterPathA]
  end;
end;
{$ELSE}
function PdhExpandCounterPathA; external PdhLib name 'PdhExpandCounterPathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandCounterPathW: Pointer;

function PdhExpandCounterPathW;
begin
  GetProcedureAddress(_PdhExpandCounterPathW, PdhLib, 'PdhExpandCounterPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandCounterPathW]
  end;
end;
{$ELSE}
function PdhExpandCounterPathW; external PdhLib name 'PdhExpandCounterPathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandCounterPath: Pointer;

function PdhExpandCounterPath;
begin
  GetProcedureAddress(_PdhExpandCounterPath, PdhLib, 'PdhExpandCounterPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandCounterPath]
  end;
end;
{$ELSE}
function PdhExpandCounterPath; external PdhLib name 'PdhExpandCounterPathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandCounterPath: Pointer;

function PdhExpandCounterPath;
begin
  GetProcedureAddress(_PdhExpandCounterPath, PdhLib, 'PdhExpandCounterPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandCounterPath]
  end;
end;
{$ELSE}
function PdhExpandCounterPath; external PdhLib name 'PdhExpandCounterPathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfNameByIndexA: Pointer;

function PdhLookupPerfNameByIndexA;
begin
  GetProcedureAddress(_PdhLookupPerfNameByIndexA, PdhLib, 'PdhLookupPerfNameByIndexA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfNameByIndexA]
  end;
end;
{$ELSE}
function PdhLookupPerfNameByIndexA; external PdhLib name 'PdhLookupPerfNameByIndexA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfNameByIndexW: Pointer;

function PdhLookupPerfNameByIndexW;
begin
  GetProcedureAddress(_PdhLookupPerfNameByIndexW, PdhLib, 'PdhLookupPerfNameByIndexW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfNameByIndexW]
  end;
end;
{$ELSE}
function PdhLookupPerfNameByIndexW; external PdhLib name 'PdhLookupPerfNameByIndexW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfNameByIndex: Pointer;

function PdhLookupPerfNameByIndex;
begin
  GetProcedureAddress(_PdhLookupPerfNameByIndex, PdhLib, 'PdhLookupPerfNameByIndexW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfNameByIndex]
  end;
end;
{$ELSE}
function PdhLookupPerfNameByIndex; external PdhLib name 'PdhLookupPerfNameByIndexW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfNameByIndex: Pointer;

function PdhLookupPerfNameByIndex;
begin
  GetProcedureAddress(_PdhLookupPerfNameByIndex, PdhLib, 'PdhLookupPerfNameByIndexA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfNameByIndex]
  end;
end;
{$ELSE}
function PdhLookupPerfNameByIndex; external PdhLib name 'PdhLookupPerfNameByIndexA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfIndexByNameA: Pointer;

function PdhLookupPerfIndexByNameA;
begin
  GetProcedureAddress(_PdhLookupPerfIndexByNameA, PdhLib, 'PdhLookupPerfIndexByNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfIndexByNameA]
  end;
end;
{$ELSE}
function PdhLookupPerfIndexByNameA; external PdhLib name 'PdhLookupPerfIndexByNameA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfIndexByNameW: Pointer;

function PdhLookupPerfIndexByNameW;
begin
  GetProcedureAddress(_PdhLookupPerfIndexByNameW, PdhLib, 'PdhLookupPerfIndexByNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfIndexByNameW]
  end;
end;
{$ELSE}
function PdhLookupPerfIndexByNameW; external PdhLib name 'PdhLookupPerfIndexByNameW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfIndexByName: Pointer;

function PdhLookupPerfIndexByName;
begin
  GetProcedureAddress(_PdhLookupPerfIndexByName, PdhLib, 'PdhLookupPerfIndexByNameW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfIndexByName]
  end;
end;
{$ELSE}
function PdhLookupPerfIndexByName; external PdhLib name 'PdhLookupPerfIndexByNameW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhLookupPerfIndexByName: Pointer;

function PdhLookupPerfIndexByName;
begin
  GetProcedureAddress(_PdhLookupPerfIndexByName, PdhLib, 'PdhLookupPerfIndexByNameA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhLookupPerfIndexByName]
  end;
end;
{$ELSE}
function PdhLookupPerfIndexByName; external PdhLib name 'PdhLookupPerfIndexByNameA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPathA: Pointer;

function PdhExpandWildCardPathA;
begin
  GetProcedureAddress(_PdhExpandWildCardPathA, PdhLib, 'PdhExpandWildCardPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPathA]
  end;
end;
{$ELSE}
function PdhExpandWildCardPathA; external PdhLib name 'PdhExpandWildCardPathA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPathW: Pointer;

function PdhExpandWildCardPathW;
begin
  GetProcedureAddress(_PdhExpandWildCardPathW, PdhLib, 'PdhExpandWildCardPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPathW]
  end;
end;
{$ELSE}
function PdhExpandWildCardPathW; external PdhLib name 'PdhExpandWildCardPathW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPath: Pointer;

function PdhExpandWildCardPath;
begin
  GetProcedureAddress(_PdhExpandWildCardPath, PdhLib, 'PdhExpandWildCardPathW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPath]
  end;
end;
{$ELSE}
function PdhExpandWildCardPath; external PdhLib name 'PdhExpandWildCardPathW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPath: Pointer;

function PdhExpandWildCardPath;
begin
  GetProcedureAddress(_PdhExpandWildCardPath, PdhLib, 'PdhExpandWildCardPathA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPath]
  end;
end;
{$ELSE}
function PdhExpandWildCardPath; external PdhLib name 'PdhExpandWildCardPathA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenLogA: Pointer;

function PdhOpenLogA;
begin
  GetProcedureAddress(_PdhOpenLogA, PdhLib, 'PdhOpenLogA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenLogA]
  end;
end;
{$ELSE}
function PdhOpenLogA; external PdhLib name 'PdhOpenLogA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenLogW: Pointer;

function PdhOpenLogW;
begin
  GetProcedureAddress(_PdhOpenLogW, PdhLib, 'PdhOpenLogW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenLogW]
  end;
end;
{$ELSE}
function PdhOpenLogW; external PdhLib name 'PdhOpenLogW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenLog: Pointer;

function PdhOpenLog;
begin
  GetProcedureAddress(_PdhOpenLog, PdhLib, 'PdhOpenLogW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenLog]
  end;
end;
{$ELSE}
function PdhOpenLog; external PdhLib name 'PdhOpenLogW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenLog: Pointer;

function PdhOpenLog;
begin
  GetProcedureAddress(_PdhOpenLog, PdhLib, 'PdhOpenLogA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenLog]
  end;
end;
{$ELSE}
function PdhOpenLog; external PdhLib name 'PdhOpenLogA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhUpdateLogA: Pointer;

function PdhUpdateLogA;
begin
  GetProcedureAddress(_PdhUpdateLogA, PdhLib, 'PdhUpdateLogA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhUpdateLogA]
  end;
end;
{$ELSE}
function PdhUpdateLogA; external PdhLib name 'PdhUpdateLogA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhUpdateLogW: Pointer;

function PdhUpdateLogW;
begin
  GetProcedureAddress(_PdhUpdateLogW, PdhLib, 'PdhUpdateLogW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhUpdateLogW]
  end;
end;
{$ELSE}
function PdhUpdateLogW; external PdhLib name 'PdhUpdateLogW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhUpdateLog: Pointer;

function PdhUpdateLog;
begin
  GetProcedureAddress(_PdhUpdateLog, PdhLib, 'PdhUpdateLogW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhUpdateLog]
  end;
end;
{$ELSE}
function PdhUpdateLog; external PdhLib name 'PdhUpdateLogW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhUpdateLog: Pointer;

function PdhUpdateLog;
begin
  GetProcedureAddress(_PdhUpdateLog, PdhLib, 'PdhUpdateLogA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhUpdateLog]
  end;
end;
{$ELSE}
function PdhUpdateLog; external PdhLib name 'PdhUpdateLogA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhUpdateLogFileCatalog: Pointer;

function PdhUpdateLogFileCatalog;
begin
  GetProcedureAddress(_PdhUpdateLogFileCatalog, PdhLib, 'PdhUpdateLogFileCatalog');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhUpdateLogFileCatalog]
  end;
end;
{$ELSE}
function PdhUpdateLogFileCatalog; external PdhLib name 'PdhUpdateLogFileCatalog';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetLogFileSize: Pointer;

function PdhGetLogFileSize;
begin
  GetProcedureAddress(_PdhGetLogFileSize, PdhLib, 'PdhGetLogFileSize');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetLogFileSize]
  end;
end;
{$ELSE}
function PdhGetLogFileSize; external PdhLib name 'PdhGetLogFileSize';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCloseLog: Pointer;

function PdhCloseLog;
begin
  GetProcedureAddress(_PdhCloseLog, PdhLib, 'PdhCloseLog');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCloseLog]
  end;
end;
{$ELSE}
function PdhCloseLog; external PdhLib name 'PdhCloseLog';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSelectDataSourceA: Pointer;

function PdhSelectDataSourceA;
begin
  GetProcedureAddress(_PdhSelectDataSourceA, PdhLib, 'PdhSelectDataSourceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSelectDataSourceA]
  end;
end;
{$ELSE}
function PdhSelectDataSourceA; external PdhLib name 'PdhSelectDataSourceA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSelectDataSourceW: Pointer;

function PdhSelectDataSourceW;
begin
  GetProcedureAddress(_PdhSelectDataSourceW, PdhLib, 'PdhSelectDataSourceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSelectDataSourceW]
  end;
end;
{$ELSE}
function PdhSelectDataSourceW; external PdhLib name 'PdhSelectDataSourceW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSelectDataSource: Pointer;

function PdhSelectDataSource;
begin
  GetProcedureAddress(_PdhSelectDataSource, PdhLib, 'PdhSelectDataSourceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSelectDataSource]
  end;
end;
{$ELSE}
function PdhSelectDataSource; external PdhLib name 'PdhSelectDataSourceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSelectDataSource: Pointer;

function PdhSelectDataSource;
begin
  GetProcedureAddress(_PdhSelectDataSource, PdhLib, 'PdhSelectDataSourceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSelectDataSource]
  end;
end;
{$ELSE}
function PdhSelectDataSource; external PdhLib name 'PdhSelectDataSourceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhIsRealTimeQuery: Pointer;

function PdhIsRealTimeQuery;
begin
  GetProcedureAddress(_PdhIsRealTimeQuery, PdhLib, 'PdhIsRealTimeQuery');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhIsRealTimeQuery]
  end;
end;
{$ELSE}
function PdhIsRealTimeQuery; external PdhLib name 'PdhIsRealTimeQuery';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSetQueryTimeRange: Pointer;

function PdhSetQueryTimeRange;
begin
  GetProcedureAddress(_PdhSetQueryTimeRange, PdhLib, 'PdhSetQueryTimeRange');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSetQueryTimeRange]
  end;
end;
{$ELSE}
function PdhSetQueryTimeRange; external PdhLib name 'PdhSetQueryTimeRange';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDataSourceTimeRangeA: Pointer;

function PdhGetDataSourceTimeRangeA;
begin
  GetProcedureAddress(_PdhGetDataSourceTimeRangeA, PdhLib, 'PdhGetDataSourceTimeRangeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDataSourceTimeRangeA]
  end;
end;
{$ELSE}
function PdhGetDataSourceTimeRangeA; external PdhLib name 'PdhGetDataSourceTimeRangeA';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDataSourceTimeRangeW: Pointer;

function PdhGetDataSourceTimeRangeW;
begin
  GetProcedureAddress(_PdhGetDataSourceTimeRangeW, PdhLib, 'PdhGetDataSourceTimeRangeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDataSourceTimeRangeW]
  end;
end;
{$ELSE}
function PdhGetDataSourceTimeRangeW; external PdhLib name 'PdhGetDataSourceTimeRangeW';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDataSourceTimeRange: Pointer;

function PdhGetDataSourceTimeRange;
begin
  GetProcedureAddress(_PdhGetDataSourceTimeRange, PdhLib, 'PdhGetDataSourceTimeRangeW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDataSourceTimeRange]
  end;
end;
{$ELSE}
function PdhGetDataSourceTimeRange; external PdhLib name 'PdhGetDataSourceTimeRangeW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDataSourceTimeRange: Pointer;

function PdhGetDataSourceTimeRange;
begin
  GetProcedureAddress(_PdhGetDataSourceTimeRange, PdhLib, 'PdhGetDataSourceTimeRangeA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDataSourceTimeRange]
  end;
end;
{$ELSE}
function PdhGetDataSourceTimeRange; external PdhLib name 'PdhGetDataSourceTimeRangeA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCollectQueryDataEx: Pointer;

function PdhCollectQueryDataEx;
begin
  GetProcedureAddress(_PdhCollectQueryDataEx, PdhLib, 'PdhCollectQueryDataEx');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCollectQueryDataEx]
  end;
end;
{$ELSE}
function PdhCollectQueryDataEx; external PdhLib name 'PdhCollectQueryDataEx';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhFormatFromRawValue: Pointer;

function PdhFormatFromRawValue;
begin
  GetProcedureAddress(_PdhFormatFromRawValue, PdhLib, 'PdhFormatFromRawValue');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhFormatFromRawValue]
  end;
end;
{$ELSE}
function PdhFormatFromRawValue; external PdhLib name 'PdhFormatFromRawValue';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetCounterTimeBase: Pointer;

function PdhGetCounterTimeBase;
begin
  GetProcedureAddress(_PdhGetCounterTimeBase, PdhLib, 'PdhGetCounterTimeBase');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetCounterTimeBase]
  end;
end;
{$ELSE}
function PdhGetCounterTimeBase; external PdhLib name 'PdhGetCounterTimeBase';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhReadRawLogRecord: Pointer;

function PdhReadRawLogRecord;
begin
  GetProcedureAddress(_PdhReadRawLogRecord, PdhLib, 'PdhReadRawLogRecord');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhReadRawLogRecord]
  end;
end;
{$ELSE}
function PdhReadRawLogRecord; external PdhLib name 'PdhReadRawLogRecord';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSetDefaultRealTimeDataSource: Pointer;

function PdhSetDefaultRealTimeDataSource;
begin
  GetProcedureAddress(_PdhSetDefaultRealTimeDataSource, PdhLib, 'PdhSetDefaultRealTimeDataSource');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSetDefaultRealTimeDataSource]
  end;
end;
{$ELSE}
function PdhSetDefaultRealTimeDataSource; external PdhLib name 'PdhSetDefaultRealTimeDataSource';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBindInputDataSourceW: Pointer;

function PdhBindInputDataSourceW;
begin
  GetProcedureAddress(_PdhBindInputDataSourceW, PdhLib, 'PdhBindInputDataSourceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBindInputDataSourceW]
  end;
end;
{$ELSE}
function PdhBindInputDataSourceW; external PdhLib name 'PdhBindInputDataSourceW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBindInputDataSourceA: Pointer;

function PdhBindInputDataSourceA;
begin
  GetProcedureAddress(_PdhBindInputDataSourceA, PdhLib, 'PdhBindInputDataSourceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBindInputDataSourceA]
  end;
end;
{$ELSE}
function PdhBindInputDataSourceA; external PdhLib name 'PdhBindInputDataSourceA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBindInputDataSource: Pointer;

function PdhBindInputDataSource;
begin
  GetProcedureAddress(_PdhBindInputDataSource, PdhLib, 'PdhBindInputDataSourceW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBindInputDataSource]
  end;
end;
{$ELSE}
function PdhBindInputDataSource; external PdhLib name 'PdhBindInputDataSourceW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBindInputDataSource: Pointer;

function PdhBindInputDataSource;
begin
  GetProcedureAddress(_PdhBindInputDataSource, PdhLib, 'PdhBindInputDataSourceA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBindInputDataSource]
  end;
end;
{$ELSE}
function PdhBindInputDataSource; external PdhLib name 'PdhBindInputDataSourceA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhOpenQueryH: Pointer;

function PdhOpenQueryH;
begin
  GetProcedureAddress(_PdhOpenQueryH, PdhLib, 'PdhOpenQueryH');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhOpenQueryH]
  end;
end;
{$ELSE}
function PdhOpenQueryH; external PdhLib name 'PdhOpenQueryH';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachinesHW: Pointer;

function PdhEnumMachinesHW;
begin
  GetProcedureAddress(_PdhEnumMachinesHW, PdhLib, 'PdhEnumMachinesHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachinesHW]
  end;
end;
{$ELSE}
function PdhEnumMachinesHW; external PdhLib name 'PdhEnumMachinesHW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachinesHA: Pointer;

function PdhEnumMachinesHA;
begin
  GetProcedureAddress(_PdhEnumMachinesHA, PdhLib, 'PdhEnumMachinesHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachinesHA]
  end;
end;
{$ELSE}
function PdhEnumMachinesHA; external PdhLib name 'PdhEnumMachinesHA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachinesH: Pointer;

function PdhEnumMachinesH;
begin
  GetProcedureAddress(_PdhEnumMachinesH, PdhLib, 'PdhEnumMachinesHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachinesH]
  end;
end;
{$ELSE}
function PdhEnumMachinesH; external PdhLib name 'PdhEnumMachinesHW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumMachinesH: Pointer;

function PdhEnumMachinesH;
begin
  GetProcedureAddress(_PdhEnumMachinesH, PdhLib, 'PdhEnumMachinesHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumMachinesH]
  end;
end;
{$ELSE}
function PdhEnumMachinesH; external PdhLib name 'PdhEnumMachinesHA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectsHW: Pointer;

function PdhEnumObjectsHW;
begin
  GetProcedureAddress(_PdhEnumObjectsHW, PdhLib, 'PdhEnumObjectsHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectsHW]
  end;
end;
{$ELSE}
function PdhEnumObjectsHW; external PdhLib name 'PdhEnumObjectsHW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectsHA: Pointer;

function PdhEnumObjectsHA;
begin
  GetProcedureAddress(_PdhEnumObjectsHA, PdhLib, 'PdhEnumObjectsHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectsHA]
  end;
end;
{$ELSE}
function PdhEnumObjectsHA; external PdhLib name 'PdhEnumObjectsHA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectsH: Pointer;

function PdhEnumObjectsH;
begin
  GetProcedureAddress(_PdhEnumObjectsH, PdhLib, 'PdhEnumObjectsHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectsH]
  end;
end;
{$ELSE}
function PdhEnumObjectsH; external PdhLib name 'PdhEnumObjectsHW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectsH: Pointer;

function PdhEnumObjectsH;
begin
  GetProcedureAddress(_PdhEnumObjectsH, PdhLib, 'PdhEnumObjectsHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectsH]
  end;
end;
{$ELSE}
function PdhEnumObjectsH; external PdhLib name 'PdhEnumObjectsHA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItemsHW: Pointer;

function PdhEnumObjectItemsHW;
begin
  GetProcedureAddress(_PdhEnumObjectItemsHW, PdhLib, 'PdhEnumObjectItemsHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItemsHW]
  end;
end;
{$ELSE}
function PdhEnumObjectItemsHW; external PdhLib name 'PdhEnumObjectItemsHW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItemsHA: Pointer;

function PdhEnumObjectItemsHA;
begin
  GetProcedureAddress(_PdhEnumObjectItemsHA, PdhLib, 'PdhEnumObjectItemsHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItemsHA]
  end;
end;
{$ELSE}
function PdhEnumObjectItemsHA; external PdhLib name 'PdhEnumObjectItemsHA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItemsH: Pointer;

function PdhEnumObjectItemsH;
begin
  GetProcedureAddress(_PdhEnumObjectItemsH, PdhLib, 'PdhEnumObjectItemsHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItemsH]
  end;
end;
{$ELSE}
function PdhEnumObjectItemsH; external PdhLib name 'PdhEnumObjectItemsHW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumObjectItemsH: Pointer;

function PdhEnumObjectItemsH;
begin
  GetProcedureAddress(_PdhEnumObjectItemsH, PdhLib, 'PdhEnumObjectItemsHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumObjectItemsH]
  end;
end;
{$ELSE}
function PdhEnumObjectItemsH; external PdhLib name 'PdhEnumObjectItemsHA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPathHW: Pointer;

function PdhExpandWildCardPathHW;
begin
  GetProcedureAddress(_PdhExpandWildCardPathHW, PdhLib, 'PdhExpandWildCardPathHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPathHW]
  end;
end;
{$ELSE}
function PdhExpandWildCardPathHW; external PdhLib name 'PdhExpandWildCardPathHW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPathHA: Pointer;

function PdhExpandWildCardPathHA;
begin
  GetProcedureAddress(_PdhExpandWildCardPathHA, PdhLib, 'PdhExpandWildCardPathHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPathHA]
  end;
end;
{$ELSE}
function PdhExpandWildCardPathHA; external PdhLib name 'PdhExpandWildCardPathHA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPathH: Pointer;

function PdhExpandWildCardPathH;
begin
  GetProcedureAddress(_PdhExpandWildCardPathH, PdhLib, 'PdhExpandWildCardPathHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPathH]
  end;
end;
{$ELSE}
function PdhExpandWildCardPathH; external PdhLib name 'PdhExpandWildCardPathHW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhExpandWildCardPathH: Pointer;

function PdhExpandWildCardPathH;
begin
  GetProcedureAddress(_PdhExpandWildCardPathH, PdhLib, 'PdhExpandWildCardPathHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhExpandWildCardPathH]
  end;
end;
{$ELSE}
function PdhExpandWildCardPathH; external PdhLib name 'PdhExpandWildCardPathHA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDataSourceTimeRangeH: Pointer;

function PdhGetDataSourceTimeRangeH;
begin
  GetProcedureAddress(_PdhGetDataSourceTimeRangeH, PdhLib, 'PdhGetDataSourceTimeRangeH');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDataSourceTimeRangeH]
  end;
end;
{$ELSE}
function PdhGetDataSourceTimeRangeH; external PdhLib name 'PdhGetDataSourceTimeRangeH';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObjectHW: Pointer;

function PdhGetDefaultPerfObjectHW;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObjectHW, PdhLib, 'PdhGetDefaultPerfObjectHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObjectHW]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObjectHW; external PdhLib name 'PdhGetDefaultPerfObjectHW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObjectHA: Pointer;

function PdhGetDefaultPerfObjectHA;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObjectHA, PdhLib, 'PdhGetDefaultPerfObjectHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObjectHA]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObjectHA; external PdhLib name 'PdhGetDefaultPerfObjectHA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObjectH: Pointer;

function PdhGetDefaultPerfObjectH;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObjectH, PdhLib, 'PdhGetDefaultPerfObjectHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObjectH]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObjectH; external PdhLib name 'PdhGetDefaultPerfObjectHW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfObjectH: Pointer;

function PdhGetDefaultPerfObjectH;
begin
  GetProcedureAddress(_PdhGetDefaultPerfObjectH, PdhLib, 'PdhGetDefaultPerfObjectHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfObjectH]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfObjectH; external PdhLib name 'PdhGetDefaultPerfObjectHA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounterHW: Pointer;

function PdhGetDefaultPerfCounterHW;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounterHW, PdhLib, 'PdhGetDefaultPerfCounterHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounterHW]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounterHW; external PdhLib name 'PdhGetDefaultPerfCounterHW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounterHA: Pointer;

function PdhGetDefaultPerfCounterHA;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounterHA, PdhLib, 'PdhGetDefaultPerfCounterHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounterHA]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounterHA; external PdhLib name 'PdhGetDefaultPerfCounterHA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounterH: Pointer;

function PdhGetDefaultPerfCounterH;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounterH, PdhLib, 'PdhGetDefaultPerfCounterHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounterH]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounterH; external PdhLib name 'PdhGetDefaultPerfCounterHW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetDefaultPerfCounterH: Pointer;

function PdhGetDefaultPerfCounterH;
begin
  GetProcedureAddress(_PdhGetDefaultPerfCounterH, PdhLib, 'PdhGetDefaultPerfCounterHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetDefaultPerfCounterH]
  end;
end;
{$ELSE}
function PdhGetDefaultPerfCounterH; external PdhLib name 'PdhGetDefaultPerfCounterHA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCountersHW: Pointer;

function PdhBrowseCountersHW;
begin
  GetProcedureAddress(_PdhBrowseCountersHW, PdhLib, 'PdhBrowseCountersHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCountersHW]
  end;
end;
{$ELSE}
function PdhBrowseCountersHW; external PdhLib name 'PdhBrowseCountersHW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCountersHA: Pointer;

function PdhBrowseCountersHA;
begin
  GetProcedureAddress(_PdhBrowseCountersHA, PdhLib, 'PdhBrowseCountersHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCountersHA]
  end;
end;
{$ELSE}
function PdhBrowseCountersHA; external PdhLib name 'PdhBrowseCountersHA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCountersH: Pointer;

function PdhBrowseCountersH;
begin
  GetProcedureAddress(_PdhBrowseCountersH, PdhLib, 'PdhBrowseCountersHW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCountersH]
  end;
end;
{$ELSE}
function PdhBrowseCountersH; external PdhLib name 'PdhBrowseCountersHW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhBrowseCountersH: Pointer;

function PdhBrowseCountersH;
begin
  GetProcedureAddress(_PdhBrowseCountersH, PdhLib, 'PdhBrowseCountersHA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhBrowseCountersH]
  end;
end;
{$ELSE}
function PdhBrowseCountersH; external PdhLib name 'PdhBrowseCountersHA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhVerifySQLDBW: Pointer;

function PdhVerifySQLDBW;
begin
  GetProcedureAddress(_PdhVerifySQLDBW, PdhLib, 'PdhVerifySQLDBW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhVerifySQLDBW]
  end;
end;
{$ELSE}
function PdhVerifySQLDBW; external PdhLib name 'PdhVerifySQLDBW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhVerifySQLDBA: Pointer;

function PdhVerifySQLDBA;
begin
  GetProcedureAddress(_PdhVerifySQLDBA, PdhLib, 'PdhVerifySQLDBA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhVerifySQLDBA]
  end;
end;
{$ELSE}
function PdhVerifySQLDBA; external PdhLib name 'PdhVerifySQLDBA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhVerifySQLDB: Pointer;

function PdhVerifySQLDB;
begin
  GetProcedureAddress(_PdhVerifySQLDB, PdhLib, 'PdhVerifySQLDBW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhVerifySQLDB]
  end;
end;
{$ELSE}
function PdhVerifySQLDB; external PdhLib name 'PdhVerifySQLDBW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhVerifySQLDB: Pointer;

function PdhVerifySQLDB;
begin
  GetProcedureAddress(_PdhVerifySQLDB, PdhLib, 'PdhVerifySQLDBA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhVerifySQLDB]
  end;
end;
{$ELSE}
function PdhVerifySQLDB; external PdhLib name 'PdhVerifySQLDBA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCreateSQLTablesW: Pointer;

function PdhCreateSQLTablesW;
begin
  GetProcedureAddress(_PdhCreateSQLTablesW, PdhLib, 'PdhCreateSQLTablesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCreateSQLTablesW]
  end;
end;
{$ELSE}
function PdhCreateSQLTablesW; external PdhLib name 'PdhCreateSQLTablesW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCreateSQLTablesA: Pointer;

function PdhCreateSQLTablesA;
begin
  GetProcedureAddress(_PdhCreateSQLTablesA, PdhLib, 'PdhCreateSQLTablesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCreateSQLTablesA]
  end;
end;
{$ELSE}
function PdhCreateSQLTablesA; external PdhLib name 'PdhCreateSQLTablesA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCreateSQLTables: Pointer;

function PdhCreateSQLTables;
begin
  GetProcedureAddress(_PdhCreateSQLTables, PdhLib, 'PdhCreateSQLTablesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCreateSQLTables]
  end;
end;
{$ELSE}
function PdhCreateSQLTables; external PdhLib name 'PdhCreateSQLTablesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhCreateSQLTables: Pointer;

function PdhCreateSQLTables;
begin
  GetProcedureAddress(_PdhCreateSQLTables, PdhLib, 'PdhCreateSQLTablesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhCreateSQLTables]
  end;
end;
{$ELSE}
function PdhCreateSQLTables; external PdhLib name 'PdhCreateSQLTablesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumLogSetNamesW: Pointer;

function PdhEnumLogSetNamesW;
begin
  GetProcedureAddress(_PdhEnumLogSetNamesW, PdhLib, 'PdhEnumLogSetNamesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumLogSetNamesW]
  end;
end;
{$ELSE}
function PdhEnumLogSetNamesW; external PdhLib name 'PdhEnumLogSetNamesW';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumLogSetNamesA: Pointer;

function PdhEnumLogSetNamesA;
begin
  GetProcedureAddress(_PdhEnumLogSetNamesA, PdhLib, 'PdhEnumLogSetNamesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumLogSetNamesA]
  end;
end;
{$ELSE}
function PdhEnumLogSetNamesA; external PdhLib name 'PdhEnumLogSetNamesA';
{$ENDIF DYNAMIC_LINK}
{$IFDEF UNICODE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumLogSetNames: Pointer;

function PdhEnumLogSetNames;
begin
  GetProcedureAddress(_PdhEnumLogSetNames, PdhLib, 'PdhEnumLogSetNamesW');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumLogSetNames]
  end;
end;
{$ELSE}
function PdhEnumLogSetNames; external PdhLib name 'PdhEnumLogSetNamesW';
{$ENDIF DYNAMIC_LINK}
{$ELSE}

{$IFDEF DYNAMIC_LINK}
var
  _PdhEnumLogSetNames: Pointer;

function PdhEnumLogSetNames;
begin
  GetProcedureAddress(_PdhEnumLogSetNames, PdhLib, 'PdhEnumLogSetNamesA');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhEnumLogSetNames]
  end;
end;
{$ELSE}
function PdhEnumLogSetNames; external PdhLib name 'PdhEnumLogSetNamesA';
{$ENDIF DYNAMIC_LINK}
{$ENDIF}

{$IFDEF DYNAMIC_LINK}
var
  _PdhGetLogSetGUID: Pointer;

function PdhGetLogSetGUID;
begin
  GetProcedureAddress(_PdhGetLogSetGUID, PdhLib, 'PdhGetLogSetGUID');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhGetLogSetGUID]
  end;
end;
{$ELSE}
function PdhGetLogSetGUID; external PdhLib name 'PdhGetLogSetGUID';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _PdhSetLogSetRunID: Pointer;

function PdhSetLogSetRunID;
begin
  GetProcedureAddress(_PdhSetLogSetRunID, PdhLib, 'PdhSetLogSetRunID');
  asm
    mov esp, ebp
    pop ebp
    jmp [_PdhSetLogSetRunID]
  end;
end;
{$ELSE}
function PdhSetLogSetRunID; external PdhLib name 'PdhSetLogSetRunID';
{$ENDIF DYNAMIC_LINK}


end.
