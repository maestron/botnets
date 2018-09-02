{******************************************************************************}
{                                                       	               }
{ Background file copier error codes API interface Unit for Object Pascal      }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: bitsmsg.h, released June 2000. The original Pascal     }
{ code is: BitsMsg.pas, released December 2000. The initial developer of the   }
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

unit JwaBitsMsg;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "BitsMsg.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinType;

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//

const

//
// MessageId: BG_E_NOT_FOUND
//
// MessageText:
//
//  The requested job was not found.
//
  BG_E_NOT_FOUND = DWORD($80200001);
  {$EXTERNALSYM BG_E_NOT_FOUND}

//
// MessageId: BG_E_INVALID_STATE
//
// MessageText:
//
//  The requested action is not allowed in the current job state. The job might have been canceled or completed transferring. It is in a read-only state now.
//
  BG_E_INVALID_STATE = DWORD($80200002);
  {$EXTERNALSYM BG_E_INVALID_STATE}

//
// MessageId: BG_E_EMPTY
//
// MessageText:
//
//  There are no files attached to this job. Attach files to the job, and then try again.
//
  BG_E_EMPTY = DWORD($80200003);
  {$EXTERNALSYM BG_E_EMPTY}

//
// MessageId: BG_E_FILE_NOT_AVAILABLE
//
// MessageText:
//
//  No file is available because no URL generated an error.
//
  BG_E_FILE_NOT_AVAILABLE = DWORD($80200004);
  {$EXTERNALSYM BG_E_FILE_NOT_AVAILABLE}

//
// MessageId: BG_E_PROTOCOL_NOT_AVAILABLE
//
// MessageText:
//
//  No protocol is available because no URL generated an error.
//
  BG_E_PROTOCOL_NOT_AVAILABLE = DWORD($80200005);
  {$EXTERNALSYM BG_E_PROTOCOL_NOT_AVAILABLE}

//
// MessageId: BG_S_ERROR_CONTEXT_NONE
//
// MessageText:
//
//  No errors have occurred.
//
  BG_S_ERROR_CONTEXT_NONE = DWORD($00200006);
  {$EXTERNALSYM BG_S_ERROR_CONTEXT_NONE}

//
// MessageId: BG_E_ERROR_CONTEXT_UNKNOWN
//
// MessageText:
//
//  The error occurred in an unknown location.
//
  BG_E_ERROR_CONTEXT_UNKNOWN = DWORD($80200007);
  {$EXTERNALSYM BG_E_ERROR_CONTEXT_UNKNOWN}

//
// MessageId: BG_E_ERROR_CONTEXT_GENERAL_QUEUE_MANAGER
//
// MessageText:
//
//  The error occurred in the Background Intelligent Transfer Service (BITS) queue manager.
//
  BG_E_ERROR_CONTEXT_GENERAL_QUEUE_MANAGER = DWORD($80200008);
  {$EXTERNALSYM BG_E_ERROR_CONTEXT_GENERAL_QUEUE_MANAGER}

//
// MessageId: BG_E_ERROR_CONTEXT_LOCAL_FILE
//
// MessageText:
//
//  The error occurred while the local file was being processed. Verify that the file is not in use, and then try again.
//
  BG_E_ERROR_CONTEXT_LOCAL_FILE = DWORD($80200009);
  {$EXTERNALSYM BG_E_ERROR_CONTEXT_LOCAL_FILE}

//
// MessageId: BG_E_ERROR_CONTEXT_REMOTE_FILE
//
// MessageText:
//
//  The error occurred while the remote file was being processed.
//
  BG_E_ERROR_CONTEXT_REMOTE_FILE = DWORD($8020000A);
  {$EXTERNALSYM BG_E_ERROR_CONTEXT_REMOTE_FILE}

//
// MessageId: BG_E_ERROR_CONTEXT_GENERAL_TRANSPORT
//
// MessageText:
//
//  The error occurred in the transport layer. The client could not connect to the server.
//
  BG_E_ERROR_CONTEXT_GENERAL_TRANSPORT = DWORD($8020000B);
  {$EXTERNALSYM BG_E_ERROR_CONTEXT_GENERAL_TRANSPORT}

