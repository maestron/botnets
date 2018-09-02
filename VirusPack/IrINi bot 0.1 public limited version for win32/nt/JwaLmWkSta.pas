{******************************************************************************}
{                                                       	               }
{ Lan Manager Workstation API interface Unit for Object Pascal                 }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: lmwksta.h, released November 2001. The original Pascal }
{ code is: LmWkSta.pas, released Februari 2002. The initial developer of the   }
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

unit JwaLmWkSta;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "lmwksta.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaLmCons, JwaWinType;

//
// Function Prototypes
//

function NetWkstaGetInfo(servername: LMSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaGetInfo}

function NetWkstaSetInfo(servername: LMSTR; level: DWORD; buffer: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaSetInfo}

function NetWkstaUserGetInfo(reserved: LMSTR; level: DWORD; var bufptr: LPBYTE): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaUserGetInfo}

function NetWkstaUserSetInfo(reserved: LMSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaUserSetInfo}

function NetWkstaUserEnum(servername: LMSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread: LPDWORD; totalentries: LPDWORD; resumehandle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaUserEnum}

function NetWkstaTransportAdd(servername: LMSTR; level: DWORD; buf: LPBYTE; parm_err: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaTransportAdd}

function NetWkstaTransportDel(servername: LMSTR; transportname: LMSTR; ucond: DWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaTransportDel}

function NetWkstaTransportEnum(servername: LMSTR; level: DWORD; var bufptr: LPBYTE; prefmaxlen: DWORD; entriesread: LPDWORD; totalentries: LPDWORD; resumehandle: LPDWORD): NET_API_STATUS; stdcall;
{$EXTERNALSYM NetWkstaTransportEnum}

//
//  Data Structures
//

//
// NetWkstaGetInfo and NetWkstaSetInfo
//

//
// NetWkstaGetInfo only.  System information - guest access
//

type
  LPWKSTA_INFO_100 = ^WKSTA_INFO_100;
  {$EXTERNALSYM LPWKSTA_INFO_100}
  PWKSTA_INFO_100 = ^WKSTA_INFO_100;
  {$EXTERNALSYM PWKSTA_INFO_100}
  _WKSTA_INFO_100 = record
    wki100_platform_id: DWORD;
    wki100_computername: LMSTR;
    wki100_langroup: LMSTR;
    wki100_ver_major: DWORD;
    wki100_ver_minor: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_100}
  WKSTA_INFO_100 = _WKSTA_INFO_100;
  {$EXTERNALSYM WKSTA_INFO_100}
  TWkstaInfo100 = WKSTA_INFO_100;
  PWkstaInfo100 = PWKSTA_INFO_100;

//
// NetWkstaGetInfo only.  System information - user access
//

  LPWKSTA_INFO_101 = ^WKSTA_INFO_101;
  {$EXTERNALSYM LPWKSTA_INFO_101}
  PWKSTA_INFO_101 = ^WKSTA_INFO_101;
  {$EXTERNALSYM PWKSTA_INFO_101}
  _WKSTA_INFO_101 = record
    wki101_platform_id: DWORD;
    wki101_computername: LMSTR;
    wki101_langroup: LMSTR;
    wki101_ver_major: DWORD;
    wki101_ver_minor: DWORD;
    wki101_lanroot: LMSTR;
  end;
  {$EXTERNALSYM _WKSTA_INFO_101}
  WKSTA_INFO_101 = _WKSTA_INFO_101;
  {$EXTERNALSYM WKSTA_INFO_101}
  TWkstaInfo101 = WKSTA_INFO_101;
  PWkstaInfo101 = PWKSTA_INFO_101;

//
// NetWkstaGetInfo only.  System information - admin or operator access
//

  LPWKSTA_INFO_102 = ^WKSTA_INFO_102;
  {$EXTERNALSYM LPWKSTA_INFO_102}
  PWKSTA_INFO_102 = ^WKSTA_INFO_102;
  {$EXTERNALSYM PWKSTA_INFO_102}
  _WKSTA_INFO_102 = record
    wki102_platform_id: DWORD;
    wki102_computername: LMSTR;
    wki102_langroup: LMSTR;
    wki102_ver_major: DWORD;
    wki102_ver_minor: DWORD;
    wki102_lanroot: LMSTR;
    wki102_logged_on_users: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_102}
  WKSTA_INFO_102 = _WKSTA_INFO_102;
  {$EXTERNALSYM WKSTA_INFO_102}
  TWkstaInfo102 = WKSTA_INFO_102;
  PWkstaInfo102 = PWKSTA_INFO_102;

//
// Down-level NetWkstaGetInfo and NetWkstaSetInfo.
//
// DOS specific workstation information -
//    admin or domain operator access
//

  LPWKSTA_INFO_302 = ^WKSTA_INFO_302;
  {$EXTERNALSYM LPWKSTA_INFO_302}
  PWKSTA_INFO_302 = ^WKSTA_INFO_302;
  {$EXTERNALSYM PWKSTA_INFO_302}
  _WKSTA_INFO_302 = record
    wki302_char_wait: DWORD;
    wki302_collection_time: DWORD;
    wki302_maximum_collection_count: DWORD;
    wki302_keep_conn: DWORD;
    wki302_keep_search: DWORD;
    wki302_max_cmds: DWORD;
    wki302_num_work_buf: DWORD;
    wki302_siz_work_buf: DWORD;
    wki302_max_wrk_cache: DWORD;
    wki302_sess_timeout: DWORD;
    wki302_siz_error: DWORD;
    wki302_num_alerts: DWORD;
    wki302_num_services: DWORD;
    wki302_errlog_sz: DWORD;
    wki302_print_buf_time: DWORD;
    wki302_num_char_buf: DWORD;
    wki302_siz_char_buf: DWORD;
    wki302_wrk_heuristics: LMSTR;
    wki302_mailslots: DWORD;
    wki302_num_dgram_buf: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_302}
  WKSTA_INFO_302 = _WKSTA_INFO_302;
  {$EXTERNALSYM WKSTA_INFO_302}
  TWkstaInfo302 = WKSTA_INFO_302;
  PWkstaInfo302 = PWKSTA_INFO_302;

