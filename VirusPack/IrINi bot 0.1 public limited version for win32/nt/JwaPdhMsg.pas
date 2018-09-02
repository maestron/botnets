{******************************************************************************}
{                                                       	               }
{ Performance Data Helper Error Codes API interface Unit for Object Pascal     }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: pdhmsg.h, released August 2001. The original Pascal    }
{ code is: PdhMsg.pas, released December 2000. The initial developer of the    }
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

unit JwaPdhMsg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "pdhmsg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//     PDH DLL messages
//
//
//      Success Messages
//
//         the Win32 error value ERROR_SUCCESS is used for success returns
//
//      MESSAGE NAME FORMAT
//
//          PDH_CSTATUS_...   messages are data item status message and
//                     are returned in reference to the status of a data
//                     item
//          PDH_...           messages are returned by FUNCTIONS only and
//                     not used as data item status values
//
//      Success Messages
//         These messages are normally returned when the operation completed
//         successfully.
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

const

//
// Define the severity codes
//

  STATUS_SEVERITY_WARNING          = $2;
  {$EXTERNALSYM STATUS_SEVERITY_WARNING}
  STATUS_SEVERITY_SUCCESS          = $0;
  {$EXTERNALSYM STATUS_SEVERITY_SUCCESS}
  STATUS_SEVERITY_INFORMATIONAL    = $1;
  {$EXTERNALSYM STATUS_SEVERITY_INFORMATIONAL}
  STATUS_SEVERITY_ERROR            = $3;
  {$EXTERNALSYM STATUS_SEVERITY_ERROR}

//
// MessageId: PDH_CSTATUS_VALID_DATA
//
// MessageText:
//
//  The returned data is valid.
//

  PDH_CSTATUS_VALID_DATA           = DWORD($00000000);
  {$EXTERNALSYM PDH_CSTATUS_VALID_DATA}

//
// MessageId: PDH_CSTATUS_NEW_DATA
//
// MessageText:
//
//  The return data value is valid and different from the last sample.
//

  PDH_CSTATUS_NEW_DATA             = DWORD($00000001);
  {$EXTERNALSYM PDH_CSTATUS_NEW_DATA}

//
//        Informational messages
//
//  None
//
//      Warning Messages
//         These messages are returned when the function has completed
//         successfully but the results may be different than expected.
//
//
// MessageId: PDH_CSTATUS_NO_MACHINE
//
// MessageText:
//
//  Unable to connect to specified machine or machine is off line.
//

  PDH_CSTATUS_NO_MACHINE           = DWORD($800007D0);
  {$EXTERNALSYM PDH_CSTATUS_NO_MACHINE}

//
// MessageId: PDH_CSTATUS_NO_INSTANCE
//
// MessageText:
//
//  The specified instance is not present.
//

  PDH_CSTATUS_NO_INSTANCE          = DWORD($800007D1);
  {$EXTERNALSYM PDH_CSTATUS_NO_INSTANCE}

//
// MessageId: PDH_MORE_DATA
//
// MessageText:
//
//  There is more data to return than would fit in the supplied buffer. Allocate
//  a larger buffer and call the function again.
//

  PDH_MORE_DATA                    = DWORD($800007D2);
  {$EXTERNALSYM PDH_MORE_DATA}

//
// MessageId: PDH_CSTATUS_ITEM_NOT_VALIDATED
//
// MessageText:
//
//  The data item has been added to the query, but has not been validated nor
//  accessed. No other status information on this data item is available.
//

  PDH_CSTATUS_ITEM_NOT_VALIDATED   = DWORD($800007D3);
  {$EXTERNALSYM PDH_CSTATUS_ITEM_NOT_VALIDATED}

//
// MessageId: PDH_RETRY
//
// MessageText:
//
//  The selected operation should be retried.
//

  PDH_RETRY                        = DWORD($800007D4);
  {$EXTERNALSYM PDH_RETRY}

//
// MessageId: PDH_NO_DATA
//
// MessageText:
//
//  No data to return.
//

  PDH_NO_DATA                      = DWORD($800007D5);
  {$EXTERNALSYM PDH_NO_DATA}

//
// MessageId: PDH_CALC_NEGATIVE_DENOMINATOR
//
// MessageText:
//
//  A counter with a negative denominator value was detected.
//

  PDH_CALC_NEGATIVE_DENOMINATOR    = DWORD($800007D6);
  {$EXTERNALSYM PDH_CALC_NEGATIVE_DENOMINATOR}

