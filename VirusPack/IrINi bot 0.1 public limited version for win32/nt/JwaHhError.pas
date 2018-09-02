{******************************************************************************}
{                                                       	               }
{ HTML Help Error API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: hherror.h, released Dec 2002. The original Pascal      }
{ code is: HhError.pas, released Dec 2002. The initial developer of the        }
{ Pascal code is Marcel van Brakel (brakelm@chello.nl).                        }
{                                                                              }
{ Portions created by Marcel van Brakel are Copyright (C) 1999-2001            }
{ Marcel van Brakel. All Rights Reserved.                                      }
{ 								               }
{ Contributor(s): Robert Chandler  (robert@helpware.net)                       }
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

unit JwaHhError;

interface

{$WEAKPACKAGEUNIT}

{$I WINDEFINES.INC}

uses
  JwaWinType;

// Published: http://support.microsoft.com/default.aspx?scid=kb;en-us;297768

type
  // HH_LAST_ERROR Command Related structures and constants
  // Used by command HH_GET_LAST_ERROR
  // You must call SysFreeString(xx.description) to free BSTR

  tagHH_LAST_ERROR = packed record
    cbStruct: Integer;      // sizeof this structure
    hr: HRESULT;            // Specifies the last error code.
    description: PWideChar; // (BSTR) Specifies a Unicode string containing a description of the error.
  end;
  HH_LAST_ERROR = tagHH_LAST_ERROR;
  THHLastError = tagHH_LAST_ERROR;


// Error codes

const
  HH_E_FILENOTFOUND: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0201; // %1 could not be found.
  HH_E_TOPICDOESNOTEXIST: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0202; // The requested topic does not exist.
  HH_E_INVALIDHELPFILE: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0203; // %1 is not a valid help file.
  HH_E_NOCONTEXTIDS: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $020A; // Help file does not contain context ids.
  HH_E_CONTEXTIDDOESNTEXIT: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $020B; // The context id does not exist.

  // 0x0300 - 0x03FF reserved for keywords

  HH_E_KEYWORD_NOT_FOUND: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0300; // no hits found.
  HH_E_KEYWORD_IS_PLACEHOLDER: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0301; // keyword is a placeholder or a "runaway" see also.
  HH_E_KEYWORD_NOT_IN_SUBSET: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0302; // no hits found because of subset exclusion.
  HH_E_KEYWORD_NOT_IN_INFOTYPE: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0303; // no hits found because of infotype exclusion.
  HH_E_KEYWORD_EXCLUDED: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0304; // no hits found because of infotype and subset exclusion.
  HH_E_KEYWORD_NOT_SUPPORTED: HRESULT = (SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $0305; // no hits found because of keywords not being supported in this mode.

implementation

end.