//
// MessageId: BG_E_ERROR_CONTEXT_QUEUE_MANAGER_NOTIFICATION
//
// MessageText:
//
//  The error occurred while the notification callback was being processed. Background Intelligent Transfer Service (BITS) will try again later.
//
  BG_E_ERROR_CONTEXT_QUEUE_MANAGER_NOTIFICATION = DWORD($8020000C);
  {$EXTERNALSYM BG_E_ERROR_CONTEXT_QUEUE_MANAGER_NOTIFICATION}

//
// MessageId: BG_E_DESTINATION_LOCKED
//
// MessageText:
//
//  The destination file system volume is not available. Verify that another program, such as CheckDisk, is not running, which would lock the volume. When the volume is available, Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_DESTINATION_LOCKED = DWORD($8020000D);
  {$EXTERNALSYM BG_E_DESTINATION_LOCKED}

//
// MessageId: BG_E_VOLUME_CHANGED
//
// MessageText:
//
//  The destination volume has changed. If the disk is removable, it might have been replaced with a different disk. Reinsert the original disk and resume the job.
//
  BG_E_VOLUME_CHANGED = DWORD($8020000E);
  {$EXTERNALSYM BG_E_VOLUME_CHANGED}

//
// MessageId: BG_E_ERROR_INFORMATION_UNAVAILABLE
//
// MessageText:
//
//  No errors have occurred.
//
  BG_E_ERROR_INFORMATION_UNAVAILABLE = DWORD($8020000F);
  {$EXTERNALSYM BG_E_ERROR_INFORMATION_UNAVAILABLE}

//
// MessageId: BG_E_NETWORK_DISCONNECTED
//
// MessageText:
//
//  There are currently no active network connections. Background Intelligent Transfer Service (BITS) will try again when an adapter is connected.
//
  BG_E_NETWORK_DISCONNECTED = DWORD($80200010);
  {$EXTERNALSYM BG_E_NETWORK_DISCONNECTED}

//
// MessageId: BG_E_MISSING_FILE_SIZE
//
// MessageText:
//
//  The server did not return the file size. The URL might point to dynamic content. The Content-Length header is not available in the server's HTTP reply.
//
  BG_E_MISSING_FILE_SIZE = DWORD($80200011);
  {$EXTERNALSYM BG_E_MISSING_FILE_SIZE}

//
// MessageId: BG_E_INSUFFICIENT_HTTP_SUPPORT
//
// MessageText:
//
//  The server does not support HTTP 1.1.
//
  BG_E_INSUFFICIENT_HTTP_SUPPORT = DWORD($80200012);
  {$EXTERNALSYM BG_E_INSUFFICIENT_HTTP_SUPPORT}

//
// MessageId: BG_E_INSUFFICIENT_RANGE_SUPPORT
//
// MessageText:
//
//  The server does not support the necessary HTTP protocol. Background Intelligent Transfer Service (BITS) requires that the server support the Range protocol header.
//
  BG_E_INSUFFICIENT_RANGE_SUPPORT = DWORD($80200013);
  {$EXTERNALSYM BG_E_INSUFFICIENT_RANGE_SUPPORT}

//
// MessageId: BG_E_REMOTE_NOT_SUPPORTED
//
// MessageText:
//
//  Background Intelligent Transfer Service (BITS) cannot be used remotely.
//
  BG_E_REMOTE_NOT_SUPPORTED = DWORD($80200014);
  {$EXTERNALSYM BG_E_REMOTE_NOT_SUPPORTED}

//
// MessageId: BG_E_NEW_OWNER_DIFF_MAPPING
//
// MessageText:
//
//  The drive mapping for the job is different for the current owner than for the previous owner. Use a UNC path instead.
//
  BG_E_NEW_OWNER_DIFF_MAPPING = DWORD($80200015);
  {$EXTERNALSYM BG_E_NEW_OWNER_DIFF_MAPPING}

//
// MessageId: BG_E_NEW_OWNER_NO_FILE_ACCESS
//
// MessageText:
//
//  The new owner has insufficient access to the local files for the job. The new owner might not have permissions to access the job files. Verify that the new owner has sufficient permissions, and then try again.
//
  BG_E_NEW_OWNER_NO_FILE_ACCESS = DWORD($80200016);
  {$EXTERNALSYM BG_E_NEW_OWNER_NO_FILE_ACCESS}

//
// MessageId: BG_S_PARTIAL_COMPLETE
//
// MessageText:
//
//  Some of the transferred files were deleted because they were incomplete.
//
  BG_S_PARTIAL_COMPLETE = DWORD($00200017);
  {$EXTERNALSYM BG_S_PARTIAL_COMPLETE}

