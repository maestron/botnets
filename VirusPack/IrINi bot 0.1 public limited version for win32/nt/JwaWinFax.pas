{******************************************************************************}
{                                                       	               }
{ Windows FAX API interface unit for Object Pascal                             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winfax.h, released November 2001. The original Pascal  }
{ code is: WinFax.pas, released April 2002. The initial developer of the       }
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

unit JwaWinFax;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "winfax.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaWinError, JwaWinBase, JwaWinNT;

//
// FAX ERROR CODES
//

const
  FAX_ERR_START = 7001; // First fax specific error code
  {$EXTERNALSYM FAX_ERR_START}

  FAX_ERR_SRV_OUTOFMEMORY           = 7001;
  {$EXTERNALSYM FAX_ERR_SRV_OUTOFMEMORY}
  FAX_ERR_GROUP_NOT_FOUND           = 7002;
  {$EXTERNALSYM FAX_ERR_GROUP_NOT_FOUND}
  FAX_ERR_BAD_GROUP_CONFIGURATION   = 7003;
  {$EXTERNALSYM FAX_ERR_BAD_GROUP_CONFIGURATION}
  FAX_ERR_GROUP_IN_USE              = 7004;
  {$EXTERNALSYM FAX_ERR_GROUP_IN_USE}
  FAX_ERR_RULE_NOT_FOUND            = 7005;
  {$EXTERNALSYM FAX_ERR_RULE_NOT_FOUND}
  FAX_ERR_NOT_NTFS                  = 7006;
  {$EXTERNALSYM FAX_ERR_NOT_NTFS}
  FAX_ERR_DIRECTORY_IN_USE          = 7007;
  {$EXTERNALSYM FAX_ERR_DIRECTORY_IN_USE}
  FAX_ERR_FILE_ACCESS_DENIED        = 7008;
  {$EXTERNALSYM FAX_ERR_FILE_ACCESS_DENIED}
  FAX_ERR_MESSAGE_NOT_FOUND         = 7009;
  {$EXTERNALSYM FAX_ERR_MESSAGE_NOT_FOUND}
  FAX_ERR_DEVICE_NUM_LIMIT_EXCEEDED = 7010;
  {$EXTERNALSYM FAX_ERR_DEVICE_NUM_LIMIT_EXCEEDED}
  FAX_ERR_NOT_SUPPORTED_ON_THIS_SKU = 7011;
  {$EXTERNALSYM FAX_ERR_NOT_SUPPORTED_ON_THIS_SKU}
  FAX_ERR_VERSION_MISMATCH          = 7012; // Fax client/server versions mismtach
  {$EXTERNALSYM FAX_ERR_VERSION_MISMATCH}
  FAX_ERR_RECIPIENTS_LIMIT          = 7013; // Recipients limit in a single broadcast
  {$EXTERNALSYM FAX_ERR_RECIPIENTS_LIMIT}

  FAX_ERR_END = 7013; // Last fax specific error code
  {$EXTERNALSYM FAX_ERR_END}

//
// MessageId: FAX_E_SRV_OUTOFMEMORY
//
// MessageText:
//
//  The fax server failed to allocate memory.
//

  FAX_E_SRV_OUTOFMEMORY = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_SRV_OUTOFMEMORY);
  {$EXTERNALSYM FAX_E_SRV_OUTOFMEMORY}

//
// MessageId: FAX_E_GROUP_NOT_FOUND
//
// MessageText:
//
//  The fax server failed to locate an outbound routing group by name.
//

  FAX_E_GROUP_NOT_FOUND = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_GROUP_NOT_FOUND);
  {$EXTERNALSYM FAX_E_GROUP_NOT_FOUND}

//
// MessageId: FAX_E_BAD_GROUP_CONFIGURATION
//
// MessageText:
//
//  The fax server encountered an outbound routing group with bad configuration.
//

  FAX_E_BAD_GROUP_CONFIGURATION = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_BAD_GROUP_CONFIGURATION);
  {$EXTERNALSYM FAX_E_BAD_GROUP_CONFIGURATION}

//
// MessageId: FAX_E_GROUP_IN_USE
//
// MessageText:
//
//  The fax server cannot remove an outbound routing group because it is in use by one or more outbound routing rules.
//

  FAX_E_GROUP_IN_USE = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_GROUP_IN_USE);
  {$EXTERNALSYM FAX_E_GROUP_IN_USE}

//
// MessageId: FAX_E_RULE_NOT_FOUND
//
// MessageText:
//
//  The fax server failed to locate an outbound routing rule by country code and area code.
//

  FAX_E_RULE_NOT_FOUND = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_RULE_NOT_FOUND);
  {$EXTERNALSYM FAX_E_RULE_NOT_FOUND}

//
// MessageId: FAX_E_NOT_NTFS
//
// MessageText:
//
//  The fax server cannot set an archive folder to a non-NTFS partition.
//

  FAX_E_NOT_NTFS = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_NOT_NTFS);
  {$EXTERNALSYM FAX_E_NOT_NTFS}

//
// MessageId: FAX_E_DIRECTORY_IN_USE
//
// MessageText:
//
//  The fax server cannot use the same folder for both the inbox and the sent-items archives.
//

  FAX_E_DIRECTORY_IN_USE = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_DIRECTORY_IN_USE);
  {$EXTERNALSYM FAX_E_DIRECTORY_IN_USE}

//
// MessageId: FAX_E_FILE_ACCESS_DENIED
//
// MessageText:
//
//  The fax server cannot access the specified file or folder.
//

  FAX_E_FILE_ACCESS_DENIED = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_FILE_ACCESS_DENIED);
  {$EXTERNALSYM FAX_E_FILE_ACCESS_DENIED}

//
// MessageId: FAX_E_MESSAGE_NOT_FOUND
//
// MessageText:
//
//  The fax server cannot find the job or message by its ID.
//

  FAX_E_MESSAGE_NOT_FOUND = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_MESSAGE_NOT_FOUND);
  {$EXTERNALSYM FAX_E_MESSAGE_NOT_FOUND}

//
// MessageId: FAX_E_DEVICE_NUM_LIMIT_EXCEEDED
//
// MessageText:
//
//  The fax server cannot complete the operation because the number of active fax devices allowed for this version of Windows was exceeded.
//

  FAX_E_DEVICE_NUM_LIMIT_EXCEEDED = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_DEVICE_NUM_LIMIT_EXCEEDED);
  {$EXTERNALSYM FAX_E_DEVICE_NUM_LIMIT_EXCEEDED}

//
// MessageId: FAX_E_NOT_SUPPORTED_ON_THIS_SKU
//
// MessageText:
//
//  The fax server cannot complete the operation because it is not supported for this version of Windows.
//

  FAX_E_NOT_SUPPORTED_ON_THIS_SKU = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_NOT_SUPPORTED_ON_THIS_SKU);
  {$EXTERNALSYM FAX_E_NOT_SUPPORTED_ON_THIS_SKU}

//
// MessageId: FAX_E_VERSION_MISMATCH
//
// MessageText:
//
//  The fax server API version does not support the requested operation.
//

  FAX_E_VERSION_MISMATCH = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_VERSION_MISMATCH);
  {$EXTERNALSYM FAX_E_VERSION_MISMATCH}

//
// MessageId: FAX_E_RECIPIENT_LIMIT
//
// MessageText:
//
// The limit on the number of recipients for a single fax broadcast was reached.
//

  FAX_E_RECIPIENTS_LIMIT = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or FAX_ERR_RECIPIENTS_LIMIT);
  {$EXTERNALSYM FAX_E_RECIPIENTS_LIMIT}

type
  FAX_ENUM_LOG_LEVELS = (
    FAXLOG_LEVEL_NONE,
    FAXLOG_LEVEL_MIN,
    FAXLOG_LEVEL_MED,
    FAXLOG_LEVEL_MAX);
  {$EXTERNALSYM FAX_ENUM_LOG_LEVELS}
  TFaxEnumLogLevels = FAX_ENUM_LOG_LEVELS;

  FAX_ENUM_LOG_CATEGORIES = (
    FAXLOG_CATEGORY_FILLER0,
    FAXLOG_CATEGORY_INIT,                   // Initialization / shutdown
    FAXLOG_CATEGORY_OUTBOUND,               // Outbound messages
    FAXLOG_CATEGORY_INBOUND,                // Inbound messages
    FAXLOG_CATEGORY_UNKNOWN);               // Unknown category (all others)
  {$EXTERNALSYM FAX_ENUM_LOG_CATEGORIES}
  TFaxEnumLogCategories = FAX_ENUM_LOG_CATEGORIES;

  PFAX_LOG_CATEGORYA = ^FAX_LOG_CATEGORYA;
  {$EXTERNALSYM PFAX_LOG_CATEGORYA}
  _FAX_LOG_CATEGORYA = record
    Name: LPCSTR; // logging category name
    Category: DWORD; // logging category number
    Level: DWORD; // logging level for the category
  end;
  {$EXTERNALSYM _FAX_LOG_CATEGORYA}
  FAX_LOG_CATEGORYA = _FAX_LOG_CATEGORYA;
  {$EXTERNALSYM FAX_LOG_CATEGORYA}
  TFaxLogCategoryA = FAX_LOG_CATEGORYA;
  PFaxLogCategoryA = PFAX_LOG_CATEGORYA;

  PFAX_LOG_CATEGORYW = ^FAX_LOG_CATEGORYW;
  {$EXTERNALSYM PFAX_LOG_CATEGORYW}
  _FAX_LOG_CATEGORYW = record
    Name: LPCWSTR; // logging category name
    Category: DWORD; // logging category number
    Level: DWORD; // logging level for the category
  end;
  {$EXTERNALSYM _FAX_LOG_CATEGORYW}
  FAX_LOG_CATEGORYW = _FAX_LOG_CATEGORYW;
  {$EXTERNALSYM FAX_LOG_CATEGORYW}
  TFaxLogCategoryW = FAX_LOG_CATEGORYW;
  PFaxLogCategoryW = PFAX_LOG_CATEGORYW;

{$IFDEF UNICODE}
  FAX_LOG_CATEGORY = FAX_LOG_CATEGORYW;
  {$EXTERNALSYM FAX_LOG_CATEGORY}
  PFAX_LOG_CATEGORY = PFAX_LOG_CATEGORYW;
  {$EXTERNALSYM PFAX_LOG_CATEGORY}
  TFaxLogCategory = TFaxLogCategoryW;
  PFaxLogCategory = PFaxLogCategoryW;
{$ELSE}
  FAX_LOG_CATEGORY = FAX_LOG_CATEGORYA;
  {$EXTERNALSYM FAX_LOG_CATEGORY}
  PFAX_LOG_CATEGORY = PFAX_LOG_CATEGORYA;
  {$EXTERNALSYM PFAX_LOG_CATEGORY}
  TFaxLogCategory = TFaxLogCategoryA;
  PFaxLogCategory = PFaxLogCategoryA;
{$ENDIF}

  PFAX_TIME = ^FAX_TIME;
  {$EXTERNALSYM PFAX_TIME}
  _FAX_TIME = record
    Hour: WORD;
    Minute: WORD;
  end;
  {$EXTERNALSYM _FAX_TIME}
  FAX_TIME = _FAX_TIME;
  {$EXTERNALSYM FAX_TIME}
  TFaxTime = FAX_TIME;
  PFaxTime = PFAX_TIME;

  PFAX_CONFIGURATIONA = ^FAX_CONFIGURATIONA;
  {$EXTERNALSYM PFAX_CONFIGURATIONA}
  _FAX_CONFIGURATIONA = record
    SizeOfStruct: DWORD; // size of this structure
    Retries: DWORD; // number of retries for fax send
    RetryDelay: DWORD; // number of minutes between retries
    DirtyDays: DWORD; // number of days to keep an unsent job in the queue
    Branding: BOOL; // fsp should brand outgoing faxes
    UseDeviceTsid: BOOL; // server uses device tsid only
    ServerCp: BOOL; // clients must use cover pages on the server
    PauseServerQueue: BOOL; // is the server queue paused?
    StartCheapTime: FAX_TIME; // start of discount rate period
    StopCheapTime: FAX_TIME; // end of discount rate period
    ArchiveOutgoingFaxes: BOOL; // whether outgoing faxes should be archived
    ArchiveDirectory: LPCSTR; // archive directory for outgoing faxes
    Reserved: LPCSTR; // Reserved; must be NULL
  end;
  {$EXTERNALSYM _FAX_CONFIGURATIONA}
  FAX_CONFIGURATIONA = _FAX_CONFIGURATIONA;
  {$EXTERNALSYM FAX_CONFIGURATIONA}
  TFaxConfigurationA = FAX_CONFIGURATIONA;
  PFaxConfigurationA = PFAX_CONFIGURATIONA;

  PFAX_CONFIGURATIONW = ^FAX_CONFIGURATIONW;
  {$EXTERNALSYM PFAX_CONFIGURATIONW}
  _FAX_CONFIGURATIONW = record
    SizeOfStruct: DWORD; // size of this structure
    Retries: DWORD; // number of retries for fax send
    RetryDelay: DWORD; // number of minutes between retries
    DirtyDays: DWORD; // number of days to keep an unsent job in the queue
    Branding: BOOL; // fsp should brand outgoing faxes
    UseDeviceTsid: BOOL; // server uses device tsid only
    ServerCp: BOOL; // clients must use cover pages on the server
    PauseServerQueue: BOOL; // is the server queue paused?
    StartCheapTime: FAX_TIME; // start of discount rate period
    StopCheapTime: FAX_TIME; // end of discount rate period
    ArchiveOutgoingFaxes: BOOL; // whether outgoing faxes should be archived
    ArchiveDirectory: LPCWSTR; // archive directory for outgoing faxes
    Reserved: LPCWSTR; // Reserved; must be NULL
  end;
  {$EXTERNALSYM _FAX_CONFIGURATIONW}
  FAX_CONFIGURATIONW = _FAX_CONFIGURATIONW;
  {$EXTERNALSYM FAX_CONFIGURATIONW}
  TFaxConfigurationW = FAX_CONFIGURATIONW;
  PFaxConfigurationW = PFAX_CONFIGURATIONW;

