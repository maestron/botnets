{******************************************************************************}
{                                                       	               }
{ Image Mastering API interface Unit for Object Pascal                         }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: imapierror.h, released Aug 2002. The original Pascal   }
{ code is: ImapiError.pas, released November 2002. The initial developer of the}
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

unit JwaImapiError;

interface

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "imapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

uses
  JwaWinError, JwaWinType;

const
  IMAPI_S_PROPERTIESIGNORED     = HRESULT((SEVERITY_SUCCESS shl 31) or (FACILITY_ITF shl 16) or $200);
  {$EXTERNALSYM IMAPI_S_PROPERTIESIGNORED}
  IMAPI_S_BUFFER_TO_SMALL       = HRESULT((SEVERITY_SUCCESS shl 31) or (FACILITY_ITF shl 16) or $201);
  {$EXTERNALSYM IMAPI_S_BUFFER_TO_SMALL}
  IMAPI_E_NOTOPENED             = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 11);
  {$EXTERNALSYM IMAPI_E_NOTOPENED}
  IMAPI_E_NOTINITIALIZED        = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 12);
  {$EXTERNALSYM IMAPI_E_NOTINITIALIZED}
  IMAPI_E_USERABORT             = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 13);
  {$EXTERNALSYM IMAPI_E_USERABORT}
  IMAPI_E_GENERIC               = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 14);
  {$EXTERNALSYM IMAPI_E_GENERIC}
  IMAPI_E_MEDIUM_NOTPRESENT     = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 15);
  {$EXTERNALSYM IMAPI_E_MEDIUM_NOTPRESENT}
  IMAPI_E_MEDIUM_INVALIDTYPE    = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 16);
  {$EXTERNALSYM IMAPI_E_MEDIUM_INVALIDTYPE}
  IMAPI_E_DEVICE_NOPROPERTIES   = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 17);
  {$EXTERNALSYM IMAPI_E_DEVICE_NOPROPERTIES}
  IMAPI_E_DEVICE_NOTACCESSIBLE  = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 18);
  {$EXTERNALSYM IMAPI_E_DEVICE_NOTACCESSIBLE}
  IMAPI_E_DEVICE_NOTPRESENT     = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 19);
  {$EXTERNALSYM IMAPI_E_DEVICE_NOTPRESENT}
  IMAPI_E_DEVICE_INVALIDTYPE    = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 20);
  {$EXTERNALSYM IMAPI_E_DEVICE_INVALIDTYPE}
  IMAPI_E_INITIALIZE_WRITE      = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 21);
  {$EXTERNALSYM IMAPI_E_INITIALIZE_WRITE}
  IMAPI_E_INITIALIZE_ENDWRITE   = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 22);
  {$EXTERNALSYM IMAPI_E_INITIALIZE_ENDWRITE}
  IMAPI_E_FILESYSTEM            = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 23);
  {$EXTERNALSYM IMAPI_E_FILESYSTEM}
  IMAPI_E_FILEACCESS            = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 24);
  {$EXTERNALSYM IMAPI_E_FILEACCESS}
  IMAPI_E_DISCINFO              = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 25);
  {$EXTERNALSYM IMAPI_E_DISCINFO}
  IMAPI_E_TRACKNOTOPEN          = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 26);
  {$EXTERNALSYM IMAPI_E_TRACKNOTOPEN}
  IMAPI_E_TRACKOPEN             = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 27);
  {$EXTERNALSYM IMAPI_E_TRACKOPEN}
  IMAPI_E_DISCFULL              = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 28);
  {$EXTERNALSYM IMAPI_E_DISCFULL}
  IMAPI_E_BADJOLIETNAME         = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 29);
  {$EXTERNALSYM IMAPI_E_BADJOLIETNAME}
  IMAPI_E_INVALIDIMAGE          = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 30);
  {$EXTERNALSYM IMAPI_E_INVALIDIMAGE}
  IMAPI_E_NOACTIVEFORMAT        = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 31);
  {$EXTERNALSYM IMAPI_E_NOACTIVEFORMAT}
  IMAPI_E_NOACTIVERECORDER      = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 32);
  {$EXTERNALSYM IMAPI_E_NOACTIVERECORDER}
  IMAPI_E_WRONGFORMAT           = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 33);
  {$EXTERNALSYM IMAPI_E_WRONGFORMAT}
  IMAPI_E_ALREADYOPEN           = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 34);
  {$EXTERNALSYM IMAPI_E_ALREADYOPEN}
  IMAPI_E_WRONGDISC             = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 35);
  {$EXTERNALSYM IMAPI_E_WRONGDISC}
  IMAPI_E_FILEEXISTS            = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 36);
  {$EXTERNALSYM IMAPI_E_FILEEXISTS}
  IMAPI_E_STASHINUSE            = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 37);
  {$EXTERNALSYM IMAPI_E_STASHINUSE}
  IMAPI_E_DEVICE_STILL_IN_USE   = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 38);
  {$EXTERNALSYM IMAPI_E_DEVICE_STILL_IN_USE}
  IMAPI_E_LOSS_OF_STREAMING     = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 39);
  {$EXTERNALSYM IMAPI_E_LOSS_OF_STREAMING}
  IMAPI_E_COMPRESSEDSTASH       = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 40);
  {$EXTERNALSYM IMAPI_E_COMPRESSEDSTASH}
  IMAPI_E_ENCRYPTEDSTASH        = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 41);
  {$EXTERNALSYM IMAPI_E_ENCRYPTEDSTASH}
  IMAPI_E_NOTENOUGHDISKFORSTASH = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 42);
  {$EXTERNALSYM IMAPI_E_NOTENOUGHDISKFORSTASH}
  IMAPI_E_REMOVABLESTASH        = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 43);
  {$EXTERNALSYM IMAPI_E_REMOVABLESTASH}
  IMAPI_E_CANNOT_WRITE_TO_MEDIA = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 44);
  {$EXTERNALSYM IMAPI_E_CANNOT_WRITE_TO_MEDIA}
  IMAPI_E_TRACK_NOT_BIG_ENOUGH  = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 45);
  {$EXTERNALSYM IMAPI_E_TRACK_NOT_BIG_ENOUGH}
  IMAPI_E_BOOTIMAGE_AND_NONBLANK_DISC = HRESULT((SEVERITY_ERROR shl 31) or (FACILITY_ITF shl 16) or $200 + 46);
  {$EXTERNALSYM IMAPI_E_BOOTIMAGE_AND_NONBLANK_DISC}

implementation

end.
