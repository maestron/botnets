{******************************************************************************}
{                                                       	               }
{ Common dialog error return codes API interface Unit for Object Pascal        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: cderr.h, released June 2000. The original Pascal       }
{ code is: CdErr.pas, released December 2000. The initial developer of the     }
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

unit JwaCdErr;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "cderr.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

const
  CDERR_DIALOGFAILURE = $FFFF;
  {$EXTERNALSYM CDERR_DIALOGFAILURE}

  CDERR_GENERALCODES    = $0000;
  {$EXTERNALSYM CDERR_GENERALCODES}
  CDERR_STRUCTSIZE      = $0001;
  {$EXTERNALSYM CDERR_STRUCTSIZE}
  CDERR_INITIALIZATION  = $0002;
  {$EXTERNALSYM CDERR_INITIALIZATION}
  CDERR_NOTEMPLATE      = $0003;
  {$EXTERNALSYM CDERR_NOTEMPLATE}
  CDERR_NOHINSTANCE     = $0004;
  {$EXTERNALSYM CDERR_NOHINSTANCE}
  CDERR_LOADSTRFAILURE  = $0005;
  {$EXTERNALSYM CDERR_LOADSTRFAILURE}
  CDERR_FINDRESFAILURE  = $0006;
  {$EXTERNALSYM CDERR_FINDRESFAILURE}
  CDERR_LOADRESFAILURE  = $0007;
  {$EXTERNALSYM CDERR_LOADRESFAILURE}
  CDERR_LOCKRESFAILURE  = $0008;
  {$EXTERNALSYM CDERR_LOCKRESFAILURE}
  CDERR_MEMALLOCFAILURE = $0009;
  {$EXTERNALSYM CDERR_MEMALLOCFAILURE}
  CDERR_MEMLOCKFAILURE  = $000A;
  {$EXTERNALSYM CDERR_MEMLOCKFAILURE}
  CDERR_NOHOOK          = $000B;
  {$EXTERNALSYM CDERR_NOHOOK}
  CDERR_REGISTERMSGFAIL = $000C;
  {$EXTERNALSYM CDERR_REGISTERMSGFAIL}

  PDERR_PRINTERCODES     = $1000;
  {$EXTERNALSYM PDERR_PRINTERCODES}
  PDERR_SETUPFAILURE     = $1001;
  {$EXTERNALSYM PDERR_SETUPFAILURE}
  PDERR_PARSEFAILURE     = $1002;
  {$EXTERNALSYM PDERR_PARSEFAILURE}
  PDERR_RETDEFFAILURE    = $1003;
  {$EXTERNALSYM PDERR_RETDEFFAILURE}
  PDERR_LOADDRVFAILURE   = $1004;
  {$EXTERNALSYM PDERR_LOADDRVFAILURE}
  PDERR_GETDEVMODEFAIL   = $1005;
  {$EXTERNALSYM PDERR_GETDEVMODEFAIL}
  PDERR_INITFAILURE      = $1006;
  {$EXTERNALSYM PDERR_INITFAILURE}
  PDERR_NODEVICES        = $1007;
  {$EXTERNALSYM PDERR_NODEVICES}
  PDERR_NODEFAULTPRN     = $1008;
  {$EXTERNALSYM PDERR_NODEFAULTPRN}
  PDERR_DNDMMISMATCH     = $1009;
  {$EXTERNALSYM PDERR_DNDMMISMATCH}
  PDERR_CREATEICFAILURE  = $100A;
  {$EXTERNALSYM PDERR_CREATEICFAILURE}
  PDERR_PRINTERNOTFOUND  = $100B;
  {$EXTERNALSYM PDERR_PRINTERNOTFOUND}
  PDERR_DEFAULTDIFFERENT = $100C;
  {$EXTERNALSYM PDERR_DEFAULTDIFFERENT}

  CFERR_CHOOSEFONTCODES = $2000;
  {$EXTERNALSYM CFERR_CHOOSEFONTCODES}
  CFERR_NOFONTS         = $2001;
  {$EXTERNALSYM CFERR_NOFONTS}
  CFERR_MAXLESSTHANMIN  = $2002;
  {$EXTERNALSYM CFERR_MAXLESSTHANMIN}

  FNERR_FILENAMECODES   = $3000;
  {$EXTERNALSYM FNERR_FILENAMECODES}
  FNERR_SUBCLASSFAILURE = $3001;
  {$EXTERNALSYM FNERR_SUBCLASSFAILURE}
  FNERR_INVALIDFILENAME = $3002;
  {$EXTERNALSYM FNERR_INVALIDFILENAME}
  FNERR_BUFFERTOOSMALL  = $3003;
  {$EXTERNALSYM FNERR_BUFFERTOOSMALL}

  FRERR_FINDREPLACECODES = $4000;
  {$EXTERNALSYM FRERR_FINDREPLACECODES}
  FRERR_BUFFERLENGTHZERO = $4001;
  {$EXTERNALSYM FRERR_BUFFERLENGTHZERO}

  CCERR_CHOOSECOLORCODES = $5000;
  {$EXTERNALSYM CCERR_CHOOSECOLORCODES}

implementation

end.
