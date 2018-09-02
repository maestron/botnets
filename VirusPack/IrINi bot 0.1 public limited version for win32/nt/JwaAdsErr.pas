{******************************************************************************}
{                                                       	               }
{ Active Directory Error Codes API interface Unit for Object Pascal            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: adserr.h, released June 2000. The original Pascal      }
{ code is: AdsErr.pas, released December 2000. The initial developer of the    }
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

unit JwaAdsErr;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "adserr.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

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
//  An invalid directory pathname was passed
//
  E_ADS_BAD_PATHNAME = HRESULT($80005000);
  {$EXTERNALSYM E_ADS_BAD_PATHNAME}

//
// MessageId: E_ADS_INVALID_DOMAIN_OBJECT
//
// MessageText:
//
//  An unknown directory domain object was requested
//
  E_ADS_INVALID_DOMAIN_OBJECT = HRESULT($80005001);
  {$EXTERNALSYM E_ADS_INVALID_DOMAIN_OBJECT}

//
// MessageId: E_ADS_INVALID_USER_OBJECT
//
// MessageText:
//
//  An unknown directory user object was requested
//
  E_ADS_INVALID_USER_OBJECT = HRESULT($80005002);
  {$EXTERNALSYM E_ADS_INVALID_USER_OBJECT}

//
// MessageId: E_ADS_INVALID_COMPUTER_OBJECT
//
// MessageText:
//
//  An unknown directory computer object was requested
//
  E_ADS_INVALID_COMPUTER_OBJECT = HRESULT($80005003);
  {$EXTERNALSYM E_ADS_INVALID_COMPUTER_OBJECT}

//
// MessageId: E_ADS_UNKNOWN_OBJECT
//
// MessageText:
//
//  An unknown directory object was requested
//
  E_ADS_UNKNOWN_OBJECT = HRESULT($80005004);
  {$EXTERNALSYM E_ADS_UNKNOWN_OBJECT}

//
// MessageId: E_ADS_PROPERTY_NOT_SET
//
// MessageText:
//
//  The specified directory property was not set
//
  E_ADS_PROPERTY_NOT_SET = HRESULT($80005005);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_SET}

//
// MessageId: E_ADS_PROPERTY_NOT_SUPPORTED
//
// MessageText:
//
//  The specified directory property is not supported
//
  E_ADS_PROPERTY_NOT_SUPPORTED = HRESULT($80005006);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_SUPPORTED}

//
// MessageId: E_ADS_PROPERTY_INVALID
//
// MessageText:
//
//  The specified directory property is invalid
//
  E_ADS_PROPERTY_INVALID = HRESULT($80005007);
  {$EXTERNALSYM E_ADS_PROPERTY_INVALID}

//
// MessageId: E_ADS_BAD_PARAMETER
//
// MessageText:
//
//  One or more input parameters are invalid
//
  E_ADS_BAD_PARAMETER = HRESULT($80005008);
  {$EXTERNALSYM E_ADS_BAD_PARAMETER}

//
// MessageId: E_ADS_OBJECT_UNBOUND
//
// MessageText:
//
//  The specified directory object is not bound to a remote resource
//
  E_ADS_OBJECT_UNBOUND = HRESULT($80005009);
  {$EXTERNALSYM E_ADS_OBJECT_UNBOUND}

//
// MessageId: E_ADS_PROPERTY_NOT_MODIFIED
//
// MessageText:
//
//  The specified directory object has not been modified
//
  E_ADS_PROPERTY_NOT_MODIFIED = HRESULT($8000500A);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_MODIFIED}

//
// MessageId: E_ADS_PROPERTY_MODIFIED
//
// MessageText:
//
//  The specified directory object has been modified
//
  E_ADS_PROPERTY_MODIFIED = HRESULT($8000500B);
  {$EXTERNALSYM E_ADS_PROPERTY_MODIFIED}

//
// MessageId: E_ADS_CANT_CONVERT_DATATYPE
//
// MessageText:
//
//  The directory datatype cannot be converted to/from a native DS datatype
//
  E_ADS_CANT_CONVERT_DATATYPE = HRESULT($8000500C);
  {$EXTERNALSYM E_ADS_CANT_CONVERT_DATATYPE}

//
// MessageId: E_ADS_PROPERTY_NOT_FOUND
//
// MessageText:
//
//  The directory property cannot be found in the cache.
//
  E_ADS_PROPERTY_NOT_FOUND = HRESULT($8000500D);
  {$EXTERNALSYM E_ADS_PROPERTY_NOT_FOUND}

//
// MessageId: E_ADS_OBJECT_EXISTS
//
// MessageText:
//
//  The directory object exists.
//
  E_ADS_OBJECT_EXISTS = HRESULT($8000500E);
  {$EXTERNALSYM E_ADS_OBJECT_EXISTS}

//
// MessageId: E_ADS_SCHEMA_VIOLATION
//
// MessageText:
//
//  The attempted action violates the DS schema rules.
//
  E_ADS_SCHEMA_VIOLATION = HRESULT($8000500F);
  {$EXTERNALSYM E_ADS_SCHEMA_VIOLATION}

//
// MessageId: E_ADS_COLUMN_NOT_SET
//
// MessageText:
//
//  The specified column in the directory was not set.
//
  E_ADS_COLUMN_NOT_SET = HRESULT($80005010);
  {$EXTERNALSYM E_ADS_COLUMN_NOT_SET}

//
// MessageId: S_ADS_ERRORSOCCURRED
//
// MessageText:
//
//  One or more errors occurred
//
  S_ADS_ERRORSOCCURRED = HRESULT($00005011);
  {$EXTERNALSYM S_ADS_ERRORSOCCURRED}

//
// MessageId: S_ADS_NOMORE_ROWS
//
// MessageText:
//
//  No more rows to be obatained by the search result.
//
  S_ADS_NOMORE_ROWS = HRESULT($00005012);
  {$EXTERNALSYM S_ADS_NOMORE_ROWS}

//
// MessageId: S_ADS_NOMORE_COLUMNS
//
// MessageText:
//
//  No more columns to be obatained for the current row.
//
  S_ADS_NOMORE_COLUMNS = HRESULT($00005013);
  {$EXTERNALSYM S_ADS_NOMORE_COLUMNS}

//
// MessageId: E_ADS_INVALID_FILTER
//
// MessageText:
//
//  The search filter specified is invalid
//
  E_ADS_INVALID_FILTER = HRESULT($80005014);
  {$EXTERNALSYM E_ADS_INVALID_FILTER}

implementation

end.