//
// MessageId: BG_E_PROXY_LIST_TOO_LARGE
//
// MessageText:
//
//  The HTTP proxy list cannot be longer than 32,000 characters. Try again with a shorter proxy list.
//
  BG_E_PROXY_LIST_TOO_LARGE = DWORD($80200018);
  {$EXTERNALSYM BG_E_PROXY_LIST_TOO_LARGE}

//
// MessageId: BG_E_PROXY_BYPASS_LIST_TOO_LARGE
//
// MessageText:
//
//  The HTTP proxy bypass list cannot be longer than 32,000 characters. Try again with a shorter bypass proxy list.
//
  BG_E_PROXY_BYPASS_LIST_TOO_LARGE = DWORD($80200019);
  {$EXTERNALSYM BG_E_PROXY_BYPASS_LIST_TOO_LARGE}

//
// MessageId: BG_S_UNABLE_TO_DELETE_FILES
//
// MessageText:
//
//  Some of the temporary files could not be deleted. Check the system event log for the complete list of files that could not be deleted.
//
  BG_S_UNABLE_TO_DELETE_FILES = DWORD($0020001A);
  {$EXTERNALSYM BG_S_UNABLE_TO_DELETE_FILES}

//
// MessageId: BG_E_INVALID_SERVER_RESPONSE
//
// MessageText:
//
//  The server's response was not valid. The server was not following the defined protocol. Resume the job, and then Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_INVALID_SERVER_RESPONSE = DWORD($8020001B);
  {$EXTERNALSYM BG_E_INVALID_SERVER_RESPONSE}

//
// MessageId: BG_E_TOO_MANY_FILES
//
// MessageText:
//
//  No more files can be added to this job.
//
  BG_E_TOO_MANY_FILES = DWORD($8020001C);
  {$EXTERNALSYM BG_E_TOO_MANY_FILES}

//
// MessageId: BG_E_LOCAL_FILE_CHANGED
//
// MessageText:
//
//  The local file was changed during the transfer. Recreate the job, and then try to transfer it again.
//
  BG_E_LOCAL_FILE_CHANGED = DWORD($8020001D);
  {$EXTERNALSYM BG_E_LOCAL_FILE_CHANGED}

//
// MessageId: BG_E_ERROR_CONTEXT_REMOTE_APPLICATION
//
// MessageText:
//
//  The program on the remote server reported the error.
//
  BG_E_ERROR_CONTEXT_REMOTE_APPLICATION = DWORD($8020001E);
  {$EXTERNALSYM BG_E_ERROR_CONTEXT_REMOTE_APPLICATION}

//
// MessageId: BG_E_SESSION_NOT_FOUND
//
// MessageText:
//
//  The specified session could not be found on the server. Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_SESSION_NOT_FOUND = DWORD($8020001F);
  {$EXTERNALSYM BG_E_SESSION_NOT_FOUND}

//
// MessageId: BG_E_TOO_LARGE
//
// MessageText:
//
//  The job is too large for the server to accept. This job might exceed a job size limit set by the server administrator. Reduce the size of the job, and then try again.
//
  BG_E_TOO_LARGE = DWORD($80200020);
  {$EXTERNALSYM BG_E_TOO_LARGE}

//
// MessageId: BG_E_STRING_TOO_LONG
//
// MessageText:
//
//  The specified string is too long.
//
  BG_E_STRING_TOO_LONG = DWORD($80200021);
  {$EXTERNALSYM BG_E_STRING_TOO_LONG}

//
// MessageId: BG_E_CLIENT_SERVER_PROTOCOL_MISMATCH
//
// MessageText:
//
//  The client and server versions of Background Intelligent Transfer Service (BITS) are incompatible.
//
  BG_E_CLIENT_SERVER_PROTOCOL_MISMATCH = DWORD($80200022);
  {$EXTERNALSYM BG_E_CLIENT_SERVER_PROTOCOL_MISMATCH}

//
// MessageId: BG_E_SERVER_EXECUTE_ENABLE
//
// MessageText:
//
//  Scripting OR execute permissions are enabled on the IIS virtual directory associated with the job. To upload files to the virtual directory, disable the scripting and execute permissions on the virtual directory.
//
  BG_E_SERVER_EXECUTE_ENABLE = DWORD($80200023);
  {$EXTERNALSYM BG_E_SERVER_EXECUTE_ENABLE}

