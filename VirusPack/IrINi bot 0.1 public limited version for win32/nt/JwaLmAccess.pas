{******************************************************************************}
{                                                       	               }
{ Lan Manager Access API interface Unit for Object Pascal                      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmaccess.h, released November 2001. The original Pascal}
{ code is: LmAccess.pas, released Februari 2002. The initial developer of the  }
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

unit JwaLmAccess;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmaccess.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinNT, JwaWinType, JwaLmCons;

//
// Function Prototypes - User
//

function NetUserAdd(servername: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserAdd}

function NetUserEnum(servername: LPCWSTR; level, filter: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resume_handle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserEnum}

function NetUserGetInfo(servername, username: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserGetInfo}

function NetUserSetInfo(servername, username: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserSetInfo}

function NetUserDel(servername: LPCWSTR; username: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserDel}

function NetUserGetGroups(servername, username: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserGetGroups}

function NetUserSetGroups(servername, username: LPCWSTR; level: DWORD; buf: LPBYTE; num_entries: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserSetGroups}

function NetUserGetLocalGroups(servername, username: LPCWSTR; level, flags: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserGetLocalGroups}

function NetUserModalsGet(servername: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserModalsGet}

function NetUserModalsSet(servername: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserModalsSet}

function NetUserChangePassword(domainname, username, oldpassword, newpassword: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetUserChangePassword}

//
//  Data Structures - User
//

type
  LPUSER_INFO_0 = ^USER_INFO_0;
  {$EXTERNALSYM LPUSER_INFO_0}
  PUSER_INFO_0 = ^USER_INFO_0;
  {$EXTERNALSYM PUSER_INFO_0}
  _USER_INFO_0 = record
    usri0_name: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_0}
  USER_INFO_0 = _USER_INFO_0;
  {$EXTERNALSYM USER_INFO_0}
  TUserInfo0 = USER_INFO_0;
  PUserInfo0 = PUSER_INFO_0;

  LPUSER_INFO_1 = ^USER_INFO_1;
  {$EXTERNALSYM LPUSER_INFO_1}
  PUSER_INFO_1 = ^USER_INFO_1;
  {$EXTERNALSYM PUSER_INFO_1}
  _USER_INFO_1 = record
    usri1_name: LPWSTR;
    usri1_password: LPWSTR;
    usri1_password_age: DWORD;
    usri1_priv: DWORD;
    usri1_home_dir: LPWSTR;
    usri1_comment: LPWSTR;
    usri1_flags: DWORD;
    usri1_script_path: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1}
  USER_INFO_1 = _USER_INFO_1;
  {$EXTERNALSYM USER_INFO_1}
  TUserInfo1 = USER_INFO_1;
  PUserInfo1 = PUSER_INFO_1;

  LPUSER_INFO_2 = ^USER_INFO_2;
  {$EXTERNALSYM LPUSER_INFO_2}
  PUSER_INFO_2 = ^USER_INFO_2;
  {$EXTERNALSYM PUSER_INFO_2}
  _USER_INFO_2 = record
    usri2_name: LPWSTR;
    usri2_password: LPWSTR;
    usri2_password_age: DWORD;
    usri2_priv: DWORD;
    usri2_home_dir: LPWSTR;
    usri2_comment: LPWSTR;
    usri2_flags: DWORD;
    usri2_script_path: LPWSTR;
    usri2_auth_flags: DWORD;
    usri2_full_name: LPWSTR;
    usri2_usr_comment: LPWSTR;
    usri2_parms: LPWSTR;
    usri2_workstations: LPWSTR;
    usri2_last_logon: DWORD;
    usri2_last_logoff: DWORD;
    usri2_acct_expires: DWORD;
    usri2_max_storage: DWORD;
    usri2_units_per_week: DWORD;
    usri2_logon_hours: PBYTE;
    usri2_bad_pw_count: DWORD;
    usri2_num_logons: DWORD;
    usri2_logon_server: LPWSTR;
    usri2_country_code: DWORD;
    usri2_code_page: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_2}
  USER_INFO_2 = _USER_INFO_2;
  {$EXTERNALSYM USER_INFO_2}
  TUserInfo2 = USER_INFO_2;
  PUserInfo2 = PUSER_INFO_2;

  LPUSER_INFO_3 = ^USER_INFO_3;
  {$EXTERNALSYM LPUSER_INFO_3}
  PUSER_INFO_3 = ^USER_INFO_3;
  {$EXTERNALSYM PUSER_INFO_3}
  _USER_INFO_3 = record
    usri3_name: LPWSTR;
    usri3_password: LPWSTR;
    usri3_password_age: DWORD;
    usri3_priv: DWORD;
    usri3_home_dir: LPWSTR;
    usri3_comment: LPWSTR;
    usri3_flags: DWORD;
    usri3_script_path: LPWSTR;
    usri3_auth_flags: DWORD;
    usri3_full_name: LPWSTR;
    usri3_usr_comment: LPWSTR;
    usri3_parms: LPWSTR;
    usri3_workstations: LPWSTR;
    usri3_last_logon: DWORD;
    usri3_last_logoff: DWORD;
    usri3_acct_expires: DWORD;
    usri3_max_storage: DWORD;
    usri3_units_per_week: DWORD;
    usri3_logon_hours: PBYTE;
    usri3_bad_pw_count: DWORD;
    usri3_num_logons: DWORD;
    usri3_logon_server: LPWSTR;
    usri3_country_code: DWORD;
    usri3_code_page: DWORD;
    usri3_user_id: DWORD;
    usri3_primary_group_id: DWORD;
    usri3_profile: LPWSTR;
    usri3_home_dir_drive: LPWSTR;
    usri3_password_expired: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_3}
  USER_INFO_3 = _USER_INFO_3;
  {$EXTERNALSYM USER_INFO_3}
  TUserInfo3 = USER_INFO_3;
  PUserInfo3 = PUSER_INFO_3;

  LPUSER_INFO_4 = ^USER_INFO_4;
  {$EXTERNALSYM LPUSER_INFO_4}
  PUSER_INFO_4 = ^USER_INFO_4;
  {$EXTERNALSYM PUSER_INFO_4}
  _USER_INFO_4 = record
    usri4_name: LPWSTR;
    usri4_password: LPWSTR;
    usri4_password_age: DWORD;
    usri4_priv: DWORD;
    usri4_home_dir: LPWSTR;
    usri4_comment: LPWSTR;
    usri4_flags: DWORD;
    usri4_script_path: LPWSTR;
    usri4_auth_flags: DWORD;
    usri4_full_name: LPWSTR;
    usri4_usr_comment: LPWSTR;
    usri4_parms: LPWSTR;
    usri4_workstations: LPWSTR;
    usri4_last_logon: DWORD;
    usri4_last_logoff: DWORD;
    usri4_acct_expires: DWORD;
    usri4_max_storage: DWORD;
    usri4_units_per_week: DWORD;
    usri4_logon_hours: PBYTE;
    usri4_bad_pw_count: DWORD;
    usri4_num_logons: DWORD;
    usri4_logon_server: LPWSTR;
    usri4_country_code: DWORD;
    usri4_code_page: DWORD;
    usri4_user_sid: PSID;
    usri4_primary_group_id: DWORD;
    usri4_profile: LPWSTR;
    usri4_home_dir_drive: LPWSTR;
    usri4_password_expired: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_4}
  USER_INFO_4 = _USER_INFO_4;
  {$EXTERNALSYM USER_INFO_4}
  TUserInfo4 = USER_INFO_4;
  PUserInfo4 = PUSER_INFO_4;

  LPUSER_INFO_10 = ^USER_INFO_10;
  {$EXTERNALSYM LPUSER_INFO_10}
  PUSER_INFO_10 = ^USER_INFO_10;
  {$EXTERNALSYM PUSER_INFO_10}
  _USER_INFO_10 = record
    usri10_name: LPWSTR;
    usri10_comment: LPWSTR;
    usri10_usr_comment: LPWSTR;
    usri10_full_name: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_10}
  USER_INFO_10 = _USER_INFO_10;
  {$EXTERNALSYM USER_INFO_10}
  TUserInfo10 = USER_INFO_10;
  PUserInfo10 = PUSER_INFO_10;

  LPUSER_INFO_11 = ^USER_INFO_11;
  {$EXTERNALSYM LPUSER_INFO_11}
  PUSER_INFO_11 = ^USER_INFO_11;
  {$EXTERNALSYM PUSER_INFO_11}
  _USER_INFO_11 = record
    usri11_name: LPWSTR;
    usri11_comment: LPWSTR;
    usri11_usr_comment: LPWSTR;
    usri11_full_name: LPWSTR;
    usri11_priv: DWORD;
    usri11_auth_flags: DWORD;
    usri11_password_age: DWORD;
    usri11_home_dir: LPWSTR;
    usri11_parms: LPWSTR;
    usri11_last_logon: DWORD;
    usri11_last_logoff: DWORD;
    usri11_bad_pw_count: DWORD;
    usri11_num_logons: DWORD;
    usri11_logon_server: LPWSTR;
    usri11_country_code: DWORD;
    usri11_workstations: LPWSTR;
    usri11_max_storage: DWORD;
    usri11_units_per_week: DWORD;
    usri11_logon_hours: PBYTE;
    usri11_code_page: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_11}
  USER_INFO_11 = _USER_INFO_11;
  {$EXTERNALSYM USER_INFO_11}
  TUserInfo11 = USER_INFO_11;
  PUserInfo11 = PUSER_INFO_11;

  LPUSER_INFO_20 = ^USER_INFO_20;
  {$EXTERNALSYM LPUSER_INFO_20}
  PUSER_INFO_20 = ^USER_INFO_20;
  {$EXTERNALSYM PUSER_INFO_20}
  _USER_INFO_20 = record
    usri20_name: LPWSTR;
    usri20_full_name: LPWSTR;
    usri20_comment: LPWSTR;
    usri20_flags: DWORD;
    usri20_user_id: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_20}
  USER_INFO_20 = _USER_INFO_20;
  {$EXTERNALSYM USER_INFO_20}
  TUserInfo20 = USER_INFO_20;
  PUserInfo20 = PUSER_INFO_20;

  LPUSER_INFO_21 = ^USER_INFO_21;
  {$EXTERNALSYM LPUSER_INFO_21}
  PUSER_INFO_21 = ^USER_INFO_21;
  {$EXTERNALSYM PUSER_INFO_21}
  _USER_INFO_21 = record
    usri21_password: array [0..ENCRYPTED_PWLEN - 1] of BYTE;
  end;
  {$EXTERNALSYM _USER_INFO_21}
  USER_INFO_21 = _USER_INFO_21;
  {$EXTERNALSYM USER_INFO_21}
  TUserInfo21 = USER_INFO_21;
  PUserInfo21 = PUSER_INFO_21;

  LPUSER_INFO_22 = ^USER_INFO_22;
  {$EXTERNALSYM LPUSER_INFO_22}
  PUSER_INFO_22 = ^USER_INFO_22;
  {$EXTERNALSYM PUSER_INFO_22}
  _USER_INFO_22 = record
    usri22_name: LPWSTR;
    usri22_password: array [0..ENCRYPTED_PWLEN - 1] of BYTE;
    usri22_password_age: DWORD;
    usri22_priv: DWORD;
    usri22_home_dir: LPWSTR;
    usri22_comment: LPWSTR;
    usri22_flags: DWORD;
    usri22_script_path: LPWSTR;
    usri22_auth_flags: DWORD;
    usri22_full_name: LPWSTR;
    usri22_usr_comment: LPWSTR;
    usri22_parms: LPWSTR;
    usri22_workstations: LPWSTR;
    usri22_last_logon: DWORD;
    usri22_last_logoff: DWORD;
    usri22_acct_expires: DWORD;
    usri22_max_storage: DWORD;
    usri22_units_per_week: DWORD;
    usri22_logon_hours: PBYTE;
    usri22_bad_pw_count: DWORD;
    usri22_num_logons: DWORD;
    usri22_logon_server: LPWSTR;
    usri22_country_code: DWORD;
    usri22_code_page: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_22}
  USER_INFO_22 = _USER_INFO_22;
  {$EXTERNALSYM USER_INFO_22}
  TUserInfo22 = USER_INFO_22;
  PUserInfo22 = PUSER_INFO_22;

  LPUSER_INFO_23 = ^USER_INFO_23;
  {$EXTERNALSYM LPUSER_INFO_23}
  PUSER_INFO_23 = ^USER_INFO_23;
  {$EXTERNALSYM PUSER_INFO_23}
  _USER_INFO_23 = record
    usri23_name: LPWSTR;
    usri23_full_name: LPWSTR;
    usri23_comment: LPWSTR;
    usri23_flags: DWORD;
    usri23_user_sid: PSID;
  end;
  {$EXTERNALSYM _USER_INFO_23}
  USER_INFO_23 = _USER_INFO_23;
  {$EXTERNALSYM USER_INFO_23}
  TUserInfo23 = USER_INFO_23;
  PUserInfo23 = PUSER_INFO_23;

  LPUSER_INFO_1003 = ^USER_INFO_1003;
  {$EXTERNALSYM LPUSER_INFO_1003}
  PUSER_INFO_1003 = ^USER_INFO_1003;
  {$EXTERNALSYM PUSER_INFO_1003}
  _USER_INFO_1003 = record
    usri1003_password: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1003}
  USER_INFO_1003 = _USER_INFO_1003;
  {$EXTERNALSYM USER_INFO_1003}
  TUserInfo1003 = USER_INFO_1003;
  PUserInfo1003 = PUSER_INFO_1003;

  LPUSER_INFO_1005 = ^USER_INFO_1005;
  {$EXTERNALSYM LPUSER_INFO_1005}
  PUSER_INFO_1005 = ^USER_INFO_1005;
  {$EXTERNALSYM PUSER_INFO_1005}
  _USER_INFO_1005 = record
    usri1005_priv: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1005}
  USER_INFO_1005 = _USER_INFO_1005;
  {$EXTERNALSYM USER_INFO_1005}
  TUserInfo1005 = USER_INFO_1005;
  PUserInfo1005 = PUSER_INFO_1005;

  LPUSER_INFO_1006 = ^USER_INFO_1006;
  {$EXTERNALSYM LPUSER_INFO_1006}
  PUSER_INFO_1006 = ^USER_INFO_1006;
  {$EXTERNALSYM PUSER_INFO_1006}
  _USER_INFO_1006 = record
    usri1006_home_dir: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1006}
  USER_INFO_1006 = _USER_INFO_1006;
  {$EXTERNALSYM USER_INFO_1006}
  TUserInfo1006 = USER_INFO_1006;
  PUserInfo1006 = PUSER_INFO_1006;

  LPUSER_INFO_1007 = ^USER_INFO_1007;
  {$EXTERNALSYM LPUSER_INFO_1007}
  PUSER_INFO_1007 = ^USER_INFO_1007;
  {$EXTERNALSYM PUSER_INFO_1007}
  _USER_INFO_1007 = record
    usri1007_comment: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1007}
  USER_INFO_1007 = _USER_INFO_1007;
  {$EXTERNALSYM USER_INFO_1007}
  TUserInfo1007 = USER_INFO_1007;
  PUserInfo1007 = PUSER_INFO_1007;

  LPUSER_INFO_1008 = ^USER_INFO_1008;
  {$EXTERNALSYM LPUSER_INFO_1008}
  PUSER_INFO_1008 = ^USER_INFO_1008;
  {$EXTERNALSYM PUSER_INFO_1008}
  _USER_INFO_1008 = record
    usri1008_flags: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1008}
  USER_INFO_1008 = _USER_INFO_1008;
  {$EXTERNALSYM USER_INFO_1008}
  TUserInfo1008 = USER_INFO_1008;
  PUserInfo1008 = PUSER_INFO_1008;

  LPUSER_INFO_1009 = ^USER_INFO_1009;
  {$EXTERNALSYM LPUSER_INFO_1009}
  PUSER_INFO_1009 = ^USER_INFO_1009;
  {$EXTERNALSYM PUSER_INFO_1009}
  _USER_INFO_1009 = record
    usri1009_script_path: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1009}
  USER_INFO_1009 = _USER_INFO_1009;
  {$EXTERNALSYM USER_INFO_1009}
  TUserInfo1009 = USER_INFO_1009;
  PUserInfo1009 = PUSER_INFO_1009;

  LPUSER_INFO_1010 = ^USER_INFO_1010;
  {$EXTERNALSYM LPUSER_INFO_1010}
  PUSER_INFO_1010 = ^USER_INFO_1010;
  {$EXTERNALSYM PUSER_INFO_1010}
  _USER_INFO_1010 = record
    usri1010_auth_flags: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1010}
  USER_INFO_1010 = _USER_INFO_1010;
  {$EXTERNALSYM USER_INFO_1010}
  TUserInfo1010 = USER_INFO_1010;
  PUserInfo1010 = PUSER_INFO_1010;

  LPUSER_INFO_1011 = ^USER_INFO_1011;
  {$EXTERNALSYM LPUSER_INFO_1011}
  PUSER_INFO_1011 = ^USER_INFO_1011;
  {$EXTERNALSYM PUSER_INFO_1011}
  _USER_INFO_1011 = record
    usri1011_full_name: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1011}
  USER_INFO_1011 = _USER_INFO_1011;
  {$EXTERNALSYM USER_INFO_1011}
  TUserInfo1011 = USER_INFO_1011;
  PUserInfo1011 = PUSER_INFO_1011;

  LPUSER_INFO_1012 = ^USER_INFO_1012;
  {$EXTERNALSYM LPUSER_INFO_1012}
  PUSER_INFO_1012 = ^USER_INFO_1012;
  {$EXTERNALSYM PUSER_INFO_1012}
  _USER_INFO_1012 = record
    usri1012_usr_comment: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1012}
  USER_INFO_1012 = _USER_INFO_1012;
  {$EXTERNALSYM USER_INFO_1012}
  TUserInfo1012 = USER_INFO_1012;
  PUserInfo1012 = PUSER_INFO_1012;

  LPUSER_INFO_1013 = ^USER_INFO_1013;
  {$EXTERNALSYM LPUSER_INFO_1013}
  PUSER_INFO_1013 = ^USER_INFO_1013;
  {$EXTERNALSYM PUSER_INFO_1013}
  _USER_INFO_1013 = record
    usri1013_parms: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1013}
  USER_INFO_1013 = _USER_INFO_1013;
  {$EXTERNALSYM USER_INFO_1013}
  TUserInfo1013 = USER_INFO_1013;
  PUserInfo1013 = PUSER_INFO_1013;

  LPUSER_INFO_1014 = ^USER_INFO_1014;
  {$EXTERNALSYM LPUSER_INFO_1014}
  PUSER_INFO_1014 = ^USER_INFO_1014;
  {$EXTERNALSYM PUSER_INFO_1014}
  _USER_INFO_1014 = record
    usri1014_workstations: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1014}
  USER_INFO_1014 = _USER_INFO_1014;
  {$EXTERNALSYM USER_INFO_1014}
  TUserInfo1014 = USER_INFO_1014;
  PUserInfo1014 = PUSER_INFO_1014;

  LPUSER_INFO_1017 = ^USER_INFO_1017;
  {$EXTERNALSYM LPUSER_INFO_1017}
  PUSER_INFO_1017 = ^USER_INFO_1017;
  {$EXTERNALSYM PUSER_INFO_1017}
  _USER_INFO_1017 = record
    usri1017_acct_expires: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1017}
  USER_INFO_1017 = _USER_INFO_1017;
  {$EXTERNALSYM USER_INFO_1017}
  TUserInfo1017 = USER_INFO_1017;
  PUserInfo1017 = PUSER_INFO_1017;

  LPUSER_INFO_1018 = ^USER_INFO_1018;
  {$EXTERNALSYM LPUSER_INFO_1018}
  PUSER_INFO_1018 = ^USER_INFO_1018;
  {$EXTERNALSYM PUSER_INFO_1018}
  _USER_INFO_1018 = record
    usri1018_max_storage: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1018}
  USER_INFO_1018 = _USER_INFO_1018;
  {$EXTERNALSYM USER_INFO_1018}
  TUserInfo1018 = USER_INFO_1018;
  PUserInfo1018 = PUSER_INFO_1018;

  LPUSER_INFO_1020 = ^USER_INFO_1020;
  {$EXTERNALSYM LPUSER_INFO_1020}
  PUSER_INFO_1020 = ^USER_INFO_1020;
  {$EXTERNALSYM PUSER_INFO_1020}
  _USER_INFO_1020 = record
    usri1020_units_per_week: DWORD;
    usri1020_logon_hours: LPBYTE;
  end;
  {$EXTERNALSYM _USER_INFO_1020}
  USER_INFO_1020 = _USER_INFO_1020;
  {$EXTERNALSYM USER_INFO_1020}
  TUserInfo1020 = USER_INFO_1020;
  PUserInfo1020 = PUSER_INFO_1020;

  LPUSER_INFO_1023 = ^USER_INFO_1023;
  {$EXTERNALSYM LPUSER_INFO_1023}
  PUSER_INFO_1023 = ^USER_INFO_1023;
  {$EXTERNALSYM PUSER_INFO_1023}
  _USER_INFO_1023 = record
    usri1023_logon_server: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1023}
  USER_INFO_1023 = _USER_INFO_1023;
  {$EXTERNALSYM USER_INFO_1023}
  TUserInfo1023 = USER_INFO_1023;
  PUserInfo1023 = PUSER_INFO_1023;

  LPUSER_INFO_1024 = ^USER_INFO_1024;
  {$EXTERNALSYM LPUSER_INFO_1024}
  PUSER_INFO_1024 = ^USER_INFO_1024;
  {$EXTERNALSYM PUSER_INFO_1024}
  _USER_INFO_1024 = record
    usri1024_country_code: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1024}
  USER_INFO_1024 = _USER_INFO_1024;
  {$EXTERNALSYM USER_INFO_1024}
  TUserInfo1024 = USER_INFO_1024;
  PUserInfo1024 = PUSER_INFO_1024;

  LPUSER_INFO_1025 = ^USER_INFO_1025;
  {$EXTERNALSYM LPUSER_INFO_1025}
  PUSER_INFO_1025 = ^USER_INFO_1025;
  {$EXTERNALSYM PUSER_INFO_1025}
  _USER_INFO_1025 = record
    usri1025_code_page: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1025}
  USER_INFO_1025 = _USER_INFO_1025;
  {$EXTERNALSYM USER_INFO_1025}
  TUserInfo1025 = USER_INFO_1025;
  PUserInfo1025 = PUSER_INFO_1025;

  LPUSER_INFO_1051 = ^USER_INFO_1051;
  {$EXTERNALSYM LPUSER_INFO_1051}
  PUSER_INFO_1051 = ^USER_INFO_1051;
  {$EXTERNALSYM PUSER_INFO_1051}
  _USER_INFO_1051 = record
    usri1051_primary_group_id: DWORD;
  end;
  {$EXTERNALSYM _USER_INFO_1051}
  USER_INFO_1051 = _USER_INFO_1051;
  {$EXTERNALSYM USER_INFO_1051}
  TUserInfo1051 = USER_INFO_1051;
  PUserInfo1051 = PUSER_INFO_1051;

  LPUSER_INFO_1052 = ^USER_INFO_1052;
  {$EXTERNALSYM LPUSER_INFO_1052}
  PUSER_INFO_1052 = ^USER_INFO_1052;
  {$EXTERNALSYM PUSER_INFO_1052}
  _USER_INFO_1052 = record
    usri1052_profile: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1052}
  USER_INFO_1052 = _USER_INFO_1052;
  {$EXTERNALSYM USER_INFO_1052}
  TUserInfo1052 = USER_INFO_1052;
  PUserInfo1052 = PUSER_INFO_1052;

  LPUSER_INFO_1053 = ^USER_INFO_1053;
  {$EXTERNALSYM LPUSER_INFO_1053}
  PUSER_INFO_1053 = ^USER_INFO_1053;
  {$EXTERNALSYM PUSER_INFO_1053}
  _USER_INFO_1053 = record
    usri1053_home_dir_drive: LPWSTR;
  end;
  {$EXTERNALSYM _USER_INFO_1053}
  USER_INFO_1053 = _USER_INFO_1053;
  {$EXTERNALSYM USER_INFO_1053}
  TUserInfo1053 = USER_INFO_1053;
  PUserInfo1053 = PUSER_INFO_1053;