//
// Down-level NetWkstaGetInfo and NetWkstaSetInfo
//
// OS/2 specific workstation information -
//    admin or domain operator access
//

  LPWKSTA_INFO_402 = ^WKSTA_INFO_402;
  {$EXTERNALSYM LPWKSTA_INFO_402}
  PWKSTA_INFO_402 = ^WKSTA_INFO_402;
  {$EXTERNALSYM PWKSTA_INFO_402}
  _WKSTA_INFO_402 = record
    wki402_char_wait: DWORD;
    wki402_collection_time: DWORD;
    wki402_maximum_collection_count: DWORD;
    wki402_keep_conn: DWORD;
    wki402_keep_search: DWORD;
    wki402_max_cmds: DWORD;
    wki402_num_work_buf: DWORD;
    wki402_siz_work_buf: DWORD;
    wki402_max_wrk_cache: DWORD;
    wki402_sess_timeout: DWORD;
    wki402_siz_error: DWORD;
    wki402_num_alerts: DWORD;
    wki402_num_services: DWORD;
    wki402_errlog_sz: DWORD;
    wki402_print_buf_time: DWORD;
    wki402_num_char_buf: DWORD;
    wki402_siz_char_buf: DWORD;
    wki402_wrk_heuristics: LMSTR;
    wki402_mailslots: DWORD;
    wki402_num_dgram_buf: DWORD;
    wki402_max_threads: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_402}
  WKSTA_INFO_402 = _WKSTA_INFO_402;
  {$EXTERNALSYM WKSTA_INFO_402}
  TWkstaInfo402 = WKSTA_INFO_402;
  PWkstaInfo402 = PWKSTA_INFO_402;

//
// Same-level NetWkstaGetInfo and NetWkstaSetInfo.
//
// NT specific workstation information -
//    admin or domain operator access
//

  LPWKSTA_INFO_502 = ^WKSTA_INFO_502;
  {$EXTERNALSYM LPWKSTA_INFO_502}
  PWKSTA_INFO_502 = ^WKSTA_INFO_502;
  {$EXTERNALSYM PWKSTA_INFO_502}
  _WKSTA_INFO_502 = record
    wki502_char_wait: DWORD;
    wki502_collection_time: DWORD;
    wki502_maximum_collection_count: DWORD;
    wki502_keep_conn: DWORD;
    wki502_max_cmds: DWORD;
    wki502_sess_timeout: DWORD;
    wki502_siz_char_buf: DWORD;
    wki502_max_threads: DWORD;
    wki502_lock_quota: DWORD;
    wki502_lock_increment: DWORD;
    wki502_lock_maximum: DWORD;
    wki502_pipe_increment: DWORD;
    wki502_pipe_maximum: DWORD;
    wki502_cache_file_timeout: DWORD;
    wki502_dormant_file_limit: DWORD;
    wki502_read_ahead_throughput: DWORD;
    wki502_num_mailslot_buffers: DWORD;
    wki502_num_srv_announce_buffers: DWORD;
    wki502_max_illegal_datagram_events: DWORD;
    wki502_illegal_datagram_event_reset_frequency: DWORD;
    wki502_log_election_packets: BOOL;
    wki502_use_opportunistic_locking: BOOL;
    wki502_use_unlock_behind: BOOL;
    wki502_use_close_behind: BOOL;
    wki502_buf_named_pipes: BOOL;
    wki502_use_lock_read_unlock: BOOL;
    wki502_utilize_nt_caching: BOOL;
    wki502_use_raw_read: BOOL;
    wki502_use_raw_write: BOOL;
    wki502_use_write_raw_data: BOOL;
    wki502_use_encryption: BOOL;
    wki502_buf_files_deny_write: BOOL;
    wki502_buf_read_only_files: BOOL;
    wki502_force_core_create_mode: BOOL;
    wki502_use_512_byte_max_transfer: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_502}
  WKSTA_INFO_502 = _WKSTA_INFO_502;
  {$EXTERNALSYM WKSTA_INFO_502}
  TWkstaInfo502 = WKSTA_INFO_502;
  PWkstaInfo502 = PWKSTA_INFO_502;


//
// The following info-levels are only valid for NetWkstaSetInfo
//

//
// The following levels are supported on down-level systems (LAN Man 2.x)
// as well as NT systems:
//

  LPWKSTA_INFO_1010 = ^WKSTA_INFO_1010;
  {$EXTERNALSYM LPWKSTA_INFO_1010}
  PWKSTA_INFO_1010 = ^WKSTA_INFO_1010;
  {$EXTERNALSYM PWKSTA_INFO_1010}
  _WKSTA_INFO_1010 = record
    wki1010_char_wait: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1010}
  WKSTA_INFO_1010 = _WKSTA_INFO_1010;
  {$EXTERNALSYM WKSTA_INFO_1010}
  TWkstaInfo1010 = WKSTA_INFO_1010;
  PWkstaInfo1010 = PWKSTA_INFO_1010;

  LPWKSTA_INFO_1011 = ^WKSTA_INFO_1011;
  {$EXTERNALSYM LPWKSTA_INFO_1011}
  PWKSTA_INFO_1011 = ^WKSTA_INFO_1011;
  {$EXTERNALSYM PWKSTA_INFO_1011}
  _WKSTA_INFO_1011 = record
    wki1011_collection_time: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1011}
  WKSTA_INFO_1011 = _WKSTA_INFO_1011;
  {$EXTERNALSYM WKSTA_INFO_1011}
  TWkstaInfo1011 = WKSTA_INFO_1011;
  PWkstaInfo1011 = PWKSTA_INFO_1011;

  LPWKSTA_INFO_1012 = ^WKSTA_INFO_1012;
  {$EXTERNALSYM LPWKSTA_INFO_1012}
  PWKSTA_INFO_1012 = ^WKSTA_INFO_1012;
  {$EXTERNALSYM PWKSTA_INFO_1012}
  _WKSTA_INFO_1012 = record
    wki1012_maximum_collection_count: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1012}
  WKSTA_INFO_1012 = _WKSTA_INFO_1012;
  {$EXTERNALSYM WKSTA_INFO_1012}
  TWkstaInfo1012 = WKSTA_INFO_1012;
  PWkstaInfo1012 = PWKSTA_INFO_1012;