{$IFDEF UNICODE}
  FAX_CONFIGURATION = FAX_CONFIGURATIONW;
  {$EXTERNALSYM FAX_CONFIGURATION}
  PFAX_CONFIGURATION = PFAX_CONFIGURATIONW;
  {$EXTERNALSYM PFAX_CONFIGURATION}
  TFaxConfiguration = TFaxConfigurationW;
  PFaxConfiguration = PFaxConfigurationW;
{$ELSE}
  FAX_CONFIGURATION = FAX_CONFIGURATIONA;
  {$EXTERNALSYM FAX_CONFIGURATION}
  PFAX_CONFIGURATION = PFAX_CONFIGURATIONA;
  {$EXTERNALSYM PFAX_CONFIGURATION}
  TFaxConfiguration = TFaxConfigurationA;
  PFaxConfiguration = PFaxConfigurationA;
{$ENDIF}

//
// FaxSetJob() command codes
//

  FAX_ENUM_JOB_COMMANDS = (
    JC_UNKNOWN,
    JC_DELETE,
    JC_PAUSE,
    JC_RESUME);
  {$EXTERNALSYM FAX_ENUM_JOB_COMMANDS}
  TFaxEnumJobCommands = FAX_ENUM_JOB_COMMANDS;

const
  JC_RESTART = JC_RESUME;
  {$EXTERNALSYM JC_RESTART}

//
// job type defines
//

  JT_UNKNOWN      = 0;
  {$EXTERNALSYM JT_UNKNOWN}
  JT_SEND         = 1;
  {$EXTERNALSYM JT_SEND}
  JT_RECEIVE      = 2;
  {$EXTERNALSYM JT_RECEIVE}
  JT_ROUTING      = 3;
  {$EXTERNALSYM JT_ROUTING}
  JT_FAIL_RECEIVE = 4;
  {$EXTERNALSYM JT_FAIL_RECEIVE}

//
// job status defines
//

  JS_PENDING          = $00000000;
  {$EXTERNALSYM JS_PENDING}
  JS_INPROGRESS       = $00000001;
  {$EXTERNALSYM JS_INPROGRESS}
  JS_DELETING         = $00000002;
  {$EXTERNALSYM JS_DELETING}
  JS_FAILED           = $00000004;
  {$EXTERNALSYM JS_FAILED}
  JS_PAUSED           = $00000008;
  {$EXTERNALSYM JS_PAUSED}
  JS_NOLINE           = $00000010;
  {$EXTERNALSYM JS_NOLINE}
  JS_RETRYING         = $00000020;
  {$EXTERNALSYM JS_RETRYING}
  JS_RETRIES_EXCEEDED = $00000040;
  {$EXTERNALSYM JS_RETRIES_EXCEEDED}

type
  PFAX_DEVICE_STATUSA = ^FAX_DEVICE_STATUSA;
  {$EXTERNALSYM PFAX_DEVICE_STATUSA}
  _FAX_DEVICE_STATUSA = record
    SizeOfStruct: DWORD; // size of this structure
    CallerId: LPCSTR; // caller id string
    Csid: LPCSTR; // station identifier
    CurrentPage: DWORD; // current page
    DeviceId: DWORD; // permanent line id
    DeviceName: LPCSTR; // device name
    DocumentName: LPCSTR; // document name
    JobType: DWORD; // send or receive?
    PhoneNumber: LPCSTR; // sending phone number
    RoutingString: LPCSTR; // routing information
    SenderName: LPCSTR; // sender name
    RecipientName: LPCSTR; // recipient name
    Size: DWORD; // size in bytes of the document
    StartTime: FILETIME; // starting time of the fax send/receive
    Status: DWORD; // current status of the device, see FPS_??? masks
    StatusString: LPCSTR; // status string if the Status field is zero.  this may be NULL.
    SubmittedTime: FILETIME; // time the document was submitted
    TotalPages: DWORD; // total number of pages in this job
    Tsid: LPCSTR; // transmitting station identifier
    UserName: LPCSTR; // user that submitted the active job
  end;
  {$EXTERNALSYM _FAX_DEVICE_STATUSA}
  FAX_DEVICE_STATUSA = _FAX_DEVICE_STATUSA;
  {$EXTERNALSYM FAX_DEVICE_STATUSA}
  TFaxDeviceStatusA = FAX_DEVICE_STATUSA;
  PFaxDeviceStatusA = PFAX_DEVICE_STATUSA;

  PFAX_DEVICE_STATUSW = ^FAX_DEVICE_STATUSW;
  {$EXTERNALSYM PFAX_DEVICE_STATUSW}
  _FAX_DEVICE_STATUSW = record
    SizeOfStruct: DWORD; // size of this structure
    CallerId: LPCWSTR; // caller id string
    Csid: LPCWSTR; // station identifier
    CurrentPage: DWORD; // current page
    DeviceId: DWORD; // permanent line id
    DeviceName: LPCWSTR; // device name
    DocumentName: LPCWSTR; // document name
    JobType: DWORD; // send or receive?
    PhoneNumber: LPCWSTR; // sending phone number
    RoutingString: LPCWSTR; // routing information
    SenderName: LPCWSTR; // sender name
    RecipientName: LPCWSTR; // recipient name
    Size: DWORD; // size in bytes of the document
    StartTime: FILETIME; // starting time of the fax send/receive
    Status: DWORD; // current status of the device, see FPS_??? masks
    StatusString: LPCWSTR; // status string if the Status field is zero.  this may be NULL.
    SubmittedTime: FILETIME; // time the document was submitted
    TotalPages: DWORD; // total number of pages in this job
    Tsid: LPCWSTR; // transmitting station identifier
    UserName: LPCWSTR; // user that submitted the active job
  end;
  {$EXTERNALSYM _FAX_DEVICE_STATUSW}
  FAX_DEVICE_STATUSW = _FAX_DEVICE_STATUSW;
  {$EXTERNALSYM FAX_DEVICE_STATUSW}
  TFaxDeviceStatusW = FAX_DEVICE_STATUSW;
  PFaxDeviceStatusW = PFAX_DEVICE_STATUSW;

{$IFDEF UNICODE}
  FAX_DEVICE_STATUS = FAX_DEVICE_STATUSW;
  {$EXTERNALSYM FAX_DEVICE_STATUS}
  PFAX_DEVICE_STATUS = PFAX_DEVICE_STATUSW;
  {$EXTERNALSYM PFAX_DEVICE_STATUS}
  TFaxDeviceStatus = TFaxDeviceStatusW;
  PFaxDeviceStatus = PFaxDeviceStatusW;
{$ELSE}
  FAX_DEVICE_STATUS = FAX_DEVICE_STATUSA;
  {$EXTERNALSYM FAX_DEVICE_STATUS}
  PFAX_DEVICE_STATUS = PFAX_DEVICE_STATUSA;
  {$EXTERNALSYM PFAX_DEVICE_STATUS}
  TFaxDeviceStatus = TFaxDeviceStatusA;
  PFaxDeviceStatus = PFaxDeviceStatusA;
{$ENDIF}

  PFAX_JOB_ENTRYA = ^FAX_JOB_ENTRYA;
  {$EXTERNALSYM PFAX_JOB_ENTRYA}
  _FAX_JOB_ENTRYA = record
    SizeOfStruct: DWORD; // size of this structure
    JobId: DWORD; // fax job id
    UserName: LPCSTR; // user who submitted the job
    JobType: DWORD; // job type, see JT defines
    QueueStatus: DWORD; // job queue status, see JS defines
    Status: DWORD; // current status of the device, see FPS_??? masks
    Size: DWORD; // size in bytes of the document
    PageCount: DWORD; // total page count
    RecipientNumber: LPCSTR; // recipient fax number
    RecipientName: LPCSTR; // recipient name
    Tsid: LPCSTR; // transmitter's id
    SenderName: LPCSTR; // sender name
    SenderCompany: LPCSTR; // sender company
    SenderDept: LPCSTR; // sender department
    BillingCode: LPCSTR; // billing code
    ScheduleAction: DWORD; // when to schedule the fax, see JSA defines
    ScheduleTime: SYSTEMTIME; // time to send the fax when JSA_SPECIFIC_TIME is used (must be local time)
    DeliveryReportType: DWORD; // delivery report type, see DRT defines
    DeliveryReportAddress: LPCSTR; // email address for delivery report (ndr or dr) thru MAPI / SMTP
    DocumentName: LPCSTR; // document name
  end;
  {$EXTERNALSYM _FAX_JOB_ENTRYA}
  FAX_JOB_ENTRYA = _FAX_JOB_ENTRYA;
  {$EXTERNALSYM FAX_JOB_ENTRYA}
  TFaxJobEntryA = FAX_JOB_ENTRYA;
  PFaxJobEntryA = PFAX_JOB_ENTRYA;

  PFAX_JOB_ENTRYW = ^FAX_JOB_ENTRYW;
  {$EXTERNALSYM PFAX_JOB_ENTRYW}
  _FAX_JOB_ENTRYW = record
    SizeOfStruct: DWORD; // size of this structure
    JobId: DWORD; // fax job id
    UserName: LPCWSTR; // user who submitted the job
    JobType: DWORD; // job type, see JT defines
    QueueStatus: DWORD; // job queue status, see JS defines
    Status: DWORD; // current status of the device, see FPS_??? masks
    Size: DWORD; // size in bytes of the document
    PageCount: DWORD; // total page count
    RecipientNumber: LPCWSTR; // recipient fax number
    RecipientName: LPCWSTR; // recipient name
    Tsid: LPCWSTR; // transmitter's id
    SenderName: LPCWSTR; // sender name
    SenderCompany: LPCWSTR; // sender company
    SenderDept: LPCWSTR; // sender department
    BillingCode: LPCWSTR; // billing code
    ScheduleAction: DWORD; // when to schedule the fax, see JSA defines
    ScheduleTime: SYSTEMTIME; // time to send the fax when JSA_SPECIFIC_TIME is used (must be local time)
    DeliveryReportType: DWORD; // delivery report type, see DRT defines
    DeliveryReportAddress: LPCWSTR; // email address for delivery report (ndr or dr) thru MAPI / SMTP
    DocumentName: LPCWSTR; // document name
  end;
  {$EXTERNALSYM _FAX_JOB_ENTRYW}
  FAX_JOB_ENTRYW = _FAX_JOB_ENTRYW;
  {$EXTERNALSYM FAX_JOB_ENTRYW}
  TFaxJobEntryW = FAX_JOB_ENTRYW;
  PFaxJobEntryW = PFAX_JOB_ENTRYW;