//
// MessageId: PDH_CALC_NEGATIVE_TIMEBASE
//
// MessageText:
//
//  A counter with a negative timebase value was detected.
//

  PDH_CALC_NEGATIVE_TIMEBASE       = DWORD($800007D7);
  {$EXTERNALSYM PDH_CALC_NEGATIVE_TIMEBASE}

//
// MessageId: PDH_CALC_NEGATIVE_VALUE
//
// MessageText:
//
//  A counter with a negative value was detected.
//

  PDH_CALC_NEGATIVE_VALUE          = DWORD($800007D8);
  {$EXTERNALSYM PDH_CALC_NEGATIVE_VALUE}

//
// MessageId: PDH_DIALOG_CANCELLED
//
// MessageText:
//
//  The user cancelled the dialog box.
//

  PDH_DIALOG_CANCELLED             = DWORD($800007D9);
  {$EXTERNALSYM PDH_DIALOG_CANCELLED}

//
// MessageId: PDH_END_OF_LOG_FILE
//
// MessageText:
//
//  The end of the log file was reached.
//

  PDH_END_OF_LOG_FILE              = DWORD($800007DA);
  {$EXTERNALSYM PDH_END_OF_LOG_FILE}

//
// MessageId: PDH_ASYNC_QUERY_TIMEOUT
//
// MessageText:
//
//  Time out while waiting for asynchronous counter collection thread to end.
//

  PDH_ASYNC_QUERY_TIMEOUT          = DWORD($800007DB);
  {$EXTERNALSYM PDH_ASYNC_QUERY_TIMEOUT}

//
// MessageId: PDH_CANNOT_SET_DEFAULT_REALTIME_DATASOURCE
//
// MessageText:
//
//  Cannot change default real-time data source. There are real-time query
//  sessions collecting counter data.
//

  PDH_CANNOT_SET_DEFAULT_REALTIME_DATASOURCE = DWORD($800007DC);
  {$EXTERNALSYM PDH_CANNOT_SET_DEFAULT_REALTIME_DATASOURCE}

//
//     Error Messages
//        These messages are returned when the function could not complete
//        as requested and some corrective action may be required by the
//        the caller or the user.
//
//
// MessageId: PDH_CSTATUS_NO_OBJECT
//
// MessageText:
//
//  The specified object is not found on the system.
//

  PDH_CSTATUS_NO_OBJECT            = DWORD($C0000BB8);
  {$EXTERNALSYM PDH_CSTATUS_NO_OBJECT}

//
// MessageId: PDH_CSTATUS_NO_COUNTER
//
// MessageText:
//
//  The specified counter could not be found.
//

  PDH_CSTATUS_NO_COUNTER           = DWORD($C0000BB9);
  {$EXTERNALSYM PDH_CSTATUS_NO_COUNTER}

//
// MessageId: PDH_CSTATUS_INVALID_DATA
//
// MessageText:
//
//  The returned data is not valid.
//

  PDH_CSTATUS_INVALID_DATA         = DWORD($C0000BBA);
  {$EXTERNALSYM PDH_CSTATUS_INVALID_DATA}

//
// MessageId: PDH_MEMORY_ALLOCATION_FAILURE
//
// MessageText:
//
//  A PDH function could not allocate enough temporary memory to complete the
//  operation. Close some applications or extend the pagefile and retry the
//  function.
//

  PDH_MEMORY_ALLOCATION_FAILURE    = DWORD($C0000BBB);
  {$EXTERNALSYM PDH_MEMORY_ALLOCATION_FAILURE}

//
// MessageId: PDH_INVALID_HANDLE
//
// MessageText:
//
//  The handle is not a valid PDH object.
//

  PDH_INVALID_HANDLE               = DWORD($C0000BBC);
  {$EXTERNALSYM PDH_INVALID_HANDLE}

//
// MessageId: PDH_INVALID_ARGUMENT
//
// MessageText:
//
//  A required argument is missing or incorrect.
//

  PDH_INVALID_ARGUMENT             = DWORD($C0000BBD);
  {$EXTERNALSYM PDH_INVALID_ARGUMENT}