//
//  Data Structures - User Modals
//

  LPUSER_MODALS_INFO_0 = ^USER_MODALS_INFO_0;
  {$EXTERNALSYM LPUSER_MODALS_INFO_0}
  PUSER_MODALS_INFO_0 = ^USER_MODALS_INFO_0;
  {$EXTERNALSYM PUSER_MODALS_INFO_0}
  _USER_MODALS_INFO_0 = record
    usrmod0_min_passwd_len: DWORD;
    usrmod0_max_passwd_age: DWORD;
    usrmod0_min_passwd_age: DWORD;
    usrmod0_force_logoff: DWORD;
    usrmod0_password_hist_len: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_0}
  USER_MODALS_INFO_0 = _USER_MODALS_INFO_0;
  {$EXTERNALSYM USER_MODALS_INFO_0}
  TUserModalsInfo0 = USER_MODALS_INFO_0;
  PUserModalsInfo0 = PUSER_MODALS_INFO_0;

  LPUSER_MODALS_INFO_1 = ^USER_MODALS_INFO_1;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1}
  PUSER_MODALS_INFO_1 = ^USER_MODALS_INFO_1;
  {$EXTERNALSYM PUSER_MODALS_INFO_1}
  _USER_MODALS_INFO_1 = record
    usrmod1_role: DWORD;
    usrmod1_primary: LPWSTR;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1}
  USER_MODALS_INFO_1 = _USER_MODALS_INFO_1;
  {$EXTERNALSYM USER_MODALS_INFO_1}
  TUserModalsInfo1 = USER_MODALS_INFO_1;
  PUserModalsInfo1 = PUSER_MODALS_INFO_1;

  LPUSER_MODALS_INFO_2 = ^USER_MODALS_INFO_2;
  {$EXTERNALSYM LPUSER_MODALS_INFO_2}
  PUSER_MODALS_INFO_2 = ^USER_MODALS_INFO_2;
  {$EXTERNALSYM PUSER_MODALS_INFO_2}
  _USER_MODALS_INFO_2 = record
    usrmod2_domain_name: LPWSTR;
    usrmod2_domain_id: PSID;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_2}
  USER_MODALS_INFO_2 = _USER_MODALS_INFO_2;
  {$EXTERNALSYM USER_MODALS_INFO_2}
  TUserModalsInfo2 = USER_MODALS_INFO_2;
  PUserModalsInfo2 = PUSER_MODALS_INFO_2;

  LPUSER_MODALS_INFO_3 = ^USER_MODALS_INFO_3;
  {$EXTERNALSYM LPUSER_MODALS_INFO_3}
  PUSER_MODALS_INFO_3 = ^USER_MODALS_INFO_3;
  {$EXTERNALSYM PUSER_MODALS_INFO_3}
  _USER_MODALS_INFO_3 = record
    usrmod3_lockout_duration: DWORD;
    usrmod3_lockout_observation_window: DWORD;
    usrmod3_lockout_threshold: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_3}
  USER_MODALS_INFO_3 = _USER_MODALS_INFO_3;
  {$EXTERNALSYM USER_MODALS_INFO_3}
  TUserModalsInfo3 = USER_MODALS_INFO_3;
  PUserModalsInfo3 = PUSER_MODALS_INFO_3;

  LPUSER_MODALS_INFO_1001 = ^USER_MODALS_INFO_1001;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1001}
  PUSER_MODALS_INFO_1001 = ^USER_MODALS_INFO_1001;
  {$EXTERNALSYM PUSER_MODALS_INFO_1001}
  _USER_MODALS_INFO_1001 = record
    usrmod1001_min_passwd_len: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1001}
  USER_MODALS_INFO_1001 = _USER_MODALS_INFO_1001;
  {$EXTERNALSYM USER_MODALS_INFO_1001}
  TUserModalsInfo1001 = USER_MODALS_INFO_1001;
  PUserModalsInfo1001 = PUSER_MODALS_INFO_1001;

  LPUSER_MODALS_INFO_1002 = ^USER_MODALS_INFO_1002;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1002}
  PUSER_MODALS_INFO_1002 = ^USER_MODALS_INFO_1002;
  {$EXTERNALSYM PUSER_MODALS_INFO_1002}
  _USER_MODALS_INFO_1002 = record
    usrmod1002_max_passwd_age: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1002}
  USER_MODALS_INFO_1002 = _USER_MODALS_INFO_1002;
  {$EXTERNALSYM USER_MODALS_INFO_1002}
  TUserModalsInfo1002 = USER_MODALS_INFO_1002;
  PUserModalsInfo1002 = PUSER_MODALS_INFO_1002;

  LPUSER_MODALS_INFO_1003 = ^USER_MODALS_INFO_1003;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1003}
  PUSER_MODALS_INFO_1003 = ^USER_MODALS_INFO_1003;
  {$EXTERNALSYM PUSER_MODALS_INFO_1003}
  _USER_MODALS_INFO_1003 = record
    usrmod1003_min_passwd_age: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1003}
  USER_MODALS_INFO_1003 = _USER_MODALS_INFO_1003;
  {$EXTERNALSYM USER_MODALS_INFO_1003}
  TUserModalsInfo1003 = USER_MODALS_INFO_1003;
  PUserModalsInfo1003 = PUSER_MODALS_INFO_1003;

  LPUSER_MODALS_INFO_1004 = ^USER_MODALS_INFO_1004;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1004}
  PUSER_MODALS_INFO_1004 = ^USER_MODALS_INFO_1004;
  {$EXTERNALSYM PUSER_MODALS_INFO_1004}
  _USER_MODALS_INFO_1004 = record
    usrmod1004_force_logoff: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1004}
  USER_MODALS_INFO_1004 = _USER_MODALS_INFO_1004;
  {$EXTERNALSYM USER_MODALS_INFO_1004}
  TUserModalsInfo1004 = USER_MODALS_INFO_1004;
  PUserModalsInfo1004 = PUSER_MODALS_INFO_1004;

  LPUSER_MODALS_INFO_1005 = ^USER_MODALS_INFO_1005;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1005}
  PUSER_MODALS_INFO_1005 = ^USER_MODALS_INFO_1005;
  {$EXTERNALSYM PUSER_MODALS_INFO_1005}
  _USER_MODALS_INFO_1005 = record
    usrmod1005_password_hist_len: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1005}
  USER_MODALS_INFO_1005 = _USER_MODALS_INFO_1005;
  {$EXTERNALSYM USER_MODALS_INFO_1005}
  TUserModalsInfo1005 = USER_MODALS_INFO_1005;
  PUserModalsInfo1005 = PUSER_MODALS_INFO_1005;

  LPUSER_MODALS_INFO_1006 = ^USER_MODALS_INFO_1006;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1006}
  PUSER_MODALS_INFO_1006 = ^USER_MODALS_INFO_1006;
  {$EXTERNALSYM PUSER_MODALS_INFO_1006}
  _USER_MODALS_INFO_1006 = record
    usrmod1006_role: DWORD;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1006}
  USER_MODALS_INFO_1006 = _USER_MODALS_INFO_1006;
  {$EXTERNALSYM USER_MODALS_INFO_1006}
  TUserModalsInfo1006 = USER_MODALS_INFO_1006;
  PUserModalsInfo1006 = PUSER_MODALS_INFO_1006;

  LPUSER_MODALS_INFO_1007 = ^USER_MODALS_INFO_1007;
  {$EXTERNALSYM LPUSER_MODALS_INFO_1007}
  PUSER_MODALS_INFO_1007 = ^USER_MODALS_INFO_1007;
  {$EXTERNALSYM PUSER_MODALS_INFO_1007}
  _USER_MODALS_INFO_1007 = record
    usrmod1007_primary: LPWSTR;
  end;
  {$EXTERNALSYM _USER_MODALS_INFO_1007}
  USER_MODALS_INFO_1007 = _USER_MODALS_INFO_1007;
  {$EXTERNALSYM USER_MODALS_INFO_1007}
  TUserModalsInfo1007 = USER_MODALS_INFO_1007;
  PUserModalsInfo1007 = PUSER_MODALS_INFO_1007;

