{******************************************************************************}
{                                                       	               }
{ Active Directory Class Names API interface Unit for Object Pascal            }
{                                                       	               }
{ Portions created by Microsoft are Copyright (C) 1995-2001 Microsoft          }
{ Corporation. All Rights Reserved.                                            }
{ 								               }
{ The original file is: adsnms.h, released June 2000. The original Pascal      }
{ code is: AdsNms.pas, released December 2000. The initial developer of the    }
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

unit JwaAdsnms;

{$WEAKPACKAGEUNIT}

{$HPPEMIT ''}
{$HPPEMIT '#include "adsnms.h"'}
{$HPPEMIT ''}

{$I WINDEFINES.INC}

interface

//  Contents:   Class Names and schema definitions for ADS objects

const
  NAMESPACE_CLASS_NAME        = 'Namespace';
  {$EXTERNALSYM NAMESPACE_CLASS_NAME}
  COUNTRY_CLASS_NAME          = 'Country';
  {$EXTERNALSYM COUNTRY_CLASS_NAME}
  LOCALITY_CLASS_NAME         = 'Locality';
  {$EXTERNALSYM LOCALITY_CLASS_NAME}
  ORGANIZATION_CLASS_NAME     = 'Organization';
  {$EXTERNALSYM ORGANIZATION_CLASS_NAME}
  ORGANIZATIONUNIT_CLASS_NAME = 'Organizational Unit';
  {$EXTERNALSYM ORGANIZATIONUNIT_CLASS_NAME}
  DOMAIN_CLASS_NAME           = 'Domain';
  {$EXTERNALSYM DOMAIN_CLASS_NAME}
  COMPUTER_CLASS_NAME         = 'Computer';
  {$EXTERNALSYM COMPUTER_CLASS_NAME}
  USER_CLASS_NAME             = 'User';
  {$EXTERNALSYM USER_CLASS_NAME}
  GROUP_CLASS_NAME            = 'Group';
  {$EXTERNALSYM GROUP_CLASS_NAME}
  GLOBALGROUP_CLASS_NAME      = 'GlobalGroup';
  {$EXTERNALSYM GLOBALGROUP_CLASS_NAME}
  LOCALGROUP_CLASS_NAME       = 'LocalGroup';
  {$EXTERNALSYM LOCALGROUP_CLASS_NAME}
  SERVICE_CLASS_NAME          = 'Service';
  {$EXTERNALSYM SERVICE_CLASS_NAME}
  FILESERVICE_CLASS_NAME      = 'FileService';
  {$EXTERNALSYM FILESERVICE_CLASS_NAME}
  SESSION_CLASS_NAME          = 'Session';
  {$EXTERNALSYM SESSION_CLASS_NAME}
  RESOURCE_CLASS_NAME         = 'Resource';
  {$EXTERNALSYM RESOURCE_CLASS_NAME}
  FILESHARE_CLASS_NAME        = 'FileShare';
  {$EXTERNALSYM FILESHARE_CLASS_NAME}
  PRINTER_CLASS_NAME          = 'PrintQueue';
  {$EXTERNALSYM PRINTER_CLASS_NAME}
  PRINTJOB_CLASS_NAME         = 'PrintJob';
  {$EXTERNALSYM PRINTJOB_CLASS_NAME}
  SCHEMA_CLASS_NAME           = 'Schema';
  {$EXTERNALSYM SCHEMA_CLASS_NAME}
  CLASS_CLASS_NAME            = 'Class';
  {$EXTERNALSYM CLASS_CLASS_NAME}
  PROPERTY_CLASS_NAME         = 'Property';
  {$EXTERNALSYM PROPERTY_CLASS_NAME}
  SYNTAX_CLASS_NAME           = 'Syntax';
  {$EXTERNALSYM SYNTAX_CLASS_NAME}
  ROOTDSE_CLASS_NAME          = 'RootDSE';
  {$EXTERNALSYM ROOTDSE_CLASS_NAME}

  NO_SCHEMA                    = '';
  {$EXTERNALSYM NO_SCHEMA}
  DOMAIN_SCHEMA_NAME           = 'Domain';
  {$EXTERNALSYM DOMAIN_SCHEMA_NAME}
  COMPUTER_SCHEMA_NAME         = 'Computer';
  {$EXTERNALSYM COMPUTER_SCHEMA_NAME}
  USER_SCHEMA_NAME             = 'User';
  {$EXTERNALSYM USER_SCHEMA_NAME}
  GROUP_SCHEMA_NAME            = 'Group';
  {$EXTERNALSYM GROUP_SCHEMA_NAME}
  GLOBALGROUP_SCHEMA_NAME      = 'GlobalGroup';
  {$EXTERNALSYM GLOBALGROUP_SCHEMA_NAME}
  LOCALGROUP_SCHEMA_NAME       = 'LocalGroup';
  {$EXTERNALSYM LOCALGROUP_SCHEMA_NAME}
  SERVICE_SCHEMA_NAME          = 'Service';
  {$EXTERNALSYM SERVICE_SCHEMA_NAME}
  PRINTER_SCHEMA_NAME          = 'PrintQueue';
  {$EXTERNALSYM PRINTER_SCHEMA_NAME}
  PRINTJOB_SCHEMA_NAME         = 'PrintJob';
  {$EXTERNALSYM PRINTJOB_SCHEMA_NAME}
  FILESERVICE_SCHEMA_NAME      = 'FileService';
  {$EXTERNALSYM FILESERVICE_SCHEMA_NAME}
  SESSION_SCHEMA_NAME          = 'Session';
  {$EXTERNALSYM SESSION_SCHEMA_NAME}
  RESOURCE_SCHEMA_NAME         = 'Resource';
  {$EXTERNALSYM RESOURCE_SCHEMA_NAME}
  FILESHARE_SCHEMA_NAME        = 'FileShare';
  {$EXTERNALSYM FILESHARE_SCHEMA_NAME}
  FPNW_FILESERVICE_SCHEMA_NAME = 'FPNWFileService';
  {$EXTERNALSYM FPNW_FILESERVICE_SCHEMA_NAME}
  FPNW_SESSION_SCHEMA_NAME     = 'FPNWSession';
  {$EXTERNALSYM FPNW_SESSION_SCHEMA_NAME}
  FPNW_RESOURCE_SCHEMA_NAME    = 'FPNWResource';
  {$EXTERNALSYM FPNW_RESOURCE_SCHEMA_NAME}
  FPNW_FILESHARE_SCHEMA_NAME   = 'FPNWFileShare';
  {$EXTERNALSYM FPNW_FILESHARE_SCHEMA_NAME}

implementation

end.
