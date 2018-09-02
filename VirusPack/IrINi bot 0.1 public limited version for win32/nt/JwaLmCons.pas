{******************************************************************************}
{                                                       	               }
{ Lan Manager Constants API interface Unit for Object Pascal                   }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmcons.h, released November 2001. The original Pascal  }
{ code is: LmCons.pas, released Februari 2002. The initial developer of the    }
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

unit JwaLmCons;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lm.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaLmErr;

const
  NetApi32 = 'netapi32.dll';

//
// NOTE:  Lengths of strings are given as the maximum lengths of the
// string in characters (not bytes).  This does not include space for the
// terminating 0-characters.  When allocating space for such an item,
// use the form:
//
//     TCHAR username[UNLEN+1];
//
// Definitions of the form LN20_* define those values in effect for
// LanMan 2.0.
//

//
// String Lengths for various LanMan names
//

const
  CNLEN      = 15; // Computer name length
  {$EXTERNALSYM CNLEN}
  LM20_CNLEN = 15; // LM 2.0 Computer name length
  {$EXTERNALSYM LM20_CNLEN}
  DNLEN      = CNLEN; // Maximum domain name length
  {$EXTERNALSYM DNLEN}
  LM20_DNLEN = LM20_CNLEN; // LM 2.0 Maximum domain name length
  {$EXTERNALSYM LM20_DNLEN}

//#if (CNLEN != DNLEN)
//#error CNLEN and DNLEN are not equal
//#endif

  UNCLEN      = (CNLEN+2); // UNC computer name length
  {$EXTERNALSYM UNCLEN}
  LM20_UNCLEN = (LM20_CNLEN+2); // LM 2.0 UNC computer name length
  {$EXTERNALSYM LM20_UNCLEN}

  NNLEN      = 80; // Net name length (share name)
  {$EXTERNALSYM NNLEN}
  LM20_NNLEN = 12; // LM 2.0 Net name length
  {$EXTERNALSYM LM20_NNLEN}

  RMLEN      = (UNCLEN+1+NNLEN); // Max remote name length
  {$EXTERNALSYM RMLEN}
  LM20_RMLEN = (LM20_UNCLEN+1+LM20_NNLEN); // LM 2.0 Max remote name length
  {$EXTERNALSYM LM20_RMLEN}

  SNLEN        = 80; // Service name length
  {$EXTERNALSYM SNLEN}
  LM20_SNLEN   = 15; // LM 2.0 Service name length
  {$EXTERNALSYM LM20_SNLEN}
  STXTLEN      = 256; // Service text length
  {$EXTERNALSYM STXTLEN}
  LM20_STXTLEN = 63; // LM 2.0 Service text length
  {$EXTERNALSYM LM20_STXTLEN}

  PATHLEN      = 256; // Max. path (not including drive name)
  {$EXTERNALSYM PATHLEN}
  LM20_PATHLEN = 256; // LM 2.0 Max. path
  {$EXTERNALSYM LM20_PATHLEN}

  DEVLEN      = 80; // Device name length
  {$EXTERNALSYM DEVLEN}
  LM20_DEVLEN = 8; // LM 2.0 Device name length
  {$EXTERNALSYM LM20_DEVLEN}

  EVLEN = 16; // Event name length
  {$EXTERNALSYM EVLEN}

//
// User, Group and Password lengths
//

  UNLEN      = 256; // Maximum user name length
  {$EXTERNALSYM UNLEN}
  LM20_UNLEN = 20; // LM 2.0 Maximum user name length
  {$EXTERNALSYM LM20_UNLEN}

  GNLEN      = UNLEN; // Group name
  {$EXTERNALSYM GNLEN}
  LM20_GNLEN = LM20_UNLEN; // LM 2.0 Group name
  {$EXTERNALSYM LM20_GNLEN}

  PWLEN      = 256; // Maximum password length
  {$EXTERNALSYM PWLEN}
  LM20_PWLEN = 14; // LM 2.0 Maximum password length
  {$EXTERNALSYM LM20_PWLEN}

  SHPWLEN = 8; // Share password length (bytes)
  {$EXTERNALSYM SHPWLEN}

  CLTYPE_LEN = 12; // Length of client type string
  {$EXTERNALSYM CLTYPE_LEN}

  MAXCOMMENTSZ      = 256; // Multipurpose comment length
  {$EXTERNALSYM MAXCOMMENTSZ}
  LM20_MAXCOMMENTSZ = 48; // LM 2.0 Multipurpose comment length
  {$EXTERNALSYM LM20_MAXCOMMENTSZ}

  QNLEN      = NNLEN; // Queue name maximum length
  {$EXTERNALSYM QNLEN}
  LM20_QNLEN = LM20_NNLEN; // LM 2.0 Queue name maximum length
  {$EXTERNALSYM LM20_QNLEN}

//#if (QNLEN != NNLEN)
//# error QNLEN and NNLEN are not equal
//#endif

//
// The ALERTSZ and MAXDEVENTRIES defines have not yet been NT'ized.
// Whoever ports these components should change these values appropriately.
//

  ALERTSZ       = 128; // size of alert string in server
  {$EXTERNALSYM ALERTSZ}
  MAXDEVENTRIES = (SizeOf(Integer)*8); // Max number of device entries
  {$EXTERNALSYM MAXDEVENTRIES}

                                        //
                                        // We use int bitmap to represent
                                        //

  NETBIOS_NAME_LEN = 16; // NetBIOS net name (bytes)
  {$EXTERNALSYM NETBIOS_NAME_LEN}

//
// Value to be used with APIs which have a "preferred maximum length"
// parameter.  This value indicates that the API should just allocate
// "as much as it takes."
//

  MAX_PREFERRED_LENGTH = DWORD(-1);
  {$EXTERNALSYM MAX_PREFERRED_LENGTH}