//
// The following level are supported on down-level systems (LAN Man 2.x)
// only:
//

  LPWKSTA_INFO_1027 = ^WKSTA_INFO_1027;
  {$EXTERNALSYM LPWKSTA_INFO_1027}
  PWKSTA_INFO_1027 = ^WKSTA_INFO_1027;
  {$EXTERNALSYM PWKSTA_INFO_1027}
  _WKSTA_INFO_1027 = record
    wki1027_errlog_sz: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1027}
  WKSTA_INFO_1027 = _WKSTA_INFO_1027;
  {$EXTERNALSYM WKSTA_INFO_1027}
  TWkstaInfo1027 = WKSTA_INFO_1027;
  PWkstaInfo1027 = PWKSTA_INFO_1027;

  LPWKSTA_INFO_1028 = ^WKSTA_INFO_1028;
  {$EXTERNALSYM LPWKSTA_INFO_1028}
  PWKSTA_INFO_1028 = ^WKSTA_INFO_1028;
  {$EXTERNALSYM PWKSTA_INFO_1028}
  _WKSTA_INFO_1028 = record
    wki1028_print_buf_time: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1028}
  WKSTA_INFO_1028 = _WKSTA_INFO_1028;
  {$EXTERNALSYM WKSTA_INFO_1028}
  TWkstaInfo1028 = WKSTA_INFO_1028;
  PWkstaInfo1028 = PWKSTA_INFO_1028;

  LPWKSTA_INFO_1032 = ^WKSTA_INFO_1032;
  {$EXTERNALSYM LPWKSTA_INFO_1032}
  PWKSTA_INFO_1032 = ^WKSTA_INFO_1032;
  {$EXTERNALSYM PWKSTA_INFO_1032}
  _WKSTA_INFO_1032 = record
    wki1032_wrk_heuristics: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1032}
  WKSTA_INFO_1032 = _WKSTA_INFO_1032;
  {$EXTERNALSYM WKSTA_INFO_1032}
  TWkstaInfo1032 = WKSTA_INFO_1032;
  PWkstaInfo1032 = PWKSTA_INFO_1032;

//
// The following levels are settable on NT systems, and have no
// effect on down-level systems (i.e. LANMan 2.x) since these
// fields cannot be set on them:
//

  LPWKSTA_INFO_1013 = ^WKSTA_INFO_1013;
  {$EXTERNALSYM LPWKSTA_INFO_1013}
  PWKSTA_INFO_1013 = ^WKSTA_INFO_1013;
  {$EXTERNALSYM PWKSTA_INFO_1013}
  _WKSTA_INFO_1013 = record
    wki1013_keep_conn: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1013}
  WKSTA_INFO_1013 = _WKSTA_INFO_1013;
  {$EXTERNALSYM WKSTA_INFO_1013}
  TWkstaInfo1013 = WKSTA_INFO_1013;
  PWkstaInfo1013 = PWKSTA_INFO_1013;

  LPWKSTA_INFO_1018 = ^WKSTA_INFO_1018;
  {$EXTERNALSYM LPWKSTA_INFO_1018}
  PWKSTA_INFO_1018 = ^WKSTA_INFO_1018;
  {$EXTERNALSYM PWKSTA_INFO_1018}
  _WKSTA_INFO_1018 = record
    wki1018_sess_timeout: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1018}
  WKSTA_INFO_1018 = _WKSTA_INFO_1018;
  {$EXTERNALSYM WKSTA_INFO_1018}
  TWkstaInfo1018 = WKSTA_INFO_1018;
  PWkstaInfo1018 = PWKSTA_INFO_1018;

  LPWKSTA_INFO_1023 = ^WKSTA_INFO_1023;
  {$EXTERNALSYM LPWKSTA_INFO_1023}
  PWKSTA_INFO_1023 = ^WKSTA_INFO_1023;
  {$EXTERNALSYM PWKSTA_INFO_1023}
  _WKSTA_INFO_1023 = record
    wki1023_siz_char_buf: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1023}
  WKSTA_INFO_1023 = _WKSTA_INFO_1023;
  {$EXTERNALSYM WKSTA_INFO_1023}
  TWkstaInfo1023 = WKSTA_INFO_1023;
  PWkstaInfo1023 = PWKSTA_INFO_1023;

  LPWKSTA_INFO_1033 = ^WKSTA_INFO_1033;
  {$EXTERNALSYM LPWKSTA_INFO_1033}
  PWKSTA_INFO_1033 = ^WKSTA_INFO_1033;
  {$EXTERNALSYM PWKSTA_INFO_1033}
  _WKSTA_INFO_1033 = record
    wki1033_max_threads: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1033}
  WKSTA_INFO_1033 = _WKSTA_INFO_1033;
  {$EXTERNALSYM WKSTA_INFO_1033}
  TWkstaInfo1033 = WKSTA_INFO_1033;
  PWkstaInfo1033 = PWKSTA_INFO_1033;