{$IFDEF UNICODE}
  FAX_JOB_ENTRY = FAX_JOB_ENTRYW;
  {$EXTERNALSYM FAX_JOB_ENTRY}
  PFAX_JOB_ENTRY = PFAX_JOB_ENTRYW;
  {$EXTERNALSYM PFAX_JOB_ENTRY}
  TFaxJobEntry = TFaxJobEntryW;
  PFaxJobEntry = PFaxJobEntryW;
{$ELSE}
  FAX_JOB_ENTRY = FAX_JOB_ENTRYA;
  {$EXTERNALSYM FAX_JOB_ENTRY}
  PFAX_JOB_ENTRY = PFAX_JOB_ENTRYA;
  {$EXTERNALSYM PFAX_JOB_ENTRY}
  TFaxJobEntry = TFaxJobEntryA;
  PFaxJobEntry = PFaxJobEntryA;
{$ENDIF}

//
// fax port state masks
//
// if you change these defines the be sure to
// change the resources in the fax service.
//

const
  FPS_DIALING          = $20000001;
  {$EXTERNALSYM FPS_DIALING}
  FPS_SENDING          = $20000002;
  {$EXTERNALSYM FPS_SENDING}
  FPS_RECEIVING        = $20000004;
  {$EXTERNALSYM FPS_RECEIVING}
  FPS_COMPLETED        = $20000008;
  {$EXTERNALSYM FPS_COMPLETED}
  FPS_HANDLED          = $20000010;
  {$EXTERNALSYM FPS_HANDLED}
  FPS_UNAVAILABLE      = $20000020;
  {$EXTERNALSYM FPS_UNAVAILABLE}
  FPS_BUSY             = $20000040;
  {$EXTERNALSYM FPS_BUSY}
  FPS_NO_ANSWER        = $20000080;
  {$EXTERNALSYM FPS_NO_ANSWER}
  FPS_BAD_ADDRESS      = $20000100;
  {$EXTERNALSYM FPS_BAD_ADDRESS}
  FPS_NO_DIAL_TONE     = $20000200;
  {$EXTERNALSYM FPS_NO_DIAL_TONE}
  FPS_DISCONNECTED     = $20000400;
  {$EXTERNALSYM FPS_DISCONNECTED}
  FPS_FATAL_ERROR      = $20000800;
  {$EXTERNALSYM FPS_FATAL_ERROR}
  FPS_NOT_FAX_CALL     = $20001000;
  {$EXTERNALSYM FPS_NOT_FAX_CALL}
  FPS_CALL_DELAYED     = $20002000;
  {$EXTERNALSYM FPS_CALL_DELAYED}
  FPS_CALL_BLACKLISTED = $20004000;
  {$EXTERNALSYM FPS_CALL_BLACKLISTED}
  FPS_INITIALIZING     = $20008000;
  {$EXTERNALSYM FPS_INITIALIZING}
  FPS_OFFLINE          = $20010000;
  {$EXTERNALSYM FPS_OFFLINE}
  FPS_RINGING          = $20020000;
  {$EXTERNALSYM FPS_RINGING}

  FPS_AVAILABLE = $20100000;
  {$EXTERNALSYM FPS_AVAILABLE}
  FPS_ABORTING  = $20200000;
  {$EXTERNALSYM FPS_ABORTING}
  FPS_ROUTING   = $20400000;
  {$EXTERNALSYM FPS_ROUTING}
  FPS_ANSWERED  = $20800000;
  {$EXTERNALSYM FPS_ANSWERED}

//
// fax port capability mask
//

  FPF_RECEIVE = $00000001; // Automatically receive faxes
  {$EXTERNALSYM FPF_RECEIVE}
  FPF_SEND    = $00000002;
  {$EXTERNALSYM FPF_SEND}
  FPF_VIRTUAL = $00000004;
  {$EXTERNALSYM FPF_VIRTUAL}

type
  PFAX_PORT_INFOA = ^FAX_PORT_INFOA;
  {$EXTERNALSYM PFAX_PORT_INFOA}
  _FAX_PORT_INFOA = record
    SizeOfStruct: DWORD; // size of this structure
    DeviceId: DWORD; // Device ID
    State: DWORD; // State of the device
    Flags: DWORD; // Device specific flags
    Rings: DWORD; // Number of rings before answer
    Priority: DWORD; // Device priority
    DeviceName: LPCSTR; // Device name
    Tsid: LPCSTR; // Device Tsid
    Csid: LPCSTR; // Device Csid
  end;
  {$EXTERNALSYM _FAX_PORT_INFOA}
  FAX_PORT_INFOA = _FAX_PORT_INFOA;
  {$EXTERNALSYM FAX_PORT_INFOA}
  TFaxPortInfoA = FAX_PORT_INFOA;
  PFaxPortInfoA = PFAX_PORT_INFOA;

  PFAX_PORT_INFOW = ^FAX_PORT_INFOW;
  {$EXTERNALSYM PFAX_PORT_INFOW}
  _FAX_PORT_INFOW = record
    SizeOfStruct: DWORD; // size of this structure
    DeviceId: DWORD; // Device ID
    State: DWORD; // State of the device
    Flags: DWORD; // Device specific flags
    Rings: DWORD; // Number of rings before answer
    Priority: DWORD; // Device priority
    DeviceName: LPCWSTR; // Device name
    Tsid: LPCWSTR; // Device Tsid
    Csid: LPCWSTR; // Device Csid
  end;
  {$EXTERNALSYM _FAX_PORT_INFOW}
  FAX_PORT_INFOW = _FAX_PORT_INFOW;
  {$EXTERNALSYM FAX_PORT_INFOW}
  TFaxPortInfoW = FAX_PORT_INFOW;
  PFaxPortInfoW = PFAX_PORT_INFOW;

{$IFDEF UNICODE}
  FAX_PORT_INFO = FAX_PORT_INFOW;
  {$EXTERNALSYM FAX_PORT_INFO}
  PFAX_PORT_INFO = PFAX_PORT_INFOW;
  {$EXTERNALSYM PFAX_PORT_INFO}
  TFaxPortInfo = TFaxPortInfoW;
  PFaxPortInfo = PFaxPortInfoW;
{$ELSE}
  FAX_PORT_INFO = FAX_PORT_INFOA;
  {$EXTERNALSYM FAX_PORT_INFO}
  PFAX_PORT_INFO = PFAX_PORT_INFOA;
  {$EXTERNALSYM PFAX_PORT_INFO}
  TFaxPortInfo = TFaxPortInfoA;
  PFaxPortInfo = PFaxPortInfoA;
{$ENDIF}

  PFAX_ROUTING_METHODA = ^FAX_ROUTING_METHODA;
  {$EXTERNALSYM PFAX_ROUTING_METHODA}
  _FAX_ROUTING_METHODA = record
    SizeOfStruct: DWORD; // size of this structure
    DeviceId: DWORD; // device identifier
    Enabled: BOOL; // is this method enabled for this device?
    DeviceName: LPCSTR; // device name
    Guid: LPCSTR; // guid that identifies this routing method
    FriendlyName: LPCSTR; // friendly name for this method
    FunctionName: LPCSTR; // exported function name that identifies this method
    ExtensionImageName: LPCSTR; // module (dll) name that implements this method
    ExtensionFriendlyName: LPCSTR; // displayable string that identifies the extension
  end;
  {$EXTERNALSYM _FAX_ROUTING_METHODA}
  FAX_ROUTING_METHODA = _FAX_ROUTING_METHODA;
  {$EXTERNALSYM FAX_ROUTING_METHODA}
  TFaxRoutingMethodA = FAX_ROUTING_METHODA;
  PFaxRoutingMethodA = PFAX_ROUTING_METHODA;

  PFAX_ROUTING_METHODW = ^FAX_ROUTING_METHODW;
  {$EXTERNALSYM PFAX_ROUTING_METHODW}
  _FAX_ROUTING_METHODW = record
    SizeOfStruct: DWORD; // size of this structure
    DeviceId: DWORD; // device identifier
    Enabled: BOOL; // is this method enabled for this device?
    DeviceName: LPCWSTR; // device name
    Guid: LPCWSTR; // guid that identifies this routing method
    FriendlyName: LPCWSTR; // friendly name for this method
    FunctionName: LPCWSTR; // exported function name that identifies this method
    ExtensionImageName: LPCWSTR; // module (dll) name that implements this method
    ExtensionFriendlyName: LPCWSTR; // displayable string that identifies the extension
  end;
  {$EXTERNALSYM _FAX_ROUTING_METHODW}
  FAX_ROUTING_METHODW = _FAX_ROUTING_METHODW;
  {$EXTERNALSYM FAX_ROUTING_METHODW}
  TFaxRoutingMethodW = FAX_ROUTING_METHODW;
  PFaxRoutingMethodW = PFAX_ROUTING_METHODW;

{$IFDEF UNICODE}
  FAX_ROUTING_METHOD = FAX_ROUTING_METHODW;
  {$EXTERNALSYM FAX_ROUTING_METHOD}
  PFAX_ROUTING_METHOD = PFAX_ROUTING_METHODW;
  {$EXTERNALSYM PFAX_ROUTING_METHOD}
  TFaxRoutingMethod = TFaxRoutingMethodW;
  PFaxRoutingMethod = PFaxRoutingMethodW;
{$ELSE}
  FAX_ROUTING_METHOD = FAX_ROUTING_METHODA;
  {$EXTERNALSYM FAX_ROUTING_METHOD}
  PFAX_ROUTING_METHOD = PFAX_ROUTING_METHODA;
  {$EXTERNALSYM PFAX_ROUTING_METHOD}
  TFaxRoutingMethod = TFaxRoutingMethodA;
  PFaxRoutingMethod = PFaxRoutingMethodA;
{$ENDIF}

  PFAX_GLOBAL_ROUTING_INFOA = ^FAX_GLOBAL_ROUTING_INFOA;
  {$EXTERNALSYM PFAX_GLOBAL_ROUTING_INFOA}
  _FAX_GLOBAL_ROUTING_INFOA = record
    SizeOfStruct: DWORD; // size of this structure
    Priority: DWORD; // priority of this device
    Guid: LPCSTR; // guid that identifies this routing method
    FriendlyName: LPCSTR; // friendly name for this method
    FunctionName: LPCSTR; // exported function name that identifies this method
    ExtensionImageName: LPCSTR; // module (dll) name that implements this method
    ExtensionFriendlyName: LPCSTR; // displayable string that identifies the extension
  end;
  {$EXTERNALSYM _FAX_GLOBAL_ROUTING_INFOA}
  FAX_GLOBAL_ROUTING_INFOA = _FAX_GLOBAL_ROUTING_INFOA;
  {$EXTERNALSYM FAX_GLOBAL_ROUTING_INFOA}
  TFaxGlobalRoutingInfoA = FAX_GLOBAL_ROUTING_INFOA;
  PFaxGlobalRoutingInfoA = PFAX_GLOBAL_ROUTING_INFOA;

  PFAX_GLOBAL_ROUTING_INFOW = ^FAX_GLOBAL_ROUTING_INFOW;
  {$EXTERNALSYM PFAX_GLOBAL_ROUTING_INFOW}
  _FAX_GLOBAL_ROUTING_INFOW = record
    SizeOfStruct: DWORD; // size of this structure
    Priority: DWORD; // priority of this device
    Guid: LPCWSTR; // guid that identifies this routing method
    FriendlyName: LPCWSTR; // friendly name for this method
    FunctionName: LPCWSTR; // exported function name that identifies this method
    ExtensionImageName: LPCWSTR; // module (dll) name that implements this method
    ExtensionFriendlyName: LPCWSTR; // displayable string that identifies the extension
  end;
  {$EXTERNALSYM _FAX_GLOBAL_ROUTING_INFOW}
  FAX_GLOBAL_ROUTING_INFOW = _FAX_GLOBAL_ROUTING_INFOW;
  {$EXTERNALSYM FAX_GLOBAL_ROUTING_INFOW}
  TFaxGlobalRoutingInfoW = FAX_GLOBAL_ROUTING_INFOW;
  PFaxGlobalRoutingInfoW = PFAX_GLOBAL_ROUTING_INFOW;