//
// Special Values and Constants - User
//

//
//  Bit masks for field usriX_flags of USER_INFO_X (X = 0/1).
//

const
  UF_SCRIPT                          = $0001;
  {$EXTERNALSYM UF_SCRIPT}
  UF_ACCOUNTDISABLE                  = $0002;
  {$EXTERNALSYM UF_ACCOUNTDISABLE}
  UF_HOMEDIR_REQUIRED                = $0008;
  {$EXTERNALSYM UF_HOMEDIR_REQUIRED}
  UF_LOCKOUT                         = $0010;
  {$EXTERNALSYM UF_LOCKOUT}
  UF_PASSWD_NOTREQD                  = $0020;
  {$EXTERNALSYM UF_PASSWD_NOTREQD}
  UF_PASSWD_CANT_CHANGE              = $0040;
  {$EXTERNALSYM UF_PASSWD_CANT_CHANGE}
  UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED = $0080;
  {$EXTERNALSYM UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED}

//
// Account type bits as part of usri_flags.
//

  UF_TEMP_DUPLICATE_ACCOUNT    = $0100;
  {$EXTERNALSYM UF_TEMP_DUPLICATE_ACCOUNT}
  UF_NORMAL_ACCOUNT            = $0200;
  {$EXTERNALSYM UF_NORMAL_ACCOUNT}
  UF_INTERDOMAIN_TRUST_ACCOUNT = $0800;
  {$EXTERNALSYM UF_INTERDOMAIN_TRUST_ACCOUNT}
  UF_WORKSTATION_TRUST_ACCOUNT = $1000;
  {$EXTERNALSYM UF_WORKSTATION_TRUST_ACCOUNT}
  UF_SERVER_TRUST_ACCOUNT      = $2000;
  {$EXTERNALSYM UF_SERVER_TRUST_ACCOUNT}

  UF_MACHINE_ACCOUNT_MASK = (UF_INTERDOMAIN_TRUST_ACCOUNT or UF_WORKSTATION_TRUST_ACCOUNT or UF_SERVER_TRUST_ACCOUNT);
  {$EXTERNALSYM UF_MACHINE_ACCOUNT_MASK}

  UF_ACCOUNT_TYPE_MASK = UF_TEMP_DUPLICATE_ACCOUNT or UF_NORMAL_ACCOUNT or UF_INTERDOMAIN_TRUST_ACCOUNT or UF_WORKSTATION_TRUST_ACCOUNT or UF_SERVER_TRUST_ACCOUNT;
  {$EXTERNALSYM UF_ACCOUNT_TYPE_MASK}

  UF_DONT_EXPIRE_PASSWD                     = $10000;
  {$EXTERNALSYM UF_DONT_EXPIRE_PASSWD}
  UF_MNS_LOGON_ACCOUNT                      = $20000;
  {$EXTERNALSYM UF_MNS_LOGON_ACCOUNT}
  UF_SMARTCARD_REQUIRED                     = $40000;
  {$EXTERNALSYM UF_SMARTCARD_REQUIRED}
  UF_TRUSTED_FOR_DELEGATION                 = $80000;
  {$EXTERNALSYM UF_TRUSTED_FOR_DELEGATION}
  UF_NOT_DELEGATED                          = $100000;
  {$EXTERNALSYM UF_NOT_DELEGATED}
  UF_USE_DES_KEY_ONLY                       = $200000;
  {$EXTERNALSYM UF_USE_DES_KEY_ONLY}
  UF_DONT_REQUIRE_PREAUTH                   = $400000;
  {$EXTERNALSYM UF_DONT_REQUIRE_PREAUTH}
  UF_PASSWORD_EXPIRED                       = DWORD($800000);
  {$EXTERNALSYM UF_PASSWORD_EXPIRED}
  UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION = $1000000;
  {$EXTERNALSYM UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION}


  UF_SETTABLE_BITS =
                    UF_SCRIPT or
                    UF_ACCOUNTDISABLE or
                    UF_LOCKOUT or
                    UF_HOMEDIR_REQUIRED or
                    UF_PASSWD_NOTREQD or
                    UF_PASSWD_CANT_CHANGE or
                    UF_ACCOUNT_TYPE_MASK or
                    UF_DONT_EXPIRE_PASSWD or
                    UF_MNS_LOGON_ACCOUNT or
                    UF_ENCRYPTED_TEXT_PASSWORD_ALLOWED or
                    UF_SMARTCARD_REQUIRED or
                    UF_TRUSTED_FOR_DELEGATION or
                    UF_NOT_DELEGATED or
                    UF_USE_DES_KEY_ONLY or
                    UF_DONT_REQUIRE_PREAUTH or
                    UF_PASSWORD_EXPIRED or
                    UF_TRUSTED_TO_AUTHENTICATE_FOR_DELEGATION;
  {$EXTERNALSYM UF_SETTABLE_BITS}

//
// bit masks for the NetUserEnum filter parameter.
//

  FILTER_TEMP_DUPLICATE_ACCOUNT = ($0001);
  {$EXTERNALSYM FILTER_TEMP_DUPLICATE_ACCOUNT}
  FILTER_NORMAL_ACCOUNT         = ($0002);
  {$EXTERNALSYM FILTER_NORMAL_ACCOUNT}
// #define FILTER_PROXY_ACCOUNT                (0x0004)
  FILTER_INTERDOMAIN_TRUST_ACCOUNT = ($0008);
  {$EXTERNALSYM FILTER_INTERDOMAIN_TRUST_ACCOUNT}
  FILTER_WORKSTATION_TRUST_ACCOUNT = ($0010);
  {$EXTERNALSYM FILTER_WORKSTATION_TRUST_ACCOUNT}
  FILTER_SERVER_TRUST_ACCOUNT      = ($0020);
  {$EXTERNALSYM FILTER_SERVER_TRUST_ACCOUNT}

//
// bit masks for the NetUserGetLocalGroups flags
//

  LG_INCLUDE_INDIRECT = ($0001);
  {$EXTERNALSYM LG_INCLUDE_INDIRECT}

//
//  Bit masks for field usri2_auth_flags of USER_INFO_2.
//

  AF_OP_PRINT      = $1;
  {$EXTERNALSYM AF_OP_PRINT}
  AF_OP_COMM       = $2;
  {$EXTERNALSYM AF_OP_COMM}
  AF_OP_SERVER     = $4;
  {$EXTERNALSYM AF_OP_SERVER}
  AF_OP_ACCOUNTS   = $8;
  {$EXTERNALSYM AF_OP_ACCOUNTS}
  AF_SETTABLE_BITS = (AF_OP_PRINT or AF_OP_COMM or AF_OP_SERVER or AF_OP_ACCOUNTS);
  {$EXTERNALSYM AF_SETTABLE_BITS}

//
//  UAS role manifests under NETLOGON
//

  UAS_ROLE_STANDALONE = 0;
  {$EXTERNALSYM UAS_ROLE_STANDALONE}
  UAS_ROLE_MEMBER     = 1;
  {$EXTERNALSYM UAS_ROLE_MEMBER}
  UAS_ROLE_BACKUP     = 2;
  {$EXTERNALSYM UAS_ROLE_BACKUP}
  UAS_ROLE_PRIMARY    = 3;
  {$EXTERNALSYM UAS_ROLE_PRIMARY}

//
//  Values for ParmError for NetUserSetInfo.
//

  USER_NAME_PARMNUM           = 1;
  {$EXTERNALSYM USER_NAME_PARMNUM}
  USER_PASSWORD_PARMNUM       = 3;
  {$EXTERNALSYM USER_PASSWORD_PARMNUM}
  USER_PASSWORD_AGE_PARMNUM   = 4;
  {$EXTERNALSYM USER_PASSWORD_AGE_PARMNUM}
  USER_PRIV_PARMNUM           = 5;
  {$EXTERNALSYM USER_PRIV_PARMNUM}
  USER_HOME_DIR_PARMNUM       = 6;
  {$EXTERNALSYM USER_HOME_DIR_PARMNUM}
  USER_COMMENT_PARMNUM        = 7;
  {$EXTERNALSYM USER_COMMENT_PARMNUM}
  USER_FLAGS_PARMNUM          = 8;
  {$EXTERNALSYM USER_FLAGS_PARMNUM}
  USER_SCRIPT_PATH_PARMNUM    = 9;
  {$EXTERNALSYM USER_SCRIPT_PATH_PARMNUM}
  USER_AUTH_FLAGS_PARMNUM     = 10;
  {$EXTERNALSYM USER_AUTH_FLAGS_PARMNUM}
  USER_FULL_NAME_PARMNUM      = 11;
  {$EXTERNALSYM USER_FULL_NAME_PARMNUM}
  USER_USR_COMMENT_PARMNUM    = 12;
  {$EXTERNALSYM USER_USR_COMMENT_PARMNUM}
  USER_PARMS_PARMNUM          = 13;
  {$EXTERNALSYM USER_PARMS_PARMNUM}
  USER_WORKSTATIONS_PARMNUM   = 14;
  {$EXTERNALSYM USER_WORKSTATIONS_PARMNUM}
  USER_LAST_LOGON_PARMNUM     = 15;
  {$EXTERNALSYM USER_LAST_LOGON_PARMNUM}
  USER_LAST_LOGOFF_PARMNUM    = 16;
  {$EXTERNALSYM USER_LAST_LOGOFF_PARMNUM}
  USER_ACCT_EXPIRES_PARMNUM   = 17;
  {$EXTERNALSYM USER_ACCT_EXPIRES_PARMNUM}
  USER_MAX_STORAGE_PARMNUM    = 18;
  {$EXTERNALSYM USER_MAX_STORAGE_PARMNUM}
  USER_UNITS_PER_WEEK_PARMNUM = 19;
  {$EXTERNALSYM USER_UNITS_PER_WEEK_PARMNUM}
  USER_LOGON_HOURS_PARMNUM    = 20;
  {$EXTERNALSYM USER_LOGON_HOURS_PARMNUM}
  USER_PAD_PW_COUNT_PARMNUM   = 21;
  {$EXTERNALSYM USER_PAD_PW_COUNT_PARMNUM}
  USER_NUM_LOGONS_PARMNUM     = 22;
  {$EXTERNALSYM USER_NUM_LOGONS_PARMNUM}
  USER_LOGON_SERVER_PARMNUM   = 23;
  {$EXTERNALSYM USER_LOGON_SERVER_PARMNUM}
  USER_COUNTRY_CODE_PARMNUM   = 24;
  {$EXTERNALSYM USER_COUNTRY_CODE_PARMNUM}
  USER_CODE_PAGE_PARMNUM      = 25;
  {$EXTERNALSYM USER_CODE_PAGE_PARMNUM}
  USER_PRIMARY_GROUP_PARMNUM  = 51;
  {$EXTERNALSYM USER_PRIMARY_GROUP_PARMNUM}
  USER_PROFILE                = 52; // ?? Delete when convenient
  {$EXTERNALSYM USER_PROFILE}
  USER_PROFILE_PARMNUM        = 52;
  {$EXTERNALSYM USER_PROFILE_PARMNUM}
  USER_HOME_DIR_DRIVE_PARMNUM = 53;
  {$EXTERNALSYM USER_HOME_DIR_DRIVE_PARMNUM}

