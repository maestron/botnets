{******************************************************************************}
{                                                       	               }
{ Windows Types API interface Unit for Object Pascal                           }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: winnt.h, released August 2001. The original Pascal     }
{ code is: WinNT.pas, released December 2000. The initial developer of the     }
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

unit JwaWinNT;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "winnt.h"'}
{$HPPEMIT ''}
{$HPPEMIT 'typedef PACL *PPACL'}
{$HPPEMIT 'typedef PSID *PPSID'}
{$HPPEMIT 'typedef PSECURITY_DESCRIPTOR *PPSECURITY_DESCRIPTOR'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

const
  MAXBYTE  = BYTE($ff);
  {$EXTERNALSYM MAXBYTE}
  MAXWORD  = WORD($ffff);
  {$EXTERNALSYM MAXWORD}
  MAXDWORD = DWORD($ffffffff);
  {$EXTERNALSYM MAXDWORD}

const
  VER_SERVER_NT                      = DWORD($80000000);
  {$EXTERNALSYM VER_SERVER_NT}
  VER_WORKSTATION_NT                 = $40000000;
  {$EXTERNALSYM VER_WORKSTATION_NT}
  VER_SUITE_SMALLBUSINESS            = $00000001;
  {$EXTERNALSYM VER_SUITE_SMALLBUSINESS}
  VER_SUITE_ENTERPRISE               = $00000002;
  {$EXTERNALSYM VER_SUITE_ENTERPRISE}
  VER_SUITE_BACKOFFICE               = $00000004;
  {$EXTERNALSYM VER_SUITE_BACKOFFICE}
  VER_SUITE_COMMUNICATIONS           = $00000008;
  {$EXTERNALSYM VER_SUITE_COMMUNICATIONS}
  VER_SUITE_TERMINAL                 = $00000010;
  {$EXTERNALSYM VER_SUITE_TERMINAL}
  VER_SUITE_SMALLBUSINESS_RESTRICTED = $00000020;
  {$EXTERNALSYM VER_SUITE_SMALLBUSINESS_RESTRICTED}
  VER_SUITE_EMBEDDEDNT               = $00000040;
  {$EXTERNALSYM VER_SUITE_EMBEDDEDNT}
  VER_SUITE_DATACENTER               = $00000080;
  {$EXTERNALSYM VER_SUITE_DATACENTER}
  VER_SUITE_SINGLEUSERTS             = $00000100;
  {$EXTERNALSYM VER_SUITE_SINGLEUSERTS}
  VER_SUITE_PERSONAL                 = $00000200;
  {$EXTERNALSYM VER_SUITE_PERSONAL}
  VER_SUITE_BLADE                    = $00000400;
  {$EXTERNALSYM VER_SUITE_BLADE}
  VER_SUITE_EMBEDDED_RESTRICTED      = $00000800;
  {$EXTERNALSYM VER_SUITE_EMBEDDED_RESTRICTED}
  VER_SUITE_SECURITY_APPLIANCE       = $00001000;
  {$EXTERNALSYM VER_SUITE_SECURITY_APPLIANCE}

//
//  Language IDs.
//
//  The following two combinations of primary language ID and
//  sublanguage ID have special semantics:
//
//    Primary Language ID   Sublanguage ID      Result
//    -------------------   ---------------     ------------------------
//    LANG_NEUTRAL          SUBLANG_NEUTRAL     Language neutral
//    LANG_NEUTRAL          SUBLANG_DEFAULT     User default language
//    LANG_NEUTRAL          SUBLANG_SYS_DEFAULT System default language
//    LANG_INVARIANT        SUBLANG_NEUTRAL     Invariant locale
//

//
//  Primary language IDs.
//

const
  LANG_NEUTRAL    = $00;
  {$EXTERNALSYM LANG_NEUTRAL}
  LANG_INVARIANT  = $7f;
  {$EXTERNALSYM LANG_INVARIANT}

  LANG_AFRIKAANS  = $36;
  {$EXTERNALSYM LANG_AFRIKAANS}
  LANG_ALBANIAN   = $1c;
  {$EXTERNALSYM LANG_ALBANIAN}
  LANG_ARABIC     = $01;
  {$EXTERNALSYM LANG_ARABIC}
  LANG_ARMENIAN   = $2b;
  {$EXTERNALSYM LANG_ARMENIAN}
  LANG_ASSAMESE   = $4d;
  {$EXTERNALSYM LANG_ASSAMESE}
  LANG_AZERI      = $2c;
  {$EXTERNALSYM LANG_AZERI}
  LANG_BASQUE     = $2d;
  {$EXTERNALSYM LANG_BASQUE}
  LANG_BELARUSIAN = $23;
  {$EXTERNALSYM LANG_BELARUSIAN}
  LANG_BENGALI    = $45;
  {$EXTERNALSYM LANG_BENGALI}
  LANG_BULGARIAN  = $02;
  {$EXTERNALSYM LANG_BULGARIAN}
  LANG_CATALAN    = $03;
  {$EXTERNALSYM LANG_CATALAN}
  LANG_CHINESE    = $04;
  {$EXTERNALSYM LANG_CHINESE}
  LANG_CROATIAN   = $1a;
  {$EXTERNALSYM LANG_CROATIAN}
  LANG_CZECH      = $05;
  {$EXTERNALSYM LANG_CZECH}
  LANG_DANISH     = $06;
  {$EXTERNALSYM LANG_DANISH}
  LANG_DIVEHI     = $65;
  {$EXTERNALSYM LANG_DIVEHI}
  LANG_DUTCH      = $13;
  {$EXTERNALSYM LANG_DUTCH}
  LANG_ENGLISH    = $09;
  {$EXTERNALSYM LANG_ENGLISH}
  LANG_ESTONIAN   = $25;
  {$EXTERNALSYM LANG_ESTONIAN}
  LANG_FAEROESE   = $38;
  {$EXTERNALSYM LANG_FAEROESE}
  LANG_FARSI      = $29;
  {$EXTERNALSYM LANG_FARSI}
  LANG_FINNISH    = $0b;
  {$EXTERNALSYM LANG_FINNISH}
  LANG_FRENCH     = $0c;
  {$EXTERNALSYM LANG_FRENCH}
  LANG_GALICIAN   = $56;
  {$EXTERNALSYM LANG_GALICIAN}
  LANG_GEORGIAN   = $37;
  {$EXTERNALSYM LANG_GEORGIAN}
  LANG_GERMAN     = $07;
  {$EXTERNALSYM LANG_GERMAN}
  LANG_GREEK      = $08;
  {$EXTERNALSYM LANG_GREEK}
  LANG_GUJARATI   = $47;
  {$EXTERNALSYM LANG_GUJARATI}
  LANG_HEBREW     = $0d;
  {$EXTERNALSYM LANG_HEBREW}
  LANG_HINDI      = $39;
  {$EXTERNALSYM LANG_HINDI}
  LANG_HUNGARIAN  = $0e;
  {$EXTERNALSYM LANG_HUNGARIAN}
  LANG_ICELANDIC  = $0f;
  {$EXTERNALSYM LANG_ICELANDIC}
  LANG_INDONESIAN = $21;
  {$EXTERNALSYM LANG_INDONESIAN}
  LANG_ITALIAN    = $10;
  {$EXTERNALSYM LANG_ITALIAN}
  LANG_JAPANESE   = $11;
  {$EXTERNALSYM LANG_JAPANESE}
  LANG_KANNADA    = $4b;
  {$EXTERNALSYM LANG_KANNADA}
  LANG_KASHMIRI   = $60;
  {$EXTERNALSYM LANG_KASHMIRI}
  LANG_KAZAK      = $3f;
  {$EXTERNALSYM LANG_KAZAK}
  LANG_KONKANI    = $57;
  {$EXTERNALSYM LANG_KONKANI}
  LANG_KOREAN     = $12;
  {$EXTERNALSYM LANG_KOREAN}
  LANG_KYRGYZ     = $40;
  {$EXTERNALSYM LANG_KYRGYZ}
  LANG_LATVIAN    = $26;
  {$EXTERNALSYM LANG_LATVIAN}
  LANG_LITHUANIAN = $27;
  {$EXTERNALSYM LANG_LITHUANIAN}
  LANG_MACEDONIAN = $2f;            // the Former Yugoslav Republic of Macedonia
  {$EXTERNALSYM LANG_MACEDONIAN}
  LANG_MALAY      = $3e;
  {$EXTERNALSYM LANG_MALAY}
  LANG_MALAYALAM  = $4c;
  {$EXTERNALSYM LANG_MALAYALAM}
  LANG_MANIPURI   = $58;
  {$EXTERNALSYM LANG_MANIPURI}
  LANG_MARATHI    = $4e;
  {$EXTERNALSYM LANG_MARATHI}
  LANG_MONGOLIAN  = $50;
  {$EXTERNALSYM LANG_MONGOLIAN}
  LANG_NEPALI     = $61;
  {$EXTERNALSYM LANG_NEPALI}
  LANG_NORWEGIAN  = $14;
  {$EXTERNALSYM LANG_NORWEGIAN}
  LANG_ORIYA      = $48;
  {$EXTERNALSYM LANG_ORIYA}
  LANG_POLISH     = $15;
  {$EXTERNALSYM LANG_POLISH}
  LANG_PORTUGUESE = $16;
  {$EXTERNALSYM LANG_PORTUGUESE}
  LANG_PUNJABI    = $46;
  {$EXTERNALSYM LANG_PUNJABI}
  LANG_ROMANIAN   = $18;
  {$EXTERNALSYM LANG_ROMANIAN}
  LANG_RUSSIAN    = $19;
  {$EXTERNALSYM LANG_RUSSIAN}
  LANG_SANSKRIT   = $4f;
  {$EXTERNALSYM LANG_SANSKRIT}
  LANG_SERBIAN    = $1a;
  {$EXTERNALSYM LANG_SERBIAN}
  LANG_SINDHI     = $59;
  {$EXTERNALSYM LANG_SINDHI}
  LANG_SLOVAK     = $1b;
  {$EXTERNALSYM LANG_SLOVAK}
  LANG_SLOVENIAN  = $24;
  {$EXTERNALSYM LANG_SLOVENIAN}
  LANG_SPANISH    = $0a;
  {$EXTERNALSYM LANG_SPANISH}
  LANG_SWAHILI    = $41;
  {$EXTERNALSYM LANG_SWAHILI}
  LANG_SWEDISH    = $1d;
  {$EXTERNALSYM LANG_SWEDISH}
  LANG_SYRIAC     = $5a;
  {$EXTERNALSYM LANG_SYRIAC}
  LANG_TAMIL      = $49;
  {$EXTERNALSYM LANG_TAMIL}
  LANG_TATAR      = $44;
  {$EXTERNALSYM LANG_TATAR}
  LANG_TELUGU     = $4a;
  {$EXTERNALSYM LANG_TELUGU}
  LANG_THAI       = $1e;
  {$EXTERNALSYM LANG_THAI}
  LANG_TURKISH    = $1f;
  {$EXTERNALSYM LANG_TURKISH}
  LANG_UKRAINIAN  = $22;
  {$EXTERNALSYM LANG_UKRAINIAN}
  LANG_URDU       = $20;
  {$EXTERNALSYM LANG_URDU}
  LANG_UZBEK      = $43;
  {$EXTERNALSYM LANG_UZBEK}
  LANG_VIETNAMESE = $2a;
  {$EXTERNALSYM LANG_VIETNAMESE}

//
//  Sublanguage IDs.
//
//  The name immediately following SUBLANG_ dictates which primary
//  language ID that sublanguage ID can be combined with to form a
//  valid language ID.
//

  SUBLANG_NEUTRAL     = $00; // language neutral
  {$EXTERNALSYM SUBLANG_NEUTRAL}
  SUBLANG_DEFAULT     = $01; // user default
  {$EXTERNALSYM SUBLANG_DEFAULT}
  SUBLANG_SYS_DEFAULT = $02; // system default
  {$EXTERNALSYM SUBLANG_SYS_DEFAULT}

  SUBLANG_ARABIC_SAUDI_ARABIA        = $01; // Arabic (Saudi Arabia)
  {$EXTERNALSYM SUBLANG_ARABIC_SAUDI_ARABIA}
  SUBLANG_ARABIC_IRAQ                = $02; // Arabic (Iraq)
  {$EXTERNALSYM SUBLANG_ARABIC_IRAQ}
  SUBLANG_ARABIC_EGYPT               = $03; // Arabic (Egypt)
  {$EXTERNALSYM SUBLANG_ARABIC_EGYPT}
  SUBLANG_ARABIC_LIBYA               = $04; // Arabic (Libya)
  {$EXTERNALSYM SUBLANG_ARABIC_LIBYA}
  SUBLANG_ARABIC_ALGERIA             = $05; // Arabic (Algeria)
  {$EXTERNALSYM SUBLANG_ARABIC_ALGERIA}
  SUBLANG_ARABIC_MOROCCO             = $06; // Arabic (Morocco)
  {$EXTERNALSYM SUBLANG_ARABIC_MOROCCO}
  SUBLANG_ARABIC_TUNISIA             = $07; // Arabic (Tunisia)
  {$EXTERNALSYM SUBLANG_ARABIC_TUNISIA}
  SUBLANG_ARABIC_OMAN                = $08; // Arabic (Oman)
  {$EXTERNALSYM SUBLANG_ARABIC_OMAN}
  SUBLANG_ARABIC_YEMEN               = $09; // Arabic (Yemen)
  {$EXTERNALSYM SUBLANG_ARABIC_YEMEN}
  SUBLANG_ARABIC_SYRIA               = $0a; // Arabic (Syria)
  {$EXTERNALSYM SUBLANG_ARABIC_SYRIA}
  SUBLANG_ARABIC_JORDAN              = $0b; // Arabic (Jordan)
  {$EXTERNALSYM SUBLANG_ARABIC_JORDAN}
  SUBLANG_ARABIC_LEBANON             = $0c; // Arabic (Lebanon)
  {$EXTERNALSYM SUBLANG_ARABIC_LEBANON}
  SUBLANG_ARABIC_KUWAIT              = $0d; // Arabic (Kuwait)
  {$EXTERNALSYM SUBLANG_ARABIC_KUWAIT}
  SUBLANG_ARABIC_UAE                 = $0e; // Arabic (U.A.E)
  {$EXTERNALSYM SUBLANG_ARABIC_UAE}
  SUBLANG_ARABIC_BAHRAIN             = $0f; // Arabic (Bahrain)
  {$EXTERNALSYM SUBLANG_ARABIC_BAHRAIN}
  SUBLANG_ARABIC_QATAR               = $10; // Arabic (Qatar)
  {$EXTERNALSYM SUBLANG_ARABIC_QATAR}
  SUBLANG_AZERI_LATIN                = $01; // Azeri (Latin)
  {$EXTERNALSYM SUBLANG_AZERI_LATIN}
  SUBLANG_AZERI_CYRILLIC             = $02; // Azeri (Cyrillic)
  {$EXTERNALSYM SUBLANG_AZERI_CYRILLIC}
  SUBLANG_CHINESE_TRADITIONAL        = $01; // Chinese (Taiwan)
  {$EXTERNALSYM SUBLANG_CHINESE_TRADITIONAL}
  SUBLANG_CHINESE_SIMPLIFIED         = $02; // Chinese (PR China)
  {$EXTERNALSYM SUBLANG_CHINESE_SIMPLIFIED}
  SUBLANG_CHINESE_HONGKONG           = $03; // Chinese (Hong Kong S.A.R., P.R.C.)
  {$EXTERNALSYM SUBLANG_CHINESE_HONGKONG}
  SUBLANG_CHINESE_SINGAPORE          = $04; // Chinese (Singapore)
  {$EXTERNALSYM SUBLANG_CHINESE_SINGAPORE}
  SUBLANG_CHINESE_MACAU              = $05; // Chinese (Macau S.A.R.)
  {$EXTERNALSYM SUBLANG_CHINESE_MACAU}
  SUBLANG_DUTCH                      = $01; // Dutch
  {$EXTERNALSYM SUBLANG_DUTCH}
  SUBLANG_DUTCH_BELGIAN              = $02; // Dutch (Belgian)
  {$EXTERNALSYM SUBLANG_DUTCH_BELGIAN}
  SUBLANG_ENGLISH_US                 = $01; // English (USA)
  {$EXTERNALSYM SUBLANG_ENGLISH_US}
  SUBLANG_ENGLISH_UK                 = $02; // English (UK)
  {$EXTERNALSYM SUBLANG_ENGLISH_UK}
  SUBLANG_ENGLISH_AUS                = $03; // English (Australian)
  {$EXTERNALSYM SUBLANG_ENGLISH_AUS}
  SUBLANG_ENGLISH_CAN                = $04; // English (Canadian)
  {$EXTERNALSYM SUBLANG_ENGLISH_CAN}
  SUBLANG_ENGLISH_NZ                 = $05; // English (New Zealand)
  {$EXTERNALSYM SUBLANG_ENGLISH_NZ}
  SUBLANG_ENGLISH_EIRE               = $06; // English (Irish)
  {$EXTERNALSYM SUBLANG_ENGLISH_EIRE}
  SUBLANG_ENGLISH_SOUTH_AFRICA       = $07; // English (South Africa)
  {$EXTERNALSYM SUBLANG_ENGLISH_SOUTH_AFRICA}
  SUBLANG_ENGLISH_JAMAICA            = $08; // English (Jamaica)
  {$EXTERNALSYM SUBLANG_ENGLISH_JAMAICA}
  SUBLANG_ENGLISH_CARIBBEAN          = $09; // English (Caribbean)
  {$EXTERNALSYM SUBLANG_ENGLISH_CARIBBEAN}
  SUBLANG_ENGLISH_BELIZE             = $0a; // English (Belize)
  {$EXTERNALSYM SUBLANG_ENGLISH_BELIZE}
  SUBLANG_ENGLISH_TRINIDAD           = $0b; // English (Trinidad)
  {$EXTERNALSYM SUBLANG_ENGLISH_TRINIDAD}
  SUBLANG_ENGLISH_ZIMBABWE           = $0c; // English (Zimbabwe)
  {$EXTERNALSYM SUBLANG_ENGLISH_ZIMBABWE}
  SUBLANG_ENGLISH_PHILIPPINES        = $0d; // English (Philippines)
  {$EXTERNALSYM SUBLANG_ENGLISH_PHILIPPINES}
  SUBLANG_FRENCH                     = $01; // French
  {$EXTERNALSYM SUBLANG_FRENCH}
  SUBLANG_FRENCH_BELGIAN             = $02; // French (Belgian)
  {$EXTERNALSYM SUBLANG_FRENCH_BELGIAN}
  SUBLANG_FRENCH_CANADIAN            = $03; // French (Canadian)
  {$EXTERNALSYM SUBLANG_FRENCH_CANADIAN}
  SUBLANG_FRENCH_SWISS               = $04; // French (Swiss)
  {$EXTERNALSYM SUBLANG_FRENCH_SWISS}
  SUBLANG_FRENCH_LUXEMBOURG          = $05; // French (Luxembourg)
  {$EXTERNALSYM SUBLANG_FRENCH_LUXEMBOURG}
  SUBLANG_FRENCH_MONACO              = $06; // French (Monaco)
  {$EXTERNALSYM SUBLANG_FRENCH_MONACO}
  SUBLANG_GERMAN                     = $01; // German
  {$EXTERNALSYM SUBLANG_GERMAN}
  SUBLANG_GERMAN_SWISS               = $02; // German (Swiss)
  {$EXTERNALSYM SUBLANG_GERMAN_SWISS}
  SUBLANG_GERMAN_AUSTRIAN            = $03; // German (Austrian)
  {$EXTERNALSYM SUBLANG_GERMAN_AUSTRIAN}
  SUBLANG_GERMAN_LUXEMBOURG          = $04; // German (Luxembourg)
  {$EXTERNALSYM SUBLANG_GERMAN_LUXEMBOURG}
  SUBLANG_GERMAN_LIECHTENSTEIN       = $05; // German (Liechtenstein)
  {$EXTERNALSYM SUBLANG_GERMAN_LIECHTENSTEIN}
  SUBLANG_ITALIAN                    = $01; // Italian
  {$EXTERNALSYM SUBLANG_ITALIAN}
  SUBLANG_ITALIAN_SWISS              = $02; // Italian (Swiss)
  {$EXTERNALSYM SUBLANG_ITALIAN_SWISS}
  SUBLANG_KASHMIRI_SASIA             = $02; // Kashmiri (South Asia)
  {$EXTERNALSYM SUBLANG_KASHMIRI_SASIA}
  SUBLANG_KASHMIRI_INDIA             = $02; // For app compatibility only
  {$EXTERNALSYM SUBLANG_KASHMIRI_INDIA}
  SUBLANG_KOREAN                     = $01; // Korean (Extended Wansung)
  {$EXTERNALSYM SUBLANG_KOREAN}
  SUBLANG_LITHUANIAN                 = $01; // Lithuanian
  {$EXTERNALSYM SUBLANG_LITHUANIAN}
  SUBLANG_MALAY_MALAYSIA             = $01; // Malay (Malaysia)
  {$EXTERNALSYM SUBLANG_MALAY_MALAYSIA}
  SUBLANG_MALAY_BRUNEI_DARUSSALAM    = $02; // Malay (Brunei Darussalam)
  {$EXTERNALSYM SUBLANG_MALAY_BRUNEI_DARUSSALAM}
  SUBLANG_NEPALI_INDIA               = $02; // Nepali (India)
  {$EXTERNALSYM SUBLANG_NEPALI_INDIA}
  SUBLANG_NORWEGIAN_BOKMAL           = $01; // Norwegian (Bokmal)
  {$EXTERNALSYM SUBLANG_NORWEGIAN_BOKMAL}
  SUBLANG_NORWEGIAN_NYNORSK          = $02; // Norwegian (Nynorsk)
  {$EXTERNALSYM SUBLANG_NORWEGIAN_NYNORSK}
  SUBLANG_PORTUGUESE                 = $02; // Portuguese
  {$EXTERNALSYM SUBLANG_PORTUGUESE}
  SUBLANG_PORTUGUESE_BRAZILIAN       = $01; // Portuguese (Brazilian)
  {$EXTERNALSYM SUBLANG_PORTUGUESE_BRAZILIAN}
  SUBLANG_SERBIAN_LATIN              = $02; // Serbian (Latin)
  {$EXTERNALSYM SUBLANG_SERBIAN_LATIN}
  SUBLANG_SERBIAN_CYRILLIC           = $03; // Serbian (Cyrillic)
  {$EXTERNALSYM SUBLANG_SERBIAN_CYRILLIC}
  SUBLANG_SPANISH                    = $01; // Spanish (Castilian)
  {$EXTERNALSYM SUBLANG_SPANISH}
  SUBLANG_SPANISH_MEXICAN            = $02; // Spanish (Mexican)
  {$EXTERNALSYM SUBLANG_SPANISH_MEXICAN}
  SUBLANG_SPANISH_MODERN             = $03; // Spanish (Spain)
  {$EXTERNALSYM SUBLANG_SPANISH_MODERN}
  SUBLANG_SPANISH_GUATEMALA          = $04; // Spanish (Guatemala)
  {$EXTERNALSYM SUBLANG_SPANISH_GUATEMALA}
  SUBLANG_SPANISH_COSTA_RICA         = $05; // Spanish (Costa Rica)
  {$EXTERNALSYM SUBLANG_SPANISH_COSTA_RICA}
  SUBLANG_SPANISH_PANAMA             = $06; // Spanish (Panama)
  {$EXTERNALSYM SUBLANG_SPANISH_PANAMA}
  SUBLANG_SPANISH_DOMINICAN_REPUBLIC = $07; // Spanish (Dominican Republic)
  {$EXTERNALSYM SUBLANG_SPANISH_DOMINICAN_REPUBLIC}
  SUBLANG_SPANISH_VENEZUELA          = $08; // Spanish (Venezuela)
  {$EXTERNALSYM SUBLANG_SPANISH_VENEZUELA}
  SUBLANG_SPANISH_COLOMBIA           = $09; // Spanish (Colombia)
  {$EXTERNALSYM SUBLANG_SPANISH_COLOMBIA}
  SUBLANG_SPANISH_PERU               = $0a; // Spanish (Peru)
  {$EXTERNALSYM SUBLANG_SPANISH_PERU}
  SUBLANG_SPANISH_ARGENTINA          = $0b; // Spanish (Argentina)
  {$EXTERNALSYM SUBLANG_SPANISH_ARGENTINA}
  SUBLANG_SPANISH_ECUADOR            = $0c; // Spanish (Ecuador)
  {$EXTERNALSYM SUBLANG_SPANISH_ECUADOR}
  SUBLANG_SPANISH_CHILE              = $0d; // Spanish (Chile)
  {$EXTERNALSYM SUBLANG_SPANISH_CHILE}
  SUBLANG_SPANISH_URUGUAY            = $0e; // Spanish (Uruguay)
  {$EXTERNALSYM SUBLANG_SPANISH_URUGUAY}
  SUBLANG_SPANISH_PARAGUAY           = $0f; // Spanish (Paraguay)
  {$EXTERNALSYM SUBLANG_SPANISH_PARAGUAY}
  SUBLANG_SPANISH_BOLIVIA            = $10; // Spanish (Bolivia)
  {$EXTERNALSYM SUBLANG_SPANISH_BOLIVIA}
  SUBLANG_SPANISH_EL_SALVADOR        = $11; // Spanish (El Salvador)
  {$EXTERNALSYM SUBLANG_SPANISH_EL_SALVADOR}
  SUBLANG_SPANISH_HONDURAS           = $12; // Spanish (Honduras)
  {$EXTERNALSYM SUBLANG_SPANISH_HONDURAS}
  SUBLANG_SPANISH_NICARAGUA          = $13; // Spanish (Nicaragua)
  {$EXTERNALSYM SUBLANG_SPANISH_NICARAGUA}
  SUBLANG_SPANISH_PUERTO_RICO        = $14; // Spanish (Puerto Rico)
  {$EXTERNALSYM SUBLANG_SPANISH_PUERTO_RICO}
  SUBLANG_SWEDISH                    = $01; // Swedish
  {$EXTERNALSYM SUBLANG_SWEDISH}
  SUBLANG_SWEDISH_FINLAND            = $02; // Swedish (Finland)
  {$EXTERNALSYM SUBLANG_SWEDISH_FINLAND}
  SUBLANG_URDU_PAKISTAN              = $01; // Urdu (Pakistan)
  {$EXTERNALSYM SUBLANG_URDU_PAKISTAN}
  SUBLANG_URDU_INDIA                 = $02; // Urdu (India)
  {$EXTERNALSYM SUBLANG_URDU_INDIA}
  SUBLANG_UZBEK_LATIN                = $01; // Uzbek (Latin)
  {$EXTERNALSYM SUBLANG_UZBEK_LATIN}
  SUBLANG_UZBEK_CYRILLIC             = $02; // Uzbek (Cyrillic)
  {$EXTERNALSYM SUBLANG_UZBEK_CYRILLIC}

//
//  Sorting IDs.
//

  SORT_DEFAULT = $0; // sorting default
  {$EXTERNALSYM SORT_DEFAULT}

  SORT_JAPANESE_XJIS    = $0; // Japanese XJIS order
  {$EXTERNALSYM SORT_JAPANESE_XJIS}
  SORT_JAPANESE_UNICODE = $1; // Japanese Unicode order
  {$EXTERNALSYM SORT_JAPANESE_UNICODE}

  SORT_CHINESE_BIG5     = $0; // Chinese BIG5 order
  {$EXTERNALSYM SORT_CHINESE_BIG5}
  SORT_CHINESE_PRCP     = $0; // PRC Chinese Phonetic order
  {$EXTERNALSYM SORT_CHINESE_PRCP}
  SORT_CHINESE_UNICODE  = $1; // Chinese Unicode order
  {$EXTERNALSYM SORT_CHINESE_UNICODE}
  SORT_CHINESE_PRC      = $2; // PRC Chinese Stroke Count order
  {$EXTERNALSYM SORT_CHINESE_PRC}
  SORT_CHINESE_BOPOMOFO = $3; // Traditional Chinese Bopomofo order
  {$EXTERNALSYM SORT_CHINESE_BOPOMOFO}

  SORT_KOREAN_KSC     = $0; // Korean KSC order
  {$EXTERNALSYM SORT_KOREAN_KSC}
  SORT_KOREAN_UNICODE = $1; // Korean Unicode order
  {$EXTERNALSYM SORT_KOREAN_UNICODE}

  SORT_GERMAN_PHONE_BOOK = $1; // German Phone Book order
  {$EXTERNALSYM SORT_GERMAN_PHONE_BOOK}

  SORT_HUNGARIAN_DEFAULT   = $0; // Hungarian Default order
  {$EXTERNALSYM SORT_HUNGARIAN_DEFAULT}
  SORT_HUNGARIAN_TECHNICAL = $1; // Hungarian Technical order
  {$EXTERNALSYM SORT_HUNGARIAN_TECHNICAL}

  SORT_GEORGIAN_TRADITIONAL = $0; // Georgian Traditional order
  {$EXTERNALSYM SORT_GEORGIAN_TRADITIONAL}
  SORT_GEORGIAN_MODERN      = $1; // Georgian Modern order
  {$EXTERNALSYM SORT_GEORGIAN_MODERN}

//
//  A language ID is a 16 bit value which is the combination of a
//  primary language ID and a secondary language ID.  The bits are
//  allocated as follows:
//
//       +-----------------------+-------------------------+
//       |     Sublanguage ID    |   Primary Language ID   |
//       +-----------------------+-------------------------+
//        15                   10 9                       0   bit
//
//
//  Language ID creation/extraction macros:
//
//    MAKELANGID    - construct language id from a primary language id and
//                    a sublanguage id.
//    PRIMARYLANGID - extract primary language id from a language id.
//    SUBLANGID     - extract sublanguage id from a language id.
//

function MAKELANGID(PrimaryLang, SubLang: USHORT): WORD;
{$EXTERNALSYM MAKELANGID}
function PRIMARYLANGID(LangId: WORD): WORD;
{$EXTERNALSYM PRIMARYLANGID}
function SUBLANGID(LangId: WORD): WORD;
{$EXTERNALSYM SUBLANGID}

//
//  A locale ID is a 32 bit value which is the combination of a
//  language ID, a sort ID, and a reserved area.  The bits are
//  allocated as follows:
//
//       +-------------+---------+-------------------------+
//       |   Reserved  | Sort ID |      Language ID        |
//       +-------------+---------+-------------------------+
//        31         20 19     16 15                      0   bit
//
//
//  Locale ID creation/extraction macros:
//
//    MAKELCID            - construct the locale id from a language id and a sort id.
//    MAKESORTLCID        - construct the locale id from a language id, sort id, and sort version.
//    LANGIDFROMLCID      - extract the language id from a locale id.
//    SORTIDFROMLCID      - extract the sort id from a locale id.
//    SORTVERSIONFROMLCID - extract the sort version from a locale id.
//

const
  NLS_VALID_LOCALE_MASK = $000fffff;
  {$EXTERNALSYM NLS_VALID_LOCALE_MASK}

function MAKELCID(LangId, SortId: WORD): DWORD;
{$EXTERNALSYM MAKELCID}
function MAKESORTLCID(LangId, SortId, SortVersion: WORD): DWORD;
{$EXTERNALSYM MAKESORTLCID}
function LANGIDFROMLCID(LocaleId: LCID): WORD;
{$EXTERNALSYM LANGIDFROMLCID}
function SORTIDFROMLCID(LocaleId: LCID): WORD;
{$EXTERNALSYM SORTIDFROMLCID}
function SORTVERSIONFROMLCID(LocaleId: LCID): WORD;
{$EXTERNALSYM SORTVERSIONFROMLCID}

//
//  Default System and User IDs for language and locale.
//

function LANG_SYSTEM_DEFAULT: WORD;
{$EXTERNALSYM LANG_SYSTEM_DEFAULT}
function LANG_USER_DEFAULT: WORD;
{$EXTERNALSYM LANG_USER_DEFAULT}
function LOCALE_SYSTEM_DEFAULT: DWORD;
{$EXTERNALSYM LOCALE_SYSTEM_DEFAULT}
function LOCALE_USER_DEFAULT: DWORD;
{$EXTERNALSYM LOCALE_USER_DEFAULT}
function LOCALE_NEUTRAL: DWORD;
{$EXTERNALSYM LOCALE_NEUTRAL}
function LOCALE_INVARIANT: DWORD;
{$EXTERNALSYM LOCALE_NEUTRAL}

{$IFNDEF WIN32_NO_STATUS}

const
  STATUS_WAIT_0                   = DWORD($00000000);
  {$EXTERNALSYM STATUS_WAIT_0}
  STATUS_ABANDONED_WAIT_0         = DWORD($00000080);
  {$EXTERNALSYM STATUS_ABANDONED_WAIT_0}
  STATUS_USER_APC                 = DWORD($000000C0);
  {$EXTERNALSYM STATUS_USER_APC}
  STATUS_TIMEOUT                  = DWORD($00000102);
  {$EXTERNALSYM STATUS_TIMEOUT}
  STATUS_PENDING                  = DWORD($00000103);
  {$EXTERNALSYM STATUS_PENDING}
  DBG_EXCEPTION_HANDLED           = DWORD($00010001);
  {$EXTERNALSYM DBG_EXCEPTION_HANDLED}
  DBG_CONTINUE                    = DWORD($00010002);
  {$EXTERNALSYM DBG_CONTINUE}
  STATUS_SEGMENT_NOTIFICATION     = DWORD($40000005);
  {$EXTERNALSYM STATUS_SEGMENT_NOTIFICATION}
  DBG_TERMINATE_THREAD            = DWORD($40010003);
  {$EXTERNALSYM DBG_TERMINATE_THREAD}
  DBG_TERMINATE_PROCESS           = DWORD($40010004);
  {$EXTERNALSYM DBG_TERMINATE_PROCESS}
  DBG_CONTROL_C                   = DWORD($40010005);
  {$EXTERNALSYM DBG_CONTROL_C}
  DBG_CONTROL_BREAK               = DWORD($40010008);
  {$EXTERNALSYM DBG_CONTROL_BREAK}
  DBG_COMMAND_EXCEPTION           = DWORD($40010009);
  {$EXTERNALSYM DBG_COMMAND_EXCEPTION}
  STATUS_GUARD_PAGE_VIOLATION     = DWORD($80000001);
  {$EXTERNALSYM STATUS_GUARD_PAGE_VIOLATION}
  STATUS_DATATYPE_MISALIGNMENT    = DWORD($80000002);
  {$EXTERNALSYM STATUS_DATATYPE_MISALIGNMENT}
  STATUS_BREAKPOINT               = DWORD($80000003);
  {$EXTERNALSYM STATUS_BREAKPOINT}
  STATUS_SINGLE_STEP              = DWORD($80000004);
  {$EXTERNALSYM STATUS_SINGLE_STEP}
  DBG_EXCEPTION_NOT_HANDLED       = DWORD($80010001);
  {$EXTERNALSYM DBG_EXCEPTION_NOT_HANDLED}
  STATUS_ACCESS_VIOLATION         = DWORD($C0000005);
  {$EXTERNALSYM STATUS_ACCESS_VIOLATION}
  STATUS_IN_PAGE_ERROR            = DWORD($C0000006);
  {$EXTERNALSYM STATUS_IN_PAGE_ERROR}
  STATUS_INVALID_HANDLE           = DWORD($C0000008);
  {$EXTERNALSYM STATUS_INVALID_HANDLE}
  STATUS_NO_MEMORY                = DWORD($C0000017);
  {$EXTERNALSYM STATUS_NO_MEMORY}
  STATUS_ILLEGAL_INSTRUCTION      = DWORD($C000001D);
  {$EXTERNALSYM STATUS_ILLEGAL_INSTRUCTION}
  STATUS_NONCONTINUABLE_EXCEPTION = DWORD($C0000025);
  {$EXTERNALSYM STATUS_NONCONTINUABLE_EXCEPTION}
  STATUS_INVALID_DISPOSITION      = DWORD($C0000026);
  {$EXTERNALSYM STATUS_INVALID_DISPOSITION}
  STATUS_ARRAY_BOUNDS_EXCEEDED    = DWORD($C000008C);
  {$EXTERNALSYM STATUS_ARRAY_BOUNDS_EXCEEDED}
  STATUS_FLOAT_DENORMAL_OPERAND   = DWORD($C000008D);
  {$EXTERNALSYM STATUS_FLOAT_DENORMAL_OPERAND}
  STATUS_FLOAT_DIVIDE_BY_ZERO     = DWORD($C000008E);
  {$EXTERNALSYM STATUS_FLOAT_DIVIDE_BY_ZERO}
  STATUS_FLOAT_INEXACT_RESULT     = DWORD($C000008F);
  {$EXTERNALSYM STATUS_FLOAT_INEXACT_RESULT}
  STATUS_FLOAT_INVALID_OPERATION  = DWORD($C0000090);
  {$EXTERNALSYM STATUS_FLOAT_INVALID_OPERATION}
  STATUS_FLOAT_OVERFLOW           = DWORD($C0000091);
  {$EXTERNALSYM STATUS_FLOAT_OVERFLOW}
  STATUS_FLOAT_STACK_CHECK        = DWORD($C0000092);
  {$EXTERNALSYM STATUS_FLOAT_STACK_CHECK}
  STATUS_FLOAT_UNDERFLOW          = DWORD($C0000093);
  {$EXTERNALSYM STATUS_FLOAT_UNDERFLOW}
  STATUS_INTEGER_DIVIDE_BY_ZERO   = DWORD($C0000094);
  {$EXTERNALSYM STATUS_INTEGER_DIVIDE_BY_ZERO}
  STATUS_INTEGER_OVERFLOW         = DWORD($C0000095);
  {$EXTERNALSYM STATUS_INTEGER_OVERFLOW}
  STATUS_PRIVILEGED_INSTRUCTION   = DWORD($C0000096);
  {$EXTERNALSYM STATUS_PRIVILEGED_INSTRUCTION}
  STATUS_STACK_OVERFLOW           = DWORD($C00000FD);
  {$EXTERNALSYM STATUS_STACK_OVERFLOW}
  STATUS_CONTROL_C_EXIT           = DWORD($C000013A);
  {$EXTERNALSYM STATUS_CONTROL_C_EXIT}
  STATUS_FLOAT_MULTIPLE_FAULTS    = DWORD($C00002B4);
  {$EXTERNALSYM STATUS_FLOAT_MULTIPLE_FAULTS}
  STATUS_FLOAT_MULTIPLE_TRAPS     = DWORD($C00002B5);
  {$EXTERNALSYM STATUS_FLOAT_MULTIPLE_TRAPS}
  STATUS_REG_NAT_CONSUMPTION      = DWORD($C00002C9);
  {$EXTERNALSYM STATUS_REG_NAT_CONSUMPTION}
  STATUS_SXS_EARLY_DEACTIVATION   = DWORD($C015000F);
  {$EXTERNALSYM STATUS_SXS_EARLY_DEACTIVATION}
  STATUS_SXS_INVALID_DEACTIVATION = DWORD($C0150010);
  {$EXTERNALSYM STATUS_SXS_INVALID_DEACTIVATION}

{$ENDIF}

const
  MAXIMUM_WAIT_OBJECTS  = 64;      // Maximum number of wait objects
  {$EXTERNALSYM MAXIMUM_WAIT_OBJECTS}

  MAXIMUM_SUSPEND_COUNT = MAXCHAR; // Maximum times thread can be suspended
  {$EXTERNALSYM MAXIMUM_SUSPEND_COUNT}

type
  KSPIN_LOCK = ULONG_PTR;
  {$EXTERNALSYM KSPIN_LOCK}
  PKSPIN_LOCK = ^KSPIN_LOCK;
  {$EXTERNALSYM PKSPIN_LOCK}

//
// Define functions to get the address of the current fiber and the
// current fiber data.
//

//
// Disable these two pramas that evaluate to "sti" "cli" on x86 so that driver
// writers to not leave them inadvertantly in their code.
//

function GetFiberData: PVOID;
{$EXTERNALSYM GetFiberData}

function GetCurrentFiber: PVOID;
{$EXTERNALSYM GetCurrentFiber}

//
//  Define the size of the 80387 save area, which is in the context frame.
//

const
  SIZE_OF_80387_REGISTERS = 80;
  {$EXTERNALSYM SIZE_OF_80387_REGISTERS}

//
// The following flags control the contents of the CONTEXT structure.
//

const
  CONTEXT_i386 = $00010000; // this assumes that i386 and
  {$EXTERNALSYM CONTEXT_i386}
  CONTEXT_i486 = $00010000; // i486 have identical context records
  {$EXTERNALSYM CONTEXT_i486}

const
  CONTEXT_CONTROL            = (CONTEXT_i386 or $00000001); // SS:SP, CS:IP, FLAGS, BP
  {$EXTERNALSYM CONTEXT_CONTROL}
  CONTEXT_INTEGER            = (CONTEXT_i386 or $00000002); // AX, BX, CX, DX, SI, DI
  {$EXTERNALSYM CONTEXT_INTEGER}
  CONTEXT_SEGMENTS           = (CONTEXT_i386 or $00000004); // DS, ES, FS, GS
  {$EXTERNALSYM CONTEXT_SEGMENTS}
  CONTEXT_FLOATING_POINT     = (CONTEXT_i386 or $00000008); // 387 state
  {$EXTERNALSYM CONTEXT_FLOATING_POINT}
  CONTEXT_DEBUG_REGISTERS    = (CONTEXT_i386 or $00000010); // DB 0-3,6,7
  {$EXTERNALSYM CONTEXT_DEBUG_REGISTERS}
  CONTEXT_EXTENDED_REGISTERS = (CONTEXT_i386 or $00000020); // cpu specific extensions
  {$EXTERNALSYM CONTEXT_EXTENDED_REGISTERS}

  CONTEXT_FULL = (CONTEXT_CONTROL or CONTEXT_INTEGER or CONTEXT_SEGMENTS);
  {$EXTERNALSYM CONTEXT_FULL}

  CONTEXT_ALL = (CONTEXT_CONTROL or CONTEXT_INTEGER or CONTEXT_SEGMENTS or CONTEXT_FLOATING_POINT or CONTEXT_DEBUG_REGISTERS);
  {$EXTERNALSYM CONTEXT_ALL}

//
// Define initial MxCsr control.
//

  INITIAL_MXCSR = $1f80;            // initial MXCSR value
  {$EXTERNALSYM INITIAL_MXCSR}

  MAXIMUM_SUPPORTED_EXTENSION = 512;
  {$EXTERNALSYM MAXIMUM_SUPPORTED_EXTENSION}

type
  PFLOATING_SAVE_AREA = ^FLOATING_SAVE_AREA;
  {$EXTERNALSYM PFLOATING_SAVE_AREA}
  _FLOATING_SAVE_AREA = record
    ControlWord: DWORD;
    StatusWord: DWORD;
    TagWord: DWORD;
    ErrorOffset: DWORD;
    ErrorSelector: DWORD;
    DataOffset: DWORD;
    DataSelector: DWORD;
    RegisterArea: array [0..SIZE_OF_80387_REGISTERS - 1] of BYTE;
    Cr0NpxState: DWORD;
  end;
  {$EXTERNALSYM _FLOATING_SAVE_AREA}
  FLOATING_SAVE_AREA = _FLOATING_SAVE_AREA;
  {$EXTERNALSYM FLOATING_SAVE_AREA}
  TFloatingSaveArea = FLOATING_SAVE_AREA;
  PFloatingSaveArea = PFLOATING_SAVE_AREA;

//
// Context Frame
//
//  This frame has a several purposes: 1) it is used as an argument to
//  NtContinue, 2) is is used to constuct a call frame for APC delivery,
//  and 3) it is used in the user level thread creation routines.
//
//  The layout of the record conforms to a standard call frame.
//

type
  PContext = ^CONTEXT;
  _CONTEXT  = record

    //
    // The flags values within this flag control the contents of
    // a CONTEXT record.
    //
    // If the context record is used as an input parameter, then
    // for each portion of the context record controlled by a flag
    // whose value is set, it is assumed that that portion of the
    // context record contains valid context. If the context record
    // is being used to modify a threads context, then only that
    // portion of the threads context will be modified.
    //
    // If the context record is used as an IN OUT parameter to capture
    // the context of a thread, then only those portions of the thread's
    // context corresponding to set flags will be returned.
    //
    // The context record is never used as an OUT only parameter.
    //

    ContextFlags: DWORD;

    //
    // This section is specified/returned if CONTEXT_DEBUG_REGISTERS is
    // set in ContextFlags.  Note that CONTEXT_DEBUG_REGISTERS is NOT
    // included in CONTEXT_FULL.
    //

    Dr0: DWORD;
    Dr1: DWORD;
    Dr2: DWORD;
    Dr3: DWORD;
    Dr6: DWORD;
    Dr7: DWORD;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_FLOATING_POINT.
    //

    FloatSave: FLOATING_SAVE_AREA;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_SEGMENTS.
    //

    SegGs: DWORD;
    SegFs: DWORD;
    SegEs: DWORD;
    SegDs: DWORD;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_INTEGER.
    //

    Edi: DWORD;
    Esi: DWORD;
    Ebx: DWORD;
    Edx: DWORD;
    Ecx: DWORD;
    Eax: DWORD;

    //
    // This section is specified/returned if the
    // ContextFlags word contians the flag CONTEXT_CONTROL.
    //

    Ebp: DWORD;
    Eip: DWORD;
    SegCs: DWORD;              // MUST BE SANITIZED
    EFlags: DWORD;             // MUST BE SANITIZED
    Esp: DWORD;
    SegSs: DWORD;

    //
    // This section is specified/returned if the ContextFlags word
    // contains the flag CONTEXT_EXTENDED_REGISTERS.
    // The format and contexts are processor specific
    //

    ExtendedRegisters: array [0..MAXIMUM_SUPPORTED_EXTENSION - 1] of BYTE;
  end;
  {$EXTERNALSYM _CONTEXT}
  CONTEXT = _CONTEXT;
  {$EXTERNALSYM CONTEXT}
  TContext = CONTEXT;

const
  LDTENTRY_FLAGS1_TYPE        = $1F;
  LDTENTRY_FLAGS1_DPL         = $60;
  LDTENTRY_FLAGS1_PRES        = $80;

  LDTENTRY_FLAGS2_LIMITHI     = $0F;
  LDTENTRY_FLAGS2_SYS         = $10;
  LDTENTRY_FLAGS2_RESERVED_0  = $20;
  LDTENTRY_FLAGS2_DEFAULT_BIG = $40;
  LDTENTRY_FLAGS2_GRANULARITY = $80;

type
  PLDT_ENTRY = ^LDT_ENTRY;
  {$EXTERNALSYM PLDT_ENTRY}
  _LDT_ENTRY = record
    LimitLow: WORD;
    BaseLow: WORD;
    BaseMid: BYTE;
    Flags1: BYTE;     // Declare as bytes to avoid alignment
    Flags2: BYTE;     // Problems.
    BaseHi: BYTE;
  end;
  {$EXTERNALSYM _LDT_ENTRY}
  LDT_ENTRY = _LDT_ENTRY;
  {$EXTERNALSYM LDT_ENTRY}
  TLdtEntry = LDT_ENTRY;
  PLdtEntry = PLDT_ENTRY;

// Please contact INTEL to get IA64-specific information

const
  EXCEPTION_NONCONTINUABLE     = $1; // Noncontinuable exception
  {$EXTERNALSYM EXCEPTION_NONCONTINUABLE}
  EXCEPTION_MAXIMUM_PARAMETERS = 15; // maximum number of exception parameters
  {$EXTERNALSYM EXCEPTION_MAXIMUM_PARAMETERS}

//
// Exception record definition.
//

type
  PEXCEPTION_RECORD = ^EXCEPTION_RECORD;
  {$EXTERNALSYM PEXCEPTION_RECORD}
  _EXCEPTION_RECORD = record
    ExceptionCode: DWORD;
    ExceptionFlags: DWORD;
    ExceptionRecord: PEXCEPTION_RECORD;
    ExceptionAddress: Pointer;
    NumberParameters: DWORD;
    ExceptionInformation: array [0..EXCEPTION_MAXIMUM_PARAMETERS - 1] of ULONG_PTR;
  end;
  {$EXTERNALSYM _EXCEPTION_RECORD}
  EXCEPTION_RECORD = _EXCEPTION_RECORD;
  {$EXTERNALSYM EXCEPTION_RECORD}
  TExceptionRecord = EXCEPTION_RECORD;
  PExceptionRecord = PEXCEPTION_RECORD;

  PEXCEPTION_RECORD32 = ^EXCEPTION_RECORD32;
  {$EXTERNALSYM PEXCEPTION_RECORD32}
  _EXCEPTION_RECORD32 = record
    ExceptionCode: DWORD;
    ExceptionFlags: DWORD;
    ExceptionRecord: DWORD;
    ExceptionAddress: DWORD;
    NumberParameters: DWORD;
    ExceptionInformation: array [0..EXCEPTION_MAXIMUM_PARAMETERS - 1] of DWORD;
  end;
  {$EXTERNALSYM _EXCEPTION_RECORD32}
  EXCEPTION_RECORD32 = _EXCEPTION_RECORD32;
  {$EXTERNALSYM EXCEPTION_RECORD32}
  TExceptionRecord32 = EXCEPTION_RECORD32;
  PExceptionRecord32 = PEXCEPTION_RECORD32;

  PEXCEPTION_RECORD64 = ^EXCEPTION_RECORD64;
  {$EXTERNALSYM PEXCEPTION_RECORD64}
  _EXCEPTION_RECORD64 = record
    ExceptionCode: DWORD;
    ExceptionFlags: DWORD;
    ExceptionRecord: DWORD64;
    ExceptionAddress: DWORD64;
    NumberParameters: DWORD;
    __unusedAlignment: DWORD;
    ExceptionInformation: array [0..EXCEPTION_MAXIMUM_PARAMETERS - 1] of DWORD64;
  end;
  {$EXTERNALSYM _EXCEPTION_RECORD64}
  EXCEPTION_RECORD64 = _EXCEPTION_RECORD64;
  {$EXTERNALSYM EXCEPTION_RECORD64}
  TExceptionRecord64 = EXCEPTION_RECORD64;
  PExceptionRecord64 = PEXCEPTION_RECORD64;

//
// Typedef for pointer returned by exception_info()
//

  PEXCEPTION_POINTERS = ^EXCEPTION_POINTERS;
  {$EXTERNALSYM PEXCEPTION_POINTERS}
  _EXCEPTION_POINTERS = record
    ExceptionRecord: PEXCEPTION_RECORD;
    ContextRecord: PCONTEXT;
  end;
  {$EXTERNALSYM _EXCEPTION_POINTERS}
  EXCEPTION_POINTERS = _EXCEPTION_POINTERS;
  {$EXTERNALSYM EXCEPTION_POINTERS}
  TExceptionPointers = EXCEPTION_POINTERS;
  PExceptionPointers = ^TExceptionPointers;

  PACCESS_TOKEN = Pointer;
  {$EXTERNALSYM PACCESS_TOKEN}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                             ACCESS MASK                            //
//                                                                    //
////////////////////////////////////////////////////////////////////////

//
//  Define the access mask as a longword sized structure divided up as
//  follows:
//
//       3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//       1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//      +---------------+---------------+-------------------------------+
//      |G|G|G|G|Res'd|A| StandardRights|         SpecificRights        |
//      |R|W|E|A|     |S|               |                               |
//      +-+-------------+---------------+-------------------------------+
//
//      typedef struct _ACCESS_MASK {
//          WORD   SpecificRights;
//          BYTE  StandardRights;
//          BYTE  AccessSystemAcl : 1;
//          BYTE  Reserved : 3;
//          BYTE  GenericAll : 1;
//          BYTE  GenericExecute : 1;
//          BYTE  GenericWrite : 1;
//          BYTE  GenericRead : 1;
//      } ACCESS_MASK;
//      typedef ACCESS_MASK *PACCESS_MASK;
//
//  but to make life simple for programmer's we'll allow them to specify
//  a desired access mask by simply OR'ing together mulitple single rights
//  and treat an access mask as a DWORD.  For example
//
//      DesiredAccess = DELETE | READ_CONTROL
//
//  So we'll declare ACCESS_MASK as DWORD
//

type
  ACCESS_MASK = DWORD;
  {$EXTERNALSYM ACCESS_MASK}
  PACCESS_MASK = ^ACCESS_MASK;
  {$EXTERNALSYM PACCESS_MASK}
  TAccessMask = ACCESS_MASK;
  PAccessMask = PACCESS_MASK;  

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                             ACCESS TYPES                           //
//                                                                    //
////////////////////////////////////////////////////////////////////////


//
//  The following are masks for the predefined standard access types
//

const
  DELETE                   = ($00010000);
  {$EXTERNALSYM DELETE}
  READ_CONTROL             = ($00020000);
  {$EXTERNALSYM READ_CONTROL}
  WRITE_DAC                = ($00040000);
  {$EXTERNALSYM WRITE_DAC}
  WRITE_OWNER              = ($00080000);
  {$EXTERNALSYM WRITE_OWNER}
  SYNCHRONIZE              = ($00100000);
  {$EXTERNALSYM SYNCHRONIZE}

  STANDARD_RIGHTS_REQUIRED = ($000F0000);
  {$EXTERNALSYM STANDARD_RIGHTS_REQUIRED}

  STANDARD_RIGHTS_READ     = (READ_CONTROL);
  {$EXTERNALSYM STANDARD_RIGHTS_READ}
  STANDARD_RIGHTS_WRITE    = (READ_CONTROL);
  {$EXTERNALSYM STANDARD_RIGHTS_WRITE}
  STANDARD_RIGHTS_EXECUTE  = (READ_CONTROL);
  {$EXTERNALSYM STANDARD_RIGHTS_EXECUTE}

  STANDARD_RIGHTS_ALL      = ($001F0000);
  {$EXTERNALSYM STANDARD_RIGHTS_ALL}
  SPECIFIC_RIGHTS_ALL      = ($0000FFFF);
  {$EXTERNALSYM SPECIFIC_RIGHTS_ALL}

//
// AccessSystemAcl access type
//

  ACCESS_SYSTEM_SECURITY = ($01000000);
  {$EXTERNALSYM ACCESS_SYSTEM_SECURITY}

//
// MaximumAllowed access type
//

  MAXIMUM_ALLOWED = ($02000000);
  {$EXTERNALSYM MAXIMUM_ALLOWED}

//
//  These are the generic rights.
//

  GENERIC_READ    = DWORD($80000000);
  {$EXTERNALSYM GENERIC_READ}
  GENERIC_WRITE   = ($40000000);
  {$EXTERNALSYM GENERIC_WRITE}
  GENERIC_EXECUTE = ($20000000);
  {$EXTERNALSYM GENERIC_EXECUTE}
  GENERIC_ALL     = ($10000000);
  {$EXTERNALSYM GENERIC_ALL}

//
//  Define the generic mapping array.  This is used to denote the
//  mapping of each generic access right to a specific access mask.
//

type
  PGENERIC_MAPPING = ^GENERIC_MAPPING;
  {$EXTERNALSYM PGENERIC_MAPPING}
  _GENERIC_MAPPING = record
    GenericRead: ACCESS_MASK;
    GenericWrite: ACCESS_MASK;
    GenericExecute: ACCESS_MASK;
    GenericAll: ACCESS_MASK;
  end;
  {$EXTERNALSYM _GENERIC_MAPPING}
  GENERIC_MAPPING = _GENERIC_MAPPING;
  {$EXTERNALSYM GENERIC_MAPPING}
  TGenericMapping = GENERIC_MAPPING;
  PGenericMapping = PGENERIC_MAPPING;

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                        LUID_AND_ATTRIBUTES                         //
//                                                                    //
////////////////////////////////////////////////////////////////////////
//
//

//#include <pshpack4.h>

  PLUID_AND_ATTRIBUTES = ^LUID_AND_ATTRIBUTES;
  {$EXTERNALSYM PLUID_AND_ATTRIBUTES}
  _LUID_AND_ATTRIBUTES = record
    Luid: LUID;
    Attributes: DWORD;
  end;
  {$EXTERNALSYM _LUID_AND_ATTRIBUTES}
  LUID_AND_ATTRIBUTES = _LUID_AND_ATTRIBUTES;
  {$EXTERNALSYM LUID_AND_ATTRIBUTES}
  TLuidAndAttributes = LUID_AND_ATTRIBUTES;
  PLuidAndAttributes = PLUID_AND_ATTRIBUTES;

  LUID_AND_ATTRIBUTES_ARRAY = array [0..ANYSIZE_ARRAY - 1] of LUID_AND_ATTRIBUTES;
  {$EXTERNALSYM LUID_AND_ATTRIBUTES_ARRAY}
  PLUID_AND_ATTRIBUTES_ARRAY = ^LUID_AND_ATTRIBUTES_ARRAY;
  {$EXTERNALSYM PLUID_AND_ATTRIBUTES_ARRAY}
  TLuidAndAttributesArray = LUID_AND_ATTRIBUTES_ARRAY;
  PLuidAndAttributesArray = ^TLuidAndAttributesArray;

//#include <poppack.h>

////////////////////////////////////////////////////////////////////////
//                                                                    //
//              Security Id     (SID)                                 //
//                                                                    //
////////////////////////////////////////////////////////////////////////
//
//
// Pictorially the structure of an SID is as follows:
//
//         1   1   1   1   1   1
//         5   4   3   2   1   0   9   8   7   6   5   4   3   2   1   0
//      +---------------------------------------------------------------+
//      |      SubAuthorityCount        |Reserved1 (SBZ)|   Revision    |
//      +---------------------------------------------------------------+
//      |                   IdentifierAuthority[0]                      |
//      +---------------------------------------------------------------+
//      |                   IdentifierAuthority[1]                      |
//      +---------------------------------------------------------------+
//      |                   IdentifierAuthority[2]                      |
//      +---------------------------------------------------------------+
//      |                                                               |
//      +- -  -  -  -  -  -  -  SubAuthority[]  -  -  -  -  -  -  -  - -+
//      |                                                               |
//      +---------------------------------------------------------------+
//
//

type
  PSID_IDENTIFIER_AUTHORITY = ^SID_IDENTIFIER_AUTHORITY;
  {$EXTERNALSYM PSID_IDENTIFIER_AUTHORITY}
  _SID_IDENTIFIER_AUTHORITY = record
    Value: array [0..5] of Byte;
  end;
  {$EXTERNALSYM _SID_IDENTIFIER_AUTHORITY}
  SID_IDENTIFIER_AUTHORITY = _SID_IDENTIFIER_AUTHORITY;
  {$EXTERNALSYM SID_IDENTIFIER_AUTHORITY}
  TSidIdentifierAuthority = SID_IDENTIFIER_AUTHORITY;
  PSidIdentifierAuthority = PSID_IDENTIFIER_AUTHORITY;

  PSid = ^SID;
  _SID = record
    Revision: Byte;
    SubAuthorityCount: Byte;
    IdentifierAuthority: SID_IDENTIFIER_AUTHORITY;
    SubAuthority: array [0..ANYSIZE_ARRAY - 1] of DWORD;
  end;
  {$EXTERNALSYM _SID}
  SID = _SID;
  {$EXTERNALSYM SID}
  PPSID = ^PSID;
  {$NODEFINE PPSID}
  TSid = SID;

const
  SID_REVISION                    = (1); // Current revision level
  {$EXTERNALSYM SID_REVISION}
  SID_MAX_SUB_AUTHORITIES         = (15);
  {$EXTERNALSYM SID_MAX_SUB_AUTHORITIES}
  SID_RECOMMENDED_SUB_AUTHORITIES = (1); // Will change to around 6 in a future release.
  {$EXTERNALSYM SID_RECOMMENDED_SUB_AUTHORITIES}

  SECURITY_MAX_SID_SIZE = SizeOf(SID) - SizeOf(DWORD) + (SID_MAX_SUB_AUTHORITIES * SizeOf(DWORD));
  {$EXTERNALSYM SECURITY_MAX_SID_SIZE}

  SidTypeUser           = 1;
  {$EXTERNALSYM SidTypeUser}
  SidTypeGroup          = 2;
  {$EXTERNALSYM SidTypeGroup}
  SidTypeDomain         = 3;
  {$EXTERNALSYM SidTypeDomain}
  SidTypeAlias          = 4;
  {$EXTERNALSYM SidTypeAlias}
  SidTypeWellKnownGroup = 5;
  {$EXTERNALSYM SidTypeWellKnownGroup}
  SidTypeDeletedAccount = 6;
  {$EXTERNALSYM SidTypeDeletedAccount}
  SidTypeInvalid        = 7;
  {$EXTERNALSYM SidTypeInvalid}
  SidTypeUnknown        = 8;
  {$EXTERNALSYM SidTypeUnknown}
  SidTypeComputer       = 9;
  {$EXTERNALSYM SidTypeComputer}

type
  _SID_NAME_USE = DWORD;
  {$EXTERNALSYM _SID_NAME_USE}
  SID_NAME_USE = _SID_NAME_USE;
  {$EXTERNALSYM SID_NAME_USE}
  PSID_NAME_USE = ^SID_NAME_USE;
  {$EXTERNALSYM PSID_NAME_USE}
  TSidNameUse = SID_NAME_USE;
  PSidNameUSe = PSID_NAME_USE;

  PSID_AND_ATTRIBUTES = ^SID_AND_ATTRIBUTES;
  {$EXTERNALSYM PSID_AND_ATTRIBUTES}
  _SID_AND_ATTRIBUTES = record
    Sid: PSID;
    Attributes: DWORD;
  end;
  {$EXTERNALSYM _SID_AND_ATTRIBUTES}
  SID_AND_ATTRIBUTES = _SID_AND_ATTRIBUTES;
  {$EXTERNALSYM SID_AND_ATTRIBUTES}
  TSidAndAttributes = SID_AND_ATTRIBUTES;
  PSidAndAttributes = PSID_AND_ATTRIBUTES;

  SID_AND_ATTRIBUTES_ARRAY = array [0..ANYSIZE_ARRAY - 1] of SID_AND_ATTRIBUTES;
  {$EXTERNALSYM SID_AND_ATTRIBUTES_ARRAY}
  PSID_AND_ATTRIBUTES_ARRAY = ^SID_AND_ATTRIBUTES_ARRAY;
  {$EXTERNALSYM PSID_AND_ATTRIBUTES_ARRAY}
  PSidAndAttributesArray = ^TSidAndAttributesArray;
  TSidAndAttributesArray = SID_AND_ATTRIBUTES_ARRAY;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Universal well-known SIDs                                               //
//                                                                         //
//     Null SID                     S-1-0-0                                //
//     World                        S-1-1-0                                //
//     Local                        S-1-2-0                                //
//     Creator Owner ID             S-1-3-0                                //
//     Creator Group ID             S-1-3-1                                //
//     Creator Owner Server ID      S-1-3-2                                //
//     Creator Group Server ID      S-1-3-3                                //
//                                                                         //
//     (Non-unique IDs)             S-1-4                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

const
  SECURITY_NULL_SID_AUTHORITY: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 0));
  {$EXTERNALSYM SECURITY_NULL_SID_AUTHORITY}
  SECURITY_WORLD_SID_AUTHORITY: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 1));
  {$EXTERNALSYM SECURITY_WORLD_SID_AUTHORITY}
  SECURITY_LOCAL_SID_AUTHORITY: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 2));
  {$EXTERNALSYM SECURITY_LOCAL_SID_AUTHORITY}
  SECURITY_CREATOR_SID_AUTHORITY: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 3));
  {$EXTERNALSYM SECURITY_CREATOR_SID_AUTHORITY}
  SECURITY_NON_UNIQUE_AUTHORITY: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 4));
  {$EXTERNALSYM SECURITY_NON_UNIQUE_AUTHORITY}
  SECURITY_RESOURCE_MANAGER_AUTHORITY: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 9));
  {$EXTERNALSYM SECURITY_RESOURCE_MANAGER_AUTHORITY}

  SECURITY_NULL_RID                 = ($00000000);
  {$EXTERNALSYM SECURITY_NULL_RID}
  SECURITY_WORLD_RID                = ($00000000);
  {$EXTERNALSYM SECURITY_WORLD_RID}
  SECURITY_LOCAL_RID                = ($00000000);
  {$EXTERNALSYM SECURITY_LOCAL_RID}

  SECURITY_CREATOR_OWNER_RID        = ($00000000);
  {$EXTERNALSYM SECURITY_CREATOR_OWNER_RID}
  SECURITY_CREATOR_GROUP_RID        = ($00000001);
  {$EXTERNALSYM SECURITY_CREATOR_GROUP_RID}

  SECURITY_CREATOR_OWNER_SERVER_RID = ($00000002);
  {$EXTERNALSYM SECURITY_CREATOR_OWNER_SERVER_RID}
  SECURITY_CREATOR_GROUP_SERVER_RID = ($00000003);
  {$EXTERNALSYM SECURITY_CREATOR_GROUP_SERVER_RID}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// NT well-known SIDs                                                        //
//                                                                           //
//     NT Authority            S-1-5                                         //
//     Dialup                  S-1-5-1                                       //
//                                                                           //
//     Network                 S-1-5-2                                       //
//     Batch                   S-1-5-3                                       //
//     Interactive             S-1-5-4                                       //
//     (Logon IDs)             S-1-5-5-X-Y                                   //
//     Service                 S-1-5-6                                       //
//     AnonymousLogon          S-1-5-7       (aka null logon session)        //
//     Proxy                   S-1-5-8                                       //
//     Enterprise DC (EDC)     S-1-5-9       (aka domain controller account) //
//     Self                    S-1-5-10      (self RID)                      //
//     Authenticated User      S-1-5-11      (Authenticated user somewhere)  //
//     Restricted Code         S-1-5-12      (Running restricted code)       //
//     Terminal Server         S-1-5-13      (Running on Terminal Server)    //
//     Remote Logon            S-1-5-14      (Remote Interactive Logon)      //
//     This Organization       S-1-5-15                                      //
//                                                                           //
//     Local System            S-1-5-18                                      //
//     Local Service           S-1-5-19                                      //
//     Network Service         S-1-5-20                                      //
//                                                                           //
//     (NT non-unique IDs)     S-1-5-0x15-... (NT Domain Sids)               //
//                                                                           //
//     (Built-in domain)       S-1-5-0x20                                    //
//                                                                           //
//     (Security Package IDs)  S-1-5-0x40                                    //
//     NTLM Authentication     S-1-5-0x40-10                                 //
//     SChannel Authentication S-1-5-0x40-14                                 //
//     Digest Authentication   S-1-5-0x40-21                                 //
//                                                                           //
//     Other Organization      S-1-5-1000    (>=1000 can not be filtered)    //
//                                                                           //
//                                                                           //
// NOTE: the relative identifier values (RIDs) determine which security      //
//       boundaries the SID is allowed to cross.  Before adding new RIDs,    //
//       a determination needs to be made regarding which range they should  //
//       be added to in order to ensure proper "SID filtering"               //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

const
  SECURITY_NT_AUTHORITY: TSidIdentifierAuthority = (Value: (0, 0, 0, 0, 0, 5));
  {$EXTERNALSYM SECURITY_NT_AUTHORITY}

  SECURITY_DIALUP_RID                 = ($00000001);
  {$EXTERNALSYM SECURITY_DIALUP_RID}
  SECURITY_NETWORK_RID                = ($00000002);
  {$EXTERNALSYM SECURITY_NETWORK_RID}
  SECURITY_BATCH_RID                  = ($00000003);
  {$EXTERNALSYM SECURITY_BATCH_RID}
  SECURITY_INTERACTIVE_RID            = ($00000004);
  {$EXTERNALSYM SECURITY_INTERACTIVE_RID}
  SECURITY_LOGON_IDS_RID              = ($00000005);
  {$EXTERNALSYM SECURITY_LOGON_IDS_RID}
  SECURITY_LOGON_IDS_RID_COUNT        = (3);
  {$EXTERNALSYM SECURITY_LOGON_IDS_RID_COUNT}
  SECURITY_SERVICE_RID                = ($00000006);
  {$EXTERNALSYM SECURITY_SERVICE_RID}
  SECURITY_ANONYMOUS_LOGON_RID        = ($00000007);
  {$EXTERNALSYM SECURITY_ANONYMOUS_LOGON_RID}
  SECURITY_PROXY_RID                  = ($00000008);
  {$EXTERNALSYM SECURITY_PROXY_RID}
  SECURITY_ENTERPRISE_CONTROLLERS_RID = ($00000009);
  {$EXTERNALSYM SECURITY_ENTERPRISE_CONTROLLERS_RID}
  SECURITY_SERVER_LOGON_RID           = SECURITY_ENTERPRISE_CONTROLLERS_RID;
  {$EXTERNALSYM SECURITY_SERVER_LOGON_RID}
  SECURITY_PRINCIPAL_SELF_RID         = ($0000000A);
  {$EXTERNALSYM SECURITY_PRINCIPAL_SELF_RID}
  SECURITY_AUTHENTICATED_USER_RID     = ($0000000B);
  {$EXTERNALSYM SECURITY_AUTHENTICATED_USER_RID}
  SECURITY_RESTRICTED_CODE_RID        = ($0000000C);
  {$EXTERNALSYM SECURITY_RESTRICTED_CODE_RID}
  SECURITY_TERMINAL_SERVER_RID        = ($0000000D);
  {$EXTERNALSYM SECURITY_TERMINAL_SERVER_RID}
  SECURITY_REMOTE_LOGON_RID           = ($0000000E);
  {$EXTERNALSYM SECURITY_REMOTE_LOGON_RID}
  SECURITY_THIS_ORGANIZATION_RID      = ($0000000F);
  {$EXTERNALSYM SECURITY_THIS_ORGANIZATION_RID}

  SECURITY_LOCAL_SYSTEM_RID    = ($00000012);
  {$EXTERNALSYM SECURITY_LOCAL_SYSTEM_RID}
  SECURITY_LOCAL_SERVICE_RID   = ($00000013);
  {$EXTERNALSYM SECURITY_LOCAL_SERVICE_RID}
  SECURITY_NETWORK_SERVICE_RID = ($00000014);
  {$EXTERNALSYM SECURITY_NETWORK_SERVICE_RID}

  SECURITY_NT_NON_UNIQUE       = ($00000015);
  {$EXTERNALSYM SECURITY_NT_NON_UNIQUE}
  SECURITY_NT_NON_UNIQUE_SUB_AUTH_COUNT = (3);
  {$EXTERNALSYM SECURITY_NT_NON_UNIQUE_SUB_AUTH_COUNT}

  SECURITY_BUILTIN_DOMAIN_RID  = ($00000020);
  {$EXTERNALSYM SECURITY_BUILTIN_DOMAIN_RID}

  SECURITY_PACKAGE_BASE_RID       = ($00000040);
  {$EXTERNALSYM SECURITY_PACKAGE_BASE_RID}
  SECURITY_PACKAGE_RID_COUNT      = (2);
  {$EXTERNALSYM SECURITY_PACKAGE_RID_COUNT}
  SECURITY_PACKAGE_NTLM_RID       = ($0000000A);
  {$EXTERNALSYM SECURITY_PACKAGE_NTLM_RID}
  SECURITY_PACKAGE_SCHANNEL_RID   = ($0000000E);
  {$EXTERNALSYM SECURITY_PACKAGE_SCHANNEL_RID}
  SECURITY_PACKAGE_DIGEST_RID     = ($00000015);
  {$EXTERNALSYM SECURITY_PACKAGE_DIGEST_RID}

  SECURITY_MAX_ALWAYS_FILTERED    = ($000003E7);
  {$EXTERNALSYM SECURITY_MAX_ALWAYS_FILTERED}
  SECURITY_MIN_NEVER_FILTERED     = ($000003E8);
  {$EXTERNALSYM SECURITY_MIN_NEVER_FILTERED}

  SECURITY_OTHER_ORGANIZATION_RID = ($000003E8);
  {$EXTERNALSYM SECURITY_OTHER_ORGANIZATION_RID}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// well-known domain relative sub-authority values (RIDs)...               //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

// Well-known users ...

  FOREST_USER_RID_MAX    = ($000001F3);
  {$EXTERNALSYM FOREST_USER_RID_MAX}

  DOMAIN_USER_RID_ADMIN  = ($000001F4);
  {$EXTERNALSYM DOMAIN_USER_RID_ADMIN}
  DOMAIN_USER_RID_GUEST  = ($000001F5);
  {$EXTERNALSYM DOMAIN_USER_RID_GUEST}
  DOMAIN_USER_RID_KRBTGT = ($000001F6);
  {$EXTERNALSYM DOMAIN_USER_RID_KRBTGT}

  DOMAIN_USER_RID_MAX    = ($000003E7);
  {$EXTERNALSYM DOMAIN_USER_RID_MAX}

// well-known groups ...

  DOMAIN_GROUP_RID_ADMINS            = ($00000200);
  {$EXTERNALSYM DOMAIN_GROUP_RID_ADMINS}
  DOMAIN_GROUP_RID_USERS             = ($00000201);
  {$EXTERNALSYM DOMAIN_GROUP_RID_USERS}
  DOMAIN_GROUP_RID_GUESTS            = ($00000202);
  {$EXTERNALSYM DOMAIN_GROUP_RID_GUESTS}
  DOMAIN_GROUP_RID_COMPUTERS         = ($00000203);
  {$EXTERNALSYM DOMAIN_GROUP_RID_COMPUTERS}
  DOMAIN_GROUP_RID_CONTROLLERS       = ($00000204);
  {$EXTERNALSYM DOMAIN_GROUP_RID_CONTROLLERS}
  DOMAIN_GROUP_RID_CERT_ADMINS       = ($00000205);
  {$EXTERNALSYM DOMAIN_GROUP_RID_CERT_ADMINS}
  DOMAIN_GROUP_RID_SCHEMA_ADMINS     = ($00000206);
  {$EXTERNALSYM DOMAIN_GROUP_RID_SCHEMA_ADMINS}
  DOMAIN_GROUP_RID_ENTERPRISE_ADMINS = ($00000207);
  {$EXTERNALSYM DOMAIN_GROUP_RID_ENTERPRISE_ADMINS}
  DOMAIN_GROUP_RID_POLICY_ADMINS     = ($00000208);
  {$EXTERNALSYM DOMAIN_GROUP_RID_POLICY_ADMINS}

// well-known aliases ...

  DOMAIN_ALIAS_RID_ADMINS           = ($00000220);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_ADMINS}
  DOMAIN_ALIAS_RID_USERS            = ($00000221);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_USERS}
  DOMAIN_ALIAS_RID_GUESTS           = ($00000222);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_GUESTS}
  DOMAIN_ALIAS_RID_POWER_USERS      = ($00000223);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_POWER_USERS}

  DOMAIN_ALIAS_RID_ACCOUNT_OPS      = ($00000224);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_ACCOUNT_OPS}
  DOMAIN_ALIAS_RID_SYSTEM_OPS       = ($00000225);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_SYSTEM_OPS}
  DOMAIN_ALIAS_RID_PRINT_OPS        = ($00000226);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_PRINT_OPS}
  DOMAIN_ALIAS_RID_BACKUP_OPS       = ($00000227);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_BACKUP_OPS}

  DOMAIN_ALIAS_RID_REPLICATOR       = ($00000228);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_REPLICATOR}
  DOMAIN_ALIAS_RID_RAS_SERVERS      = ($00000229);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_RAS_SERVERS}
  DOMAIN_ALIAS_RID_PREW2KCOMPACCESS = ($0000022A);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_PREW2KCOMPACCESS}
  DOMAIN_ALIAS_RID_REMOTE_DESKTOP_USERS = ($0000022B);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_REMOTE_DESKTOP_USERS}
  DOMAIN_ALIAS_RID_NETWORK_CONFIGURATION_OPS = ($0000022C);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_NETWORK_CONFIGURATION_OPS}
  DOMAIN_ALIAS_RID_INCOMING_FOREST_TRUST_BUILDERS = ($0000022D);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_INCOMING_FOREST_TRUST_BUILDERS}

  DOMAIN_ALIAS_RID_MONITORING_USERS      = ($0000022E);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_MONITORING_USERS}
  DOMAIN_ALIAS_RID_LOGGING_USERS         = ($0000022F);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_LOGGING_USERS}
  DOMAIN_ALIAS_RID_AUTHORIZATIONACCESS   = ($00000230);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_AUTHORIZATIONACCESS}
  DOMAIN_ALIAS_RID_TS_LICENSE_SERVERS    = ($00000231);
  {$EXTERNALSYM DOMAIN_ALIAS_RID_TS_LICENSE_SERVERS}

type
  WELL_KNOWN_SID_TYPE = (
    WinNullSid,
    WinWorldSid,
    WinLocalSid,
    WinCreatorOwnerSid,
    WinCreatorGroupSid,
    WinCreatorOwnerServerSid,
    WinCreatorGroupServerSid,
    WinNtAuthoritySid,
    WinDialupSid,
    WinNetworkSid,
    WinBatchSid,
    WinInteractiveSid,
    WinServiceSid,
    WinAnonymousSid,
    WinProxySid,
    WinEnterpriseControllersSid,
    WinSelfSid,
    WinAuthenticatedUserSid,
    WinRestrictedCodeSid,
    WinTerminalServerSid,
    WinRemoteLogonIdSid,
    WinLogonIdsSid,
    WinLocalSystemSid,
    WinLocalServiceSid,
    WinNetworkServiceSid,
    WinBuiltinDomainSid,
    WinBuiltinAdministratorsSid,
    WinBuiltinUsersSid,
    WinBuiltinGuestsSid,
    WinBuiltinPowerUsersSid,
    WinBuiltinAccountOperatorsSid,
    WinBuiltinSystemOperatorsSid,
    WinBuiltinPrintOperatorsSid,
    WinBuiltinBackupOperatorsSid,
    WinBuiltinReplicatorSid,
    WinBuiltinPreWindows2000CompatibleAccessSid,
    WinBuiltinRemoteDesktopUsersSid,
    WinBuiltinNetworkConfigurationOperatorsSid,
    WinAccountAdministratorSid,
    WinAccountGuestSid,
    WinAccountKrbtgtSid,
    WinAccountDomainAdminsSid,
    WinAccountDomainUsersSid,
    WinAccountDomainGuestsSid,
    WinAccountComputersSid,
    WinAccountControllersSid,
    WinAccountCertAdminsSid,
    WinAccountSchemaAdminsSid,
    WinAccountEnterpriseAdminsSid,
    WinAccountPolicyAdminsSid,
    WinAccountRasAndIasServersSid,
    WinNTLMAuthenticationSid,
    WinDigestAuthenticationSid,
    WinSChannelAuthenticationSid,
    WinThisOrganizationSid,
    WinOtherOrganizationSid,
    WinBuiltinIncomingForestTrustBuildersSid,
    WinBuiltinPerfMonitoringUsersSid,
    WinBuiltinPerfLoggingUsersSid,
    WinBuiltinAuthorizationAccessSid,
    WinBuiltinTerminalServerLicenseServersSid);
  {$EXTERNALSYM WELL_KNOWN_SID_TYPE}
  TWellKnownSidType = WELL_KNOWN_SID_TYPE;

//
// Allocate the System Luid.  The first 1000 LUIDs are reserved.
// Use #999 here (0x3E7 = 999)
//

const
  SYSTEM_LUID: LUID = (LowPart: $3E7; HighPart: $0);
  {$EXTERNALSYM SYSTEM_LUID}
  ANONYMOUS_LOGON_LUID: LUID = (LowPart: $3E6; HighPart: $0);
  {$EXTERNALSYM ANONYMOUS_LOGON_LUID}
  LOCALSERVICE_LUID: LUID = (LowPart: $3E5; HighPart: $0);
  {$EXTERNALSYM LOCALSERVICE_LUID}
  NETWORKSERVICE_LUID: LUID = (LowPart: $3E4; HighPart: $0);
  {$EXTERNALSYM NETWORKSERVICE_LUID}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                          User and Group related SID attributes     //
//                                                                    //
////////////////////////////////////////////////////////////////////////

//
// Group attributes
//

  SE_GROUP_MANDATORY          = ($00000001);
  {$EXTERNALSYM SE_GROUP_MANDATORY}
  SE_GROUP_ENABLED_BY_DEFAULT = ($00000002);
  {$EXTERNALSYM SE_GROUP_ENABLED_BY_DEFAULT}
  SE_GROUP_ENABLED            = ($00000004);
  {$EXTERNALSYM SE_GROUP_ENABLED}
  SE_GROUP_OWNER              = ($00000008);
  {$EXTERNALSYM SE_GROUP_OWNER}
  SE_GROUP_USE_FOR_DENY_ONLY  = ($00000010);
  {$EXTERNALSYM SE_GROUP_USE_FOR_DENY_ONLY}
  SE_GROUP_LOGON_ID           = ($C0000000);
  {$EXTERNALSYM SE_GROUP_LOGON_ID}
  SE_GROUP_RESOURCE           = ($20000000);
  {$EXTERNALSYM SE_GROUP_RESOURCE}

//
// User attributes
//

// (None yet defined.)

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                         ACL  and  ACE                              //
//                                                                    //
////////////////////////////////////////////////////////////////////////

//
//  Define an ACL and the ACE format.  The structure of an ACL header
//  followed by one or more ACEs.  Pictorally the structure of an ACL header
//  is as follows:
//
//       3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//       1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//      +-------------------------------+---------------+---------------+
//      |            AclSize            |      Sbz1     |  AclRevision  |
//      +-------------------------------+---------------+---------------+
//      |              Sbz2             |           AceCount            |
//      +-------------------------------+-------------------------------+
//
//  The current AclRevision is defined to be ACL_REVISION.
//
//  AclSize is the size, in bytes, allocated for the ACL.  This includes
//  the ACL header, ACES, and remaining free space in the buffer.
//
//  AceCount is the number of ACES in the ACL.
//

// This is the *current* ACL revision

  ACL_REVISION    = (2);
  {$EXTERNALSYM ACL_REVISION}
  ACL_REVISION_DS = (4);
  {$EXTERNALSYM ACL_REVISION_DS}

// This is the history of ACL revisions.  Add a new one whenever
// ACL_REVISION is updated

  ACL_REVISION1    = (1);
  {$EXTERNALSYM ACL_REVISION1}
  ACL_REVISION2    = (2);
  {$EXTERNALSYM ACL_REVISION2}
  MIN_ACL_REVISION = ACL_REVISION2;
  {$EXTERNALSYM MIN_ACL_REVISION}
  ACL_REVISION3    = (3);
  {$EXTERNALSYM ACL_REVISION3}
  ACL_REVISION4    = (4);
  {$EXTERNALSYM ACL_REVISION4}
  MAX_ACL_REVISION = ACL_REVISION4;
  {$EXTERNALSYM MAX_ACL_REVISION}

type
  PACL = ^ACL;
  {$EXTERNALSYM PACL}
  _ACL = record
    AclRevision: Byte;
    Sbz1: Byte;
    AclSize: Word;
    AceCount: Word;
    Sbz2: Word;
  end;
  {$EXTERNALSYM _ACL}
  ACL = _ACL;
  {$EXTERNALSYM ACL}
  TAcl = ACL;

  PPACL = ^PAcl;
  {$NODEFINE PPACL}

//
//  The structure of an ACE is a common ace header followed by ace type
//  specific data.  Pictorally the structure of the common ace header is
//  as follows:
//
//       3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//       1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//      +---------------+-------+-------+---------------+---------------+
//      |            AceSize            |    AceFlags   |     AceType   |
//      +---------------+-------+-------+---------------+---------------+
//
//  AceType denotes the type of the ace, there are some predefined ace
//  types
//
//  AceSize is the size, in bytes, of ace.
//
//  AceFlags are the Ace flags for audit and inheritance, defined shortly.

type
  PACE_HEADER = ^ACE_HEADER;
  {$EXTERNALSYM PACE_HEADER}
  _ACE_HEADER = record
    AceType: Byte;
    AceFlags: Byte;
    AceSize: Word;
  end;
  {$EXTERNALSYM _ACE_HEADER}
  ACE_HEADER = _ACE_HEADER;
  {$EXTERNALSYM ACE_HEADER}
  TAceHeader = ACE_HEADER;
  PAceHeader = PACE_HEADER;

//
//  The following are the predefined ace types that go into the AceType
//  field of an Ace header.
//

const
  ACCESS_MIN_MS_ACE_TYPE    = ($0);
  {$EXTERNALSYM ACCESS_MIN_MS_ACE_TYPE}
  ACCESS_ALLOWED_ACE_TYPE   = ($0);
  {$EXTERNALSYM ACCESS_ALLOWED_ACE_TYPE}
  ACCESS_DENIED_ACE_TYPE    = ($1);
  {$EXTERNALSYM ACCESS_DENIED_ACE_TYPE}
  SYSTEM_AUDIT_ACE_TYPE     = ($2);
  {$EXTERNALSYM SYSTEM_AUDIT_ACE_TYPE}
  SYSTEM_ALARM_ACE_TYPE     = ($3);
  {$EXTERNALSYM SYSTEM_ALARM_ACE_TYPE}
  ACCESS_MAX_MS_V2_ACE_TYPE = ($3);
  {$EXTERNALSYM ACCESS_MAX_MS_V2_ACE_TYPE}

  ACCESS_ALLOWED_COMPOUND_ACE_TYPE = ($4);
  {$EXTERNALSYM ACCESS_ALLOWED_COMPOUND_ACE_TYPE}
  ACCESS_MAX_MS_V3_ACE_TYPE        = ($4);
  {$EXTERNALSYM ACCESS_MAX_MS_V3_ACE_TYPE}

  ACCESS_MIN_MS_OBJECT_ACE_TYPE  = ($5);
  {$EXTERNALSYM ACCESS_MIN_MS_OBJECT_ACE_TYPE}
  ACCESS_ALLOWED_OBJECT_ACE_TYPE = ($5);
  {$EXTERNALSYM ACCESS_ALLOWED_OBJECT_ACE_TYPE}
  ACCESS_DENIED_OBJECT_ACE_TYPE  = ($6);
  {$EXTERNALSYM ACCESS_DENIED_OBJECT_ACE_TYPE}
  SYSTEM_AUDIT_OBJECT_ACE_TYPE   = ($7);
  {$EXTERNALSYM SYSTEM_AUDIT_OBJECT_ACE_TYPE}
  SYSTEM_ALARM_OBJECT_ACE_TYPE   = ($8);
  {$EXTERNALSYM SYSTEM_ALARM_OBJECT_ACE_TYPE}
  ACCESS_MAX_MS_OBJECT_ACE_TYPE  = ($8);
  {$EXTERNALSYM ACCESS_MAX_MS_OBJECT_ACE_TYPE}

  ACCESS_MAX_MS_V4_ACE_TYPE = ($8);
  {$EXTERNALSYM ACCESS_MAX_MS_V4_ACE_TYPE}
  ACCESS_MAX_MS_ACE_TYPE    = ($8);
  {$EXTERNALSYM ACCESS_MAX_MS_ACE_TYPE}

  ACCESS_ALLOWED_CALLBACK_ACE_TYPE        = $9;
  {$EXTERNALSYM ACCESS_ALLOWED_CALLBACK_ACE_TYPE}
  ACCESS_DENIED_CALLBACK_ACE_TYPE         = $A;
  {$EXTERNALSYM ACCESS_DENIED_CALLBACK_ACE_TYPE}
  ACCESS_ALLOWED_CALLBACK_OBJECT_ACE_TYPE = $B;
  {$EXTERNALSYM ACCESS_ALLOWED_CALLBACK_OBJECT_ACE_TYPE}
  ACCESS_DENIED_CALLBACK_OBJECT_ACE_TYPE  = $C;
  {$EXTERNALSYM ACCESS_DENIED_CALLBACK_OBJECT_ACE_TYPE}
  SYSTEM_AUDIT_CALLBACK_ACE_TYPE          = $D;
  {$EXTERNALSYM SYSTEM_AUDIT_CALLBACK_ACE_TYPE}
  SYSTEM_ALARM_CALLBACK_ACE_TYPE          = $E;
  {$EXTERNALSYM SYSTEM_ALARM_CALLBACK_ACE_TYPE}
  SYSTEM_AUDIT_CALLBACK_OBJECT_ACE_TYPE   = $F;
  {$EXTERNALSYM SYSTEM_AUDIT_CALLBACK_OBJECT_ACE_TYPE}
  SYSTEM_ALARM_CALLBACK_OBJECT_ACE_TYPE   = $10;
  {$EXTERNALSYM SYSTEM_ALARM_CALLBACK_OBJECT_ACE_TYPE}

  ACCESS_MAX_MS_V5_ACE_TYPE               = $10;
  {$EXTERNALSYM ACCESS_MAX_MS_V5_ACE_TYPE}

//
//  The following are the inherit flags that go into the AceFlags field
//  of an Ace header.
//

  OBJECT_INHERIT_ACE       = ($1);
  {$EXTERNALSYM OBJECT_INHERIT_ACE}
  CONTAINER_INHERIT_ACE    = ($2);
  {$EXTERNALSYM CONTAINER_INHERIT_ACE}
  NO_PROPAGATE_INHERIT_ACE = ($4);
  {$EXTERNALSYM NO_PROPAGATE_INHERIT_ACE}
  INHERIT_ONLY_ACE         = ($8);
  {$EXTERNALSYM INHERIT_ONLY_ACE}
  INHERITED_ACE            = ($10);
  {$EXTERNALSYM INHERITED_ACE}
  VALID_INHERIT_FLAGS      = ($1F);
  {$EXTERNALSYM VALID_INHERIT_FLAGS}

//  The following are the currently defined ACE flags that go into the
//  AceFlags field of an ACE header.  Each ACE type has its own set of
//  AceFlags.
//
//  SUCCESSFUL_ACCESS_ACE_FLAG - used only with system audit and alarm ACE
//  types to indicate that a message is generated for successful accesses.
//
//  FAILED_ACCESS_ACE_FLAG - used only with system audit and alarm ACE types
//  to indicate that a message is generated for failed accesses.
//

//
//  SYSTEM_AUDIT and SYSTEM_ALARM AceFlags
//
//  These control the signaling of audit and alarms for success or failure.
//

  SUCCESSFUL_ACCESS_ACE_FLAG = ($40);
  {$EXTERNALSYM SUCCESSFUL_ACCESS_ACE_FLAG}
  FAILED_ACCESS_ACE_FLAG     = ($80);
  {$EXTERNALSYM FAILED_ACCESS_ACE_FLAG}

//
//  We'll define the structure of the predefined ACE types.  Pictorally
//  the structure of the predefined ACE's is as follows:
//
//       3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//       1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//      +---------------+-------+-------+---------------+---------------+
//      |    AceFlags   | Resd  |Inherit|    AceSize    |     AceType   |
//      +---------------+-------+-------+---------------+---------------+
//      |                              Mask                             |
//      +---------------------------------------------------------------+
//      |                                                               |
//      +                                                               +
//      |                                                               |
//      +                              Sid                              +
//      |                                                               |
//      +                                                               +
//      |                                                               |
//      +---------------------------------------------------------------+
//
//  Mask is the access mask associated with the ACE.  This is either the
//  access allowed, access denied, audit, or alarm mask.
//
//  Sid is the Sid associated with the ACE.
//

//  The following are the four predefined ACE types.

//  Examine the AceType field in the Header to determine
//  which structure is appropriate to use for casting.

type
  PACCESS_ALLOWED_ACE = ^ACCESS_ALLOWED_ACE;
  {$EXTERNALSYM PACCESS_ALLOWED_ACE}
  _ACCESS_ALLOWED_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _ACCESS_ALLOWED_ACE}
  ACCESS_ALLOWED_ACE = _ACCESS_ALLOWED_ACE;
  {$EXTERNALSYM ACCESS_ALLOWED_ACE}
  TAccessAllowedAce = ACCESS_ALLOWED_ACE;
  PAccessAllowedAce = PACCESS_ALLOWED_ACE;

  PACCESS_DENIED_ACE = ^ACCESS_DENIED_ACE;
  {$EXTERNALSYM PACCESS_DENIED_ACE}
  _ACCESS_DENIED_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _ACCESS_DENIED_ACE}
  ACCESS_DENIED_ACE = _ACCESS_DENIED_ACE;
  {$EXTERNALSYM ACCESS_DENIED_ACE}
  TAccessDeniedAce = ACCESS_DENIED_ACE;
  PAccessDeniedAce = PACCESS_DENIED_ACE;

  PSYSTEM_AUDIT_ACE = ^SYSTEM_AUDIT_ACE;
  {$EXTERNALSYM PSYSTEM_AUDIT_ACE}
  _SYSTEM_AUDIT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _SYSTEM_AUDIT_ACE}
  SYSTEM_AUDIT_ACE = _SYSTEM_AUDIT_ACE;
  {$EXTERNALSYM SYSTEM_AUDIT_ACE}
  TSystemAuditAce = SYSTEM_AUDIT_ACE;
  PSystemAuditAce = PSYSTEM_AUDIT_ACE;

  PSYSTEM_ALARM_ACE = ^SYSTEM_ALARM_ACE;
  {$EXTERNALSYM PSYSTEM_ALARM_ACE}
  _SYSTEM_ALARM_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _SYSTEM_ALARM_ACE}
  SYSTEM_ALARM_ACE = _SYSTEM_ALARM_ACE;
  {$EXTERNALSYM SYSTEM_ALARM_ACE}
  TSystemAlarmAce = SYSTEM_ALARM_ACE;
  PSystemAlarmAce = PSYSTEM_ALARM_ACE;

  PACCESS_ALLOWED_OBJECT_ACE = ^ACCESS_ALLOWED_OBJECT_ACE;
  {$EXTERNALSYM PACCESS_ALLOWED_OBJECT_ACE}
  _ACCESS_ALLOWED_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _ACCESS_ALLOWED_OBJECT_ACE}
  ACCESS_ALLOWED_OBJECT_ACE = _ACCESS_ALLOWED_OBJECT_ACE;
  {$EXTERNALSYM ACCESS_ALLOWED_OBJECT_ACE}
  TAccessAllowedObjectAce = ACCESS_ALLOWED_OBJECT_ACE;
  PAccessAllowedObjectAce = PACCESS_ALLOWED_OBJECT_ACE;

  PACCESS_DENIED_OBJECT_ACE = ^ACCESS_DENIED_OBJECT_ACE;
  {$EXTERNALSYM PACCESS_DENIED_OBJECT_ACE}
  _ACCESS_DENIED_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _ACCESS_DENIED_OBJECT_ACE}
  ACCESS_DENIED_OBJECT_ACE = _ACCESS_DENIED_OBJECT_ACE;
  {$EXTERNALSYM ACCESS_DENIED_OBJECT_ACE}
  TAccessDeniedObjectAce = ACCESS_DENIED_OBJECT_ACE;
  PAccessDeniedObjectAce = PACCESS_DENIED_OBJECT_ACE;

  PSYSTEM_AUDIT_OBJECT_ACE = ^SYSTEM_AUDIT_OBJECT_ACE;
  {$EXTERNALSYM PSYSTEM_AUDIT_OBJECT_ACE}
  _SYSTEM_AUDIT_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _SYSTEM_AUDIT_OBJECT_ACE}
  SYSTEM_AUDIT_OBJECT_ACE = _SYSTEM_AUDIT_OBJECT_ACE;
  {$EXTERNALSYM SYSTEM_AUDIT_OBJECT_ACE}
  TSystemAuditObjectAce = SYSTEM_AUDIT_OBJECT_ACE;
  PSystemAuditObjectAce = PSYSTEM_AUDIT_OBJECT_ACE;

  PSYSTEM_ALARM_OBJECT_ACE = ^SYSTEM_ALARM_OBJECT_ACE;
  {$EXTERNALSYM PSYSTEM_ALARM_OBJECT_ACE}
  _SYSTEM_ALARM_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
  end;
  {$EXTERNALSYM _SYSTEM_ALARM_OBJECT_ACE}
  SYSTEM_ALARM_OBJECT_ACE = _SYSTEM_ALARM_OBJECT_ACE;
  {$EXTERNALSYM SYSTEM_ALARM_OBJECT_ACE}
  TSystemAlarmObjectAce = SYSTEM_ALARM_OBJECT_ACE;
  PSystemAlarmObjectAce = PSYSTEM_ALARM_OBJECT_ACE;

//
// Callback ace support in post Win2000.
// Resource managers can put their own data after Sidstart + Length of the sid
//

  _ACCESS_ALLOWED_CALLBACK_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _ACCESS_ALLOWED_CALLBACK_ACE}
  ACCESS_ALLOWED_CALLBACK_ACE = _ACCESS_ALLOWED_CALLBACK_ACE;
  {$EXTERNALSYM ACCESS_ALLOWED_CALLBACK_ACE}
  PACCESS_ALLOWED_CALLBACK_ACE = ^ACCESS_ALLOWED_CALLBACK_ACE;
  {$EXTERNALSYM PACCESS_ALLOWED_CALLBACK_ACE}
  TAccessAllowedCallBackAce = ACCESS_ALLOWED_CALLBACK_ACE;
  PAccessAllowedCallBackAce = PACCESS_ALLOWED_CALLBACK_ACE;  

  _ACCESS_DENIED_CALLBACK_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _ACCESS_DENIED_CALLBACK_ACE}
  ACCESS_DENIED_CALLBACK_ACE = _ACCESS_DENIED_CALLBACK_ACE;
  {$EXTERNALSYM ACCESS_DENIED_CALLBACK_ACE}
  PACCESS_DENIED_CALLBACK_ACE = ^ACCESS_DENIED_CALLBACK_ACE;
  {$EXTERNALSYM PACCESS_DENIED_CALLBACK_ACE}
  TAccessDeniedCallBackAce = ACCESS_DENIED_CALLBACK_ACE;
  PAccessDeniedCallBackAce = PACCESS_DENIED_CALLBACK_ACE;

  _SYSTEM_AUDIT_CALLBACK_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _SYSTEM_AUDIT_CALLBACK_ACE}
  SYSTEM_AUDIT_CALLBACK_ACE = _SYSTEM_AUDIT_CALLBACK_ACE;
  {$EXTERNALSYM SYSTEM_AUDIT_CALLBACK_ACE}
  PSYSTEM_AUDIT_CALLBACK_ACE = ^SYSTEM_AUDIT_CALLBACK_ACE;
  {$EXTERNALSYM PSYSTEM_AUDIT_CALLBACK_ACE}
  TSystemAuditCallBackAce = SYSTEM_AUDIT_CALLBACK_ACE;
  PSystemAuditCallBackAce = PSYSTEM_AUDIT_CALLBACK_ACE;

  _SYSTEM_ALARM_CALLBACK_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _SYSTEM_ALARM_CALLBACK_ACE}
  SYSTEM_ALARM_CALLBACK_ACE = _SYSTEM_ALARM_CALLBACK_ACE;
  {$EXTERNALSYM SYSTEM_ALARM_CALLBACK_ACE}
  PSYSTEM_ALARM_CALLBACK_ACE = ^SYSTEM_ALARM_CALLBACK_ACE;
  {$EXTERNALSYM PSYSTEM_ALARM_CALLBACK_ACE}
  TSystemAlarmCallBackAce = SYSTEM_ALARM_CALLBACK_ACE;
  PSystemAlarmCallBackAce = PSYSTEM_ALARM_CALLBACK_ACE;

  _ACCESS_ALLOWED_CALLBACK_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _ACCESS_ALLOWED_CALLBACK_OBJECT_ACE}
  ACCESS_ALLOWED_CALLBACK_OBJECT_ACE = _ACCESS_ALLOWED_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM ACCESS_ALLOWED_CALLBACK_OBJECT_ACE}
  PACCESS_ALLOWED_CALLBACK_OBJECT_ACE = ^ACCESS_ALLOWED_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM PACCESS_ALLOWED_CALLBACK_OBJECT_ACE}
  TAccessAllowedCallBackObjectAce = ACCESS_ALLOWED_CALLBACK_OBJECT_ACE;
  PAccessAllowedCallBackObjectAce = PACCESS_ALLOWED_CALLBACK_OBJECT_ACE;

  _ACCESS_DENIED_CALLBACK_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _ACCESS_DENIED_CALLBACK_OBJECT_ACE}
  ACCESS_DENIED_CALLBACK_OBJECT_ACE = _ACCESS_DENIED_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM ACCESS_DENIED_CALLBACK_OBJECT_ACE}
  PACCESS_DENIED_CALLBACK_OBJECT_ACE = ^ACCESS_DENIED_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM PACCESS_DENIED_CALLBACK_OBJECT_ACE}
  TAccessDeniedCallBackObjectAce = ACCESS_DENIED_CALLBACK_OBJECT_ACE;
  PAccessDeniedCallBackObjectAce = PACCESS_DENIED_CALLBACK_OBJECT_ACE;

  _SYSTEM_AUDIT_CALLBACK_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _SYSTEM_AUDIT_CALLBACK_OBJECT_ACE}
  SYSTEM_AUDIT_CALLBACK_OBJECT_ACE = _SYSTEM_AUDIT_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM SYSTEM_AUDIT_CALLBACK_OBJECT_ACE}
  PSYSTEM_AUDIT_CALLBACK_OBJECT_ACE = ^SYSTEM_AUDIT_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM PSYSTEM_AUDIT_CALLBACK_OBJECT_ACE}
  TSystemAuditCallBackObjectAce = SYSTEM_AUDIT_CALLBACK_OBJECT_ACE;
  PSystemAuditCallBackObjectAce = PSYSTEM_AUDIT_CALLBACK_OBJECT_ACE;

  _SYSTEM_ALARM_CALLBACK_OBJECT_ACE = record
    Header: ACE_HEADER;
    Mask: ACCESS_MASK;
    Flags: DWORD;
    ObjectType: GUID;
    InheritedObjectType: GUID;
    SidStart: DWORD;
    // Opaque resouce manager specific data
  end;
  {$EXTERNALSYM _SYSTEM_ALARM_CALLBACK_OBJECT_ACE}
  SYSTEM_ALARM_CALLBACK_OBJECT_ACE = _SYSTEM_ALARM_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM SYSTEM_ALARM_CALLBACK_OBJECT_ACE}
  PSYSTEM_ALARM_CALLBACK_OBJECT_ACE = ^SYSTEM_ALARM_CALLBACK_OBJECT_ACE;
  {$EXTERNALSYM PSYSTEM_ALARM_CALLBACK_OBJECT_ACE}
  TSystemAlarmCallBackObjectAce = SYSTEM_ALARM_CALLBACK_OBJECT_ACE;
  PSystemAlarmCallBackObjectAce = PSYSTEM_ALARM_CALLBACK_OBJECT_ACE;

//
// Currently define Flags for "OBJECT" ACE types.
//

const
  ACE_OBJECT_TYPE_PRESENT           = $1;
  {$EXTERNALSYM ACE_OBJECT_TYPE_PRESENT}
  ACE_INHERITED_OBJECT_TYPE_PRESENT = $2;
  {$EXTERNALSYM ACE_INHERITED_OBJECT_TYPE_PRESENT}

//
//  The following declarations are used for setting and querying information
//  about and ACL.  First are the various information classes available to
//  the user.
//

  AclRevisionInformation = 1;
  {$EXTERNALSYM AclRevisionInformation}
  AclSizeInformation = 2;
  {$EXTERNALSYM AclSizeInformation}

type
  _ACL_INFORMATION_CLASS = DWORD;
  {$EXTERNALSYM _ACL_INFORMATION_CLASS}
  ACL_INFORMATION_CLASS = _ACL_INFORMATION_CLASS;
  {$EXTERNALSYM ACL_INFORMATION_CLASS}
  TAclInformationClass = ACL_INFORMATION_CLASS;

//
//  This record is returned/sent if the user is requesting/setting the
//  AclRevisionInformation
//

  PACL_REVISION_INFORMATION = ^ACL_REVISION_INFORMATION;
  {$EXTERNALSYM PACL_REVISION_INFORMATION}
  _ACL_REVISION_INFORMATION = record
    AclRevision: DWORD;
  end;
  {$EXTERNALSYM _ACL_REVISION_INFORMATION}
  ACL_REVISION_INFORMATION = _ACL_REVISION_INFORMATION;
  {$EXTERNALSYM ACL_REVISION_INFORMATION}
  TAclRevisionInformation = ACL_REVISION_INFORMATION;
  PAclRevisionInformation = PACL_REVISION_INFORMATION;

//
//  This record is returned if the user is requesting AclSizeInformation
//

  PACL_SIZE_INFORMATION = ^ACL_SIZE_INFORMATION;
  {$EXTERNALSYM PACL_SIZE_INFORMATION}
  _ACL_SIZE_INFORMATION = record
    AceCount: DWORD;
    AclBytesInUse: DWORD;
    AclBytesFree: DWORD;
  end;
  {$EXTERNALSYM _ACL_SIZE_INFORMATION}
  ACL_SIZE_INFORMATION = _ACL_SIZE_INFORMATION;
  {$EXTERNALSYM ACL_SIZE_INFORMATION}
  TAclSizeInformation = ACL_SIZE_INFORMATION;
  PAclSizeInformation = PACL_SIZE_INFORMATION;

////////////////////////////////////////////////////////////////////////
//                                                                    //
//                             SECURITY_DESCRIPTOR                    //
//                                                                    //
////////////////////////////////////////////////////////////////////////
//
//  Define the Security Descriptor and related data types.
//  This is an opaque data structure.
//

//
// Current security descriptor revision value
//

const
  SECURITY_DESCRIPTOR_REVISION  = (1);
  {$EXTERNALSYM SECURITY_DESCRIPTOR_REVISION}
  SECURITY_DESCRIPTOR_REVISION1 = (1);
  {$EXTERNALSYM SECURITY_DESCRIPTOR_REVISION1}

type
  SECURITY_DESCRIPTOR_CONTROL = WORD;
  {$EXTERNALSYM SECURITY_DESCRIPTOR_CONTROL}
  PSECURITY_DESCRIPTOR_CONTROL = ^SECURITY_DESCRIPTOR_CONTROL;
  {$EXTERNALSYM PSECURITY_DESCRIPTOR_CONTROL}
  TSecurityDescriptorControl = SECURITY_DESCRIPTOR_CONTROL;
  PSecurityDescriptorControl = PSECURITY_DESCRIPTOR_CONTROL;

const
  SE_OWNER_DEFAULTED       = ($0001);
  {$EXTERNALSYM SE_OWNER_DEFAULTED}
  SE_GROUP_DEFAULTED       = ($0002);
  {$EXTERNALSYM SE_GROUP_DEFAULTED}
  SE_DACL_PRESENT          = ($0004);
  {$EXTERNALSYM SE_DACL_PRESENT}
  SE_DACL_DEFAULTED        = ($0008);
  {$EXTERNALSYM SE_DACL_DEFAULTED}
  SE_SACL_PRESENT          = ($0010);
  {$EXTERNALSYM SE_SACL_PRESENT}
  SE_SACL_DEFAULTED        = ($0020);
  {$EXTERNALSYM SE_SACL_DEFAULTED}
  SE_DACL_AUTO_INHERIT_REQ = ($0100);
  {$EXTERNALSYM SE_DACL_AUTO_INHERIT_REQ}
  SE_SACL_AUTO_INHERIT_REQ = ($0200);
  {$EXTERNALSYM SE_SACL_AUTO_INHERIT_REQ}
  SE_DACL_AUTO_INHERITED   = ($0400);
  {$EXTERNALSYM SE_DACL_AUTO_INHERITED}
  SE_SACL_AUTO_INHERITED   = ($0800);
  {$EXTERNALSYM SE_SACL_AUTO_INHERITED}
  SE_DACL_PROTECTED        = ($1000);
  {$EXTERNALSYM SE_DACL_PROTECTED}
  SE_SACL_PROTECTED        = ($2000);
  {$EXTERNALSYM SE_SACL_PROTECTED}
  SE_RM_CONTROL_VALID      = ($4000);
  {$EXTERNALSYM SE_RM_CONTROL_VALID}
  SE_SELF_RELATIVE         = ($8000);
  {$EXTERNALSYM SE_SELF_RELATIVE}

//
//  Where:
//
//      SE_OWNER_DEFAULTED - This boolean flag, when set, indicates that the
//          SID pointed to by the Owner field was provided by a
//          defaulting mechanism rather than explicitly provided by the
//          original provider of the security descriptor.  This may
//          affect the treatment of the SID with respect to inheritence
//          of an owner.
//
//      SE_GROUP_DEFAULTED - This boolean flag, when set, indicates that the
//          SID in the Group field was provided by a defaulting mechanism
//          rather than explicitly provided by the original provider of
//          the security descriptor.  This may affect the treatment of
//          the SID with respect to inheritence of a primary group.
//
//      SE_DACL_PRESENT - This boolean flag, when set, indicates that the
//          security descriptor contains a discretionary ACL.  If this
//          flag is set and the Dacl field of the SECURITY_DESCRIPTOR is
//          null, then a null ACL is explicitly being specified.
//
//      SE_DACL_DEFAULTED - This boolean flag, when set, indicates that the
//          ACL pointed to by the Dacl field was provided by a defaulting
//          mechanism rather than explicitly provided by the original
//          provider of the security descriptor.  This may affect the
//          treatment of the ACL with respect to inheritence of an ACL.
//          This flag is ignored if the DaclPresent flag is not set.
//
//      SE_SACL_PRESENT - This boolean flag, when set,  indicates that the
//          security descriptor contains a system ACL pointed to by the
//          Sacl field.  If this flag is set and the Sacl field of the
//          SECURITY_DESCRIPTOR is null, then an empty (but present)
//          ACL is being specified.
//
//      SE_SACL_DEFAULTED - This boolean flag, when set, indicates that the
//          ACL pointed to by the Sacl field was provided by a defaulting
//          mechanism rather than explicitly provided by the original
//          provider of the security descriptor.  This may affect the
//          treatment of the ACL with respect to inheritence of an ACL.
//          This flag is ignored if the SaclPresent flag is not set.
//
//      SE_SELF_RELATIVE - This boolean flag, when set, indicates that the
//          security descriptor is in self-relative form.  In this form,
//          all fields of the security descriptor are contiguous in memory
//          and all pointer fields are expressed as offsets from the
//          beginning of the security descriptor.  This form is useful
//          for treating security descriptors as opaque data structures
//          for transmission in communication protocol or for storage on
//          secondary media.
//
//
//
// Pictorially the structure of a security descriptor is as follows:
//
//       3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//       1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//      +---------------------------------------------------------------+
//      |            Control            |Reserved1 (SBZ)|   Revision    |
//      +---------------------------------------------------------------+
//      |                            Owner                              |
//      +---------------------------------------------------------------+
//      |                            Group                              |
//      +---------------------------------------------------------------+
//      |                            Sacl                               |
//      +---------------------------------------------------------------+
//      |                            Dacl                               |
//      +---------------------------------------------------------------+
//
// In general, this data structure should be treated opaquely to ensure future
// compatibility.
//
//

type
  PSECURITY_DESCRIPTOR_RELATIVE = ^SECURITY_DESCRIPTOR_RELATIVE;
  {$EXTERNALSYM PSECURITY_DESCRIPTOR_RELATIVE}
  _SECURITY_DESCRIPTOR_RELATIVE = record
    Revision: Byte;
    Sbz1: Byte;
    Control: SECURITY_DESCRIPTOR_CONTROL;
    Owner: DWORD;
    Group: DWORD;
    Sacl: DWORD;
    Dacl: DWORD;
  end;
  {$EXTERNALSYM _SECURITY_DESCRIPTOR_RELATIVE}
  SECURITY_DESCRIPTOR_RELATIVE = _SECURITY_DESCRIPTOR_RELATIVE;
  {$EXTERNALSYM SECURITY_DESCRIPTOR_RELATIVE}
  TSecurityDescriptorRelative = SECURITY_DESCRIPTOR_RELATIVE;
  PSecurityDescriptorRelative = PSECURITY_DESCRIPTOR_RELATIVE;

  PSECURITY_DESCRIPTOR = ^SECURITY_DESCRIPTOR;
  {$EXTERNALSYM PSECURITY_DESCRIPTOR}
  _SECURITY_DESCRIPTOR = record
    Revision: Byte;
    Sbz1: Byte;
    Control: SECURITY_DESCRIPTOR_CONTROL;
    Owner: PSID;
    Group: PSID;
    Sacl: PACL;
    Dacl: PACL;
  end;
  {$EXTERNALSYM _SECURITY_DESCRIPTOR}
  SECURITY_DESCRIPTOR = _SECURITY_DESCRIPTOR;
  {$EXTERNALSYM SECURITY_DESCRIPTOR}
  TSecurityDescriptor = SECURITY_DESCRIPTOR;
  PSecurityDescriptor = PSECURITY_DESCRIPTOR;

  PPSECURITY_DESCRIPTOR = ^PSECURITY_DESCRIPTOR;
  {$NODEFINE PPSECURITY_DESCRIPTOR}

const
  SECURITY_DESCRIPTOR_MIN_LENGTH = SizeOf(SECURITY_DESCRIPTOR);
  {$EXTERNALSYM SECURITY_DESCRIPTOR_MIN_LENGTH}

// Where:
//
//     Revision - Contains the revision level of the security
//         descriptor.  This allows this structure to be passed between
//         systems or stored on disk even though it is expected to
//         change in the future.
//
//     Control - A set of flags which qualify the meaning of the
//         security descriptor or individual fields of the security
//         descriptor.
//
//     Owner - is a pointer to an SID representing an object's owner.
//         If this field is null, then no owner SID is present in the
//         security descriptor.  If the security descriptor is in
//         self-relative form, then this field contains an offset to
//         the SID, rather than a pointer.
//
//     Group - is a pointer to an SID representing an object's primary
//         group.  If this field is null, then no primary group SID is
//         present in the security descriptor.  If the security descriptor
//         is in self-relative form, then this field contains an offset to
//         the SID, rather than a pointer.
//
//     Sacl - is a pointer to a system ACL.  This field value is only
//         valid if the DaclPresent control flag is set.  If the
//         SaclPresent flag is set and this field is null, then a null
//         ACL  is specified.  If the security descriptor is in
//         self-relative form, then this field contains an offset to
//         the ACL, rather than a pointer.
//
//     Dacl - is a pointer to a discretionary ACL.  This field value is
//         only valid if the DaclPresent control flag is set.  If the
//         DaclPresent flag is set and this field is null, then a null
//         ACL (unconditionally granting access) is specified.  If the
//         security descriptor is in self-relative form, then this field
//         contains an offset to the ACL, rather than a pointer.
//

////////////////////////////////////////////////////////////////////////
//                                                                    //
//               Object Type list for AccessCheckByType               //
//                                                                    //
////////////////////////////////////////////////////////////////////////

type
  POBJECT_TYPE_LIST = ^OBJECT_TYPE_LIST;
  {$EXTERNALSYM POBJECT_TYPE_LIST}
  _OBJECT_TYPE_LIST = record
    Level: Word;
    Sbz: Word;
    ObjectType: PGUID;
  end;
  {$EXTERNALSYM _OBJECT_TYPE_LIST}
  OBJECT_TYPE_LIST = _OBJECT_TYPE_LIST;
  {$EXTERNALSYM OBJECT_TYPE_LIST}
  TObjectTypeList = OBJECT_TYPE_LIST;
  PObjectTypeList = POBJECT_TYPE_LIST;

//
// DS values for Level
//

const
  ACCESS_OBJECT_GUID       = 0;
  {$EXTERNALSYM ACCESS_OBJECT_GUID}
  ACCESS_PROPERTY_SET_GUID = 1;
  {$EXTERNALSYM ACCESS_PROPERTY_SET_GUID}
  ACCESS_PROPERTY_GUID     = 2;
  {$EXTERNALSYM ACCESS_PROPERTY_GUID}

  ACCESS_MAX_LEVEL         = 4;
  {$EXTERNALSYM ACCESS_MAX_LEVEL}

//
// Parameters to NtAccessCheckByTypeAndAditAlarm
//

type
  _AUDIT_EVENT_TYPE = (AuditEventObjectAccess, AuditEventDirectoryServiceAccess);
  {$EXTERNALSYM _AUDIT_EVENT_TYPE}
  AUDIT_EVENT_TYPE = _AUDIT_EVENT_TYPE;
  {$EXTERNALSYM AUDIT_EVENT_TYPE}
  PAUDIT_EVENT_TYPE = ^AUDIT_EVENT_TYPE;
  {$EXTERNALSYM PAUDIT_EVENT_TYPE}
  TAuditEventType = AUDIT_EVENT_TYPE;
  PAuditEventType = PAUDIT_EVENT_TYPE;

const
  AUDIT_ALLOW_NO_PRIVILEGE = $1;
  {$EXTERNALSYM AUDIT_ALLOW_NO_PRIVILEGE}

//
// DS values for Source and ObjectTypeName
//

  ACCESS_DS_SOURCE_A           = 'DS';
  {$EXTERNALSYM ACCESS_DS_SOURCE_A}
  ACCESS_DS_SOURCE_W           = WideString('DS');
  {$EXTERNALSYM ACCESS_DS_SOURCE_W}
  ACCESS_DS_OBJECT_TYPE_NAME_A = 'Directory Service Object';
  {$EXTERNALSYM ACCESS_DS_OBJECT_TYPE_NAME_A}
  ACCESS_DS_OBJECT_TYPE_NAME_W = WideString('Directory Service Object');
  {$EXTERNALSYM ACCESS_DS_OBJECT_TYPE_NAME_W}

////////////////////////////////////////////////////////////////////////
//                                                                    //
//               Privilege Related Data Structures                    //
//                                                                    //
////////////////////////////////////////////////////////////////////////

//
// Privilege attributes
//

const
  SE_PRIVILEGE_ENABLED_BY_DEFAULT = ($00000001);
  {$EXTERNALSYM SE_PRIVILEGE_ENABLED_BY_DEFAULT}
  SE_PRIVILEGE_ENABLED            = ($00000002);
  {$EXTERNALSYM SE_PRIVILEGE_ENABLED}
  SE_PRIVILEGE_REMOVED            = ($00000004);
  {$EXTERNALSYM SE_PRIVILEGE_REMOVED}
  SE_PRIVILEGE_USED_FOR_ACCESS    = DWORD($80000000);
  {$EXTERNALSYM SE_PRIVILEGE_USED_FOR_ACCESS}

//
// Privilege Set Control flags
//

  PRIVILEGE_SET_ALL_NECESSARY = (1);
  {$EXTERNALSYM PRIVILEGE_SET_ALL_NECESSARY}

//
//  Privilege Set - This is defined for a privilege set of one.
//                  If more than one privilege is needed, then this structure
//                  will need to be allocated with more space.
//
//  Note: don't change this structure without fixing the INITIAL_PRIVILEGE_SET
//  structure (defined in se.h)
//

type
  PPRIVILEGE_SET = ^PRIVILEGE_SET;
  {$EXTERNALSYM PPRIVILEGE_SET}
  _PRIVILEGE_SET = record
    PrivilegeCount: DWORD;
    Control: DWORD;
    Privilege: array [0..ANYSIZE_ARRAY - 1] of LUID_AND_ATTRIBUTES;
    //Privilege: LUID_AND_ATTRIBUTES;
  end;
  {$EXTERNALSYM _PRIVILEGE_SET}
  PRIVILEGE_SET = _PRIVILEGE_SET;
  {$EXTERNALSYM PRIVILEGE_SET}
  TPrivilegeSet = PRIVILEGE_SET;
  PPrivilegeSet = PPRIVILEGE_SET;

////////////////////////////////////////////////////////////////////////
//                                                                    //
//               NT Defined Privileges                                //
//                                                                    //
////////////////////////////////////////////////////////////////////////

const
  SE_CREATE_TOKEN_NAME        = 'SeCreateTokenPrivilege';
  {$EXTERNALSYM SE_CREATE_TOKEN_NAME}
  SE_ASSIGNPRIMARYTOKEN_NAME  = 'SeAssignPrimaryTokenPrivilege';
  {$EXTERNALSYM SE_ASSIGNPRIMARYTOKEN_NAME}
  SE_LOCK_MEMORY_NAME         = 'SeLockMemoryPrivilege';
  {$EXTERNALSYM SE_LOCK_MEMORY_NAME}
  SE_INCREASE_QUOTA_NAME      = 'SeIncreaseQuotaPrivilege';
  {$EXTERNALSYM SE_INCREASE_QUOTA_NAME}
  SE_UNSOLICITED_INPUT_NAME   = 'SeUnsolicitedInputPrivilege';
  {$EXTERNALSYM SE_UNSOLICITED_INPUT_NAME}
  SE_MACHINE_ACCOUNT_NAME     = 'SeMachineAccountPrivilege';
  {$EXTERNALSYM SE_MACHINE_ACCOUNT_NAME}
  SE_TCB_NAME                 = 'SeTcbPrivilege';
  {$EXTERNALSYM SE_TCB_NAME}
  SE_SECURITY_NAME            = 'SeSecurityPrivilege';
  {$EXTERNALSYM SE_SECURITY_NAME}
  SE_TAKE_OWNERSHIP_NAME      = 'SeTakeOwnershipPrivilege';
  {$EXTERNALSYM SE_TAKE_OWNERSHIP_NAME}
  SE_LOAD_DRIVER_NAME         = 'SeLoadDriverPrivilege';
  {$EXTERNALSYM SE_LOAD_DRIVER_NAME}
  SE_SYSTEM_PROFILE_NAME      = 'SeSystemProfilePrivilege';
  {$EXTERNALSYM SE_SYSTEM_PROFILE_NAME}
  SE_SYSTEMTIME_NAME          = 'SeSystemtimePrivilege';
  {$EXTERNALSYM SE_SYSTEMTIME_NAME}
  SE_PROF_SINGLE_PROCESS_NAME = 'SeProfileSingleProcessPrivilege';
  {$EXTERNALSYM SE_PROF_SINGLE_PROCESS_NAME}
  SE_INC_BASE_PRIORITY_NAME   = 'SeIncreaseBasePriorityPrivilege';
  {$EXTERNALSYM SE_INC_BASE_PRIORITY_NAME}
  SE_CREATE_PAGEFILE_NAME     = 'SeCreatePagefilePrivilege';
  {$EXTERNALSYM SE_CREATE_PAGEFILE_NAME}
  SE_CREATE_PERMANENT_NAME    = 'SeCreatePermanentPrivilege';
  {$EXTERNALSYM SE_CREATE_PERMANENT_NAME}
  SE_BACKUP_NAME              = 'SeBackupPrivilege';
  {$EXTERNALSYM SE_BACKUP_NAME}
  SE_RESTORE_NAME             = 'SeRestorePrivilege';
  {$EXTERNALSYM SE_RESTORE_NAME}
  SE_SHUTDOWN_NAME            = 'SeShutdownPrivilege';
  {$EXTERNALSYM SE_SHUTDOWN_NAME}
  SE_DEBUG_NAME               = 'SeDebugPrivilege';
  {$EXTERNALSYM SE_DEBUG_NAME}
  SE_AUDIT_NAME               = 'SeAuditPrivilege';
  {$EXTERNALSYM SE_AUDIT_NAME}
  SE_SYSTEM_ENVIRONMENT_NAME  = 'SeSystemEnvironmentPrivilege';
  {$EXTERNALSYM SE_SYSTEM_ENVIRONMENT_NAME}
  SE_CHANGE_NOTIFY_NAME       = 'SeChangeNotifyPrivilege';
  {$EXTERNALSYM SE_CHANGE_NOTIFY_NAME}
  SE_REMOTE_SHUTDOWN_NAME     = 'SeRemoteShutdownPrivilege';
  {$EXTERNALSYM SE_REMOTE_SHUTDOWN_NAME}
  SE_UNDOCK_NAME              = 'SeUndockPrivilege';
  {$EXTERNALSYM SE_UNDOCK_NAME}
  SE_SYNC_AGENT_NAME          = 'SeSyncAgentPrivilege';
  {$EXTERNALSYM SE_SYNC_AGENT_NAME}
  SE_ENABLE_DELEGATION_NAME   = 'SeEnableDelegationPrivilege';
  {$EXTERNALSYM SE_ENABLE_DELEGATION_NAME}
  SE_MANAGE_VOLUME_NAME       = 'SeManageVolumePrivilege';
  {$EXTERNALSYM SE_MANAGE_VOLUME_NAME}
  SE_IMPERSONATE_NAME         = 'SeImpersonatePrivilege';
  {$EXTERNALSYM SE_IMPERSONATE_NAME}
  SE_CREATE_GLOBAL_NAME       = 'SeCreateGlobalPrivilege';
  {$EXTERNALSYM SE_CREATE_GLOBAL_NAME}


////////////////////////////////////////////////////////////////////
//                                                                //
//           Security Quality Of Service                          //
//                                                                //
//                                                                //
////////////////////////////////////////////////////////////////////

//
// Impersonation Level
//
// Impersonation level is represented by a pair of bits in Windows.
// If a new impersonation level is added or lowest value is changed from
// 0 to something else, fix the Windows CreateFile call.
//

type
  _SECURITY_IMPERSONATION_LEVEL = (SecurityAnonymous, SecurityIdentification,
    SecurityImpersonation, SecurityDelegation);
  {$EXTERNALSYM _SECURITY_IMPERSONATION_LEVEL}
  SECURITY_IMPERSONATION_LEVEL = _SECURITY_IMPERSONATION_LEVEL;
  {$EXTERNALSYM SECURITY_IMPERSONATION_LEVEL}
  PSECURITY_IMPERSONATION_LEVEL = ^SECURITY_IMPERSONATION_LEVEL;
  {$EXTERNALSYM PSECURITY_IMPERSONATION_LEVEL}
  TSecurityImpersonationLevel = SECURITY_IMPERSONATION_LEVEL;
  PSecurityImpersonationLevel = PSECURITY_IMPERSONATION_LEVEL;

const
  SECURITY_MAX_IMPERSONATION_LEVEL = SecurityDelegation;
  {$EXTERNALSYM SECURITY_MAX_IMPERSONATION_LEVEL}
  SECURITY_MIN_IMPERSONATION_LEVEL = SecurityAnonymous;
  {$EXTERNALSYM SECURITY_MIN_IMPERSONATION_LEVEL}
  DEFAULT_IMPERSONATION_LEVEL      = SecurityImpersonation;
  {$EXTERNALSYM DEFAULT_IMPERSONATION_LEVEL}

function VALID_IMPERSONATION_LEVEL(L: TSecurityImpersonationLevel): BOOL;
{$EXTERNALSYM VALID_IMPERSONATION_LEVEL}

////////////////////////////////////////////////////////////////////
//                                                                //
//           Token Object Definitions                             //
//                                                                //
//                                                                //
////////////////////////////////////////////////////////////////////


//
// Token Specific Access Rights.
//

const
  TOKEN_ASSIGN_PRIMARY    = ($0001);
  {$EXTERNALSYM TOKEN_ASSIGN_PRIMARY}
  TOKEN_DUPLICATE         = ($0002);
  {$EXTERNALSYM TOKEN_DUPLICATE}
  TOKEN_IMPERSONATE       = ($0004);
  {$EXTERNALSYM TOKEN_IMPERSONATE}
  TOKEN_QUERY             = ($0008);
  {$EXTERNALSYM TOKEN_QUERY}
  TOKEN_QUERY_SOURCE      = ($0010);
  {$EXTERNALSYM TOKEN_QUERY_SOURCE}
  TOKEN_ADJUST_PRIVILEGES = ($0020);
  {$EXTERNALSYM TOKEN_ADJUST_PRIVILEGES}
  TOKEN_ADJUST_GROUPS     = ($0040);
  {$EXTERNALSYM TOKEN_ADJUST_GROUPS}
  TOKEN_ADJUST_DEFAULT    = ($0080);
  {$EXTERNALSYM TOKEN_ADJUST_DEFAULT}
  TOKEN_ADJUST_SESSIONID  = ($0100);
  {$EXTERNALSYM TOKEN_ADJUST_SESSIONID}

  TOKEN_ALL_ACCESS_P = STANDARD_RIGHTS_REQUIRED or TOKEN_ASSIGN_PRIMARY or
    TOKEN_DUPLICATE or TOKEN_IMPERSONATE or TOKEN_QUERY or TOKEN_QUERY_SOURCE or
    TOKEN_ADJUST_PRIVILEGES or TOKEN_ADJUST_GROUPS or TOKEN_ADJUST_DEFAULT;
  {$EXTERNALSYM TOKEN_ALL_ACCESS_P}

  TOKEN_ALL_ACCESS = TOKEN_ALL_ACCESS_P or TOKEN_ADJUST_SESSIONID;
  {$EXTERNALSYM TOKEN_ALL_ACCESS}

  TOKEN_READ = (STANDARD_RIGHTS_READ or TOKEN_QUERY);
  {$EXTERNALSYM TOKEN_READ}

  TOKEN_WRITE = (STANDARD_RIGHTS_WRITE or TOKEN_ADJUST_PRIVILEGES or
    TOKEN_ADJUST_GROUPS or TOKEN_ADJUST_DEFAULT);
  {$EXTERNALSYM TOKEN_WRITE}

  TOKEN_EXECUTE = (STANDARD_RIGHTS_EXECUTE);
  {$EXTERNALSYM TOKEN_EXECUTE}

//
// Token Types
//

type
  _TOKEN_TYPE = (TokenTypePad0, TokenPrimary, TokenImpersonation);
  {$EXTERNALSYM _TOKEN_TYPE}
  TOKEN_TYPE = _TOKEN_TYPE;
  {$EXTERNALSYM TOKEN_TYPE}
  PTOKEN_TYPE = ^TOKEN_TYPE;
  {$EXTERNALSYM PTOKEN_TYPE}

  TTokenType = TOKEN_TYPE;
  PTokenType = PTOKEN_TYPE;

//
// Token Information Classes.
//

type
  _TOKEN_INFORMATION_CLASS = (TokenInfoClassPad0, TokenUser, TokenGroups,
    TokenPrivileges, TokenOwner, TokenPrimaryGroup, TokenDefaultDacl, TokenSource,
    TokenType, TokenImpersonationLevel, TokenStatistics, TokenRestrictedSids,
    TokenSessionId, TokenGroupsAndPrivileges, TokenSessionReference,
    TokenSandBoxInert, TokenAuditPolicy, TokenOrigin,
    MaxTokenInfoClass); {MaxTokenInfoClass should always be the last enum}
  {$EXTERNALSYM _TOKEN_INFORMATION_CLASS}
  TOKEN_INFORMATION_CLASS = _TOKEN_INFORMATION_CLASS;
  {$EXTERNALSYM TOKEN_INFORMATION_CLASS}
  PTOKEN_INFORMATION_CLASS = ^TOKEN_INFORMATION_CLASS;
  {$EXTERNALSYM PTOKEN_INFORMATION_CLASS}

  TTokenInformationClass = TOKEN_INFORMATION_CLASS;
  PTokenInformationClass = PTOKEN_INFORMATION_CLASS;

//
// Token information class structures
//

type
  PTOKEN_USER = ^TOKEN_USER;
  {$EXTERNALSYM PTOKEN_USER}
  _TOKEN_USER = record
    User: SID_AND_ATTRIBUTES;
  end;
  {$EXTERNALSYM _TOKEN_USER}
  TOKEN_USER = _TOKEN_USER;
  {$EXTERNALSYM TOKEN_USER}
  TTokenUser = TOKEN_USER;
  PTokenUser = PTOKEN_USER;

  PTOKEN_GROUPS = ^TOKEN_GROUPS;
  {$EXTERNALSYM PTOKEN_GROUPS}
  _TOKEN_GROUPS = record
    GroupCount: DWORD;
    Groups: array [0..ANYSIZE_ARRAY - 1] of SID_AND_ATTRIBUTES;
  end;
  {$EXTERNALSYM _TOKEN_GROUPS}
  TOKEN_GROUPS = _TOKEN_GROUPS;
  {$EXTERNALSYM TOKEN_GROUPS}
  TTokenGroups = TOKEN_GROUPS;
  PTokenGroups = PTOKEN_GROUPS;

  PTOKEN_PRIVILEGES = ^TOKEN_PRIVILEGES;
  {$EXTERNALSYM PTOKEN_PRIVILEGES}
  _TOKEN_PRIVILEGES = record
    PrivilegeCount: DWORD;
    Privileges: array [0..ANYSIZE_ARRAY - 1] of LUID_AND_ATTRIBUTES;
  end;
  {$EXTERNALSYM _TOKEN_PRIVILEGES}
  TOKEN_PRIVILEGES = _TOKEN_PRIVILEGES;
  {$EXTERNALSYM TOKEN_PRIVILEGES}
  TTokenPrivileges = TOKEN_PRIVILEGES;
  PTokenPrivileges = PTOKEN_PRIVILEGES;

  PTOKEN_OWNER = ^TOKEN_OWNER;
  {$EXTERNALSYM PTOKEN_OWNER}
  _TOKEN_OWNER = record
    Owner: PSID;
  end;
  {$EXTERNALSYM _TOKEN_OWNER}
  TOKEN_OWNER = _TOKEN_OWNER;
  {$EXTERNALSYM TOKEN_OWNER}
  TTokenOwner = TOKEN_OWNER;
  PTokenOwner = PTOKEN_OWNER;

  PTOKEN_PRIMARY_GROUP = ^TOKEN_PRIMARY_GROUP;
  {$EXTERNALSYM PTOKEN_PRIMARY_GROUP}
  _TOKEN_PRIMARY_GROUP = record
    PrimaryGroup: PSID;
  end;
  {$EXTERNALSYM _TOKEN_PRIMARY_GROUP}
  TOKEN_PRIMARY_GROUP = _TOKEN_PRIMARY_GROUP;
  {$EXTERNALSYM TOKEN_PRIMARY_GROUP}
  TTokenPrimaryGroup = TOKEN_PRIMARY_GROUP;
  PTokenPrimaryGroup = PTOKEN_PRIMARY_GROUP;

  PTOKEN_DEFAULT_DACL = ^TOKEN_DEFAULT_DACL;
  {$EXTERNALSYM PTOKEN_DEFAULT_DACL}
  _TOKEN_DEFAULT_DACL = record
    DefaultDacl: PACL;
  end;
  {$EXTERNALSYM _TOKEN_DEFAULT_DACL}
  TOKEN_DEFAULT_DACL = _TOKEN_DEFAULT_DACL;
  {$EXTERNALSYM TOKEN_DEFAULT_DACL}
  TTokenDefaultDacl = TOKEN_DEFAULT_DACL;
  PTokenDefaultDacl = PTOKEN_DEFAULT_DACL;

  _TOKEN_GROUPS_AND_PRIVILEGES = record
    SidCount: DWORD;
    SidLength: DWORD;
    Sids: PSID_AND_ATTRIBUTES;
    RestrictedSidCount: DWORD;
    RestrictedSidLength: DWORD;
    RestrictedSids: PSID_AND_ATTRIBUTES;
    PrivilegeCount: DWORD;
    PrivilegeLength: DWORD;
    Privileges: PLUID_AND_ATTRIBUTES;
    AuthenticationId: LUID;
  end;
  {$EXTERNALSYM _TOKEN_GROUPS_AND_PRIVILEGES}
  TOKEN_GROUPS_AND_PRIVILEGES = _TOKEN_GROUPS_AND_PRIVILEGES;
  {$EXTERNALSYM TOKEN_GROUPS_AND_PRIVILEGES}
  PTOKEN_GROUPS_AND_PRIVILEGES = ^TOKEN_GROUPS_AND_PRIVILEGES;
  {$EXTERNALSYM PTOKEN_GROUPS_AND_PRIVILEGES}
  TTokenGroupsAndPrivileges = TOKEN_GROUPS_AND_PRIVILEGES;
  PTokenGroupsAndPrivileges = PTOKEN_GROUPS_AND_PRIVILEGES;

//
// Valid bits for each TOKEN_AUDIT_POLICY policy mask field.
//

const
  TOKEN_AUDIT_SUCCESS_INCLUDE = $1;
  {$EXTERNALSYM TOKEN_AUDIT_SUCCESS_INCLUDE}
  TOKEN_AUDIT_SUCCESS_EXCLUDE = $2;
  {$EXTERNALSYM TOKEN_AUDIT_SUCCESS_EXCLUDE}
  TOKEN_AUDIT_FAILURE_INCLUDE = $4;
  {$EXTERNALSYM TOKEN_AUDIT_FAILURE_INCLUDE}
  TOKEN_AUDIT_FAILURE_EXCLUDE = $8;
  {$EXTERNALSYM TOKEN_AUDIT_FAILURE_EXCLUDE}

  VALID_AUDIT_POLICY_BITS = (TOKEN_AUDIT_SUCCESS_INCLUDE or
                             TOKEN_AUDIT_SUCCESS_EXCLUDE or
                             TOKEN_AUDIT_FAILURE_INCLUDE or
                             TOKEN_AUDIT_FAILURE_EXCLUDE);
  {$EXTERNALSYM VALID_AUDIT_POLICY_BITS}

type
  _TOKEN_AUDIT_POLICY_ELEMENT = record
    Category: DWORD;
    PolicyMask: DWORD;
  end;
  {$EXTERNALSYM _TOKEN_AUDIT_POLICY_ELEMENT}
  TOKEN_AUDIT_POLICY_ELEMENT = _TOKEN_AUDIT_POLICY_ELEMENT;
  {$EXTERNALSYM TOKEN_AUDIT_POLICY_ELEMENT}
  PTOKEN_AUDIT_POLICY_ELEMENT = ^TOKEN_AUDIT_POLICY_ELEMENT;
  {$EXTERNALSYM PTOKEN_AUDIT_POLICY_ELEMENT}
  TTokenAuditPolicyElement = TOKEN_AUDIT_POLICY_ELEMENT;
  PTokenAuditPolicyElement = PTOKEN_AUDIT_POLICY_ELEMENT;

// TODO Implementation references AuditEventMaxType, which isn't defined anywhere
//function VALID_TOKEN_AUDIT_POLICY_ELEMENT(P: TOKEN_AUDIT_POLICY_ELEMENT): BOOL;
//{$EXTERNALSYM VALID_TOKEN_AUDIT_POLICY_ELEMENT}

type
  _TOKEN_AUDIT_POLICY = record
    PolicyCount: DWORD;
    Policy: array [0..ANYSIZE_ARRAY - 1] of TOKEN_AUDIT_POLICY_ELEMENT;
  end;
  {$EXTERNALSYM _TOKEN_AUDIT_POLICY}
  TOKEN_AUDIT_POLICY = _TOKEN_AUDIT_POLICY;
  {$EXTERNALSYM TOKEN_AUDIT_POLICY}
  PTOKEN_AUDIT_POLICY = ^TOKEN_AUDIT_POLICY;
  {$EXTERNALSYM PTOKEN_AUDIT_POLICY}
  TTokenAuditPolicy = TOKEN_AUDIT_POLICY;
  PTokenAuditPolicy = PTOKEN_AUDIT_POLICY;

function PER_USER_AUDITING_POLICY_SIZE(p: PTOKEN_AUDIT_POLICY): DWORD;
{$EXTERNALSYM PER_USER_AUDITING_POLICY_SIZE}

function PER_USER_AUDITING_POLICY_SIZE_BY_COUNT(C: DWORD): DWORD;
{$EXTERNALSYM PER_USER_AUDITING_POLICY_SIZE_BY_COUNT}

const
  TOKEN_SOURCE_LENGTH = 8;
  {$EXTERNALSYM TOKEN_SOURCE_LENGTH}

type
  PTOKEN_SOURCE = ^TOKEN_SOURCE;
  {$EXTERNALSYM PTOKEN_SOURCE}
  _TOKEN_SOURCE = record
    SourceName: array [0..TOKEN_SOURCE_LENGTH - 1] of CHAR;
    SourceIdentifier: LUID;
  end;
  {$EXTERNALSYM _TOKEN_SOURCE}
  TOKEN_SOURCE = _TOKEN_SOURCE;
  {$EXTERNALSYM TOKEN_SOURCE}
  TTokenSource = TOKEN_SOURCE;
  PTokenSource = PTOKEN_SOURCE;

  PTOKEN_STATISTICS = ^TOKEN_STATISTICS;
  {$EXTERNALSYM PTOKEN_STATISTICS}
  _TOKEN_STATISTICS = record
    TokenId: LUID;
    AuthenticationId: LUID;
    ExpirationTime: LARGE_INTEGER;
    TokenType: TOKEN_TYPE;
    ImpersonationLevel: SECURITY_IMPERSONATION_LEVEL;
    DynamicCharged: DWORD;
    DynamicAvailable: DWORD;
    GroupCount: DWORD;
    PrivilegeCount: DWORD;
    ModifiedId: LUID;
  end;
  {$EXTERNALSYM _TOKEN_STATISTICS}
  TOKEN_STATISTICS = _TOKEN_STATISTICS;
  {$EXTERNALSYM TOKEN_STATISTICS}
  TTokenStatistics = TOKEN_STATISTICS;
  PTokenStatistics = PTOKEN_STATISTICS;

  PTOKEN_CONTROL = ^TOKEN_CONTROL;
  {$EXTERNALSYM PTOKEN_CONTROL}
  _TOKEN_CONTROL = record
    TokenId: LUID;
    AuthenticationId: LUID;
    ModifiedId: LUID;
    TokenSource: TOKEN_SOURCE;
  end;
  {$EXTERNALSYM _TOKEN_CONTROL}
  TOKEN_CONTROL = _TOKEN_CONTROL;
  {$EXTERNALSYM TOKEN_CONTROL}
  TTokenControl = TOKEN_CONTROL;
  PTokenControl = PTOKEN_CONTROL;

  _TOKEN_ORIGIN = record
    OriginatingLogonSession: LUID;
  end;
  {$EXTERNALSYM _TOKEN_ORIGIN}
  TOKEN_ORIGIN = _TOKEN_ORIGIN;
  {$EXTERNALSYM TOKEN_ORIGIN}
  PTOKEN_ORIGIN = ^TOKEN_ORIGIN;
  {$EXTERNALSYM PTOKEN_ORIGIN}
  TTokenOrigin = TOKEN_ORIGIN;
  PTokenOrigin = PTOKEN_ORIGIN;  

//
// Security Tracking Mode
//

const
  SECURITY_DYNAMIC_TRACKING = (TRUE);
  {$EXTERNALSYM SECURITY_DYNAMIC_TRACKING}
  SECURITY_STATIC_TRACKING  = (FALSE);
  {$EXTERNALSYM SECURITY_STATIC_TRACKING}

type
  SECURITY_CONTEXT_TRACKING_MODE = ByteBool;
  {$EXTERNALSYM SECURITY_CONTEXT_TRACKING_MODE}
  PSECURITY_CONTEXT_TRACKING_MODE = ^SECURITY_CONTEXT_TRACKING_MODE;
  {$EXTERNALSYM PSECURITY_CONTEXT_TRACKING_MODE}

//
// Quality Of Service
//

  PSECURITY_QUALITY_OF_SERVICE = ^SECURITY_QUALITY_OF_SERVICE;
  {$EXTERNALSYM PSECURITY_QUALITY_OF_SERVICE}
  _SECURITY_QUALITY_OF_SERVICE = record
    Length: DWORD;
    ImpersonationLevel: SECURITY_IMPERSONATION_LEVEL;
    ContextTrackingMode: SECURITY_CONTEXT_TRACKING_MODE;
    EffectiveOnly: ByteBool;
  end;
  {$EXTERNALSYM _SECURITY_QUALITY_OF_SERVICE}
  SECURITY_QUALITY_OF_SERVICE = _SECURITY_QUALITY_OF_SERVICE;
  {$EXTERNALSYM SECURITY_QUALITY_OF_SERVICE}
  TSecurityQualityOfService = SECURITY_QUALITY_OF_SERVICE;
  PSecurityQualityOfService = PSECURITY_QUALITY_OF_SERVICE;

//
// Used to represent information related to a thread impersonation
//

  PSE_IMPERSONATION_STATE = ^SE_IMPERSONATION_STATE;
  {$EXTERNALSYM PSE_IMPERSONATION_STATE}
  _SE_IMPERSONATION_STATE = record
    Token: PACCESS_TOKEN;
    CopyOnOpen: ByteBool;
    EffectiveOnly: ByteBool;
    Level: SECURITY_IMPERSONATION_LEVEL;
  end;
  {$EXTERNALSYM _SE_IMPERSONATION_STATE}
  SE_IMPERSONATION_STATE = _SE_IMPERSONATION_STATE;
  {$EXTERNALSYM SE_IMPERSONATION_STATE}
  TSeImpersonationState = SE_IMPERSONATION_STATE;
  PSeImpersonationState = PSE_IMPERSONATION_STATE;

const
  DISABLE_MAX_PRIVILEGE = $1;
  {$EXTERNALSYM DISABLE_MAX_PRIVILEGE}
  SANDBOX_INERT         = $2;
  {$EXTERNALSYM SANDBOX_INERT}

type
  SECURITY_INFORMATION = DWORD;
  {$EXTERNALSYM SECURITY_INFORMATION}
  PSECURITY_INFORMATION = ^SECURITY_INFORMATION;
  {$EXTERNALSYM PSECURITY_INFORMATION}
  TSecurityInformation = SECURITY_INFORMATION;
  PSecurityInformation = PSECURITY_INFORMATION;  

const
  OWNER_SECURITY_INFORMATION = ($00000001);
  {$EXTERNALSYM OWNER_SECURITY_INFORMATION}
  GROUP_SECURITY_INFORMATION = ($00000002);
  {$EXTERNALSYM GROUP_SECURITY_INFORMATION}
  DACL_SECURITY_INFORMATION  = ($00000004);
  {$EXTERNALSYM DACL_SECURITY_INFORMATION}
  SACL_SECURITY_INFORMATION  = ($00000008);
  {$EXTERNALSYM SACL_SECURITY_INFORMATION}

  PROTECTED_DACL_SECURITY_INFORMATION   = ($80000000);
  {$EXTERNALSYM PROTECTED_DACL_SECURITY_INFORMATION}
  PROTECTED_SACL_SECURITY_INFORMATION   = ($40000000);
  {$EXTERNALSYM PROTECTED_SACL_SECURITY_INFORMATION}
  UNPROTECTED_DACL_SECURITY_INFORMATION = ($20000000);
  {$EXTERNALSYM UNPROTECTED_DACL_SECURITY_INFORMATION}
  UNPROTECTED_SACL_SECURITY_INFORMATION = ($10000000);
  {$EXTERNALSYM UNPROTECTED_SACL_SECURITY_INFORMATION}

  PROCESS_TERMINATE         = ($0001);
  {$EXTERNALSYM PROCESS_TERMINATE}
  PROCESS_CREATE_THREAD     = ($0002);
  {$EXTERNALSYM PROCESS_CREATE_THREAD}
  PROCESS_SET_SESSIONID     = ($0004);
  {$EXTERNALSYM PROCESS_SET_SESSIONID}
  PROCESS_VM_OPERATION      = ($0008);
  {$EXTERNALSYM PROCESS_VM_OPERATION}
  PROCESS_VM_READ           = ($0010);
  {$EXTERNALSYM PROCESS_VM_READ}
  PROCESS_VM_WRITE          = ($0020);
  {$EXTERNALSYM PROCESS_VM_WRITE}
  PROCESS_DUP_HANDLE        = ($0040);
  {$EXTERNALSYM PROCESS_DUP_HANDLE}
  PROCESS_CREATE_PROCESS    = ($0080);
  {$EXTERNALSYM PROCESS_CREATE_PROCESS}
  PROCESS_SET_QUOTA         = ($0100);
  {$EXTERNALSYM PROCESS_SET_QUOTA}
  PROCESS_SET_INFORMATION   = ($0200);
  {$EXTERNALSYM PROCESS_SET_INFORMATION}
  PROCESS_QUERY_INFORMATION = ($0400);
  {$EXTERNALSYM PROCESS_QUERY_INFORMATION}
  PROCESS_SUSPEND_RESUME    = ($0800);
  {$EXTERNALSYM PROCESS_SUSPEND_RESUME}
  PROCESS_ALL_ACCESS        = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $FFF);
  {$EXTERNALSYM PROCESS_ALL_ACCESS}

  MAXIMUM_PROCESSORS = 32;
  {$EXTERNALSYM MAXIMUM_PROCESSORS}

  THREAD_TERMINATE            = ($0001);
  {$EXTERNALSYM THREAD_TERMINATE}
  THREAD_SUSPEND_RESUME       = ($0002);
  {$EXTERNALSYM THREAD_SUSPEND_RESUME}
  THREAD_GET_CONTEXT          = ($0008);
  {$EXTERNALSYM THREAD_GET_CONTEXT}
  THREAD_SET_CONTEXT          = ($0010);
  {$EXTERNALSYM THREAD_SET_CONTEXT}
  THREAD_SET_INFORMATION      = ($0020);
  {$EXTERNALSYM THREAD_SET_INFORMATION}
  THREAD_QUERY_INFORMATION    = ($0040);
  {$EXTERNALSYM THREAD_QUERY_INFORMATION}
  THREAD_SET_THREAD_TOKEN     = ($0080);
  {$EXTERNALSYM THREAD_SET_THREAD_TOKEN}
  THREAD_IMPERSONATE          = ($0100);
  {$EXTERNALSYM THREAD_IMPERSONATE}
  THREAD_DIRECT_IMPERSONATION = ($0200);
  {$EXTERNALSYM THREAD_DIRECT_IMPERSONATION}

  THREAD_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $3FF);
  {$EXTERNALSYM THREAD_ALL_ACCESS}

  JOB_OBJECT_ASSIGN_PROCESS          = ($0001);
  {$EXTERNALSYM JOB_OBJECT_ASSIGN_PROCESS}
  JOB_OBJECT_SET_ATTRIBUTES          = ($0002);
  {$EXTERNALSYM JOB_OBJECT_SET_ATTRIBUTES}
  JOB_OBJECT_QUERY                   = ($0004);
  {$EXTERNALSYM JOB_OBJECT_QUERY}
  JOB_OBJECT_TERMINATE               = ($0008);
  {$EXTERNALSYM JOB_OBJECT_TERMINATE}
  JOB_OBJECT_SET_SECURITY_ATTRIBUTES = ($0010);
  {$EXTERNALSYM JOB_OBJECT_SET_SECURITY_ATTRIBUTES}
  JOB_OBJECT_ALL_ACCESS              = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $1F );
  {$EXTERNALSYM JOB_OBJECT_ALL_ACCESS}

type
  _JOB_SET_ARRAY = record
    JobHandle: HANDLE;   // Handle to job object to insert
    MemberLevel: DWORD;  // Level of this job in the set. Must be > 0. Can be sparse.
    Flags: DWORD;        // Unused. Must be zero
  end;
  {$EXTERNALSYM _JOB_SET_ARRAY}
  JOB_SET_ARRAY = _JOB_SET_ARRAY;
  {$EXTERNALSYM JOB_SET_ARRAY}
  PJOB_SET_ARRAY = ^JOB_SET_ARRAY;
  {$EXTERNALSYM PJOB_SET_ARRAY}
  TJobSetArray = JOB_SET_ARRAY;
  PJobSetArray = PJOB_SET_ARRAY;

const
  FLS_MAXIMUM_AVAILABLE = 128;
  {$EXTERNALSYM FLS_MAXIMUM_AVAILABLE}
  TLS_MINIMUM_AVAILABLE = 64;
  {$EXTERNALSYM TLS_MINIMUM_AVAILABLE}

type
  PEXCEPTION_REGISTRATION_RECORD = ^EXCEPTION_REGISTRATION_RECORD;
  _EXCEPTION_REGISTRATION_RECORD = packed record
    pNext: PEXCEPTION_REGISTRATION_RECORD;
    pfnHandler: FARPROC;
  end;
  EXCEPTION_REGISTRATION_RECORD = _EXCEPTION_REGISTRATION_RECORD;
  TExceptionRegistrationRecord = EXCEPTION_REGISTRATION_RECORD;
  PExceptionRegistrationRecord = PEXCEPTION_REGISTRATION_RECORD;

  PNT_TIB = ^NT_TIB;
  {$EXTERNALSYM PNT_TIB}
  _NT_TIB = record
    ExceptionList: PEXCEPTION_REGISTRATION_RECORD; // 00h Head of exception record list
    StackBase: PVOID;     // 04h Top of user stack
    StackLimit: PVOID;    // 08h Base of user stack

    //union                       // 0Ch (NT/Win95 differences)
    //{
    //    struct  // Win95 fields
    //    {
    //        WORD    pvTDB;         // 0Ch TDB
    //        WORD    pvThunkSS;     // 0Eh SS selector used for thunking to 16 bits
    //        DWORD   unknown1;      // 10h
    //    } WIN95;
    //
    //    struct  // WinNT fields
    //    {

    SubSystemTib: PVOID;     // 0Ch

    Union: record             // 10H
    case Integer of
      0: (FiberData: PVOID);
      1: (Version: DWORD);
    end;

    //    } WINNT;
    //} TIB_UNION1;

    ArbitraryUserPointer: PVOID;      // 14h Available for application use
    Self: PNT_TIB;          // 18h Linear address of TIB structure

    //union                       // 1Ch (NT/Win95 differences)
    //{
    //    struct  // Win95 fields
    //    {
    //        WORD    TIBFlags;           // 1Ch
    //        WORD    Win16MutexCount;    // 1Eh
    //        DWORD   DebugContext;       // 20h
    //        DWORD   pCurrentPriority;   // 24h
    //        DWORD   pvQueue;            // 28h Message Queue selector
    //    } WIN95;
    //
    //    struct  // WinNT fields
    //    {

    unknown1: DWORD;             // 1Ch
    processID: DWORD;            // 20h
    threadID: DWORD;             // 24h
    unknown2: DWORD;             // 28h

    //    } WINNT;
    //} TIB_UNION2;

    pvTLSArray: PVOID;          // (PPVOID!) 2Ch Thread Local Storage array

    //union                      // 30h (NT/Win95 differences)
    //{
    //    struct  // Win95 fields
    //    {
    //        PVOID*  pProcess;  // 30h Pointer to owning process database
    //    } WIN95;
    //} TIB_UNION3;
  end;
  {$EXTERNALSYM _NT_TIB}
  NT_TIB = _NT_TIB;
  {$EXTERNALSYM NT_TIB}
  TNtTib = NT_TIB;
  PNtTib = ^TNtTib;

//
// 32 and 64 bit specific version for wow64 and the debugger
//

  PNT_TIB32 = ^NT_TIB32;
  {$EXTERNALSYM PNT_TIB32}
  _NT_TIB32 = record
    ExceptionList: DWORD;
    StackBase: DWORD;
    StackLimit: DWORD;
    SubSystemTib: DWORD;
    Union: record
    case Integer of
      0: (FiberData: DWORD);
      1: (Version: DWORD);
    end;
    ArbitraryUserPointer: DWORD;
    Self: DWORD;
  end;
  {$EXTERNALSYM _NT_TIB32}
  NT_TIB32 = _NT_TIB32;
  {$EXTERNALSYM NT_TIB32}
  TNtTib32 = NT_TIB32;
  PNtTib32 = ^TNtTib32;

  PNT_TIB64 = ^NT_TIB64;
  {$EXTERNALSYM PNT_TIB64}
  _NT_TIB64 = record
    ExceptionList: DWORD64;
    StackBase: DWORD64;
    StackLimit: DWORD64;
    SubSystemTib: DWORD64;
    Union: record
    case Integer of
      0: (FiberData: DWORD64);
      1: (Version: DWORD);
    end;
    ArbitraryUserPointer: DWORD64;
    Self: DWORD64;
  end;
  {$EXTERNALSYM _NT_TIB64}
  NT_TIB64 = _NT_TIB64;
  {$EXTERNALSYM NT_TIB64}
  TNtTib64 = NT_TIB64;
  PNtTib64 = ^TNtTib64;

//
// Define function to return the current Thread Environment Block
//

function NtCurrentTeb: PNT_TIB;
{$EXTERNALSYM NtCurrentTeb}

const
  THREAD_BASE_PRIORITY_LOWRT = 15;         // value that gets a thread to LowRealtime-1
  {$EXTERNALSYM THREAD_BASE_PRIORITY_LOWRT}
  THREAD_BASE_PRIORITY_MAX   = 2;          // maximum thread base priority boost
  {$EXTERNALSYM THREAD_BASE_PRIORITY_MAX}
  THREAD_BASE_PRIORITY_MIN   = DWORD(-2);  // minimum thread base priority boost
  {$EXTERNALSYM THREAD_BASE_PRIORITY_MIN}
  THREAD_BASE_PRIORITY_IDLE  = DWORD(-15); // value that gets a thread to idle
  {$EXTERNALSYM THREAD_BASE_PRIORITY_IDLE}

type
  PQUOTA_LIMITS = ^QUOTA_LIMITS;
  {$EXTERNALSYM PQUOTA_LIMITS}
  _QUOTA_LIMITS = record
    PagedPoolLimit: SIZE_T;
    NonPagedPoolLimit: SIZE_T;
    MinimumWorkingSetSize: SIZE_T;
    MaximumWorkingSetSize: SIZE_T;
    PagefileLimit: SIZE_T;
    TimeLimit: LARGE_INTEGER;
  end;
  {$EXTERNALSYM _QUOTA_LIMITS}
  QUOTA_LIMITS = _QUOTA_LIMITS;
  {$EXTERNALSYM QUOTA_LIMITS}
  TQuotaLimits = QUOTA_LIMITS;
  PQuotaLimits = PQUOTA_LIMITS;

const
  QUOTA_LIMITS_HARDWS_MIN_ENABLE  = $00000001;
  {$EXTERNALSYM QUOTA_LIMITS_HARDWS_MIN_ENABLE}
  QUOTA_LIMITS_HARDWS_MIN_DISABLE = $00000002;
  {$EXTERNALSYM QUOTA_LIMITS_HARDWS_MIN_DISABLE}
  QUOTA_LIMITS_HARDWS_MAX_ENABLE  = $00000004;
  {$EXTERNALSYM QUOTA_LIMITS_HARDWS_MAX_ENABLE}
  QUOTA_LIMITS_HARDWS_MAX_DISABLE = $00000008;
  {$EXTERNALSYM QUOTA_LIMITS_HARDWS_MAX_DISABLE}

type
  _QUOTA_LIMITS_EX = record
    PagedPoolLimit: SIZE_T;
    NonPagedPoolLimit: SIZE_T;
    MinimumWorkingSetSize: SIZE_T;
    MaximumWorkingSetSize: SIZE_T;
    PagefileLimit: SIZE_T;
    TimeLimit: LARGE_INTEGER;
    Reserved1: SIZE_T;
    Reserved2: SIZE_T;
    Reserved3: SIZE_T;
    Reserved4: SIZE_T;
    Flags: DWORD;
    Reserved5: DWORD;
  end;
  {$EXTERNALSYM _QUOTA_LIMITS_EX}
  QUOTA_LIMITS_EX = _QUOTA_LIMITS_EX;
  {$EXTERNALSYM QUOTA_LIMITS_EX}
  PQUOTA_LIMITS_EX = ^QUOTA_LIMITS_EX;
  {$EXTERNALSYM PQUOTA_LIMITS_EX}
  TQuotaLimitsEx = QUOTA_LIMITS_EX;
  PQuotaLimitsEx = PQUOTA_LIMITS_EX;  

  PIO_COUNTERS = ^IO_COUNTERS;
  {$EXTERNALSYM PIO_COUNTERS}
  _IO_COUNTERS = record
    ReadOperationCount: Int64;
    WriteOperationCount: Int64;
    OtherOperationCount: Int64;
    ReadTransferCount: Int64;
    WriteTransferCount: Int64;
    OtherTransferCount: Int64;
  end;
  {$EXTERNALSYM _IO_COUNTERS}
  IO_COUNTERS = _IO_COUNTERS;
  {$EXTERNALSYM IO_COUNTERS}
  TIoCounters = IO_COUNTERS;
  PIoCounters = PIO_COUNTERS;

  PJOBOBJECT_BASIC_ACCOUNTING_INFORMATION = ^JOBOBJECT_BASIC_ACCOUNTING_INFORMATION;
  {$EXTERNALSYM PJOBOBJECT_BASIC_ACCOUNTING_INFORMATION}
  _JOBOBJECT_BASIC_ACCOUNTING_INFORMATION = record
    TotalUserTime: LARGE_INTEGER;
    TotalKernelTime: LARGE_INTEGER;
    ThisPeriodTotalUserTime: LARGE_INTEGER;
    ThisPeriodTotalKernelTime: LARGE_INTEGER;
    TotalPageFaultCount: DWORD;
    TotalProcesses: DWORD;
    ActiveProcesses: DWORD;
    TotalTerminatedProcesses: DWORD;
  end;
  {$EXTERNALSYM _JOBOBJECT_BASIC_ACCOUNTING_INFORMATION}
  JOBOBJECT_BASIC_ACCOUNTING_INFORMATION = _JOBOBJECT_BASIC_ACCOUNTING_INFORMATION;
  {$EXTERNALSYM JOBOBJECT_BASIC_ACCOUNTING_INFORMATION}
  TJobObjectBasicAccountingInformation = JOBOBJECT_BASIC_ACCOUNTING_INFORMATION;
  PJobObjectBasicAccountingInformation = PJOBOBJECT_BASIC_ACCOUNTING_INFORMATION;

  PJOBOBJECT_BASIC_LIMIT_INFORMATION = ^JOBOBJECT_BASIC_LIMIT_INFORMATION;
  {$EXTERNALSYM PJOBOBJECT_BASIC_LIMIT_INFORMATION}
  _JOBOBJECT_BASIC_LIMIT_INFORMATION = record
    PerProcessUserTimeLimit: LARGE_INTEGER;
    PerJobUserTimeLimit: LARGE_INTEGER;
    LimitFlags: DWORD;
    MinimumWorkingSetSize: SIZE_T;
    MaximumWorkingSetSize: SIZE_T;
    ActiveProcessLimit: DWORD;
    Affinity: ULONG_PTR;
    PriorityClass: DWORD;
    SchedulingClass: DWORD;
  end;
  {$EXTERNALSYM _JOBOBJECT_BASIC_LIMIT_INFORMATION}
  JOBOBJECT_BASIC_LIMIT_INFORMATION = _JOBOBJECT_BASIC_LIMIT_INFORMATION;
  {$EXTERNALSYM JOBOBJECT_BASIC_LIMIT_INFORMATION}
  TJobObjectBasicLimitInformation = JOBOBJECT_BASIC_LIMIT_INFORMATION;
  PJobObjectBasicLimitInformation = PJOBOBJECT_BASIC_LIMIT_INFORMATION;

  PJOBOBJECT_EXTENDED_LIMIT_INFORMATION = ^JOBOBJECT_EXTENDED_LIMIT_INFORMATION;
  {$EXTERNALSYM PJOBOBJECT_EXTENDED_LIMIT_INFORMATION}
  _JOBOBJECT_EXTENDED_LIMIT_INFORMATION = record
    BasicLimitInformation: JOBOBJECT_BASIC_LIMIT_INFORMATION;
    IoInfo: IO_COUNTERS;
    ProcessMemoryLimit: SIZE_T;
    JobMemoryLimit: SIZE_T;
    PeakProcessMemoryUsed: SIZE_T;
    PeakJobMemoryUsed: SIZE_T;
  end;
  {$EXTERNALSYM _JOBOBJECT_EXTENDED_LIMIT_INFORMATION}
  JOBOBJECT_EXTENDED_LIMIT_INFORMATION = _JOBOBJECT_EXTENDED_LIMIT_INFORMATION;
  {$EXTERNALSYM JOBOBJECT_EXTENDED_LIMIT_INFORMATION}
  TJobObjectExtendedLimitInformation = JOBOBJECT_EXTENDED_LIMIT_INFORMATION;
  PJobObjectExtendedLimitInformation = PJOBOBJECT_EXTENDED_LIMIT_INFORMATION;

  PJOBOBJECT_BASIC_PROCESS_ID_LIST = ^JOBOBJECT_BASIC_PROCESS_ID_LIST;
  {$EXTERNALSYM PJOBOBJECT_BASIC_PROCESS_ID_LIST}
  _JOBOBJECT_BASIC_PROCESS_ID_LIST = record
    NumberOfAssignedProcesses: DWORD;
    NumberOfProcessIdsInList: DWORD;
    ProcessIdList: array [0..0] of ULONG_PTR;
  end;
  {$EXTERNALSYM _JOBOBJECT_BASIC_PROCESS_ID_LIST}
  JOBOBJECT_BASIC_PROCESS_ID_LIST = _JOBOBJECT_BASIC_PROCESS_ID_LIST;
  {$EXTERNALSYM JOBOBJECT_BASIC_PROCESS_ID_LIST}
  TJobObjectBasicProcessIdList = JOBOBJECT_BASIC_PROCESS_ID_LIST;
  PJobObjectBasicProcessIdList = PJOBOBJECT_BASIC_PROCESS_ID_LIST;

  PJOBOBJECT_BASIC_UI_RESTRICTIONS = ^JOBOBJECT_BASIC_UI_RESTRICTIONS;
  {$EXTERNALSYM PJOBOBJECT_BASIC_UI_RESTRICTIONS}
  _JOBOBJECT_BASIC_UI_RESTRICTIONS = record
    UIRestrictionsClass: DWORD;
  end;
  {$EXTERNALSYM _JOBOBJECT_BASIC_UI_RESTRICTIONS}
  JOBOBJECT_BASIC_UI_RESTRICTIONS = _JOBOBJECT_BASIC_UI_RESTRICTIONS;
  {$EXTERNALSYM JOBOBJECT_BASIC_UI_RESTRICTIONS}
  TJobObjectBasicUiRestrictions = JOBOBJECT_BASIC_UI_RESTRICTIONS;
  PJobObjectBasicUiRestrictions = PJOBOBJECT_BASIC_UI_RESTRICTIONS;

  PJOBOBJECT_SECURITY_LIMIT_INFORMATION = ^JOBOBJECT_SECURITY_LIMIT_INFORMATION;
  {$EXTERNALSYM PJOBOBJECT_SECURITY_LIMIT_INFORMATION}
  _JOBOBJECT_SECURITY_LIMIT_INFORMATION = record
    SecurityLimitFlags : DWORD;
    JobToken : THandle;
    SidsToDisable : PTOKEN_GROUPS;
    PrivilegesToDelete : PTOKEN_PRIVILEGES;
    RestrictedSids : PTOKEN_GROUPS;
  end;
  {$EXTERNALSYM _JOBOBJECT_SECURITY_LIMIT_INFORMATION}
  JOBOBJECT_SECURITY_LIMIT_INFORMATION = _JOBOBJECT_SECURITY_LIMIT_INFORMATION;
  {$EXTERNALSYM JOBOBJECT_SECURITY_LIMIT_INFORMATION}
  TJobObjectSecurityLimitInformation = JOBOBJECT_SECURITY_LIMIT_INFORMATION;
  PJobObjectSecurityLimitInformation = PJOBOBJECT_SECURITY_LIMIT_INFORMATION;

  PJOBOBJECT_END_OF_JOB_TIME_INFORMATION = ^JOBOBJECT_END_OF_JOB_TIME_INFORMATION;
  {$EXTERNALSYM PJOBOBJECT_END_OF_JOB_TIME_INFORMATION}
  _JOBOBJECT_END_OF_JOB_TIME_INFORMATION = record
    EndOfJobTimeAction: DWORD;
  end;
  {$EXTERNALSYM _JOBOBJECT_END_OF_JOB_TIME_INFORMATION}
  JOBOBJECT_END_OF_JOB_TIME_INFORMATION = _JOBOBJECT_END_OF_JOB_TIME_INFORMATION;
  {$EXTERNALSYM JOBOBJECT_END_OF_JOB_TIME_INFORMATION}
  TJobObjectEndOfJobTimeInformation = JOBOBJECT_END_OF_JOB_TIME_INFORMATION;
  PJobObjectEndOfJobTimeInformation = PJOBOBJECT_END_OF_JOB_TIME_INFORMATION;

  PJOBOBJECT_ASSOCIATE_COMPLETION_PORT = ^JOBOBJECT_ASSOCIATE_COMPLETION_PORT;
  {$EXTERNALSYM PJOBOBJECT_ASSOCIATE_COMPLETION_PORT}
  _JOBOBJECT_ASSOCIATE_COMPLETION_PORT = record
    CompletionKey: Pointer;
    CompletionPort: THandle;
  end;
  {$EXTERNALSYM _JOBOBJECT_ASSOCIATE_COMPLETION_PORT}
  JOBOBJECT_ASSOCIATE_COMPLETION_PORT = _JOBOBJECT_ASSOCIATE_COMPLETION_PORT;
  {$EXTERNALSYM JOBOBJECT_ASSOCIATE_COMPLETION_PORT}
  TJobObjectAssociateCompletionPort = JOBOBJECT_ASSOCIATE_COMPLETION_PORT;
  PJobObjectAssociateCompletionPort = PJOBOBJECT_ASSOCIATE_COMPLETION_PORT;

  PJOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION = ^JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION;
  {$EXTERNALSYM PJOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION}
  _JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION = record
    BasicInfo: JOBOBJECT_BASIC_ACCOUNTING_INFORMATION;
    IoInfo: IO_COUNTERS;
  end;
  {$EXTERNALSYM _JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION}
  JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION = _JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION;
  {$EXTERNALSYM JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION}
  TJobObjectBasicAndIoAccountingInformation = JOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION;
  PJobObjectBasicAndIoAccountingInformation = PJOBOBJECT_BASIC_AND_IO_ACCOUNTING_INFORMATION;

  _JOBOBJECT_JOBSET_INFORMATION = record
    MemberLevel: DWORD;
  end;
  {$EXTERNALSYM _JOBOBJECT_JOBSET_INFORMATION}
  JOBOBJECT_JOBSET_INFORMATION = _JOBOBJECT_JOBSET_INFORMATION;
  {$EXTERNALSYM JOBOBJECT_JOBSET_INFORMATION}
  PJOBOBJECT_JOBSET_INFORMATION = ^JOBOBJECT_JOBSET_INFORMATION;
  {$EXTERNALSYM PJOBOBJECT_JOBSET_INFORMATION}
  TJobObjectSetInformation = JOBOBJECT_JOBSET_INFORMATION;
  PJobObjectSetInformation = PJOBOBJECT_JOBSET_INFORMATION;  

const
  JOB_OBJECT_TERMINATE_AT_END_OF_JOB = 0;
  {$EXTERNALSYM JOB_OBJECT_TERMINATE_AT_END_OF_JOB}
  JOB_OBJECT_POST_AT_END_OF_JOB      = 1;
  {$EXTERNALSYM JOB_OBJECT_POST_AT_END_OF_JOB}

//
// Completion Port Messages for job objects
//
// These values are returned via the lpNumberOfBytesTransferred parameter
//

  JOB_OBJECT_MSG_END_OF_JOB_TIME       = 1;
  {$EXTERNALSYM JOB_OBJECT_MSG_END_OF_JOB_TIME}
  JOB_OBJECT_MSG_END_OF_PROCESS_TIME   = 2;
  {$EXTERNALSYM JOB_OBJECT_MSG_END_OF_PROCESS_TIME}
  JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT  = 3;
  {$EXTERNALSYM JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT}
  JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO   = 4;
  {$EXTERNALSYM JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO}
  JOB_OBJECT_MSG_NEW_PROCESS           = 6;
  {$EXTERNALSYM JOB_OBJECT_MSG_NEW_PROCESS}
  JOB_OBJECT_MSG_EXIT_PROCESS          = 7;
  {$EXTERNALSYM JOB_OBJECT_MSG_EXIT_PROCESS}
  JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS = 8;
  {$EXTERNALSYM JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS}
  JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT  = 9;
  {$EXTERNALSYM JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT}
  JOB_OBJECT_MSG_JOB_MEMORY_LIMIT      = 10;
  {$EXTERNALSYM JOB_OBJECT_MSG_JOB_MEMORY_LIMIT}

//
// Basic Limits
//

  JOB_OBJECT_LIMIT_WORKINGSET        = $00000001;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_WORKINGSET}
  JOB_OBJECT_LIMIT_PROCESS_TIME      = $00000002;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_PROCESS_TIME}
  JOB_OBJECT_LIMIT_JOB_TIME          = $00000004;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_JOB_TIME}
  JOB_OBJECT_LIMIT_ACTIVE_PROCESS    = $00000008;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_ACTIVE_PROCESS}
  JOB_OBJECT_LIMIT_AFFINITY          = $00000010;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_AFFINITY}
  JOB_OBJECT_LIMIT_PRIORITY_CLASS    = $00000020;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_PRIORITY_CLASS}
  JOB_OBJECT_LIMIT_PRESERVE_JOB_TIME = $00000040;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_PRESERVE_JOB_TIME}
  JOB_OBJECT_LIMIT_SCHEDULING_CLASS  = $00000080;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_SCHEDULING_CLASS}

//
// Extended Limits
//

  JOB_OBJECT_LIMIT_PROCESS_MEMORY             = $00000100;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_PROCESS_MEMORY}
  JOB_OBJECT_LIMIT_JOB_MEMORY                 = $00000200;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_JOB_MEMORY}
  JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION = $00000400;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION}
  JOB_OBJECT_LIMIT_BREAKAWAY_OK               = $00000800;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_BREAKAWAY_OK}
  JOB_OBJECT_LIMIT_SILENT_BREAKAWAY_OK        = $00001000;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_SILENT_BREAKAWAY_OK}
  JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE          = $00002000;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE}

  JOB_OBJECT_LIMIT_RESERVED2 = $00004000;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_RESERVED2}
  JOB_OBJECT_LIMIT_RESERVED3 = $00008000;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_RESERVED3}
  JOB_OBJECT_LIMIT_RESERVED4 = $00010000;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_RESERVED4}
  JOB_OBJECT_LIMIT_RESERVED5 = $00020000;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_RESERVED5}
  JOB_OBJECT_LIMIT_RESERVED6 = $00040000;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_RESERVED6}

  JOB_OBJECT_LIMIT_VALID_FLAGS = $0007ffff;
  {$EXTERNALSYM JOB_OBJECT_LIMIT_VALID_FLAGS}

  JOB_OBJECT_BASIC_LIMIT_VALID_FLAGS    = $000000ff;
  {$EXTERNALSYM JOB_OBJECT_BASIC_LIMIT_VALID_FLAGS}
  JOB_OBJECT_EXTENDED_LIMIT_VALID_FLAGS = $00003fff;
  {$EXTERNALSYM JOB_OBJECT_EXTENDED_LIMIT_VALID_FLAGS}
  JOB_OBJECT_RESERVED_LIMIT_VALID_FLAGS = $0007ffff;
  {$EXTERNALSYM JOB_OBJECT_RESERVED_LIMIT_VALID_FLAGS}

//
// UI restrictions for jobs
//

  JOB_OBJECT_UILIMIT_NONE = $00000000;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_NONE}

  JOB_OBJECT_UILIMIT_HANDLES          = $00000001;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_HANDLES}
  JOB_OBJECT_UILIMIT_READCLIPBOARD    = $00000002;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_READCLIPBOARD}
  JOB_OBJECT_UILIMIT_WRITECLIPBOARD   = $00000004;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_WRITECLIPBOARD}
  JOB_OBJECT_UILIMIT_SYSTEMPARAMETERS = $00000008;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_SYSTEMPARAMETERS}
  JOB_OBJECT_UILIMIT_DISPLAYSETTINGS  = $00000010;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_DISPLAYSETTINGS}
  JOB_OBJECT_UILIMIT_GLOBALATOMS      = $00000020;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_GLOBALATOMS}
  JOB_OBJECT_UILIMIT_DESKTOP          = $00000040;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_DESKTOP}
  JOB_OBJECT_UILIMIT_EXITWINDOWS      = $00000080;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_EXITWINDOWS}

  JOB_OBJECT_UILIMIT_ALL = $000000FF;
  {$EXTERNALSYM JOB_OBJECT_UILIMIT_ALL}

  JOB_OBJECT_UI_VALID_FLAGS = $000000FF;
  {$EXTERNALSYM JOB_OBJECT_UI_VALID_FLAGS}

  JOB_OBJECT_SECURITY_NO_ADMIN         = $00000001;
  {$EXTERNALSYM JOB_OBJECT_SECURITY_NO_ADMIN}
  JOB_OBJECT_SECURITY_RESTRICTED_TOKEN = $00000002;
  {$EXTERNALSYM JOB_OBJECT_SECURITY_RESTRICTED_TOKEN}
  JOB_OBJECT_SECURITY_ONLY_TOKEN       = $00000004;
  {$EXTERNALSYM JOB_OBJECT_SECURITY_ONLY_TOKEN}
  JOB_OBJECT_SECURITY_FILTER_TOKENS    = $00000008;
  {$EXTERNALSYM JOB_OBJECT_SECURITY_FILTER_TOKENS}

  JOB_OBJECT_SECURITY_VALID_FLAGS = $0000000f;
  {$EXTERNALSYM JOB_OBJECT_SECURITY_VALID_FLAGS}

type
  _JOBOBJECTINFOCLASS = (
    JobObjectInfoClassPadding0,
    JobObjectBasicAccountingInformation,
    JobObjectBasicLimitInformation,
    JobObjectBasicProcessIdList,
    JobObjectBasicUIRestrictions,
    JobObjectSecurityLimitInformation,
    JobObjectEndOfJobTimeInformation,
    JobObjectAssociateCompletionPortInformation,
    JobObjectBasicAndIoAccountingInformation,
    JobObjectExtendedLimitInformation,
    JobObjectJobSetInformation,
    MaxJobObjectInfoClass);
  {$EXTERNALSYM _JOBOBJECTINFOCLASS}
  JOBOBJECTINFOCLASS = _JOBOBJECTINFOCLASS;
  {$EXTERNALSYM JOBOBJECTINFOCLASS}
  TJobObjectInfoClass = JOBOBJECTINFOCLASS;

const
  EVENT_MODIFY_STATE = $0002;
  {$EXTERNALSYM EVENT_MODIFY_STATE}
  EVENT_ALL_ACCESS   = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $3);
  {$EXTERNALSYM EVENT_ALL_ACCESS}
  MUTANT_QUERY_STATE = $0001;
  {$EXTERNALSYM MUTANT_QUERY_STATE}

  MUTANT_ALL_ACCESS      = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or MUTANT_QUERY_STATE);
  {$EXTERNALSYM MUTANT_ALL_ACCESS}
  SEMAPHORE_MODIFY_STATE = $0002;
  {$EXTERNALSYM SEMAPHORE_MODIFY_STATE}
  SEMAPHORE_ALL_ACCESS   = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $3);
  {$EXTERNALSYM SEMAPHORE_ALL_ACCESS}

//
// Timer Specific Access Rights.
//

  TIMER_QUERY_STATE  = $0001;
  {$EXTERNALSYM TIMER_QUERY_STATE}
  TIMER_MODIFY_STATE = $0002;
  {$EXTERNALSYM TIMER_MODIFY_STATE}

  TIMER_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or TIMER_QUERY_STATE or TIMER_MODIFY_STATE);
  {$EXTERNALSYM TIMER_ALL_ACCESS}

  TIME_ZONE_ID_UNKNOWN  = 0;
  {$EXTERNALSYM TIME_ZONE_ID_UNKNOWN}
  TIME_ZONE_ID_STANDARD = 1;
  {$EXTERNALSYM TIME_ZONE_ID_STANDARD}
  TIME_ZONE_ID_DAYLIGHT = 2;
  {$EXTERNALSYM TIME_ZONE_ID_DAYLIGHT}

type
  _LOGICAL_PROCESSOR_RELATIONSHIP = (RelationProcessorCore, RelationNumaNode);
  {$EXTERNALSYM _LOGICAL_PROCESSOR_RELATIONSHIP}
  LOGICAL_PROCESSOR_RELATIONSHIP = _LOGICAL_PROCESSOR_RELATIONSHIP;
  {$EXTERNALSYM LOGICAL_PROCESSOR_RELATIONSHIP}
  TLogicalProcessorRelationship = LOGICAL_PROCESSOR_RELATIONSHIP;

const
  LTP_PC_SMT = $1;
  {$EXTERNALSYM LTP_PC_SMT}

type
  _SYSTEM_LOGICAL_PROCESSOR_INFORMATION = record
    ProcessorMask: ULONG_PTR;
    Relationship: LOGICAL_PROCESSOR_RELATIONSHIP;
    case Integer of
      0: (Flags: BYTE); // ProcessorCore
      1: (NodeNumber: DWORD); // NumaNode
      2: (Reserved: array [0..1] of ULONGLONG);
  end;
  {$EXTERNALSYM _SYSTEM_LOGICAL_PROCESSOR_INFORMATION}
  SYSTEM_LOGICAL_PROCESSOR_INFORMATION = _SYSTEM_LOGICAL_PROCESSOR_INFORMATION;
  {$EXTERNALSYM SYSTEM_LOGICAL_PROCESSOR_INFORMATION}
  PSYSTEM_LOGICAL_PROCESSOR_INFORMATION = ^SYSTEM_LOGICAL_PROCESSOR_INFORMATION;
  TSystemLogicalProcessorInformation = SYSTEM_LOGICAL_PROCESSOR_INFORMATION;
  PSystemLogicalProcessorInformation = PSYSTEM_LOGICAL_PROCESSOR_INFORMATION;  

const
  PROCESSOR_INTEL_386     = 386;
  {$EXTERNALSYM PROCESSOR_INTEL_386}
  PROCESSOR_INTEL_486     = 486;
  {$EXTERNALSYM PROCESSOR_INTEL_486}
  PROCESSOR_INTEL_PENTIUM = 586;
  {$EXTERNALSYM PROCESSOR_INTEL_PENTIUM}
  PROCESSOR_INTEL_IA64    = 2200;
  {$EXTERNALSYM PROCESSOR_INTEL_IA64}
  PROCESSOR_AMD_X8664     = 8664;
  {$EXTERNALSYM PROCESSOR_AMD_X8664}
  PROCESSOR_MIPS_R4000    = 4000; // incl R4101 & R3910 for Windows CE
  {$EXTERNALSYM PROCESSOR_MIPS_R4000}
  PROCESSOR_ALPHA_21064   = 21064;
  {$EXTERNALSYM PROCESSOR_ALPHA_21064}
  PROCESSOR_PPC_601       = 601;
  {$EXTERNALSYM PROCESSOR_PPC_601}
  PROCESSOR_PPC_603       = 603;
  {$EXTERNALSYM PROCESSOR_PPC_603}
  PROCESSOR_PPC_604       = 604;
  {$EXTERNALSYM PROCESSOR_PPC_604}
  PROCESSOR_PPC_620       = 620;
  {$EXTERNALSYM PROCESSOR_PPC_620}
  PROCESSOR_HITACHI_SH3   = 10003; // Windows CE
  {$EXTERNALSYM PROCESSOR_HITACHI_SH3}
  PROCESSOR_HITACHI_SH3E  = 10004; // Windows CE
  {$EXTERNALSYM PROCESSOR_HITACHI_SH3E}
  PROCESSOR_HITACHI_SH4   = 10005; // Windows CE
  {$EXTERNALSYM PROCESSOR_HITACHI_SH4}
  PROCESSOR_MOTOROLA_821  = 821; // Windows CE
  {$EXTERNALSYM PROCESSOR_MOTOROLA_821}
  PROCESSOR_SHx_SH3       = 103; // Windows CE
  {$EXTERNALSYM PROCESSOR_SHx_SH3}
  PROCESSOR_SHx_SH4       = 104; // Windows CE
  {$EXTERNALSYM PROCESSOR_SHx_SH4}
  PROCESSOR_STRONGARM     = 2577; // Windows CE - 0xA11
  {$EXTERNALSYM PROCESSOR_STRONGARM}
  PROCESSOR_ARM720        = 1824; // Windows CE - 0x720
  {$EXTERNALSYM PROCESSOR_ARM720}
  PROCESSOR_ARM820        = 2080; // Windows CE - 0x820
  {$EXTERNALSYM PROCESSOR_ARM820}
  PROCESSOR_ARM920        = 2336; // Windows CE - 0x920
  {$EXTERNALSYM PROCESSOR_ARM920}
  PROCESSOR_ARM_7TDMI     = 70001; // Windows CE
  {$EXTERNALSYM PROCESSOR_ARM_7TDMI}
  PROCESSOR_OPTIL         = $494f; // MSIL
  {$EXTERNALSYM PROCESSOR_OPTIL}

  PROCESSOR_ARCHITECTURE_INTEL   = 0;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_INTEL}
  PROCESSOR_ARCHITECTURE_MIPS    = 1;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_MIPS}
  PROCESSOR_ARCHITECTURE_ALPHA   = 2;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_ALPHA}
  PROCESSOR_ARCHITECTURE_PPC     = 3;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_PPC}
  PROCESSOR_ARCHITECTURE_SHX     = 4;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_SHX}
  PROCESSOR_ARCHITECTURE_ARM     = 5;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_ARM}
  PROCESSOR_ARCHITECTURE_IA64    = 6;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_IA64}
  PROCESSOR_ARCHITECTURE_ALPHA64 = 7;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_ALPHA64}
  PROCESSOR_ARCHITECTURE_MSIL    = 8;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_MSIL}
  PROCESSOR_ARCHITECTURE_AMD64         = 9;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_AMD64}
  PROCESSOR_ARCHITECTURE_IA32_ON_WIN64 = 10;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_IA32_ON_WIN64}

  PROCESSOR_ARCHITECTURE_UNKNOWN = $FFFF;
  {$EXTERNALSYM PROCESSOR_ARCHITECTURE_UNKNOWN}

  PF_FLOATING_POINT_PRECISION_ERRATA = 0;
  {$EXTERNALSYM PF_FLOATING_POINT_PRECISION_ERRATA}
  PF_FLOATING_POINT_EMULATED         = 1;
  {$EXTERNALSYM PF_FLOATING_POINT_EMULATED}
  PF_COMPARE_EXCHANGE_DOUBLE         = 2;
  {$EXTERNALSYM PF_COMPARE_EXCHANGE_DOUBLE}
  PF_MMX_INSTRUCTIONS_AVAILABLE      = 3;
  {$EXTERNALSYM PF_MMX_INSTRUCTIONS_AVAILABLE}
  PF_PPC_MOVEMEM_64BIT_OK            = 4;
  {$EXTERNALSYM PF_PPC_MOVEMEM_64BIT_OK}
  PF_ALPHA_BYTE_INSTRUCTIONS         = 5;
  {$EXTERNALSYM PF_ALPHA_BYTE_INSTRUCTIONS}
  PF_XMMI_INSTRUCTIONS_AVAILABLE     = 6;
  {$EXTERNALSYM PF_XMMI_INSTRUCTIONS_AVAILABLE}
  PF_3DNOW_INSTRUCTIONS_AVAILABLE    = 7;
  {$EXTERNALSYM PF_3DNOW_INSTRUCTIONS_AVAILABLE}
  PF_RDTSC_INSTRUCTION_AVAILABLE     = 8;
  {$EXTERNALSYM PF_RDTSC_INSTRUCTION_AVAILABLE}
  PF_PAE_ENABLED                     = 9;
  {$EXTERNALSYM PF_PAE_ENABLED}
  PF_XMMI64_INSTRUCTIONS_AVAILABLE   = 10;
  {$EXTERNALSYM PF_XMMI64_INSTRUCTIONS_AVAILABLE}

type
  PMEMORY_BASIC_INFORMATION = ^MEMORY_BASIC_INFORMATION;
  {$EXTERNALSYM PMEMORY_BASIC_INFORMATION}
  _MEMORY_BASIC_INFORMATION = record
    BaseAddress: Pointer;
    AllocationBase: Pointer;
    AllocationProtect: DWORD;
    RegionSize: SIZE_T;
    State: DWORD;
    Protect: DWORD;
    Type_: DWORD;
  end;
  {$EXTERNALSYM _MEMORY_BASIC_INFORMATION}
  MEMORY_BASIC_INFORMATION = _MEMORY_BASIC_INFORMATION;
  {$EXTERNALSYM MEMORY_BASIC_INFORMATION}
  TMemoryBasicInformation = MEMORY_BASIC_INFORMATION;
  PMemoryBasicInformation = PMEMORY_BASIC_INFORMATION;

  PMEMORY_BASIC_INFORMATION32 = ^MEMORY_BASIC_INFORMATION32;
  {$EXTERNALSYM PMEMORY_BASIC_INFORMATION32}
  _MEMORY_BASIC_INFORMATION32 = record
    BaseAddress: DWORD;
    AllocationBase: DWORD;
    AllocationProtect: DWORD;
    RegionSize: DWORD;
    State: DWORD;
    Protect: DWORD;
    Type_: DWORD;
  end;
  {$EXTERNALSYM _MEMORY_BASIC_INFORMATION32}
  MEMORY_BASIC_INFORMATION32 = _MEMORY_BASIC_INFORMATION32;
  {$EXTERNALSYM MEMORY_BASIC_INFORMATION32}
  TMemoryBasicInformation32 = MEMORY_BASIC_INFORMATION32;
  PMemoryBasicInformation32 = PMEMORY_BASIC_INFORMATION32;

  PMEMORY_BASIC_INFORMATION64 = ^MEMORY_BASIC_INFORMATION64;
  {$EXTERNALSYM PMEMORY_BASIC_INFORMATION64}
  _MEMORY_BASIC_INFORMATION64 = record
    BaseAddress: ULONGLONG;
    AllocationBase: ULONGLONG;
    AllocationProtect: DWORD;
    __alignment1: DWORD;
    RegionSize: ULONGLONG;
    State: DWORD;
    Protect: DWORD;
    Type_: DWORD;
    __alignment2: DWORD;
  end;
  {$EXTERNALSYM _MEMORY_BASIC_INFORMATION64}
  MEMORY_BASIC_INFORMATION64 = _MEMORY_BASIC_INFORMATION64;
  {$EXTERNALSYM MEMORY_BASIC_INFORMATION64}
  TMemoryBasicInformation64 = MEMORY_BASIC_INFORMATION64;
  PMemoryBasicInformation64 = PMEMORY_BASIC_INFORMATION64;

const
  SECTION_QUERY       = $0001;
  {$EXTERNALSYM SECTION_QUERY}
  SECTION_MAP_WRITE   = $0002;
  {$EXTERNALSYM SECTION_MAP_WRITE}
  SECTION_MAP_READ    = $0004;
  {$EXTERNALSYM SECTION_MAP_READ}
  SECTION_MAP_EXECUTE = $0008;
  {$EXTERNALSYM SECTION_MAP_EXECUTE}
  SECTION_EXTEND_SIZE = $0010;
  {$EXTERNALSYM SECTION_EXTEND_SIZE}

  SECTION_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED or SECTION_QUERY or
    SECTION_MAP_WRITE or SECTION_MAP_READ or SECTION_MAP_EXECUTE or
    SECTION_EXTEND_SIZE);
  {$EXTERNALSYM SECTION_ALL_ACCESS}

  PAGE_NOACCESS          = $01;
  {$EXTERNALSYM PAGE_NOACCESS}
  PAGE_READONLY          = $02;
  {$EXTERNALSYM PAGE_READONLY}
  PAGE_READWRITE         = $04;
  {$EXTERNALSYM PAGE_READWRITE}
  PAGE_WRITECOPY         = $08;
  {$EXTERNALSYM PAGE_WRITECOPY}
  PAGE_EXECUTE           = $10;
  {$EXTERNALSYM PAGE_EXECUTE}
  PAGE_EXECUTE_READ      = $20;
  {$EXTERNALSYM PAGE_EXECUTE_READ}
  PAGE_EXECUTE_READWRITE = $40;
  {$EXTERNALSYM PAGE_EXECUTE_READWRITE}
  PAGE_EXECUTE_WRITECOPY = $80;
  {$EXTERNALSYM PAGE_EXECUTE_WRITECOPY}
  PAGE_GUARD             = $100;
  {$EXTERNALSYM PAGE_GUARD}
  PAGE_NOCACHE           = $200;
  {$EXTERNALSYM PAGE_NOCACHE}
  PAGE_WRITECOMBINE      = $400;
  {$EXTERNALSYM PAGE_WRITECOMBINE}
  MEM_COMMIT             = $1000;
  {$EXTERNALSYM MEM_COMMIT}
  MEM_RESERVE            = $2000;
  {$EXTERNALSYM MEM_RESERVE}
  MEM_DECOMMIT           = $4000;
  {$EXTERNALSYM MEM_DECOMMIT}
  MEM_RELEASE            = $8000;
  {$EXTERNALSYM MEM_RELEASE}
  MEM_FREE               = $10000;
  {$EXTERNALSYM MEM_FREE}
  MEM_PRIVATE            = $20000;
  {$EXTERNALSYM MEM_PRIVATE}
  MEM_MAPPED             = $40000;
  {$EXTERNALSYM MEM_MAPPED}
  MEM_RESET              = $80000;
  {$EXTERNALSYM MEM_RESET}
  MEM_TOP_DOWN           = $100000;
  {$EXTERNALSYM MEM_TOP_DOWN}
  MEM_WRITE_WATCH        = $200000;
  {$EXTERNALSYM MEM_WRITE_WATCH}
  MEM_PHYSICAL           = $400000;
  {$EXTERNALSYM MEM_PHYSICAL}
  MEM_LARGE_PAGES        = $20000000;
  {$EXTERNALSYM MEM_LARGE_PAGES}
  MEM_4MB_PAGES          = DWORD($80000000);
  {$EXTERNALSYM MEM_4MB_PAGES}
  SEC_FILE               = $800000;
  {$EXTERNALSYM SEC_FILE}
  SEC_IMAGE              = $1000000;
  {$EXTERNALSYM SEC_IMAGE}
  SEC_RESERVE            = $4000000;
  {$EXTERNALSYM SEC_RESERVE}
  SEC_COMMIT             = DWORD($8000000);
  {$EXTERNALSYM SEC_COMMIT}
  SEC_NOCACHE            = $10000000;
  {$EXTERNALSYM SEC_NOCACHE}
  MEM_IMAGE              = SEC_IMAGE;
  {$EXTERNALSYM MEM_IMAGE}
  WRITE_WATCH_FLAG_RESET = $01;
  {$EXTERNALSYM WRITE_WATCH_FLAG_RESET}

//
// Define access rights to files and directories
//

//
// The FILE_READ_DATA and FILE_WRITE_DATA constants are also defined in
// devioctl.h as FILE_READ_ACCESS and FILE_WRITE_ACCESS. The values for these
// constants *MUST* always be in sync.
// The values are redefined in devioctl.h because they must be available to
// both DOS and NT.
//

  FILE_READ_DATA            = ($0001); // file & pipe
  {$EXTERNALSYM FILE_READ_DATA}
  FILE_LIST_DIRECTORY       = ($0001); // directory
  {$EXTERNALSYM FILE_LIST_DIRECTORY}

  FILE_WRITE_DATA           = ($0002); // file & pipe
  {$EXTERNALSYM FILE_WRITE_DATA}
  FILE_ADD_FILE             = ($0002); // directory
  {$EXTERNALSYM FILE_ADD_FILE}

  FILE_APPEND_DATA          = ($0004); // file
  {$EXTERNALSYM FILE_APPEND_DATA}
  FILE_ADD_SUBDIRECTORY     = ($0004); // directory
  {$EXTERNALSYM FILE_ADD_SUBDIRECTORY}
  FILE_CREATE_PIPE_INSTANCE = ($0004); // named pipe
  {$EXTERNALSYM FILE_CREATE_PIPE_INSTANCE}

  FILE_READ_EA = ($0008); // file & directory
  {$EXTERNALSYM FILE_READ_EA}

  FILE_WRITE_EA = ($0010); // file & directory
  {$EXTERNALSYM FILE_WRITE_EA}

  FILE_EXECUTE = ($0020); // file
  {$EXTERNALSYM FILE_EXECUTE}
  FILE_TRAVERSE = ($0020); // directory
  {$EXTERNALSYM FILE_TRAVERSE}

  FILE_DELETE_CHILD = ($0040); // directory
  {$EXTERNALSYM FILE_DELETE_CHILD}

  FILE_READ_ATTRIBUTES = ($0080); // all
  {$EXTERNALSYM FILE_READ_ATTRIBUTES}

  FILE_WRITE_ATTRIBUTES = ($0100); // all
  {$EXTERNALSYM FILE_WRITE_ATTRIBUTES}

  FILE_ALL_ACCESS = (STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $1FF);
  {$EXTERNALSYM FILE_ALL_ACCESS}

  FILE_GENERIC_READ = (STANDARD_RIGHTS_READ or FILE_READ_DATA or
    FILE_READ_ATTRIBUTES or FILE_READ_EA or SYNCHRONIZE);
  {$EXTERNALSYM FILE_GENERIC_READ}

  FILE_GENERIC_WRITE = (STANDARD_RIGHTS_WRITE or FILE_WRITE_DATA or
    FILE_WRITE_ATTRIBUTES or FILE_WRITE_EA or FILE_APPEND_DATA or SYNCHRONIZE);
  {$EXTERNALSYM FILE_GENERIC_WRITE}

  FILE_GENERIC_EXECUTE = (STANDARD_RIGHTS_EXECUTE or FILE_READ_ATTRIBUTES or
    FILE_EXECUTE or SYNCHRONIZE);
  {$EXTERNALSYM FILE_GENERIC_EXECUTE}

  FILE_SHARE_READ                    = $00000001;
  {$EXTERNALSYM FILE_SHARE_READ}
  FILE_SHARE_WRITE                   = $00000002;
  {$EXTERNALSYM FILE_SHARE_WRITE}
  FILE_SHARE_DELETE                  = $00000004;
  {$EXTERNALSYM FILE_SHARE_DELETE}
  FILE_ATTRIBUTE_READONLY            = $00000001;
  {$EXTERNALSYM FILE_ATTRIBUTE_READONLY}
  FILE_ATTRIBUTE_HIDDEN              = $00000002;
  {$EXTERNALSYM FILE_ATTRIBUTE_HIDDEN}
  FILE_ATTRIBUTE_SYSTEM              = $00000004;
  {$EXTERNALSYM FILE_ATTRIBUTE_SYSTEM}
  FILE_ATTRIBUTE_DIRECTORY           = $00000010;
  {$EXTERNALSYM FILE_ATTRIBUTE_DIRECTORY}
  FILE_ATTRIBUTE_ARCHIVE             = $00000020;
  {$EXTERNALSYM FILE_ATTRIBUTE_ARCHIVE}
  FILE_ATTRIBUTE_DEVICE              = $00000040;
  {$EXTERNALSYM FILE_ATTRIBUTE_DEVICE}
  FILE_ATTRIBUTE_NORMAL              = $00000080;
  {$EXTERNALSYM FILE_ATTRIBUTE_NORMAL}
  FILE_ATTRIBUTE_TEMPORARY           = $00000100;
  {$EXTERNALSYM FILE_ATTRIBUTE_TEMPORARY}
  FILE_ATTRIBUTE_SPARSE_FILE         = $00000200;
  {$EXTERNALSYM FILE_ATTRIBUTE_SPARSE_FILE}
  FILE_ATTRIBUTE_REPARSE_POINT       = $00000400;
  {$EXTERNALSYM FILE_ATTRIBUTE_REPARSE_POINT}
  FILE_ATTRIBUTE_COMPRESSED          = $00000800;
  {$EXTERNALSYM FILE_ATTRIBUTE_COMPRESSED}
  FILE_ATTRIBUTE_OFFLINE             = $00001000;
  {$EXTERNALSYM FILE_ATTRIBUTE_OFFLINE}
  FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = $00002000;
  {$EXTERNALSYM FILE_ATTRIBUTE_NOT_CONTENT_INDEXED}
  FILE_ATTRIBUTE_ENCRYPTED           = $00004000;
  {$EXTERNALSYM FILE_ATTRIBUTE_ENCRYPTED}
  FILE_NOTIFY_CHANGE_FILE_NAME       = $00000001;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_FILE_NAME}
  FILE_NOTIFY_CHANGE_DIR_NAME        = $00000002;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_DIR_NAME}
  FILE_NOTIFY_CHANGE_ATTRIBUTES      = $00000004;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_ATTRIBUTES}
  FILE_NOTIFY_CHANGE_SIZE            = $00000008;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_SIZE}
  FILE_NOTIFY_CHANGE_LAST_WRITE      = $00000010;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_LAST_WRITE}
  FILE_NOTIFY_CHANGE_LAST_ACCESS     = $00000020;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_LAST_ACCESS}
  FILE_NOTIFY_CHANGE_CREATION        = $00000040;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_CREATION}
  FILE_NOTIFY_CHANGE_SECURITY        = $00000100;
  {$EXTERNALSYM FILE_NOTIFY_CHANGE_SECURITY}
  FILE_ACTION_ADDED                  = $00000001;
  {$EXTERNALSYM FILE_ACTION_ADDED}
  FILE_ACTION_REMOVED                = $00000002;
  {$EXTERNALSYM FILE_ACTION_REMOVED}
  FILE_ACTION_MODIFIED               = $00000003;
  {$EXTERNALSYM FILE_ACTION_MODIFIED}
  FILE_ACTION_RENAMED_OLD_NAME       = $00000004;
  {$EXTERNALSYM FILE_ACTION_RENAMED_OLD_NAME}
  FILE_ACTION_RENAMED_NEW_NAME       = $00000005;
  {$EXTERNALSYM FILE_ACTION_RENAMED_NEW_NAME}
  MAILSLOT_NO_MESSAGE                = DWORD(-1);
  {$EXTERNALSYM MAILSLOT_NO_MESSAGE}
  MAILSLOT_WAIT_FOREVER              = DWORD(-1);
  {$EXTERNALSYM MAILSLOT_WAIT_FOREVER}
  FILE_CASE_SENSITIVE_SEARCH         = $00000001;
  {$EXTERNALSYM FILE_CASE_SENSITIVE_SEARCH}
  FILE_CASE_PRESERVED_NAMES          = $00000002;
  {$EXTERNALSYM FILE_CASE_PRESERVED_NAMES}
  FILE_UNICODE_ON_DISK               = $00000004;
  {$EXTERNALSYM FILE_UNICODE_ON_DISK}
  FILE_PERSISTENT_ACLS               = $00000008;
  {$EXTERNALSYM FILE_PERSISTENT_ACLS}
  FILE_FILE_COMPRESSION              = $00000010;
  {$EXTERNALSYM FILE_FILE_COMPRESSION}
  FILE_VOLUME_QUOTAS                 = $00000020;
  {$EXTERNALSYM FILE_VOLUME_QUOTAS}
  FILE_SUPPORTS_SPARSE_FILES         = $00000040;
  {$EXTERNALSYM FILE_SUPPORTS_SPARSE_FILES}
  FILE_SUPPORTS_REPARSE_POINTS       = $00000080;
  {$EXTERNALSYM FILE_SUPPORTS_REPARSE_POINTS}
  FILE_SUPPORTS_REMOTE_STORAGE       = $00000100;
  {$EXTERNALSYM FILE_SUPPORTS_REMOTE_STORAGE}
  FILE_VOLUME_IS_COMPRESSED          = $00008000;
  {$EXTERNALSYM FILE_VOLUME_IS_COMPRESSED}
  FILE_SUPPORTS_OBJECT_IDS           = $00010000;
  {$EXTERNALSYM FILE_SUPPORTS_OBJECT_IDS}
  FILE_SUPPORTS_ENCRYPTION           = $00020000;
  {$EXTERNALSYM FILE_SUPPORTS_ENCRYPTION}
  FILE_NAMED_STREAMS                 = $00040000;
  {$EXTERNALSYM FILE_NAMED_STREAMS}
  FILE_READ_ONLY_VOLUME              = $00080000;
  {$EXTERNALSYM FILE_READ_ONLY_VOLUME}

//
// Define the file notification information structure
//

type
  PFILE_NOTIFY_INFORMATION = ^FILE_NOTIFY_INFORMATION;
  {$EXTERNALSYM PFILE_NOTIFY_INFORMATION}
  _FILE_NOTIFY_INFORMATION = record
    NextEntryOffset: DWORD;
    Action: DWORD;
    FileNameLength: DWORD;
    FileName: array [0..0] of WCHAR;
  end;
  {$EXTERNALSYM _FILE_NOTIFY_INFORMATION}
  FILE_NOTIFY_INFORMATION = _FILE_NOTIFY_INFORMATION;
  {$EXTERNALSYM FILE_NOTIFY_INFORMATION}
  TFileNotifyInformation = FILE_NOTIFY_INFORMATION;
  PFileNotifyInformation = PFILE_NOTIFY_INFORMATION;

//
// Define segement buffer structure for scatter/gather read/write.
//

type
  PFILE_SEGMENT_ELEMENT = ^FILE_SEGMENT_ELEMENT;
  {$EXTERNALSYM PFILE_SEGMENT_ELEMENT}
  _FILE_SEGMENT_ELEMENT = record
    case Integer of
      0: (Buffer: PVOID64);
      1: (Alignment: ULONGLONG);
  end;
  {$EXTERNALSYM _FILE_SEGMENT_ELEMENT}
  FILE_SEGMENT_ELEMENT = _FILE_SEGMENT_ELEMENT;
  {$EXTERNALSYM FILE_SEGMENT_ELEMENT}
  TFileSegmentElement = FILE_SEGMENT_ELEMENT;
  PFileSegmentElement = PFILE_SEGMENT_ELEMENT;

//
// The reparse GUID structure is used by all 3rd party layered drivers to
// store data in a reparse point. For non-Microsoft tags, The GUID field
// cannot be GUID_NULL.
// The constraints on reparse tags are defined below.
// Microsoft tags can also be used with this format of the reparse point buffer.
//
  TGenericReparseBuffer = record
    DataBuffer: array [0..0] of BYTE;
  end;

  PREPARSE_GUID_DATA_BUFFER = ^REPARSE_GUID_DATA_BUFFER;
  {$EXTERNALSYM PREPARSE_GUID_DATA_BUFFER}
  _REPARSE_GUID_DATA_BUFFER = record
    ReparseTag: DWORD;
    ReparseDataLength: WORD;
    Reserved: WORD;
    ReparseGuid: GUID;
    GenericReparseBuffer: TGenericReparseBuffer;
  end;
  {$EXTERNALSYM _REPARSE_GUID_DATA_BUFFER}
  REPARSE_GUID_DATA_BUFFER = _REPARSE_GUID_DATA_BUFFER;
  {$EXTERNALSYM REPARSE_GUID_DATA_BUFFER}
  TReparseGuidDataBuffer = REPARSE_GUID_DATA_BUFFER;
  PReparseGuidDataBuffer = PREPARSE_GUID_DATA_BUFFER;

const
  REPARSE_GUID_DATA_BUFFER_HEADER_SIZE = 24;
  {$EXTERNALSYM REPARSE_GUID_DATA_BUFFER_HEADER_SIZE}
//
// Maximum allowed size of the reparse data.
//

const
  MAXIMUM_REPARSE_DATA_BUFFER_SIZE = 16 * 1024;
  {$EXTERNALSYM MAXIMUM_REPARSE_DATA_BUFFER_SIZE}

//
// Predefined reparse tags.
// These tags need to avoid conflicting with IO_REMOUNT defined in ntos\inc\io.h
//

  IO_REPARSE_TAG_RESERVED_ZERO = (0);
  {$EXTERNALSYM IO_REPARSE_TAG_RESERVED_ZERO}
  IO_REPARSE_TAG_RESERVED_ONE  = (1);
  {$EXTERNALSYM IO_REPARSE_TAG_RESERVED_ONE}

//
// The value of the following constant needs to satisfy the following conditions:
//  (1) Be at least as large as the largest of the reserved tags.
//  (2) Be strictly smaller than all the tags in use.
//

  IO_REPARSE_TAG_RESERVED_RANGE = IO_REPARSE_TAG_RESERVED_ONE;
  {$EXTERNALSYM IO_REPARSE_TAG_RESERVED_RANGE}

//
// The reparse tags are a DWORD. The 32 bits are laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-----------------------+-------------------------------+
//  |M|R|N|R|     Reserved bits     |       Reparse Tag Value       |
//  +-+-+-+-+-----------------------+-------------------------------+
//
// M is the Microsoft bit. When set to 1, it denotes a tag owned by Microsoft.
//   All ISVs must use a tag with a 0 in this position.
//   Note: If a Microsoft tag is used by non-Microsoft software, the
//   behavior is not defined.
//
// R is reserved.  Must be zero for non-Microsoft tags.
//
// N is name surrogate. When set to 1, the file represents another named
//   entity in the system.
//
// The M and N bits are OR-able.
// The following macros check for the M and N bit values:
//

//
// Macro to determine whether a reparse point tag corresponds to a tag
// owned by Microsoft.
//

function IsReparseTagMicrosoft(Tag: ULONG): Boolean;
{$EXTERNALSYM IsReparseTagMicrosoft}

//
// Macro to determine whether a reparse point tag corresponds to a file
// that is to be displayed with the slow icon overlay.
//

function IsReparseTagHighLatency(Tag: ULONG): Boolean;
{$EXTERNALSYM IsReparseTagHighLatency}

//
// Macro to determine whether a reparse point tag is a name surrogate
//

function IsReparseTagNameSurrogate(Tag: ULONG): Boolean;
{$EXTERNALSYM IsReparseTagNameSurrogate}

const
  IO_REPARSE_TAG_MOUNT_POINT = DWORD($A0000003);
  {$EXTERNALSYM IO_REPARSE_TAG_MOUNT_POINT}
  IO_REPARSE_TAG_HSM         = DWORD($C0000004);
  {$EXTERNALSYM IO_REPARSE_TAG_HSM}
  IO_REPARSE_TAG_SIS         = DWORD($80000007);
  {$EXTERNALSYM IO_REPARSE_TAG_SIS}
  IO_REPARSE_TAG_DFS         = DWORD($8000000A);
  {$EXTERNALSYM IO_REPARSE_TAG_DFS}
  IO_REPARSE_TAG_FILTER_MANAGER = DWORD($8000000B);
  {$EXTERNALSYM IO_REPARSE_TAG_FILTER_MANAGER}
  IO_COMPLETION_MODIFY_STATE = $0002;
  {$EXTERNALSYM IO_COMPLETION_MODIFY_STATE}
  IO_COMPLETION_ALL_ACCESS   = DWORD(STANDARD_RIGHTS_REQUIRED or SYNCHRONIZE or $3);
  {$EXTERNALSYM IO_COMPLETION_ALL_ACCESS}
  DUPLICATE_CLOSE_SOURCE     = $00000001;
  {$EXTERNALSYM DUPLICATE_CLOSE_SOURCE}
  DUPLICATE_SAME_ACCESS      = $00000002;
  {$EXTERNALSYM DUPLICATE_SAME_ACCESS}

type
  _SYSTEM_POWER_STATE = (
    PowerSystemUnspecified,
    PowerSystemWorking,
    PowerSystemSleeping1,
    PowerSystemSleeping2,
    PowerSystemSleeping3,
    PowerSystemHibernate,
    PowerSystemShutdown,
    PowerSystemMaximum);
  {$EXTERNALSYM _SYSTEM_POWER_STATE}
  SYSTEM_POWER_STATE = _SYSTEM_POWER_STATE;
  {$EXTERNALSYM SYSTEM_POWER_STATE}
  PSYSTEM_POWER_STATE = ^SYSTEM_POWER_STATE;
  {$EXTERNALSYM PSYSTEM_POWER_STATE}
  TSystemPowerState = SYSTEM_POWER_STATE;
  PSystemPowerState = PSYSTEM_POWER_STATE;

const
  POWER_SYSTEM_MAXIMUM = 7;
  {$EXTERNALSYM POWER_SYSTEM_MAXIMUM}

type
  POWER_ACTION = (
    PowerActionNone,
    PowerActionReserved,
    PowerActionSleep,
    PowerActionHibernate,
    PowerActionShutdown,
    PowerActionShutdownReset,
    PowerActionShutdownOff,
    PowerActionWarmEject);
  {$EXTERNALSYM POWER_ACTION}
  PPOWER_ACTION = ^POWER_ACTION;
  {$EXTERNALSYM PPOWER_ACTION}
  TPowerAction = POWER_ACTION;
  PPowerAction = PPOWER_ACTION;

  _DEVICE_POWER_STATE = (
    PowerDeviceUnspecified,
    PowerDeviceD0,
    PowerDeviceD1,
    PowerDeviceD2,
    PowerDeviceD3,
    PowerDeviceMaximum);
  {$EXTERNALSYM _DEVICE_POWER_STATE}
  DEVICE_POWER_STATE = _DEVICE_POWER_STATE;
  {$EXTERNALSYM DEVICE_POWER_STATE}
  PDEVICE_POWER_STATE = ^DEVICE_POWER_STATE;
  {$EXTERNALSYM PDEVICE_POWER_STATE}
  TDevicePowerState = DEVICE_POWER_STATE;
  PDevicePowerState = PDEVICE_POWER_STATE;

const
  ES_SYSTEM_REQUIRED  = DWORD($00000001);
  {$EXTERNALSYM ES_SYSTEM_REQUIRED}
  ES_DISPLAY_REQUIRED = DWORD($00000002);
  {$EXTERNALSYM ES_DISPLAY_REQUIRED}
  ES_USER_PRESENT     = DWORD($00000004);
  {$EXTERNALSYM ES_USER_PRESENT}
  ES_CONTINUOUS       = DWORD($80000000);
  {$EXTERNALSYM ES_CONTINUOUS}

type
  EXECUTION_STATE = DWORD;
  {$EXTERNALSYM EXECUTION_STATE}

  LATENCY_TIME = (LT_DONT_CARE, LT_LOWEST_LATENCY);
  {$EXTERNALSYM LATENCY_TIME}
  TLatencyTime = LATENCY_TIME;

//-----------------------------------------------------------------------------
// Device Power Information
// Accessable via CM_Get_DevInst_Registry_Property_Ex(CM_DRP_DEVICE_POWER_DATA)
//-----------------------------------------------------------------------------

const
  PDCAP_D0_SUPPORTED           = $00000001;
  {$EXTERNALSYM PDCAP_D0_SUPPORTED}
  PDCAP_D1_SUPPORTED           = $00000002;
  {$EXTERNALSYM PDCAP_D1_SUPPORTED}
  PDCAP_D2_SUPPORTED           = $00000004;
  {$EXTERNALSYM PDCAP_D2_SUPPORTED}
  PDCAP_D3_SUPPORTED           = $00000008;
  {$EXTERNALSYM PDCAP_D3_SUPPORTED}
  PDCAP_WAKE_FROM_D0_SUPPORTED = $00000010;
  {$EXTERNALSYM PDCAP_WAKE_FROM_D0_SUPPORTED}
  PDCAP_WAKE_FROM_D1_SUPPORTED = $00000020;
  {$EXTERNALSYM PDCAP_WAKE_FROM_D1_SUPPORTED}
  PDCAP_WAKE_FROM_D2_SUPPORTED = $00000040;
  {$EXTERNALSYM PDCAP_WAKE_FROM_D2_SUPPORTED}
  PDCAP_WAKE_FROM_D3_SUPPORTED = $00000080;
  {$EXTERNALSYM PDCAP_WAKE_FROM_D3_SUPPORTED}
  PDCAP_WARM_EJECT_SUPPORTED   = $00000100;
  {$EXTERNALSYM PDCAP_WARM_EJECT_SUPPORTED}

type
  CM_Power_Data_s = record
    PD_Size: DWORD;
    PD_MostRecentPowerState: DEVICE_POWER_STATE;
    PD_Capabilities: DWORD;
    PD_D1Latency: DWORD;
    PD_D2Latency: DWORD;
    PD_D3Latency: DWORD;
    PD_PowerStateMapping: array [0..POWER_SYSTEM_MAXIMUM - 1] of DEVICE_POWER_STATE;
    PD_DeepestSystemWake: SYSTEM_POWER_STATE;
  end;
  {$EXTERNALSYM CM_Power_Data_s}
  CM_POWER_DATA = CM_Power_Data_s;
  {$EXTERNALSYM CM_POWER_DATA}
  PCM_POWER_DATA = ^CM_POWER_DATA;
  {$EXTERNALSYM PCM_POWER_DATA}
  TCmPowerData = CM_POWER_DATA;
  PCmPowerData = PCM_POWER_DATA;

  POWER_INFORMATION_LEVEL = (
    SystemPowerPolicyAc,
    SystemPowerPolicyDc,
    VerifySystemPolicyAc,
    VerifySystemPolicyDc,
    SystemPowerCapabilities,
    SystemBatteryState,
    SystemPowerStateHandler,
    ProcessorStateHandler,
    SystemPowerPolicyCurrent,
    AdministratorPowerPolicy,
    SystemReserveHiberFile,
    ProcessorInformation,
    SystemPowerInformation,
    ProcessorStateHandler2,
    LastWakeTime,                                   // Compare with KeQueryInterruptTime()
    LastSleepTime,                                  // Compare with KeQueryInterruptTime()
    SystemExecutionState,
    SystemPowerStateNotifyHandler,
    ProcessorPowerPolicyAc,
    ProcessorPowerPolicyDc,
    VerifyProcessorPowerPolicyAc,
    VerifyProcessorPowerPolicyDc,
    ProcessorPowerPolicyCurrent,
    SystemPowerStateLogging,
    SystemPowerLoggingEntry);
  {$EXTERNALSYM POWER_INFORMATION_LEVEL}
  TPowerInformationLevel = POWER_INFORMATION_LEVEL;

//
// System power manager capabilities
//

  BATTERY_REPORTING_SCALE = record
    Granularity: DWORD;
    Capacity: DWORD;
  end;
  {$EXTERNALSYM BATTERY_REPORTING_SCALE}
  PBATTERY_REPORTING_SCALE = ^BATTERY_REPORTING_SCALE;
  {$EXTERNALSYM PBATTERY_REPORTING_SCALE}
  TBatteryReportingScale = BATTERY_REPORTING_SCALE;
  PBatteryReportingScale = PBATTERY_REPORTING_SCALE;

// Power Policy Management interfaces
//

  PPOWER_ACTION_POLICY = ^POWER_ACTION_POLICY;
  {$EXTERNALSYM PPOWER_ACTION_POLICY}
  POWER_ACTION_POLICY = record
    Action: POWER_ACTION;
    Flags: DWORD;
    EventCode: DWORD;
  end;
  {$EXTERNALSYM POWER_ACTION_POLICY}
  TPowerActionPolicy = POWER_ACTION_POLICY;
  PPowerActionPolicy = PPOWER_ACTION_POLICY;

// POWER_ACTION_POLICY->Flags:

const
  POWER_ACTION_QUERY_ALLOWED  = $00000001;
  {$EXTERNALSYM POWER_ACTION_QUERY_ALLOWED}
  POWER_ACTION_UI_ALLOWED     = $00000002;
  {$EXTERNALSYM POWER_ACTION_UI_ALLOWED}
  POWER_ACTION_OVERRIDE_APPS  = $00000004;
  {$EXTERNALSYM POWER_ACTION_OVERRIDE_APPS}
  POWER_ACTION_LIGHTEST_FIRST = $10000000;
  {$EXTERNALSYM POWER_ACTION_LIGHTEST_FIRST}
  POWER_ACTION_LOCK_CONSOLE   = $20000000;
  {$EXTERNALSYM POWER_ACTION_LOCK_CONSOLE}
  POWER_ACTION_DISABLE_WAKES  = $40000000;
  {$EXTERNALSYM POWER_ACTION_DISABLE_WAKES}
  POWER_ACTION_CRITICAL       = DWORD($80000000);
  {$EXTERNALSYM POWER_ACTION_CRITICAL}

// POWER_ACTION_POLICY->EventCode flags

  POWER_LEVEL_USER_NOTIFY_TEXT  = $00000001;
  {$EXTERNALSYM POWER_LEVEL_USER_NOTIFY_TEXT}
  POWER_LEVEL_USER_NOTIFY_SOUND = $00000002;
  {$EXTERNALSYM POWER_LEVEL_USER_NOTIFY_SOUND}
  POWER_LEVEL_USER_NOTIFY_EXEC  = $00000004;
  {$EXTERNALSYM POWER_LEVEL_USER_NOTIFY_EXEC}
  POWER_USER_NOTIFY_BUTTON      = $00000008;
  {$EXTERNALSYM POWER_USER_NOTIFY_BUTTON}
  POWER_USER_NOTIFY_SHUTDOWN    = $00000010;
  {$EXTERNALSYM POWER_USER_NOTIFY_SHUTDOWN}
  POWER_FORCE_TRIGGER_RESET     = DWORD($80000000);
  {$EXTERNALSYM POWER_FORCE_TRIGGER_RESET}

// system battery drain policies

type
  PSYSTEM_POWER_LEVEL = ^SYSTEM_POWER_LEVEL;
  {$EXTERNALSYM PSYSTEM_POWER_LEVEL}
  SYSTEM_POWER_LEVEL = record
    Enable: BOOLEAN;
    Spare: array [0..3 - 1] of BYTE;
    BatteryLevel: DWORD;
    PowerPolicy: POWER_ACTION_POLICY;
    MinSystemState: SYSTEM_POWER_STATE;
  end;
  {$EXTERNALSYM SYSTEM_POWER_LEVEL}
  TSystemPowerLevel = SYSTEM_POWER_LEVEL;
  PSystemPowerLevel = PSYSTEM_POWER_LEVEL;

// Discharge policy constants

const
  NUM_DISCHARGE_POLICIES    = 4;
  {$EXTERNALSYM NUM_DISCHARGE_POLICIES}
  DISCHARGE_POLICY_CRITICAL = 0;
  {$EXTERNALSYM DISCHARGE_POLICY_CRITICAL}
  DISCHARGE_POLICY_LOW      = 1;
  {$EXTERNALSYM DISCHARGE_POLICY_LOW}

//
// Throttling policies
//

  PO_THROTTLE_NONE     = 0;
  {$EXTERNALSYM PO_THROTTLE_NONE}
  PO_THROTTLE_CONSTANT = 1;
  {$EXTERNALSYM PO_THROTTLE_CONSTANT}
  PO_THROTTLE_DEGRADE  = 2;
  {$EXTERNALSYM PO_THROTTLE_DEGRADE}
  PO_THROTTLE_ADAPTIVE = 3;
  {$EXTERNALSYM PO_THROTTLE_ADAPTIVE}
  PO_THROTTLE_MAXIMUM  = 4; // not a policy, just a limit
  {$EXTERNALSYM PO_THROTTLE_MAXIMUM}

// system power policies

type
  PSYSTEM_POWER_POLICY = ^SYSTEM_POWER_POLICY;
  {$EXTERNALSYM PSYSTEM_POWER_POLICY}
  _SYSTEM_POWER_POLICY = record
    Revision: DWORD; // 1
    // events
    PowerButton: POWER_ACTION_POLICY;
    SleepButton: POWER_ACTION_POLICY;
    LidClose: POWER_ACTION_POLICY;
    LidOpenWake: SYSTEM_POWER_STATE;
    Reserved: DWORD;
    // "system idle" detection
    Idle: POWER_ACTION_POLICY;
    IdleTimeout: DWORD;
    IdleSensitivity: BYTE;
    // dynamic throttling policy
    //      PO_THROTTLE_NONE, PO_THROTTLE_CONSTANT, PO_THROTTLE_DEGRADE, or PO_THROTTLE_ADAPTIVE
    DynamicThrottle: BYTE;
    Spare2: array [0..1] of BYTE;
    // meaning of power action "sleep"
    MinSleep: SYSTEM_POWER_STATE;
    MaxSleep: SYSTEM_POWER_STATE;
    ReducedLatencySleep: SYSTEM_POWER_STATE;
    WinLogonFlags: DWORD;
    // parameters for dozing
    Spare3: DWORD;
    DozeS4Timeout: DWORD;
    // battery policies
    BroadcastCapacityResolution: DWORD;
    DischargePolicy: array [0..NUM_DISCHARGE_POLICIES - 1] of SYSTEM_POWER_LEVEL;
    // video policies
    VideoTimeout: DWORD;
    VideoDimDisplay: BOOLEAN;
    VideoReserved: array [0..2] of DWORD;
    // hard disk policies
    SpindownTimeout: DWORD;
    // processor policies
    OptimizeForPower: LongBool;
    FanThrottleTolerance: BYTE;
    ForcedThrottle: BYTE;
    MinThrottle: BYTE;
    OverThrottled: POWER_ACTION_POLICY;
  end;
  {$EXTERNALSYM _SYSTEM_POWER_POLICY}
  SYSTEM_POWER_POLICY = _SYSTEM_POWER_POLICY;
  {$EXTERNALSYM SYSTEM_POWER_POLICY}
  TSystemPowerPolicy = SYSTEM_POWER_POLICY;
  PSystemPowerPolicy = PSYSTEM_POWER_POLICY;

// processor power policy state

  PPROCESSOR_POWER_POLICY_INFO = ^PROCESSOR_POWER_POLICY_INFO;
  {$EXTERNALSYM PPROCESSOR_POWER_POLICY_INFO}
  _PROCESSOR_POWER_POLICY_INFO = record
    // Time based information (will be converted to kernel units)
    TimeCheck: DWORD; // in US
    DemoteLimit: DWORD; // in US
    PromoteLimit: DWORD; // in US
    // Percentage based information
    DemotePercent: BYTE;
    PromotePercent: BYTE;
    Spare: array [0..1] of BYTE;
    // Flags
    Flags: DWORD;
    //DWORD                   AllowDemotion:1;
    //DWORD                   AllowPromotion:1;
    //DWORD                   Reserved:30;
  end;
  {$EXTERNALSYM _PROCESSOR_POWER_POLICY_INFO}
  PROCESSOR_POWER_POLICY_INFO = _PROCESSOR_POWER_POLICY_INFO;
  {$EXTERNALSYM PROCESSOR_POWER_POLICY_INFO}
  TProcessorPowerPolicyInfo = PROCESSOR_POWER_POLICY_INFO;
  PProcessorPowerPolicyInfo = PPROCESSOR_POWER_POLICY_INFO;

// processor power policy

  PPROCESSOR_POWER_POLICY = ^PROCESSOR_POWER_POLICY;
  {$EXTERNALSYM PPROCESSOR_POWER_POLICY}
  _PROCESSOR_POWER_POLICY = record
    Revision: DWORD; // 1
    // Dynamic Throttling Policy
    DynamicThrottle: BYTE;
    Spare: array [0..2] of BYTE;
    // Flags
    Reserved: DWORD;
    //DWORD                       DisableCStates:1;
    //DWORD                       Reserved:31;

    // System policy information
    // The Array is last, in case it needs to be grown and the structure
    // revision incremented.
    PolicyCount: DWORD;
    Policy: array [0..2] of PROCESSOR_POWER_POLICY_INFO;
  end;
  {$EXTERNALSYM _PROCESSOR_POWER_POLICY}
  PROCESSOR_POWER_POLICY = _PROCESSOR_POWER_POLICY;
  {$EXTERNALSYM PROCESSOR_POWER_POLICY}
  TProcessorPowerPolicy = PROCESSOR_POWER_POLICY;
  PProcessorPowerPolicy = PPROCESSOR_POWER_POLICY;

// administrator power policy overrides

  PADMINISTRATOR_POWER_POLICY = ^ADMINISTRATOR_POWER_POLICY;
  {$EXTERNALSYM PADMINISTRATOR_POWER_POLICY}
  _ADMINISTRATOR_POWER_POLICY = record
    // meaning of power action "sleep"
    MinSleep: SYSTEM_POWER_STATE;
    MaxSleep: SYSTEM_POWER_STATE;
    // video policies
    MinVideoTimeout: DWORD;
    MaxVideoTimeout: DWORD;
    // disk policies
    MinSpindownTimeout: DWORD;
    MaxSpindownTimeout: DWORD;
  end;
  {$EXTERNALSYM _ADMINISTRATOR_POWER_POLICY}
  ADMINISTRATOR_POWER_POLICY = _ADMINISTRATOR_POWER_POLICY;
  {$EXTERNALSYM ADMINISTRATOR_POWER_POLICY}
  TAdministratorPowerPolicy = ADMINISTRATOR_POWER_POLICY;
  PAdministratorPowerPolicy = PADMINISTRATOR_POWER_POLICY;

  PSYSTEM_POWER_CAPABILITIES = ^SYSTEM_POWER_CAPABILITIES;
  {$EXTERNALSYM PSYSTEM_POWER_CAPABILITIES}
  SYSTEM_POWER_CAPABILITIES = record
    // Misc supported system features
    PowerButtonPresent: BOOLEAN;
    SleepButtonPresent: BOOLEAN;
    LidPresent: BOOLEAN;
    SystemS1: BOOLEAN;
    SystemS2: BOOLEAN;
    SystemS3: BOOLEAN;
    SystemS4: BOOLEAN; // hibernate
    SystemS5: BOOLEAN; // off
    HiberFilePresent: BOOLEAN;
    FullWake: BOOLEAN;
    VideoDimPresent: BOOLEAN;
    ApmPresent: BOOLEAN;
    UpsPresent: BOOLEAN;
    // Processors
    ThermalControl: BOOLEAN;
    ProcessorThrottle: BOOLEAN;
    ProcessorMinThrottle: BYTE;
    ProcessorMaxThrottle: BYTE;
    spare2: array [0..4 - 1] of BYTE;
    // Disk
    DiskSpinDown: BOOLEAN;
    spare3: array [0..8 - 1] of BYTE;
    // System Battery
    SystemBatteriesPresent: BOOLEAN;
    BatteriesAreShortTerm: BOOLEAN;
    BatteryScale: array [0..3 - 1] of BATTERY_REPORTING_SCALE;
    // Wake
    AcOnLineWake: SYSTEM_POWER_STATE;
    SoftLidWake: SYSTEM_POWER_STATE;
    RtcWake: SYSTEM_POWER_STATE;
    MinDeviceWakeState: SYSTEM_POWER_STATE; // note this may change on driver load
    DefaultLowLatencyWake: SYSTEM_POWER_STATE;
  end;
  {$EXTERNALSYM SYSTEM_POWER_CAPABILITIES}
  TSystemPowerCapabilities = SYSTEM_POWER_CAPABILITIES;
  PSystemPowerCapabilities = PSYSTEM_POWER_CAPABILITIES;

  PSYSTEM_BATTERY_STATE = ^SYSTEM_BATTERY_STATE;
  {$EXTERNALSYM PSYSTEM_BATTERY_STATE}
  SYSTEM_BATTERY_STATE = record
    AcOnLine: BOOLEAN;
    BatteryPresent: BOOLEAN;
    Charging: BOOLEAN;
    Discharging: BOOLEAN;
    Spare1: array [0..3] of BOOLEAN;
    MaxCapacity: DWORD;
    RemainingCapacity: DWORD;
    Rate: DWORD;
    EstimatedTime: DWORD;
    DefaultAlert1: DWORD;
    DefaultAlert2: DWORD;
  end;
  {$EXTERNALSYM SYSTEM_BATTERY_STATE}
  TSystemBatteryState = SYSTEM_BATTERY_STATE;
  PSystemBatteryState = PSYSTEM_BATTERY_STATE;

//
// Image Format
//

// #include "pshpack4.h"                   // 4 byte packing is the default

const
  IMAGE_DOS_SIGNATURE    = $5A4D; // MZ
  {$EXTERNALSYM IMAGE_DOS_SIGNATURE}
  IMAGE_OS2_SIGNATURE    = $454E; // NE
  {$EXTERNALSYM IMAGE_OS2_SIGNATURE}
  IMAGE_OS2_SIGNATURE_LE = $454C; // LE
  {$EXTERNALSYM IMAGE_OS2_SIGNATURE_LE}
  IMAGE_VXD_SIGNATURE    = $454C; // LE
  {$EXTERNALSYM IMAGE_VXD_SIGNATURE}
  IMAGE_NT_SIGNATURE     = $00004550; // PE00
  {$EXTERNALSYM IMAGE_NT_SIGNATURE}

// #include "pshpack2.h"                   // 16 bit headers are 2 byte packed

type

  // DOS .EXE header

  PIMAGE_DOS_HEADER = ^IMAGE_DOS_HEADER;
  {$EXTERNALSYM PIMAGE_DOS_HEADER}
  _IMAGE_DOS_HEADER = record
    e_magic: Word;     // Magic number
    e_cblp: Word;      // Bytes on last page of file
    e_cp: Word;        // Pages in file
    e_crlc: Word;      // Relocations
    e_cparhdr: Word;   // Size of header in paragraphs
    e_minalloc: Word;  // Minimum extra paragraphs needed
    e_maxalloc: Word;  // Maximum extra paragraphs needed
    e_ss: Word;        // Initial (relative) SS value
    e_sp: Word;        // Initial SP value
    e_csum: Word;      // Checksum
    e_ip: Word;        // Initial IP value
    e_cs: Word;        // Initial (relative) CS value
    e_lfarlc: Word;    // File address of relocation table
    e_ovno: Word;      // Overlay number
    e_res: array [0..3] of Word;    // Reserved words
    e_oemid: Word;     // OEM identifier (for e_oeminfo)
    e_oeminfo: Word;   // OEM information; e_oemid specific
    e_res2: array [0..9] of Word;  // Reserved words
    e_lfanew: Longint; // File address of new exe header
  end;
  {$EXTERNALSYM _IMAGE_DOS_HEADER}
  IMAGE_DOS_HEADER = _IMAGE_DOS_HEADER;
  {$EXTERNALSYM IMAGE_DOS_HEADER}
  TImageDosHeader = IMAGE_DOS_HEADER;
  PImageDosHeader = PIMAGE_DOS_HEADER;

  // OS/2 .EXE header

  PIMAGE_OS2_HEADER = ^IMAGE_OS2_HEADER;
  {$EXTERNALSYM PIMAGE_OS2_HEADER}
  _IMAGE_OS2_HEADER = record
    ne_magic: Word;        // Magic number
    ne_ver: CHAR;          // Version number
    ne_rev: CHAR;          // Revision number
    ne_enttab: Word;       // Offset of Entry Table
    ne_cbenttab: Word;     // Number of bytes in Entry Table
    ne_crc: Longint;       // Checksum of whole file
    ne_flags: Word;        // Flag word
    ne_autodata: Word;     // Automatic data segment number
    ne_heap: Word;         // Initial heap allocation
    ne_stack: Word;        // Initial stack allocation
    ne_csip: Longint;      // Initial CS:IP setting
    ne_sssp: Longint;      // Initial SS:SP setting
    ne_cseg: Word;         // Count of file segments
    ne_cmod: Word;         // Entries in Module Reference Table
    ne_cbnrestab: Word;    // Size of non-resident name table
    ne_segtab: Word;       // Offset of Segment Table
    ne_rsrctab: Word;      // Offset of Resource Table
    ne_restab: Word;       // Offset of resident name table
    ne_modtab: Word;       // Offset of Module Reference Table
    ne_imptab: Word;       // Offset of Imported Names Table
    ne_nrestab: Longint;   // Offset of Non-resident Names Table
    ne_cmovent: Word;      // Count of movable entries
    ne_align: Word;        // Segment alignment shift count
    ne_cres: Word;         // Count of resource segments
    ne_exetyp: Byte;       // Target Operating system
    ne_flagsothers: Byte;  // Other .EXE flags
    ne_pretthunks: Word;   // offset to return thunks
    ne_psegrefbytes: Word; // offset to segment ref. bytes
    ne_swaparea: Word;     // Minimum code swap area size
    ne_expver: Word;       // Expected Windows version number
  end;
  {$EXTERNALSYM _IMAGE_OS2_HEADER}
  IMAGE_OS2_HEADER = _IMAGE_OS2_HEADER;
  {$EXTERNALSYM IMAGE_OS2_HEADER}
  TImageOs2Header = IMAGE_OS2_HEADER;
  PImageOs2Header = PIMAGE_OS2_HEADER;

  // Windows VXD header

  PIMAGE_VXD_HEADER = ^IMAGE_VXD_HEADER;
  {$EXTERNALSYM PIMAGE_VXD_HEADER}
  _IMAGE_VXD_HEADER = record
    e32_magic: Word;         // Magic number
    e32_border: Byte;        // The byte ordering for the VXD
    e32_worder: Byte;        // The word ordering for the VXD
    e32_level: DWORD;        // The EXE format level for now = 0
    e32_cpu: Word;           // The CPU type
    e32_os: Word;            // The OS type
    e32_ver: DWORD;          // Module version
    e32_mflags: DWORD;       // Module flags
    e32_mpages: DWORD;       // Module # pages
    e32_startobj: DWORD;     // Object # for instruction pointer
    e32_eip: DWORD;          // Extended instruction pointer
    e32_stackobj: DWORD;     // Object # for stack pointer
    e32_esp: DWORD;          // Extended stack pointer
    e32_pagesize: DWORD;     // VXD page size
    e32_lastpagesize: DWORD; // Last page size in VXD
    e32_fixupsize: DWORD;    // Fixup section size
    e32_fixupsum: DWORD;     // Fixup section checksum
    e32_ldrsize: DWORD;      // Loader section size
    e32_ldrsum: DWORD;       // Loader section checksum
    e32_objtab: DWORD;       // Object table offset
    e32_objcnt: DWORD;       // Number of objects in module
    e32_objmap: DWORD;       // Object page map offset
    e32_itermap: DWORD;      // Object iterated data map offset
    e32_rsrctab: DWORD;      // Offset of Resource Table
    e32_rsrccnt: DWORD;      // Number of resource entries
    e32_restab: DWORD;       // Offset of resident name table
    e32_enttab: DWORD;       // Offset of Entry Table
    e32_dirtab: DWORD;       // Offset of Module Directive Table
    e32_dircnt: DWORD;       // Number of module directives
    e32_fpagetab: DWORD;     // Offset of Fixup Page Table
    e32_frectab: DWORD;      // Offset of Fixup Record Table
    e32_impmod: DWORD;       // Offset of Import Module Name Table
    e32_impmodcnt: DWORD;    // Number of entries in Import Module Name Table
    e32_impproc: DWORD;      // Offset of Import Procedure Name Table
    e32_pagesum: DWORD;      // Offset of Per-Page Checksum Table
    e32_datapage: DWORD;     // Offset of Enumerated Data Pages
    e32_preload: DWORD;      // Number of preload pages
    e32_nrestab: DWORD;      // Offset of Non-resident Names Table
    e32_cbnrestab: DWORD;    // Size of Non-resident Name Table
    e32_nressum: DWORD;      // Non-resident Name Table Checksum
    e32_autodata: DWORD;     // Object # for automatic data object
    e32_debuginfo: DWORD;    // Offset of the debugging information
    e32_debuglen: DWORD;     // The length of the debugging info. in bytes
    e32_instpreload: DWORD;  // Number of instance pages in preload section of VXD file
    e32_instdemand: DWORD;   // Number of instance pages in demand load section of VXD file
    e32_heapsize: DWORD;     // Size of heap - for 16-bit apps
    e32_res3: array [0..11] of Byte;      // Reserved words
    e32_winresoff: DWORD;
    e32_winreslen: DWORD;
    e32_devid: Word;         // Device ID for VxD
    e32_ddkver: Word;        // DDK version for VxD
  end;
  {$EXTERNALSYM _IMAGE_VXD_HEADER}
  IMAGE_VXD_HEADER = _IMAGE_VXD_HEADER;
  {$EXTERNALSYM IMAGE_VXD_HEADER}
  TImageVxdHeader = IMAGE_VXD_HEADER;
  PImageVxdHeader = PIMAGE_VXD_HEADER;

// #include "poppack.h"                    // Back to 4 byte packing

//
// File header format.
//

  PIMAGE_FILE_HEADER = ^IMAGE_FILE_HEADER;
  {$EXTERNALSYM PIMAGE_FILE_HEADER}
  _IMAGE_FILE_HEADER = record
    Machine: WORD;
    NumberOfSections: WORD;
    TimeDateStamp: DWORD;
    PointerToSymbolTable: DWORD;
    NumberOfSymbols: DWORD;
    SizeOfOptionalHeader: WORD;
    Characteristics: WORD;
  end;
  {$EXTERNALSYM _IMAGE_FILE_HEADER}
  IMAGE_FILE_HEADER = _IMAGE_FILE_HEADER;
  {$EXTERNALSYM IMAGE_FILE_HEADER}
  TImageFileHeader = IMAGE_FILE_HEADER;
  PImageFileHeader = PIMAGE_FILE_HEADER;

const
  IMAGE_SIZEOF_FILE_HEADER = 20;
  {$EXTERNALSYM IMAGE_SIZEOF_FILE_HEADER}

  IMAGE_FILE_RELOCS_STRIPPED         = $0001; // Relocation info stripped from file.
  {$EXTERNALSYM IMAGE_FILE_RELOCS_STRIPPED}
  IMAGE_FILE_EXECUTABLE_IMAGE        = $0002; // File is executable  (i.e. no unresolved externel references).
  {$EXTERNALSYM IMAGE_FILE_EXECUTABLE_IMAGE}
  IMAGE_FILE_LINE_NUMS_STRIPPED      = $0004; // Line nunbers stripped from file.
  {$EXTERNALSYM IMAGE_FILE_LINE_NUMS_STRIPPED}
  IMAGE_FILE_LOCAL_SYMS_STRIPPED     = $0008; // Local symbols stripped from file.
  {$EXTERNALSYM IMAGE_FILE_LOCAL_SYMS_STRIPPED}
  IMAGE_FILE_AGGRESIVE_WS_TRIM       = $0010; // Agressively trim working set
  {$EXTERNALSYM IMAGE_FILE_AGGRESIVE_WS_TRIM}
  IMAGE_FILE_LARGE_ADDRESS_AWARE     = $0020; // App can handle >2gb addresses
  {$EXTERNALSYM IMAGE_FILE_LARGE_ADDRESS_AWARE}
  IMAGE_FILE_BYTES_REVERSED_LO       = $0080; // Bytes of machine word are reversed.
  {$EXTERNALSYM IMAGE_FILE_BYTES_REVERSED_LO}
  IMAGE_FILE_32BIT_MACHINE           = $0100; // 32 bit word machine.
  {$EXTERNALSYM IMAGE_FILE_32BIT_MACHINE}
  IMAGE_FILE_DEBUG_STRIPPED          = $0200; // Debugging info stripped from file in .DBG file
  {$EXTERNALSYM IMAGE_FILE_DEBUG_STRIPPED}
  IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP = $0400; // If Image is on removable media, copy and run from the swap file.
  {$EXTERNALSYM IMAGE_FILE_REMOVABLE_RUN_FROM_SWAP}
  IMAGE_FILE_NET_RUN_FROM_SWAP       = $0800; // If Image is on Net, copy and run from the swap file.
  {$EXTERNALSYM IMAGE_FILE_NET_RUN_FROM_SWAP}
  IMAGE_FILE_SYSTEM                  = $1000; // System File.
  {$EXTERNALSYM IMAGE_FILE_SYSTEM}
  IMAGE_FILE_DLL                     = $2000; // File is a DLL.
  {$EXTERNALSYM IMAGE_FILE_DLL}
  IMAGE_FILE_UP_SYSTEM_ONLY          = $4000; // File should only be run on a UP machine
  {$EXTERNALSYM IMAGE_FILE_UP_SYSTEM_ONLY}
  IMAGE_FILE_BYTES_REVERSED_HI       = $8000; // Bytes of machine word are reversed.
  {$EXTERNALSYM IMAGE_FILE_BYTES_REVERSED_HI}

  IMAGE_FILE_MACHINE_UNKNOWN   = 0;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_UNKNOWN}
  IMAGE_FILE_MACHINE_I386      = $014c; // Intel 386.
  {$EXTERNALSYM IMAGE_FILE_MACHINE_I386}
  IMAGE_FILE_MACHINE_R3000     = $0162; // MIPS little-endian, 0x160 big-endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_R3000}
  IMAGE_FILE_MACHINE_R4000     = $0166; // MIPS little-endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_R4000}
  IMAGE_FILE_MACHINE_R10000    = $0168; // MIPS little-endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_R10000}
  IMAGE_FILE_MACHINE_WCEMIPSV2 = $0169; // MIPS little-endian WCE v2
  {$EXTERNALSYM IMAGE_FILE_MACHINE_WCEMIPSV2}
  IMAGE_FILE_MACHINE_ALPHA     = $0184; // Alpha_AXP
  {$EXTERNALSYM IMAGE_FILE_MACHINE_ALPHA}
  IMAGE_FILE_MACHINE_SH3       = $01a2; // SH3 little-endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_SH3}
  IMAGE_FILE_MACHINE_SH3DSP    = $01a3;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_SH3DSP}
  IMAGE_FILE_MACHINE_SH3E      = $01a4; // SH3E little-endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_SH3E}
  IMAGE_FILE_MACHINE_SH4       = $01a6; // SH4 little-endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_SH4}
  IMAGE_FILE_MACHINE_SH5       = $01a8; // SH5
  {$EXTERNALSYM IMAGE_FILE_MACHINE_SH5}
  IMAGE_FILE_MACHINE_ARM       = $01c0; // ARM Little-Endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_ARM}
  IMAGE_FILE_MACHINE_THUMB     = $01c2;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_THUMB}
  IMAGE_FILE_MACHINE_AM33      = $01d3;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_AM33}
  IMAGE_FILE_MACHINE_POWERPC   = $01F0; // IBM PowerPC Little-Endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_POWERPC}
  IMAGE_FILE_MACHINE_POWERPCFP = $01f1;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_POWERPCFP}
  IMAGE_FILE_MACHINE_IA64      = $0200; // Intel 64
  {$EXTERNALSYM IMAGE_FILE_MACHINE_IA64}
  IMAGE_FILE_MACHINE_MIPS16    = $0266; // MIPS
  {$EXTERNALSYM IMAGE_FILE_MACHINE_MIPS16}
  IMAGE_FILE_MACHINE_ALPHA64   = $0284; // ALPHA64
  {$EXTERNALSYM IMAGE_FILE_MACHINE_ALPHA64}
  IMAGE_FILE_MACHINE_MIPSFPU   = $0366; // MIPS
  {$EXTERNALSYM IMAGE_FILE_MACHINE_MIPSFPU}
  IMAGE_FILE_MACHINE_MIPSFPU16 = $0466; // MIPS
  {$EXTERNALSYM IMAGE_FILE_MACHINE_MIPSFPU16}
  IMAGE_FILE_MACHINE_AXP64     = IMAGE_FILE_MACHINE_ALPHA64;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_AXP64}
  IMAGE_FILE_MACHINE_TRICORE   = $0520; // Infineon
  {$EXTERNALSYM IMAGE_FILE_MACHINE_TRICORE}
  IMAGE_FILE_MACHINE_CEF       = $0CEF;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_CEF}
  IMAGE_FILE_MACHINE_EBC       = $0EBC; // EFI Byte Code
  {$EXTERNALSYM IMAGE_FILE_MACHINE_EBC}
  IMAGE_FILE_MACHINE_AMD64     = $8664; // AMD64 (K8)
  {$EXTERNALSYM IMAGE_FILE_MACHINE_AMD64}
  IMAGE_FILE_MACHINE_M32R      = $9041; // M32R little-endian
  {$EXTERNALSYM IMAGE_FILE_MACHINE_M32R}
  IMAGE_FILE_MACHINE_CEE       = $C0EE;
  {$EXTERNALSYM IMAGE_FILE_MACHINE_CEE}

//
// Directory format.
//

type
  PIMAGE_DATA_DIRECTORY = ^IMAGE_DATA_DIRECTORY;
  {$EXTERNALSYM PIMAGE_DATA_DIRECTORY}
  _IMAGE_DATA_DIRECTORY = record
    VirtualAddress: DWORD;
    Size: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_DATA_DIRECTORY}
  IMAGE_DATA_DIRECTORY = _IMAGE_DATA_DIRECTORY;
  {$EXTERNALSYM IMAGE_DATA_DIRECTORY}
  TImageDataDirectory = IMAGE_DATA_DIRECTORY;
  PImageDataDirectory = PIMAGE_DATA_DIRECTORY;

const
  IMAGE_NUMBEROF_DIRECTORY_ENTRIES = 16;
  {$EXTERNALSYM IMAGE_NUMBEROF_DIRECTORY_ENTRIES}

//
// Optional header format.
//

type
  PIMAGE_OPTIONAL_HEADER32 = ^IMAGE_OPTIONAL_HEADER32;
  {$EXTERNALSYM PIMAGE_OPTIONAL_HEADER32}
  _IMAGE_OPTIONAL_HEADER = record
    //
    // Standard fields.
    //
    Magic: Word;
    MajorLinkerVersion: Byte;
    MinorLinkerVersion: Byte;
    SizeOfCode: DWORD;
    SizeOfInitializedData: DWORD;
    SizeOfUninitializedData: DWORD;
    AddressOfEntryPoint: DWORD;
    BaseOfCode: DWORD;
    BaseOfData: DWORD;
    //
    // NT additional fields.
    //
    ImageBase: DWORD;
    SectionAlignment: DWORD;
    FileAlignment: DWORD;
    MajorOperatingSystemVersion: Word;
    MinorOperatingSystemVersion: Word;
    MajorImageVersion: Word;
    MinorImageVersion: Word;
    MajorSubsystemVersion: Word;
    MinorSubsystemVersion: Word;
    Win32VersionValue: DWORD;
    SizeOfImage: DWORD;
    SizeOfHeaders: DWORD;
    CheckSum: DWORD;
    Subsystem: Word;
    DllCharacteristics: Word;
    SizeOfStackReserve: DWORD;
    SizeOfStackCommit: DWORD;
    SizeOfHeapReserve: DWORD;
    SizeOfHeapCommit: DWORD;
    LoaderFlags: DWORD;
    NumberOfRvaAndSizes: DWORD;
    DataDirectory: array [0..IMAGE_NUMBEROF_DIRECTORY_ENTRIES - 1] of IMAGE_DATA_DIRECTORY;
  end;
  {$EXTERNALSYM _IMAGE_OPTIONAL_HEADER}
  IMAGE_OPTIONAL_HEADER32 = _IMAGE_OPTIONAL_HEADER;
  {$EXTERNALSYM IMAGE_OPTIONAL_HEADER32}
  TImageOptionalHeader32 = IMAGE_OPTIONAL_HEADER32;
  PImageOptionalHeader32 = PIMAGE_OPTIONAL_HEADER32;

  PIMAGE_ROM_OPTIONAL_HEADER = ^IMAGE_ROM_OPTIONAL_HEADER;
  {$EXTERNALSYM PIMAGE_ROM_OPTIONAL_HEADER}
  _IMAGE_ROM_OPTIONAL_HEADER = record
    Magic: Word;
    MajorLinkerVersion: Byte;
    MinorLinkerVersion: Byte;
    SizeOfCode: DWORD;
    SizeOfInitializedData: DWORD;
    SizeOfUninitializedData: DWORD;
    AddressOfEntryPoint: DWORD;
    BaseOfCode: DWORD;
    BaseOfData: DWORD;
    BaseOfBss: DWORD;
    GprMask: DWORD;
    CprMask: array [0..3] of DWORD;
    GpValue: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_ROM_OPTIONAL_HEADER}
  IMAGE_ROM_OPTIONAL_HEADER = _IMAGE_ROM_OPTIONAL_HEADER;
  {$EXTERNALSYM IMAGE_ROM_OPTIONAL_HEADER}
  TImageRomOptionalHeader = IMAGE_ROM_OPTIONAL_HEADER;
  PImageRomOptionalHeader = PIMAGE_ROM_OPTIONAL_HEADER;

  PIMAGE_OPTIONAL_HEADER64 = ^IMAGE_OPTIONAL_HEADER64;
  {$EXTERNALSYM PIMAGE_OPTIONAL_HEADER64}
  _IMAGE_OPTIONAL_HEADER64 = record
    Magic: Word;
    MajorLinkerVersion: Byte;
    MinorLinkerVersion: Byte;
    SizeOfCode: DWORD;
    SizeOfInitializedData: DWORD;
    SizeOfUninitializedData: DWORD;
    AddressOfEntryPoint: DWORD;
    BaseOfCode: DWORD;
    ImageBase: Int64;
    SectionAlignment: DWORD;
    FileAlignment: DWORD;
    MajorOperatingSystemVersion: Word;
    MinorOperatingSystemVersion: Word;
    MajorImageVersion: Word;
    MinorImageVersion: Word;
    MajorSubsystemVersion: Word;
    MinorSubsystemVersion: Word;
    Win32VersionValue: DWORD;
    SizeOfImage: DWORD;
    SizeOfHeaders: DWORD;
    CheckSum: DWORD;
    Subsystem: Word;
    DllCharacteristics: Word;
    SizeOfStackReserve: Int64;
    SizeOfStackCommit: Int64;
    SizeOfHeapReserve: Int64;
    SizeOfHeapCommit: Int64;
    LoaderFlags: DWORD;
    NumberOfRvaAndSizes: DWORD;
    DataDirectory: array [0..IMAGE_NUMBEROF_DIRECTORY_ENTRIES - 1] of IMAGE_DATA_DIRECTORY;
  end;
  {$EXTERNALSYM _IMAGE_OPTIONAL_HEADER64}
  IMAGE_OPTIONAL_HEADER64 = _IMAGE_OPTIONAL_HEADER64;
  {$EXTERNALSYM IMAGE_OPTIONAL_HEADER64}
  TImageOptionalHeader64 = IMAGE_OPTIONAL_HEADER64;
  PImageOptionalHeader64 = PIMAGE_OPTIONAL_HEADER64;

const
  IMAGE_SIZEOF_ROM_OPTIONAL_HEADER  = 56;
  {$EXTERNALSYM IMAGE_SIZEOF_ROM_OPTIONAL_HEADER}
  IMAGE_SIZEOF_STD_OPTIONAL_HEADER  = 28;
  {$EXTERNALSYM IMAGE_SIZEOF_STD_OPTIONAL_HEADER}
  IMAGE_SIZEOF_NT_OPTIONAL32_HEADER = 224;
  {$EXTERNALSYM IMAGE_SIZEOF_NT_OPTIONAL32_HEADER}
  IMAGE_SIZEOF_NT_OPTIONAL64_HEADER = 240;
  {$EXTERNALSYM IMAGE_SIZEOF_NT_OPTIONAL64_HEADER}

  IMAGE_NT_OPTIONAL_HDR32_MAGIC = $10b;
  {$EXTERNALSYM IMAGE_NT_OPTIONAL_HDR32_MAGIC}
  IMAGE_NT_OPTIONAL_HDR64_MAGIC = $20b;
  {$EXTERNALSYM IMAGE_NT_OPTIONAL_HDR64_MAGIC}
  IMAGE_ROM_OPTIONAL_HDR_MAGIC  = $107;
  {$EXTERNALSYM IMAGE_ROM_OPTIONAL_HDR_MAGIC}

type
  IMAGE_OPTIONAL_HEADER = IMAGE_OPTIONAL_HEADER32;
  {$EXTERNALSYM IMAGE_OPTIONAL_HEADER}
  PIMAGE_OPTIONAL_HEADER = PIMAGE_OPTIONAL_HEADER32;
  {$EXTERNALSYM PIMAGE_OPTIONAL_HEADER}

const
  IMAGE_SIZEOF_NT_OPTIONAL_HEADER = IMAGE_SIZEOF_NT_OPTIONAL32_HEADER;
  {$EXTERNALSYM IMAGE_SIZEOF_NT_OPTIONAL_HEADER}
  IMAGE_NT_OPTIONAL_HDR_MAGIC     = IMAGE_NT_OPTIONAL_HDR32_MAGIC;
  {$EXTERNALSYM IMAGE_NT_OPTIONAL_HDR_MAGIC}

type
  PIMAGE_NT_HEADERS64 = ^IMAGE_NT_HEADERS64;
  {$EXTERNALSYM PIMAGE_NT_HEADERS64}
  _IMAGE_NT_HEADERS64 = record
    Signature: DWORD;
    FileHeader: IMAGE_FILE_HEADER;
    OptionalHeader: IMAGE_OPTIONAL_HEADER64;
  end;
  {$EXTERNALSYM _IMAGE_NT_HEADERS64}
  IMAGE_NT_HEADERS64 = _IMAGE_NT_HEADERS64;
  {$EXTERNALSYM IMAGE_NT_HEADERS64}
  TImageNtHeaders64 = IMAGE_NT_HEADERS64;
  PImageNtHeaders64 = PIMAGE_NT_HEADERS64;

  PIMAGE_NT_HEADERS32 = ^IMAGE_NT_HEADERS32;
  {$EXTERNALSYM PIMAGE_NT_HEADERS32}
  _IMAGE_NT_HEADERS = record
    Signature: DWORD;
    FileHeader: IMAGE_FILE_HEADER;
    OptionalHeader: IMAGE_OPTIONAL_HEADER32;
  end;
  {$EXTERNALSYM _IMAGE_NT_HEADERS}
  IMAGE_NT_HEADERS32 = _IMAGE_NT_HEADERS;
  {$EXTERNALSYM IMAGE_NT_HEADERS32}
  TImageNtHeaders32 = IMAGE_NT_HEADERS32;
  PImageNtHeaders32 = PIMAGE_NT_HEADERS32;

  PIMAGE_ROM_HEADERS = ^IMAGE_ROM_HEADERS;
  {$EXTERNALSYM PIMAGE_ROM_HEADERS}
  _IMAGE_ROM_HEADERS = record
    FileHeader: IMAGE_FILE_HEADER;
    OptionalHeader: IMAGE_ROM_OPTIONAL_HEADER;
  end;
  {$EXTERNALSYM _IMAGE_ROM_HEADERS}
  IMAGE_ROM_HEADERS = _IMAGE_ROM_HEADERS;
  {$EXTERNALSYM IMAGE_ROM_HEADERS}
  TImageRomHeaders = IMAGE_ROM_HEADERS;
  PImageRomHeaders = PIMAGE_ROM_HEADERS;

  IMAGE_NT_HEADERS = IMAGE_NT_HEADERS32;
  {$EXTERNALSYM IMAGE_NT_HEADERS}
  PIMAGE_NT_HEADERS = PIMAGE_NT_HEADERS32;
  {$EXTERNALSYM PIMAGE_NT_HEADERS}

  PImageNtHeaders = PIMAGE_NT_HEADERS;

// Subsystem Values

const
  IMAGE_SUBSYSTEM_UNKNOWN                 = 0; // Unknown subsystem.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_UNKNOWN}
  IMAGE_SUBSYSTEM_NATIVE                  = 1; // Image doesn't require a subsystem.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_NATIVE}
  IMAGE_SUBSYSTEM_WINDOWS_GUI             = 2; // Image runs in the Windows GUI subsystem.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_WINDOWS_GUI}
  IMAGE_SUBSYSTEM_WINDOWS_CUI             = 3; // Image runs in the Windows character subsystem.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_WINDOWS_CUI}
  IMAGE_SUBSYSTEM_OS2_CUI                 = 5; // image runs in the OS/2 character subsystem.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_OS2_CUI}
  IMAGE_SUBSYSTEM_POSIX_CUI               = 7; // image runs in the Posix character subsystem.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_POSIX_CUI}
  IMAGE_SUBSYSTEM_NATIVE_WINDOWS          = 8; // image is a native Win9x driver.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_NATIVE_WINDOWS}
  IMAGE_SUBSYSTEM_WINDOWS_CE_GUI          = 9; // Image runs in the Windows CE subsystem.
  {$EXTERNALSYM IMAGE_SUBSYSTEM_WINDOWS_CE_GUI}
  IMAGE_SUBSYSTEM_EFI_APPLICATION         = 10;
  {$EXTERNALSYM IMAGE_SUBSYSTEM_EFI_APPLICATION}
  IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER = 11;
  {$EXTERNALSYM IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER}
  IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER      = 12;
  {$EXTERNALSYM IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER}
  IMAGE_SUBSYSTEM_EFI_ROM                 = 13;
  {$EXTERNALSYM IMAGE_SUBSYSTEM_EFI_ROM}
  IMAGE_SUBSYSTEM_XBOX                    = 14;
  {$EXTERNALSYM IMAGE_SUBSYSTEM_XBOX}

// DllCharacteristics Entries

//      IMAGE_LIBRARY_PROCESS_INIT           0x0001     // Reserved.
//      IMAGE_LIBRARY_PROCESS_TERM           0x0002     // Reserved.
//      IMAGE_LIBRARY_THREAD_INIT            0x0004     // Reserved.
//      IMAGE_LIBRARY_THREAD_TERM            0x0008     // Reserved.
  IMAGE_DLLCHARACTERISTICS_NO_ISOLATION = $0200;    // Image understands isolation and doesn't want it
  {$EXTERNALSYM IMAGE_DLLCHARACTERISTICS_NO_ISOLATION}
  IMAGE_DLLCHARACTERISTICS_NO_SEH  = $0400; // Image does not use SEH.  No SE handler may reside in this image
  {$EXTERNALSYM IMAGE_DLLCHARACTERISTICS_NO_SEH}
  IMAGE_DLLCHARACTERISTICS_NO_BIND = $0800; // Do not bind this image.
  {$EXTERNALSYM IMAGE_DLLCHARACTERISTICS_NO_BIND}

//                                           0x1000     // Reserved.

  IMAGE_DLLCHARACTERISTICS_WDM_DRIVER = $2000; // Driver uses WDM model
  {$EXTERNALSYM IMAGE_DLLCHARACTERISTICS_WDM_DRIVER}

//                                           0x4000     // Reserved.

  IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE = $8000;
  {$EXTERNALSYM IMAGE_DLLCHARACTERISTICS_TERMINAL_SERVER_AWARE}

// Directory Entries

  IMAGE_DIRECTORY_ENTRY_EXPORT    = 0; // Export Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_EXPORT}
  IMAGE_DIRECTORY_ENTRY_IMPORT    = 1; // Import Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_IMPORT}
  IMAGE_DIRECTORY_ENTRY_RESOURCE  = 2; // Resource Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_RESOURCE}
  IMAGE_DIRECTORY_ENTRY_EXCEPTION = 3; // Exception Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_EXCEPTION}
  IMAGE_DIRECTORY_ENTRY_SECURITY  = 4; // Security Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_SECURITY}
  IMAGE_DIRECTORY_ENTRY_BASERELOC = 5; // Base Relocation Table
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_BASERELOC}
  IMAGE_DIRECTORY_ENTRY_DEBUG     = 6; // Debug Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_DEBUG}

//      IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)

  IMAGE_DIRECTORY_ENTRY_ARCHITECTURE   = 7; // Architecture Specific Data
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_ARCHITECTURE}
  IMAGE_DIRECTORY_ENTRY_GLOBALPTR      = 8; // RVA of GP
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_GLOBALPTR}
  IMAGE_DIRECTORY_ENTRY_TLS            = 9; // TLS Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_TLS}
  IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    = 10; // Load Configuration Directory
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG}
  IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   = 11; // Bound Import Directory in headers
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT}
  IMAGE_DIRECTORY_ENTRY_IAT            = 12; // Import Address Table
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_IAT}
  IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   = 13; // Delay Load Import Descriptors
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT}
  IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR = 14; // COM Runtime descriptor
  {$EXTERNALSYM IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR}

//
// Non-COFF Object file header
//

type
  PAnonObjectHeader = ^ANON_OBJECT_HEADER;
  ANON_OBJECT_HEADER = record
    Sig1: Word;        // Must be IMAGE_FILE_MACHINE_UNKNOWN
    Sig2: Word;        // Must be 0xffff
    Version: Word;     // >= 1 (implies the CLSID field is present)
    Machine: Word;
    TimeDateStamp: DWORD;
    ClassID: CLSID;    // Used to invoke CoCreateInstance
    SizeOfData: DWORD; // Size of data that follows the header
  end;
  {$EXTERNALSYM ANON_OBJECT_HEADER}
  TAnonObjectHeader = ANON_OBJECT_HEADER;

//
// Section header format.
//

const
  IMAGE_SIZEOF_SHORT_NAME = 8;
  {$EXTERNALSYM IMAGE_SIZEOF_SHORT_NAME}

type
  TImgSecHdrMisc = record
    case Integer of
      0: (PhysicalAddress: DWORD);
      1: (VirtualSize: DWORD);
  end;

  PIMAGE_SECTION_HEADER = ^IMAGE_SECTION_HEADER;
  {$EXTERNALSYM PIMAGE_SECTION_HEADER}
  _IMAGE_SECTION_HEADER = record
    Name: array [0..IMAGE_SIZEOF_SHORT_NAME - 1] of BYTE;
    Misc: TImgSecHdrMisc;
    VirtualAddress: DWORD;
    SizeOfRawData: DWORD;
    PointerToRawData: DWORD;
    PointerToRelocations: DWORD;
    PointerToLinenumbers: DWORD;
    NumberOfRelocations: WORD;
    NumberOfLinenumbers: WORD;
    Characteristics: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_SECTION_HEADER}
  IMAGE_SECTION_HEADER = _IMAGE_SECTION_HEADER;
  {$EXTERNALSYM IMAGE_SECTION_HEADER}
  TImageSectionHeader = IMAGE_SECTION_HEADER;
  PImageSectionHeader = PIMAGE_SECTION_HEADER;

// IMAGE_FIRST_SECTION doesn't need 32/64 versions since the file header is the same either way.

function IMAGE_FIRST_SECTION(NtHeader: PImageNtHeaders): PImageSectionHeader;
{$EXTERNALSYM IMAGE_FIRST_SECTION}
  
const
  IMAGE_SIZEOF_SECTION_HEADER = 40;
  {$EXTERNALSYM IMAGE_SIZEOF_SECTION_HEADER}

//
// Section characteristics.
//
//      IMAGE_SCN_TYPE_REG                   0x00000000  // Reserved.
//      IMAGE_SCN_TYPE_DSECT                 0x00000001  // Reserved.
//      IMAGE_SCN_TYPE_NOLOAD                0x00000002  // Reserved.
//      IMAGE_SCN_TYPE_GROUP                 0x00000004  // Reserved.

  IMAGE_SCN_TYPE_NO_PAD = $00000008; // Reserved.
  {$EXTERNALSYM IMAGE_SCN_TYPE_NO_PAD}

//      IMAGE_SCN_TYPE_COPY                  0x00000010  // Reserved.

  IMAGE_SCN_CNT_CODE               = $00000020; // Section contains code.
  {$EXTERNALSYM IMAGE_SCN_CNT_CODE}
  IMAGE_SCN_CNT_INITIALIZED_DATA   = $00000040; // Section contains initialized data.
  {$EXTERNALSYM IMAGE_SCN_CNT_INITIALIZED_DATA}
  IMAGE_SCN_CNT_UNINITIALIZED_DATA = $00000080; // Section contains uninitialized data.
  {$EXTERNALSYM IMAGE_SCN_CNT_UNINITIALIZED_DATA}

  IMAGE_SCN_LNK_OTHER = $00000100; // Reserved.
  {$EXTERNALSYM IMAGE_SCN_LNK_OTHER}
  IMAGE_SCN_LNK_INFO  = $00000200; // Section contains comments or some other type of information.
  {$EXTERNALSYM IMAGE_SCN_LNK_INFO}

//      IMAGE_SCN_TYPE_OVER                  0x00000400  // Reserved.

  IMAGE_SCN_LNK_REMOVE = $00000800; // Section contents will not become part of image.
  {$EXTERNALSYM IMAGE_SCN_LNK_REMOVE}
  IMAGE_SCN_LNK_COMDAT = $00001000; // Section contents comdat.
  {$EXTERNALSYM IMAGE_SCN_LNK_COMDAT}

//                                           0x00002000  // Reserved.
//      IMAGE_SCN_MEM_PROTECTED - Obsolete   0x00004000

  IMAGE_SCN_NO_DEFER_SPEC_EXC = $00004000; // Reset speculative exceptions handling bits in the TLB entries for this section.
  {$EXTERNALSYM IMAGE_SCN_NO_DEFER_SPEC_EXC}
  IMAGE_SCN_GPREL             = $00008000; // Section content can be accessed relative to GP
  {$EXTERNALSYM IMAGE_SCN_GPREL}
  IMAGE_SCN_MEM_FARDATA       = $00008000;
  {$EXTERNALSYM IMAGE_SCN_MEM_FARDATA}

//      IMAGE_SCN_MEM_SYSHEAP  - Obsolete    0x00010000

  IMAGE_SCN_MEM_PURGEABLE = $00020000;
  {$EXTERNALSYM IMAGE_SCN_MEM_PURGEABLE}
  IMAGE_SCN_MEM_16BIT     = $00020000;
  {$EXTERNALSYM IMAGE_SCN_MEM_16BIT}
  IMAGE_SCN_MEM_LOCKED    = $00040000;
  {$EXTERNALSYM IMAGE_SCN_MEM_LOCKED}
  IMAGE_SCN_MEM_PRELOAD   = $00080000;
  {$EXTERNALSYM IMAGE_SCN_MEM_PRELOAD}

  IMAGE_SCN_ALIGN_1BYTES    = $00100000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_1BYTES}
  IMAGE_SCN_ALIGN_2BYTES    = $00200000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_2BYTES}
  IMAGE_SCN_ALIGN_4BYTES    = $00300000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_4BYTES}
  IMAGE_SCN_ALIGN_8BYTES    = $00400000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_8BYTES}
  IMAGE_SCN_ALIGN_16BYTES   = $00500000; // Default alignment if no others are specified.
  {$EXTERNALSYM IMAGE_SCN_ALIGN_16BYTES}
  IMAGE_SCN_ALIGN_32BYTES   = $00600000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_32BYTES}
  IMAGE_SCN_ALIGN_64BYTES   = $00700000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_64BYTES}
  IMAGE_SCN_ALIGN_128BYTES  = $00800000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_128BYTES}
  IMAGE_SCN_ALIGN_256BYTES  = $00900000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_256BYTES}
  IMAGE_SCN_ALIGN_512BYTES  = $00A00000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_512BYTES}
  IMAGE_SCN_ALIGN_1024BYTES = $00B00000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_1024BYTES}
  IMAGE_SCN_ALIGN_2048BYTES = $00C00000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_2048BYTES}
  IMAGE_SCN_ALIGN_4096BYTES = $00D00000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_4096BYTES}
  IMAGE_SCN_ALIGN_8192BYTES = $00E00000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_8192BYTES}

// Unused                                    0x00F00000

  IMAGE_SCN_ALIGN_MASK = $00F00000;
  {$EXTERNALSYM IMAGE_SCN_ALIGN_MASK}

  IMAGE_SCN_LNK_NRELOC_OVFL = $01000000; // Section contains extended relocations.
  {$EXTERNALSYM IMAGE_SCN_LNK_NRELOC_OVFL}
  IMAGE_SCN_MEM_DISCARDABLE = $02000000; // Section can be discarded.
  {$EXTERNALSYM IMAGE_SCN_MEM_DISCARDABLE}
  IMAGE_SCN_MEM_NOT_CACHED  = $04000000; // Section is not cachable.
  {$EXTERNALSYM IMAGE_SCN_MEM_NOT_CACHED}
  IMAGE_SCN_MEM_NOT_PAGED   = $08000000; // Section is not pageable.
  {$EXTERNALSYM IMAGE_SCN_MEM_NOT_PAGED}
  IMAGE_SCN_MEM_SHARED      = $10000000; // Section is shareable.
  {$EXTERNALSYM IMAGE_SCN_MEM_SHARED}
  IMAGE_SCN_MEM_EXECUTE     = $20000000; // Section is executable.
  {$EXTERNALSYM IMAGE_SCN_MEM_EXECUTE}
  IMAGE_SCN_MEM_READ        = $40000000; // Section is readable.
  {$EXTERNALSYM IMAGE_SCN_MEM_READ}
  IMAGE_SCN_MEM_WRITE       = DWORD($80000000); // Section is writeable.
  {$EXTERNALSYM IMAGE_SCN_MEM_WRITE}

//
// TLS Chaacteristic Flags
//

  IMAGE_SCN_SCALE_INDEX = $00000001; // Tls index is scaled
  {$EXTERNALSYM IMAGE_SCN_SCALE_INDEX}

// #include "pshpack2.h"                       // Symbols, relocs, and linenumbers are 2 byte packed

//
// Symbol format.
//

type
  TImageSymbolN = record
    case Integer of
      0: (
        ShortName: array [0..7] of BYTE);
      1: (
        Short: DWORD;     // if 0, use LongName
        Long: DWORD);     // offset into string table
      2: (
        LongName: array [0..1] of DWORD);
  end;

  PIMAGE_SYMBOL = ^IMAGE_SYMBOL;
  {$EXTERNALSYM PIMAGE_SYMBOL}
  _IMAGE_SYMBOL = record
    N: TImageSymbolN;
    Value: DWORD;
    SectionNumber: SHORT;
    Type_: WORD;
    StorageClass: BYTE;
    NumberOfAuxSymbols: BYTE;
  end;
  {$EXTERNALSYM _IMAGE_SYMBOL}
  IMAGE_SYMBOL = _IMAGE_SYMBOL;
  {$EXTERNALSYM IMAGE_SYMBOL}
  TImageSymbol = IMAGE_SYMBOL;
  PImageSymbol = PIMAGE_SYMBOL;

const
  IMAGE_SIZEOF_SYMBOL = 18;
  {$EXTERNALSYM IMAGE_SIZEOF_SYMBOL}

//
// Section values.
//
// Symbols have a section number of the section in which they are
// defined. Otherwise, section numbers have the following meanings:
//

  IMAGE_SYM_UNDEFINED = SHORT(0);  // Symbol is undefined or is common.
  {$EXTERNALSYM IMAGE_SYM_UNDEFINED}
  IMAGE_SYM_ABSOLUTE  = SHORT(-1); // Symbol is an absolute value.
  {$EXTERNALSYM IMAGE_SYM_ABSOLUTE}
  IMAGE_SYM_DEBUG     = SHORT(-2); // Symbol is a special debug item.
  {$EXTERNALSYM IMAGE_SYM_DEBUG}
  IMAGE_SYM_SECTION_MAX = SHORT($FEFF ); // Values 0xFF00-0xFFFF are special
  {$EXTERNALSYM IMAGE_SYM_SECTION_MAX}

//
// Type (fundamental) values.
//

  IMAGE_SYM_TYPE_NULL   = $0000; // no type.
  {$EXTERNALSYM IMAGE_SYM_TYPE_NULL}
  IMAGE_SYM_TYPE_VOID   = $0001;
  {$EXTERNALSYM IMAGE_SYM_TYPE_VOID}
  IMAGE_SYM_TYPE_CHAR   = $0002; // type character.
  {$EXTERNALSYM IMAGE_SYM_TYPE_CHAR}
  IMAGE_SYM_TYPE_SHORT  = $0003; // type short integer.
  {$EXTERNALSYM IMAGE_SYM_TYPE_SHORT}
  IMAGE_SYM_TYPE_INT    = $0004;
  {$EXTERNALSYM IMAGE_SYM_TYPE_INT}
  IMAGE_SYM_TYPE_LONG   = $0005;
  {$EXTERNALSYM IMAGE_SYM_TYPE_LONG}
  IMAGE_SYM_TYPE_FLOAT  = $0006;
  {$EXTERNALSYM IMAGE_SYM_TYPE_FLOAT}
  IMAGE_SYM_TYPE_DOUBLE = $0007;
  {$EXTERNALSYM IMAGE_SYM_TYPE_DOUBLE}
  IMAGE_SYM_TYPE_STRUCT = $0008;
  {$EXTERNALSYM IMAGE_SYM_TYPE_STRUCT}
  IMAGE_SYM_TYPE_UNION  = $0009;
  {$EXTERNALSYM IMAGE_SYM_TYPE_UNION}
  IMAGE_SYM_TYPE_ENUM   = $000A; // enumeration.
  {$EXTERNALSYM IMAGE_SYM_TYPE_ENUM}
  IMAGE_SYM_TYPE_MOE    = $000B; // member of enumeration.
  {$EXTERNALSYM IMAGE_SYM_TYPE_MOE}
  IMAGE_SYM_TYPE_BYTE   = $000C;
  {$EXTERNALSYM IMAGE_SYM_TYPE_BYTE}
  IMAGE_SYM_TYPE_WORD   = $000D;
  {$EXTERNALSYM IMAGE_SYM_TYPE_WORD}
  IMAGE_SYM_TYPE_UINT   = $000E;
  {$EXTERNALSYM IMAGE_SYM_TYPE_UINT}
  IMAGE_SYM_TYPE_DWORD  = $000F;
  {$EXTERNALSYM IMAGE_SYM_TYPE_DWORD}
  IMAGE_SYM_TYPE_PCODE  = $8000;
  {$EXTERNALSYM IMAGE_SYM_TYPE_PCODE}

//
// Type (derived) values.
//

  IMAGE_SYM_DTYPE_NULL     = 0; // no derived type.
  {$EXTERNALSYM IMAGE_SYM_DTYPE_NULL}
  IMAGE_SYM_DTYPE_POINTER  = 1; // pointer.
  {$EXTERNALSYM IMAGE_SYM_DTYPE_POINTER}
  IMAGE_SYM_DTYPE_FUNCTION = 2; // function.
  {$EXTERNALSYM IMAGE_SYM_DTYPE_FUNCTION}
  IMAGE_SYM_DTYPE_ARRAY    = 3; // array.
  {$EXTERNALSYM IMAGE_SYM_DTYPE_ARRAY}

//
// Storage classes.
//

  IMAGE_SYM_CLASS_END_OF_FUNCTION  = BYTE(-1);
  {$EXTERNALSYM IMAGE_SYM_CLASS_END_OF_FUNCTION}
  IMAGE_SYM_CLASS_NULL             = $0000;
  {$EXTERNALSYM IMAGE_SYM_CLASS_NULL}
  IMAGE_SYM_CLASS_AUTOMATIC        = $0001;
  {$EXTERNALSYM IMAGE_SYM_CLASS_AUTOMATIC}
  IMAGE_SYM_CLASS_EXTERNAL         = $0002;
  {$EXTERNALSYM IMAGE_SYM_CLASS_EXTERNAL}
  IMAGE_SYM_CLASS_STATIC           = $0003;
  {$EXTERNALSYM IMAGE_SYM_CLASS_STATIC}
  IMAGE_SYM_CLASS_REGISTER         = $0004;
  {$EXTERNALSYM IMAGE_SYM_CLASS_REGISTER}
  IMAGE_SYM_CLASS_EXTERNAL_DEF     = $0005;
  {$EXTERNALSYM IMAGE_SYM_CLASS_EXTERNAL_DEF}
  IMAGE_SYM_CLASS_LABEL            = $0006;
  {$EXTERNALSYM IMAGE_SYM_CLASS_LABEL}
  IMAGE_SYM_CLASS_UNDEFINED_LABEL  = $0007;
  {$EXTERNALSYM IMAGE_SYM_CLASS_UNDEFINED_LABEL}
  IMAGE_SYM_CLASS_MEMBER_OF_STRUCT = $0008;
  {$EXTERNALSYM IMAGE_SYM_CLASS_MEMBER_OF_STRUCT}
  IMAGE_SYM_CLASS_ARGUMENT         = $0009;
  {$EXTERNALSYM IMAGE_SYM_CLASS_ARGUMENT}
  IMAGE_SYM_CLASS_STRUCT_TAG       = $000A;
  {$EXTERNALSYM IMAGE_SYM_CLASS_STRUCT_TAG}
  IMAGE_SYM_CLASS_MEMBER_OF_UNION  = $000B;
  {$EXTERNALSYM IMAGE_SYM_CLASS_MEMBER_OF_UNION}
  IMAGE_SYM_CLASS_UNION_TAG        = $000C;
  {$EXTERNALSYM IMAGE_SYM_CLASS_UNION_TAG}
  IMAGE_SYM_CLASS_TYPE_DEFINITION  = $000D;
  {$EXTERNALSYM IMAGE_SYM_CLASS_TYPE_DEFINITION}
  IMAGE_SYM_CLASS_UNDEFINED_STATIC = $000E;
  {$EXTERNALSYM IMAGE_SYM_CLASS_UNDEFINED_STATIC}
  IMAGE_SYM_CLASS_ENUM_TAG         = $000F;
  {$EXTERNALSYM IMAGE_SYM_CLASS_ENUM_TAG}
  IMAGE_SYM_CLASS_MEMBER_OF_ENUM   = $0010;
  {$EXTERNALSYM IMAGE_SYM_CLASS_MEMBER_OF_ENUM}
  IMAGE_SYM_CLASS_REGISTER_PARAM   = $0011;
  {$EXTERNALSYM IMAGE_SYM_CLASS_REGISTER_PARAM}
  IMAGE_SYM_CLASS_BIT_FIELD        = $0012;
  {$EXTERNALSYM IMAGE_SYM_CLASS_BIT_FIELD}

  IMAGE_SYM_CLASS_FAR_EXTERNAL = $0044;
  {$EXTERNALSYM IMAGE_SYM_CLASS_FAR_EXTERNAL}

  IMAGE_SYM_CLASS_BLOCK         = $0064;
  {$EXTERNALSYM IMAGE_SYM_CLASS_BLOCK}
  IMAGE_SYM_CLASS_FUNCTION      = $0065;
  {$EXTERNALSYM IMAGE_SYM_CLASS_FUNCTION}
  IMAGE_SYM_CLASS_END_OF_STRUCT = $0066;
  {$EXTERNALSYM IMAGE_SYM_CLASS_END_OF_STRUCT}
  IMAGE_SYM_CLASS_FILE          = $0067;
  {$EXTERNALSYM IMAGE_SYM_CLASS_FILE}

// new

  IMAGE_SYM_CLASS_SECTION       = $0068;
  {$EXTERNALSYM IMAGE_SYM_CLASS_SECTION}
  IMAGE_SYM_CLASS_WEAK_EXTERNAL = $0069;
  {$EXTERNALSYM IMAGE_SYM_CLASS_WEAK_EXTERNAL}

  IMAGE_SYM_CLASS_CLR_TOKEN     = $006B;
  {$EXTERNALSYM IMAGE_SYM_CLASS_CLR_TOKEN}

// type packing constants

  N_BTMASK = $000F;
  {$EXTERNALSYM N_BTMASK}
  N_TMASK  = $0030;
  {$EXTERNALSYM N_TMASK}
  N_TMASK1 = $00C0;
  {$EXTERNALSYM N_TMASK1}
  N_TMASK2 = $00F0;
  {$EXTERNALSYM N_TMASK2}
  N_BTSHFT = 4;
  {$EXTERNALSYM N_BTSHFT}
  N_TSHIFT = 2;
  {$EXTERNALSYM N_TSHIFT}

// MACROS

// Basic Type of  x

function BTYPE(x: DWORD): DWORD;
{$EXTERNALSYM BTYPE}

// Is x a pointer?

function ISPTR(x: DWORD): Boolean;
{$EXTERNALSYM ISPTR}

// Is x a function?

function ISFCN(x: DWORD): Boolean;
{$EXTERNALSYM ISFCN}

// Is x an array?

function ISARY(x: DWORD): Boolean;
{$EXTERNALSYM ISARY}

// Is x a structure, union, or enumeration TAG?

function ISTAG(x: DWORD): Boolean;
{$EXTERNALSYM ISTAG}

//
// Auxiliary entry format.
//

type
  TImgAuzSymSymMisc = record
    case Integer of
      0: (
        Linenumber: WORD;             // declaration line number
        Size: WORD);                  // size of struct, union, or enum
      1: (
        TotalSize: DWORD);
  end;

  TImgAuzSymSymFcnAry = record
    case Integer of
      0: ( // if ISFCN, tag, or .bb
        PointerToLinenumber: DWORD;
        PointerToNextFunction: DWORD);
      1: ( // if ISARY, up to 4 dimen.
        Dimension: array [0..3] of WORD);
  end;

  TImgAuxSymSym = record
    TagIndex: DWORD;                      // struct, union, or enum tag index
    Misc: TImgAuzSymSymMisc;
    FcnAry: TImgAuzSymSymFcnAry;
    TvIndex: WORD;                        // tv index
  end;

  TImgAuxSymFile = record
    Name: array [0..IMAGE_SIZEOF_SYMBOL - 1] of BYTE;
  end;

  TImgAuxSymSection = record
    Length: DWORD;                         // section length
    NumberOfRelocations: WORD;             // number of relocation entries
    NumberOfLinenumbers: WORD;             // number of line numbers
    CheckSum: DWORD;                       // checksum for communal
    Number: SHORT;                         // section number to associate with
    Selection: BYTE;                       // communal selection type
  end;

  PIMAGE_AUX_SYMBOL = ^IMAGE_AUX_SYMBOL;
  {$EXTERNALSYM PIMAGE_AUX_SYMBOL}
  _IMAGE_AUX_SYMBOL = record
    case Integer of
      0: (Sym: TImgAuxSymSym);
      1: (File_: TImgAuxSymFile);
      2: (Section: TImgAuxSymSection);
  end;
  {$EXTERNALSYM _IMAGE_AUX_SYMBOL}
  IMAGE_AUX_SYMBOL = _IMAGE_AUX_SYMBOL;
  {$EXTERNALSYM IMAGE_AUX_SYMBOL}
  TImageAuxSymbol = IMAGE_AUX_SYMBOL;
  PImageAuxSymbol = PIMAGE_AUX_SYMBOL;

const
  IMAGE_SIZEOF_AUX_SYMBOL = 18;
  {$EXTERNALSYM IMAGE_SIZEOF_AUX_SYMBOL}

  IMAGE_AUX_SYMBOL_TYPE_TOKEN_DEF = 1;
  {$EXTERNALSYM IMAGE_AUX_SYMBOL_TYPE_TOKEN_DEF}

type
  IMAGE_AUX_SYMBOL_TYPE = DWORD;
  {$EXTERNALSYM IMAGE_AUX_SYMBOL_TYPE}
  TImageAuxSymbolType = IMAGE_AUX_SYMBOL_TYPE;

  IMAGE_AUX_SYMBOL_TOKEN_DEF = packed record
    bAuxType: BYTE;                  // IMAGE_AUX_SYMBOL_TYPE
    bReserved: BYTE;                 // Must be 0
    SymbolTableIndex: DWORD;
    rgbReserved: array [0..11] of BYTE;           // Must be 0
  end;
  {$EXTERNALSYM IMAGE_AUX_SYMBOL_TOKEN_DEF}
  PIMAGE_AUX_SYMBOL_TOKEN_DEF = ^IMAGE_AUX_SYMBOL_TOKEN_DEF;
  {$EXTERNALSYM PIMAGE_AUX_SYMBOL_TOKEN_DEF}
  TImageAuxSymbolTokenDef = IMAGE_AUX_SYMBOL_TOKEN_DEF;
  PImageAuxSymbolTokenDef = PIMAGE_AUX_SYMBOL_TOKEN_DEF;

//
// Communal selection types.
//

const
  IMAGE_COMDAT_SELECT_NODUPLICATES = 1;
  {$EXTERNALSYM IMAGE_COMDAT_SELECT_NODUPLICATES}
  IMAGE_COMDAT_SELECT_ANY          = 2;
  {$EXTERNALSYM IMAGE_COMDAT_SELECT_ANY}
  IMAGE_COMDAT_SELECT_SAME_SIZE    = 3;
  {$EXTERNALSYM IMAGE_COMDAT_SELECT_SAME_SIZE}
  IMAGE_COMDAT_SELECT_EXACT_MATCH  = 4;
  {$EXTERNALSYM IMAGE_COMDAT_SELECT_EXACT_MATCH}
  IMAGE_COMDAT_SELECT_ASSOCIATIVE  = 5;
  {$EXTERNALSYM IMAGE_COMDAT_SELECT_ASSOCIATIVE}
  IMAGE_COMDAT_SELECT_LARGEST      = 6;
  {$EXTERNALSYM IMAGE_COMDAT_SELECT_LARGEST}
  IMAGE_COMDAT_SELECT_NEWEST       = 7;
  {$EXTERNALSYM IMAGE_COMDAT_SELECT_NEWEST}

  IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY = 1;
  {$EXTERNALSYM IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY}
  IMAGE_WEAK_EXTERN_SEARCH_LIBRARY   = 2;
  {$EXTERNALSYM IMAGE_WEAK_EXTERN_SEARCH_LIBRARY}
  IMAGE_WEAK_EXTERN_SEARCH_ALIAS     = 3;
  {$EXTERNALSYM IMAGE_WEAK_EXTERN_SEARCH_ALIAS}

//
// Relocation format.
//

type
  TImgRelocUnion = record
    case Integer of
      0: (VirtualAddress: DWORD);
      1: (RelocCount: DWORD);  // Set to the real count when IMAGE_SCN_LNK_NRELOC_OVFL is set
  end;

  PIMAGE_RELOCATION = ^IMAGE_RELOCATION;
  {$EXTERNALSYM PIMAGE_RELOCATION}
  _IMAGE_RELOCATION = record
    Union: TImgRelocUnion;
    SymbolTableIndex: DWORD;
    Type_: WORD;
  end;
  {$EXTERNALSYM _IMAGE_RELOCATION}
  IMAGE_RELOCATION = _IMAGE_RELOCATION;
  {$EXTERNALSYM IMAGE_RELOCATION}
  TImageRelocation = IMAGE_RELOCATION;
  PImageRelocation = PIMAGE_RELOCATION;

const
  IMAGE_SIZEOF_RELOCATION = 10;
  {$EXTERNALSYM IMAGE_SIZEOF_RELOCATION}

//
// I386 relocation types.
//

  IMAGE_REL_I386_ABSOLUTE = $0000; // Reference is absolute, no relocation is necessary
  {$EXTERNALSYM IMAGE_REL_I386_ABSOLUTE}
  IMAGE_REL_I386_DIR16    = $0001; // Direct 16-bit reference to the symbols virtual address
  {$EXTERNALSYM IMAGE_REL_I386_DIR16}
  IMAGE_REL_I386_REL16    = $0002; // PC-relative 16-bit reference to the symbols virtual address
  {$EXTERNALSYM IMAGE_REL_I386_REL16}
  IMAGE_REL_I386_DIR32    = $0006; // Direct 32-bit reference to the symbols virtual address
  {$EXTERNALSYM IMAGE_REL_I386_DIR32}
  IMAGE_REL_I386_DIR32NB  = $0007; // Direct 32-bit reference to the symbols virtual address, base not included
  {$EXTERNALSYM IMAGE_REL_I386_DIR32NB}
  IMAGE_REL_I386_SEG12    = $0009; // Direct 16-bit reference to the segment-selector bits of a 32-bit virtual address
  {$EXTERNALSYM IMAGE_REL_I386_SEG12}
  IMAGE_REL_I386_SECTION  = $000A;
  {$EXTERNALSYM IMAGE_REL_I386_SECTION}
  IMAGE_REL_I386_SECREL   = $000B;
  {$EXTERNALSYM IMAGE_REL_I386_SECREL}
  IMAGE_REL_MIPS_SECRELLO = $000C; // Low 16-bit section relative referemce (used for >32k TLS)
  {$EXTERNALSYM IMAGE_REL_MIPS_SECRELLO}
  IMAGE_REL_MIPS_SECRELHI = $000D; // High 16-bit section relative reference (used for >32k TLS)
  {$EXTERNALSYM IMAGE_REL_MIPS_SECRELHI}
  IMAGE_REL_I386_REL32    = $0014; // PC-relative 32-bit reference to the symbols virtual address
  {$EXTERNALSYM IMAGE_REL_I386_REL32}

//
// MIPS relocation types.
//

  IMAGE_REL_MIPS_ABSOLUTE  = $0000; // Reference is absolute, no relocation is necessary
  {$EXTERNALSYM IMAGE_REL_MIPS_ABSOLUTE}
  IMAGE_REL_MIPS_REFHALF   = $0001;
  {$EXTERNALSYM IMAGE_REL_MIPS_REFHALF}
  IMAGE_REL_MIPS_REFWORD   = $0002;
  {$EXTERNALSYM IMAGE_REL_MIPS_REFWORD}
  IMAGE_REL_MIPS_JMPADDR   = $0003;
  {$EXTERNALSYM IMAGE_REL_MIPS_JMPADDR}
  IMAGE_REL_MIPS_REFHI     = $0004;
  {$EXTERNALSYM IMAGE_REL_MIPS_REFHI}
  IMAGE_REL_MIPS_REFLO     = $0005;
  {$EXTERNALSYM IMAGE_REL_MIPS_REFLO}
  IMAGE_REL_MIPS_GPREL     = $0006;
  {$EXTERNALSYM IMAGE_REL_MIPS_GPREL}
  IMAGE_REL_MIPS_LITERAL   = $0007;
  {$EXTERNALSYM IMAGE_REL_MIPS_LITERAL}
  IMAGE_REL_MIPS_SECTION   = $000A;
  {$EXTERNALSYM IMAGE_REL_MIPS_SECTION}
  IMAGE_REL_MIPS_SECREL    = $000B;
  {$EXTERNALSYM IMAGE_REL_MIPS_SECREL}
  //IMAGE_REL_MIPS_SECRELLO  = $000C; // Low 16-bit section relative referemce (used for >32k TLS)
  //{$EXTERNALSYM IMAGE_REL_MIPS_SECRELLO}
  //IMAGE_REL_MIPS_SECRELHI  = $000D; // High 16-bit section relative reference (used for >32k TLS)
  //{$EXTERNALSYM IMAGE_REL_MIPS_SECRELHI}
  IMAGE_REL_MIPS_TOKEN     = $000E; // clr token
  {$EXTERNALSYM IMAGE_REL_MIPS_TOKEN}
  IMAGE_REL_MIPS_JMPADDR16 = $0010;
  {$EXTERNALSYM IMAGE_REL_MIPS_JMPADDR16}
  IMAGE_REL_MIPS_REFWORDNB = $0022;
  {$EXTERNALSYM IMAGE_REL_MIPS_REFWORDNB}
  IMAGE_REL_MIPS_PAIR      = $0025;
  {$EXTERNALSYM IMAGE_REL_MIPS_PAIR}

//
// Alpha Relocation types.
//

  IMAGE_REL_ALPHA_ABSOLUTE       = $0000;
  {$EXTERNALSYM IMAGE_REL_ALPHA_ABSOLUTE}
  IMAGE_REL_ALPHA_REFLONG        = $0001;
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFLONG}
  IMAGE_REL_ALPHA_REFQUAD        = $0002;
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFQUAD}
  IMAGE_REL_ALPHA_GPREL32        = $0003;
  {$EXTERNALSYM IMAGE_REL_ALPHA_GPREL32}
  IMAGE_REL_ALPHA_LITERAL        = $0004;
  {$EXTERNALSYM IMAGE_REL_ALPHA_LITERAL}
  IMAGE_REL_ALPHA_LITUSE         = $0005;
  {$EXTERNALSYM IMAGE_REL_ALPHA_LITUSE}
  IMAGE_REL_ALPHA_GPDISP         = $0006;
  {$EXTERNALSYM IMAGE_REL_ALPHA_GPDISP}
  IMAGE_REL_ALPHA_BRADDR         = $0007;
  {$EXTERNALSYM IMAGE_REL_ALPHA_BRADDR}
  IMAGE_REL_ALPHA_HINT           = $0008;
  {$EXTERNALSYM IMAGE_REL_ALPHA_HINT}
  IMAGE_REL_ALPHA_INLINE_REFLONG = $0009;
  {$EXTERNALSYM IMAGE_REL_ALPHA_INLINE_REFLONG}
  IMAGE_REL_ALPHA_REFHI          = $000A;
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFHI}
  IMAGE_REL_ALPHA_REFLO          = $000B;
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFLO}
  IMAGE_REL_ALPHA_PAIR           = $000C;
  {$EXTERNALSYM IMAGE_REL_ALPHA_PAIR}
  IMAGE_REL_ALPHA_MATCH          = $000D;
  {$EXTERNALSYM IMAGE_REL_ALPHA_MATCH}
  IMAGE_REL_ALPHA_SECTION        = $000E;
  {$EXTERNALSYM IMAGE_REL_ALPHA_SECTION}
  IMAGE_REL_ALPHA_SECREL         = $000F;
  {$EXTERNALSYM IMAGE_REL_ALPHA_SECREL}
  IMAGE_REL_ALPHA_REFLONGNB      = $0010;
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFLONGNB}
  IMAGE_REL_ALPHA_SECRELLO       = $0011; // Low 16-bit section relative reference
  {$EXTERNALSYM IMAGE_REL_ALPHA_SECRELLO}
  IMAGE_REL_ALPHA_SECRELHI       = $0012; // High 16-bit section relative reference
  {$EXTERNALSYM IMAGE_REL_ALPHA_SECRELHI}
  IMAGE_REL_ALPHA_REFQ3          = $0013; // High 16 bits of 48 bit reference
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFQ3}
  IMAGE_REL_ALPHA_REFQ2          = $0014; // Middle 16 bits of 48 bit reference
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFQ2}
  IMAGE_REL_ALPHA_REFQ1          = $0015; // Low 16 bits of 48 bit reference
  {$EXTERNALSYM IMAGE_REL_ALPHA_REFQ1}
  IMAGE_REL_ALPHA_GPRELLO        = $0016; // Low 16-bit GP relative reference
  {$EXTERNALSYM IMAGE_REL_ALPHA_GPRELLO}
  IMAGE_REL_ALPHA_GPRELHI        = $0017; // High 16-bit GP relative reference
  {$EXTERNALSYM IMAGE_REL_ALPHA_GPRELHI}

//
// IBM PowerPC relocation types.
//

  IMAGE_REL_PPC_ABSOLUTE = $0000; // NOP
  {$EXTERNALSYM IMAGE_REL_PPC_ABSOLUTE}
  IMAGE_REL_PPC_ADDR64   = $0001; // 64-bit address
  {$EXTERNALSYM IMAGE_REL_PPC_ADDR64}
  IMAGE_REL_PPC_ADDR32   = $0002; // 32-bit address
  {$EXTERNALSYM IMAGE_REL_PPC_ADDR32}
  IMAGE_REL_PPC_ADDR24   = $0003; // 26-bit address, shifted left 2 (branch absolute)
  {$EXTERNALSYM IMAGE_REL_PPC_ADDR24}
  IMAGE_REL_PPC_ADDR16   = $0004; // 16-bit address
  {$EXTERNALSYM IMAGE_REL_PPC_ADDR16}
  IMAGE_REL_PPC_ADDR14   = $0005; // 16-bit address, shifted left 2 (load doubleword)
  {$EXTERNALSYM IMAGE_REL_PPC_ADDR14}
  IMAGE_REL_PPC_REL24    = $0006; // 26-bit PC-relative offset, shifted left 2 (branch relative)
  {$EXTERNALSYM IMAGE_REL_PPC_REL24}
  IMAGE_REL_PPC_REL14    = $0007; // 16-bit PC-relative offset, shifted left 2 (br cond relative)
  {$EXTERNALSYM IMAGE_REL_PPC_REL14}
  IMAGE_REL_PPC_TOCREL16 = $0008; // 16-bit offset from TOC base
  {$EXTERNALSYM IMAGE_REL_PPC_TOCREL16}
  IMAGE_REL_PPC_TOCREL14 = $0009; // 16-bit offset from TOC base, shifted left 2 (load doubleword)
  {$EXTERNALSYM IMAGE_REL_PPC_TOCREL14}

  IMAGE_REL_PPC_ADDR32NB = $000A; // 32-bit addr w/o image base
  {$EXTERNALSYM IMAGE_REL_PPC_ADDR32NB}
  IMAGE_REL_PPC_SECREL   = $000B; // va of containing section (as in an image sectionhdr)
  {$EXTERNALSYM IMAGE_REL_PPC_SECREL}
  IMAGE_REL_PPC_SECTION  = $000C; // sectionheader number
  {$EXTERNALSYM IMAGE_REL_PPC_SECTION}
  IMAGE_REL_PPC_IFGLUE   = $000D; // substitute TOC restore instruction iff symbol is glue code
  {$EXTERNALSYM IMAGE_REL_PPC_IFGLUE}
  IMAGE_REL_PPC_IMGLUE   = $000E; // symbol is glue code; virtual address is TOC restore instruction
  {$EXTERNALSYM IMAGE_REL_PPC_IMGLUE}
  IMAGE_REL_PPC_SECREL16 = $000F; // va of containing section (limited to 16 bits)
  {$EXTERNALSYM IMAGE_REL_PPC_SECREL16}
  IMAGE_REL_PPC_REFHI    = $0010;
  {$EXTERNALSYM IMAGE_REL_PPC_REFHI}
  IMAGE_REL_PPC_REFLO    = $0011;
  {$EXTERNALSYM IMAGE_REL_PPC_REFLO}
  IMAGE_REL_PPC_PAIR     = $0012;
  {$EXTERNALSYM IMAGE_REL_PPC_PAIR}
  IMAGE_REL_PPC_SECRELLO = $0013; // Low 16-bit section relative reference (used for >32k TLS)
  {$EXTERNALSYM IMAGE_REL_PPC_SECRELLO}
  IMAGE_REL_PPC_SECRELHI = $0014; // High 16-bit section relative reference (used for >32k TLS)
  {$EXTERNALSYM IMAGE_REL_PPC_SECRELHI}
  IMAGE_REL_PPC_GPREL    = $0015;
  {$EXTERNALSYM IMAGE_REL_PPC_GPREL}
  IMAGE_REL_PPC_TOKEN    = $0016; // clr token
  {$EXTERNALSYM IMAGE_REL_PPC_TOKEN}

  IMAGE_REL_PPC_TYPEMASK = $00FF; // mask to isolate above values in IMAGE_RELOCATION.Type
  {$EXTERNALSYM IMAGE_REL_PPC_TYPEMASK}

// Flag bits in IMAGE_RELOCATION.TYPE

  IMAGE_REL_PPC_NEG      = $0100; // subtract reloc value rather than adding it
  {$EXTERNALSYM IMAGE_REL_PPC_NEG}
  IMAGE_REL_PPC_BRTAKEN  = $0200; // fix branch prediction bit to predict branch taken
  {$EXTERNALSYM IMAGE_REL_PPC_BRTAKEN}
  IMAGE_REL_PPC_BRNTAKEN = $0400; // fix branch prediction bit to predict branch not taken
  {$EXTERNALSYM IMAGE_REL_PPC_BRNTAKEN}
  IMAGE_REL_PPC_TOCDEFN  = $0800; // toc slot defined in file (or, data in toc)
  {$EXTERNALSYM IMAGE_REL_PPC_TOCDEFN}

//
// Hitachi SH3 relocation types.
//

  IMAGE_REL_SH3_ABSOLUTE        = $0000; // No relocation
  {$EXTERNALSYM IMAGE_REL_SH3_ABSOLUTE}
  IMAGE_REL_SH3_DIRECT16        = $0001; // 16 bit direct
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT16}
  IMAGE_REL_SH3_DIRECT32        = $0002; // 32 bit direct
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT32}
  IMAGE_REL_SH3_DIRECT8         = $0003; // 8 bit direct, -128..255
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT8}
  IMAGE_REL_SH3_DIRECT8_WORD    = $0004; // 8 bit direct .W (0 ext.)
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT8_WORD}
  IMAGE_REL_SH3_DIRECT8_LONG    = $0005; // 8 bit direct .L (0 ext.)
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT8_LONG}
  IMAGE_REL_SH3_DIRECT4         = $0006; // 4 bit direct (0 ext.)
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT4}
  IMAGE_REL_SH3_DIRECT4_WORD    = $0007; // 4 bit direct .W (0 ext.)
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT4_WORD}
  IMAGE_REL_SH3_DIRECT4_LONG    = $0008; // 4 bit direct .L (0 ext.)
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT4_LONG}
  IMAGE_REL_SH3_PCREL8_WORD     = $0009; // 8 bit PC relative .W
  {$EXTERNALSYM IMAGE_REL_SH3_PCREL8_WORD}
  IMAGE_REL_SH3_PCREL8_LONG     = $000A; // 8 bit PC relative .L
  {$EXTERNALSYM IMAGE_REL_SH3_PCREL8_LONG}
  IMAGE_REL_SH3_PCREL12_WORD    = $000B; // 12 LSB PC relative .W
  {$EXTERNALSYM IMAGE_REL_SH3_PCREL12_WORD}
  IMAGE_REL_SH3_STARTOF_SECTION = $000C; // Start of EXE section
  {$EXTERNALSYM IMAGE_REL_SH3_STARTOF_SECTION}
  IMAGE_REL_SH3_SIZEOF_SECTION  = $000D; // Size of EXE section
  {$EXTERNALSYM IMAGE_REL_SH3_SIZEOF_SECTION}
  IMAGE_REL_SH3_SECTION         = $000E; // Section table index
  {$EXTERNALSYM IMAGE_REL_SH3_SECTION}
  IMAGE_REL_SH3_SECREL          = $000F; // Offset within section
  {$EXTERNALSYM IMAGE_REL_SH3_SECREL}
  IMAGE_REL_SH3_DIRECT32_NB     = $0010; // 32 bit direct not based
  {$EXTERNALSYM IMAGE_REL_SH3_DIRECT32_NB}
  IMAGE_REL_SH3_GPREL4_LONG     = $0011; // GP-relative addressing
  {$EXTERNALSYM IMAGE_REL_SH3_GPREL4_LONG}
  IMAGE_REL_SH3_TOKEN           = $0012; // clr token
  {$EXTERNALSYM IMAGE_REL_SH3_TOKEN}

  IMAGE_REL_ARM_ABSOLUTE = $0000; // No relocation required
  {$EXTERNALSYM IMAGE_REL_ARM_ABSOLUTE}
  IMAGE_REL_ARM_ADDR32   = $0001; // 32 bit address
  {$EXTERNALSYM IMAGE_REL_ARM_ADDR32}
  IMAGE_REL_ARM_ADDR32NB = $0002; // 32 bit address w/o image base
  {$EXTERNALSYM IMAGE_REL_ARM_ADDR32NB}
  IMAGE_REL_ARM_BRANCH24 = $0003; // 24 bit offset << 2 & sign ext.
  {$EXTERNALSYM IMAGE_REL_ARM_BRANCH24}
  IMAGE_REL_ARM_BRANCH11 = $0004; // Thumb: 2 11 bit offsets
  {$EXTERNALSYM IMAGE_REL_ARM_BRANCH11}
  IMAGE_REL_ARM_TOKEN    = $0005; // clr token
  {$EXTERNALSYM IMAGE_REL_ARM_TOKEN}
  IMAGE_REL_ARM_GPREL12  = $0006; // GP-relative addressing (ARM)
  {$EXTERNALSYM IMAGE_REL_ARM_GPREL12}
  IMAGE_REL_ARM_GPREL7   = $0007; // GP-relative addressing (Thumb)
  {$EXTERNALSYM IMAGE_REL_ARM_GPREL7}
  IMAGE_REL_ARM_BLX24    = $0008;
  {$EXTERNALSYM IMAGE_REL_ARM_BLX24}
  IMAGE_REL_ARM_BLX11    = $0009;
  {$EXTERNALSYM IMAGE_REL_ARM_BLX11}
  IMAGE_REL_ARM_SECTION  = $000E; // Section table index
  {$EXTERNALSYM IMAGE_REL_ARM_SECTION}
  IMAGE_REL_ARM_SECREL   = $000F; // Offset within section
  {$EXTERNALSYM IMAGE_REL_ARM_SECREL}

  IMAGE_REL_AM_ABSOLUTE = $0000;
  {$EXTERNALSYM IMAGE_REL_AM_ABSOLUTE}
  IMAGE_REL_AM_ADDR32   = $0001;
  {$EXTERNALSYM IMAGE_REL_AM_ADDR32}
  IMAGE_REL_AM_ADDR32NB = $0002;
  {$EXTERNALSYM IMAGE_REL_AM_ADDR32NB}
  IMAGE_REL_AM_CALL32   = $0003;
  {$EXTERNALSYM IMAGE_REL_AM_CALL32}
  IMAGE_REL_AM_FUNCINFO = $0004;
  {$EXTERNALSYM IMAGE_REL_AM_FUNCINFO}
  IMAGE_REL_AM_REL32_1  = $0005;
  {$EXTERNALSYM IMAGE_REL_AM_REL32_1}
  IMAGE_REL_AM_REL32_2  = $0006;
  {$EXTERNALSYM IMAGE_REL_AM_REL32_2}
  IMAGE_REL_AM_SECREL   = $0007;
  {$EXTERNALSYM IMAGE_REL_AM_SECREL}
  IMAGE_REL_AM_SECTION  = $0008;
  {$EXTERNALSYM IMAGE_REL_AM_SECTION}
  IMAGE_REL_AM_TOKEN    = $0009;
  {$EXTERNALSYM IMAGE_REL_AM_TOKEN}

//
// X86-64 relocations
//

  IMAGE_REL_AMD64_ABSOLUTE = $0000; // Reference is absolute, no relocation is necessary
  {$EXTERNALSYM IMAGE_REL_AMD64_ABSOLUTE}
  IMAGE_REL_AMD64_ADDR64   = $0001; // 64-bit address (VA).
  {$EXTERNALSYM IMAGE_REL_AMD64_ADDR64}
  IMAGE_REL_AMD64_ADDR32   = $0002; // 32-bit address (VA).
  {$EXTERNALSYM IMAGE_REL_AMD64_ADDR32}
  IMAGE_REL_AMD64_ADDR32NB = $0003; // 32-bit address w/o image base (RVA).
  {$EXTERNALSYM IMAGE_REL_AMD64_ADDR32NB}
  IMAGE_REL_AMD64_REL32    = $0004; // 32-bit relative address from byte following reloc
  {$EXTERNALSYM IMAGE_REL_AMD64_REL32}
  IMAGE_REL_AMD64_REL32_1  = $0005; // 32-bit relative address from byte distance 1 from reloc
  {$EXTERNALSYM IMAGE_REL_AMD64_REL32_1}
  IMAGE_REL_AMD64_REL32_2  = $0006; // 32-bit relative address from byte distance 2 from reloc
  {$EXTERNALSYM IMAGE_REL_AMD64_REL32_2}
  IMAGE_REL_AMD64_REL32_3  = $0007; // 32-bit relative address from byte distance 3 from reloc
  {$EXTERNALSYM IMAGE_REL_AMD64_REL32_3}
  IMAGE_REL_AMD64_REL32_4  = $0008; // 32-bit relative address from byte distance 4 from reloc
  {$EXTERNALSYM IMAGE_REL_AMD64_REL32_4}
  IMAGE_REL_AMD64_REL32_5  = $0009; // 32-bit relative address from byte distance 5 from reloc
  {$EXTERNALSYM IMAGE_REL_AMD64_REL32_5}
  IMAGE_REL_AMD64_SECTION  = $000A; // Section index
  {$EXTERNALSYM IMAGE_REL_AMD64_SECTION}
  IMAGE_REL_AMD64_SECREL   = $000B; // 32 bit offset from base of section containing target
  {$EXTERNALSYM IMAGE_REL_AMD64_SECREL}
  IMAGE_REL_AMD64_SECREL7  = $000C; // 7 bit unsigned offset from base of section containing target
  {$EXTERNALSYM IMAGE_REL_AMD64_SECREL7}
  IMAGE_REL_AMD64_TOKEN    = $000D; // 32 bit metadata token
  {$EXTERNALSYM IMAGE_REL_AMD64_TOKEN}
  IMAGE_REL_AMD64_SREL32   = $000E;  // 32 bit signed span-dependent value emitted into object
  {$EXTERNALSYM IMAGE_REL_AMD64_SREL32}
  IMAGE_REL_AMD64_PAIR     = $000F;
  {$EXTERNALSYM IMAGE_REL_AMD64_PAIR}
  IMAGE_REL_AMD64_SSPAN32  = $0010;  // 32 bit signed span-dependent value applied at link time
  {$EXTERNALSYM IMAGE_REL_AMD64_SSPAN32}

//
// IA64 relocation types.
//

  IMAGE_REL_IA64_ABSOLUTE  = $0000;
  {$EXTERNALSYM IMAGE_REL_IA64_ABSOLUTE}
  IMAGE_REL_IA64_IMM14     = $0001;
  {$EXTERNALSYM IMAGE_REL_IA64_IMM14}
  IMAGE_REL_IA64_IMM22     = $0002;
  {$EXTERNALSYM IMAGE_REL_IA64_IMM22}
  IMAGE_REL_IA64_IMM64     = $0003;
  {$EXTERNALSYM IMAGE_REL_IA64_IMM64}
  IMAGE_REL_IA64_DIR32     = $0004;
  {$EXTERNALSYM IMAGE_REL_IA64_DIR32}
  IMAGE_REL_IA64_DIR64     = $0005;
  {$EXTERNALSYM IMAGE_REL_IA64_DIR64}
  IMAGE_REL_IA64_PCREL21B  = $0006;
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL21B}
  IMAGE_REL_IA64_PCREL21M  = $0007;
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL21M}
  IMAGE_REL_IA64_PCREL21F  = $0008;
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL21F}
  IMAGE_REL_IA64_GPREL22   = $0009;
  {$EXTERNALSYM IMAGE_REL_IA64_GPREL22}
  IMAGE_REL_IA64_LTOFF22   = $000A;
  {$EXTERNALSYM IMAGE_REL_IA64_LTOFF22}
  IMAGE_REL_IA64_SECTION   = $000B;
  {$EXTERNALSYM IMAGE_REL_IA64_SECTION}
  IMAGE_REL_IA64_SECREL22  = $000C;
  {$EXTERNALSYM IMAGE_REL_IA64_SECREL22}
  IMAGE_REL_IA64_SECREL64I = $000D;
  {$EXTERNALSYM IMAGE_REL_IA64_SECREL64I}
  IMAGE_REL_IA64_SECREL32  = $000E;
  {$EXTERNALSYM IMAGE_REL_IA64_SECREL32}

//

  IMAGE_REL_IA64_DIR32NB    = $0010;
  {$EXTERNALSYM IMAGE_REL_IA64_DIR32NB}
  IMAGE_REL_IA64_SREL14     = $0011;
  {$EXTERNALSYM IMAGE_REL_IA64_SREL14}
  IMAGE_REL_IA64_SREL22     = $0012;
  {$EXTERNALSYM IMAGE_REL_IA64_SREL22}
  IMAGE_REL_IA64_SREL32     = $0013;
  {$EXTERNALSYM IMAGE_REL_IA64_SREL32}
  IMAGE_REL_IA64_UREL32     = $0014;
  {$EXTERNALSYM IMAGE_REL_IA64_UREL32}
  IMAGE_REL_IA64_PCREL60X   = $0015; // This is always a BRL and never converted
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL60X}
  IMAGE_REL_IA64_PCREL60B   = $0016; // If possible, convert to MBB bundle with NOP.B in slot 1
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL60B}
  IMAGE_REL_IA64_PCREL60F   = $0017; // If possible, convert to MFB bundle with NOP.F in slot 1
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL60F}
  IMAGE_REL_IA64_PCREL60I   = $0018; // If possible, convert to MIB bundle with NOP.I in slot 1
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL60I}
  IMAGE_REL_IA64_PCREL60M   = $0019; // If possible, convert to MMB bundle with NOP.M in slot 1
  {$EXTERNALSYM IMAGE_REL_IA64_PCREL60M}
  IMAGE_REL_IA64_IMMGPREL64 = $001A;
  {$EXTERNALSYM IMAGE_REL_IA64_IMMGPREL64}
  IMAGE_REL_IA64_TOKEN      = $001B; // clr token
  {$EXTERNALSYM IMAGE_REL_IA64_TOKEN}
  IMAGE_REL_IA64_GPREL32    = $001C;
  {$EXTERNALSYM IMAGE_REL_IA64_GPREL32}
  IMAGE_REL_IA64_ADDEND     = $001F;
  {$EXTERNALSYM IMAGE_REL_IA64_ADDEND}

//
// CEF relocation types.
//

  IMAGE_REL_CEF_ABSOLUTE = $0000; // Reference is absolute, no relocation is necessary
  {$EXTERNALSYM IMAGE_REL_CEF_ABSOLUTE}
  IMAGE_REL_CEF_ADDR32   = $0001; // 32-bit address (VA).
  {$EXTERNALSYM IMAGE_REL_CEF_ADDR32}
  IMAGE_REL_CEF_ADDR64   = $0002; // 64-bit address (VA).
  {$EXTERNALSYM IMAGE_REL_CEF_ADDR64}
  IMAGE_REL_CEF_ADDR32NB = $0003; // 32-bit address w/o image base (RVA).
  {$EXTERNALSYM IMAGE_REL_CEF_ADDR32NB}
  IMAGE_REL_CEF_SECTION  = $0004; // Section index
  {$EXTERNALSYM IMAGE_REL_CEF_SECTION}
  IMAGE_REL_CEF_SECREL   = $0005; // 32 bit offset from base of section containing target
  {$EXTERNALSYM IMAGE_REL_CEF_SECREL}
  IMAGE_REL_CEF_TOKEN    = $0006; // 32 bit metadata token
  {$EXTERNALSYM IMAGE_REL_CEF_TOKEN}

//
// clr relocation types.
//

  IMAGE_REL_CEE_ABSOLUTE = $0000; // Reference is absolute, no relocation is necessary
  {$EXTERNALSYM IMAGE_REL_CEE_ABSOLUTE}
  IMAGE_REL_CEE_ADDR32   = $0001; // 32-bit address (VA).
  {$EXTERNALSYM IMAGE_REL_CEE_ADDR32}
  IMAGE_REL_CEE_ADDR64   = $0002; // 64-bit address (VA).
  {$EXTERNALSYM IMAGE_REL_CEE_ADDR64}
  IMAGE_REL_CEE_ADDR32NB = $0003; // 32-bit address w/o image base (RVA).
  {$EXTERNALSYM IMAGE_REL_CEE_ADDR32NB}
  IMAGE_REL_CEE_SECTION  = $0004; // Section index
  {$EXTERNALSYM IMAGE_REL_CEE_SECTION}
  IMAGE_REL_CEE_SECREL   = $0005; // 32 bit offset from base of section containing target
  {$EXTERNALSYM IMAGE_REL_CEE_SECREL}
  IMAGE_REL_CEE_TOKEN    = $0006; // 32 bit metadata token
  {$EXTERNALSYM IMAGE_REL_CEE_TOKEN}

  IMAGE_REL_M32R_ABSOLUTE = $0000; // No relocation required
  {$EXTERNALSYM IMAGE_REL_M32R_ABSOLUTE}
  IMAGE_REL_M32R_ADDR32   = $0001; // 32 bit address
  {$EXTERNALSYM IMAGE_REL_M32R_ADDR32}
  IMAGE_REL_M32R_ADDR32NB = $0002; // 32 bit address w/o image base
  {$EXTERNALSYM IMAGE_REL_M32R_ADDR32NB}
  IMAGE_REL_M32R_ADDR24   = $0003; // 24 bit address
  {$EXTERNALSYM IMAGE_REL_M32R_ADDR24}
  IMAGE_REL_M32R_GPREL16  = $0004; // GP relative addressing
  {$EXTERNALSYM IMAGE_REL_M32R_GPREL16}
  IMAGE_REL_M32R_PCREL24  = $0005; // 24 bit offset << 2 & sign ext.
  {$EXTERNALSYM IMAGE_REL_M32R_PCREL24}
  IMAGE_REL_M32R_PCREL16  = $0006; // 16 bit offset << 2 & sign ext.
  {$EXTERNALSYM IMAGE_REL_M32R_PCREL16}
  IMAGE_REL_M32R_PCREL8   = $0007; // 8 bit offset << 2 & sign ext.
  {$EXTERNALSYM IMAGE_REL_M32R_PCREL8}
  IMAGE_REL_M32R_REFHALF  = $0008; // 16 MSBs
  {$EXTERNALSYM IMAGE_REL_M32R_REFHALF}
  IMAGE_REL_M32R_REFHI    = $0009; // 16 MSBs; adj for LSB sign ext.
  {$EXTERNALSYM IMAGE_REL_M32R_REFHI}
  IMAGE_REL_M32R_REFLO    = $000A; // 16 LSBs
  {$EXTERNALSYM IMAGE_REL_M32R_REFLO}
  IMAGE_REL_M32R_PAIR     = $000B; // Link HI and LO
  {$EXTERNALSYM IMAGE_REL_M32R_PAIR}
  IMAGE_REL_M32R_SECTION  = $000C; // Section table index
  {$EXTERNALSYM IMAGE_REL_M32R_SECTION}
  IMAGE_REL_M32R_SECREL32 = $000D; // 32 bit section relative reference
  {$EXTERNALSYM IMAGE_REL_M32R_SECREL32}
  IMAGE_REL_M32R_TOKEN    = $000E; // clr token
  {$EXTERNALSYM IMAGE_REL_M32R_TOKEN}

// Please contact INTEL to get IA64-specific information

(* TODO
#define EXT_IMM64(Value, Address, Size, InstPos, ValPos)
    Value |= (((ULONGLONG)((*(Address) >> InstPos) & (((ULONGLONG)1 << Size) - 1))) << ValPos)  // Intel-IA64-Filler

#define INS_IMM64(Value, Address, Size, InstPos, ValPos)  /* Intel-IA64-Filler */\
    *(PDWORD)Address = (*(PDWORD)Address & ~(((1 << Size) - 1) << InstPos)) | /* Intel-IA64-Filler */\
          ((DWORD)((((ULONGLONG)Value >> ValPos) & (((ULONGLONG)1 << Size) - 1))) << InstPos)  // Intel-IA64-Filler
*)

const
  EMARCH_ENC_I17_IMM7B_INST_WORD_X     = 3; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM7B_INST_WORD_X}
  EMARCH_ENC_I17_IMM7B_SIZE_X          = 7; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM7B_SIZE_X}
  EMARCH_ENC_I17_IMM7B_INST_WORD_POS_X = 4; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM7B_INST_WORD_POS_X}
  EMARCH_ENC_I17_IMM7B_VAL_POS_X       = 0; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM7B_VAL_POS_X}

  EMARCH_ENC_I17_IMM9D_INST_WORD_X     = 3; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM9D_INST_WORD_X}
  EMARCH_ENC_I17_IMM9D_SIZE_X          = 9; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM9D_SIZE_X}
  EMARCH_ENC_I17_IMM9D_INST_WORD_POS_X = 18; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM9D_INST_WORD_POS_X}
  EMARCH_ENC_I17_IMM9D_VAL_POS_X       = 7; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM9D_VAL_POS_X}

  EMARCH_ENC_I17_IMM5C_INST_WORD_X     = 3; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM5C_INST_WORD_X}
  EMARCH_ENC_I17_IMM5C_SIZE_X          = 5; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM5C_SIZE_X}
  EMARCH_ENC_I17_IMM5C_INST_WORD_POS_X = 13; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM5C_INST_WORD_POS_X}
  EMARCH_ENC_I17_IMM5C_VAL_POS_X       = 16; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM5C_VAL_POS_X}

  EMARCH_ENC_I17_IC_INST_WORD_X     = 3; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IC_INST_WORD_X}
  EMARCH_ENC_I17_IC_SIZE_X          = 1; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IC_SIZE_X}
  EMARCH_ENC_I17_IC_INST_WORD_POS_X = 12; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IC_INST_WORD_POS_X}
  EMARCH_ENC_I17_IC_VAL_POS_X       = 21; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IC_VAL_POS_X}

  EMARCH_ENC_I17_IMM41a_INST_WORD_X     = 1; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41a_INST_WORD_X}
  EMARCH_ENC_I17_IMM41a_SIZE_X          = 10; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41a_SIZE_X}
  EMARCH_ENC_I17_IMM41a_INST_WORD_POS_X = 14; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41a_INST_WORD_POS_X}
  EMARCH_ENC_I17_IMM41a_VAL_POS_X       = 22; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41a_VAL_POS_X}

  EMARCH_ENC_I17_IMM41b_INST_WORD_X     = 1; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41b_INST_WORD_X}
  EMARCH_ENC_I17_IMM41b_SIZE_X          = 8; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41b_SIZE_X}
  EMARCH_ENC_I17_IMM41b_INST_WORD_POS_X = 24; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41b_INST_WORD_POS_X}
  EMARCH_ENC_I17_IMM41b_VAL_POS_X       = 32; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41b_VAL_POS_X}

  EMARCH_ENC_I17_IMM41c_INST_WORD_X     = 2; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41c_INST_WORD_X}
  EMARCH_ENC_I17_IMM41c_SIZE_X          = 23; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41c_SIZE_X}
  EMARCH_ENC_I17_IMM41c_INST_WORD_POS_X = 0; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41c_INST_WORD_POS_X}
  EMARCH_ENC_I17_IMM41c_VAL_POS_X       = 40; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_IMM41c_VAL_POS_X}

  EMARCH_ENC_I17_SIGN_INST_WORD_X     = 3; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_SIGN_INST_WORD_X}
  EMARCH_ENC_I17_SIGN_SIZE_X          = 1; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_SIGN_SIZE_X}
  EMARCH_ENC_I17_SIGN_INST_WORD_POS_X = 27; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_SIGN_INST_WORD_POS_X}
  EMARCH_ENC_I17_SIGN_VAL_POS_X       = 63; // Intel-IA64-Filler
  {$EXTERNALSYM EMARCH_ENC_I17_SIGN_VAL_POS_X}

//
// Line number format.
//

type
  TImgLineNoType = record
    case Integer of
      0: (SymbolTableIndex: DWORD);               // Symbol table index of function name if Linenumber is 0.
      1: (VirtualAddress: DWORD);                 // Virtual address of line number.
  end;

  PIMAGE_LINENUMBER = ^IMAGE_LINENUMBER;
  {$EXTERNALSYM PIMAGE_LINENUMBER}
  _IMAGE_LINENUMBER = record
    Type_: TImgLineNoType;
    Linenumber: WORD;                         // Line number.
  end;
  {$EXTERNALSYM _IMAGE_LINENUMBER}
  IMAGE_LINENUMBER = _IMAGE_LINENUMBER;
  {$EXTERNALSYM IMAGE_LINENUMBER}
  TImageLineNumber = IMAGE_LINENUMBER;
  PImageLineNumber = PIMAGE_LINENUMBER;

const
  IMAGE_SIZEOF_LINENUMBER = 6;
  {$EXTERNALSYM IMAGE_SIZEOF_LINENUMBER}

// #include "poppack.h"                        // Back to 4 byte packing

//
// Based relocation format.
//

type
  PIMAGE_BASE_RELOCATION = ^IMAGE_BASE_RELOCATION;
  {$EXTERNALSYM PIMAGE_BASE_RELOCATION}
  _IMAGE_BASE_RELOCATION = record
    VirtualAddress: DWORD;
    SizeOfBlock: DWORD;
    //  WORD    TypeOffset[1];
  end;
  {$EXTERNALSYM _IMAGE_BASE_RELOCATION}
  IMAGE_BASE_RELOCATION = _IMAGE_BASE_RELOCATION;
  {$EXTERNALSYM IMAGE_BASE_RELOCATION}
  TImageBaseRelocation = IMAGE_BASE_RELOCATION;
  PImageBaseRelocation = PIMAGE_BASE_RELOCATION;

const
  IMAGE_SIZEOF_BASE_RELOCATION = 8;
  {$EXTERNALSYM IMAGE_SIZEOF_BASE_RELOCATION}

//
// Based relocation types.
//

  IMAGE_REL_BASED_ABSOLUTE     = 0;
  {$EXTERNALSYM IMAGE_REL_BASED_ABSOLUTE}
  IMAGE_REL_BASED_HIGH         = 1;
  {$EXTERNALSYM IMAGE_REL_BASED_HIGH}
  IMAGE_REL_BASED_LOW          = 2;
  {$EXTERNALSYM IMAGE_REL_BASED_LOW}
  IMAGE_REL_BASED_HIGHLOW      = 3;
  {$EXTERNALSYM IMAGE_REL_BASED_HIGHLOW}
  IMAGE_REL_BASED_HIGHADJ      = 4;
  {$EXTERNALSYM IMAGE_REL_BASED_HIGHADJ}
  IMAGE_REL_BASED_MIPS_JMPADDR = 5;
  {$EXTERNALSYM IMAGE_REL_BASED_MIPS_JMPADDR}

  IMAGE_REL_BASED_MIPS_JMPADDR16 = 9;
  {$EXTERNALSYM IMAGE_REL_BASED_MIPS_JMPADDR16}
  IMAGE_REL_BASED_IA64_IMM64     = 9;
  {$EXTERNALSYM IMAGE_REL_BASED_IA64_IMM64}
  IMAGE_REL_BASED_DIR64          = 10;
  {$EXTERNALSYM IMAGE_REL_BASED_DIR64}

//
// Archive format.
//

  IMAGE_ARCHIVE_START_SIZE       = 8;
  {$EXTERNALSYM IMAGE_ARCHIVE_START_SIZE}
  IMAGE_ARCHIVE_START            = '!<arch>'#10;
  {$EXTERNALSYM IMAGE_ARCHIVE_START}
  IMAGE_ARCHIVE_END              = '`'#10;
  {$EXTERNALSYM IMAGE_ARCHIVE_END}
  IMAGE_ARCHIVE_PAD              = #10;
  {$EXTERNALSYM IMAGE_ARCHIVE_PAD}
  IMAGE_ARCHIVE_LINKER_MEMBER    = '/               ';
  {$EXTERNALSYM IMAGE_ARCHIVE_LINKER_MEMBER}
  IMAGE_ARCHIVE_LONGNAMES_MEMBER = '//              ';
  {$EXTERNALSYM IMAGE_ARCHIVE_LONGNAMES_MEMBER}

type
  PIMAGE_ARCHIVE_MEMBER_HEADER = ^IMAGE_ARCHIVE_MEMBER_HEADER;
  {$EXTERNALSYM PIMAGE_ARCHIVE_MEMBER_HEADER}
  _IMAGE_ARCHIVE_MEMBER_HEADER = record
    Name: array [0..15] of Byte; // File member name - `/' terminated.
    Date: array [0..11] of Byte; // File member date - decimal.
    UserID: array [0..5] of Byte; // File member user id - decimal.
    GroupID: array [0..5] of Byte; // File member group id - decimal.
    Mode: array [0..7] of Byte; // File member mode - octal.
    Size: array [0..9] of Byte; // File member size - decimal.
    EndHeader: array [0..1] of Byte; // String to end header.
  end;
  {$EXTERNALSYM _IMAGE_ARCHIVE_MEMBER_HEADER}
  IMAGE_ARCHIVE_MEMBER_HEADER = _IMAGE_ARCHIVE_MEMBER_HEADER;
  {$EXTERNALSYM IMAGE_ARCHIVE_MEMBER_HEADER}
  TImageArchiveMemberHeader = IMAGE_ARCHIVE_MEMBER_HEADER;
  PImageArchiveMemberHeader = PIMAGE_ARCHIVE_MEMBER_HEADER;

const
  IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR = 60;
  {$EXTERNALSYM IMAGE_SIZEOF_ARCHIVE_MEMBER_HDR}

//
// DLL support.
//

//
// Export Format
//

type
  PIMAGE_EXPORT_DIRECTORY = ^IMAGE_EXPORT_DIRECTORY;
  {$EXTERNALSYM PIMAGE_EXPORT_DIRECTORY}
  _IMAGE_EXPORT_DIRECTORY = record
    Characteristics: DWORD;
    TimeDateStamp: DWORD;
    MajorVersion: Word;
    MinorVersion: Word;
    Name: DWORD;
    Base: DWORD;
    NumberOfFunctions: DWORD;
    NumberOfNames: DWORD;
    AddressOfFunctions: DWORD; // RVA from base of image
    AddressOfNames: DWORD; // RVA from base of image
    AddressOfNameOrdinals: DWORD; // RVA from base of image
  end;
  {$EXTERNALSYM _IMAGE_EXPORT_DIRECTORY}
  IMAGE_EXPORT_DIRECTORY = _IMAGE_EXPORT_DIRECTORY;
  {$EXTERNALSYM IMAGE_EXPORT_DIRECTORY}
  TImageExportDirectory = IMAGE_EXPORT_DIRECTORY;
  PImageExportDirectory = PIMAGE_EXPORT_DIRECTORY;

//
// Import Format
//

  PIMAGE_IMPORT_BY_NAME = ^IMAGE_IMPORT_BY_NAME;
  {$EXTERNALSYM PIMAGE_IMPORT_BY_NAME}
  _IMAGE_IMPORT_BY_NAME = record
    Hint: Word;
    Name: array [0..0] of Byte;
  end;
  {$EXTERNALSYM _IMAGE_IMPORT_BY_NAME}
  IMAGE_IMPORT_BY_NAME = _IMAGE_IMPORT_BY_NAME;
  {$EXTERNALSYM IMAGE_IMPORT_BY_NAME}
  TImageImportByName = IMAGE_IMPORT_BY_NAME;
  PImageImportByName = PIMAGE_IMPORT_BY_NAME;

// #include "pshpack8.h"                       // Use align 8 for the 64-bit IAT.

  PIMAGE_THUNK_DATA64 = ^IMAGE_THUNK_DATA64;
  {$EXTERNALSYM PIMAGE_THUNK_DATA64}
  _IMAGE_THUNK_DATA64 = record
    case Integer of
      0: (ForwarderString: ULONGLONG);   // PBYTE
      1: (Function_: ULONGLONG);         // PDWORD
      2: (Ordinal: ULONGLONG);
      3: (AddressOfData: ULONGLONG);     // PIMAGE_IMPORT_BY_NAME
  end;
  {$EXTERNALSYM _IMAGE_THUNK_DATA64}
  IMAGE_THUNK_DATA64 = _IMAGE_THUNK_DATA64;
  {$EXTERNALSYM IMAGE_THUNK_DATA64}
  TImageThunkData64 = IMAGE_THUNK_DATA64;
  PImageThunkData64 = PIMAGE_THUNK_DATA64;

// #include "poppack.h"                        // Back to 4 byte packing

  PIMAGE_THUNK_DATA32 = ^IMAGE_THUNK_DATA32;
  {$EXTERNALSYM PIMAGE_THUNK_DATA32}
  _IMAGE_THUNK_DATA32 = record
    case Integer of
      0: (ForwarderString: DWORD);   // PBYTE
      1: (Function_: DWORD);         // PDWORD
      2: (Ordinal: DWORD);
      3: (AddressOfData: DWORD);     // PIMAGE_IMPORT_BY_NAME
  end;
  {$EXTERNALSYM _IMAGE_THUNK_DATA32}
  IMAGE_THUNK_DATA32 = _IMAGE_THUNK_DATA32;
  {$EXTERNALSYM IMAGE_THUNK_DATA32}
  TImageThunkData32 = IMAGE_THUNK_DATA32;
  PImageThunkData32 = PIMAGE_THUNK_DATA32;

const
  IMAGE_ORDINAL_FLAG64 = ULONGLONG($8000000000000000);
  {$EXTERNALSYM IMAGE_ORDINAL_FLAG64}
  IMAGE_ORDINAL_FLAG32 = DWORD($80000000);
  {$EXTERNALSYM IMAGE_ORDINAL_FLAG32}

function IMAGE_ORDINAL64(Ordinal: ULONGLONG): ULONGLONG;
{$EXTERNALSYM IMAGE_ORDINAL64}
function IMAGE_ORDINAL32(Ordinal: DWORD): DWORD;
{$EXTERNALSYM IMAGE_ORDINAL32}
function IMAGE_SNAP_BY_ORDINAL64(Ordinal: ULONGLONG): Boolean;
{$EXTERNALSYM IMAGE_SNAP_BY_ORDINAL64}
function IMAGE_SNAP_BY_ORDINAL32(Ordinal: DWORD): Boolean;
{$EXTERNALSYM IMAGE_SNAP_BY_ORDINAL32}

//
// Thread Local Storage
//

type
  PIMAGE_TLS_CALLBACK = procedure (DllHandle: Pointer; Reason: DWORD; Reserved: Pointer); stdcall;
  {$EXTERNALSYM PIMAGE_TLS_CALLBACK}
  TImageTlsCallback = PIMAGE_TLS_CALLBACK;

  PIMAGE_TLS_DIRECTORY64 = ^IMAGE_TLS_DIRECTORY64;
  {$EXTERNALSYM PIMAGE_TLS_DIRECTORY64}
  _IMAGE_TLS_DIRECTORY64 = record
    StartAddressOfRawData: ULONGLONG;
    EndAddressOfRawData: ULONGLONG;
    AddressOfIndex: ULONGLONG;         // PDWORD
    AddressOfCallBacks: ULONGLONG;     // PIMAGE_TLS_CALLBACK *;
    SizeOfZeroFill: DWORD;
    Characteristics: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_TLS_DIRECTORY64}
  IMAGE_TLS_DIRECTORY64 = _IMAGE_TLS_DIRECTORY64;
  {$EXTERNALSYM IMAGE_TLS_DIRECTORY64}
  TImageTlsDirectory64 = IMAGE_TLS_DIRECTORY64;
  PImageTlsDirectory64 = PIMAGE_TLS_DIRECTORY64;

  PIMAGE_TLS_DIRECTORY32 = ^IMAGE_TLS_DIRECTORY32;
  {$EXTERNALSYM PIMAGE_TLS_DIRECTORY32}
  _IMAGE_TLS_DIRECTORY32 = record
    StartAddressOfRawData: DWORD;
    EndAddressOfRawData: DWORD;
    AddressOfIndex: DWORD;             // PDWORD
    AddressOfCallBacks: DWORD;         // PIMAGE_TLS_CALLBACK *
    SizeOfZeroFill: DWORD;
    Characteristics: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_TLS_DIRECTORY32}
  IMAGE_TLS_DIRECTORY32 = _IMAGE_TLS_DIRECTORY32;
  {$EXTERNALSYM IMAGE_TLS_DIRECTORY32}
  TImageTlsDirectory32 = IMAGE_TLS_DIRECTORY32;
  PImageTlsDirectory32 = PIMAGE_TLS_DIRECTORY32;

const
  IMAGE_ORDINAL_FLAG = IMAGE_ORDINAL_FLAG32;
  {$EXTERNALSYM IMAGE_ORDINAL_FLAG}

function IMAGE_ORDINAL(Ordinal: DWORD): DWORD;

type
  IMAGE_THUNK_DATA = IMAGE_THUNK_DATA32;
  {$EXTERNALSYM IMAGE_THUNK_DATA}
  PIMAGE_THUNK_DATA = PIMAGE_THUNK_DATA32;
  {$EXTERNALSYM PIMAGE_THUNK_DATA}
  TImageThunkData = TImageThunkData32;
  PImageThunkData = PImageThunkData32;

function IMAGE_SNAP_BY_ORDINAL(Ordinal: DWORD): Boolean;
{$EXTERNALSYM IMAGE_SNAP_BY_ORDINAL}

type
  IMAGE_TLS_DIRECTORY = IMAGE_TLS_DIRECTORY32;
  {$EXTERNALSYM IMAGE_TLS_DIRECTORY}
  PIMAGE_TLS_DIRECTORY = PIMAGE_TLS_DIRECTORY32;
  {$EXTERNALSYM PIMAGE_TLS_DIRECTORY}
  TImageTlsDirectory = TImageTlsDirectory32;
  PImageTlsDirectory = PImageTlsDirectory32;

  TIIDUnion = record
    case Integer of
      0: (Characteristics: DWORD);         // 0 for terminating null import descriptor
      1: (OriginalFirstThunk: DWORD);      // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
  end;

  PIMAGE_IMPORT_DESCRIPTOR = ^IMAGE_IMPORT_DESCRIPTOR;
  {$EXTERNALSYM PIMAGE_IMPORT_DESCRIPTOR}
  _IMAGE_IMPORT_DESCRIPTOR = record
    Union: TIIDUnion;
    TimeDateStamp: DWORD;                  // 0 if not bound,
                                           // -1 if bound, and real date\time stamp
                                           //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
                                           // O.W. date/time stamp of DLL bound to (Old BIND)

    ForwarderChain: DWORD;                 // -1 if no forwarders
    Name: DWORD;
    FirstThunk: DWORD;                     // RVA to IAT (if bound this IAT has actual addresses)
  end;
  {$EXTERNALSYM _IMAGE_IMPORT_DESCRIPTOR}
  IMAGE_IMPORT_DESCRIPTOR = _IMAGE_IMPORT_DESCRIPTOR;
  {$EXTERNALSYM IMAGE_IMPORT_DESCRIPTOR}
  TImageImportDecriptor = IMAGE_IMPORT_DESCRIPTOR;
  PImageImportDecriptor = PIMAGE_IMPORT_DESCRIPTOR;

//
// New format import descriptors pointed to by DataDirectory[ IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT ]
//

type
  PIMAGE_BOUND_IMPORT_DESCRIPTOR = ^IMAGE_BOUND_IMPORT_DESCRIPTOR;
  {$EXTERNALSYM PIMAGE_BOUND_IMPORT_DESCRIPTOR}
  _IMAGE_BOUND_IMPORT_DESCRIPTOR = record
    TimeDateStamp: DWORD;
    OffsetModuleName: Word;
    NumberOfModuleForwarderRefs: Word;
    // Array of zero or more IMAGE_BOUND_FORWARDER_REF follows
  end;
  {$EXTERNALSYM _IMAGE_BOUND_IMPORT_DESCRIPTOR}
  IMAGE_BOUND_IMPORT_DESCRIPTOR = _IMAGE_BOUND_IMPORT_DESCRIPTOR;
  {$EXTERNALSYM IMAGE_BOUND_IMPORT_DESCRIPTOR}
  TImageBoundImportDescriptor = IMAGE_BOUND_IMPORT_DESCRIPTOR;
  PImageBoundImportDescriptor = PIMAGE_BOUND_IMPORT_DESCRIPTOR;

  PIMAGE_BOUND_FORWARDER_REF = ^IMAGE_BOUND_FORWARDER_REF;
  {$EXTERNALSYM PIMAGE_BOUND_FORWARDER_REF}
  _IMAGE_BOUND_FORWARDER_REF = record
    TimeDateStamp: DWORD;
    OffsetModuleName: Word;
    Reserved: Word;
  end;
  {$EXTERNALSYM _IMAGE_BOUND_FORWARDER_REF}
  IMAGE_BOUND_FORWARDER_REF = _IMAGE_BOUND_FORWARDER_REF;
  {$EXTERNALSYM IMAGE_BOUND_FORWARDER_REF}
  TImageBoundForwarderRef = IMAGE_BOUND_FORWARDER_REF;
  PImageBoundForwarderRef = PIMAGE_BOUND_FORWARDER_REF;

//
// Resource Format.
//

//
// Resource directory consists of two counts, following by a variable length
// array of directory entries.  The first count is the number of entries at
// beginning of the array that have actual names associated with each entry.
// The entries are in ascending order, case insensitive strings.  The second
// count is the number of entries that immediately follow the named entries.
// This second count identifies the number of entries that have 16-bit integer
// Ids as their name.  These entries are also sorted in ascending order.
//
// This structure allows fast lookup by either name or number, but for any
// given resource entry only one form of lookup is supported, not both.
// This is consistant with the syntax of the .RC file and the .RES file.
//

  PIMAGE_RESOURCE_DIRECTORY = ^IMAGE_RESOURCE_DIRECTORY;
  {$EXTERNALSYM PIMAGE_RESOURCE_DIRECTORY}
  _IMAGE_RESOURCE_DIRECTORY = record
    Characteristics: DWORD;
    TimeDateStamp: DWORD;
    MajorVersion: Word;
    MinorVersion: Word;
    NumberOfNamedEntries: Word;
    NumberOfIdEntries: Word;
    // IMAGE_RESOURCE_DIRECTORY_ENTRY DirectoryEntries[];
  end;
  {$EXTERNALSYM _IMAGE_RESOURCE_DIRECTORY}
  IMAGE_RESOURCE_DIRECTORY = _IMAGE_RESOURCE_DIRECTORY;
  {$EXTERNALSYM IMAGE_RESOURCE_DIRECTORY}
  TImageResourceDirectory = IMAGE_RESOURCE_DIRECTORY;
  PImageResourceDirectory = PIMAGE_RESOURCE_DIRECTORY;

const
  IMAGE_RESOURCE_NAME_IS_STRING    = DWORD($80000000);
  {$EXTERNALSYM IMAGE_RESOURCE_NAME_IS_STRING}
  IMAGE_RESOURCE_DATA_IS_DIRECTORY = DWORD($80000000);
  {$EXTERNALSYM IMAGE_RESOURCE_DATA_IS_DIRECTORY}

//
// Each directory contains the 32-bit Name of the entry and an offset,
// relative to the beginning of the resource directory of the data associated
// with this directory entry.  If the name of the entry is an actual text
// string instead of an integer Id, then the high order bit of the name field
// is set to one and the low order 31-bits are an offset, relative to the
// beginning of the resource directory of the string, which is of type
// IMAGE_RESOURCE_DIRECTORY_STRING.  Otherwise the high bit is clear and the
// low-order 16-bits are the integer Id that identify this resource directory
// entry. If the directory entry is yet another resource directory (i.e. a
// subdirectory), then the high order bit of the offset field will be
// set to indicate this.  Otherwise the high bit is clear and the offset
// field points to a resource data entry.
//

type
  TIRDEName = record
    case Integer of
      0: (
        NameOffset: DWORD); // 0..30: NameOffset; 31: NameIsString
      1: (
        Name: DWORD);
      2: (
        Id: WORD);
  end;

  TIRDEDirectory = record
    case Integer of
      0: (
        OffsetToData: DWORD);
      1: (
        OffsetToDirectory: DWORD); // 0..30: OffsetToDirectory; 31: DataIsDirectory
  end;

  PIMAGE_RESOURCE_DIRECTORY_ENTRY = ^IMAGE_RESOURCE_DIRECTORY_ENTRY;
  {$EXTERNALSYM PIMAGE_RESOURCE_DIRECTORY_ENTRY}
  _IMAGE_RESOURCE_DIRECTORY_ENTRY = record
    Name: TIRDEName;
    Directory: TIRDEDirectory;
  end;
  {$EXTERNALSYM _IMAGE_RESOURCE_DIRECTORY_ENTRY}
  IMAGE_RESOURCE_DIRECTORY_ENTRY = _IMAGE_RESOURCE_DIRECTORY_ENTRY;
  {$EXTERNALSYM IMAGE_RESOURCE_DIRECTORY_ENTRY}
  TImageResourceDirectoryEntry = IMAGE_RESOURCE_DIRECTORY_ENTRY;
  PImageResourceDirectoryEntry = PIMAGE_RESOURCE_DIRECTORY_ENTRY;

//
// For resource directory entries that have actual string names, the Name
// field of the directory entry points to an object of the following type.
// All of these string objects are stored together after the last resource
// directory entry and before the first resource data object.  This minimizes
// the impact of these variable length objects on the alignment of the fixed
// size directory entry objects.
//

type
  PIMAGE_RESOURCE_DIRECTORY_STRING = ^IMAGE_RESOURCE_DIRECTORY_STRING;
  {$EXTERNALSYM PIMAGE_RESOURCE_DIRECTORY_STRING}
  _IMAGE_RESOURCE_DIRECTORY_STRING = record
    Length: Word;
    NameString: array [0..0] of CHAR;
  end;
  {$EXTERNALSYM _IMAGE_RESOURCE_DIRECTORY_STRING}
  IMAGE_RESOURCE_DIRECTORY_STRING = _IMAGE_RESOURCE_DIRECTORY_STRING;
  {$EXTERNALSYM IMAGE_RESOURCE_DIRECTORY_STRING}
  TImageResourceDirectoryString = IMAGE_RESOURCE_DIRECTORY_STRING;
  PImageResourceDirectoryString = PIMAGE_RESOURCE_DIRECTORY_STRING;

  PIMAGE_RESOURCE_DIR_STRING_U = ^IMAGE_RESOURCE_DIR_STRING_U;
  {$EXTERNALSYM PIMAGE_RESOURCE_DIR_STRING_U}
  _IMAGE_RESOURCE_DIR_STRING_U = record
    Length: Word;
    NameString: array [0..0] of WCHAR;
  end;
  {$EXTERNALSYM _IMAGE_RESOURCE_DIR_STRING_U}
  IMAGE_RESOURCE_DIR_STRING_U = _IMAGE_RESOURCE_DIR_STRING_U;
  {$EXTERNALSYM IMAGE_RESOURCE_DIR_STRING_U}
  TImageResourceDirStringU = IMAGE_RESOURCE_DIR_STRING_U;
  PImageResourceDirStringU = PIMAGE_RESOURCE_DIR_STRING_U;

//
// Each resource data entry describes a leaf node in the resource directory
// tree.  It contains an offset, relative to the beginning of the resource
// directory of the data for the resource, a size field that gives the number
// of bytes of data at that offset, a CodePage that should be used when
// decoding code point values within the resource data.  Typically for new
// applications the code page would be the unicode code page.
//

  PIMAGE_RESOURCE_DATA_ENTRY = ^IMAGE_RESOURCE_DATA_ENTRY;
  {$EXTERNALSYM PIMAGE_RESOURCE_DATA_ENTRY}
  _IMAGE_RESOURCE_DATA_ENTRY = record
    OffsetToData: DWORD;
    Size: DWORD;
    CodePage: DWORD;
    Reserved: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_RESOURCE_DATA_ENTRY}
  IMAGE_RESOURCE_DATA_ENTRY = _IMAGE_RESOURCE_DATA_ENTRY;
  {$EXTERNALSYM IMAGE_RESOURCE_DATA_ENTRY}
  TImageResourceDataEntry = IMAGE_RESOURCE_DATA_ENTRY;
  PImageResourceDataEntry = PIMAGE_RESOURCE_DATA_ENTRY;

//
// Load Configuration Directory Entry
//

type
  PIMAGE_LOAD_CONFIG_DIRECTORY32 = ^IMAGE_LOAD_CONFIG_DIRECTORY32;
  {$EXTERNALSYM PIMAGE_LOAD_CONFIG_DIRECTORY32}
  IMAGE_LOAD_CONFIG_DIRECTORY32 = record
    Size: DWORD;
    TimeDateStamp: DWORD;
    MajorVersion: WORD;
    MinorVersion: WORD;
    GlobalFlagsClear: DWORD;
    GlobalFlagsSet: DWORD;
    CriticalSectionDefaultTimeout: DWORD;
    DeCommitFreeBlockThreshold: DWORD;
    DeCommitTotalFreeThreshold: DWORD;
    LockPrefixTable: DWORD;            // VA
    MaximumAllocationSize: DWORD;
    VirtualMemoryThreshold: DWORD;
    ProcessHeapFlags: DWORD;
    ProcessAffinityMask: DWORD;
    CSDVersion: WORD;
    Reserved1: WORD;
    EditList: DWORD;                   // VA
    SecurityCookie: DWORD;             // VA
    SEHandlerTable: DWORD;             // VA
    SEHandlerCount: DWORD;
  end;
  {$EXTERNALSYM IMAGE_LOAD_CONFIG_DIRECTORY32}
  TImageLoadConfigDirectory32 = IMAGE_LOAD_CONFIG_DIRECTORY32;
  PImageLoadConfigDirectory32 = PIMAGE_LOAD_CONFIG_DIRECTORY32;

  PIMAGE_LOAD_CONFIG_DIRECTORY64 = ^IMAGE_LOAD_CONFIG_DIRECTORY64;
  {$EXTERNALSYM PIMAGE_LOAD_CONFIG_DIRECTORY64}
  IMAGE_LOAD_CONFIG_DIRECTORY64 = record
    Size: DWORD;
    TimeDateStamp: DWORD;
    MajorVersion: WORD;
    MinorVersion: WORD;
    GlobalFlagsClear: DWORD;
    GlobalFlagsSet: DWORD;
    CriticalSectionDefaultTimeout: DWORD;
    DeCommitFreeBlockThreshold: ULONGLONG;
    DeCommitTotalFreeThreshold: ULONGLONG;
    LockPrefixTable: ULONGLONG;         // VA
    MaximumAllocationSize: ULONGLONG;
    VirtualMemoryThreshold: ULONGLONG;
    ProcessAffinityMask: ULONGLONG;
    ProcessHeapFlags: DWORD;
    CSDVersion: WORD;
    Reserved1: WORD;
    EditList: ULONGLONG;                // VA
    SecurityCookie: ULONGLONG;             // VA
    SEHandlerTable: ULONGLONG;             // VA
    SEHandlerCount: ULONGLONG;
  end;
  {$EXTERNALSYM IMAGE_LOAD_CONFIG_DIRECTORY64}
  TImageLoadConfigDirectory64 = IMAGE_LOAD_CONFIG_DIRECTORY64;
  PImageLoadConfigDirectory64 = PIMAGE_LOAD_CONFIG_DIRECTORY64;

  IMAGE_LOAD_CONFIG_DIRECTORY = IMAGE_LOAD_CONFIG_DIRECTORY32;
  {$EXTERNALSYM IMAGE_LOAD_CONFIG_DIRECTORY}
  PIMAGE_LOAD_CONFIG_DIRECTORY = PIMAGE_LOAD_CONFIG_DIRECTORY32;
  {$EXTERNALSYM PIMAGE_LOAD_CONFIG_DIRECTORY}
  TImageLoadConfigDirectory = TImageLoadConfigDirectory32;
  PImageLoadConfigDirectory = PImageLoadConfigDirectory32;

//
// WIN CE Exception table format
//

//
// Function table entry format.  Function table is pointed to by the
// IMAGE_DIRECTORY_ENTRY_EXCEPTION directory entry.
//

type
  PIMAGE_CE_RUNTIME_FUNCTION_ENTRY = ^IMAGE_CE_RUNTIME_FUNCTION_ENTRY;
  {$EXTERNALSYM PIMAGE_CE_RUNTIME_FUNCTION_ENTRY}
  _IMAGE_CE_RUNTIME_FUNCTION_ENTRY = record
    FuncStart: DWORD;
    Flags: DWORD;
    //DWORD PrologLen : 8;
    //DWORD FuncLen : 22;
    //DWORD ThirtyTwoBit : 1;
    //DWORD ExceptionFlag : 1;
  end;
  {$EXTERNALSYM _IMAGE_CE_RUNTIME_FUNCTION_ENTRY}
  IMAGE_CE_RUNTIME_FUNCTION_ENTRY = _IMAGE_CE_RUNTIME_FUNCTION_ENTRY;
  {$EXTERNALSYM IMAGE_CE_RUNTIME_FUNCTION_ENTRY}
  TImageCERuntimeFunctionEntry = IMAGE_CE_RUNTIME_FUNCTION_ENTRY;
  PImageCERuntimeFunctionEntry = PIMAGE_CE_RUNTIME_FUNCTION_ENTRY;

//
// Debug Format
//

type
  PIMAGE_DEBUG_DIRECTORY = ^IMAGE_DEBUG_DIRECTORY;
  {$EXTERNALSYM PIMAGE_DEBUG_DIRECTORY}
  _IMAGE_DEBUG_DIRECTORY = record
    Characteristics: DWORD;
    TimeDateStamp: DWORD;
    MajorVersion: Word;
    MinorVersion: Word;
    Type_: DWORD;
    SizeOfData: DWORD;
    AddressOfRawData: DWORD;
    PointerToRawData: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_DEBUG_DIRECTORY}
  IMAGE_DEBUG_DIRECTORY = _IMAGE_DEBUG_DIRECTORY;
  {$EXTERNALSYM IMAGE_DEBUG_DIRECTORY}
  TImageDebugDirectory = IMAGE_DEBUG_DIRECTORY;
  PImageDebugDirectory = PIMAGE_DEBUG_DIRECTORY;

const
  IMAGE_DEBUG_TYPE_UNKNOWN       = 0;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_UNKNOWN}
  IMAGE_DEBUG_TYPE_COFF          = 1;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_COFF}
  IMAGE_DEBUG_TYPE_CODEVIEW      = 2;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_CODEVIEW}
  IMAGE_DEBUG_TYPE_FPO           = 3;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_FPO}
  IMAGE_DEBUG_TYPE_MISC          = 4;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_MISC}
  IMAGE_DEBUG_TYPE_EXCEPTION     = 5;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_EXCEPTION}
  IMAGE_DEBUG_TYPE_FIXUP         = 6;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_FIXUP}
  IMAGE_DEBUG_TYPE_OMAP_TO_SRC   = 7;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_OMAP_TO_SRC}
  IMAGE_DEBUG_TYPE_OMAP_FROM_SRC = 8;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_OMAP_FROM_SRC}
  IMAGE_DEBUG_TYPE_BORLAND       = 9;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_BORLAND}
  IMAGE_DEBUG_TYPE_RESERVED10    = 10;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_RESERVED10}
  IMAGE_DEBUG_TYPE_CLSID         = 11;
  {$EXTERNALSYM IMAGE_DEBUG_TYPE_CLSID}

type
  PIMAGE_COFF_SYMBOLS_HEADER = ^IMAGE_COFF_SYMBOLS_HEADER;
  {$EXTERNALSYM PIMAGE_COFF_SYMBOLS_HEADER}
  _IMAGE_COFF_SYMBOLS_HEADER = record
    NumberOfSymbols: DWORD;
    LvaToFirstSymbol: DWORD;
    NumberOfLinenumbers: DWORD;
    LvaToFirstLinenumber: DWORD;
    RvaToFirstByteOfCode: DWORD;
    RvaToLastByteOfCode: DWORD;
    RvaToFirstByteOfData: DWORD;
    RvaToLastByteOfData: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_COFF_SYMBOLS_HEADER}
  IMAGE_COFF_SYMBOLS_HEADER = _IMAGE_COFF_SYMBOLS_HEADER;
  {$EXTERNALSYM IMAGE_COFF_SYMBOLS_HEADER}
  TImageCoffSymbolsHeader = IMAGE_COFF_SYMBOLS_HEADER;
  PImageCoffSymbolsHeader = PIMAGE_COFF_SYMBOLS_HEADER;

const
  FRAME_FPO    = 0;
  {$EXTERNALSYM FRAME_FPO}
  FRAME_TRAP   = 1;
  {$EXTERNALSYM FRAME_TRAP}
  FRAME_TSS    = 2;
  {$EXTERNALSYM FRAME_TSS}
  FRAME_NONFPO = 3;
  {$EXTERNALSYM FRAME_NONFPO}

  FPOFLAGS_PROLOG   = $00FF; // # bytes in prolog
  FPOFLAGS_REGS     = $0700; // # regs saved
  FPOFLAGS_HAS_SEH  = $0800; // TRUE if SEH in func
  FPOFLAGS_USE_BP   = $1000; // TRUE if EBP has been allocated
  FPOFLAGS_RESERVED = $2000; // reserved for future use
  FPOFLAGS_FRAME    = $C000; // frame type

type
  PFPO_DATA = ^FPO_DATA;
  {$EXTERNALSYM PFPO_DATA}
  _FPO_DATA = record
    ulOffStart: DWORD;       // offset 1st byte of function code
    cbProcSize: DWORD;       // # bytes in function
    cdwLocals: DWORD;        // # bytes in locals/4
    cdwParams: WORD;         // # bytes in params/4
    Flags: WORD;
  end;
  {$EXTERNALSYM _FPO_DATA}
  FPO_DATA = _FPO_DATA;
  {$EXTERNALSYM FPO_DATA}
  TFpoData = FPO_DATA;
  PFpoData = PFPO_DATA;

const
  SIZEOF_RFPO_DATA = 16;
  {$EXTERNALSYM SIZEOF_RFPO_DATA}

  IMAGE_DEBUG_MISC_EXENAME = 1;
  {$EXTERNALSYM IMAGE_DEBUG_MISC_EXENAME}

type
  PIMAGE_DEBUG_MISC = ^IMAGE_DEBUG_MISC;
  {$EXTERNALSYM PIMAGE_DEBUG_MISC}
  _IMAGE_DEBUG_MISC = record
    DataType: DWORD;   // type of misc data, see defines
    Length: DWORD;     // total length of record, rounded to four byte multiple.
    Unicode: ByteBool; // TRUE if data is unicode string
    Reserved: array [0..2] of Byte;
    Data: array [0..0] of Byte; // Actual data
  end;
  {$EXTERNALSYM _IMAGE_DEBUG_MISC}
  IMAGE_DEBUG_MISC = _IMAGE_DEBUG_MISC;
  {$EXTERNALSYM IMAGE_DEBUG_MISC}
  TImageDebugMisc = IMAGE_DEBUG_MISC;
  PImageDebugMisc = PIMAGE_DEBUG_MISC;

//
// Function table extracted from MIPS/ALPHA/IA64 images.  Does not contain
// information needed only for runtime support.  Just those fields for
// each entry needed by a debugger.
//

  PIMAGE_FUNCTION_ENTRY = ^IMAGE_FUNCTION_ENTRY;
  {$EXTERNALSYM PIMAGE_FUNCTION_ENTRY}
  _IMAGE_FUNCTION_ENTRY = record
    StartingAddress: DWORD;
    EndingAddress: DWORD;
    EndOfPrologue: DWORD;
  end;
  {$EXTERNALSYM _IMAGE_FUNCTION_ENTRY}
  IMAGE_FUNCTION_ENTRY = _IMAGE_FUNCTION_ENTRY;
  {$EXTERNALSYM IMAGE_FUNCTION_ENTRY}
  TImageFunctionEntry = IMAGE_FUNCTION_ENTRY;
  PImageFunctionEntry = PIMAGE_FUNCTION_ENTRY;

  PIMAGE_FUNCTION_ENTRY64 = ^IMAGE_FUNCTION_ENTRY64;
  {$EXTERNALSYM PIMAGE_FUNCTION_ENTRY64}
  _IMAGE_FUNCTION_ENTRY64 = record
    StartingAddress: ULONGLONG;
    EndingAddress: ULONGLONG;
    case Integer of
      0: (EndOfPrologue: ULONGLONG);
      1: (UnwindInfoAddress: ULONGLONG);
  end;
  {$EXTERNALSYM _IMAGE_FUNCTION_ENTRY64}
  IMAGE_FUNCTION_ENTRY64 = _IMAGE_FUNCTION_ENTRY64;
  {$EXTERNALSYM IMAGE_FUNCTION_ENTRY64}
  TImageFunctionEntry64 = IMAGE_FUNCTION_ENTRY64;
  PImageFunctionEntry64 = PIMAGE_FUNCTION_ENTRY64;

//
// Debugging information can be stripped from an image file and placed
// in a separate .DBG file, whose file name part is the same as the
// image file name part (e.g. symbols for CMD.EXE could be stripped
// and placed in CMD.DBG).  This is indicated by the IMAGE_FILE_DEBUG_STRIPPED
// flag in the Characteristics field of the file header.  The beginning of
// the .DBG file contains the following structure which captures certain
// information from the image file.  This allows a debug to proceed even if
// the original image file is not accessable.  This header is followed by
// zero of more IMAGE_SECTION_HEADER structures, followed by zero or more
// IMAGE_DEBUG_DIRECTORY structures.  The latter structures and those in
// the image file contain file offsets relative to the beginning of the
// .DBG file.
//
// If symbols have been stripped from an image, the IMAGE_DEBUG_MISC structure
// is left in the image file, but not mapped.  This allows a debugger to
// compute the name of the .DBG file, from the name of the image in the
// IMAGE_DEBUG_MISC structure.
//

  PIMAGE_SEPARATE_DEBUG_HEADER = ^IMAGE_SEPARATE_DEBUG_HEADER;
  {$EXTERNALSYM PIMAGE_SEPARATE_DEBUG_HEADER}
  _IMAGE_SEPARATE_DEBUG_HEADER = record
    Signature: Word;
    Flags: Word;
    Machine: Word;
    Characteristics: Word;
    TimeDateStamp: DWORD;
    CheckSum: DWORD;
    ImageBase: DWORD;
    SizeOfImage: DWORD;
    NumberOfSections: DWORD;
    ExportedNamesSize: DWORD;
    DebugDirectorySize: DWORD;
    SectionAlignment: DWORD;
    Reserved: array [0..1] of DWORD;
  end;
  {$EXTERNALSYM _IMAGE_SEPARATE_DEBUG_HEADER}
  IMAGE_SEPARATE_DEBUG_HEADER = _IMAGE_SEPARATE_DEBUG_HEADER;
  {$EXTERNALSYM IMAGE_SEPARATE_DEBUG_HEADER}
  TImageSeparateDebugHeader = IMAGE_SEPARATE_DEBUG_HEADER;
  PImageSeparateDebugHeader = PIMAGE_SEPARATE_DEBUG_HEADER;

  _NON_PAGED_DEBUG_INFO = record
    Signature: WORD;
    Flags: WORD;
    Size: DWORD;
    Machine: WORD;
    Characteristics: WORD;
    TimeDateStamp: DWORD;
    CheckSum: DWORD;
    SizeOfImage: DWORD;
    ImageBase: ULONGLONG;
    //DebugDirectorySize
    //IMAGE_DEBUG_DIRECTORY
  end;
  {$EXTERNALSYM _NON_PAGED_DEBUG_INFO}
  NON_PAGED_DEBUG_INFO = _NON_PAGED_DEBUG_INFO;
  {$EXTERNALSYM NON_PAGED_DEBUG_INFO}
  PNON_PAGED_DEBUG_INFO = ^NON_PAGED_DEBUG_INFO;
  {$EXTERNALSYM PNON_PAGED_DEBUG_INFO}

const
  IMAGE_SEPARATE_DEBUG_SIGNATURE = $4944;
  {$EXTERNALSYM IMAGE_SEPARATE_DEBUG_SIGNATURE}
  NON_PAGED_DEBUG_SIGNATURE      = $494E;
  {$EXTERNALSYM NON_PAGED_DEBUG_SIGNATURE}

  IMAGE_SEPARATE_DEBUG_FLAGS_MASK = $8000;
  {$EXTERNALSYM IMAGE_SEPARATE_DEBUG_FLAGS_MASK}
  IMAGE_SEPARATE_DEBUG_MISMATCH   = $8000; // when DBG was updated, the old checksum didn't match.
  {$EXTERNALSYM IMAGE_SEPARATE_DEBUG_MISMATCH}

//
//  The .arch section is made up of headers, each describing an amask position/value
//  pointing to an array of IMAGE_ARCHITECTURE_ENTRY's.  Each "array" (both the header
//  and entry arrays) are terminiated by a quadword of 0xffffffffL.
//
//  NOTE: There may be quadwords of 0 sprinkled around and must be skipped.
//

const
  IAHMASK_VALUE = $00000001; // 1 -> code section depends on mask bit
                             // 0 -> new instruction depends on mask bit
  IAHMASK_MBZ7  = $000000FE; // MBZ
  IAHMASK_SHIFT = $0000FF00; // Amask bit in question for this fixup
  IAHMASK_MBZ16 = DWORD($FFFF0000); // MBZ

type
  PIMAGE_ARCHITECTURE_HEADER = ^IMAGE_ARCHITECTURE_HEADER;
  {$EXTERNALSYM PIMAGE_ARCHITECTURE_HEADER}
  _ImageArchitectureHeader = record
    Mask: DWORD;
    FirstEntryRVA: DWORD;    // RVA into .arch section to array of ARCHITECTURE_ENTRY's
  end;
  {$EXTERNALSYM _ImageArchitectureHeader}
  IMAGE_ARCHITECTURE_HEADER = _ImageArchitectureHeader;
  {$EXTERNALSYM IMAGE_ARCHITECTURE_HEADER}
  TImageArchitectureHeader = IMAGE_ARCHITECTURE_HEADER;
  PImageArchitectureHeader = PIMAGE_ARCHITECTURE_HEADER;

  PIMAGE_ARCHITECTURE_ENTRY = ^IMAGE_ARCHITECTURE_ENTRY;
  {$EXTERNALSYM PIMAGE_ARCHITECTURE_ENTRY}
  _ImageArchitectureEntry = record
    FixupInstRVA: DWORD;                         // RVA of instruction to fixup
    NewInst: DWORD;                              // fixup instruction (see alphaops.h)
  end;
  {$EXTERNALSYM _ImageArchitectureEntry}
  IMAGE_ARCHITECTURE_ENTRY = _ImageArchitectureEntry;
  {$EXTERNALSYM IMAGE_ARCHITECTURE_ENTRY}
  TImageArchitectureEntry = IMAGE_ARCHITECTURE_ENTRY;
  PImageArchitectureEntry = PIMAGE_ARCHITECTURE_ENTRY;

// #include "poppack.h"                // Back to the initial value

// The following structure defines the new import object.  Note the values of the first two fields,
// which must be set as stated in order to differentiate old and new import members.
// Following this structure, the linker emits two null-terminated strings used to recreate the
// import at the time of use.  The first string is the import's name, the second is the dll's name.

const
  IMPORT_OBJECT_HDR_SIG2 = $ffff;
  {$EXTERNALSYM IMPORT_OBJECT_HDR_SIG2}

const
  IOHFLAGS_TYPE = $0003;      // IMPORT_TYPE
  IAHFLAGS_NAMETYPE = $001C;  // IMPORT_NAME_TYPE
  IAHFLAGS_RESERVED = $FFE0;  // Reserved. Must be zero.

type
  PImportObjectHeader = ^IMPORT_OBJECT_HEADER;
  IMPORT_OBJECT_HEADER = record
    Sig1: WORD;                       // Must be IMAGE_FILE_MACHINE_UNKNOWN
    Sig2: WORD;                       // Must be IMPORT_OBJECT_HDR_SIG2.
    Version: WORD;
    Machine: WORD;
    TimeDateStamp: DWORD;             // Time/date stamp
    SizeOfData: DWORD;                // particularly useful for incremental links
    OrdinalOrHint: record
    case Integer of
      0: (Ordinal: WORD);             // if grf & IMPORT_OBJECT_ORDINAL
      1: (Flags: DWORD);
    end;
    Flags: WORD;
    //WORD    Type : 2;                   // IMPORT_TYPE
    //WORD    NameType : 3;               // IMPORT_NAME_TYPE
    //WORD    Reserved : 11;              // Reserved. Must be zero.
  end;
  {$EXTERNALSYM IMPORT_OBJECT_HEADER}
  TImportObjectHeader = IMPORT_OBJECT_HEADER;

  IMPORT_OBJECT_TYPE = (IMPORT_OBJECT_CODE, IMPORT_OBJECT_DATA, IMPORT_OBJECT_CONST);
  {$EXTERNALSYM IMPORT_OBJECT_TYPE}
  TImportObjectType = IMPORT_OBJECT_TYPE;

  IMPORT_OBJECT_NAME_TYPE = (
    IMPORT_OBJECT_ORDINAL,          // Import by ordinal
    IMPORT_OBJECT_NAME,             // Import name == public symbol name.
    IMPORT_OBJECT_NAME_NO_PREFIX,   // Import name == public symbol name skipping leading ?, @, or optionally _.
    IMPORT_OBJECT_NAME_UNDECORATE); // Import name == public symbol name skipping leading ?, @, or optionally _
                                    // and truncating at first @
  {$EXTERNALSYM IMPORT_OBJECT_NAME_TYPE}
  TImportObjectNameType = IMPORT_OBJECT_NAME_TYPE;

  ReplacesCorHdrNumericDefines = DWORD;
  {$EXTERNALSYM ReplacesCorHdrNumericDefines}

const

// COM+ Header entry point flags.

  COMIMAGE_FLAGS_ILONLY               = $00000001;
  {$EXTERNALSYM COMIMAGE_FLAGS_ILONLY}
  COMIMAGE_FLAGS_32BITREQUIRED        = $00000002;
  {$EXTERNALSYM COMIMAGE_FLAGS_32BITREQUIRED}
  COMIMAGE_FLAGS_IL_LIBRARY           = $00000004;
  {$EXTERNALSYM COMIMAGE_FLAGS_IL_LIBRARY}
  COMIMAGE_FLAGS_STRONGNAMESIGNED     = $00000008;
  {$EXTERNALSYM COMIMAGE_FLAGS_STRONGNAMESIGNED}
  COMIMAGE_FLAGS_TRACKDEBUGDATA       = $00010000;
  {$EXTERNALSYM COMIMAGE_FLAGS_TRACKDEBUGDATA}

// Version flags for image.

  COR_VERSION_MAJOR_V2                = 2;
  {$EXTERNALSYM COR_VERSION_MAJOR_V2}
  COR_VERSION_MAJOR                   = COR_VERSION_MAJOR_V2;
  {$EXTERNALSYM COR_VERSION_MAJOR}
  COR_VERSION_MINOR                   = 0;
  {$EXTERNALSYM COR_VERSION_MINOR}
  COR_DELETED_NAME_LENGTH             = 8;
  {$EXTERNALSYM COR_DELETED_NAME_LENGTH}
  COR_VTABLEGAP_NAME_LENGTH           = 8;
  {$EXTERNALSYM COR_VTABLEGAP_NAME_LENGTH}

// Maximum size of a NativeType descriptor.

  NATIVE_TYPE_MAX_CB                  = 1;
  {$EXTERNALSYM NATIVE_TYPE_MAX_CB}
  COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE= $FF;
  {$EXTERNALSYM COR_ILMETHOD_SECT_SMALL_MAX_DATASIZE}

// #defines for the MIH FLAGS

  IMAGE_COR_MIH_METHODRVA             = $01;
  {$EXTERNALSYM IMAGE_COR_MIH_METHODRVA}
  IMAGE_COR_MIH_EHRVA                 = $02;
  {$EXTERNALSYM IMAGE_COR_MIH_EHRVA}
  IMAGE_COR_MIH_BASICBLOCK            = $08;
  {$EXTERNALSYM IMAGE_COR_MIH_BASICBLOCK}

// V-table constants

  COR_VTABLE_32BIT                    = $01;          // V-table slots are 32-bits in size.
  {$EXTERNALSYM COR_VTABLE_32BIT}
  COR_VTABLE_64BIT                    = $02;          // V-table slots are 64-bits in size.
  {$EXTERNALSYM COR_VTABLE_64BIT}
  COR_VTABLE_FROM_UNMANAGED           = $04;          // If set, transition from unmanaged.
  {$EXTERNALSYM COR_VTABLE_FROM_UNMANAGED}
  COR_VTABLE_CALL_MOST_DERIVED        = $10;          // Call most derived method described by
  {$EXTERNALSYM COR_VTABLE_CALL_MOST_DERIVED}

// EATJ constants

  IMAGE_COR_EATJ_THUNK_SIZE           = 32;            // Size of a jump thunk reserved range.
  {$EXTERNALSYM IMAGE_COR_EATJ_THUNK_SIZE}

// Max name lengths
// Change to unlimited name lengths.

  MAX_CLASS_NAME                      = 1024;
  {$EXTERNALSYM MAX_CLASS_NAME}
  MAX_PACKAGE_NAME                    = 1024;
  {$EXTERNALSYM MAX_PACKAGE_NAME}

// COM+ 2.0 header structure.

type
  IMAGE_COR20_HEADER = record

    // Header versioning

    cb: DWORD;
    MajorRuntimeVersion: WORD;
    MinorRuntimeVersion: WORD;

    // Symbol table and startup information

    MetaData: IMAGE_DATA_DIRECTORY;
    Flags: DWORD;
    EntryPointToken: DWORD;

    // Binding information

    Resources: IMAGE_DATA_DIRECTORY;
    StrongNameSignature: IMAGE_DATA_DIRECTORY;

    // Regular fixup and binding information

    CodeManagerTable: IMAGE_DATA_DIRECTORY;
    VTableFixups: IMAGE_DATA_DIRECTORY;
    ExportAddressTableJumps: IMAGE_DATA_DIRECTORY;

    // Precompiled image info (internal use only - set to zero)

    ManagedNativeHeader: IMAGE_DATA_DIRECTORY;
  end;
  {$EXTERNALSYM IMAGE_COR20_HEADER}
  PIMAGE_COR20_HEADER = ^IMAGE_COR20_HEADER;
  {$EXTERNALSYM PIMAGE_COR20_HEADER}
  TImageCor20Header = IMAGE_COR20_HEADER;
  PImageCor20Header = PIMAGE_COR20_HEADER;

//
// End Image Format
//

type
  SLIST_ENTRY = SINGLE_LIST_ENTRY;
  {$EXTERNALSYM SLIST_ENTRY}
  _SLIST_ENTRY = _SINGLE_LIST_ENTRY;
  {$EXTERNALSYM _SLIST_ENTRY}
  PSLIST_ENTRY = PSINGLE_LIST_ENTRY;
  {$EXTERNALSYM PSLIST_ENTRY}
  TSListEntry = SLIST_ENTRY;
  PSListEntry = PSLIST_ENTRY;  

type
  _SLIST_HEADER = record
  case Integer of
    0: (
      Alignment: ULONGLONG);
    1: (
      Next: SLIST_ENTRY;
      Depth: WORD;
      Sequence: WORD);
  end;
  {$EXTERNALSYM _SLIST_HEADER}
  SLIST_HEADER = _SLIST_HEADER;
  {$EXTERNALSYM SLIST_HEADER}
  PSLIST_HEADER = ^SLIST_HEADER;
  {$EXTERNALSYM PSLIST_HEADER}
  TSListHeader = SLIST_HEADER;
  PSListHeader = PSLIST_HEADER;  

procedure RtlInitializeSListHead(ListHead: PSLIST_HEADER); stdcall;
{$EXTERNALSYM RtlInitializeSListHead}
function RtlFirstEntrySList(ListHead: PSLIST_HEADER): PSLIST_ENTRY; stdcall;
{$EXTERNALSYM RtlFirstEntrySList}
function RtlInterlockedPopEntrySList(ListHead: PSLIST_HEADER): PSLIST_ENTRY; stdcall;
{$EXTERNALSYM RtlInterlockedPopEntrySList}
function RtlInterlockedPushEntrySList(ListHead, ListEntry: PSLIST_HEADER): PSLIST_ENTRY; stdcall;
{$EXTERNALSYM RtlInterlockedPushEntrySList}
function RtlInterlockedFlushSList(ListHead: PSLIST_HEADER): PSLIST_ENTRY; stdcall;
{$EXTERNALSYM RtlInterlockedFlushSList}
function RtlQueryDepthSList(ListHead: PSLIST_HEADER): WORD; stdcall;
{$EXTERNALSYM RtlQueryDepthSList}

const
  HEAP_NO_SERIALIZE             = $00000001;
  {$EXTERNALSYM HEAP_NO_SERIALIZE}
  HEAP_GROWABLE                 = $00000002;
  {$EXTERNALSYM HEAP_GROWABLE}
  HEAP_GENERATE_EXCEPTIONS      = $00000004;
  {$EXTERNALSYM HEAP_GENERATE_EXCEPTIONS}
  HEAP_ZERO_MEMORY              = $00000008;
  {$EXTERNALSYM HEAP_ZERO_MEMORY}
  HEAP_REALLOC_IN_PLACE_ONLY    = $00000010;
  {$EXTERNALSYM HEAP_REALLOC_IN_PLACE_ONLY}
  HEAP_TAIL_CHECKING_ENABLED    = $00000020;
  {$EXTERNALSYM HEAP_TAIL_CHECKING_ENABLED}
  HEAP_FREE_CHECKING_ENABLED    = $00000040;
  {$EXTERNALSYM HEAP_FREE_CHECKING_ENABLED}
  HEAP_DISABLE_COALESCE_ON_FREE = $00000080;
  {$EXTERNALSYM HEAP_DISABLE_COALESCE_ON_FREE}
  HEAP_CREATE_ALIGN_16          = $00010000;
  {$EXTERNALSYM HEAP_CREATE_ALIGN_16}
  HEAP_CREATE_ENABLE_TRACING    = $00020000;
  {$EXTERNALSYM HEAP_CREATE_ENABLE_TRACING}
  HEAP_MAXIMUM_TAG              = $0FFF;
  {$EXTERNALSYM HEAP_MAXIMUM_TAG}
  HEAP_PSEUDO_TAG_FLAG          = $8000;
  {$EXTERNALSYM HEAP_PSEUDO_TAG_FLAG}
  HEAP_TAG_SHIFT                = 18;
  {$EXTERNALSYM HEAP_TAG_SHIFT}

function HEAP_MAKE_TAG_FLAGS(b, o: DWORD): DWORD;
{$EXTERNALSYM HEAP_MAKE_TAG_FLAGS}

procedure RtlCaptureContext(ContextRecord: PCONTEXT); stdcall;
{$EXTERNALSYM RtlCaptureContext}

const
  IS_TEXT_UNICODE_ASCII16         = $0001;
  {$EXTERNALSYM IS_TEXT_UNICODE_ASCII16}
  IS_TEXT_UNICODE_REVERSE_ASCII16 = $0010;
  {$EXTERNALSYM IS_TEXT_UNICODE_REVERSE_ASCII16}

  IS_TEXT_UNICODE_STATISTICS         = $0002;
  {$EXTERNALSYM IS_TEXT_UNICODE_STATISTICS}
  IS_TEXT_UNICODE_REVERSE_STATISTICS = $0020;
  {$EXTERNALSYM IS_TEXT_UNICODE_REVERSE_STATISTICS}

  IS_TEXT_UNICODE_CONTROLS         = $0004;
  {$EXTERNALSYM IS_TEXT_UNICODE_CONTROLS}
  IS_TEXT_UNICODE_REVERSE_CONTROLS = $0040;
  {$EXTERNALSYM IS_TEXT_UNICODE_REVERSE_CONTROLS}

  IS_TEXT_UNICODE_SIGNATURE         = $0008;
  {$EXTERNALSYM IS_TEXT_UNICODE_SIGNATURE}
  IS_TEXT_UNICODE_REVERSE_SIGNATURE = $0080;
  {$EXTERNALSYM IS_TEXT_UNICODE_REVERSE_SIGNATURE}

  IS_TEXT_UNICODE_ILLEGAL_CHARS = $0100;
  {$EXTERNALSYM IS_TEXT_UNICODE_ILLEGAL_CHARS}
  IS_TEXT_UNICODE_ODD_LENGTH    = $0200;
  {$EXTERNALSYM IS_TEXT_UNICODE_ODD_LENGTH}
  IS_TEXT_UNICODE_DBCS_LEADBYTE = $0400;
  {$EXTERNALSYM IS_TEXT_UNICODE_DBCS_LEADBYTE}
  IS_TEXT_UNICODE_NULL_BYTES    = $1000;
  {$EXTERNALSYM IS_TEXT_UNICODE_NULL_BYTES}

  IS_TEXT_UNICODE_UNICODE_MASK     = $000F;
  {$EXTERNALSYM IS_TEXT_UNICODE_UNICODE_MASK}
  IS_TEXT_UNICODE_REVERSE_MASK     = $00F0;
  {$EXTERNALSYM IS_TEXT_UNICODE_REVERSE_MASK}
  IS_TEXT_UNICODE_NOT_UNICODE_MASK = $0F00;
  {$EXTERNALSYM IS_TEXT_UNICODE_NOT_UNICODE_MASK}
  IS_TEXT_UNICODE_NOT_ASCII_MASK   = $F000;
  {$EXTERNALSYM IS_TEXT_UNICODE_NOT_ASCII_MASK}

  COMPRESSION_FORMAT_NONE     = ($0000);
  {$EXTERNALSYM COMPRESSION_FORMAT_NONE}
  COMPRESSION_FORMAT_DEFAULT  = ($0001);
  {$EXTERNALSYM COMPRESSION_FORMAT_DEFAULT}
  COMPRESSION_FORMAT_LZNT1    = ($0002);
  {$EXTERNALSYM COMPRESSION_FORMAT_LZNT1}
  COMPRESSION_ENGINE_STANDARD = ($0000);
  {$EXTERNALSYM COMPRESSION_ENGINE_STANDARD}
  COMPRESSION_ENGINE_MAXIMUM  = ($0100);
  {$EXTERNALSYM COMPRESSION_ENGINE_MAXIMUM}
  COMPRESSION_ENGINE_HIBER    = ($0200);
  {$EXTERNALSYM COMPRESSION_ENGINE_HIBER}

function RtlCompareMemory(const Source1, Source2: Pointer; Length: SIZE_T): SIZE_T; stdcall;
{$EXTERNALSYM RtlCompareMemory}

type
  PMESSAGE_RESOURCE_ENTRY = ^MESSAGE_RESOURCE_ENTRY;
  {$EXTERNALSYM PMESSAGE_RESOURCE_ENTRY}
  _MESSAGE_RESOURCE_ENTRY = record
    Length: Word;
    Flags: Word;
    Text: array [0..0] of Byte;
  end;
  {$EXTERNALSYM _MESSAGE_RESOURCE_ENTRY}
  MESSAGE_RESOURCE_ENTRY = _MESSAGE_RESOURCE_ENTRY;
  {$EXTERNALSYM MESSAGE_RESOURCE_ENTRY}
  TMessageResourceEntry = MESSAGE_RESOURCE_ENTRY;
  PMessageResourceEntry = PMESSAGE_RESOURCE_ENTRY;

const
  MESSAGE_RESOURCE_UNICODE = $0001;
  {$EXTERNALSYM MESSAGE_RESOURCE_UNICODE}

type
  PMESSAGE_RESOURCE_BLOCK = ^MESSAGE_RESOURCE_BLOCK;
  {$EXTERNALSYM PMESSAGE_RESOURCE_BLOCK}
  _MESSAGE_RESOURCE_BLOCK = record
    LowId: DWORD;
    HighId: DWORD;
    OffsetToEntries: DWORD;
  end;
  {$EXTERNALSYM _MESSAGE_RESOURCE_BLOCK}
  MESSAGE_RESOURCE_BLOCK = _MESSAGE_RESOURCE_BLOCK;
  {$EXTERNALSYM MESSAGE_RESOURCE_BLOCK}
  TMessageResourceBlock = MESSAGE_RESOURCE_BLOCK;
  PMessageResourceBlock = PMESSAGE_RESOURCE_BLOCK;

  PMESSAGE_RESOURCE_DATA = ^MESSAGE_RESOURCE_DATA;
  {$EXTERNALSYM PMESSAGE_RESOURCE_DATA}
  _MESSAGE_RESOURCE_DATA = record
    NumberOfBlocks: DWORD;
    Blocks: array [0..0] of MESSAGE_RESOURCE_BLOCK;
  end;
  {$EXTERNALSYM _MESSAGE_RESOURCE_DATA}
  MESSAGE_RESOURCE_DATA = _MESSAGE_RESOURCE_DATA;
  {$EXTERNALSYM MESSAGE_RESOURCE_DATA}
  TMessageResourceData = MESSAGE_RESOURCE_DATA;
  PMessageResourceData = PMESSAGE_RESOURCE_DATA;

  LPOSVERSIONINFOA = ^OSVERSIONINFOA;
  {$EXTERNALSYM LPOSVERSIONINFOA}
  _OSVERSIONINFOA = record
    dwOSVersionInfoSize: DWORD;
    dwMajorVersion: DWORD;
    dwMinorVersion: DWORD;
    dwBuildNumber: DWORD;
    dwPlatformId: DWORD;
    szCSDVersion: array [0..127] of CHAR; // Maintenance string for PSS usage
  end;
  {$EXTERNALSYM _OSVERSIONINFOA}
  OSVERSIONINFOA = _OSVERSIONINFOA;
  {$EXTERNALSYM OSVERSIONINFOA}
  TOsVersionInfoA = OSVERSIONINFOA;
  POsVersionInfoA = LPOSVERSIONINFOA;

  LPOSVERSIONINFOW = ^OSVERSIONINFOW;
  {$EXTERNALSYM LPOSVERSIONINFOW}
  _OSVERSIONINFOW = record
    dwOSVersionInfoSize: DWORD;
    dwMajorVersion: DWORD;
    dwMinorVersion: DWORD;
    dwBuildNumber: DWORD;
    dwPlatformId: DWORD;
    szCSDVersion: array [0..127] of WCHAR; // Maintenance string for PSS usage
  end;
  {$EXTERNALSYM _OSVERSIONINFOW}
  OSVERSIONINFOW = _OSVERSIONINFOW;
  {$EXTERNALSYM OSVERSIONINFOW}
  TOsVersionInfoW = OSVERSIONINFOW;
  POsVersionInfoW = LPOSVERSIONINFOW;

{$IFDEF UNICODE}
  OSVERSIONINFO = OSVERSIONINFOW;
  {$EXTERNALSYM OSVERSIONINFO}
  POSVERSIONINFO = POSVERSIONINFOW;
  {$EXTERNALSYM POSVERSIONINFO}
  LPOSVERSIONINFO = LPOSVERSIONINFOW;
  {$EXTERNALSYM LPOSVERSIONINFO}
  TOSVersionInfo = TOSVersionInfoW;
{$ELSE}
  OSVERSIONINFO = OSVERSIONINFOA;
  {$EXTERNALSYM OSVERSIONINFO}
  POSVERSIONINFO = POSVERSIONINFOA;
  {$EXTERNALSYM POSVERSIONINFO}
  LPOSVERSIONINFO = LPOSVERSIONINFOA;
  {$EXTERNALSYM LPOSVERSIONINFO}
  TOSVersionInfo = TOSVersionInfoA;
{$ENDIF}

type
  POSVERSIONINFOEXA = ^OSVERSIONINFOEXA;
  {$EXTERNALSYM POSVERSIONINFOEXA}
  _OSVERSIONINFOEXA = record
    dwOSVersionInfoSize: DWORD;
    dwMajorVersion: DWORD;
    dwMinorVersion: DWORD;
    dwBuildNumber: DWORD;
    dwPlatformId: DWORD;
    szCSDVersion: array [0..127] of CHAR;     // Maintenance string for PSS usage
    wServicePackMajor: WORD;
    wServicePackMinor: WORD;
    wSuiteMask: WORD;
    wProductType: BYTE;
    wReserved: BYTE;
  end;
  {$EXTERNALSYM _OSVERSIONINFOEXA}
  OSVERSIONINFOEXA = _OSVERSIONINFOEXA;
  {$EXTERNALSYM OSVERSIONINFOEXA}
  LPOSVERSIONINFOEXA = ^OSVERSIONINFOEXA;
  {$EXTERNALSYM LPOSVERSIONINFOEXA}
  TOSVersionInfoExA = _OSVERSIONINFOEXA;

  POSVERSIONINFOEXW = ^OSVERSIONINFOEXW;
  {$EXTERNALSYM POSVERSIONINFOEXW}
  _OSVERSIONINFOEXW = record
    dwOSVersionInfoSize: DWORD;
    dwMajorVersion: DWORD;
    dwMinorVersion: DWORD;
    dwBuildNumber: DWORD;
    dwPlatformId: DWORD;
    szCSDVersion: array [0..127] of WCHAR;     // Maintenance string for PSS usage
    wServicePackMajor: WORD;
    wServicePackMinor: WORD;
    wSuiteMask: WORD;
    wProductType: BYTE;
    wReserved: BYTE;
  end;
  {$EXTERNALSYM _OSVERSIONINFOEXW}
  OSVERSIONINFOEXW = _OSVERSIONINFOEXW;
  {$EXTERNALSYM OSVERSIONINFOEXW}
  LPOSVERSIONINFOEXW = ^OSVERSIONINFOEXW;
  {$EXTERNALSYM LPOSVERSIONINFOEXW}
  RTL_OSVERSIONINFOEXW = _OSVERSIONINFOEXW;
  {$EXTERNALSYM RTL_OSVERSIONINFOEXW}
  PRTL_OSVERSIONINFOEXW = ^RTL_OSVERSIONINFOEXW;
  {$EXTERNALSYM PRTL_OSVERSIONINFOEXW}
  TOSVersionInfoExW = _OSVERSIONINFOEXW;

{$IFDEF UNICODE}

  OSVERSIONINFOEX = OSVERSIONINFOEXW;
  {$EXTERNALSYM OSVERSIONINFOEX}
  POSVERSIONINFOEX = POSVERSIONINFOEXW;
  {$EXTERNALSYM POSVERSIONINFOEX}
  LPOSVERSIONINFOEX = LPOSVERSIONINFOEXW;
  {$EXTERNALSYM LPOSVERSIONINFOEX}
  TOSVersionInfoEx = TOSVersionInfoExW;

{$ELSE}

  OSVERSIONINFOEX = OSVERSIONINFOEXA;
  {$EXTERNALSYM OSVERSIONINFOEX}
  POSVERSIONINFOEX = POSVERSIONINFOEXA;
  {$EXTERNALSYM POSVERSIONINFOEX}
  LPOSVERSIONINFOEX = LPOSVERSIONINFOEXA;
  {$EXTERNALSYM LPOSVERSIONINFOEX}
  TOSVersionInfoEx = TOSVersionInfoExA;  

{$ENDIF}

//
// RtlVerifyVersionInfo() conditions
//

const
  VER_EQUAL         = 1;
  {$EXTERNALSYM VER_EQUAL}
  VER_GREATER       = 2;
  {$EXTERNALSYM VER_GREATER}
  VER_GREATER_EQUAL = 3;
  {$EXTERNALSYM VER_GREATER_EQUAL}
  VER_LESS          = 4;
  {$EXTERNALSYM VER_LESS}
  VER_LESS_EQUAL    = 5;
  {$EXTERNALSYM VER_LESS_EQUAL}
  VER_AND           = 6;
  {$EXTERNALSYM VER_AND}
  VER_OR            = 7;
  {$EXTERNALSYM VER_OR}

  VER_CONDITION_MASK              = 7;
  {$EXTERNALSYM VER_CONDITION_MASK}
  VER_NUM_BITS_PER_CONDITION_MASK = 3;
  {$EXTERNALSYM VER_NUM_BITS_PER_CONDITION_MASK}

//
// RtlVerifyVersionInfo() type mask bits
//

  VER_MINORVERSION     = $0000001;
  {$EXTERNALSYM VER_MINORVERSION}
  VER_MAJORVERSION     = $0000002;
  {$EXTERNALSYM VER_MAJORVERSION}
  VER_BUILDNUMBER      = $0000004;
  {$EXTERNALSYM VER_BUILDNUMBER}
  VER_PLATFORMID       = $0000008;
  {$EXTERNALSYM VER_PLATFORMID}
  VER_SERVICEPACKMINOR = $0000010;
  {$EXTERNALSYM VER_SERVICEPACKMINOR}
  VER_SERVICEPACKMAJOR = $0000020;
  {$EXTERNALSYM VER_SERVICEPACKMAJOR}
  VER_SUITENAME        = $0000040;
  {$EXTERNALSYM VER_SUITENAME}
  VER_PRODUCT_TYPE     = $0000080;
  {$EXTERNALSYM VER_PRODUCT_TYPE}

//
// RtlVerifyVersionInfo() os product type values
//

  VER_NT_WORKSTATION       = $0000001;
  {$EXTERNALSYM VER_NT_WORKSTATION}
  VER_NT_DOMAIN_CONTROLLER = $0000002;
  {$EXTERNALSYM VER_NT_DOMAIN_CONTROLLER}
  VER_NT_SERVER            = $0000003;
  {$EXTERNALSYM VER_NT_SERVER}

//
// dwPlatformId defines:
//

  VER_PLATFORM_WIN32s        = 0;
  {$EXTERNALSYM VER_PLATFORM_WIN32s}
  VER_PLATFORM_WIN32_WINDOWS = 1;
  {$EXTERNALSYM VER_PLATFORM_WIN32_WINDOWS}
  VER_PLATFORM_WIN32_NT      = 2;
  {$EXTERNALSYM VER_PLATFORM_WIN32_NT}

//
//
// VerifyVersionInfo() macro to set the condition mask
//
// For documentation sakes here's the old version of the macro that got
// changed to call an API
// #define VER_SET_CONDITION(_m_,_t_,_c_)  _m_=(_m_|(_c_<<(1<<_t_)))
//

procedure VER_SET_CONDITION(var Mask: DWORDLONG; TypeBitmask, ConditionMask: ULONG);
{$EXTERNALSYM VER_SET_CONDITION}

function VerSetConditionMask(ConditionMask: ULONGLONG; TypeMask: DWORD;
  Condition: BYTE): ULONGLONG; stdcall;
{$EXTERNALSYM VerSetConditionMask}

type
  PRTL_CRITICAL_SECTION_DEBUG = ^RTL_CRITICAL_SECTION_DEBUG;
  {$EXTERNALSYM PRTL_CRITICAL_SECTION_DEBUG}
  _RTL_CRITICAL_SECTION_DEBUG = record
    _Type: WORD;
    CreatorBackTraceIndex: WORD;
    CriticalSection: PRTL_CRITICAL_SECTION_DEBUG;
    ProcessLocksList: LIST_ENTRY;
    EntryCount: DWORD;
    ContentionCount: DWORD;
    Spare: array [0..1] of DWORD;
  end;
  {$EXTERNALSYM _RTL_CRITICAL_SECTION_DEBUG}
  RTL_CRITICAL_SECTION_DEBUG = _RTL_CRITICAL_SECTION_DEBUG;
  {$EXTERNALSYM RTL_CRITICAL_SECTION_DEBUG}
  TRtlCriticalSectionDebug = RTL_CRITICAL_SECTION_DEBUG;
  PRtlCriticalSectionDebug = PRTL_CRITICAL_SECTION_DEBUG;
  RTL_RESOURCE_DEBUG = _RTL_CRITICAL_SECTION_DEBUG;
  {$EXTERNALSYM RTL_RESOURCE_DEBUG}
  PRTL_RESOURCE_DEBUG = RTL_RESOURCE_DEBUG;
  {$EXTERNALSYM PRTL_RESOURCE_DEBUG}
  TRtlResourceDebug = RTL_CRITICAL_SECTION_DEBUG;
  PRtlResourceDebug = PRTL_CRITICAL_SECTION_DEBUG;

const
  RTL_CRITSECT_TYPE = 0;
  {$EXTERNALSYM RTL_CRITSECT_TYPE}
  RTL_RESOURCE_TYPE = 1;
  {$EXTERNALSYM RTL_RESOURCE_TYPE}

type
  PRTL_CRITICAL_SECTION = ^RTL_CRITICAL_SECTION;
  {$EXTERNALSYM PRTL_CRITICAL_SECTION}
  _RTL_CRITICAL_SECTION = record
    DebugInfo: PRTL_CRITICAL_SECTION_DEBUG;

    //
    //  The following three fields control entering and exiting the critical
    //  section for the resource
    //

    LockCount: LONG;
    RecursionCount: LONG;
    OwningThread: HANDLE;        // from the thread's ClientId->UniqueThread
    LockSemaphore: HANDLE;
    SpinCount: ULONG_PTR;        // force size on 64-bit systems when packed
  end;
  {$EXTERNALSYM _RTL_CRITICAL_SECTION}
  RTL_CRITICAL_SECTION = _RTL_CRITICAL_SECTION;
  {$EXTERNALSYM RTL_CRITICAL_SECTION}
  TRtlCriticalSection = RTL_CRITICAL_SECTION;
  PRtlCriticalSection = PRTL_CRITICAL_SECTION;

  RTL_VERIFIER_DLL_LOAD_CALLBACK = procedure (DllName: PWSTR; DllBase: PVOID; DllSize: SIZE_T;
    Reserved: PVOID); stdcall;
  {$EXTERNALSYM RTL_VERIFIER_DLL_LOAD_CALLBACK}

  RTL_VERIFIER_DLL_UNLOAD_CALLBACK = procedure (DllName: PWSTR; DllBase: PVOID; DllSize: SIZE_T;
    Reserved: PVOID); stdcall;
  {$EXTERNALSYM RTL_VERIFIER_DLL_UNLOAD_CALLBACK}

  RTL_VERIFIER_NTDLLHEAPFREE_CALLBACK = procedure (AllocationBase: PVOID; AllocationSize: SIZE_T); stdcall;
  {$EXTERNALSYM RTL_VERIFIER_NTDLLHEAPFREE_CALLBACK}

  PRTL_VERIFIER_THUNK_DESCRIPTOR = ^RTL_VERIFIER_THUNK_DESCRIPTOR;
  {$EXTERNALSYM PRTL_VERIFIER_THUNK_DESCRIPTOR}
  _RTL_VERIFIER_THUNK_DESCRIPTOR = record
    ThunkName: PCHAR;
    ThunkOldAddress: PVOID;
    ThunkNewAddress: PVOID;
  end;
  {$EXTERNALSYM _RTL_VERIFIER_THUNK_DESCRIPTOR}
  RTL_VERIFIER_THUNK_DESCRIPTOR = _RTL_VERIFIER_THUNK_DESCRIPTOR;
  {$EXTERNALSYM RTL_VERIFIER_THUNK_DESCRIPTOR}
  TRtlVerifierThunkDescriptor = RTL_VERIFIER_THUNK_DESCRIPTOR;
  PRtlVerifierThunkDescriptor = PRTL_VERIFIER_THUNK_DESCRIPTOR;

  PRTL_VERIFIER_DLL_DESCRIPTOR = ^RTL_VERIFIER_DLL_DESCRIPTOR;
  {$EXTERNALSYM PRTL_VERIFIER_DLL_DESCRIPTOR}
  _RTL_VERIFIER_DLL_DESCRIPTOR = record
    DllName: PWCHAR;
    DllFlags: DWORD;
    DllAddress: PVOID;
    DllThunks: PRTL_VERIFIER_THUNK_DESCRIPTOR;
  end;
  {$EXTERNALSYM _RTL_VERIFIER_DLL_DESCRIPTOR}
  RTL_VERIFIER_DLL_DESCRIPTOR = _RTL_VERIFIER_DLL_DESCRIPTOR;
  {$EXTERNALSYM RTL_VERIFIER_DLL_DESCRIPTOR}
  TRtlVerifierDllDescriptor = RTL_VERIFIER_DLL_DESCRIPTOR;
  PRtlVerifierDllDescriptor = PRTL_VERIFIER_DLL_DESCRIPTOR;

  PRTL_VERIFIER_PROVIDER_DESCRIPTOR = ^RTL_VERIFIER_PROVIDER_DESCRIPTOR;
  {$EXTERNALSYM PRTL_VERIFIER_PROVIDER_DESCRIPTOR}
  _RTL_VERIFIER_PROVIDER_DESCRIPTOR = record
    //
    // Filled by verifier provider DLL
    //
    Length: DWORD;
    ProviderDlls: PRTL_VERIFIER_DLL_DESCRIPTOR;
    ProviderDllLoadCallback: RTL_VERIFIER_DLL_LOAD_CALLBACK;
    ProviderDllUnloadCallback: RTL_VERIFIER_DLL_UNLOAD_CALLBACK;
    //
    // Filled by verifier engine
    //
    VerifierImage: PWSTR;
    VerifierFlags: DWORD;
    VerifierDebug: DWORD;

    RtlpGetStackTraceAddress: PVOID;
    RtlpDebugPageHeapCreate: PVOID;
    RtlpDebugPageHeapDestroy: PVOID;

    //
    // Filled by verifier provider DLL
    // 
    
    ProviderNtdllHeapFreeCallback: RTL_VERIFIER_NTDLLHEAPFREE_CALLBACK;
  end;
  {$EXTERNALSYM _RTL_VERIFIER_PROVIDER_DESCRIPTOR}
  RTL_VERIFIER_PROVIDER_DESCRIPTOR = _RTL_VERIFIER_PROVIDER_DESCRIPTOR;
  {$EXTERNALSYM RTL_VERIFIER_PROVIDER_DESCRIPTOR}
  TRtlVerifierProviderDescriptor = RTL_VERIFIER_PROVIDER_DESCRIPTOR;
  PRtlVerifierProviderDescriptor = PRTL_VERIFIER_PROVIDER_DESCRIPTOR;

//
// Application verifier standard flags
//

const
  // todo externalsym
  RTL_VRF_FLG_FULL_PAGE_HEAP                 = $00000001;
  RTL_VRF_FLG_RESERVED_DONOTUSE              = $00000002; // old RTL_VRF_FLG_LOCK_CHECKS
  RTL_VRF_FLG_HANDLE_CHECKS                  = $00000004;
  RTL_VRF_FLG_STACK_CHECKS                   = $00000008;
  RTL_VRF_FLG_APPCOMPAT_CHECKS               = $00000010;
  RTL_VRF_FLG_TLS_CHECKS                     = $00000020;
  RTL_VRF_FLG_DIRTY_STACKS                   = $00000040;
  RTL_VRF_FLG_RPC_CHECKS                     = $00000080;
  RTL_VRF_FLG_COM_CHECKS                     = $00000100;
  RTL_VRF_FLG_DANGEROUS_APIS                 = $00000200;
  RTL_VRF_FLG_RACE_CHECKS                    = $00000400;
  RTL_VRF_FLG_DEADLOCK_CHECKS                = $00000800;
  RTL_VRF_FLG_FIRST_CHANCE_EXCEPTION_CHECKS  = $00001000;
  RTL_VRF_FLG_VIRTUAL_MEM_CHECKS             = $00002000;
  RTL_VRF_FLG_ENABLE_LOGGING                 = $00004000;
  RTL_VRF_FLG_FAST_FILL_HEAP                 = $00008000;
  RTL_VRF_FLG_VIRTUAL_SPACE_TRACKING         = $00010000;
  RTL_VRF_FLG_ENABLED_SYSTEM_WIDE            = $00020000;
  RTL_VRF_FLG_MISCELLANEOUS_CHECKS           = $00020000;
  RTL_VRF_FLG_LOCK_CHECKS                    = $00040000;  

//
// Application verifier standard stop codes
//

  APPLICATION_VERIFIER_INTERNAL_ERROR    = DWORD($80000000);
  {$EXTERNALSYM APPLICATION_VERIFIER_INTERNAL_ERROR}
  APPLICATION_VERIFIER_INTERNAL_WARNING  = $40000000;
  {$EXTERNALSYM APPLICATION_VERIFIER_INTERNAL_WARNING}
  APPLICATION_VERIFIER_NO_BREAK          = $20000000;
  {$EXTERNALSYM APPLICATION_VERIFIER_NO_BREAK}
  APPLICATION_VERIFIER_CONTINUABLE_BREAK = $10000000;
  {$EXTERNALSYM APPLICATION_VERIFIER_CONTINUABLE_BREAK}

  APPLICATION_VERIFIER_UNKNOWN_ERROR         = $0001;
  {$EXTERNALSYM APPLICATION_VERIFIER_UNKNOWN_ERROR}
  APPLICATION_VERIFIER_ACCESS_VIOLATION      = $0002;
  {$EXTERNALSYM APPLICATION_VERIFIER_ACCESS_VIOLATION}
  APPLICATION_VERIFIER_UNSYNCHRONIZED_ACCESS = $0003;
  {$EXTERNALSYM APPLICATION_VERIFIER_UNSYNCHRONIZED_ACCESS}
  APPLICATION_VERIFIER_EXTREME_SIZE_REQUEST  = $0004;
  {$EXTERNALSYM APPLICATION_VERIFIER_EXTREME_SIZE_REQUEST}
  APPLICATION_VERIFIER_BAD_HEAP_HANDLE       = $0005;
  {$EXTERNALSYM APPLICATION_VERIFIER_BAD_HEAP_HANDLE}
  APPLICATION_VERIFIER_SWITCHED_HEAP_HANDLE  = $0006;
  {$EXTERNALSYM APPLICATION_VERIFIER_SWITCHED_HEAP_HANDLE}
  APPLICATION_VERIFIER_DOUBLE_FREE           = $0007;
  {$EXTERNALSYM APPLICATION_VERIFIER_DOUBLE_FREE}
  APPLICATION_VERIFIER_CORRUPTED_HEAP_BLOCK  = $0008;
  {$EXTERNALSYM APPLICATION_VERIFIER_CORRUPTED_HEAP_BLOCK}
  APPLICATION_VERIFIER_DESTROY_PROCESS_HEAP  = $0009;
  {$EXTERNALSYM APPLICATION_VERIFIER_DESTROY_PROCESS_HEAP}
  APPLICATION_VERIFIER_UNEXPECTED_EXCEPTION  = $000A;
  {$EXTERNALSYM APPLICATION_VERIFIER_UNEXPECTED_EXCEPTION}
  APPLICATION_VERIFIER_STACK_OVERFLOW        = $000B;
  {$EXTERNALSYM APPLICATION_VERIFIER_STACK_OVERFLOW}

  APPLICATION_VERIFIER_TERMINATE_THREAD_CALL = $0100;
  {$EXTERNALSYM APPLICATION_VERIFIER_TERMINATE_THREAD_CALL}
  APPLICATION_VERIFIER_INVALID_EXIT_PROCESS_CALL = $0101;
  {$EXTERNALSYM APPLICATION_VERIFIER_INVALID_EXIT_PROCESS_CALL}

  APPLICATION_VERIFIER_EXIT_THREAD_OWNS_LOCK        = $0200;
  {$EXTERNALSYM APPLICATION_VERIFIER_EXIT_THREAD_OWNS_LOCK}
  APPLICATION_VERIFIER_LOCK_IN_UNLOADED_DLL         = $0201;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_IN_UNLOADED_DLL}
  APPLICATION_VERIFIER_LOCK_IN_FREED_HEAP           = $0202;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_IN_FREED_HEAP}
  APPLICATION_VERIFIER_LOCK_DOUBLE_INITIALIZE       = $0203;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_DOUBLE_INITIALIZE}
  APPLICATION_VERIFIER_LOCK_IN_FREED_MEMORY         = $0204;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_IN_FREED_MEMORY}
  APPLICATION_VERIFIER_LOCK_CORRUPTED               = $0205;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_CORRUPTED}
  APPLICATION_VERIFIER_LOCK_INVALID_OWNER           = $0206;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_INVALID_OWNER}
  APPLICATION_VERIFIER_LOCK_INVALID_RECURSION_COUNT = $0207;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_INVALID_RECURSION_COUNT}
  APPLICATION_VERIFIER_LOCK_INVALID_LOCK_COUNT      = $0208;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_INVALID_LOCK_COUNT}
  APPLICATION_VERIFIER_LOCK_OVER_RELEASED           = $0209;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_OVER_RELEASED}
  APPLICATION_VERIFIER_LOCK_NOT_INITIALIZED         = $0210;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_NOT_INITIALIZED}
  APPLICATION_VERIFIER_LOCK_ALREADY_INITIALIZED     = $0211;
  {$EXTERNALSYM APPLICATION_VERIFIER_LOCK_ALREADY_INITIALIZED}

  APPLICATION_VERIFIER_INVALID_HANDLE      = $0300;
  {$EXTERNALSYM APPLICATION_VERIFIER_INVALID_HANDLE}
  APPLICATION_VERIFIER_INVALID_TLS_VALUE   = $0301;
  {$EXTERNALSYM APPLICATION_VERIFIER_INVALID_TLS_VALUE}
  APPLICATION_VERIFIER_INCORRECT_WAIT_CALL = $0302;
  {$EXTERNALSYM APPLICATION_VERIFIER_INCORRECT_WAIT_CALL}
  APPLICATION_VERIFIER_NULL_HANDLE         = $0303;
  {$EXTERNALSYM APPLICATION_VERIFIER_NULL_HANDLE}
  APPLICATION_VERIFIER_WAIT_IN_DLLMAIN     = $0304;
  {$EXTERNALSYM APPLICATION_VERIFIER_WAIT_IN_DLLMAIN}

  APPLICATION_VERIFIER_COM_ERROR                   = $0400;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_ERROR}
  APPLICATION_VERIFIER_COM_API_IN_DLLMAIN          = $0401;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_API_IN_DLLMAIN}
  APPLICATION_VERIFIER_COM_UNHANDLED_EXCEPTION     = $0402;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_UNHANDLED_EXCEPTION}
  APPLICATION_VERIFIER_COM_UNBALANCED_COINIT       = $0403;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_UNBALANCED_COINIT}
  APPLICATION_VERIFIER_COM_UNBALANCED_OLEINIT      = $0404;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_UNBALANCED_OLEINIT}
  APPLICATION_VERIFIER_COM_UNBALANCED_SWC          = $0405;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_UNBALANCED_SWC}
  APPLICATION_VERIFIER_COM_NULL_DACL               = $0406;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_NULL_DACL}
  APPLICATION_VERIFIER_COM_UNSAFE_IMPERSONATION    = $0407;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_UNSAFE_IMPERSONATION}
  APPLICATION_VERIFIER_COM_SMUGGLED_WRAPPER        = $0408;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_SMUGGLED_WRAPPER}
  APPLICATION_VERIFIER_COM_SMUGGLED_PROXY          = $0409;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_SMUGGLED_PROXY}
  APPLICATION_VERIFIER_COM_CF_SUCCESS_WITH_NULL    = $040A;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_CF_SUCCESS_WITH_NULL}
  APPLICATION_VERIFIER_COM_GCO_SUCCESS_WITH_NULL   = $040B;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_GCO_SUCCESS_WITH_NULL}
  APPLICATION_VERIFIER_COM_OBJECT_IN_FREED_MEMORY  = $040C;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_OBJECT_IN_FREED_MEMORY}
  APPLICATION_VERIFIER_COM_OBJECT_IN_UNLOADED_DLL  = $040D;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_OBJECT_IN_UNLOADED_DLL}
  APPLICATION_VERIFIER_COM_VTBL_IN_FREED_MEMORY    = $040E;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_VTBL_IN_FREED_MEMORY}
  APPLICATION_VERIFIER_COM_VTBL_IN_UNLOADED_DLL    = $040F;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_VTBL_IN_UNLOADED_DLL}
  APPLICATION_VERIFIER_COM_HOLDING_LOCKS_ON_CALL   = $0410;
  {$EXTERNALSYM APPLICATION_VERIFIER_COM_HOLDING_LOCKS_ON_CALL}

  APPLICATION_VERIFIER_RPC_ERROR                  = $0500;
  {$EXTERNALSYM APPLICATION_VERIFIER_RPC_ERROR}

  APPLICATION_VERIFIER_INVALID_FREEMEM            = $0600;
  {$EXTERNALSYM APPLICATION_VERIFIER_INVALID_FREEMEM}
  APPLICATION_VERIFIER_INVALID_ALLOCMEM           = $0601;
  {$EXTERNALSYM APPLICATION_VERIFIER_INVALID_ALLOCMEM}
  APPLICATION_VERIFIER_INVALID_MAPVIEW            = $0602;
  {$EXTERNALSYM APPLICATION_VERIFIER_INVALID_MAPVIEW}
  APPLICATION_VERIFIER_PROBE_INVALID_ADDRESS        = $0603;
  {$EXTERNALSYM APPLICATION_VERIFIER_PROBE_INVALID_ADDRESS}
  APPLICATION_VERIFIER_PROBE_FREE_MEM               = $0604;
  {$EXTERNALSYM APPLICATION_VERIFIER_PROBE_FREE_MEM}
  APPLICATION_VERIFIER_PROBE_GUARD_PAGE             = $0605;
  {$EXTERNALSYM APPLICATION_VERIFIER_PROBE_GUARD_PAGE}
  APPLICATION_VERIFIER_PROBE_NULL                   = $0606;
  {$EXTERNALSYM APPLICATION_VERIFIER_PROBE_NULL}
  APPLICATION_VERIFIER_PROBE_INVALID_START_OR_SIZE  = $0607;
  {$EXTERNALSYM APPLICATION_VERIFIER_PROBE_INVALID_START_OR_SIZE}


(* TODO
#define VERIFIER_STOP(Code, Msg, P1, S1, P2, S2, P3, S3, P4, S4) {  \
        RtlApplicationVerifierStop ((Code),                         \
                                    (Msg),                          \
                                    (ULONG_PTR)(P1),(S1),           \
                                    (ULONG_PTR)(P2),(S2),           \
                                    (ULONG_PTR)(P3),(S3),           \
                                    (ULONG_PTR)(P4),(S4));          \
  }

VOID NTAPI
RtlApplicationVerifierStop (
    ULONG_PTR Code,
    PCHAR Message,
    ULONG_PTR Param1, PCHAR Description1,
    ULONG_PTR Param2, PCHAR Description2,
    ULONG_PTR Param3, PCHAR Description3,
    ULONG_PTR Param4, PCHAR Description4
    );
*)

type
  PVECTORED_EXCEPTION_HANDLER = function (ExceptionInfo: PEXCEPTION_POINTERS): LONG; stdcall;
  {$EXTERNALSYM PVECTORED_EXCEPTION_HANDLER}
  PVectoredExceptionHandler = PVECTORED_EXCEPTION_HANDLER;

const
  SEF_DACL_AUTO_INHERIT             = $01;
  {$EXTERNALSYM SEF_DACL_AUTO_INHERIT}
  SEF_SACL_AUTO_INHERIT             = $02;
  {$EXTERNALSYM SEF_SACL_AUTO_INHERIT}
  SEF_DEFAULT_DESCRIPTOR_FOR_OBJECT = $04;
  {$EXTERNALSYM SEF_DEFAULT_DESCRIPTOR_FOR_OBJECT}
  SEF_AVOID_PRIVILEGE_CHECK         = $08;
  {$EXTERNALSYM SEF_AVOID_PRIVILEGE_CHECK}
  SEF_AVOID_OWNER_CHECK             = $10;
  {$EXTERNALSYM SEF_AVOID_OWNER_CHECK}
  SEF_DEFAULT_OWNER_FROM_PARENT     = $20;
  {$EXTERNALSYM SEF_DEFAULT_OWNER_FROM_PARENT}
  SEF_DEFAULT_GROUP_FROM_PARENT     = $40;
  {$EXTERNALSYM SEF_DEFAULT_GROUP_FROM_PARENT}

type
  _HEAP_INFORMATION_CLASS = (HeapCompatibilityInformation);
  {$EXTERNALSYM _HEAP_INFORMATION_CLASS}
  HEAP_INFORMATION_CLASS = _HEAP_INFORMATION_CLASS;
  {$EXTERNALSYM HEAP_INFORMATION_CLASS}
  THeapInformationClass = HEAP_INFORMATION_CLASS;

{ TODO
DWORD NTAPI
RtlSetHeapInformation (
    IN PVOID HeapHandle,
    IN HEAP_INFORMATION_CLASS HeapInformationClass,
    IN PVOID HeapInformation OPTIONAL,
    IN SIZE_T HeapInformationLength OPTIONAL
    );

DWORD NTAPI
RtlQueryHeapInformation (
    IN PVOID HeapHandle,
    IN HEAP_INFORMATION_CLASS HeapInformationClass,
    OUT PVOID HeapInformation OPTIONAL,
    IN SIZE_T HeapInformationLength OPTIONAL,
    OUT PSIZE_T ReturnLength OPTIONAL
    );

//
//  Multiple alloc-free APIS
//

DWORD
NTAPI
RtlMultipleAllocateHeap (
    IN PVOID HeapHandle,
    IN DWORD Flags,
    IN SIZE_T Size,
    IN DWORD Count,
    OUT PVOID * Array
    );

DWORD
NTAPI
RtlMultipleFreeHeap (
    IN PVOID HeapHandle,
    IN DWORD Flags,
    IN DWORD Count,
    OUT PVOID * Array
    );
}

const
  WT_EXECUTEDEFAULT                 = $00000000;
  {$EXTERNALSYM WT_EXECUTEDEFAULT}
  WT_EXECUTEINIOTHREAD              = $00000001;
  {$EXTERNALSYM WT_EXECUTEINIOTHREAD}
  WT_EXECUTEINUITHREAD              = $00000002;
  {$EXTERNALSYM WT_EXECUTEINUITHREAD}
  WT_EXECUTEINWAITTHREAD            = $00000004;
  {$EXTERNALSYM WT_EXECUTEINWAITTHREAD}
  WT_EXECUTEONLYONCE                = $00000008;
  {$EXTERNALSYM WT_EXECUTEONLYONCE}
  WT_EXECUTEINTIMERTHREAD           = $00000020;
  {$EXTERNALSYM WT_EXECUTEINTIMERTHREAD}
  WT_EXECUTELONGFUNCTION            = $00000010;
  {$EXTERNALSYM WT_EXECUTELONGFUNCTION}
  WT_EXECUTEINPERSISTENTIOTHREAD    = $00000040;
  {$EXTERNALSYM WT_EXECUTEINPERSISTENTIOTHREAD}
  WT_EXECUTEINPERSISTENTTHREAD      = $00000080;
  {$EXTERNALSYM WT_EXECUTEINPERSISTENTTHREAD}
  WT_TRANSFER_IMPERSONATION         = $00000100;
  {$EXTERNALSYM WT_TRANSFER_IMPERSONATION}

function WT_SET_MAX_THREADPOOL_THREADS(var Flags: DWORD; Limit: DWORD): DWORD;
{$EXTERNALSYM WT_SET_MAX_THREADPOOL_THREADS}

type
  WAITORTIMERCALLBACKFUNC = procedure (P: PVOID; B: ByteBool); stdcall;
  {$EXTERNALSYM WAITORTIMERCALLBACKFUNC}
  WORKERCALLBACKFUNC = procedure (P: PVOID); stdcall;
  {$EXTERNALSYM WORKERCALLBACKFUNC}
  APC_CALLBACK_FUNCTION = procedure (D: DWORD; P1, P2: PVOID); stdcall;
  {$EXTERNALSYM APC_CALLBACK_FUNCTION}

const
  WT_EXECUTEINLONGTHREAD = $00000010;
  {$EXTERNALSYM WT_EXECUTEINLONGTHREAD}
  WT_EXECUTEDELETEWAIT   = $00000008;
  {$EXTERNALSYM WT_EXECUTEDELETEWAIT}

type
  _ACTIVATION_CONTEXT_INFO_CLASS = DWORD;
  {$EXTERNALSYM _ACTIVATION_CONTEXT_INFO_CLASS}
  ACTIVATION_CONTEXT_INFO_CLASS = _ACTIVATION_CONTEXT_INFO_CLASS;
  {$EXTERNALSYM ACTIVATION_CONTEXT_INFO_CLASS}
  TActivationContextInfoClass = ACTIVATION_CONTEXT_INFO_CLASS;

const
  ActivationContextBasicInformation                       = 1;
  {$EXTERNALSYM ActivationContextBasicInformation}
  ActivationContextDetailedInformation                    = 2;
  {$EXTERNALSYM ActivationContextDetailedInformation}
  AssemblyDetailedInformationInActivationContxt           = 3;
  {$EXTERNALSYM AssemblyDetailedInformationInActivationContxt}
  FileInformationInAssemblyOfAssemblyInActivationContxt   = 4;
  {$EXTERNALSYM FileInformationInAssemblyOfAssemblyInActivationContxt}
  MaxActivationContextInfoClass                           = 5;
  {$EXTERNALSYM MaxActivationContextInfoClass}

type
  PACTIVATION_CONTEXT_QUERY_INDEX = ^ACTIVATION_CONTEXT_QUERY_INDEX;
  {$EXTERNALSYM PACTIVATION_CONTEXT_QUERY_INDEX}
  _ACTIVATION_CONTEXT_QUERY_INDEX = record
    ulAssemblyIndex: DWORD;
    ulFileIndexInAssembly: DWORD;
  end;
  {$EXTERNALSYM _ACTIVATION_CONTEXT_QUERY_INDEX}
  ACTIVATION_CONTEXT_QUERY_INDEX = _ACTIVATION_CONTEXT_QUERY_INDEX;
  {$EXTERNALSYM ACTIVATION_CONTEXT_QUERY_INDEX}
  TActivationContextQueryIndex = ACTIVATION_CONTEXT_QUERY_INDEX;
  PActivationContextQueryIndex = PACTIVATION_CONTEXT_QUERY_INDEX;

const
  ACTIVATION_CONTEXT_PATH_TYPE_NONE        = (1);
  {$EXTERNALSYM ACTIVATION_CONTEXT_PATH_TYPE_NONE}
  ACTIVATION_CONTEXT_PATH_TYPE_WIN32_FILE  = (2);
  {$EXTERNALSYM ACTIVATION_CONTEXT_PATH_TYPE_WIN32_FILE}
  ACTIVATION_CONTEXT_PATH_TYPE_URL         = (3);
  {$EXTERNALSYM ACTIVATION_CONTEXT_PATH_TYPE_URL}
  ACTIVATION_CONTEXT_PATH_TYPE_ASSEMBLYREF = (4);
  {$EXTERNALSYM ACTIVATION_CONTEXT_PATH_TYPE_ASSEMBLYREF}

type
  PASSEMBLY_FILE_DETAILED_INFORMATION = ^ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION;
  {$EXTERNALSYM PASSEMBLY_FILE_DETAILED_INFORMATION}
  _ASSEMBLY_FILE_DETAILED_INFORMATION = record
    ulFlags: DWORD;
    ulFilenameLength: DWORD;
    ulPathLength: DWORD;
    lpFileName: LPCWSTR;
    lpFilePath: LPCWSTR;
  end;
  {$EXTERNALSYM _ASSEMBLY_FILE_DETAILED_INFORMATION}
  ASSEMBLY_FILE_DETAILED_INFORMATION = _ASSEMBLY_FILE_DETAILED_INFORMATION;
  {$EXTERNALSYM ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION}
  PCASSEMBLY_FILE_DETAILED_INFORMATION = PASSEMBLY_FILE_DETAILED_INFORMATION;
  {$EXTERNALSYM PCASSEMBLY_FILE_DETAILED_INFORMATION}
  TAssemblyFileDetailedInformation = ASSEMBLY_FILE_DETAILED_INFORMATION;
  PAssemblyFileDetailedInformation = PASSEMBLY_FILE_DETAILED_INFORMATION;

//
// compatibility with old names
// The new names use "file" consistently.
//

  _ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION = _ASSEMBLY_FILE_DETAILED_INFORMATION;
  {$EXTERNALSYM _ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION}
  ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION = ASSEMBLY_FILE_DETAILED_INFORMATION;
  {$EXTERNALSYM ASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION}
  PASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION = PASSEMBLY_FILE_DETAILED_INFORMATION;
  {$EXTERNALSYM PASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION}
  PCASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION = PCASSEMBLY_FILE_DETAILED_INFORMATION;
  {$EXTERNALSYM PCASSEMBLY_DLL_REDIRECTION_DETAILED_INFORMATION}
  TAssemblyDllRedirectionDetailedInformation = TAssemblyFileDetailedInformation;
  PAssemblyDllRedirectionDetailedInformation = PAssemblyFileDetailedInformation;

  PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION = ^ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION;
  {$EXTERNALSYM PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION}
  _ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION = record
    ulFlags: DWORD;
    ulEncodedAssemblyIdentityLength: DWORD; // in bytes
    ulManifestPathType: DWORD;              // ACTIVATION_CONTEXT_PATH_TYPE_*
    ulManifestPathLength: DWORD;            // in bytes
    liManifestLastWriteTime: LARGE_INTEGER; // FILETIME
    ulPolicyPathType: DWORD;                // ACTIVATION_CONTEXT_PATH_TYPE_*
    ulPolicyPathLength: DWORD;              // in bytes
    liPolicyLastWriteTime: LARGE_INTEGER;   // FILETIME
    ulMetadataSatelliteRosterIndex: DWORD;
    ulManifestVersionMajor: DWORD;          // 1
    ulManifestVersionMinor: DWORD;          // 0
    ulPolicyVersionMajor: DWORD;            // 0
    ulPolicyVersionMinor: DWORD;            // 0
    ulAssemblyDirectoryNameLength: DWORD;   // in bytes
    lpAssemblyEncodedAssemblyIdentity: LPCWSTR;
    lpAssemblyManifestPath: LPCWSTR;
    lpAssemblyPolicyPath: LPCWSTR;
    lpAssemblyDirectoryName: LPCWSTR;
    ulFileCount: DWORD;
  end;
  {$EXTERNALSYM _ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION}
  ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION = _ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION;
  {$EXTERNALSYM ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION}
  TActivationContextAssemblyDetailedInformation = ACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION;
  PActivationContextAssemblyDetailedInformation = PACTIVATION_CONTEXT_ASSEMBLY_DETAILED_INFORMATION;

  PACTIVATION_CONTEXT_DETAILED_INFORMATION = ^ACTIVATION_CONTEXT_DETAILED_INFORMATION;
  {$EXTERNALSYM PACTIVATION_CONTEXT_DETAILED_INFORMATION}
  _ACTIVATION_CONTEXT_DETAILED_INFORMATION = record
    dwFlags: DWORD;
    ulFormatVersion: DWORD;
    ulAssemblyCount: DWORD;
    ulRootManifestPathType: DWORD;
    ulRootManifestPathChars: DWORD;
    ulRootConfigurationPathType: DWORD;
    ulRootConfigurationPathChars: DWORD;
    ulAppDirPathType: DWORD;
    ulAppDirPathChars: DWORD;
    lpRootManifestPath: LPCWSTR;
    lpRootConfigurationPath: LPCWSTR;
    lpAppDirPath: LPCWSTR;
  end;
  {$EXTERNALSYM _ACTIVATION_CONTEXT_DETAILED_INFORMATION}
  ACTIVATION_CONTEXT_DETAILED_INFORMATION = _ACTIVATION_CONTEXT_DETAILED_INFORMATION;
  {$EXTERNALSYM ACTIVATION_CONTEXT_DETAILED_INFORMATION}
  TActivationContextDetailedInformation = ACTIVATION_CONTEXT_DETAILED_INFORMATION;
  PActivationContextDetailedInformation = PACTIVATION_CONTEXT_DETAILED_INFORMATION;

const
  DLL_PROCESS_ATTACH     = 1;
  {$EXTERNALSYM DLL_PROCESS_ATTACH}
  DLL_THREAD_ATTACH      = 2;
  {$EXTERNALSYM DLL_THREAD_ATTACH}
  DLL_THREAD_DETACH      = 3;
  {$EXTERNALSYM DLL_THREAD_DETACH}
  DLL_PROCESS_DETACH     = 0;
  {$EXTERNALSYM DLL_PROCESS_DETACH}
  DLL_PROCESS_VERIFIER   = 4;
  {$EXTERNALSYM DLL_PROCESS_VERIFIER}

//
// Defines for the READ flags for Eventlogging
//

  EVENTLOG_SEQUENTIAL_READ = $0001;
  {$EXTERNALSYM EVENTLOG_SEQUENTIAL_READ}
  EVENTLOG_SEEK_READ       = $0002;
  {$EXTERNALSYM EVENTLOG_SEEK_READ}
  EVENTLOG_FORWARDS_READ   = $0004;
  {$EXTERNALSYM EVENTLOG_FORWARDS_READ}
  EVENTLOG_BACKWARDS_READ  = $0008;
  {$EXTERNALSYM EVENTLOG_BACKWARDS_READ}

//
// The types of events that can be logged.
//

  EVENTLOG_SUCCESS          = $0000;
  {$EXTERNALSYM EVENTLOG_SUCCESS}
  EVENTLOG_ERROR_TYPE       = $0001;
  {$EXTERNALSYM EVENTLOG_ERROR_TYPE}
  EVENTLOG_WARNING_TYPE     = $0002;
  {$EXTERNALSYM EVENTLOG_WARNING_TYPE}
  EVENTLOG_INFORMATION_TYPE = $0004;
  {$EXTERNALSYM EVENTLOG_INFORMATION_TYPE}
  EVENTLOG_AUDIT_SUCCESS    = $0008;
  {$EXTERNALSYM EVENTLOG_AUDIT_SUCCESS}
  EVENTLOG_AUDIT_FAILURE    = $0010;
  {$EXTERNALSYM EVENTLOG_AUDIT_FAILURE}

//
// Defines for the WRITE flags used by Auditing for paired events
// These are not implemented in Product 1
//

  EVENTLOG_START_PAIRED_EVENT    = $0001;
  {$EXTERNALSYM EVENTLOG_START_PAIRED_EVENT}
  EVENTLOG_END_PAIRED_EVENT      = $0002;
  {$EXTERNALSYM EVENTLOG_END_PAIRED_EVENT}
  EVENTLOG_END_ALL_PAIRED_EVENTS = $0004;
  {$EXTERNALSYM EVENTLOG_END_ALL_PAIRED_EVENTS}
  EVENTLOG_PAIRED_EVENT_ACTIVE   = $0008;
  {$EXTERNALSYM EVENTLOG_PAIRED_EVENT_ACTIVE}
  EVENTLOG_PAIRED_EVENT_INACTIVE = $0010;
  {$EXTERNALSYM EVENTLOG_PAIRED_EVENT_INACTIVE}

//
// Structure that defines the header of the Eventlog record. This is the
// fixed-sized portion before all the variable-length strings, binary
// data and pad bytes.
//
// TimeGenerated is the time it was generated at the client.
// TimeWritten is the time it was put into the log at the server end.
//

type
  PEventlogrecord = ^EVENTLOGRECORD;
  _EVENTLOGRECORD = record
    Length: DWORD; // Length of full record
    Reserved: DWORD; // Used by the service
    RecordNumber: DWORD; // Absolute record number
    TimeGenerated: DWORD; // Seconds since 1-1-1970
    TimeWritten: DWORD; // Seconds since 1-1-1970
    EventID: DWORD;
    EventType: Word;
    NumStrings: Word;
    EventCategory: Word;
    ReservedFlags: Word; // For use with paired events (auditing)
    ClosingRecordNumber: DWORD; // For use with paired events (auditing)
    StringOffset: DWORD; // Offset from beginning of record
    UserSidLength: DWORD;
    UserSidOffset: DWORD;
    DataLength: DWORD;
    DataOffset: DWORD; // Offset from beginning of record
    //
    // Then follow:
    //
    // WCHAR SourceName[]
    // WCHAR Computername[]
    // SID   UserSid
    // WCHAR Strings[]
    // BYTE  Data[]
    // CHAR  Pad[]
    // DWORD Length;
    //
  end;
  {$EXTERNALSYM _EVENTLOGRECORD}
  EVENTLOGRECORD = _EVENTLOGRECORD;
  {$EXTERNALSYM EVENTLOGRECORD}
  TEventlogrecord = EVENTLOGRECORD;

const
  MAXLOGICALLOGNAMESIZE = 256;
  {$EXTERNALSYM MAXLOGICALLOGNAMESIZE}

type
  PEventsForLogFile = ^EVENTSFORLOGFILE;
  _EVENTSFORLOGFILE = record
    ulSize: DWORD;
    szLogicalLogFile: array [0..MAXLOGICALLOGNAMESIZE - 1] of WCHAR; // name of the logical file-security/application/system
    ulNumRecords: DWORD;
    pEventLogRecords: array [0..0] of EVENTLOGRECORD;
  end;
  {$EXTERNALSYM _EVENTSFORLOGFILE}
  EVENTSFORLOGFILE = _EVENTSFORLOGFILE;
  {$EXTERNALSYM EVENTSFORLOGFILE}
  TEventsForLogFile = EVENTSFORLOGFILE;

  PPackedEventInfo = ^PACKEDEVENTINFO;
  _PACKEDEVENTINFO = record
    ulSize: DWORD;                    // total size of the structure
    ulNumEventsForLogFile: DWORD;     // number of EventsForLogFile structure that follow
    ulOffsets: array [0..0] of DWORD; // the offsets from the start of this structure to the EVENTSFORLOGFILE structure
  end;
  {$EXTERNALSYM _PACKEDEVENTINFO}
  PACKEDEVENTINFO = _PACKEDEVENTINFO;
  {$EXTERNALSYM PACKEDEVENTINFO}
  TPackedEventInfo = PACKEDEVENTINFO;

//
// Registry Specific Access Rights.
//

const
  KEY_QUERY_VALUE        = ($0001);
  {$EXTERNALSYM KEY_QUERY_VALUE}
  KEY_SET_VALUE          = ($0002);
  {$EXTERNALSYM KEY_SET_VALUE}
  KEY_CREATE_SUB_KEY     = ($0004);
  {$EXTERNALSYM KEY_CREATE_SUB_KEY}
  KEY_ENUMERATE_SUB_KEYS = ($0008);
  {$EXTERNALSYM KEY_ENUMERATE_SUB_KEYS}
  KEY_NOTIFY             = ($0010);
  {$EXTERNALSYM KEY_NOTIFY}
  KEY_CREATE_LINK        = ($0020);
  {$EXTERNALSYM KEY_CREATE_LINK}
  KEY_WOW64_32KEY        = ($0200);
  {$EXTERNALSYM KEY_WOW64_32KEY}
  KEY_WOW64_64KEY        = ($0100);
  {$EXTERNALSYM KEY_WOW64_64KEY}
  KEY_WOW64_RES          = ($0300);
  {$EXTERNALSYM KEY_WOW64_RES}

  KEY_READ = STANDARD_RIGHTS_READ or KEY_QUERY_VALUE or KEY_ENUMERATE_SUB_KEYS or
    KEY_NOTIFY  and (not SYNCHRONIZE);
  {$EXTERNALSYM KEY_READ}

  KEY_WRITE = STANDARD_RIGHTS_WRITE or KEY_SET_VALUE or KEY_CREATE_SUB_KEY and
    (not SYNCHRONIZE);
  {$EXTERNALSYM KEY_WRITE}

  KEY_EXECUTE = KEY_READ and  (not SYNCHRONIZE);
  {$EXTERNALSYM KEY_EXECUTE}

  KEY_ALL_ACCESS = STANDARD_RIGHTS_ALL or KEY_QUERY_VALUE or KEY_SET_VALUE or
    KEY_CREATE_SUB_KEY or KEY_ENUMERATE_SUB_KEYS or KEY_NOTIFY or
    KEY_CREATE_LINK and (not SYNCHRONIZE);
  {$EXTERNALSYM KEY_ALL_ACCESS}

//
// Open/Create Options
//

  REG_OPTION_RESERVED = ($00000000); // Parameter is reserved
  {$EXTERNALSYM REG_OPTION_RESERVED}

  REG_OPTION_NON_VOLATILE = ($00000000); // Key is preserved when system is rebooted
  {$EXTERNALSYM REG_OPTION_NON_VOLATILE}

  REG_OPTION_VOLATILE = ($00000001); // Key is not preserved when system is rebooted
  {$EXTERNALSYM REG_OPTION_VOLATILE}

  REG_OPTION_CREATE_LINK = ($00000002); // Created key is a symbolic link
  {$EXTERNALSYM REG_OPTION_CREATE_LINK}

  REG_OPTION_BACKUP_RESTORE = ($00000004); // open for backup or restore
  {$EXTERNALSYM REG_OPTION_BACKUP_RESTORE}
                                                    // special access rules
                                                    // privilege required

  REG_OPTION_OPEN_LINK = ($00000008); // Open symbolic link
  {$EXTERNALSYM REG_OPTION_OPEN_LINK}

  REG_LEGAL_OPTION = REG_OPTION_RESERVED or REG_OPTION_NON_VOLATILE or
    REG_OPTION_VOLATILE or REG_OPTION_CREATE_LINK or REG_OPTION_BACKUP_RESTORE or
    REG_OPTION_OPEN_LINK;
  {$EXTERNALSYM REG_LEGAL_OPTION}

//
// Key creation/open disposition
//

  REG_CREATED_NEW_KEY     = ($00000001); // New Registry Key created
  {$EXTERNALSYM REG_CREATED_NEW_KEY}
  REG_OPENED_EXISTING_KEY = ($00000002); // Existing Key opened
  {$EXTERNALSYM REG_OPENED_EXISTING_KEY}

//
// hive format to be used by Reg(Nt)SaveKeyEx
//

  REG_STANDARD_FORMAT    = 1;
  {$EXTERNALSYM REG_STANDARD_FORMAT}
  REG_LATEST_FORMAT      = 2;
  {$EXTERNALSYM REG_LATEST_FORMAT}
  REG_NO_COMPRESSION     = 4;
  {$EXTERNALSYM REG_NO_COMPRESSION}

//
// Key restore flags
//

  REG_WHOLE_HIVE_VOLATILE = ($00000001); // Restore whole hive volatile
  {$EXTERNALSYM REG_WHOLE_HIVE_VOLATILE}
  REG_REFRESH_HIVE        = ($00000002); // Unwind changes to last flush
  {$EXTERNALSYM REG_REFRESH_HIVE}
  REG_NO_LAZY_FLUSH       = ($00000004); // Never lazy flush this hive
  {$EXTERNALSYM REG_NO_LAZY_FLUSH}
  REG_FORCE_RESTORE       = ($00000008); // Force the restore process even when we have open handles on subkeys
  {$EXTERNALSYM REG_FORCE_RESTORE}

//
// Unload Flags
//

  REG_FORCE_UNLOAD = 1;
  {$EXTERNALSYM REG_FORCE_UNLOAD}

// end_ntddk end_wdm end_nthal

//
// Notify filter values
//

  REG_NOTIFY_CHANGE_NAME       = ($00000001); // Create or delete (child)
  {$EXTERNALSYM REG_NOTIFY_CHANGE_NAME}
  REG_NOTIFY_CHANGE_ATTRIBUTES = ($00000002);
  {$EXTERNALSYM REG_NOTIFY_CHANGE_ATTRIBUTES}
  REG_NOTIFY_CHANGE_LAST_SET   = ($00000004); // time stamp
  {$EXTERNALSYM REG_NOTIFY_CHANGE_LAST_SET}
  REG_NOTIFY_CHANGE_SECURITY   = ($00000008);
  {$EXTERNALSYM REG_NOTIFY_CHANGE_SECURITY}

  REG_LEGAL_CHANGE_FILTER = REG_NOTIFY_CHANGE_NAME or REG_NOTIFY_CHANGE_ATTRIBUTES or
    REG_NOTIFY_CHANGE_LAST_SET or REG_NOTIFY_CHANGE_SECURITY;
  {$EXTERNALSYM REG_LEGAL_CHANGE_FILTER}

//
//
// Predefined Value Types.
//

  REG_NONE      = ( 0 ); // No value type
  {$EXTERNALSYM REG_NONE}
  REG_SZ        = ( 1 ); // Unicode nul terminated string
  {$EXTERNALSYM REG_SZ}
  REG_EXPAND_SZ = ( 2 ); // Unicode nul terminated string
  {$EXTERNALSYM REG_EXPAND_SZ}
                                            // (with environment variable references)
  REG_BINARY                     = ( 3 ); // Free form binary
  {$EXTERNALSYM REG_BINARY}
  REG_DWORD                      = ( 4 ); // 32-bit number
  {$EXTERNALSYM REG_DWORD}
  REG_DWORD_LITTLE_ENDIAN        = ( 4 ); // 32-bit number (same as REG_DWORD)
  {$EXTERNALSYM REG_DWORD_LITTLE_ENDIAN}
  REG_DWORD_BIG_ENDIAN           = ( 5 ); // 32-bit number
  {$EXTERNALSYM REG_DWORD_BIG_ENDIAN}
  REG_LINK                       = ( 6 ); // Symbolic Link (unicode)
  {$EXTERNALSYM REG_LINK}
  REG_MULTI_SZ                   = ( 7 ); // Multiple Unicode strings
  {$EXTERNALSYM REG_MULTI_SZ}
  REG_RESOURCE_LIST              = ( 8 ); // Resource list in the resource map
  {$EXTERNALSYM REG_RESOURCE_LIST}
  REG_FULL_RESOURCE_DESCRIPTOR   = ( 9 ); // Resource list in the hardware description
  {$EXTERNALSYM REG_FULL_RESOURCE_DESCRIPTOR}
  REG_RESOURCE_REQUIREMENTS_LIST = ( 10 );
  {$EXTERNALSYM REG_RESOURCE_REQUIREMENTS_LIST}
  REG_QWORD                      = ( 11 ); // 64-bit number
  {$EXTERNALSYM REG_QWORD}
  REG_QWORD_LITTLE_ENDIAN        = ( 11 ); // 64-bit number (same as REG_QWORD)
  {$EXTERNALSYM REG_QWORD_LITTLE_ENDIAN}

//
// Service Types (Bit Mask)
//

  SERVICE_KERNEL_DRIVER      = $00000001;
  {$EXTERNALSYM SERVICE_KERNEL_DRIVER}
  SERVICE_FILE_SYSTEM_DRIVER = $00000002;
  {$EXTERNALSYM SERVICE_FILE_SYSTEM_DRIVER}
  SERVICE_ADAPTER            = $00000004;
  {$EXTERNALSYM SERVICE_ADAPTER}
  SERVICE_RECOGNIZER_DRIVER  = $00000008;
  {$EXTERNALSYM SERVICE_RECOGNIZER_DRIVER}

  SERVICE_DRIVER = SERVICE_KERNEL_DRIVER or SERVICE_FILE_SYSTEM_DRIVER or
    SERVICE_RECOGNIZER_DRIVER;
  {$EXTERNALSYM SERVICE_DRIVER}

  SERVICE_WIN32_OWN_PROCESS   = $00000010;
  {$EXTERNALSYM SERVICE_WIN32_OWN_PROCESS}
  SERVICE_WIN32_SHARE_PROCESS = $00000020;
  {$EXTERNALSYM SERVICE_WIN32_SHARE_PROCESS}

  SERVICE_WIN32 = SERVICE_WIN32_OWN_PROCESS or SERVICE_WIN32_SHARE_PROCESS;
  {$EXTERNALSYM SERVICE_WIN32}

  SERVICE_INTERACTIVE_PROCESS = $00000100;
  {$EXTERNALSYM SERVICE_INTERACTIVE_PROCESS}

  SERVICE_TYPE_ALL = SERVICE_WIN32 or SERVICE_ADAPTER or SERVICE_DRIVER or
    SERVICE_INTERACTIVE_PROCESS;
  {$EXTERNALSYM SERVICE_TYPE_ALL}

//
// Start Type
//

  SERVICE_BOOT_START   = $00000000;
  {$EXTERNALSYM SERVICE_BOOT_START}
  SERVICE_SYSTEM_START = $00000001;
  {$EXTERNALSYM SERVICE_SYSTEM_START}
  SERVICE_AUTO_START   = $00000002;
  {$EXTERNALSYM SERVICE_AUTO_START}
  SERVICE_DEMAND_START = $00000003;
  {$EXTERNALSYM SERVICE_DEMAND_START}
  SERVICE_DISABLED     = $00000004;
  {$EXTERNALSYM SERVICE_DISABLED}

//
// Error control type
//

  SERVICE_ERROR_IGNORE   = $00000000;
  {$EXTERNALSYM SERVICE_ERROR_IGNORE}
  SERVICE_ERROR_NORMAL   = $00000001;
  {$EXTERNALSYM SERVICE_ERROR_NORMAL}
  SERVICE_ERROR_SEVERE   = $00000002;
  {$EXTERNALSYM SERVICE_ERROR_SEVERE}
  SERVICE_ERROR_CRITICAL = $00000003;
  {$EXTERNALSYM SERVICE_ERROR_CRITICAL}

//
// Define the registry driver node enumerations
//

const

//SERVICE_NODE_TYPE

  DriverType               = SERVICE_KERNEL_DRIVER;
  FileSystemType           = SERVICE_FILE_SYSTEM_DRIVER;
  Win32ServiceOwnProcess   = SERVICE_WIN32_OWN_PROCESS;
  Win32ServiceShareProcess = SERVICE_WIN32_SHARE_PROCESS;
  AdapterType              = SERVICE_ADAPTER;
  RecognizerType           = SERVICE_RECOGNIZER_DRIVER;

//SERVICE_LOAD_TYPE

  BootLoad    = SERVICE_BOOT_START;
  SystemLoad  = SERVICE_SYSTEM_START;
  AutoLoad    = SERVICE_AUTO_START;
  DemandLoad  = SERVICE_DEMAND_START;
  DisableLoad = SERVICE_DISABLED;

//SERVICE_ERROR_TYPE

  IgnoreError   = SERVICE_ERROR_IGNORE;
  NormalError   = SERVICE_ERROR_NORMAL;
  SevereError   = SERVICE_ERROR_SEVERE;
  CriticalError = SERVICE_ERROR_CRITICAL;

//
// IOCTL_TAPE_ERASE definitions
//

type
  SERVICE_NODE_TYPE = DWORD;
  {$EXTERNALSYM SERVICE_NODE_TYPE}
  TServiceNodeType = SERVICE_NODE_TYPE;
  SERVICE_LOAD_TYPE = DWORD;
  {$EXTERNALSYM SERVICE_LOAD_TYPE}
  TServiceLoadType = SERVICE_LOAD_TYPE;
  SERVICE_ERROR_TYPE = DWORD;
  {$EXTERNALSYM SERVICE_ERROR_TYPE}
  TServiceErrorType = SERVICE_ERROR_TYPE;

const
  TAPE_ERASE_SHORT = 0;
  {$EXTERNALSYM TAPE_ERASE_SHORT}
  TAPE_ERASE_LONG  = 1;
  {$EXTERNALSYM TAPE_ERASE_LONG}

type
  PTAPE_ERASE = ^TAPE_ERASE;
  {$EXTERNALSYM PTAPE_ERASE}
  _TAPE_ERASE = record
    Type_: DWORD;
    Immediate: ByteBool;
  end;
  {$EXTERNALSYM _TAPE_ERASE}
  TAPE_ERASE = _TAPE_ERASE;
  {$EXTERNALSYM TAPE_ERASE}
  TTapeErase = TAPE_ERASE;
  PTapeErase = PTAPE_ERASE;

//
// IOCTL_TAPE_PREPARE definitions
//

const
  TAPE_LOAD    = 0;
  {$EXTERNALSYM TAPE_LOAD}
  TAPE_UNLOAD  = 1;
  {$EXTERNALSYM TAPE_UNLOAD}
  TAPE_TENSION = 2;
  {$EXTERNALSYM TAPE_TENSION}
  TAPE_LOCK    = 3;
  {$EXTERNALSYM TAPE_LOCK}
  TAPE_UNLOCK  = 4;
  {$EXTERNALSYM TAPE_UNLOCK}
  TAPE_FORMAT  = 5;
  {$EXTERNALSYM TAPE_FORMAT}

type
  PTAPE_PREPARE = ^TAPE_PREPARE;
  {$EXTERNALSYM PTAPE_PREPARE}
  _TAPE_PREPARE = record
    Operation: DWORD;
    Immediate: ByteBool;
  end;
  {$EXTERNALSYM _TAPE_PREPARE}
  TAPE_PREPARE = _TAPE_PREPARE;
  {$EXTERNALSYM TAPE_PREPARE}
  TTapePrepare = TAPE_PREPARE;
  PTapePrepare = PTAPE_PREPARE;

//
// IOCTL_TAPE_WRITE_MARKS definitions
//

const
  TAPE_SETMARKS        = 0;
  {$EXTERNALSYM TAPE_SETMARKS}
  TAPE_FILEMARKS       = 1;
  {$EXTERNALSYM TAPE_FILEMARKS}
  TAPE_SHORT_FILEMARKS = 2;
  {$EXTERNALSYM TAPE_SHORT_FILEMARKS}
  TAPE_LONG_FILEMARKS  = 3;
  {$EXTERNALSYM TAPE_LONG_FILEMARKS}

type
  PTAPE_WRITE_MARKS = ^TAPE_WRITE_MARKS;
  {$EXTERNALSYM PTAPE_WRITE_MARKS}
  _TAPE_WRITE_MARKS = record
    Type_: DWORD;
    Count: DWORD;
    Immediate: ByteBool;
  end;
  {$EXTERNALSYM _TAPE_WRITE_MARKS}
  TAPE_WRITE_MARKS = _TAPE_WRITE_MARKS;
  {$EXTERNALSYM TAPE_WRITE_MARKS}
  TTapeWriteMarks = TAPE_WRITE_MARKS;
  PTapeWriteMarks = PTAPE_WRITE_MARKS;

//
// IOCTL_TAPE_GET_POSITION definitions
//

const
  TAPE_ABSOLUTE_POSITION       = 0;
  {$EXTERNALSYM TAPE_ABSOLUTE_POSITION}
  TAPE_LOGICAL_POSITION        = 1;
  {$EXTERNALSYM TAPE_LOGICAL_POSITION}
  TAPE_PSEUDO_LOGICAL_POSITION = 2;
  {$EXTERNALSYM TAPE_PSEUDO_LOGICAL_POSITION}

type
  PTAPE_GET_POSITION = ^TAPE_GET_POSITION;
  {$EXTERNALSYM PTAPE_GET_POSITION}
  _TAPE_GET_POSITION = record
    Type_: DWORD;
    Partition: DWORD;
    Offset: LARGE_INTEGER;
  end;
  {$EXTERNALSYM _TAPE_GET_POSITION}
  TAPE_GET_POSITION = _TAPE_GET_POSITION;
  {$EXTERNALSYM TAPE_GET_POSITION}
  TTapeGetPosition = TAPE_GET_POSITION;
  PTapeGetPosition = PTAPE_GET_POSITION;

//
// IOCTL_TAPE_SET_POSITION definitions
//

const
  TAPE_REWIND                = 0;
  {$EXTERNALSYM TAPE_REWIND}
  TAPE_ABSOLUTE_BLOCK        = 1;
  {$EXTERNALSYM TAPE_ABSOLUTE_BLOCK}
  TAPE_LOGICAL_BLOCK         = 2;
  {$EXTERNALSYM TAPE_LOGICAL_BLOCK}
  TAPE_PSEUDO_LOGICAL_BLOCK  = 3;
  {$EXTERNALSYM TAPE_PSEUDO_LOGICAL_BLOCK}
  TAPE_SPACE_END_OF_DATA     = 4;
  {$EXTERNALSYM TAPE_SPACE_END_OF_DATA}
  TAPE_SPACE_RELATIVE_BLOCKS = 5;
  {$EXTERNALSYM TAPE_SPACE_RELATIVE_BLOCKS}
  TAPE_SPACE_FILEMARKS       = 6;
  {$EXTERNALSYM TAPE_SPACE_FILEMARKS}
  TAPE_SPACE_SEQUENTIAL_FMKS = 7;
  {$EXTERNALSYM TAPE_SPACE_SEQUENTIAL_FMKS}
  TAPE_SPACE_SETMARKS        = 8;
  {$EXTERNALSYM TAPE_SPACE_SETMARKS}
  TAPE_SPACE_SEQUENTIAL_SMKS = 9;
  {$EXTERNALSYM TAPE_SPACE_SEQUENTIAL_SMKS}

type
  PTAPE_SET_POSITION = ^TAPE_SET_POSITION;
  {$EXTERNALSYM PTAPE_SET_POSITION}
  _TAPE_SET_POSITION = record
    Method: DWORD;
    Partition: DWORD;
    Offset: LARGE_INTEGER;
    Immediate: ByteBool;
  end;
  {$EXTERNALSYM _TAPE_SET_POSITION}
  TAPE_SET_POSITION = _TAPE_SET_POSITION;
  {$EXTERNALSYM TAPE_SET_POSITION}
  TTapeSetPosition = TAPE_SET_POSITION;
  PTapeSetPosition = PTAPE_SET_POSITION;

//
// IOCTL_TAPE_GET_DRIVE_PARAMS definitions
//

//
// Definitions for FeaturesLow parameter
//

const
  TAPE_DRIVE_FIXED     = $00000001;
  {$EXTERNALSYM TAPE_DRIVE_FIXED}
  TAPE_DRIVE_SELECT    = $00000002;
  {$EXTERNALSYM TAPE_DRIVE_SELECT}
  TAPE_DRIVE_INITIATOR = $00000004;
  {$EXTERNALSYM TAPE_DRIVE_INITIATOR}

  TAPE_DRIVE_ERASE_SHORT     = $00000010;
  {$EXTERNALSYM TAPE_DRIVE_ERASE_SHORT}
  TAPE_DRIVE_ERASE_LONG      = $00000020;
  {$EXTERNALSYM TAPE_DRIVE_ERASE_LONG}
  TAPE_DRIVE_ERASE_BOP_ONLY  = $00000040;
  {$EXTERNALSYM TAPE_DRIVE_ERASE_BOP_ONLY}
  TAPE_DRIVE_ERASE_IMMEDIATE = $00000080;
  {$EXTERNALSYM TAPE_DRIVE_ERASE_IMMEDIATE}

  TAPE_DRIVE_TAPE_CAPACITY  = $00000100;
  {$EXTERNALSYM TAPE_DRIVE_TAPE_CAPACITY}
  TAPE_DRIVE_TAPE_REMAINING = $00000200;
  {$EXTERNALSYM TAPE_DRIVE_TAPE_REMAINING}
  TAPE_DRIVE_FIXED_BLOCK    = $00000400;
  {$EXTERNALSYM TAPE_DRIVE_FIXED_BLOCK}
  TAPE_DRIVE_VARIABLE_BLOCK = $00000800;
  {$EXTERNALSYM TAPE_DRIVE_VARIABLE_BLOCK}

  TAPE_DRIVE_WRITE_PROTECT = $00001000;
  {$EXTERNALSYM TAPE_DRIVE_WRITE_PROTECT}
  TAPE_DRIVE_EOT_WZ_SIZE   = $00002000;
  {$EXTERNALSYM TAPE_DRIVE_EOT_WZ_SIZE}

  TAPE_DRIVE_ECC         = $00010000;
  {$EXTERNALSYM TAPE_DRIVE_ECC}
  TAPE_DRIVE_COMPRESSION = $00020000;
  {$EXTERNALSYM TAPE_DRIVE_COMPRESSION}
  TAPE_DRIVE_PADDING     = $00040000;
  {$EXTERNALSYM TAPE_DRIVE_PADDING}
  TAPE_DRIVE_REPORT_SMKS = $00080000;
  {$EXTERNALSYM TAPE_DRIVE_REPORT_SMKS}

  TAPE_DRIVE_GET_ABSOLUTE_BLK = $00100000;
  {$EXTERNALSYM TAPE_DRIVE_GET_ABSOLUTE_BLK}
  TAPE_DRIVE_GET_LOGICAL_BLK  = $00200000;
  {$EXTERNALSYM TAPE_DRIVE_GET_LOGICAL_BLK}
  TAPE_DRIVE_SET_EOT_WZ_SIZE  = $00400000;
  {$EXTERNALSYM TAPE_DRIVE_SET_EOT_WZ_SIZE}

  TAPE_DRIVE_EJECT_MEDIA      = $01000000;
  {$EXTERNALSYM TAPE_DRIVE_EJECT_MEDIA}
  TAPE_DRIVE_CLEAN_REQUESTS   = $02000000;
  {$EXTERNALSYM TAPE_DRIVE_CLEAN_REQUESTS}
  TAPE_DRIVE_SET_CMP_BOP_ONLY = $04000000;
  {$EXTERNALSYM TAPE_DRIVE_SET_CMP_BOP_ONLY}

  TAPE_DRIVE_RESERVED_BIT = DWORD($80000000); // don't use this bit!
  {$EXTERNALSYM TAPE_DRIVE_RESERVED_BIT}
  //                                              //can't be a low features bit!
//                                              //reserved; high features only

//
// Definitions for FeaturesHigh parameter
//

  TAPE_DRIVE_LOAD_UNLOAD      = DWORD($80000001);
  {$EXTERNALSYM TAPE_DRIVE_LOAD_UNLOAD}
  TAPE_DRIVE_TENSION          = DWORD($80000002);
  {$EXTERNALSYM TAPE_DRIVE_TENSION}
  TAPE_DRIVE_LOCK_UNLOCK      = DWORD($80000004);
  {$EXTERNALSYM TAPE_DRIVE_LOCK_UNLOCK}
  TAPE_DRIVE_REWIND_IMMEDIATE = DWORD($80000008);
  {$EXTERNALSYM TAPE_DRIVE_REWIND_IMMEDIATE}

  TAPE_DRIVE_SET_BLOCK_SIZE  = DWORD($80000010);
  {$EXTERNALSYM TAPE_DRIVE_SET_BLOCK_SIZE}
  TAPE_DRIVE_LOAD_UNLD_IMMED = DWORD($80000020);
  {$EXTERNALSYM TAPE_DRIVE_LOAD_UNLD_IMMED}
  TAPE_DRIVE_TENSION_IMMED   = DWORD($80000040);
  {$EXTERNALSYM TAPE_DRIVE_TENSION_IMMED}
  TAPE_DRIVE_LOCK_UNLK_IMMED = DWORD($80000080);
  {$EXTERNALSYM TAPE_DRIVE_LOCK_UNLK_IMMED}

  TAPE_DRIVE_SET_ECC         = DWORD($80000100);
  {$EXTERNALSYM TAPE_DRIVE_SET_ECC}
  TAPE_DRIVE_SET_COMPRESSION = DWORD($80000200);
  {$EXTERNALSYM TAPE_DRIVE_SET_COMPRESSION}
  TAPE_DRIVE_SET_PADDING     = DWORD($80000400);
  {$EXTERNALSYM TAPE_DRIVE_SET_PADDING}
  TAPE_DRIVE_SET_REPORT_SMKS = DWORD($80000800);
  {$EXTERNALSYM TAPE_DRIVE_SET_REPORT_SMKS}

  TAPE_DRIVE_ABSOLUTE_BLK  = DWORD($80001000);
  {$EXTERNALSYM TAPE_DRIVE_ABSOLUTE_BLK}
  TAPE_DRIVE_ABS_BLK_IMMED = DWORD($80002000);
  {$EXTERNALSYM TAPE_DRIVE_ABS_BLK_IMMED}
  TAPE_DRIVE_LOGICAL_BLK   = DWORD($80004000);
  {$EXTERNALSYM TAPE_DRIVE_LOGICAL_BLK}
  TAPE_DRIVE_LOG_BLK_IMMED = DWORD($80008000);
  {$EXTERNALSYM TAPE_DRIVE_LOG_BLK_IMMED}

  TAPE_DRIVE_END_OF_DATA     = DWORD($80010000);
  {$EXTERNALSYM TAPE_DRIVE_END_OF_DATA}
  TAPE_DRIVE_RELATIVE_BLKS   = DWORD($80020000);
  {$EXTERNALSYM TAPE_DRIVE_RELATIVE_BLKS}
  TAPE_DRIVE_FILEMARKS       = DWORD($80040000);
  {$EXTERNALSYM TAPE_DRIVE_FILEMARKS}
  TAPE_DRIVE_SEQUENTIAL_FMKS = DWORD($80080000);
  {$EXTERNALSYM TAPE_DRIVE_SEQUENTIAL_FMKS}

  TAPE_DRIVE_SETMARKS         = DWORD($80100000);
  {$EXTERNALSYM TAPE_DRIVE_SETMARKS}
  TAPE_DRIVE_SEQUENTIAL_SMKS  = DWORD($80200000);
  {$EXTERNALSYM TAPE_DRIVE_SEQUENTIAL_SMKS}
  TAPE_DRIVE_REVERSE_POSITION = DWORD($80400000);
  {$EXTERNALSYM TAPE_DRIVE_REVERSE_POSITION}
  TAPE_DRIVE_SPACE_IMMEDIATE  = DWORD($80800000);
  {$EXTERNALSYM TAPE_DRIVE_SPACE_IMMEDIATE}

  TAPE_DRIVE_WRITE_SETMARKS   = DWORD($81000000);
  {$EXTERNALSYM TAPE_DRIVE_WRITE_SETMARKS}
  TAPE_DRIVE_WRITE_FILEMARKS  = DWORD($82000000);
  {$EXTERNALSYM TAPE_DRIVE_WRITE_FILEMARKS}
  TAPE_DRIVE_WRITE_SHORT_FMKS = DWORD($84000000);
  {$EXTERNALSYM TAPE_DRIVE_WRITE_SHORT_FMKS}
  TAPE_DRIVE_WRITE_LONG_FMKS  = DWORD($88000000);
  {$EXTERNALSYM TAPE_DRIVE_WRITE_LONG_FMKS}

  TAPE_DRIVE_WRITE_MARK_IMMED = DWORD($90000000);
  {$EXTERNALSYM TAPE_DRIVE_WRITE_MARK_IMMED}
  TAPE_DRIVE_FORMAT           = DWORD($A0000000);
  {$EXTERNALSYM TAPE_DRIVE_FORMAT}
  TAPE_DRIVE_FORMAT_IMMEDIATE = DWORD($C0000000);
  {$EXTERNALSYM TAPE_DRIVE_FORMAT_IMMEDIATE}
  TAPE_DRIVE_HIGH_FEATURES    = DWORD($80000000); // mask for high features flag
  {$EXTERNALSYM TAPE_DRIVE_HIGH_FEATURES}

type
  PTAPE_GET_DRIVE_PARAMETERS = ^TAPE_GET_DRIVE_PARAMETERS;
  {$EXTERNALSYM PTAPE_GET_DRIVE_PARAMETERS}
  _TAPE_GET_DRIVE_PARAMETERS = record
    ECC: ByteBool;
    Compression: ByteBool;
    DataPadding: ByteBool;
    ReportSetmarks: ByteBool;
    DefaultBlockSize: DWORD;
    MaximumBlockSize: DWORD;
    MinimumBlockSize: DWORD;
    MaximumPartitionCount: DWORD;
    FeaturesLow: DWORD;
    FeaturesHigh: DWORD;
    EOTWarningZoneSize: DWORD;
  end;
  {$EXTERNALSYM _TAPE_GET_DRIVE_PARAMETERS}
  TAPE_GET_DRIVE_PARAMETERS = _TAPE_GET_DRIVE_PARAMETERS;
  {$EXTERNALSYM TAPE_GET_DRIVE_PARAMETERS}
  TTapeGetDriveParameters = TAPE_GET_DRIVE_PARAMETERS;
  PTapeGetDriveParameters = PTAPE_GET_DRIVE_PARAMETERS;

//
// IOCTL_TAPE_SET_DRIVE_PARAMETERS definitions
//

  PTAPE_SET_DRIVE_PARAMETERS = ^TAPE_SET_DRIVE_PARAMETERS;
  {$EXTERNALSYM PTAPE_SET_DRIVE_PARAMETERS}
  _TAPE_SET_DRIVE_PARAMETERS = record
    ECC: ByteBool;
    Compression: ByteBool;
    DataPadding: ByteBool;
    ReportSetmarks: ByteBool;
    EOTWarningZoneSize: DWORD;
  end;
  {$EXTERNALSYM _TAPE_SET_DRIVE_PARAMETERS}
  TAPE_SET_DRIVE_PARAMETERS = _TAPE_SET_DRIVE_PARAMETERS;
  {$EXTERNALSYM TAPE_SET_DRIVE_PARAMETERS}
  TTapeSetDriveParameters = TAPE_SET_DRIVE_PARAMETERS;
  PTapeSetDriveParameters = PTAPE_SET_DRIVE_PARAMETERS;

//
// IOCTL_TAPE_GET_MEDIA_PARAMETERS definitions
//

  PTAPE_GET_MEDIA_PARAMETERS = ^TAPE_GET_MEDIA_PARAMETERS;
  {$EXTERNALSYM PTAPE_GET_MEDIA_PARAMETERS}
  _TAPE_GET_MEDIA_PARAMETERS = record
    Capacity: LARGE_INTEGER;
    Remaining: LARGE_INTEGER;
    BlockSize: DWORD;
    PartitionCount: DWORD;
    WriteProtected: ByteBool;
  end;
  {$EXTERNALSYM _TAPE_GET_MEDIA_PARAMETERS}
  TAPE_GET_MEDIA_PARAMETERS = _TAPE_GET_MEDIA_PARAMETERS;
  {$EXTERNALSYM TAPE_GET_MEDIA_PARAMETERS}
  TTapeGetMediaParameters = TAPE_GET_MEDIA_PARAMETERS;
  PTapeGetMediaParameters = PTAPE_GET_MEDIA_PARAMETERS;

//
// IOCTL_TAPE_SET_MEDIA_PARAMETERS definitions
//

  PTAPE_SET_MEDIA_PARAMETERS = ^TAPE_SET_MEDIA_PARAMETERS;
  {$EXTERNALSYM PTAPE_SET_MEDIA_PARAMETERS}
  _TAPE_SET_MEDIA_PARAMETERS = record
    BlockSize: DWORD;
  end;
  {$EXTERNALSYM _TAPE_SET_MEDIA_PARAMETERS}
  TAPE_SET_MEDIA_PARAMETERS = _TAPE_SET_MEDIA_PARAMETERS;
  {$EXTERNALSYM TAPE_SET_MEDIA_PARAMETERS}
  TTapeSetMediaParameters = TAPE_SET_MEDIA_PARAMETERS;
  PTapeSetMediaParameters = PTAPE_SET_MEDIA_PARAMETERS;

//
// IOCTL_TAPE_CREATE_PARTITION definitions
//

const
  TAPE_FIXED_PARTITIONS     = 0;
  {$EXTERNALSYM TAPE_FIXED_PARTITIONS}
  TAPE_SELECT_PARTITIONS    = 1;
  {$EXTERNALSYM TAPE_SELECT_PARTITIONS}
  TAPE_INITIATOR_PARTITIONS = 2;
  {$EXTERNALSYM TAPE_INITIATOR_PARTITIONS}

type
  PTAPE_CREATE_PARTITION = ^TAPE_CREATE_PARTITION;
  {$EXTERNALSYM PTAPE_CREATE_PARTITION}
  _TAPE_CREATE_PARTITION = record
    Method: DWORD;
    Count: DWORD;
    Size: DWORD;
  end;
  {$EXTERNALSYM _TAPE_CREATE_PARTITION}
  TAPE_CREATE_PARTITION = _TAPE_CREATE_PARTITION;
  {$EXTERNALSYM TAPE_CREATE_PARTITION}
  TTapeCreatePartition = TAPE_CREATE_PARTITION;
  PTapeCreatePartition = PTAPE_CREATE_PARTITION;

//
// WMI Methods
//

const
  TAPE_QUERY_DRIVE_PARAMETERS     = 0;
  {$EXTERNALSYM TAPE_QUERY_DRIVE_PARAMETERS}
  TAPE_QUERY_MEDIA_CAPACITY       = 1;
  {$EXTERNALSYM TAPE_QUERY_MEDIA_CAPACITY}
  TAPE_CHECK_FOR_DRIVE_PROBLEM    = 2;
  {$EXTERNALSYM TAPE_CHECK_FOR_DRIVE_PROBLEM}
  TAPE_QUERY_IO_ERROR_DATA        = 3;
  {$EXTERNALSYM TAPE_QUERY_IO_ERROR_DATA}
  TAPE_QUERY_DEVICE_ERROR_DATA    = 4;
  {$EXTERNALSYM TAPE_QUERY_DEVICE_ERROR_DATA}

type
  _TAPE_WMI_OPERATIONS = record
    Method: DWORD;
    DataBufferSize: DWORD;
    DataBuffer: PVOID;
  end;
  {$EXTERNALSYM _TAPE_WMI_OPERATIONS}
  TAPE_WMI_OPERATIONS = _TAPE_WMI_OPERATIONS;
  {$EXTERNALSYM TAPE_WMI_OPERATIONS}
  PTAPE_WMI_OPERATIONS = ^TAPE_WMI_OPERATIONS;
  {$EXTERNALSYM PTAPE_WMI_OPERATIONS}
  TTapeWMIOperations = TAPE_WMI_OPERATIONS;
  PTapeWMIOperations = PTAPE_WMI_OPERATIONS;

//
// Type of drive errors
//

  _TAPE_DRIVE_PROBLEM_TYPE = (
    TapeDriveProblemNone, TapeDriveReadWriteWarning,
    TapeDriveReadWriteError, TapeDriveReadWarning,
    TapeDriveWriteWarning, TapeDriveReadError,
    TapeDriveWriteError, TapeDriveHardwareError,
    TapeDriveUnsupportedMedia, TapeDriveScsiConnectionError,
    TapeDriveTimetoClean, TapeDriveCleanDriveNow,
    TapeDriveMediaLifeExpired, TapeDriveSnappedTape);
  {$EXTERNALSYM _TAPE_DRIVE_PROBLEM_TYPE}
  TAPE_DRIVE_PROBLEM_TYPE = _TAPE_DRIVE_PROBLEM_TYPE;
  TTapeDriveProblemType = TAPE_DRIVE_PROBLEM_TYPE;

const
  ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION         = (1);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_ASSEMBLY_INFORMATION}
  ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION              = (2);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_DLL_REDIRECTION}
  ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION     = (3);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_WINDOW_CLASS_REDIRECTION}
  ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION       = (4);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_COM_SERVER_REDIRECTION}
  ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION    = (5);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_COM_INTERFACE_REDIRECTION}
  ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION = (6);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_COM_TYPE_LIBRARY_REDIRECTION}
  ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION       = (7);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_COM_PROGID_REDIRECTION}
  ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE   = (8);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_GLOBAL_OBJECT_RENAME_TABLE}
  ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES               = (9);
  {$EXTERNALSYM ACTIVATION_CONTEXT_SECTION_CLR_SURROGATES}

implementation

const
  ntdll = 'ntdll.dll';
  kernel32 = 'kernel32.dll';

function WT_SET_MAX_THREADPOOL_THREADS(var Flags: DWORD; Limit: DWORD): DWORD;
begin
  Flags := Flags or (Limit shl 16);
  Result := Flags;
end;

function VALID_IMPERSONATION_LEVEL(L: TSecurityImpersonationLevel): BOOL;
begin
  Result := (L >= SECURITY_MIN_IMPERSONATION_LEVEL) and (L <= SECURITY_MAX_IMPERSONATION_LEVEL);
end;

{
function VALID_TOKEN_AUDIT_POLICY_ELEMENT(P: TOKEN_AUDIT_POLICY_ELEMENT): BOOL;
begin
  Result := ((P.PolicyMask and (not VALID_AUDIT_POLICY_BITS) = 0) and (P.Category <= AuditEventMaxType);
// ((((P).PolicyMask & ~VALID_AUDIT_POLICY_BITS) == 0) && \
//                                             ((P).Category <= AuditEventMaxType))
end;
}

function PER_USER_AUDITING_POLICY_SIZE(p: PTOKEN_AUDIT_POLICY): DWORD;
begin
  Result := SizeOf(TOKEN_AUDIT_POLICY);
  if p^.PolicyCount > ANYSIZE_ARRAY then
    Result := Result + SizeOf(TOKEN_AUDIT_POLICY_ELEMENT) * (P^.PolicyCount - ANYSIZE_ARRAY);
//  ( sizeof(TOKEN_AUDIT_POLICY) + (((p)->PolicyCount > ANYSIZE_ARRAY) ? (sizeof(TOKEN_AUDIT_POLICY_ELEMENT) * ((p)->PolicyCount - ANYSIZE_ARRAY)) : 0) )
end;

function PER_USER_AUDITING_POLICY_SIZE_BY_COUNT(C: DWORD): DWORD;
begin
  Result := SizeOf(TOKEN_AUDIT_POLICY);
  if C > ANYSIZE_ARRAY then
    Result := Result + SizeOf(TOKEN_AUDIT_POLICY_ELEMENT) * (C - ANYSIZE_ARRAY);
//    ( sizeof(TOKEN_AUDIT_POLICY) + (((C) > ANYSIZE_ARRAY) ? (sizeof(TOKEN_AUDIT_POLICY_ELEMENT) * ((C) - ANYSIZE_ARRAY)) : 0) )
end;

function NtCurrentTeb: PNT_TIB;
asm
        MOV     EAX, FS:[0]
end;

function GetFiberData: PVOID;
asm
        MOV     EAX, FS:[$10]
        MOV     EAX, [EAX]
end;

function GetCurrentFiber: PVOID;
asm
        MOV     EAX, FS:[$10]
end;

function Int32x32To64(a, b: LONG): LONGLONG;
begin
  Result := a * b;
end;

function UInt32x32To64(a, b: DWORD): ULONGLONG;
begin
  Result := a * b;
end;

function MAKELANGID(PrimaryLang, SubLang: USHORT): WORD;
begin
  Result := (SubLang shl 10) or PrimaryLang;
end;

function PRIMARYLANGID(LangId: WORD): WORD;
begin
  Result := LangId and $3FF;
end;

function SUBLANGID(LangId: WORD): WORD;
begin
  Result := LangId shr 10;
end;

function MAKELCID(LangId, SortId: WORD): DWORD;
begin
  Result := (DWORD(SortId) shl 16) or DWORD(LangId);
end;

function MAKESORTLCID(LangId, SortId, SortVersion: WORD): DWORD;
begin
  Result := MAKELCID(LangId, SortId) or (SortVersion shl 20);
end;

function LANGIDFROMLCID(LocaleId: LCID): WORD;
begin
  Result := WORD(LocaleId);
end;

function SORTIDFROMLCID(LocaleId: LCID): WORD;
begin
  Result := WORD((DWORD(LocaleId) shr 16) and $F);
end;

function SORTVERSIONFROMLCID(LocaleId: LCID): WORD;
begin
  Result := WORD((DWORD(LocaleId) shr 20) and $F);
end;

function LANG_SYSTEM_DEFAULT: WORD;
begin
  Result := MAKELANGID(LANG_NEUTRAL, SUBLANG_SYS_DEFAULT);
end;

function LANG_USER_DEFAULT: WORD;
begin
  Result := MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);
end;

function LOCALE_SYSTEM_DEFAULT: DWORD;
begin
  Result := MAKELCID(LANG_SYSTEM_DEFAULT, SORT_DEFAULT);
end;

function LOCALE_USER_DEFAULT: DWORD;
begin
  Result := MAKELCID(LANG_USER_DEFAULT, SORT_DEFAULT);
end;

function LOCALE_NEUTRAL: DWORD;
begin
  Result := MAKELCID(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SORT_DEFAULT);
end;

function LOCALE_INVARIANT: DWORD;
begin
  Result := MAKELCID(MAKELANGID(LANG_INVARIANT, SUBLANG_NEUTRAL), SORT_DEFAULT);
end;

function IsReparseTagMicrosoft(Tag: ULONG): Boolean;
begin
  Result := (Tag and ULONG($80000000)) <> 0;
end;

function IsReparseTagHighLatency(Tag: ULONG): Boolean;
begin
  Result := (Tag and ULONG($40000000)) <> 0;
end;

function IsReparseTagNameSurrogate(Tag: ULONG): Boolean;
begin
  Result := (Tag and ULONG($20000000)) <> 0;
end;

// IMAGE_FIRST_SECTION by Nico Bendlin - supplied by Markus Fuchs

function FieldOffset(const Struc; const Field): Cardinal;
begin
  Result := Cardinal(@Field) - Cardinal(@Struc);
end;

function IMAGE_FIRST_SECTION(NtHeader: PImageNtHeaders): PImageSectionHeader;
begin
  Result := PImageSectionHeader(Cardinal(NtHeader) +
      FieldOffset(NtHeader^, NtHeader^.OptionalHeader) +
      NtHeader^.FileHeader.SizeOfOptionalHeader);
end;

function BTYPE(x: DWORD): DWORD;
begin
  Result := x and N_BTMASK;
end;

function ISPTR(x: DWORD): Boolean;
begin
  Result := (x and N_TMASK) = (IMAGE_SYM_DTYPE_POINTER shl N_BTSHFT);
end;

function ISFCN(x: DWORD): Boolean;
begin
  Result := (x and N_TMASK) = (IMAGE_SYM_DTYPE_FUNCTION shl N_BTSHFT);
end;

function ISARY(x: DWORD): Boolean;
begin
  Result := (x and N_TMASK) = (IMAGE_SYM_DTYPE_ARRAY shl N_BTSHFT);
end;

function ISTAG(x: DWORD): Boolean;
begin
  Result := (x = IMAGE_SYM_CLASS_STRUCT_TAG) or (x = IMAGE_SYM_CLASS_UNION_TAG) or
    (x = IMAGE_SYM_CLASS_ENUM_TAG);
end;

function IMAGE_ORDINAL64(Ordinal: ULONGLONG): ULONGLONG;
begin
  Result := (Ordinal and $ffff);
end;

function IMAGE_ORDINAL32(Ordinal: DWORD): DWORD;
begin
  Result := (Ordinal and $ffff);
end;

function IMAGE_ORDINAL(Ordinal: DWORD): DWORD;
begin
  Result := (Ordinal and $ffff);
end;

function IMAGE_SNAP_BY_ORDINAL64(Ordinal: ULONGLONG): Boolean;
begin
  Result := ((Ordinal and IMAGE_ORDINAL_FLAG64) <> 0);
end;

function IMAGE_SNAP_BY_ORDINAL32(Ordinal: DWORD): Boolean;
begin
  Result := ((Ordinal and IMAGE_ORDINAL_FLAG32) <> 0);
end;

function IMAGE_SNAP_BY_ORDINAL(Ordinal: DWORD): Boolean;
begin
  Result := ((Ordinal and IMAGE_ORDINAL_FLAG32) <> 0);
end;

function HEAP_MAKE_TAG_FLAGS(b, o: DWORD): DWORD;
begin
  Result := b + (o shl 18);
end;

{$IFDEF DYNAMIC_LINK}
var
  _RtlCaptureContext: Pointer;

procedure RtlCaptureContext;
begin
  GetProcedureAddress(_RtlCaptureContext, ntdll, 'RtlCaptureContext');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlCaptureContext]
  end;
end;
{$ELSE}
procedure RtlCaptureContext; external ntdll name 'RtlCaptureContext';
{$ENDIF DYNAMIC_LINK}

procedure VER_SET_CONDITION(var Mask: DWORDLONG; TypeBitmask, ConditionMask: ULONG);
begin
  Mask := VerSetConditionMask(Mask, TypeBitmask, ConditionMask);
end;


{$IFDEF DYNAMIC_LINK}
var
  _RtlCompareMemory: Pointer;

function RtlCompareMemory;
begin
  GetProcedureAddress(_RtlCompareMemory, ntdll, 'RtlCompareMemory');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlCompareMemory]
  end;
end;
{$ELSE}
function RtlCompareMemory; external ntdll name 'RtlCompareMemory';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _VerSetConditionMask: Pointer;

function VerSetConditionMask;
begin
  GetProcedureAddress(_VerSetConditionMask, kernel32, 'VerSetConditionMask');
  asm
    mov esp, ebp
    pop ebp
    jmp [_VerSetConditionMask]
  end;
end;
{$ELSE}
function VerSetConditionMask; external kernel32 name 'VerSetConditionMask';
{$ENDIF DYNAMIC_LINK}


{$IFDEF DYNAMIC_LINK}
var
  _RtlInitializeSListHead: Pointer;

procedure RtlInitializeSListHead;
begin
  GetProcedureAddress(_RtlInitializeSListHead, 'ntdll.dll', 'RtlInitializeSListHead');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlInitializeSListHead]
  end;
end;
{$ELSE}
procedure RtlInitializeSListHead; external 'ntdll.dll' name 'RtlInitializeSListHead';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RtlFirstEntrySList: Pointer;

function RtlFirstEntrySList;
begin
  GetProcedureAddress(_RtlFirstEntrySList, 'ntdll.dll', 'RtlFirstEntrySList');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlFirstEntrySList]
  end;
end;
{$ELSE}
function RtlFirstEntrySList; external 'ntdll.dll' name 'RtlFirstEntrySList';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RtlInterlockedPopEntrySList: Pointer;

function RtlInterlockedPopEntrySList;
begin
  GetProcedureAddress(_RtlInterlockedPopEntrySList, 'ntdll.dll', 'RtlInterlockedPopEntrySList');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlInterlockedPopEntrySList]
  end;
end;
{$ELSE}
function RtlInterlockedPopEntrySList; external 'ntdll.dll' name 'RtlInterlockedPopEntrySList';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RtlInterlockedPushEntrySList: Pointer;

function RtlInterlockedPushEntrySList;
begin
  GetProcedureAddress(_RtlInterlockedPushEntrySList, 'ntdll.dll', 'RtlInterlockedPushEntrySList');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlInterlockedPushEntrySList]
  end;
end;
{$ELSE}
function RtlInterlockedPushEntrySList; external 'ntdll.dll' name 'RtlInterlockedPushEntrySList';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RtlInterlockedFlushSList: Pointer;

function RtlInterlockedFlushSList;
begin
  GetProcedureAddress(_RtlInterlockedFlushSList, 'ntdll.dll', 'RtlInterlockedFlushSList');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlInterlockedFlushSList]
  end;
end;
{$ELSE}
function RtlInterlockedFlushSList; external 'ntdll.dll' name 'RtlInterlockedFlushSList';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _RtlQueryDepthSList: Pointer;

function RtlQueryDepthSList;
begin
  GetProcedureAddress(_RtlQueryDepthSList, 'ntdll.dll', 'RtlQueryDepthSList');
  asm
    mov esp, ebp
    pop ebp
    jmp [_RtlQueryDepthSList]
  end;
end;
{$ELSE}
function RtlQueryDepthSList; external 'ntdll.dll' name 'RtlQueryDepthSList';
{$ENDIF DYNAMIC_LINK}

end.