//
// MessageId: PDH_FUNCTION_NOT_FOUND
//
// MessageText:
//
//  Unable to find the specified function.
//

  PDH_FUNCTION_NOT_FOUND           = DWORD($C0000BBE);
  {$EXTERNALSYM PDH_FUNCTION_NOT_FOUND}

//
// MessageId: PDH_CSTATUS_NO_COUNTERNAME
//
// MessageText:
//
//  No counter was specified.
//

  PDH_CSTATUS_NO_COUNTERNAME       = DWORD($C0000BBF);
  {$EXTERNALSYM PDH_CSTATUS_NO_COUNTERNAME}

//
// MessageId: PDH_CSTATUS_BAD_COUNTERNAME
//
// MessageText:
//
//  Unable to parse the counter path. Check the format and syntax of the
//  specified path.
//

  PDH_CSTATUS_BAD_COUNTERNAME      = DWORD($C0000BC0);
  {$EXTERNALSYM PDH_CSTATUS_BAD_COUNTERNAME}

//
// MessageId: PDH_INVALID_BUFFER
//
// MessageText:
//
//  The buffer passed by the caller is invalid.
//

  PDH_INVALID_BUFFER               = DWORD($C0000BC1);
  {$EXTERNALSYM PDH_INVALID_BUFFER}

//
// MessageId: PDH_INSUFFICIENT_BUFFER
//
// MessageText:
//
//  The requested data is larger than the buffer supplied. Unable to return the
//  requested data.
//

  PDH_INSUFFICIENT_BUFFER          = DWORD($C0000BC2);
  {$EXTERNALSYM PDH_INSUFFICIENT_BUFFER}

//
// MessageId: PDH_CANNOT_CONNECT_MACHINE
//
// MessageText:
//
//  Unable to connect to the requested machine.
//

  PDH_CANNOT_CONNECT_MACHINE       = DWORD($C0000BC3);
  {$EXTERNALSYM PDH_CANNOT_CONNECT_MACHINE}

//
// MessageId: PDH_INVALID_PATH
//
// MessageText:
//
//  The specified counter path could not be interpreted.
//

  PDH_INVALID_PATH                 = DWORD($C0000BC4);
  {$EXTERNALSYM PDH_INVALID_PATH}

//
// MessageId: PDH_INVALID_INSTANCE
//
// MessageText:
//
//  The instance name could not be read from the specified counter path.
//

  PDH_INVALID_INSTANCE             = DWORD($C0000BC5);
  {$EXTERNALSYM PDH_INVALID_INSTANCE}

//
// MessageId: PDH_INVALID_DATA
//
// MessageText:
//
//  The data is not valid.
//

  PDH_INVALID_DATA                 = DWORD($C0000BC6);
  {$EXTERNALSYM PDH_INVALID_DATA}

//
// MessageId: PDH_NO_DIALOG_DATA
//
// MessageText:
//
//  The dialog box data block was missing or invalid.
//

  PDH_NO_DIALOG_DATA               = DWORD($C0000BC7);
  {$EXTERNALSYM PDH_NO_DIALOG_DATA}

//
// MessageId: PDH_CANNOT_READ_NAME_STRINGS
//
// MessageText:
//
//  Unable to read the counter and/or explain text from the specified machine.
//

  PDH_CANNOT_READ_NAME_STRINGS     = DWORD($C0000BC8);
  {$EXTERNALSYM PDH_CANNOT_READ_NAME_STRINGS}

//
// MessageId: PDH_LOG_FILE_CREATE_ERROR
//
// MessageText:
//
//  Unable to create the specified log file.
//

  PDH_LOG_FILE_CREATE_ERROR        = DWORD($C0000BC9);
  {$EXTERNALSYM PDH_LOG_FILE_CREATE_ERROR}

//
// MessageId: PDH_LOG_FILE_OPEN_ERROR
//
// MessageText:
//
//  Unable to open the specified log file.
//

  PDH_LOG_FILE_OPEN_ERROR          = DWORD($C0000BCA);
  {$EXTERNALSYM PDH_LOG_FILE_OPEN_ERROR}

//
// MessageId: PDH_LOG_TYPE_NOT_FOUND
//
// MessageText:
//
//  The specified log file type has not been installed on this system.
//

  PDH_LOG_TYPE_NOT_FOUND           = DWORD($C0000BCB);
  {$EXTERNALSYM PDH_LOG_TYPE_NOT_FOUND}

