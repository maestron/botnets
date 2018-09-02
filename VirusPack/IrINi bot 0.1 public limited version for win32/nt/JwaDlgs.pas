{******************************************************************************}
{                                                       	               }
{ UI dialog header information API interface unit for Object Pascal            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: dlgs.h, released June 2000. The original Pascal        }
{ code is: Dlgs.pas, released December 2000. The initial developer of the      }
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

unit JwaDlgs;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "dlgs.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//
//  Constant Declarations.
//

const
  ctlFirst = $0400;
  {$EXTERNALSYM ctlFirst}
  ctlLast  = $04ff;
  {$EXTERNALSYM ctlLast}

//
//  Push buttons.
//

  psh1    = $0400;
  {$EXTERNALSYM psh1}
  psh2    = $0401;
  {$EXTERNALSYM psh2}
  psh3    = $0402;
  {$EXTERNALSYM psh3}
  psh4    = $0403;
  {$EXTERNALSYM psh4}
  psh5    = $0404;
  {$EXTERNALSYM psh5}
  psh6    = $0405;
  {$EXTERNALSYM psh6}
  psh7    = $0406;
  {$EXTERNALSYM psh7}
  psh8    = $0407;
  {$EXTERNALSYM psh8}
  psh9    = $0408;
  {$EXTERNALSYM psh9}
  psh10   = $0409;
  {$EXTERNALSYM psh10}
  psh11   = $040a;
  {$EXTERNALSYM psh11}
  psh12   = $040b;
  {$EXTERNALSYM psh12}
  psh13   = $040c;
  {$EXTERNALSYM psh13}
  psh14   = $040d;
  {$EXTERNALSYM psh14}
  psh15   = $040e;
  {$EXTERNALSYM psh15}
  pshHelp = psh15;
  {$EXTERNALSYM pshHelp}
  psh16   = $040f;
  {$EXTERNALSYM psh16}

//
//  Checkboxes.
//

  chx1  = $0410;
  {$EXTERNALSYM chx1}
  chx2  = $0411;
  {$EXTERNALSYM chx2}
  chx3  = $0412;
  {$EXTERNALSYM chx3}
  chx4  = $0413;
  {$EXTERNALSYM chx4}
  chx5  = $0414;
  {$EXTERNALSYM chx5}
  chx6  = $0415;
  {$EXTERNALSYM chx6}
  chx7  = $0416;
  {$EXTERNALSYM chx7}
  chx8  = $0417;
  {$EXTERNALSYM chx8}
  chx9  = $0418;
  {$EXTERNALSYM chx9}
  chx10 = $0419;
  {$EXTERNALSYM chx10}
  chx11 = $041a;
  {$EXTERNALSYM chx11}
  chx12 = $041b;
  {$EXTERNALSYM chx12}
  chx13 = $041c;
  {$EXTERNALSYM chx13}
  chx14 = $041d;
  {$EXTERNALSYM chx14}
  chx15 = $041e;
  {$EXTERNALSYM chx15}
  chx16 = $041f;
  {$EXTERNALSYM chx16}

//
//  Radio buttons.
//

  rad1  = $0420;
  {$EXTERNALSYM rad1}
  rad2  = $0421;
  {$EXTERNALSYM rad2}
  rad3  = $0422;
  {$EXTERNALSYM rad3}
  rad4  = $0423;
  {$EXTERNALSYM rad4}
  rad5  = $0424;
  {$EXTERNALSYM rad5}
  rad6  = $0425;
  {$EXTERNALSYM rad6}
  rad7  = $0426;
  {$EXTERNALSYM rad7}
  rad8  = $0427;
  {$EXTERNALSYM rad8}
  rad9  = $0428;
  {$EXTERNALSYM rad9}
  rad10 = $0429;
  {$EXTERNALSYM rad10}
  rad11 = $042a;
  {$EXTERNALSYM rad11}
  rad12 = $042b;
  {$EXTERNALSYM rad12}
  rad13 = $042c;
  {$EXTERNALSYM rad13}
  rad14 = $042d;
  {$EXTERNALSYM rad14}
  rad15 = $042e;
  {$EXTERNALSYM rad15}
  rad16 = $042f;
  {$EXTERNALSYM rad16}

//
//  Groups, frames, rectangles, and icons.
//

  grp1 = $0430;
  {$EXTERNALSYM grp1}
  grp2 = $0431;
  {$EXTERNALSYM grp2}
  grp3 = $0432;
  {$EXTERNALSYM grp3}
  grp4 = $0433;
  {$EXTERNALSYM grp4}
  frm1 = $0434;
  {$EXTERNALSYM frm1}
  frm2 = $0435;
  {$EXTERNALSYM frm2}
  frm3 = $0436;
  {$EXTERNALSYM frm3}
  frm4 = $0437;
  {$EXTERNALSYM frm4}
  rct1 = $0438;
  {$EXTERNALSYM rct1}
  rct2 = $0439;
  {$EXTERNALSYM rct2}
  rct3 = $043a;
  {$EXTERNALSYM rct3}
  rct4 = $043b;
  {$EXTERNALSYM rct4}
  ico1 = $043c;
  {$EXTERNALSYM ico1}
  ico2 = $043d;
  {$EXTERNALSYM ico2}
  ico3 = $043e;
  {$EXTERNALSYM ico3}
  ico4 = $043f;
  {$EXTERNALSYM ico4}