//
// the new infolevel counterparts of the old info level + parmnum
//

  USER_NAME_INFOLEVEL           = (PARMNUM_BASE_INFOLEVEL + USER_NAME_PARMNUM);
  {$EXTERNALSYM USER_NAME_INFOLEVEL}
  USER_PASSWORD_INFOLEVEL       = (PARMNUM_BASE_INFOLEVEL + USER_PASSWORD_PARMNUM);
  {$EXTERNALSYM USER_PASSWORD_INFOLEVEL}
  USER_PASSWORD_AGE_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + USER_PASSWORD_AGE_PARMNUM);
  {$EXTERNALSYM USER_PASSWORD_AGE_INFOLEVEL}
  USER_PRIV_INFOLEVEL           = (PARMNUM_BASE_INFOLEVEL + USER_PRIV_PARMNUM);
  {$EXTERNALSYM USER_PRIV_INFOLEVEL}
  USER_HOME_DIR_INFOLEVEL       = (PARMNUM_BASE_INFOLEVEL + USER_HOME_DIR_PARMNUM);
  {$EXTERNALSYM USER_HOME_DIR_INFOLEVEL}
  USER_COMMENT_INFOLEVEL        = (PARMNUM_BASE_INFOLEVEL + USER_COMMENT_PARMNUM);
  {$EXTERNALSYM USER_COMMENT_INFOLEVEL}
  USER_FLAGS_INFOLEVEL          = (PARMNUM_BASE_INFOLEVEL + USER_FLAGS_PARMNUM);
  {$EXTERNALSYM USER_FLAGS_INFOLEVEL}
  USER_SCRIPT_PATH_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + USER_SCRIPT_PATH_PARMNUM);
  {$EXTERNALSYM USER_SCRIPT_PATH_INFOLEVEL}
  USER_AUTH_FLAGS_INFOLEVEL     = (PARMNUM_BASE_INFOLEVEL + USER_AUTH_FLAGS_PARMNUM);
  {$EXTERNALSYM USER_AUTH_FLAGS_INFOLEVEL}
  USER_FULL_NAME_INFOLEVEL      = (PARMNUM_BASE_INFOLEVEL + USER_FULL_NAME_PARMNUM);
  {$EXTERNALSYM USER_FULL_NAME_INFOLEVEL}
  USER_USR_COMMENT_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + USER_USR_COMMENT_PARMNUM);
  {$EXTERNALSYM USER_USR_COMMENT_INFOLEVEL}
  USER_PARMS_INFOLEVEL          = (PARMNUM_BASE_INFOLEVEL + USER_PARMS_PARMNUM);
  {$EXTERNALSYM USER_PARMS_INFOLEVEL}
  USER_WORKSTATIONS_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + USER_WORKSTATIONS_PARMNUM);
  {$EXTERNALSYM USER_WORKSTATIONS_INFOLEVEL}
  USER_LAST_LOGON_INFOLEVEL     = (PARMNUM_BASE_INFOLEVEL + USER_LAST_LOGON_PARMNUM);
  {$EXTERNALSYM USER_LAST_LOGON_INFOLEVEL}
  USER_LAST_LOGOFF_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + USER_LAST_LOGOFF_PARMNUM);
  {$EXTERNALSYM USER_LAST_LOGOFF_INFOLEVEL}
  USER_ACCT_EXPIRES_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + USER_ACCT_EXPIRES_PARMNUM);
  {$EXTERNALSYM USER_ACCT_EXPIRES_INFOLEVEL}
  USER_MAX_STORAGE_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + USER_MAX_STORAGE_PARMNUM);
  {$EXTERNALSYM USER_MAX_STORAGE_INFOLEVEL}
  USER_UNITS_PER_WEEK_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_UNITS_PER_WEEK_PARMNUM);
  {$EXTERNALSYM USER_UNITS_PER_WEEK_INFOLEVEL}
  USER_LOGON_HOURS_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + USER_LOGON_HOURS_PARMNUM);
  {$EXTERNALSYM USER_LOGON_HOURS_INFOLEVEL}
  USER_PAD_PW_COUNT_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + USER_PAD_PW_COUNT_PARMNUM);
  {$EXTERNALSYM USER_PAD_PW_COUNT_INFOLEVEL}
  USER_NUM_LOGONS_INFOLEVEL     = (PARMNUM_BASE_INFOLEVEL + USER_NUM_LOGONS_PARMNUM);
  {$EXTERNALSYM USER_NUM_LOGONS_INFOLEVEL}
  USER_LOGON_SERVER_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + USER_LOGON_SERVER_PARMNUM);
  {$EXTERNALSYM USER_LOGON_SERVER_INFOLEVEL}
  USER_COUNTRY_CODE_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + USER_COUNTRY_CODE_PARMNUM);
  {$EXTERNALSYM USER_COUNTRY_CODE_INFOLEVEL}
  USER_CODE_PAGE_INFOLEVEL      = (PARMNUM_BASE_INFOLEVEL + USER_CODE_PAGE_PARMNUM);
  {$EXTERNALSYM USER_CODE_PAGE_INFOLEVEL}
  USER_PRIMARY_GROUP_INFOLEVEL  = (PARMNUM_BASE_INFOLEVEL + USER_PRIMARY_GROUP_PARMNUM);
  {$EXTERNALSYM USER_PRIMARY_GROUP_INFOLEVEL}
//  todo USER_POSIX_ID_PARMNUM where is it defined?
//  USER_POSIX_ID_INFOLEVEL       = (PARMNUM_BASE_INFOLEVEL + USER_POSIX_ID_PARMNUM);
//  {$EXTERNALSYM USER_POSIX_ID_INFOLEVEL}
  USER_HOME_DIR_DRIVE_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + USER_HOME_DIR_DRIVE_PARMNUM);
  {$EXTERNALSYM USER_HOME_DIR_DRIVE_INFOLEVEL}

//
//  For SetInfo call (parmnum 0) when password change not required
//

  NULL_USERSETINFO_PASSWD = '              ';
  {$EXTERNALSYM NULL_USERSETINFO_PASSWD}

  TIMEQ_FOREVER             = ULONG(-1);
  {$EXTERNALSYM TIMEQ_FOREVER}
  USER_MAXSTORAGE_UNLIMITED = ULONG(-1);
  {$EXTERNALSYM USER_MAXSTORAGE_UNLIMITED}
  USER_NO_LOGOFF            = ULONG(-1);
  {$EXTERNALSYM USER_NO_LOGOFF}
  UNITS_PER_DAY             = 24;
  {$EXTERNALSYM UNITS_PER_DAY}
  UNITS_PER_WEEK            = UNITS_PER_DAY * 7;
  {$EXTERNALSYM UNITS_PER_WEEK}

//
// Privilege levels (USER_INFO_X field usriX_priv (X = 0/1)).
//

  USER_PRIV_MASK  = $3;
  {$EXTERNALSYM USER_PRIV_MASK}
  USER_PRIV_GUEST = 0;
  {$EXTERNALSYM USER_PRIV_GUEST}
  USER_PRIV_USER  = 1;
  {$EXTERNALSYM USER_PRIV_USER}
  USER_PRIV_ADMIN = 2;
  {$EXTERNALSYM USER_PRIV_ADMIN}

//
// user modals related defaults
//

  MAX_PASSWD_LEN   = PWLEN;
  {$EXTERNALSYM MAX_PASSWD_LEN}
  DEF_MIN_PWLEN    = 6;
  {$EXTERNALSYM DEF_MIN_PWLEN}
  DEF_PWUNIQUENESS = 5;
  {$EXTERNALSYM DEF_PWUNIQUENESS}
  DEF_MAX_PWHIST   = 8;
  {$EXTERNALSYM DEF_MAX_PWHIST}

  DEF_MAX_PWAGE    = TIMEQ_FOREVER; // forever
  {$EXTERNALSYM DEF_MAX_PWAGE}
  DEF_MIN_PWAGE    = 0; // 0 days
  {$EXTERNALSYM DEF_MIN_PWAGE}
  DEF_FORCE_LOGOFF = ULONG($ffffffff); // never
  {$EXTERNALSYM DEF_FORCE_LOGOFF}
  DEF_MAX_BADPW    = 0; // no limit
  {$EXTERNALSYM DEF_MAX_BADPW}
  ONE_DAY          = ULONG(01*24*3600); // 01 day
  {$EXTERNALSYM ONE_DAY}

//
// User Logon Validation (codes returned)
//

  VALIDATED_LOGON     = 0;
  {$EXTERNALSYM VALIDATED_LOGON}
  PASSWORD_EXPIRED    = 2;
  {$EXTERNALSYM PASSWORD_EXPIRED}
  NON_VALIDATED_LOGON = 3;
  {$EXTERNALSYM NON_VALIDATED_LOGON}

  VALID_LOGOFF = 1;
  {$EXTERNALSYM VALID_LOGOFF}

//
// parmnum manifests for user modals
//

  MODALS_MIN_PASSWD_LEN_PARMNUM             = 1;
  {$EXTERNALSYM MODALS_MIN_PASSWD_LEN_PARMNUM}
  MODALS_MAX_PASSWD_AGE_PARMNUM             = 2;
  {$EXTERNALSYM MODALS_MAX_PASSWD_AGE_PARMNUM}
  MODALS_MIN_PASSWD_AGE_PARMNUM             = 3;
  {$EXTERNALSYM MODALS_MIN_PASSWD_AGE_PARMNUM}
  MODALS_FORCE_LOGOFF_PARMNUM               = 4;
  {$EXTERNALSYM MODALS_FORCE_LOGOFF_PARMNUM}
  MODALS_PASSWD_HIST_LEN_PARMNUM            = 5;
  {$EXTERNALSYM MODALS_PASSWD_HIST_LEN_PARMNUM}
  MODALS_ROLE_PARMNUM                       = 6;
  {$EXTERNALSYM MODALS_ROLE_PARMNUM}
  MODALS_PRIMARY_PARMNUM                    = 7;
  {$EXTERNALSYM MODALS_PRIMARY_PARMNUM}
  MODALS_DOMAIN_NAME_PARMNUM                = 8;
  {$EXTERNALSYM MODALS_DOMAIN_NAME_PARMNUM}
  MODALS_DOMAIN_ID_PARMNUM                  = 9;
  {$EXTERNALSYM MODALS_DOMAIN_ID_PARMNUM}
  MODALS_LOCKOUT_DURATION_PARMNUM           = 10;
  {$EXTERNALSYM MODALS_LOCKOUT_DURATION_PARMNUM}
  MODALS_LOCKOUT_OBSERVATION_WINDOW_PARMNUM = 11;
  {$EXTERNALSYM MODALS_LOCKOUT_OBSERVATION_WINDOW_PARMNUM}
  MODALS_LOCKOUT_THRESHOLD_PARMNUM          = 12;
  {$EXTERNALSYM MODALS_LOCKOUT_THRESHOLD_PARMNUM}

//
// the new infolevel counterparts of the old info level + parmnum
//

  MODALS_MIN_PASSWD_LEN_INFOLEVEL  = (PARMNUM_BASE_INFOLEVEL + MODALS_MIN_PASSWD_LEN_PARMNUM);
  {$EXTERNALSYM MODALS_MIN_PASSWD_LEN_INFOLEVEL}
  MODALS_MAX_PASSWD_AGE_INFOLEVEL  = (PARMNUM_BASE_INFOLEVEL + MODALS_MAX_PASSWD_AGE_PARMNUM);
  {$EXTERNALSYM MODALS_MAX_PASSWD_AGE_INFOLEVEL}
  MODALS_MIN_PASSWD_AGE_INFOLEVEL  = (PARMNUM_BASE_INFOLEVEL + MODALS_MIN_PASSWD_AGE_PARMNUM);
  {$EXTERNALSYM MODALS_MIN_PASSWD_AGE_INFOLEVEL}
  MODALS_FORCE_LOGOFF_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + MODALS_FORCE_LOGOFF_PARMNUM);
  {$EXTERNALSYM MODALS_FORCE_LOGOFF_INFOLEVEL}
  MODALS_PASSWD_HIST_LEN_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + MODALS_PASSWD_HIST_LEN_PARMNUM);
  {$EXTERNALSYM MODALS_PASSWD_HIST_LEN_INFOLEVEL}
  MODALS_ROLE_INFOLEVEL            = (PARMNUM_BASE_INFOLEVEL + MODALS_ROLE_PARMNUM);
  {$EXTERNALSYM MODALS_ROLE_INFOLEVEL}
  MODALS_PRIMARY_INFOLEVEL         = (PARMNUM_BASE_INFOLEVEL + MODALS_PRIMARY_PARMNUM);
  {$EXTERNALSYM MODALS_PRIMARY_INFOLEVEL}
  MODALS_DOMAIN_NAME_INFOLEVEL     = (PARMNUM_BASE_INFOLEVEL + MODALS_DOMAIN_NAME_PARMNUM);
  {$EXTERNALSYM MODALS_DOMAIN_NAME_INFOLEVEL}
  MODALS_DOMAIN_ID_INFOLEVEL       = (PARMNUM_BASE_INFOLEVEL + MODALS_DOMAIN_ID_PARMNUM);
  {$EXTERNALSYM MODALS_DOMAIN_ID_INFOLEVEL}

//
// Group Class
//

//
// Function Prototypes
//

function NetGroupAdd(servername: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupAdd}

function NetGroupAddUser(servername, GroupName, username: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupAddUser}

function NetGroupEnum(servername: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries: LPDWORD; resume_handle: PDWORD_PTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupEnum}

function NetGroupGetInfo(servername, groupname: LPCWSTR; level: DWORD; bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupGetInfo}

function NetGroupSetInfo(servername, groupname: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupSetInfo}

function NetGroupDel(servername: LPCWSTR; groupname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupDel}

function NetGroupDelUser(servername: LPCWSTR; GroupName: LPCWSTR; Username: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupDelUser}

function NetGroupGetUsers(servername, groupname: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries: LPDWORD; ResumeHandle: PDWORD_PTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupGetUsers}

function NetGroupSetUsers(servername, groupname: LPCWSTR; level: DWORD; buf: LPBYTE; totalentries: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGroupSetUsers}

//
//  Data Structures - Group
//