//
// MessageId: PDH_NO_MORE_DATA
//
// MessageText:
//
//  No more data is available.
//

  PDH_NO_MORE_DATA                 = DWORD($C0000BCC);
  {$EXTERNALSYM PDH_NO_MORE_DATA}

//
// MessageId: PDH_ENTRY_NOT_IN_LOG_FILE
//
// MessageText:
//
//  The specified record was not found in the log file.
//

  PDH_ENTRY_NOT_IN_LOG_FILE        = DWORD($C0000BCD);
  {$EXTERNALSYM PDH_ENTRY_NOT_IN_LOG_FILE}

//
// MessageId: PDH_DATA_SOURCE_IS_LOG_FILE
//
// MessageText:
//
//  The specified data source is a log file.
//

  PDH_DATA_SOURCE_IS_LOG_FILE      = DWORD($C0000BCE);
  {$EXTERNALSYM PDH_DATA_SOURCE_IS_LOG_FILE}

//
// MessageId: PDH_DATA_SOURCE_IS_REAL_TIME
//
// MessageText:
//
//  The specified data source is the current activity.
//

  PDH_DATA_SOURCE_IS_REAL_TIME     = DWORD($C0000BCF);
  {$EXTERNALSYM PDH_DATA_SOURCE_IS_REAL_TIME}

//
// MessageId: PDH_UNABLE_READ_LOG_HEADER
//
// MessageText:
//
//  The log file header could not be read.
//

  PDH_UNABLE_READ_LOG_HEADER       = DWORD($C0000BD0);
  {$EXTERNALSYM PDH_UNABLE_READ_LOG_HEADER}

//
// MessageId: PDH_FILE_NOT_FOUND
//
// MessageText:
//
//  Unable to find the specified file.
//

  PDH_FILE_NOT_FOUND               = DWORD($C0000BD1);
  {$EXTERNALSYM PDH_FILE_NOT_FOUND}

//
// MessageId: PDH_FILE_ALREADY_EXISTS
//
// MessageText:
//
//  There is already a file with the specified file name.
//

  PDH_FILE_ALREADY_EXISTS          = DWORD($C0000BD2);
  {$EXTERNALSYM PDH_FILE_ALREADY_EXISTS}

//
// MessageId: PDH_NOT_IMPLEMENTED
//
// MessageText:
//
//  The function referenced has not been implemented.
//

  PDH_NOT_IMPLEMENTED              = DWORD($C0000BD3);
  {$EXTERNALSYM PDH_NOT_IMPLEMENTED}

//
// MessageId: PDH_STRING_NOT_FOUND
//
// MessageText:
//
//  Unable to find the specified string in the list of performance name and
//  explain text strings.
//

  PDH_STRING_NOT_FOUND             = DWORD($C0000BD4);
  {$EXTERNALSYM PDH_STRING_NOT_FOUND}

//
// MessageId: PDH_UNABLE_MAP_NAME_FILES
//
// MessageText:
//
//  Unable to map to the performance counter name data files. The data
//  will be read from the registry and stored locally.
//

  PDH_UNABLE_MAP_NAME_FILES        = DWORD($80000BD5);
  {$EXTERNALSYM PDH_UNABLE_MAP_NAME_FILES}

//
// MessageId: PDH_UNKNOWN_LOG_FORMAT
//
// MessageText:
//
//  The format of the specified log file is not recognized by the PDH DLL.
//

  PDH_UNKNOWN_LOG_FORMAT           = DWORD($C0000BD6);
  {$EXTERNALSYM PDH_UNKNOWN_LOG_FORMAT}

//
// MessageId: PDH_UNKNOWN_LOGSVC_COMMAND
//
// MessageText:
//
//  The specified Log Service command value is not recognized.
//

  PDH_UNKNOWN_LOGSVC_COMMAND       = DWORD($C0000BD7);
  {$EXTERNALSYM PDH_UNKNOWN_LOGSVC_COMMAND}

//
// MessageId: PDH_LOGSVC_QUERY_NOT_FOUND
//
// MessageText:
//
//  The specified Query from the Log Service could not be found or could not
//  be opened.
//

  PDH_LOGSVC_QUERY_NOT_FOUND       = DWORD($C0000BD8);
  {$EXTERNALSYM PDH_LOGSVC_QUERY_NOT_FOUND}