//
//  Static text.
//

  stc1  = $0440;
  {$EXTERNALSYM stc1}
  stc2  = $0441;
  {$EXTERNALSYM stc2}
  stc3  = $0442;
  {$EXTERNALSYM stc3}
  stc4  = $0443;
  {$EXTERNALSYM stc4}
  stc5  = $0444;
  {$EXTERNALSYM stc5}
  stc6  = $0445;
  {$EXTERNALSYM stc6}
  stc7  = $0446;
  {$EXTERNALSYM stc7}
  stc8  = $0447;
  {$EXTERNALSYM stc8}
  stc9  = $0448;
  {$EXTERNALSYM stc9}
  stc10 = $0449;
  {$EXTERNALSYM stc10}
  stc11 = $044a;
  {$EXTERNALSYM stc11}
  stc12 = $044b;
  {$EXTERNALSYM stc12}
  stc13 = $044c;
  {$EXTERNALSYM stc13}
  stc14 = $044d;
  {$EXTERNALSYM stc14}
  stc15 = $044e;
  {$EXTERNALSYM stc15}
  stc16 = $044f;
  {$EXTERNALSYM stc16}
  stc17 = $0450;
  {$EXTERNALSYM stc17}
  stc18 = $0451;
  {$EXTERNALSYM stc18}
  stc19 = $0452;
  {$EXTERNALSYM stc19}
  stc20 = $0453;
  {$EXTERNALSYM stc20}
  stc21 = $0454;
  {$EXTERNALSYM stc21}
  stc22 = $0455;
  {$EXTERNALSYM stc22}
  stc23 = $0456;
  {$EXTERNALSYM stc23}
  stc24 = $0457;
  {$EXTERNALSYM stc24}
  stc25 = $0458;
  {$EXTERNALSYM stc25}
  stc26 = $0459;
  {$EXTERNALSYM stc26}
  stc27 = $045a;
  {$EXTERNALSYM stc27}
  stc28 = $045b;
  {$EXTERNALSYM stc28}
  stc29 = $045c;
  {$EXTERNALSYM stc29}
  stc30 = $045d;
  {$EXTERNALSYM stc30}
  stc31 = $045e;
  {$EXTERNALSYM stc31}
  stc32 = $045f;
  {$EXTERNALSYM stc32}

//
//  Listboxes.
//

  lst1  = $0460;
  {$EXTERNALSYM lst1}
  lst2  = $0461;
  {$EXTERNALSYM lst2}
  lst3  = $0462;
  {$EXTERNALSYM lst3}
  lst4  = $0463;
  {$EXTERNALSYM lst4}
  lst5  = $0464;
  {$EXTERNALSYM lst5}
  lst6  = $0465;
  {$EXTERNALSYM lst6}
  lst7  = $0466;
  {$EXTERNALSYM lst7}
  lst8  = $0467;
  {$EXTERNALSYM lst8}
  lst9  = $0468;
  {$EXTERNALSYM lst9}
  lst10 = $0469;
  {$EXTERNALSYM lst10}
  lst11 = $046a;
  {$EXTERNALSYM lst11}
  lst12 = $046b;
  {$EXTERNALSYM lst12}
  lst13 = $046c;
  {$EXTERNALSYM lst13}
  lst14 = $046d;
  {$EXTERNALSYM lst14}
  lst15 = $046e;
  {$EXTERNALSYM lst15}
  lst16 = $046f;
  {$EXTERNALSYM lst16}

//
//  Combo boxes.
//

  cmb1  = $0470;
  {$EXTERNALSYM cmb1}
  cmb2  = $0471;
  {$EXTERNALSYM cmb2}
  cmb3  = $0472;
  {$EXTERNALSYM cmb3}
  cmb4  = $0473;
  {$EXTERNALSYM cmb4}
  cmb5  = $0474;
  {$EXTERNALSYM cmb5}
  cmb6  = $0475;
  {$EXTERNALSYM cmb6}
  cmb7  = $0476;
  {$EXTERNALSYM cmb7}
  cmb8  = $0477;
  {$EXTERNALSYM cmb8}
  cmb9  = $0478;
  {$EXTERNALSYM cmb9}
  cmb10 = $0479;
  {$EXTERNALSYM cmb10}
  cmb11 = $047a;
  {$EXTERNALSYM cmb11}
  cmb12 = $047b;
  {$EXTERNALSYM cmb12}
  cmb13 = $047c;
  {$EXTERNALSYM cmb13}
  cmb14 = $047d;
  {$EXTERNALSYM cmb14}
  cmb15 = $047e;
  {$EXTERNALSYM cmb15}
  cmb16 = $047f;
  {$EXTERNALSYM cmb16}

