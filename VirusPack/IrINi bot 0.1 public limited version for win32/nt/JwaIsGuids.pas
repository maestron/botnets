{******************************************************************************}
{                                                       	               }
{ Internet Shortcut GUID definitions API interface Unit for Object Pascal      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: isguids.h, released November 2002. The original Pascal }
{ code is: JwaIsGuids.pas, released April 2002. The initial developer of the   }
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

unit JwaIsGuids;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "isguids.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//
// isguids.h - Internet Shortcut GUID definitions.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
// 

const
  CLSID_InternetShortcut: TGUID = (D1:$FBF23B40; D2:$E3F0; D3:$101B; D4:($84, $88, $00, $AA, $00, $3E, $56, $F8));
  {$EXTERNALSYM CLSID_InternetShortcut}

  IID_IUniformResourceLocatorA: TGUID = (D1:$FBF23B80; D2:$E3F0; D3:$101B; D4:($84, $88, $00, $AA, $00, $3E, $56, $F8));
  {$EXTERNALSYM IID_IUniformResourceLocatorA}
  IID_IUniformResourceLocatorW: TGUID = (D1:$CABB0DA0; D2:$DA57; D3:$11CF; D4:($99, $74, $00, $20, $AF, $D7, $97, $62));
  {$EXTERNALSYM IID_IUniformResourceLocatorW}

{$IFDEF UNICODE}
  IID_IUniformResourceLocator: TGUID = (D1:$CABB0DA0; D2:$DA57; D3:$11CF; D4:($99, $74, $00, $20, $AF, $D7, $97, $62));
  {$EXTERNALSYM IID_IUniformResourceLocator}
{$ELSE}
  IID_IUniformResourceLocator: TGUID = (D1:$FBF23B80; D2:$E3F0; D3:$101B; D4:($84, $88, $00, $AA, $00, $3E, $56, $F8));
  {$EXTERNALSYM IID_IUniformResourceLocator}
{$ENDIF}

implementation

end.