//
// MessageId: BG_E_NO_PROGRESS
//
// MessageText:
//
//  The job is not making headway.  The server may be misconfigured.  Background Intelligent Transfer Service (BITS) will try again later.
//
  BG_E_NO_PROGRESS = DWORD($80200024);
  {$EXTERNALSYM BG_E_NO_PROGRESS}

//
// MessageId: BG_E_USERNAME_TOO_LARGE
//
// MessageText:
//
//  The user name cannot be longer than 300 characters. Try again with a shorter name.
//
  BG_E_USERNAME_TOO_LARGE = DWORD($80200025);
  {$EXTERNALSYM BG_E_USERNAME_TOO_LARGE}

//
// MessageId: BG_E_PASSWORD_TOO_LARGE
//
// MessageText:
//
//  The password cannot be longer than 300 characters. Try again with a shorter password.
//
  BG_E_PASSWORD_TOO_LARGE = DWORD($80200026);
  {$EXTERNALSYM BG_E_PASSWORD_TOO_LARGE}

//
// MessageId: BG_E_INVALID_AUTH_TARGET
//
// MessageText:
//
//  The authentication target specified in the credentials is not defined.
//
  BG_E_INVALID_AUTH_TARGET = DWORD($80200027);
  {$EXTERNALSYM BG_E_INVALID_AUTH_TARGET}

//
// MessageId: BG_E_INVALID_AUTH_SCHEME
//
// MessageText:
//
//  The authentication scheme specified in the credentials is not defined.
//
  BG_E_INVALID_AUTH_SCHEME = DWORD($80200028);
  {$EXTERNALSYM BG_E_INVALID_AUTH_SCHEME}

//
// MessageId: BG_E_HTTP_ERROR_100
//
// MessageText:
//
//  The request can be continued.
//
  BG_E_HTTP_ERROR_100 = DWORD($80190064);
  {$EXTERNALSYM BG_E_HTTP_ERROR_100}

//
// MessageId: BG_E_HTTP_ERROR_101
//
// MessageText:
//
//  The server switched protocols in an upgrade header.
//
  BG_E_HTTP_ERROR_101 = DWORD($80190065);
  {$EXTERNALSYM BG_E_HTTP_ERROR_101}

//
// MessageId: BG_E_HTTP_ERROR_200
//
// MessageText:
//
//  The server's response was not valid. The server was not following the defined protocol. Resume the job, and then Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_HTTP_ERROR_200 = DWORD($801900C8);
  {$EXTERNALSYM BG_E_HTTP_ERROR_200}

//
// MessageId: BG_E_HTTP_ERROR_201
//
// MessageText:
//
//  The request was fulfilled and resulted in the creation of a new resource.
//
  BG_E_HTTP_ERROR_201 = DWORD($801900C9);
  {$EXTERNALSYM BG_E_HTTP_ERROR_201}

//
// MessageId: BG_E_HTTP_ERROR_202
//
// MessageText:
//
//  The request was accepted for processing, but the processing has not been completed yet.
//
  BG_E_HTTP_ERROR_202 = DWORD($801900CA);
  {$EXTERNALSYM BG_E_HTTP_ERROR_202}

//
// MessageId: BG_E_HTTP_ERROR_203
//
// MessageText:
//
//  The returned metadata in the entity-header is not the definitive set available from the server of origin.
//
  BG_E_HTTP_ERROR_203 = DWORD($801900CB);
  {$EXTERNALSYM BG_E_HTTP_ERROR_203}

//
// MessageId: BG_E_HTTP_ERROR_204
//
// MessageText:
//
//  The server has fulfilled the request, but there is no new information to send back.
//
  BG_E_HTTP_ERROR_204 = DWORD($801900CC);
  {$EXTERNALSYM BG_E_HTTP_ERROR_204}

//
// MessageId: BG_E_HTTP_ERROR_205
//
// MessageText:
//
//  The server's response was not valid. The server was not following the defined protocol. Resume the job, and then Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_HTTP_ERROR_205 = DWORD($801900CD);
  {$EXTERNALSYM BG_E_HTTP_ERROR_205}

//
// MessageId: BG_E_HTTP_ERROR_206
//
// MessageText:
//
//  The server fulfilled the partial GET request for the resource.
//
  BG_E_HTTP_ERROR_206 = DWORD($801900CE);
  {$EXTERNALSYM BG_E_HTTP_ERROR_206}