//
//        Constants used with encryption
//

  CRYPT_KEY_LEN      = 7;
  {$EXTERNALSYM CRYPT_KEY_LEN}
  CRYPT_TXT_LEN      = 8;
  {$EXTERNALSYM CRYPT_TXT_LEN}
  ENCRYPTED_PWLEN    = 16;
  {$EXTERNALSYM ENCRYPTED_PWLEN}
  SESSION_PWLEN      = 24;
  {$EXTERNALSYM SESSION_PWLEN}
  SESSION_CRYPT_KLEN = 21;
  {$EXTERNALSYM SESSION_CRYPT_KLEN}

//
//  Value to be used with SetInfo calls to allow setting of all
//  settable parameters (parmnum zero option)
//

  PARMNUM_ALL = 0;
  {$EXTERNALSYM PARMNUM_ALL}

  PARM_ERROR_UNKNOWN     = DWORD(-1);
  {$EXTERNALSYM PARM_ERROR_UNKNOWN}
  PARM_ERROR_NONE        = 0;
  {$EXTERNALSYM PARM_ERROR_NONE}
  PARMNUM_BASE_INFOLEVEL = 1000;
  {$EXTERNALSYM PARMNUM_BASE_INFOLEVEL}

//
// Only the UNICODE version of the LM APIs are available on NT.
// Non-UNICODE version on other platforms
//

//#if defined( _WIN32_WINNT ) || defined( WINNT ) || defined( FORCE_UNICODE )

{$IFDEF _WIN32_WINNT}
{$DEFINE LM_USE_UNICODE}
{$ENDIF}

{$IFDEF WINNT}
{$DEFINE LM_USE_UNICODE}
{$ENDIF}

{$IFDEF FORCE_UNICODE}
{$DEFINE LM_USE_UNICODE}
{$ENDIF}

{$IFDEF LM_USE_UNICODE}

type
  LMSTR = LPWSTR;
  {$EXTERNALSYM LMSTR}
  LMCSTR = LPCWSTR;
  {$EXTERNALSYM LMCSTR}
  PLMSTR = ^LMSTR;
  {$NODEFINE PLMSTR}

{$ELSE}

type
  LMSTR = LPSTR;
  {$EXTERNALSYM LMSTR}
  LMCSTR = LPCSTR;
  {$EXTERNALSYM LMCSTR}

{$ENDIF}

{$UNDEF LM_USE_UNICODE}

//
//        Message File Names
//

const
  MESSAGE_FILENAME  = TEXT('NETMSG');
  {$EXTERNALSYM MESSAGE_FILENAME}
  OS2MSG_FILENAME   = TEXT('BASE');
  {$EXTERNALSYM OS2MSG_FILENAME}
  HELP_MSG_FILENAME = TEXT('NETH');
  {$EXTERNALSYM HELP_MSG_FILENAME}

// ** INTERNAL_ONLY **

// The backup message file named here is a duplicate of net.msg. It
// is not shipped with the product, but is used at buildtime to
// msgbind certain messages to netapi.dll and some of the services.
// This allows for OEMs to modify the message text in net.msg and
// have those changes show up.        Only in case there is an error in
// retrieving the messages from net.msg do we then get the bound
// messages out of bak.msg (really out of the message segment).

  BACKUP_MSG_FILENAME = TEXT('BAK.MSG');
  {$EXTERNALSYM BACKUP_MSG_FILENAME}

// ** END_INTERNAL **

//
// Keywords used in Function Prototypes
//

type
  NET_API_STATUS = DWORD;
  {$EXTERNALSYM NET_API_STATUS}
  TNetApiStatus = NET_API_STATUS;

//
// The platform ID indicates the levels to use for platform-specific
// information.
//

const
  PLATFORM_ID_DOS = 300;
  {$EXTERNALSYM PLATFORM_ID_DOS}
  PLATFORM_ID_OS2 = 400;
  {$EXTERNALSYM PLATFORM_ID_OS2}
  PLATFORM_ID_NT  = 500;
  {$EXTERNALSYM PLATFORM_ID_NT}
  PLATFORM_ID_OSF = 600;
  {$EXTERNALSYM PLATFORM_ID_OSF}
  PLATFORM_ID_VMS = 700;
  {$EXTERNALSYM PLATFORM_ID_VMS}

//
//      There message numbers assigned to different LANMAN components
//      are as defined below.
//
//      lmerr.h:        2100 - 2999     NERR_BASE
//      alertmsg.h:     3000 - 3049     ALERT_BASE
//      lmsvc.h:        3050 - 3099     SERVICE_BASE
//      lmerrlog.h:     3100 - 3299     ERRLOG_BASE
//      msgtext.h:      3300 - 3499     MTXT_BASE
//      apperr.h:       3500 - 3999     APPERR_BASE
//      apperrfs.h:     4000 - 4299     APPERRFS_BASE
//      apperr2.h:      4300 - 5299     APPERR2_BASE
//      ncberr.h:       5300 - 5499     NRCERR_BASE
//      alertmsg.h:     5500 - 5599     ALERT2_BASE
//      lmsvc.h:        5600 - 5699     SERVICE2_BASE
//      lmerrlog.h      5700 - 5899     ERRLOG2_BASE
//

  MIN_LANMAN_MESSAGE_ID = NERR_BASE;
  {$EXTERNALSYM MIN_LANMAN_MESSAGE_ID}
  MAX_LANMAN_MESSAGE_ID = 5899;
  {$EXTERNALSYM MAX_LANMAN_MESSAGE_ID}

implementation

end.