//
// The following levels are only supported on NT systems:
//

  LPWKSTA_INFO_1041 = ^WKSTA_INFO_1041;
  {$EXTERNALSYM LPWKSTA_INFO_1041}
  PWKSTA_INFO_1041 = ^WKSTA_INFO_1041;
  {$EXTERNALSYM PWKSTA_INFO_1041}
  _WKSTA_INFO_1041 = record
    wki1041_lock_quota: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1041}
  WKSTA_INFO_1041 = _WKSTA_INFO_1041;
  {$EXTERNALSYM WKSTA_INFO_1041}
  TWkstaInfo1041 = WKSTA_INFO_1041;
  PWkstaInfo1041 = PWKSTA_INFO_1041;

  LPWKSTA_INFO_1042 = ^WKSTA_INFO_1042;
  {$EXTERNALSYM LPWKSTA_INFO_1042}
  PWKSTA_INFO_1042 = ^WKSTA_INFO_1042;
  {$EXTERNALSYM PWKSTA_INFO_1042}
  _WKSTA_INFO_1042 = record
    wki1042_lock_increment: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1042}
  WKSTA_INFO_1042 = _WKSTA_INFO_1042;
  {$EXTERNALSYM WKSTA_INFO_1042}
  TWkstaInfo1042 = WKSTA_INFO_1042;
  PWkstaInfo1042 = PWKSTA_INFO_1042;

  LPWKSTA_INFO_1043 = ^WKSTA_INFO_1043;
  {$EXTERNALSYM LPWKSTA_INFO_1043}
  PWKSTA_INFO_1043 = ^WKSTA_INFO_1043;
  {$EXTERNALSYM PWKSTA_INFO_1043}
  _WKSTA_INFO_1043 = record
    wki1043_lock_maximum: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1043}
  WKSTA_INFO_1043 = _WKSTA_INFO_1043;
  {$EXTERNALSYM WKSTA_INFO_1043}
  TWkstaInfo1043 = WKSTA_INFO_1043;
  PWkstaInfo1043 = PWKSTA_INFO_1043;

  LPWKSTA_INFO_1044 = ^WKSTA_INFO_1044;
  {$EXTERNALSYM LPWKSTA_INFO_1044}
  PWKSTA_INFO_1044 = ^WKSTA_INFO_1044;
  {$EXTERNALSYM PWKSTA_INFO_1044}
  _WKSTA_INFO_1044 = record
    wki1044_pipe_increment: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1044}
  WKSTA_INFO_1044 = _WKSTA_INFO_1044;
  {$EXTERNALSYM WKSTA_INFO_1044}
  TWkstaInfo1044 = WKSTA_INFO_1044;
  PWkstaInfo1044 = PWKSTA_INFO_1044;

  LPWKSTA_INFO_1045 = ^WKSTA_INFO_1045;
  {$EXTERNALSYM LPWKSTA_INFO_1045}
  PWKSTA_INFO_1045 = ^WKSTA_INFO_1045;
  {$EXTERNALSYM PWKSTA_INFO_1045}
  _WKSTA_INFO_1045 = record
    wki1045_pipe_maximum: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1045}
  WKSTA_INFO_1045 = _WKSTA_INFO_1045;
  {$EXTERNALSYM WKSTA_INFO_1045}
  TWkstaInfo1045 = WKSTA_INFO_1045;
  PWkstaInfo1045 = PWKSTA_INFO_1045;

  LPWKSTA_INFO_1046 = ^WKSTA_INFO_1046;
  {$EXTERNALSYM LPWKSTA_INFO_1046}
  PWKSTA_INFO_1046 = ^WKSTA_INFO_1046;
  {$EXTERNALSYM PWKSTA_INFO_1046}
  _WKSTA_INFO_1046 = record
    wki1046_dormant_file_limit: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1046}
  WKSTA_INFO_1046 = _WKSTA_INFO_1046;
  {$EXTERNALSYM WKSTA_INFO_1046}
  TWkstaInfo1046 = WKSTA_INFO_1046;
  PWkstaInfo1046 = PWKSTA_INFO_1046;

  LPWKSTA_INFO_1047 = ^WKSTA_INFO_1047;
  {$EXTERNALSYM LPWKSTA_INFO_1047}
  PWKSTA_INFO_1047 = ^WKSTA_INFO_1047;
  {$EXTERNALSYM PWKSTA_INFO_1047}
  _WKSTA_INFO_1047 = record
    wki1047_cache_file_timeout: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1047}
  WKSTA_INFO_1047 = _WKSTA_INFO_1047;
  {$EXTERNALSYM WKSTA_INFO_1047}
  TWkstaInfo1047 = WKSTA_INFO_1047;
  PWkstaInfo1047 = PWKSTA_INFO_1047;

  LPWKSTA_INFO_1048 = ^WKSTA_INFO_1048;
  {$EXTERNALSYM LPWKSTA_INFO_1048}
  PWKSTA_INFO_1048 = ^WKSTA_INFO_1048;
  {$EXTERNALSYM PWKSTA_INFO_1048}
  _WKSTA_INFO_1048 = record
    wki1048_use_opportunistic_locking: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1048}
  WKSTA_INFO_1048 = _WKSTA_INFO_1048;
  {$EXTERNALSYM WKSTA_INFO_1048}
  TWkstaInfo1048 = WKSTA_INFO_1048;
  PWkstaInfo1048 = PWKSTA_INFO_1048;

  LPWKSTA_INFO_1049 = ^WKSTA_INFO_1049;
  {$EXTERNALSYM LPWKSTA_INFO_1049}
  PWKSTA_INFO_1049 = ^WKSTA_INFO_1049;
  {$EXTERNALSYM PWKSTA_INFO_1049}
  _WKSTA_INFO_1049 = record
    wki1049_use_unlock_behind: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1049}
  WKSTA_INFO_1049 = _WKSTA_INFO_1049;
  {$EXTERNALSYM WKSTA_INFO_1049}
  TWkstaInfo1049 = WKSTA_INFO_1049;
  PWkstaInfo1049 = PWKSTA_INFO_1049;

  LPWKSTA_INFO_1050 = ^WKSTA_INFO_1050;
  {$EXTERNALSYM LPWKSTA_INFO_1050}
  PWKSTA_INFO_1050 = ^WKSTA_INFO_1050;
  {$EXTERNALSYM PWKSTA_INFO_1050}
  _WKSTA_INFO_1050 = record
    wki1050_use_close_behind: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1050}
  WKSTA_INFO_1050 = _WKSTA_INFO_1050;
  {$EXTERNALSYM WKSTA_INFO_1050}
  TWkstaInfo1050 = WKSTA_INFO_1050;
  PWkstaInfo1050 = PWKSTA_INFO_1050;

  LPWKSTA_INFO_1051 = ^WKSTA_INFO_1051;
  {$EXTERNALSYM LPWKSTA_INFO_1051}
  PWKSTA_INFO_1051 = ^WKSTA_INFO_1051;
  {$EXTERNALSYM PWKSTA_INFO_1051}
  _WKSTA_INFO_1051 = record
    wki1051_buf_named_pipes: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1051}
  WKSTA_INFO_1051 = _WKSTA_INFO_1051;
  {$EXTERNALSYM WKSTA_INFO_1051}
  TWkstaInfo1051 = WKSTA_INFO_1051;
  PWkstaInfo1051 = PWKSTA_INFO_1051;

  LPWKSTA_INFO_1052 = ^WKSTA_INFO_1052;
  {$EXTERNALSYM LPWKSTA_INFO_1052}
  PWKSTA_INFO_1052 = ^WKSTA_INFO_1052;
  {$EXTERNALSYM PWKSTA_INFO_1052}
  _WKSTA_INFO_1052 = record
    wki1052_use_lock_read_unlock: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1052}
  WKSTA_INFO_1052 = _WKSTA_INFO_1052;
  {$EXTERNALSYM WKSTA_INFO_1052}
  TWkstaInfo1052 = WKSTA_INFO_1052;
  PWkstaInfo1052 = PWKSTA_INFO_1052;

  LPWKSTA_INFO_1053 = ^WKSTA_INFO_1053;
  {$EXTERNALSYM LPWKSTA_INFO_1053}
  PWKSTA_INFO_1053 = ^WKSTA_INFO_1053;
  {$EXTERNALSYM PWKSTA_INFO_1053}
  _WKSTA_INFO_1053 = record
    wki1053_utilize_nt_caching: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1053}
  WKSTA_INFO_1053 = _WKSTA_INFO_1053;
  {$EXTERNALSYM WKSTA_INFO_1053}
  TWkstaInfo1053 = WKSTA_INFO_1053;
  PWkstaInfo1053 = PWKSTA_INFO_1053;

  LPWKSTA_INFO_1054 = ^WKSTA_INFO_1054;
  {$EXTERNALSYM LPWKSTA_INFO_1054}
  PWKSTA_INFO_1054 = ^WKSTA_INFO_1054;
  {$EXTERNALSYM PWKSTA_INFO_1054}
  _WKSTA_INFO_1054 = record
    wki1054_use_raw_read: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1054}
  WKSTA_INFO_1054 = _WKSTA_INFO_1054;
  {$EXTERNALSYM WKSTA_INFO_1054}
  TWkstaInfo1054 = WKSTA_INFO_1054;
  PWkstaInfo1054 = PWKSTA_INFO_1054;

  LPWKSTA_INFO_1055 = ^WKSTA_INFO_1055;
  {$EXTERNALSYM LPWKSTA_INFO_1055}
  PWKSTA_INFO_1055 = ^WKSTA_INFO_1055;
  {$EXTERNALSYM PWKSTA_INFO_1055}
  _WKSTA_INFO_1055 = record
    wki1055_use_raw_write: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1055}
  WKSTA_INFO_1055 = _WKSTA_INFO_1055;
  {$EXTERNALSYM WKSTA_INFO_1055}
  TWkstaInfo1055 = WKSTA_INFO_1055;
  PWkstaInfo1055 = PWKSTA_INFO_1055;

  LPWKSTA_INFO_1056 = ^WKSTA_INFO_1056;
  {$EXTERNALSYM LPWKSTA_INFO_1056}
  PWKSTA_INFO_1056 = ^WKSTA_INFO_1056;
  {$EXTERNALSYM PWKSTA_INFO_1056}
  _WKSTA_INFO_1056 = record
    wki1056_use_write_raw_data: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1056}
  WKSTA_INFO_1056 = _WKSTA_INFO_1056;
  {$EXTERNALSYM WKSTA_INFO_1056}
  TWkstaInfo1056 = WKSTA_INFO_1056;
  PWkstaInfo1056 = PWKSTA_INFO_1056;

  LPWKSTA_INFO_1057 = ^WKSTA_INFO_1057;
  {$EXTERNALSYM LPWKSTA_INFO_1057}
  PWKSTA_INFO_1057 = ^WKSTA_INFO_1057;
  {$EXTERNALSYM PWKSTA_INFO_1057}
  _WKSTA_INFO_1057 = record
    wki1057_use_encryption: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1057}
  WKSTA_INFO_1057 = _WKSTA_INFO_1057;
  {$EXTERNALSYM WKSTA_INFO_1057}
  TWkstaInfo1057 = WKSTA_INFO_1057;
  PWkstaInfo1057 = PWKSTA_INFO_1057;

  LPWKSTA_INFO_1058 = ^WKSTA_INFO_1058;
  {$EXTERNALSYM LPWKSTA_INFO_1058}
  PWKSTA_INFO_1058 = ^WKSTA_INFO_1058;
  {$EXTERNALSYM PWKSTA_INFO_1058}
  _WKSTA_INFO_1058 = record
    wki1058_buf_files_deny_write: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1058}
  WKSTA_INFO_1058 = _WKSTA_INFO_1058;
  {$EXTERNALSYM WKSTA_INFO_1058}
  TWkstaInfo1058 = WKSTA_INFO_1058;
  PWkstaInfo1058 = PWKSTA_INFO_1058;

  LPWKSTA_INFO_1059 = ^WKSTA_INFO_1059;
  {$EXTERNALSYM LPWKSTA_INFO_1059}
  PWKSTA_INFO_1059 = ^WKSTA_INFO_1059;
  {$EXTERNALSYM PWKSTA_INFO_1059}
  _WKSTA_INFO_1059 = record
    wki1059_buf_read_only_files: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1059}
  WKSTA_INFO_1059 = _WKSTA_INFO_1059;
  {$EXTERNALSYM WKSTA_INFO_1059}
  TWkstaInfo1059 = WKSTA_INFO_1059;
  PWkstaInfo1059 = PWKSTA_INFO_1059;

  LPWKSTA_INFO_1060 = ^WKSTA_INFO_1060;
  {$EXTERNALSYM LPWKSTA_INFO_1060}
  PWKSTA_INFO_1060 = ^WKSTA_INFO_1060;
  {$EXTERNALSYM PWKSTA_INFO_1060}
  _WKSTA_INFO_1060 = record
    wki1060_force_core_create_mode: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1060}
  WKSTA_INFO_1060 = _WKSTA_INFO_1060;
  {$EXTERNALSYM WKSTA_INFO_1060}
  TWkstaInfo1060 = WKSTA_INFO_1060;
  PWkstaInfo1060 = PWKSTA_INFO_1060;

  LPWKSTA_INFO_1061 = ^WKSTA_INFO_1061;
  {$EXTERNALSYM LPWKSTA_INFO_1061}
  PWKSTA_INFO_1061 = ^WKSTA_INFO_1061;
  {$EXTERNALSYM PWKSTA_INFO_1061}
  _WKSTA_INFO_1061 = record
    wki1061_use_512_byte_max_transfer: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1061}
  WKSTA_INFO_1061 = _WKSTA_INFO_1061;
  {$EXTERNALSYM WKSTA_INFO_1061}
  TWkstaInfo1061 = WKSTA_INFO_1061;
  PWkstaInfo1061 = PWKSTA_INFO_1061;

  LPWKSTA_INFO_1062 = ^WKSTA_INFO_1062;
  {$EXTERNALSYM LPWKSTA_INFO_1062}
  PWKSTA_INFO_1062 = ^WKSTA_INFO_1062;
  {$EXTERNALSYM PWKSTA_INFO_1062}
  _WKSTA_INFO_1062 = record
    wki1062_read_ahead_throughput: DWORD;
  end;
  {$EXTERNALSYM _WKSTA_INFO_1062}
  WKSTA_INFO_1062 = _WKSTA_INFO_1062;
  {$EXTERNALSYM WKSTA_INFO_1062}
  TWkstaInfo1062 = WKSTA_INFO_1062;
  PWkstaInfo1062 = PWKSTA_INFO_1062;