//
// MessageId: BG_E_HTTP_ERROR_300
//
// MessageText:
//
//  The server could not return the requested data.
//
  BG_E_HTTP_ERROR_300 = DWORD($8019012C);
  {$EXTERNALSYM BG_E_HTTP_ERROR_300}

//
// MessageId: BG_E_HTTP_ERROR_301
//
// MessageText:
//
//  The requested resource was assigned to a new permanent Uniform Resource Identifier (URI), and any future references to this resource should use one of the returned URIs.
//
  BG_E_HTTP_ERROR_301 = DWORD($8019012D);
  {$EXTERNALSYM BG_E_HTTP_ERROR_301}

//
// MessageId: BG_E_HTTP_ERROR_302
//
// MessageText:
//
//  The requested resource was assigned a different Uniform Resource Identifier (URI). This change is temporary.
//
  BG_E_HTTP_ERROR_302 = DWORD($8019012E);
  {$EXTERNALSYM BG_E_HTTP_ERROR_302}

//
// MessageId: BG_E_HTTP_ERROR_303
//
// MessageText:
//
//  The response to the request is under a different Uniform Resource Identifier (URI) and must be retrieved using a GET method on that resource.
//
  BG_E_HTTP_ERROR_303 = DWORD($8019012F);
  {$EXTERNALSYM BG_E_HTTP_ERROR_303}

//
// MessageId: BG_E_HTTP_ERROR_304
//
// MessageText:
//
//  The server's response was not valid. The server was not following the defined protocol. Resume the job, and then Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_HTTP_ERROR_304 = DWORD($80190130);
  {$EXTERNALSYM BG_E_HTTP_ERROR_304}

//
// MessageId: BG_E_HTTP_ERROR_305
//
// MessageText:
//
//  The requested resource must be accessed through the proxy given by the location field.
//
  BG_E_HTTP_ERROR_305 = DWORD($80190131);
  {$EXTERNALSYM BG_E_HTTP_ERROR_305}

//
// MessageId: BG_E_HTTP_ERROR_307
//
// MessageText:
//
//  The URL has been temporarily relocated. Try again later.
//
  BG_E_HTTP_ERROR_307 = DWORD($80190133);
  {$EXTERNALSYM BG_E_HTTP_ERROR_307}

//
// MessageId: BG_E_HTTP_ERROR_400
//
// MessageText:
//
//  The server cannot process the request because the syntax is not valid.
//
  BG_E_HTTP_ERROR_400 = DWORD($80190190);
  {$EXTERNALSYM BG_E_HTTP_ERROR_400}

//
// MessageId: BG_E_HTTP_ERROR_401
//
// MessageText:
//
//  The requested resource requires user authentication.
//
  BG_E_HTTP_ERROR_401 = DWORD($80190191);
  {$EXTERNALSYM BG_E_HTTP_ERROR_401}

//
// MessageId: BG_E_HTTP_ERROR_402
//
// MessageText:
//
//  The server's response was not valid. The server was not following the defined protocol. Resume the job, and then Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_HTTP_ERROR_402 = DWORD($80190192);
  {$EXTERNALSYM BG_E_HTTP_ERROR_402}

//
// MessageId: BG_E_HTTP_ERROR_403
//
// MessageText:
//
//  The client does not have sufficient access rights to the requested server object.
//
  BG_E_HTTP_ERROR_403 = DWORD($80190193);
  {$EXTERNALSYM BG_E_HTTP_ERROR_403}

//
// MessageId: BG_E_HTTP_ERROR_404
//
// MessageText:
//
//  The requested URL does not exist on the server.
//
  BG_E_HTTP_ERROR_404 = DWORD($80190194);
  {$EXTERNALSYM BG_E_HTTP_ERROR_404}

//
// MessageId: BG_E_HTTP_ERROR_405
//
// MessageText:
//
//  The method used is not allowed.
//
  BG_E_HTTP_ERROR_405 = DWORD($80190195);
  {$EXTERNALSYM BG_E_HTTP_ERROR_405}

//
// MessageId: BG_E_HTTP_ERROR_406
//
// MessageText:
//
//  No responses acceptable to the client were found.
//
  BG_E_HTTP_ERROR_406 = DWORD($80190196);
  {$EXTERNALSYM BG_E_HTTP_ERROR_406}