type
  LPGROUP_INFO_0 = ^GROUP_INFO_0;
  {$EXTERNALSYM LPGROUP_INFO_0}
  PGROUP_INFO_0 = ^GROUP_INFO_0;
  {$EXTERNALSYM PGROUP_INFO_0}
  _GROUP_INFO_0 = record
    grpi0_name: LPWSTR;
  end;
  {$EXTERNALSYM _GROUP_INFO_0}
  GROUP_INFO_0 = _GROUP_INFO_0;
  {$EXTERNALSYM GROUP_INFO_0}
  TGroupInfo0 = GROUP_INFO_0;
  PGroupInfo0 = PGROUP_INFO_0;

  LPGROUP_INFO_1 = ^GROUP_INFO_1;
  {$EXTERNALSYM LPGROUP_INFO_1}
  PGROUP_INFO_1 = ^GROUP_INFO_1;
  {$EXTERNALSYM PGROUP_INFO_1}
  _GROUP_INFO_1 = record
    grpi1_name: LPWSTR;
    grpi1_comment: LPWSTR;
  end;
  {$EXTERNALSYM _GROUP_INFO_1}
  GROUP_INFO_1 = _GROUP_INFO_1;
  {$EXTERNALSYM GROUP_INFO_1}
  TGroupInfo1 = GROUP_INFO_1;
  PGroupInfo1 = PGROUP_INFO_1;

  LPGROUP_INFO_2 = ^GROUP_INFO_2;
  {$EXTERNALSYM LPGROUP_INFO_2}
  PGROUP_INFO_2 = ^GROUP_INFO_2;
  {$EXTERNALSYM PGROUP_INFO_2}
  _GROUP_INFO_2 = record
    grpi2_name: LPWSTR;
    grpi2_comment: LPWSTR;
    grpi2_group_id: DWORD;
    grpi2_attributes: DWORD;
  end;
  {$EXTERNALSYM _GROUP_INFO_2}
  GROUP_INFO_2 = _GROUP_INFO_2;
  {$EXTERNALSYM GROUP_INFO_2}
  TGroupInfo2 = GROUP_INFO_2;
  PGroupInfo2 = PGROUP_INFO_2;

  LPGROUP_INFO_3 = ^GROUP_INFO_3;
  {$EXTERNALSYM LPGROUP_INFO_3}
  PGROUP_INFO_3 = ^GROUP_INFO_3;
  {$EXTERNALSYM PGROUP_INFO_3}
  _GROUP_INFO_3 = record
    grpi3_name: LPWSTR;
    grpi3_comment: LPWSTR;
    grpi3_group_sid: PSID;
    grpi3_attributes: DWORD;
  end;
  {$EXTERNALSYM _GROUP_INFO_3}
  GROUP_INFO_3 = _GROUP_INFO_3;
  {$EXTERNALSYM GROUP_INFO_3}
  TGroupInfo3 = GROUP_INFO_3;
  PGroupInfo3 = PGROUP_INFO_3;

  LPGROUP_INFO_1002 = ^GROUP_INFO_1002;
  {$EXTERNALSYM LPGROUP_INFO_1002}
  PGROUP_INFO_1002 = ^GROUP_INFO_1002;
  {$EXTERNALSYM PGROUP_INFO_1002}
  _GROUP_INFO_1002 = record
    grpi1002_comment: LPWSTR;
  end;
  {$EXTERNALSYM _GROUP_INFO_1002}
  GROUP_INFO_1002 = _GROUP_INFO_1002;
  {$EXTERNALSYM GROUP_INFO_1002}
  TGroupInfo1002 = GROUP_INFO_1002;
  PGroupInfo1002 = PGROUP_INFO_1002;

  LPGROUP_INFO_1005 = ^GROUP_INFO_1005;
  {$EXTERNALSYM LPGROUP_INFO_1005}
  PGROUP_INFO_1005 = ^GROUP_INFO_1005;
  {$EXTERNALSYM PGROUP_INFO_1005}
  _GROUP_INFO_1005 = record
    grpi1005_attributes: DWORD;
  end;
  {$EXTERNALSYM _GROUP_INFO_1005}
  GROUP_INFO_1005 = _GROUP_INFO_1005;
  {$EXTERNALSYM GROUP_INFO_1005}
  TGroupInfo1005 = GROUP_INFO_1005;
  PGroupInfo1005 = PGROUP_INFO_1005;

  LPGROUP_USERS_INFO_0 = ^GROUP_USERS_INFO_0;
  {$EXTERNALSYM LPGROUP_USERS_INFO_0}
  PGROUP_USERS_INFO_0 = ^GROUP_USERS_INFO_0;
  {$EXTERNALSYM PGROUP_USERS_INFO_0}
  _GROUP_USERS_INFO_0 = record
    grui0_name: LPWSTR;
  end;
  {$EXTERNALSYM _GROUP_USERS_INFO_0}
  GROUP_USERS_INFO_0 = _GROUP_USERS_INFO_0;
  {$EXTERNALSYM GROUP_USERS_INFO_0}
  TGroupUsersInfo0 = GROUP_USERS_INFO_0;
  PGroupUsersInfo0 = PGROUP_USERS_INFO_0;

  LPGROUP_USERS_INFO_1 = ^GROUP_USERS_INFO_1;
  {$EXTERNALSYM LPGROUP_USERS_INFO_1}
  PGROUP_USERS_INFO_1 = ^GROUP_USERS_INFO_1;
  {$EXTERNALSYM PGROUP_USERS_INFO_1}
  _GROUP_USERS_INFO_1 = record
    grui1_name: LPWSTR;
    grui1_attributes: DWORD;
  end;
  {$EXTERNALSYM _GROUP_USERS_INFO_1}
  GROUP_USERS_INFO_1 = _GROUP_USERS_INFO_1;
  {$EXTERNALSYM GROUP_USERS_INFO_1}
  TGroupUsersInfo1 = GROUP_USERS_INFO_1;
  PGroupUsersInfo1 = PGROUP_USERS_INFO_1;

//
// Special Values and Constants - Group
//

const
  GROUPIDMASK = $8000; // MSB set if uid refers to a group
  {$EXTERNALSYM GROUPIDMASK}

//
// Predefined group for all normal users, administrators and guests
// LOCAL is a special group for pinball local security.
//

  GROUP_SPECIALGRP_USERS  = WideString('USERS');
  {$EXTERNALSYM GROUP_SPECIALGRP_USERS}
  GROUP_SPECIALGRP_ADMINS = WideString('ADMINS');
  {$EXTERNALSYM GROUP_SPECIALGRP_ADMINS}
  GROUP_SPECIALGRP_GUESTS = WideString('GUESTS');
  {$EXTERNALSYM GROUP_SPECIALGRP_GUESTS}
  GROUP_SPECIALGRP_LOCAL  = WideString('LOCAL');
  {$EXTERNALSYM GROUP_SPECIALGRP_LOCAL}

//
// parmnum manifests for SetInfo calls (only comment is settable)
//

  GROUP_ALL_PARMNUM        = 0;
  {$EXTERNALSYM GROUP_ALL_PARMNUM}
  GROUP_NAME_PARMNUM       = 1;
  {$EXTERNALSYM GROUP_NAME_PARMNUM}
  GROUP_COMMENT_PARMNUM    = 2;
  {$EXTERNALSYM GROUP_COMMENT_PARMNUM}
  GROUP_ATTRIBUTES_PARMNUM = 3;
  {$EXTERNALSYM GROUP_ATTRIBUTES_PARMNUM}

//
// the new infolevel counterparts of the old info level + parmnum
//

  GROUP_ALL_INFOLEVEL        = (PARMNUM_BASE_INFOLEVEL + GROUP_ALL_PARMNUM);
  {$EXTERNALSYM GROUP_ALL_INFOLEVEL}
  GROUP_NAME_INFOLEVEL       = (PARMNUM_BASE_INFOLEVEL + GROUP_NAME_PARMNUM);
  {$EXTERNALSYM GROUP_NAME_INFOLEVEL}
  GROUP_COMMENT_INFOLEVEL    = (PARMNUM_BASE_INFOLEVEL + GROUP_COMMENT_PARMNUM);
  {$EXTERNALSYM GROUP_COMMENT_INFOLEVEL}
  GROUP_ATTRIBUTES_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + GROUP_ATTRIBUTES_PARMNUM);
  {$EXTERNALSYM GROUP_ATTRIBUTES_INFOLEVEL}
//  todo see GROUP_POSIX_ID_PARMNUM
//  GROUP_POSIX_ID_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + GROUP_POSIX_ID_PARMNUM);
//  {$EXTERNALSYM GROUP_POSIX_ID_INFOLEVEL}

//
// LocalGroup Class
//

//
// Function Prototypes
//

function NetLocalGroupAdd(servername: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupAdd}

function NetLocalGroupAddMember(servername, groupname: LPCWSTR; membersid: PSID): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupAddMember}

function NetLocalGroupEnum(servername: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries: LPDWORD; resumehandle: PDWORD_PTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupEnum}

function NetLocalGroupGetInfo(servername, groupname: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupGetInfo}

function NetLocalGroupSetInfo(servername, groupname: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupSetInfo}

function NetLocalGroupDel(servername: LPCWSTR; groupname: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupDel}

function NetLocalGroupDelMember(servername: LPCWSTR; groupname: LPCWSTR; membersid: PSID): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupDelMember}

function NetLocalGroupGetMembers(servername, localgroupname: LPCWSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries: LPDWORD; resumehandle: PDWORD_PTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupGetMembers}

function NetLocalGroupSetMembers(servername, groupname: LPCWSTR; level: DWORD; buf: LPBYTE; totalentries: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupSetMembers}

function NetLocalGroupAddMembers(servername, groupname: LPCWSTR; level: DWORD; buf: LPBYTE; totalentries: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupAddMembers}

function NetLocalGroupDelMembers(servername, groupname: LPCWSTR; level: DWORD; buf: LPBYTE; totalentries: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetLocalGroupDelMembers}

//
//  Data Structures - LocalGroup
//

type
  LPLOCALGROUP_INFO_0 = ^LOCALGROUP_INFO_0;
  {$EXTERNALSYM LPLOCALGROUP_INFO_0}
  PLOCALGROUP_INFO_0 = ^LOCALGROUP_INFO_0;
  {$EXTERNALSYM PLOCALGROUP_INFO_0}
  _LOCALGROUP_INFO_0 = record
    lgrpi0_name: LPWSTR;
  end;
  {$EXTERNALSYM _LOCALGROUP_INFO_0}
  LOCALGROUP_INFO_0 = _LOCALGROUP_INFO_0;
  {$EXTERNALSYM LOCALGROUP_INFO_0}
  TLocalGroupInfo0 = LOCALGROUP_INFO_0;
  PLocalGroupInfo0 = PLOCALGROUP_INFO_0;

  LPLOCALGROUP_INFO_1 = ^LOCALGROUP_INFO_1;
  {$EXTERNALSYM LPLOCALGROUP_INFO_1}
  PLOCALGROUP_INFO_1 = ^LOCALGROUP_INFO_1;
  {$EXTERNALSYM PLOCALGROUP_INFO_1}
  _LOCALGROUP_INFO_1 = record
    lgrpi1_name: LPWSTR;
    lgrpi1_comment: LPWSTR;
  end;
  {$EXTERNALSYM _LOCALGROUP_INFO_1}
  LOCALGROUP_INFO_1 = _LOCALGROUP_INFO_1;
  {$EXTERNALSYM LOCALGROUP_INFO_1}
  TLocalGroupInfo1 = LOCALGROUP_INFO_1;
  PLocalGroupInfo1 = PLOCALGROUP_INFO_1;

  LPLOCALGROUP_INFO_1002 = ^LOCALGROUP_INFO_1002;
  {$EXTERNALSYM LPLOCALGROUP_INFO_1002}
  PLOCALGROUP_INFO_1002 = ^LOCALGROUP_INFO_1002;
  {$EXTERNALSYM PLOCALGROUP_INFO_1002}
  _LOCALGROUP_INFO_1002 = record
    lgrpi1002_comment: LPWSTR;
  end;
  {$EXTERNALSYM _LOCALGROUP_INFO_1002}
  LOCALGROUP_INFO_1002 = _LOCALGROUP_INFO_1002;
  {$EXTERNALSYM LOCALGROUP_INFO_1002}
  TLocalGroupInfo1002 = LOCALGROUP_INFO_1002;
  PLocalGroupInfo1002 = PLOCALGROUP_INFO_1002;

  LPLOCALGROUP_MEMBERS_INFO_0 = ^LOCALGROUP_MEMBERS_INFO_0;
  {$EXTERNALSYM LPLOCALGROUP_MEMBERS_INFO_0}
  PLOCALGROUP_MEMBERS_INFO_0 = ^LOCALGROUP_MEMBERS_INFO_0;
  {$EXTERNALSYM PLOCALGROUP_MEMBERS_INFO_0}
  _LOCALGROUP_MEMBERS_INFO_0 = record
    lgrmi0_sid: PSID;
  end;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_0}
  LOCALGROUP_MEMBERS_INFO_0 = _LOCALGROUP_MEMBERS_INFO_0;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_0}
  TLocalGroupMembersInfo0 = LOCALGROUP_MEMBERS_INFO_0;
  PLocalGroupMembersInfo0 = PLOCALGROUP_MEMBERS_INFO_0;

  LPLOCALGROUP_MEMBERS_INFO_1 = ^LOCALGROUP_MEMBERS_INFO_1;
  {$EXTERNALSYM LPLOCALGROUP_MEMBERS_INFO_1}
  PLOCALGROUP_MEMBERS_INFO_1 = ^LOCALGROUP_MEMBERS_INFO_1;
  {$EXTERNALSYM PLOCALGROUP_MEMBERS_INFO_1}
  _LOCALGROUP_MEMBERS_INFO_1 = record
    lgrmi1_sid: PSID;
    lgrmi1_sidusage: SID_NAME_USE;
    lgrmi1_name: LPWSTR;
  end;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_1}
  LOCALGROUP_MEMBERS_INFO_1 = _LOCALGROUP_MEMBERS_INFO_1;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_1}
  TLocalGroupMembersInfo1 = LOCALGROUP_MEMBERS_INFO_1;
  PLocalGroupMembersInfo1 = PLOCALGROUP_MEMBERS_INFO_1;

  LPLOCALGROUP_MEMBERS_INFO_2 = ^LOCALGROUP_MEMBERS_INFO_2;
  {$EXTERNALSYM LPLOCALGROUP_MEMBERS_INFO_2}
  PLOCALGROUP_MEMBERS_INFO_2 = ^LOCALGROUP_MEMBERS_INFO_2;
  {$EXTERNALSYM PLOCALGROUP_MEMBERS_INFO_2}
  _LOCALGROUP_MEMBERS_INFO_2 = record
    lgrmi2_sid: PSID;
    lgrmi2_sidusage: SID_NAME_USE;
    lgrmi2_domainandname: LPWSTR;
  end;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_2}
  LOCALGROUP_MEMBERS_INFO_2 = _LOCALGROUP_MEMBERS_INFO_2;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_2}
  TLocalGroupMembersInfo2 = LOCALGROUP_MEMBERS_INFO_2;
  PLocalGroupMembersInfo2 = PLOCALGROUP_MEMBERS_INFO_2;

  LPLOCALGROUP_MEMBERS_INFO_3 = ^LOCALGROUP_MEMBERS_INFO_3;
  {$EXTERNALSYM LPLOCALGROUP_MEMBERS_INFO_3}
  PLOCALGROUP_MEMBERS_INFO_3 = ^LOCALGROUP_MEMBERS_INFO_3;
  {$EXTERNALSYM PLOCALGROUP_MEMBERS_INFO_3}
  _LOCALGROUP_MEMBERS_INFO_3 = record
    lgrmi3_domainandname: LPWSTR;
  end;
  {$EXTERNALSYM _LOCALGROUP_MEMBERS_INFO_3}
  LOCALGROUP_MEMBERS_INFO_3 = _LOCALGROUP_MEMBERS_INFO_3;
  {$EXTERNALSYM LOCALGROUP_MEMBERS_INFO_3}
  TLocalGroupMembersInfo3 = LOCALGROUP_MEMBERS_INFO_3;
  PLocalGroupMembersInfo3 = PLOCALGROUP_MEMBERS_INFO_3;

  LPLOCALGROUP_USERS_INFO_0 = ^LOCALGROUP_USERS_INFO_0;
  {$EXTERNALSYM LPLOCALGROUP_USERS_INFO_0}
  PLOCALGROUP_USERS_INFO_0 = ^LOCALGROUP_USERS_INFO_0;
  {$EXTERNALSYM PLOCALGROUP_USERS_INFO_0}
  _LOCALGROUP_USERS_INFO_0 = record
    lgrui0_name: LPWSTR;
  end;
  {$EXTERNALSYM _LOCALGROUP_USERS_INFO_0}
  LOCALGROUP_USERS_INFO_0 = _LOCALGROUP_USERS_INFO_0;
  {$EXTERNALSYM LOCALGROUP_USERS_INFO_0}
  TLocalGroupUsersInfo0 = LOCALGROUP_USERS_INFO_0;
  PLocalGroupUsersInfo0 = PLOCALGROUP_USERS_INFO_0;

const
  LOCALGROUP_NAME_PARMNUM    = 1;
  {$EXTERNALSYM LOCALGROUP_NAME_PARMNUM}
  LOCALGROUP_COMMENT_PARMNUM = 2;
  {$EXTERNALSYM LOCALGROUP_COMMENT_PARMNUM}

//
// Display Information APIs
//