//
// NetWkstaUserGetInfo (local only) and NetWkstaUserEnum -
//     no access restrictions.
//

  LPWKSTA_USER_INFO_0 = ^WKSTA_USER_INFO_0;
  {$EXTERNALSYM LPWKSTA_USER_INFO_0}
  PWKSTA_USER_INFO_0 = ^WKSTA_USER_INFO_0;
  {$EXTERNALSYM PWKSTA_USER_INFO_0}
  _WKSTA_USER_INFO_0 = record
    wkui0_username: LMSTR;
  end;
  {$EXTERNALSYM _WKSTA_USER_INFO_0}
  WKSTA_USER_INFO_0 = _WKSTA_USER_INFO_0;
  {$EXTERNALSYM WKSTA_USER_INFO_0}
  TWkstaUserInfo0 = WKSTA_USER_INFO_0;
  PWkstaUserInfo0 = PWKSTA_USER_INFO_0;

//
// NetWkstaUserGetInfo (local only) and NetWkstaUserEnum -
//     no access restrictions.
//

  LPWKSTA_USER_INFO_1 = ^WKSTA_USER_INFO_1;
  {$EXTERNALSYM LPWKSTA_USER_INFO_1}
  PWKSTA_USER_INFO_1 = ^WKSTA_USER_INFO_1;
  {$EXTERNALSYM PWKSTA_USER_INFO_1}
  _WKSTA_USER_INFO_1 = record
    wkui1_username: LMSTR;
    wkui1_logon_domain: LMSTR;
    wkui1_oth_domains: LMSTR;
    wkui1_logon_server: LMSTR;
  end;
  {$EXTERNALSYM _WKSTA_USER_INFO_1}
  WKSTA_USER_INFO_1 = _WKSTA_USER_INFO_1;
  {$EXTERNALSYM WKSTA_USER_INFO_1}
  TWkstaUserInfo1 = WKSTA_USER_INFO_1;
  PWkstaUserInfo1 = PWKSTA_USER_INFO_1;

