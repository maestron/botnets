{******************************************************************************}
{                                                       	               }
{ Web Publishing CRS Error Codes API interface Unit for Object Pascal          }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wpcrsmsg.h, released June 2000. The original Pascal    }
{ code is: WPCrsMsg.pas, released December 2000. The initial developer of the  }
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

unit JwaWPCrsMsg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wpcrsmsg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;


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


//
// Define the severity codes
//


//
// MessageId: CRSWPP_ERROR_FIRST
//
// MessageText:
//
//  CRS WebPost provider's first error message.
//

const
  CRSWPP_ERROR_FIRST = DWORD($40042200);
  {$EXTERNALSYM CRSWPP_ERROR_FIRST}

//
// MessageId: CRSWPP_INVALID_POSTINFO_FILE
//
// MessageText:
//
//  The PostInfo file is invalid on the server you selected.
//

  CRSWPP_INVALID_POSTINFO_FILE = DWORD($C0042201);
  {$EXTERNALSYM CRSWPP_INVALID_POSTINFO_FILE}

//
// MessageId: CRSWPP_NO_MATCHING_MAPURL
//
// MessageText:
//
//  The CRS project you selected has no MAPURL.
//

  CRSWPP_NO_MATCHING_MAPURL = DWORD($C0042202);
  {$EXTERNALSYM CRSWPP_NO_MATCHING_MAPURL}

//
// MessageId: CRSWPP_SECURITY_PACKAGE
//
// MessageText:
//
//  The initialization of the security package failed.
//

  CRSWPP_SECURITY_PACKAGE = DWORD($C0042203);
  {$EXTERNALSYM CRSWPP_SECURITY_PACKAGE}

//
// MessageId: CRSWPP_SECURITY_PACKAGE_NOT_FOUND
//
// MessageText:
//
//  The security package(s) required by the server could not be found on your computer.
//

  CRSWPP_SECURITY_PACKAGE_NOT_FOUND = DWORD($C0042204);
  {$EXTERNALSYM CRSWPP_SECURITY_PACKAGE_NOT_FOUND}

//
// MessageId: CRSWPP_PROJECT_BINDING_INCOMPLETE
//
// MessageText:
//
//  The CRS provider has not determined which CRS project on the server corresponds to the URL you selected.
//

  CRSWPP_PROJECT_BINDING_INCOMPLETE = DWORD($C0042205);
  {$EXTERNALSYM CRSWPP_PROJECT_BINDING_INCOMPLETE}

//
// MessageId: CRSWPP_SERVER_BINDING_INCOMPLETE
//
// MessageText:
//
//  The CRS provider has not determined the name of the server that corresponds to the URL you selected.
//

  CRSWPP_SERVER_BINDING_INCOMPLETE = DWORD($C0042206);
  {$EXTERNALSYM CRSWPP_SERVER_BINDING_INCOMPLETE}

//
// MessageId: CRSWPP_SERVER_NOT_RESPONDING
//
// MessageText:
//
//  The CRS server is not responding.
//

  CRSWPP_SERVER_NOT_RESPONDING = DWORD($C0042207);
  {$EXTERNALSYM CRSWPP_SERVER_NOT_RESPONDING}

//
// MessageId: CRSWPP_FAILED_AUTH
//
// MessageText:
//
//  You do not have the necessary access privileges to publish to this CRS server.
//

  CRSWPP_FAILED_AUTH = DWORD($C0042208);
  {$EXTERNALSYM CRSWPP_FAILED_AUTH}

//
// MessageId: CRSWPP_POSTINFO_NEEDED
//
// MessageText:
//
//  The CRS provider could not retrieve all of the required information from the PostInfo file on the server.
//

  CRSWPP_POSTINFO_NEEDED = DWORD($40042209);
  {$EXTERNALSYM CRSWPP_POSTINFO_NEEDED}

//
// MessageId: CRSWPP_BIND_FAILED
//
// MessageText:
//
//  The CRS provider could not connect to the CRS server.
//

  CRSWPP_BIND_FAILED = DWORD($C004220A);
  {$EXTERNALSYM CRSWPP_BIND_FAILED}

implementation

end.