{$IFDEF UNICODE}
  FAX_GLOBAL_ROUTING_INFO = FAX_GLOBAL_ROUTING_INFOW;
  {$EXTERNALSYM FAX_GLOBAL_ROUTING_INFO}
  PFAX_GLOBAL_ROUTING_INFO = FAX_GLOBAL_ROUTING_INFOW;
  {$EXTERNALSYM PFAX_GLOBAL_ROUTING_INFO}
  TFaxGlobalRoutingInfo = TFaxGlobalRoutingInfoW;
  PFaxGlobalRoutingInfo = PFaxGlobalRoutingInfoW;
{$ELSE}
  FAX_GLOBAL_ROUTING_INFO = FAX_GLOBAL_ROUTING_INFOA;
  {$EXTERNALSYM FAX_GLOBAL_ROUTING_INFO}
  PFAX_GLOBAL_ROUTING_INFO = FAX_GLOBAL_ROUTING_INFOA;
  {$EXTERNALSYM PFAX_GLOBAL_ROUTING_INFO}
  TFaxGlobalRoutingInfo = TFaxGlobalRoutingInfoA;
  PFaxGlobalRoutingInfo = PFaxGlobalRoutingInfoA;
{$ENDIF}

  PFAX_COVERPAGE_INFOA = ^FAX_COVERPAGE_INFOA;
  {$EXTERNALSYM PFAX_COVERPAGE_INFOA}
  _FAX_COVERPAGE_INFOA = record
    SizeOfStruct: DWORD; // Size of this structure
    //
    // general
    //
    CoverPageName: LPCSTR; // coverpage document name
    UseServerCoverPage: BOOL; // coverpage exists on the fax server
    //
    // Recipient information
    //
    RecName: LPCSTR;
    RecFaxNumber: LPCSTR;
    RecCompany: LPCSTR;
    RecStreetAddress: LPCSTR;
    RecCity: LPCSTR;
    RecState: LPCSTR;
    RecZip: LPCSTR;
    RecCountry: LPCSTR;
    RecTitle: LPCSTR;
    RecDepartment: LPCSTR;
    RecOfficeLocation: LPCSTR;
    RecHomePhone: LPCSTR;
    RecOfficePhone: LPCSTR;
    //
    // Sender information
    //
    SdrName: LPCSTR;
    SdrFaxNumber: LPCSTR;
    SdrCompany: LPCSTR;
    SdrAddress: LPCSTR;
    SdrTitle: LPCSTR;
    SdrDepartment: LPCSTR;
    SdrOfficeLocation: LPCSTR;
    SdrHomePhone: LPCSTR;
    SdrOfficePhone: LPCSTR;
    //
    // Misc information
    //
    Note: LPCSTR;
    Subject: LPCSTR;
    TimeSent: SYSTEMTIME; // Time the fax was sent
    PageCount: DWORD; // Number of pages
  end;
  {$EXTERNALSYM _FAX_COVERPAGE_INFOA}
  FAX_COVERPAGE_INFOA = _FAX_COVERPAGE_INFOA;
  {$EXTERNALSYM FAX_COVERPAGE_INFOA}
  TFaxCoverpageInfoA = FAX_COVERPAGE_INFOA;
  PFaxCoverpageInfoA = PFAX_COVERPAGE_INFOA;

  PFAX_COVERPAGE_INFOW = ^FAX_COVERPAGE_INFOW;
  {$EXTERNALSYM PFAX_COVERPAGE_INFOW}
  _FAX_COVERPAGE_INFOW = record
    SizeOfStruct: DWORD; // Size of this structure
    //
    // general
    //
    CoverPageName: LPCWSTR; // coverpage document name
    UseServerCoverPage: BOOL; // coverpage exists on the fax server
    //
    // Recipient information
    //
    RecName: LPCWSTR;
    RecFaxNumber: LPCWSTR;
    RecCompany: LPCWSTR;
    RecStreetAddress: LPCWSTR;
    RecCity: LPCWSTR;
    RecState: LPCWSTR;
    RecZip: LPCWSTR;
    RecCountry: LPCWSTR;
    RecTitle: LPCWSTR;
    RecDepartment: LPCWSTR;
    RecOfficeLocation: LPCWSTR;
    RecHomePhone: LPCWSTR;
    RecOfficePhone: LPCWSTR;
    //
    // Sender information
    //
    SdrName: LPCWSTR;
    SdrFaxNumber: LPCWSTR;
    SdrCompany: LPCWSTR;
    SdrAddress: LPCWSTR;
    SdrTitle: LPCWSTR;
    SdrDepartment: LPCWSTR;
    SdrOfficeLocation: LPCWSTR;
    SdrHomePhone: LPCWSTR;
    SdrOfficePhone: LPCWSTR;
    //
    // Misc information
    //
    Note: LPCWSTR;
    Subject: LPCWSTR;
    TimeSent: SYSTEMTIME; // Time the fax was sent
    PageCount: DWORD; // Number of pages
  end;
  {$EXTERNALSYM _FAX_COVERPAGE_INFOW}
  FAX_COVERPAGE_INFOW = _FAX_COVERPAGE_INFOW;
  {$EXTERNALSYM FAX_COVERPAGE_INFOW}
  TFaxCoverpageInfoW = FAX_COVERPAGE_INFOW;
  PFaxCoverpageInfoW = PFAX_COVERPAGE_INFOW;

{$IFDEF UNICODE}
  FAX_COVERPAGE_INFO = FAX_COVERPAGE_INFOW;
  {$EXTERNALSYM FAX_COVERPAGE_INFO}
  PFAX_COVERPAGE_INFO = PFAX_COVERPAGE_INFOW;
  {$EXTERNALSYM PFAX_COVERPAGE_INFO}
  TFaxCoverpageInfo = TFaxCoverpageInfoW;
  PFaxCoverpageInfo = PFaxCoverpageInfoW;
{$ELSE}
  FAX_COVERPAGE_INFO = FAX_COVERPAGE_INFOA;
  {$EXTERNALSYM FAX_COVERPAGE_INFO}
  PFAX_COVERPAGE_INFO = PFAX_COVERPAGE_INFOA;
  {$EXTERNALSYM PFAX_COVERPAGE_INFO}
  TFaxCoverpageInfo = TFaxCoverpageInfoA;
  PFaxCoverpageInfo = PFaxCoverpageInfoA;
{$ENDIF}

  FAX_ENUM_JOB_SEND_ATTRIBUTES = (
    JSA_NOW,                        // Send now
    JSA_SPECIFIC_TIME,              // Send at specific time
    JSA_DISCOUNT_PERIOD);           // Send at server configured discount period
  {$EXTERNALSYM FAX_ENUM_JOB_SEND_ATTRIBUTES}
  TFaxEnumJobSendAttributes = FAX_ENUM_JOB_SEND_ATTRIBUTES;

  FAX_ENUM_DELIVERY_REPORT_TYPES = (
    DRT_NONE,          // Do not send receipt
    DRT_EMAIL,         // Send receipt by email
    DRT_INBOX);        // send receipt to local inbox
  {$EXTERNALSYM FAX_ENUM_DELIVERY_REPORT_TYPES}
  TFaxEnumDeliveryReportTypes = FAX_ENUM_DELIVERY_REPORT_TYPES;

  HCALL = HANDLE; // todo from TAPI

  PFAX_JOB_PARAMA = ^FAX_JOB_PARAMA;
  {$EXTERNALSYM PFAX_JOB_PARAMA}
  _FAX_JOB_PARAMA = record
    SizeOfStruct: DWORD; // size of this structure
    RecipientNumber: LPCSTR; // recipient fax number
    RecipientName: LPCSTR; // recipient name
    Tsid: LPCSTR; // transmitter's id
    SenderName: LPCSTR; // sender name
    SenderCompany: LPCSTR; // sender company
    SenderDept: LPCSTR; // sender department
    BillingCode: LPCSTR; // billing code
    ScheduleAction: DWORD; // when to schedule the fax, see JSA defines
    ScheduleTime: SYSTEMTIME; // time to send the fax when JSA_SPECIFIC_TIME is used (must be local time)
    DeliveryReportType: DWORD; // delivery report type, see DRT defines
    DeliveryReportAddress: LPCSTR; // email address for delivery report (ndr or dr) thru MAPI / SMTP
    DocumentName: LPCSTR; // document name (optional)
    CallHandle: HCALL; // optional call handle
    Reserved: array [0..3 - 1] of DWORD_PTR; // reserved for ms use only
  end;
  {$EXTERNALSYM _FAX_JOB_PARAMA}
  FAX_JOB_PARAMA = _FAX_JOB_PARAMA;
  {$EXTERNALSYM FAX_JOB_PARAMA}
  TFaxJobParamA = FAX_JOB_PARAMA;
  PFaxJobParamA = PFAX_JOB_PARAMA;

  PFAX_JOB_PARAMW = ^FAX_JOB_PARAMW;
  {$EXTERNALSYM PFAX_JOB_PARAMW}
  _FAX_JOB_PARAMW = record
    SizeOfStruct: DWORD; // size of this structure
    RecipientNumber: LPCWSTR; // recipient fax number
    RecipientName: LPCWSTR; // recipient name
    Tsid: LPCWSTR; // transmitter's id
    SenderName: LPCWSTR; // sender name
    SenderCompany: LPCWSTR; // sender company
    SenderDept: LPCWSTR; // sender department
    BillingCode: LPCWSTR; // billing code
    ScheduleAction: DWORD; // when to schedule the fax, see JSA defines
    ScheduleTime: SYSTEMTIME; // time to send the fax when JSA_SPECIFIC_TIME is used (must be local time)
    DeliveryReportType: DWORD; // delivery report type, see DRT defines
    DeliveryReportAddress: LPCWSTR; // email address for delivery report (ndr or dr) thru MAPI / SMTP
    DocumentName: LPCWSTR; // document name (optional)
    CallHandle: HCALL; // optional call handle
    Reserved: array [0..3 - 1] of DWORD_PTR; // reserved for ms use only
  end;
  {$EXTERNALSYM _FAX_JOB_PARAMW}
  FAX_JOB_PARAMW = _FAX_JOB_PARAMW;
  {$EXTERNALSYM FAX_JOB_PARAMW}
  TFaxJobParamW = FAX_JOB_PARAMW;
  PFaxJobParamW = PFAX_JOB_PARAMW;

{$IFDEF UNICODE}
  FAX_JOB_PARAM = FAX_JOB_PARAMW;
  {$EXTERNALSYM FAX_JOB_PARAM}
  PFAX_JOB_PARAM = PFAX_JOB_PARAMW;
  {$EXTERNALSYM PFAX_JOB_PARAM}
  TFaxJobParam = TFaxJobParamW;
  PFaxJobParam = PFaxJobParamW;
{$ELSE}
  FAX_JOB_PARAM = FAX_JOB_PARAMA;
  {$EXTERNALSYM FAX_JOB_PARAM}
  PFAX_JOB_PARAM = PFAX_JOB_PARAMA;
  {$EXTERNALSYM PFAX_JOB_PARAM}
  TFaxJobParam = TFaxJobParamA;
  PFaxJobParam = PFaxJobParamA;
{$ENDIF}

//
// Event Ids
//
// FEI_NEVENTS is the number of events
//