function NetQueryDisplayInformation(ServerName: LPCWSTR; Level, Index, EntriesRequested, PreferredMaximumLength: DWORD; ReturnedEntryCount: LPDWORD; var SortedBuffer: PVOID): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetQueryDisplayInformation}

function NetGetDisplayInformationIndex(ServerName: LPCWSTR; Level: DWORD; Prefix: LPCWSTR; Index: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGetDisplayInformationIndex}

//
// QueryDisplayInformation levels

type
  PNET_DISPLAY_USER = ^NET_DISPLAY_USER;
  {$EXTERNALSYM PNET_DISPLAY_USER}
  _NET_DISPLAY_USER = record
    usri1_name: LPWSTR;
    usri1_comment: LPWSTR;
    usri1_flags: DWORD;
    usri1_full_name: LPWSTR;
    usri1_user_id: DWORD;
    usri1_next_index: DWORD;
  end;
  {$EXTERNALSYM _NET_DISPLAY_USER}
  NET_DISPLAY_USER = _NET_DISPLAY_USER;
  {$EXTERNALSYM NET_DISPLAY_USER}
  TNetDisplayUser = NET_DISPLAY_USER;
  PNetDisplayUser = PNET_DISPLAY_USER;

  PNET_DISPLAY_MACHINE = ^NET_DISPLAY_MACHINE;
  {$EXTERNALSYM PNET_DISPLAY_MACHINE}
  _NET_DISPLAY_MACHINE = record
    usri2_name: LPWSTR;
    usri2_comment: LPWSTR;
    usri2_flags: DWORD;
    usri2_user_id: DWORD;
    usri2_next_index: DWORD;
  end;
  {$EXTERNALSYM _NET_DISPLAY_MACHINE}
  NET_DISPLAY_MACHINE = _NET_DISPLAY_MACHINE;
  {$EXTERNALSYM NET_DISPLAY_MACHINE}
  TNetDisplayMachine = NET_DISPLAY_MACHINE;
  PNetDisplayMachine = PNET_DISPLAY_MACHINE;

  PNET_DISPLAY_GROUP = ^NET_DISPLAY_GROUP;
  {$EXTERNALSYM PNET_DISPLAY_GROUP}
  _NET_DISPLAY_GROUP = record
    grpi3_name: LPWSTR;
    grpi3_comment: LPWSTR;
    grpi3_group_id: DWORD;
    grpi3_attributes: DWORD;
    grpi3_next_index: DWORD;
  end;
  {$EXTERNALSYM _NET_DISPLAY_GROUP}
  NET_DISPLAY_GROUP = _NET_DISPLAY_GROUP;
  {$EXTERNALSYM NET_DISPLAY_GROUP}
  TNetDisplayGroup = NET_DISPLAY_GROUP;
  PNetDisplayGroup = PNET_DISPLAY_GROUP;

//
// Access Class
//

//
// Function Prototypes - Access
//
//
// The NetAccess APIs are only available to downlevel
//

//#define NetAccessAdd RxNetAccessAdd

function NetAccessAdd(servername: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAccessAdd}

//#define NetAccessEnum RxNetAccessEnum

function NetAccessEnum(servername, BasePath: LPCWSTR; Recursive, level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread, totalentries, resume_handle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAccessEnum}

//#define NetAccessGetInfo RxNetAccessGetInfo

function NetAccessGetInfo(servername, resource: LPCWSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAccessGetInfo}

//#define NetAccessSetInfo RxNetAccessSetInfo

function NetAccessSetInfo(servername, resource: LPCWSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAccessSetInfo}

//#define NetAccessDel RxNetAccessDel

function NetAccessDel(servername: LPCWSTR; resource: LPCWSTR): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAccessDel}

//#define NetAccessGetUserPerms RxNetAccessGetUserPerms

function NetAccessGetUserPerms(servername, UGname, resource: LPCWSTR; Perms: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetAccessGetUserPerms}

//
// Data Structures - Access
//

type
  LPACCESS_INFO_0 = ^ACCESS_INFO_0;
  {$EXTERNALSYM LPACCESS_INFO_0}
  PACCESS_INFO_0 = ^ACCESS_INFO_0;
  {$EXTERNALSYM PACCESS_INFO_0}
  _ACCESS_INFO_0 = record
    acc0_resource_name: LPWSTR;
  end;
  {$EXTERNALSYM _ACCESS_INFO_0}
  ACCESS_INFO_0 = _ACCESS_INFO_0;
  {$EXTERNALSYM ACCESS_INFO_0}
  TAccessInfo0 = ACCESS_INFO_0;
  PAccessInfo0 = PACCESS_INFO_0;

  LPACCESS_INFO_1 = ^ACCESS_INFO_1;
  {$EXTERNALSYM LPACCESS_INFO_1}
  PACCESS_INFO_1 = ^ACCESS_INFO_1;
  {$EXTERNALSYM PACCESS_INFO_1}
  _ACCESS_INFO_1 = record
    acc1_resource_name: LPWSTR;
    acc1_attr: DWORD;
    acc1_count: DWORD;
  end;
  {$EXTERNALSYM _ACCESS_INFO_1}
  ACCESS_INFO_1 = _ACCESS_INFO_1;
  {$EXTERNALSYM ACCESS_INFO_1}
  TAccessInfo1 = ACCESS_INFO_1;
  PAccessInfo1 = PACCESS_INFO_1;

  LPACCESS_INFO_1002 = ^ACCESS_INFO_1002;
  {$EXTERNALSYM LPACCESS_INFO_1002}
  PACCESS_INFO_1002 = ^ACCESS_INFO_1002;
  {$EXTERNALSYM PACCESS_INFO_1002}
  _ACCESS_INFO_1002 = record
    acc1002_attr: DWORD;
  end;
  {$EXTERNALSYM _ACCESS_INFO_1002}
  ACCESS_INFO_1002 = _ACCESS_INFO_1002;
  {$EXTERNALSYM ACCESS_INFO_1002}
  TAccessInfo1002 = ACCESS_INFO_1002;
  PAccessInfo1002 = PACCESS_INFO_1002;

  LPACCESS_LIST = ^ACCESS_LIST;
  {$EXTERNALSYM LPACCESS_LIST}
  PACCESS_LIST = ^ACCESS_LIST;
  {$EXTERNALSYM PACCESS_LIST}
  _ACCESS_LIST = record
    acl_ugname: LPWSTR;
    acl_access: DWORD;
  end;
  {$EXTERNALSYM _ACCESS_LIST}
  ACCESS_LIST = _ACCESS_LIST;
  {$EXTERNALSYM ACCESS_LIST}
  TAccessList = ACCESS_LIST;
  PAccessList = PACCESS_LIST;

//
// Special Values and Constants - Access
//

//
// Maximum number of permission entries for each resource.
//

const
  MAXPERMENTRIES = 64;
  {$EXTERNALSYM MAXPERMENTRIES}

//
//  Bit values for the access permissions.  ACCESS_ALL is a handy
//  way to specify maximum permissions.  These are used in
//  acl_access field of access_list structures.
//

  ACCESS_READ   = $01;
  {$EXTERNALSYM ACCESS_READ}
  ACCESS_WRITE  = $02;
  {$EXTERNALSYM ACCESS_WRITE}
  ACCESS_CREATE = $04;
  {$EXTERNALSYM ACCESS_CREATE}
  ACCESS_EXEC   = $08;
  {$EXTERNALSYM ACCESS_EXEC}
  ACCESS_DELETE = $10;
  {$EXTERNALSYM ACCESS_DELETE}
  ACCESS_ATRIB  = $20;
  {$EXTERNALSYM ACCESS_ATRIB}
  ACCESS_PERM   = $40;
  {$EXTERNALSYM ACCESS_PERM}

  ACCESS_GROUP = $8000;
  {$EXTERNALSYM ACCESS_GROUP}

  ACCESS_NONE = 0;
  {$EXTERNALSYM ACCESS_NONE}
  ACCESS_ALL  = (ACCESS_READ or ACCESS_WRITE or ACCESS_CREATE or ACCESS_EXEC or ACCESS_DELETE or ACCESS_ATRIB or ACCESS_PERM);
  {$EXTERNALSYM ACCESS_ALL}
  
//
// Bit values for the acc1_attr field of the ACCESS_INFO_1 structure.
//

  ACCESS_AUDIT = $1;
  {$EXTERNALSYM ACCESS_AUDIT}

  ACCESS_SUCCESS_OPEN   = $10;
  {$EXTERNALSYM ACCESS_SUCCESS_OPEN}
  ACCESS_SUCCESS_WRITE  = $20;
  {$EXTERNALSYM ACCESS_SUCCESS_WRITE}
  ACCESS_SUCCESS_DELETE = $40;
  {$EXTERNALSYM ACCESS_SUCCESS_DELETE}
  ACCESS_SUCCESS_ACL    = $80;
  {$EXTERNALSYM ACCESS_SUCCESS_ACL}
  ACCESS_SUCCESS_MASK   = $F0;
  {$EXTERNALSYM ACCESS_SUCCESS_MASK}

  ACCESS_FAIL_OPEN   = $100;
  {$EXTERNALSYM ACCESS_FAIL_OPEN}
  ACCESS_FAIL_WRITE  = $200;
  {$EXTERNALSYM ACCESS_FAIL_WRITE}
  ACCESS_FAIL_DELETE = $400;
  {$EXTERNALSYM ACCESS_FAIL_DELETE}
  ACCESS_FAIL_ACL    = $800;
  {$EXTERNALSYM ACCESS_FAIL_ACL}
  ACCESS_FAIL_MASK   = $F00;
  {$EXTERNALSYM ACCESS_FAIL_MASK}

  ACCESS_FAIL_SHIFT = 4;
  {$EXTERNALSYM ACCESS_FAIL_SHIFT}

//
// Parmnum value for NetAccessSetInfo.
//

  ACCESS_RESOURCE_NAME_PARMNUM = 1;
  {$EXTERNALSYM ACCESS_RESOURCE_NAME_PARMNUM}
  ACCESS_ATTR_PARMNUM          = 2;
  {$EXTERNALSYM ACCESS_ATTR_PARMNUM}
  ACCESS_COUNT_PARMNUM         = 3;
  {$EXTERNALSYM ACCESS_COUNT_PARMNUM}
  ACCESS_ACCESS_LIST_PARMNUM   = 4;
  {$EXTERNALSYM ACCESS_ACCESS_LIST_PARMNUM}

//
// the new infolevel counterparts of the old info level + parmnum
//

  ACCESS_RESOURCE_NAME_INFOLEVEL = (PARMNUM_BASE_INFOLEVEL + ACCESS_RESOURCE_NAME_PARMNUM);
  {$EXTERNALSYM ACCESS_RESOURCE_NAME_INFOLEVEL}
  ACCESS_ATTR_INFOLEVEL          = (PARMNUM_BASE_INFOLEVEL + ACCESS_ATTR_PARMNUM);
  {$EXTERNALSYM ACCESS_ATTR_INFOLEVEL}
  ACCESS_COUNT_INFOLEVEL         = (PARMNUM_BASE_INFOLEVEL + ACCESS_COUNT_PARMNUM);
  {$EXTERNALSYM ACCESS_COUNT_INFOLEVEL}
  ACCESS_ACCESS_LIST_INFOLEVEL   = (PARMNUM_BASE_INFOLEVEL + ACCESS_ACCESS_LIST_PARMNUM);
  {$EXTERNALSYM ACCESS_ACCESS_LIST_INFOLEVEL}

//
// ACCESS_LETTERS defines a letter for each bit position in
// the acl_access field of struct access_list.  Note that some
// bits have a corresponding letter of ' ' (space).
//

  ACCESS_LETTERS = 'RWCXDAP         ';
  {$EXTERNALSYM ACCESS_LETTERS}

//    ********************************
//
//    Password Checking API structures
//
//    ********************************


//
//    What kind of password checking is to be performed?
//        NetValidateAuthentication : Check if the authentication can be done
//        NetValidatePasswordChange: Check if the password can be changed
//        NetValidatePasswordReset: Reset the password to the given value
//

type
  _NET_VALIDATE_PASSWORD_TYPE = (
    NetValidateFiller0,
    NetValidateAuthentication,
    NetValidatePasswordChange,
    NetValidatePasswordReset);
  {$EXTERNALSYM _NET_VALIDATE_PASSWORD_TYPE}
  NET_VALIDATE_PASSWORD_TYPE = _NET_VALIDATE_PASSWORD_TYPE;
  {$EXTERNALSYM NET_VALIDATE_PASSWORD_TYPE}
  PNET_VALIDATE_PASSWORD_TYPE = ^NET_VALIDATE_PASSWORD_TYPE;
  {$EXTERNALSYM PNET_VALIDATE_PASSWORD_TYPE}
  TNetValidatePasswordType = NET_VALIDATE_PASSWORD_TYPE;
  PNetValidatePasswordType = PNET_VALIDATE_PASSWORD_TYPE;

//
//    Structure to keep the password hash
//

  _NET_VALIDATE_PASSWORD_HASH = record
    Length: ULONG;
    Hash: LPBYTE;
  end;
  {$EXTERNALSYM _NET_VALIDATE_PASSWORD_HASH}
  NET_VALIDATE_PASSWORD_HASH = _NET_VALIDATE_PASSWORD_HASH;
  {$EXTERNALSYM NET_VALIDATE_PASSWORD_HASH}
  PNET_VALIDATE_PASSWORD_HASH = ^NET_VALIDATE_PASSWORD_HASH;
  {$EXTERNALSYM PNET_VALIDATE_PASSWORD_HASH}
  TNetValidatePasswordHash = NET_VALIDATE_PASSWORD_HASH;
  PNetValidatePasswordHash = PNET_VALIDATE_PASSWORD_HASH;

// To be used with PresentFields member of NET_VALIDATE_PERSISTED_FIELDS

const
  NET_VALIDATE_PASSWORD_LAST_SET         = $00000001;
  {$EXTERNALSYM NET_VALIDATE_PASSWORD_LAST_SET}
  NET_VALIDATE_BAD_PASSWORD_TIME         = $00000002;
  {$EXTERNALSYM NET_VALIDATE_BAD_PASSWORD_TIME}
  NET_VALIDATE_LOCKOUT_TIME              = $00000004;
  {$EXTERNALSYM NET_VALIDATE_LOCKOUT_TIME}
  NET_VALIDATE_BAD_PASSWORD_COUNT        = $00000008;
  {$EXTERNALSYM NET_VALIDATE_BAD_PASSWORD_COUNT}
  NET_VALIDATE_PASSWORD_HISTORY_LENGTH   = $00000010;
  {$EXTERNALSYM NET_VALIDATE_PASSWORD_HISTORY_LENGTH}
  NET_VALIDATE_PASSWORD_HISTORY          = $00000020;
  {$EXTERNALSYM NET_VALIDATE_PASSWORD_HISTORY}

//#if !defined(_WINBASE_) && !defined(_FILETIME_)
//#define _FILETIME_
//typedef struct _FILETIME
//{/
//    DWORD dwLowDateTime;
//    DWORD dwHighDateTime;
//} FILETIME, FAR * LPFILETIME, *PFILETIME;
//#endif