//
// MessageId: PDH_LOGSVC_NOT_OPENED
//
// MessageText:
//
//  The Performance Data Log Service key could not be opened. This may be due
//  to insufficient privilege or because the service has not been installed.
//

  PDH_LOGSVC_NOT_OPENED            = DWORD($C0000BD9);
  {$EXTERNALSYM PDH_LOGSVC_NOT_OPENED}

//
// MessageId: PDH_WBEM_ERROR
//
// MessageText:
//
//  An error occurred while accessing the WBEM data store.
//

  PDH_WBEM_ERROR                   = DWORD($C0000BDA);
  {$EXTERNALSYM PDH_WBEM_ERROR}

//
// MessageId: PDH_ACCESS_DENIED
//
// MessageText:
//
//  Unable to access the desired machine or service. Check the permissions and
//  authentication of the log service or the interactive user session against
//  those on the machine or service being monitored.
//

  PDH_ACCESS_DENIED                = DWORD($C0000BDB);
  {$EXTERNALSYM PDH_ACCESS_DENIED}

//
// MessageId: PDH_LOG_FILE_TOO_SMALL
//
// MessageText:
//
//  The maximum log file size specified is too small to log the selected counters.
//  No data will be recorded in this log file. Specify a smaller set of counters
//  to log or a larger file size and retry this call.
//

  PDH_LOG_FILE_TOO_SMALL           = DWORD($C0000BDC);
  {$EXTERNALSYM PDH_LOG_FILE_TOO_SMALL}

//
// MessageId: PDH_INVALID_DATASOURCE
//
// MessageText:
//
//  Cannot connect to ODBC DataSource Name.
//

  PDH_INVALID_DATASOURCE           = DWORD($C0000BDD);
  {$EXTERNALSYM PDH_INVALID_DATASOURCE}

//
// MessageId: PDH_INVALID_SQLDB
//
// MessageText:
//
//  SQL Database does not contain a valid set of tables for Perfmon, use PdhCreateSQLTables.
//

  PDH_INVALID_SQLDB                = DWORD($C0000BDE);
  {$EXTERNALSYM PDH_INVALID_SQLDB}

//
// MessageId: PDH_NO_COUNTERS
//
// MessageText:
//
//  No counters were found for this Perfmon SQL Log Set.
//

  PDH_NO_COUNTERS                  = DWORD($C0000BDF);
  {$EXTERNALSYM PDH_NO_COUNTERS}

//
// MessageId: PDH_SQL_ALLOC_FAILED
//
// MessageText:
//
//  Call to SQLAllocStmt failed with %1.
//

  PDH_SQL_ALLOC_FAILED             = DWORD($C0000BE0);
  {$EXTERNALSYM PDH_SQL_ALLOC_FAILED}

//
// MessageId: PDH_SQL_ALLOCCON_FAILED
//
// MessageText:
//
//  Call to SQLAllocConnect failed with %1.
//

  PDH_SQL_ALLOCCON_FAILED          = DWORD($C0000BE1);
  {$EXTERNALSYM PDH_SQL_ALLOCCON_FAILED}

//
// MessageId: PDH_SQL_EXEC_DIRECT_FAILED
//
// MessageText:
//
//  Call to SQLExecDirect failed with %1.
//

  PDH_SQL_EXEC_DIRECT_FAILED       = DWORD($C0000BE2);
  {$EXTERNALSYM PDH_SQL_EXEC_DIRECT_FAILED}

//
// MessageId: PDH_SQL_FETCH_FAILED
//
// MessageText:
//
//  Call to SQLFetch failed with %1.
//

  PDH_SQL_FETCH_FAILED             = DWORD($C0000BE3);
  {$EXTERNALSYM PDH_SQL_FETCH_FAILED}

//
// MessageId: PDH_SQL_ROWCOUNT_FAILED
//
// MessageText:
//
//  Call to SQLRowCount failed with %1.
//

  PDH_SQL_ROWCOUNT_FAILED          = DWORD($C0000BE4);
  {$EXTERNALSYM PDH_SQL_ROWCOUNT_FAILED}

//
// MessageId: PDH_SQL_MORE_RESULTS_FAILED
//
// MessageText:
//
//  Call to SQLMoreResults failed with %1.
//

  PDH_SQL_MORE_RESULTS_FAILED      = DWORD($C0000BE5);
  {$EXTERNALSYM PDH_SQL_MORE_RESULTS_FAILED}