const
  FEI_DIALING           = $00000001;
  {$EXTERNALSYM FEI_DIALING}
  FEI_SENDING           = $00000002;
  {$EXTERNALSYM FEI_SENDING}
  FEI_RECEIVING         = $00000003;
  {$EXTERNALSYM FEI_RECEIVING}
  FEI_COMPLETED         = $00000004;
  {$EXTERNALSYM FEI_COMPLETED}
  FEI_BUSY              = $00000005;
  {$EXTERNALSYM FEI_BUSY}
  FEI_NO_ANSWER         = $00000006;
  {$EXTERNALSYM FEI_NO_ANSWER}
  FEI_BAD_ADDRESS       = $00000007;
  {$EXTERNALSYM FEI_BAD_ADDRESS}
  FEI_NO_DIAL_TONE      = $00000008;
  {$EXTERNALSYM FEI_NO_DIAL_TONE}
  FEI_DISCONNECTED      = $00000009;
  {$EXTERNALSYM FEI_DISCONNECTED}
  FEI_FATAL_ERROR       = $0000000a;
  {$EXTERNALSYM FEI_FATAL_ERROR}
  FEI_NOT_FAX_CALL      = $0000000b;
  {$EXTERNALSYM FEI_NOT_FAX_CALL}
  FEI_CALL_DELAYED      = $0000000c;
  {$EXTERNALSYM FEI_CALL_DELAYED}
  FEI_CALL_BLACKLISTED  = $0000000d;
  {$EXTERNALSYM FEI_CALL_BLACKLISTED}
  FEI_RINGING           = $0000000e;
  {$EXTERNALSYM FEI_RINGING}
  FEI_ABORTING          = $0000000f;
  {$EXTERNALSYM FEI_ABORTING}
  FEI_ROUTING           = $00000010;
  {$EXTERNALSYM FEI_ROUTING}
  FEI_MODEM_POWERED_ON  = $00000011;
  {$EXTERNALSYM FEI_MODEM_POWERED_ON}
  FEI_MODEM_POWERED_OFF = $00000012;
  {$EXTERNALSYM FEI_MODEM_POWERED_OFF}
  FEI_IDLE              = $00000013;
  {$EXTERNALSYM FEI_IDLE}
  FEI_FAXSVC_ENDED      = $00000014;
  {$EXTERNALSYM FEI_FAXSVC_ENDED}
  FEI_ANSWERED          = $00000015;
  {$EXTERNALSYM FEI_ANSWERED}
  FEI_JOB_QUEUED        = $00000016;
  {$EXTERNALSYM FEI_JOB_QUEUED}
  FEI_DELETED           = $00000017;
  {$EXTERNALSYM FEI_DELETED}
  FEI_INITIALIZING      = $00000018;
  {$EXTERNALSYM FEI_INITIALIZING}
  FEI_LINE_UNAVAILABLE  = $00000019;
  {$EXTERNALSYM FEI_LINE_UNAVAILABLE}
  FEI_HANDLED           = $0000001a;
  {$EXTERNALSYM FEI_HANDLED}
  FEI_FAXSVC_STARTED    = $0000001b;
  {$EXTERNALSYM FEI_FAXSVC_STARTED}

  FEI_NEVENTS = FEI_FAXSVC_STARTED;
  {$EXTERNALSYM FEI_NEVENTS}

type
  PFAX_EVENTA = ^FAX_EVENTA;
  {$EXTERNALSYM PFAX_EVENTA}
  _FAX_EVENTA = record
    SizeOfStruct: DWORD; // Size of this structure
    TimeStamp: FILETIME; // Timestamp for when the event was generated
    DeviceId: DWORD; // Permanent line id
    EventId: DWORD; // Current event id
    JobId: DWORD; // Fax Job Id, 0xffffffff indicates inactive job
  end;
  {$EXTERNALSYM _FAX_EVENTA}
  FAX_EVENTA = _FAX_EVENTA;
  {$EXTERNALSYM FAX_EVENTA}
  TFaxEventA = FAX_EVENTA;
  PFaxEventA = PFAX_EVENTA;

  PFAX_EVENTW = ^FAX_EVENTW;
  {$EXTERNALSYM PFAX_EVENTW}
  _FAX_EVENTW = record
    SizeOfStruct: DWORD; // Size of this structure
    TimeStamp: FILETIME; // Timestamp for when the event was generated
    DeviceId: DWORD; // Permanent line id
    EventId: DWORD; // Current event id
    JobId: DWORD; // Fax Job Id, 0xffffffff indicates inactive job
  end;
  {$EXTERNALSYM _FAX_EVENTW}
  FAX_EVENTW = _FAX_EVENTW;
  {$EXTERNALSYM FAX_EVENTW}
  TFaxEventW = FAX_EVENTW;
  PFaxEventW = PFAX_EVENTW;

{$IFDEF UNICODE}
  FAX_EVENT = FAX_EVENTW;
  {$EXTERNALSYM FAX_EVENT}
  PFAX_EVENT = PFAX_EVENTW;
  {$EXTERNALSYM PFAX_EVENT}
  TFaxEvent = TFaxEventW;
  PFaxEvent = PFaxEventW;
{$ELSE}
  FAX_EVENT = FAX_EVENTA;
  {$EXTERNALSYM FAX_EVENT}
  PFAX_EVENT = PFAX_EVENTA;
  {$EXTERNALSYM PFAX_EVENT}
  TFaxEvent = TFaxEventA;
  PFaxEvent = PFaxEventA;
{$ENDIF}

  PFAX_PRINT_INFOA = ^FAX_PRINT_INFOA;
  {$EXTERNALSYM PFAX_PRINT_INFOA}
  _FAX_PRINT_INFOA = record
    SizeOfStruct: DWORD; // Size of this structure
    DocName: LPCSTR; // Document name that appears in the spooler
    RecipientName: LPCSTR; // Recipient name
    RecipientNumber: LPCSTR; // Recipient fax number (non-canonical number)
    SenderName: LPCSTR; // Sender name
    SenderCompany: LPCSTR; // Sender company (optional)
    SenderDept: LPCSTR; // Sender department
    SenderBillingCode: LPCSTR; // Billing code
    Reserved: LPCSTR; // Reserved; must be NULL
    DrEmailAddress: LPCSTR; // E.Mail address for delivery report
    OutputFileName: LPCSTR; // for print to file, resulting file name
  end;
  {$EXTERNALSYM _FAX_PRINT_INFOA}
  FAX_PRINT_INFOA = _FAX_PRINT_INFOA;
  {$EXTERNALSYM FAX_PRINT_INFOA}
  TFaxPrintInfoA = FAX_PRINT_INFOA;
  PFaxPrintInfoA = PFAX_PRINT_INFOA;

  PFAX_PRINT_INFOW = ^FAX_PRINT_INFOW;
  {$EXTERNALSYM PFAX_PRINT_INFOW}
  _FAX_PRINT_INFOW = record
    SizeOfStruct: DWORD; // Size of this structure
    DocName: LPCWSTR; // Document name that appears in the spooler
    RecipientName: LPCWSTR; // Recipient name
    RecipientNumber: LPCWSTR; // Recipient fax number (non-canonical number)
    SenderName: LPCWSTR; // Sender name
    SenderCompany: LPCWSTR; // Sender company (optional)
    SenderDept: LPCWSTR; // Sender department
    SenderBillingCode: LPCWSTR; // Billing code
    Reserved: LPCWSTR; // Reserved; must be NULL
    DrEmailAddress: LPCWSTR; // E.Mail address for delivery report
    OutputFileName: LPCWSTR; // for print to file, resulting file name
  end;
  {$EXTERNALSYM _FAX_PRINT_INFOW}
  FAX_PRINT_INFOW = _FAX_PRINT_INFOW;
  {$EXTERNALSYM FAX_PRINT_INFOW}
  TFaxPrintInfoW = FAX_PRINT_INFOW;
  PFaxPrintInfoW = PFAX_PRINT_INFOW;

{$IFDEF UNICODE}
  FAX_PRINT_INFO = FAX_PRINT_INFOW;
  {$EXTERNALSYM FAX_PRINT_INFO}
  PFAX_PRINT_INFO = PFAX_PRINT_INFOW;
  {$EXTERNALSYM PFAX_PRINT_INFO}
  TFaxPrintInfo = TFaxPrintInfoW;
  PFaxPrintInfo = PFaxPrintInfoW;
{$ELSE}
  FAX_PRINT_INFO = FAX_PRINT_INFOA;
  {$EXTERNALSYM FAX_PRINT_INFO}
  PFAX_PRINT_INFO = PFAX_PRINT_INFOA;
  {$EXTERNALSYM PFAX_PRINT_INFO}
  TFaxPrintInfo = TFaxPrintInfoA;
  PFaxPrintInfo = PFaxPrintInfoA;
{$ENDIF}

  PFAX_CONTEXT_INFOA = ^FAX_CONTEXT_INFOA;
  {$EXTERNALSYM PFAX_CONTEXT_INFOA}
  _FAX_CONTEXT_INFOA = record
    SizeOfStruct: DWORD; // Size of this structure
    hDC: HDC; // Device Context
    ServerName: array [0..MAX_COMPUTERNAME_LENGTH] of CHAR; // Server name
  end;
  {$EXTERNALSYM _FAX_CONTEXT_INFOA}
  FAX_CONTEXT_INFOA = _FAX_CONTEXT_INFOA;
  {$EXTERNALSYM FAX_CONTEXT_INFOA}
  TFaxContextInfoA = FAX_CONTEXT_INFOA;
  PFaxContextInfoA = PFAX_CONTEXT_INFOA;

  PFAX_CONTEXT_INFOW = ^FAX_CONTEXT_INFOW;
  {$EXTERNALSYM PFAX_CONTEXT_INFOW}
  _FAX_CONTEXT_INFOW = record
    SizeOfStruct: DWORD; // Size of this structure
    hDC: HDC; // Device Context
    ServerName: array [0..MAX_COMPUTERNAME_LENGTH] of WCHAR; // Server name
  end;
  {$EXTERNALSYM _FAX_CONTEXT_INFOW}
  FAX_CONTEXT_INFOW = _FAX_CONTEXT_INFOW;
  {$EXTERNALSYM FAX_CONTEXT_INFOW}
  TFaxContextInfoW = FAX_CONTEXT_INFOW;
  PFaxContextInfoW = PFAX_CONTEXT_INFOW;

{$IFDEF UNICODE}
  FAX_CONTEXT_INFO = FAX_CONTEXT_INFOW;
  {$EXTERNALSYM FAX_CONTEXT_INFO}
  PFAX_CONTEXT_INFO = PFAX_CONTEXT_INFOW;
  {$EXTERNALSYM PFAX_CONTEXT_INFO}
  TFaxContextInfo = TFaxContextInfoW;
  PFaxContextInfo = PFaxContextInfoW;  
{$ELSE}
  FAX_CONTEXT_INFO = FAX_CONTEXT_INFOA;
  {$EXTERNALSYM FAX_CONTEXT_INFO}
  PFAX_CONTEXT_INFO = PFAX_CONTEXT_INFOA;
  {$EXTERNALSYM PFAX_CONTEXT_INFO}
  TFaxContextInfo = TFaxContextInfoA;
  PFaxContextInfo = PFaxContextInfoA;
{$ENDIF}

//
// prototypes
//

function FaxConnectFaxServerA(MachineName: LPCSTR; var FaxHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM FaxConnectFaxServerA}
function FaxConnectFaxServerW(MachineName: LPCWSTR; var FaxHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM FaxConnectFaxServerW}

{$IFDEF UNICODE}
function FaxConnectFaxServer(MachineName: LPCWSTR; var FaxHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM FaxConnectFaxServer}
{$ELSE}
function FaxConnectFaxServer(MachineName: LPCSTR; var FaxHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM FaxConnectFaxServer}
{$ENDIF}

function FaxClose(FaxHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM FaxClose}

type
  FAX_ENUM_PORT_OPEN_TYPE = (
    PORT_OPEN_FILLER0,
    PORT_OPEN_QUERY,
    PORT_OPEN_MODIFY);
  {$EXTERNALSYM FAX_ENUM_PORT_OPEN_TYPE}
  TFaxEnumPortOpenType = FAX_ENUM_PORT_OPEN_TYPE;

function FaxOpenPort(FaxHandle: HANDLE; DeviceId: DWORD; Flags: DWORD; var FaxPortHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM FaxOpenPort}

function FaxCompleteJobParamsA(var JobParams: PFAX_JOB_PARAMA; var CoverpageInfo: PFAX_COVERPAGE_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxCompleteJobParamsA}
function FaxCompleteJobParamsW(var JobParams: PFAX_JOB_PARAMW; var CoverpageInfo: PFAX_COVERPAGE_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxCompleteJobParamsW}

{$IFDEF UNICODE}
function FaxCompleteJobParams(var JobParams: PFAX_JOB_PARAMW; var CoverpageInfo: PFAX_COVERPAGE_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxCompleteJobParams}
{$ELSE}
function FaxCompleteJobParams(var JobParams: PFAX_JOB_PARAMA; var CoverpageInfo: PFAX_COVERPAGE_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxCompleteJobParams}
{$ENDIF}