//
//    Structure to keep information about the password and related things.
//        Present Fields: (used only in output args) which fields are changed.
//            See the constants above.
//        PasswordLastSet: When the password is last set.
//        BadPasswordTime: When the password was incorrect for the last time.
//        LockoutTime: When the account is locked out. If the account is not locked out
//            it is 0.
//        BadPasswordCount: How many times the password has given incorrectly in the
//            Observation Window.
//        PasswordHistoryLength: How many passwords are kept in the history
//        PasswordHistory: Password hashes that are in the history
//

type
  _NET_VALIDATE_PERSISTED_FIELDS = record
    PresentFields: ULONG;
    PasswordLastSet: FILETIME;
    BadPasswordTime: FILETIME;
    LockoutTime: FILETIME;
    BadPasswordCount: ULONG;
    PasswordHistoryLength: ULONG;
    PasswordHistory: PNET_VALIDATE_PASSWORD_HASH;
  end;
  {$EXTERNALSYM _NET_VALIDATE_PERSISTED_FIELDS}
  NET_VALIDATE_PERSISTED_FIELDS = _NET_VALIDATE_PERSISTED_FIELDS;
  {$EXTERNALSYM NET_VALIDATE_PERSISTED_FIELDS}
  PNET_VALIDATE_PERSISTED_FIELDS = ^NET_VALIDATE_PERSISTED_FIELDS;
  {$EXTERNALSYM PNET_VALIDATE_PERSISTED_FIELDS}
  TNetValidatePersistedFields = NET_VALIDATE_PERSISTED_FIELDS;
  PNetValidatePersistedFields = PNET_VALIDATE_PERSISTED_FIELDS;

//
//    Output Arg
//        ChangedPersistedFields: Any changes to the password related info
//        ValidationStatus: Shows the result of the request
//

  _NET_VALIDATE_OUTPUT_ARG = record
    ChangedPersistedFields: NET_VALIDATE_PERSISTED_FIELDS;
    ValidationStatus: NET_API_STATUS;
  end;
  {$EXTERNALSYM _NET_VALIDATE_OUTPUT_ARG}
  NET_VALIDATE_OUTPUT_ARG = _NET_VALIDATE_OUTPUT_ARG;
  {$EXTERNALSYM NET_VALIDATE_OUTPUT_ARG}
  PNET_VALIDATE_OUTPUT_ARG = ^NET_VALIDATE_OUTPUT_ARG;
  {$EXTERNALSYM PNET_VALIDATE_OUTPUT_ARG}
  TNetValidateOutputArg = NET_VALIDATE_OUTPUT_ARG;
  PNetValidateOutputArg = PNET_VALIDATE_OUTPUT_ARG;  

//
//    If authentication type of password check is to be made,
//        this kind of input must be used
//        
//    InputPersistedFields: Information about the account to be logged into
//    PasswordMatched: Indicates the result of the application's authentication of the supplied password 
//

  _NET_VALIDATE_AUTHENTICATION_INPUT_ARG = record
    InputPersistedFields: NET_VALIDATE_PERSISTED_FIELDS;
    PasswordMatched: BOOLEAN;
  end;
  {$EXTERNALSYM _NET_VALIDATE_AUTHENTICATION_INPUT_ARG}
  NET_VALIDATE_AUTHENTICATION_INPUT_ARG = _NET_VALIDATE_AUTHENTICATION_INPUT_ARG;
  {$EXTERNALSYM NET_VALIDATE_AUTHENTICATION_INPUT_ARG}
  PNET_VALIDATE_AUTHENTICATION_INPUT_ARG = ^NET_VALIDATE_AUTHENTICATION_INPUT_ARG;
  {$EXTERNALSYM PNET_VALIDATE_AUTHENTICATION_INPUT_ARG}
  TNetValidateAuthenticationInputArg = NET_VALIDATE_AUTHENTICATION_INPUT_ARG;
  PNetValidateAuthenticationInputArg = PNET_VALIDATE_AUTHENTICATION_INPUT_ARG;

//
//    If password change type of check is to be made,
//        this kind of input must be used
//
//    InputPersistedFields: Information about the account to be logged into
//    ClearPassword: The string which password is going to be
//    UserAccountName: Name of the user account
//    HashedPassword: Hash of the string that the password is going to be
//    PasswordMatch: denotes if the old password supplied by user matched or not
//

  _NET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG = record
    InputPersistedFields: NET_VALIDATE_PERSISTED_FIELDS;
    ClearPassword: LPWSTR;
    UserAccountName: LPWSTR;
    HashedPassword: NET_VALIDATE_PASSWORD_HASH;
    PasswordMatch: BOOLEAN;
  end;
  {$EXTERNALSYM _NET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG}
  NET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG = _NET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG;
  {$EXTERNALSYM NET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG}
  PNET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG = ^NET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG;
  {$EXTERNALSYM PNET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG}
  TNetValidatePasswordChangeInputArg = NET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG;
  PNetValidatePasswordChangeInputArg = PNET_VALIDATE_PASSWORD_CHANGE_INPUT_ARG;

//
//    If password reset type of check is to be made,
//        this kind of input must be used
//
//    InputPersistedFields: Information about the account to be logged into
//    ClearPassword: The string which password is going to be
//    UserAccountName: Name of the user account
//    HashedPassword: Hash of the string that the password is going to be
//    PasswordMustChangeAtNextLogon: Password must change for the user to be logged in
//    ClearLockout: If the account was locked out, this field can be used to clear lockout
//

  _NET_VALIDATE_PASSWORD_RESET_INPUT_ARG = record
    InputPersistedFields: NET_VALIDATE_PERSISTED_FIELDS;
    ClearPassword: LPWSTR;
    UserAccountName: LPWSTR;
    HashedPassword: NET_VALIDATE_PASSWORD_HASH;
    PasswordMustChangeAtNextLogon: BOOLEAN;
    ClearLockout: BOOLEAN;
  end;
  {$EXTERNALSYM _NET_VALIDATE_PASSWORD_RESET_INPUT_ARG}
  NET_VALIDATE_PASSWORD_RESET_INPUT_ARG = _NET_VALIDATE_PASSWORD_RESET_INPUT_ARG;
  {$EXTERNALSYM NET_VALIDATE_PASSWORD_RESET_INPUT_ARG}
  PNET_VALIDATE_PASSWORD_RESET_INPUT_ARG = ^NET_VALIDATE_PASSWORD_RESET_INPUT_ARG;
  {$EXTERNALSYM PNET_VALIDATE_PASSWORD_RESET_INPUT_ARG}
  TNetValidatePasswordResetInputArg = NET_VALIDATE_PASSWORD_RESET_INPUT_ARG;
  PNetValidatePasswordResetInputArg = PNET_VALIDATE_PASSWORD_RESET_INPUT_ARG;  

//
//    Password Checking API structures end here
//

function NetValidatePasswordPolicy(ServerName: LPWSTR; Qualifier: LPVOID; ValidationType: NET_VALIDATE_PASSWORD_TYPE;
  InputArg: LPVOID; var OutputArg: LPVOID): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetValidatePasswordPolicy}

function NetValidatePasswordPolicyFree(var OutputArg: LPVOID): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetValidatePasswordPolicyFree}

//
// Domain Class
//

//
// Function Prototypes - Domain
//

function NetGetDCName(servername, domainname: LPCWSTR; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGetDCName}

function NetGetAnyDCName(servername, domainname: LPCWSTR; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetGetAnyDCName}

function I_NetLogonControl(ServerName: LPCWSTR; FunctionCode, QueryLevel: DWORD; var Buffer: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_NetLogonControl}

function I_NetLogonControl2(ServerName: LPCWSTR; FunctionCode, QueryLevel: DWORD; Data: LPBYTE; var Buffer: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM I_NetLogonControl2}

function NetEnumerateTrustedDomains(ServerName: LPWSTR; var DomainNames: LPWSTR): NTSTATUS; stdcall;
{$EXTERNALSYM NetEnumerateTrustedDomains}

//
// Special Values and Constants - Domain
//

//
// FunctionCode values for I_NetLogonControl.
//
// NOTE : if you change the following NETLOGON_CONTROL_* values,
// change them in net\svcdlls\logonsrv\logon.idl file also.
//

const
  NETLOGON_CONTROL_QUERY            = 1; // No-op: just query
  {$EXTERNALSYM NETLOGON_CONTROL_QUERY}
  NETLOGON_CONTROL_REPLICATE        = 2; // Force replicate on BDC
  {$EXTERNALSYM NETLOGON_CONTROL_REPLICATE}
  NETLOGON_CONTROL_SYNCHRONIZE      = 3; // Force synchronize on BDC
  {$EXTERNALSYM NETLOGON_CONTROL_SYNCHRONIZE}
  NETLOGON_CONTROL_PDC_REPLICATE    = 4; // Force PDC to broadcast change
  {$EXTERNALSYM NETLOGON_CONTROL_PDC_REPLICATE}
  NETLOGON_CONTROL_REDISCOVER       = 5; // Force to re-discover trusted domain DCs
  {$EXTERNALSYM NETLOGON_CONTROL_REDISCOVER}
  NETLOGON_CONTROL_TC_QUERY         = 6; // Query status of specified trusted channel status
  {$EXTERNALSYM NETLOGON_CONTROL_TC_QUERY}
  NETLOGON_CONTROL_TRANSPORT_NOTIFY = 7; // Notify netlogon that a new transport has come online
  {$EXTERNALSYM NETLOGON_CONTROL_TRANSPORT_NOTIFY}
  NETLOGON_CONTROL_FIND_USER        = 8; // Find named user in a trusted domain
  {$EXTERNALSYM NETLOGON_CONTROL_FIND_USER}
  NETLOGON_CONTROL_CHANGE_PASSWORD  = 9; // Change machine password on a secure channel to a trusted domain
  {$EXTERNALSYM NETLOGON_CONTROL_CHANGE_PASSWORD}
  NETLOGON_CONTROL_TC_VERIFY        = 10; // Verify status of specified trusted channel
  {$EXTERNALSYM NETLOGON_CONTROL_TC_VERIFY}
  NETLOGON_CONTROL_FORCE_DNS_REG    = 11; // Force DNS re-registration of all registered records
  {$EXTERNALSYM NETLOGON_CONTROL_FORCE_DNS_REG}
  NETLOGON_CONTROL_QUERY_DNS_REG    = 12; // Query the status of DNS updates
  {$EXTERNALSYM NETLOGON_CONTROL_QUERY_DNS_REG}

// Debug function codes

  NETLOGON_CONTROL_UNLOAD_NETLOGON_DLL = $FFFB;
  {$EXTERNALSYM NETLOGON_CONTROL_UNLOAD_NETLOGON_DLL}
  NETLOGON_CONTROL_BACKUP_CHANGE_LOG   = $FFFC;
  {$EXTERNALSYM NETLOGON_CONTROL_BACKUP_CHANGE_LOG}
  NETLOGON_CONTROL_TRUNCATE_LOG        = $FFFD;
  {$EXTERNALSYM NETLOGON_CONTROL_TRUNCATE_LOG}
  NETLOGON_CONTROL_SET_DBFLAG          = $FFFE;
  {$EXTERNALSYM NETLOGON_CONTROL_SET_DBFLAG}
  NETLOGON_CONTROL_BREAKPOINT          = $FFFF;
  {$EXTERNALSYM NETLOGON_CONTROL_BREAKPOINT}

//
// Query level 1 for I_NetLogonControl
//

type
  PNETLOGON_INFO_1 = ^NETLOGON_INFO_1;
  {$EXTERNALSYM PNETLOGON_INFO_1}
  _NETLOGON_INFO_1 = record
    netlog1_flags: DWORD;
    netlog1_pdc_connection_status: NET_API_STATUS;
  end;
  {$EXTERNALSYM _NETLOGON_INFO_1}
  NETLOGON_INFO_1 = _NETLOGON_INFO_1;
  {$EXTERNALSYM NETLOGON_INFO_1}
  TNetLogonInfo1 = NETLOGON_INFO_1;
  PNetLogonInfo1 = PNETLOGON_INFO_1;

  PNETLOGON_INFO_2 = ^NETLOGON_INFO_2;
  {$EXTERNALSYM PNETLOGON_INFO_2}
  _NETLOGON_INFO_2 = record
    netlog2_flags: DWORD;
    //
    // If NETLOGON_VERIFY_STATUS_RETURNED bit is set in
    //  netlog2_flags, the following field will return
    //  the status of trust verification. Otherwise,
    //  the field will return the status of the secure
    //  channel to the primary domain of the machine
    //  (useful for BDCs only).
    //
    netlog2_pdc_connection_status: NET_API_STATUS;
    netlog2_trusted_dc_name: LPWSTR;
    netlog2_tc_connection_status: NET_API_STATUS;
  end;
  {$EXTERNALSYM _NETLOGON_INFO_2}
  NETLOGON_INFO_2 = _NETLOGON_INFO_2;
  {$EXTERNALSYM NETLOGON_INFO_2}
  TNetLogonInfo2 = NETLOGON_INFO_2;
  PNetLogonInfo2 = PNETLOGON_INFO_2;

  PNETLOGON_INFO_3 = ^NETLOGON_INFO_3;
  {$EXTERNALSYM PNETLOGON_INFO_3}
  _NETLOGON_INFO_3 = record
    netlog3_flags: DWORD;
    netlog3_logon_attempts: DWORD;
    netlog3_reserved1: DWORD;
    netlog3_reserved2: DWORD;
    netlog3_reserved3: DWORD;
    netlog3_reserved4: DWORD;
    netlog3_reserved5: DWORD;
  end;
  {$EXTERNALSYM _NETLOGON_INFO_3}
  NETLOGON_INFO_3 = _NETLOGON_INFO_3;
  {$EXTERNALSYM NETLOGON_INFO_3}
  TNetLogonInfo3 = NETLOGON_INFO_3;
  PNetLogonInfo3 = PNETLOGON_INFO_3;

  PNETLOGON_INFO_4 = ^NETLOGON_INFO_4;
  {$EXTERNALSYM PNETLOGON_INFO_4}
  _NETLOGON_INFO_4 = record
    netlog4_trusted_dc_name: LPWSTR;
    netlog4_trusted_domain_name: LPWSTR;
  end;
  {$EXTERNALSYM _NETLOGON_INFO_4}
  NETLOGON_INFO_4 = _NETLOGON_INFO_4;
  {$EXTERNALSYM NETLOGON_INFO_4}
  TNetLogonInfo4 = NETLOGON_INFO_4;
  PNetLogonInfo4 = PNETLOGON_INFO_4;

//
// Values of netlog1_flags
//

