{******************************************************************************}
{                                                       	               }
{ Winsock2 Service Policy API interface Unit for Object Pascal                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: qospol.h, released June 2000. The original Pascal      }
{ code is: QosPol.pas, released December 2000. The initial developer of the    }
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

unit JwaQosPol;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "qospol.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinSock2;

const
  PE_TYPE_APPID = 3;            // policy element contains Application Identity
  {$EXTERNALSYM PE_TYPE_APPID}

// Policy Location attribute carries sub application attributes

  PE_ATTRIB_TYPE_POLICY_LOCATOR = 1;
  {$EXTERNALSYM PE_ATTRIB_TYPE_POLICY_LOCATOR}

  POLICY_LOCATOR_SUB_TYPE_ASCII_DN       = 1;
  {$EXTERNALSYM POLICY_LOCATOR_SUB_TYPE_ASCII_DN}
  POLICY_LOCATOR_SUB_TYPE_UNICODE_DN     = 2;
  {$EXTERNALSYM POLICY_LOCATOR_SUB_TYPE_UNICODE_DN}
  POLICY_LOCATOR_SUB_TYPE_ASCII_DN_ENC   = 3;
  {$EXTERNALSYM POLICY_LOCATOR_SUB_TYPE_ASCII_DN_ENC}
  POLICY_LOCATOR_SUB_TYPE_UNICODE_DN_ENC = 4;
  {$EXTERNALSYM POLICY_LOCATOR_SUB_TYPE_UNICODE_DN_ENC}

// Credentials attribute carries the application identity

  PE_ATTRIB_TYPE_CREDENTIAL        = 2;
  {$EXTERNALSYM PE_ATTRIB_TYPE_CREDENTIAL}

  CREDENTIAL_SUB_TYPE_ASCII_ID     = 1;
  {$EXTERNALSYM CREDENTIAL_SUB_TYPE_ASCII_ID}
  CREDENTIAL_SUB_TYPE_UNICODE_ID   = 2;
  {$EXTERNALSYM CREDENTIAL_SUB_TYPE_UNICODE_ID}
  CREDENTIAL_SUB_TYPE_KERBEROS_TKT = 3;
  {$EXTERNALSYM CREDENTIAL_SUB_TYPE_KERBEROS_TKT}
  CREDENTIAL_SUB_TYPE_X509_V3_CERT = 4;
  {$EXTERNALSYM CREDENTIAL_SUB_TYPE_X509_V3_CERT}
  CREDENTIAL_SUB_TYPE_PGP_CERT     = 5;
  {$EXTERNALSYM CREDENTIAL_SUB_TYPE_PGP_CERT} 

// Identity Policy Element attribute structure

type
  _IDPE_ATTR = record
    PeAttribLength: USHORT;
    PeAttribType: UCHAR;            // Use the #defines from above
    PeAttribSubType: UCHAR;         // Use the #defines from above
    PeAttribValue: array [0..3] of UCHAR;
  end;
  {$EXTERNALSYM _IDPE_ATTR}
  IDPE_ATTR = _IDPE_ATTR;
  {$EXTERNALSYM IDPE_ATTR}
  LPIDPE_ATTR = ^IDPE_ATTR;
  {$EXTERNALSYM LPIDPE_ATTR}
  TIDPEAttr = IDPE_ATTR;
  PIDPEAttr = LPIDPE_ATTR;

const
  IDPE_ATTR_HDR_LEN = SizeOf(USHORT) + SizeOf(UCHAR) + SizeOf(UCHAR);
  {$EXTERNALSYM IDPE_ATTR_HDR_LEN}

function RSVP_BYTE_MULTIPLE(X: Integer): Integer;
{$EXTERNALSYM RSVP_BYTE_MULTIPLE}

implementation

function RSVP_BYTE_MULTIPLE(X: Integer): Integer;
begin
  Result := Round(((X + 3) / 4) * 4);
end;

end.
