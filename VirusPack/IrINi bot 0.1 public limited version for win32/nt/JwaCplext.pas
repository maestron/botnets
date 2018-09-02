{******************************************************************************}
{                                                       	               }
{ Control Panel Applet Extensions interface Unit for Object Pascal             }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: cplext.h, released June 2000. The original Pascal      }
{ code is: CplExt.pas, released December 2000. The initial developer of the    }
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

unit JwaCplext;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "Cplext.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

///////////////////////////////////////////////////////////////////////////////
//  Below are constants for pages which can be replaced in the standard control
// panel applets.  To extend an applet, you must define an object which
// supports the IShellPropSheetExt interface and register it's in-process
// server in a subkey under the applet's registry key.  Registry paths for the
// applets are defined in the header file REGSTR.H
//  Generally, when an IShellPropSheetExt is loaded, it's AddPages method
// will be called once, while it's ReplacePage method may be called zero or
// more times.  ReplacePage is only called in context.
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Mouse Control Panel Extensions
// The following constants MAY be passed in IShellPropSheetExt::ReplacePage's
// uPageID parameter for servers registered under
//                                  ( REGSTR_PATH_CONTROLSFOLDER "\\Mouse" )
//-----------------------------------------------------------------------------

const
  CPLPAGE_MOUSE_BUTTONS      = 1;
  {$EXTERNALSYM CPLPAGE_MOUSE_BUTTONS}
  CPLPAGE_MOUSE_PTRMOTION    = 2;
  {$EXTERNALSYM CPLPAGE_MOUSE_PTRMOTION}
  CPLPAGE_MOUSE_WHEEL        = 3;
  {$EXTERNALSYM CPLPAGE_MOUSE_WHEEL}

//-----------------------------------------------------------------------------
// Keyboard Control Panel Extensions
// The following constants MAY be passed in IShellPropSheetExt::ReplacePage's
// uPageID parameter for servers registered under
//                                  ( REGSTR_PATH_CONTROLSFOLDER "\\Keyboard" )
//-----------------------------------------------------------------------------

  CPLPAGE_KEYBOARD_SPEED     = 1;
  {$EXTERNALSYM CPLPAGE_KEYBOARD_SPEED}

//-----------------------------------------------------------------------------
// Display Control Panel Extensions
// The following constants MAY be passed in IShellPropSheetExt::ReplacePage's
// uPageID parameter for servers registered under
//                                  ( REGSTR_PATH_CONTROLSFOLDER "\\Display" )
//-----------------------------------------------------------------------------

  CPLPAGE_DISPLAY_BACKGROUND = 1;
  {$EXTERNALSYM CPLPAGE_DISPLAY_BACKGROUND}

///////////////////////////////////////////////////////////////////////////////

implementation

end.