//
// MessageId: BG_E_HTTP_ERROR_407
//
// MessageText:
//
//  Proxy authentication is required.
//
  BG_E_HTTP_ERROR_407 = DWORD($80190197);
  {$EXTERNALSYM BG_E_HTTP_ERROR_407}

//
// MessageId: BG_E_HTTP_ERROR_408
//
// MessageText:
//
//  The server timed out waiting for the request.
//
  BG_E_HTTP_ERROR_408 = DWORD($80190198);
  {$EXTERNALSYM BG_E_HTTP_ERROR_408}

//
// MessageId: BG_E_HTTP_ERROR_409
//
// MessageText:
//
//  The request could not be completed because of a conflict with the current state of the resource. The user should resubmit the request with more information.
//
  BG_E_HTTP_ERROR_409 = DWORD($80190199);
  {$EXTERNALSYM BG_E_HTTP_ERROR_409}

//
// MessageId: BG_E_HTTP_ERROR_410
//
// MessageText:
//
//  The requested resource is not currently available at the server, and no forwarding address is known.
//
  BG_E_HTTP_ERROR_410 = DWORD($8019019A);
  {$EXTERNALSYM BG_E_HTTP_ERROR_410}

//
// MessageId: BG_E_HTTP_ERROR_411
//
// MessageText:
//
//  The server cannot accept the request without a defined content length.
//
  BG_E_HTTP_ERROR_411 = DWORD($8019019B);
  {$EXTERNALSYM BG_E_HTTP_ERROR_411}

//
// MessageId: BG_E_HTTP_ERROR_412
//
// MessageText:
//
//  The precondition given in one or more of the request header fields evaluated to false when it was tested on the server.
//
  BG_E_HTTP_ERROR_412 = DWORD($8019019C);
  {$EXTERNALSYM BG_E_HTTP_ERROR_412}

//
// MessageId: BG_E_HTTP_ERROR_413
//
// MessageText:
//
//  The server cannot process the request because the request entity is too large.
//
  BG_E_HTTP_ERROR_413 = DWORD($8019019D);
  {$EXTERNALSYM BG_E_HTTP_ERROR_413}

//
// MessageId: BG_E_HTTP_ERROR_414
//
// MessageText:
//
//  The server cannot process the request because the request Uniform Resource Identifier (URI) is longer than the server can interpret.
//
  BG_E_HTTP_ERROR_414 = DWORD($8019019E);
  {$EXTERNALSYM BG_E_HTTP_ERROR_414}

//
// MessageId: BG_E_HTTP_ERROR_415
//
// MessageText:
//
//  The server's response was not valid. The server was not following the defined protocol. Resume the job, and then Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_HTTP_ERROR_415 = DWORD($8019019F);
  {$EXTERNALSYM BG_E_HTTP_ERROR_415}

//
// MessageId: BG_E_HTTP_ERROR_416
//
// MessageText:
//
//  The server could not satisfy the range request.
//
  BG_E_HTTP_ERROR_416 = DWORD($801901A0);
  {$EXTERNALSYM BG_E_HTTP_ERROR_416}

//
// MessageId: BG_E_HTTP_ERROR_417
//
// MessageText:
//
//  The server could not meet the expectation given in an Expect request-header field.
//
  BG_E_HTTP_ERROR_417 = DWORD($801901A1);
  {$EXTERNALSYM BG_E_HTTP_ERROR_417}

//
// MessageId: BG_E_HTTP_ERROR_449
//
// MessageText:
//
//   The server's response was not valid. The server was not following the defined protocol. Resume the job, and then Background Intelligent Transfer Service (BITS) will try again.
//
  BG_E_HTTP_ERROR_449 = DWORD($801901C1);
  {$EXTERNALSYM BG_E_HTTP_ERROR_449}

//
// MessageId: BG_E_HTTP_ERROR_500
//
// MessageText:
//
//  An unexpected condition prevented the server from fulfilling the request.
//
  BG_E_HTTP_ERROR_500 = DWORD($801901F4);
  {$EXTERNALSYM BG_E_HTTP_ERROR_500}

//
// MessageId: BG_E_HTTP_ERROR_501
//
// MessageText:
//
//  The server does not support the functionality required to fulfill the request.
//
  BG_E_HTTP_ERROR_501 = DWORD($801901F5);
  {$EXTERNALSYM BG_E_HTTP_ERROR_501}

