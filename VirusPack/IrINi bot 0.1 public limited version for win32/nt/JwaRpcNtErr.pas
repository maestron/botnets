{******************************************************************************}
{                                                       	               }
{ RPC Error Codes  API interface Unit for Object Pascal                        }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: rpcnterr.h, released June 2000. The original Pascal    }
{ code is: RpcNtErr.pas, released December 2000. The initial developer of the  }
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

unit JwaRpcNtErr;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "RpcNtErr.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

uses
  JwaWinError;

{*********************************************************/
/**               Microsoft LAN Manager                 **/
/**       Copyright(c) Microsoft Corp., 1987-1999       **/
/**                                                     **/
/**     Rpc Error Codes from the compiler and runtime   **/
/**                                                     **/
/*********************************************************}

const
  RPC_S_OK                         = ERROR_SUCCESS;
  {$EXTERNALSYM RPC_S_OK}
  RPC_S_INVALID_ARG                = ERROR_INVALID_PARAMETER;
  {$EXTERNALSYM RPC_S_INVALID_ARG}
  RPC_S_OUT_OF_MEMORY              = ERROR_OUTOFMEMORY;
  {$EXTERNALSYM RPC_S_OUT_OF_MEMORY}
  RPC_S_OUT_OF_THREADS             = ERROR_MAX_THRDS_REACHED;
  {$EXTERNALSYM RPC_S_OUT_OF_THREADS}
  RPC_S_INVALID_LEVEL              = ERROR_INVALID_PARAMETER;
  {$EXTERNALSYM RPC_S_INVALID_LEVEL}
  RPC_S_BUFFER_TOO_SMALL           = ERROR_INSUFFICIENT_BUFFER;
  {$EXTERNALSYM RPC_S_BUFFER_TOO_SMALL}
  RPC_S_INVALID_SECURITY_DESC      = ERROR_INVALID_SECURITY_DESCR;
  {$EXTERNALSYM RPC_S_INVALID_SECURITY_DESC}
  RPC_S_ACCESS_DENIED              = ERROR_ACCESS_DENIED;
  {$EXTERNALSYM RPC_S_ACCESS_DENIED}
  RPC_S_SERVER_OUT_OF_MEMORY       = ERROR_NOT_ENOUGH_SERVER_MEMORY;
  {$EXTERNALSYM RPC_S_SERVER_OUT_OF_MEMORY}
  RPC_S_ASYNC_CALL_PENDING         = ERROR_IO_PENDING;
  {$EXTERNALSYM RPC_S_ASYNC_CALL_PENDING}
  RPC_S_UNKNOWN_PRINCIPAL          = ERROR_NONE_MAPPED;
  {$EXTERNALSYM RPC_S_UNKNOWN_PRINCIPAL}
  RPC_S_TIMEOUT                    = ERROR_TIMEOUT;
  {$EXTERNALSYM RPC_S_TIMEOUT}

  RPC_X_NO_MEMORY                  = RPC_S_OUT_OF_MEMORY;
  {$EXTERNALSYM RPC_X_NO_MEMORY}
  RPC_X_INVALID_BOUND              = RPC_S_INVALID_BOUND;
  {$EXTERNALSYM RPC_X_INVALID_BOUND}
  RPC_X_INVALID_TAG                = RPC_S_INVALID_TAG;
  {$EXTERNALSYM RPC_X_INVALID_TAG}
  RPC_X_ENUM_VALUE_TOO_LARGE       = RPC_X_ENUM_VALUE_OUT_OF_RANGE;
  {$EXTERNALSYM RPC_X_ENUM_VALUE_TOO_LARGE}
  RPC_X_SS_CONTEXT_MISMATCH        = ERROR_INVALID_HANDLE;
  {$EXTERNALSYM RPC_X_SS_CONTEXT_MISMATCH}
  RPC_X_INVALID_BUFFER             = ERROR_INVALID_USER_BUFFER;
  {$EXTERNALSYM RPC_X_INVALID_BUFFER}
  RPC_X_PIPE_APP_MEMORY            = ERROR_OUTOFMEMORY;
  {$EXTERNALSYM RPC_X_PIPE_APP_MEMORY}
  RPC_X_INVALID_PIPE_OPERATION     = RPC_X_WRONG_PIPE_ORDER;
  {$EXTERNALSYM RPC_X_INVALID_PIPE_OPERATION}

implementation

end.
