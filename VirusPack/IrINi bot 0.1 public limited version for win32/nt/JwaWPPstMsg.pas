{******************************************************************************}
{                                                       	               }
{ Web Publishing Post Error Codes API interface Unit for Object Pascal         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: wppstmsg.h, released June 2000. The original Pascal    }
{ code is: WPPstMsg.pas, released December 2000. The initial developer of the  }
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

unit JwaWPPstMsg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "wppstmsg.h"'}
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
// MessageId: WPP_ERROR_FIRST
//
// MessageText:
//
//  WebPost Provider first error message.
//

const
  WPP_ERROR_FIRST = DWORD($40042380);
  {$EXTERNALSYM WPP_ERROR_FIRST}

//
// MessageId: WPP_POST_POSTING_URL_ERROR
//
// MessageText:
//
//  The URL you selected, %1, is invalid.
//

  WPP_POST_POSTING_URL_ERROR = DWORD($C0042381);
  {$EXTERNALSYM WPP_POST_POSTING_URL_ERROR}

//
// MessageId: WPP_POST_POSTING_SERVER_ERROR
//
// MessageText:
//
//  The Web server returned the following error: %1.
//

  WPP_POST_POSTING_SERVER_ERROR = DWORD($C0042382);
  {$EXTERNALSYM WPP_POST_POSTING_SERVER_ERROR}

//
// MessageId: WPP_POST_POSTING_NO_RESPONSE_ERROR
//
// MessageText:
//
//  The Web server either is not responding or returned an unrecognized response.
//

  WPP_POST_POSTING_NO_RESPONSE_ERROR = DWORD($C0042383);
  {$EXTERNALSYM WPP_POST_POSTING_NO_RESPONSE_ERROR}

//
// MessageId: WPP_ERROR_LAST
//
// MessageText:
//
//  WebPost Provider last error message.
//

  WPP_ERROR_LAST = DWORD($400423FF);
  {$EXTERNALSYM WPP_ERROR_LAST}

implementation

end.