//
// MessageId: BG_E_HTTP_ERROR_502
//
// MessageText:
//
//  The server, while acting as a gateway or proxy to fulfill the request, received an invalid response from the upstream server it accessed.
//
  BG_E_HTTP_ERROR_502 = DWORD($801901F6);
  {$EXTERNALSYM BG_E_HTTP_ERROR_502}

//
// MessageId: BG_E_HTTP_ERROR_503
//
// MessageText:
//
//  The service is temporarily overloaded.
//
  BG_E_HTTP_ERROR_503 = DWORD($801901F7);
  {$EXTERNALSYM BG_E_HTTP_ERROR_503}

//
// MessageId: BG_E_HTTP_ERROR_504
//
// MessageText:
//
//  The request was timed out waiting for a gateway.
//
  BG_E_HTTP_ERROR_504 = DWORD($801901F8);
  {$EXTERNALSYM BG_E_HTTP_ERROR_504}

//
// MessageId: BG_E_HTTP_ERROR_505
//
// MessageText:
//
//  The server does not support the HTTP protocol version that was used in the request message.
//
  BG_E_HTTP_ERROR_505 = DWORD($801901F9);
  {$EXTERNALSYM BG_E_HTTP_ERROR_505}

//
// MessageId: MC_JOB_CANCELLED
//
// MessageText:
//
//  The administrator %4 canceled job "%2" on behalf of %3.  The job ID was %1.
//
  MC_JOB_CANCELLED = DWORD($80194000);
  {$EXTERNALSYM MC_JOB_CANCELLED}

//
// MessageId: MC_FILE_DELETION_FAILED
//
// MessageText:
//
//  While canceling job "%2", BITS was not able to remove the temporary files listed below.
//  If you can delete them, then you will regain some disk space.  The job ID was %1.%\
//  
//  %3
//
  MC_FILE_DELETION_FAILED = DWORD($80194001);
  {$EXTERNALSYM MC_FILE_DELETION_FAILED}

//
// MessageId: MC_FILE_DELETION_FAILED_MORE
//
// MessageText:
//
//  While canceling job "%2", BITS was not able to remove the temporary files listed below.
//  If you can delete them, then you will regain some disk space.  The job ID was %1. %\
//  
//  %3
//  %\
//  Due to space limitations, not all files are listed here.  Check for additional files of the form BITxxx.TMP in the same directory.
//
  MC_FILE_DELETION_FAILED_MORE = DWORD($80194002);
  {$EXTERNALSYM MC_FILE_DELETION_FAILED_MORE}

//
// MessageId: MC_JOB_PROPERTY_CHANGE
//
// MessageText:
//
//  The administrator %3 modified the %4 property of job "%2".  The job ID was %1.
//
  MC_JOB_PROPERTY_CHANGE = DWORD($80194003);
  {$EXTERNALSYM MC_JOB_PROPERTY_CHANGE}

//
// MessageId: MC_JOB_TAKE_OWNERSHIP
//
// MessageText:
//
//  The administrator %4 took ownership of job "%2" from %3.  The job ID was %1.
//
  MC_JOB_TAKE_OWNERSHIP = DWORD($80194004);
  {$EXTERNALSYM MC_JOB_TAKE_OWNERSHIP}

//
// MessageId: MC_JOB_SCAVENGED
//
// MessageText:
//
//  Job "%2" owned by %3 was canceled after being inactive for more than %4 days.  The job ID was %1.
//
  MC_JOB_SCAVENGED = DWORD($80194005);
  {$EXTERNALSYM MC_JOB_SCAVENGED}

//
// MessageId: MC_JOB_NOTIFICATION_FAILURE
//
// MessageText:
//
//  Job "%2" owned by %3 failed to notify its associated application.  BITS will retry in %4 minutes.  The job ID was %1.
//
  MC_JOB_NOTIFICATION_FAILURE = DWORD($80194006);
  {$EXTERNALSYM MC_JOB_NOTIFICATION_FAILURE}

//
// MessageId: MC_STATE_FILE_CORRUPT
//
// MessageText:
//
//  The BITS job list is not in a recognized format.  It may have been created by a different version of BITS.  The job list has been cleared.
//
  MC_STATE_FILE_CORRUPT = DWORD($80194007);
  {$EXTERNALSYM MC_STATE_FILE_CORRUPT}

implementation

end.