//
// MessageId: PDH_SQL_CONNECT_FAILED
//
// MessageText:
//
//  Call to SQLConnect failed with %1.
//

  PDH_SQL_CONNECT_FAILED           = DWORD($C0000BE6);
  {$EXTERNALSYM PDH_SQL_CONNECT_FAILED}

//
// MessageId: PDH_SQL_BIND_FAILED
//
// MessageText:
//
//  Call to SQLBindCol failed with %1.
//

  PDH_SQL_BIND_FAILED              = DWORD($C0000BE7);
  {$EXTERNALSYM PDH_SQL_BIND_FAILED}

//
// MessageId: PDH_CANNOT_CONNECT_WMI_SERVER
//
// MessageText:
//
//  Unable to connect to the WMI server on requested machine.
//

  PDH_CANNOT_CONNECT_WMI_SERVER    = DWORD($C0000BE8);
  {$EXTERNALSYM PDH_CANNOT_CONNECT_WMI_SERVER}

//
// MessageId: PDH_PLA_COLLECTION_ALREADY_RUNNING
//
// MessageText:
//
//  Collection "%1!s!" is already running.
//

  PDH_PLA_COLLECTION_ALREADY_RUNNING = DWORD($C0000BE9);
  {$EXTERNALSYM PDH_PLA_COLLECTION_ALREADY_RUNNING}

//
// MessageId: PDH_PLA_ERROR_SCHEDULE_OVERLAP
//
// MessageText:
//
//  The specified start time is after the end time.
//

  PDH_PLA_ERROR_SCHEDULE_OVERLAP   = DWORD($C0000BEA);
  {$EXTERNALSYM PDH_PLA_ERROR_SCHEDULE_OVERLAP}

//
// MessageId: PDH_PLA_COLLECTION_NOT_FOUND
//
// MessageText:
//
//  Collection "%1!s!" does not exist.
//

  PDH_PLA_COLLECTION_NOT_FOUND     = DWORD($C0000BEB);
  {$EXTERNALSYM PDH_PLA_COLLECTION_NOT_FOUND}

//
// MessageId: PDH_PLA_ERROR_SCHEDULE_ELAPSED
//
// MessageText:
//
//  The specified end time has already elapsed.
//

  PDH_PLA_ERROR_SCHEDULE_ELAPSED   = DWORD($C0000BEC);
  {$EXTERNALSYM PDH_PLA_ERROR_SCHEDULE_ELAPSED}

//
// MessageId: PDH_PLA_ERROR_NOSTART
//
// MessageText:
//
//  Collection "%1!s!" did not start, check the application event log for any errors.
//

  PDH_PLA_ERROR_NOSTART            = DWORD($C0000BED);
  {$EXTERNALSYM PDH_PLA_ERROR_NOSTART}

//
// MessageId: PDH_PLA_ERROR_ALREADY_EXISTS
//
// MessageText:
//
//  Collection "%1!s!" already exists.
//

  PDH_PLA_ERROR_ALREADY_EXISTS     = DWORD($C0000BEE);
  {$EXTERNALSYM PDH_PLA_ERROR_ALREADY_EXISTS}

//
// MessageId: PDH_PLA_ERROR_TYPE_MISMATCH
//
// MessageText:
//
//  There is a mismatch in the settings type.
//

  PDH_PLA_ERROR_TYPE_MISMATCH      = DWORD($C0000BEF);
  {$EXTERNALSYM PDH_PLA_ERROR_TYPE_MISMATCH}

//
// MessageId: PDH_PLA_ERROR_FILEPATH
//
// MessageText:
//
//  The information specified does not resolve to a valid path name.
//

  PDH_PLA_ERROR_FILEPATH           = DWORD($C0000BF0);
  {$EXTERNALSYM PDH_PLA_ERROR_FILEPATH}

//
// MessageId: PDH_PLA_SERVICE_ERROR
//
// MessageText:
//
//  The "Performance Logs & Alerts" service did not respond.
//

  PDH_PLA_SERVICE_ERROR            = DWORD($C0000BF1);
  {$EXTERNALSYM PDH_PLA_SERVICE_ERROR}

//
// MessageId: PDH_PLA_VALIDATION_ERROR
//
// MessageText:
//
//  The information passed is not valid.
//

  PDH_PLA_VALIDATION_ERROR         = DWORD($C0000BF2);
  {$EXTERNALSYM PDH_PLA_VALIDATION_ERROR}