//
// NetWkstaUserSetInfo - local access.
//

  LPWKSTA_USER_INFO_1101 = ^WKSTA_USER_INFO_1101;
  {$EXTERNALSYM LPWKSTA_USER_INFO_1101}
  PWKSTA_USER_INFO_1101 = ^WKSTA_USER_INFO_1101;
  {$EXTERNALSYM PWKSTA_USER_INFO_1101}
  _WKSTA_USER_INFO_1101 = record
    wkui1101_oth_domains: LMSTR;
  end;
  {$EXTERNALSYM _WKSTA_USER_INFO_1101}
  WKSTA_USER_INFO_1101 = _WKSTA_USER_INFO_1101;
  {$EXTERNALSYM WKSTA_USER_INFO_1101}
  TWkstaUserInfo1101 = WKSTA_USER_INFO_1101;
  PWkstaUserInfo1101 = PWKSTA_USER_INFO_1101;

//
// NetWkstaTransportAdd - admin access
//

  LPWKSTA_TRANSPORT_INFO_0 = ^WKSTA_TRANSPORT_INFO_0;
  {$EXTERNALSYM LPWKSTA_TRANSPORT_INFO_0}
  PWKSTA_TRANSPORT_INFO_0 = ^WKSTA_TRANSPORT_INFO_0;
  {$EXTERNALSYM PWKSTA_TRANSPORT_INFO_0}
  _WKSTA_TRANSPORT_INFO_0 = record
    wkti0_quality_of_service: DWORD;
    wkti0_number_of_vcs: DWORD;
    wkti0_transport_name: LMSTR;
    wkti0_transport_address: LMSTR;
    wkti0_wan_ish: BOOL;
  end;
  {$EXTERNALSYM _WKSTA_TRANSPORT_INFO_0}
  WKSTA_TRANSPORT_INFO_0 = _WKSTA_TRANSPORT_INFO_0;
  {$EXTERNALSYM WKSTA_TRANSPORT_INFO_0}
  TWkstaTransportInfo0 = WKSTA_TRANSPORT_INFO_0;
  PWkstaTransportInfo0 = PWKSTA_TRANSPORT_INFO_0;

//
// Special Values and Constants
//

//
//  Identifiers for use as NetWkstaSetInfo parmnum parameter
//

//
// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaSetInfo.
//

