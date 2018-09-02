{******************************************************************************}
{                                                       	               }
{ ICMP Echo API interface Unit for Object Pascal                               }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: icmpapi.h, released Feb 2003. The original Pascal      }
{ code is: IcmpApi.pas, released December 2003. The initial developer of the   }
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

unit JwaIcmpApi;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "icmpapi.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType, JwaIpExport, JwaWS2tcpip;

//    Declarations for the Win32 ICMP Echo request API.

//
// Exported Routines.
//

//++
//
// Routine Name:
//
//     IcmpCreateFile
//
// Routine Description:
//
//     Opens a handle on which ICMP Echo Requests can be issued.
//
// Arguments:
//
//     None.
//
// Return Value:
//
//     An open file handle or INVALID_HANDLE_VALUE. Extended error information
//     is available by calling GetLastError().
//
//--

function IcmpCreateFile: HANDLE; stdcall;
{$EXTERNALSYM IcmpCreateFile}

//++
//
// Routine Name:
//
//     Icmp6CreateFile
//
// Routine Description:
//
//     Opens a handle on which ICMPv6 Echo Requests can be issued.
//
// Arguments:
//
//     None.
//
// Return Value:
//
//     An open file handle or INVALID_HANDLE_VALUE. Extended error information
//     is available by calling GetLastError().
//
//--

function Icmp6CreateFile: HANDLE; stdcall;
{$EXTERNALSYM Icmp6CreateFile}

//++
//
// Routine Name:
//
//     IcmpCloseHandle
//
// Routine Description:
//
//     Closes a handle opened by ICMPOpenFile.
//
// Arguments:
//
//     IcmpHandle  - The handle to close.
//
// Return Value:
//
//     TRUE if the handle was closed successfully, otherwise FALSE. Extended
//     error information is available by calling GetLastError().
//
//--

function IcmpCloseHandle(IcmpHandle: HANDLE): BOOL; stdcall;
{$EXTERNALSYM IcmpCloseHandle}

//++
//
// Routine Name:
//
//     IcmpSendEcho
//
// Routine Description:
//
//     Sends an ICMP Echo request and returns any replies. The
//     call returns when the timeout has expired or the reply buffer
//     is filled.
//
// Arguments:
//
//     IcmpHandle           - An open handle returned by ICMPCreateFile.
//
//     DestinationAddress   - The destination of the echo request.
//
//     RequestData          - A buffer containing the data to send in the
//                            request.
//
//     RequestSize          - The number of bytes in the request data buffer.
//
//     RequestOptions       - Pointer to the IP header options for the request.
//                            May be NULL.
//
//     ReplyBuffer          - A buffer to hold any replies to the request.
//                            On return, the buffer will contain an array of
//                            ICMP_ECHO_REPLY structures followed by the
//                            options and data for the replies. The buffer
//                            should be large enough to hold at least one
//                            ICMP_ECHO_REPLY structure plus
//                            MAX(RequestSize, 8) bytes of data since an ICMP
//                            error message contains 8 bytes of data.
//
//     ReplySize            - The size in bytes of the reply buffer.
//
//     Timeout              - The time in milliseconds to wait for replies.
//
// Return Value:
//
//     Returns the number of ICMP_ECHO_REPLY structures stored in ReplyBuffer.
//     The status of each reply is contained in the structure. If the return
//     value is zero, extended error information is available via
//     GetLastError().
//
//--

function IcmpSendEcho(
  IcmpHandle: HANDLE;
  DestinationAddress: IpAddr;
  RequestData: LPVOID;
  RequestSize: WORD;
  RequestOptions: PIP_OPTION_INFORMATION;
  ReplyBuffer: LPVOID;
  ReplySize: DWORD;
  Timeout: DWORD): DWORD; stdcall;
{$EXTERNALSYM IcmpSendEcho}