const
  NETLOGON_REPLICATION_NEEDED      = $01; // Database is out of date
  {$EXTERNALSYM NETLOGON_REPLICATION_NEEDED}
  NETLOGON_REPLICATION_IN_PROGRESS = $02; // Replication is happening now
  {$EXTERNALSYM NETLOGON_REPLICATION_IN_PROGRESS}
  NETLOGON_FULL_SYNC_REPLICATION   = $04; // full sync replication required/progress
  {$EXTERNALSYM NETLOGON_FULL_SYNC_REPLICATION}
  NETLOGON_REDO_NEEDED             = $08; // Redo of previous replication needed
  {$EXTERNALSYM NETLOGON_REDO_NEEDED}
  NETLOGON_HAS_IP                  = $10; // The trusted domain DC has an IP address
  {$EXTERNALSYM NETLOGON_HAS_IP}
  NETLOGON_HAS_TIMESERV            = $20; // The trusted domain DC runs the Windows Time Service
  {$EXTERNALSYM NETLOGON_HAS_TIMESERV}
  NETLOGON_DNS_UPDATE_FAILURE      = $40; // There was a failure in the last update for one of the DNS records
  {$EXTERNALSYM NETLOGON_DNS_UPDATE_FAILURE}
  NETLOGON_VERIFY_STATUS_RETURNED  = $80; // Trust verification status returned in netlog2_pdc_connection_status
  {$EXTERNALSYM NETLOGON_VERIFY_STATUS_RETURNED}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetUserAdd: Pointer;

function NetUserAdd;
begin
  GetProcedureAddress(_NetUserAdd, netapi32, 'NetUserAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserAdd]
  end;
end;
{$ELSE}
function NetUserAdd; external netapi32 name 'NetUserAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserEnum: Pointer;

function NetUserEnum;
begin
  GetProcedureAddress(_NetUserEnum, netapi32, 'NetUserEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserEnum]
  end;
end;
{$ELSE}
function NetUserEnum; external netapi32 name 'NetUserEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserGetInfo: Pointer;

function NetUserGetInfo;
begin
  GetProcedureAddress(_NetUserGetInfo, netapi32, 'NetUserGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserGetInfo]
  end;
end;
{$ELSE}
function NetUserGetInfo; external netapi32 name 'NetUserGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserSetInfo: Pointer;

function NetUserSetInfo;
begin
  GetProcedureAddress(_NetUserSetInfo, netapi32, 'NetUserSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserSetInfo]
  end;
end;
{$ELSE}
function NetUserSetInfo; external netapi32 name 'NetUserSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserDel: Pointer;

function NetUserDel;
begin
  GetProcedureAddress(_NetUserDel, netapi32, 'NetUserDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserDel]
  end;
end;
{$ELSE}
function NetUserDel; external netapi32 name 'NetUserDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserGetGroups: Pointer;

function NetUserGetGroups;
begin
  GetProcedureAddress(_NetUserGetGroups, netapi32, 'NetUserGetGroups');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserGetGroups]
  end;
end;
{$ELSE}
function NetUserGetGroups; external netapi32 name 'NetUserGetGroups';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserSetGroups: Pointer;

function NetUserSetGroups;
begin
  GetProcedureAddress(_NetUserSetGroups, netapi32, 'NetUserSetGroups');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserSetGroups]
  end;
end;
{$ELSE}
function NetUserSetGroups; external netapi32 name 'NetUserSetGroups';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserGetLocalGroups: Pointer;

function NetUserGetLocalGroups;
begin
  GetProcedureAddress(_NetUserGetLocalGroups, netapi32, 'NetUserGetLocalGroups');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserGetLocalGroups]
  end;
end;
{$ELSE}
function NetUserGetLocalGroups; external netapi32 name 'NetUserGetLocalGroups';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserModalsGet: Pointer;

function NetUserModalsGet;
begin
  GetProcedureAddress(_NetUserModalsGet, netapi32, 'NetUserModalsGet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserModalsGet]
  end;
end;
{$ELSE}
function NetUserModalsGet; external netapi32 name 'NetUserModalsGet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserModalsSet: Pointer;

function NetUserModalsSet;
begin
  GetProcedureAddress(_NetUserModalsSet, netapi32, 'NetUserModalsSet');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserModalsSet]
  end;
end;
{$ELSE}
function NetUserModalsSet; external netapi32 name 'NetUserModalsSet';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetUserChangePassword: Pointer;

function NetUserChangePassword;
begin
  GetProcedureAddress(_NetUserChangePassword, netapi32, 'NetUserChangePassword');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetUserChangePassword]
  end;
end;
{$ELSE}
function NetUserChangePassword; external netapi32 name 'NetUserChangePassword';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupAdd: Pointer;

function NetGroupAdd;
begin
  GetProcedureAddress(_NetGroupAdd, netapi32, 'NetGroupAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupAdd]
  end;
end;
{$ELSE}
function NetGroupAdd; external netapi32 name 'NetGroupAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupAddUser: Pointer;

function NetGroupAddUser;
begin
  GetProcedureAddress(_NetGroupAddUser, netapi32, 'NetGroupAddUser');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupAddUser]
  end;
end;
{$ELSE}
function NetGroupAddUser; external netapi32 name 'NetGroupAddUser';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupEnum: Pointer;

function NetGroupEnum;
begin
  GetProcedureAddress(_NetGroupEnum, netapi32, 'NetGroupEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupEnum]
  end;
end;
{$ELSE}
function NetGroupEnum; external netapi32 name 'NetGroupEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupGetInfo: Pointer;

function NetGroupGetInfo;
begin
  GetProcedureAddress(_NetGroupGetInfo, netapi32, 'NetGroupGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupGetInfo]
  end;
end;
{$ELSE}
function NetGroupGetInfo; external netapi32 name 'NetGroupGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupSetInfo: Pointer;

function NetGroupSetInfo;
begin
  GetProcedureAddress(_NetGroupSetInfo, netapi32, 'NetGroupSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupSetInfo]
  end;
end;
{$ELSE}
function NetGroupSetInfo; external netapi32 name 'NetGroupSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupDel: Pointer;

function NetGroupDel;
begin
  GetProcedureAddress(_NetGroupDel, netapi32, 'NetGroupDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupDel]
  end;
end;
{$ELSE}
function NetGroupDel; external netapi32 name 'NetGroupDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupDelUser: Pointer;

function NetGroupDelUser;
begin
  GetProcedureAddress(_NetGroupDelUser, netapi32, 'NetGroupDelUser');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupDelUser]
  end;
end;
{$ELSE}
function NetGroupDelUser; external netapi32 name 'NetGroupDelUser';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupGetUsers: Pointer;

function NetGroupGetUsers;
begin
  GetProcedureAddress(_NetGroupGetUsers, netapi32, 'NetGroupGetUsers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupGetUsers]
  end;
end;
{$ELSE}
function NetGroupGetUsers; external netapi32 name 'NetGroupGetUsers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGroupSetUsers: Pointer;

function NetGroupSetUsers;
begin
  GetProcedureAddress(_NetGroupSetUsers, netapi32, 'NetGroupSetUsers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGroupSetUsers]
  end;
end;
{$ELSE}
function NetGroupSetUsers; external netapi32 name 'NetGroupSetUsers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupAdd: Pointer;

function NetLocalGroupAdd;
begin
  GetProcedureAddress(_NetLocalGroupAdd, netapi32, 'NetLocalGroupAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupAdd]
  end;
end;
{$ELSE}
function NetLocalGroupAdd; external netapi32 name 'NetLocalGroupAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupAddMember: Pointer;

function NetLocalGroupAddMember;
begin
  GetProcedureAddress(_NetLocalGroupAddMember, netapi32, 'NetLocalGroupAddMember');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupAddMember]
  end;
end;
{$ELSE}
function NetLocalGroupAddMember; external netapi32 name 'NetLocalGroupAddMember';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupEnum: Pointer;

function NetLocalGroupEnum;
begin
  GetProcedureAddress(_NetLocalGroupEnum, netapi32, 'NetLocalGroupEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupEnum]
  end;
end;
{$ELSE}
function NetLocalGroupEnum; external netapi32 name 'NetLocalGroupEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupGetInfo: Pointer;

function NetLocalGroupGetInfo;
begin
  GetProcedureAddress(_NetLocalGroupGetInfo, netapi32, 'NetLocalGroupGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupGetInfo]
  end;
end;
{$ELSE}
function NetLocalGroupGetInfo; external netapi32 name 'NetLocalGroupGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupSetInfo: Pointer;

function NetLocalGroupSetInfo;
begin
  GetProcedureAddress(_NetLocalGroupSetInfo, netapi32, 'NetLocalGroupSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupSetInfo]
  end;
end;
{$ELSE}
function NetLocalGroupSetInfo; external netapi32 name 'NetLocalGroupSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupDel: Pointer;

function NetLocalGroupDel;
begin
  GetProcedureAddress(_NetLocalGroupDel, netapi32, 'NetLocalGroupDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupDel]
  end;
end;
{$ELSE}
function NetLocalGroupDel; external netapi32 name 'NetLocalGroupDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupDelMember: Pointer;

function NetLocalGroupDelMember;
begin
  GetProcedureAddress(_NetLocalGroupDelMember, netapi32, 'NetLocalGroupDelMember');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupDelMember]
  end;
end;
{$ELSE}
function NetLocalGroupDelMember; external netapi32 name 'NetLocalGroupDelMember';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupGetMembers: Pointer;

function NetLocalGroupGetMembers;
begin
  GetProcedureAddress(_NetLocalGroupGetMembers, netapi32, 'NetLocalGroupGetMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupGetMembers]
  end;
end;
{$ELSE}
function NetLocalGroupGetMembers; external netapi32 name 'NetLocalGroupGetMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupSetMembers: Pointer;

function NetLocalGroupSetMembers;
begin
  GetProcedureAddress(_NetLocalGroupSetMembers, netapi32, 'NetLocalGroupSetMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupSetMembers]
  end;
end;
{$ELSE}
function NetLocalGroupSetMembers; external netapi32 name 'NetLocalGroupSetMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupAddMembers: Pointer;

function NetLocalGroupAddMembers;
begin
  GetProcedureAddress(_NetLocalGroupAddMembers, netapi32, 'NetLocalGroupAddMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupAddMembers]
  end;
end;
{$ELSE}
function NetLocalGroupAddMembers; external netapi32 name 'NetLocalGroupAddMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetLocalGroupDelMembers: Pointer;

function NetLocalGroupDelMembers;
begin
  GetProcedureAddress(_NetLocalGroupDelMembers, netapi32, 'NetLocalGroupDelMembers');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetLocalGroupDelMembers]
  end;
end;
{$ELSE}
function NetLocalGroupDelMembers; external netapi32 name 'NetLocalGroupDelMembers';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetQueryDisplayInformation: Pointer;

function NetQueryDisplayInformation;
begin
  GetProcedureAddress(_NetQueryDisplayInformation, netapi32, 'NetQueryDisplayInformation');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetQueryDisplayInformation]
  end;
end;
{$ELSE}
function NetQueryDisplayInformation; external netapi32 name 'NetQueryDisplayInformation';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetDisplayInformationIndex: Pointer;

function NetGetDisplayInformationIndex;
begin
  GetProcedureAddress(_NetGetDisplayInformationIndex, netapi32, 'NetGetDisplayInformationIndex');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetDisplayInformationIndex]
  end;
end;
{$ELSE}
function NetGetDisplayInformationIndex; external netapi32 name 'NetGetDisplayInformationIndex';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessAdd: Pointer;

function NetAccessAdd;
begin
  GetProcedureAddress(_NetAccessAdd, netapi32, 'NetAccessAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessAdd]
  end;
end;
{$ELSE}
function NetAccessAdd; external netapi32 name 'NetAccessAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessEnum: Pointer;

function NetAccessEnum;
begin
  GetProcedureAddress(_NetAccessEnum, netapi32, 'NetAccessEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessEnum]
  end;
end;
{$ELSE}
function NetAccessEnum; external netapi32 name 'NetAccessEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessGetInfo: Pointer;

function NetAccessGetInfo;
begin
  GetProcedureAddress(_NetAccessGetInfo, netapi32, 'NetAccessGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessGetInfo]
  end;
end;
{$ELSE}
function NetAccessGetInfo; external netapi32 name 'NetAccessGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessSetInfo: Pointer;

function NetAccessSetInfo;
begin
  GetProcedureAddress(_NetAccessSetInfo, netapi32, 'NetAccessSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessSetInfo]
  end;
end;
{$ELSE}
function NetAccessSetInfo; external netapi32 name 'NetAccessSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessDel: Pointer;

function NetAccessDel;
begin
  GetProcedureAddress(_NetAccessDel, netapi32, 'NetAccessDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessDel]
  end;
end;
{$ELSE}
function NetAccessDel; external netapi32 name 'NetAccessDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetAccessGetUserPerms: Pointer;

function NetAccessGetUserPerms;
begin
  GetProcedureAddress(_NetAccessGetUserPerms, netapi32, 'NetAccessGetUserPerms');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetAccessGetUserPerms]
  end;
end;
{$ELSE}
function NetAccessGetUserPerms; external netapi32 name 'NetAccessGetUserPerms';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetValidatePasswordPolicy: Pointer;

function NetValidatePasswordPolicy;
begin
  GetProcedureAddress(_NetValidatePasswordPolicy, netapi32, 'NetValidatePasswordPolicy');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetValidatePasswordPolicy]
  end;
end;
{$ELSE}
function NetValidatePasswordPolicy; external netapi32 name 'NetValidatePasswordPolicy';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetValidatePasswordPolicyFree: Pointer;

function NetValidatePasswordPolicyFree;
begin
  GetProcedureAddress(_NetValidatePasswordPolicyFree, netapi32, 'NetValidatePasswordPolicyFree');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetValidatePasswordPolicyFree]
  end;
end;
{$ELSE}
function NetValidatePasswordPolicyFree; external netapi32 name 'NetValidatePasswordPolicyFree';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetDCName: Pointer;

function NetGetDCName;
begin
  GetProcedureAddress(_NetGetDCName, netapi32, 'NetGetDCName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetDCName]
  end;
end;
{$ELSE}
function NetGetDCName; external netapi32 name 'NetGetDCName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetGetAnyDCName: Pointer;

function NetGetAnyDCName;
begin
  GetProcedureAddress(_NetGetAnyDCName, netapi32, 'NetGetAnyDCName');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetGetAnyDCName]
  end;
end;
{$ELSE}
function NetGetAnyDCName; external netapi32 name 'NetGetAnyDCName';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_NetLogonControl: Pointer;

function I_NetLogonControl;
begin
  GetProcedureAddress(_I_NetLogonControl, netapi32, 'I_NetLogonControl');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_NetLogonControl]
  end;
end;
{$ELSE}
function I_NetLogonControl; external netapi32 name 'I_NetLogonControl';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _I_NetLogonControl2: Pointer;

function I_NetLogonControl2;
begin
  GetProcedureAddress(_I_NetLogonControl2, netapi32, 'I_NetLogonControl2');
  asm
    mov esp, ebp
    pop ebp
    jmp [_I_NetLogonControl2]
  end;
end;
{$ELSE}
function I_NetLogonControl2; external netapi32 name 'I_NetLogonControl2';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetEnumerateTrustedDomains: Pointer;

function NetEnumerateTrustedDomains;
begin
  GetProcedureAddress(_NetEnumerateTrustedDomains, netapi32, 'NetEnumerateTrustedDomains');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetEnumerateTrustedDomains]
  end;
end;
{$ELSE}
function NetEnumerateTrustedDomains; external netapi32 name 'NetEnumerateTrustedDomains';
{$ENDIF DYNAMIC_LINK}

end.