const
  WKSTA_PLATFORM_ID_PARMNUM     = 100;
  {$EXTERNALSYM WKSTA_PLATFORM_ID_PARMNUM}
  WKSTA_COMPUTERNAME_PARMNUM    = 1;
  {$EXTERNALSYM WKSTA_COMPUTERNAME_PARMNUM}
  WKSTA_LANGROUP_PARMNUM        = 2;
  {$EXTERNALSYM WKSTA_LANGROUP_PARMNUM}
  WKSTA_VER_MAJOR_PARMNUM       = 4;
  {$EXTERNALSYM WKSTA_VER_MAJOR_PARMNUM}
  WKSTA_VER_MINOR_PARMNUM       = 5;
  {$EXTERNALSYM WKSTA_VER_MINOR_PARMNUM}
  WKSTA_LOGGED_ON_USERS_PARMNUM = 6;
  {$EXTERNALSYM WKSTA_LOGGED_ON_USERS_PARMNUM}
  WKSTA_LANROOT_PARMNUM         = 7;
  {$EXTERNALSYM WKSTA_LANROOT_PARMNUM}
  WKSTA_LOGON_DOMAIN_PARMNUM    = 8;
  {$EXTERNALSYM WKSTA_LOGON_DOMAIN_PARMNUM}
  WKSTA_LOGON_SERVER_PARMNUM    = 9;
  {$EXTERNALSYM WKSTA_LOGON_SERVER_PARMNUM}
  WKSTA_CHARWAIT_PARMNUM        = 10; // Supported by down-level.
  {$EXTERNALSYM WKSTA_CHARWAIT_PARMNUM}
  WKSTA_CHARTIME_PARMNUM        = 11; // Supported by down-level.
  {$EXTERNALSYM WKSTA_CHARTIME_PARMNUM}
  WKSTA_CHARCOUNT_PARMNUM       = 12; // Supported by down-level.
  {$EXTERNALSYM WKSTA_CHARCOUNT_PARMNUM}
  WKSTA_KEEPCONN_PARMNUM        = 13;
  {$EXTERNALSYM WKSTA_KEEPCONN_PARMNUM}
  WKSTA_KEEPSEARCH_PARMNUM      = 14;
  {$EXTERNALSYM WKSTA_KEEPSEARCH_PARMNUM}
  WKSTA_MAXCMDS_PARMNUM         = 15;
  {$EXTERNALSYM WKSTA_MAXCMDS_PARMNUM}
  WKSTA_NUMWORKBUF_PARMNUM      = 16;
  {$EXTERNALSYM WKSTA_NUMWORKBUF_PARMNUM}
  WKSTA_MAXWRKCACHE_PARMNUM     = 17;
  {$EXTERNALSYM WKSTA_MAXWRKCACHE_PARMNUM}
  WKSTA_SESSTIMEOUT_PARMNUM     = 18;
  {$EXTERNALSYM WKSTA_SESSTIMEOUT_PARMNUM}
  WKSTA_SIZERROR_PARMNUM        = 19;
  {$EXTERNALSYM WKSTA_SIZERROR_PARMNUM}
  WKSTA_NUMALERTS_PARMNUM       = 20;
  {$EXTERNALSYM WKSTA_NUMALERTS_PARMNUM}
  WKSTA_NUMSERVICES_PARMNUM     = 21;
  {$EXTERNALSYM WKSTA_NUMSERVICES_PARMNUM}
  WKSTA_NUMCHARBUF_PARMNUM      = 22;
  {$EXTERNALSYM WKSTA_NUMCHARBUF_PARMNUM}
  WKSTA_SIZCHARBUF_PARMNUM      = 23;
  {$EXTERNALSYM WKSTA_SIZCHARBUF_PARMNUM}
  WKSTA_ERRLOGSZ_PARMNUM        = 27; // Supported by down-level.
  {$EXTERNALSYM WKSTA_ERRLOGSZ_PARMNUM}
  WKSTA_PRINTBUFTIME_PARMNUM    = 28; // Supported by down-level.
  {$EXTERNALSYM WKSTA_PRINTBUFTIME_PARMNUM}
  WKSTA_SIZWORKBUF_PARMNUM      = 29;
  {$EXTERNALSYM WKSTA_SIZWORKBUF_PARMNUM}
  WKSTA_MAILSLOTS_PARMNUM       = 30;
  {$EXTERNALSYM WKSTA_MAILSLOTS_PARMNUM}
  WKSTA_NUMDGRAMBUF_PARMNUM     = 31;
  {$EXTERNALSYM WKSTA_NUMDGRAMBUF_PARMNUM}
  WKSTA_WRKHEURISTICS_PARMNUM   = 32; // Supported by down-level.
  {$EXTERNALSYM WKSTA_WRKHEURISTICS_PARMNUM}
  WKSTA_MAXTHREADS_PARMNUM      = 33;
  {$EXTERNALSYM WKSTA_MAXTHREADS_PARMNUM}

  WKSTA_LOCKQUOTA_PARMNUM               = 41;
  {$EXTERNALSYM WKSTA_LOCKQUOTA_PARMNUM}
  WKSTA_LOCKINCREMENT_PARMNUM           = 42;
  {$EXTERNALSYM WKSTA_LOCKINCREMENT_PARMNUM}
  WKSTA_LOCKMAXIMUM_PARMNUM             = 43;
  {$EXTERNALSYM WKSTA_LOCKMAXIMUM_PARMNUM}
  WKSTA_PIPEINCREMENT_PARMNUM           = 44;
  {$EXTERNALSYM WKSTA_PIPEINCREMENT_PARMNUM}
  WKSTA_PIPEMAXIMUM_PARMNUM             = 45;
  {$EXTERNALSYM WKSTA_PIPEMAXIMUM_PARMNUM}
  WKSTA_DORMANTFILELIMIT_PARMNUM        = 46;
  {$EXTERNALSYM WKSTA_DORMANTFILELIMIT_PARMNUM}
  WKSTA_CACHEFILETIMEOUT_PARMNUM        = 47;
  {$EXTERNALSYM WKSTA_CACHEFILETIMEOUT_PARMNUM}
  WKSTA_USEOPPORTUNISTICLOCKING_PARMNUM = 48;
  {$EXTERNALSYM WKSTA_USEOPPORTUNISTICLOCKING_PARMNUM}
  WKSTA_USEUNLOCKBEHIND_PARMNUM         = 49;
  {$EXTERNALSYM WKSTA_USEUNLOCKBEHIND_PARMNUM}
  WKSTA_USECLOSEBEHIND_PARMNUM          = 50;
  {$EXTERNALSYM WKSTA_USECLOSEBEHIND_PARMNUM}
  WKSTA_BUFFERNAMEDPIPES_PARMNUM        = 51;
  {$EXTERNALSYM WKSTA_BUFFERNAMEDPIPES_PARMNUM}
  WKSTA_USELOCKANDREADANDUNLOCK_PARMNUM = 52;
  {$EXTERNALSYM WKSTA_USELOCKANDREADANDUNLOCK_PARMNUM}
  WKSTA_UTILIZENTCACHING_PARMNUM        = 53;
  {$EXTERNALSYM WKSTA_UTILIZENTCACHING_PARMNUM}
  WKSTA_USERAWREAD_PARMNUM              = 54;
  {$EXTERNALSYM WKSTA_USERAWREAD_PARMNUM}
  WKSTA_USERAWWRITE_PARMNUM             = 55;
  {$EXTERNALSYM WKSTA_USERAWWRITE_PARMNUM}
  WKSTA_USEWRITERAWWITHDATA_PARMNUM     = 56;
  {$EXTERNALSYM WKSTA_USEWRITERAWWITHDATA_PARMNUM}
  WKSTA_USEENCRYPTION_PARMNUM           = 57;
  {$EXTERNALSYM WKSTA_USEENCRYPTION_PARMNUM}
  WKSTA_BUFFILESWITHDENYWRITE_PARMNUM   = 58;
  {$EXTERNALSYM WKSTA_BUFFILESWITHDENYWRITE_PARMNUM}
  WKSTA_BUFFERREADONLYFILES_PARMNUM     = 59;
  {$EXTERNALSYM WKSTA_BUFFERREADONLYFILES_PARMNUM}
  WKSTA_FORCECORECREATEMODE_PARMNUM     = 60;
  {$EXTERNALSYM WKSTA_FORCECORECREATEMODE_PARMNUM}
  WKSTA_USE512BYTESMAXTRANSFER_PARMNUM  = 61;
  {$EXTERNALSYM WKSTA_USE512BYTESMAXTRANSFER_PARMNUM}
  WKSTA_READAHEADTHRUPUT_PARMNUM        = 62;
  {$EXTERNALSYM WKSTA_READAHEADTHRUPUT_PARMNUM}