//++
//
// Routine Description:
//
//    Sends an ICMP Echo request and the call returns either immediately
//    (if Event or ApcRoutine is NonNULL) or returns after the specified
//    timeout.   The ReplyBuffer contains the ICMP responses, if any.
//
// Arguments:
//
//    IcmpHandle           - An open handle returned by ICMPCreateFile.
//
//    Event                - This is the event to be signalled whenever an IcmpResponse
//                           comes in.
//
//    ApcRoutine           - This routine would be called when the calling thread
//                           is in an alertable thread and an ICMP reply comes in.
//
//    ApcContext           - This optional parameter is given to the ApcRoutine when
//                           this call succeeds.
//
//    DestinationAddress   - The destination of the echo request.
//
//    RequestData          - A buffer containing the data to send in the
//                           request.
//
//    RequestSize          - The number of bytes in the request data buffer.
//
//    RequestOptions       - Pointer to the IP header options for the request.
//                           May be NULL.
//
//    ReplyBuffer          - A buffer to hold any replies to the request.
//                           On return, the buffer will contain an array of
//                           ICMP_ECHO_REPLY structures followed by options
//                           and data. The buffer must be large enough to
//                           hold at least one ICMP_ECHO_REPLY structure.
//                           It should be large enough to also hold
//                           8 more bytes of data - this is the size of
//                           an ICMP error message.
//
//    ReplySize            - The size in bytes of the reply buffer.
//
//    Timeout              - The time in milliseconds to wait for replies.
//                           This is NOT used if ApcRoutine is not NULL or if Event
//                           is not NULL.
//
// Return Value:
//
//    Returns the number of replies received and stored in ReplyBuffer. If
//    the return value is zero, extended error information is available
//    via GetLastError().
//
// Remarks:
//
//    On NT platforms,
//    If used Asynchronously (either ApcRoutine or Event is specified), then
//    ReplyBuffer and ReplySize are still needed.  This is where the response
//    comes in.
//    ICMP Response data is copied to the ReplyBuffer provided, and the caller of
//    this function has to parse it asynchronously.  The function IcmpParseReply
//    is provided for this purpose.
//
//    On non-NT platforms,
//    Event, ApcRoutine and ApcContext are IGNORED.
//
//--


function IcmpSendEcho2(
  IcmpHandle: HANDLE;
  Event: HANDLE;
  {$IFDEF PIO_APC_ROUTINE_DEFINED}
  ApcRoutine: PIO_APC_ROUTINE;
  {$ELSE}
  ApcRoutine: FARPROC;
  {$ENDIF}
  ApcContext: PVOID;
  DestinationAddress: IpAddr;
  RequestData: LPVOID;
  RequestSize: WORD;
  RequestOptions: PIP_OPTION_INFORMATION;
  ReplyBuffer: LPVOID;
  ReplySize: DWORD;
  Timeout: DWORD): DWORD; stdcall;

function Icmp6SendEcho2(
  IcmpHandle: HANDLE;
  Event: HANDLE;
  {$IFDEF PIO_APC_ROUTINE_DEFINED}
  ApcRoutine: PIO_APC_ROUTINE;
  {$ELSE}
  ApcRoutine: FARPROC;
  {$ENDIF}
  ApcContext: PVOID;
  SourceAddress: Psockaddr_in6;
  DestinationAddress: Psockaddr_in6;
  RequestData,
  RequestSize: WORD;
  RequestOptions: PIP_OPTION_INFORMATION;
  ReplyBuffer: LPVOID;
  ReplySize: DWORD;
  Timeout: DWORD): DWORD; stdcall;

//++
//
// Routine Description:
//
//    Parses the reply buffer provided and returns the number of ICMP responses found.
//
// Arguments:
//
//    ReplyBuffer            - This must be the same buffer that was passed to IcmpSendEcho2
//                             This is rewritten to hold an array of ICMP_ECHO_REPLY structures.
//                             (i.e. the type is PICMP_ECHO_REPLY).
//
//    ReplySize              - This must be the size of the above buffer.
//
// Return Value:
//    Returns the number of ICMP responses found.  If there is an errors, return value is
//    zero.  The error can be determined by a call to GetLastError.
//
// Remarks:
//    This function SHOULD NOT BE USED on a reply buffer that was passed to SendIcmpEcho.
//    SendIcmpEcho actually parses the buffer before returning back to the user.  This function
//    is meant to be used only with SendIcmpEcho2.
//--

function IcmpParseReplies(ReplyBuffer: LPVOID; ReplySize: DWORD): DWORD; stdcall;
{$EXTERNALSYM IcmpParseReplies}

function Icmp6ParseReplies(ReplyBuffer: LPVOID; ReplySize: DWORD): DWORD; stdcall;
{$EXTERNALSYM Icmp6ParseReplies}

implementation

const
  icmp_lib = 'iphlpapi.dll';

function IcmpCreateFile; external icmp_lib name 'IcmpCreateFile';
function Icmp6CreateFile; external icmp_lib name 'Icmp6CreateFile';
function IcmpCloseHandle; external icmp_lib name 'IcmpCloseHandle';
function IcmpSendEcho; external icmp_lib name 'IcmpSendEcho';
function IcmpSendEcho2; external icmp_lib name 'IcmpSendEcho2';
function Icmp6SendEcho2; external icmp_lib name 'Icmp6SendEcho2';
function IcmpParseReplies; external icmp_lib name 'IcmpParseReplies';
function Icmp6ParseReplies; external icmp_lib name 'Icmp6ParseReplies';

end.