function FaxSendDocumentA(FaxHandle: HANDLE; FileName: LPCSTR; JobParams: PFAX_JOB_PARAMA; CoverpageInfo: PFAX_COVERPAGE_INFOA; FaxJobId: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocumentA}
function FaxSendDocumentW(FaxHandle: HANDLE; FileName: LPCWSTR; JobParams: PFAX_JOB_PARAMW; CoverpageInfo: PFAX_COVERPAGE_INFOW; FaxJobId: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocumentW}

{$IFDEF UNICODE}
function FaxSendDocument(FaxHandle: HANDLE; FileName: LPCWSTR; JobParams: PFAX_JOB_PARAMW; CoverpageInfo: PFAX_COVERPAGE_INFOW; FaxJobId: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocument}
{$ELSE}
function FaxSendDocument(FaxHandle: HANDLE; FileName: LPCSTR; JobParams: PFAX_JOB_PARAMA; CoverpageInfo: PFAX_COVERPAGE_INFOA; FaxJobId: LPDWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocument}
{$ENDIF}

type
  PFAX_RECIPIENT_CALLBACKA = function (FaxHandle: HANDLE; RecipientNumber: DWORD; Context: LPVOID; JobParams: PFAX_JOB_PARAMA; CoverpageInfo: PFAX_COVERPAGE_INFOA): BOOL; stdcall;
  {$EXTERNALSYM PFAX_RECIPIENT_CALLBACKA}
  TFaxRecipientCallbackA = PFAX_RECIPIENT_CALLBACKA;
  PFAX_RECIPIENT_CALLBACKW = function (FaxHandle: HANDLE; RecipientNumber: DWORD; Context: LPVOID; JobParams: PFAX_JOB_PARAMW; CoverpageInfo: PFAX_COVERPAGE_INFOW): BOOL; stdcall;
  {$EXTERNALSYM PFAX_RECIPIENT_CALLBACKW}
  TFaxRecipientCallbackW = PFAX_RECIPIENT_CALLBACKW;

{$IFDEF UNICODE}
  PFAX_RECIPIENT_CALLBACK = PFAX_RECIPIENT_CALLBACKW;
  {$EXTERNALSYM PFAX_RECIPIENT_CALLBACK}
  TFaxRecipientCallback = TFaxRecipientCallbackW;
{$ELSE}
  PFAX_RECIPIENT_CALLBACK = PFAX_RECIPIENT_CALLBACKA;
  {$EXTERNALSYM PFAX_RECIPIENT_CALLBACK}
  TFaxRecipientCallback = TFaxRecipientCallbackA;  
{$ENDIF}

function FaxSendDocumentForBroadcastA(FaxHandle: HANDLE; FileName: LPCSTR; FaxJobId: LPDWORD; FaxRecipientCallback: PFAX_RECIPIENT_CALLBACKA; Context: LPVOID): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocumentForBroadcastA}
function FaxSendDocumentForBroadcastW(FaxHandle: HANDLE; FileName: LPCWSTR; FaxJobId: LPDWORD; FaxRecipientCallback: PFAX_RECIPIENT_CALLBACKW; Context: LPVOID): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocumentForBroadcastW}

{$IFDEF UNICODE}
function FaxSendDocumentForBroadcast(FaxHandle: HANDLE; FileName: LPCWSTR; FaxJobId: LPDWORD; FaxRecipientCallback: PFAX_RECIPIENT_CALLBACKW; Context: LPVOID): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocumentForBroadcast}
{$ELSE}
function FaxSendDocumentForBroadcast(FaxHandle: HANDLE; FileName: LPCSTR; FaxJobId: LPDWORD; FaxRecipientCallback: PFAX_RECIPIENT_CALLBACKA; Context: LPVOID): BOOL; stdcall;
{$EXTERNALSYM FaxSendDocumentForBroadcast}
{$ENDIF}

function FaxEnumJobsA(FaxHandle: HANDLE; var JobEntry: PFAX_JOB_ENTRYA; var JobsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumJobsA}
function FaxEnumJobsW(FaxHandle: HANDLE; var JobEntry: PFAX_JOB_ENTRYW; var JobsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumJobsW}

{$IFDEF UNICODE}
function FaxEnumJobs(FaxHandle: HANDLE; var JobEntry: PFAX_JOB_ENTRYW; var JobsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumJobs}
{$ELSE}
function FaxEnumJobs(FaxHandle: HANDLE; var JobEntry: PFAX_JOB_ENTRYA; var JobsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumJobs}
{$ENDIF}

function FaxGetJobA(FaxHandle: HANDLE; JobId: DWORD; var JobEntry: PFAX_JOB_ENTRYA): BOOL; stdcall;
{$EXTERNALSYM FaxGetJobA}
function FaxGetJobW(FaxHandle: HANDLE; JobId: DWORD; var JobEntry: PFAX_JOB_ENTRYW): BOOL; stdcall;
{$EXTERNALSYM FaxGetJobW}

{$IFDEF UNICODE}
function FaxGetJob(FaxHandle: HANDLE; JobId: DWORD; var JobEntry: PFAX_JOB_ENTRYW): BOOL; stdcall;
{$EXTERNALSYM FaxGetJob}
{$ELSE}
function FaxGetJob(FaxHandle: HANDLE; JobId: DWORD; var JobEntry: PFAX_JOB_ENTRYA): BOOL; stdcall;
{$EXTERNALSYM FaxGetJob}
{$ENDIF}

function FaxSetJobA(FaxHandle: HANDLE; JobId: DWORD; Command: DWORD; JobEntry: PFAX_JOB_ENTRYA): BOOL; stdcall;
{$EXTERNALSYM FaxSetJobA}
function FaxSetJobW(FaxHandle: HANDLE; JobId: DWORD; Command: DWORD; JobEntry: PFAX_JOB_ENTRYW): BOOL; stdcall;
{$EXTERNALSYM FaxSetJobW}

{$IFDEF UNICODE}
function FaxSetJob(FaxHandle: HANDLE; JobId: DWORD; Command: DWORD; JobEntry: PFAX_JOB_ENTRYW): BOOL; stdcall;
{$EXTERNALSYM FaxSetJob}
{$ELSE}
function FaxSetJob(FaxHandle: HANDLE; JobId: DWORD; Command: DWORD; JobEntry: PFAX_JOB_ENTRYA): BOOL; stdcall;
{$EXTERNALSYM FaxSetJob}
{$ENDIF}

function FaxGetPageData(FaxHandle: HANDLE; JobId: DWORD; var Buffer: LPBYTE; var BufferSize, ImageWidth, ImageHeight: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetPageData}

function FaxGetDeviceStatusA(FaxPortHandle: HANDLE; var DeviceStatus: PFAX_DEVICE_STATUSA): BOOL; stdcall;
{$EXTERNALSYM FaxGetDeviceStatusA}
function FaxGetDeviceStatusW(FaxPortHandle: HANDLE; var DeviceStatus: PFAX_DEVICE_STATUSW): BOOL; stdcall;
{$EXTERNALSYM FaxGetDeviceStatusW}

{$IFDEF UNICODE}
function FaxGetDeviceStatus(FaxPortHandle: HANDLE; var DeviceStatus: PFAX_DEVICE_STATUSW): BOOL; stdcall;
{$EXTERNALSYM FaxGetDeviceStatus}
{$ELSE}
function FaxGetDeviceStatus(FaxPortHandle: HANDLE; var DeviceStatus: PFAX_DEVICE_STATUSA): BOOL; stdcall;
{$EXTERNALSYM FaxGetDeviceStatus}
{$ENDIF}

function FaxAbort(FaxHandle: HANDLE; JobId: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxAbort}

function FaxGetConfigurationA(FaxHandle: HANDLE; var FaxConfig: PFAX_CONFIGURATIONA): BOOL; stdcall;
{$EXTERNALSYM FaxGetConfigurationA}
function FaxGetConfigurationW(FaxHandle: HANDLE; var FaxConfig: PFAX_CONFIGURATIONW): BOOL; stdcall;
{$EXTERNALSYM FaxGetConfigurationW}

{$IFDEF UNICODE}
function FaxGetConfiguration(FaxHandle: HANDLE; var FaxConfig: PFAX_CONFIGURATIONW): BOOL; stdcall;
{$EXTERNALSYM FaxGetConfiguration}
{$ELSE}
function FaxGetConfiguration(FaxHandle: HANDLE; var FaxConfig: PFAX_CONFIGURATIONA): BOOL; stdcall;
{$EXTERNALSYM FaxGetConfiguration}
{$ENDIF}

function FaxSetConfigurationA(FaxHandle: HANDLE; const FaxConfig: FAX_CONFIGURATIONA): BOOL; stdcall;
{$EXTERNALSYM FaxSetConfigurationA}
function FaxSetConfigurationW(FaxHandle: HANDLE; const FaxConfig: FAX_CONFIGURATIONW): BOOL; stdcall;
{$EXTERNALSYM FaxSetConfigurationW}

{$IFDEF UNICODE}
function FaxSetConfiguration(FaxHandle: HANDLE; const FaxConfig: FAX_CONFIGURATIONW): BOOL; stdcall;
{$EXTERNALSYM FaxSetConfiguration}
{$ELSE}
function FaxSetConfiguration(FaxHandle: HANDLE; const FaxConfig: FAX_CONFIGURATIONA): BOOL; stdcall;
{$EXTERNALSYM FaxSetConfiguration}
{$ENDIF}

function FaxGetLoggingCategoriesA(FaxHandle: HANDLE; var Categories: PFAX_LOG_CATEGORYA; var NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetLoggingCategoriesA}
function FaxGetLoggingCategoriesW(FaxHandle: HANDLE; var Categories: PFAX_LOG_CATEGORYW; var NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetLoggingCategoriesW}

{$IFDEF UNICODE}
function FaxGetLoggingCategories(FaxHandle: HANDLE; var Categories: PFAX_LOG_CATEGORYW; var NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetLoggingCategories}
{$ELSE}
function FaxGetLoggingCategories(FaxHandle: HANDLE; var Categories: PFAX_LOG_CATEGORYA; var NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetLoggingCategories}
{$ENDIF}

function FaxSetLoggingCategoriesA(FaxHandle: HANDLE; Categories: PFAX_LOG_CATEGORYA; NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetLoggingCategoriesA}
function FaxSetLoggingCategoriesW(FaxHandle: HANDLE; Categories: PFAX_LOG_CATEGORYW; NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetLoggingCategoriesW}

{$IFDEF UNICODE}
function FaxSetLoggingCategories(FaxHandle: HANDLE; Categories: PFAX_LOG_CATEGORYW; NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetLoggingCategories}
{$ELSE}
function FaxSetLoggingCategories(FaxHandle: HANDLE; Categories: PFAX_LOG_CATEGORYA; NumberCategories: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetLoggingCategories}
{$ENDIF}

function FaxEnumPortsA(FaxHandle: HANDLE; var PortInfo: PFAX_PORT_INFOA; var PortsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumPortsA}
function FaxEnumPortsW(FaxHandle: HANDLE; var PortInfo: PFAX_PORT_INFOW; var PortsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumPortsW}

{$IFDEF UNICODE}
function FaxEnumPorts(FaxHandle: HANDLE; var PortInfo: PFAX_PORT_INFOW; var PortsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumPorts}
{$ELSE}
function FaxEnumPorts(FaxHandle: HANDLE; var PortInfo: PFAX_PORT_INFOA; var PortsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumPorts}
{$ENDIF}

function FaxGetPortA(FaxPortHandle: HANDLE; var PortInfo: PFAX_PORT_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxGetPortA}
function FaxGetPortW(FaxPortHandle: HANDLE; var PortInfo: PFAX_PORT_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxGetPortW}

{$IFDEF UNICODE}
function FaxGetPort(FaxPortHandle: HANDLE; var PortInfo: PFAX_PORT_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxGetPort}
{$ELSE}
function FaxGetPort(FaxPortHandle: HANDLE; var PortInfo: PFAX_PORT_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxGetPort}
{$ENDIF}

function FaxSetPortA(FaxPortHandle: HANDLE; const PortInfo: FAX_PORT_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxSetPortA}
function FaxSetPortW(FaxPortHandle: HANDLE; const PortInfo: FAX_PORT_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxSetPortW}

{$IFDEF UNICODE}
function FaxSetPort(FaxPortHandle: HANDLE; const PortInfo: FAX_PORT_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxSetPort}
{$ELSE}
function FaxSetPort(FaxPortHandle: HANDLE; const PortInfo: FAX_PORT_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxSetPort}
{$ENDIF}