//
// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaUserSetInfo.
//

  WKSTA_OTH_DOMAINS_PARMNUM = 101;
  {$EXTERNALSYM WKSTA_OTH_DOMAINS_PARMNUM}

//
// One of these values indicates the parameter within an information
// structure that is invalid when ERROR_INVALID_PARAMETER is returned by
// NetWkstaTransportAdd.
//

  TRANSPORT_QUALITYOFSERVICE_PARMNUM = 201;
  {$EXTERNALSYM TRANSPORT_QUALITYOFSERVICE_PARMNUM}
  TRANSPORT_NAME_PARMNUM             = 202;
  {$EXTERNALSYM TRANSPORT_NAME_PARMNUM}

implementation


{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaGetInfo: Pointer;

function NetWkstaGetInfo;
begin
  GetProcedureAddress(_NetWkstaGetInfo, netapi32, 'NetWkstaGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaGetInfo]
  end;
end;
{$ELSE}
function NetWkstaGetInfo; external netapi32 name 'NetWkstaGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaSetInfo: Pointer;

function NetWkstaSetInfo;
begin
  GetProcedureAddress(_NetWkstaSetInfo, netapi32, 'NetWkstaSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaSetInfo]
  end;
end;
{$ELSE}
function NetWkstaSetInfo; external netapi32 name 'NetWkstaSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaUserGetInfo: Pointer;

function NetWkstaUserGetInfo;
begin
  GetProcedureAddress(_NetWkstaUserGetInfo, netapi32, 'NetWkstaUserGetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaUserGetInfo]
  end;
end;
{$ELSE}
function NetWkstaUserGetInfo; external netapi32 name 'NetWkstaUserGetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaUserSetInfo: Pointer;

function NetWkstaUserSetInfo;
begin
  GetProcedureAddress(_NetWkstaUserSetInfo, netapi32, 'NetWkstaUserSetInfo');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaUserSetInfo]
  end;
end;
{$ELSE}
function NetWkstaUserSetInfo; external netapi32 name 'NetWkstaUserSetInfo';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaUserEnum: Pointer;

function NetWkstaUserEnum;
begin
  GetProcedureAddress(_NetWkstaUserEnum, netapi32, 'NetWkstaUserEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaUserEnum]
  end;
end;
{$ELSE}
function NetWkstaUserEnum; external netapi32 name 'NetWkstaUserEnum';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaTransportAdd: Pointer;

function NetWkstaTransportAdd;
begin
  GetProcedureAddress(_NetWkstaTransportAdd, netapi32, 'NetWkstaTransportAdd');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaTransportAdd]
  end;
end;
{$ELSE}
function NetWkstaTransportAdd; external netapi32 name 'NetWkstaTransportAdd';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaTransportDel: Pointer;

function NetWkstaTransportDel;
begin
  GetProcedureAddress(_NetWkstaTransportDel, netapi32, 'NetWkstaTransportDel');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaTransportDel]
  end;
end;
{$ELSE}
function NetWkstaTransportDel; external netapi32 name 'NetWkstaTransportDel';
{$ENDIF DYNAMIC_LINK}

{$IFDEF DYNAMIC_LINK}
var
  _NetWkstaTransportEnum: Pointer;

function NetWkstaTransportEnum;
begin
  GetProcedureAddress(_NetWkstaTransportEnum, netapi32, 'NetWkstaTransportEnum');
  asm
    mov esp, ebp
    pop ebp
    jmp [_NetWkstaTransportEnum]
  end;
end;
{$ELSE}
function NetWkstaTransportEnum; external netapi32 name 'NetWkstaTransportEnum';
{$ENDIF DYNAMIC_LINK}

end.