//
//  Edit controls.
//

  edt1  = $0480;
  {$EXTERNALSYM edt1}
  edt2  = $0481;
  {$EXTERNALSYM edt2}
  edt3  = $0482;
  {$EXTERNALSYM edt3}
  edt4  = $0483;
  {$EXTERNALSYM edt4}
  edt5  = $0484;
  {$EXTERNALSYM edt5}
  edt6  = $0485;
  {$EXTERNALSYM edt6}
  edt7  = $0486;
  {$EXTERNALSYM edt7}
  edt8  = $0487;
  {$EXTERNALSYM edt8}
  edt9  = $0488;
  {$EXTERNALSYM edt9}
  edt10 = $0489;
  {$EXTERNALSYM edt10}
  edt11 = $048a;
  {$EXTERNALSYM edt11}
  edt12 = $048b;
  {$EXTERNALSYM edt12}
  edt13 = $048c;
  {$EXTERNALSYM edt13}
  edt14 = $048d;
  {$EXTERNALSYM edt14}
  edt15 = $048e;
  {$EXTERNALSYM edt15}
  edt16 = $048f;
  {$EXTERNALSYM edt16}

//
//  Scroll bars.
//

  scr1 = $0490;
  {$EXTERNALSYM scr1}
  scr2 = $0491;
  {$EXTERNALSYM scr2}
  scr3 = $0492;
  {$EXTERNALSYM scr3}
  scr4 = $0493;
  {$EXTERNALSYM scr4}
  scr5 = $0494;
  {$EXTERNALSYM scr5}
  scr6 = $0495;
  {$EXTERNALSYM scr6}
  scr7 = $0496;
  {$EXTERNALSYM scr7}
  scr8 = $0497;
  {$EXTERNALSYM scr8}

//
//  Controls
//

  ctl1 = $04A0;
  {$EXTERNALSYM ctl1}

//
//  These dialog resource ordinals really start at 0x0600, but the
//  RC Compiler can't handle hex for resource IDs, hence the decimal.
//

{$IFDEF UNIX}

  MW_BIG_FILEOPENORD      = 10000;
  {$EXTERNALSYM MW_BIG_FILEOPENORD}
  MW_BIG_MULTIFILEOPENORD = 10001;
  {$EXTERNALSYM MW_BIG_MULTIFILEOPENORD}

  FILEOPENORDMOTIF = 10003;
  {$EXTERNALSYM FILEOPENORDMOTIF}
  PRINTDLGORDMOTIF = 10004;
  {$EXTERNALSYM PRINTDLGORDMOTIF}
  FINDDLGORDMOTIF  = 10005;
  {$EXTERNALSYM FINDDLGORDMOTIF}

{$ENDIF}

  FILEOPENORD      = 1536;
  {$EXTERNALSYM FILEOPENORD}
  MULTIFILEOPENORD = 1537;
  {$EXTERNALSYM MULTIFILEOPENORD}
  PRINTDLGORD      = 1538;
  {$EXTERNALSYM PRINTDLGORD}
  PRNSETUPDLGORD   = 1539;
  {$EXTERNALSYM PRNSETUPDLGORD}
  FINDDLGORD       = 1540;
  {$EXTERNALSYM FINDDLGORD}
  REPLACEDLGORD    = 1541;
  {$EXTERNALSYM REPLACEDLGORD}
  FONTDLGORD       = 1542;
  {$EXTERNALSYM FONTDLGORD}
  FORMATDLGORD31   = 1543;
  {$EXTERNALSYM FORMATDLGORD31}
  FORMATDLGORD30   = 1544;
  {$EXTERNALSYM FORMATDLGORD30}
  RUNDLGORD        = 1545;
  {$EXTERNALSYM RUNDLGORD}

  PAGESETUPDLGORD      = 1546;
  {$EXTERNALSYM PAGESETUPDLGORD}
  NEWFILEOPENORD       = 1547;
  {$EXTERNALSYM NEWFILEOPENORD}
  PRINTDLGEXORD        = 1549;
  {$EXTERNALSYM PRINTDLGEXORD}
  PAGESETUPDLGORDMOTIF = 1550;
  {$EXTERNALSYM PAGESETUPDLGORDMOTIF}
  COLORMGMTDLGORD      = 1551;
  {$EXTERNALSYM COLORMGMTDLGORD}
  NEWFILEOPENV2ORD     = 1552;
  {$EXTERNALSYM NEWFILEOPENV2ORD}

//
//  Typedef Declarations.
//

type
  tagCRGB = record
    bRed: BYTE;
    bGreen: BYTE;
    bBlue: BYTE;
    bExtra: BYTE;
  end;
  {$EXTERNALSYM tagCRGB}
  CRGB = tagCRGB;
  {$EXTERNALSYM CRGB}

implementation

end.