function FaxEnumRoutingMethodsA(FaxPortHandle: HANDLE; var RoutingMethod: PFAX_ROUTING_METHODA; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumRoutingMethodsA}
function FaxEnumRoutingMethodsW(FaxPortHandle: HANDLE; var RoutingMethod: PFAX_ROUTING_METHODW; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumRoutingMethodsW}

{$IFDEF UNICODE}
function FaxEnumRoutingMethods(FaxPortHandle: HANDLE; var RoutingMethod: PFAX_ROUTING_METHODW; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumRoutingMethods}
{$ELSE}
function FaxEnumRoutingMethods(FaxPortHandle: HANDLE; var RoutingMethod: PFAX_ROUTING_METHODA; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumRoutingMethods}
{$ENDIF}

function FaxEnableRoutingMethodA(FaxPortHandle: HANDLE; RoutingGuid: LPCSTR; Enabled: BOOL): BOOL; stdcall;
{$EXTERNALSYM FaxEnableRoutingMethodA}
function FaxEnableRoutingMethodW(FaxPortHandle: HANDLE; RoutingGuid: LPCWSTR; Enabled: BOOL): BOOL; stdcall;
{$EXTERNALSYM FaxEnableRoutingMethodW}

{$IFDEF UNICODE}
function FaxEnableRoutingMethod(FaxPortHandle: HANDLE; RoutingGuid: LPCWSTR; Enabled: BOOL): BOOL; stdcall;
{$EXTERNALSYM FaxEnableRoutingMethod}
{$ELSE}
function FaxEnableRoutingMethod(FaxPortHandle: HANDLE; RoutingGuid: LPCSTR; Enabled: BOOL): BOOL; stdcall;
{$EXTERNALSYM FaxEnableRoutingMethod}
{$ENDIF}

function FaxEnumGlobalRoutingInfoA(FaxHandle: HANDLE; var RoutingInfo: PFAX_GLOBAL_ROUTING_INFOA; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumGlobalRoutingInfoA}
function FaxEnumGlobalRoutingInfoW(FaxHandle: HANDLE; var RoutingInfo: PFAX_GLOBAL_ROUTING_INFOW; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumGlobalRoutingInfoW}

{$IFDEF UNICODE}
function FaxEnumGlobalRoutingInfo(FaxHandle: HANDLE; var RoutingInfo: PFAX_GLOBAL_ROUTING_INFOW; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumGlobalRoutingInfo}
{$ELSE}
function FaxEnumGlobalRoutingInfo(FaxHandle: HANDLE; var RoutingInfo: PFAX_GLOBAL_ROUTING_INFOA; var MethodsReturned: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxEnumGlobalRoutingInfo}
{$ENDIF}

function FaxSetGlobalRoutingInfoA(FaxHandle: HANDLE; const RoutingInfo: FAX_GLOBAL_ROUTING_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxSetGlobalRoutingInfoA}
function FaxSetGlobalRoutingInfoW(FaxHandle: HANDLE; const RoutingInfo: FAX_GLOBAL_ROUTING_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxSetGlobalRoutingInfoW}

{$IFDEF UNICODE}
function FaxSetGlobalRoutingInfo(FaxHandle: HANDLE; const RoutingInfo: FAX_GLOBAL_ROUTING_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxSetGlobalRoutingInfo}
{$ELSE}
function FaxSetGlobalRoutingInfo(FaxHandle: HANDLE; const RoutingInfo: FAX_GLOBAL_ROUTING_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxSetGlobalRoutingInfo}
{$ENDIF}

function FaxGetRoutingInfoA(FaxPortHandle: HANDLE; RoutingGuid: LPCSTR; var RoutingInfoBuffer: LPBYTE; var RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetRoutingInfoA}
function FaxGetRoutingInfoW(FaxPortHandle: HANDLE; RoutingGuid: LPCWSTR; var RoutingInfoBuffer: LPBYTE; var RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetRoutingInfoW}

{$IFDEF UNICODE}
function FaxGetRoutingInfo(FaxPortHandle: HANDLE; RoutingGuid: LPCWSTR; var RoutingInfoBuffer: LPBYTE; var RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetRoutingInfo}
{$ELSE}
function FaxGetRoutingInfo(FaxPortHandle: HANDLE; RoutingGuid: LPCSTR; var RoutingInfoBuffer: LPBYTE; var RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxGetRoutingInfo}
{$ENDIF}

function FaxSetRoutingInfoA(FaxPortHandle: HANDLE; RoutingGuid: LPCSTR; RoutingInfoBuffer: LPBYTE; RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetRoutingInfoA}
function FaxSetRoutingInfoW(FaxPortHandle: HANDLE; RoutingGuid: LPCWSTR; RoutingInfoBuffer: LPBYTE; RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetRoutingInfoW}

{$IFDEF UNICODE}
function FaxSetRoutingInfo(FaxPortHandle: HANDLE; RoutingGuid: LPCWSTR; RoutingInfoBuffer: LPBYTE; RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetRoutingInfo}
{$ELSE}
function FaxSetRoutingInfo(FaxPortHandle: HANDLE; RoutingGuid: LPCSTR; RoutingInfoBuffer: LPBYTE; RoutingInfoBufferSize: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxSetRoutingInfo}
{$ENDIF}

function FaxInitializeEventQueue(FaxHandle: HANDLE; CompletionPort: HANDLE; CompletionKey: ULONG_PTR; hWnd: HWND; MessageStart: UINT): BOOL; stdcall;
{$EXTERNALSYM FaxInitializeEventQueue}

procedure FaxFreeBuffer(Buffer: LPVOID); stdcall;
{$EXTERNALSYM FaxFreeBuffer}

function FaxStartPrintJobA(PrinterName: LPCSTR; const PrintInfo: FAX_PRINT_INFOA; var FaxJobId: DWORD; FaxContextInfo: PFAX_CONTEXT_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxStartPrintJobA}
function FaxStartPrintJobW(PrinterName: LPCWSTR; const PrintInfo: FAX_PRINT_INFOW; var FaxJobId: DWORD; FaxContextInfo: PFAX_CONTEXT_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxStartPrintJobW}

{$IFDEF UNICODE}
function FaxStartPrintJob(PrinterName: LPCWSTR; const PrintInfo: FAX_PRINT_INFOW; var FaxJobId: DWORD; FaxContextInfo: PFAX_CONTEXT_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxStartPrintJob}
{$ELSE}
function FaxStartPrintJob(PrinterName: LPCSTR; const PrintInfo: FAX_PRINT_INFOA; var FaxJobId: DWORD; FaxContextInfo: PFAX_CONTEXT_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxStartPrintJob}
{$ENDIF}

function FaxPrintCoverPageA(const FaxContextInfo: FAX_CONTEXT_INFOA; const CoverPageInfo: FAX_COVERPAGE_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxPrintCoverPageA}
function FaxPrintCoverPageW(const FaxContextInfo: FAX_CONTEXT_INFOW; const CoverPageInfo: FAX_COVERPAGE_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxPrintCoverPageW}

{$IFDEF UNICODE}
function FaxPrintCoverPage(const FaxContextInfo: FAX_CONTEXT_INFOW; const CoverPageInfo: FAX_COVERPAGE_INFOW): BOOL; stdcall;
{$EXTERNALSYM FaxPrintCoverPage}
{$ELSE}
function FaxPrintCoverPage(const FaxContextInfo: FAX_CONTEXT_INFOA; const CoverPageInfo: FAX_COVERPAGE_INFOA): BOOL; stdcall;
{$EXTERNALSYM FaxPrintCoverPage}
{$ENDIF}

function FaxRegisterServiceProviderW(DeviceProvider: LPCWSTR; FriendlyName: LPCWSTR; ImageName: LPCWSTR; TspName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM FaxRegisterServiceProviderW}

function FaxRegisterServiceProvider(DeviceProvider: LPCWSTR; FriendlyName: LPCWSTR; ImageName: LPCWSTR; TspName: LPCWSTR): BOOL;
{$EXTERNALSYM FaxRegisterServiceProvider}

function FaxUnregisterServiceProviderW(DeviceProvider: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM FaxUnregisterServiceProviderW}

function FaxUnregisterServiceProvider(DeviceProvider: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM FaxUnregisterServiceProvider}

type
  PFAXUNREGISTERSERVICEPROVIDERW = function (DeviceProvider: LPCWSTR): BOOL; stdcall;
  {$EXTERNALSYM PFAXUNREGISTERSERVICEPROVIDERW}
  PFAXUNREGISTERSERVICEPROVIDER = PFAXUNREGISTERSERVICEPROVIDERW;
  {$EXTERNALSYM PFAXUNREGISTERSERVICEPROVIDER}

type
  PFAX_ROUTING_INSTALLATION_CALLBACKW = function (FaxHandle: HANDLE; Context: LPVOID; MethodName, FriendlyName, FunctionName, Guid: LPWSTR): BOOL; stdcall;
  {$EXTERNALSYM PFAX_ROUTING_INSTALLATION_CALLBACKW}
  TFaxRoutingInstallationCallbackW = PFAX_ROUTING_INSTALLATION_CALLBACKW;

  PFAX_ROUTING_INSTALLATION_CALLBACK = PFAX_ROUTING_INSTALLATION_CALLBACKW;
  {$EXTERNALSYM PFAX_ROUTING_INSTALLATION_CALLBACK}
  TFaxRoutingInstallationCallback = TFaxRoutingInstallationCallbackW;

function FaxRegisterRoutingExtensionW(FaxHandle: HANDLE; ExtensionName, FriendlyName, ImageName: LPCWSTR; CallBack: PFAX_ROUTING_INSTALLATION_CALLBACKW; Context: LPVOID): BOOL; stdcall;
{$EXTERNALSYM FaxRegisterRoutingExtensionW}

function FaxRegisterRoutingExtension(FaxHandle: HANDLE; ExtensionName, FriendlyName, ImageName: LPCWSTR; CallBack: PFAX_ROUTING_INSTALLATION_CALLBACKW; Context: LPVOID): BOOL;
{$EXTERNALSYM FaxRegisterRoutingExtension}

function FaxUnregisterRoutingExtensionA(hFaxHandle: HANDLE; lpctstrExtensionName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM FaxUnregisterRoutingExtensionA}
function FaxUnregisterRoutingExtensionW(hFaxHandle: HANDLE; lpctstrExtensionName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM FaxUnregisterRoutingExtensionW}

{$IFDEF UNICODE}
function FaxUnregisterRoutingExtension(hFaxHandle: HANDLE; lpctstrExtensionName: LPCWSTR): BOOL; stdcall;
{$EXTERNALSYM FaxUnregisterRoutingExtension}
{$ELSE}
function FaxUnregisterRoutingExtension(hFaxHandle: HANDLE; lpctstrExtensionName: LPCSTR): BOOL; stdcall;
{$EXTERNALSYM FaxUnregisterRoutingExtension}
{$ENDIF}

function FaxAccessCheck(FaxHandle: HANDLE; AccessMask: DWORD): BOOL; stdcall;
{$EXTERNALSYM FaxAccessCheck}

//
// Fax Specific Access Rights
//

const
  FAX_JOB_SUBMIT   = ($0001);
  {$EXTERNALSYM FAX_JOB_SUBMIT}
  FAX_JOB_QUERY    = ($0002);
  {$EXTERNALSYM FAX_JOB_QUERY}
  FAX_CONFIG_QUERY = ($0004);
  {$EXTERNALSYM FAX_CONFIG_QUERY}
  FAX_CONFIG_SET   = ($0008);
  {$EXTERNALSYM FAX_CONFIG_SET}
  FAX_PORT_QUERY   = ($0010);
  {$EXTERNALSYM FAX_PORT_QUERY}
  FAX_PORT_SET     = ($0020);
  {$EXTERNALSYM FAX_PORT_SET}
  FAX_JOB_MANAGE   = ($0040);
  {$EXTERNALSYM FAX_JOB_MANAGE}

  FAX_READ = (STANDARD_RIGHTS_READ or FAX_JOB_QUERY or FAX_CONFIG_QUERY or FAX_PORT_QUERY);
  {$EXTERNALSYM FAX_READ}

  FAX_WRITE = (STANDARD_RIGHTS_WRITE or FAX_JOB_SUBMIT );
  {$EXTERNALSYM FAX_WRITE}

  FAX_ALL_ACCESS = (STANDARD_RIGHTS_ALL or FAX_JOB_SUBMIT or FAX_JOB_QUERY or FAX_CONFIG_QUERY or FAX_CONFIG_SET or FAX_PORT_QUERY or FAX_PORT_SET or FAX_JOB_MANAGE);
  {$EXTERNALSYM FAX_ALL_ACCESS}