//
// MessageId: PDH_PLA_VALIDATION_WARNING
//
// MessageText:
//
//  The information passed is not valid.
//

  PDH_PLA_VALIDATION_WARNING       = DWORD($80000BF3);
  {$EXTERNALSYM PDH_PLA_VALIDATION_WARNING}

//
// MessageId: PDH_PLA_ERROR_NAME_TOO_LONG
//
// MessageText:
//
//  The name supplied is too long.
//

  PDH_PLA_ERROR_NAME_TOO_LONG      = DWORD($C0000BF4);
  {$EXTERNALSYM PDH_PLA_ERROR_NAME_TOO_LONG}

//
// MessageId: PDH_INVALID_SQL_LOG_FORMAT
//
// MessageText:
//
//  SQL log format is incorrect. Correct format is "SQL:<DSN-name>!<LogSet-Name>".
//

  PDH_INVALID_SQL_LOG_FORMAT       = DWORD($C0000BF5);
  {$EXTERNALSYM PDH_INVALID_SQL_LOG_FORMAT}

//
// MessageId: PDH_COUNTER_ALREADY_IN_QUERY
//
// MessageText:
//
//  Performance counter in PdhAddCounter() call has already been added
//  in the performance query. This counter is ignored.
//

  PDH_COUNTER_ALREADY_IN_QUERY     = DWORD($C0000BF6);
  {$EXTERNALSYM PDH_COUNTER_ALREADY_IN_QUERY}

//
// MessageId: PDH_BINARY_LOG_CORRUPT
//
// MessageText:
//
//  Unable to read counter information and data from input binary log files.
//

  PDH_BINARY_LOG_CORRUPT           = DWORD($C0000BF7);
  {$EXTERNALSYM PDH_BINARY_LOG_CORRUPT}

//
// MessageId: PDH_LOG_SAMPLE_TOO_SMALL
//
// MessageText:
//
//  At least one of the input binary log files contain fewer than two data samples.
//

  PDH_LOG_SAMPLE_TOO_SMALL         = DWORD($C0000BF8);
  {$EXTERNALSYM PDH_LOG_SAMPLE_TOO_SMALL}

//
// MessageId: PDH_OS_LATER_VERSION
//
// MessageText:
//
//  The version of the operating system on the computer named %1 is later than that on the local computer. This operation is not available from the local computer.
//

  PDH_OS_LATER_VERSION             = DWORD($C0000BF9);
  {$EXTERNALSYM PDH_OS_LATER_VERSION}

//
// MessageId: PDH_OS_EARLIER_VERSION
//
// MessageText:
//
//  %1 supports %2 or later. Check the operating system version on the computer named %3.
//

  PDH_OS_EARLIER_VERSION           = DWORD($C0000BFA);
  {$EXTERNALSYM PDH_OS_EARLIER_VERSION}

//
// MessageId: PDH_INCORRECT_APPEND_TIME
//
// MessageText:
//
//  The output file must contain earlier data than the file to be appended.
//

  PDH_INCORRECT_APPEND_TIME        = DWORD($C0000BFB);
  {$EXTERNALSYM PDH_INCORRECT_APPEND_TIME}

//
// MessageId: PDH_UNMATCHED_APPEND_COUNTER
//
// MessageText:
//
//  Both files must have identical counters in order to append.
//

  PDH_UNMATCHED_APPEND_COUNTER     = DWORD($C0000BFC);
  {$EXTERNALSYM PDH_UNMATCHED_APPEND_COUNTER}

//
// MessageId: PDH_SQL_ALTER_DETAIL_FAILED
//
// MessageText:
//
//  Cannot alter CounterDetail table layout in SQL database.
//

  PDH_SQL_ALTER_DETAIL_FAILED      = DWORD($C0000BFD);
  {$EXTERNALSYM PDH_SQL_ALTER_DETAIL_FAILED}

//
// MessageId: PDH_QUERY_PERF_DATA_TIMEOUT
//
// MessageText:
//
//  System is busy. Timeout when collecting counter data. Please retry later or increase "CollectTime" registry value.
//

  PDH_QUERY_PERF_DATA_TIMEOUT      = DWORD($C0000BFE);
  {$EXTERNALSYM PDH_QUERY_PERF_DATA_TIMEOUT}

implementation

end.