implementation

const
  winfax = 'winfax.dll';

function FaxConnectFaxServerA; external winfax name 'FaxConnectFaxServerA';
function FaxConnectFaxServerW; external winfax name 'FaxConnectFaxServerW';
{$IFDEF UNICODE}
function FaxConnectFaxServer; external winfax name 'FaxConnectFaxServerW';
{$ELSE}
function FaxConnectFaxServer; external winfax name 'FaxConnectFaxServerA';
{$ENDIF}
function FaxClose; external winfax name 'FaxClose';
function FaxOpenPort; external winfax name 'FaxOpenPort';
function FaxCompleteJobParamsA; external winfax name 'FaxCompleteJobParamsA';
function FaxCompleteJobParamsW; external winfax name 'FaxCompleteJobParamsW';
{$IFDEF UNICODE}
function FaxCompleteJobParams; external winfax name 'FaxCompleteJobParamsW';
{$ELSE}
function FaxCompleteJobParams; external winfax name 'FaxCompleteJobParamsA';
{$ENDIF}
function FaxSendDocumentA; external winfax name 'FaxSendDocumentA';
function FaxSendDocumentW; external winfax name 'FaxSendDocumentW';
{$IFDEF UNICODE}
function FaxSendDocument; external winfax name 'FaxSendDocumentW';
{$ELSE}
function FaxSendDocument; external winfax name 'FaxSendDocumentA';
{$ENDIF}
function FaxSendDocumentForBroadcastA; external winfax name 'FaxSendDocumentForBroadcastA';
function FaxSendDocumentForBroadcastW; external winfax name 'FaxSendDocumentForBroadcastW';
{$IFDEF UNICODE}
function FaxSendDocumentForBroadcast; external winfax name 'FaxSendDocumentForBroadcastW';
{$ELSE}
function FaxSendDocumentForBroadcast; external winfax name 'FaxSendDocumentForBroadcastA';
{$ENDIF}
function FaxEnumJobsA; external winfax name 'FaxEnumJobsA';
function FaxEnumJobsW; external winfax name 'FaxEnumJobsW';
{$IFDEF UNICODE}
function FaxEnumJobs; external winfax name 'FaxEnumJobsW';
{$ELSE}
function FaxEnumJobs; external winfax name 'FaxEnumJobsA';
{$ENDIF}
function FaxGetJobA; external winfax name 'FaxGetJobA';
function FaxGetJobW; external winfax name 'FaxGetJobW';
{$IFDEF UNICODE}
function FaxGetJob; external winfax name 'FaxGetJobW';
{$ELSE}
function FaxGetJob; external winfax name 'FaxGetJobA';
{$ENDIF}
function FaxSetJobA; external winfax name 'FaxSetJobA';
function FaxSetJobW; external winfax name 'FaxSetJobW';
{$IFDEF UNICODE}
function FaxSetJob; external winfax name 'FaxSetJobW';
{$ELSE}
function FaxSetJob; external winfax name 'FaxSetJobA';
{$ENDIF}
function FaxGetPageData; external winfax name 'FaxGetPageData';
function FaxGetDeviceStatusA; external winfax name 'FaxGetDeviceStatusA';
function FaxGetDeviceStatusW; external winfax name 'FaxGetDeviceStatusW';
{$IFDEF UNICODE}
function FaxGetDeviceStatus; external winfax name 'FaxGetDeviceStatusW';
{$ELSE}
function FaxGetDeviceStatus; external winfax name 'FaxGetDeviceStatusA';
{$ENDIF}
function FaxAbort; external winfax name 'FaxAbort';
function FaxGetConfigurationA; external winfax name 'FaxGetConfigurationA';
function FaxGetConfigurationW; external winfax name 'FaxGetConfigurationW';
{$IFDEF UNICODE}
function FaxGetConfiguration; external winfax name 'FaxGetConfigurationW';
{$ELSE}
function FaxGetConfiguration; external winfax name 'FaxGetConfigurationA';
{$ENDIF}
function FaxSetConfigurationA; external winfax name 'FaxSetConfigurationA';
function FaxSetConfigurationW; external winfax name 'FaxSetConfigurationW';
{$IFDEF UNICODE}
function FaxSetConfiguration; external winfax name 'FaxSetConfigurationW';
{$ELSE}
function FaxSetConfiguration; external winfax name 'FaxSetConfigurationA';
{$ENDIF}
function FaxGetLoggingCategoriesA; external winfax name 'FaxGetLoggingCategoriesA';
function FaxGetLoggingCategoriesW; external winfax name 'FaxGetLoggingCategoriesW';
{$IFDEF UNICODE}
function FaxGetLoggingCategories; external winfax name 'FaxGetLoggingCategoriesW';
{$ELSE}
function FaxGetLoggingCategories; external winfax name 'FaxGetLoggingCategoriesA';
{$ENDIF}
function FaxSetLoggingCategoriesA; external winfax name 'FaxSetLoggingCategoriesA';
function FaxSetLoggingCategoriesW; external winfax name 'FaxSetLoggingCategoriesW';
{$IFDEF UNICODE}
function FaxSetLoggingCategories; external winfax name 'FaxSetLoggingCategoriesW';
{$ELSE}
function FaxSetLoggingCategories; external winfax name 'FaxSetLoggingCategoriesA';
{$ENDIF}
function FaxEnumPortsA; external winfax name 'FaxEnumPortsA';
function FaxEnumPortsW; external winfax name 'FaxEnumPortsW';
{$IFDEF UNICODE}
function FaxEnumPorts; external winfax name 'FaxEnumPortsW';
{$ELSE}
function FaxEnumPorts; external winfax name 'FaxEnumPortsA';
{$ENDIF}
function FaxGetPortA; external winfax name 'FaxGetPortA';
function FaxGetPortW; external winfax name 'FaxGetPortW';
{$IFDEF UNICODE}
function FaxGetPort; external winfax name 'FaxGetPortW';
{$ELSE}
function FaxGetPort; external winfax name 'FaxGetPortA';
{$ENDIF}
function FaxSetPortA; external winfax name 'FaxSetPortA';
function FaxSetPortW; external winfax name 'FaxSetPortW';
{$IFDEF UNICODE}
function FaxSetPort; external winfax name 'FaxSetPortW';
{$ELSE}
function FaxSetPort; external winfax name 'FaxSetPortA';
{$ENDIF}
function FaxEnumRoutingMethodsA; external winfax name 'FaxEnumRoutingMethodsA';
function FaxEnumRoutingMethodsW; external winfax name 'FaxEnumRoutingMethodsW';
{$IFDEF UNICODE}
function FaxEnumRoutingMethods; external winfax name 'FaxEnumRoutingMethodsW';
{$ELSE}
function FaxEnumRoutingMethods; external winfax name 'FaxEnumRoutingMethodsA';
{$ENDIF}
function FaxEnableRoutingMethodA; external winfax name 'FaxEnableRoutingMethodA';
function FaxEnableRoutingMethodW; external winfax name 'FaxEnableRoutingMethodW';
{$IFDEF UNICODE}
function FaxEnableRoutingMethod; external winfax name 'FaxEnableRoutingMethodW';
{$ELSE}
function FaxEnableRoutingMethod; external winfax name 'FaxEnableRoutingMethodA';
{$ENDIF}
function FaxEnumGlobalRoutingInfoA; external winfax name 'FaxEnumGlobalRoutingInfoA';
function FaxEnumGlobalRoutingInfoW; external winfax name 'FaxEnumGlobalRoutingInfoW';
{$IFDEF UNICODE}
function FaxEnumGlobalRoutingInfo; external winfax name 'FaxEnumGlobalRoutingInfoW';
{$ELSE}
function FaxEnumGlobalRoutingInfo; external winfax name 'FaxEnumGlobalRoutingInfoA';
{$ENDIF}
function FaxSetGlobalRoutingInfoA; external winfax name 'FaxSetGlobalRoutingInfoA';
function FaxSetGlobalRoutingInfoW; external winfax name 'FaxSetGlobalRoutingInfoW';
{$IFDEF UNICODE}
function FaxSetGlobalRoutingInfo; external winfax name 'FaxSetGlobalRoutingInfoW';
{$ELSE}
function FaxSetGlobalRoutingInfo; external winfax name 'FaxSetGlobalRoutingInfoA';
{$ENDIF}
function FaxGetRoutingInfoA; external winfax name 'FaxGetRoutingInfoA';
function FaxGetRoutingInfoW; external winfax name 'FaxGetRoutingInfoW';
{$IFDEF UNICODE}
function FaxGetRoutingInfo; external winfax name 'FaxGetRoutingInfoW';
{$ELSE}
function FaxGetRoutingInfo; external winfax name 'FaxGetRoutingInfoA';
{$ENDIF}
function FaxSetRoutingInfoA; external winfax name 'FaxSetRoutingInfoA';
function FaxSetRoutingInfoW; external winfax name 'FaxSetRoutingInfoW';
{$IFDEF UNICODE}
function FaxSetRoutingInfo; external winfax name 'FaxSetRoutingInfoW';
{$ELSE}
function FaxSetRoutingInfo; external winfax name 'FaxSetRoutingInfoA';
{$ENDIF}
function FaxInitializeEventQueue; external winfax name 'FaxInitializeEventQueue';
procedure FaxFreeBuffer; external winfax name 'FaxFreeBuffer';
function FaxStartPrintJobA; external winfax name 'FaxStartPrintJobA';
function FaxStartPrintJobW; external winfax name 'FaxStartPrintJobW';
{$IFDEF UNICODE}
function FaxStartPrintJob; external winfax name 'FaxStartPrintJobW';
{$ELSE}
function FaxStartPrintJob; external winfax name 'FaxStartPrintJobA';
{$ENDIF}
function FaxPrintCoverPageA; external winfax name 'FaxPrintCoverPageA';
function FaxPrintCoverPageW; external winfax name 'FaxPrintCoverPageW';
{$IFDEF UNICODE}
function FaxPrintCoverPage; external winfax name 'FaxPrintCoverPageW';
{$ELSE}
function FaxPrintCoverPage; external winfax name 'FaxPrintCoverPageA';
{$ENDIF}
function FaxRegisterServiceProviderW; external winfax name 'FaxRegisterServiceProviderW';

function FaxRegisterServiceProvider(DeviceProvider: LPCWSTR; FriendlyName: LPCWSTR; ImageName: LPCWSTR; TspName: LPCWSTR): BOOL;
begin
  Result := FaxRegisterServiceProvider(DeviceProvider, FriendlyName, ImageName, TspName);
end;

function FaxUnregisterServiceProviderW; external winfax name 'FaxUnregisterServiceProviderW';

function FaxUnregisterServiceProvider(DeviceProvider: LPCWSTR): BOOL;
begin
  Result := FaxUnregisterServiceProviderW(DeviceProvider);
end;

function FaxRegisterRoutingExtensionW; external winfax name 'FaxRegisterRoutingExtensionW';

function FaxRegisterRoutingExtension(FaxHandle: HANDLE; ExtensionName, FriendlyName, ImageName: LPCWSTR; CallBack: PFAX_ROUTING_INSTALLATION_CALLBACKW; Context: LPVOID): BOOL;
begin
  Result := FaxRegisterRoutingExtension(FaxHandle, ExtensionName, FriendlyName, ImageName, CallBack, Context);
end;

function FaxUnregisterRoutingExtensionA; external winfax name 'FaxUnregisterRoutingExtensionA';
function FaxUnregisterRoutingExtensionW; external winfax name 'FaxUnregisterRoutingExtensionW';

{$IFDEF UNICODE}
function FaxUnregisterRoutingExtension; external winfax name 'FaxUnregisterRoutingExtensionW';
{$ELSE}
function FaxUnregisterRoutingExtension; external winfax name 'FaxUnregisterRoutingExtensionA';
{$ENDIF}
function FaxAccessCheck; external winfax name 'FaxAccessCheck';


end.
